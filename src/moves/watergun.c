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


void water_gun_anim(struct Object* obj) {
    // cycle frames
    u16 frame_duration[] = {3, 30, 5, 5, 2, 1};
    // priv[0] = delay
    // priv[1] = frame
    // priv[3] = objid
    // priv[6] = orientation
    if (obj->pos1.y >  160 || obj->pos1.x > 460) {
        world_state_remove_obj(obj);
        obj_attack_free(obj);
    }
    
    void* dst = (void*)((obj->final_oam.tile_num * 32) + SPRITE_RAM); 
    void* src = &water_gunTiles;
    src += (obj->priv[6]) ? (32 * 4 * 4 * 6) : 0;
    switch (obj->priv[1]) {
        case 0:
            // frame1
            src += (32 * 4 * 4 * 0);
            memcpy(dst, src, (32 * 4 * 4));
            if (obj->priv[0] >= frame_duration[0]) {
                obj->priv[1]++;
                obj->priv[0] = 0;
            } else {
                obj->priv[0]++;
            }
            break;
        case 1:
            // frame2
            src += (32 * 4 * 4 * 1);
            memcpy(dst, src, (32 * 4 * 4));
            if (obj->priv[0] >= frame_duration[1]) {
                obj->priv[1]++;
                obj->priv[0] = 0;
            } else {
                obj->priv[0]++;
            }
            obj->pos1.x += (obj->priv[6]) ? -3 : 3;
            break;
        case 2:
            // frame3
            src += (32 * 4 * 4 * 2);
            memcpy(dst, src, (32 * 4 * 4));
            if (obj->priv[0] >= frame_duration[2]) {
                obj->priv[1]++;
                obj->priv[0] = 0;
            } else {
                obj->priv[0]++;
            }
            obj->pos1.x += (obj->priv[6]) ? -1 : 1;
            obj->pos1.y -= (obj->priv[6]) ? -1 : 1;
            break;
        case 3:
            // frame4
            src += (32 * 4 * 4 * 3);
            memcpy(dst, src, (32 * 4 * 4));
            if (obj->priv[0] >= frame_duration[3]) {
                obj->priv[1]++;
                obj->priv[0] = 0;
            } else {
                obj->priv[0]++;
            }
            obj->pos1.y += (obj->priv[6]) ? -1 : 1;
            break;
        case 4:
            // frame5
            src += (32 * 4 * 4 * 4);
            memcpy(dst, src, (32 * 4 * 4));
            if (obj->priv[0] >= frame_duration[4]) {
                obj->priv[1]++;
                obj->priv[0] = 0;
            } else {
                obj->priv[0]++;
            }
            obj->pos1.y += (obj->priv[6]) ? -1 : 1;
            break;
        case 5:
            src += (32 * 4 * 4 * 5);
            memcpy(dst, src, (32 * 4 * 4));
            if (obj->priv[0] >= frame_duration[5]) {
                obj->priv[1]++;
                obj->priv[0] = 0;
            } else {
                obj->priv[0]++;
            }
            obj->pos1.y += (obj->priv[6]) ? -1 : 1;
        case 6:
            // frame6
            world_state_remove_obj(obj);
            obj_attack_free(obj);
            break;
    };
    return;
}


void exec_watergun(enum BattlerFacingDir orientation, struct battler* fighter) {
    struct Object* obj = &objects[fighter->obj_id];
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
    u8 objid = create_move(INDEX_WATERGUN, move_x, move_y, obj->priv[4], 32 - move[INDEX_WATERGUN].hitbox_x, 32 - move[INDEX_WATERGUN].hitbox_y);
    fighter->objid_move = objid;
    objects[objid].priv[3] = fighter->obj_id;
    objects[objid].priv[7] = move[INDEX_WATERGUN].base_dmg;
    objects[objid].priv[6] = orientation;
}

