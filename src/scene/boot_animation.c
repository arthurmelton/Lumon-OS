#include <flame/flame.h>
#include <flame/xbm.h>
#include <scene/state.h>
#include <unistd.h>

#include <assets/LUMON_LOGO.xbm>

void boot_animation(struct flame screen, unsigned long long int frame,
					enum state *screen_state) {
	if (*screen_state == BootAnimation) {
		flame_clear(screen);

		flame_xbm(screen, (screen.width - LUMON_LOGO_WIDTH) / 2,
				  (screen.height - LUMON_LOGO_HEIGHT) / 2, LUMON_LOGO,
				  LUMON_LOGO_WIDTH, LUMON_LOGO_HEIGHT, 0x00FFFFFF, 0x00000000);

		sleep(5);  // there is where the animation would be

		*screen_state = Select;
	}
}
