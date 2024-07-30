#ifndef UNRECOVERABLECHESSEXCEPTION_H
#define UNRECOVERABLECHESSEXCEPTION_H
#include <stdexcept>
struct UnrecoverableChessException : std::runtime_error {
    using std::runtime_error::runtime_error;
};
#endif
