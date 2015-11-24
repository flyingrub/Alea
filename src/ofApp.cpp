#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	 
	
	ofSetVerticalSync(false);
	ofEnableSmoothing();
	ofSetFrameRate(60);
	ofSetCircleResolution(3);
	ofBackground(54, 54, 54);
	
	// 0 output channels, 
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	
	soundStream.printDeviceList();
	
	//if you want to set a different device id 
	soundStream.setDeviceID(4); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
	
	soundStream.setup(this, 0, 2, 44100, BUFFER_SIZE, 4);

	post.init(ofGetWidth(), ofGetHeight());
	post.createPass<FxaaPass>();
	post.createPass<BloomPass>();
}

//--------------------------------------------------------------
void ofApp::update(){
	
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
		ofDrawBitmapString("Average vol (0-100): " + ofToString(audio.getVol() * 100.0, 0), 32, 20);
		ofDrawBitmapString("bass vol (0-100): " + ofToString(audio.getBass().scale() * 100.0, 0), 32, 40);
		ofDrawBitmapString("mid vol (0-100): " + ofToString(audio.getMid().scale() * 100.0, 0), 32, 60);
		ofDrawBitmapString("high vol (0-100): " + ofToString(audio.getHigh().scale() * 100.0, 0), 32, 80);
		ofSetLineWidth(1);	
		ofDrawRectangle(0, 0, 512, 200);
		ofPopMatrix();
	ofPopStyle();

	// draw the right channel:
	ofPushStyle();
		ofPushMatrix();
		ofTranslate(32, 300, 0);
			
		ofSetColor(225);
		ofDrawBitmapString("Right Channel", 32, 18);
		
		ofSetLineWidth(1);	
		ofDrawRectangle(0, 0, 512, 200);

		ofSetColor(41, 182, 246);
		ofSetLineWidth(3);
					
			ofBeginShape();
			for (unsigned int i = 0; i < audio.right.size(); i++){
				ofVertex(i*2, 100 - audio.right[i]*180.0f);
			}
			ofEndShape(false);
			
		ofPopMatrix();
	ofPopStyle();
	
	// draw the volume history:
	ofPushStyle();
		ofPushMatrix();
		ofTranslate(32, 500, 0);
		ofDrawRectangle(0, 0, 912, 200);
		
		ofSetColor(41, 182, 246);
		//ofDrawBitmapString("history: " + ofToString(volHistory), 32, 20);

		ofFill();
		//lets draw the volume history as a graph
		ofBeginShape();
		for (unsigned int i = 0; i < audio.volHistory.size(); i++){
			if( i == 0 ) ofVertex(i, 199);

			ofVertex(i, 199 - audio.volHistory[i] * 170);
			
			if( i == audio.volHistory.size() -1 ) ofVertex(i, 199);
		}
		ofEndShape(false);		
			
		ofPopMatrix();
	ofPopStyle();

	// ALEA
	ofPushStyle();
		ofPushMatrix();
		ofTranslate(544, 100, 0);
			
		ofSetColor(225);
		ofDrawRectangle(0, 0, 400, 400);
		
		ofSetColor(41, 182, 246);
		ofFill();
		//ofDrawCircle(200, 200, audio.getBass() * 100.0f + audio.getVol() * 50.0f);

		ofSetColor(52, 52, 52);
		ofFill();
		//ofDrawCircle(200, 200, audio.getBass() * 100.0f);

		ofPopMatrix();
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
	audio.update(input, bufferSize);
	audio.calc();
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

