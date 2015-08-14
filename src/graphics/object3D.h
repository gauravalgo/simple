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

#ifndef OBJECT3D_H
#define OBJECT3D_H

// Libraries
#include "../maths/vector3.h"
#include "../maths/matrix4.h"

namespace simple {

  class object3D {

  protected:
    // Transformation matrix that convert local-space
    // coordinates to world-space coordinates
    matrix4 mTransformMatrix;

  public:

    // -------------------- Methods -------------------- //

    // Constructor
    object3D();

    // Destructor
    virtual ~object3D();

    // Return the transform matrix
    const matrix4& getTransformMatrix() const;

    // Set to the identity transform
    void setToIdentity();

    // Return the origin of object in world-space
    vector3 getOrigin() const;

    // Translate the object in world-space
    void translateWorld(const vector3& v);

    // Translate the object in local-space
    void translateLocal(const vector3& v);

    // Rotate the object in world-space
    void rotateWorld(const vector3& axis, float angle);

    // Rotate the object in local-space
    void rotateLocal(const vector3& axis, float angle);

    // Rotate around a world-space point
    void rotateAroundWorldPoint(const vector3& axis, float angle, const vector3& point);

    // Rotate around a local-space point
    void rotateAroundLocalPoint(const vector3& axis, float angle, const vector3& worldPoint);
  };

  // Return the transform matrix
  inline const matrix4& object3D::getTransformMatrix() const {
    return mTransformMatrix;
  }

  // Set to the identity transform
  inline void object3D::setToIdentity() {
    mTransformMatrix.setToIdentity();
  }

  // Return the origin of object in world-space
  inline vector3 object3D::getOrigin() const {
    return mTransformMatrix * vector3(0.0, 0.0, 0.0);
  }

  // Translate the object in world-space
  inline void object3D::translateWorld(const vector3& v) {
    mTransformMatrix = matrix4::translationMatrix(v) * mTransformMatrix;
  }

  // Translate the object in local-space
  inline void object3D::translateLocal(const vector3& v) {
    mTransformMatrix = mTransformMatrix * matrix4::translationMatrix(v);
  }

  // Rotate the object in world-space
  inline void object3D::rotateWorld(const vector3& axis, float angle) {
    mTransformMatrix = matrix4::rotationMatrix(axis, angle) * mTransformMatrix;
  }

  // Rotate the object in local-space
  inline void object3D::rotateLocal(const vector3& axis, float angle) {
    mTransformMatrix = mTransformMatrix * matrix4::rotationMatrix(axis, angle);
  }

  // Rotate the object around a world-space point
  inline void object3D::rotateAroundWorldPoint(const vector3& axis, float angle,
					       const vector3& worldPoint) {
    mTransformMatrix = matrix4::translationMatrix(worldPoint) * matrix4::rotationMatrix(axis, angle)
      * matrix4::translationMatrix(-worldPoint) * mTransformMatrix;
  }

  // Rotate the object around a local-space point
  inline void object3D::rotateAroundLocalPoint(const vector3& axis, float angle,
					       const vector3& worldPoint) {

    // Convert the world point into the local coordinate system
    vector3 localPoint = mTransformMatrix.getInverse() * worldPoint;

    mTransformMatrix = mTransformMatrix * matrix4::translationMatrix(localPoint)
      * matrix4::rotationMatrix(axis, angle)
      * matrix4::translationMatrix(-localPoint);
  }

}

#endif
