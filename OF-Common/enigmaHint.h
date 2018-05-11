//
//  enigmaHint.hpp
//  theEnigmaTest
//
//  Created by Sébastien Albert on 11/05/2018.
//
//

#pragma once

#include "ofMain.h"

class enigmaHint {
    
public:
    
    enigmaHint(string _imagePath, string _desc){
        image.load(_imagePath);
        description = _desc;
    };
    bool isAvailable(){
        return (image.isAllocated() && (description != ""));
    };
    
    ofImage     getImage(){return image;};
    string      getDescription(){return description;};
    
private:
    ofImage image;
    string  description;
    
};
