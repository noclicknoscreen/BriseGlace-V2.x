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
    enigmaHint(){
        image.load("void.jpg)");
    };
    
    enigmaHint(string _imagePath, string _titre){
        
        ofFile img(_imagePath);
        if(_imagePath!= "" && img.exists()){
            image.load(_imagePath);
        }else{
            ofLogWarning() << "Image file does not exist :"  << _imagePath;
        }
        titre = _titre;
        
    };
    bool isAvailable(){
        return (image.isAllocated() && (titre != ""));
    };
    
    ofImage     getImage(){return image;};
    string      getTitre(){return titre;};
    
private:
    ofImage image;
    string  titre;
    
};
