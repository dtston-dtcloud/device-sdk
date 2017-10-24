
#include "ssv_types.h"
#include "oss_map.h"

typedef struct oss_pair_s oss_pair_t;

typedef struct oss_bucket_s oss_bucket_t;

struct oss_pair_s {
    char *key;
    char *value;
};

struct oss_bucket_s {
    unsigned int count;
    oss_pair_t *pairs;
};

struct oss_map_s {
    unsigned int count;
    oss_bucket_t *buckets;
};

static oss_pair_t * get_pair(oss_bucket_t *bucket, const char *key);
static unsigned long hash(const char *str);

oss_map_t * oss_map_new(unsigned int capacity)
{
    oss_map_t *map;

    map = malloc(sizeof(oss_map_t));
    if (map == NULL) {
        return NULL;
    }
    map->count = capacity;
    map->buckets = malloc((map->count) * sizeof(oss_bucket_t));
    if (map->buckets == NULL) {
        free(map);
        return NULL;
    }
    memset(map->buckets, 0, map->count * sizeof(oss_bucket_t));
    return map;
}

void oss_map_delete(oss_map_t *map)
{
    unsigned int i, j, n, m;
    oss_bucket_t *bucket;
    oss_pair_t *pair;

    if (map == NULL) {
        return;
    }
    n = map->count;
    bucket = map->buckets;
    i = 0;
    while (i < n) {
        m = bucket->count;
        pair = bucket->pairs;
        j = 0;
        while(j < m) {
            free(pair->key);
            free(pair->value);
            pair++;
            j++;
        }
        free(bucket->pairs);
        bucket++;
        i++;
    }
    free(map->buckets);
    free(map);
}

int oss_map_get(const oss_map_t *map, const char *key, char *out_buf, unsigned int out_buf_len)
{
    unsigned int index;
    oss_bucket_t *bucket;
    oss_pair_t *pair;

    if (map == NULL) {
        return 0;
    }
    if (key == NULL) {
        return 0;
    }
    index = hash(key) % map->count;
    bucket = &(map->buckets[index]);
    pair = get_pair(bucket, key);
    if (pair == NULL) {
        return 0;
    }
    if (out_buf == NULL && out_buf_len == 0) {
        return strlen(pair->value) + 1;
    }
    if (out_buf == NULL) {
        return 0;
    }
    if (strlen(pair->value) >= out_buf_len) {
        return 0;
    }
    strcpy(out_buf, pair->value);
    return 1;
}

int oss_map_exists(const oss_map_t *map, const char *key)
{
    unsigned int index;
    oss_bucket_t *bucket;
    oss_pair_t *pair;

    if (map == NULL) {
        return 0;
    }
    if (key == NULL) {
        return 0;
    }
    index = hash(key) % map->count;
    bucket = &(map->buckets[index]);
    pair = get_pair(bucket, key);
    if (pair == NULL) {
        return 0;
    }
    return 1;
}

int oss_map_put(oss_map_t *map, const char *key, const char *value)
{
    unsigned int key_len, value_len, index;
    oss_bucket_t *bucket;
    oss_pair_t *tmp_pairs, *pair;
    char *tmp_value;
    char *new_key, *new_value;

    if (map == NULL) {
        return 0;
    }
    if (key == NULL || value == NULL) {
        return 0;
    }
    key_len = strlen(key);
    value_len = strlen(value);
    /* Get a pointer to the bucket the key string hashes to */
    index = hash(key) % map->count;
    bucket = &(map->buckets[index]);
    /* Check if we can handle insertion by simply replacing
    * an existing value in a key-value pair in the bucket.
    */
    if ((pair = get_pair(bucket, key)) != NULL) {
        /* The bucket contains a pair that matches the provided key,
        * change the value for that pair to the new value.
        */
        if (strlen(pair->value) < value_len) {
            /* If the new value is larger than the old value, re-allocate
            * space for the new larger value.
            */
            tmp_value = realloc(pair->value, (value_len + 1) * sizeof(char));
            if (tmp_value == NULL) {
                return 0;
            }
            pair->value = tmp_value;
        }
        /* Copy the new value into the pair that matches the key */
        strcpy(pair->value, value);
        return 1;
    }
    /* Allocate space for a new key and value */
    new_key = malloc((key_len + 1) * sizeof(char));
    if (new_key == NULL) {
        return 0;
    }
    new_value = malloc((value_len + 1) * sizeof(char));
    if (new_value == NULL) {
        free(new_key);
        return 0;
    }
    /* Create a key-value pair */
    if (bucket->count == 0) {
        /* The bucket is empty, lazily allocate space for a single
        * key-value pair.
        */
        bucket->pairs = malloc(sizeof(oss_pair_t));
        if (bucket->pairs == NULL) {
            free(new_key);
            free(new_value);
            return 0;
        }
        bucket->count = 1;
    }
    else {
        /* The bucket wasn't empty but no pair existed that matches the provided
        * key, so create a new key-value pair.
        */
        tmp_pairs = realloc(bucket->pairs, (bucket->count + 1) * sizeof(oss_pair_t));
        if (tmp_pairs == NULL) {
            free(new_key);
            free(new_value);
            return 0;
        }
        bucket->pairs = tmp_pairs;
        bucket->count++;
    }
    /* Get the last pair in the chain for the bucket */
    pair = &(bucket->pairs[bucket->count - 1]);
    pair->key = new_key;
    pair->value = new_value;
    /* Copy the key and its value into the key-value pair */
    strcpy(pair->key, key);
    strcpy(pair->value, value);
    return 1;
}

int oss_map_get_count(const oss_map_t *map)
{
    unsigned int i, j, n, m;
    unsigned int count;
    oss_bucket_t *bucket;
    oss_pair_t *pair;

    if (map == NULL) {
        return 0;
    }
    bucket = map->buckets;
    n = map->count;
    i = 0;
    count = 0;
    while (i < n) {
        pair = bucket->pairs;
        m = bucket->count;
        j = 0;
        while (j < m) {
            count++;
            pair++;
            j++;
        }
        bucket++;
        i++;
    }
    return count;
}

int oss_map_enum(const oss_map_t *map, oss_map_enum_func enum_func, const void *obj)
{
    unsigned int i, j, n, m;
    oss_bucket_t *bucket;
    oss_pair_t *pair;

    if (map == NULL) {
        return 0;
    }
    if (enum_func == NULL) {
        return 0;
    }
    bucket = map->buckets;
    n = map->count;
    i = 0;
    while (i < n) {
        pair = bucket->pairs;
        m = bucket->count;
        j = 0;
        while (j < m) {
            enum_func(pair->key, pair->value, obj);
            pair++;
            j++;
        }
        bucket++;
        i++;
    }
    return 1;
}

/*
 * Returns a pair from the bucket that matches the provided key,
 * or null if no such pair exist.
 */
static oss_pair_t * get_pair(oss_bucket_t *bucket, const char *key)
{
    unsigned int i, n;
    oss_pair_t *pair;

    n = bucket->count;
    if (n == 0) {
        return NULL;
    }
    pair = bucket->pairs;
    i = 0;
    while (i < n) {
        if (pair->key != NULL && pair->value != NULL) {
            if (strcmp(pair->key, key) == 0) {
                return pair;
            }
        }
        pair++;
        i++;
    }
    return NULL;
}

/*
 * Returns a hash code for the provided string.
 */
static unsigned long hash(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++) == TRUE) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

