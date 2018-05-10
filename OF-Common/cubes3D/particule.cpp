//
//  particule.cpp
//  bulletClass
//
//  Created by Blindsp0t on 30/04/2018.
//
//

#include "particule.h"
#include "ofMain.h"

#define PARTICULES_WIDTH 40;
#define PARTICULES_HEIGHT 40;
#define PARTICULES_DEPTH 40;

particule::particule(World3D_ptr _world, float _size, ofVec3f pos, string _letter)
{
    world = _world;
    size = _size;
    me = Particle3D::create();
    world->addParticle(me);
    me->moveTo(pos);
    me->setRadius(size/2);
    texture.load("contreplaque.png");
    font.load("Avenir.ttc", 34);
    letter = _letter;
    initPos = pos;
}


void particule::draw()
{
    //apply texture
    ofEnableNormalizedTexCoords();
    texture.bind();
    
    //Shadows
    float alpha = ofMap(me->getPosition().y, -ofGetHeight() * 1.5, ofGetHeight(), 0, 1);
    if(alpha>0) {
        glPushMatrix();
        glTranslatef(me->getPosition().x, ofGetHeight(), me->getPosition().z);
        glRotatef(-90, 1, 0, 0);
        glColor4f(0, 0, 0, alpha * alpha * alpha * alpha);
        
        float r = me->getRadius() * alpha;
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(-r, -r);
        glTexCoord2f(1, 0); glVertex2f(r, -r);
        glTexCoord2f(1, 1); glVertex2f(r, r);
        glTexCoord2f(0, 1); glVertex2f(-r, r);
        glEnd();
        glPopMatrix();
    }
    
    
    //3d box
    ofSetColor(255);
    
    ofFill();
    ofDrawBox(me->getPosition().x, me->getPosition().y, me->getPosition().z, size, size, size);
    
    ofNoFill();
    ofSetColor(0);
    ofDrawBox(me->getPosition().x, me->getPosition().y, me->getPosition().z, size, size, size);
    ofFill();
    
    texture.unbind();
    ofDisableNormalizedTexCoords();
    
    float textHeight, textWidth;
    textWidth = font.getStringBoundingBox(letter, 0, 0).getWidth();
    textHeight = font.getStringBoundingBox(letter, 0, 0).getHeight();
    
    ofSetColor(0);
    ofPushMatrix();
    ofTranslate(me->getPosition().x- textWidth/2, me->getPosition().y + textHeight/2, me->getPosition().z+(size/2)+1);
    
    font.drawString(letter, 0, 0);
    
    ofPopMatrix();
};
