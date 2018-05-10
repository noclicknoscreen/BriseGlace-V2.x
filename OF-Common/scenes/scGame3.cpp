//
//  scGame3.cpp
//  sceneManager-Rough
//
//  Created by Sébastien Albert on 04/05/2018.
//
//

#include "scGame3.h"

void scGame3::setup(){
    
    scScene::setup();
    ofLogNotice() << "Game 3 : Setup !";
    myTitle = "Game 3 : Boggle";
    
    //setup the 3D scene
    initScene();
    
    // Player manager events
    ofAddListener(myPlayerManager->someoneSpoke,this,&scGame3::someoneSpoke);
    
    //test particles ;)
    //createTestParticules();
    
    //TODO : word to be taken from enigma Singleton
    wantedWord = "BONHEUR";
    createParticules(wantedWord);
};


void scGame3::update(float dt){
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    world->update();
};

void scGame3::draw(){
    
    
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    ofPushMatrix();
    
    ofTranslate(width/2, 0, -width / 3);	 // center scene
    ofRotate(rotX, 0, 1, 0);                 // rotate scene
    ofRotate(rotY, 1, 0, 0);                 // rotate scene
    
    //applyRandomForces();  //makes the screen and walls move with forces applied
    drawRoom();
    drawSprings();
    
    for(int i=0; i<myParticules.size(); i++) {
        Particle3D_ptr p = myParticules[i]->me;
        myParticules[i]->draw();
    }
    
    ofPopMatrix();
    ofDisableDepthTest();
    ofDisableLighting();
    
    
    ofPushStyle();
    // Style setup
    ofSetColor(ofColor::blue);
    
    //scScene::draw();            // Draw title
    myPlayerManager->draw();    // Draw players
    drawCenterText(myPlayerManager->getLastMessage(), 0, 50); // Draw last message
    
    ofPopStyle();
    
};


// Speaking event
void scGame3::someoneSpoke(player & _player){
    scScene::someoneSpoke(_player);
   
    if(toUpperCase(_player.getLastMessage()) == toUpperCase(wantedWord))
    {
        cout << "c'est gagné !!! " << endl;
    }
    else
    {
        addRandomForce(FORCE_AMOUNT * 3);
    }
    
}

//scene notifications
void scGame3::sceneWillAppear( ofxScene * fromScreen ){
    // reset our scene when we appear
    setupLighting();
    
};

//scene notifications
void scGame3::sceneWillDisappear( ofxScene * toScreen ){
}

string scGame3::toUpperCase(string str)
{
    string strUpper = "";
    
    for( int i=0; i<str.length(); i++ )
    {
        strUpper += toupper( str[ i ] );
    }
    return strUpper;
}  





//--------------------------------------------------------------
void scGame3::keyPressed(int key){
    
    switch(key) {
        case ' ': myParticules[0]->me->makeFree(); break;
        case 't':
        {
            for(int i=0; i<myParticules.size(); i++)
                myParticules[i]->me->makeFree();
            
            break;
        }
        case 'f': addRandomForce(FORCE_AMOUNT); break;
        case 'F': addRandomForce(FORCE_AMOUNT * 3); break;
            
        case 'm': myParticules[0]->me->moveTo(ofVec3f(-400,100,100)); myParticules[0]->me->makeFixed(); break;
            
        case 's':
        {
            
            for(int i=0; i<myParticules.size(); i++)
            {
                particule* ppp = new particule(world, 1, myParticules[i]->getInitPos(), "S");
                ppp->me->makeFixed();
                ppp->me->enablePassiveCollision();
                //myParticules.push_back(ppp);
                world->makeSpring(ppp->me, myParticules[i]->me, SPRING_MIN_STRENGTH, 300);
            }
            break;
        }
            
        case 'S':
        {
            for(int i=0; i<world->numberOfSprings(); i++)
            {
                world->getSpring(i)->kill();
            }
            break;
        }
    }
}


//--------------------------------------------------------------
void scGame3::initScene() {
    
    ofBackground(255, 255, 255);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    world = World3D::create();
    world->setGravity(ofVec3f(0, GRAVITY, 0));
    world->setWorldSize(ofVec3f(-width/2, -height, -width/(2*depthDivide)), ofVec3f(width/2, height, width/(2*depthDivide)));
    world->setSectorCount(SECTOR_COUNT);
    world->enableCollision();
}

//--------------------------------------------------------------
void scGame3::setupLighting() {
    
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0, (float)height/2, 0.0, 0.0 };
    glShadeModel(GL_SMOOTH);
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
}


