// Engine : keyboard.hpp

#pragma once

#ifndef ENGINE_INPUTS_KEYBOARD_CHPP
#define ENGINE_INPUTS_KEYBOARD_CHPP

#include <GLFW/glfw3.h>

class Keyboard {

public:

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers);
    static bool KeyDown(int key);
    static bool KeyUp(int key);
    static bool KeyIsPressed(int key);

private:

    static bool Keys[];
    static bool KeysDown[];
    static bool KeysUp[];
};

#endif // !ENGINE_INPUTS_KEYBOARD_CHPP
