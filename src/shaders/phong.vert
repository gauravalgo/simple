// Uniform variables
uniform mat4 modelToWorldMatrix;        // Model too world coordinates matrix
uniform mat4 worldToCameraMatrix;       // World to camera coordinates matrix
uniform mat4 projectionMatrix;          // Projection matrix

// Varying variables
varying vec3 worldPosition;             // World position of the vertex
varying vec3 worldNormal;               // World surface normalWorld
varying vec2 texCoords;                 // Texture coordinates

void main() {

    // Compute the vertex position
    vec4 worldPos = modelToWorldMatrix * gl_Vertex;
    worldPosition = worldPos.xyz;

    // Compute the world surface normal
    worldNormal = (modelToWorldMatrix * vec4(gl_Normal, 0.0)).xyz;

    // Get the texture coordinates
    texCoords = gl_MultiTexCoord0.xy;

    // Compute the clip-space vertex coordinates
    gl_Position = projectionMatrix * worldToCameraMatrix * worldPos;
}
