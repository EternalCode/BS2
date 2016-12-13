#include <pokeagb/pokeagb.h>
#include "../battler_data/battler_data.h"
#include "../battler_data/pokemon_base.h"
#include "../battle_state.h"

#define DEFAULT_SCALE_X 0x100
#define DEFAULT_SCALE_y 0x100

#define DEF_OBJ_SCALE 0x9A
#define GROUND_Y 0x60
#define WORLD_GRAVITY -1
#define GRAVITY_FREQUENCY 10
#define X_BOUNDARY_LEFT -8
#define X_BOUNDARY_RIGHT 188

void set_affine(s16* affine) {
    __asm__("swi 0xF");
    return;
}

void update_world() {
    struct Object* pc = &objects[player->obj_id];
    struct Object* oc = &objects[opponent->obj_id];
    
    // judge absolute distance of sprites
    s16 distance = 0;
    distance += (MAX(pc->pos1.x, oc->pos1.x) - MIN(pc->pos1.x, oc->pos1.x));
    distance += (MAX(pc->pos1.y, oc->pos1.y) - MIN(pc->pos1.y, oc->pos1.y));
    distance = ABS(distance);
    distance = distance >> 2;
 
    // bg is updated when player or opponent not using special move
    if ((!player->boosting)) { 
        // scale BG
        lcd_io_set(0x20, DEFAULT_SCALE_X + (distance << 1)); // X-scale
        lcd_io_set(0x26, DEFAULT_SCALE_y + (distance << 1)); // Y-scale
        
        // incorporate new BG positions based on scale factor
        bgid_mod_y_offset(2, (174 - (distance)) << 8 , 0);
        bgid_mod_x_offset(2, (0 - ((distance * 2) + (distance - distance))) << 8, 0);
    }
    // scale world objects by scale factor
    u8 i;
    for (i = 0; i < 6; i++) {
        struct Object* obj = &objects[world_state->map_obj[i].objid];
        obj->final_oam.affine_mode = 3;
        obj_id_set_rotscale(world_state->map_obj[i].objid,
                            DEF_OBJ_SCALE + (distance << 1), // PA - scale X
                            DEF_OBJ_SCALE + (distance << 1), // PB - scale Y
                            DEF_OBJ_SCALE + (distance << 1), // PC
                            DEF_OBJ_SCALE + (distance << 1)  // PD
        );
    }
    // fighters set movement state after jump completes & falling
    extern void modify_jump_state(u8 side);
    modify_jump_state(0);
    modify_jump_state(1);

    // apply positional vectors to fighters
    extern void vectors_apply(u8 side);
    vectors_apply(0);
    vectors_apply(1);
    
    // animation sprite shake
   
    s16* pos = (s16*)0x20370B8;
    *pos = objects[player->obj_id].pos1.x;
}

void vectors_apply(u8 side) {
    struct battler* fighter = (side) ? player : opponent;
    struct Object* obj = &objects[fighter->obj_id];
    
    // Apply gravity to y component of movement vector    
    // TODO: Should I add mass?
    fighter->delta_time++;
    s16 mass_gravity = WORLD_GRAVITY - p_base[fighter->species].weight;
    fighter->delta_y += mass_gravity * (fighter->delta_time / GRAVITY_FREQUENCY);
    obj->pos1.y -= fighter->delta_y;
    
    // prevent falling through the floor
    if (obj->pos1.y >= GROUND_Y) {
        obj->pos1.y =  GROUND_Y;
        fighter->has_jumped = false;
    } else {
        fighter->has_jumped = true;
    }
    
    // delay to offset call frequency
    if (fighter->x_delay_timer % fighter->x_delay_time) {
        fighter->x_delay_timer = 0;
        obj->pos1.x += fighter->delta_x;
        obj->pos1.x = (obj->pos1.x < X_BOUNDARY_LEFT) ? X_BOUNDARY_LEFT : obj->pos1.x;
        obj->pos1.x = (obj->pos1.x > X_BOUNDARY_RIGHT) ? X_BOUNDARY_RIGHT : obj->pos1.x;
    } else {
        fighter->x_delay_timer++;
    }
}


u8 get_objid(struct Object* obj) {
  u8 i;
    for (i = 0; i < 0x3F; i++) {
        if ((u32)&objects[i] == (u32)obj)
            return i;
    }
    return 0x3F;
}


void world_state_remove_obj(struct Object* obj) {
    u8 id = get_objid(obj);
    u8 j;
    for (j = 0; j < 6; j++) {
        if (world_state->map_obj[j].objid == id) {
            world_state->map_obj[j].objid = 0x3F;
            return;
        }
    }
}


void world_state_add_obj(u8 hitbox, u8 hitbox2, u8 objid, enum ObjectType type, u16 index) {
    u8 i;
    for (i = 0; i < 6; i++) {
        if (world_state->map_obj[i].objid == 0x3F) {
            world_state->map_obj[i].hitbox_x = hitbox;
            world_state->map_obj[i].hitbox_y = hitbox2;
            world_state->map_obj[i].objid = objid;
            world_state->map_obj[i].type = type;
            world_state->map_obj[i].index = index;
            return;
        }
    }
}

void modify_jump_state(u8 side) {
    // object change to movement state if on floor
    struct battler* fighter = (side) ? player : opponent;
    s16 fighter_pos = objects[fighter->obj_id].pos1.y;
    
    // enable jumping flag if not on floor
    if ((fighter_pos == GROUND_Y) &&
        (fighter->bstate != BATTLER_UNCONTROLLABLE_JUMPING)) {
        // fighter is on the ground
        fighter->has_jumped = false;
    } else {
        fighter->has_jumped = true;
    }   
}


