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

#ifndef COLOR_H
#define COLOR_H


struct color {

public:

  float r, g, b, a;

color() : r(1), g(1), b(1), a(1) {}
color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
color(const color& color) : r(color.r), g(color.g), b(color.b), a(color.a) {}

  ~color() {}

  static color black() { return color(0.0f, 0.0f, 0.0f, 1.0f);}
  static color white() { return color(1.0f, 1.0f, 1.0f, 1.0f);}
  static color red() { return color(1.0f, 0.0f, 0.0f, 1.0f);}
  static color green() { return color(0.0f, 1.0f, 0.0f, 1.0f);}
  static color blue() { return color(0.0f, 0.0f, 1.0f, 1.0f);}
  
  color& operator=(const color& color) {
    if (&color != this) {
      r = color.r;
      g = color.g;
      b = color.b;
      a = color.a;
    }
    return *this;
  }
};

#endif
