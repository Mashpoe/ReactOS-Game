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
        FG_RED          = 0x04,
        FG_LIGHT_RED    = 0x0C,
        FG_PURPLE       = 0x05,
        FG_LIGHT_PURPLE = 0x0D,
        FG_YELLOW       = 0x06,
        FG_LIGHT_YELLOW = 0x0E,


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
        BG_RED          = 0x40,
        BG_LIGHT_RED    = 0xC0,
        BG_PURPLE       = 0x50,
        BG_LIGHT_PURPLE = 0xD0,
        BG_YELLOW       = 0x60,
        BG_LIGHT_YELLOW = 0xE0,
    };

}

#endif // COLOR_HPP_INCLUDED
