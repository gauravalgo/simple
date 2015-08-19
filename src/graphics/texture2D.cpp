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

// Libraries
#include "texture2D.h"
#include <fstream>
#include <iostream>
#include <string>

#include <stb_image.h>

#include "../utils/definitions.h"

// Namespaces
using namespace simple;
using namespace simple::graphics;

texture2D::texture2D() : mID(0), mLayer(0), mWidth(0), mHeight(0) {
}

texture2D::~texture2D() {
  glDeleteTextures(1,&mID);
  if (mID != 0) {
    glDeleteTextures(1, &mID);
    mID = 0;
    mLayer = 0;
    mWidth = 0;
    mHeight = 0;
  }
}

// Create the texture from an array of pixels
void texture2D::create(int width, int height, void* data)  {

  // Destroy the current texture
  destroy();

  mWidth = width;
  mHeight = height;

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Create the OpenGL texture
  glGenTextures(1, &mID);
  assert(mID != 0);
  glBindTexture(GL_TEXTURE_2D, mID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
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
