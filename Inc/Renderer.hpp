#pragma once 

#include "Gl.hpp"

#include <cstdlib>

namespace gl {

#ifdef DEBUG
#define ASSERT(x)                                                              \
  if (!(x))                                                                    \
    std::abort();

#define GL_CALL(x)                                                             \
  glClearError();                                                              \
  x;                                                                           \
  ASSERT(glLogCall(#x, __func__, __FILE__, __LINE__));
#else
#define ASSERT(x)
#define ASSERT_GL_ERROR(x) x
#define GL_CALL(x) x
#endif

void glClearError();
bool glLogCall(const char *context, const char *func, const char *file,
               int line);

} // namespace gl
