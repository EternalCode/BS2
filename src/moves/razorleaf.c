#include <pokeagb/pokeagb.h>
#include "../move_animations.h"
#include "../battler_data/battler_data.h"
#include "move_table.h"

extern void world_state_remove_obj(struct Object* obj);
extern u8 create_move(u16 moveid, s16 x, s16 y, u8 side, u8 hitbox, u8 hitbox2);
extern u8 animation_frame_handler_move(struct Object* obj, u8 frame_start, u8 frame_end, u16 frame_duration[],
                                    s8 x_displace, s8 y_displace, void* src, u8 loop_times, u8 size);
extern s8* direction_mod(u8 distance, enum BattlerFacingDir dir, s8* delta);
extern void obj_attack_free(struct Object* obj);
                                   
void razor_leaf_anim(struct Object* obj) {
    // cycle frames
    u16 frame_duration[] = {3, 3, 3, 3, 3, 3, 3, 3};
    s8 delta[] = {0, 0};
    direction_mod(4, obj->priv[6], (s8*)&delta);
    if (animation_frame_handler_move(obj, 0, 7, frame_duration, *delta, *(delta + 1), &razor_leafTiles, 4, 1) ||
        obj->pos1.y >  160 || obj->pos1.x > 460) {
        world_state_remove_obj(obj);
        obj_attack_free(obj);
    }
    return;
}


void exec_razorleaf(enum BattlerFacingDir orientation, struct battler* fighter, struct Object* obj) {
        s16 move_x, move_y;
        switch (orientation) {
        case FACING_LEFT:
            move_x = obj->pos1.x;
            move_y = obj->pos1.y;
            break;
        default:
            move_x = obj->pos1.x + ((8 << obj->final_oam.size) >> 2);
            move_y = obj->pos1.y;
            break;
        };
        u8 objid = create_move(INDEX_RAZORLEAF, move_x, move_y, obj->priv[4], 32 - move[INDEX_RAZORLEAF].hitbox_x, 32 - move[INDEX_RAZORLEAF].hitbox_y);
        fighter->objid_move = objid;
        objects[objid].priv[3] = fighter->obj_id;
        objects[objid].priv[7] = move[INDEX_RAZORLEAF].base_dmg;
        objects[objid].priv[6] = orientation;
}

