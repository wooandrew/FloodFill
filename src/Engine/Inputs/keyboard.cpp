// Engine : keyboard.cpp

#include "keyboard.hpp"

bool Keyboard::Keys[GLFW_KEY_LAST] = { 0 };
bool Keyboard::KeysDown[GLFW_KEY_LAST] = { 0 };
bool Keyboard::KeysUp[GLFW_KEY_LAST] = { 0 };

void Keyboard::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers) {

    if (key < 0)
        return;

    if ((action != GLFW_RELEASE) && (!Keys[key])) {
        KeysDown[key] = true;
        KeysUp[key] = false;
    }

    if ((action == GLFW_RELEASE) && (Keys[key])) {
        KeysDown[key] = false;
        KeysUp[key] = true;
    }

    Keys[key] = (action != GLFW_RELEASE);
}

bool Keyboard::KeyDown(int key) {

    bool keyDown = KeysDown[key];
    KeysDown[key] = false;

    return keyDown;
}

bool Keyboard::KeyUp(int key) {

    bool keyUp = KeysUp[key];
    KeysUp[key] = false;

    return keyUp;
}

bool Keyboard::KeyIsPressed(int key) {
    return Keys[key];
}
