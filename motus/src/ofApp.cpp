#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    initScene();
    setupLighting();
    
    //test particles ;)
    createTestParticules();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    world->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
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
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
            
        case 'a': {
            //attraction point
            particule* ppp = new particule(world, 1, myParticules[0]->getInitPos(), "S");
            ppp->me->makeFixed();
            ppp->me->enablePassiveCollision();
            myParticules.push_back(ppp);
            
            myParticules[0]->me->setBounce(0);
            world->makeAttraction(ppp->me, myParticules[0]->me, 50);
            break;
        }
            
        case 'A': {
            //destroy attraction forces
            for(int i=0; i<world->numberOfAttractions(); i++) world->getAttraction(i)->kill();
            break;
        }
            
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
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

    rotX = (x - mouseClickPos.x)/2;
    rotY = (mouseClickPos.y - y)/2;
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    mouseClickPos = ofPoint(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    mouseClickPos = ofPoint(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}


//--------------------------------------------------------------
void ofApp::initScene() {
    
    ofBackground(255, 255, 255);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    world = World3D::create();
    world->setGravity(ofVec3f(0, GRAVITY, 0));
    world->setWorldSize(ofVec3f(-width/2, -height, -width/2), ofVec3f(width/2, height, width/2));
    world->setSectorCount(SECTOR_COUNT);
    world->enableCollision();
}

//--------------------------------------------------------------
void ofApp::setupLighting() {
    
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
void ofApp::drawRoom()
{
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    // draw right wall
    glColor3f(.9, 0.9, 0.9);		glVertex3f(width/2, height+1, width/2);
    glColor3f(1, 1, 1);				glVertex3f(width/2, -height, width/2);
    glColor3f(0.95, 0.95, 0.95);	glVertex3f(width/2, -height, -width/2);
    glColor3f(.85, 0.85, 0.85);		glVertex3f(width/2, height+1, -width/2);
    
    // back wall
    glColor3f(.9, 0.9, 0.9);		glVertex3f(width/2, height+1, -width/2);
    glColor3f(1, 1, 1);				glVertex3f(width/2, -height, -width/2);
    glColor3f(0.95, 0.95, 0.95);	glVertex3f(-width/2, -height, -width/2);
    glColor3f(.85, 0.85, 0.85);		glVertex3f(-width/2, height+1, -width/2);
    
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
void ofApp::drawSprings()
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
void ofApp::createTestParticules()
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
void ofApp::applyRandomForces()
{
    if(forceTimer) {
        float translateMax = forceTimer;
        glTranslatef(ofRandom(-translateMax, translateMax), ofRandom(-translateMax, translateMax), ofRandom(-translateMax, translateMax));
        forceTimer--;
    }
}

//--------------------------------------------------------------
void ofApp::addRandomForce(float f) {
    forceTimer = f;
    for(int i=0; i<world->numberOfParticles(); i++) {
        Particle3D_ptr p = world->getParticle(i);
        if(p->isFree()) p->addVelocity(ofVec3f(ofRandom(-f, f), ofRandom(-f, f), ofRandom(-f, f)));
    }
}



