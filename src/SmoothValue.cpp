#include "SmoothValue.h"

SmoothValue::SmoothValue() {
	value = 0;
}

void SmoothValue::setup(float val) {
	value = val;
}

void SmoothValue::update(float val) {
	value *= 0.93;
	value += 0.07 * val;
}

float SmoothValue::scale(float oldMin, float oldMax, float newMin, float newMax) {
	return ofMap(value, oldMin, oldMax, newMin, newMax, true);
}