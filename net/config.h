#ifndef HERO_CONFIG_H
#define SERVER_PORT 8090
#define SERVER_INET_ADDR "127.0.0.1"
#define RECV_MAX_BUFFER_SIZE 4096 * 1024
#define SEND_MAX_BUFFER_SIZE 4096 * 1024
#define MAX_BACK_LOG 128
#define TRUE 1
#define FALSE 0
#define USER_NAME "pay"
#define PASS_WORD "MiraCle"
#define MAX_FRAME_SIZE (RECV_MAX_BUFFER_SIZE-MYSQL_HEADER_LEN)
#endif