#ifndef TEXTURE2D_H
#define TEXTURE2D_H

// Libraries
#include <string>
#include <cassert>
#include "definitions.h"
#include <GL/glew.h>

using namespace std;

namespace simple {

  class texture2D {

  private:

    // OpenGL texture ID
    uint mID;

    // Layer of the texture
    uint mLayer;

    // Width
    uint mWidth;

    // Height
    uint mHeight;

  public:

    // Constructor
    texture2D();

    // Constructor
    texture2D(uint width, uint height, uint internalFormat, uint format, uint type);

    // Destructor
    ~texture2D();

    // Create the texture
    void create(uint width, uint height, uint internalFormat, uint format, uint type,
		void* data = NULL);

    // Destroy the texture
    void destroy();

    // Bind the texture
    void bind() const;

    // Unbind the texture
    void unbind() const;

    // Get the OpenGL texture ID
    uint getID() const;

    // Get the layer of the texture
    uint getLayer() const;

    // Set the layer of the texture
    void setLayer(uint layer);

    // Get the width
    uint getWidth() const;

    // Get the height
    uint getHeight() const;
  };

  // Bind the texture
  inline void texture2D::bind() const {
    assert(mID != 0);
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0 + mLayer);
    glBindTexture(GL_TEXTURE_2D, mID);
  }

  // Unbind the texture
  inline void texture2D::unbind() const {
    assert(mID != 0);
    glActiveTexture(GL_TEXTURE0 + mLayer);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
  }

  // Get the OpenGL texture ID
  inline uint texture2D::getID() const {
    return mID;
  }

  // Get the layer of the texture
  inline uint texture2D::getLayer() const {
    return mLayer;
  }

  // Set the layer of the texture
  inline void texture2D::setLayer(uint layer) {
    mLayer = layer;
  }

  // Get the width
  inline uint texture2D::getWidth() const {
    return mWidth;
  }

  // Get the height
  inline uint texture2D::getHeight() const {
    return mHeight;
  }

}

#endif
