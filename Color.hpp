#ifndef COLOR_HPP_INCLUDED
#define COLOR_HPP_INCLUDED

namespace Game {

    enum Color {
        FG_BLACK        = 0x00,
        FG_GRAY         = 0x08,
        FG_LIGHT_GRAY   = 0x07,
        FG_WHITE        = 0x0F,
        FG_BLUE         = 0x01,
        FG_LIGHT_BLUE   = 0x09,
        FG_GREEN        = 0x02,
        FG_LIGHT_GREEN  = 0x0A,
        FG_AQUA         = 0x03,
        FG_LIGHT_AQUA   = 0x0B,
        FG_RED          = 0x03,
        FG_PINK         = 0x0B,
        FG_PURPLE       = 0x03,
        FG_LIGHT_PURPLE = 0x0B,
        FG_YELLOW       = 0x03,
        FG_LIGHT_YELLOW = 0x0B,


        BG_BLACK        = 0x00,
        BG_GRAY         = 0x80,
        BG_LIGHT_GRAY   = 0x70,
        BG_WHITE        = 0xF0,
        BG_BLUE         = 0x10,
        BG_LIGHT_BLUE   = 0x90,
        BG_GREEN        = 0x20,
        BG_LIGHT_GREEN  = 0xA0,
        BG_AQUA         = 0x30,
        BG_LIGHT_AQUA   = 0xB0,
        BG_RED          = 0x30,
        BG_PINK         = 0xB0,
        BG_PURPLE       = 0x30,
        BG_LIGHT_PURPLE = 0xB0,
        BG_YELLOW       = 0x30,
        BG_LIGHT_YELLOW = 0xB0,
    };

}

#endif // COLOR_HPP_INCLUDED
