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

// #define hydro_secretbox_CONTEXTBYTES 8
// #define hydro_secretbox_HEADERBYTES (20 + 16)
// #define hydro_secretbox_KEYBYTES 32
// #define hydro_secretbox_PROBEBYTES 16
//
// void hydro_secretbox_keygen(uint8_t key[hydro_secretbox_KEYBYTES]);
//
// int hydro_secretbox_encrypt(uint8_t *c, const void *m_, size_t mlen, uint64_t msg_id,
                            // const char    ctx[hydro_secretbox_CONTEXTBYTES],
                            // const uint8_t key[hydro_secretbox_KEYBYTES]);
//
// int hydro_secretbox_decrypt(void *m_, const uint8_t *c, size_t clen, uint64_t msg_id,
                            // const char    ctx[hydro_secretbox_CONTEXTBYTES],
                            // const uint8_t key[hydro_secretbox_KEYBYTES])
    // _hydro_attr_warn_unused_result_;

void secret(void) {
    ARRAY(out, 68); // out = 36 + 32
    ARRAY(  m, 32);
      CTX(ctx, 8);
    ARRAY(key, 32);
    int i = 0;

    i = hydro_secretbox_encrypt(out, m, 32, 777, ctx, key);
    i = hydro_secretbox_decrypt(m, out, 68, 777, ctx, key);
    i++;
}

int main(void) {
    hash();
    kdf();
    secret();
    return 0;
}
