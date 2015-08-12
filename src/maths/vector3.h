#ifndef VECTOR3_H
#define VECTOR3_H

// Libraries
#include <cmath>
#include <cassert>
#include <limits>

namespace simple {

class vector3 {

    public:

        // Components of the vector
        float x, y, z;

        // -------------------- Methods -------------------- //

        // Constructor
        vector3(float x=0, float y=0, float z=0) : x(x), y(y), z(z) {}

        // Constructor
        vector3(const vector3& vector) : x(vector.x), y(vector.y), z(vector.z) {}

        // Constructor
        ~vector3() {}

        // = operator
        vector3& operator=(const vector3& vector) {
            if (&vector != this) {
                x = vector.x;
                y = vector.y;
                z = vector.z;
            }
            return *this;
        }

        // + operator
        vector3 operator+(const vector3 &v) const {
            return vector3(x + v.x, y + v.y, z + v.z);
        }

        // += operator
        vector3& operator+=(const vector3 &v) {
            x += v.x; y += v.y; z += v.z;
            return *this;
        }

        // - operator
        vector3 operator-(const vector3 &v) const {
            return vector3(x - v.x, y - v.y, z - v.z);
        }

        // -= operator
        vector3& operator-=(const vector3 &v) {
            x -= v.x; y -= v.y; z -= v.z;
            return *this;
        }

        // == operator
        bool operator==(const vector3 &v) const {
            return x == v.x && y == v.y && z == v.z;
        }

        // != operator
        bool operator!=(const vector3 &v) const {
          return !( *this == v );
        }

        // * operator
        vector3 operator*(float f) const {
            return vector3(f*x, f*y, f*z);
        }

        // *= operator
        vector3 &operator*=(float f) {
            x *= f; y *= f; z *= f;
            return *this;
        }

        // / operator
        vector3 operator/(float f) const {
            assert(f > std::numeric_limits<float>::epsilon() );
            float inv = 1.f / f;
            return vector3(x * inv, y * inv, z * inv);
        }

        // /= operator
        vector3 &operator/=(float f) {
            assert(f > std::numeric_limits<float>::epsilon());
            float inv = 1.f / f;
            x *= inv; y *= inv; z *= inv;
            return *this;
        }

        // - operator
        vector3 operator-() const {
            return vector3(-x, -y, -z);
        }

        // [] operator
        float &operator[](int i) {
            assert(i >= 0 && i <= 2);
            switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            }
            return z;
        }

        // [] operator
        const float &operator[](int i) const {
            assert(i >= 0 && i <= 2);
            switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            }
            return z;
        }

        // Cross product operator
        vector3 cross(const vector3 &v) const{
            return vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
        }

        // Dot product operator
        float dot(const vector3 &v) const{
            return x * v.x + y * v.y + z * v.z;
        }

        // Normalize the vector and return it
        vector3 normalize() {
            float l = length();
            if(l < std::numeric_limits<float>::epsilon() ) {
              assert(false);
              }
            x /= l;
            y /= l;
            z /= l;
            return *this;
        }

        bool isNull() const {
          return( x == 0. && y == 0. && z == 0. );
        }

        // Clamp the values between 0 and 1
        vector3 clamp01() {
            if (x>1.f) x=1.f;
            else if (x<0.f) x=0.f;
            if (y>1.f) y=1.f;
            else if (y<0.f) y=0.f;
            if (z>1.f) z=1.f;
            else if (z<0.f) z=0.f;
            return *this;
        }

        // Return the squared length of the vector
        float lengthSquared() const { return x*x + y*y + z*z; }

        // Return the length of the vector
        float length() const { return sqrt(lengthSquared()); }
};

inline vector3 operator*(float f, const vector3 & o) {
  return o*f;
}

}

#endif
