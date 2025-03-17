#pragma once

#include "glm.hpp"

class Camera {
public:
    Camera(int x, int y, int w, int h);

    inline void SetViewport(int w, int h) { m_Width = w; m_Height = h; }

    inline int GetX() { return m_X; }
    inline int GetY() { return m_Y; }

    glm::vec2 TranslatePos(float x, float y);

private:
    int m_X, m_Y, m_Width, m_Height;
};