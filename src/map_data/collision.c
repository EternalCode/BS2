#include <pokeagb/pokeagb.h>
#include "../battle_state.h"

extern u8 get_objid(struct Object* obj);

enum SideOrientation {
    SIDE_WIDTH,
    SIDE_HEIGHT,
};


bool range_intersect(u16 min, u16 max, u16 min2, u16 max2) {
    return ((MAX(min, max) >=  MIN(min2, max2)) &&
            (MIN(min, max) <= MAX(min2, max2)));
}


void get_hitbox_side(struct Object* obj, enum SideOrientation side, u8 (*points)[2], u8 hitbox) {
    if (side == SIDE_WIDTH) {
        // assuming all objects are square
        *points[0] = obj->pos1.x + ((8 << obj->final_oam.size) >> 2);
        ((*points) + 1)[0] = obj->pos1.x + (8 << obj->final_oam.size);
    } else {
        // Utilize table to figure pixel reduction from top
        *points[0] = obj->pos1.y + hitbox;
        ((*points) + 1)[0] = obj->pos1.y + (8 << obj->final_oam.size);    
    }
    return;
}


bool check_collision(struct Object* obj, struct Object* obj2, u8 hitbox, u8 hitbox2) {
    u8 magnitude_one_w[2] = {0, 0};
    u8 magnitude_one_h[2] = {0, 0};
    u8 magnitude_two_w[2] = {0, 0};
    u8 magnitude_two_h[2] = {0, 0};
    
    // update magnitude arrays for w/h for each object
    get_hitbox_side(obj, SIDE_WIDTH, &magnitude_one_w,  hitbox);
    get_hitbox_side(obj, SIDE_HEIGHT, &magnitude_one_h,  hitbox);
    
    get_hitbox_side(obj2, SIDE_WIDTH, &magnitude_two_w,  hitbox2);
    get_hitbox_side(obj2, SIDE_HEIGHT, &magnitude_two_h,  hitbox2);
    
    // check intersection
    return (range_intersect(magnitude_one_w[0], magnitude_one_w[1], magnitude_two_w[0], magnitude_two_w[1]) &&
            range_intersect(magnitude_one_h[0], magnitude_one_h[1], magnitude_two_h[0], magnitude_two_h[1]));
}


void evaluate_world_collision() {
    /* u8 i, j;
    for (i = 0; i < 6; i++) {
        struct map_objects map_obji = world_state->map_obj[i];
        if (map_obji.objid == 0x3F) {
            continue;
        }
        for (j = 0; j < 6; j++) {
            struct map_objects map_objj = world_state->map_obj[j];
            if (map_objj.objid == 0x3F) {
                continue;
            }
            // if they are the same object, ignore
            if (i == j) {
                continue;
            }
            
            // check collision, if no collision, continue
            struct Object* obj1 = &objects[map_obji.objid];
            struct Object* obj2 = &objects[map_objj.objid];
            if (!check_collision(obj1, obj2, map_obji.hitbox_x, map_objj.hitbox_x)) {
                continue;
            }
            
            // collision between two battlers, pass. May changle this later
            if ((map_obji.type == BATTLER_OBJ) && (map_objj.type == BATTLER_OBJ)) {
                continue;

            // collision between two moves, cancel weaker move, reduce remaining move's damage parameter
            } else if ((map_obji.type == MOVE_OBJ) && (map_objj.type == MOVE_OBJ)) {
                // explosion? delete smaller one
                continue;
            } else {
                // one is a battler, other is a move particle

                // check if move particle belongs to battler
                
                
                if (map_obji.type == BATTLER_OBJ) {
                    // Battler take damage
                    if (objects[map_objj.objid].priv[3] == get_objid(obj1)) {
                        continue;   
                    } else {
                        // do damage
                        //*var = 0x78;
                        //*(var
                    }
                } else {
                    // Battler take damage
                    if (objects[map_obji.objid].priv[3] == get_objid(obj2)) {
                        continue;
                    } else {
                        // do damage
                        extern void dmg_bar(u8 side, u8 start, u8 to);
                        dmg_bar(objects[map_objj.objid].priv[4], 64, 20);
                        break;
                        
                    }
                }
            }
                
        }
    }         */
}




