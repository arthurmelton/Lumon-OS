#include <assets/IBM_VGA_8x16.h>
#include <flame/flame.h>
#include <flame/xbm.h>
#include <scene/state.h>

static char startup_print[] =
	"LUMON OS\n"
	"ParseElements: keyboard: 0 digitizer: 12 pointer: 0 0 scroll: 0 led: 0\n"
	"GPU Initialized: Control ID 16\n"
	"startupTask\n"
	"Video has output streams: 1\n"
	"Reuse output buffer index:2 dev:Code Output offset: 1840000 size:20800\n"
	"Audio has output streams: 1\n"
	"DisableInput = 0\n"
	"portType = 3\n"
	"skipCached = 0\n"
	"PortType:3, Length: 128";

int offset_x = 32;
int offset_y = 32;

void boot_text(struct flame screen, unsigned long long int frame,
			   enum state *screen_state) {
	if (*screen_state == BootText) {
		if (frame == sizeof(startup_print) / sizeof(*startup_print)) {
			*screen_state = BootAnimation;
			return;
		}
		if (startup_print[frame] == '\n') {
			offset_y += 20;
			offset_x = 32;
		} else {
			flame_xbm(screen, offset_x, offset_y,
					  IBM_VGA_8x16 + startup_print[frame] * 16, 8, 16,
					  0x00FFFFFF, 0x00000000);
			offset_x += 9;
		}
	}
}
