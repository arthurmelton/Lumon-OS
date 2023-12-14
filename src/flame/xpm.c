#include <flame/flame.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void flame_xpm(struct flame screen, int offset_x, int offset_y, char *xpm[]) {
	int width = 0;
	int height = 0;
	int colors_count = 0;
	int chars_per_pixel = 0;

	int current_number = 0;
	for (int i = 0; xpm[0][i] != '\0'; i++) {
		uint8_t num = xpm[0][i] - 48;

		if (num < 10) {
			current_number *= 10;
			current_number += num;
		} else {
			if (!width) {
				width = current_number;
			} else if (!height) {
				height = current_number;
			} else if (!colors_count) {
				colors_count = current_number;
			} else if (!chars_per_pixel) {
				chars_per_pixel = current_number;
			}
			current_number = 0;
		}
	}

	char *index = malloc(colors_count * chars_per_pixel);
	if (!index) {
		printf("Failed to alloc space for indexes for xpm.\n");
		return;
	}

	uint32_t *colors = malloc(colors_count * 4);
	if (!colors) {
		printf("Failed to alloc space for colors for xpm.\n");
		return;
	}

	for (int i = 0; i < colors_count; i++) {
		memcpy(&index[i * chars_per_pixel], &xpm[i + 1][0], chars_per_pixel);
		colors[i] = strtol(&xpm[i + 1][chars_per_pixel + 4], NULL, 16);
	}

	char *current = malloc(chars_per_pixel);

	for (int y = 0; y < height; y++) {
		char *color_map = &xpm[colors_count + 1 + y][0];

		for (int x = 0; x < width; x++) {
			memcpy(current, color_map, chars_per_pixel);

			for (int i = 0; i < colors_count; i++) {
				if (memcmp(&index[i * chars_per_pixel], current,
						   chars_per_pixel) == 0) {
					flame_draw(screen, x + offset_x, y + offset_y, colors[i]);
					break;
				}
			}

			color_map += chars_per_pixel;
		}
	}

	free(index);
	free(current);
	free(colors);
}
