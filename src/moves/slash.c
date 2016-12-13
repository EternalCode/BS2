#include <pokeagb/pokeagb.h>
#include "../move_animations.h"
#include "../battler_data/battler_data.h"
#include "move_table.h"

extern void world_state_remove_obj(struct Object* obj);
extern u8 create_move(u16 moveid, s16 x, s16 y, u8 side, u8 hitbox, u8 hitbox2);
extern u8 animation_frame_handler_move(struct Object* obj, u8 frame_start, u8 frame_end, u16 frame_duration[],
                                    s8 x_displace, s8 y_displace, void* src, u8 loop_times, u8 size);
extern void obj_attack_free(struct Object* obj);
                                   
void slash_anim(struct Object* obj) {
    // cycle frames
    u16 frame_duration[] = {10, 5, 5};
    if (animation_frame_handler_move(obj, 0, 1, frame_duration, 0, 0, move[obj->priv[6]].move_img, 0, 1)) {
        world_state_remove_obj(obj);
        obj_attack_free(obj);
    }
    return;
}


void exec_slash(struct battler* fighter) {
        struct Object* obj = &objects[fighter->obj_id];
        
        // use left or right oriented slash image
        u16 move_id = (fighter->dir == FACING_RIGHT) ? INDEX_SLASH_LEFT : INDEX_SLASH_RIGHT;
        
        // mod position to spawn slash particle
        s16 move_y = obj->pos1.y + 16;
        s16 move_x = obj->pos1.x + ((fighter->dir == FACING_RIGHT) ? -8 : 32);
        
        u8 objid = create_move(move_id, move_x, move_y, obj->priv[4], move[move_id].hitbox_x, move[move_id].hitbox_y);
        fighter->objid_move = objid;
        objects[objid].priv[3] = fighter->obj_id;
        objects[objid].priv[6] = move_id;
}

