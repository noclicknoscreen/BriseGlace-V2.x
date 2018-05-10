//
//  particule.hpp
//  bulletClass
//
//  Created by Blindsp0t on 30/04/2018.
//
//

#ifndef particule_h
#define particule_h

#include <stdio.h>
#include "MSAPhysics3D.h"

using namespace msa::physics;

class particule
{
    
    
public:
    
    //constructor
    Particle3D_ptr      me;
    particule(World3D_ptr _world, float _size=40, ofVec3f pos=ofVec3f(0,0,0), string _letter = "!");
    
    //////////////
    void addToWorld(World3D_ptr world);
    void draw();
    ofPoint getInitPos() {return initPos;};
    
private:
    
    int             	size;
    ofImage				texture;
    World3D_ptr         world;
    ofTrueTypeFont      font;
    string letter;
    ofPoint initPos;
    
};

#endif /* particule_h */
