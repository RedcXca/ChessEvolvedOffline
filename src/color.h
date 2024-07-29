#ifndef COLOR_H
#define COLOR_H
enum class Color {
    White,
    Black
};
Color getNextColor(Color color) {
    return Color(int(color) ^ 1);
}
#endif
