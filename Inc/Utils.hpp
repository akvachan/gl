#pragma once

#include "Gl.hpp"
#include <string>
#include <stdexcept>

namespace gl {

constexpr uint32_t getTypeSize(GLenum type) {
  switch (type) {
  case GL_FLOAT:
    return sizeof(float);
  case GL_UNSIGNED_INT:
    return sizeof(uint32_t);
  case GL_INT:
    return sizeof(int32_t);
  case GL_UNSIGNED_BYTE:
    return sizeof(uint8_t);
  default:
    throw std::runtime_error("ERROR: Unsupported OpenGL type.");
  }
}

constexpr std::string getShaderStringType(GLenum type) {
    switch (type) {
    case GL_VERTEX_SHADER:
      return "vertex";
    case GL_FRAGMENT_SHADER:
      return "fragment";
    default:
      return "unknown";
    }
}

} // namespace gl
