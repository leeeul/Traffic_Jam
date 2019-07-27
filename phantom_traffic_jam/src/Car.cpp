#include "Car.hpp"
#include "CarController.hpp"
CarController* Car::controller = nullptr;

float Car::maxVel = 0;
float Car::force = 0;
float Car::safeDist = 0;

Car::Car(float rad, float angle)
         :angle(angle),
         rad(rad),
         acc(0),
         vel(0),
         frontCar(nullptr),
         accDiff(ofRandom(1.,1.08))
{
}
         
Car::Car(float rad)
:Car(rad, ofRandom(TWO_PI))
{
}

Car::Car(){}

void Car::addForce(float force){
    acc = force;
}

float Car::getNextAngle(float vel){
    float totalLeng = rad*TWO_PI; // approx 3000
    float dAngle = TWO_PI*vel/totalLeng;
    float result = angle + dAngle;
    
    while(result>=TWO_PI){
        result -= TWO_PI;
    }
    
    return result;
}

float get_angleBetween(Car* mine, Car* other){
    
    float myAng = mine->getAngle();
    float otherAng = other->getAngle();
    
    float d1 = otherAng - myAng;
    float d2 = otherAng + TWO_PI - myAng;
    float md;
    if(d1*d2<0){
        md = max(d1, d2);
    }else{
        md = min(d1, d2);
    }
    
    return md;
}

bool Car::isSafe(){
//    if(frontCar==nullptr){
        frontCar = controller->findFrontCar(this);
//    }
    
    float a = get_angleBetween(this, frontCar);
    float d = a*rad;
    if(d<safeDist) safe = false;
    else safe = true;
    return safe;
}

void Car::update(){
    float dt = ofGetLastFrameTime();
    
    if(isSafe()==false && vel>0){
        float brake = (maxVel*maxVel)/(2.0*force*0.5*safeDist);
        acc = -force*brake; // you should multiply 10
    }else{
        acc = force;
    }
    
    acc *= accDiff;
    vel = ofClamp(vel + acc*dt, 0, maxVel*accDiff);
    angle = getNextAngle(vel*dt);
}

ofVec2f Car::getXY(){
    ofVec2f center =  controller->getCenter();
    float x = sin(angle)*rad;
    float y = cos(angle)*rad;
    
    return center + ofVec2f(x, y);
}

void Car::draw(){
    ofVec2f xy = getXY();
    if(safe) ofSetColor(255,255,255);
    else ofSetColor(255,0,0);
    
    ofVec2f mouse = ofVec2f(ofGetMouseX(), ofGetMouseY());
    float r = 5;
    bool underMouse = mouse.distance(xy)<r?true:false;
    if(underMouse){
        ofSetColor(0,0,255);
        ofDrawEllipse(frontCar->getXY(), r*2.5, r*2.5);
        ofSetColor(0,255,0);
    }
    ofDrawEllipse(xy, r*2, r*2);
}

void Car::setMVel(float f){
    maxVel = f;
}

void Car::setForce(float f){
    force = f;
}

void Car::setSafeDist(float f){
    safeDist = f;
}

float Car::getAngle() const{
    return angle;
}

void Car::setController(CarController* cc){
    controller = cc;
}

bool Car::getSafe(){
    return safe;
}

float Car::getVel(){
    return vel;
}
