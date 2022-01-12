/*
Adam Rilatt
11 January 2022
C++ Rasterization Engine -- Screen Class Test
*/

#include "Screen.h"
#include <time.h>
#include <stdlib.h>

using namespace std;

int main() {

    srand(time(nullptr));

    short width = 160;
    short height = 120;
    short pixel_size = 6;

    Screen screen { "Worms", width, height, pixel_size };

    ConsolePixel pixel_types[5] = { ConsolePixel::SOLID,
                                    ConsolePixel::THREEQUARTERS,
                                    ConsolePixel::HALF,
                                    ConsolePixel::QUARTER,
                                    ConsolePixel::BLANK };

    ConsoleColor color_palette[15] = { ConsoleColor::FG_DARK_BLUE,
                                       ConsoleColor::FG_DARK_GREEN,
                                       ConsoleColor::FG_DARK_CYAN,
                                       ConsoleColor::FG_DARK_RED,
                                       ConsoleColor::FG_DARK_MAGENTA,
                                       ConsoleColor::FG_DARK_YELLOW,
                                       ConsoleColor::FG_GREY,
                                       ConsoleColor::FG_DARK_GREY,
                                       ConsoleColor::FG_BLUE,
                                       ConsoleColor::FG_GREEN,
                                       ConsoleColor::FG_CYAN,
                                       ConsoleColor::FG_RED,
                                       ConsoleColor::FG_MAGENTA,
                                       ConsoleColor::FG_YELLOW,
                                       ConsoleColor::FG_WHITE };

    int c = 0;

    while (true) {

        int x1 = rand() % screen.get_width();
        int y1 = rand() % screen.get_height();
        int x2 = rand() % screen.get_width();
        int y2 = rand() % screen.get_height();
        int x3 = rand() % screen.get_width();
        int y3 = rand() % screen.get_height();

        screen.draw_tri(x1, y1, x2, y2, x3, y3, pixel_types[rand() % 5],
                         color_palette[rand() % 15], ConsoleColor::BG_BLACK);

        //screen.set_pixel(x, y, pixel_types[rand() % 5], ConsoleColor::FG_DARK_RED, ConsoleColor::BG_BLACK);

        ++c;
        //if (!(c % 2))
            screen.update();

    }

}
