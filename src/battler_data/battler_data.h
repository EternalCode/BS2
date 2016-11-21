#ifndef BATTLER_DATA_H_
#define BATTLER_DATA_H_

#include <pokeagb/pokeagb.h>

struct movement_frames {
    u8 frame_count;
    u8 loop_time;
    u8 displacement;
    u8 padding;
};

struct b_attacks {
    u8 id;
    u8 time;
    u8 frame_count;
};

struct battler_base {
    struct movement_frames up;
    struct movement_frames down;
    struct movement_frames side;
    struct movement_frames jump; // maybe
    u8 attacks_learnable[8]; // max 8
    u16 species
};

static const struct battler_base p_base[1] = {
    { {NULL}, {NULL}, {NULL}, {NULL}, 0, 1, 2, 3, 4, 5, 6, 7, 1},
};


struct battler {
    u16 is_status : 1;
    u16 status_id : 4; // par, psn, slp, brn
    u16 freeze_state : 1; // middle of animation
    u16 padding : 6;
    u16 current_hp;
    u16 total_hp;
    u8 level;
    u16 atk;
    u16 spatk;
    u16 def;
    u16 spdef;
    u16 spd;    
    struct b_attacks attack[4];
    u16 species;
    pchar name[15];
    u8 obj_id;
};

struct battler* opponent = (struct battler*)0x202024C;
struct battler* player = (struct battler*)0x2024284;


static const pchar battler_names[3][15] = {
    _"Bulbasaur",
    _"Ivysaur",
    _"Venasaur",
};

#endif /* BATTLER_DATA_H_ */
