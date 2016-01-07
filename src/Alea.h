#pragma once
#include "ofMain.h"
#include "Audio.h"
#include "Midi.h"

class Alea {

	public:
		Alea();
		void setup(Audio* a, Midi* m);
        void update();
        void draw(); 
	private:
		bool shouldDraw();
		Audio* audio;
		Midi* midi;
		int counter = 60;
		int rotation = 0;
};