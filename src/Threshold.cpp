#include "Threshold.h"

Threshold::Threshold() {
	threshold = 0;
	firstTime = true;
	history.assign(HISTORY_SIZE, 0.0);
	hold = 0;
}

void Threshold::compare(float val) {
	if (firstTime) {
		firstTime = false;
		threshold = val;
	}
	beat = false;
	history.push_back(val);
	
	if(history.size() >= HISTORY_SIZE){
		history.erase(history.begin(), history.begin()+1);
	}

	if (threshold < val) {
		if (hold == 0) {
			beat = true;
			hold = HOLD_VALUE;
		}
		threshold = val;
	} else {
		if (hold > 0) {
			hold--;
		} else {
			if (threshold > THRESHOLD_DIM_VLAUE) {
				threshold -= THRESHOLD_DIM_VLAUE;
			}
		}
	}
}

float Threshold::getMin() {
	float min = history[0];
	for( int i = 1; i < history.size(); i++){
  		if (history[i] < min) {
  			min = history[i];
  		}
	}
	return min;
}

float Threshold::beatAmount() {
	return threshold - getMin();
}

bool Threshold::isBeat() {
	return beat;
}

float Threshold::getVal() {
	return threshold;
}