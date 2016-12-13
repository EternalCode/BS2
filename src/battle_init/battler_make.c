#include <pokeagb/pokeagb.h>
#include "../battler_data/battler_data.h"
#include "../battle_state.h"
#include "../battler_data/pokemon_base.h"


extern u8 init_battler(u16 species, u8 side);
 
 
void battler_make(u16 species, u8 level, u8 side) {
    struct battler* fighter = (side) ? player : opponent;
    fighter->hitbox_x = 32 - p_base[species].hitbox_x;
    fighter->hitbox_y = 32 - p_base[species].hitbox_y;
    fighter->dir = FACING_LEFT;
    fighter->has_jumped = false;
    fighter->apply_dir_to_jump = false;
    fighter->is_meleeing = false;
    fighter->hitbox_increase_x = 0;
    fighter->hitbox_increase_y = 0;
    fighter->x_delay_time = 0;
    fighter->x_delay_timer = 0;
    fighter->delta_time = 0;
    fighter->delta_x = 0;
    fighter->delta_y = 0;
    fighter->obj_id = 0;
    u8 i;
    for (i = 0; i < 8; i++) {
        fighter->hpbarids[i] = 0x3F;
    }
    fighter->bstate = BATTLER_MOVEMENT;
    fighter->objid_move = 0x3F;   
    struct PokemonBaseStat species_stats = pokemon_base_stats[species+ 1];
    fighter->current_hp = ((species_stats.hp) >> 3) * level;
    fighter->total_hp = fighter->current_hp;
    fighter->level = level;
    fighter->atk = (species_stats.atk >> 3) * level;
    fighter->spatk = (species_stats.spatk >> 3) *level;
    fighter->def = (species_stats.def >> 3) * level;
    fighter->spdef = (species_stats.spdef >> 3) * level;
    fighter->spd = (species_stats.spd >> 4) * level;
    fighter->species = species;
    fighter->boosts.all = 0;
    fighter->boosting = false;
    fighter->protect_pp = 15;
    fighter->protect_enable = 0;
    memcpy((void *)fighter->name, (void*)&battler_names[species], 15);
}

