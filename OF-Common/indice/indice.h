//
//  indice.hpp
//  emptyExample
//
//  Created by Blindsp0t on 09/05/2018.
//
//

#ifndef indice_hpp
#define indice_hpp

#include <stdio.h>
#include "ofMain.h"
#include "cube.h"
#include "ofxTextSuite.h"

class indice
{
public:
    
    void setup(string photoFilename="test.jpg");
    void update();
    void draw();
    
    void drawTexturedCube(int i, float texCoordX_min, float texCoordX_max, float texCoordY_min, float texCoordY_max);
    void drawTexturedCubeTEXT(int i, float texCoordX_min, float texCoordX_max, float texCoordY_min, float texCoordY_max);

    
    void setRevealMode(){revealMode = true;}
    
    vector<cube> myCubes;
    
private :
    
    //cubes attributes
    float cubeSize;
    float totalWidth;
    float yPos;
    
    //image to be revealed
    ofImage texture;
    
    //utils
    bool revealMode;
    int cubeIndex;
    
    //font
    ofTrueTypeFont font;
    
    //fbo to draw text, to be used as texture
    ofFbo textFbo;
    ofImage textImageFromFbo;
    
    //lumiere
    ofLight spotLight;
    ofColor lightColor;
    ofColor materialColor;
    ofMaterial material;
    
    //text
    ofxTextBlock myText;
};



#endif /* indice_hpp */
