#include <pokeagb/pokeagb.h>
#include "../battler_data.h"
#include "../../battle_frames.h"
#include "../../moves/move_table.h"

extern void exec_protect(struct battler* fighter);
extern void exec_swords_dance(struct battler* fighter);
extern void exec_x_scissor(struct battler* fighter);
extern void exec_slash(struct battler* fighter);
extern void animation_sprite_shake(struct Object*, u8 amount, u8 delay);
extern u8 animation_frame_handler(struct Object* obj, u8 frame_start, u8 frame_end, u16 frame_duration[], u8 looptimes);
extern void activate_idle(struct Object* obj, u8 dir);

/* Scyther */
// Idle state facing forward
void cb_001_battler_idle_F(struct Object* obj) {
    // assign positional vectors for animation
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    fighter->delta_x = 0;
    fighter->delta_y = 0;
    fighter->x_delay_time = 0;

    // animation frame handling
    u16 frame_durations[] =  {5};
    u8 status = animation_frame_handler(obj, 1, 1, frame_durations, 0);
    
    // Idle when finished animation
    if (status)
        activate_idle(obj, 0);
}

// Idle state facing backward
void cb_001_battler_idle_B(struct Object* obj) {
    // assign positional vectors for animation
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    fighter->delta_x = 0;
    fighter->delta_y = 0;
    fighter->x_delay_time = 0;
    
    // animation frame handling
    u16 frame_durations[] =  {5};
    u8 status = animation_frame_handler(obj, 0, 0, frame_durations, 0);
    
    // Idle when finished animation
    if (status)
        activate_idle(obj, 1);
}

// Walking left animation
void cb_001_battler_L(struct Object* obj) {
    // assign positional vectors for animation
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    fighter->delta_x = -2;
    fighter->delta_y = 0;
    fighter->x_delay_time = 8;
    
    // animation frame handling
    u16 frame_durations[] =  {6, 6, 6, 6};
    u8 status = animation_frame_handler(obj, 2, 4, frame_durations, 0);
    
    // idle when finished animation
    if (status)
        activate_idle(obj, 1);
}

// Walking right animation 
void cb_001_battler_R(struct Object* obj) {
    // assign positional vectors for animation
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    fighter->delta_x = 2;
    fighter->delta_y = 0;
    fighter->x_delay_time = 8;
    
    // animation frame handling
    u16 frame_durations[] =  {6, 6, 6, 6};
    u8 status = animation_frame_handler(obj, 5, 7, frame_durations, 0);
    
    // idle when finished animation
    if (status)
        activate_idle(obj, 0);
}

// Jumping animation
void cb_001_battler_U(struct Object* obj) {
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    u8 facing_right = (fighter->dir == FACING_RIGHT);
    u8 start_frame, end_frame, status;
    
    // assign positional vectors for animation
    fighter->delta_y = 6;   
    fighter->x_delay_time = 5;
    if (fighter->apply_dir_to_jump) {
        fighter->delta_x = (facing_right) ? -2 : 2;
    } else {
        fighter->delta_x = 0;
    }
    
    // change starting frame based on facing direction
    if (facing_right) {
        start_frame = 20;
        end_frame = 21;
    } else {
        start_frame = 22;
        end_frame = 23;
    }

    // animation frame handling
    u16 frame_durations[] = {3, 10, 10};
    status = animation_frame_handler(obj, start_frame, end_frame, frame_durations, 0);
    
    // idle when finished animation
    if (status) {
        activate_idle(obj, facing_right);
        fighter->apply_dir_to_jump = false;
    }
}

// Falling down left animation idle state
void cb_001_battler_FL(struct Object* obj) {
    // animation frame handling
    u16 frame_durations [] = {1, 1};
    u8 status = animation_frame_handler(obj, 23, 23, frame_durations, 0);
    
    // idle when finished animation
    if (status)
        activate_idle(obj, 0);
}

// Falling down right animation idle state
void cb_001_battler_FR(struct Object* obj) {
    // animation frame handling
    u16 frame_durations [] = {1, 1};
    u8 status = animation_frame_handler(obj, 21, 21, frame_durations, 0);
    
    // idle when finished animation
    if (status)
        activate_idle(obj, 1);
    
}

