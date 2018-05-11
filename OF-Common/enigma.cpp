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
    ofFile imgFile;
    
    //
    if(!fileJson.exists()){
        ofLogError() << "[" << fileJson.path() << "]" << "enigma.json don't exists";
        return false;
        
    }else{
        ofxJSONElement content;
        if(content.open(fileJson.getAbsolutePath())){
            ofLogNotice() << "Le mot est : " << content["mot"];
            
            mDesc = content["mot"].asString();
            mPath = fileJson.getAbsolutePath();
            
            int nbHints = content["indices"].size();
            for (int idxHint = 0; idxHint < nbHints; ++idxHint)
            {
                // Does player exists ?
                ofLogNotice() << "Indice [" << ofToString(idxHint + 1) << "] : " << content["indices"][idxHint]["description"] << " - " << content["indices"][idxHint]["image"];
                
                string fullPath;
                fullPath += _path;
                fullPath += "/image/";
                fullPath += content["indices"][idxHint]["image"].asString();
                
                imgFile = ofFile(fullPath);
                if(imgFile.exists()){
        
                    enigmaHint newHint(fullPath, content["indices"][idxHint]["description"].asString());
                    mHints.push_back(newHint);
                    
                }
            }
            
            string rewImgPath;
            rewImgPath += _path;
            rewImgPath += "/image/";
            rewImgPath += content["recompense"]["image"].asString();
            
            imgFile = ofFile(rewImgPath);
            if(imgFile.exists()){
                mReward = enigmaHint(rewImgPath, content["recompense"]["description"].asString());
            }
            
        }
    };
    
    return true;
    
}

enigmaHint* enigma::getHint(enigmaType _type){
    
    switch (_type) {
        case REWARD:
            if(mReward.isAvailable()){
                return &mReward;;
            }
            break;
        case HINT1:
            if(mHints[0].isAvailable()){
                return &mHints[0];
            }
            break;
        case HINT2:
            if(mHints[1].isAvailable()){
                return &mHints[1];
            }
            break;
        case HINT3:
            if(mHints[2].isAvailable()){
                return &mHints[2];
            }
            break;
        default:
            return nullptr;
            break;
    };

}

