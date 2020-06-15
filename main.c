#include <assert.h>
#include "hydrogen.h"

#define ARRAY(name, size) \
    uint8_t name[size]; \
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
    int i;

    i = hydro_secretbox_encrypt (out,   m, 32, 777, ctx, key);
        hydro_secretbox_probe_create(prb, out, 68, ctx, key);
    i = hydro_secretbox_probe_verify(prb, out, 68, ctx, key);
    assert(i == 0);
    i = hydro_secretbox_decrypt (  m, out, 68, 777, ctx, key);
    i++;
}

void sign(void) {
    ARRAY(sig, 64);
      CTX(ctx,  8);
    ARRAY(in , 32);
    int i;

    hydro_sign_keypair pair;
    hydro_sign_keygen(&pair);
    hydro_sign_create(sig, in, 32, ctx, pair.sk);
    i = hydro_sign_verify(sig, in, 32, ctx, pair.pk);
    assert(i == 0);
}

void pwhash(void) {
    ARRAY(master, 32);
    ARRAY(out, 32);
      CTX( in, 32);
      CTX(ctx,  8);
    hydro_pwhash_deterministic(out, 32, in, 32, ctx, master, 1024, 0, 1);
}

int main(void) {
    hydro_init();

    hash();
    kdf();
    secretbox();
    sign();
    pwhash();
    return 0;
}
