//
//  scScene.hpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 07/05/2018.
//
//

#pragma once

#include "scScene.h"

class scSelect: public scScene {
    
protected:
    string  mPlayerMessage;
    ofColor mPlayerColor;
    
    timer mTimerEraseWord;
    
public:
    void someoneSpoke(player & _player);
    void  timerEraseWordEnd();
    
    void sceneWillAppear( ofxScene * fromScreen );
    void sceneWillDisappear( ofxScene * fromScreen );
    
};

