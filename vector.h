#pragma once
/* Includes */

#include <cmath>


/* Class */

class Vector
{
public:
    Vector();
    Vector(double x, double y, double z);
    ~Vector();

    /* Operators */
    friend Vector operator + (const Vector &v1, const Vector &v2);
    friend Vector operator - (const Vector &v1, const Vector &v2);
    friend Vector operator * (const Vector &v, double k);
    friend Vector operator * (double k, const Vector &v);

    double dot(const Vector &v);
    void normalize();

    Vector transformMatrixToVector(const double m[16]);

    double getX() { return _x; }
    double getY() { return _y; }
    double getZ() { return _z; }

    void setX(double x) { _x = x; }
    void setY(double y) { _y = y; }
    void setZ(double z) { _z = z; }

    void set(double x, double y, double z);

private:
    double _x;
    double _y;
    double _z;
};

 