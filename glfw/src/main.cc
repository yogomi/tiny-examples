// Copyright 2014 Makoto Yano

#if defined(_WIN32)
  #define GLFW_EXPOSE_NATIVE_WIN32
  #define GLFW_EXPOSE_NATIVE_WGL
  #define OVR_OS_WIN32
#elif defined(__APPLE__)
  #define GLFW_EXPOSE_NATIVE_COCOA
  #define GLFW_EXPOSE_NATIVE_NSGL
  #define OVR_OS_MAC
#elif defined(__linux__)
  #define GLFW_EXPOSE_NATIVE_X11
  #define GLFW_EXPOSE_NATIVE_GLX
  #define OVR_OS_LINUX
#endif


#include <math.h>
#include <unistd.h>
#include <stdio.h>

#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#elif __linux__
#include <GL/glu.h>
#include <GL/gl.h>
#endif

void reshape_func(int width, int height) {
  glViewport(0, 0, width, height);
}

void display_func(GLFWwindow *window) {
  float ratio;
  int width, height;

  glfwGetFramebufferSize(window, &width, &height);
  ratio = width / static_cast<float>(height);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(
    60.0f,
    static_cast<float>(width)
    / static_cast<float>(height), 2.0f, 200000.0f);
  gluLookAt(0, 0, 0
      , 0, 0,  -300, 0, 1, 0);

  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();
  glTranslated(0
      , 0
      , -600);

  glLoadIdentity();
  /*
  glTranslated(listener.camera_x_position
      , -listener.camera_y_position
      , -listener.camera_z_position);
      */

  glfwSwapBuffers(window);
  glfwPollEvents();
}

void key_func(unsigned char key, int x, int y) {
  switch (toupper(key)) {
  case 'Q':
    exit(0);
    break;
  case 'I':
    break;
  }
}

void error_callback(int error, const char *description) {
  fputs(description, stderr);
}

static void key_callback(GLFWwindow* window
                        , int key
                        , int scancode
                        , int action
                        , int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void init_opengl() {
  glEnable(GL_DEPTH_TEST);

  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 100.0 };
  GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
  GLfloat white_light[] = { 1.0, 1.0, 1.0, 0.0 };
  GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
  glClearColor(0, 0, 0, 1.0f);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  glShadeModel(GL_SMOOTH);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char** argv) {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    exit(EXIT_FAILURE);

  GLFWwindow *window = nullptr;

  window = glfwCreateWindow(900
                          , 600
                          , "My Title"
                          , NULL
                          , NULL);

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  glfwSetKeyCallback(window, key_callback);

  init_opengl();

  while (!glfwWindowShouldClose(window)) {
    display_func(window);
  }

  printf("finish\n");

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
