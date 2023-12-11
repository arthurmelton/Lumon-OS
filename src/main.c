#include <assert.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <lumon_logo.h>

int main(int argc, char *argv[]) {
    printf("\033[30m\033[8m\033c\033[999E\n");

	int fb = open("/dev/fb0", O_RDWR);
	if (!fb) {
		printf("Error opening frame buffer\n");
		return 1;
	}

	struct fb_var_screeninfo info = (struct fb_var_screeninfo){};
	if (ioctl(fb, FBIOGET_VSCREENINFO, &info)) {
		printf("Error with this stuff\n");
		return 1;
	}

	size_t len = 4 * info.xres * info.yres;
    int fb_width = info.xres;

	char *buf = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
	if (buf == MAP_FAILED) {
		printf("Map failed\n");
		return 1;
	}

    for (int y = 0; y < LUMON_LOGO_HEIGHT; y++) {
        for (int x = 0; x < LUMON_LOGO_WIDTH; x++) {
            int offset = (y * fb_width + x)*4;
            if (LUMON_LOGO[(y*LUMON_LOGO_WIDTH+x)/8] & (1<<((y*LUMON_LOGO_WIDTH+x)%8))) {
                buf[offset] = 255;
                buf[offset+1] = 255;
                buf[offset+2] = 255;
                buf[offset+3] = 0;
            }
            else {
                buf[offset] = 0;
                buf[offset+1] = 0;
                buf[offset+2] = 0;
                buf[offset+3] = 0;
            }
        }
        printf("\n");
    }

	sleep(999999999);

	return 0;
}
