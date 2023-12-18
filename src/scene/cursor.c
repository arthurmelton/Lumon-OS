#include <flame/flame.h>
#include <flame/input.h>
#include <flame/xbm.h>
#include <scene/cursor.h>
#include <scene/state.h>

#include <assets/_CURSOR.xbm>

void draw_cursor(struct flame screen, enum state *screen_state,
				 struct mice cursor) {
	flame_xbm(screen, cursor.x, cursor.y, _CURSOR, _CURSOR_WIDTH,
			  _CURSOR_HEIGHT, 0x00FFFFFF, 0x01000000);
}
