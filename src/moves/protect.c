#include <pokeagb/pokeagb.h>
#include "../move_animations.h"
#include "../battler_data/battler_data.h"
#include "move_table.h"

extern void world_state_remove_obj(struct Object* obj);
extern u8 create_move(u16 moveid, s16 x, s16 y, u8 side, u8 hitbox, u8 hitbox2);
extern u8 animation_frame_handler_move(struct Object* obj, u8 frame_start, u8 frame_end, u16 frame_duration[],
                                    s8 x_displace, s8 y_displace, void* src, u8 loop_times, u8 size);
extern void obj_attack_free(struct Object* obj);

void protect_anim(struct Object* obj) {
    struct battler* fighter = (obj->priv[3]) ? player : opponent;
    // cycle frames
    u16 frame_duration[] = {3, 1, 3};
    if (animation_frame_handler_move(obj, 0, 1, frame_duration, 0, 0, &protectTiles, 10, 2)) {
        world_state_remove_obj(obj);
        obj_attack_free(obj);
    }
    return;
}


void exec_protect(struct battler* fighter) {
        struct Object* obj = &objects[fighter->obj_id];
        s16 move_x = obj->pos1.x;
        s16 move_y = obj->pos1.y;
        u8 objid = create_move(INDEX_PROTECT, move_x, move_y, obj->priv[4], 0, 0);
        fighter->objid_move = objid;
        objects[objid].priv[3] = fighter->obj_id;
        objects[objid].priv[7] = move[INDEX_RAZORLEAF].base_dmg;
}


