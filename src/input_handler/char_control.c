#include <pokeagb/pokeagb.h>
#include "../battler_data/battler_data.h"


static struct battler* opponent = (struct battler*)0x202024C;
static struct battler* player = (struct battler*)0x2024284;

extern void cb_battler_UL(struct Object*);
extern void cb_battler_UR(struct Object*);
extern void cb_battler_DL(struct Object*);
extern void cb_battler_DR(struct Object*);
extern void cb_battler_L(struct Object*);
extern void cb_battler_U(struct Object*);
extern void cb_battler_R(struct Object*);
extern void cb_battler_D(struct Object*);
extern void cb_battler_idle_F(struct Object*);
extern void cb_battler_idle_B(struct Object*);

void process_input(u16 button_press) {
    struct Object* obj = &objects[player->obj_id];
    /*if (obj->priv[3]) {
        return;
    }*/
    u8* var = (u8*)0x20370B8;
    *var = obj->pos1.x;
    *(var+2) = obj->pos1.y;
    // process attacks -> priority over movements
    /* TODO */
    
    // strip unneeded buttons for movements
    u16 button = button_press & (KEY_UP | KEY_LEFT | KEY_RIGHT | KEY_DOWN);
    
    // process input movements
    if (button == (KEY_UP | KEY_LEFT)) {
        // Diagonal upleft
        obj->callback = cb_battler_UL;
        obj->final_oam.h_flip = 0;
        obj->priv[3] = 1;
    } else if (button == (KEY_UP | KEY_RIGHT)) {
        // Diagonal upright
        obj->callback = cb_battler_UR;
        obj->final_oam.h_flip = 1;
        obj->priv[3] = 1;
    } else if (button == (KEY_DOWN | KEY_LEFT)) {
        // Diagonal downleft  
        obj->callback = cb_battler_DL;
        obj->final_oam.h_flip = 0;
        obj->priv[3] = 1;
    } else if (button == (KEY_DOWN | KEY_RIGHT)) {
        // Diagonal downright
        obj->callback = cb_battler_DR;
        obj->final_oam.h_flip = 1;
        obj->priv[3] = 1;
    } else if (button == (KEY_LEFT)) {
        // left
        obj->callback = cb_battler_L;
        obj->final_oam.h_flip = 0;
        obj->priv[3] = 1;
    } else if (button == (KEY_RIGHT)) {
        // right
        obj->callback = cb_battler_R;
        obj->final_oam.h_flip = 1;
        obj->priv[3] = 1;
    } else if (button == (KEY_UP)) {
        // up
        obj->callback = cb_battler_U;
        obj->priv[3] = 1;
    } else if (button == (KEY_DOWN)) {
        // down
        obj->callback = cb_battler_D;
        obj->priv[3] = 1;
    } else {
        // continue idle state
    }
}


void process_opponent(u16 button) {
    // AI when it happens
}