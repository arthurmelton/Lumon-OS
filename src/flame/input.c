#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <flame/flame.h>
#include <flame/input.h>
#include <stdlib.h>

char mice_data[3];
int mice_fd;
int mice_x = WIDTH/2;
int mice_y = HEIGHT/2;

void input_init() {
    mice_fd = open("/dev/input/mice", O_RDWR | O_NONBLOCK);
    if(!mice_fd) {
        printf("Error opening mice.\n");
        exit(1);
    }
}

struct mice get_mice() {
    int bytes = read(mice_fd, mice_data, sizeof(mice_data));

    int left = 0;
    int right = 0;
    int middle = 0;

    if(bytes > 0) {
        mice_x += mice_data[1]*1.5;
        mice_y -= mice_data[2]*1.5;

        if (mice_x < 0) {
            mice_x = 0;
        }
        else if (mice_x > WIDTH-1) {
            mice_x = WIDTH-1;
        }

        if (mice_y < 0) {
            mice_y = 0;
        }
        else if (mice_y > HEIGHT-1) {
            mice_y = HEIGHT-1;
        }

        left = mice_data[0] & 0x1;
        right = mice_data[0] & 0x2;
        middle = mice_data[0] & 0x4;
    }

    return (struct mice){mice_x, mice_y, left, right, middle};
}
