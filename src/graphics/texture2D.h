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

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

// Libraries
#include <string>
#include <cassert>
#include "../utils/definitions.h"

#include <GL/glew.h>

using namespace std;

namespace simple
{
  namespace graphics
  {
    class texture2D {

    private:

      // OpenGL texture ID
      uint mID;

      // Layer of the texture
      int mLayer;

      // Width
      int mWidth;

      // Height
      int mHeight;

    public:

      // Constructor
      texture2D();

      // Destructor
      ~texture2D();

      // Create the texture
      void create(int width, int height,
                  void* data = NULL);
      void create(const string &fileName);

      // Destroy the texture
      void destroy();

      // Bind the texture
      void bind() const;

      // Unbind the texture
      void unbind() const;

      // Get the OpenGL texture ID
      uint getID() const;
      // Set the OpenGL texuture ID
      void setID(uint value);
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
      glEnable(GL_BLEND);

// glEnable(GL_TEXTURE_2D);
      glActiveTexture(GL_TEXTURE0 + mLayer);
      glBindTexture(GL_TEXTURE_2D, mID);
    }

    // Unbind the texture
    inline void texture2D::unbind() const {
      assert(mID != 0);
      glActiveTexture(GL_TEXTURE0 + mLayer);
      glBindTexture(GL_TEXTURE_2D, 0);
      glDisable(GL_BLEND);
//    glDisable(GL_TEXTURE_2D);
    }

    // Get the OpenGL texture ID
    inline uint texture2D::getID() const {
      return mID;
    }

    inline void texture2D::setID(uint value) {
      mID = value;
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
}

#endif
