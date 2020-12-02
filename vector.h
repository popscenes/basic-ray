#pragma once

typedef struct {
	float x;
	float y;
	float z;

} vector3_t;

vector3_t operator*(vector3_t vector, float scaler);
vector3_t operator*(float scaler, vector3_t vector);
vector3_t operator+(vector3_t a, vector3_t b);