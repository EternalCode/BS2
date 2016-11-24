#include <pokeagb/pokeagb.h>
#include "../../generated/images/hpbar.h"
#include "../battler_data/battler_data.h"

#define player_x 57
#define opponent_x 140

const struct OamData bar = {
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

struct SpritePalette hppalette = {(u8*)&hpbarPal, 0x154};

static struct battler* opponent = (struct battler*)0x202024C;
static struct battler* player = (struct battler*)0x2024284;
static const struct Frame** nullframe = (const struct Frame**)0x8231CF0;
static const struct RotscaleFrame** nullrsf = (const struct RotscaleFrame**)0x8231CFC;

void hpbars_cleaninit(u8 slot) {
    u8 i;
    for (i = 0; i < 8; i++) {
        u8 tiletag = (i + ((slot * 8) + slot) + 0x154);
        struct SpriteTiles hpbarsprite = {&hpbarTiles[32 * 8], 32, tiletag};
        struct Template hp_temp = {
            tiletag, 0x154, &bar, nullframe, &hpbarsprite, nullrsf, (ObjectCallback)0x800760D
        };
        gpu_tile_obj_alloc_tag_and_upload(&hpbarsprite);
        gpu_pal_obj_alloc_tag_and_apply(&hppalette);
        u8 position = ((slot) ? opponent_x : player_x);
        u8 objid = template_instanciate_forward_search(&hp_temp, position + (i * 8), 26, 0);
        if (slot) {
            opponent->hpbarids[i] = objid;
        } else {
            player->hpbarids[i] = objid;
        }
    }
    
    if (!(slot))
        hpbars_cleaninit(1);
}


u8 calc_hp(u8 side) {
    u16 m_hp = 0;
    u16 c_hp = 0;
    
    switch(side) {
        case 0:
        {
            c_hp = player->current_hp;
            m_hp = player->total_hp;
            break;            
        }
        default:
        {
            c_hp = opponent->current_hp;
            m_hp = opponent->total_hp;
            break;
        }
    };
    return ((((c_hp * 100) / m_hp) * 64) / 100);      
}


void drawbar(u8 pixel_count, u8 side) {
    u8 bar[8] = {8, 8, 8, 8, 8, 8, 8, 8};
    u8 i = 0;
    while (pixel_count >= 8) {
        bar[i] = 0;
        pixel_count -= 8;
        i += 1;
    }
    switch (pixel_count) {
        case 0:
            // full bar
            break;
        case 1:
        {
            // px 1
            bar[i] = 7;
            break;
        }
        case 2:
        {
            // px 2
            bar[i] = 6;
        }
        case 3:
        {
            // px 3
            bar[i] = 5;
        }
        case 4:
        {
            // px 4
            bar[i] = 4;
        }
        case 5:
        {
            // px 5
            bar[i] = 3;
        }
        case 6:
        {
            // px 6
            bar[i] = 2;
        }
        case 7:
        {
            // px 7
            bar[i] = 1;
        }  
    };
    
    // determine bar color
    u8 color = 0;
    for (i = 0; i < 8; i++) {
        if (bar[i] == 8) {
            if (i > 4) {
                // green
                color = 0;
            } else if (i > 2) {
                // yellow
                color = 1;
            } else {
                // red
                color = 2;
            }
            break;
        }
    }
    
    // draw bar
    for (i = 0; i < 8; i++) {
        u8 objid;
        if (side) {
            objid = opponent->hpbarids[i];
        } else {
            objid = player->hpbarids[i];
        }
        u32* dst = (u32*)((objects[objid].final_oam.tile_num * 32) + SPRITE_RAM);
        u16 tileid = ((9 * color * 32) + (bar[i] * 32));
        u32* src = (u32*)&hpbarTiles[tileid];
        memcpy(dst, src, 32);
    }
    
}

void task_hp_deplete (u8 tid) {
    struct Task* t = &tasks[tid];
    if (t->priv[3] < (t->priv[1] - t->priv[2])) {
        drawbar(t->priv[0], t->priv[1] + t->priv[3]);
    }
    t->priv[3]++;
    return;
}


void dmg_bar(u8 side, u8 start, u8 to) {
    u8 tid = task_add(dmg_bar, 0x1);
    tasks[tid].priv[0] = side;
    tasks[tid].priv[1] = start;
    tasks[tid].priv[2] = to;
    tasks[tid].priv[3] = 0;
    u8 i;
    for (i = 0; i < (start - to); i ++) {
        drawbar(side, start - i);
    }
}
