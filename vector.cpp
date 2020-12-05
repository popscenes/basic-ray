#include "vector.h"

vector3_t operator*(vector3_t vector, float scaler)
{
	vector3_t result = {
		vector.x * scaler,
		vector.y * scaler,
		vector.z * scaler,
	};

	return result;
}

vector3_t operator*(float scaler, vector3_t vector)
{
	return vector*scaler;
}

vector3_t operator+(vector3_t a, vector3_t b)
{
	vector3_t result = {
		a.x + b.x,
		a.y + b.y,
		a.z + b.z,
	};

	return result;
}

vector3_t operator-(vector3_t a, vector3_t b)
{
	vector3_t result = {
		a.x - b.x,
		a.y - b.y,
		a.z - b.z,
	};

	return result;
}

float dot(vector3_t a, vector3_t b)
{
	float result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);

	return result;
}

vector3_t cross(vector3_t a, vector3_t b)
{
	vector3_t result = {
	(a.y * b.z) - (a.z * b.y),
	(a.z * b.x) - (a.x * b.z),
	(a.x * b.y) - (a.y * b.x),
	};

	return result;
}