#!/usr/bin/env python
import os

files = []
files = os.listdir('.' + "/../images/portraits/")

grit_args = "-gB 4 -pe16 -gu8 -pu8 -ftc\n"

portraits_headergaurd_top = ("#ifndef PORTRAITS_H_\n#define PORTRAITS_H_\n\n" +
                             "#include <pokeagb/pokeagb.h>\n")
portraits_includefiles = ""
portraits_tiles = "\n\nu8* portraits_tiles[] = {\n\t"
portraits_tile_contents = ""
portraits_pals = "\n\nu8* portraits_pals[] = {\n\t"
portraits_pals_contents = ""
portraits_headergaurd_bot = "\n\n#endif /* PORTRAITS_H_*/\n"

width = 0
for img in files:
    grit_loc = '../images/portraits/' + img.replace('.png', '.grit')
    with open(grit_loc, 'w+') as f:
        f.seek(0)
        f.write(grit_args)
        f.close()
    portraits_includefiles += ('#include "../generated/images/portraits/' + 
                               img.replace('.png', '.h') + '"\n')
    portraits_tile_contents += ("(u8*)&" + img.replace('.png', '') + "Tiles,")
    portraits_pals_contents += ("(u8*)&" + img.replace('.png', '') + "Pal,")
    if (width > 2):
        portraits_tile_contents += "\n\t"
        portraits_pals_contents += "\n\t"
        width = 0
    else:
        width += 1
        portraits_tile_contents += " "
        portraits_pals_contents += " "        

portraits_h =  (portraits_headergaurd_top + portraits_includefiles + 
                portraits_tiles + portraits_tile_contents + "\n};\n\n" + 
                portraits_pals + portraits_pals_contents + "\n};\n" + 
                portraits_headergaurd_bot)
    
with open('../src/portraits.h', 'w+') as f:
    f.seek(0)
    f.write(portraits_h)
        
        
