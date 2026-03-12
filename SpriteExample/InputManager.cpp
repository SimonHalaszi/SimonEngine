#include "InputManager.hpp"
#include <iostream>
#include <cctype>

void INPUTMANAGERprocSpecialKeys(int key, int x, int y) {
    int k = mapSpecialKey(key);
    if (k != -1) InputManager::getInstance().specialKeyDown(k);
}

void INPUTMANAGERprocSpecialKeysUp(int key, int x, int y) {
    int k = mapSpecialKey(key);
    if (k != -1) InputManager::getInstance().specialKeyUp(k);
}

void INPUTMANAGERprocKeys(unsigned char key, int x, int y) {
    int code = static_cast<int>(key);
    char ch = std::isprint(static_cast<unsigned char>(key)) ? static_cast<char>(key) : '?';
    InputManager::getInstance().keyDown(key);
}

void INPUTMANAGERprocKeysUp(unsigned char key, int x, int y) {
    int code = static_cast<int>(key);
    char ch = std::isprint(static_cast<unsigned char>(key)) ? static_cast<char>(key) : '?';
    InputManager::getInstance().keyUp(key);
}

void INPUTMANAGERprocMouse(int button, int state, int x, int y) {
    if (button == 3 || button == 4) {
        bool up = (button == 3);
        InputManager::getInstance().registerScroll(button);
        return;
    }

    if (state == GLUT_DOWN) {
        InputManager::getInstance().mouseButtonDown(button, x, y);
    }
    else {
        InputManager::getInstance().mouseButtonUp(button, x, y);
    }
}

void INPUTMANAGERmouseMove(int x, int y) {
    InputManager::getInstance().mouseMove(x, y);
}

void INPUTMANAGERpassiveMouseMove(int x, int y) {
    InputManager::getInstance().mouseMove(x, y);
}

int mapSpecialKey(int key) {
    switch (key) {
    case GLUT_KEY_LEFT:   return 0;
    case GLUT_KEY_UP:     return 1;
    case GLUT_KEY_RIGHT:  return 2;
    case GLUT_KEY_DOWN:   return 3;
    case GLUT_KEY_F1:     return 4;
    case GLUT_KEY_F2:     return 5;
    case GLUT_KEY_F3:     return 6;
    case GLUT_KEY_F4:     return 7;
    case GLUT_KEY_F5:     return 8;
    case GLUT_KEY_F6:     return 9;
    case GLUT_KEY_F7:     return 10;
    case GLUT_KEY_F8:     return 11;
    default: return -1;
    }
}