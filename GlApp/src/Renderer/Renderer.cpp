#include "Renderer.h"

void Renderer::DrawLine(Camera& cam, int x1, int y1, int x2, int y2) {
    // Transform world coordinates to NDC using the camera
    glm::vec2 ndc1 = cam.TranslatePos((float)x1, (float)y1);
    glm::vec2 ndc2 = cam.TranslatePos((float)x2, (float)y2);

    // Define the line vertices in NDC space
    GLfloat vertices[] = {
        ndc1.x, ndc1.y,  // Point 1
        ndc2.x, ndc2.y   // Point 2
    };

    // Create VAO and VBO
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind and fill VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Define vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    // Draw the line
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);

    // Cleanup
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}