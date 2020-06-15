#include "hydrogen.h"

typedef uint8_t u8;

#define ARRAY(name, size) \
    u8 name[size]; \
    for(size_t i = 0; i < size; i++) name[i] = i;
#define CTX(name, size) \
    char name[size]; \
    for(size_t i = 0; i < size; i++) name[i] = i;

// int hydro_hash_hash(uint8_t *out, size_t out_len, const void *in_, size_t in_len,
                    // const char    ctx[hydro_hash_CONTEXTBYTES],
                    // const uint8_t key[hydro_hash_KEYBYTES]);
void hash(void) {
    ARRAY(out, 32);
    ARRAY(in , 32);
      CTX(ctx,  8);
    ARRAY(key, 32);
    hydro_hash_hash(out, 32, in, 32, ctx, key);
}

int main(void) {
    return 0;
}
