#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <time.h>
#include <linux/input.h>

static volatile sig_atomic_t quit = 0;

static void sig_handler(int _)
{
	quit = 1;
}

int write_to_cfg_file() {

	char bw_mode[1] = {0x00};
	int fd;

	fd = open("/blackbox/glass_user_setting.dat", O_RDWR);

	if (fd < 0){
		printf("Open glass_user_setting.dat error\n");
		exit(1);
	}

	pwrite(fd, bw_mode, 1, 0xc0);
	close(fd);
	
	return 1;
}


int main(){

	signal(SIGINT, sig_handler);
	struct timespec button_start, now;
	struct pollfd poll_fd;
	struct input_event ev;
	int event_fd = open("/dev/input/event0", O_RDONLY);
	memset(&button_start, 0, sizeof(button_start));
	
	while(!quit){
		clock_gettime(CLOCK_MONOTONIC, &now);

		if(button_start.tv_sec > 0 && ((now.tv_sec - button_start.tv_sec) > 6)) {
			// We held the back button channel down for 7 seconds.
			memset(&button_start, 0, sizeof(button_start));
			system("setprop dji.glasses_service 0");
			write_to_cfg_file();
			system("setprop dji.glasses_service 1");
			system("/system/bin/modem_info.sh reboot");
		}

		poll_fd.fd = event_fd;
		poll_fd.events = POLLIN;
		poll(&poll_fd, 1, 100);

		if(poll_fd.revents) {
			read(event_fd, &ev, sizeof(struct input_event));
			if(ev.code == 0xcc) {  //button channel down
				if(ev.value == 1) {
					clock_gettime(CLOCK_MONOTONIC, &button_start);
				} else {
					memset(&button_start, 0, sizeof(button_start));
				}
			}
			// printf("input type: %i, code: %i, value: %i\n", ev.type, ev.code, ev.value);
		}
	}
	close(event_fd);

	return 0;
}
