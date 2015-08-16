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
