#include <fcntl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <flame/flame.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

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

    uint32_t *frame = malloc(WIDTH*HEIGHT*sizeof(uint32_t));

    if (!frame) {
        printf("Failed to allocate for sceen.\n");
        exit(1);
    }
    return (struct flame){info, buf, WIDTH, HEIGHT, frame};
}

void flame_clear(struct flame screen) {
    memset(screen.buf, 0, WIDTH * HEIGHT * 4);
}

void flame_clear_screen(struct flame screen) {
    memset(screen.screen, 0, 4 * screen.info.xres * screen.info.yres);
}

void flame_draw(struct flame screen) {
    int border = screen.info.xres*3/4-screen.info.yres;

    int vertical_margin = 0;
    int horizontal_margin = 0;

    if (border > 0) {
        horizontal_margin = border/2;
    }
    else {
        vertical_margin = border*-1/2;
    }

    float y_scale = (float)(screen.info.yres-vertical_margin*2)/HEIGHT;
    float x_scale = (float)(screen.info.xres-horizontal_margin*2)/WIDTH;

    for (float y = 0; y < screen.info.yres-vertical_margin*2; y++) {
        for (float x = 0; x < screen.info.xres-horizontal_margin*2; x++) {
            int real_offset = (y + vertical_margin) * screen.info.xres + x + horizontal_margin;
            int virtual_offset = round(y/y_scale)*WIDTH+round(x/x_scale);

            screen.screen[real_offset] = screen.buf[virtual_offset];
        }
    }

    printf("\n"); // Release the buffer atleast when testing, not in OS
}
