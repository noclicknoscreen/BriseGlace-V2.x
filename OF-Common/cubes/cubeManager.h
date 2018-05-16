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
#include "utils.h"

#define cubesPositionY 200
#define consignesPositionY 100
#define espacementCubes 15

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
        void colorizeCube(int cubeId, ofColor _color);
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
    
        //consigne
        string consigne;
        float consigneWidth;
    
        //backgroundImage
        ofImage background;
};



#endif /* cubeManager_hpp */
