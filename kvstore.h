

#ifndef _KVSTORE_H_
#define _KVSTORE_H_

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

#define ENABLE_ARRAY_KVENGINE	1
#if ENABLE_ARRAY_KVENGINE

struct kvs_array_item {
	char *key;
	char *value;   
};

#define KVS_ARRAY_SIZE		1024

#endif

#endif