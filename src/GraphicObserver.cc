#include "GraphicObserver.h"
#include <png.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "UnrecoverableChessException.h"
#include <cstdio>
#include <filesystem>
#include <cassert>
#include <memory>
#include <vector>

constexpr inline int RGB(int r, int g, int b) {
    return b | g << 8 | r << 16;
}

constexpr int SQUARE_DIM = 60, WHITE_SQUARE = RGB(238, 238, 210), BLACK_SQUARE = RGB(118, 150, 86);

std::vector<png_bytep> GraphicsObserver::read_png_file(const char* file_name) {
    std::unique_ptr<FILE, decltype([](FILE* fp){ // RAII to interface with C-style API
        std::fclose(fp);
    })> fp{std::fopen(file_name, "rb")};
    if (!fp) throw UnrecoverableChessException{std::string{"File "} + file_name + " could not be opened for reading."};
    std::unique_ptr<png_struct, decltype([](png_structp p){
        if (p) png_destroy_read_struct(&p, nullptr, nullptr);
    })> png{png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL)};
    if (!png) throw UnrecoverableChessException{"png_create_read_struct failed."};
    std::unique_ptr<png_info, decltype([](png_infop p){
        if (p) png_destroy_info_struct(nullptr, &p);
    })> info{png_create_info_struct(png.get())};
    if (!info) throw UnrecoverableChessException{"png_create_info_struct failed."};
    if (setjmp(png_jmpbuf(png.get()))) throw UnrecoverableChessException{"setjmp failed."};
    png_init_io(png.get(), fp.get());
    png_read_info(png.get(), info.get());
    assert(png_get_image_width(png.get(), info.get()) == SQUARE_DIM && png_get_image_height(png.get(), info.get()) == SQUARE_DIM);
    png_byte color_type = png_get_color_type(png.get(), info.get());
    png_byte bit_depth = png_get_bit_depth(png.get(), info.get());
    if (bit_depth == 16)
        png_set_strip_16(png.get());
    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png.get());
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png.get());
    if (png_get_valid(png.get(), info.get(), PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png.get());
    if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png.get(), 0xFF, PNG_FILLER_AFTER);
    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png.get());
    png_read_update_info(png.get(), info.get());
    std::vector<png_bytep> rawRowPointers;
    rawRowPointers.reserve(SQUARE_DIM);
    for (int y = 0; y < SQUARE_DIM; y++) {
        rawRowPointers.push_back(new png_byte[png_get_rowbytes(png.get(), info.get())]);
        rowPointers.emplace_back(std::unique_ptr<png_byte>(rawRowPointers.back()));
    }
    png_read_image(png.get(), rawRowPointers.data());
    return rawRowPointers;
}

void GraphicsObserver::blendImageWithBackground(Pixmap pixmap, GC gc, png_bytep* rowPointers, int width, int height, int bgPixel) {
    XImage* ximage = XGetImage(display, pixmap, 0, 0, width, height, AllPlanes, ZPixmap);
    int bytes_per_pixel = 4, // RGBA
        bytes_per_line = width * bytes_per_pixel;
    for (int y = 0; y < height; y++) {
        png_bytep row = rowPointers[y];
        for (int x = 0; x < width; x++) {
            int offset = y * bytes_per_line + x * bytes_per_pixel;
            int alpha = row[x * 4 + 3];
            int src_r = row[x * 4];
            int src_g = row[x * 4 + 1];
            int src_b = row[x * 4 + 2];
            int dst_r = (bgPixel >> 16) & 0xFF;
            int dst_g = (bgPixel >> 8) & 0xFF;
            int dst_b = bgPixel & 0xFF;
            int blended_r = (alpha * src_r + (255 - alpha) * dst_r) / 255;
            int blended_g = (alpha * src_g + (255 - alpha) * dst_g) / 255;
            int blended_b = (alpha * src_b + (255 - alpha) * dst_b) / 255;
            unsigned long pixel = (blended_r << 16) | (blended_g << 8) | blended_b;
            XPutPixel(ximage, x, y, pixel);
        }
    }
    XPutImage(display, pixmap, gc, ximage, 0, 0, 0, 0, width, height);
    XDestroyImage(ximage);
}

