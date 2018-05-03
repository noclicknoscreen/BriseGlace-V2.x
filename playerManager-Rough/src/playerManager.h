//
//  playerManager.hpp
//  playerManager-Rough
//
//  Created by Sébastien Albert on 03/05/2018.
//
//

#pragma once

#include "ofMain.h"
#include "ofxJSON.h"

class playerManager : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void urlResponse(ofHttpResponse & response);
    
    int getLastNumber(){return mLastNumber;};
    string getLastMessage(){return mLastMessage;};
    
private:
    bool mHttpLoading;
    
    int mLastNumber;
    string mLastMessage;
    
    ofxJSONElement response;
    
};
