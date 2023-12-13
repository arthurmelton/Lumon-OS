#include <flame/flame.h>
#include <flame/xbm.h>
#include <scene/boot_animation.h>
#include <scene/boot_text.h>
#include <scene/state.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	struct flame screen = flame_init();
	flame_clear_screen(screen);

	unsigned long long int frame = 0;

	enum state screen_state = BootText;

	struct timeval before, after, delta;

	while (1) {
		gettimeofday(&before, NULL);

		boot_text(screen, frame, &screen_state);

		boot_animation(screen, frame, &screen_state);

		flame_draw(screen);

		gettimeofday(&after, NULL);
		timersub(&after, &before, &delta);

		usleep(16666 - delta.tv_usec);
		frame++;
	}

	sleep(999999999);
}
