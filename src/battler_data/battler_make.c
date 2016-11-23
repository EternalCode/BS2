#include <pokeagb/pokeagb.h>
#include "battler_data.h"

static struct battler* opponent = (struct battler*)0x202024C;
static struct battler* player = (struct battler*)0x2024284;

void battler_make(u16 species, u8 level, u8 side) {
    struct battler* this_pkmn;
    switch (side) {
        case 1:
        {
            this_pkmn = (struct battler*)&opponent[side - 1];
            break;
        }
        default:
        {
            this_pkmn = (struct battler*)player;
            break;
        }
    };
    
    memset((void*)this_pkmn, 0, sizeof(struct battler));
    
    // fill base stats
    struct PokemonBaseStat species_stats = pokemon_base_stats[species];
    
    // hp
    this_pkmn->total_hp = ((species_stats.hp) >> 3) * level;
    this_pkmn->current_hp = this_pkmn->total_hp;
    //atk
    this_pkmn->atk = (species_stats.atk >> 3) * level;
    this_pkmn->spatk = (species_stats.spatk >> 3) *level;
    
    // def
    this_pkmn->def = (species_stats.def >> 3) * level;
    this_pkmn->spdef = (species_stats.spdef >> 3) * level;
    
    // speed
    this_pkmn->spd = (species_stats.spd >> 4) * level;
    
    // misc data
    memcpy((void *)this_pkmn->name, (void*)&battler_names[species], 15);
    this_pkmn->species = species;    
    this_pkmn->level = level;
    
    // pick attacks
    
}





