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

	return (counter / timeOn ) % 2 == 0;
}

void Alea::drawOne(float size, ofColor color, SmoothValue value) {
	if (size <= 0) {
		return;
	}
	float amount = value.scale() * 100.0;
	float amountThres  = value.getThreshold().getVal() * 100.0;

	int beatAmount = value.getThreshold().beatAmount() * 100;
	ofRotateZ(beatAmount);

	ofSetColor(color.clamp());

	int circleSize = amount * size;
	while (beatAmount <= circleSize) {
		ofDrawCircle(0, 0, circleSize - beatAmount);
		color.setBrightness(color.getBrightness() * 0.8);
		ofSetColor(color.clamp());
		beatAmount = beatAmount * 2.6 + 10;
	}
}

void Alea::draw() {
	if (!shouldDraw()) {
		return;
	}

	rotation += ofMap(midi->controller.getPotentiometer(0), 0, 127, -2.0f, 2.0f, true);
	if (rotation >= 360) {
		rotation -=360;
	}

	bool beat = audio->getVol().getThreshold().isBeat() && audio->getVol().getThreshold().beatAmount() > 0.05f;
	if (beat) {
		ofSetCircleResolution(ofRandom(4, 9));
	}

	ofPushStyle();
		ofPushMatrix();
		ofNoFill();
		ofSetLineWidth(2);
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);

		ofRotateZ(rotation);

		int beatcolor = ofMap(audio->getBass().getThreshold().beatAmount(), 0.0f, 0.25f, 0, 122, true) +
			ofMap(audio->getHigh().getThreshold().beatAmount(), 0.0f, 0.25f, 0, 123, true);

		this->drawOne(2, ofColor(100 - beatcolor, 200 - beatcolor/2, 255), audio->getVol());
		this->drawOne(3.5, ofColor(255, beatcolor - 100, 255 - beatcolor/2), audio->getBass());
		this->drawOne(1, ofColor(150 - beatcolor, 255 - beatcolor/2, 255), audio->getMid());
		this->drawOne(3, ofColor(255 - beatcolor, beatcolor, 255), audio->getHigh());

		ofPopMatrix();
	ofPopStyle();
}