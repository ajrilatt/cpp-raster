/*
Adam Rilatt
11 January 2022
C++ Rasterization Engine -- Screen Implementation
*/

#include "Screen.h"

using namespace std;

Screen::Screen(const string& name, int window_width, int window_height, int pixel_size)
: name(name), width(window_width), height(window_height), pixel_size(pixel_size) {

    console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    // The screen buffer needs to be the right size to create the screen, but
    // the screen needs to be the right size to create the buffer. See
    // javidx9's olcConsoleGameEngine for further detail.

    rect_window = { 0, 0, 1, 1 };
    SetConsoleWindowInfo(console_handle, true, &rect_window);

    COORD coord = { width, height };
    if (!SetConsoleScreenBufferSize(console_handle, coord))
    	throw invalid_argument("SetConsoleScreenBufferSize");

    if (!SetConsoleActiveScreenBuffer(console_handle))
    	throw invalid_argument("SetConsoleActiveScreenBuffer");

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = pixel_size;
    cfi.dwFontSize.Y = pixel_size;
    cfi.FontFamily = FF_DONTCARE;    // same
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas");

    if (!SetCurrentConsoleFontEx(console_handle, false, &cfi))
        throw invalid_argument("SetCurrentConsoleFontEx");

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(console_handle, &csbi))
        throw invalid_argument("GetConsoleScreenBufferInfo");
    if (height > csbi.dwMaximumWindowSize.Y)
        throw invalid_argument("Screen Height / Font Height Too Big");
    if (width > csbi.dwMaximumWindowSize.X)
        throw invalid_argument("Screen Width / Font Width Too Big");

    rect_window = { 0, 0, static_cast<short>(width - 1), static_cast<short>(height - 1) };
    if (!SetConsoleWindowInfo(console_handle, true, &rect_window))
    	throw invalid_argument("SetConsoleWindowInfo");

    SetConsoleTitleA(name.c_str());

    screen_buffer = new CHAR_INFO[width * height];
    memset(screen_buffer, 0, sizeof(CHAR_INFO) * width * height);
}

// Internal helper method.
pair<int, int> Screen::clip_coords(int x, int y) {

    if (x < 0) x = 0;
    if (x >= width) x = width - 1;
    if (y < 0) y = 0;
    if (y >= height) y = height - 1;

    return pair<int, int>(x, y);

}

void Screen::update() {

    WriteConsoleOutput(console_handle,
                       screen_buffer,
                       { width, height },
                       { 0, 0 },
                       &rect_window);

}

void Screen::set_pixel(int x, int y,
               ConsolePixel pixel, ConsoleColor pixel_color, ConsoleColor bg_color) {

    pair<int, int> xy = clip_coords(x, y);
    x = xy.first;
    y = xy.second;

    screen_buffer[y * width + x].Char.AsciiChar = pixel;
    screen_buffer[y * width + x].Attributes = pixel_color | bg_color;

}

// No guarantees whether the line will be drawn from p1 or from p2.
// Current implementation mostly lifted from the Bresenham's line rasterization
// algorithm Wikipedia: https://en.wikipedia.org/wiki/Bresenham's_line_algorithm.
void Screen::draw_line(int x1, int y1, int x2, int y2,
               ConsolePixel pixel, ConsoleColor pixel_color, ConsoleColor bg_color) {

    int dx = abs(x2 - x1);
    int sx = (x1 < x2) ? 1 : -1;
    int dy = -abs(y2 - y1);
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx + dy;  // error value e_xy

    while (true) {

        set_pixel(x1, y1, pixel, pixel_color, bg_color);

        // End of line reached.
        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 >= dy) { // e_xy+e_x > 0
             err += dy;
             x1 += sx;
        }

        if (e2 <= dx) {// e_xy+e_y < 0
              err += dx;
              y1 += sy;
        }

    }

}

void Screen::draw_tri(int x1, int y1, int x2, int y2, int x3, int y3,
                      ConsolePixel pixel, ConsoleColor pixel_color, ConsoleColor bg_color) {

    draw_line(x1, y1, x2, y2, pixel, pixel_color, bg_color);
    draw_line(x2, y2, x3, y3, pixel, pixel_color, bg_color);
    draw_line(x3, y3, x1, y1, pixel, pixel_color, bg_color);

}

void fill_rect(int x1, int y1, int x2, int y2,
               ConsolePixel pixel, ConsoleColor pixel_color, ConsoleColor bg_color) {

}

short Screen::get_width() { return width; }

short Screen::get_height() { return height; }
