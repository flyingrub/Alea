#pragma once
#include "SmoothValue.h"


class PointCircleInfo {

	public:
		PointCircleInfo(float size, float rotationSpeed, bool rotationDirection,
			int circleResolution);
		float getSize();
		float getSizeValue(float amount);
		bool getRotationDirection();
		int getCircleResolution();
		float getRotationSpeed();
		float addRotation(float amount);
		float addPadding(float amount);

	private:
		float rotation = 0.0f;
		float size;
		bool rotationDirection;
		int circleResolution;
		float rotationSpeed;
};