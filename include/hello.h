#ifndef HELLO_H
#define HELLO_H
#include<mutex>

extern std::mutex log_mtx;
void handle_client(int client_fd);

#endif
