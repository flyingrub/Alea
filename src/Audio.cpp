#include "Audio.h"

Audio::Audio() {
	left.assign(BUFFER_SIZE, 0.0);
	right.assign(BUFFER_SIZE, 0.0);
	volHistory.assign(912, 0.0);

	data = new float[BUFFER_SIZE];

	for (int i = 0; i < NUM_WINDOWS; i++) {
		for (int j = 0; j < BUFFER_SIZE/2; j++) {
			freq[i][j] = 0;
		}
	}
}

void Audio::update(float * input, int bufferSize) {
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;	

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
		data[i]		= left[i] + right[i];

		curVol += left[i] * left[i];
		curVol += right[i] * right[i];

		numCounted+=2;
	}
	curVol /= (float)numCounted;
	curVol = sqrt( curVol );
	volume.update(curVol);
	bass.update(magnitude[1]);
}


void Audio::calc() {
	float avg_power = 0.0f;
	myfft.powerSpectrum(0,(int)BUFFER_SIZE/2, data,BUFFER_SIZE,&magnitude[0],&phase[0],&power[0],&avg_power);
	
	//lets record the volume into an array
	volHistory.push_back(getVol());
	
	//if we are bigger the the size we want to record - lets drop the oldest value
	if( volHistory.size() >= 912 ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}
}

float Audio::getBass() {
	return bass.scale(0.0, 10, 0.0, 100);
}

float Audio::getVol() {
	return volume.scale(0.0, 0.17, 0.0, 1.0);
}