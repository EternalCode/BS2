#include <pokeagb/pokeagb.h>
#include "../../generated/images/BF_Grass.h"
#include "../../generated/images/sky.h"



void init_battle_elements() {
    extern void setup(void);
    extern void battle_bg(void);
    setup();
    super.multi_purpose_state_tracker = 0;
    vblank_handler_set((SuperCallback)0x8046FC1);
    set_callback1((SuperCallback)battle_bg);
}

void battle_bg() {
    switch (super.multi_purpose_state_tracker) {
    case 0:
    {
        gpu_tile_bg_drop_all_sets(0);
        struct BgConfig bg0_config = { 	
                                    .padding = 0,
                                    .b_padding = 0,
                                    .priority = 2,
                                    .palette = 1,
                                    .size = 0,
                                    .map_base = 31,
                                    .character_base = 0,
                                    .bgid = 0
        };
        struct BgConfig bg1_config = {	
                                    .padding = 0,
                                    .b_padding = 0,
                                    .priority = 0,
                                    .palette = 0,
                                    .size = 0,
                                    .map_base = 30,
                                    .character_base = 1,
                                    .bgid = 1
        };
        struct BgConfig bg2_config = {
                                    .padding = 0,
                                    .b_padding = 0,
                                    .priority = 3,
                                    .palette = 0,
                                    .size = 0,
                                    .map_base = 29,
                                    .character_base = 2,
                                    .bgid = 2
        };
        struct BgConfig bg3_config = {
                                    .padding = 0,
                                    .b_padding = 0,
                                    .priority = 1,
                                    .palette = 0,
                                    .size = 0,
                                    .map_base = 28,
                                    .character_base = 3,
                                    .bgid = 3
        };
        struct BgConfig bg_config_data[4] = {bg0_config, bg1_config, bg2_config, bg3_config};
        bg_vram_setup(0, (struct BgConfig *)&bg_config_data, 4);
        super.multi_purpose_state_tracker++;
        break;
    }
    case 1:
    {
        // TODO : Make this not hard coded.
        void *char_base = (void *)0x6000000 + (0x4000 * 0);
        void *map_base = (void *)0x6000000 + (0xF800 - (0x800 * 0));
        lz77UnCompVram((void *)BF_GrassTiles, char_base);
        lz77UnCompVram((void *)BF_GrassMap, map_base);
        gpu_pal_apply((void *)BF_GrassPal, 0, 64);
        
        char_base += 0x8000;
        map_base -= (0x800 * 2);
        lz77UnCompVram((void *)skyTiles, char_base);
        lz77UnCompVram((void *)skyMap, map_base);
        gpu_pal_apply((void *)skyPal, 16 * 3, 64);  

        bgid_mark_for_sync(0);
        bgid_mark_for_sync(2);
        bgid_mark_for_sync(3);
        gpu_sync_bg_show(0);
        gpu_sync_bg_show(2);
        gpu_sync_bg_show(3);
        
        super.multi_purpose_state_tracker++;
        break;
    }
    case 2:
    {
    
        extern void draw_portraits(u16, u16);
        draw_portraits(0, 1);
        super.multi_purpose_state_tracker++;
        break;
        
    }
    default:
        REG_BG2VOFS = 0;
        bgid_mod_x_offset(2, 60, 1);
        break;
    };
    return;
}