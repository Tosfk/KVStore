#include <stdio.h>

#include "kvstore.h"

struct kvs_array_item array_table[KVS_ARRAY_SIZE] = {0};
int array_idx = 0;  // 当前数组插入到了第几个位置

kvstore_array_set(char *key, char *value) {
    if (key == NULL || value == NULL || array_idx == KVS_ARRAY_SIZE) return -1;

    

    if (array_idx >= KVS_ARRAY_SIZE) {
        return -1;
    }

    array_table[array_idx].key = key;
    array_table[array_idx].value = value;

    array_idx++;

    return 0;
}