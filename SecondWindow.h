#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include "Server.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>
#include <QString>
#include <QDialogButtonBox>
#include <QObject>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class SecondWindow : public QDialogButtonBox
{
    Q_OBJECT
    public:
    SecondWindow();
    int getKeyPressed();
    static LRESULT CALLBACK LowLevelKeyboardProc( int nCode, WPARAM wParam, LPARAM lParam );
    void convert(QString *string);
    static Server *wsServer;

    public slots:
    void accept();
    void reject();


    protected:
     void keyPressEvent(QKeyEvent *event);

    private:
    QDialogButtonBox *buttonBox;
    int *temporaryKeyPressed;
    static int *keyPressedChar;
    static char temp;
    QLabel *label;
    QKeyEvent *keyEvt;
};
#endif // SECONDWINDOW_H
