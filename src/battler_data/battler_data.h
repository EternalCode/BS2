#ifndef BATTLER_DATAH_H_
#define BATTLER_DATAH_H_

#include <pokeagb/pokeagb.h>
#include "../battle_state.h"


struct movement_frames {
    u8 frame_count;
    u8 loop_time;
    u8 displacement;
    u8 padding;
};

struct battler_base {
    void* image_data;
    void* palette_data;
    ObjectCallback idle_F;
    ObjectCallback idle_B;
    ObjectCallback walk_U;
    ObjectCallback walk_D;
    ObjectCallback walk_L;
    ObjectCallback walk_R;
    ObjectCallback walk_UL;
    ObjectCallback walk_UR;
    ObjectCallback walk_DL;
    ObjectCallback walk_DR;
    ObjectCallback atk[4];
    u8 hitbox_size;
    
};

enum BattlerFacingDir {
    DOWN,
    UP,
};

enum HitboxSize {
    HITBOX_SMALL,
    HITBOX_MEDIUM,
    HITBOX_LARGE,
};


enum BattlerStates {
    BATTLER_MOVEMENT,
    BATTLER_ATTACKING,
    BATTLER_DAMAGED,
    BATTLER_FAINT,
};

struct battler {
    // Positional vectors
    u8 map_x;
    u8 map_y;
    u8 hit_box_size;
    enum BattlerFacingDir dir;
    
    // tied object logging
    u8 obj_id;
    u8 hpbarids[8];
    
    // game callback controller
    enum BattlerStates bstate;
    
    // Move obj ids
    u8 objid_move;
    
    // Battler status related
    u16 current_hp;
    u16 total_hp;
    u8 level;
    u16 atk;
    u16 spatk;
    u16 def;
    u16 spdef;
    u16 spd;    
    u16 species;
    
    // unneeded for now, but perhaps useful later
    pchar name[15];

};


static const enum HitboxSize battler_sizes[] = {
    HITBOX_SMALL,
};


static const pchar battler_names[169][15] = {
    _"Bulbasaur",
    _"Ivysaur",
    _"Venasaur",
    _"Charmander",
    _"Charmeleon",
    _"Charizard",
    _"Squirtle",
    _"Wartortle",
    _"Blastoise",
    _"Caterpie",
    _"Metapod",
    _"Butterfree",
    _"Weedle",
    _"Kakuna",
    _"Beedrill",
    _"Pidgey",
    _"Pidgeotto",
    _"Pidgeot",
    _"Rattata",
    _"Rattata",
    _"Raticate",
    _"Raticate",
    _"Spearow",
    _"Fearow",
    _"Ekans",
    _"Arbok",
    _"Pikachu",
    _"Raichu",
    _"Sandshrew",
    _"Sandslash",
    _"NidoranF",
    _"Nidorina",
    _"Nidoqueen",
    _"NidoranM",
    _"Nidorino",
    _"Nidoking",
    _"Clefairy",
    _"Clefable",
    _"Vulpix",
    _"Ninetails",
    _"Jigglypuff",
    _"Wigglytuff",
    _"Zubat",
    _"Zubat", 
    _"Golbat",
    _"Golbat",
    _"Oddish",
    _"Gloom",
    _"Gloom",
    _"Vileploom",
    _"Vileploom",
    _"Paras",
    _"Parasect",
    _"Venonat",
    _"Venomoth",
    _"Diglet",
    _"Dugtrio",
    _"Meowth",
    _"Persian",
    _"Psyduck",
    _"Golduck",
    _"Mankey",
    _"Primape",
    _"Growlithe",
    _"Arcanine",
    _"Poliwag",
    _"Poliwhirl",
    _"Poliwrath",
    _"Abra",
    _"Kadabra",
    _"Alakazam",
    _"Machop",
    _"Machoke",
    _"Machamp",
    _"Belsprout",
    _"Weepinbell",
    _"Victrebell",
    _"Tentacool",
    _"Tentacruel",
    _"Geodude",
    _"Graveler",
    _"Golem",
    _"Ponyta",
    _"Rapidash",
    _"Slowpoke",
    _"Slowbro",
    _"Magnemite",
    _"Magneton",
    _"Farfechd",
    _"Doduo",
    _"Doduo",
    _"Dodrio",
    _"Dodrio",
    _"Seel",
    _"Dewgong",
    _"Grimer",
    _"Muk",
    _"Shellder",
    _"Cloyster",
    _"Ghastly",
    _"Haunter",
    _"Gengar",
    _"Onix",
    _"Drowzee",
    _"Hypno",
    _"Hypno",
    _"Krabby",
    _"Kingler",
    _"Voltorb",
    _"Electrode",
    _"Eggecute",
    _"Exeggutor",
    _"Cubone",
    _"Marowak",
    _"Hitmonlee",
    _"Hitmonchan",
    _"Lickitung",
    _"Koffing",
    _"Weezing",
    _"Rhyhorn",
    _"Rhyhorn",
    _"Rhydon",
    _"Rhydon",
    _"Chansey",
    _"Tangela",
    _"Kangaskhan",
    _"Horsea",
    _"Seadra",
    _"Goldeen",
    _"Seaking",
    _"Staryu",
    _"Starmie",
    _"Mr.Mime",
    _"Scyther",
    _"Jinx",
    _"Electabuzz",
    _"Magmar",
    _"Pinsir",
    _"Tauros",
    _"Magikarp",
    _"Magikarp",
    _"Gyarados",
    _"Gyarados",
    _"Lapras",
    _"Ditto",
    _"Eevee",
    _"Vaporeon",
    _"Jolteon",
    _"Flareon",
    _"Porygon",
    _"Omnistar",
    _"Omnistar",
    _"Kabuto",
    _"Kabutops",
    _"Aerodactyl",
    _"Snorlax",
    _"Articuno",
    _"Zapdos",
    _"Moltres",
    _"Dratini",
    _"Dragonair",
    _"Dragonite",
    _"Mewtwo",
    _"Mew",   
};

static struct battler* opponent = (struct battler*)0x202024C;
static struct battler* player = (struct battler*)0x2024284;

#endif /* BATTLER_DATAH_H_ */
