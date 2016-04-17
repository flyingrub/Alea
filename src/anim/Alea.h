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
		void drawOne(float size, ofColor color, SmoothValue value);

	private:
		bool shouldDraw();
		Audio* audio;
		Midi* midi;
		int counter = 60;
		float rotation = 0.0f;
};
