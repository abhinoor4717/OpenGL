#include "Camera.h"
#include <iostream>

Camera::Camera(int x, int y, int w, int h) : m_X(x), m_Y(y), m_Width(w), m_Height(h) {}

glm::vec2 Camera::TranslatePos(float x, float y) {
    // Define the orthographic projection
    glm::mat4 projection = glm::ortho(0.0f, (float)m_Width, (float)m_Height, 0.0f, -1.0f, 1.0f);

    // View transformation (camera position)
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-m_X, -m_Y, 0.0f));

    // Model matrix is not needed if x, y are already in world space
    glm::vec4 worldPos(x, y, 0.0f, 1.0f);

    // Transform to clip space
    glm::vec4 clipSpace = projection * view * worldPos;

    // Convert to NDC (normally needed for perspective projections, but orthographic w = 1)
    glm::vec2 ndc = glm::vec2(clipSpace.x, clipSpace.y);  // No need to divide by w

    // Debug print
    std::cout << "NDC: " << ndc.x << ", " << ndc.y << std::endl;

    return ndc;
}
