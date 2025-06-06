/*
 * Copyright (c) 2024 The mlkem-native project authors
 * SPDX-License-Identifier: Apache-2.0
 */

#include "common.h"

#if defined(MLKEM_NATIVE_FIPS202_BACKEND_AARCH64_DEFAULT) || \
    defined(MLKEM_NATIVE_FIPS202_BACKEND_AARCH64_A55)

#include <stdint.h>
#include "fips202_native_aarch64.h"

ALIGN const uint64_t keccakf1600_round_constants[] = {
    0x0000000000000001, 0x0000000000008082, 0x800000000000808a,
    0x8000000080008000, 0x000000000000808b, 0x0000000080000001,
    0x8000000080008081, 0x8000000000008009, 0x000000000000008a,
    0x0000000000000088, 0x0000000080008009, 0x000000008000000a,
    0x000000008000808b, 0x800000000000008b, 0x8000000000008089,
    0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
    0x000000000000800a, 0x800000008000000a, 0x8000000080008081,
    0x8000000000008080, 0x0000000080000001, 0x8000000080008008,
};

#else

/* Dummy declaration for compilers disliking empty compilation units */
#define empty_cu_keccakf1600_round_constants \
  MLKEM_NAMESPACE(empty_cu_keccakf1600_round_constants)
int empty_cu_keccakf1600_round_constants;
#endif
