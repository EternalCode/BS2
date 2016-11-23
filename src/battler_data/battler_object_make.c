#include <pokeagb/pokeagb.h>
#include "../../generated/images/battlers_frames/001.h"
#include "../battler_data/battler_data.h"

/*
 *
 * Obj->priv[0] next frame delay counter
 * Obj->priv[1] current frame index
 * Obj->priv[2] Species
 */

 #define SPAWNX_PLAYER 16
 #define SPAWNX_OPPONENT 224

const struct OamData small = {
                                .y = 0,
                                .affine_mode = 0,
                                .obj_mode = 0,
                                .mosaic = 0,
                                .bpp = 0,
                                .shape = 0,
                                .x = 0,
                                .matrix_num = 0,
                                .size = 2, //32 x 32
                                .tile_num = 0,
                                .priority = 0,
                                .palette_num = 0,
                                .affine_param = 0
};

static const struct Frame** nullframe = (const struct Frame**)0x8231CF0;
static const struct RotscaleFrame** nullrsf = (const struct RotscaleFrame**)0x8231CFC;
static struct battler* opponent = (struct battler*)0x202024C;
static struct battler* player = (struct battler*)0x2024284;


void init_battler(u16 species, u8 side) {
    extern void cb_battler_idle_F(struct Object*);
    struct SpritePalette battlerpalette = {&_01Pal, (0x1000 + species)};
    struct SpriteTiles battlersprite = {&_01Tiles[0], 512, ((0x1000 * (side + 1)) + species)};
    struct Template battler_temp = {
                                    ((0x1000 * (side + 1)) + species), (0x1000 + species),
                                    &small, nullframe, &battlersprite, nullrsf,
                                    (ObjectCallback)cb_battler_idle_F
    };
    gpu_tile_obj_alloc_tag_and_upload(&battlersprite);
    gpu_pal_obj_alloc_tag_and_apply(&battlerpalette);
    if (!side) {
        u8 obj_id = template_instanciate_forward_search(&battler_temp, SPAWNX_PLAYER, 140, 0);
        objects[obj_id].final_oam.h_flip = 1;
        player->obj_id = obj_id;
    } else {
        u8 obj_id = template_instanciate_forward_search(&battler_temp, SPAWNX_OPPONENT, 140, 0);
        opponent->obj_id = obj_id;
    }
}












