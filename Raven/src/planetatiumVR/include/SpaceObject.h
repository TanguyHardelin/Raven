#ifndef SPACE_OBJECT_H
#define SPACE_OBJECT_H

#include <iostream>
#include <QString>
#include "Vector3D.h"

class SpaceObject{
    public:
        SpaceObject(QString name,double mass,Vector3D position,Vector3D speed,Vector3D acceleration,double radius);

        //Getter:
        inline QString getName(){return _name;}
        inline double  getMass(){return _mass;}
        inline double  isContinue(){return _continue_simulation;}
        inline double getRadius(){return _radius;}
        inline Vector3D getPosition(){return _position;}
        inline Vector3D getSpeed(){return _speed;}
        inline Vector3D getAcceleration(){return _acceleration;}

        inline void stopSimulation(){
            _continue_simulation=false;
            _speed = Vector3D(0,0,0);
            _acceleration = Vector3D(0,0,0);
            _force_accum = Vector3D(0,0,0);
        }
                
        void compute(double delta_t);
        void addForce(Vector3D force);

    protected:
        QString _name;
        double _mass;
        Vector3D _position,_speed,_acceleration,_force_accum;
        double _radius;
        bool _continue_simulation;

};

#endif