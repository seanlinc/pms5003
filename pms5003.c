#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include "pms5003.h"

bool pms5003_init(int fd) 
{
	bool pms5003_init_success = true;

	struct termios options;

	if (tcgetattr(fd, &options) < 0) {
		fprintf(stderr, "termios error\n");
	}

	cfsetospeed(&options, (speed_t) B9600);
	cfsetispeed(&options, (speed_t) B9600);

	options.c_cflag |= CLOCAL; // ignore modem status lines
	options.c_cflag |= CREAD; // enable receiver
	options.c_cflag |= CS8; // 8-bit data 
	options.c_cflag &= ~PARENB; // no parity bit
	options.c_cflag &= ~CSTOPB; // 1 stop bit

	options.c_iflag &=
		~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	
	options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	options.c_oflag &= ~OPOST;

	options.c_cc[VMIN] = 1;
	options.c_cc[VTIME] = 1;

	if (tcsetattr(fd, TCSANOW, &options) != 0) {
		fprintf(stderr, "fatal: tcsetattr\n");
		pms5003_init_success = false;
	}

	return pms5003_init_success;
}

bool pms5003_read(int fd, void *buffer, size_t num_of_bytes) 
{
	size_t num_read = 0;

	do {		
		ssize_t rdlen = read(fd, (char *)buffer + num_read, num_of_bytes - num_read);
		if (rdlen < 1) {
			fprintf(stderr, "too large");
		}
	
		num_read += rdlen;
	} while (num_read < num_of_bytes);
}


