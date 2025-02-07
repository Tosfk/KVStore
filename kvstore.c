
#include "kvstore.h"

#define KVSTORE_MAX_TOKENS 128

const char *commands[] = {
    "SET", "GET", "DEL", "MOD",
};

// 下一步对比token和commands  
// 每个工程都有字符串和数字的映射关系
// 定义一个枚举

enum {
    KVS_CMD_START = 0,
    KVS_CMD_SET = KVS_CMD_START,
    KVS_CMD_GET,
    KVS_CMD_DEL,
    KVS_CMD_MOD,
    KVS_CMD_COUNT,
};

void *kvstore_malloc(size_t size) {
    return malloc(size);
}

void kvstore_free(void *ptr) {
    return free(ptr);
}

// 分割字符串
int kvstore_split_token(char *msg, char **tokens) {

    if (msg == NULL || tokens == NULL) return -1;

    int idx = 0;

    char *token = strtok(msg, " ");

    while(token != NULL) {
        tokens[idx++] = token;
        token = strtok(NULL, " "); //传入 NULL 作为第一个参数，表示继续从上一次分割的位置开始。如果再次传入 msg，则会重新从头开始分割。
    }
    return idx;
}

// 把协议解析出来
int kvstore_parser_protocol(struct conn_item *item, char **tokens, int count) {
    if(item == NULL || tokens[0] == NULL || count == 0) return -1;

    int cmd = KVS_CMD_START;

    for (cmd = KVS_CMD_START; cmd < KVS_CMD_COUNT; cmd++){
        if (strcmp(commands[cmd], tokens[0]) == 0) {
            break;
        }
    }

    char *msg = item->wbuffer;
    memset(msg, 0, BUFFER_LENGTH); // 初始化
    switch (cmd) {
        case KVS_CMD_SET:
            int res = kvstore_array_set(tokens[1], tokens[2]);
            if (!res) {
                snprintf(msg, BUFFER_LENGTH, "SUCCESS");    
            } else {
                snprintf(msg, BUFFER_LENGTH, "FAILED");
            }
            printf("set: %d\n", res);
            break;
        case KVS_CMD_GET:
            char *value = kvstore_array_get(tokens[1]);
            if (value) {
                snprintf(msg, BUFFER_LENGTH, "%s", value);    
            } else {
                snprintf(msg, BUFFER_LENGTH, "NO EXIST");
            }
            printf("get: %s\n", value);
            break;
        case KVS_CMD_DEL:
            printf("DEL\n");
            break;
        case KVS_CMD_MOD:
            printf("MOD\n");
            break;
        default:
            printf("cmd: %s\n", commands[cmd]);
            assert(0);  // 打印一条错误信息并终止执行
    }
}

int kvstore_request(struct conn_item *item) {
    printf("recv: %s\n", item->rbuffer);

    // 解析msg
    char *msg = item->rbuffer; 
    char *tokens[KVSTORE_MAX_TOKENS];

    int count = kvstore_split_token(msg, tokens);
    
    int idx = 0;
    for (idx = 0; idx < count; idx++){
        printf("idx: %s\n", tokens[idx]);
    }
    kvstore_parser_protocol(item, tokens, count);

    return 0;
}

int main() {
    epoll_entry();
     
}