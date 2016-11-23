#include <pokeagb/pokeagb.h>
#include "../battler_data/battler_data.h"
#include "../../generated/images/battlers_frames/001.h"

static struct battler* opponent = (struct battler*)0x202024C;
static struct battler* player = (struct battler*)0x2024284;

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
                            u8 looptimes, s8 x_displace, s8 y_displace, u8 idle_state) {
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
        switch (idle_state) {
            case 0:
                obj->callback = cb_battler_idle_F;
                break;
            default:
                obj->callback = cb_battler_idle_B;
                break;
        };
        obj->priv[3] = 0;
    } else {
        // animation starting
        void* dst = (void*)((obj->final_oam.tile_num * 32) + SPRITE_RAM);
        void* src = (void*)&_01Tiles[(32 * 4 * 4 * frame)];
        memcpy(dst, src, (32 * 4 * 4));
        obj->pos1.x += x_displace;
        obj->pos1.y += y_displace;
        obj->priv[2]++;            
    }
}


// Idle state facing forward
void cb_battler_idle_F(struct Object* obj) {
    animation_frame_handler(obj, 0, 5, 10, 0xFF, 0, 0, 1); 
}

// Idle state facing backwards
void cb_battler_idle_B(struct Object* obj) {
    animation_frame_handler(obj, 6, 11, 10, 0xFF, 0, 0, 1);
}

// up_left
void cb_battler_UL(struct Object* obj) {
    animation_frame_handler(obj, 16, 19, 5, 1, -2, -2, 1);
}

// up_right
void cb_battler_UR(struct Object* obj) {
    animation_frame_handler(obj, 16, 19, 5, 1, 2, -2, 1);
}

// down_left
void cb_battler_DL(struct Object* obj) {
    animation_frame_handler(obj, 12, 15, 5, 1, -2, 2, 0);
}

// down_right
void cb_battler_DR(struct Object* obj) {
    animation_frame_handler(obj, 12, 15, 5, 1, 2, 2, 0);
}

// left
void cb_battler_L(struct Object* obj) {
    animation_frame_handler(obj, 12, 15, 5, 1, -2, 0, 0);
}

// right
void cb_battler_R(struct Object* obj) {
    animation_frame_handler(obj, 16, 19, 5, 1, 2, 0, 1);
}

// up
void cb_battler_U(struct Object* obj) {
    // based on side facing, use other frame
    animation_frame_handler(obj, 16, 19, 5, 1, 0, -2, 1);
}

// down
void cb_battler_D(struct Object* obj) {
    // based on side facing, use other frame
    animation_frame_handler(obj, 12, 15, 5, 1, 0, 2, 0);
}



