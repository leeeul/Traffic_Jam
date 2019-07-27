#include "CarController.hpp"
#define CC CarController

CC* CC::instance = nullptr;

CC::CC(int size, float rad, ofColor bgCol, ofColor roadCol)
:size(size),
rad(rad),
center(ofVec2f(ofGetWidth()*0.5, ofGetHeight()*0.5)),
bgCol(bgCol),
roadCol(roadCol)
{
    list = new Car*[size];
    float gap = TWO_PI/size;
    for(int i=0; i<size; ++i){
        list[i] = new Car(rad, i*gap);
    }
    
}

ofVec2f CC::getCenter(){
    return this->center;
}

CC* CC::getInstance(int size, float rad, ofColor bgCol, ofColor roadCol){
    if(instance == nullptr){
        instance = new CC(size, rad, bgCol, roadCol);
    }
    
    Car::setController(instance);
    
    return instance;
}

CC::~CC(){
    eraseInstance();
    eraseList();
}

void CC::eraseInstance(){
    if(instance == nullptr) return;
    
    delete instance;
    instance = nullptr;
}

void CC::eraseList(){
    if(list == nullptr) return;
    
    for(int i=0; i<size; ++i){
        delete list[i];
        list[i] = nullptr;
    }
    
    delete list;
    list = nullptr;
}

void CC::setMaxVal(float maxAcc, float maxVel, float force, float sd){
    if(list==nullptr || list[0]==nullptr) return;
    list[0]->setMVel(maxVel);
    list[0]->setForce(force);
    list[0]->setSafeDist(sd);
}

void CC::update(){
    for(int i=0; i<size; ++i){
        list[i]->update();
    }
}

void CC::draw(){
    float width = 30;
    ofSetCircleResolution(100);
    ofSetColor(roadCol);
    ofDrawEllipse(center, rad*2+width, rad*2+width);
    ofSetColor(bgCol);
    ofDrawEllipse(center, rad*2-width, rad*2-width);
    
    ofSetCircleResolution(10);
    for(int i=0; i<size; ++i){
        list[i]->draw();
    }
}

Car* CC::findFrontCar(const Car* mine){
    float myAng = mine->getAngle();
    float globalMd = TWO_PI;
    int idx;
    for(int i=0; i<size; ++i){
        Car* other = list[i];
        if(other == mine){
            continue;
        }
        float otherAng = other->getAngle();
        
        float d1 = otherAng - myAng;
        float d2 = otherAng + TWO_PI - myAng;
        float md;
        if(d1*d2<0){
            md = max(d1, d2);
        }else{
            md = min(d1, d2);
        }
        
        if(md<globalMd){
            globalMd = md;
            idx = i;
        }
    }
    return list[idx];
}

int CC::getJammed(){
    int count = 0;
    for(int i=0; i<size; ++i){
        if(list[i]->getSafe() == false){
            ++count;
        }
    }
    return count;
}

float CC::getAVel(){
    float totalVel = 0;
    for(int i=0; i<size; ++i){
        totalVel += list[i]->getVel();
    }
    return totalVel/size;
}





