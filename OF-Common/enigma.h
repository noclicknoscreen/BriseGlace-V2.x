//
//  enigma.hpp
//  theBigGame
//
//  Created by Sébastien Albert on 10/05/2018.
//
//

#pragma once

#include "ofMain.h"

//////////////////////////////////////////////////////////////////////////////////
class hint{
    
private:
    string  mDesc;
    ofImage mImg;
    
    // Getters & setters
private:
    string getDesc(){return mDesc;}
    void setDesc(string _desc){mDesc = _desc;};
    
    ofImage* getImgRef(){return &mImg;};
    void setImg(ofImage _img){mImg = _img;};
    
};

//////////////////////////////////////////////////////////////////////////////////
class enigma{
    
private:
    vector<hint>    mHints;
    hint            mReward;
    
};
