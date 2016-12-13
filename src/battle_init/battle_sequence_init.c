#include <pokeagb/pokeagb.h>
#include "../../generated/images/BF_Grass.h"
#include "../../generated/images/BF_Grass2.h"
#include "../../generated/images/sky.h"
#include "../map_data/map_movement_permissions.h"
#include "../battle_state.h"
#include "../battler_data/pokemon_base.h"
#include "../../generated/images/sky.h"

//static struct engine_state* world_state = (struct engine_state*)0x02023BE4;
extern void world_state_add_obj(u8 hitbox, u8 hitbox2, u8 objid, enum ObjectType type, u16 index);

void init_battle_elements() {
    extern void setup(void);
    extern void c1_battle_gfx_load(void);
    setup();
    super.multi_purpose_state_tracker = 0;
    vblank_handler_set((SuperCallback)0x8046FC1);
    set_callback1((SuperCallback)c1_battle_gfx_load);
}


void c1_battle_gfx_load() {

    u8* op = (u8*)0x20370BA;
    u8* p = (u8*)0x20370BC;
    u8 i;
    switch (super.multi_purpose_state_tracker) {
    case 0:
    {
        gpu_tile_bg_drop_all_sets(0);
        struct BgConfig bg0_config = { 	
                                    .padding = 0,
                                    .b_padding = 0,
                                    .priority = 1,
                                    .palette = 0,
                                    .size = 0,
                                    .map_base = 31,
                                    .character_base = 2,
                                    .bgid = 0
        };
        struct BgConfig bg1_config = {	
                                    .padding = 0,
                                    .b_padding = 0,
                                    .priority = 2,
                                    .palette = 0,
                                    .size = 0,
                                    .map_base = 30,
                                    .character_base = 3,
                                    .bgid = 1
        };
        struct BgConfig bg2_config = {
                                    .padding = 0,
                                    .b_padding = 0,
                                    .priority = 3,
                                    .palette = 1,
                                    .size = 2,
                                    .map_base = 20,
                                    .character_base = 0,
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
        bg_vram_setup(1, (struct BgConfig *)&bg_config_data, 4);
        
        extern void player_execute_state(void);
        extern void opponent_execute_state(void);
        world_state->FSM_Player_state = player_execute_state;
        world_state->FSM_AI_state = opponent_execute_state;
       
        for (i = 0; i < 6; i++) {
            world_state->map_obj[i].objid = 0x3F;
        }
        
        
        //bgid_mod_y_offset(2, 50, 1); 
        super.multi_purpose_state_tracker++;
        break;
    }
    case 1:
    {
        // TODO : Make this not hard coded.
        void *char_base = (void *)0x6000000;
        void *map_base = (void *)0x600A000;
        lz77UnCompVram((void *)BF_GrassTiles, char_base);
        lz77UnCompVram((void *)BF_GrassMap, map_base);   
        gpu_pal_apply((void *)BF_GrassPal, 0, 64);
        
        char_base = (void *)0x6008000;
        map_base = (void *)0x600F800;
        lz77UnCompVram((void *)BF_Grass2Tiles, char_base);
        lz77UnCompVram((void *)BF_Grass2Map, map_base);   
        gpu_pal_apply((void *)BF_Grass2Pal, 16*2, 64);
 
        char_base = (void *)0x600C000;
        map_base = (void *)0x600F000;
        lz77UnCompVram((void *)skyTiles, char_base);
        lz77UnCompVram((void *)skyMap, map_base);   
        gpu_pal_apply((void *)skyPal, 16 * 6, 32);
        
        pal_fill_black();
        super.multi_purpose_state_tracker = 4;
        break;
    }
    case 2:
    {
        super.multi_purpose_state_tracker = 4;
        break;
    }
    case 3:
    {
        //wait state
        break;
    }
    case 4:
    {
        extern void draw_portraits(u16, u16);
        //*p = rand() % 163;
        *p = 1;
        *op = 0;//rand() % 163;
        draw_portraits(*p, *op);
        super.multi_purpose_state_tracker++;
        break;
        
    }
    case 5:
    {
        // generate battler
        extern void battler_make(u16, u8, u8);
        battler_make (*p, 20, 1);
        battler_make (*op, 20, 0);
        
        // draw level font
        extern void draw_name(u8);
        draw_name(1);
        draw_name(0);
        
        // draw health
        extern void hpbars_cleaninit(u8);
        extern void drawbar(u8, u8);
        hpbars_cleaninit(0);
        
        extern u8 calc_hp(u8);
        drawbar(calc_hp(0), 0);
        drawbar(calc_hp(1), 1);
        super.multi_purpose_state_tracker++;
        break;
        
    }
    case 6:
    {
        extern void init_battler(u16, u8);
        init_battler(0, 0);
        init_battler(*p, 1);        
        world_state_add_obj(player->hitbox_x, player->hitbox_y, player->obj_id, BATTLER_OBJ, 0);
        world_state_add_obj(opponent->hitbox_x, opponent->hitbox_y, opponent->obj_id, BATTLER_OBJ, 0);
        super.multi_purpose_state_tracker++;
        break;
    }
    case 7:
    {
        // initialize map array
        u8* map_data = (u8*)malloc_and_clear( sizeof(map_grass));
        memcpy((void*)map_data, (void*)&map_grass, sizeof(map_grass));
        world_state->map = (union map_state_u*)map_data;
        super.multi_purpose_state_tracker++;
        break;
        
    }
    default:
        bgid_mark_for_sync(2);
        bgid_mark_for_sync(0);
        bgid_mark_for_sync(1);
        gpu_sync_bg_show(2);
        gpu_sync_bg_show(0);
        gpu_sync_bg_show(1);
        
        extern void vblank_cb_spq(void);
        extern void c2_battle(void);
        extern void battle_handler(void);
        vblank_handler_set(vblank_cb_spq);
        set_callback2(c2_battle);
        set_callback1(battle_handler);       
        break;
    };
    return;
}

void battle_handler() {
    REG_BG2VOFS = 0;
    REG_BG1VOFS = 0;
    REG_BG2CNT |= 0x2000;
    bgid_mod_x_offset(1, 1 << 6 , 1);
    extern void update_world(void);
    update_world();
    //world_state->FSM_AI_state();
    world_state->FSM_Player_state();

    extern void evaluate_world_collision(void);
    evaluate_world_collision();
}

