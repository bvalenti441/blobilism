#include <iostream>
#include <vector>
#include "tinygl-cpp.h"
using namespace tinygl;

class MyWindow : public Window {
private:

    // todo: create member variables for 
    // current circle size
    int currBrushSize = 35;
    // current transparency
    // current color
    int currColor;
    // list of circles to draw each frame
    std::vector<float[4]> circles; // color, x position, y position, brush size
    // color pallet

public:
    MyWindow(int w, int h) : Window(w, h) {}

    int getCurrColor() {
        return this->currColor;
    }

    void setCurrColor(int i) {
        this->currColor = i;
    }

    std::vector<float[4]> getCircles() {
        return this->circles;
    }

    void setCircles(std::vector<float[4]> vec) {
        this->circles = vec;
    }

    void setup() override {
        std::cout << "Window size: " << width() << ", " << height() << std::endl;
    }

    virtual void mouseMotion(int x, int y, int dx, int dy) {
        if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
            // todo: store a circle with the current color, size, x, y
        }
    }

    void paletteColor(int num) {
        switch (num) {
        case 1:
            color(0.5f, 0, 0);
            setCurrColor(1);
            return;
        case 2:
            color(0, 0.5f, 0);
            setCurrColor(2);
            return;
        case 3:
            color(0, 0, 1.0f);
            setCurrColor(3);
            return;
        case 4:
            color(0.5f, 0.5f, 0);
            setCurrColor(4);
            return;
        case 5:
            color(0.5f, 0, 0.5f);
            setCurrColor(5);
            return;
        case 6:
            color(0, 0.5f, 0.5f);
            setCurrColor(6);
            return;
        case 7:
            color(1.0f, 0, 1.0f);
            setCurrColor(7);
            return;
        case 8:
            color(1.0f, 1.0f, 1.0f);
            setCurrColor(8);
            return;
        case 9:
            color(0.5f, 0.5f, 0.5f);
            setCurrColor(9);
            return;
        case 10:
            color(0, 0, 0);
            setCurrColor(10);
            return;
        default:
            std::cout << "not a color on the pallette" << std::endl;
            return;
        }
    }
    virtual void mouseDown(int button, int mods) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            // todo: check if user clicked a color 
            float mx = mouseX();  // current mouse pos x
            float my = mouseY();  // current mouse pos y
            if (sqrt((mx - width() / 11.0f) + (my - 35)) <= 35) { //pallette circles
                paletteColor(1);
            }
            else if (sqrt((mx - width() / 11.0f * 2.0f) + (my - 35)) <= 35) { //pallette circles
                paletteColor(2);
            }
            else if (sqrt((mx - width() / 11.0f * 3.0f) + (my - 35)) <= 35) { //pallette circles
                paletteColor(3);
            }
            else if (sqrt((mx - width() / 11.0f * 4.0f) + (my - 35)) <= 35) { //pallette circles
                paletteColor(4);
            }
            else if (sqrt((mx - width() / 11.0f * 5.0f) + (my - 35)) <= 35) { //pallette circles
                paletteColor(5);
            }
            else if (sqrt((mx - width() / 11.0f * 6.0f) + (my - 35)) <= 35) { //pallette circles
                paletteColor(6);
            }
            else if (sqrt((mx - width() / 11.0f * 7.0f) + (my - 35)) <= 35) { //pallette circles
                paletteColor(7);
            }
            else if (sqrt((mx - width() / 11.0f * 8.0f) + (my - 35)) <= 35) { //pallette circles
                paletteColor(8);
            }
            else if (sqrt((mx - width() / 11.0f * 9.0) + (my - 35)) <= 35) { //pallette circles
                paletteColor(9);
            }
            else if (sqrt((mx - width() / 11.0f * 10.0) + (my - 35)) <= 35) { //pallette circles
                paletteColor(10);
            }
            else if (my <= 35) {
                return;
            } 
            else {
                getCircles().push_back({ (float)currColor, mx, my, (float) currBrushSize }); // draw new circle
            }
        }
    }

    void keyDown(int key, int mods) {
        if (key == GLFW_KEY_UP) {
            // increase size of circle
        }
        else if (key == GLFW_KEY_DOWN) {
            // decrease size of circle
        }
        else if (key == GLFW_KEY_LEFT) {
            // decrease alpha
        }
        else if (key == GLFW_KEY_RIGHT) {
            // increase alpha
        }
        else if (key == GLFW_KEY_C) {
            // clear vector of circles
            circles = {};
        }
    }
    void draw() override {
        background(0.95f, 0.95f, 0.95f); // parameters: r, g, b

        // todo : draw pallette
        color(0.1f, 0.1f, 0.1f);
        square(width()/2.0f, 35, width(), 70);
        paletteColor(1);
        circle(width() / 10.0f, 35, 35);
        paletteColor(2);
        circle(width() / 5.0f, 35, 35);
        paletteColor(3);
        circle(width() / 10.0f * 3, 35, 35);
        paletteColor(4);
        circle(width() / 10.0f * 4.0f, 35, 35);
        paletteColor(5);
        circle(width() / 2.0f, 35, 1);
        paletteColor(6);
        circle(width() / 10.0f * 6.0f, 35, 35);
        paletteColor(7);
        circle(width() / 10.0f * 7.0f, 35, 35);
        paletteColor(8);
        circle(width() / 10.0f * 8.0f, 35, 35);
        paletteColor(9);
        circle(width() / 10.0f * 9.0f, 35, 35);
        paletteColor(10);
        circle(width() / 10.0f, 35, 35);
        for (float* c : circles) {
            paletteColor(c[0]);
            circle(c[1], c[2], c[3]);
        }
    }
};

int main() {
  MyWindow window(500, 500);
  window.run();
}
