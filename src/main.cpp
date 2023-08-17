// Main.cpp

#include <iostream>

#include "Engine/engine.hpp"

int main() {

    std::cout << "Hello World!" << std::endl;

    Engine e("FloodFill", 1000, 618);

    e.init();

    while (!glfwWindowShouldClose(e.GetWindow())) {

        e.Update();

    }

    return 0;
}
