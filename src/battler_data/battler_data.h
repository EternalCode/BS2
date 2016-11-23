#ifndef BATTLER_DATAH_H_
#define BATTLER_DATAH_H_

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
    u16 species;
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
    u8 hpbarids[8];
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


#endif /* BATTLER_DATAH_H_ */
