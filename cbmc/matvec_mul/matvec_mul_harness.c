// Copyright (c) 2024 The mlkem-native project authors
// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

#include "indcpa.h"
#include "polyvec.h"

void matvec_mul(polyvec *out, polyvec const *a, polyvec const *v,
                polyvec_mulcache const *vc);

void harness(void)
{
  polyvec *out, *a, *v;
  polyvec_mulcache *vc;
  matvec_mul(out, a, v, vc);
}
