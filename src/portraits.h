#ifndef PORTRAITS_H_
#define PORTRAITS_H_

#include <pokeagb/pokeagb.h>
#include "../generated/images/portaits/face001.h"
#include "../generated/images/portaits/face002.h"



u8* portraits_tiles[] = {
    (u8*)&face001Tiles, (u8*)&face002Tiles,
};

u8* portraits_pals[] = {
    (u8*)&face001Pal, (u8*)&face002Pal,
};


#endif /* PORTRAITS_H_*/