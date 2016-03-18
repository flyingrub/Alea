#include "PreferenceApp.h"

void PreferenceApp::setup(){
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofBackground(0, 0, 0);
	ofSetEscapeQuitsApp(false);

	parameters.setName("parameters");
	parameters.add(showFPS.set("showFPS", false));
	gui.setup(parameters);

}

void PreferenceApp::setup(Audio* a, Midi* m) {
	audio = a;
	midi = m;
	bar.setup(audio, midi);
}

void PreferenceApp::update(){

}

void PreferenceApp::draw(){
	gui.draw();

	float vol  = audio->getVol().scale() * 100.0;
	float bass = audio->getBass().scale() * 100.0;
	float mid  = audio->getMid().scale() * 100.0;
	float high = audio->getHigh().scale() * 100.0;
	float hold = audio->getVol().getThreshold().hold;

	ofNoFill();

	ofPushStyle();
		ofPushMatrix();
			ofTranslate(2, 2, 0);
			ofSetLineWidth(1);
			ofDrawBitmapString("Value: " + ofToString(midi->value, 0), 40, 40);
			ofDrawBitmapString("Control: " + ofToString(midi->control, 0), 40, 60);

			ofPushMatrix();
				ofDrawRectangle(0, 0, 400, 430);
				ofTranslate(40, 400, 0);
				bar.draw();
				ofSetLineWidth(1);
			ofPopMatrix();
		ofPopMatrix();
	ofPopStyle();
	bar.draw();
}

void PreferenceApp::keyPressed  (int key) {
	if( key == OF_KEY_RETURN ) {
		ofToggleFullscreen();
	}
}
