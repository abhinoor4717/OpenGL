#include "Renderer/Shader.h"

Shader::Shader(const std::string& vPath, const std::string& fPath) {
    std::ifstream vSrcFile(vPath);
    std::ifstream fSrcFile(fPath);

    if (!vSrcFile) {
        std::cout << "RENDERER::SHADER::COULD_NOT_OPEN_VERTEX_SHADER_SOURCE_FILE: " << vPath << std::endl;
        return;
    }

    if (!fSrcFile) {
        std::cout << "RENDERER::SHADER::COULD_NOT_OPEN_FRAGMENT_SHADER_SOURCE_FILE: " << fPath << std::endl;
        return;
    }

    std::stringstream vBuffer, fBuffer;
    vBuffer << vSrcFile.rdbuf();
    fBuffer << fSrcFile.rdbuf();

    std::string vStr = vBuffer.str();
    std::string fStr = fBuffer.str();
    const char* vSrc = vStr.c_str();
    const char* fSrc = fStr.c_str();

    unsigned int vShader, fShader;
    int success;
    char infoLog[512];

    // Compile Vertex Shader
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vSrc, NULL);
    glCompileShader(vShader);
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShader, 512, NULL, infoLog);
        std::cout << "RENDERER::SHADER::VERTEX::COMPILE_ERROR\n" << infoLog << std::endl;
        return;
    }

    // Compile Fragment Shader (Fixed)
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fSrc, NULL);
    glCompileShader(fShader);
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fShader, 512, NULL, infoLog);
        std::cout << "RENDERER::SHADER::FRAGMENT::COMPILE_ERROR\n" << infoLog << std::endl;
        return;
    }

    // Link Shader Program
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vShader);
    glAttachShader(m_ID, fShader);
    glLinkProgram(m_ID);
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        std::cout << "RENDERER::PROGRAM::LINK_ERROR\n" << infoLog << std::endl;
        return;
    }

    // Cleanup
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    std::cout << "RENDERER::SHADER::LINK::SUCCESS!" << std::endl;
}

Shader::~Shader() {
    glDeleteProgram(m_ID);
}

void Shader::Use() {
    glUseProgram(m_ID);
}

void Shader::Reload(Shader*& shader, const std::string& vSrc, const std::string& fSrc) {
    delete shader;
    shader = new Shader(vSrc, fSrc);
}