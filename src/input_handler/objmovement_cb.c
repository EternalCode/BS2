#include <pokeagb/pokeagb.h>
#include "../battler_data/battler_data.h"
#include "../map_data/map_movement_permissions.h"
#include "../battle_state.h"
#include "../battler_data/pokemon_base.h"

#define ARRAY_COORDX(x) ((x - 10) / 6)
#define ARRAY_COORDY(y) ((y + 6) / 6)

/* This is only for player objects to check map movability permissions */
void map_boundary_check(struct Object* obj, u16 x, u16 y, s16 x_displace, s16 y_displace) {  
    u16 result_x = x + x_displace;
    u16 result_y = y + y_displace; 
    
    u16 x_coord = ARRAY_COORDX(result_x);
    u16 y_coord = ARRAY_COORDY(result_y);
    
    // if obj->priv[4], ignore array value 2
    // else ignore array value 3
    u8 ignored_unit = 3 - (1 * obj->priv[4]);
    
    if ((!world_state->map->map_2d[y_coord][ARRAY_COORDX(x)]) ||
        (world_state->map->map_2d[y_coord][ARRAY_COORDX(x)] == ignored_unit)) {
        // the Y coordinate displacement is applicable
        obj->pos1.y = result_y;
    }
    
    if ((!world_state->map->map_2d[ARRAY_COORDY(y)][x_coord]) ||
        (world_state->map->map_2d[ARRAY_COORDY(y)][x_coord] == ignored_unit)) {
        // the X coordinate displacement is applicable
        obj->pos1.x = result_x;
    }
    
    // Object location logging
    if (obj->priv[4]) {
        // erase old world state
        world_state->map->map_2d[player->map_y][player->map_x] = 0;
        
        //write new state player locally
        player->map_x = ARRAY_COORDX(obj->pos1.x);
        player->map_y = ARRAY_COORDY(obj->pos1.y);
        
        // Player in world state update
        world_state->map->map_2d[ARRAY_COORDY(obj->pos1.y)][ARRAY_COORDX(obj->pos1.x)] = 2;
    } else {
        // erase old world state
        world_state->map->map_2d[opponent->map_y][opponent->map_x] = 0;
        
        //write new state opp locally
        opponent->map_x = ARRAY_COORDX(obj->pos1.x);
        opponent->map_y = ARRAY_COORDY(obj->pos1.y);
        
        // Opp in world state update
        world_state->map->map_2d[ARRAY_COORDY(obj->pos1.y)][ARRAY_COORDX(obj->pos1.x)] = 3; // Opp in world state        
    } 
    
}


/*
 * Object private variable representation:
 *
 * Priv[0] = Frame delay counter
 * Priv[1] = Frame to show
 * Priv[2] = Animation looped flag
 * Priv[3] = Is active flag
 * Priv[4] = Is player
 * Priv[5] = Shaking delay
 * Priv[6] = Shaking dir
 * Priv[7] = frame_id
 *
 */

void animation_sprite_shake(struct Object* obj, u8 amount, u8 delay) {
    obj->priv[5]++;
    if (obj->priv[5] < delay) {
        return;
    }
    obj->priv[5] = 0;
    obj->pos1.x += (obj->priv[6]) ? 0 : amount;
    obj->pos1.x -= (obj->priv[6]) ? amount : 0;
    obj->priv[6] = !obj->priv[6];
}

void animation_frame_handler(struct Object* obj, u8 frame_start, u8 frame_end, u16 frame_duration[],
                                    u8 looptimes, s8 x_displace, s8 y_displace, u8 idle_state) {
    // animation delay
    obj->priv[0]++;
    if (obj->priv[0] > frame_duration[obj->priv[7]]) {
        obj->priv[0] = 0;
        obj->priv[7]++;
    } else {
        return;
    }
    // check which frame to execute next
    obj->priv[1] = (obj->priv[1] < frame_start) ? frame_start : obj->priv[1];
    obj->priv[1] = ((obj->priv[1] >= frame_end) ? (frame_start) : (obj->priv[1] + 1));
    u8 frame = obj->priv[1];
    if ((frame == frame_start) && (obj->priv[2] > 0) && (looptimes != 0xFF)) {
        // animation ended
        extern void cb_battler_idle_F(struct Object*);
        extern void cb_battler_idle_B(struct Object*);
        if (idle_state) {
            obj->callback = (obj->priv[4]) ? p_base[player->species].idle_B : p_base[opponent->species].idle_B;
        } else {
            obj->callback = (obj->priv[4]) ? p_base[player->species].idle_F : p_base[opponent->species].idle_F;
        }
        if (obj->priv[4]) {
            player->bstate = BATTLER_MOVEMENT;
        } else {
            opponent->bstate = BATTLER_MOVEMENT;
        }
        obj->priv[0] = 0xFF;
        obj->priv[7] = 0;
         // jumps to new frame immediately
    } else {
        // animation starting
        void* dst = (void*)((obj->final_oam.tile_num * 32) + SPRITE_RAM);
        void* src = (obj->priv[4]) ? p_base[player->species].image_data : p_base[opponent->species].image_data;
        
        src += (32 * 4 * 4 * frame);
        memcpy(dst, src, (32 * 4 * 4));
        map_boundary_check(obj, obj->pos1.x, obj->pos1.y, x_displace, y_displace);
        obj->priv[2]++;            
    }
}


u8 animation_frame_handler_move(struct Object* obj, u8 frame_start, u8 frame_end,
                                u16 frame_duration[], s8 x_displace, s8 y_displace,
                                void* src, u8 loop_times) {
    // animation delay
    obj->priv[0]++;
    if (obj->priv[0] > frame_duration[obj->priv[1] - frame_start]) {
        obj->priv[0] = 0;
    } else {
        return 0;
    }
    // check which frame to execute next
    obj->priv[1] = (obj->priv[1] < frame_start) ? frame_start : obj->priv[1];
    obj->priv[1] = ((obj->priv[1] >= frame_end) ? (frame_start) : (obj->priv[1] + 1));
    u8 frame = obj->priv[1];
    if (frame == frame_start) {
        obj->priv[4]++;
    }
    if (obj->priv[4] > loop_times) {
        // animation ended
        return 1;
    } else {
        // animation starting
        void* dst = (void*)((obj->final_oam.tile_num * 32) + SPRITE_RAM);        
        src += (32 * 4 * 4 * frame);
        memcpy(dst, src, (32 * 4 * 4));
        obj->pos1.x += x_displace;
        obj->pos1.y += y_displace;
        return 0;
    }   
}

void obj_attack_free(struct Object* obj) {
    switch (obj->priv[3]) {
        case 1:
            player->objid_move = 0;
            break;
        default:
            opponent->objid_move = 0;
    };
    obj_free(obj);
    return;
}




