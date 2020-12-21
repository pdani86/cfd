#ifndef CFD_H
#define CFD_H

#include <vector>
#include <cmath>

class CFD
{
public:
    struct vec3 {
    public:
        vec3(double x = 0.0, double y = 0.0, double z = 0.0) {v[0] = x; v[1] = y; v[2] = z;}
        vec3(const vec3&) = default;

        double X() const {return v[0];}
        double Y() const {return v[1];}
        double Z() const {return v[2];}
        double lengthSqr() const {return v[0]*v[0]+v[1]*v[1]+v[2]*v[2];}
        double length() const {return std::sqrt(lengthSqr());}

        vec3 operator-(const vec3& other) const {return vec3(v[0]-other.v[0],v[1]-other.v[1],v[2]-other.v[2]);}
        vec3 operator+(const vec3& other) const {return vec3(v[0]+other.v[0],v[1]+other.v[1],v[2]+other.v[2]);}
        vec3& operator+=(const vec3& other) {v[0]+=other.v[0]; v[1]+=other.v[1]; v[2]+=other.v[2]; return *this;}
        vec3 operator*(double k) const {return vec3(k*v[0], k*v[1], k*v[2]);}
        vec3& operator=(const vec3&) = default;
        static double dot(const vec3& v1, const vec3& v2) {return v1.v[0]*v2.v[0]+v1.v[1]*v2.v[1]+v1.v[2]*v2.v[2];}
    public:
        double v[3];
    };
    struct ElemState
    {
        vec3 velocity;

    };

    CFD(int w = 100, int h = 100, int d = 10);
    void iterate(double dt = 0.01);
    std::vector<ElemState> getXYPlaneData(int z = 1);
public:
    std::vector<ElemState> data;
    std::vector<vec3> tmpDvData;
    int width;
    int height;
    int depth;
};

#endif // CFD_H
