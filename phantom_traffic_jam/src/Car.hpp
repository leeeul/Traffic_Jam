#ifndef Car_hpp
#define Car_hpp

#include <stdio.h>
#include "ofMain.h"

class CarController;

class Car{
    float angle;
    float acc, vel;
    float accDiff;
    static float maxVel;
    static float force;
    static float safeDist;
    float rad;
    bool safe;
    
    Car* frontCar;
    static CarController* controller;
    float getNextAngle(float vel);
    ofVec2f getXY();
    
public:
    Car(float rad);
    Car(float rad, float angle);
    Car();
    void addForce(float force);
    void update();
    void draw();
    void setMVel(float);
    void setForce(float);
    void setSafeDist(float);

    bool isSafe();
    bool getSafe();
    float getVel();
    
    float getAngle() const;
    static void setController(CarController*);
};

#endif /* Car_hpp */
