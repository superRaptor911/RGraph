#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <string>

namespace rg
{
    class Window;
    class Keyboard
    {
    private:
        
        Keyboard();
        typedef std::pair<std::string, int>  pair;

        // Key bindings
        static inline const std::unordered_map<std::string, int> _key_bindings{ 
            pair("SPACE",32), pair("APOSTROPHE",39), pair("COMMA",44), pair("MINUS",45), 
            pair("PERIOD",46), pair("SLASH",47), pair("0",48), pair("1",49), 
            pair("2",50), pair("3",51), pair("4",52), pair("5",53), 
            pair("6",54), pair("7",55), pair("8",56), pair("9",57), 
            pair("SEMICOLON",59), pair("EQUAL",61), pair("A",65), pair("B",66), 
            pair("C",67), pair("D",68), pair("E",69), pair("F",70), 
            pair("G",71), pair("H",72), pair("I",73), pair("J",74), 
            pair("K",75), pair("L",76), pair("M",77), pair("N",78), 
            pair("O",79), pair("P",80), pair("Q",81), pair("R",82), 
            pair("S",83), pair("T",84), pair("U",85), pair("V",86), 
            pair("W",87), pair("X",88), pair("Y",89), pair("Z",90), 
            pair("LEFT_BRACKET",91), pair("BACKSLASH",92), pair("RIGHT_BRACKET",93), pair("GRAVE_ACCENT",96), 
            pair("WORLD_1",161), pair("WORLD_2",162), pair("ESCAPE",256), pair("ENTER",257), 
            pair("TAB",258), pair("BACKSPACE",259), pair("INSERT",260), pair("DELETE",261), 
            pair("RIGHT",262), pair("LEFT",263), pair("DOWN",264), pair("UP",265), 
            pair("PAGE_UP",266), pair("PAGE_DOWN",267), pair("HOME",268), pair("END",269), 
            pair("CAPS_LOCK",280), pair("SCROLL_LOCK",281), pair("NUM_LOCK",282), pair("PRINT_SCREEN",283), 
            pair("PAUSE",284), pair("F1",290), pair("F2",291), pair("F3",292), 
            pair("F4",293), pair("F5",294), pair("F6",295), pair("F7",296), 
            pair("F8",297), pair("F9",298), pair("F10",299), pair("F11",300), 
            pair("F12",301), pair("F13",302), pair("F14",303), pair("F15",304), 
            pair("F16",305), pair("F17",306), pair("F18",307), pair("F19",308), 
            pair("F20",309), pair("F21",310), pair("F22",311), pair("F23",312), 
            pair("F24",313), pair("F25",314), pair("KP_0",320), pair("KP_1",321), 
            pair("KP_2",322), pair("KP_3",323), pair("KP_4",324), pair("KP_5",325), 
            pair("KP_6",326), pair("KP_7",327), pair("KP_8",328), pair("KP_9",329), 
            pair("KP_DECIMAL",330), pair("KP_DIVIDE",331), pair("KP_MULTIPLY",332), pair("KP_SUBTRACT",333), 
            pair("KP_ADD",334), pair("KP_ENTER",335), pair("KP_EQUAL",336), pair("LEFT_SHIFT",340), 
            pair("LEFT_CONTROL",341), pair("LEFT_ALT",342), pair("LEFT_SUPER",343), pair("RIGHT_SHIFT",344), 
            pair("RIGHT_CONTROL",345), pair("RIGHT_ALT",346), pair("RIGHT_SUPER",347), pair("MENU",348)
         };

         Window *m_window = nullptr;

    public:

        Keyboard(Window *window);
        
        bool isKeyPressed(const std::string &key);
        bool isKeyPressed(const int key_id);
        
        bool isKeyReleased(const std::string &key);
        bool isKeyReleased(const int key_id);



    };    
}

#endif
