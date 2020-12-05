#pragma once 

#include "vector.h"
typedef struct {
	vector3_t origin;
	vector3_t direction;
	bool hit;
}
ray_t;