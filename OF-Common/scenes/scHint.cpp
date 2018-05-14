//
//  scHint.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scHint.h"

void scHint::setup(){  //load your scene 1 assets here...
    
    scScene::setup();
    ofLogNotice() << "Indice : Setup !";
    myTitle = "Ecran d'indices";
    
    
    //load texture
    texture.load("test.jpg");
    
    cubeSize = 120;
    totalWidth = cubeSize * 3;
    yPos = ofGetHeight()/2 - 3*(cubeSize/2);
    cubeIndex = 0;
    revealMode = false;
    
    
    //create cubes
    for(int i=0; i<9; i++)
    {
        int line = i%3;
        int row = i/3;
        
        if(i%3 == 0)
            yPos+= cubeSize;
        
        ofPoint pos = ofPoint((ofGetWidth()-totalWidth)/2 + (i%3)*cubeSize + cubeSize/2, yPos);
        
        cube c;
        c.setup(pos, cubeSize);
        c.currentRot = 180;
        c.desiredRot = 180;
        myCubes.push_back(c);
    }
    
    //load font
    font.load("Avenir.ttc", 12);
    textFbo.allocate(3*cubeSize, 3*cubeSize);
    textFbo.setUseTexture(true);
    
    //wrap text
    myText.init("Avenir.ttc", 12);
    myText.setText("Un château est à l'origine une construction médiévale destinée à protéger le seigneur et à symboliser son autorité au sein du fief. Les premiers châteaux étaient construits en bois souvent sur une élévation de terre (motte castrale ou féodale), puis en pierre afin de résister aux nouvelles armes de guerre. On les appela les châteaux forts.");
    myText.wrapTextX(cubeSize*3);
    
    //fill fbo and put it into an image
    textFbo.begin();
    ofClear(255);
    ofSetColor(0);
    myText.draw(0,0);
    textFbo.end();
    
    //put fbo in an image
    ofPixels tmp;
    textFbo.readToPixels(tmp);
    textImageFromFbo.setFromPixels(tmp);
    
    //lumiere
    spotLight.setSpotlight();
    spotLight.setSpotlightCutOff(200);
    spotLight.setAttenuation(0.3,0,0); //puissance de la light = inverse de l'attenuation
    spotLight.setSpotConcentration(0.15);
    spotLight.setDiffuseColor( ofColor(255.f, 255.f, 255.f));
    spotLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    spotLight.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    spotLight.setPosition(ofGetWidth()-300, 100, 0);
    material.setShininess( 128);
    lightColor.setBrightness( 255.0f);
    lightColor.setSaturation( 0.f );
    materialColor.setBrightness(255);
    materialColor.setSaturation(0);

};


void scHint::update(float dt){ //update scene 1 here
    
    //reveal corresponding cubes
    if(revealMode)
    {
        bool someoneRotating = false;
        for(int i=0; i<myCubes.size(); i++)
        {
            if(myCubes[i].isRotating == true)
                someoneRotating = true;
        }
        
        if(!someoneRotating)
        {
            if(cubeIndex < myCubes.size())
            {
                cubeIndex++;
                myCubes[cubeIndex-1].rotateToWhite();
            }
        }
    }
    
    //update cubes
    for(int i=0; i<myCubes.size(); i++)
    {
        myCubes[i].update(1);
    }
    
    //lumiere
    spotLight.setPosition(ofGetMouseX(), ofGetMouseY(),100);
    spotLight.setOrientation( ofVec3f( 0, 45, 30) );
    lightColor.setHue(0);
    spotLight.setDiffuseColor(lightColor);
    material.setSpecularColor(materialColor);

    if(ofGetElapsedTimef() - timer > 10 && !revealMode)
    {
        setRevealMode();
    }
    
    
};

