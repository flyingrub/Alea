#include "Alea.h"

Alea::Alea() {
	ofSetCircleResolution(3);
}

void Alea::setup(Audio* a, Midi* m) {
	audio = a;
	midi = m;
}

void Alea::update() {

}

bool Alea::shouldDraw() {
	int val = ofMap(midi->controller.getFader(0), 0, 127, 1, 30, true);
	counter--;
	if (counter == 0) {
		counter = 60;
	}

	int timeOn = 60 / val;

	return (counter / timeOn )% 2 == 0;
}

void Alea::draw() {
	if (!shouldDraw()) {
		return;
	}
	rotation += ofMap(midi->controller.getPotentiometer(0), 0, 127, -3, 3, true);
	if (rotation >= 360) {
		rotation -=360; 
	}

	float vol  = audio->getVol().scale() * 100.0;
	float bass = audio->getBass().scale() * 100.0;
	float mid  = audio->getMid().scale() * 100.0;
	float high = audio->getHigh().scale() * 100.0;

	float volThres  = audio->getVol().getThreshold().getVal() * 100.0;
	float bassThres = audio->getBass().getThreshold().getVal() * 100.0;
	float midThres  = audio->getMid().getThreshold().getVal() * 100.0;
	float highThres = audio->getHigh().getThreshold().getVal() * 100.0;

	bool beat = audio->getBass().getThreshold().isBeat();

	int beatcolor;
	if (audio->getBass().getThreshold().beatAmount() > 0) {
		beatcolor = ofMap(audio->getBass().getThreshold().beatAmount(), 0.0f, 0.25f, 0, 255, true);
	} else {
		beatcolor = 0;
	}

	if (beat) {
		ofSetCircleResolution(ofRandom(3, 8));
	}

	ofPushStyle();
		ofPushMatrix();
		ofNoFill();
		ofSetLineWidth(2); 
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);

		ofRotateZ(rotation + audio->getBass().getThreshold().beatAmount()*100);
		ofSetColor(255 - beatcolor/2, 255 - beatcolor, 255);
		ofDrawCircle(0, 0, bass * 4);

		ofRotateZ(90 - audio->getMid().getThreshold().beatAmount()*100);
		ofSetColor(150 - beatcolor, 255 - beatcolor/2, 255);
		ofDrawCircle(0, 0, mid * 1);
		
		ofRotateZ(90 + audio->getHigh().getThreshold().beatAmount()*100);
		ofSetColor(255 - beatcolor, beatcolor, 255);
		ofDrawCircle(0, 0, high * 3);

		ofRotateZ(90 - audio->getHigh().getThreshold().beatAmount()*100);
		ofSetColor(100 - beatcolor, 200 - beatcolor/2, 255);
		ofDrawCircle(0, 0, vol * 2);

		ofPopMatrix();
	ofPopStyle();
}