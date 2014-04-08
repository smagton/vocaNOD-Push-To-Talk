#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include "lib/libwebsockets.h"

class WebSocketServer{
public:
    WebSocketServer();
    static int callback_http(struct libwebsocket_context * smth,struct libwebsocket *wsi,enum libwebsocket_callback_reasons reason, void *user,void *in, size_t len);
    static int callback_dumb_increment(struct libwebsocket_context * smth,struct libwebsocket *wsi,enum libwebsocket_callback_reasons reason,void *user, void *in, size_t len);
    static struct libwebsocket_protocols protocols[];

};


#endif // WEBSOCKET_H
