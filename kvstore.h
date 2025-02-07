

#ifndef _KVSTORE_H_
#define _KVSTORE_H_

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


#define BUFFER_LENGTH		512

typedef int (*RCALLBACK)(int fd);

// conn, fd, buffer, callback
struct conn_item {
	int fd;
	
	char rbuffer[BUFFER_LENGTH];
	int rlen;
	char wbuffer[BUFFER_LENGTH];
	int wlen;

	union {
		RCALLBACK accept_callback;
		RCALLBACK recv_callback;
	} recv_t;
	RCALLBACK send_callback;
};
// libevent --> 

int epoll_entry(void);
int kvstore_request(struct conn_item *item);

void *kvstore_malloc(size_t size);
void kvstore_free(void *ptr);
// 引入内存池的时候不用改代码，只需要改这两个接口即可

#define ENABLE_ARRAY_KVENGINE	1
#if ENABLE_ARRAY_KVENGINE

struct kvs_array_item {
	char *key;
	char *value;   
};

#define KVS_ARRAY_SIZE		1024

int kvstore_array_set(char *key, char *value);    
char* kvstore_array_get(char *key);

#endif

#endif