void GraphicsObserver::fillRectangle(int x, int y, int width, int height, int color) {
    XSetForeground(display, gc, color);
    XFillRectangle(display, win, gc, x, y, width, height);
}

void GraphicsObserver::drawSquare(int x, int y, char symbol) {
    int bg = x + y & 1 ? BLACK_SQUARE : WHITE_SQUARE;
    fillRectangle(x * SQUARE_DIM, y * SQUARE_DIM, SQUARE_DIM, SQUARE_DIM, bg);
    if (symbol && symbol != ' ' && symbol != '_') {
        Pixmap pixmap = XCreatePixmap(display, win, SQUARE_DIM, SQUARE_DIM, vinfo.depth);
        blendImageWithBackground(pixmap, gc, pngIcons.at(std::string("icons/") + symbol + ".png").data(), SQUARE_DIM, SQUARE_DIM, bg);
        XCopyArea(display, pixmap, win, gc, 0, 0, SQUARE_DIM, SQUARE_DIM, x * SQUARE_DIM, y * SQUARE_DIM);
        XFreePixmap(display, pixmap);
    }
    XFlush(display);
    if (y == Board::SIZE - 1) {
        char file = x + 'a';
        XFlush(display);
        XDrawString(display, win, DefaultGC(display, screen), (x + 1) * SQUARE_DIM - 10, (y + 1) * SQUARE_DIM - 5, &file, 1);
    }
    if (x == 0) {
        char rank = Board::SIZE - y + '0';
        XFlush(display);
        XDrawString(display, win, DefaultGC(display, screen), 5, y * SQUARE_DIM + 15, &rank, 1);
    }
    XFlush(display);
}

GraphicsObserver::GraphicsObserver(Game* game) : Observer{game}, display{XOpenDisplay(NULL)} {
    if (!display) throw UnrecoverableChessException{"Unable to open X display."};
    screen = DefaultScreen(display);
    root = RootWindow(display, screen);
    if (!XMatchVisualInfo(display, screen, 24, TrueColor, &vinfo)) throw UnrecoverableChessException{"No matching visual found."};
    win = XCreateSimpleWindow(display, root, 0, 0, Board::SIZE * SQUARE_DIM, Board::SIZE * SQUARE_DIM, 1, BlackPixel(display, screen), BlackPixel(display, screen));
    XMapWindow(display, win);
    XStoreName(display, win, "Chess");
    gc = XCreateGC(display, win, 0, NULL);
    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize);
    hints.height = hints.base_height = hints.min_height = hints.max_height = Board::SIZE * SQUARE_DIM;
    hints.width = hints.base_width = hints.min_width = hints.max_width = Board::SIZE * SQUARE_DIM;
    XSetNormalHints(display, win, &hints);
    // XSynchronize(display, True);
    for (int y = 0; y < Board::SIZE; ++y)
        for (int x = 0; x < Board::SIZE; ++x)
            drawSquare(x, y, 0);
    for (const auto& dirEntry : std::filesystem::directory_iterator{"icons"})
        pngIcons.emplace(dirEntry.path(), read_png_file(dirEntry.path().c_str()));
    XFlush(display);
}

void GraphicsObserver::update() {
    for (int y = 0; y < Board::SIZE; ++y)
        for (int x = 0; x < Board::SIZE; ++x)
            drawSquare(x, y, game->getState(Position{x, Board::SIZE - 1 - y}));
}

GraphicsObserver::~GraphicsObserver() {
    XFreeGC(display, gc);
    XDestroyWindow(display, win);
    XCloseDisplay(display);
}
