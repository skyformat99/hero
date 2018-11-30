#include "packet.h"
#include "packet_const.h"
#include <string.h>
#include "../network.h"
#include "../basic.h"
#include <stdatomic.h>
#include <stdlib.h>

atomic_int g_client_id=0;

unsigned char* random_seed(int size);

void packet(){
    printf("this is packet\n");
}

int caculate_handshake_size(){
    int size = 1;
    size += strlen(SERVER_VERSION);
    size +=5; // 1+4;
    size += 8; // for seed 
    size += 19; // 1+2+1+2+13
    size += 12; // for rest of scrambleBuff
    size +=1;
    return size;
}

hand_shake_packet* get_handshake_packet(){
    hand_shake_packet* hand_shake = (hand_shake_packet*)mem_alloc(sizeof(hand_shake_packet));
    hand_shake->header.packet_id=0;
    hand_shake->protol_version=10;
    hand_shake->server_version=SERVER_VERSION;
    hand_shake->thread_id=g_client_id++;
    hand_shake->seed= random_seed(8);
    hand_shake->server_capabilities=get_server_capacities();
    hand_shake->server_charset_index = UTF8_CHAR_INDEX;
    hand_shake->server_status=2;
    hand_shake->rest_of_scramble_buff= random_seed(12);
    return hand_shake;
}

ok_packet* get_ok_packet(){
    ok_packet* okay = (ok_packet*)mem_alloc(sizeof(ok_packet));
    okay->affected_rows = 0;
    // todo;
    return okay;
}

unsigned char* random_seed(int size){
    unsigned char* buffer = mem_alloc(size);
    for(int i=0 ;i < size ;i++){
        buffer[i] = rand()%256;
    }
    return buffer;
}


void free_handshake_packet(hand_shake_packet* packet){
    mem_free(packet->seed);
    mem_free(packet->rest_of_scramble_buff);
    mem_free(packet);
}

packet_buffer* get_handshake_buff(){
    // 还需要加上头长度
    return get_packet_buffer(caculate_handshake_size()+MYSQL_HEADER_LEN);
}

