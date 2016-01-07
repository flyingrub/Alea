#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	 
	
	ofSetVerticalSync(false);
	ofEnableSmoothing();
	ofSetFrameRate(60);
	ofBackground(0, 0, 0);
	
	// 0 output channels, 
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	
	soundStream.printDeviceList();
	//if you want to set a different device id 
	soundStream.setDeviceID(4); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
	soundStream.setup(this, 0, 2, 44100, BUFFER_SIZE, 4);

	midi.setup(1);

	alea.setup(&audio, &midi);
	bar.setup(&audio, &midi);
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::exit(){
	midi.exit();
}

//--------------------------------------------------------------
void ofApp::draw(){
	audio.calc();
	float vol  = audio.getVol().scale() * 100.0;
	float bass = audio.getBass().scale() * 100.0;
	float mid  = audio.getMid().scale() * 100.0;
	float high = audio.getHigh().scale() * 100.0;
	float hold = audio.getVol().getThreshold().hold;
	
	ofNoFill();

	if (midi.controller.getButton(0)) {
		ofPushStyle();
			ofPushMatrix();
			ofTranslate(2, 2, 0);
				
			ofSetColor(225);
			ofDrawBitmapString("Fps: " + ofToString((int)ofGetFrameRate()), 32, 20);
			ofDrawBitmapString("Average vol (0-100): " + ofToString(vol, 0), 32, 40);
			ofDrawBitmapString("Bass vol (0-100): " + ofToString(bass, 0), 32, 60);
			ofDrawBitmapString("Mid vol (0-100): " + ofToString(mid, 0), 32, 80);
			ofDrawBitmapString("High vol (0-100): " + ofToString(high, 0), 32, 100);
			ofDrawBitmapString("hold: " + ofToString(hold, 0), 32, 160);
			ofDrawBitmapString("Value: " + ofToString(midi.value, 0), 32, 120);
			ofDrawBitmapString("Control: " + ofToString(midi.control, 0), 32, 140);
			ofSetLineWidth(1);	
			ofDrawRectangle(0, 0, 400, 180);
			ofPopMatrix();
		ofPopStyle();
	}

	if (midi.controller.getButton(0)) {
		bar.draw();
	}

	if (midi.controller.getButton(1)) {
		alea.draw();
	}
	
	
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
	audio.update(input, bufferSize);
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

