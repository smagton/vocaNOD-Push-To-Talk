vocaNOD-Push-To-Talk
====================

Allowing push to talk to web applications

## Overview

vocaNOD's Push To Talk is a tool for setting up push to talk into [our website](www.vocanod.com) . It uses [qtwebsockets](https://github.com/qtproject/qtwebsockets) and [Qt Creator](https://qt-project.org/wiki/Category:Tools::QtCreator). 
The application acts like a websocket server listening incoming connections on  the port 3939. Windows Hooks are used for key event handling even if the application does not has focus.

## Requirements

* Qt 5.x (built with MinGW)
* Works on Windows

## License

MIT

