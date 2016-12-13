#include <pokeagb/pokeagb.h>
#include "../battler_data/battler_data.h"
#include "../battler_data/pokemon_base.h"
#include "../moves/move_table.h"

#define GROUND_LEVEL_COORD 0x60


/*
 *
 * This file contains utility animation handling functions shared across multiple playable characters.
 *
 */

 // null object callback
 void obj_null_oac(struct Object* obj) {
    return;
 } 
 
// Picks idle state for NPC based on if the NPC is falling or not
void activate_idle(struct Object* obj, u8 dir) {
    extern void cb_battler_idle_F(struct Object*);
    extern void cb_battler_idle_B(struct Object*);
    struct battler* fighter = (obj->priv[4]) ? player : opponent;
    
    // if falling, use falling frame
    fighter->old_dir = fighter->dir;
    fighter->dir = (dir) ? FACING_RIGHT : FACING_LEFT;

    if (fighter->has_jumped) {
        if (fighter->dir == FACING_RIGHT) {
            obj->callback = p_base[fighter->species].falling_R;
        } else {
            obj->callback = p_base[fighter->species].falling_L;
        }
    } else {
    // already on the ground idling
        if (fighter->dir == FACING_RIGHT) {
            obj->callback = p_base[fighter->species].idle_B;
        } else {
            obj->callback = p_base[fighter->species].idle_F;
        }
    }
}


/*
 * Object private variable representation:
 *
 *
 *
 */

 
 /* TODO: Decide if moving shaking into a task based system to utilize the task's resources is a good decision */
  // Shakes the object back and forth in a vertical motion
void animation_sprite_shake(struct Object* obj, u8 amount, u8 delay) {
    obj->priv[5]++;
    if (obj->priv[5] < delay) {
        return;
    }
    obj->priv[5] = 0;
    obj->pos1.x += (obj->priv[6]) ? 0 : amount;
    obj->pos1.x -= (obj->priv[6]) ? amount : 0;
    obj->priv[6] = !obj->priv[6];
}


void write_frame(struct Object* obj) {    
    // Play frame animation
    void* dst = (void*)((obj->final_oam.tile_num * 32) + SPRITE_RAM);
    void* src = (obj->priv[4]) ? p_base[player->species].image_data : p_base[opponent->species].image_data;
    src += (32 * 8 * 8 * obj->priv[1]);
    memcpy(dst, src, (32 * 8 * 8));
}

// display a frame in an animation list
u8 animation_frame_handler(struct Object* obj, u8 frame_start, u8 frame_end, u16 frame_duration[], u8 loop_times) {

    // update first frame of animation, if this is animation's first frame
    if (!obj->priv[2]) {
        obj->priv[1] = frame_start;
        obj->priv[2] = 1;
        obj->priv[0] = 0;
        obj->priv[7] = 0;
    }
    
    // last frame play frame for last frame's duration
    if (obj->priv[1] == 0xFF) {
        if (obj->priv[0] < frame_duration[obj->priv[7]]) {
            obj->priv[0]++;
            return 0;
        }
        
        // if looped, start new loop
        if (obj->priv[3] < loop_times) {
            obj->priv[3]++;
            obj->priv[1] = frame_start;
            obj->priv[2] = 0;
            return 0;
        }

        // done looping, mark as done
        obj->priv[2] = 0;
        return 1;
    }

    // if this is the first frame, draw it without delay
    if (frame_start == frame_end) {
        write_frame(obj);
        if (obj->priv[3] < loop_times) {
            obj->priv[3]++;
            return 0;
        }
        obj->priv[2] = 0;
        return 1;
    } else if (obj->priv[1] == frame_start) {
        write_frame(obj);
        obj->priv[1] = (obj->priv[1] != frame_end) ? (obj->priv[1] + 1) : 0xFF;
        obj->priv[7]++;
    } else {
        // not first frame, check delay
        if (obj->priv[0] < frame_duration[obj->priv[7]]) {
            obj->priv[0]++;
            return 0;
        }
        
        // delay finished, reset delay counter and load delay for next frame
        obj->priv[7]++;
        obj->priv[0] = 0;
        
        // update frame to show
        write_frame(obj);
        obj->priv[1] = (obj->priv[1] != frame_end) ? (obj->priv[1] + 1) : 0xFF;
        
        // if frame is start frame, then iteration is finished.
        if (obj->priv[1] == frame_start) {
            if (obj->priv[3] < loop_times) {
                obj->priv[3]++;
                return 0;
            }
            obj->priv[2] = 0;
            return 1;
        }
        
    }
    
    return 0; 
}

// animation frame manager for moves, also contains movement management. Moves are unaffected by gravity.
u8 animation_frame_handler_move(struct Object* obj, u8 frame_start, u8 frame_end,
                                u16 frame_duration[], s8 x_displace, s8 y_displace,
                                void* src, u8 loop_times, u8 size) {
    // animation delay
    obj->priv[0]++;
    if (obj->priv[0] > frame_duration[obj->priv[1] - frame_start]) {
        obj->priv[0] = 0;
    } else {
        return 0;
    }
    // check which frame to execute next
    obj->priv[1] = (obj->priv[1] < frame_start) ? frame_start : obj->priv[1];
    obj->priv[1] = ((obj->priv[1] >= frame_end) ? (frame_start) : (obj->priv[1] + 1));
    u8 frame = obj->priv[1];
    if (frame == frame_start) {
        obj->priv[4]++;
    }
    if (obj->priv[4] > loop_times) {
        // animation ended
        return 1;
    } else {
        // animation starting
        void* dst = (void*)((obj->final_oam.tile_num * 32) + SPRITE_RAM);  
        u8 s = size * 4;
        src += (32 * s * s * frame);
        memcpy(dst, src, (32 * s * s));
        obj->pos1.x += x_displace;
        obj->pos1.y += y_displace;
        return 0;
    }   
}


// free resources of a given object
void obj_attack_free(struct Object* obj) {
    obj_free(obj);
    return;
}


// Clear obj private variables dealing with current frame, and object shaking
void obj_priv_clear(struct Object* obj) {
    obj->priv[2] = 0;
    obj->priv[3] = 0;
}

