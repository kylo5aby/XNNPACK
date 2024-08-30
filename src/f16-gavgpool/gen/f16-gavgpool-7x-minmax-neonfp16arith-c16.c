// Auto-generated file. Do not edit!
//   Template: src/f16-gavgpool/unipass-neonfp16arith.c.in
//   Generator: tools/xngen
//
// Copyright 2022 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <arm_neon.h>

#include "xnnpack/gavgpool.h"


void xnn_f16_gavgpool_minmax_ukernel_7x__neonfp16arith_c16(
    size_t rows,
    size_t channels,
    const void* input,
    size_t input_stride,
    const void* zero,
    void* output,
    const struct xnn_f16_scaleminmax_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(rows != 0);
  assert(rows <= 7);
  assert(channels != 0);

  const uint16_t* i0 = input;
  const uint16_t* i1 = (const uint16_t*) ((uintptr_t) i0 + input_stride);
  if XNN_UNPREDICTABLE(rows < 2) {
    i1 = (const uint16_t*) zero;
  }
  const uint16_t* i2 = (const uint16_t*) ((uintptr_t) i1 + input_stride);
  if XNN_UNPREDICTABLE(rows <= 2) {
    i2 = (const uint16_t*) zero;
  }
  const uint16_t* i3 = (const uint16_t*) ((uintptr_t) i2 + input_stride);
  if XNN_UNPREDICTABLE(rows < 4) {
    i3 = (const uint16_t*) zero;
  }
  const uint16_t* i4 = (const uint16_t*) ((uintptr_t) i3 + input_stride);
  if XNN_UNPREDICTABLE(rows <= 4) {
    i4 = (const uint16_t*) zero;
  }
  const uint16_t* i5 = (const uint16_t*) ((uintptr_t) i4 + input_stride);
  if XNN_UNPREDICTABLE(rows < 6) {
    i5 = (const uint16_t*) zero;
  }
  const uint16_t* i6 = (const uint16_t*) ((uintptr_t) i5 + input_stride);
  if XNN_UNPREDICTABLE(rows <= 6) {
    i6 = (const uint16_t*) zero;
  }

  const float16x8_t vscale = vreinterpretq_f16_u16(vld1q_dup_u16(&params->scalar.scale));
  const float16x8_t vmin = vreinterpretq_f16_u16(vld1q_dup_u16(&params->scalar.min));
  const float16x8_t vmax = vreinterpretq_f16_u16(vld1q_dup_u16(&params->scalar.max));
  for (; channels >= 16; channels -= 16) {
    const float16x8_t vi0x01234567 = vreinterpretq_f16_u16(vld1q_u16(i0)); i0 += 8;
    const float16x8_t vi0x89ABCDEF = vreinterpretq_f16_u16(vld1q_u16(i0)); i0 += 8;
    const float16x8_t vi1x01234567 = vreinterpretq_f16_u16(vld1q_u16(i1)); i1 += 8;
    const float16x8_t vi1x89ABCDEF = vreinterpretq_f16_u16(vld1q_u16(i1)); i1 += 8;

    const float16x8_t vi2x01234567 = vreinterpretq_f16_u16(vld1q_u16(i2)); i2 += 8;
    float16x8_t vacc01234567 = vaddq_f16(vi0x01234567, vi1x01234567);
    const float16x8_t vi2x89ABCDEF = vreinterpretq_f16_u16(vld1q_u16(i2)); i2 += 8;
    float16x8_t vacc89ABCDEF = vaddq_f16(vi0x89ABCDEF, vi1x89ABCDEF);

    const float16x8_t vi3x01234567 = vreinterpretq_f16_u16(vld1q_u16(i3)); i3 += 8;
    vacc01234567 = vaddq_f16(vacc01234567, vi2x01234567);
    const float16x8_t vi3x89ABCDEF = vreinterpretq_f16_u16(vld1q_u16(i3)); i3 += 8;
    vacc89ABCDEF = vaddq_f16(vacc89ABCDEF, vi2x89ABCDEF);
    const float16x8_t vi4x01234567 = vreinterpretq_f16_u16(vld1q_u16(i4)); i4 += 8;
    vacc01234567 = vaddq_f16(vacc01234567, vi3x01234567);
    const float16x8_t vi4x89ABCDEF = vreinterpretq_f16_u16(vld1q_u16(i4)); i4 += 8;
    vacc89ABCDEF = vaddq_f16(vacc89ABCDEF, vi3x89ABCDEF);
    const float16x8_t vi5x01234567 = vreinterpretq_f16_u16(vld1q_u16(i5)); i5 += 8;
    vacc01234567 = vaddq_f16(vacc01234567, vi4x01234567);
    const float16x8_t vi5x89ABCDEF = vreinterpretq_f16_u16(vld1q_u16(i5)); i5 += 8;
    vacc89ABCDEF = vaddq_f16(vacc89ABCDEF, vi4x89ABCDEF);
    const float16x8_t vi6x01234567 = vreinterpretq_f16_u16(vld1q_u16(i6)); i6 += 8;
    vacc01234567 = vaddq_f16(vacc01234567, vi5x01234567);
    const float16x8_t vi6x89ABCDEF = vreinterpretq_f16_u16(vld1q_u16(i6)); i6 += 8;
    vacc89ABCDEF = vaddq_f16(vacc89ABCDEF, vi5x89ABCDEF);
    vacc01234567 = vaddq_f16(vacc01234567, vi6x01234567);
    vacc89ABCDEF = vaddq_f16(vacc89ABCDEF, vi6x89ABCDEF);

    vacc01234567 = vmulq_f16(vacc01234567, vscale);
    vacc89ABCDEF = vmulq_f16(vacc89ABCDEF, vscale);

    vacc01234567 = vmaxq_f16(vacc01234567, vmin);
    vacc89ABCDEF = vmaxq_f16(vacc89ABCDEF, vmin);

    vacc01234567 = vminq_f16(vacc01234567, vmax);
    vacc89ABCDEF = vminq_f16(vacc89ABCDEF, vmax);

    vst1q_u16(output, vreinterpretq_u16_f16(vacc01234567)); output = (uint16_t*) output + 8;
    vst1q_u16(output, vreinterpretq_u16_f16(vacc89ABCDEF)); output = (uint16_t*) output + 8;
  }
  if XNN_UNLIKELY(channels != 0) {
    do {
      const float16x8_t vi0x01234567 = vreinterpretq_f16_u16(vld1q_u16(i0)); i0 += 8;
      const float16x8_t vi1x01234567 = vreinterpretq_f16_u16(vld1q_u16(i1)); i1 += 8;

      const float16x8_t vi2x01234567 = vreinterpretq_f16_u16(vld1q_u16(i2)); i2 += 8;
      float16x8_t vacc01234567 = vaddq_f16(vi0x01234567, vi1x01234567);

      const float16x8_t vi3x01234567 = vreinterpretq_f16_u16(vld1q_u16(i3)); i3 += 8;
      vacc01234567 = vaddq_f16(vacc01234567, vi2x01234567);
      const float16x8_t vi4x01234567 = vreinterpretq_f16_u16(vld1q_u16(i4)); i4 += 8;
      vacc01234567 = vaddq_f16(vacc01234567, vi3x01234567);
      const float16x8_t vi5x01234567 = vreinterpretq_f16_u16(vld1q_u16(i5)); i5 += 8;
      vacc01234567 = vaddq_f16(vacc01234567, vi4x01234567);
      const float16x8_t vi6x01234567 = vreinterpretq_f16_u16(vld1q_u16(i6)); i6 += 8;
      vacc01234567 = vaddq_f16(vacc01234567, vi5x01234567);
      vacc01234567 = vaddq_f16(vacc01234567, vi6x01234567);

      vacc01234567 = vmulq_f16(vacc01234567, vscale);
      vacc01234567 = vmaxq_f16(vacc01234567, vmin);
      vacc01234567 = vminq_f16(vacc01234567, vmax);

      if XNN_LIKELY(channels >= 8) {
        vst1q_u16(output, vreinterpretq_u16_f16(vacc01234567)); output = (uint16_t*) output + 8;
        channels -= 8;
      } else {
        float16x4_t vacc0123 = vget_low_f16(vacc01234567);
        if (channels & 4) {
          vst1_u16(output, vreinterpret_u16_f16(vacc0123)); output = (uint16_t*) output + 4;
          vacc0123 = vget_high_f16(vacc01234567);
        }
        if (channels & 2) {
          vst1_lane_u32(output, vreinterpret_u32_f16(vacc0123), 0); output = (uint16_t*) output + 2;
          vacc0123 = vext_f16(vacc0123, vacc0123, 2);
        }
        if (channels & 1) {
          vst1_lane_u16(output, vreinterpret_u16_f16(vacc0123), 0); output = (uint16_t*) output + 1;
        }
        channels = 0;
      }
    } while (channels != 0);
  }
}
