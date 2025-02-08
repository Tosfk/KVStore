#include "kvstore.h"

struct kvs_array_item array_table[KVS_ARRAY_SIZE] = {0};
int array_idx = 0;  // 当前数组插入到了第几个位置

int kvstore_array_set(char *key, char *value) {
    if (key == NULL || value == NULL || array_idx == KVS_ARRAY_SIZE) return -1;

    printf("Setting: key='%s', value='%s'\n", key, value);

    char *kcopy = kvstore_malloc(strlen(key) + 1);
    if (kcopy == NULL) return -1;

    char *vcopy = kvstore_malloc(strlen(value) + 1);
    if (vcopy == NULL) {
        kvstore_free(kcopy);
        return -1;
    }
    strncpy(vcopy, value, strlen(value)+1);
    vcopy[strlen(value)] = '\0';

    array_table[array_idx].key = kcopy;
    array_table[array_idx].value = vcopy;
    array_idx++;
    
    return 0;
}

// 1:26:12
char *kvstore_array_get(char *key) {
    int i = 0;
    for (i = 0; i < array_idx; i++) {
        printf("Comparing: '%s' with '%s'\n", array_table[i].key, key);
        if (strcmp(array_table[i].key, key) == 0) {
            //printf("i= %d, key: %s, value: %s\n",i, array_table[i].key, array_table[i].value);
            return  array_table[i].value;
        }
    }

    return NULL;
}
