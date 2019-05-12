#include "SpaceObject.h"

using namespace std;

SpaceObject::SpaceObject(QString name,double mass,Vector3D position,Vector3D speed,Vector3D acceleration,double radius):_name(name),_mass(mass),_position(position),_speed(speed),_acceleration(acceleration),_force_accum(0,0,0),_radius(radius){
    _continue_simulation = true;

}

void SpaceObject::compute(double delta_t){
    //Update acceleration
    _acceleration += _force_accum * delta_t / _mass;
    //Update speed
    _speed += _acceleration * delta_t;
    
    //Update position
    _position += _speed * delta_t;
    //cout<<"Name: "<<_name.toStdString()<<" Position"<<_position.toString()<<endl;
}
void SpaceObject::addForce(Vector3D force){
    _force_accum+=force;
}