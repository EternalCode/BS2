#include <pokeagb/pokeagb.h>
#include "../move_animations.h"
#include "../battler_data/battler_data.h"
#include "move_table.h"

extern void world_state_remove_obj(struct Object* obj);
extern u8 create_move(u16 moveid, s16 x, s16 y, u8 side, u8 hitbox, u8 hitbox2);
extern u8 animation_frame_handler_move(struct Object* obj, u8 frame_start, u8 frame_end, u16 frame_duration[],
                                    s8 x_displace, s8 y_displace, void* src, u8 loop_times, u8 size);
extern void obj_attack_free(struct Object* obj);
                                   
void swords_dance_anim(struct Object* obj) {
    // cycle frames
    u16 frame_duration[] = {2, 2, 2};
    u16 frame_duration2[] = {6, 6, 6};
    animation_frame_handler_move(&(objects[obj->priv[6]]), 0, 1, frame_duration2, 0, 0, &swords_dance2Tiles, 0xFF, 2);
    if (animation_frame_handler_move(obj, 0, 2, frame_duration, 0, 0, &swords_danceTiles, 9, 1)) {
        world_state_remove_obj(obj);
        obj_attack_free(&objects[obj->priv[6]]);
        obj_attack_free(obj);
    }
    obj->final_oam.priority = 2;
    return;
}


void exec_swords_dance(struct battler* fighter) {
        struct Object* obj = &objects[fighter->obj_id];
        
        // mod position to spawn swords dance animation
        s16 move_y = obj->pos1.y + 16;
        s16 move_x = obj->pos1.x + 16;
        u8 objid = create_move(INDEX_SWORDSDANCE, move_x, move_y, obj->priv[4], move[INDEX_SWORDSDANCE].hitbox_x, move[INDEX_SWORDSDANCE].hitbox_y);
        u8 objid2 = create_move(INDEX_SWORDSDANCE2, move_x + 20 , move_y - 32, obj->priv[4], move[INDEX_SWORDSDANCE2].hitbox_x, move[INDEX_SWORDSDANCE2].hitbox_y);
        fighter->objid_move = objid2;
        objects[objid].priv[3] = fighter->obj_id;
        objects[objid].priv[6] = objid2;
        world_state_remove_obj(&objects[objid2]);
}

