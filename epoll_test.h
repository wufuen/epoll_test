#ifndef _EPOLL_TEST_H_
#define _EPOLL_TEST_H_
struct conn{
    int id;
    int socket;
    int transfer_rx;
    int transfer_tx;
    int status;
};

struct conn_set{
    int size;
    struct conn *e_conn;
};
#endif
