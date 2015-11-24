#pragma once
#include "ofMain.h"

class SmoothValue {

	public:
		SmoothValue();
		void setup(float val);
		void update(float val);
		float getVal();
		float scale(float oldMin, float oldMax, float newMin, float newMax);
	private:
		float value;
	
};