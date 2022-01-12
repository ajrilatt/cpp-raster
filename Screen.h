/*
Adam Rilatt
11 January 2022
C++ Raster Engine -- Screen Class
*/

#ifndef SCREEN_H
#define SCREEN_H

#include <windows.h>
#include <string>   // window name
#include <utility>  // (x, y) pairs
#include <stdexcept> // sizing errors

// Borrowed from javidx9's olcConsoleGameEngine. Thanks javid!
enum ConsoleColor {
	FG_BLACK		= 0x0000,
	FG_DARK_BLUE    = 0x0001,
	FG_DARK_GREEN   = 0x0002,
	FG_DARK_CYAN    = 0x0003,
	FG_DARK_RED     = 0x0004,
	FG_DARK_MAGENTA = 0x0005,
	FG_DARK_YELLOW  = 0x0006,
	FG_GREY			= 0x0007,
	FG_DARK_GREY    = 0x0008,
	FG_BLUE			= 0x0009,
	FG_GREEN		= 0x000A,
	FG_CYAN			= 0x000B,
	FG_RED			= 0x000C,
	FG_MAGENTA		= 0x000D,
	FG_YELLOW		= 0x000E,
	FG_WHITE		= 0x000F,
	BG_BLACK		= 0x0000,
	BG_DARK_BLUE	= 0x0010,
	BG_DARK_GREEN	= 0x0020,
	BG_DARK_CYAN	= 0x0030,
	BG_DARK_RED		= 0x0040,
	BG_DARK_MAGENTA = 0x0050,
	BG_DARK_YELLOW	= 0x0060,
	BG_GREY			= 0x0070,
	BG_DARK_GREY	= 0x0080,
	BG_BLUE			= 0x0090,
	BG_GREEN		= 0x00A0,
	BG_CYAN			= 0x00B0,
	BG_RED			= 0x00C0,
	BG_MAGENTA		= 0x00D0,
	BG_YELLOW		= 0x00E0,
	BG_WHITE		= 0x00F0
};

// ASCII, not Unicode, so char is adequate
enum ConsolePixel {
	SOLID         = static_cast<char>(219),
	THREEQUARTERS = static_cast<char>(178),
	HALF          = static_cast<char>(177),
	QUARTER       = static_cast<char>(176),
    BLANK         = static_cast<char>(32)
};

class Screen {
public:

    // Constructor.
    Screen(const std::string& name,
           int window_width,
           int window_height,
           int pixel_size);

    // Destructor.
    ~Screen();

	// Returns the width of the console.
	short get_width();

	// Returns the height of the console.
	short get_height();

    // Displays the most recent version of the screen buffer.
    void update();

    // Edits the pixel at the corresponding x, y location.
    void set_pixel(int x, int y,
                   ConsolePixel pixel, ConsoleColor pixel_color, ConsoleColor bg_color);

    void draw_line(int x1, int y1, int x2, int y2,
                   ConsolePixel pixel, ConsoleColor pixel_color, ConsoleColor bg_color);

    void draw_tri(int x1, int y1, int x2, int y2, int x3, int y3,
                  ConsolePixel pixel, ConsoleColor pixel_color, ConsoleColor bg_color);

    void fill_rect(int x1, int y1, int x2, int y2,
                   ConsolePixel pixel, ConsoleColor pixel_color, ConsoleColor bg_color);

private:

    std::string name { "" };
    short width  { 0 };
    short height { 0 };
    short pixel_size { 0 };
    CHAR_INFO* screen_buffer;
	HANDLE console_handle;
	SMALL_RECT rect_window;

    // Helper function used to clip coordinates.
    std::pair<int, int> clip_coords(int x, int y);


};

#endif
