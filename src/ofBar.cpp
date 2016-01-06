#include "ofBar.h"

ofBar::ofBar() {

}

void ofBar::setup(Audio* a, Midi* m) {
	audio = a;
	midi = m;
}

void ofBar::update() {

}

void ofBar::draw() {
	int color = 0xf44336;

	float vol  = audio->getVol().scale() * 100.0;
	float bass = audio->getBass().scale() * 100.0;
	float mid  = audio->getMid().scale() * 100.0;
	float high = audio->getHigh().scale() * 100.0;

	float volThres  = audio->getVol().getThreshold().getVal() * 100.0;
	float bassThres = audio->getBass().getThreshold().getVal() * 100.0;
	float midThres  = audio->getMid().getThreshold().getVal() * 100.0;
	float highThres = audio->getHigh().getThreshold().getVal() * 100.0;

	float midiValue = ofMap(midi->value, 0, 127, 0.0f, 1.0f, true) * 100.0;

	ofPushStyle();
		ofPushMatrix();
		ofTranslate(50, 500, 0);
		glLineWidth(50);
		ofSetHexColor(0x2196f3);

		int margin = 100;
		int pos1 = margin * 1;
		int pos2 = margin * 2;
		int pos3 = margin * 3;
		int pos4 = margin * 4;
		
		ofDrawLine(0, 0, 0, -vol * 3.0f);
		ofDrawLine(pos1, 0, pos1, -bass * 3.0f);
		ofDrawLine(pos2, 0, pos2, -mid * 3.0f);
		ofDrawLine(pos3, 0, pos3, -high * 3.0f);

		ofDrawLine(pos4, 0, pos4, -midiValue * 3.0f);
		
		// VOL THRES
		if (audio->getVol().getThreshold().hold > BEAT) {
			color = 0xd500f9;
		}
		if (audio->getVol().getThreshold().hold < 5) {
			color = 0xf44336;
		}
		ofSetHexColor(color);
		ofDrawLine(0, -volThres * 3.0f, 0, -volThres * 3.0f + 5);

		// BASS THRES
		if (audio->getBass().getThreshold().hold > BEAT) {
			color = 0xd500f9;
		}
		if (audio->getBass().getThreshold().hold < 5) {
			color = 0xf44336;
		}
		ofSetHexColor(color);
		ofDrawLine(pos1, -bassThres * 3.0f, pos1, -bassThres * 3.0f + 5);
		
		// MID THRES
		if (audio->getMid().getThreshold().hold > BEAT) {
			color = 0xd500f9;
		}
		if (audio->getMid().getThreshold().hold < 5) {
			color = 0xf44336;
		}
		ofSetHexColor(color);
		ofDrawLine(pos2, -midThres * 3.0f, pos2, -midThres * 3.0f + 5);

		// HIGH THRES
		if (audio->getHigh().getThreshold().hold > BEAT) {
			color = 0xd500f9;
		}
		if (audio->getHigh().getThreshold().hold < 5) {
			color = 0xf44336;
		}
		ofSetHexColor(color);
		ofDrawLine(pos3, -highThres * 3.0f, pos3, -highThres * 3.0f + 5);

		ofPopMatrix();
	ofPopStyle();
}