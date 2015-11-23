#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	 
	
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofSetFrameRate(60);
	ofSetCircleResolution(3);
	ofBackground(54, 54, 54);	
	
	// 0 output channels, 
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	
	soundStream.listDevices();
	
	//if you want to set a different device id 
	soundStream.setDeviceID(4); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
	
	int bufferSize = 256;
	
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(912, 0.0);

	smoothedVol     = 0.0;
	scaledVol		= 0.0;
	smoothedVolBass = 0.0;
	scaledVolBass	= 0.0;

	decayRate = 0.05;
	minThreshold = ofMap(0.05, 0.0, 1.0, 0.0, 0.17, true);
	threshold = minThreshold;
	scaledThreshold = minThreshold;
	hold = 0;

	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);

}

//--------------------------------------------------------------
void ofApp::update(){
	//lets scale the vol up to a 0-1 range 
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
	scaledVolBass = ofMap(smoothedVolBass, 0.0, 0.17, 0.0, 1.0, true);
	scaledThreshold = ofMap(threshold, 0.0, 0.17, 0.0, 1.0, true);

	//lets record the volume into an array
	volHistory.push_back( scaledVol );
	
	//if we are bigger the the size we want to record - lets drop the oldest value
	if( volHistory.size() >= 912 ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofNoFill();

	ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 32, 20);

	// draw the left channel:
	ofPushStyle();
		ofPushMatrix();
		ofTranslate(32, 100, 0);
			
		ofSetColor(225);
		ofDrawBitmapString("Left Channel", 32, 18);
		
		ofSetLineWidth(1);	
		ofRect(0, 0, 512, 200);

		ofSetColor(41, 182, 246);
		ofSetLineWidth(3);
					
			ofBeginShape();
			for (unsigned int i = 0; i < left.size(); i++){
				ofVertex(i*2, 100 -left[i]*180.0f);
			}
			ofEndShape(false);
			
		ofPopMatrix();
	ofPopStyle();

	// draw the right channel:
	ofPushStyle();
		ofPushMatrix();
		ofTranslate(32, 300, 0);
			
		ofSetColor(225);
		ofDrawBitmapString("Right Channel", 32, 18);
		
		ofSetLineWidth(1);	
		ofRect(0, 0, 512, 200);

		ofSetColor(41, 182, 246);
		ofSetLineWidth(3);
					
			ofBeginShape();
			for (unsigned int i = 0; i < right.size(); i++){
				ofVertex(i*2, 100 -right[i]*180.0f);
			}
			ofEndShape(false);
			
		ofPopMatrix();
	ofPopStyle();
	
	// draw the volume history:
	ofPushStyle();
		ofPushMatrix();
		ofTranslate(32, 500, 0);
		ofRect(0, 0, 912, 200);
		
		ofSetColor(41, 182, 246);
		//ofDrawBitmapString("history: " + ofToString(volHistory), 32, 20);

		ofFill();
		//lets draw the volume history as a graph
		ofBeginShape();
		for (unsigned int i = 0; i < volHistory.size(); i++){
			if( i == 0 ) ofVertex(i, 199);

			ofVertex(i, 199 - volHistory[i] * 170);
			
			if( i == volHistory.size() -1 ) ofVertex(i, 199);
		}
		ofEndShape(false);		
			
		ofPopMatrix();
	ofPopStyle();

	// ALEA
	ofPushStyle();
		ofPushMatrix();
		ofTranslate(544, 100, 0);
			
		ofSetColor(225);
		ofDrawBitmapString("average vol (0-100): " + ofToString(scaledVol * 100.0, 0), 32, 20);
		ofDrawBitmapString("average BAss vol (0-100): " + ofToString(scaledVolBass * 100.0, 0), 32, 40);
		ofDrawBitmapString("threshold (0-100): " + ofToString(scaledThreshold * 100.0, 0), 32, 60);
		ofDrawBitmapString("canbeat: " + ofToString(canBeat), 32, 80);
		ofRect(0, 0, 400, 400);
		
		ofSetColor(41, 182, 246);
		ofFill();
		ofCircle(200, 200, scaledVol * 200.0f);

		ofSetColor(52, 52, 52);
		ofFill();
		ofCircle(200, 200, scaledVol * 150.0f);

		ofPopMatrix();
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){	
	
	float curVol = 0.0;
	float curBass = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;	

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;

		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		if (i <= 10) {
			curBass += left[i] * left[i];
			curBass += right[i] * right[i];
		}
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :) 
	curVol /= (float)numCounted;
	curBass /= 10.0;
	
	// this is how we get the root of rms :) 
	curVol = sqrt( curVol );
	curBass = sqrt( curBass );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;

	smoothedVolBass *= 0.95;
	smoothedVolBass += 0.05 * curBass;


	// BEAT DETECTION
	threshold = ofLerp(threshold, minThreshold, 0.005);
	canBeat = ofGetElapsedTimef() - hold >= 1.0; 

	if(smoothedVol > threshold && canBeat) {
        this->beatDetected();
        hold = ofGetElapsedTimef();
        threshold = smoothedVol;
    }
}

void ofApp::beatDetected() {
	ofSetCircleResolution(ofRandom(3,7));
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	if( key == 's' ){
		soundStream.start();
	}
	
	if( key == 'e' ){
		soundStream.stop();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

