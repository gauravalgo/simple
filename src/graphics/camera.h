#ifndef CAMERA_H
#define CAMERA_H

// Libraries
#include "object3D.h"
#include "definitions.h"
#include "../maths/matrix3.h"
#include "../maths/matrix4.h"

namespace simple {

  // Class Camera
  class camera : public object3D {

  protected :

    // ------------------- Attributes ------------------- //

    // Field of view
    float mFieldOfView;

    // Radius of the scene
    float mSceneRadius;

    // Near plane
    float mNearPlane;

    // Far plane
    float mFarPlane;

    // Width of the camera
    uint mWidth;

    // Height of the camera
    uint mHeight;

    // Projection matrix
    matrix4 mProjectionMatrix;

    // ------------------- Methods ------------------- //

    // Update the projection matrix
    void updateProjectionMatrix();

  public:

    // ------------------- Methods ------------------- //

    // Constructor
    camera();

    // Destructor
    ~camera();

    // Get the projection matrix
    const matrix4& getProjectionMatrix() const;

    // Set the dimensions of the camera
    void setDimensions(uint width, uint height);

    // Get the radius of the scene the camera should capture
    float getSceneRadius() const;

    // Set the radius of the scene the camera should capture
    // This will update the clipping planes accordingly
    void setSceneRadius(float radius);

    // Set the clipping planes
    void setClippingPlanes(float near, float far);

    // Set the field of view
    void setFieldOfView(float fov);

    // Set the zoom of the camera (a fraction between 0 and 1)
    void setZoom(float fraction);

    // Translate the camera go a given point using the dx, dy fraction
    void translateCamera(float dx, float dy, const vector3& worldPoint);

    // Get the near clipping plane
    float getNearClippingPlane() const;

    // Get the far clipping plane
    float getFarClippingPlane() const;

    // Get the width
    uint getWidth() const;

    // Get the height
    uint getHeight() const;
  };

  // Get the projection matrix
  inline const matrix4& camera::getProjectionMatrix() const {
    return mProjectionMatrix;
  }

  // Set the dimensions of the camera
  inline void camera::setDimensions(uint width, uint height) {
    mWidth = width;
    mHeight = height;
    updateProjectionMatrix();
  }

  // Get the radius of the scene the camera should capture
  inline float camera::getSceneRadius() const {
    return mSceneRadius;
  }

  // Set the radius of the scene the camera should capture
  // This will update the clipping planes accordingly
  inline void camera::setSceneRadius(float radius) {
    mSceneRadius = radius;
    setClippingPlanes(0.01f * radius, 10.0f * radius);
  }

  // Set the clipping planes
  inline void camera::setClippingPlanes(float near, float far) {
    mNearPlane = near;
    mFarPlane = far;
    updateProjectionMatrix();
  }

  // Set the field of view
  inline void camera::setFieldOfView(float fov) {
    mFieldOfView = fov;
    updateProjectionMatrix();
  }

  // Set the zoom of the camera (a fraction between 0 and 1)
  inline void camera::setZoom(float fraction) {
    vector3 zoomVector(0, 0, mSceneRadius * fraction * 3.0f);
    translateLocal(zoomVector);
  }

  // Get the near clipping plane
  inline float camera::getNearClippingPlane() const {
    return mNearPlane;
  }

  // Get the far clipping plane
  inline float camera::getFarClippingPlane() const {
    return mFarPlane;
  }

  // Get the width
  inline uint camera::getWidth() const {
    return mWidth;
  }

  // Get the height
  inline uint camera::getHeight() const {
    return mHeight;
  }

}

#endif
