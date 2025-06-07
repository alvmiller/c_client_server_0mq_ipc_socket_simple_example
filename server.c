//  Hello World server
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

// https://github.com/zeromq/cppzmq
// https://zeromq.org/get-started/
// https://zeromq.org/languages/c/

// sudo apt-get install gnutls-bin
// sudo apt-get install libczmq-dev
// gcc -o client client_zmq.c -lzmq
// gcc -o server server_zmq.c -lzmq

int main (void)
{
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);

    while (1) {
        char buffer [10];
        zmq_recv (responder, buffer, 10, 0);
        printf ("Received Hello\n");
        sleep (1);          //  Do some 'work'
        zmq_send (responder, "World", 5, 0);
    }
    return 0;
}
