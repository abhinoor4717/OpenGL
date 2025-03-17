#pragma once
#include <Glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader {
public:
    Shader(const std::string& vSrc, const std::string& fSrc);
    ~Shader();
    void Use();
    inline unsigned int GetID() { return m_ID; }

    static void Reload(Shader*& shader, const std::string& vSrc, const std::string& fSrc);

private:
    unsigned int m_ID;
};