#ifndef CHESSEXCEPTION_H
#define CHESSEXCEPTION_H
#include <stdexcept>
struct ChessException : std::runtime_error {
    using std::runtime_error::runtime_error;
};
#endif
