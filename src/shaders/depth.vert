// Uniform variables
uniform mat4 modelToWorldMatrix;        // Model too world coordinates matrix
uniform mat4 worldToCameraMatrix;       // World to camera coordinates matrix
uniform mat4 projectionMatrix;          // Projection matrix

void main(void) {

    // Compute the clip-space vertex coordinates
    gl_Position = projectionMatrix * worldToCameraMatrix *
                  modelToWorldMatrix * gl_Vertex;
}
