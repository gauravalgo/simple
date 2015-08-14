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
#include "camera.h"
#include "definitions.h"
#include <cmath>
#include "../maths/vector3.h"

// Namespaces
using namespace simple;

// Constructor
camera::camera() : object3D() {

  // Set default values
  mFieldOfView = 45.0f;
  mSceneRadius = 1.0f;
  mNearPlane = 0.1f;
  mFarPlane = 10.0f;
  mWidth = 1;
  mHeight = 1;

  // Update the projection matrix
  updateProjectionMatrix();
}

// Destructor
camera::~camera() {

}

// Update the projection matrix
void camera::updateProjectionMatrix() {

  // Compute the aspect ratio
  float aspect = float(mWidth) / float(mHeight);

  float top = mNearPlane * tan((mFieldOfView / 2.0f) * (float(PI) / 180.0f));
  float bottom = -top;
  float left = bottom * aspect;
  float right = top * aspect;

  float fx = 2.0f * mNearPlane / (right - left);
  float fy = 2.0f * mNearPlane / (top - bottom);
  float fz = -(mFarPlane + mNearPlane) / (mFarPlane - mNearPlane);
  float fw = -2.0f * mFarPlane * mNearPlane / (mFarPlane - mNearPlane);

  // Recompute the projection matrix
  mProjectionMatrix = matrix4(fx, 0, 0, 0,
			      0, fy, 0, 0,
			      0, 0, fz, fw,
			      0, 0, -1, 0);
}

// Translate the camera go a given point using the dx, dy fraction
void camera::translateCamera(float dx, float dy, const vector3& worldPoint) {

  // Transform the world point into camera coordinates
  vector3 pointCamera = mTransformMatrix.getInverse() * worldPoint;

  // Get the depth
  float z = -pointCamera.z;

  // Find the scaling of dx and dy from windows coordinates to near plane coordinates
  // and from there to camera coordinates at the object's depth
  float aspect = float(mWidth) / float(mHeight);
  float top = mNearPlane * tan(mFieldOfView * PI / 360.0f);
  float right = top * aspect;

  // Translate the camera
  translateLocal(vector3(2.0f * dx * right / mNearPlane * z,
			 -2.0f * dy * top / mNearPlane * z,
			 0.0f));
}
