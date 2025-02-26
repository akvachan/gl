#include "Renderer.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

#include <iostream>

using namespace std::literals::string_view_literals;

const size_t WIDTH = 1920;
const size_t HEIGHT = 1080;
const std::string_view WINDOW_NAME = "OpenGL"sv;
const std::string_view SHADER_PATH = "res/shaders/basic.glsl"sv;

static void quitCallback(GLFWwindow *window, int key,
                         [[maybe_unused]] int scancode, int action,
                         [[maybe_unused]] int _mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void framebufferSizeCallback([[maybe_unused]] GLFWwindow *window, int width,
                             int height) {
  glViewport(0, 0, width, height);
}

int main() {
  if (!glfwInit()) {
    std::cerr << "ERROR: Could not start GLFW3" << std::endl;
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window = glfwCreateWindow(
      WIDTH, HEIGHT, ((std::string)WINDOW_NAME).c_str(), NULL, NULL);
  if (!window) {
    std::cerr << "ERROR: Could not open window with GLFW3" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwSetKeyCallback(window, quitCallback);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "ERROR: Could not initialize GLEW" << std::endl;
    return -1;
  }

  int fbWidth, fbHeight;
  glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
  glViewport(0, 0, fbWidth, fbHeight);
  glfwSwapInterval(1);

  std::cout << "INFO: Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "INFO: OpenGL version supported: " << glGetString(GL_VERSION)
            << std::endl;

  float positions[] = {
      -0.5f, 0.5f,  0.5f, 0.5f, -0.5f, -0.5f,
      0.5f,  -0.5f, 1.0f, 0.5f, -1.0f, -0.5f,
  };
  uint32_t indices[] = {
      0, 1, 2, 1, 2, 3, 1, 3, 4, 0, 2, 5,
  };
  gl::VertexBufferLayout VertexBufferLayout{};
  gl::VertexArray VertexArray{};
  gl::VertexBuffer VertexBuffer{positions, sizeof(positions)};
  gl::IndexBuffer IndexBuffer{indices, sizeof(indices) / sizeof(uint32_t)};
  VertexBufferLayout.addFloat(2);
  VertexArray.addBuffer(VertexBuffer, VertexBufferLayout);

  gl::Shader Shader{SHADER_PATH};
  float red = 1.0f, green = 0.0f, blue = 0.0f, trans = 1.0f;
  const std::string uniformName = "u_Color";
  Shader.setUniform4f(uniformName, {red, green, blue, trans});

  VertexArray.unbind();
  VertexBuffer.unbind();
  IndexBuffer.unbind();
  Shader.unbind();

  while (!glfwWindowShouldClose(window)) {
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

    VertexArray.bind();
    VertexBuffer.bind();
    IndexBuffer.bind();
    Shader.bind();

    float timeValue = glfwGetTime();
    red = (sin(timeValue * 2.0f) + 1.0f) / 2.0f;
    blue = (cos(timeValue * 2.0f) + 1.0f) / 2.0f;
    Shader.setUniform4f(uniformName, {red, green, blue, trans});

    GL_CALL(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr));
    GL_CALL(glfwSwapBuffers(window));
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
