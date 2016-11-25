#include <pokeagb/pokeagb.h>
#include "../battler_data/battler_data.h"
#include "../../generated/images/battlers_frames/001.h"
#include "../map_data/map_movement_permissions.h"
#include "../battle_state.h"

#define ARRAY_COORDX(x) ((x - 10) / 6)
#define ARRAY_COORDY(y) ((y + 6) / 6)

static struct battler* opponent = (struct battler*)0x202024C;
static struct battler* player = (struct battler*)0x2024284;

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
 *
 */
 

void animation_frame_handler(struct Object* obj, u8 frame_start, u8 frame_end, u8 frame_duration,
                            u8 looptimes, s8 x_displace, s8 y_displace) {
    // animation delay
    obj->priv[0]++;
    if (obj->priv[0] > frame_duration) {
        obj->priv[0] = 0;
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
        obj->callback = cb_battler_idle_F;
        obj->priv[3] = 0;
        obj->priv[0] = 19;
    } else {
        // animation starting
        void* dst = (void*)((obj->final_oam.tile_num * 32) + SPRITE_RAM);
        void* src = (void*)&_01Tiles[(32 * 4 * 4 * frame)];
        memcpy(dst, src, (32 * 4 * 4));
        map_boundary_check(obj, obj->pos1.x, obj->pos1.y, x_displace, y_displace);
        obj->priv[2]++;            
    }
}


// Idle state facing forward
void cb_battler_idle_F(struct Object* obj) {
    animation_frame_handler(obj, 0, 3, 20, 0xFF, 0, 0); 
}

// up_left
void cb_battler_UL(struct Object* obj) {
    animation_frame_handler(obj, 15, 18, 5, 1, -2, -2);
}

// up_right
void cb_battler_UR(struct Object* obj) {
    animation_frame_handler(obj, 15, 18, 5, 1, 2, -2);
}

// down_left
void cb_battler_DL(struct Object* obj) {
    animation_frame_handler(obj, 12, 15, 5, 1, -2, 2);
}

// down_right
void cb_battler_DR(struct Object* obj) {
    animation_frame_handler(obj, 12, 15, 5, 1, 2, 2);
}

// left
void cb_battler_L(struct Object* obj) {
    animation_frame_handler(obj, 3, 6, 5, 1, -4, 0);
}

// right
void cb_battler_R(struct Object* obj) {
    animation_frame_handler(obj, 3, 6, 5, 1, 4, 0);
}

// up
void cb_battler_U(struct Object* obj) {
    // based on side facing, use other frame
    animation_frame_handler(obj, 9, 12, 5, 1, 0, -4);
}

// down
void cb_battler_D(struct Object* obj) {
    // based on side facing, use other frame
    animation_frame_handler(obj, 6, 9, 5, 1, 0, 4);
}



