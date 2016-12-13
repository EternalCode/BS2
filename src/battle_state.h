#ifndef BATTLE_STATE_H_
#define BATTLE_STATE_H_

#include <pokeagb/pokeagb.h>

#define Y_SCALE 0x100

enum ObjectType {
    BATTLER_OBJ, // impassable
    MOVE_OBJ, // Applies damage on contact
    TERRAIN_OBJ, // Impassable terrain
};

union map_state_u {
    u8 map_2d[26][73]; // 23 rows and 35 coloums
    u8 map_1d[26 * 73];
};

struct map_objects {
    u8 hitbox_x;
    u8 hitbox_y;// Amount to add to objy coord
    u8 objid;
    enum ObjectType type;
    u16 index; // Species or move index
};

struct engine_state {
    union map_state_u* map;
    struct map_objects map_obj[6]; // these are ones that can collide meaningfully
    // engine element positions
    SuperCallback FSM_Player_state;
    SuperCallback FSM_AI_state;   
};

static struct engine_state* world_state = (struct engine_state*)0x02023BE4;

#endif /* BATTLE_STATE_H_ */

