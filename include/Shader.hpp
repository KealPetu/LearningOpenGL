#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
private:
    GLuint m_ID;
    void checkCompileErrors(GLuint shader, const std::string &type) const;

public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void use() const;

    void setBool(const std::string &varName, GLboolean value) const;
    void setInt(const std::string &varName, GLint value) const;
    void setFloat(const std::string &varName, GLfloat value) const;
    void setVec2(const std::string &varName, GLfloat x, GLfloat y) const;
    void setVec3(const std::string &varName, GLfloat x, GLfloat y,  GLfloat z) const;
    void setVec4(const std::string &varName, GLfloat x,  GLfloat y,  GLfloat z,  GLfloat w) const;
    void setColor(const std::string &varName, GLfloat r,  GLfloat g,  GLfloat b) const;
    void setMat4(const std::string &varName, const glm::mat4 &mat) const;
};