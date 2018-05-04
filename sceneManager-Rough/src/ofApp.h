#pragma once

#include "ofMain.h"
#include "ofxAnimatableFloat.h"

#include "ofxSceneManager.h"
// Include Scenes
#include "scIntro.h"
#include "scInitialize.h"
#include "scSelectGame.h"
#include "scGame1.h"
#include "scGame2.h"
#include "scGame3.h"
#include "scHint.h"
#include "scVictory.h"

class ofApp : public ofBaseApp{

	enum Scenes{ INTRO = 1, INITIALIZE, SELECT_GAME, GAME1, GAME2, GAME3, HINT, VICTORY };
	
	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mousePressed( int x, int y, int button );


		void windowResized(int w, int h);
	
		ofxSceneManager *		sceneManager;
};
