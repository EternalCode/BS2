#include <pokeagb/pokeagb.h>
#include "../move_animations.h"
#include "../battler_data/battler_data.h"
#include "move_table.h"

extern void world_state_remove_obj(struct Object* obj);
extern u8 create_move(u16 moveid, s16 x, s16 y, u8 side, u8 hitbox, u8 hitbox2);
extern u8 animation_frame_handler_move(struct Object* obj, u8 frame_start, u8 frame_end, u16 frame_duration[],
                                    s8 x_displace, s8 y_displace, void* src, u8 loop_times, u8 size);
extern void obj_attack_free(struct Object* obj);
                                   
void x_scissor_anim(struct Object* obj) {
    // cycle frames
    u16 frame_duration[] = {2, 4, 8, 4, 2};
    if (animation_frame_handler_move(obj, 0, 4, frame_duration, 0, 0, &x_scissorTiles, 0, 1)) {
        world_state_remove_obj(obj);
        obj_attack_free(obj);
    }
    return;
}


void exec_x_scissor(struct battler* fighter) {
        struct Object* obj = &objects[fighter->obj_id];
        
        // mod position to spawn swords dance animation
        s16 move_y = obj->pos1.y + 16;
        s16 move_x = obj->pos1.x + ((fighter->dir == FACING_RIGHT) ? -8 : 32);
        u8 objid = create_move(INDEX_XSCISSOR, move_x, move_y, obj->priv[4], move[INDEX_XSCISSOR].hitbox_x, move[INDEX_XSCISSOR].hitbox_y);
        fighter->objid_move = objid;
        objects[objid].priv[3] = fighter->obj_id;
}

