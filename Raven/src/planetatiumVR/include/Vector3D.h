#ifndef VECTORD_H
#define VECTORD_H

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

class Vector3D{
    public:
    //Constructors:
    Vector3D(double x,double y,double z);
    Vector3D(Vector3D const& v);

    //Getters:
    inline double getX() const{return _x;};
    inline double getY() const{return _y;};
    inline double getZ() const{return _z;};

    //Setters:
    inline void setX(double x){_x=x;};
    inline void setY(double y){_y=y;};
    inline void setZ(double z){_z=z;};

    //Methods:
    void display() const;
    std::string toString() const;

    double norm() const;
    double scalarProduct(Vector3D const& v) const;
    Vector3D projectOn(Vector3D const& v) const;
    Vector3D normalize() const;
    double distanceOf(Vector3D const& v) const;
    Vector3D vectorProduct(Vector3D const& v) const;


    //Operators:
    double& operator[] (int index);

    void operator=(Vector3D a);

    void operator+=(Vector3D const& a);
    void operator-=(Vector3D const& a);
    void operator*=(Vector3D const& a);
    void operator/=(Vector3D const& a);

    void operator+=(double a);
    void operator-=(double a);
    void operator*=(double a);
    void operator/=(double a);

    protected:
    double  _x,_y,_z;
};

//Others operators:
bool operator==(Vector3D const& a, Vector3D const& b);
bool operator!=(Vector3D const&a, Vector3D const&b);

Vector3D operator+(Vector3D  const&a, Vector3D const&b);
Vector3D operator-(Vector3D  const&a, Vector3D const&b);
Vector3D operator*(Vector3D  const&a, Vector3D const&b);
Vector3D operator/(Vector3D  const&a, Vector3D const&b);
Vector3D operator+(Vector3D  const&a, double k);
Vector3D operator-(Vector3D  const&a, double k);
Vector3D operator/(Vector3D  const&a, double k);
Vector3D operator*(Vector3D  const&a, double k);

//Other functions:
double norm(Vector3D const& v);                                         //Return the norm of vector v
double scalarProduct(Vector3D const& a,Vector3D const& b);              //Return the scalar product of a and b
Vector3D project(Vector3D const& a,Vector3D const& b);                  //Return a projected on b
Vector3D normalize(Vector3D const& v);                                  //Return v normalized
double distance(Vector3D const& a,Vector3D const& b);                   //Return distance between a and b
Vector3D vectorProduct(Vector3D const& a,Vector3D const& b);            //Return the vector product of a and b

#endif