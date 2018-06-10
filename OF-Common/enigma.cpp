//
//  enigma.cpp
//  theBigGame
//
//  Created by Sébastien Albert on 10/05/2018.
//
//

#include "enigma.h"

const string tagJeu = "jeux";
const string tagMot = "mot";
const string tagIndice = "indice";
const string tagRecompense = "recompense";

const string tagTitre = "titre";
const string tagImage = "image-crop";
const string tagURL = "url";

const string tagLegende = "legende";

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
            
            // Head of the enigma (Solution, legend) --
            mSolution   = content[tagMot][tagTitre].asString();
            mLegende    = content[tagRecompense][tagLegende].asString();
            
            ofLogNotice() << "Enigma : " << mSolution << "," << mLegende;
            
            
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
                    enigmaHint newHint(fullPath, content[tagIndice][idxHint][tagTitre].asString());
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
                mReward = enigmaHint(rewImgPath, content[tagRecompense][tagIndice][tagTitre].asString());
            }
            
            
            
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
bool enigma::getIsAvailable(enigmaType _type){
    return getHint(_type)->isAvailable();
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



