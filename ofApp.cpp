#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("openFrameworks");
	ofSetFrameRate(30);

	ofBackground(0);
	ofNoFill();
	ofSetLineWidth(2);
	ofEnableDepthTest();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	for (int x = -330; x <= 330; x += 30) {

		for (int y = -330; y <= 330; y += 30) {

			ofPushMatrix();
			ofTranslate(x, y);

			auto distance = glm::length(glm::vec2(x, y));

			auto x_value = ofNoise(noise_seed.x, x * 0.015, y * 0.015, ofGetFrameNum() * 0.015);
			auto y_value = ofNoise(noise_seed.y, x * 0.015, y * 0.015, ofGetFrameNum() * 0.015);
			auto z_value = ofNoise(noise_seed.z, x * 0.015, y * 0.015, ofGetFrameNum() * 0.015);

			auto x_deg = x_value < 0.35 ? ofMap(x_value, 0, 0.35, -360, 0) : x_value > 0.75 ? ofMap(x_value, 0.75, 1, 0, 360) : 0;
			auto y_deg = y_value < 0.35 ? ofMap(y_value, 0, 0.35, -360, 0) : y_value > 0.75 ? ofMap(y_value, 0.75, 1, 0, 360) : 0;
			auto z_deg = z_value < 0.35 ? ofMap(z_value, 0, 0.35, -360, 0) : z_value > 0.75 ? ofMap(z_value, 0.75, 1, 0, 360) : 0;

			ofRotateZ(z_deg);
			ofRotateY(y_deg);
			ofRotateX(x_deg);

			auto alpha = 64;

			ofFill();
			ofSetColor(255, 0, 0, alpha);
			ofDrawCircle(glm::vec2(), 12);

			ofNoFill();
			ofSetColor(255, 0, 0);
			ofDrawCircle(glm::vec2(), 12);

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}