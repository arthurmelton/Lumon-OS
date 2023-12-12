#include <assets/lumon_logo.xbm>
#include <flame/flame.h>
#include <flame/xbm.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct flame screen = flame_init();
    flame_clear_screen(screen);

    int x = 1;
    int y = 1;

    int offset_x = (screen.width-LUMON_LOGO_WIDTH)/2;
    int offset_y = 0;

    struct timeval before, after, delta;

    while(1) {
        gettimeofday(&before, NULL);

        flame_clear(screen);

        flame_xbm(screen, offset_x, offset_y, LUMON_LOGO, LUMON_LOGO_WIDTH, LUMON_LOGO_HEIGHT, 0x00FFFFFF, 0x00000000);

        flame_draw(screen);

        offset_x+=x;
        offset_y+=y;

        if (offset_x + LUMON_LOGO_WIDTH == screen.width || offset_x == 0) {
            x*=-1;
        }

        if (offset_y + LUMON_LOGO_HEIGHT == screen.height || offset_y == 0) {
            y*=-1;
        }

        gettimeofday(&after, NULL);
        timersub(&after, &before, &delta);

        sleep(0.1 - (float)delta.tv_usec/1000000);
    }


    //sleep(999999999);

	return 0;
}
