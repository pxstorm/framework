#pragma once

#include <cstdio>
#include <cassert>

// FIXME: Only in debug mode
#define EXPECT(e, msg, ...) if(!(e)) { fprintf(stderr, msg, ##__VA_ARGS__); assert(e); }
#define UNEXPECTED(msg, ...) { fprintf(stderr, msg, ##__VA_ARGS__); assert(false); }