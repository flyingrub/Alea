#pragma once
#include "ofMain.h"
#include "Threshold.h"

class SmoothValue {

	public:
		SmoothValue();
		void update(float val);
		float getVal();
		float scale();
		void setRange(float rmin, float rmax);
		Threshold getThreshold();
	private:
		float value;
		float min;
		float max;
		Threshold threshold;


};