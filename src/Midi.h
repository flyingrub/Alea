#pragma once
#include "ofxMidi.h"
#include "ofMain.h"

class Midi : public ofxMidiListener {

public:
	Midi();
	void setup();
	void exit();
	
	void newMidiMessage(ofxMidiMessage& eventArgs);
	
	int value;
	int control;
	
	ofxMidiIn midiIn;
};
