#pragma once

#include "ofMain.h"
//#include "ofxPostProcessing.h"
#include "Audio.h"
#include "Midi.h"
#include "Alea.h"
#include "PointCircle.h"
#include "PreferenceApp.h"

class ofApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void audioIn(float * input, int bufferSize, int nChannels);
		shared_ptr<PreferenceApp> gui;

	private:

		void beatDetected();

		ofSoundStream soundStream;
		//ofxPostProcessing post;
		Audio audio;
		Midi midi;
		Alea alea;
		PointCircle pointCircle;


};
