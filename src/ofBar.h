#pragma once
#include "ofMain.h"
#include "Audio.h"
#include "Midi.h"

class ofBar {

	public:
		ofBar();
		void setup(Audio* a, Midi* m);
		void update();
		void draw(); 
	private:
		Audio* audio;
		Midi* midi;

		int const BEAT = 25 - 5;
		
};