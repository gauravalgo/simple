#ifndef VECTOR2_H
#define VECTOR2_H

// Libraries
#include <math.h>
#include <assert.h>

namespace simple {

  class vec2 {

  public:

    float x, y;

    // Constructor
  vec2(float x=0, float y=0) : x(x), y(y) {}

    // Constructor
  vec2(const vec2& vector) : x(vector.x), y(vector.y) {}

    // + operator
    vec2 operator+(const vec2 &v) const {
      return vec2(x + v.x, y + v.y);
    }

    // += operator
    vec2& operator+=(const vec2 &v) {
      x += v.x; y += v.y;
      return *this;
    }

    // - operator
    vec2 operator-(const vec2 &v) const {
      return vec2(x - v.x, y - v.y);
    }

    // -= operator
    vec2& operator-=(const vec2 &v) {
      x -= v.x; y -= v.y;
      return *this;
    }

    // = operator
    vec2& operator=(const vec2& vector) {
      if (&vector != this) {
	x = vector.x;
	y = vector.y;
      }
      return *this;
    }

    // == operator
    bool operator==(const vec2 &v) const {
      return x == v.x && y == v.y;
    }

    // * operator
    vec2 operator*(float f) const {
      return vec2(f*x, f*y);
    }

    // *= operator
    vec2 &operator*=(float f) {
      x *= f; y *= f;
      return *this;
    }

    // / operator
    vec2 operator/(float f) const {
      assert(f!=0);
      float inv = 1.f / f;
      return vec2(x * inv, y * inv);
    }

    // /= operator
    vec2 &operator/=(float f) {
      assert(f!=0);
      float inv = 1.f / f;
      x *= inv; y *= inv;
      return *this;
    }

    // - operator
    vec2 operator-() const {
      return vec2(-x, -y);
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
    vec2 normalize() {
      float l = length();
      assert(l > 0);
      x /= l;
      y /= l;
      return *this;
    }

    // Clamp the vector values between 0 and 1
    vec2 clamp01() {
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
