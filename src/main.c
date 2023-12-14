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

#if _DEBUG
	int peak = 0;
#endif

	while (1) {
		gettimeofday(&before, NULL);

		boot_text(screen, frame, &screen_state);

		boot_animation(screen, frame, &screen_state);

		flame_refresh();

		gettimeofday(&after, NULL);
		timersub(&after, &before, &delta);

		delta_time = delta.tv_usec;

#if _DEBUG
		if (delta_time > peak) {
			peak = delta_time;
		}
		printf("%d %d\n", delta_time, peak);
#endif

		if (delta_time < 16666) {
			usleep(16666 - delta_time);
		}

		frame++;
	}

	sleep(999999999);
}
