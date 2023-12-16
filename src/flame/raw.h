#include <stdint.h>

#ifndef RAW
#define RAW

void flame_raw(struct flame item, int offset_x, int offset_y, uint32_t *image,
			   int width, int height);

#endif
