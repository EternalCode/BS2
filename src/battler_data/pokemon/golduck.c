#include <pokeagb/pokeagb.h>
#include "../battler_data.h"
#include "../../battle_frames.h"
#include "../../moves/move_table.h"

extern void exec_protect(struct battler* fighter);
extern void exec_whirlpool(enum BattlerFacingDir orientation, struct battler* fighter);
extern void exec_psyshock(enum BattlerFacingDir orientation, struct battler* fighter);
extern void exec_watergun(enum BattlerFacingDir orientation, struct battler* fighter);
extern void animation_sprite_shake(struct Object*, u8 amount, u8 delay);
extern u8 animation_frame_handler(struct Object* obj, u8 frame_start, u8 frame_end, u16 frame_duration[], u8 looptimes);
extern void activate_idle(struct Object* obj, u8 dir);

/* Scyther */
// Idle state facing forward
void cb_002_battler_idle_F(struct Object* obj) {
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
void cb_002_battler_idle_B(struct Object* obj) {
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
void cb_002_battler_L(struct Object* obj) {
    // assign positional vectors for animation
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    fighter->delta_x = -1;
    fighter->delta_y = 0;
    fighter->x_delay_time = 3;
    
    // animation frame handling
    u16 frame_durations[] =  {6, 6, 6, 6};
    u8 status = animation_frame_handler(obj, 2, 4, frame_durations, 0);
    
    // idle when finished animation
    if (status)
        activate_idle(obj, 1);
}

// Walking right animation 
void cb_002_battler_R(struct Object* obj) {
    // assign positional vectors for animation
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    fighter->delta_x = 1;
    fighter->delta_y = 0;
    fighter->x_delay_time = 3;
    
    // animation frame handling
    u16 frame_durations[] =  {6, 6, 6, 6};
    u8 status = animation_frame_handler(obj, 5, 7, frame_durations, 0);
    
    // idle when finished animation
    if (status)
        activate_idle(obj, 0);
}

// Jumping animation
void cb_002_battler_U(struct Object* obj) {
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    u8 facing_right = (fighter->dir == FACING_RIGHT);
    u8 start_frame, end_frame, status;
    
    // assign positional vectors for animation
    fighter->delta_y = 5;   
    fighter->x_delay_time = 2;
    if (fighter->apply_dir_to_jump) {
        fighter->delta_x = (facing_right) ? -3 : 3;
    } else {
        fighter->delta_x = 0;
    }
    
    // change starting frame based on facing direction
    if (facing_right) {
        start_frame = 30;
        end_frame = 31;
    } else {
        start_frame = 32;
        end_frame = 33;
    }

    // animation frame handling
    u16 frame_durations[] = {3, 20, 10};
    status = animation_frame_handler(obj, start_frame, end_frame, frame_durations, 0);
    
    // idle when finished animation
    if (status) {
        activate_idle(obj, facing_right);
        fighter->apply_dir_to_jump = false;
    }
}

// Falling down left animation idle state
void cb_002_battler_FL(struct Object* obj) {
    // animation frame handling
    u16 frame_durations [] = {1, 1};
    u8 status = animation_frame_handler(obj, 33, 33, frame_durations, 0);
    
    // idle when finished animation
    if (status)
        activate_idle(obj, 0);
}

// Falling down right animation idle state
void cb_002_battler_FR(struct Object* obj) {
    // animation frame handling
    u16 frame_durations [] = {1, 1};
    u8 status = animation_frame_handler(obj, 31, 31, frame_durations, 0);
    
    // idle when finished animation
    if (status)
        activate_idle(obj, 1);
    
}

// atk0
// fury swipes
void fury_swipes_launch(struct Object* obj) {
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    u8 facing_right = (fighter->dir == FACING_RIGHT);
    u16 frame_durations[] =  {15, 5, 5, 5, 5, 5, 5};
    u8 status;
    fighter->delta_y = 0;
    fighter->delta_x = (facing_right) ? -1 : 1;
    fighter->x_delay_time = 4;
    if (facing_right) {
        status = animation_frame_handler(obj, 8, 13, frame_durations, fighter->anim_loop);
    } else {
        status = animation_frame_handler(obj, 14, 19, frame_durations, fighter->anim_loop);    
    }
    
    fighter->is_meleeing = ((obj->priv[1] == 12) || (obj->priv[1] == 15));
 
    if (status)
        activate_idle(obj, (facing_right) ? 1 : 0);
}

void cb_002_battler_ATK0(struct Object* obj) {
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    fighter->anim_loop =  (rand() % 4); // fury swipes times hit
    obj->callback = fury_swipes_launch;
}


// atk1
// Water gun
void cb_002_battler_ATK1(struct Object* obj) {
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    u8 facing_right = (fighter->dir == FACING_RIGHT);
    u16 frame_durations[] =  {10, 20, 35};
    u8 status;
    fighter->delta_y = 0;
    fighter->x_delay_time = 10;
    fighter->x_delay_timer = 0;
    fighter->delta_x = 1;
    if (facing_right) {
        status = animation_frame_handler(obj, 20, 21, frame_durations, 0);
    } else {
        status = animation_frame_handler(obj, 22, 23, frame_durations, 0);    
    }
    
    if ((fighter->objid_move == 0x3F) && (obj->priv[0] > 19)) {
        if ((obj->priv[1] == 21) || (obj->priv[1] == 23))
            exec_watergun(facing_right, fighter);
    }
    if (status) {
        activate_idle(obj, facing_right ? 1 : 0);
        fighter->objid_move = 0x3F;
    }
}

// atk2
// Psyshock
void cb_002_battler_ATK2(struct Object* obj) {
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    u8 facing_right = (fighter->dir == FACING_RIGHT);
    u16 frame_durations[] =  {5, 140, 40};
    u8 status;
    fighter->delta_y = 0;
    fighter->x_delay_time = 10;
    fighter->x_delay_timer = 0;
    fighter->delta_x = 1;
    if (facing_right) {
        status = animation_frame_handler(obj, 20, 21, frame_durations, 0);
    } else {
        status = animation_frame_handler(obj, 22, 23, frame_durations, 0);    
    }
    
    if ((fighter->objid_move == 0x3F) && (obj->priv[0] == 20)) {
        if ((obj->priv[1] == 21) || (obj->priv[1] == 23))
            exec_psyshock(facing_right, fighter);
    }
    if (status) {
        activate_idle(obj, facing_right ? 1 : 0);
        fighter->objid_move = 0x3F;
    }
}

// atk3
// whirlpool
void cb_002_battler_ATK3(struct Object* obj) {
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    u8 facing_right = (fighter->dir == FACING_RIGHT);
    fighter->boosting = true;
    u16 frame_durations[] =  {1, 30};
    u8 status = 0;
    fighter->delta_y = 0;
    fighter->x_delay_time = 0;
    fighter->x_delay_timer = 0;
    fighter->delta_x = 0;
    if (facing_right) {
        status = animation_frame_handler(obj, 20, 21, frame_durations, 0);
    } else {
        status = animation_frame_handler(obj, 22, 23, frame_durations, 0);    
    }
    
    if (fighter->objid_move == 0x3F) {
        if (((obj->priv[1] == 21) || (obj->priv[1] == 23)) && (obj->priv[0] > 20))    
            exec_whirlpool(facing_right, fighter);
    }
    if (status) {
        activate_idle(obj, facing_right ? 1 : 0);
        fighter->objid_move = 0x3F;
        fighter->boosting = false;
    }
}

// Down button, atk protect
void cb_002_protect(struct Object* obj) {
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

