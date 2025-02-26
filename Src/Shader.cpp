#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Gl.hpp"
#include "Renderer.hpp"
#include "Utils.hpp"

namespace gl {

Shader::Shader(const std::string_view &filePath) : _rendererId(0) {
  const auto [vertexShader, fragmentShader] = _parseShaderFile(filePath);
  uint32_t vertexShaderId = _compileShader(GL_VERTEX_SHADER, vertexShader);
  uint32_t fragmentShaderId =
      _compileShader(GL_FRAGMENT_SHADER, fragmentShader);
  _rendererId = _createShader(vertexShaderId, fragmentShaderId);
}

Shader::~Shader() { GL_CALL(glDeleteProgram(_rendererId)); }

void Shader::bind() const { GL_CALL(glUseProgram(_rendererId)); }

void Shader::unbind() const { GL_CALL(glUseProgram(0)); }

void Shader::setUniform1f(const std::string &name, const float f) {
  _uniformName = name;
  int location = _getUniformLocation(name);
  GL_CALL(glUniform1f(location, f));
};

void Shader::setUniform4f(const std::string &name,
                          const std::array<float, 4> &floats) {
  _uniformName = name;
  int location = _getUniformLocation(name);
  GL_CALL(glUniform4f(location, floats[0], floats[1], floats[2], floats[3]));
}

std::pair<std::string, std::string>
Shader::_parseShaderFile(const std::string_view path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    std::cerr << "ERROR: Failed to open file: " << path << '\n';
    return {};
  }

  std::stringstream shaderStream[2];
  std::string fileLine;
  ShaderType type = ShaderType::NONE;
  while (std::getline(file, fileLine)) {
    if (fileLine.find("#shader") != std::string::npos) {
      if (fileLine.find("vertex") != std::string::npos) {
        type = ShaderType::VERTEX;
      } else if (fileLine.find("fragment") != std::string::npos) {
        type = ShaderType::FRAGMENT;
      }
    } else {
      shaderStream[(int)type] << fileLine << '\n';
    }
  }

  return {shaderStream[ShaderType::VERTEX].str(),
          shaderStream[ShaderType::FRAGMENT].str()};
}

int Shader::_compileShader(GLenum type, const std::string &source) const {
  GL_CALL(uint32_t id = glCreateShader(type));
  const char *src = source.c_str();
  GL_CALL(glShaderSource(id, 1, &src, nullptr));
  GL_CALL(glCompileShader(id));

  int success;
  GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
  if (success == GL_FALSE) {
    int length;
    GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
    auto message = std::unique_ptr<char[]>(new char[length]);
    GL_CALL(glGetShaderInfoLog(id, length, nullptr, message.get()));
    std::cerr << "ERROR: Failed to compile shader: "
              << getShaderStringType(type) << message.get() << '\n';
    GL_CALL(glDeleteShader(id));
    return 0;
  }

  return id;
}

int Shader::_getUniformLocation(const std::string &name) {
  if (_uniformLocations.contains(name))
    return _uniformLocations[name];

  GL_CALL(int location = glGetUniformLocation(_rendererId, name.c_str()));
  ASSERT(location != -1);
  _uniformLocations[name] = location;
  return location;

}

uint32_t Shader::_createShader(uint32_t vertexShaderId,
                               uint32_t fragmentShaderId) const {
  uint32_t program = GL_CALL(glCreateProgram());
  GL_CALL(glAttachShader(program, vertexShaderId));
  GL_CALL(glAttachShader(program, fragmentShaderId));
  GL_CALL(glLinkProgram(program));

  int success;
  GL_CALL(glGetProgramiv(program, GL_LINK_STATUS, &success));
  if (success == GL_FALSE) {
    int length;
    GL_CALL(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
    auto message = std::unique_ptr<char[]>(new char[length]);
    GL_CALL(glGetProgramInfoLog(program, length, nullptr, message.get()));
    std::cerr << "ERROR: Failed to link program:\n" << message.get() << '\n';
  }

  GL_CALL(glValidateProgram(program));
  GL_CALL(glDeleteShader(vertexShaderId));
  GL_CALL(glDeleteShader(fragmentShaderId));

  return program;
}

} // namespace gl
