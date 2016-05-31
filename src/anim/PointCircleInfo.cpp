#include "PointCircleInfo.h"

PointCircleInfo::PointCircleInfo(float p_size, float p_rotationSpeed, bool p_rotationDirection,
			int p_circleResolution) {
	size = p_size;
	rotationSpeed = p_rotationSpeed;
	rotationDirection = p_rotationDirection;
	circleResolution = p_circleResolution;
}

float PointCircleInfo::getSize() {
	return size;
}

float PointCircleInfo::getSizeValue(float amount) {
	return amount * 50;
}

int PointCircleInfo::getCircleResolution() {
	return circleResolution;
}

float PointCircleInfo::getRotationSpeed() {
	return rotationSpeed;
}

float PointCircleInfo::addRotation(float amount) {
	rotation += rotationSpeed + amount * 1.2;
	if (rotation >= 360) {
		rotation -= 360;
	}
	return rotationDirection ? -rotation : rotation;
}

float PointCircleInfo::addPadding(float amount) {
	rotation += rotationSpeed + amount * 5;
	if (rotation >= size) {
		rotation -= size;
	}
	return rotationDirection ? -rotation : rotation;
}