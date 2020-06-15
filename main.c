#include <assert.h>
#include "hydrogen.h"

typedef uint8_t u8;

#define ARRAY(name, size) \
    u8 name[size]; \
    for(size_t i = 0; i < size; i++) name[i] = i;
#define CTX(name, size) \
    char name[size]; \
    for(size_t i = 0; i < size; i++) name[i] = i;

void hash(void) {
    ARRAY(out, 32);
    ARRAY(in , 32);
      CTX(ctx,  8);
    ARRAY(key, 32);
    hydro_hash_hash(out, 32, in, 32, ctx, key);
}

void kdf(void) {
    ARRAY(out, 32);
      CTX(ctx,  8);
    ARRAY(key, 32);
    hydro_kdf_derive_from_key(out, 32, 777, ctx, key);
}

void secretbox(void) {
    ARRAY(out, 68); // out = 36 + 32
    ARRAY(  m, 32);
      CTX(ctx, 8);
    ARRAY(key, 32);
    ARRAY(prb, 16);
    int i = 0;

    i = hydro_secretbox_encrypt (out,   m, 32, 777, ctx, key);
        hydro_secretbox_probe_create(prb, out, 68, ctx, key);
    i = hydro_secretbox_probe_verify(prb, out, 68, ctx, key);
    assert(i == 0);
    i = hydro_secretbox_decrypt (  m, out, 68, 777, ctx, key);
    i++;
}

int main(void) {
    hash();
    kdf();
    secretbox();
    return 0;
}
