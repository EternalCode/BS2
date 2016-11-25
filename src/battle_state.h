#ifndef BATTLE_STATE_H_
#define BATTLE_STATE_H_

#include <pokeagb/pokeagb.h>

union map_state_u {
    u8 map_2d[26][38]; // 23 rows and 35 coloums
    u8 map_1d[26 * 38];
};
struct engine_state {
    union map_state_u* map;
    SuperCallback FSM_state;
    
};

static struct engine_state* world_state = (struct engine_state*)0x02023BE4;

#endif /* BATTLE_STATE_H_ */

