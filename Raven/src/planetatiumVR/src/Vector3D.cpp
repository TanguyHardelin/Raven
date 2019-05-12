#include "Vector3D.h"

using namespace std;

//Constructors:
Vector3D::Vector3D(double x,double y,double z){
    _x=x;
    _y=y;
    _z=z;
}
Vector3D::Vector3D(Vector3D const& v){
    _x=v.getX();
    _y=v.getY();
    _z=v.getZ();
}

//Methods:
void Vector3D::display() const{
    cout<<"("<<_x<<","<<_y<<","<<_z<<")"<<endl;
}
string Vector3D::toString() const{
    ostringstream strs_x;
    strs_x << _x;
    string x=strs_x.str();

    ostringstream strs_y;
    strs_y << _y;
    string y=strs_y.str();

    ostringstream strs_z;
    strs_z << _z;
    string z=strs_z.str();

    return "("+x+","+y+","+z+")";
}
double Vector3D::norm() const{
    return sqrt(_x*_x+_y*_y+_z*_z);
}
double Vector3D::scalarProduct(Vector3D const& v) const{
    return _x*v.getX()+_y*v.getY()+_z*v.getZ();
}
Vector3D Vector3D::projectOn(Vector3D const& a) const{
    Vector3D v(a);
    scalarProduct(v);
    v*=scalarProduct(v)/(v.norm()*v.norm());
    return v;
}
Vector3D Vector3D::normalize() const{
    double norm_of_vector=norm();
    Vector3D v(*this);
    v=v/norm_of_vector;
    return v;
}
double Vector3D::distanceOf(Vector3D const& v) const{
    return sqrt((_x*v.getX())*(_x*v.getX())+(_y*v.getY())*(_y*v.getY())+(_z*v.getZ())*(_z*v.getZ()));
}
Vector3D Vector3D::vectorProduct(Vector3D const& v) const{
    Vector3D a(0,0,0);

    a[0]=_y*v.getZ()-_z*v.getY();
    a[1]=_z*v.getX()-_x*v.getZ();
    a[2]=_x*v.getY()-_y*v.getX();

    return a;
}


//Operators:
double& Vector3D::operator[] (int index){
    switch(index){
        case 0:
        return _x;
        break;
        case 1:
        return _y;
        break;
        case 2:
        return _z;
        default:
        throw std::runtime_error( "Index > 2: Impossible in Vector3D");
    }
}
void Vector3D::operator=(Vector3D a){
    _x=a.getX();
    _y=a.getY();
    _z=a.getZ();
}
void Vector3D::operator+=(Vector3D const& a){
    _x+=a.getX();
    _y+=a.getY();
    _z+=a.getZ();
}
void Vector3D::operator-=(Vector3D const& a){
    _x-=a.getX();
    _y-=a.getY();
    _z-=a.getZ();
}
void Vector3D::operator*=(Vector3D const& a){
    _x*=a.getX();
    _y*=a.getY();
    _z*=a.getZ();
}
void Vector3D::operator/=(Vector3D const& a){
    _x/=a.getX();
    _y/=a.getY();
    _z/=a.getZ();
}

void Vector3D::operator+=(double a){
    _x+=a;
    _y+=a;
    _z+=a;
}
void Vector3D::operator-=(double a){
    _x-=a;
    _y-=a;
    _z-=a;
}
void Vector3D::operator*=(double a){
    _x*=a;
    _y*=a;
    _z*=a;
}
void Vector3D::operator/=(double a){
    _x/=a;
    _y/=a;
    _z/=a;
}

//Others operators:
bool operator==(Vector3D const& a, Vector3D const& b){
    bool ok=true;
    if(a.getX()!=b.getX())ok=false;
    if(a.getY()!=b.getY())ok=false;
    if(a.getZ()!=b.getZ())ok=false;

    return ok;
}
bool operator!=(Vector3D const&a, Vector3D const&b){
    return !(a==b);
}

Vector3D operator+(Vector3D  const&a, Vector3D const&b){
    Vector3D v(0,0,0);
    v[0]=a.getX()+b.getX();
    v[1]=a.getY()+b.getY();
    v[2]=a.getZ()+b.getZ();
    return v;
}
Vector3D operator-(Vector3D  const&a, Vector3D const&b){
    Vector3D v(0,0,0);
    v[0]=a.getX()-b.getX();
    v[1]=a.getY()-b.getY();
    v[2]=a.getZ()-b.getZ();
    return v;
}
Vector3D operator*(Vector3D  const&a, Vector3D const&b){
    Vector3D v(0,0,0);
    v[0]=a.getX()*b.getX();
    v[1]=a.getY()*b.getY();
    v[2]=a.getZ()*b.getZ();
    return v;
}
Vector3D operator/(Vector3D  const&a, Vector3D const&b){
    Vector3D v(0,0,0);
    v[0]=a.getX()/b.getX();
    v[1]=a.getY()/b.getY();
    v[2]=a.getZ()/b.getZ();
    return v;
}
Vector3D operator+(Vector3D  const&a,double k){
    Vector3D v(0,0,0);
    v[0]=a.getX()+k;
    v[1]=a.getY()+k;
    v[2]=a.getZ()+k;
    return v;
}
Vector3D operator-(Vector3D  const&a,double k){
    Vector3D v(0,0,0);
    v[0]=a.getX()-k;
    v[1]=a.getY()-k;
    v[2]=a.getZ()-k;
    return v;
}
Vector3D operator/(Vector3D  const&a,double k){
    Vector3D v(0,0,0);
    v[0]=a.getX()/k;
    v[1]=a.getY()/k;
    v[2]=a.getZ()/k;
    return v;
}
Vector3D operator*(Vector3D  const&a,double k){
    Vector3D v(0,0,0);
    v[0]=a.getX()*k;
    v[1]=a.getY()*k;
    v[2]=a.getZ()*k;
    return v;
}

//Other functions:
double norm(Vector3D const& v){
    return v.norm();
}                                 
double scalarProduct(Vector3D const& a,Vector3D const& b){
    return a.scalarProduct(b);
}
Vector3D project(Vector3D const& a,Vector3D const& b){
    return a.projectOn(b);
}
Vector3D normalize(Vector3D const& v){
    return v.normalize();
}
double distance(Vector3D const& a,Vector3D const& b){
    return a.distanceOf(b);
}
Vector3D vectorProduct(Vector3D const& a,Vector3D const& b){
    return a.vectorProduct(b);
}