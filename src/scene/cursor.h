#include <flame/flame.h>
#include <scene/state.h>
#include <flame/input.h>

#ifndef CURSOR
#define CURSOR

void draw_cursor(struct flame screen, enum state *screen_state, struct mice cursor);

#endif
