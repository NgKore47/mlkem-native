/*
 * Copyright (c) 2024 The mlkem-native project authors
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "kem.h"
#include "randombytes.h"

#define NTESTS 1000

static int test_keys(void)
{
  uint8_t pk[CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[CRYPTO_SECRETKEYBYTES];
  uint8_t ct[CRYPTO_CIPHERTEXTBYTES];
  uint8_t key_a[CRYPTO_BYTES];
  uint8_t key_b[CRYPTO_BYTES];

  /* Alice generates a public key */
  crypto_kem_keypair(pk, sk);

  /* Bob derives a secret key and creates a response */
  crypto_kem_enc(ct, key_b, pk);

  /* Alice uses Bobs response to get her shared key */
  crypto_kem_dec(key_a, ct, sk);

  if (memcmp(key_a, key_b, CRYPTO_BYTES))
  {
    printf("ERROR keys\n");
    return 1;
  }

  return 0;
}

static int test_invalid_pk(void)
{
  uint8_t pk[CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[CRYPTO_SECRETKEYBYTES];
  uint8_t ct[CRYPTO_CIPHERTEXTBYTES];
  uint8_t key_b[CRYPTO_BYTES];
  int rc;
  /* Alice generates a public key */
  crypto_kem_keypair(pk, sk);

  /* Bob derives a secret key and creates a response */
  rc = crypto_kem_enc(ct, key_b, pk);

  if (rc)
  {
    printf("ERROR test_invalid_pk\n");
    return 1;
  }

  /* set first public key coefficient to 4095 (0xFFF) */
  pk[0] = 0xFF;
  pk[1] |= 0x0F;
  /* Bob derives a secret key and creates a response */
  rc = crypto_kem_enc(ct, key_b, pk);

  if (!rc)
  {
    printf("ERROR test_invalid_pk\n");
    return 1;
  }
  return 0;
}

static int test_invalid_sk_a(void)
{
  uint8_t pk[CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[CRYPTO_SECRETKEYBYTES];
  uint8_t ct[CRYPTO_CIPHERTEXTBYTES];
  uint8_t key_a[CRYPTO_BYTES];
  uint8_t key_b[CRYPTO_BYTES];
  int rc;

  /* Alice generates a public key */
  crypto_kem_keypair(pk, sk);

  /* Bob derives a secret key and creates a response */
  crypto_kem_enc(ct, key_b, pk);

  /* Replace first part of secret key with random values */
  randombytes(sk, 10);

  /*
   * Alice uses Bobs response to get her shared key
   * This should fail due to wrong sk
   */
  rc = crypto_kem_dec(key_a, ct, sk);
  if (rc)
  {
    printf("ERROR test_invalid_sk_a\n");
    return 1;
  }

  if (!memcmp(key_a, key_b, CRYPTO_BYTES))
  {
    printf("ERROR invalid sk\n");
    return 1;
  }

  return 0;
}

static int test_invalid_sk_b(void)
{
  uint8_t pk[CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[CRYPTO_SECRETKEYBYTES];
  uint8_t ct[CRYPTO_CIPHERTEXTBYTES];
  uint8_t key_a[CRYPTO_BYTES];
  uint8_t key_b[CRYPTO_BYTES];
  int rc;

  /* Alice generates a public key */
  crypto_kem_keypair(pk, sk);

  /* Bob derives a secret key and creates a response */
  crypto_kem_enc(ct, key_b, pk);

  /* Replace H(pk) with radom values; */
  randombytes(sk + CRYPTO_SECRETKEYBYTES - 64, 32);

  /*
   * Alice uses Bobs response to get her shared key
   * This should fail due to the input validation
   */
  rc = crypto_kem_dec(key_a, ct, sk);
  if (!rc)
  {
    printf("ERROR test_invalid_sk_b\n");
    return 1;
  }

  return 0;
}

static int test_invalid_ciphertext(void)
{
  uint8_t pk[CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[CRYPTO_SECRETKEYBYTES];
  uint8_t ct[CRYPTO_CIPHERTEXTBYTES];
  uint8_t key_a[CRYPTO_BYTES];
  uint8_t key_b[CRYPTO_BYTES];
  uint8_t b;
  size_t pos;

  do
  {
    randombytes(&b, sizeof(uint8_t));
  } while (!b);
  randombytes((uint8_t *)&pos, sizeof(size_t));

  /* Alice generates a public key */
  crypto_kem_keypair(pk, sk);

  /* Bob derives a secret key and creates a response */
  crypto_kem_enc(ct, key_b, pk);

  /* Change some byte in the ciphertext (i.e., encapsulated key) */
  ct[pos % CRYPTO_CIPHERTEXTBYTES] ^= b;

  /* Alice uses Bobs response to get her shared key */
  crypto_kem_dec(key_a, ct, sk);

  if (!memcmp(key_a, key_b, CRYPTO_BYTES))
  {
    printf("ERROR invalid ciphertext\n");
    return 1;
  }

  return 0;
}

int main(void)
{
  unsigned int i;
  int r;

  for (i = 0; i < NTESTS; i++)
  {
    r = test_keys();
    r |= test_invalid_pk();
    r |= test_invalid_sk_a();
    r |= test_invalid_sk_b();
    r |= test_invalid_ciphertext();
    if (r)
    {
      return 1;
    }
  }

  printf("CRYPTO_SECRETKEYBYTES:  %d\n", CRYPTO_SECRETKEYBYTES);
  printf("CRYPTO_PUBLICKEYBYTES:  %d\n", CRYPTO_PUBLICKEYBYTES);
  printf("CRYPTO_CIPHERTEXTBYTES: %d\n", CRYPTO_CIPHERTEXTBYTES);

  return 0;
}
