#ifndef BATTLER_DATAH_H_
#define BATTLER_DATAH_H_

#include <pokeagb/pokeagb.h>


struct battler_base {
    void* image_data;
    void* palette_data;
    ObjectCallback idle_F;
    ObjectCallback idle_B;
    ObjectCallback jump_U;
    ObjectCallback walk_L;
    ObjectCallback walk_R;
    ObjectCallback falling_L;
    ObjectCallback falling_R;
    ObjectCallback atk[4];
    ObjectCallback protect;
    ObjectCallback burst_move;
    u8 hitbox_x;
    u8 hitbox_y;
    s8 weight;
    
};

enum BattlerFacingDir {
    FACING_UP = (1 << 0),
    FACING_LEFT = (1 << 1),
    FACING_RIGHT = (1 << 2),
    FACING_ONLY_UP = (1 << 3),
};

enum BattlerStates {
    BATTLER_MOVEMENT,
    BATTLER_UNCONTROLLABLE_JUMPING,
    BATTLER_ATTACKING,
    BATTLER_DAMAGED,
    BATTLER_FAINT,
    BATTLER_UTURN,
    BATTLER_BLOCKING,
};

struct battler {
    // Character hit box
    u8 hitbox_x;
    u8 hitbox_y;
    
    // Currently facing direction component
    enum BattlerFacingDir dir;
    enum BattlerFacingDir old_dir;
   // u8 loop_times;
   u8 anim_loop;
    
    // double jump flag
    bool has_jumped;
    
    // flag toggled when directional jumping    
    bool apply_dir_to_jump;
    
    // flag toggled when melee attack is on frame
    bool is_meleeing;
    
    // flag to stop camera movement -> powering up
    bool boosting;
    
    u8 protect_enable;
    u8 protect_duration;
    u8 protect_pp;
    
    u8 hitbox_increase_x;
    u8 hitbox_increase_y;
    
    // World gravity physics relatd variables
    u16 x_delay_time;
    u16 x_delay_timer;
    u16 delta_time; // relative to animation start
    s16 delta_x; // transformation in X direction -> idle state sets to 0
    s16 delta_y; // transformation in Y axis -> idle state sets to 0
    
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
    
    // Base stat modifiers
    union {
        u16 spatk_boost : 3;
        u16 atk_boost : 3;
        u16 spdef_boost : 3;
        u16 def_boost : 3;
        u16 spd_boost : 3;
        u16 padding : 1;
        u16 all;
    } boosts;
    // unneeded for now, but perhaps useful later
    pchar name[15];

};


static const pchar battler_names[169][15] = {
    _"SCYTHER",
    _"Golduck",
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
