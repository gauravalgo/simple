#ifndef VECTOR2_H
#define VECTOR2_H

// Libraries
#include <math.h>
#include <assert.h>

namespace simple {

  class vector2 {

  public:

    float x, y;

    // -------------------- Methods -------------------- //

    // Constructor
  vector2(float x=0, float y=0) : x(x), y(y) {}

    // Constructor
  vector2(const vector2& vector) : x(vector.x), y(vector.y) {}

    // + operator
    vector2 operator+(const vector2 &v) const {
      return vector2(x + v.x, y + v.y);
    }

    // += operator
    vector2& operator+=(const vector2 &v) {
      x += v.x; y += v.y;
      return *this;
    }

    // - operator
    vector2 operator-(const vector2 &v) const {
      return vector2(x - v.x, y - v.y);
    }

    // -= operator
    vector2& operator-=(const vector2 &v) {
      x -= v.x; y -= v.y;
      return *this;
    }

    // = operator
    vector2& operator=(const vector2& vector) {
      if (&vector != this) {
	x = vector.x;
	y = vector.y;
      }
      return *this;
    }

    // == operator
    bool operator==(const vector2 &v) const {
      return x == v.x && y == v.y;
    }

    // * operator
    vector2 operator*(float f) const {
      return vector2(f*x, f*y);
    }

    // *= operator
    vector2 &operator*=(float f) {
      x *= f; y *= f;
      return *this;
    }

    // / operator
    vector2 operator/(float f) const {
      assert(f!=0);
      float inv = 1.f / f;
      return vector2(x * inv, y * inv);
    }

    // /= operator
    vector2 &operator/=(float f) {
      assert(f!=0);
      float inv = 1.f / f;
      x *= inv; y *= inv;
      return *this;
    }

    // - operator
    vector2 operator-() const {
      return vector2(-x, -y);
    }

    // [] operator
    float &operator[](int i) {
      assert(i >= 0 && i <= 1);
      switch (i) {
      case 0: return x;
      case 1: return y;
      }
      return y;
    }

    // Normalize the vector and return it
    vector2 normalize() {
      float l = length();
      assert(l > 0);
      x /= l;
      y /= l;
      return *this;
    }

    // Clamp the vector values between 0 and 1
    vector2 clamp01() {
      if (x>1.f) x=1.f;
      else if (x<0.f) x=0.f;
      if (y>1.f) y=1.f;
      else if (y<0.f) y=0.f;
      return *this;
    }

    // Return the squared length of the vector
    float lengthSquared() const { return x*x + y*y; }

    // Return the length of the vector
    float length() const { return sqrt(lengthSquared()); }
  };

}

#endif
