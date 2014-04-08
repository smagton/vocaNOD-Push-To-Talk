#ifndef OURWINDOW_H
#define OURWINDOW_H

#include <QApplication>
#include<unordered_map>
#include <QMainWindow>
#include <QPushButton>
#include <QMouseEvent>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "Server.h"
#include <QKeyEvent>
#include <QPixmap>
#include <QSystemTrayIcon>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
class OurWindow : public QMainWindow // On hérite de QWidget (IMPORTANT)
{
    Q_OBJECT

    public:
    OurWindow();
    void convert(QString *string);
    static Server *wsServer;
    static LRESULT CALLBACK LowLevelKeyboardProc( int nCode, WPARAM wParam, LPARAM lParam );
    static LRESULT CALLBACK LowLevelMouseProc( int nCode, WPARAM wParam, LPARAM lParam );

    public slots:
    void buttonClicked();
    void changeState(bool state);
    void keyAssignedSlot();
    void handleActivatedSystemTrayIconSlot(QSystemTrayIcon::ActivationReason reason);
    void about();

    signals:
    void keyAssignedSignal();

    protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);

    private:
    std::unordered_map<int,std::string> buttonMapping;
    bool buttonState; //true if the user clicked to assign, false otherwise
    static int *temporaryKeyPressed;
    static int *keyPressedChar;
    void accept();
    QSystemTrayIcon *sticon;
    QLabel *stateLabel;
    QLabel *imgStateLabel;
    QLabel *keyAssignedLabel;
    QPixmap *redDot;
    QPixmap redDotScaled;
    QPixmap *greenDot;
    QPixmap greenDotScaled;
    bool active;
    void createActions();
    void createMenus();
    QLabel *vocaNODLogoLabel;
    QLabel *pushToTalkLogoLabel;
    QPushButton *m_bouton;
    QMenu *fileMenu;
    QMenu *systemTrayMenu;
    QAction *newAct;
    QAction *aboutAct;
    QAction *exitAct;
    QAction *systemTrayOpenAct;
    QAction *systemTrayCloseAct;
    QPoint *cursorPosition;
    QLabel *infoLabel;
    QVBoxLayout *alignmentGroup;
    QKeyEvent *keyEvt;
    QIcon *icon;
};



#endif // OURWINDOW_H
