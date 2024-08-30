// Auto-generated file. Do not edit!
//   Template: src/f16-velu/neonfp16arith-rr1-p3.c.in
//   Generator: tools/xngen
//
// Copyright 2022 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <arm_neon.h>

#include "xnnpack/common.h"
#include "xnnpack/vunary.h"


void xnn_f16_velu_ukernel__neonfp16arith_rr1_p3_u8(
    size_t batch,
    const void* input,
    void* output,
    const struct xnn_f16_elu_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(batch != 0);
  assert(batch % sizeof(uint16_t) == 0);
  assert(input != NULL);
  assert(output != NULL);

  const float16x8_t vsat_cutoff = vreinterpretq_f16_u16(vmovq_n_u16(UINT16_C(0xC829)));  // -0x1.0A4p+3h
  const float16x8_t vmagic_bias = vreinterpretq_f16_u16(vmovq_n_u16(UINT16_C(0x660F)));  // 0x1.83Cp+10h
  const float16x8_t vlog2e = vreinterpretq_f16_u16(vmovq_n_u16(UINT16_C(0x3DC5)));  // 0x1.714p+0h
  const float16x8_t vminus_ln2 = vreinterpretq_f16_u16(vmovq_n_u16(UINT16_C(0xB98C)));  // -0x1.62E430p-1h
  const float16x8_t vc3 = vreinterpretq_f16_u16(vmovq_n_u16(UINT16_C(0x315B)));  // 0x1.56Cp-3h
  const float16x8_t vc2 = vreinterpretq_f16_u16(vmovq_n_u16(UINT16_C(0x3808)));  // 0x1.020p-1h

  XNN_FORCE_REALIZATION(vsat_cutoff);
  XNN_FORCE_REALIZATION(vmagic_bias);
  XNN_FORCE_REALIZATION(vlog2e);
  XNN_FORCE_REALIZATION(vminus_ln2);
  XNN_FORCE_REALIZATION(vc3);
  XNN_FORCE_REALIZATION(vc2);

  const float16x8_t vprescale = vreinterpretq_f16_u16(vld1q_dup_u16(&params->scalar.prescale));
  const float16x8_t vminus_alpha = vnegq_f16(vreinterpretq_f16_u16(vld1q_dup_u16(&params->scalar.alpha)));
  const float16x8_t vbeta = vreinterpretq_f16_u16(vld1q_dup_u16(&params->scalar.beta));

  const uint16_t* i = (const uint16_t*) input;
  uint16_t* o = (uint16_t*) output;
  for (; batch >= 8 * sizeof(uint16_t); batch -= 8 * sizeof(uint16_t)) {
    float16x8_t vx = vreinterpretq_f16_u16(vld1q_u16(i)); i += 8;
    float16x8_t vz = vmulq_f16(vx, vprescale);
    vz = vmaxq_f16(vz, vsat_cutoff);

    float16x8_t vn = vfmaq_f16(vmagic_bias, vz, vlog2e);
    float16x8_t vs = vreinterpretq_f16_s16(vshlq_n_s16(vreinterpretq_s16_f16(vn), 10));
    vn = vsubq_f16(vn, vmagic_bias);
    float16x8_t vt = vfmaq_f16(vz, vn, vminus_ln2);

    float16x8_t vp = vfmaq_f16(vc2, vc3, vt);
    vp = vmulq_f16(vp, vt);
    vt = vmulq_f16(vt, vs);
    vs = vfmsq_f16(vminus_alpha, vs, vminus_alpha);
    vp = vfmaq_f16(vt, vp, vt);
    float16x8_t ve = vfmsq_f16(vs, vp, vminus_alpha);

    const uint16x8_t vm = vcltq_s16(vreinterpretq_s16_f16(vx), vmovq_n_s16(0));
    vx = vmulq_f16(vx, vbeta);
    const float16x8_t vy = vbslq_f16(vm, ve, vx);
    vst1q_u16(o, vreinterpretq_u16_f16(vy)); o += 8;
  }
  if XNN_UNLIKELY(batch != 0) {
    float16x8_t vx = vreinterpretq_f16_u16(vld1q_u16(i)); i += 8;
    float16x8_t vz = vmulq_f16(vx, vprescale);
    vz = vmaxq_f16(vz, vsat_cutoff);

    float16x8_t vn = vfmaq_f16(vmagic_bias, vz, vlog2e);
    float16x8_t vs = vreinterpretq_f16_s16(vshlq_n_s16(vreinterpretq_s16_f16(vn), 10));
    vn = vsubq_f16(vn, vmagic_bias);
    float16x8_t vt = vfmaq_f16(vz, vn, vminus_ln2);

    float16x8_t vp = vfmaq_f16(vc2, vc3, vt);
    vp = vmulq_f16(vp, vt);
    vt = vmulq_f16(vt, vs);
    vs = vfmsq_f16(vminus_alpha, vs, vminus_alpha);
    vp = vfmaq_f16(vt, vp, vt);
    float16x8_t ve = vfmsq_f16(vs, vp, vminus_alpha);

    const uint16x8_t vm = vcltq_s16(vreinterpretq_s16_f16(vx), vmovq_n_s16(0));
    vx = vmulq_f16(vx, vbeta);
    float16x8_t vy = vbslq_f16(vm, ve, vx);
    float16x4_t vy_lo = vget_low_f16(vy);
    if (batch & (4 * sizeof(uint16_t))) {
      vst1_u16(o, vreinterpret_u16_f16(vy_lo)); o += 4;
      vy_lo = vget_high_f16(vy);
    }
    if (batch & (2 * sizeof(uint16_t))) {
      vst1_lane_u32((void*) o, vreinterpret_u32_f16(vy_lo), 0); o += 2;
      vy_lo = vext_f16(vy_lo, vy_lo, 2);
    }
    if (batch & (1 * sizeof(uint16_t))) {
      vst1_lane_u16(o, vreinterpret_u16_f16(vy_lo), 0);
    }
  }
}
