#ifndef MOVE_TABLE_H_
#define MOVE_TABLE_H_

#include <pokeagb/pokeagb.h>
#include "../move_animations.h"

extern void razor_leaf_anim(struct Object* obj);


struct move_entry {
    u8 base_dmg;
    u8 size;
    u8 hitbox;
    u8* move_img;
    u8* move_pal;
    ObjectCallback move_cb;
};

static const struct move_entry move[] = {
    {10, 0, 24, (u8*)&razor_leafTiles, (u8*)&razor_leafPal, (ObjectCallback)razor_leaf_anim},
};

enum MoveIndex {
  INDEX_RAZORLEAF,  
};


#endif /* MOVE_TABLE_H_ */

