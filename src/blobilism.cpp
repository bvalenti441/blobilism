#include <iostream>
#include <vector>
#include "tinygl-cpp.h"
using namespace tinygl;

struct Circle {
    float color[3];
    float x;
    float y;
    float diameter;
    float transparency;
};

class MyWindow : public Window {
private:

    // todo: create member variables for 
    // current circle size
    int currBrushSize = 10;
    // current transparency
    float currTransparency = 1.0f;
    // current color
    float currColor[3];
    // list of circles to draw each frame
    std::vector<Circle> circles; // color, x position, y position, brush size

public:

    // color palette
    static const float red[3];
    static const float green[3];
    static const float blue[3];
    static const float yellow[3];
    static const float black[3];
    static const float gray[3];

    MyWindow(int w, int h) : Window(w, h) {}

    int getCurrBrushSize() {
        return this->currBrushSize;
    }

    void changeBrushSize(int change) {
        if (this->currBrushSize + change < 1) {
            this->currBrushSize = 1;
            return;
        }
        else if (currBrushSize == 1) {
            this->currBrushSize = change;
        }
        this->currBrushSize += change;
    }

    float getTransparency() {
        return this->currTransparency;
    }

    void changeTransparency(float change) {
        if (currTransparency + change < 0){
            this->currTransparency = 0;
            return;
        } 
        else if (currTransparency + change > 1.0f) {
            this->currTransparency = 1.0f;
            return;
        }
        this->currTransparency += change;
    }

    float* getCurrColor() {
        return this->currColor;
    }

    void setCurrColor(const float* newColor) {
        this->currColor[0] = newColor[0];
        this->currColor[1] = newColor[1];
        this->currColor[2] = newColor[2];
    }

    std::vector<Circle>* getCircles() {
        return &(this->circles);
    }

    void setCircles(std::vector<Circle> vec) {
        this->circles = vec;
    }

    void setup() override {
        setCircles({});
        std::cout << "Window size: " << width() << ", " << height() << std::endl;
    }

    virtual void mouseMotion(int x, int y, int dx, int dy) {
        if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
            // todo: store a circle with the current color, size, x, y
            Circle newCircle;
            float* circColor = getCurrColor();
            newCircle.color[0] = circColor[0];
            newCircle.color[1] = circColor[1];
            newCircle.color[2] = circColor[2];
            newCircle.x = x;
            newCircle.y = y;
            newCircle.diameter = getCurrBrushSize();
            newCircle.transparency = getTransparency();
            (*getCircles()).push_back(newCircle);
        }
    }

    virtual void mouseDown(int button, int mods) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            // todo: check if user clicked a color 
            float mx = mouseX();  // current mouse pos x
            float my = mouseY();  // current mouse pos y
            
            // pallete circles
            if (sqrt(pow(mx - (width() / 7.0f), 2) + pow(my - 35, 2)) <= 35) {
                setCurrColor(red);
            }
            else if (sqrt(pow(mx - width() / 7.0f * 2.0f, 2) + pow(my - 35, 2)) <= 35) { 
                setCurrColor(green);
                std::cout << "green" << std::endl;
            }
            else if (sqrt(pow(mx - width() / 7.0f * 3.0f, 2) + pow(my - 35, 2)) <= 35) { //pallette circles
                setCurrColor(blue);
                std::cout << "blue" << std::endl;
            }
            else if (sqrt(pow(mx - width() / 7.0f * 4.0f, 2) + pow(my - 35, 2)) <= 35) { //pallette circles
                setCurrColor(yellow);
                std::cout << "yellow" << std::endl;
            }
            else if (sqrt(pow(mx - width() / 7.0f * 5.0f, 2) + pow(my - 35, 2)) <= 35) { //pallette circles
                setCurrColor(black);
                std::cout << "black" << std::endl;
            }
            else if (sqrt(pow(mx - width() / 7.0f * 6.0f, 2) + pow(my - 35, 2)) <= 35) { //pallette circles
                setCurrColor(gray);
                std::cout << "gray" << std::endl;
            }
            else if (my <= 70) {
                return;
            }
            else {
                // add new circle to list of circles to draw every frame
                Circle newCircle;
                float* circleColor = getCurrColor();
                newCircle.color[0] = circleColor[0];
                newCircle.color[1] = circleColor[1];
                newCircle.color[2] = circleColor[2];
                newCircle.diameter = getCurrBrushSize();
                newCircle.transparency = getTransparency();
                (*getCircles()).push_back(newCircle);
            }
        }
    }

    void keyDown(int key, int mods) {
        if (key == GLFW_KEY_UP) {
            // increase size of circle
            changeBrushSize(10);
        }
        else if (key == GLFW_KEY_DOWN) {
            // decrease size of circle
            changeBrushSize(-10);
        }
        else if (key == GLFW_KEY_LEFT) {
            // decrease transparency
            changeTransparency(-0.1f);
        }
        else if (key == GLFW_KEY_RIGHT) {
            // increase transparency
            changeTransparency(0.1f);
        }
        else if (key == GLFW_KEY_C) {
            // clear canvas
            setCircles({});
        }
    }

    void draw() override {

        background(0.95f, 0.95f, 0.95f); // parameters: r, g, b

        // todo : draw pallette
        color(0.1f, 0.1f, 0.1f);
        square(width()/2.0f, 35, width(), 70);
        
        color(red[0], red[1], red[2]);
        circle(width() / 7.0f, 35, 35);
        color(green[0], green[1], green[2]);
        circle(width() / 7.0f * 2.0f, 35, 35);
        color(blue[0], blue[1], blue[2]);
        circle(width() / 7.0f * 3.0f, 35, 35);
        color(yellow[0], yellow[1], yellow[2]);
        circle(width() / 7.0f * 4.0f, 35, 35);
        color(black[0], black[1], black[2]);
        circle(width() / 7.0f * 5.0, 35, 1);
        color(gray[0], gray[1], gray[2]);
        circle(width() / 7.0f * 6.0f, 35, 35);

        // draw all stored circles the user input
        for (Circle c : (*getCircles())) {
            color(c.color[0], c.color[1], c.color[2], c.transparency);
            circle(c.x, c.y, c.diameter);
        }
    }
};

// initialize public color variables
const float MyWindow::red[3] = {1.0f, 0, 0};
const float MyWindow::green[3] = { 0, 1.0f, 0 };
const float MyWindow::blue[3] = { 0, 0, 1.0f };
const float MyWindow::yellow[3] = { 1.0f, 1.0f, 0 };
const float MyWindow::black[3] = { 0, 0, 0 };
unsigned char grayHex = '0x80';
const float MyWindow::gray[3] = { grayHex/255.0f, grayHex/255.0f, grayHex/255.0f };

int main() {
    MyWindow window(500, 500);
    window.run();
}
