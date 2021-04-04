#include "pms5003.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	uint8_t ch;

	fd = open("/dev/serial0", O_RDWR | O_NOCTTY | O_SYNC);
	
	if (fd < 0) {
    	fprintf(stderr, "fd error\n");
    }
 
	if (pms5003_init(fd)) {
		puts("init sucess"); 
	}

	while (1) {
		
	pms5003_read(fd, &ch, 1); 	
	if (ch != 0x42) {
		fprintf(stderr, "pms5003 data error\n"); 
	}

	pms5003_read(fd, &ch, 1);
	if (ch != 0x4d) {		
	    fprintf(stderr, "pms5003 data error\n");
	}

	uint8_t dump[8]; 
	
	pms5003_read(fd, &dump, 8);

	uint16_t pm1 = 0;
	uint16_t pm2_5 = 0; 

	pms5003_read(fd, &ch, 1);
	pm1 = ch << 8; 
	pms5003_read(fd, &ch, 1);
	pm1 |= ch; 

	pms5003_read(fd, &ch, 1);
    pm2_5 = ch << 8;
    pms5003_read(fd, &ch, 1);
    pm2_5 |= ch;	


	printf("PM1.0: %d u g/m3\n", pm1);
	printf("PM2.5: %d u g/m3\n", pm2_5); 	

	uint8_t dump1[18]; 

    pms5003_read(fd, &dump1, 18);


//printf("recieved data from pms: 0x%x\n", ch);
	sleep(1);  
	}
	return 0; 
}

