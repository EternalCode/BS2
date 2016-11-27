#include <pokeagb/pokeagb.h>
#include "../battle_state.h"
#include "battler_data.h"

/*
enum battler_states {
    BATTLER_MOVEMENT;
    BATTLER_ATTACKING;
    BATTLER_DAMAGED;
    BATTLER_FAINT;
};
*/


void player_execute_state() {
    extern void process_input_player(u16 button_press);
    
    switch (player->bstate) {
        case BATTLER_MOVEMENT:
            player->objid_move = 0x3F;
            process_input_player(super.buttons_held | super.buttons_new);
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
};

void opponent_execute_state() {
    extern void process_input_opponent(u16 button_press);
    extern u16 AI_decision_parse(u8 move);
    switch (opponent->bstate) {
        case BATTLER_MOVEMENT:
            process_input_opponent(AI_decision_parse(0));
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
};

