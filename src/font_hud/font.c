#include <pokeagb/pokeagb.h>
#include "../battler_data/battler_data.h"
#include "../../generated/images/font.h"

#define op_name_pos 130
#define player_name 46

static const struct Frame (**nullframe)[] = (const struct Frame (**)[])0x8231CF0;
static const struct RotscaleFrame (**nullrsf)[] = (const struct RotscaleFrame (**)[])0x8231CFC;

const struct OamData font_oam = {
                                .y = 0,
                                .affine_mode = 0,
                                .obj_mode = 0,
                                .mosaic = 0,
                                .bpp = 0,
                                .shape = 0,
                                .x = 0,
                                .matrix_num = 0,
                                .size = 0,
                                .tile_num = 0,
                                .priority = 0,
                                .palette_num = 0,
                                .affine_param = 0
};

struct SpritePalette fontpalette = {(u8*)&fontPal, 0xAA};

void oam_letter_make(pchar letter, u16 tile) {
    u8 caps_letter = (letter > 0xD4) ? (letter - 0x1A) : (letter);

    struct SpriteTiles fontsprite = {&fontTiles[(caps_letter - 0xBB) * 32], 64, (caps_letter + 0xAA)};
    
    
    struct Template font_temp = {
                                (caps_letter + 0xAA), 0xAA,
                                &font_oam, nullframe, &fontsprite, nullrsf, 
                                (ObjectCallback)0x800760D
                                };
    gpu_tile_obj_alloc_tag_and_upload(&fontsprite);
    gpu_pal_obj_alloc_tag_and_apply(&fontpalette);
    template_instanciate_forward_search(&font_temp, tile, 17, 0x0); 
}

/* TODO: Use less OAMs */

void draw_name(u8 side) {
    u8 x_pos = 0;
    u8 len = 0;
    pchar *name;
    if (side) {
        len = pstrlen(opponent->name);
        name = &opponent->name[0];
        x_pos = op_name_pos;
    } else {
        len = pstrlen(player->name);
        x_pos = player_name;
        name = &player->name[0];
    }
    
    u8 i = 0;
    for (i = 0; i < len; i++) {
        oam_letter_make(name[i], (x_pos + (7 * i)));
    }
}