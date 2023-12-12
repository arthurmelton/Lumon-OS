#include <stdint.h>
#include <flame/flame.h>
#include <stdio.h>

void flame_xbm(struct flame frame, int offset_x, int offset_y, char *image, int width, int height, uint32_t foreground, uint32_t background) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int offset = (y+offset_y) * frame.width + (x+offset_x);
            if (image[(y*width+x)/8] & (1<<((y*width+x)%8))) {
                frame.buf[offset] = foreground;
            }
            else if (background != 1) {
                frame.buf[offset] = background;
            }
        }
    }
}
