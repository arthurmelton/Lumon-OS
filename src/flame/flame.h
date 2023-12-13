#include <linux/fb.h>
#include <stdint.h>

#ifndef FLAME
#define FLAME

struct flame {
	// Everything for internals
	struct fb_var_screeninfo info;
	uint32_t *screen;
	int horizontal_margin;
	int vertical_margin;
	float x_scale;
	float y_scale;

	// Public
	int width;
	int height;
};

struct flame flame_init();

void flame_clear(struct flame screen);

void flame_draw(struct flame screen, int x, int y, uint32_t color);

void flame_refresh();

#endif
