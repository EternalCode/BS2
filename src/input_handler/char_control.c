#include <pokeagb/pokeagb.h>
#include "../battler_data/battler_data.h"
#include "../battler_data/pokemon_base.h"

extern void obj_priv_clear(struct Object* obj);
extern void protect_cb(struct Object* obj, struct battler* fighter);

void process_input(u16 button_press, struct battler* fighter) {
    struct Object* obj = &objects[fighter->obj_id];
    u16 species = fighter->species;
    
    // blocking check
    if ((button_press == KEY_DOWN)  && (fighter->protect_pp)) {
        fighter->bstate = BATTLER_ATTACKING;
        obj->callback = p_base[species].protect;
        obj_priv_clear(obj);

        return;
    }
    // strip unneeded buttons for attacks
    u16 button = button_press & (KEY_A | KEY_B | KEY_L | KEY_R);
    
    // check attack used. Priority over movement
    if (button == (KEY_A)) {
        obj->callback = p_base[species].atk[0];
        fighter->bstate = BATTLER_ATTACKING;
        obj_priv_clear(obj);
        return;
    } else if (button == (KEY_B)) {
        obj->callback = p_base[species].atk[1];
        fighter->bstate = BATTLER_ATTACKING;
        obj_priv_clear(obj);
        return;
    } else if (button == (KEY_L)) {
        obj->callback = p_base[species].atk[2];
        fighter->bstate = BATTLER_ATTACKING;
        obj_priv_clear(obj);
        return;
    } else if (button == (KEY_R)) {
        obj->callback = p_base[species].atk[3];
        fighter->bstate = BATTLER_ATTACKING;
        obj_priv_clear(obj);
        return;
    }
    
    // Vertical vector removal during falling down
    if (fighter->has_jumped) {
        button = button_press & (KEY_LEFT | KEY_RIGHT);
    } else {
        button = button_press & (KEY_UP | KEY_LEFT | KEY_RIGHT);
    }
    
    // process input movements
    if ((button == (KEY_UP | KEY_LEFT)) && (!fighter->has_jumped)) {
        // up left
        fighter->dir = FACING_RIGHT;
        fighter->bstate = BATTLER_UNCONTROLLABLE_JUMPING;
        obj_priv_clear(obj);
        obj->callback = p_base[species].jump_U;
        fighter->apply_dir_to_jump = true;
        fighter->delta_time = 0;
    } else if ((button == (KEY_UP | KEY_RIGHT)) && (!fighter->has_jumped)) {
        // up right
        fighter->dir = FACING_LEFT;
        fighter->bstate = BATTLER_UNCONTROLLABLE_JUMPING;
        obj_priv_clear(obj);
        obj->callback = p_base[species].jump_U;
        fighter->apply_dir_to_jump = true;
        fighter->delta_time = 0;
    } else if (button == (KEY_LEFT)) {
        // left
        obj->priv[2] = (fighter->dir == FACING_RIGHT) ? obj->priv[2] : 0;
        fighter->dir = FACING_RIGHT;
        obj->callback = p_base[species].walk_L;
    } else if (button == (KEY_RIGHT)) {
        // right
        obj->priv[2] = (fighter->dir == FACING_LEFT) ? obj->priv[2] : 0;
        fighter->dir = FACING_LEFT;
        obj->callback = p_base[species].walk_R;
    } else if ((button == (KEY_UP)) && (!fighter->has_jumped)) {
        // up
        fighter->bstate = BATTLER_UNCONTROLLABLE_JUMPING;
        obj_priv_clear(obj);
        obj->callback = p_base[species].jump_U;
        fighter->apply_dir_to_jump = false;
        fighter->delta_time = 0;
        
    } else {
       // obj_priv_clear(obj);
        // continue idle state
    }
}


void process_uturn(u16 button_press, struct battler* fighter) {
    u16 button = button_press & (KEY_A | KEY_B | KEY_L | KEY_R);
    if (button) {
        //cancel state, enter
    }
    return;
}


