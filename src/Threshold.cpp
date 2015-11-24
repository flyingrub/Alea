#include "Threshold.h"

Threshold::Threshold() {
	threshold = 0;
	firstTime = true;
	history.assign(20, 0.0);
	hold = 0;
}

void Threshold::compare(float val) {
	if (firstTime) {
		firstTime = false;
		threshold = val;
	}
	beat = false;
	history.push_back(val);
	
	if( history.size() >= 20 ){
		history.erase(history.begin(), history.begin()+1);
	}

	if (threshold < val) {
		threshold = val;
		hold = 60;
		if (hold == 0) {
			beat = true;
		}
	} else {
		if (hold > 0) {
			hold--;
		} else {
			if (threshold > 0) {
				threshold -= 0.01;
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