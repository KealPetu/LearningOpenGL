#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
private:
    GLuint ID;

    void checkCompileErrors(GLuint shader, const std::string &type) const;

public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void use() const;

    void setBool(const std::string &varName, GLboolean value) const;
    void setInt(const std::string &varName, GLint value) const;
    void setFloat(const std::string &varName, GLfloat value) const;
};