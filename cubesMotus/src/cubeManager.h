//
//  cubeManager.hpp
//  cubes
//
//  Created by Blindsp0t on 03/05/2018.
//
//

#ifndef cubeManager_hpp
#define cubeManager_hpp

#include <stdio.h>
#include "ofMain.h"
#include "cube.h"
#include "ofxShadowSimple.h"

#define cubesPositionY 200

class cubeManager
{

    public :
    
        void setup();
        void update(ofPoint _lightPos, int cubesRotationSpeed);
        void draw();
        void getWord(string word);
    
        //cubes
        vector<cube>                myCubes;
        void rotateToWhite(int i);
        void rotateToWood(int i);
        void rotateToLetter(int i);
    
        void colorizeCube(int cubeId, int userId);
    
        int getNumberOfCubes() {return myCubes.size();}
    
    
    private:
    
        //lumiere    
        ofLight spotLight;
        ofColor lightColor;
        ofColor materialColor;
        ofMaterial material;
    
        //police de caracteres
        ofTrueTypeFont              font;
        
        //texture
        ofImage                     texture;
    
        //cubes size
        float                       cubeSize;
    
};



#endif /* cubeManager_hpp */