// atk0
// Slash
void cb_001_battler_ATK0(struct Object* obj) {
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    u8 facing_right = (fighter->dir == FACING_RIGHT);
    u16 frame_durations[] =  {10, 10, 10, 10};
    u8 status;
    fighter->delta_y = 0;
    fighter->delta_x = 0;
    if (facing_right) {
        status = animation_frame_handler(obj, 8, 10, frame_durations, 0);
    } else {
        status = animation_frame_handler(obj, 11, 13, frame_durations, 0);    
    }
    
     if (fighter->objid_move == 0x3F)
        exec_slash(fighter);
 
    if (status) {
        activate_idle(obj, (facing_right) ? 1 : 0);
        fighter->objid_move = 0x3F;
    }
}

// atk1
// X-scissor
void cb_001_battler_ATK1(struct Object* obj) {
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    u8 facing_right = (fighter->dir == FACING_RIGHT);
    u16 frame_durations[] =  {10, 10, 35};
    u8 status;
    fighter->delta_y = 0;
    fighter->x_delay_time = 10;
    fighter->x_delay_timer = 0;
    fighter->delta_x = 1;
    if (facing_right) {
        status = animation_frame_handler(obj, 14, 15, frame_durations, 0);
    } else {
        status = animation_frame_handler(obj, 16, 17, frame_durations, 0);    
    }
    
    if (fighter->objid_move == 0x3F)
        exec_x_scissor(fighter);

    if (status) {
        activate_idle(obj, facing_right ? 1 : 0);
        fighter->objid_move = 0x3F;
    }
}

// atk2
// U-turn start 
void cb_001_battler_ATK2(struct Object* obj) {
    extern void uturn_start(struct Object*);
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    fighter->has_jumped = true;
    fighter->bstate = BATTLER_UNCONTROLLABLE_JUMPING;
    obj->callback = uturn_start;
    fighter->x_delay_timer = 0;
    fighter->delta_time = 0;
    return;
}

void uturn_start(struct Object* obj) {
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    u8 facing_right = (fighter->dir == FACING_RIGHT);
    u16 frame_durations[] =  {5, 5, 10, 10, 10, 10};
    u8 frame_start, status;
    fighter->delta_y = 4;   
    fighter->x_delay_time = 8;
    
    fighter->delta_x = (facing_right) ? 4 : -4;
    if (facing_right) {
        frame_start = 27;
        status = animation_frame_handler(obj, 28, 30, frame_durations, 0);
    } else {
        frame_start = 30;
        status = animation_frame_handler(obj, 31, 33, frame_durations, 0);
    }


    if (status) {
        activate_idle(obj, (frame_start == 30) ? 1 : 0);
        fighter->objid_move = 0x3F;
        fighter->dir = (facing_right) ? FACING_RIGHT : FACING_LEFT;
    }  
}

// atk3
// Swords dance
void cb_001_battler_ATK3(struct Object* obj) {
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    u8 facing_right = (fighter->dir == FACING_RIGHT);
    fighter->boosting = true;
    u16 frame_durations[] =  {1, 50, 50};
    u8 status = 0;
    fighter->delta_y = 0;
    fighter->x_delay_time = 0;
    fighter->x_delay_timer = 0;
    fighter->delta_x = 0;
    if (facing_right) {
        status = animation_frame_handler(obj, 24, 25, frame_durations, 0);
    } else {
        status = animation_frame_handler(obj, 26, 27, frame_durations, 0);    
    }
    
    if (fighter->objid_move == 0x3F)
        exec_swords_dance(fighter);
    
    if (status) {
        activate_idle(obj, facing_right ? 1 : 0);
        fighter->objid_move = 0x3F;
        fighter->boosting = false;
    } else if (obj->priv[7]) {
        animation_sprite_shake(obj, 3, 6);
    }

}

// Down button, atk protect
void cb_001_protect(struct Object* obj) {
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    u8 facing_right = (fighter->dir == FACING_RIGHT);
    u16 frame_durations[] =  {5};
    u8 status;
    fighter->delta_y = 0;
    fighter->x_delay_time = 0;
    fighter->x_delay_timer = 0;
    fighter->delta_x = 0;
    
    if (facing_right) {
        status = animation_frame_handler(obj, 28, 28, frame_durations, 65);
    } else {
        status = animation_frame_handler(obj, 31, 31, frame_durations, 65);
    }

    if (fighter->objid_move == 0x3F)
        exec_protect(fighter);
    
    if (status) {
        activate_idle(obj, (facing_right) ? 1 : 0);
        fighter->objid_move = 0x3F;
    } 
}

