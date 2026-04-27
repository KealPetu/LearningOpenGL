//
// Created by Keal on 4/16/2026.
//
#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // Shader Program
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);
    glLinkProgram(m_ID);
    checkCompileErrors(m_ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(m_ID);
}

void Shader::use() const {
    glUseProgram(m_ID);
}

// --- Utility functions for the Uniforms ---
void Shader::setBool(const std::string &varName, const GLboolean value) const {
    glUniform1i(glGetUniformLocation(m_ID, varName.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string &varName, const GLint value) const {
    glUniform1i(glGetUniformLocation(m_ID, varName.c_str()), value);
}

void Shader::setFloat(const std::string &varName, const GLfloat value) const {
    glUniform1f(glGetUniformLocation(m_ID, varName.c_str()), value);
}

void Shader::setVec2(const std::string &varName, const GLfloat x, const GLfloat y) const {
    glUniform2f(glGetUniformLocation(m_ID, varName.c_str()), x, y);
}

void Shader::setVec3(const std::string &varName, const GLfloat x, const GLfloat y, const GLfloat z) const {
    glUniform3f(glGetUniformLocation(m_ID, varName.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &varName, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w) const {
    glUniform4f(glGetUniformLocation(m_ID, varName.c_str()), x, y, z, w);
}

void Shader::setColor(const std::string &varName, const GLfloat r, const GLfloat g, const GLfloat b) const {
    glUniform3f(glGetUniformLocation(m_ID, varName.c_str()), r, g, b);
}

void Shader::setMat4(const std::string &varName, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(m_ID, varName.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::checkCompileErrors(const GLuint shader, const std::string &type) const {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}