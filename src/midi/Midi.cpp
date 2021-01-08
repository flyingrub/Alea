#include "Midi.h"

//--------------------------------------------------------------
Midi::Midi() {


}

void Midi::setup(int port) {
	// print input ports to console
	midiIn.listInPorts(); // via instance
	//ofxMidiIn::listPorts(); // via static as well

	// open port by number (you may need to change this)
	midiIn.openPort(port);
	//midiIn.openPort("IAC Pure Data In");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port

	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);

	// add Midi as a listener
	midiIn.addListener(this);

	// print received messages to the console
	midiIn.setVerbose(true);
}

//--------------------------------------------------------------
void Midi::exit() {
	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}

//--------------------------------------------------------------
void Midi::newMidiMessage(ofxMidiMessage& msg) {
	// make a copy of the latest message
	value = msg.value;
	control = msg.control;
	controller.update(control, value);
}