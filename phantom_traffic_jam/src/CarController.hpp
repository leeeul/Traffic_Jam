#ifndef CarController_hpp
#define CarController_hpp

#include <stdio.h>
#include "Car.hpp"

class CarController{
    static CarController* instance;
    Car** list;
    int size;
    int rad;
    ofVec2f center;
    
    ofColor bgCol;
    ofColor roadCol;
    
    CarController(int size, float rad, ofColor bgCol, ofColor roadCol);
    void eraseInstance();
    void eraseList();
public:
    static CarController* getInstance(int size, float rad, ofColor bgCol, ofColor roadCol);
    void setMaxVal(float maxAcc, float maxVel, float force, float sd);
    void update();
    void draw();
    Car* findFrontCar(const Car* mine);
    
    int getJammed();
    float getAVel();
    ofVec2f getCenter();
    virtual ~CarController();
};

#endif /* CarController_hpp */

