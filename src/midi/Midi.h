#pragma once
#include "ofxMidi.h"
#include "ofMain.h"
#include "TinyControl.h"

class Midi : public ofxMidiListener {

public:
	Midi();
	void setup(int port);
	void exit();

	void newMidiMessage(ofxMidiMessage& eventArgs);

	int value;
	int control;
	TinyControl controller;

	ofxMidiIn midiIn;

private:

};
