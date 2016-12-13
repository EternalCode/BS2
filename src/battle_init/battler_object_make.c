#include <pokeagb/pokeagb.h>
#include "../battler_data/battler_data.h"
#include "../battler_data/pokemon_base.h"

/*
 *
 * Obj->priv[0] next frame delay counter
 * Obj->priv[1] current frame index
 * Obj->priv[2] Species
 */

 #define SPAWNX_PLAYER 16
 #define SPAWNX_OPPONENT 180

const struct OamData large = {
                                .y = 0,
                                .affine_mode = 0,
                                .obj_mode = 0,
                                .mosaic = 0,
                                .bpp = 0,
                                .shape = 0,
                                .x = 0,
                                .matrix_num = 0,
                                .size = 3, //64x64
                                .tile_num = 0,
                                .priority = 1,
                                .palette_num = 0,
                                .affine_param = 0
};


static const struct Frame (**nullframe)[] = (const struct Frame (**)[])0x8231CF0;
static const struct RotscaleFrame (**nullrsf)[] = (const struct RotscaleFrame (**)[])0x8231CFC;
extern void activate_idle(struct Object* obj, u8 dir);

u8 init_battler(u16 species, u8 side) {
    extern void cb_battler_idle_B(struct Object*);
    u16 tag = (side) ? (0x1000 + species) : (0x1100 + species);
    struct SpritePalette battlerpalette = {p_base[species].palette_data, tag};
    struct SpriteTiles battlersprite = {p_base[species].image_data, 2048, tag};
    struct Template battler_temp = {tag, tag, &large, nullframe, &battlersprite,
                                    nullrsf, (ObjectCallback)p_base[species].idle_F
    };
    gpu_tile_obj_alloc_tag_and_upload(&battlersprite);
    gpu_pal_obj_alloc_tag_and_apply(&battlerpalette);
    u8 obj_id;
    if (side) {
        obj_id = template_instanciate_forward_search(&battler_temp, SPAWNX_PLAYER, 96, 0);
        player->obj_id = obj_id;
        activate_idle(&objects[obj_id], 0);
        player->old_dir = player->dir;
    } else {
        obj_id = template_instanciate_forward_search(&battler_temp, SPAWNX_OPPONENT, 96, 0);
        opponent->obj_id = obj_id;
        activate_idle(&objects[obj_id], 1);
        opponent->old_dir = opponent->dir;
    }
    return obj_id;
}












