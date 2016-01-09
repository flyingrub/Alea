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
	rotation += ofMap(midi->controller.getPotentiometer(0), 0, 127, -2.0f, 2.0f, true);
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

	bool beat = audio->getVol().getThreshold().isBeat() && audio->getVol().getThreshold().beatAmount() > 0.05f;

	int beatcolor;
	if (audio->getBass().getThreshold().beatAmount() > 0) {
		beatcolor = ofMap(audio->getBass().getThreshold().beatAmount(), 0.0f, 0.25f, 0, 122, true) + 
			ofMap(audio->getHigh().getThreshold().beatAmount(), 0.0f, 0.25f, 0, 123, true);
	} else {
		beatcolor = 0;
	}
	if (beat) {
		ofSetCircleResolution(ofRandom(4, 9));
	}

	ofPushStyle();
		ofPushMatrix();
		ofNoFill();
		ofSetLineWidth(2.5); 
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);

		int beatAmount = audio->getBass().getThreshold().beatAmount() * 100;
		ofRotateZ(rotation + beatAmount);
		ofSetColor(beatcolor +50, 100-beatcolor, beatcolor +100);
		while (beatAmount <= bass * 3) {
			ofDrawCircle(0, 0, (bass * 3) - beatAmount);
			beatAmount = beatAmount * 2 + 10;
		}
		
		beatAmount = audio->getMid().getThreshold().beatAmount() * 50;
		ofRotateZ(90 - beatAmount);
		ofSetColor(150 - beatcolor, 255 - beatcolor/2, 255);
		while (beatAmount <= mid * 1) {
			ofDrawCircle(0, 0, mid * 1 - beatAmount);
			beatAmount = beatAmount * 1.5 + 10;
		}

		beatAmount = audio->getHigh().getThreshold().beatAmount() * 50;
		ofRotateZ(90 + beatAmount);
		ofSetColor(255 - beatcolor, beatcolor, 255);
		while (beatAmount <= high * 3) {
			ofDrawCircle(0, 0, high * 3 - beatAmount);
			beatAmount = beatAmount * 3 + 10;
		}

		beatAmount = audio->getVol().getThreshold().beatAmount() * 100;
		ofRotateZ(90 - beatAmount);
		ofSetColor(100 - beatcolor, 200 - beatcolor/2, 255);
		while (beatAmount <= vol * 2) {
			ofDrawCircle(0, 0, vol * 2 -beatAmount);
			beatAmount = beatAmount * 2.5 + 10;
		}


		ofPopMatrix();
	ofPopStyle();
}