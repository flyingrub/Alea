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

void Alea::draw() {
	float vol  = audio->getVol().scale() * 100.0;
	float bass = audio->getBass().scale() * 100.0;
	float mid  = audio->getMid().scale() * 100.0;
	float high = audio->getHigh().scale() * 100.0;

	float volThres  = audio->getVol().getThreshold().getVal() * 100.0;
	float bassThres = audio->getBass().getThreshold().getVal() * 100.0;
	float midThres  = audio->getMid().getThreshold().getVal() * 100.0;
	float highThres = audio->getHigh().getThreshold().getVal() * 100.0;

	float midiValue = ofMap(midi->value, 0, 127, 0.0f, 1.0f, true) * 100.0;

	bool beat = audio->getVol().getThreshold().isBeat() && audio->getVol().getThreshold().beatAmount() > 0.05f;

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
		
		ofRotateZ(audio->getBass().getThreshold().beatAmount()*15);
		ofSetColor(255 - beatcolor, beatcolor, 255);
		ofDrawCircle(0, 0, high*2 + mid);

		ofRotateZ(180);
		ofSetColor(255 - beatcolor/2, 255 - beatcolor, 255);
		ofDrawCircle(0, 0, (bass + mid) /2 + vol * 2);

		ofRotateZ(90);
		ofSetColor(100 - beatcolor, 200 - beatcolor/2, 255);
		ofDrawCircle(0, 0, vol * 2);

		ofPopMatrix();
	ofPopStyle();
}