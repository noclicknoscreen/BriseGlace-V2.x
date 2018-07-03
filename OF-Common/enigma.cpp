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
            
            // Load all hints -------------------------
            int nbHints = content[tagIndice].size();
            for (int idxHint = 0; idxHint < nbHints; idxHint++)
            {
                string fullPath;
                fullPath += _path;
                fullPath += "/image/";
                fullPath += content[tagIndice][idxHint][tagImage].asString();
                
                imgFile = ofFile(imgFile);
                if(imgFile.exists()){
//                    enigmaHint newHint(content[tagIndice][idxHint][tagTitre].asString());
                    enigmaHint newHint(_path, content[tagIndice][idxHint]);
                    mHints.push_back(newHint);
                }else{
                    ofLogError() << "Image file does not exists : "  << fullPath;
                }
            }
            
            // Load reward ------------------------------
            string rewImgPath;
            rewImgPath += _path;
            rewImgPath += "/image/";
            rewImgPath += content[tagRecompense][tagIndice][tagImage].asString();
            
            imgFile = ofFile(rewImgPath);
            if(imgFile.exists()){
//                mRecompense = enigmaHint(rewImgPath, content[tagRecompense][tagIndice][tagTitre].asString());
                mRecompense = enigmaHint(_path, content[tagRecompense][tagIndice]);
            }
            
            
            // Load Solution ------------------------------
            rewImgPath = "";
            rewImgPath += _path;
            rewImgPath += "/image/";
            rewImgPath += content[tagMot][tagIndice][tagImage].asString();
            
            imgFile = ofFile(rewImgPath);
            if(imgFile.exists()){
//                mSolution = enigmaHint(rewImgPath, content[tagMot][tagIndice][tagTitre].asString());
                mSolution = enigmaHint(_path, content[tagMot]);
            }
            
            // Basic enigma fields
            mLegende = utils::cleanString(content[tagRecompense][tagLegende].asString());
            mTheme   = content[tagTheme].asString();
            mAuteurMot = content[tagMot][tagAuteur].asString();
            
            // Head of the enigma (Solution, legend) --
            ofLogNotice() << "Enigma : ";
            ofLogNotice() << getSolution();
            ofLogNotice() << getLegende();
            
        }
    };
    
    return true;
    
}

ofImage enigma::getImage(enigmaType _type){
    return getHint(_type)->getImage();
}
string enigma::getTitre(enigmaType _type){
    return getHint(_type)->getTitre();
}
string enigma::getAuteur(enigmaType _type){
    return getHint(_type)->getAuteur();
}
bool enigma::getIsAvailable(enigmaType _type){
    return getHint(_type)->isAvailable();
}

enigmaHint* enigma::getHint(enigmaType _type){
    
    switch (_type) {
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



