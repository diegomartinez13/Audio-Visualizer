#pragma once

#include "ofMain.h"
#include "AudioVisualizer.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		int R = ofRandom(256);
		int G = ofRandom(256);
		int B = ofRandom(256);



		void songChanger(string song);

		void drawMode1(vector<float> amplitudes);
		void drawMode2(vector<float> amplitudes);
		void drawMode3(vector<float> amplitudes);
		void drawMode4(vector<float> amplitudes);
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	private:
		ofSoundPlayer sound;
		AudioVisualizer visualizer;
		
		bool playing = false;
		bool drawing = true;
		char mode = '1';
		double vol = 1;
	
	bool lock = false;
	bool looping = false;
	float startTime;

	//Images:
	ofImage cloud;
	ofImage pikachu;
	ofImage background;
	ofImage energy;

	//Cloud movers:
	float move1 = 0;
	float move2 = - 500;
	float move3 = - 900;

	//Pikachu mover:
	float moveP = 0;
	int index = 1;

};
