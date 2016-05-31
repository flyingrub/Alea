#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofBackground(0, 0, 0);
	ofSetEscapeQuitsApp(false);

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
	pointCircle.setup(&audio, &midi);
	gui->setup(&audio, &midi);
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

	if (gui->showFPS) {
		ofDrawBitmapString("Fps: " + ofToString((int)ofGetFrameRate()), 32, 20);
	}

	if (midi.controller.getButton(1)) {
		alea.draw();
		pointCircle.draw();
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
	if( key == 's' ) {
		soundStream.start();
	}

	if( key == 'e' ) {
		soundStream.stop();
	}

	if( key == OF_KEY_RETURN ) {
		ofToggleFullscreen();
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

