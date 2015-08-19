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

#ifndef VECTOR4_H
#define VECTOR4_H

// Libraries
#include <math.h>
#include <assert.h>

namespace simple {

  namespace maths {
    class vec4 {

    public:

      float x, y, z, w;

    vec4(float x=0, float y=0, float z=0, float w=0) : x(x), y(y), z(z), w(w) {}

    vec4(const vec4& vector) : x(vector.x), y(vector.y), z(vector.z), w(vector.w) {}

      vec4 operator+(const vec4 &v) const {
	return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
      }

      // += operator
      vec4& operator+=(const vec4 &v) {
	x += v.x; y += v.y; z += v.z; w += v.w;
	return *this;
      }

      // - operator
      vec4 operator-(const vec4 &v) const {
	return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
      }

      // -= operator
      vec4& operator-=(const vec4 &v) {
	x -= v.x; y -= v.y; z -= v.z, w -=v.w;
	return *this;
      }

      // = operator
      vec4& operator=(const vec4& vector) {
	if (&vector != this) {
	  x = vector.x;
	  y = vector.y;
	  z = vector.z;
	  w = vector.w;
	}
	return *this;
      }

      // == operator
      bool operator==(const vec4 &v) const {
	return x == v.x && y == v.y && z == v.z && w == v.w;
      }

      // * operator
      vec4 operator*(float f) const {
	return vec4(f*x, f*y, f*z, f*w);
      }

      // *= operator
      vec4 &operator*=(float f) {
	x *= f; y *= f; z *= f; w *= f;
	return *this;
      }

      // / operator
      vec4 operator/(float f) const {
	assert(f!=0);
	float inv = 1.f / f;
	return vec4(x * inv, y * inv, z * inv, w * inv);
      }

      // /= operator
      vec4 &operator/=(float f) {
	assert(f!=0);
	float inv = 1.f / f;
	x *= inv; y *= inv; z *= inv; w *= inv;
	return *this;
      }

      // - operator
      vec4 operator-() const {
	return vec4(-x, -y, -z, -w);
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
      float dot(const vec4 &v) const {
	return x * v.x + y * v.y + z * v.z + w * v.w;
      }

      // Multiply two vectors by their components
      vec4 componentMul(const vec4 &v) const {
	return vec4(x * v.x, y * v.y, z * v.z, w * v.w);
      }

      // Clamp the values between 0 and 1
      vec4 clamp01() {
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
}
#endif //_VECTOR4_H
