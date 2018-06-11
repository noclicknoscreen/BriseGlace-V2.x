//
//  enigmaHint.hpp
//  theEnigmaTest
//
//  Created by Sébastien Albert on 11/05/2018.
//
//

#pragma once

#include "ofMain.h"

#include "ofxJson.h"

const string tagJeu = "jeux";
const string tagMot = "mot";
const string tagIndice = "indice";
const string tagRecompense = "recompense";

const string tagTitre = "titre";
const string tagImage = "image-crop";
const string tagURL = "url";
const string tagLegende = "legende";

class enigmaHint {
    
public:
    enigmaHint(){
        mImage.load("void.jpg)");
    };
    
    enigmaHint(string _path, ofxJSONElement _content){
        
        string _imagePath;
        string _titre = _content[tagTitre].asString();
        string _legende = _content[tagLegende].asString();
        
        _imagePath += _path;
        _imagePath += "/image/";
        _imagePath += _content[tagImage].asString();
        
        ofFile img(_imagePath);
        if(_imagePath!= "" && img.exists()){
            mImage.load(_imagePath);
        }else{
            ofLogWarning() << "Image file does not exist :"  << _imagePath;
            mIsAvaiable = false;
        }
        
        mTitre = _titre;
        mIsAvaiable = true;
    };
    
    bool isAvailable(){
        return mIsAvaiable;
    };
    
    ofImage     getImage(){return mImage;};
    string      getTitre(){return mTitre;};
    
private:
    ofImage mImage;
    string  mTitre;
    
    bool mIsAvaiable;
    
};
