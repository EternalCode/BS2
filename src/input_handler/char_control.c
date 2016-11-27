#include <pokeagb/pokeagb.h>
#include "../battler_data/battler_data.h"
#include "../battler_data/pokemon_base.h"

void obj_priv_clear(struct Object* obj) {
    obj->priv[7] = 0;
    obj->priv[5] = 0;
    obj->priv[6] = 0;
}

void process_input_player(u16 button_press) {
    struct Object* obj = &objects[player->obj_id];
    obj->priv[4] = 1;
    // strip unneeded buttons for movements
    u16 button = button_press & (KEY_A | KEY_B | KEY_L | KEY_R);
    u16 species = player->species;
    
    // check attack used
    if (button == (KEY_A)) {
        obj->callback = p_base[species].atk[0];
        player->bstate = BATTLER_ATTACKING;
        obj_priv_clear(obj);
        return;
    } else if (button == (KEY_B)) {
        obj->callback = p_base[species].atk[1];
        player->bstate = BATTLER_ATTACKING;
        obj_priv_clear(obj);
        return;
    } else if (button == (KEY_L)) {
        obj->callback = p_base[species].atk[2];
        player->bstate = BATTLER_ATTACKING;
        obj_priv_clear(obj);
        return;
    } else if (button == (KEY_R)) {
        obj->callback = p_base[species].atk[3];
        player->bstate = BATTLER_ATTACKING;
        obj_priv_clear(obj);
        return;
    }
    
    button = button_press & (KEY_UP | KEY_LEFT | KEY_RIGHT | KEY_DOWN);
    // process input movements
    if (button == (KEY_UP | KEY_LEFT)) {
        // Diagonal upleft
        obj_priv_clear(obj);
        obj->callback = p_base[species].walk_UL;
        obj->final_oam.h_flip = 0;
    } else if (button == (KEY_UP | KEY_RIGHT)) {
        // Diagonal upright
        obj_priv_clear(obj);
        obj->callback = p_base[species].walk_UR;
        obj->final_oam.h_flip = 1;
    } else if (button == (KEY_DOWN | KEY_LEFT)) {
        // Diagonal downleft  
        obj_priv_clear(obj);
        obj->callback = p_base[species].walk_DL;
        obj->final_oam.h_flip = 0;
    } else if (button == (KEY_DOWN | KEY_RIGHT)) {
        // Diagonal downright
        obj_priv_clear(obj);
        obj->callback = p_base[species].walk_DR;
        obj->final_oam.h_flip = 1;
    } else if (button == (KEY_LEFT)) {
        // left
        obj_priv_clear(obj);
        obj->callback = p_base[species].walk_L;
        obj->final_oam.h_flip = 0;
    } else if (button == (KEY_RIGHT)) {
        // right
        obj_priv_clear(obj);
        obj->callback = p_base[species].walk_R;
        obj->final_oam.h_flip = 1;
    } else if (button == (KEY_UP)) {
        // up
        obj_priv_clear(obj);
        obj->callback = p_base[species].walk_U;
    } else if (button == (KEY_DOWN)) {
        // down
        obj_priv_clear(obj);
        obj->callback = p_base[species].walk_D;
    } else {
        obj_priv_clear(obj);
        // continue idle state
    }
}


void process_input_opponent(u16 button_press) {
    // AI when it happens
   struct Object* obj = &objects[opponent->obj_id];
    obj->priv[4] = 0;
    // strip unneeded buttons for movements
    u16 button = button_press & (KEY_A | KEY_B | KEY_L | KEY_R);
    u16 species = opponent->species;
    
    // check attack used
    if (button == (KEY_A)) {
        obj->callback = p_base[species].atk[0];
        opponent->bstate = BATTLER_ATTACKING;
        return;
    } else if (button == (KEY_B)) {
        obj->callback = p_base[species].atk[1];
        opponent->bstate = BATTLER_ATTACKING;
        return;
    } else if (button == (KEY_L)) {
        obj->callback = p_base[species].atk[2];
        opponent->bstate = BATTLER_ATTACKING;
        return;
    } else if (button == (KEY_R)) {
        obj->callback = p_base[species].atk[3];
        opponent->bstate = BATTLER_ATTACKING;
        return;
    }
    
    button = button_press & (KEY_UP | KEY_LEFT | KEY_RIGHT | KEY_DOWN);
    // process input movements
    if (button == (KEY_UP | KEY_LEFT)) {
        // Diagonal upleft
        obj->callback = p_base[species].walk_UL;
        obj->final_oam.h_flip = 0;
    } else if (button == (KEY_UP | KEY_RIGHT)) {
        // Diagonal upright
        obj->callback = p_base[species].walk_UR;
        obj->final_oam.h_flip = 1;
    } else if (button == (KEY_DOWN | KEY_LEFT)) {
        // Diagonal downleft  
        obj->callback = p_base[species].walk_DL;
        obj->final_oam.h_flip = 0;
    } else if (button == (KEY_DOWN | KEY_RIGHT)) {
        // Diagonal downright
        obj->callback = p_base[species].walk_DR;
        obj->final_oam.h_flip = 1;
    } else if (button == (KEY_LEFT)) {
        // left
        obj->callback = p_base[species].walk_L;
        obj->final_oam.h_flip = 0;
    } else if (button == (KEY_RIGHT)) {
        // right
        obj->callback = p_base[species].walk_R;
        obj->final_oam.h_flip = 1;
    } else if (button == (KEY_UP)) {
        // up
        obj->callback = p_base[species].walk_U;
    } else if (button == (KEY_DOWN)) {
        // down
        obj->callback = p_base[species].walk_D;
    } else {
        // continue idle state
    }
}