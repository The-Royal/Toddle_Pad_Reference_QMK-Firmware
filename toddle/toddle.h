#pragma once

#include "quantum.h"

#define LAYOUT_LEFTHAND( \
          K000, K001, K002, K003, K004,       \
          K100, K101, K102, K103, K104,       \
          K200, K201, K202, K203, K204,       \
    K300,    K301,    K302,    K303,    K304 \
) \
{ \
    { K000, K001, K002, K003, K004 }, \
    { K100, K101, K102, K103, K104 }, \
    { K200, K201, K202, K203, K204 }, \
    { K300, K301, K302, K303, K304 }  \
}
