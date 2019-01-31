#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetColor(255);
	ofNoFill();
	ofSetLineWidth(0.5);
	ofEnableDepthTest();

	// Parameter reference by https://twitter.com/ru_sack/status/798308368007892992

	float a = 1.25;
	float b = 1.25;
	float c = 1.0;
	float h = 3.5;
	float k = 0;
	float w = 0.12;
	int R = 1;
	int scale = 100;

	float u_step = 0.15;
	int v_step = 15;
	for (float u = -35; u <= -1; u += u_step) {

		for (int v = 0; v <= 360; v += v_step) {
			
			vector<glm::vec3> vertices;
			vertices.push_back(this->make_shell_point(a, b, c, h, k, u + u_step * 0.5, (v + v_step * 0.5) * DEG_TO_RAD, w, R) * scale);
			vertices.push_back(this->make_shell_point(a, b, c, h, k, u + u_step * 0.5, (v - v_step * 0.5) * DEG_TO_RAD, w, R) * scale);
			vertices.push_back(this->make_shell_point(a, b, c, h, k, u - u_step * 0.5, (v - v_step * 0.5) * DEG_TO_RAD, w, R) * scale);
			vertices.push_back(this->make_shell_point(a, b, c, h, k, u - u_step * 0.5, (v + v_step * 0.5) * DEG_TO_RAD, w, R) * scale);
			this->verticesList.push_back(vertices);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int sound_index = 0;
	for (auto vertices : this->verticesList) {

		ofBeginShape();
		for (auto vertex : vertices) {

			float noise_value = ofMap(ofNoise(vertex.x * 0.005, vertex.y * 0.005, vertex.z * 0.005, ofGetFrameNum() * 0.05), 0, 1, 0.8, 1.0);
			ofVertex(vertex * noise_value);
		}
		ofEndShape(true);
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_shell_point(float a, float b, float c, float h, float k, float u, float v, float w, int R) {

	// 数学デッサン教室 描いて楽しむ数学たち 貝殻の形 shape of shell P.59

	float x = (h + a * cos(v)) * exp(w * u) * cos(c * u);
	float y = R * (h + a * cos(v)) * exp(w * u) * sin(c * u);
	float z = (k + b * sin(v)) * exp(w * u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
