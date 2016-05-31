#include "PointCircle.h"

PointCircle::PointCircle() {

}

void PointCircle::setup(Audio* a, Midi* m) {
	audio = a;
	midi = m;
	infoBass =  new PointCircleInfo(600, 0.02, false, 50);
	infoMid = new PointCircleInfo(400, 0.1, true, 15);
	infoHigh = new PointCircleInfo(200, 0.06, false, 20);
	infoVol = new PointCircleInfo(800, 0.5, true, 40);
}

void PointCircle::update() {

}

void PointCircle::drawOneCircle(PointCircleInfo* info, ofColor color, SmoothValue value) {
	float amount = value.scale();
	float rotation = info->addRotation(amount);
	int circleRes = info->getCircleResolution();

	ofSetCircleResolution(100);
	ofSetColor(color.clamp());
	ofFill();

	ofPushMatrix();
	ofRotateZ(rotation);
	float radius = info->getSize() / 2 + info->getSizeValue(amount);

	for(int i=0; i < circleRes; i++) {
		float angle = TWO_PI / circleRes * i;
		float x = cos(angle) * radius;
		float y = sin(angle) * radius;
		ofDrawCircle(x, y, 3);
	}
	ofPopMatrix();
}

void PointCircle::drawOneSquare(PointCircleInfo* info, ofColor color, SmoothValue value) {
	float amount = value.scale();
	float rotation = info->addPadding(amount);
	int circleRes = info->getCircleResolution();

	ofSetCircleResolution(100);
	ofSetColor(color.clamp());
	ofFill();

	ofPushMatrix();
	int size = info->getSize();
	int pad = size * 4 / circleRes;

	float length = rotation;
	for(int i=0; i < circleRes; i++) {
		length += pad;
		float x;
		float y;
		if (length < 0) {
			x = 0; y = -length;
		} else if (length < size) {
			x = length; y = 0;
		} else if (length < size * 2) {
			x = size; y = length - size;
		} else if (length < size * 3) {
			x = size - (length - size * 2); y = size;
		} else if (length < size * 4){
			x = 0; y = size - (length - size * 3);
		} else {
			x = length - size * 4; y= 0;
		}
		x -= size / 2; y -= size /2;
		ofDrawCircle(x, y, 3);	}
	ofPopMatrix();
}

void PointCircle::draw() {
	ofPushStyle();
		ofPushMatrix();
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);

		this->drawOneCircle(infoBass, ofColor(255, 255, 255), audio->getBass());
		this->drawOneCircle(infoMid, ofColor(255, 255, 255), audio->getMid());
		this->drawOneCircle(infoHigh, ofColor(255, 255, 255), audio->getHigh());
		this->drawOneSquare(infoVol, ofColor(255, 255, 255), audio->getVol());

		ofPopMatrix();
	ofPopStyle();
}