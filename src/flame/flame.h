#include <linux/fb.h>
#include <stdint.h>

#ifndef FLAME
#define FLAME

struct flame {
    // Everything for internals
	struct fb_var_screeninfo info;
    uint32_t *screen;

    // Public
    int width;
    int height;
    uint32_t *buf;
};

struct flame flame_init();

void flame_clear(struct flame screen);
void flame_clear_screen(struct flame screen);

void flame_draw(struct flame screen);

#endif
