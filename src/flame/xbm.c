#include <flame/flame.h>
#include <stdint.h>
#include <stdio.h>

void flame_xbm(struct flame screen, int offset_x, int offset_y, char *image,
			   int width, int height, uint32_t foreground,
			   uint32_t background) {
	char *offset = image;
	char index = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (index == 8) {
				offset++;
				index = 0;
			}
			index++;

			if (*offset & (1 << (index))) {
				flame_draw(screen, x + offset_x, y + offset_y, foreground);
			} else {
				flame_draw(screen, x + offset_x, y + offset_y, background);
			}
		}
	}
}
