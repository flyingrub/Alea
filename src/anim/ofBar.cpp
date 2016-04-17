#include "ofBar.h"

ofBar::ofBar() {

}

void ofBar::setup(Audio* a, Midi* m) {
	audio = a;
	midi = m;
}

void ofBar::update() {

}

void ofBar::drawOne(int pos, SmoothValue value) {
	float amount = value.scale() * 100.0;
	float amountThres  = value.getThreshold().getVal() * 100.0;

	int margin = 100;
	pos = pos * margin;

	// Amount
	ofSetColor(255);
	ofFill();
	ofDrawRectangle(pos, 0, 10, -amount * 3.0f);

	// Threshold
	if (audio->getVol().getThreshold().hold > BEAT) {
		ofSetHexColor(0x18ffff);
	}
	ofDrawRectangle(pos, -amountThres * 3.0f - 2, 10, - 4);

	// GUI
	ofNoFill();
	ofSetHexColor(0x18ffff);
	ofDrawTriangle(pos - 10, 0, pos - 10, - 5, pos, 0);
	ofDrawTriangle(pos - 10, - 155, pos - 10, - 145, pos, - 150);
	ofDrawTriangle(pos - 10, - 300, pos - 10, - 295, pos, - 300);
}

void ofBar::draw() {
	ofPushStyle();
		ofPushMatrix();
		glLineWidth(1);

		this->drawOne(0, audio->getVol());
		this->drawOne(1, audio->getBass());
		this->drawOne(2, audio->getMid());
		this->drawOne(3, audio->getHigh());

		ofPopMatrix();
	ofPopStyle();
}