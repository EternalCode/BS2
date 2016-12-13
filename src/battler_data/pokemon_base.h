#ifndef POKEMON_BASE_ANIM_H_
#define POKEMON_BASE_ANIM_H_

#include <pokeagb/pokeagb.h>
#include "battler_data.h"
#include "../battle_frames.h"
#include "../moves/move_table.h"



// Scyther functions
extern void cb_001_battler_idle_F(struct Object*);
extern void cb_001_battler_idle_B(struct Object*);
extern void cb_001_battler_U(struct Object*);
extern void cb_001_battler_L(struct Object*);
extern void cb_001_battler_R(struct Object*);
extern void cb_001_battler_FL(struct Object*);
extern void cb_001_battler_FR(struct Object*);
extern void cb_001_battler_ATK0(struct Object*);
extern void cb_001_battler_ATK1(struct Object*);
extern void cb_001_battler_ATK2(struct Object*);
extern void cb_001_battler_ATK3(struct Object*);
extern void cb_001_protect(struct Object*);

// Golduck functions
extern void cb_002_battler_idle_F(struct Object*);
extern void cb_002_battler_idle_B(struct Object*);
extern void cb_002_battler_U(struct Object*);
extern void cb_002_battler_L(struct Object*);
extern void cb_002_battler_R(struct Object*);
extern void cb_002_battler_FL(struct Object*);
extern void cb_002_battler_FR(struct Object*);
extern void cb_002_battler_ATK0(struct Object*);
extern void cb_002_battler_ATK1(struct Object*);
extern void cb_002_battler_ATK2(struct Object*);
extern void cb_002_battler_ATK3(struct Object*);
extern void cb_002_protect(struct Object*);

static const struct battler_base p_base[2] = {
    // Scyther
    {&_01Tiles, &_01Pal, cb_001_battler_idle_F, cb_001_battler_idle_B,
    cb_001_battler_U, cb_001_battler_L, cb_001_battler_R, cb_001_battler_FL, 
    cb_001_battler_FR, {cb_001_battler_ATK0, cb_001_battler_ATK1,
    cb_001_battler_ATK2, cb_001_battler_ATK3}, cb_001_protect, cb_001_protect, 24, 24, 4},
    
    // Golduck
    {&_02Tiles, &_02Pal, cb_002_battler_idle_F, cb_002_battler_idle_B,
    cb_002_battler_U, cb_002_battler_L, cb_002_battler_R, cb_002_battler_FL, 
    cb_002_battler_FR, {cb_002_battler_ATK0, cb_002_battler_ATK1,
    cb_002_battler_ATK2, cb_002_battler_ATK3}, cb_002_protect, cb_002_protect, 24, 24, 2},
};


#endif /* POKEMON_BASE_ANIM_H_ */