//--------------------------------------------------------------
void scGame3::drawRoom()
{
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    // draw right wall
    glColor3f(.9, 0.9, 0.9);		glVertex3f(width/2, height+1, width/2);
    glColor3f(1, 1, 1);				glVertex3f(width/2, -height, width/2);
    glColor3f(0.95, 0.95, 0.95);	glVertex3f(width/2, -height, -width/2);
    glColor3f(.85, 0.85, 0.85);		glVertex3f(width/2, height+1, -width/2);
    
    // back wall
    glColor3f(.9, 0.9, 0.9);		glVertex3f(width/2, height+1, -width/(2*depthDivide));
    glColor3f(1, 1, 1);				glVertex3f(width/2, -height, -width/(2*depthDivide));
    glColor3f(0.95, 0.95, 0.95);	glVertex3f(-width/2, -height, -width/(2*depthDivide));
    glColor3f(.85, 0.85, 0.85);		glVertex3f(-width/2, height+1, -width/(2*depthDivide));
    
    // left wall
    glColor3f(.9, 0.9, 0.9);		glVertex3f(-width/2, height+1, -width/2);
    glColor3f(1, 1, 1);				glVertex3f(-width/2, -height, -width/2);
    glColor3f(0.95, 0.95, 0.95);	glVertex3f(-width/2, -height, width/2);
    glColor3f(.85, 0.85, 0.85);		glVertex3f(-width/2, height+1, width/2);
    
    // front wall
    /*
     glColor3f(0.95, 0.95, 0.95);	glVertex3f(width/2, -height, width/2);
     glColor3f(.85, 0.85, 0.85);		glVertex3f(width/2, height+1, width/2);
     glColor3f(.9, 0.9, 0.9);		glVertex3f(-width/2, height+1, width/2);
     glColor3f(1, 1, 1);				glVertex3f(-width/2, -height, width/2);
     */
    
    // floor
    glColor3f(.8, 0.8, 0.8);
    glVertex3f(width/2, height+1, width/2);
    glVertex3f(width/2, height+1, -width/2);
    glVertex3f(-width/2, height+1, -width/2);
    glVertex3f(-width/2, height+1, width/2);
    glEnd();
    
}


//--------------------------------------------------------------
void scGame3::drawSprings()
{
    // draw springs
    ofSetColor(128);
    for(int i=0; i<world->numberOfSprings(); i++) {
        Spring3D_ptr spring     = world->getSpring(i);
        Particle3D_ptr a        = spring->getA();
        Particle3D_ptr b        = spring->getB();
        ofVec3f vec             = b->getPosition() - a->getPosition();
        float dist              = vec.length();
        float angle             = acos( vec.z / dist ) * RAD_TO_DEG;
        if(vec.z <= 0 ) angle   = -angle;
        float rx                = -vec.y * vec.z;
        float ry                =  vec.x * vec.z;
        
        ofPushMatrix();
        ofTranslate(a->getPosition());
        ofRotate(angle, rx, ry, 0.0);
        float size  = ofMap(spring->getStrength(), SPRING_MIN_STRENGTH, SPRING_MAX_STRENGTH, SPRING_MIN_WIDTH, SPRING_MAX_WIDTH);
        
        ofScale(size, size, dist);
        ofTranslate(0, 0, 0.5);
        ofDrawBox(1);
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void scGame3::createTestParticules()
{
    particule* pp = new particule(world, 100, ofVec3f(-400,-250,100), "S");
    pp->me->makeFixed();
    myParticules.push_back(pp);
    
    particule* pp2 = new particule(world, 100, ofVec3f(-200,-250,100), "A" );
    pp2->me->makeFixed();
    myParticules.push_back(pp2);
    
    particule* pp3 = new particule(world, 100, ofVec3f(0,-250,100), "L");
    pp3->me->makeFixed();
    myParticules.push_back(pp3);
    
    particule* pp4 = new particule(world, 100, ofVec3f(200,-250,100), "U");
    pp4->me->makeFixed();
    myParticules.push_back(pp4);
    
    particule* pp5 = new particule(world, 100, ofVec3f(400,-250,100), "T");
    pp5->me->makeFixed();
    myParticules.push_back(pp5);
    
}

//--------------------------------------------------------------
void scGame3::createParticules(string _word)
{
    for (int i=0; i<_word.size(); i++)
    {
        particule* pp = new particule(world, 100, ofVec3f(ofRandom(-ofGetWidth()/2, ofGetWidth()/2),-250,100), ofToString(_word[i]));
        pp->me->makeFree();
        
        //adjust mass and bounce
        pp->me->setMass(15);
        pp->me->setBounce(0.7);
        
        myParticules.push_back(pp);
    }
}


//--------------------------------------------------------------
void scGame3::applyRandomForces()
{
    if(forceTimer) {
        float translateMax = forceTimer;
        glTranslatef(ofRandom(-translateMax, translateMax), ofRandom(-translateMax, translateMax), ofRandom(-translateMax, translateMax));
        forceTimer--;
    }
}

//--------------------------------------------------------------
void scGame3::addRandomForce(float f) {
    forceTimer = f;
    for(int i=0; i<world->numberOfParticles(); i++) {
        Particle3D_ptr p = world->getParticle(i);
        if(p->isFree()) p->addVelocity(ofVec3f(ofRandom(-f, f), ofRandom(-f, f), ofRandom(-f, f)));
    }
}


