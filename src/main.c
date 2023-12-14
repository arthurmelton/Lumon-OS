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
	flame_clear(screen);

	unsigned long long int frame = 0;

	enum state screen_state = BootText;

	struct timeval before, after, delta;

	int delta_time = 16666;

	while (1) {
		gettimeofday(&before, NULL);

		boot_text(screen, frame, &screen_state);

		boot_animation(screen, frame, &screen_state);

		flame_refresh();

		gettimeofday(&after, NULL);
		timersub(&after, &before, &delta);

		delta_time = delta.tv_usec;

		// printf("%d\n", delta_time);

		if (delta_time < 16666) {
			usleep(16666 - delta_time);
		}

		frame++;
	}

	sleep(999999999);
}
