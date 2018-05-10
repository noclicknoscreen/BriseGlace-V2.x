//
//  enigma.cpp
//  theBigGame
//
//  Created by Sébastien Albert on 10/05/2018.
//
//

#include "enigma.h"

bool enigma::load(string _path){
    
    ofFile fileJson(_path + "/enigma.json");
    
    //
    if(!fileJson.exists()){
        ofLogError() << "[" << fileJson.path() << "]" << "enigma.json don't exists";
        return false;
        
    }else{
        ofxJSONElement content;
        if(content.open(fileJson.getAbsolutePath())){
            ofLogNotice() << "Le mot est : " << content["mot"];
            
            int nbHints = content["indices"].size();
            for (int idxHint = 0; idxHint < nbHints; ++idxHint)
            {
                // Does player exists ?
                ofLogNotice() << "Indice [" << ofToString(idxHint + 1) << "] : " << content["indices"][idxHint]["nom"] << " - " << content["indices"][idxHint]["image"];
                ofImage img;
                string fullPath;
                fullPath += _path;
                fullPath += "/image/";
                fullPath += content["indices"][idxHint]["image"].asString();
                
                img.load(fullPath);
                
            }
        }
    };
    
    return true;
    
}
