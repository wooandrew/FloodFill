// Engine : mouse.hpp

#pragma once

#ifndef ENGINE_INPUTS_MOUSE_CHPP
#define ENGINE_INPUTS_MOUSE_CHPP

#include <GLFW/glfw3.h>

class Mouse {

public:

    static void PositionCallback(GLFWwindow* window, double _x, double _y);
    static void ButtonCallback(GLFWwindow* window, int button, int action, int modifiers);

	static bool ButtonDown(int button);
	static bool ButtonUp(int button);
	static bool ButtonIsPressed(int button);

private:

	static double x;
	static double y;

	static bool Buttons[];
	static bool ButtonsDown[];
	static bool ButtonsUp[];
};

#endif
