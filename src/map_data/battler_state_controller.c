#include <pokeagb/pokeagb.h>
#include "../battle_state.h"
#include "../battler_data/battler_data.h"
#include "../battler_data/pokemon_base.h"

/*
enum battler_states {
    BATTLER_MOVEMENT;
    BATTLER_ATTACKING;
    BATTLER_DAMAGED;
    BATTLER_FAINT;
};
*/
extern void process_input(u16 button_press, struct battler* fighter);

void player_execute_state() {
    
    switch (player->bstate) {
        case BATTLER_MOVEMENT:
            //player->objid_move = 0x3F;
            objects[player->obj_id].priv[4] = 1;
            process_input(super.buttons_held | super.buttons_new, player);
            break;
        case BATTLER_UNCONTROLLABLE_JUMPING:
        case BATTLER_ATTACKING:
            /*  of fighter has an idle callback activate_idle has been called, thus upward portion
            of the jump has been completed. */
            if ((objects[player->obj_id].callback == p_base[player->species].falling_R) || 
                (objects[player->obj_id].callback == p_base[player->species].falling_L) ||
                (objects[player->obj_id].callback == p_base[player->species].idle_B) ||
                (objects[player->obj_id].callback == p_base[player->species].idle_F)) {
                // enter movement state, in all cases
                player->bstate = BATTLER_MOVEMENT;
            }
            break;
        case BATTLER_DAMAGED:
            break;
        case BATTLER_FAINT:
            break;
        case BATTLER_BLOCKING:
            break;
        default:
            // invalid state
            break;
    };
}

void opponent_execute_state() {

    extern u16 AI_decision_parse(u8 move);
    switch (opponent->bstate) {
        case BATTLER_MOVEMENT:
            opponent->objid_move = 0x3F;
            objects[opponent->obj_id].priv[4] = 0;
            process_input(AI_decision_parse(0), opponent);
            break;
        case BATTLER_UNCONTROLLABLE_JUMPING:
            //process_input_jumping_dir(AI_decision_parse(0), 0);
            break;
        case BATTLER_ATTACKING:
            break;
        case BATTLER_DAMAGED:
            break;
        case BATTLER_FAINT:
            break;
        default:
            // invalid state
            break;
    };
}

