// Auto-generated file. Do not edit!
//   Template: src/x8-packw/kr4-avxvnni.c.in
//   Generator: tools/xngen
//
// Copyright 2024 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.


#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include <immintrin.h>

#include "xnnpack/packw.h"
#include "xnnpack/unaligned.h"
#include "xnnpack/prefetch.h"


void xnn_qs8_packw_gemm_goi_ukernel_x8c4__avxvnni_prfm(
  size_t g,
  size_t nc,
  size_t kc,
  size_t nr,
  size_t kr,
  size_t sr,
  const int8_t* weights,
  const int32_t* bias,
  const void* scale,
  int8_t* packed_weights,
  size_t extra_bytes,
  const void* params) XNN_OOB_READS
{
  assert(g != 0);
  assert(nc != 0);
  assert(kc != 0);
  assert(nr == 8);
  assert(kr == 4);
  assert(sr == 1);
  assert(weights != NULL);
  assert(packed_weights != NULL);

  int8_t* out = (int8_t*) packed_weights;
  const int32_t* b = (const int32_t*) bias;

  const __m256i vone = _mm256_set1_epi8(1);
  const uint32_t izp = (uint32_t) (params ? (((const struct xnn_qs8_packw_params*) params)->input_zero_point + 0): 0);
  __m256i vzeropoint = _mm256_set1_epi32((int32_t) izp);

  do {
    // NC main loop multiple of 8
    const int8_t* w0 = (const int8_t*) weights;
    size_t n = nc;
    for (; n >= 8; n -= 8) {
      int32_t* packed_b = (int32_t*) out;
      if XNN_LIKELY(b != NULL) {
        const __m256i vb0 = _mm256_loadu_si256((const __m256i*) (b + 0));
        _mm256_storeu_si256((__m256i*) (out + 0), vb0);
        b += 8;
      } else {
        _mm256_storeu_si256((__m256i*) (out + 0), _mm256_setzero_si256());
      }
      out += 8 * sizeof(int32_t);

      const int8_t* w1 = w0 + kc;
      const int8_t* w2 = w1 + kc;
      const int8_t* w3 = w2 + kc;
      const int8_t* w4 = w3 + kc;
      const int8_t* w5 = w4 + kc;
      const int8_t* w6 = w5 + kc;
      const int8_t* w7 = w6 + kc;
      xnn_prefetch_to_l1((const int8_t*) w0 + 0);
      xnn_prefetch_to_l1((const int8_t*) w0 + 64);
      xnn_prefetch_to_l1((const int8_t*) w0 + 128);
      xnn_prefetch_to_l1((const int8_t*) w0 + 192);
      xnn_prefetch_to_l1((const int8_t*) w1 + 0);
      xnn_prefetch_to_l1((const int8_t*) w1 + 64);
      xnn_prefetch_to_l1((const int8_t*) w1 + 128);
      xnn_prefetch_to_l1((const int8_t*) w1 + 192);
      xnn_prefetch_to_l1((const int8_t*) w2 + 0);
      xnn_prefetch_to_l1((const int8_t*) w2 + 64);
      xnn_prefetch_to_l1((const int8_t*) w2 + 128);
      xnn_prefetch_to_l1((const int8_t*) w2 + 192);
      xnn_prefetch_to_l1((const int8_t*) w3 + 0);
      xnn_prefetch_to_l1((const int8_t*) w3 + 64);
      xnn_prefetch_to_l1((const int8_t*) w3 + 128);
      xnn_prefetch_to_l1((const int8_t*) w3 + 192);
      xnn_prefetch_to_l1((const int8_t*) w4 + 0);
      xnn_prefetch_to_l1((const int8_t*) w4 + 64);
      xnn_prefetch_to_l1((const int8_t*) w4 + 128);
      xnn_prefetch_to_l1((const int8_t*) w4 + 192);
      xnn_prefetch_to_l1((const int8_t*) w5 + 0);
      xnn_prefetch_to_l1((const int8_t*) w5 + 64);
      xnn_prefetch_to_l1((const int8_t*) w5 + 128);
      xnn_prefetch_to_l1((const int8_t*) w5 + 192);
      xnn_prefetch_to_l1((const int8_t*) w6 + 0);
      xnn_prefetch_to_l1((const int8_t*) w6 + 64);
      xnn_prefetch_to_l1((const int8_t*) w6 + 128);
      xnn_prefetch_to_l1((const int8_t*) w6 + 192);
      xnn_prefetch_to_l1((const int8_t*) w7 + 0);
      xnn_prefetch_to_l1((const int8_t*) w7 + 64);
      xnn_prefetch_to_l1((const int8_t*) w7 + 128);
      xnn_prefetch_to_l1((const int8_t*) w7 + 192);

      __m256i vacc0 = _mm256_setzero_si256();

      size_t k = kc;
      // KC main loop multiple of 8x32
      for (; k >= 32; k -= 32) {
        const __m256i v0_01234567 = _mm256_loadu_si256((const __m256i*) w0);
        const __m256i v1_01234567 = _mm256_loadu_si256((const __m256i*) w1);
        const __m256i v2_01234567 = _mm256_loadu_si256((const __m256i*) w2);
        const __m256i v3_01234567 = _mm256_loadu_si256((const __m256i*) w3);
        const __m256i v4_01234567 = _mm256_loadu_si256((const __m256i*) w4);
        const __m256i v5_01234567 = _mm256_loadu_si256((const __m256i*) w5);
        const __m256i v6_01234567 = _mm256_loadu_si256((const __m256i*) w6);
        const __m256i v7_01234567 = _mm256_loadu_si256((const __m256i*) w7);

        const __m256i v01_0145 = _mm256_unpacklo_epi32(v0_01234567, v1_01234567);
        const __m256i v01_2367 = _mm256_unpackhi_epi32(v0_01234567, v1_01234567);
        const __m256i v23_0145 = _mm256_unpacklo_epi32(v2_01234567, v3_01234567);
        const __m256i v23_2367 = _mm256_unpackhi_epi32(v2_01234567, v3_01234567);
        const __m256i v45_0145 = _mm256_unpacklo_epi32(v4_01234567, v5_01234567);
        const __m256i v45_2367 = _mm256_unpackhi_epi32(v4_01234567, v5_01234567);
        const __m256i v67_0145 = _mm256_unpacklo_epi32(v6_01234567, v7_01234567);
        const __m256i v67_2367 = _mm256_unpackhi_epi32(v6_01234567, v7_01234567);

        const __m256i v02_02 = _mm256_unpacklo_epi64(v01_0145, v23_0145);
        const __m256i v02_13 = _mm256_unpackhi_epi64(v01_0145, v23_0145);
        const __m256i v13_02 = _mm256_unpacklo_epi64(v01_2367, v23_2367);
        const __m256i v13_13 = _mm256_unpackhi_epi64(v01_2367, v23_2367);
        const __m256i v46_02 = _mm256_unpacklo_epi64(v45_0145, v67_0145);
        const __m256i v46_13 = _mm256_unpackhi_epi64(v45_0145, v67_0145);
        const __m256i v57_02 = _mm256_unpacklo_epi64(v45_2367, v67_2367);
        const __m256i v57_13 = _mm256_unpackhi_epi64(v45_2367, v67_2367);

       const __m256i v04_0 = _mm256_permute2f128_si256(v02_02, v46_02, _MM_SHUFFLE(0, 2, 0, 0));
       const __m256i v04_1 = _mm256_permute2f128_si256(v02_02, v46_02, _MM_SHUFFLE(0, 3, 0, 1));
       const __m256i v15_0 = _mm256_permute2f128_si256(v02_13, v46_13, _MM_SHUFFLE(0, 2, 0, 0));
       const __m256i v15_1 = _mm256_permute2f128_si256(v02_13, v46_13, _MM_SHUFFLE(0, 3, 0, 1));
       const __m256i v26_0 = _mm256_permute2f128_si256(v13_02, v57_02, _MM_SHUFFLE(0, 2, 0, 0));
       const __m256i v26_1 = _mm256_permute2f128_si256(v13_02, v57_02, _MM_SHUFFLE(0, 3, 0, 1));
       const __m256i v37_0 = _mm256_permute2f128_si256(v13_13, v57_13, _MM_SHUFFLE(0, 2, 0, 0));
       const __m256i v37_1 = _mm256_permute2f128_si256(v13_13, v57_13, _MM_SHUFFLE(0, 3, 0, 1));

        xnn_prefetch_to_l1((const int8_t*) w0 + 448);
        xnn_prefetch_to_l1((const int8_t*) w1 + 448);
        xnn_prefetch_to_l1((const int8_t*) w2 + 448);
        xnn_prefetch_to_l1((const int8_t*) w3 + 448);
        xnn_prefetch_to_l1((const int8_t*) w4 + 448);
        xnn_prefetch_to_l1((const int8_t*) w5 + 448);
        xnn_prefetch_to_l1((const int8_t*) w6 + 448);
        xnn_prefetch_to_l1((const int8_t*) w7 + 448);

        vacc0 = _mm256_dpbusd_avx_epi32(vacc0, vone, v04_0);
        vacc0 = _mm256_dpbusd_avx_epi32(vacc0, vone, v15_0);
        vacc0 = _mm256_dpbusd_avx_epi32(vacc0, vone, v26_0);
        vacc0 = _mm256_dpbusd_avx_epi32(vacc0, vone, v37_0);
        vacc0 = _mm256_dpbusd_avx_epi32(vacc0, vone, v04_1);
        vacc0 = _mm256_dpbusd_avx_epi32(vacc0, vone, v15_1);
        vacc0 = _mm256_dpbusd_avx_epi32(vacc0, vone, v26_1);
        vacc0 = _mm256_dpbusd_avx_epi32(vacc0, vone, v37_1);

        _mm256_storeu_si256((__m256i *)&out[0],  v04_0);
        _mm256_storeu_si256((__m256i *)&out[32],  v15_0);
        _mm256_storeu_si256((__m256i *)&out[64],  v26_0);
        _mm256_storeu_si256((__m256i *)&out[96],  v37_0);
        _mm256_storeu_si256((__m256i *)&out[128],  v04_1);
        _mm256_storeu_si256((__m256i *)&out[160],  v15_1);
        _mm256_storeu_si256((__m256i *)&out[192],  v26_1);
        _mm256_storeu_si256((__m256i *)&out[224],  v37_1);

        w0 += 32;
        w1 += 32;
        w2 += 32;
        w3 += 32;
        w4 += 32;
        w5 += 32;
        w6 += 32;
        w7 += 32;
        out += 256;
      }

      // KC main loop multiple of 8x8
      for (; k >= 8; k -= 8) {
        __m256i v0 = _mm256_set1_epi64x((int64_t) unaligned_load_u64(w0));
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi64x((int64_t) unaligned_load_u64(w1)), 0x0C);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi64x((int64_t) unaligned_load_u64(w2)), 0x30);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi64x((int64_t) unaligned_load_u64(w3)), 0xC0);
        __m256i v4 = _mm256_set1_epi64x((int64_t) unaligned_load_u64(w4));
        v4 = _mm256_blend_epi32(v4, _mm256_set1_epi64x((int64_t) unaligned_load_u64(w5)), 0x0C);
        v4 = _mm256_blend_epi32(v4, _mm256_set1_epi64x((int64_t) unaligned_load_u64(w6)), 0x30);
        v4 = _mm256_blend_epi32(v4, _mm256_set1_epi64x((int64_t) unaligned_load_u64(w7)), 0xC0);
        xnn_prefetch_to_l1((const int8_t*) w0 + 448);
        xnn_prefetch_to_l1((const int8_t*) w1 + 448);
        xnn_prefetch_to_l1((const int8_t*) w2 + 448);
        xnn_prefetch_to_l1((const int8_t*) w3 + 448);
        xnn_prefetch_to_l1((const int8_t*) w4 + 448);
        xnn_prefetch_to_l1((const int8_t*) w5 + 448);
        xnn_prefetch_to_l1((const int8_t*) w6 + 448);
        xnn_prefetch_to_l1((const int8_t*) w7 + 448);

        const __m256i permute_mask0 =  _mm256_set_epi32(6, 4, 2, 0, 6, 4, 2, 0);
        const __m256i permute_mask1 =  _mm256_set_epi32(7, 5, 3, 1, 7, 5, 3, 1);

        const __m256i v0_0 = _mm256_permutevar8x32_epi32(v0, permute_mask0);
        const __m256i v0_1 = _mm256_permutevar8x32_epi32(v0, permute_mask1);
        const __m256i v4_0 = _mm256_permutevar8x32_epi32(v4, permute_mask0);
        const __m256i v4_1 = _mm256_permutevar8x32_epi32(v4, permute_mask1);

        const __m256i v04_0 = _mm256_permute2f128_si256(v0_0, v4_0, 0x20);
        const __m256i v04_1 = _mm256_permute2f128_si256(v0_1, v4_1, 0x20);

        vacc0 = _mm256_dpbusd_avx_epi32(vacc0, vone, v04_0);
        vacc0 = _mm256_dpbusd_avx_epi32(vacc0, vone, v04_1);

        _mm256_storeu_si256((__m256i *)&out[0],  v04_0);
        _mm256_storeu_si256((__m256i *)&out[32],  v04_1);

        w0 += 8;
        w1 += 8;
        w2 += 8;
        w3 += 8;
        w4 += 8;
        w5 += 8;
        w6 += 8;
        w7 += 8;
        out += 64;
      }

      // KC main loop multiple of 8x4
      for (; k >= 4; k -= 4) {
        __m256i v0 = _mm256_set1_epi32((int32_t) unaligned_load_u32(w0));
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w1)), 0x02);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w2)), 0x04);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w3)), 0x08);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w4)), 0x10);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w5)), 0x20);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w6)), 0x40);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w7)), 0x80);
        xnn_prefetch_to_l1((const int8_t*) w0 + 224);
        xnn_prefetch_to_l1((const int8_t*) w1 + 224);
        xnn_prefetch_to_l1((const int8_t*) w2 + 224);
        xnn_prefetch_to_l1((const int8_t*) w3 + 224);
        xnn_prefetch_to_l1((const int8_t*) w4 + 224);
        xnn_prefetch_to_l1((const int8_t*) w5 + 224);
        xnn_prefetch_to_l1((const int8_t*) w6 + 224);
        xnn_prefetch_to_l1((const int8_t*) w7 + 224);

        vacc0 = _mm256_dpbusd_avx_epi32(vacc0, vone, v0);

        _mm256_storeu_si256((__m256i *)&out[0],  v0);

        w0 += 4;
        w1 += 4;
        w2 += 4;
        w3 += 4;
        w4 += 4;
        w5 += 4;
        w6 += 4;
        w7 += 4;
        out += 32;
      }

      // KC remainder of 1..3
      if (k != 0) {
        assert(k >= 1 && k <= 3);

        const __m256i vmask = _mm256_set1_epi32((1u << (k * sizeof(int8_t) * 8)) - 1);

        __m256i v0 = _mm256_set1_epi32((int32_t) unaligned_load_u32(w0));
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w1)), 0x02);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w2)), 0x04);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w3)), 0x08);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w4)), 0x10);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w5)), 0x20);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w6)), 0x40);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w7)), 0x80);
        v0 = _mm256_and_si256(v0, vmask);

        w0 += k;
        w1 += k;
        w2 += k;
        w3 += k;
        w4 += k;
        w5 += k;
        w6 += k;
        w7 += k;

        vacc0 = _mm256_dpbusd_avx_epi32(vacc0, vone, v0);

        _mm256_storeu_si256((__m256i *)&out[0],  v0);

        out += 32;
      }

      __m256i vksum0 = _mm256_mullo_epi32(vacc0, vzeropoint);
      __m256i vpack0 =  _mm256_loadu_si256((const __m256i*) (packed_b + 0));
      vpack0 = _mm256_sub_epi32(vpack0, vksum0);
      _mm256_storeu_si256((__m256i *) (packed_b + 0), vpack0);
      out = (int8_t*) ((uintptr_t) out + extra_bytes);
      w0 = w7;
    }

    // NC remainder (1..7)
    if XNN_UNLIKELY(n != 0) {
      assert(n >= 1 && n <= 7);

      int32_t* packed_b = (int32_t*) out;
      if XNN_LIKELY(b != NULL) {
        size_t nb = n;
        do {
          *((int32_t*) out) = *b++;
          out += sizeof(int32_t);
        } while (--nb != 0);
      } else {
        size_t nb = n;
        do {
          *((int32_t*) out) = 0;
          out += sizeof(int32_t);
        } while (--nb != 0);
      }
      out += (8 - n) * sizeof(int32_t);

      const int8_t* w1 = w0 + kc;
      if XNN_UNPREDICTABLE(n < 2) {
        w1 = w0;
      }
      const int8_t* w2 = w1 + kc;
      if XNN_UNPREDICTABLE(n <= 2) {
        w2 = w1;
      }
      const int8_t* w3 = w2 + kc;
      if XNN_UNPREDICTABLE(n < 4) {
        w3 = w2;
      }
      const int8_t* w4 = w3 + kc;
      if XNN_UNPREDICTABLE(n <= 4) {
        w4 = w3;
      }
      const int8_t* w5 = w4 + kc;
      if XNN_UNPREDICTABLE(n < 6) {
        w5 = w4;
      }
      const int8_t* w6 = w5 + kc;
      if XNN_UNPREDICTABLE(n <= 6) {
        w6 = w5;
      }
      const int8_t* w7 = w6 + kc;
      if XNN_UNPREDICTABLE(n < 8) {
        w7 = w6;
      }
      xnn_prefetch_to_l1((const int8_t*) w0);
      xnn_prefetch_to_l1((const int8_t*) w0 + 64);
      xnn_prefetch_to_l1((const int8_t*) w1);
      xnn_prefetch_to_l1((const int8_t*) w1 + 64);
      xnn_prefetch_to_l1((const int8_t*) w2);
      xnn_prefetch_to_l1((const int8_t*) w2 + 64);
      xnn_prefetch_to_l1((const int8_t*) w3);
      xnn_prefetch_to_l1((const int8_t*) w3 + 64);
      xnn_prefetch_to_l1((const int8_t*) w4);
      xnn_prefetch_to_l1((const int8_t*) w4 + 64);
      xnn_prefetch_to_l1((const int8_t*) w5);
      xnn_prefetch_to_l1((const int8_t*) w5 + 64);
      xnn_prefetch_to_l1((const int8_t*) w6);
      xnn_prefetch_to_l1((const int8_t*) w6 + 64);
      xnn_prefetch_to_l1((const int8_t*) w7);
      xnn_prefetch_to_l1((const int8_t*) w7 + 64);

      __m256i vacc0 = _mm256_setzero_si256();

      // KC main loop multiple of 8x4
      size_t k = kc;
      for (; k >= 4; k -= 4) {
        __m256i v0 = _mm256_set1_epi32((int32_t) unaligned_load_u32(w0));
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w1)), 0x02);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w2)), 0x04);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w3)), 0x08);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w4)), 0x10);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w5)), 0x20);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w6)), 0x40);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w7)), 0x80);
        xnn_prefetch_to_l1((const int8_t*) w0 + 224);
        xnn_prefetch_to_l1((const int8_t*) w1 + 224);
        xnn_prefetch_to_l1((const int8_t*) w2 + 224);
        xnn_prefetch_to_l1((const int8_t*) w3 + 224);
        xnn_prefetch_to_l1((const int8_t*) w4 + 224);
        xnn_prefetch_to_l1((const int8_t*) w5 + 224);
        xnn_prefetch_to_l1((const int8_t*) w6 + 224);
        xnn_prefetch_to_l1((const int8_t*) w7 + 224);

        vacc0 = _mm256_dpbusd_avx_epi32(vacc0, vone, v0);

        _mm256_storeu_si256((__m256i *)&out[0],  v0);

        w0 += 4;
        w1 += 4;
        w2 += 4;
        w3 += 4;
        w4 += 4;
        w5 += 4;
        w6 += 4;
        w7 += 4;
        out += 32;
      }

      // KC remainder of 1..3
      if (k != 0) {
        assert(k >= 1 && k <= 3);

        const __m256i vmask = _mm256_set1_epi32((1u << (k * sizeof(int8_t) * 8)) - 1);

        __m256i v0 = _mm256_set1_epi32((int32_t) unaligned_load_u32(w0));
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w1)), 0x02);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w2)), 0x04);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w3)), 0x08);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w4)), 0x10);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w5)), 0x20);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w6)), 0x40);
        v0 = _mm256_blend_epi32(v0, _mm256_set1_epi32((int32_t) unaligned_load_u32(w7)), 0x80);
        v0 = _mm256_and_si256(v0, vmask);

        w0 += k;
        w1 += k;
        w2 += k;
        w3 += k;
        w4 += k;
        w5 += k;
        w6 += k;
        w7 += k;

        vacc0 = _mm256_dpbusd_avx_epi32(vacc0, vone, v0);

        _mm256_storeu_si256((__m256i *)&out[0],  v0);

        out += 32;
      }

      __m256i vksum0 = _mm256_mullo_epi32(vksum0, vzeropoint);
      __m256i vpack0 =  _mm256_loadu_si256((const __m256i*) (packed_b + 0));
      vpack0 = _mm256_sub_epi32(vpack0, vksum0);
      _mm256_storeu_si256((__m256i *) (packed_b + 0), vpack0);
      out = (int8_t*) ((uintptr_t) out + extra_bytes);
    }

    weights += nc * kc;
  } while (--g != 0);
}
