#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H
#include "Observer.h"
#include "Game.h"
#include "Board.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <png.h>
#include <map>
#include <string>
#include <vector>
#include <memory>
struct GraphicsObserver : Observer {
    void update() override;
    GraphicsObserver(Game* game);
    ~GraphicsObserver();

private:
    Display* display;
    int screen;
    Window win;
    XVisualInfo vinfo;
    GC gc{}, textGC{};
    XFontStruct* font{};
    std::map<std::string, std::vector<png_bytep>> pngIcons;
    std::vector<std::unique_ptr<png_byte[]>> rowPointers;
    std::array<std::array<Board::SquareState, Board::SIZE>, Board::SIZE> prevGrid;

    void fillRectangle(int x, int y, int width, int height, int color);
    void drawSquare(int x, int y, Board::SquareState piece);
    void blendImageWithBackground(Pixmap pixmap, GC gc, png_bytep* rowPointers, int width, int height, int bgPixel);
    std::vector<png_bytep> readPngFile(const char* file_name);
};
#endif
