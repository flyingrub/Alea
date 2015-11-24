#pragma once
#include "ofMain.h"

class Threshold {

	public:
		Threshold();
		void compare(float val);
		float beatAmount();
		bool isBeat();
		float getVal();
		float hold;
	private:
		float getMin();
		vector <float> history;
		bool firstTime;
		float threshold;
		
		bool beat;
		
};