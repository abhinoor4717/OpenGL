#pragma once

#include <Glad/glad.h>
#include "Camera.h"

class Renderer {
public:
    static void DrawLine(Camera& cam, int x1, int y1, int x2, int y2);
private:

};