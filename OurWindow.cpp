#include "OurWindow.h"
#include <QVBoxLayout>
#include <QActionGroup>
#include <QStatusBar>
#include <QMenuBar>
#include <QIcon>
#include <QPixmap>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QMessageBox>

OurWindow::OurWindow() : QMainWindow ()
{
    //we initialize here some variables
    active = false;
    temporaryKeyPressed = new int;
    keyPressedChar = new int(0);
    wsServer = new Server(3939, QtWebsocket::Tcp);
  //  buttonMapping = new std::unordered_map<int,std::string>;

  /*  //We set the dictionary for button mapping, useful when we'll want to parse the key event
    buttonMapping[16777216] = "Escape";
    buttonMapping[16777217] = "Tab";
    buttonMapping[16777219] = "BackSpace";
    buttonMapping[16777221] = "Enter";
    buttonMapping[16777234] = "Left";
    buttonMapping[16777235] = "Up";
    buttonMapping[16777236] = "Right";
    buttonMapping[16777237] = "Left";
    buttonMapping[16777238] = "PageUp";
    buttonMapping[16777239] = "PageDown";
    buttonMapping[16777248] = "Shift";
    buttonMapping[16777249] = "Control";
    buttonMapping[16777251] = "Alt";
    buttonMapping[16781571] = "Alt Gr";
    buttonMapping[16777252] = "CAPS LOCK §§";
    buttonMapping[16777216] = "Enter";
    buttonMapping[16777216] = "Enter";
    buttonMapping[16777216] = "Enter";
    buttonMapping[16777216] = "Enter";
    buttonMapping[16777216] = "Enter";
    buttonMapping[16777216] = "Enter";
    buttonMapping[16777216] = "Enter";
    buttonMapping[16777216] = "Enter";
    buttonMapping[16777216] = "Enter";
    buttonMapping[16777216] = "Enter";
    buttonMapping[16777216] = "Enter";
    buttonMapping[16777216] = "Enter";
    buttonMapping[16777216] = "Enter";
    buttonMapping[16777216] = "Enter";
    buttonMapping[16777216] = "Enter";

    Not finished yet (and boooooring), it will be done for 2.0 */

    //We connect the server to the changeState so that the dot will change if you are connected
     QObject::connect(wsServer,SIGNAL(state(bool)),this,SLOT(changeState(bool)));


     //Graphical stuff

    //vocaNOD image , it's the vocaNODLogoLabel
    QPixmap pic(":/images/vocaNOD.png");
    QPixmap scaled=pic.scaled ( 200, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation );

    vocaNODLogoLabel = new QLabel;
    vocaNODLogoLabel->setPixmap(scaled);
    vocaNODLogoLabel->setAlignment(Qt::AlignCenter);

    //Push to talk logo and integration

    QPixmap picptt(":/images/PushToTalk.png");
    QPixmap scaledptt=picptt.scaled ( 100, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation );

    pushToTalkLogoLabel = new QLabel;
    pushToTalkLogoLabel->setPixmap(scaledptt);
    pushToTalkLogoLabel->setAlignment(Qt::AlignCenter);

    //The state lign + their logo being initialized
    stateLabel = new QLabel (tr("State : "));
    keyAssignedLabel = new QLabel(tr("Key assigned : "));

    redDot = new QPixmap(":/images/red.png");
    redDotScaled=redDot->scaled ( 15, 15, Qt::KeepAspectRatio, Qt::SmoothTransformation );

    greenDot = new QPixmap(":/images/green.png");
    greenDotScaled=greenDot->scaled ( 15, 15, Qt::KeepAspectRatio, Qt::SmoothTransformation );


    imgStateLabel = new QLabel;
    imgStateLabel->setPixmap(redDotScaled); // red dot at first
    imgStateLabel->setAlignment(Qt::AlignLeft);


    // construction of the button to assign a key
    m_bouton = new QPushButton("Assign key", this);
    QObject::connect(m_bouton,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    QObject::connect(this,SIGNAL(keyAssignedSignal()),this,SLOT(keyAssignedSlot()));
    m_bouton->setFont(QFont("Archivo Narrow", 11));
    m_bouton->setCursor(Qt::PointingHandCursor);
    m_bouton->setFocusPolicy(Qt::NoFocus);


    //We are now creating the widget that will be displayed
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    //This bottom filler widget is to set some space between the the other widgets
    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    //Horizontal box layout, this will put the widgets horizontally (this is for the bar in the bottom of the application)
    QHBoxLayout *stateLayout = new QHBoxLayout;
    stateLayout->setSpacing(10);
    stateLayout->addWidget(stateLabel);
    stateLayout->addWidget(imgStateLabel);
    stateLayout->addWidget(keyAssignedLabel);
    stateLayout->addStretch();

    //Vertical box layout, for the other widgets that we want displayed vertically
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->addWidget(vocaNODLogoLabel);
    layout->setSpacing(10);
    layout->addWidget(pushToTalkLogoLabel);
    layout->addWidget(bottomFiller);
    layout->addWidget(m_bouton);
    layout->addLayout(stateLayout);
    widget->setLayout(layout);



    //Nothing in the message of the status bar, this is for avoiding the status bar to pop, like this it
    // will already be popped
    QString message = tr("");
    statusBar()->showMessage(message);


    //The icon of the window
    icon = new QIcon(":/images/favicon.png");
    setWindowIcon(*icon);
    //Now the system tray Icon to put a little bit of swag into our application
    sticon = new QSystemTrayIcon(this);
    sticon->setIcon(*icon);


    //Window title and size
    setWindowTitle(tr("Vocanod's Push To Talk"));
    setFixedSize(250,200);


    //This is for the menus, the one displayed in the application and the contextual menu of the system tray icon
    createActions();
    createMenus();


}

//We've got static variables, we need to do that or the compiler won't be happy
int* OurWindow::keyPressedChar;

Server* OurWindow::wsServer;

int* OurWindow::temporaryKeyPressed;


//Create Menu et actions
void OurWindow::createActions(){


    //This is for the button of assigning a key
    newAct = new QAction(tr("&Assign key"), this);
    newAct->setStatusTip(tr("Assign your key for push to talk"));


    //The about and help action
    aboutAct = new QAction(tr("Help and About"),this);
    aboutAct->setStatusTip(tr("This will explain you how you can configure the push to talk"));

    //For leaving the application
    exitAct = new QAction(tr("Exit"),this);
    exitAct->setStatusTip(tr("Exit the application"));


    //System tray's actions
    systemTrayOpenAct = new QAction(tr("&Open"),this);
    systemTrayCloseAct = new QAction(tr("&Close"),this);

    //Then connect them to the right slots
    connect(newAct, SIGNAL(triggered()), this, SLOT(buttonClicked()));
    connect(aboutAct,SIGNAL(triggered()), this, SLOT(about()));
    connect(exitAct,SIGNAL(triggered()),this,SLOT(close()));
    connect(systemTrayOpenAct,SIGNAL(triggered()),this,SLOT(show()));
    connect(systemTrayCloseAct,SIGNAL(triggered()),this,SLOT(close()));
    connect(sticon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(handleActivatedSystemTrayIconSlot(QSystemTrayIcon::ActivationReason)));
}


void OurWindow::createMenus()
 {

    //configuration of the menu inside the app
    fileMenu = menuBar()->addMenu(tr("&Menu"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(aboutAct);
    fileMenu->addAction(exitAct);


    //System tray menu configuration
    systemTrayMenu = new QMenu(this);
    systemTrayMenu->addAction(systemTrayOpenAct);
    systemTrayMenu->addAction(systemTrayCloseAct);


    //This is for saying that the systemtray icon is connected to the context menu we just created
    sticon->setContextMenu(systemTrayMenu);



 }

void OurWindow::handleActivatedSystemTrayIconSlot(QSystemTrayIcon::ActivationReason reason){

//This is just a function so that the window is displayed if we click or double click on the system tray icon
    switch(reason){

        case QSystemTrayIcon::DoubleClick:
            this->show();
            break;
        case QSystemTrayIcon::Trigger:
            this->show();
            break;
        default:
            break;

    }

}

void OurWindow::about()
{
    //The about box is here
    QMessageBox::about(this, tr("About"),
            tr("<p>This application allows you to enable push to talk to the vocaNOD website </p>"
               "<p>You need to click on the 'Assign a key' button (or in the Menu Panel) then to type the key"
               "you want enabled for push to talk, it can be a keyboard key or a mouse button</p>"
               "<p> The state dot is a visual indicator to tell whether the application is connected or not to"
               "your web browser. If you opened the executable before opening the web browser then it should be green"
               "otherwise you need to click on the 'Enable push to talk' button. Once you assigned a key and the "
               "indicator is green, the push to talk option is enabled.</p>"
               "<p>© vocaNOD 2014</p>"));
}

void OurWindow::closeEvent(QCloseEvent *event)
{
    if (event->spontaneous()){ //This is to know if you click on the "X" (this case) button or on a exit button on a menu
        sticon->show();
        sticon->showMessage("vocaNOD Push To Talk running in notification tray","Click to re-open it");
        this->hide();
        event->ignore();
    }
    else{ //This means you clicked on a exit button on a menu, so the app will close
        event->accept();
    }
}




//push to talk functions

//Reimplementing events


void OurWindow::mousePressEvent(QMouseEvent *event)
{

    *temporaryKeyPressed = event->button();
    if (active == true){ //Since this function is called everytime a mouse click is pressed, we have to put this boolean
    statusBar()->showMessage("You wish to assign a mouse button");
    keyAssignedLabel->setText("Key assigned : mouse button "); //Can't do much better since there is no explicit names for mouse buttons
    accept();
    emit keyAssignedSignal(); //We emit the fact that we assigned a key, so that the label will be reinitialized
    active = false;
    }
}


void OurWindow::keyPressEvent(QKeyEvent *event)
{

    //Same as the mouse press event
    *temporaryKeyPressed = event->key();
    if (active == true){
      /*  switch(event->key()){
          case 16777216: //Escape
                statusBar()->showMessage("You wish to assign key Escape");
                keyAssignedLabel->setText("Key assigned : Escape ");
                break;
        case 16777217: //Tab
              statusBar()->showMessage("You wish to assign key Tab");
              keyAssignedLabel->setText("Key assigned : Tab ");
              break;
        case 16777219: //BackSpace
              statusBar()->showMessage("You wish to assign key BackSpace");
              keyAssignedLabel->setText("Key assigned : BackSpace ");
              break;
        case 16777221: //Enter
              statusBar()->showMessage("You wish to assign key Enter");
              keyAssignedLabel->setText("Key assigned : Enter ");
              break;
        case 16777234: //Left
              statusBar()->showMessage("You wish to assign key Left");
              keyAssignedLabel->setText("Key assigned : Left ");
              break;
        case 16777235: //Up
              statusBar()->showMessage("You wish to assign key Up");
              keyAssignedLabel->setText("Key assigned : Up ");
              break;
        case 16777236: //Right
              statusBar()->showMessage("You wish to assign key Right");
              keyAssignedLabel->setText("Key assigned : Right ");
              break;
        case 16777237: //Down
              statusBar()->showMessage("You wish to assign key Down");
              keyAssignedLabel->setText("Key assigned : Down ");
              break;
          default:*/
            statusBar()->showMessage("You wish to assign key " + event->text());
            keyAssignedLabel->setText("Key assigned : " + event->text());
           // break;
      //  } //Not finished yet, this is for allowing the display on keys such as Space, tab, etc...
        accept();
        emit keyAssignedSignal();
        active = false;
    }
}


void OurWindow::accept(){
    //The accept is for assigned a char to keyPressed char that will be used in the several windows hookss
    *keyPressedChar = *temporaryKeyPressed;
}

void OurWindow::buttonClicked(){

    //This method is for assigning a key if you clicked on button "assign a key" in the menu
        m_bouton->setText("Type a key ");
        active = true;
        statusBar()->showMessage("Type a key ");
}

void OurWindow::keyAssignedSlot(){
    //This is to reput the "Assign key" label once you actually assigned a key
    m_bouton->setText("Assign key");
}


void OurWindow::changeState(bool state){

    if (state ==true)
         imgStateLabel->setPixmap(greenDotScaled);
    else
        imgStateLabel->setPixmap(redDotScaled);

}


//Les deux fonctions qui suivent servent à mettre en place les keyboard et mouse logger


//The function that implements the key logging functionality
LRESULT CALLBACK OurWindow::LowLevelKeyboardProc( int nCode, WPARAM wParam, LPARAM lParam )
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


LRESULT CALLBACK OurWindow::LowLevelMouseProc( int nCode, WPARAM wParam, LPARAM lParam )
{
   // Declare a pointer to the KBDLLHOOKSTRUCTdsad
   //MSLLHOOKSTRUCT  *pMouse = (MSLLHOOKSTRUCT  *)lParam;

 switch( wParam )
   {

       case WM_RBUTTONUP: // When the key has been released
       {
          if (*temporaryKeyPressed == *keyPressedChar)
            {
               wsServer->processReleased();
         }
       }
       break;

       case WM_RBUTTONDOWN: // When the key has been pressed
       {

          if (*temporaryKeyPressed == *keyPressedChar)
          {

              wsServer->processPressed();
          }
       }
       break;
     case WM_XBUTTONUP: // When the key has been released
     {


         if (*temporaryKeyPressed == *keyPressedChar)
         {
             wsServer->processReleased();
         }
     }
         break;

     case WM_XBUTTONDOWN: // When the key has been pressed
     {
         if (*temporaryKeyPressed == *keyPressedChar)
         {

             wsServer->processPressed();
         }
     }
     break;
       default:
           return CallNextHookEx( NULL, nCode, wParam, lParam );
       break;
   }


   //according to winapi all functions which implement a hook must return by calling next hook
   return CallNextHookEx( NULL, nCode, wParam, lParam);
}


