#include "OVMT.h"
#include <TlHelp32.h>
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
#include <wtypes.h>
#include "macroConfig.h"
#include "fsfml.h"


///*
int main() {
    try {
       /* HWND hwnd = GetConsoleWindow();
        ShowWindow(hwnd, SW_SHOW);*/
        //OVMT sl;
        //sl.sys.bringWindowToFront(hwnd);
        //SetFocus(hwnd);
        //sl.startMacro();
        //sl.macroLoop();
        fsfml sf;
        sf.startSFML();
        return 0;
    }
    catch (int k) {
        std::cout << "Configuration failed" << std::endl;
    }
    return 0;

}//*/