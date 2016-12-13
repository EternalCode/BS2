#include <pokeagb/pokeagb.h>


u16 AI_decision_parse(u8 move) {
    u16 input = 0;
    switch (rand() % 12) {
        case 0:
            input = KEY_A;
            break;  
        case 1:
            input = KEY_B;
            break;
        case 2:
            input = KEY_L;
            break;
        case 3:
            input = KEY_R;
            break;
        case 5:
            input = KEY_UP;
            break;
        case 6:
            input = KEY_DOWN;
            break;
        case 7:
            input = KEY_RIGHT;
            break;
        case 8:
            input = KEY_LEFT;
            break;
        case 9:
            input = KEY_UP | KEY_RIGHT;
            break;
        case 10:
            input = KEY_UP | KEY_LEFT;
            break;
        case 11:
            input = KEY_DOWN | KEY_RIGHT;
            break;
        case 12:
            input = KEY_DOWN | KEY_LEFT;
            break;
        
    };
    return input;    
}            
