#include <flame/flame.h>
#include <stdint.h>
#include <stdio.h>

void flame_raw(struct flame screen, int offset_x, int offset_y, uint32_t *image,
			   int width, int height) {
	uint32_t *offset = image;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			flame_draw(screen, x + offset_x, y + offset_y, *(++offset));
		}
	}
}
