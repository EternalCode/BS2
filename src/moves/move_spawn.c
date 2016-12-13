#include <pokeagb/pokeagb.h>
#include "move_table.h"
#include "../battler_data/battler_data.h"
#include "../battle_state.h"

extern void world_state_add_obj(u8 hitbox, u8 hitbox2, u8 objid, enum ObjectType type, u16 index);

const struct OamData move32 = {
                                .y = 0,
                                .affine_mode = 0,
                                .obj_mode = 0,
                                .mosaic = 0,
                                .bpp = 0,
                                .shape = 0,
                                .x = 0,
                                .matrix_num = 0,
                                .size = 2, // 32x32
                                .tile_num = 0,
                                .priority = 0,
                                .palette_num = 0,
                                .affine_param = 0
};

const struct OamData move64 = {
                                .y = 0,
                                .affine_mode = 0,
                                .obj_mode = 0,
                                .mosaic = 0,
                                .bpp = 0,
                                .shape = 0,
                                .x = 0,
                                .matrix_num = 0,
                                .size = 3, //64 x 64
                                .tile_num = 0,
                                .priority = 0,
                                .palette_num = 0,
                                .affine_param = 0
};


static const struct Frame (**nullframe)[] = (const struct Frame (**)[])0x8231CF0;
static const struct RotscaleFrame (**nullrsf)[] = (const struct RotscaleFrame (**)[])0x8231CFC;

void empty_cb_oac(struct Object* obj) {
    return;
}

u8 create_move(u16 moveid, s16 x, s16 y, u8 side, u8 hitbox, u8 hitbox2) {
    struct SpritePalette movepalette = {(void*)move[moveid].move_pal, (0x3000 + moveid)};
    struct SpriteTiles movesprite = {move[moveid].move_img, 512, ((0x3000 * (side + 1)) + moveid)};
    struct Template move_temp = {
                                    ((0x3000 * (side + 1)) + moveid), (0x3000 + moveid),
                                    NULL, nullframe, &movesprite, nullrsf,
                                    (ObjectCallback)move[moveid].move_cb
    };
    switch (move[moveid].size) {
        case 0:
            move_temp.oam = &move32;
            break;
        default:
            move_temp.oam = &move64;
            movesprite.size = 2048; 
            break;
    };
    gpu_tile_obj_alloc_tag_and_upload(&movesprite);
    gpu_pal_obj_alloc_tag_and_apply(&movepalette);
    u8 objid = template_instanciate_forward_search(&move_temp, x, y, 0);
    world_state_add_obj(hitbox, hitbox2, objid, MOVE_OBJ, moveid);
    return objid;
}


s8* direction_mod(u8 distance, enum BattlerFacingDir dir, s8* dimensions) {
    switch (dir) {
        case FACING_LEFT:
            dimensions[0] = -(distance);
            dimensions[1] = 0;
            break;
        default:
            dimensions[0] = distance;
            dimensions[1] = 0;
            break;
    };
    return (s8*)dimensions;
}













