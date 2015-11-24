#pragma once
#include "ofMain.h"

class SmoothValue {

	public:
		SmoothValue();
		void setup(float val);
		void update(float val);
		float getVal();
		float getMin();
		float getMax();
		float scale();
		void setRange(float rmin, float rmax);
		float testMin;
		float testMax;
	private:
		float value;
		float min;
		float max;

	
};