void scHint::draw(){ //draw scene 1 here
    
    ofEnableDepthTest();
    ofEnableLighting();
    spotLight.enable();
    
    materialColor.setHue(0);
    material.setAmbientColor(materialColor);
    material.setDiffuseColor(materialColor);
    material.begin();
    
    
    for(int i=0; i<myCubes.size(); i++)
    {
        int line = i%3;
        int row = i/3;
        
        drawTexturedCube(i,
                         float(line*texture.getWidth()/3),
                         float((line+1)*texture.getWidth()/3),
                         float(row*texture.getHeight()/3),
                         float((row+1)*texture.getHeight()/3)
                         );
        drawTexturedCubeTEXT(i,
                             float(line*texture.getWidth()/3),
                             float((line+1)*texture.getWidth()/3),
                             float(row*texture.getHeight()/3),
                             float((row+1)*texture.getHeight()/3)
                             );
    }
    
    material.end();
    spotLight.disable();
    ofDisableLighting();
    spotLight.draw();

    
//    ofPushStyle();
//    // Style setup
//    ofSetColor(ofColor::black);
//    scScene::draw();
//    ofPopStyle();
    
};

//scene notifications
void scHint::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
    scScene::sceneWillAppear(fromScreen);
    
    ofEnableDepthTest();
    ofEnableLighting();
    
    timer = ofGetElapsedTimef();
};

//scene notifications
void scHint::sceneWillDisappear( ofxScene * toScreen ){
}





void scHint::drawTexturedCube(int i, float texCoordX_min, float texCoordX_max, float texCoordY_min, float texCoordY_max)
{
    ofPushMatrix();
    ofTranslate(myCubes[i].position.x, myCubes[i].position.y);
    ofRotate(myCubes[i].currentRot, 1, 0, 0);
    ofDrawBox(0, 0, 0, myCubes[i].size, myCubes[i].size, myCubes[i].size);
    
    texture.bind();
    ofPushMatrix();
    
    ofTranslate(-myCubes[i].size/2, -myCubes[i].size/2, myCubes[i].size/2+0.1);
    GLfloat tx0 = texCoordX_min;
    GLfloat ty0 = texCoordY_min;
    GLfloat tx1 = texCoordX_max;
    GLfloat ty1 = texCoordY_max;
    
    GLfloat px0 = 0.0f;
    GLfloat py0 = 0.0f;
    GLfloat px1 = myCubes[i].size;
    GLfloat py1 = myCubes[i].size;
    
    GLfloat tex_coords[] = {
        tx0,ty0,
        tx1,ty0,
        tx1,ty1,
        tx0,ty1
    };
    GLfloat verts[] = {
        px0,py0,
        px1,py0,
        px1,py1,
        px0,py1
    };
    
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glTexCoordPointer(2, GL_FLOAT, 0, tex_coords );
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, verts );
    glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    
    
    ofPopMatrix();
    
    ofSetColor(255);
    texture.unbind();
    ofPopMatrix();
    
}


void scHint::drawTexturedCubeTEXT(int i, float texCoordX_min, float texCoordX_max, float texCoordY_min, float texCoordY_max)
{
    ofPushMatrix();
    ofTranslate(myCubes[i].position.x, myCubes[i].position.y);
    
    
    GLfloat tx0 = texCoordX_min;
    GLfloat ty0 = texCoordY_min;
    GLfloat tx1 = texCoordX_max;
    GLfloat ty1 = texCoordY_max;
    
    GLfloat px0 = 0.0f;
    GLfloat py0 = 0.0f;
    GLfloat px1 = myCubes[i].size;
    GLfloat py1 = myCubes[i].size;
    
    GLfloat tex_coords[] = {
        tx0,ty0,
        tx1,ty0,
        tx1,ty1,
        tx0,ty1
    };
    GLfloat verts[] = {
        px0,py0,
        px1,py0,
        px1,py1,
        px0,py1
    };
    
    ofPushMatrix();
    ofRotate(myCubes[i].currentRot+180, 1, 0, 0);
    
    textImageFromFbo.getTexture().bind();
    ofPushMatrix();
    
    ofTranslate(-myCubes[i].size/2, -myCubes[i].size/2, (myCubes[i].size+0.1)/2);
    
    
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glTexCoordPointer(2, GL_FLOAT, 0, tex_coords );
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, verts );
    glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    
    
    ofPopMatrix();
    ofSetColor(255);
    textImageFromFbo.getTexture().unbind();
    ofPopMatrix();
    
    ofPopMatrix();
    
    
}


