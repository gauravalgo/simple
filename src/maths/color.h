#ifndef COLOR_H
#define COLOR_H

struct color {

public:

  // RGBA color components
  float r, g, b, a;

  // Constructor
color() : r(1), g(1), b(1), a(1) {}

  // Constructor
color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

  // Constructor
color(const color& color) : r(color.r), g(color.g), b(color.b), a(color.a) {}

  // Destructor
  ~color() {}

  // Return the black color
  static color black() { return color(0.0f, 0.0f, 0.0f, 1.0f);}

  // Return the white color
  static color white() { return color(1.0f, 1.0f, 1.0f, 1.0f);}

  // = operator
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
