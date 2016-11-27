#ifndef POKEMON_BASE_ANIM_H_
#define POKEMON_BASE_ANIM_H_

#include <pokeagb/pokeagb.h>
#include "battler_data.h"
#include "../battle_frames.h"
#include "../moves/move_table.h"


extern void animation_sprite_shake(struct Object*, u8 amount, u8 delay);
extern void animation_frame_handler(struct Object* obj, u8 frame_start, u8 frame_end,
                                            u16 frame_duration[], u8 looptimes, s8 x_displace,
                                            s8 y_displace, u8 idle_state);
//
/* Bulbasaur */
// Idle state facing forward
static void cb_001_battler_idle_F(struct Object* obj) {
    u16 frame_durations[] =  {10, 10, 10, 10, 10, 10};
    animation_frame_handler(obj, 0, 5, frame_durations, 0xFF, 0, 0, 0); 
}

// Idle state facing backward
static void cb_001_battler_idle_B(struct Object* obj) {
    u16 frame_durations[] =  {10, 10, 10, 10, 10, 10};
    animation_frame_handler(obj, 6, 10, frame_durations, 0xFF, 0, 0, 0);
}

// up_left
static void cb_001_battler_UL(struct Object* obj) {
    if (obj->priv[4]) {
        player->dir = DOWN;
    } else {
        opponent->dir = DOWN;
    }
    u16 frame_durations[] =  {5, 5, 5, 5, 5, 5};
    animation_frame_handler(obj, 15, 19, frame_durations, 1, -2, -2,1);
}

// up_right
static void cb_001_battler_UR(struct Object* obj) {
    if (obj->priv[4]) {
        player->dir = DOWN;
    } else {
        opponent->dir = DOWN;
    }
    u16 frame_durations[] =  {5, 5, 5, 5, 5, 5};
    animation_frame_handler(obj, 15, 19, frame_durations, 1, 2, -2, 1);
}

// down_left
static void cb_001_battler_DL(struct Object* obj) {
    if (obj->priv[4]) {
        player->dir = UP;
    } else {
        opponent->dir = UP;
    }
    u16 frame_durations[] =  {5, 5, 5, 5, 5, 5};
    animation_frame_handler(obj, 11, 15, frame_durations, 1, -2, 2, 0);
}

// down_right
static void cb_001_battler_DR(struct Object* obj) {
    if (obj->priv[4]) {
        player->dir = UP;
    } else {
        opponent->dir = UP;
    }
    u16 frame_durations[] =  {5, 5, 5, 5, 5, 5};
    animation_frame_handler(obj, 11, 15, frame_durations, 1, 2, 2, 0);
}

// left
static void cb_001_battler_L(struct Object* obj) {
    if (obj->priv[4]) {
        player->dir = DOWN;
    } else {
        opponent->dir = DOWN;
    }
    u16 frame_durations[] =  {5, 5, 5, 5, 5, 5};
    animation_frame_handler(obj, 15, 19, frame_durations, 1, -4, 0, 1);
}

// right
static void cb_001_battler_R(struct Object* obj) {
    if (obj->priv[4]) {
        player->dir = UP;
    } else {
        opponent->dir = UP;
    }
    u16 frame_durations[] =  {5, 5, 5, 5, 5, 5};
    animation_frame_handler(obj, 11, 15, frame_durations, 1, 4, 0, 0);
}

// up
static void cb_001_battler_U(struct Object* obj) {
    if (obj->priv[4]) {
        player->dir = DOWN;
    } else {
        opponent->dir = DOWN;
    }
    u16 frame_durations[] =  {5, 5, 5, 5, 5, 5};
    animation_frame_handler(obj, 15, 19, frame_durations, 1, 0, -4, 1);
}

// down
static void cb_001_battler_D(struct Object* obj) {
    if (obj->priv[4]) {
        player->dir = UP;
    } else {
        opponent->dir = UP;
    }
    u16 frame_durations[] =  {5, 5, 5, 5, 5, 5};
    animation_frame_handler(obj, 11, 15, frame_durations, 1, 0, 4, 0);
}

// atk0
// Razor leaf
static void cb_001_battler_ATK0(struct Object* obj) {
    u8 orientation = (obj->priv[4]) ? player->dir : opponent->dir;
    u16 frame_durations[] =  {8, 8, 8, 8, 40};
    u8 frame_start;
    if (orientation ==  UP) {
        frame_start = 20;
        animation_frame_handler(obj, 20, 24, frame_durations, 1, 0, 0, 0);
    } else {
        frame_start = 25;
        animation_frame_handler(obj, 25, 29, frame_durations, 1, 0, 0, 1);    
    }
    animation_sprite_shake(obj, 3, 2);
    u8 move_status = (obj->priv[4]) ? player->objid_move : opponent->objid_move;
    if (((obj->priv[1] - frame_start) == 2) && (move_status == 0x3F)) {
        extern u8 create_move(u16 moveid, u16 x, u16 y, u8 side);
        u8 objid = create_move(0, obj->pos1.x + 20, obj->pos1.y, 0);
        player->objid_move = objid;
        objects[objid].priv[3] = obj->priv[4];
        
    }
}

// atk1
// Vine whip
static void cb_001_battler_ATK1(struct Object* obj) {
    u8 orientation = (obj->priv[4]) ? player->dir : opponent->dir;
     u16 frame_durations[] =  {8, 8, 8, 8, 60};   
    if (orientation ==  UP) {
        animation_frame_handler(obj, 20, 24, frame_durations, 1, 0, 0, 0);
    } else {
        animation_frame_handler(obj, 25, 29, frame_durations, 1, 0, 0, 1);
    }
}

// atk2
// Tackle
static void cb_001_battler_ATK2(struct Object* obj) {
    u8 orientation = (obj->priv[4]) ? player->dir : opponent->dir;
    u16 frame_durations[] =  {8, 8, 8, 8, 60};
    if (orientation ==  UP) {
        animation_frame_handler(obj, 20, 24, frame_durations, 1, 0, 0, 0);
    } else {
        animation_frame_handler(obj, 25, 29, frame_durations, 1, 0, 0, 1);    
    }
    animation_sprite_shake(obj, 3, 2);
}

// atk3
// Solarbeam
static void cb_001_battler_ATK3(struct Object* obj) {
    u8 orientation = (obj->priv[4]) ? player->dir : opponent->dir;
    u16 frame_durations[] =  {8, 8, 8, 8, 60};
    if (orientation ==  UP) {
        animation_frame_handler(obj, 20, 24, frame_durations, 1, 0, 0, 0);
    } else {
        animation_frame_handler(obj, 25, 29, frame_durations, 1, 0, 0, 1);    
    }
    animation_sprite_shake(obj, 3, 2);
}

static const struct battler_base p_base[1] = {
    // bulbasaur
    {&_01Tiles, &_01Pal, cb_001_battler_idle_F, cb_001_battler_idle_B,
    cb_001_battler_U, cb_001_battler_D, cb_001_battler_L, cb_001_battler_R,
    cb_001_battler_UL, cb_001_battler_UR, cb_001_battler_DL,
    cb_001_battler_DR, {cb_001_battler_ATK0, cb_001_battler_ATK1,
    cb_001_battler_ATK2, cb_001_battler_ATK3}, 32},
};

#endif /* POKEMON_BASE_ANIM_H_ */

