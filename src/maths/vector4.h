#ifndef VECTOR4_H
#define VECTOR4_H

// Libraries
#include <math.h>
#include <assert.h>

namespace simple {

  class vector4 {

  public:

    // Components of the vector
    float x, y, z, w;

    // -------------------- Methods -------------------- //

    // Constructor
  vector4(float x=0, float y=0, float z=0, float w=0) : x(x), y(y), z(z), w(w) {}

    // Constructor
  vector4(const vector4& vector) : x(vector.x), y(vector.y), z(vector.z), w(vector.w) {}

    // + operator
    vector4 operator+(const vector4 &v) const {
      return vector4(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    // += operator
    vector4& operator+=(const vector4 &v) {
      x += v.x; y += v.y; z += v.z; w += v.w;
      return *this;
    }

    // - operator
    vector4 operator-(const vector4 &v) const {
      return vector4(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    // -= operator
    vector4& operator-=(const vector4 &v) {
      x -= v.x; y -= v.y; z -= v.z, w -=v.w;
      return *this;
    }

    // = operator
    vector4& operator=(const vector4& vector) {
      if (&vector != this) {
	x = vector.x;
	y = vector.y;
	z = vector.z;
	w = vector.w;
      }
      return *this;
    }

    // == operator
    bool operator==(const vector4 &v) const {
      return x == v.x && y == v.y && z == v.z && w == v.w;
    }

    // * operator
    vector4 operator*(float f) const {
      return vector4(f*x, f*y, f*z, f*w);
    }

    // *= operator
    vector4 &operator*=(float f) {
      x *= f; y *= f; z *= f; w *= f;
      return *this;
    }

    // / operator
    vector4 operator/(float f) const {
      assert(f!=0);
      float inv = 1.f / f;
      return vector4(x * inv, y * inv, z * inv, w * inv);
    }

    // /= operator
    vector4 &operator/=(float f) {
      assert(f!=0);
      float inv = 1.f / f;
      x *= inv; y *= inv; z *= inv; w *= inv;
      return *this;
    }

    // - operator
    vector4 operator-() const {
      return vector4(-x, -y, -z, -w);
    }

    // [] operator
    float &operator[](int i) {
      assert(i >= 0 && i <= 3);
      switch (i) {
      case 0: return x;
      case 1: return y;
      case 2: return z;
      case 3: return w;
      }
      return w;
    }

    // Dot product operator
    float dot(const vector4 &v) const {
      return x * v.x + y * v.y + z * v.z + w * v.w;
    }

    // Multiply two vectors by their components
    vector4 componentMul(const vector4 &v) const {
      return vector4(x * v.x, y * v.y, z * v.z, w * v.w);
    }

    // Clamp the values between 0 and 1
    vector4 clamp01() {
      if (x>1.f) x=1.f;
      else if (x<0.f) x=0.f;
      if (y>1.f) y=1.f;
      else if (y<0.f) y=0.f;
      if (z>1.f) z=1.f;
      else if (z<0.f) z=0.f;
      if (w>1.f) w=1.f;
      else if (w<0.f) w=0.f;
      return *this;
    }

    // Return the squared length of the vector
    float lengthSquared() const { return x * x + y * y + z * z + w * w; }

    // Return the length of the vector
    float length() const { return sqrt(lengthSquared()); }
  };

}

#endif //_VECTOR4_H
