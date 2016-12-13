#ifndef MOVE_TABLE_H_
#define MOVE_TABLE_H_

#include <pokeagb/pokeagb.h>
#include "../move_animations.h"

extern void razor_leaf_anim(struct Object* obj);
extern void swords_dance_anim(struct Object* obj);
extern void obj_null_oac(struct Object* obj);
extern void x_scissor_anim(struct Object* obj);
extern void slash_anim(struct Object* obj);
extern void protect_anim(struct Object* obj);
extern void water_gun_anim(struct Object* obj);
extern void whirlpool_anim(struct Object* obj);
extern void psyshock_anim(struct Object* obj);


struct move_entry {
    u8 base_dmg;
    u8 size;
    u8 hitbox_x;
    u8 hitbox_y;
    u8* move_img;
    u8* move_pal;
    ObjectCallback move_cb;
};

static const struct move_entry move[] = {
    {10, 0, 18, 18, (u8*)&razor_leafTiles, (u8*)&razor_leafPal, (ObjectCallback)razor_leaf_anim},
    {0, 0, 0, 0, (u8*)&swords_danceTiles, (u8*)&swords_dancePal, (ObjectCallback)swords_dance_anim},
    {0, 1, 0, 0, (u8*)&swords_dance2Tiles, (u8*)&swords_dance2Pal, (ObjectCallback)obj_null_oac},
    {0, 0, 0, 0, (u8*)&x_scissorTiles, (u8*)&x_scissorPal, (ObjectCallback)x_scissor_anim},
    {0, 0, 0, 0, (u8*)&slashTiles, (u8*)&slashPal, (ObjectCallback)slash_anim},
    {0, 0, 0, 0, (u8*)&slashTiles[1024], (u8*)&slashPal, (ObjectCallback)slash_anim},
    {0, 1, 0, 0, (u8*)&protectTiles, (u8*)&protectPal, (ObjectCallback)protect_anim},
    {0, 0, 5, 5, (u8*)&water_gunTiles, (u8*)&water_gunPal, (ObjectCallback)water_gun_anim},
    {0, 0, 32, 32, (u8*)&whirlpoolTiles, (u8*)&whirlpoolPal, (ObjectCallback)whirlpool_anim},
    {0, 0, 28, 28, (u8*)&psyshockTiles, (u8*)&psyshockPal, (ObjectCallback)psyshock_anim},
};

enum MoveIndex {
    INDEX_RAZORLEAF,
    INDEX_SWORDSDANCE,
    INDEX_SWORDSDANCE2,
    INDEX_XSCISSOR,
    INDEX_SLASH_LEFT,
    INDEX_SLASH_RIGHT,
    INDEX_PROTECT,
    INDEX_WATERGUN,
    INDEX_WHIRLPOOL,
    INDEX_PSYSHOCK,
};


#endif /* MOVE_TABLE_H_ */

