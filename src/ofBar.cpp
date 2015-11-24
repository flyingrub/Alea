#include "ofBar.h"

ofBar::ofBar() {

}

void ofBar::update() {

}

void ofBar::draw(Audio audio) {
	int color = 0xf44336;

	float vol  = audio.getVol().scale() * 100.0;
	float bass = audio.getBass().scale() * 100.0;
	float mid  = audio.getMid().scale() * 100.0;
	float high = audio.getHigh().scale() * 100.0;

	float volThres  = audio.getVol().getThreshold().getVal() * 100.0;
	float bassThres = audio.getBass().getThreshold().getVal() * 100.0;
	float midThres  = audio.getMid().getThreshold().getVal() * 100.0;
	float highThres = audio.getHigh().getThreshold().getVal() * 100.0;

	ofPushStyle();
		ofPushMatrix();
		ofTranslate(100, 600, 0);
		glLineWidth(50);
		ofSetHexColor(0x2196f3);
		
		ofDrawLine(0, 0, 0, -vol * 3.0f);
		ofDrawLine(100, 0, 100, -bass * 3.0f);
		ofDrawLine(200, 0, 200, -mid * 3.0f);
		ofDrawLine(300, 0, 300, -high * 3.0f);
		
		if (audio.getVol().getThreshold().hold > 55) {
			color = 0xd500f9;
		}
		if (audio.getVol().getThreshold().hold < 5) {
			color = 0xf44336;
		}
		ofSetHexColor(color);
		ofDrawLine(0, -volThres * 3.0f, 0, -volThres * 3.0f + 5);

		if (audio.getBass().getThreshold().hold > 55) {
			color = 0xd500f9;
		}
		if (audio.getBass().getThreshold().hold < 5) {
			color = 0xf44336;
		}
		ofSetHexColor(color);
		ofDrawLine(100, -bassThres * 3.0f, 100, -bassThres * 3.0f + 5);
		if (audio.getMid().getThreshold().hold > 55) {
			color = 0xd500f9;
		}
		if (audio.getMid().getThreshold().hold < 5) {
			color = 0xf44336;
		}
		ofSetHexColor(color);
		ofDrawLine(200, -midThres * 3.0f, 200, -midThres * 3.0f + 5);

		if (audio.getHigh().getThreshold().hold > 55) {
			color = 0xd500f9;
		}
		if (audio.getHigh().getThreshold().hold < 5) {
			color = 0xf44336;
		}
		ofSetHexColor(color);
		ofDrawLine(300, -highThres * 3.0f, 300, -highThres * 3.0f + 5);

		ofPopMatrix();
	ofPopStyle();
}