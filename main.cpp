
#include <QApplication>
#include "OurWindow.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <iostream>
#include "Server.h"




int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(application);
    QApplication app(argc, argv);

    OurWindow *window;
    window = new OurWindow();
    window->show();


    //Retrieve the applications instance
   HINSTANCE instance = GetModuleHandle(NULL);
  //Set a global Windows Hook to capture keystrokes using the function declared above
   HHOOK test1 = SetWindowsHookEx( WH_KEYBOARD_LL,&OurWindow::LowLevelKeyboardProc, instance,0);
   //and the the mouse
   HHOOK test2 = SetWindowsHookEx( WH_MOUSE_LL,&OurWindow::LowLevelMouseProc, instance,0);
    return app.exec();
}
