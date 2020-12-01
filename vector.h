#pragma once

typedef struct {
	float x;
	float y;
	float z;

} vector3_t;

void Mult(vector3_t* vector, float scaler);
void Add(vector3_t* vector, vector3_t* addVector);