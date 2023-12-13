#include <fcntl.h>
#include <flame/flame.h>
#include <linux/fb.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#define WIDTH 1024
#define HEIGHT 768

struct flame flame_init() {
	int fb = open("/dev/fb0", O_RDWR);
	if (!fb) {
		printf("Error opening frame buffer\n");
		exit(1);
	}

	struct fb_var_screeninfo info = (struct fb_var_screeninfo){};
	if (ioctl(fb, FBIOGET_VSCREENINFO, &info)) {
		printf("Error getting screen info\n");
		exit(1);
	}

	size_t len = 4 * info.xres * info.yres;

	uint32_t *buf = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
	if (buf == MAP_FAILED) {
		printf("Map failed\n");
		exit(1);
	}

	int border = info.xres * 3 / 4 - info.yres;

	int horizontal_margin = 0;
	int vertical_margin = 0;

	if (border > 0) {
		horizontal_margin = border / 2;
	} else {
		vertical_margin = border * -1 / 2;
	}

	float y_scale = (float)(info.yres - vertical_margin * 2) / HEIGHT;
	float x_scale = (float)(info.xres - horizontal_margin * 2) / WIDTH;

	return (struct flame){
		info,  buf,	  horizontal_margin, vertical_margin, x_scale, y_scale,
		WIDTH, HEIGHT};
}

void flame_clear(struct flame screen) {
	memset(screen.screen, 0, 4 * screen.info.xres * screen.info.yres);
}

void flame_draw(struct flame screen, int x, int y, uint32_t color) {
	if (color != 1) {
		float y_float = screen.y_scale * y;
		float x_float = screen.x_scale * x;

		int real_offset =
			((int)y_float + screen.vertical_margin) * screen.info.xres +
			(int)x_float + screen.horizontal_margin;

		for (int i = 0; i < ceil(screen.y_scale); i++) {
			for (int x = 0; x < ceil(screen.x_scale); x++) {
				*(screen.screen + real_offset + x) = color;
			}
			real_offset += screen.info.xres;
		}
	}
}

void flame_refresh() {
	printf("\n");  // Release the buffer atleast when testing, not in OS
}
