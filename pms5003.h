#pragma once 

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
	uint16_t length; 
	uint16_t pm1_0; 
	uint16_t pm2_5; 
	uint16_t pm10; 
} pms5003_s; 

bool pms5003_init(int fd);
bool pms5003_read(int fd, void *buffer, size_t num_of_bytes);
 
