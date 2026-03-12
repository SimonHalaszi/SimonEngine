#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <array>

enum KeyState { KEYSTATE_UP, KEYSTATE_DOWN, KEYSTATE_PRESSED, KEYSTATE_RELEASED };
enum MouseButton { MOUSEBUTTON_LEFT = 0, MOUSEBUTTON_MIDDLE = 1, MOUSEBUTTON_RIGHT = 2, MOUSEBUTTON_SCROLLUP = 3, MOUSEBUTTON_SCROLLDOWN = 4 };

class InputManager {
    public:
        static InputManager& getInstance() {
            static InputManager instance;
            return instance;
        }

        void keyDown(unsigned char key) { keyCurrent_[key] = true; }
        void keyUp(unsigned char key) { keyCurrent_[key] = false; }

        bool isDown(unsigned char key)      const { return keyCurrent_[key]; }
        bool isPressed(unsigned char key)   const { return keyCurrent_[key] && !keyPrevious_[key]; }
        bool isReleased(unsigned char key)  const { return !keyCurrent_[key] && keyPrevious_[key]; }

        void specialKeyDown(int key)    { if (key >= 0 && key < int(specialKeyCurrent_.size())) specialKeyCurrent_[key] = true; }
        void specialKeyUp(int key)      { if (key >= 0 && key < int(specialKeyCurrent_.size())) specialKeyCurrent_[key] = false; }

        bool isSpecialKeyDown(int key)      const { return (key >= 0 && key < int(specialKeyCurrent_.size())) ? specialKeyCurrent_[key] : false; }
        bool isSpecialKeyPressed(int key)   const { return (key >= 0 && key < int(specialKeyCurrent_.size())) ? (specialKeyCurrent_[key] && !specialKeyPrevious_[key]) : false; }
        bool isSpecialKeyReleased(int key)  const { return (key >= 0 && key < int(specialKeyCurrent_.size())) ? (!specialKeyCurrent_[key] && specialKeyPrevious_[key]) : false; }

        void mouseButtonDown(int button, int x, int y)  { if (button >= 0 && button < int(mouseCurrent_.size())) mouseCurrent_[button] = true; }
        void mouseButtonUp(int button, int x, int y)    { if (button >= 0 && button < int(mouseCurrent_.size())) mouseCurrent_[button] = false; }

        bool isMouseButtonDown(MouseButton button) const {
            if (button == MOUSEBUTTON_SCROLLUP) return scrollUpThisFrame_;
            if (button == MOUSEBUTTON_SCROLLDOWN) return scrollDownThisFrame_;
            return mouseCurrent_[button];
        }
        
        bool isMouseButtonPressed(MouseButton button) const {
            if (button == MOUSEBUTTON_SCROLLUP) return scrollUpThisFrame_;
            if (button == MOUSEBUTTON_SCROLLDOWN) return scrollDownThisFrame_;
            return mouseCurrent_[button] && !mousePrevious_[button];
        }
        
        bool isMouseButtonReleased(MouseButton button) const {
            if (button == MOUSEBUTTON_SCROLLUP || button == MOUSEBUTTON_SCROLLDOWN) return false;
            return !mouseCurrent_[button] && mousePrevious_[button];
        }

        void mouseMove(int x, int y) {
            mouseDeltaX_ = x - mouseX_;
            mouseDeltaY_ = y - mouseY_;
            mouseX_ = x;
            mouseY_ = y;
        }

        int mouseX()        const { return mouseX_; }
        int mouseY()        const { return mouseY_; }
        int mouseDeltaX()   const { return mouseDeltaX_; }
        int mouseDeltaY()   const { return mouseDeltaY_; }

        void registerScroll(int button) {
            if (button == 3) scrollUpThisFrame_ = true;
            if (button == 4) scrollDownThisFrame_ = true;
        }

        void update() {
            scrollUpThisFrame_ = false;
            scrollDownThisFrame_ = false;

            keyPrevious_ = keyCurrent_;
            mousePrevious_ = mouseCurrent_;
            specialKeyPrevious_ = specialKeyCurrent_;

            mouseDeltaX_ = mouseDeltaY_ = 0;
        }

    private:
        InputManager() : mouseX_(0), mouseY_(0), mouseDeltaX_(0), mouseDeltaY_(0) {}
        ~InputManager() {}

        bool scrollUpThisFrame_ = false;
        bool scrollDownThisFrame_ = false;

        std::array<bool, 256> keyCurrent_ = {};
        std::array<bool, 256> keyPrevious_ = {};

        std::array<bool, 8> mouseCurrent_ = {};
        std::array<bool, 8> mousePrevious_ = {};

        std::array<bool, 12> specialKeyCurrent_ = {};
        std::array<bool, 12> specialKeyPrevious_ = {};

        int mouseX_, mouseY_;
        int mouseDeltaX_, mouseDeltaY_;
};

void INPUTMANAGERprocSpecialKeys(int key, int x, int y);
void INPUTMANAGERprocSpecialKeysUp(int key, int x, int y);
void INPUTMANAGERprocKeys(unsigned char key, int x, int y);
void INPUTMANAGERprocKeysUp(unsigned char key, int x, int y);
void INPUTMANAGERprocMouse(int button, int state, int x, int y);
void INPUTMANAGERmouseMove(int x, int y);
void INPUTMANAGERpassiveMouseMove(int x, int y);
int mapSpecialKey(int key);

#endif // INPUT_MANAGER_HPP