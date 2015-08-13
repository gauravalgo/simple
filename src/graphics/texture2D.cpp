// Libraries
#include "texture2D.h"
#include <fstream>
#include <iostream>
#include <string>

// Namespaces
using namespace simple;

// Constructor
texture2D::texture2D() : mID(0), mLayer(0), mWidth(0), mHeight(0) {

}

// Constructor
texture2D::texture2D(uint width, uint height, uint internalFormat, uint format, uint type)
  : mID(0), mLayer(0), mWidth(0), mHeight(0){

  // Create the texture
  create(width, height, internalFormat, format, type);
}

// Destructor
texture2D::~texture2D() {

}

// Create the texture
void texture2D::create(uint width, uint height, uint internalFormat, uint format, uint type,
		       void* data)  {

  // Destroy the current texture
  destroy();

  mWidth = width;
  mHeight = height;

  // Create the OpenGL texture
  glGenTextures(1, &mID);
  assert(mID != 0);
  glBindTexture(GL_TEXTURE_2D, mID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mWidth, mHeight, 0, format, type, data);
  glBindTexture(GL_TEXTURE_2D, 0);
}

// Destroy the texture
void texture2D::destroy() {
  if (mID != 0) {
    glDeleteTextures(1, &mID);
    mID = 0;
    mLayer = 0;
    mWidth = 0;
    mHeight = 0;
  }
}
