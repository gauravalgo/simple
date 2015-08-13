// Libraries
#include "texture2D.h"
#include <fstream>
#include <iostream>
#include <string>

#include "stb_image.h"

#include "../graphics/definitions.h"

// Namespaces
using namespace simple;

texture2D::texture2D() : mID(0), mLayer(0), mWidth(0), mHeight(0) {

}

texture2D::~texture2D() {
 glDeleteTextures(1,&mID);
}

// Create the texture from an array of pixels
void texture2D::create(int width, int height, void* data)  {

  // Destroy the current texture
  destroy();

  mWidth = width;
  mHeight = height;

  glGenTextures(1, &mID);
  assert(mID != 0);
  glBindTexture(GL_TEXTURE_2D, mID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glGenerateMipmap(GL_TEXTURE_2D); //GL ES 2 but not GL 2
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_FLOAT, data);
}

// Create the texture from a file
void texture2D::create(const std::string& fileName)  {

  // Destroy the current texture
  destroy();

  int numComponents;
  unsigned char* pixels = stbi_load((fileName).c_str(),&mWidth,&mHeight,&numComponents,4);

  if(pixels == NULL)
      LOG("Error: Could not load image - " << fileName);

  // Create the OpenGL texture
  glGenTextures(1, &mID);
  assert(mID != 0);
  glBindTexture(GL_TEXTURE_2D, mID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glGenerateMipmap(GL_TEXTURE_2D); //GL ES 2 but not GL 2
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

  stbi_image_free(pixels);
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
