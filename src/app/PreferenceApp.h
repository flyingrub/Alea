#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Audio.h"
#include "Midi.h"
#include "ofBar.h"

class PreferenceApp: public ofBaseApp {
public:
	void setup();
	void setup(Audio* a, Midi* m);
	void update();
	void draw();

	void keyPressed(int key);


	ofParameterGroup parameters;
	ofParameter<float> radius;
	ofParameter<ofColor> color;
	ofxPanel gui;

	Audio* audio;
	Midi* midi;

	ofBar bar;
};

