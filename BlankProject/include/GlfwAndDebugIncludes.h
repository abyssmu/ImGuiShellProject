/*
* This file holds the common GLFW libary and DebugManager inclusions.
* Since the core framework of the application requires both, it can be
* managed in one place.
*/

#pragma once

#ifndef _GLFWANDDEBUG_
#define _GLFWANDDEBUG_

#define GL_SILENCE_DEPRECATION
#ifdef IMGUI_IMPL_OPENGL_ES2
#include <GLES2/gl2.h>
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "DebugManager.h"

#endif