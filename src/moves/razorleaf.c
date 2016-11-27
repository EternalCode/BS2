#include <pokeagb/pokeagb.h>
#include "../move_animations.h"

extern u8 animation_frame_handler_move(struct Object* obj, u8 frame_start, u8 frame_end, u16 frame_duration[],
                                    s8 x_displace, s8 y_displace, void* src, u8 loop_times);
                                    
void razor_leaf_anim(struct Object* obj) {
    // cycle frames
    u16 frame_duration[] = {3, 3, 3, 3, 3, 3, 3, 3};
    if (animation_frame_handler_move(obj, 0, 7, frame_duration, 4, 0, &razor_leafTiles, 4)) {
        extern void obj_attack_free(struct Object* obj);
        obj_attack_free(obj);
    }
    return;
}

