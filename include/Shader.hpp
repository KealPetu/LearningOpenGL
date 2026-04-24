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
    void setVec2(const std::string &varName, const GLfloat x, const GLfloat y) const;
    void setVec3(const std::string &varName, const GLfloat x, const GLfloat y, const GLfloat z) const;
    void setVec4(const std::string &varName, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w) const;
    void setColor(const std::string &varName, const GLfloat r, const GLfloat g, const GLfloat b) const;
};