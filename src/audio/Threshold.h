#pragma once
#include "ofMain.h"

class Threshold {

	public:
		unsigned const HOLD_VALUE = 30;
		float const THRESHOLD_DIM_VLAUE = 0.01;
		unsigned const HISTORY_SIZE = 20;

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