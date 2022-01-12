/*
Adam Rilatt
11 January 2022
C++ Rasterization Engine -- Console Draw Test
*/

/* Lots of this stuff was taken from javidx9's olcConsoleGameEngine. Thanks,
Jx9, you're a steely-eyed missile man. */

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>

using namespace std;

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
	BG_WHITE		= 0x00F0,
};

// we're going ASCII because Bill Gates hates me
enum ConsolePixel {
	SOLID         = static_cast<char>(219),
	THREEQUARTERS = static_cast<char>(178),
	HALF          = static_cast<char>(177),
	QUARTER       = static_cast<char>(176),
};

int main() {

    // seed rng for later
    srand(time(nullptr));

    // character dimensions of console
    short width = 160;
    short height = 80;

    // dimension of the character 'pixels'
    short font_width = 8;
    short font_height = 8;

    // presumably an output console handle passed to WriteConsoleOutput
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    // bit of difficulty here... the screen buffer needs to be the right size
    // to create the screen, but the screen needs to be the right size to create
    // the buffer.

    // change console visual size to a minimum so screen buffer can shrink
	// below the actual visual size
    SMALL_RECT rect_window = { 0, 0, 1, 1 };
    SetConsoleWindowInfo(console_handle, true, &rect_window);

    // set the size of the screen buffer
	COORD coord = { width, height };
	if (!SetConsoleScreenBufferSize(console_handle, coord))
		throw invalid_argument("SetConsoleScreenBufferSize error");

	// assign screen buffer to the console
	if (!SetConsoleActiveScreenBuffer(console_handle))
		throw invalid_argument("SetConsoleActiveScreenBuffer");

    // set the font size now that the screen buffer has been assigned to the console
    CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = font_width;
	cfi.dwFontSize.Y = font_height;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;

    wcscpy(cfi.FaceName, L"Consolas");
	if (!SetCurrentConsoleFontEx(console_handle, false, &cfi))
		throw invalid_argument("SetCurrentConsoleFontEx");

	// get screen buffer info and check the maximum allowed window size. Return
	// error if exceeded, so user knows their dimensions/fontsize are too large
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(console_handle, &csbi))
		throw invalid_argument("GetConsoleScreenBufferInfo");
	if (height > csbi.dwMaximumWindowSize.Y)
		throw invalid_argument("Screen Height / Font Height Too Big");
	if (width > csbi.dwMaximumWindowSize.X)
		throw invalid_argument("Screen Width / Font Width Too Big");

	// Set physical console window size
	rect_window = { 0, 0, static_cast<short>(width - 1), static_cast<short>(height - 1) };
	if (!SetConsoleWindowInfo(console_handle, true, &rect_window))
		throw invalid_argument("SetConsoleWindowInfo");

    // the console window is presumably set up by this point.

    // update console title
    SetConsoleTitleA("Test Console");

    // screen buffer (no double buffer or anything silly yet)
    CHAR_INFO screen_buffer[width * height];
    memset(screen_buffer, 0, sizeof(CHAR_INFO) * width * height);

    ConsolePixel pixel_types[4] = { ConsolePixel::SOLID,
                                    ConsolePixel::THREEQUARTERS,
                                    ConsolePixel::HALF,
                                    ConsolePixel::QUARTER };
    int c = 0;
    while (true) {

        int x = rand() % width;
        int y = rand() % height;

		screen_buffer[y * width + x].Char.AsciiChar = pixel_types[rand() % 4];
		screen_buffer[y * width + x].Attributes = ConsoleColor::FG_DARK_YELLOW | ConsoleColor::BG_BLACK;

        // write to console
        if (!(c % 128))
        WriteConsoleOutput(console_handle,
                           screen_buffer,
                           { width, height },
                           { 0, 0 },
                           &rect_window);
        ++c;

    }

    return 0;

}
