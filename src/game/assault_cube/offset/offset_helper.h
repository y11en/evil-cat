#ifndef EVIL_CAT_GAME_ASSAULT_CUBE_OFFSET_OFFSET_HELPER_H
#define EVIL_CAT_GAME_ASSAULT_CUBE_OFFSET_OFFSET_HELPER_H

#include <cstdint>
#include "game_ptr.h"

// dynamic define
#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

// offset
#define ADDRESS(t,c,m) ((gameptr_t)(&(((c*)t)->m)))

#endif //EVIL_CAT_GAME_ASSAULT_CUBE_OFFSET_OFFSET_HELPER_H
