#include "PreferenceApp.h"

void PreferenceApp::setup(){
	ofSetVerticalSync(false);
	ofEnableSmoothing();
	ofSetFrameRate(60);
	ofBackground(0, 0, 0);
	ofSetEscapeQuitsApp(false);

	parameters.setName("parameters");
	parameters.add(radius.set("radius",50,1,100));
	parameters.add(color.set("color",100,ofColor(0,0),255));
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
	bar.draw();

	float vol  = audio->getVol().scale() * 100.0;
	float bass = audio->getBass().scale() * 100.0;
	float mid  = audio->getMid().scale() * 100.0;
	float high = audio->getHigh().scale() * 100.0;
	float hold = audio->getVol().getThreshold().hold;
	
	ofNoFill();

	ofPushStyle();
		ofPushMatrix();
		ofTranslate(2, 2, 0);
			
		ofSetColor(225);
		ofDrawBitmapString("Fps: " + ofToString((int)ofGetFrameRate()), 32, 20);
		ofDrawBitmapString("Average vol (0-100): " + ofToString(vol, 0), 32, 40);
		ofDrawBitmapString("Bass vol (0-100): " + ofToString(bass, 0), 32, 60);
		ofDrawBitmapString("Mid vol (0-100): " + ofToString(mid, 0), 32, 80);
		ofDrawBitmapString("High vol (0-100): " + ofToString(high, 0), 32, 100);
		ofDrawBitmapString("hold: " + ofToString(hold, 0), 32, 160);
		ofDrawBitmapString("Value: " + ofToString(midi->value, 0), 32, 120);
		ofDrawBitmapString("Control: " + ofToString(midi->control, 0), 32, 140);
		ofSetLineWidth(1);	
		ofDrawRectangle(0, 0, 400, 180);
		ofPopMatrix();
	ofPopStyle();
}

void PreferenceApp::keyPressed  (int key) { 
	if( key == OF_KEY_RETURN ) { 
		ofToggleFullscreen();
	}
}
