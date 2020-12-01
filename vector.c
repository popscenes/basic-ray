#include "vector.h"

void Mult(vector3_t *vector, float scaler)
{
	vector->x *= scaler;
	vector->y *= scaler;
	vector->z *= scaler;
}

void Add(vector3_t* vector, vector3_t *addVector)
{
	vector->x += addVector->x;
	vector->y += addVector->y;
	vector->z += addVector->z;
}