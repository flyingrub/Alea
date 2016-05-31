#pragma once
#include "ofMain.h"
#include "Audio.h"
#include "Midi.h"
#include "PointCircleInfo.h"


class PointCircle {

	public:
		PointCircle();
		void setup(Audio* a, Midi* m);
		void update();
		void draw();
		void drawOneCircle(PointCircleInfo* info, ofColor color, SmoothValue value);
		void drawOneSquare(PointCircleInfo* info, ofColor color, SmoothValue value);

	private:
		Audio* audio;
		Midi* midi;
		int counter = 60;
		PointCircleInfo* infoBass;
		PointCircleInfo* infoMid;
		PointCircleInfo* infoHigh;
		PointCircleInfo* infoVol;

};
