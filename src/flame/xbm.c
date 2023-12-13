#include <flame/flame.h>
#include <stdint.h>
#include <stdio.h>

void flame_xbm(struct flame screen, int offset_x, int offset_y, char *image,
			   int width, int height, uint32_t foreground,
			   uint32_t background) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (y > 0 && y < screen.height && x > 0 && x < screen.width) {
				if (image[(y * width + x) / 8] & (1 << ((y * width + x) % 8))) {
					flame_draw(screen, x + offset_x, y + offset_y, foreground);
				} else {
					flame_draw(screen, x + offset_x, y + offset_y, background);
				}
			}
		}
	}
}
