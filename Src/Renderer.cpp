#include "Renderer.hpp"

#include <iostream>

namespace gl {

void glClearError() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

bool glLogCall(const char *context, const char *func, const char *file,
               int line) {
  while (GLenum error = glGetError()) {
    std::cout << "\nERROR: 0x0" << std::hex << error << std::dec
              << "] in [" << context << "] from [" << file << ':' << func << ":"
              << line << "]\n\n";
    return false;
  }
  return true;
}

} // namespace gl
