#pragma once 
#include <stdint.h>
#include "vector.h"


typedef struct {
	vector3_t origin;
	vector3_t direction;
	vector3_t normal;
	vector3_t light;
	vector3_t view;
	vector3_t half;
	bool hit;
	uint32_t colour;
}
ray_t;