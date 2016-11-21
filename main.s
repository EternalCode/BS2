        .gba
        .thumb
        .open "roms/BPRE0.gba","build/multi.gba", 0x08000000

        .include "patches/menutest.s"

        .org 0x08800000
        .importobj "build/linked.o"
        .close
