/*******************************************************************************
 * Copyright 2015 See AUTHORS file.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#ifndef VECTOR3_H
#define VECTOR3_H

// Libraries
#include <cmath>
#include <cassert>
#include <limits>

namespace simple {

  class vec3 {

  public:
    float x, y, z;

  vec3(float x=0, float y=0, float z=0) : x(x), y(y), z(z) {}

  vec3(const vec3& vector) : x(vector.x), y(vector.y), z(vector.z) {}

    ~vec3() {}

    // = operator
    vec3& operator=(const vec3& vector) {
      if (&vector != this) {
	x = vector.x;
	y = vector.y;
	z = vector.z;
      }
      return *this;
    }

    // + operator
    vec3 operator+(const vec3 &v) const {
      return vec3(x + v.x, y + v.y, z + v.z);
    }

    // += operator
    vec3& operator+=(const vec3 &v) {
      x += v.x; y += v.y; z += v.z;
      return *this;
    }

    // - operator
    vec3 operator-(const vec3 &v) const {
      return vec3(x - v.x, y - v.y, z - v.z);
    }

    // -= operator
    vec3& operator-=(const vec3 &v) {
      x -= v.x; y -= v.y; z -= v.z;
      return *this;
    }

    // == operator
    bool operator==(const vec3 &v) const {
      return x == v.x && y == v.y && z == v.z;
    }

    // != operator
    bool operator!=(const vec3 &v) const {
      return !( *this == v );
    }

    // * operator
    vec3 operator*(float f) const {
      return vec3(f*x, f*y, f*z);
    }

    // *= operator
    vec3 &operator*=(float f) {
      x *= f; y *= f; z *= f;
      return *this;
    }

    // / operator
    vec3 operator/(float f) const {
      assert(f > std::numeric_limits<float>::epsilon() );
      float inv = 1.f / f;
      return vec3(x * inv, y * inv, z * inv);
    }

    // /= operator
    vec3 &operator/=(float f) {
      assert(f > std::numeric_limits<float>::epsilon());
      float inv = 1.f / f;
      x *= inv; y *= inv; z *= inv;
      return *this;
    }

    // - operator
    vec3 operator-() const {
      return vec3(-x, -y, -z);
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
    vec3 cross(const vec3 &v) const{
      return vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    // Dot product operator
    float dot(const vec3 &v) const{
      return x * v.x + y * v.y + z * v.z;
    }

    // Normalize the vector and return it
    vec3 normalize() {
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
    vec3 clamp01() {
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

  inline vec3 operator*(float f, const vec3 & o) {
    return o*f;
  }

}

#endif
