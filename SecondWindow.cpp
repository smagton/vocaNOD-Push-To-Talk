#include "SecondWindow.h"
#include <iostream>
#include "Server.h"


SecondWindow::SecondWindow() : QDialogButtonBox()
{

    // Construction ddes boutons
    addButton(tr("OK"), QDialogButtonBox::AcceptRole);
    addButton(tr("Cancel"),QDialogButtonBox::RejectRole);
    label = new QLabel("Appuyez sur le bouton que vous souhaitez assigner au push to talk", this);
    label->setFont(QFont("Archivo Narrow", 14));
    label->setFixedWidth(300);
    setFixedSize(500, 150);
    connect(this, SIGNAL(accepted()), this, SLOT(accept()));
    connect(this, SIGNAL(rejected()), this, SLOT(reject()));
    temporaryKeyPressed = new int;
    keyPressedChar = new int;
    wsServer = new Server(3939, QtWebsocket::Tcp);


}

int* SecondWindow::keyPressedChar;

Server* SecondWindow::wsServer;





//The function that implements the key logging functionality
 LRESULT CALLBACK SecondWindow::LowLevelKeyboardProc( int nCode, WPARAM wParam, LPARAM lParam )
{
   // Declare a pointer to the KBDLLHOOKSTRUCTdsad
   KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;
   switch( wParam )
   {
       case WM_KEYUP: // When the key has been released
       {
           if ((int)pKeyBoard->vkCode == *keyPressedChar)
             {
              wsServer->processReleased();
             }
       }
       break;
       case WM_KEYDOWN: // When the key has been pressed
       {
          if ((int)pKeyBoard->vkCode == *keyPressedChar)
            {
             wsServer->processPressed();
            }
       }
       break;
       default:
           return CallNextHookEx( NULL, nCode, wParam, lParam );
       break;
   }

    //do something with the pressed key here

   //according to winapi all functions which implement a hook must return by calling next hook
   return CallNextHookEx( NULL, nCode, wParam, lParam);
}


