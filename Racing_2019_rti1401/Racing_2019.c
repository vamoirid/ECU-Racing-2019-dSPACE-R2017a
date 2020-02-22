#include "Racing_2019_trc_ptr.h"
#include "Racing_2019.h"
#include "Racing_2019_private.h"

B_Racing_2019_T Racing_2019_B;
DW_Racing_2019_T Racing_2019_DW;
PrevZCX_Racing_2019_T Racing_2019_PrevZCX;
RT_MODEL_Racing_2019_T Racing_2019_M_;
RT_MODEL_Racing_2019_T *const Racing_2019_M = &Racing_2019_M_;
static void Racing_2019_dec2hex(real_T d, char_T s_data[], int32_T s_size[2]);
static real_T Racing_2019_hex2dec(const char_T s[2]);
static real_T Racing_2019_hex2dec_f(char_T s);
real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
{
  real_T frac;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  return (table[iLeft + 1U] - table[iLeft]) * frac + table[iLeft];
}

real32_T look1_iflf_pbinlxpw(real32_T u0, const real32_T bp0[], const real32_T
  table[], uint32_T prevIndex[], uint32_T maxIndex)
{
  real32_T frac;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;
  uint32_T found;
  if (u0 <= bp0[0U]) {
    bpIdx = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    bpIdx = prevIndex[0U];
    iLeft = 0U;
    iRght = maxIndex;
    found = 0U;
    while (found == 0U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx - 1U;
        bpIdx = (iRght + iLeft) >> 1U;
      } else if (u0 < bp0[bpIdx + 1U]) {
        found = 1U;
      } else {
        iLeft = bpIdx + 1U;
        bpIdx = (iRght + iLeft) >> 1U;
      }
    }

    frac = (u0 - bp0[bpIdx]) / (bp0[bpIdx + 1U] - bp0[bpIdx]);
  } else {
    bpIdx = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  prevIndex[0U] = bpIdx;
  return (table[bpIdx + 1U] - table[bpIdx]) * frac + table[bpIdx];
}

void uMultiWordMul(const uint32_T u1[], int32_T n1, const uint32_T u2[], int32_T
                   n2, uint32_T y[], int32_T n)
{
  int32_T i;
  int32_T j;
  int32_T k;
  int32_T nj;
  uint32_T u1i;
  uint32_T yk;
  uint32_T a1;
  uint32_T a0;
  uint32_T b1;
  uint32_T w10;
  uint32_T w01;
  uint32_T cb;
  for (k = 0; k < n; k++) {
    y[k] = 0U;
  }

  for (i = 0; i < n1; i++) {
    cb = 0U;
    u1i = u1[i];
    a1 = u1i >> 16U;
    a0 = u1i & 65535U;
    k = n - i;
    nj = n2 <= k ? n2 : k;
    k = i;
    for (j = 0; j < nj; j++) {
      yk = y[k];
      u1i = u2[j];
      b1 = u1i >> 16U;
      u1i &= 65535U;
      w10 = a1 * u1i;
      w01 = a0 * b1;
      yk += cb;
      cb = (uint32_T)(yk < cb);
      u1i *= a0;
      yk += u1i;
      cb += (yk < u1i);
      u1i = w10 << 16U;
      yk += u1i;
      cb += (yk < u1i);
      u1i = w01 << 16U;
      yk += u1i;
      cb += (yk < u1i);
      y[k] = yk;
      cb += w10 >> 16U;
      cb += w01 >> 16U;
      cb += a1 * b1;
      k++;
    }

    if (k < n) {
      y[k] = cb;
    }
  }
}

uint32_T MultiWord2uLong(const uint32_T u[])
{
  return u[0];
}

void uMultiWordShr(const uint32_T u1[], int32_T n1, uint32_T n2, uint32_T y[],
                   int32_T n)
{
  int32_T nb;
  int32_T i;
  uint32_T yi;
  uint32_T u1i;
  int32_T nc;
  uint32_T nr;
  uint32_T nl;
  int32_T i1;
  nb = (int32_T)(n2 >> 5);
  i = 0;
  if (nb < n1) {
    nc = n + nb;
    if (nc > n1) {
      nc = n1;
    }

    nr = n2 - ((uint32_T)nb << 5);
    if (nr > 0U) {
      nl = 32U - nr;
      u1i = u1[nb];
      for (i1 = nb + 1; i1 < nc; i1++) {
        yi = u1i >> nr;
        u1i = u1[i1];
        y[i] = u1i << nl | yi;
        i++;
      }

      yi = u1i >> nr;
      if (nc < n1) {
        yi |= u1[nc] << nl;
      }

      y[i] = yi;
      i++;
    } else {
      for (i1 = nb; i1 < nc; i1++) {
        y[i] = u1[i1];
        i++;
      }
    }
  }

  while (i < n) {
    y[i] = 0U;
    i++;
  }
}

void mul_wide_s32(int32_T in0, int32_T in1, uint32_T *ptrOutBitsHi, uint32_T
                  *ptrOutBitsLo)
{
  uint32_T absIn0;
  uint32_T absIn1;
  uint32_T in0Lo;
  uint32_T in0Hi;
  uint32_T in1Hi;
  uint32_T productHiLo;
  uint32_T productLoHi;
  absIn0 = in0 < 0 ? ~(uint32_T)in0 + 1U : (uint32_T)in0;
  absIn1 = in1 < 0 ? ~(uint32_T)in1 + 1U : (uint32_T)in1;
  in0Hi = absIn0 >> 16U;
  in0Lo = absIn0 & 65535U;
  in1Hi = absIn1 >> 16U;
  absIn0 = absIn1 & 65535U;
  productHiLo = in0Hi * absIn0;
  productLoHi = in0Lo * in1Hi;
  absIn0 *= in0Lo;
  absIn1 = 0U;
  in0Lo = (productLoHi << 16U) + absIn0;
  if (in0Lo < absIn0) {
    absIn1 = 1U;
  }

  absIn0 = in0Lo;
  in0Lo += productHiLo << 16U;
  if (in0Lo < absIn0) {
    absIn1++;
  }

  absIn0 = (((productLoHi >> 16U) + (productHiLo >> 16U)) + in0Hi * in1Hi) +
    absIn1;
  if (!((in0 == 0) || ((in1 == 0) || ((in0 > 0) == (in1 > 0))))) {
    absIn0 = ~absIn0;
    in0Lo = ~in0Lo;
    in0Lo++;
    if (in0Lo == 0U) {
      absIn0++;
    }
  }

  *ptrOutBitsHi = absIn0;
  *ptrOutBitsLo = in0Lo;
}

int32_T mul_s32_hiSR(int32_T a, int32_T b, uint32_T aShift)
{
  uint32_T u32_chi;
  uint32_T u32_clo;
  mul_wide_s32(a, b, &u32_chi, &u32_clo);
  return (int32_T)u32_chi >> aShift;
}

void Racing_20_NEGATIVEEdge_Init(B_NEGATIVEEdge_Racing_2019_T *localB,
  P_NEGATIVEEdge_Racing_2019_T *localP)
{
  localB->RelationalOperator1 = localP->OUT_Y0;
}

void Racing_2019_NEGATIVEEdge(real_T rtu_Enable, boolean_T rtu_IN, boolean_T
  rtu_INprevious, B_NEGATIVEEdge_Racing_2019_T *localB)
{
  if (rtu_Enable > 0.0) {
    localB->RelationalOperator1 = ((int32_T)rtu_INprevious > (int32_T)rtu_IN);
  }
}

void Racing_20_POSITIVEEdge_Init(B_POSITIVEEdge_Racing_2019_T *localB,
  P_POSITIVEEdge_Racing_2019_T *localP)
{
  localB->RelationalOperator1 = localP->OUT_Y0;
}

void Racing_2019_POSITIVEEdge(real_T rtu_Enable, boolean_T rtu_IN, boolean_T
  rtu_INprevious, B_POSITIVEEdge_Racing_2019_T *localB)
{
  if (rtu_Enable > 0.0) {
    localB->RelationalOperator1 = ((int32_T)rtu_IN > (int32_T)rtu_INprevious);
  }
}

void Racing_2019_s1t1(real32_T rtu_x, B_s1t1_Racing_2019_T *localB)
{
  localB->y = 1.0F / ((((real32_T)log(10000.0F * rtu_x / (5.0F - rtu_x) /
    10000.0F) * 0.000256524F + 0.00335401599F) + (real32_T)log(10000.0F * rtu_x /
    (5.0F - rtu_x) / 100000.0F) * 2.60597E-6F * (real32_T)log(10000.0F * rtu_x /
    (5.0F - rtu_x) / 10000.0F)) + (real32_T)log(100000.0F * rtu_x / (5.0F -
    rtu_x) / 10000.0F) * 6.32926E-8F * (real32_T)log(10000.0F * rtu_x / (5.0F -
    rtu_x) / 10000.0F) * (real32_T)log(10000.0F * rtu_x / (5.0F - rtu_x) /
    10000.0F)) - 273.15F;
}

void Racing_2019_s1t4(real32_T rtu_x, B_s1t4_Racing_2019_T *localB)
{
  localB->y = 1.0F / (((real32_T)log(10000.0F * rtu_x / (5.0F - rtu_x * 0.0015F)
    / 100000.0F) * 2.60597E-6F * (real32_T)log(10000.0F * rtu_x / (5.0F - rtu_x)
    / 10000.0F) + ((real32_T)log(10000.0F * rtu_x / (5.0F - rtu_x) / 10000.0F) *
                   0.000256524F + 0.00335401599F)) + (real32_T)log(100000.0F *
    rtu_x / (5.0F - rtu_x) / 10000.0F) * 6.32926E-8F * (real32_T)log(10000.0F *
    rtu_x / (5.0F - rtu_x) / 10000.0F) * (real32_T)log(10000.0F * rtu_x / (5.0F
    - rtu_x) / 10000.0F)) - 273.15F;
}

void Racing_2019_s7t1(real32_T rtu_x, B_s7t1_Racing_2019_T *localB)
{
  localB->y = 1.0F / ((((real32_T)log(10000.0F * rtu_x / (5.0F - rtu_x) /
    10000.0F) * 0.000256524F + 0.00335401599F) + (real32_T)log(10000.0F * rtu_x /
    (5.0F - rtu_x) / 100000.0F) * 2.60597E-6F * (real32_T)log(10000.0F * rtu_x /
    (5.0F - rtu_x) / 10000.0F)) + (real32_T)log(100000.0F * rtu_x / (5.0F -
    rtu_x) / 10000.0F) * 6.32926E-8F * (real32_T)log(10000.0F * rtu_x / (5.0F -
    rtu_x) / 10000.0F) * (real32_T)log(10000.0F * rtu_x / (5.0F - rtu_x) /
    10000.0F)) - 272.15F;
}

void Racing_201_IrmsLEFTRaw_Init(B_IrmsLEFTRaw_Racing_2019_T *localB,
  P_IrmsLEFTRaw_Racing_2019_T *localP)
{
  localB->In1 = localP->Out1_Y0;
}

void Racing_2019_IrmsLEFTRaw(real_T rtu_In1, B_IrmsLEFTRaw_Racing_2019_T *localB)
{
  localB->In1 = rtu_In1;
}

static void Racing_2019_dec2hex(real_T d, char_T s_data[], int32_T s_size[2])
{
  real_T di;
  real_T r;
  int32_T firstcol;
  int32_T b_j;
  boolean_T p;
  char_T s_data_0[13];
  boolean_T exitg1;
  s_size[0] = 1;
  s_size[1] = 13;
  for (firstcol = 0; firstcol < 13; firstcol++) {
    s_data[firstcol] = '0';
  }

  di = d;
  firstcol = 13;
  exitg1 = false;
  while ((!exitg1) && (firstcol > 0)) {
    r = di;
    di = floor(di / 16.0);
    r -= di * 16.0;
    if (r > 9.0) {
      r += 7.0;
    }

    s_data[firstcol - 1] = (int8_T)((uint16_T)r + 48U);
    if (di > 0.0) {
      firstcol--;
    } else {
      exitg1 = true;
    }
  }

  firstcol = 13;
  b_j = 1;
  exitg1 = false;
  while ((!exitg1) && (b_j <= 12)) {
    p = false;
    if (s_data[b_j - 1] != '0') {
      p = true;
    }

    if (p) {
      firstcol = b_j;
      exitg1 = true;
    } else {
      b_j++;
    }
  }

  if (firstcol > 1) {
    for (b_j = firstcol; b_j < 14; b_j++) {
      s_data[b_j - firstcol] = s_data[b_j - 1];
    }

    b_j = 14 - firstcol;
    for (firstcol = 0; firstcol < b_j; firstcol++) {
      s_data_0[firstcol] = s_data[firstcol];
    }

    s_size[0] = 1;
    s_size[1] = b_j;
    for (firstcol = 0; firstcol < b_j; firstcol++) {
      s_data[firstcol] = s_data_0[firstcol];
    }
  }
}

static real_T Racing_2019_hex2dec(const char_T s[2])
{
  real_T x;
  int32_T p16;
  int32_T skj;
  x = 0.0;
  p16 = 1;
  if (s[1] != ' ') {
    if (((uint8_T)s[1] != 0) && ((uint8_T)s[1] != 48)) {
      if ((uint8_T)s[1] <= 57) {
        skj = (uint8_T)s[1];
      } else if ((uint8_T)s[1] > 70) {
        skj = (uint8_T)s[1] - 39;
      } else {
        skj = (uint8_T)s[1] - 7;
      }

      skj -= 48;
      x = skj;
    }

    p16 = 16;
  }

  if ((s[0] != ' ') && ((uint8_T)s[0] != 0) && ((uint8_T)s[0] != 48)) {
    if ((uint8_T)s[0] <= 57) {
      skj = (uint8_T)s[0];
    } else if ((uint8_T)s[0] > 70) {
      skj = (uint8_T)s[0] - 39;
    } else {
      skj = (uint8_T)s[0] - 7;
    }

    skj -= 48;
    x += (real_T)(skj * p16);
  }

  return x;
}

static real_T Racing_2019_hex2dec_f(char_T s)
{
  real_T x;
  int32_T skj;
  x = 0.0;
  if ((s != ' ') && ((uint8_T)s != 0) && ((uint8_T)s != 48)) {
    if ((uint8_T)s <= 57) {
      skj = (uint8_T)s;
    } else if ((uint8_T)s > 70) {
      skj = (uint8_T)s - 39;
    } else {
      skj = (uint8_T)s - 7;
    }

    skj -= 48;
    x = skj;
  }

  return x;
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T tmp;
  real_T tmp_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

real32_T rt_powf_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  real32_T tmp;
  real32_T tmp_0;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = (rtNaNF);
  } else {
    tmp = (real32_T)fabs(u0);
    tmp_0 = (real32_T)fabs(u1);
    if (rtIsInfF(u1)) {
      if (tmp == 1.0F) {
        y = 1.0F;
      } else if (tmp > 1.0F) {
        if (u1 > 0.0F) {
          y = (rtInfF);
        } else {
          y = 0.0F;
        }
      } else if (u1 > 0.0F) {
        y = 0.0F;
      } else {
        y = (rtInfF);
      }
    } else if (tmp_0 == 0.0F) {
      y = 1.0F;
    } else if (tmp_0 == 1.0F) {
      if (u1 > 0.0F) {
        y = u0;
      } else {
        y = 1.0F / u0;
      }
    } else if (u1 == 2.0F) {
      y = u0 * u0;
    } else if ((u1 == 0.5F) && (u0 >= 0.0F)) {
      y = (real32_T)sqrt(u0);
    } else if ((u0 < 0.0F) && (u1 > (real32_T)floor(u1))) {
      y = (rtNaNF);
    } else {
      y = (real32_T)pow(u0, u1);
    }
  }

  return y;
}

void Racing_2019_output0(void)
{
  char_T IcontHex_data[13];
  char_T IcontHexFinal[3];
  real_T IcontL;
  real_T IcontH;
  char_T RPM_maxHex_data[13];
  real_T RPM_maxL;
  real_T RPM_maxH;
  boolean_T zcEvent;
  real32_T tmp;
  real32_T tmp_0;
  ZCEventType zcEvent_0;
  int32_T i;
  int32_T IcontHex_size[2];
  real32_T u2;
  uint8_T u0;
  uint8_T u1;
  uint8_T u2_0;
  int16_T u0_0;
  int16_T u1_0;
  int16_T u2_1;
  real_T u1_1;
  (Racing_2019_M->Timing.RateInteraction.TID1_2)++;
  if ((Racing_2019_M->Timing.RateInteraction.TID1_2) > 9) {
    Racing_2019_M->Timing.RateInteraction.TID1_2 = 0;
  }

  (Racing_2019_M->Timing.RateInteraction.TID1_3)++;
  if ((Racing_2019_M->Timing.RateInteraction.TID1_3) > 99) {
    Racing_2019_M->Timing.RateInteraction.TID1_3 = 0;
  }

  (Racing_2019_M->Timing.RateInteraction.TID1_4)++;
  if ((Racing_2019_M->Timing.RateInteraction.TID1_4) > 199) {
    Racing_2019_M->Timing.RateInteraction.TID1_4 = 0;
  }

  (Racing_2019_M->Timing.RateInteraction.TID1_5)++;
  if ((Racing_2019_M->Timing.RateInteraction.TID1_5) > 999) {
    Racing_2019_M->Timing.RateInteraction.TID1_5 = 0;
  }

  Racing_2019_B.Memory = Racing_2019_DW.Memory_PreviousInput;
  u1_1 = Racing_2019_B.Memory;
  IcontL = Racing_2019_P.I_MAX;
  RPM_maxL = Racing_2019_P.RPM_MAX;
  Racing_2019_dec2hex(Racing_2019_P.I_MAX * 10.0, IcontHex_data, IcontHex_size);
  if (IcontL < 26.0) {
    IcontHexFinal[0] = '0';
    IcontHexFinal[1] = IcontHex_data[0];
    IcontHexFinal[2] = IcontHex_data[1];
    IcontL = Racing_2019_hex2dec(&IcontHexFinal[1]);
    IcontH = Racing_2019_hex2dec_f('\x30');
  } else {
    IcontL = Racing_2019_hex2dec(&IcontHex_data[1]);
    IcontH = Racing_2019_hex2dec_f(IcontHex_data[0]);
  }

  Racing_2019_dec2hex(RPM_maxL, RPM_maxHex_data, IcontHex_size);
  if (RPM_maxL < 26.0) {
    IcontHexFinal[0] = '0';
    IcontHexFinal[1] = IcontHex_data[0];
    IcontHexFinal[2] = IcontHex_data[1];
    RPM_maxL = Racing_2019_hex2dec(&IcontHexFinal[1]);
    RPM_maxH = Racing_2019_hex2dec_f('\x30');
  } else {
    RPM_maxL = Racing_2019_hex2dec(&RPM_maxHex_data[1]);
    RPM_maxH = Racing_2019_hex2dec_f(RPM_maxHex_data[0]);
  }

  if (u1_1 == -14.0) {
    i = 61;
    RPM_maxL = 77.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == -13.0) {
    i = 61;
    RPM_maxL = 78.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == -12.0) {
    i = 61;
    RPM_maxL = 200.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == -11.0) {
    i = 61;
    RPM_maxL = 77.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == -10.0) {
    i = 61;
    RPM_maxL = 78.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == -9.0) {
    i = 61;
    RPM_maxL = 200.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == -8.0) {
    i = 61;
    RPM_maxL = 77.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == -7.0) {
    i = 61;
    RPM_maxL = 78.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == -6.0) {
    i = 61;
    RPM_maxL = 200.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == -5.0) {
    i = 61;
    RPM_maxL = 77.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == -4.0) {
    i = 61;
    RPM_maxL = 78.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == -3.0) {
    i = 61;
    RPM_maxL = 200.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == -2.0) {
    i = 61;
    RPM_maxL = 77.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == -1.0) {
    i = 61;
    RPM_maxL = 78.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == 0.0) {
    i = 61;
    RPM_maxL = 200.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == 1.0) {
    i = 61;
    RPM_maxL = 48.0;
    RPM_maxH = 10.0;
  } else if (u1_1 == 2.0) {
    i = 61;
    RPM_maxL = 73.0;
    RPM_maxH = 250.0;
  } else if (u1_1 == 3.0) {
    i = 61;
    RPM_maxL = 34.0;
    RPM_maxH = 250.0;
  } else if (u1_1 == 4.0) {
    i = 61;
    RPM_maxL = 226.0;
    RPM_maxH = 250.0;
  } else if (u1_1 == 5.0) {
    i = 61;
    RPM_maxL = 74.0;
    RPM_maxH = 250.0;
  } else if (u1_1 == 6.0) {
    i = 61;
    RPM_maxL = 138.0;
    RPM_maxH = 250.0;
  } else if (u1_1 == 7.0) {
    i = 61;
    RPM_maxL = 32.0;
    RPM_maxH = 10.0;
  } else if (u1_1 == 8.0) {
    i = 61;
    RPM_maxL = 143.0;
    RPM_maxH = 250.0;
  } else if (u1_1 == 9.0) {
    i = 61;
    RPM_maxL = 48.0;
    RPM_maxH = 10.0;
  } else if (u1_1 == 10.0) {
    i = 61;
    RPM_maxL = 73.0;
    RPM_maxH = 100.0;
  } else if (u1_1 == 11.0) {
    i = 61;
    RPM_maxL = 34.0;
    RPM_maxH = 250.0;
  } else if (u1_1 == 12.0) {
    i = 61;
    RPM_maxL = 226.0;
    RPM_maxH = 250.0;
  } else if (u1_1 == 13.0) {
    i = 61;
    RPM_maxL = 74.0;
    RPM_maxH = 250.0;
  } else if (u1_1 == 14.0) {
    i = 61;
    RPM_maxL = 138.0;
    RPM_maxH = 250.0;
  } else if (u1_1 == 15.0) {
    i = 61;
    RPM_maxL = 32.0;
    RPM_maxH = 10.0;
  } else if (u1_1 == 16.0) {
    i = 61;
    RPM_maxL = 143.0;
    RPM_maxH = 250.0;
  } else if (u1_1 == 17.0) {
    i = 61;
    RPM_maxL = 77.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == 18.0) {
    i = 61;
    RPM_maxL = 78.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == 19.0) {
    i = 61;
    RPM_maxL = 200.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == 101.0) {
    i = 61;
    RPM_maxL = 48.0;
    RPM_maxH = 255.0;
  } else if (u1_1 == 102.0) {
    i = 61;
    RPM_maxL = 73.0;
    RPM_maxH = 255.0;
  } else if (u1_1 == 103.0) {
    i = 61;
    RPM_maxL = 34.0;
    RPM_maxH = 255.0;
  } else if (u1_1 == 104.0) {
    i = 61;
    RPM_maxL = 226.0;
    RPM_maxH = 255.0;
  } else if (u1_1 == 105.0) {
    i = 61;
    RPM_maxL = 74.0;
    RPM_maxH = 255.0;
  } else if (u1_1 == 106.0) {
    i = 61;
    RPM_maxL = 138.0;
    RPM_maxH = 255.0;
  } else if (u1_1 == 107.0) {
    i = 61;
    RPM_maxL = 32.0;
    RPM_maxH = 255.0;
  } else if (u1_1 == 108.0) {
    i = 61;
    RPM_maxL = 143.0;
    RPM_maxH = 255.0;
  } else if (u1_1 == 201.0) {
    i = 61;
    RPM_maxL = 200.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == 202.0) {
    i = 61;
    RPM_maxL = 77.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == 203.0) {
    i = 61;
    RPM_maxL = 78.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == 301.0) {
    i = 77;
    RPM_maxL = IcontL;
    RPM_maxH = IcontH;
  } else if (u1_1 == 302.0) {
    i = 78;
    RPM_maxL = IcontL;
    RPM_maxH = IcontH;
  } else if (u1_1 == 401.0) {
    i = 132;
    RPM_maxL = 0.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == 501.0) {
    i = 131;
    RPM_maxL = 0.0;
    RPM_maxH = 0.0;
  } else if (u1_1 == 601.0) {
    i = 200;
  } else {
    i = 144;
    RPM_maxL = 0.0;
    RPM_maxH = 0.0;
  }

  Racing_2019_B.Mode_b = i;
  Racing_2019_B.ID_m = RPM_maxL;
  Racing_2019_B.Time_b = RPM_maxH;
  Racing_2019_B.Mode = Racing_2019_B.Mode_b;
  Racing_2019_B.Compare = (Racing_2019_B.Mode == Racing_2019_P.TorqueMode_const);
  Racing_2019_B.ID = Racing_2019_B.ID_m;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X65]);
    if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X65]->processed) {
      can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X65]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X65]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X65]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X65]->processed) {
        Racing_2019_B.SFunction1_o4 = (real_T)
          can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X65]->processed;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X65]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_f0 = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_o2 = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_a4 = ((UInt16) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X65]->processed) {
      Racing_2019_B.SFunction1_o4 = 0.0;
    }
  }

  Racing_2019_B.Subtract1 = (real_T)Racing_2019_B.SFunction1_o1_f0 -
    Racing_2019_P.APPS1_Threshold_Value;
  Racing_2019_B.APPS1_Gain_1000 = Racing_2019_P.APPS1_Gain_1000_Gain *
    Racing_2019_B.Subtract1;
  Racing_2019_B.Subtract2 = (real_T)Racing_2019_B.SFunction1_o2_o2 -
    Racing_2019_P.APPS2_Threshold_Value;
  Racing_2019_B.APPS2_Gain_1000 = Racing_2019_P.APPS2_Gain_1000_Gain *
    Racing_2019_B.Subtract2;
  Racing_2019_B.Add = Racing_2019_B.APPS1_Gain_1000 +
    Racing_2019_B.APPS2_Gain_1000;
  Racing_2019_B.Gain = Racing_2019_P.Gain_Gain * Racing_2019_B.Add;
  Racing_2019_B.TG = Racing_2019_P.Torque_Gain * Racing_2019_B.Gain;
  IcontL = Racing_2019_B.TG;
  u1_1 = Racing_2019_P.APPS_Limiter_LowerSat;
  RPM_maxL = Racing_2019_P.APPS_Limiter_UpperSat;
  if (IcontL > RPM_maxL) {
    Racing_2019_B.APPS_Limiter = RPM_maxL;
  } else if (IcontL < u1_1) {
    Racing_2019_B.APPS_Limiter = u1_1;
  } else {
    Racing_2019_B.APPS_Limiter = IcontL;
  }

  if (Racing_2019_P.APPS_Bypass > Racing_2019_P.Switch_Threshold) {
    u1_1 = floor(Racing_2019_P.APPS_Value);
    if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
      u1_1 = 0.0;
    } else {
      u1_1 = fmod(u1_1, 65536.0);
    }

    Racing_2019_B.Switch_e1 = (uint16_T)(u1_1 < 0.0 ? (int32_T)(uint16_T)
      -(int16_T)(uint16_T)-u1_1 : (int32_T)(uint16_T)u1_1);
  } else {
    u1_1 = floor(Racing_2019_B.APPS_Limiter);
    if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
      u1_1 = 0.0;
    } else {
      u1_1 = fmod(u1_1, 65536.0);
    }

    Racing_2019_B.Switch_e1 = (uint16_T)(u1_1 < 0.0 ? (int32_T)(uint16_T)
      -(int16_T)(uint16_T)-u1_1 : (int32_T)(uint16_T)u1_1);
  }

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M1[CANTP1_M1_C1_RX_STD_0X181]);
    if (can_type1_msg_M1[CANTP1_M1_C1_RX_STD_0X181]->processed) {
      can_type1_msg_M1[CANTP1_M1_C1_RX_STD_0X181]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M1[CANTP1_M1_C1_RX_STD_0X181]->timestamp);
    }

    if (can_type1_msg_M1[CANTP1_M1_C1_RX_STD_0X181]->timestamp > 0.0) {
      if (can_type1_msg_M1[CANTP1_M1_C1_RX_STD_0X181]->processed) {
        Racing_2019_B.SFunction1_o3 = (real_T)
          can_type1_msg_M1[CANTP1_M1_C1_RX_STD_0X181]->processed;
        CAN_Msg = can_type1_msg_M1[CANTP1_M1_C1_RX_STD_0X181]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte0 = CAN_Msg[0];
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          Racing_2019_B.SFunction1_o1 = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte0 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte1 = CAN_Msg[2];
          CAN_Sgn.SignedSgn &= 0x0000FFFF;
          if (CAN_Sgn.SignedSgn >> 15) {
            CAN_Sgn.SignedSgn |= 0xFFFF0000;
          }

          Racing_2019_B.SFunction1_o2 = ((real_T) CAN_Sgn.SignedSgn);
        }
      }
    }

    if (!can_type1_msg_M1[CANTP1_M1_C1_RX_STD_0X181]->processed) {
      Racing_2019_B.SFunction1_o3 = 0.0;
    }
  }

  u1_1 = floor(Racing_2019_B.SFunction1_o1);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 256.0);
  }

  Racing_2019_B.DataTypeConversion2_e = (uint8_T)(u1_1 < 0.0 ? (int32_T)(uint8_T)
    -(int8_T)(uint8_T)-u1_1 : (int32_T)(uint8_T)u1_1);
  switch (Racing_2019_B.DataTypeConversion2_e) {
   case 32:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2,
      &Racing_2019_B.IrmsLEFTRaw);
    break;

   case 34:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2,
      &Racing_2019_B.CommandedTorqueLEFT);
    break;

   case 48:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2,
      &Racing_2019_B.RPMLEFTRaw);
    break;

   case 73:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2,
      &Racing_2019_B.MotorTempLEFTRaw);
    break;

   case 74:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2,
      &Racing_2019_B.IGBTTempLEFTRaw);
    break;

   case 75:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2,
      &Racing_2019_B.AirTempLEFTRaw);
    break;

   case 77:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2,
      &Racing_2019_B.IpeakLEFTRaw);
    break;

   case 78:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2,
      &Racing_2019_B.IcontLEFTRaw);
    break;

   case 138:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2, &Racing_2019_B.VoutLEFT);
    break;

   case 143:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2,
      &Racing_2019_B.ErrorLEFTRaw);
    break;

   case 200:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2,
      &Racing_2019_B.RPMLimitLEFTRaw);
    break;

   case 226:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2,
      &Racing_2019_B.BTBLEFTRaw);
    break;

   case 246:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2,
      &Racing_2019_B.MotorPowerLEFTRaw);
    break;
  }

  IcontL = Racing_2019_B.IpeakLEFTRaw.In1;
  u1_1 = Racing_2019_B.IcontLEFTRaw.In1;
  if ((IcontL < u1_1) || rtIsNaN(u1_1)) {
    u1_1 = IcontL;
  }

  Racing_2019_B.IrmsMaxLEFT = u1_1;
  Racing_2019_B.Gain_i = Racing_2019_P.Gain_Gain_l * Racing_2019_B.IrmsMaxLEFT;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M1[CANTP1_M1_C2_RX_STD_0X182]);
    if (can_type1_msg_M1[CANTP1_M1_C2_RX_STD_0X182]->processed) {
      can_type1_msg_M1[CANTP1_M1_C2_RX_STD_0X182]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M1[CANTP1_M1_C2_RX_STD_0X182]->timestamp);
    }

    if (can_type1_msg_M1[CANTP1_M1_C2_RX_STD_0X182]->timestamp > 0.0) {
      if (can_type1_msg_M1[CANTP1_M1_C2_RX_STD_0X182]->processed) {
        Racing_2019_B.SFunction1_o3_h = (real_T)
          can_type1_msg_M1[CANTP1_M1_C2_RX_STD_0X182]->processed;
        CAN_Msg = can_type1_msg_M1[CANTP1_M1_C2_RX_STD_0X182]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte0 = CAN_Msg[0];
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          Racing_2019_B.SFunction1_o1_m = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte0 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte1 = CAN_Msg[2];
          CAN_Sgn.SignedSgn &= 0x0000FFFF;
          if (CAN_Sgn.SignedSgn >> 15) {
            CAN_Sgn.SignedSgn |= 0xFFFF0000;
          }

          Racing_2019_B.SFunction1_o2_h = ((real_T) CAN_Sgn.SignedSgn);
        }
      }
    }

    if (!can_type1_msg_M1[CANTP1_M1_C2_RX_STD_0X182]->processed) {
      Racing_2019_B.SFunction1_o3_h = 0.0;
    }
  }

  u1_1 = floor(Racing_2019_B.SFunction1_o1_m);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 256.0);
  }

  Racing_2019_B.DataTypeConversion2_am = (uint8_T)(u1_1 < 0.0 ? (int32_T)
    (uint8_T)-(int8_T)(uint8_T)-u1_1 : (int32_T)(uint8_T)u1_1);
  switch (Racing_2019_B.DataTypeConversion2_am) {
   case 32:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2_h,
      &Racing_2019_B.IrmsRIGHTRaw);
    break;

   case 34:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2_h,
      &Racing_2019_B.CommandTorqueRIGHT);
    break;

   case 48:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2_h,
      &Racing_2019_B.RPMRIGHTRaw);
    break;

   case 73:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2_h,
      &Racing_2019_B.MotorTempRIGHTRaw);
    break;

   case 74:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2_h,
      &Racing_2019_B.IGBTTempRIGHTRaw);
    break;

   case 75:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2_h,
      &Racing_2019_B.AirTempRIGHTRaw);
    break;

   case 77:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2_h,
      &Racing_2019_B.IpeakRIGHTRaw);
    break;

   case 78:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2_h,
      &Racing_2019_B.IcontRIGHTRaw);
    break;

   case 138:
    Racing_2019_IrmsLEFTRaw(0.0, &Racing_2019_B.VoutRIGHTRaw);
    break;

   case 143:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2_h,
      &Racing_2019_B.ErrorRIGHTRaw);
    break;

   case 200:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2_h,
      &Racing_2019_B.RPMLimitRIGHTRaw);
    break;

   case 226:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2_h,
      &Racing_2019_B.BTBRIGHTRaw);
    break;

   case 246:
    Racing_2019_IrmsLEFTRaw(Racing_2019_B.SFunction1_o2_h,
      &Racing_2019_B.MotorPowerRIGHTRaw);
    break;
  }

  IcontL = Racing_2019_B.IpeakRIGHTRaw.In1;
  u1_1 = Racing_2019_B.IcontRIGHTRaw.In1;
  if ((IcontL < u1_1) || rtIsNaN(u1_1)) {
    u1_1 = IcontL;
  }

  Racing_2019_B.IrmsMaxRIGHT = u1_1;
  Racing_2019_B.Gain_e = Racing_2019_P.Gain_Gain_n * Racing_2019_B.IrmsMaxRIGHT;
  Racing_2019_B.Add_p = Racing_2019_B.Gain_e - Racing_2019_B.Gain_i;
  if (Racing_2019_B.Add_p > Racing_2019_P.IrmsMin_Threshold) {
    Racing_2019_B.IrmsMin = Racing_2019_B.Gain_i;
  } else {
    Racing_2019_B.IrmsMin = Racing_2019_B.Gain_e;
  }

  Racing_2019_B.Watt = Racing_2019_P.Watt_Gain * Racing_2019_P.Power_Target_kW;

  {
    adc_tp4_single_new_read(ADC_TP4_1_MODULE_ADDR,
      ADC_TP4_CH6,
      (dsfloat *)&Racing_2019_B.SFunction1);
  }

  Racing_2019_B.LEMIDCGain = Racing_2019_P.LEMIDCGain_Gain *
    Racing_2019_B.SFunction1;
  Racing_2019_B.DynamicOffsetLEMIDC =
    Racing_2019_DW.DynamicOffsetLEMIDC_PreviousInp;
  Racing_2019_B.RemoveIDCoffset = Racing_2019_B.LEMIDCGain -
    Racing_2019_B.DynamicOffsetLEMIDC;
  Racing_2019_B.IDC_Transfer_Function = Racing_2019_P.IDC_Transfer_Function_Gain
    * Racing_2019_B.RemoveIDCoffset;
  IcontL = Racing_2019_B.IDC_Transfer_Function;
  u1_1 = Racing_2019_P.IDCSaturation_LowerSat;
  RPM_maxL = Racing_2019_P.IDCSaturation_UpperSat;
  if (IcontL > RPM_maxL) {
    Racing_2019_B.IDCSaturation = RPM_maxL;
  } else if (IcontL < u1_1) {
    Racing_2019_B.IDCSaturation = u1_1;
  } else {
    Racing_2019_B.IDCSaturation = IcontL;
  }

  u1_1 = Racing_2019_B.IDCSaturation;
  Racing_2019_B.MathFunction = u1_1 * u1_1;
  Racing_2019_B.DCLosses = Racing_2019_B.MathFunction *
    Racing_2019_P.DCLossesconst_Value;
  Racing_2019_B.IrmsPrevious = Racing_2019_DW.IrmsPrevious_PreviousInput;
  IcontL = Racing_2019_B.IrmsPrevious;
  if (IcontL > 0.0) {
    Racing_2019_B.Irms_Out = IcontL;
  } else {
    Racing_2019_B.Irms_Out = 0.0;
  }

  Racing_2019_B.MathFunction1 = Racing_2019_B.Irms_Out * Racing_2019_B.Irms_Out;
  Racing_2019_B.ACLosses = Racing_2019_B.MathFunction1 *
    Racing_2019_P.ACLossesconst_Value;
  u1_1 = Racing_2019_P.Inverter_Frequency;
  if (u1_1 < 0.0) {
    u1_1 = ceil(u1_1);
  } else {
    u1_1 = floor(u1_1);
  }

  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 4.294967296E+9);
  }

  switch (u1_1 < 0.0 ? -(int32_T)(uint32_T)-u1_1 : (int32_T)(uint32_T)u1_1) {
   case 8:
    IcontL = Racing_2019_B.Irms_Out;
    u1_1 = rt_powd_snf(IcontL, 5.0);
    IcontH = Racing_2019_B.Irms_Out;
    IcontL = rt_powd_snf(IcontH, 4.0);
    RPM_maxL = Racing_2019_B.Irms_Out;
    IcontH = rt_powd_snf(RPM_maxL, 3.0);
    RPM_maxH = Racing_2019_B.Irms_Out;
    RPM_maxL = rt_powd_snf(RPM_maxH, 2.0);
    Racing_2019_B.IGBTLosses = ((((3.59348952131459e-10 * u1_1 -
      3.40337729221243e-7 * IcontL) + 0.000126380462610146 * IcontH) -
      0.0186128468087641 * RPM_maxL) + 5.60210298880688 * Racing_2019_B.Irms_Out)
      - 15.4523076923087;
    break;

   case 12:
    IcontL = Racing_2019_B.Irms_Out;
    u1_1 = rt_powd_snf(IcontL, 5.0);
    IcontH = Racing_2019_B.Irms_Out;
    IcontL = rt_powd_snf(IcontH, 4.0);
    RPM_maxL = Racing_2019_B.Irms_Out;
    IcontH = rt_powd_snf(RPM_maxL, 3.0);
    RPM_maxH = Racing_2019_B.Irms_Out;
    RPM_maxL = rt_powd_snf(RPM_maxH, 2.0);
    Racing_2019_B.IGBTLosses = ((((7.49434389140272e-10 * u1_1 -
      6.63725061703005e-7 * IcontL) + 0.000230122634718224 * IcontH) -
      0.0349086152817771 * RPM_maxL) + 7.52169158782394 * Racing_2019_B.Irms_Out)
      - 25.9342657342656;
    break;

   default:
    Racing_2019_B.IGBTLosses = Racing_2019_P.Constant_Value;
    break;
  }

  Racing_2019_B.PowerMotors = ((Racing_2019_B.Watt - Racing_2019_B.DCLosses) -
    Racing_2019_B.ACLosses) - Racing_2019_B.IGBTLosses;
  Racing_2019_B.PMGain = Racing_2019_P.PMGain_Gain * Racing_2019_B.PowerMotors;
  Racing_2019_B.DataTypeConversion4 = (real32_T)Racing_2019_B.RPMRIGHTRaw.In1;
  Racing_2019_B.RPMRIGHT = Racing_2019_B.DataTypeConversion4 *
    Racing_2019_B.RPMLimitRIGHTRaw.In1 / Racing_2019_P.Constant_Value_f;
  u1_1 = floor(Racing_2019_B.RPMRIGHT);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 65536.0);
  }

  Racing_2019_B.DataTypeConversion14 = (int16_T)(u1_1 < 0.0 ? (int32_T)(int16_T)
    -(int16_T)(uint16_T)-u1_1 : (int32_T)(int16_T)(uint16_T)u1_1);
  Racing_2019_B.DataTypeConversion4_f = (real32_T)Racing_2019_B.RPMLEFTRaw.In1;
  Racing_2019_B.RPMLEFT = Racing_2019_B.DataTypeConversion4_f *
    Racing_2019_B.RPMLimitLEFTRaw.In1 / Racing_2019_P.Constant_Value_n;
  u1_1 = floor(Racing_2019_B.RPMLEFT);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 65536.0);
  }

  Racing_2019_B.DataTypeConversion14_n = (int16_T)(u1_1 < 0.0 ? (int32_T)
    (int16_T)-(int16_T)(uint16_T)-u1_1 : (int32_T)(int16_T)(uint16_T)u1_1);
  Racing_2019_B.Add_e = (int16_T)(Racing_2019_B.DataTypeConversion14 -
    Racing_2019_B.DataTypeConversion14_n);
  if (Racing_2019_B.Add_e > Racing_2019_P.Switch_Threshold_h) {
    Racing_2019_B.Switch_n = Racing_2019_B.DataTypeConversion14;
  } else {
    Racing_2019_B.Switch_n = Racing_2019_B.DataTypeConversion14_n;
  }

  u0_0 = Racing_2019_B.Switch_n;
  u1_0 = Racing_2019_P.RPMSaturation_LowerSat;
  u2_1 = Racing_2019_P.RPMSaturation_UpperSat;
  if (u0_0 > u2_1) {
    Racing_2019_B.RPMSaturation = u2_1;
  } else if (u0_0 < u1_0) {
    Racing_2019_B.RPMSaturation = u1_0;
  } else {
    Racing_2019_B.RPMSaturation = u0_0;
  }

  Racing_2019_B.RPMtorads = Racing_2019_P.RPMtorads_Gain *
    Racing_2019_B.RPMSaturation;
  Racing_2019_B.LUTKtconstant = look1_binlxpw(Racing_2019_B.Irms_Out,
    Racing_2019_P.LUTKtconstant_bp01Data, Racing_2019_P.LUTKtconstant_tableData,
    29U);
  Racing_2019_B.BackEMF = (real_T)Racing_2019_B.RPMtorads * 3.814697265625E-6 *
    Racing_2019_B.LUTKtconstant;
  Racing_2019_B.Amps = Racing_2019_B.PMGain / Racing_2019_B.BackEMF;
  Racing_2019_B.LowerRelop1 = (Racing_2019_B.Amps > Racing_2019_B.IrmsMin);
  Racing_2019_B.UpperRelop = (Racing_2019_B.Amps <
    Racing_2019_P.Constant_Value_d);
  if (Racing_2019_B.UpperRelop) {
    Racing_2019_B.Switch = Racing_2019_P.Constant_Value_d;
  } else {
    Racing_2019_B.Switch = Racing_2019_B.Amps;
  }

  if (Racing_2019_B.LowerRelop1) {
    Racing_2019_B.Switch2 = Racing_2019_B.IrmsMin;
  } else {
    Racing_2019_B.Switch2 = Racing_2019_B.Switch;
  }

  Racing_2019_B.AmpsRef = Racing_2019_B.Switch2 / Racing_2019_P.IMax_Value;
  Racing_2019_B.APPSKillswitch = Racing_2019_B.AmpsRef +
    Racing_2019_P.Power_Limiter_Killswitch;
  IcontL = Racing_2019_B.APPSKillswitch;
  u1_1 = Racing_2019_P.TorqueLimiter_LowerSat;
  RPM_maxL = Racing_2019_P.TorqueLimiter_UpperSat;
  if (IcontL > RPM_maxL) {
    Racing_2019_B.TorqueLimiter = RPM_maxL;
  } else if (IcontL < u1_1) {
    Racing_2019_B.TorqueLimiter = u1_1;
  } else {
    Racing_2019_B.TorqueLimiter = IcontL;
  }

  Racing_2019_B.APPSPL = (real_T)Racing_2019_B.Switch_e1 *
    Racing_2019_B.TorqueLimiter;
  Racing_2019_B.Subtract3 = 0.0 - Racing_2019_P.Steering_Threshold_Value;
  Racing_2019_B.Steering_Gain_1000 = Racing_2019_P.Steering_Gain_1000_Gain *
    Racing_2019_B.Subtract3;
  IcontL = Racing_2019_B.Steering_Gain_1000;
  u1_1 = Racing_2019_P.Steering_Limiter_LowerSat;
  RPM_maxL = Racing_2019_P.Steering_Limiter_UpperSat;
  if (IcontL > RPM_maxL) {
    Racing_2019_B.Steering_Limiter = RPM_maxL;
  } else if (IcontL < u1_1) {
    Racing_2019_B.Steering_Limiter = u1_1;
  } else {
    Racing_2019_B.Steering_Limiter = IcontL;
  }

  u1_1 = floor(Racing_2019_B.Steering_Limiter);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 65536.0);
  }

  Racing_2019_B.DataTypeConversion5_g = (uint16_T)(u1_1 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_1 : (int32_T)(uint16_T)u1_1);
  Racing_2019_B.Compare_d = (Racing_2019_B.DataTypeConversion5_g <
    Racing_2019_P.CompareL_const);
  Racing_2019_B.AddL = Racing_2019_P.Constant_Value_j - (real_T)
    Racing_2019_B.DataTypeConversion5_g;
  Racing_2019_B.AddL2 = Racing_2019_B.AddL - Racing_2019_P.Constant2_Value;
  Racing_2019_B.GainL2 = Racing_2019_P.GainL2_Gain * Racing_2019_B.AddL2;
  IcontL = Racing_2019_B.GainL2;
  u1_1 = Racing_2019_P.SaturationL_LowerSat;
  RPM_maxL = Racing_2019_P.SaturationL_UpperSat;
  if (IcontL > RPM_maxL) {
    Racing_2019_B.SaturationL = RPM_maxL;
  } else if (IcontL < u1_1) {
    Racing_2019_B.SaturationL = u1_1;
  } else {
    Racing_2019_B.SaturationL = IcontL;
  }

  Racing_2019_B.Product = Racing_2019_B.APPSPL * Racing_2019_B.SaturationL;
  if (Racing_2019_B.Compare_d) {
    Racing_2019_B.SwitchL3 = Racing_2019_B.APPSPL;
  } else {
    Racing_2019_B.SwitchL3 = Racing_2019_B.Product;
  }

  if (Racing_2019_M->Timing.RateInteraction.TID1_3 == 1) {
    Racing_2019_B.RateTransition13 = Racing_2019_DW.RateTransition13_Buffer0;
  }

  Racing_2019_B.EDOR = (Racing_2019_B.RateTransition13 || (Racing_2019_P.ED_On
    != 0));
  Racing_2019_B.EDEnable = (Racing_2019_B.EDOR && (Racing_2019_P.ED_Enable != 0));
  if (Racing_2019_B.EDEnable) {
    Racing_2019_B.SwitchL2 = Racing_2019_B.SwitchL3;
  } else {
    Racing_2019_B.SwitchL2 = Racing_2019_B.APPSPL;
  }

  Racing_2019_B.Compare_g = (Racing_2019_B.Switch_e1 ==
    Racing_2019_P.Constant_Value_kw);
  if (Racing_2019_M->Timing.RateInteraction.TID1_4 == 1) {
    Racing_2019_B.uHzto1kHz = Racing_2019_DW.uHzto1kHz_Buffer0;
  }

  Racing_2019_B.Compare_m = (Racing_2019_B.uHzto1kHz <=
    Racing_2019_P.NoFire_const);
  Racing_2019_B.Compare_p = (Racing_2019_B.Switch_n <=
    Racing_2019_P.NoCheetah_const);
  Racing_2019_B.Add1 = (int16_T)(Racing_2019_B.DataTypeConversion14_n -
    Racing_2019_B.DataTypeConversion14);
  if (Racing_2019_B.Add1 > Racing_2019_P.Switch1_Threshold_n) {
    Racing_2019_B.Switch1_gi = Racing_2019_B.DataTypeConversion14;
  } else {
    Racing_2019_B.Switch1_gi = Racing_2019_B.DataTypeConversion14_n;
  }

  Racing_2019_B.Compare_j = (Racing_2019_B.Switch1_gi >=
    Racing_2019_P.NoTurtle_const);

  {
    adc_tp4_single_new_read(ADC_TP4_1_MODULE_ADDR,
      ADC_TP4_CH5,
      (dsfloat *)&Racing_2019_B.SFunction1_i);
  }

  Racing_2019_B.LEMVDCGain = Racing_2019_P.LEMVDCGain_Gain *
    Racing_2019_B.SFunction1_i;
  Racing_2019_B.DynamicOffsetLEMVDC =
    Racing_2019_DW.DynamicOffsetLEMVDC_PreviousInp;
  Racing_2019_B.RemoveVDCOffset = Racing_2019_B.LEMVDCGain -
    Racing_2019_B.DynamicOffsetLEMVDC;
  Racing_2019_B.VDC_Transfer_Function = Racing_2019_P.VDC_Transfer_Function_Gain
    * Racing_2019_B.RemoveVDCOffset;
  Racing_2019_B.Compare_b = (Racing_2019_B.VDC_Transfer_Function <=
    Racing_2019_P.NoBoom_const);
  Racing_2019_B.RegenAND = (Racing_2019_B.Compare_g && Racing_2019_B.Compare_m &&
    Racing_2019_B.Compare_p && Racing_2019_B.Compare_j &&
    Racing_2019_B.Compare_b && (Racing_2019_P.Regen_Enable != 0.0) &&
    (Racing_2019_P.Regen_Enable != 0.0));
  if (Racing_2019_B.RegenAND) {
    Racing_2019_B.Switch2_m = Racing_2019_P.RegenTorque_Value;
  } else {
    Racing_2019_B.Switch2_m = Racing_2019_P.EnableTorque_Value;
  }

  Racing_2019_B.Compare_d2 = (Racing_2019_B.IDC_Transfer_Function <=
    Racing_2019_P.Death_const);
  if (Racing_2019_B.Compare_d2) {
    Racing_2019_B.Switch_h = Racing_2019_P.Icontinuous2_Value;
  } else {
    Racing_2019_B.Switch_h = Racing_2019_P.Braking_Torque;
  }

  u0 = Racing_2019_B.Switch_h;
  u1 = Racing_2019_P.TorqueLeftLimiter2_LowerSat;
  u2_0 = Racing_2019_P.TorqueLeftLimiter2_UpperSat;
  if (u0 > u2_0) {
    Racing_2019_B.TorqueLeftLimiter2 = u2_0;
  } else if (u0 < u1) {
    Racing_2019_B.TorqueLeftLimiter2 = u1;
  } else {
    Racing_2019_B.TorqueLeftLimiter2 = u0;
  }

  Racing_2019_B.Memory_n = Racing_2019_DW.Memory_PreviousInput_e;
  Racing_2019_B.LUTKtconstant_a = look1_iflf_pbinlxpw(Racing_2019_B.Memory_n,
    Racing_2019_P.LUTKtconstant_bp01Data_i,
    Racing_2019_P.LUTKtconstant_tableData_g, &Racing_2019_DW.m_bpIndex, 29U);
  Racing_2019_B.TorqueRightFiltered1 = (real32_T)
    Racing_2019_B.TorqueLeftLimiter2 / Racing_2019_B.LUTKtconstant_a;
  Racing_2019_B.TorqueRightFiltered2 = (real32_T)
    (Racing_2019_B.TorqueRightFiltered1 / Racing_2019_P.Irmsmax_Value);
  tmp_0 = Racing_2019_B.TorqueRightFiltered2;
  tmp = Racing_2019_P.TorqueLeftLimiter1_LowerSat;
  u2 = Racing_2019_P.TorqueLeftLimiter1_UpperSat;
  if (tmp_0 > u2) {
    Racing_2019_B.TorqueLeftLimiter1 = u2;
  } else if (tmp_0 < tmp) {
    Racing_2019_B.TorqueLeftLimiter1 = tmp;
  } else {
    Racing_2019_B.TorqueLeftLimiter1 = tmp_0;
  }

  Racing_2019_B.torGainL1 = (real_T)Racing_2019_P.torGainL1_Gain *
    Racing_2019_B.TorqueLeftLimiter1;
  if (Racing_2019_B.Switch2_m > Racing_2019_P.RightTorqueSwitch_Threshold) {
    Racing_2019_B.RightTorqueSwitch = Racing_2019_B.SwitchL2;
  } else {
    Racing_2019_B.RightTorqueSwitch = Racing_2019_B.torGainL1;
  }

  Racing_2019_B.Gain_Right = Racing_2019_P.Gain_Right_Gain *
    Racing_2019_B.RightTorqueSwitch;
  Racing_2019_B.DataTypeConversion5 = Racing_2019_B.Gain_Right;
  Racing_2019_B.Time = Racing_2019_B.Time_b;
  Racing_2019_B.Delay50ms = Racing_2019_DW.Delay50ms_DSTATE[0];
  if (Racing_2019_B.Compare) {
    Racing_2019_B.Switch_l = Racing_2019_B.Compare;
  } else {
    Racing_2019_B.Switch_l = Racing_2019_B.Delay50ms;
  }

  Racing_2019_B.TorqueAND = ((Racing_2019_P.Inverter_CAN_Tx_Enable != 0.0) &&
    (Racing_2019_B.Switch_l != 0.0));
  if (Racing_2019_B.TorqueAND) {
    {
      UInt32 CAN_Msg[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

      Float32 delayTime = 0.0;
      can_tp1_msg_read(can_type1_msg_M1[CANTP1_M1_C2_TX_STD_0X162]);
      if (can_type1_msg_M1[CANTP1_M1_C2_TX_STD_0X162]->processed) {
        can_type1_msg_M1[CANTP1_M1_C2_TX_STD_0X162]->timestamp =
          rtk_dsts_time_to_simtime_convert
          (can_type1_msg_M1[CANTP1_M1_C2_TX_STD_0X162]->timestamp);
      }

      if (can_type1_msg_M1[CANTP1_M1_C2_TX_STD_0X162]->timestamp > 0.0) {
        Racing_2019_B.SFunction1_g = (real_T)
          can_type1_msg_M1[CANTP1_M1_C2_TX_STD_0X162]->processed;
      }

      {
        rtican_Signal_t CAN_Sgn;
        UInt32 modeSignal;
        CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.Mode ) + 0.5);
        CAN_Sgn.UnsignedSgn &= 0x000000FF;
        CAN_Msg[0] |= CAN_Sgn.SgnBytes.Byte0;
        modeSignal = (UInt32) Racing_2019_B.Mode;
        if (modeSignal == 61) {
          CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.ID ) + 0.5);
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          CAN_Msg[1] |= CAN_Sgn.SgnBytes.Byte0;
        }

        if (modeSignal == 77) {
          CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.ID ) + 0.5);
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          CAN_Msg[1] |= CAN_Sgn.SgnBytes.Byte0;
        }

        if (modeSignal == 78) {
          CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.ID ) + 0.5);
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          CAN_Msg[1] |= CAN_Sgn.SgnBytes.Byte0;
        }

        if (modeSignal == 144) {
          if (( Racing_2019_B.DataTypeConversion5 ) < -0.5)
            CAN_Sgn.SignedSgn = (Int32) (( Racing_2019_B.DataTypeConversion5 ) -
              0.5);
          else
            CAN_Sgn.SignedSgn = (Int32) (( Racing_2019_B.DataTypeConversion5 ) +
              0.5);
          CAN_Sgn.SignedSgn &= 0x0000FFFF;
          CAN_Msg[1] |= CAN_Sgn.SgnBytes.Byte0;
          CAN_Msg[2] |= CAN_Sgn.SgnBytes.Byte1;
        }

        if (modeSignal == 200) {
          CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.ID ) + 0.5);
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          CAN_Msg[1] |= CAN_Sgn.SgnBytes.Byte0;
        }

        if (modeSignal == 61) {
          CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.Time ) + 0.5);
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          CAN_Msg[2] |= CAN_Sgn.SgnBytes.Byte0;
        }

        if (modeSignal == 77) {
          CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.Time ) + 0.5);
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          CAN_Msg[2] |= CAN_Sgn.SgnBytes.Byte0;
        }

        if (modeSignal == 78) {
          CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.Time ) + 0.5);
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          CAN_Msg[2] |= CAN_Sgn.SgnBytes.Byte0;
        }

        if (modeSignal == 200) {
          CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.Time ) + 0.5);
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          CAN_Msg[2] |= CAN_Sgn.SgnBytes.Byte0;
        }
      }

      can_tp1_msg_send(can_type1_msg_M1[CANTP1_M1_C2_TX_STD_0X162], 3,
                       &(CAN_Msg[0]), delayTime);
    }
  }

  if ((rt_ZCFcn(ANY_ZERO_CROSSING,
                &Racing_2019_PrevZCX.Inverter_RIGHT_CAN_0x162_Reset_,
                (Racing_2019_B.SFunction1_g)) != NO_ZCEVENT) ||
      (Racing_2019_B.SFunction1_g != 0.0)) {
    for (i = 0; i < 1000; i++) {
      Racing_2019_DW.Inverter_RIGHT_CAN_0x162_DSTATE[i] =
        Racing_2019_P.Inverter_RIGHT_CAN_0x162_Initia;
    }
  }

  Racing_2019_B.Inverter_RIGHT_CAN_0x162 =
    Racing_2019_DW.Inverter_RIGHT_CAN_0x162_DSTATE[0];
  Racing_2019_B.AddR2 = (real_T)Racing_2019_B.DataTypeConversion5_g -
    Racing_2019_P.Constant1_Value;
  Racing_2019_B.GainR2 = Racing_2019_P.GainR2_Gain * Racing_2019_B.AddR2;
  IcontL = Racing_2019_B.GainR2;
  u1_1 = Racing_2019_P.SaturationR_LowerSat;
  RPM_maxL = Racing_2019_P.SaturationR_UpperSat;
  if (IcontL > RPM_maxL) {
    Racing_2019_B.SaturationR = RPM_maxL;
  } else if (IcontL < u1_1) {
    Racing_2019_B.SaturationR = u1_1;
  } else {
    Racing_2019_B.SaturationR = IcontL;
  }

  Racing_2019_B.Product1 = Racing_2019_B.SaturationR * Racing_2019_B.APPSPL;
  Racing_2019_B.Compare_l = (Racing_2019_B.DataTypeConversion5_g <
    Racing_2019_P.CompareR_const);
  if (Racing_2019_B.Compare_l) {
    Racing_2019_B.SwitchR3 = Racing_2019_B.Product1;
  } else {
    Racing_2019_B.SwitchR3 = Racing_2019_B.APPSPL;
  }

  if (Racing_2019_B.EDEnable) {
    Racing_2019_B.SwitchR2 = Racing_2019_B.SwitchR3;
  } else {
    Racing_2019_B.SwitchR2 = Racing_2019_B.APPSPL;
  }

  if (Racing_2019_B.Switch2_m > Racing_2019_P.LeftTorqueSwitch_Threshold) {
    Racing_2019_B.LeftTorqueSwitch = Racing_2019_B.SwitchR2;
  } else {
    Racing_2019_B.LeftTorqueSwitch = Racing_2019_B.torGainL1;
  }

  Racing_2019_B.Gain_Left = Racing_2019_P.Gain_Left_Gain *
    Racing_2019_B.LeftTorqueSwitch;
  Racing_2019_B.DataTypeConversion6 = Racing_2019_B.Gain_Left;
  if (Racing_2019_B.TorqueAND) {
    {
      UInt32 CAN_Msg[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

      Float32 delayTime = 0.0;
      can_tp1_msg_read(can_type1_msg_M1[CANTP1_M1_C1_TX_STD_0X161]);
      if (can_type1_msg_M1[CANTP1_M1_C1_TX_STD_0X161]->processed) {
        can_type1_msg_M1[CANTP1_M1_C1_TX_STD_0X161]->timestamp =
          rtk_dsts_time_to_simtime_convert
          (can_type1_msg_M1[CANTP1_M1_C1_TX_STD_0X161]->timestamp);
      }

      if (can_type1_msg_M1[CANTP1_M1_C1_TX_STD_0X161]->timestamp > 0.0) {
        Racing_2019_B.SFunction1_kx = (real_T)
          can_type1_msg_M1[CANTP1_M1_C1_TX_STD_0X161]->processed;
      }

      {
        rtican_Signal_t CAN_Sgn;
        UInt32 modeSignal;
        CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.Mode ) + 0.5);
        CAN_Sgn.UnsignedSgn &= 0x000000FF;
        CAN_Msg[0] |= CAN_Sgn.SgnBytes.Byte0;
        modeSignal = (UInt32) Racing_2019_B.Mode;
        if (modeSignal == 61) {
          CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.ID ) + 0.5);
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          CAN_Msg[1] |= CAN_Sgn.SgnBytes.Byte0;
        }

        if (modeSignal == 77) {
          CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.ID ) + 0.5);
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          CAN_Msg[1] |= CAN_Sgn.SgnBytes.Byte0;
        }

        if (modeSignal == 78) {
          CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.ID ) + 0.5);
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          CAN_Msg[1] |= CAN_Sgn.SgnBytes.Byte0;
        }

        if (modeSignal == 144) {
          if (( Racing_2019_B.DataTypeConversion6 ) < -0.5)
            CAN_Sgn.SignedSgn = (Int32) (( Racing_2019_B.DataTypeConversion6 ) -
              0.5);
          else
            CAN_Sgn.SignedSgn = (Int32) (( Racing_2019_B.DataTypeConversion6 ) +
              0.5);
          CAN_Sgn.SignedSgn &= 0x0000FFFF;
          CAN_Msg[1] |= CAN_Sgn.SgnBytes.Byte0;
          CAN_Msg[2] |= CAN_Sgn.SgnBytes.Byte1;
        }

        if (modeSignal == 200) {
          CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.ID ) + 0.5);
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          CAN_Msg[1] |= CAN_Sgn.SgnBytes.Byte0;
        }

        if (modeSignal == 61) {
          CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.Time ) + 0.5);
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          CAN_Msg[2] |= CAN_Sgn.SgnBytes.Byte0;
        }

        if (modeSignal == 77) {
          CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.Time ) + 0.5);
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          CAN_Msg[2] |= CAN_Sgn.SgnBytes.Byte0;
        }

        if (modeSignal == 78) {
          CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.Time ) + 0.5);
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          CAN_Msg[2] |= CAN_Sgn.SgnBytes.Byte0;
        }

        if (modeSignal == 200) {
          CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.Time ) + 0.5);
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          CAN_Msg[2] |= CAN_Sgn.SgnBytes.Byte0;
        }
      }

      can_tp1_msg_send(can_type1_msg_M1[CANTP1_M1_C1_TX_STD_0X161], 3,
                       &(CAN_Msg[0]), delayTime);
    }
  }

  if ((rt_ZCFcn(ANY_ZERO_CROSSING,
                &Racing_2019_PrevZCX.Inverter_LEFT_CAN_0x161_Reset_Z,
                (Racing_2019_B.SFunction1_kx)) != NO_ZCEVENT) ||
      (Racing_2019_B.SFunction1_kx != 0.0)) {
    for (i = 0; i < 1000; i++) {
      Racing_2019_DW.Inverter_LEFT_CAN_0x161_DSTATE[i] =
        Racing_2019_P.Inverter_LEFT_CAN_0x161_Initial;
    }
  }

  Racing_2019_B.Inverter_LEFT_CAN_0x161 =
    Racing_2019_DW.Inverter_LEFT_CAN_0x161_DSTATE[0];
  Racing_2019_B.LogicalOperator = (Racing_2019_B.Compare &&
    (Racing_2019_B.Inverter_RIGHT_CAN_0x162 != 0.0) &&
    (Racing_2019_B.Inverter_LEFT_CAN_0x161 != 0.0));
  if (Racing_2019_M->Timing.RateInteraction.TID1_2 == 1) {
    Racing_2019_B.to100Hz3 = Racing_2019_B.LogicalOperator;
  }

  {
    UInt32 loop_counter, memory, j;
    for (j=0;j<=9;j++) {
      rtican_type1_tq_error[0][6] = can_tp1_service_read
        (can_type1_service_M1_C2[j]);
      loop_counter = 0;
      while ((rtican_type1_tq_error[0][6] = can_tp1_service_request
              (can_type1_service_M1_C2[j]))== DSMCOM_BUFFER_OVERFLOW) {
        loop_counter++;
        if (loop_counter > MAX_LOOP) {
          memory = rtican_type1_error_level;
          rtican_type1_error_level = 1;
          rtican_type1_tq_err_sig(0, 6);
          rtican_type1_error_level = memory;
          break;
        }
      }

      if (j==CANTP1_M1_C2_RXLost) {
        rtican_type1_tq_error[0][6] = can_tp1_service_read
          (can_type1_service_M1_C2[CANTP1_M1_C2_DataLost]);
        loop_counter = 0;
        while ((rtican_type1_tq_error[0][6] = can_tp1_service_request
                (can_type1_service_M1_C2[CANTP1_M1_C2_DataLost]))==
               DSMCOM_BUFFER_OVERFLOW) {
          loop_counter++;
          if (loop_counter > MAX_LOOP) {
            memory = rtican_type1_error_level;
            rtican_type1_error_level = 1;
            rtican_type1_tq_err_sig(0, 6);
            rtican_type1_error_level = memory;
            break;
          }
        }
      }
    }

    Racing_2019_B.SFunction1_o1_et = (UInt32)
      can_type1_service_M1_C2[CANTP1_M1_C2_Status]->data0;
    Racing_2019_B.SFunction1_o2_ga = (UInt32)
      can_type1_service_M1_C2[CANTP1_M1_C2_StuffErrors]->data0;
    Racing_2019_B.SFunction1_o3_n2 = (UInt32)
      can_type1_service_M1_C2[CANTP1_M1_C2_FormatErrors]->data0;
    Racing_2019_B.SFunction1_o4_is = (UInt32)
      can_type1_service_M1_C2[CANTP1_M1_C2_AckErrors]->data0;
    Racing_2019_B.SFunction1_o5_gi = (UInt32)
      can_type1_service_M1_C2[CANTP1_M1_C2_Bit0Errors]->data0;
    Racing_2019_B.SFunction1_o6_nl = (UInt32)
      can_type1_service_M1_C2[CANTP1_M1_C2_Bit1Errors]->data0;
    Racing_2019_B.SFunction1_o7 = (UInt32)
      can_type1_service_M1_C2[CANTP1_M1_C2_CRCErrors]->data0;
    Racing_2019_B.SFunction1_o8_o = (UInt32)
      (can_type1_service_M1_C2[CANTP1_M1_C2_RXLost]->data0 +
       can_type1_service_M1_C2[CANTP1_M1_C2_DataLost]->data0);
    Racing_2019_B.SFunction1_o9 = (UInt32)
      can_type1_service_M1_C2[CANTP1_M1_C2_RXOK]->data0;
    Racing_2019_B.SFunction1_o10 = (UInt32)
      can_type1_service_M1_C2[CANTP1_M1_C2_TXOK]->data0;
  }

  Racing_2019_B.Compare_h = (Racing_2019_B.SFunction1_o1_et >=
    Racing_2019_P.CompareToConstant16_const);
  Racing_2019_B.Compare_k = (Racing_2019_B.SFunction1_o2_ga >
    Racing_2019_P.CompareToConstant15_const);
  Racing_2019_B.Compare_pr = (Racing_2019_B.SFunction1_o3_n2 >
    Racing_2019_P.CompareToConstant14_const_g);
  Racing_2019_B.Compare_jk = (Racing_2019_B.SFunction1_o4_is >
    Racing_2019_P.CompareToConstant13_const_g);
  Racing_2019_B.Compare_dk = (Racing_2019_B.SFunction1_o5_gi >
    Racing_2019_P.CompareToConstant12_const_j);
  Racing_2019_B.Compare_i = (Racing_2019_B.SFunction1_o6_nl >
    Racing_2019_P.CompareToConstant11_const);
  Racing_2019_B.Compare_a = (Racing_2019_B.SFunction1_o7 >
    Racing_2019_P.CompareToConstant10_const);
  Racing_2019_B.Compare_hj = (Racing_2019_B.SFunction1_o8_o >
    Racing_2019_P.CompareToConstant9_const);
  Racing_2019_B.InverterLEFTCANError = (Racing_2019_B.Compare_h ||
    Racing_2019_B.Compare_k || Racing_2019_B.Compare_pr ||
    Racing_2019_B.Compare_jk || Racing_2019_B.Compare_dk ||
    Racing_2019_B.Compare_i || Racing_2019_B.Compare_a ||
    Racing_2019_B.Compare_hj);

  {
    UInt32 loop_counter, memory, j;
    for (j=0;j<=9;j++) {
      rtican_type1_tq_error[0][6] = can_tp1_service_read
        (can_type1_service_M1_C1[j]);
      loop_counter = 0;
      while ((rtican_type1_tq_error[0][6] = can_tp1_service_request
              (can_type1_service_M1_C1[j]))== DSMCOM_BUFFER_OVERFLOW) {
        loop_counter++;
        if (loop_counter > MAX_LOOP) {
          memory = rtican_type1_error_level;
          rtican_type1_error_level = 1;
          rtican_type1_tq_err_sig(0, 6);
          rtican_type1_error_level = memory;
          break;
        }
      }

      if (j==CANTP1_M1_C1_RXLost) {
        rtican_type1_tq_error[0][6] = can_tp1_service_read
          (can_type1_service_M1_C1[CANTP1_M1_C1_DataLost]);
        loop_counter = 0;
        while ((rtican_type1_tq_error[0][6] = can_tp1_service_request
                (can_type1_service_M1_C1[CANTP1_M1_C1_DataLost]))==
               DSMCOM_BUFFER_OVERFLOW) {
          loop_counter++;
          if (loop_counter > MAX_LOOP) {
            memory = rtican_type1_error_level;
            rtican_type1_error_level = 1;
            rtican_type1_tq_err_sig(0, 6);
            rtican_type1_error_level = memory;
            break;
          }
        }
      }
    }

    Racing_2019_B.SFunction1_o1_i = (UInt32)
      can_type1_service_M1_C1[CANTP1_M1_C1_Status]->data0;
    Racing_2019_B.SFunction1_o2_o = (UInt32)
      can_type1_service_M1_C1[CANTP1_M1_C1_StuffErrors]->data0;
    Racing_2019_B.SFunction1_o3_os = (UInt32)
      can_type1_service_M1_C1[CANTP1_M1_C1_FormatErrors]->data0;
    Racing_2019_B.SFunction1_o4_j = (UInt32)
      can_type1_service_M1_C1[CANTP1_M1_C1_AckErrors]->data0;
    Racing_2019_B.SFunction1_o5_e = (UInt32)
      can_type1_service_M1_C1[CANTP1_M1_C1_Bit0Errors]->data0;
    Racing_2019_B.SFunction1_o6_mp = (UInt32)
      can_type1_service_M1_C1[CANTP1_M1_C1_Bit1Errors]->data0;
    Racing_2019_B.SFunction1_o7_n = (UInt32)
      can_type1_service_M1_C1[CANTP1_M1_C1_CRCErrors]->data0;
    Racing_2019_B.SFunction1_o8_n = (UInt32)
      (can_type1_service_M1_C1[CANTP1_M1_C1_RXLost]->data0 +
       can_type1_service_M1_C1[CANTP1_M1_C1_DataLost]->data0);
    Racing_2019_B.SFunction1_o9_j = (UInt32)
      can_type1_service_M1_C1[CANTP1_M1_C1_RXOK]->data0;
    Racing_2019_B.SFunction1_o10_f = (UInt32)
      can_type1_service_M1_C1[CANTP1_M1_C1_TXOK]->data0;
  }

  Racing_2019_B.Compare_dx = (Racing_2019_B.SFunction1_o1_i >=
    Racing_2019_P.CompareToConstant23_const);
  Racing_2019_B.Compare_hf = (Racing_2019_B.SFunction1_o2_o >
    Racing_2019_P.CompareToConstant22_const);
  Racing_2019_B.Compare_e = (Racing_2019_B.SFunction1_o3_os >
    Racing_2019_P.CompareToConstant21_const);
  Racing_2019_B.Compare_ah = (Racing_2019_B.SFunction1_o4_j >
    Racing_2019_P.CompareToConstant20_const);
  Racing_2019_B.Compare_i2 = (Racing_2019_B.SFunction1_o5_e >
    Racing_2019_P.CompareToConstant19_const);
  Racing_2019_B.Compare_js = (Racing_2019_B.SFunction1_o6_mp >
    Racing_2019_P.CompareToConstant18_const);
  Racing_2019_B.Compare_mb = (Racing_2019_B.SFunction1_o7_n >
    Racing_2019_P.CompareToConstant17_const_m);
  Racing_2019_B.Compare_eq = (Racing_2019_B.SFunction1_o8_n >
    Racing_2019_P.CompareToConstant24_const);
  Racing_2019_B.InverterRIGHTCANError = (Racing_2019_B.Compare_dx ||
    Racing_2019_B.Compare_hf || Racing_2019_B.Compare_e ||
    Racing_2019_B.Compare_ah || Racing_2019_B.Compare_i2 ||
    Racing_2019_B.Compare_js || Racing_2019_B.Compare_mb ||
    Racing_2019_B.Compare_eq);
  Racing_2019_B.CANError = (Racing_2019_B.InverterLEFTCANError ||
    Racing_2019_B.InverterRIGHTCANError || (Racing_2019_P.Constant1_Value_j !=
    0.0) || (Racing_2019_P.Constant_Value_nj != 0.0));
  Racing_2019_B.LogicalOperator2 = !Racing_2019_B.CANError;
  if (Racing_2019_M->Timing.RateInteraction.TID1_2 == 1) {
    Racing_2019_B.to100Hz4 = Racing_2019_B.LogicalOperator2;
  }

  if ((rt_ZCFcn(ANY_ZERO_CROSSING,
                &Racing_2019_PrevZCX.Inverter_LEFT_CAN_0x181_Reset_Z,
                (Racing_2019_B.SFunction1_o3)) != NO_ZCEVENT) ||
      (Racing_2019_B.SFunction1_o3 != 0.0)) {
    for (i = 0; i < 10000; i++) {
      Racing_2019_DW.Inverter_LEFT_CAN_0x181_DSTATE[i] =
        Racing_2019_P.Inverter_LEFT_CAN_0x181_Initial;
    }
  }

  Racing_2019_B.Inverter_LEFT_CAN_0x181 =
    Racing_2019_DW.Inverter_LEFT_CAN_0x181_DSTATE[0];
  if (Racing_2019_M->Timing.RateInteraction.TID1_2 == 1) {
    Racing_2019_B.to100Hz8 = Racing_2019_B.Inverter_LEFT_CAN_0x181;
  }

  if ((rt_ZCFcn(ANY_ZERO_CROSSING,
                &Racing_2019_PrevZCX.Inverter_RIGHT_CAN_0x182_Reset_,
                (Racing_2019_B.SFunction1_o3_h)) != NO_ZCEVENT) ||
      (Racing_2019_B.SFunction1_o3_h != 0.0)) {
    for (i = 0; i < 10000; i++) {
      Racing_2019_DW.Inverter_RIGHT_CAN_0x182_DSTATE[i] =
        Racing_2019_P.Inverter_RIGHT_CAN_0x182_Initia;
    }
  }

  Racing_2019_B.Inverter_RIGHT_CAN_0x182 =
    Racing_2019_DW.Inverter_RIGHT_CAN_0x182_DSTATE[0];
  if (Racing_2019_M->Timing.RateInteraction.TID1_2 == 1) {
    Racing_2019_B.to100Hz9 = Racing_2019_B.Inverter_RIGHT_CAN_0x182;
  }

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XC6]);
    if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XC6]->processed) {
      can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XC6]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XC6]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XC6]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XC6]->processed) {
        Racing_2019_B.SFunction1_o3_a = (real_T)
          can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XC6]->processed;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XC6]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_gy = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_b1 = ((UInt16) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XC6]->processed) {
      Racing_2019_B.SFunction1_o3_a = 0.0;
    }
  }

  Racing_2019_B.Subtract = (real_T)Racing_2019_B.SFunction1_o1_gy -
    Racing_2019_P.Brake_Threshold_Value;
  Racing_2019_B.Brake_Gain_1000 = Racing_2019_P.Brake_Gain_1000_Gain *
    Racing_2019_B.Subtract;
  u1_1 = floor(Racing_2019_B.Brake_Gain_1000);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 65536.0);
  }

  Racing_2019_B.DataTypeConversion6_dk = (uint16_T)(u1_1 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_1 : (int32_T)(uint16_T)u1_1);
  if (Racing_2019_M->Timing.RateInteraction.TID1_2 == 1) {
    Racing_2019_B.to100Hz12 = Racing_2019_B.DataTypeConversion6_dk;
    Racing_2019_B.to100Hz13 = Racing_2019_B.VDC_Transfer_Function;
  }

  Racing_2019_B.Compare_mf = (Racing_2019_B.SFunction1_o1_gy <
    Racing_2019_P.CompareToConstant4_const_n);
  Racing_2019_B.Compare_c = (Racing_2019_B.SFunction1_o1_gy >
    Racing_2019_P.CompareToConstant5_const_a);
  Racing_2019_B.Brake_Error_OR = (Racing_2019_B.Compare_mf ||
    Racing_2019_B.Compare_c);
  Racing_2019_B.Compare_n = (Racing_2019_B.SFunction1_o1_f0 <
    Racing_2019_P.CompareToConstant6_const_a);
  Racing_2019_B.Compare_gg = (Racing_2019_B.SFunction1_o1_f0 >
    Racing_2019_P.CompareToConstant7_const_p);
  Racing_2019_B.APPS1_Error_OR = (Racing_2019_B.Compare_n ||
    Racing_2019_B.Compare_gg);
  Racing_2019_B.Compare_o = (Racing_2019_B.SFunction1_o2_o2 <
    Racing_2019_P.CompareToConstant8_const_j);
  Racing_2019_B.Compare_px = (Racing_2019_B.SFunction1_o2_o2 >
    Racing_2019_P.CompareToConstant9_const_f);
  Racing_2019_B.APPS2_Error_OR = (Racing_2019_B.Compare_o ||
    Racing_2019_B.Compare_px);
  Racing_2019_B.Sensor_Error_OR = (Racing_2019_B.Brake_Error_OR ||
    Racing_2019_B.APPS1_Error_OR || (Racing_2019_P.Constant1_Value_jz != 0.0) ||
    Racing_2019_B.APPS2_Error_OR || (Racing_2019_P.Constant_Value_k != 0.0));
  zcEvent = ((!Racing_2019_B.Sensor_Error_OR) &&
             (Racing_2019_PrevZCX.ResettableDelay50ms_Reset_ZCE_d != ZERO_ZCSIG));
  if (zcEvent) {
    for (i = 0; i < 50; i++) {
      Racing_2019_DW.ResettableDelay50ms_DSTATE_h[i] =
        Racing_2019_P.ResettableDelay50ms_InitialCo_f;
    }
  }

  Racing_2019_PrevZCX.ResettableDelay50ms_Reset_ZCE_d =
    Racing_2019_B.Sensor_Error_OR;
  Racing_2019_B.ResettableDelay50ms_k =
    Racing_2019_DW.ResettableDelay50ms_DSTATE_h[0];
  if (Racing_2019_M->Timing.RateInteraction.TID1_2 == 1) {
    Racing_2019_B.to100Hz14 = Racing_2019_B.ResettableDelay50ms_k;
  }

  Racing_2019_B.Add_b = Racing_2019_P.Constant1_Value_c +
    Racing_2019_P.Brake_Plausibility_Threshold;
  Racing_2019_B.RelationalOperator = (Racing_2019_B.DataTypeConversion6_dk >=
    Racing_2019_B.Add_b);
  Racing_2019_B.Compare_g1 = (Racing_2019_B.Switch_e1 >=
    Racing_2019_P.CompareToConstant_const_l);
  Racing_2019_B.LogicalOperator_i = (Racing_2019_B.RelationalOperator &&
    Racing_2019_B.Compare_g1);
  zcEvent = (Racing_2019_B.LogicalOperator_i &&
             (Racing_2019_PrevZCX.ResettableDelay350ms_Reset_ZCE != POS_ZCSIG));
  if (zcEvent) {
    for (i = 0; i < 350; i++) {
      Racing_2019_DW.ResettableDelay350ms_DSTATE[i] =
        Racing_2019_P.ResettableDelay350ms_InitialCon;
    }
  }

  Racing_2019_PrevZCX.ResettableDelay350ms_Reset_ZCE =
    Racing_2019_B.LogicalOperator_i;
  Racing_2019_B.ResettableDelay350ms =
    Racing_2019_DW.ResettableDelay350ms_DSTATE[0];
  Racing_2019_B.Compare_ig = (Racing_2019_B.Switch_e1 <=
    Racing_2019_P.CompareToConstant1_const_e);
  Racing_2019_B.Memory_k = Racing_2019_DW.Memory_PreviousInput_h;
  zcEvent = Racing_2019_B.ResettableDelay350ms;
  i = zcEvent;
  zcEvent = Racing_2019_B.Compare_ig;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  zcEvent = Racing_2019_B.Memory_k;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  Racing_2019_B.Logic_j[0U] = Racing_2019_P.Logic_table_i[(uint32_T)i];
  Racing_2019_B.Logic_j[1U] = Racing_2019_P.Logic_table_i[i + 8U];
  if (Racing_2019_M->Timing.RateInteraction.TID1_2 == 1) {
    Racing_2019_B.to100Hz15 = Racing_2019_B.Logic_j[0];
  }

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XC8]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XC8]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XC8]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XC8]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XC8]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XC8]->processed) {
        Racing_2019_B.SFunction1_o4_a = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XC8]->processed;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XC8]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte0 = CAN_Msg[0];
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          Racing_2019_B.SFunction1_o1_gs = ((UInt8) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.SignedSgn &= 0x0000FFFF;
          if (CAN_Sgn.SignedSgn >> 15) {
            CAN_Sgn.SignedSgn |= 0xFFFF0000;
          }

          Racing_2019_B.SFunction1_o2_ah = ((Int16) CAN_Sgn.SignedSgn);
          CAN_Sgn.SgnBytes.Byte0 = CAN_Msg[5];
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          Racing_2019_B.SFunction1_o3_n2g = ((UInt8) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XC8]->processed) {
      Racing_2019_B.SFunction1_o4_a = 0.0;
    }
  }

  Racing_2019_B.BMS = !(Racing_2019_B.SFunction1_o1_gs != 0);
  Racing_2019_B.DataTypeConversion3_ez = Racing_2019_B.BMS;
  if (Racing_2019_M->Timing.RateInteraction.TID1_2 == 1) {
    Racing_2019_B.to100Hz18 = Racing_2019_B.DataTypeConversion3_ez;
  }

  Racing_2019_B.Compare_f = (Racing_2019_B.VDC_Transfer_Function >=
    Racing_2019_P.CompareToConstant_const);
  Racing_2019_B.DataTypeConversion2_d = Racing_2019_B.Compare_f;
  Racing_2019_B.UnitDelay = Racing_2019_DW.UnitDelay_DSTATE;
  switch ((int32_T)Racing_2019_P.EdgeDetector_model) {
   case 1:
    Racing_2019_B.MultiportSwitch[0] = Racing_2019_P.posedge_Value[0];
    Racing_2019_B.MultiportSwitch[1] = Racing_2019_P.posedge_Value[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch[0] = Racing_2019_P.negedge_Value[0];
    Racing_2019_B.MultiportSwitch[1] = Racing_2019_P.negedge_Value[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch[0] = Racing_2019_P.eitheredge_Value[0];
    Racing_2019_B.MultiportSwitch[1] = Racing_2019_P.eitheredge_Value[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch[0],
    Racing_2019_B.DataTypeConversion2_d, Racing_2019_B.UnitDelay,
    &Racing_2019_B.POSITIVEEdge);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch[1],
    Racing_2019_B.DataTypeConversion2_d, Racing_2019_B.UnitDelay,
    &Racing_2019_B.NEGATIVEEdge);
  Racing_2019_B.LogicalOperator1_g =
    (Racing_2019_B.POSITIVEEdge.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge.RelationalOperator1);
  Racing_2019_B.LogicalOperator3_h = ((Racing_2019_P.Car_Reset != 0.0) ||
    Racing_2019_B.LogicalOperator1_g);
  Racing_2019_B.LogicalOperator2_d = (Racing_2019_B.LogicalOperator3_h &&
    (Racing_2019_P.Car_Reset_Enable != 0.0));
  Racing_2019_B.DataTypeConversion2_n3 = Racing_2019_B.LogicalOperator2_d;
  dio_tp4_digout_write(DIO_TP4_1_MODULE_ADDR, 1, DIO_TP4_MASK_CH10, (UInt16)
                       (Racing_2019_B.DataTypeConversion2_n3 << 9));
  Racing_2019_B.DataTypeConversion5_c = Racing_2019_B.DataTypeConversion2_n3;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Car_Reset_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion5_c);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.LogicalOperator1_e = ((Racing_2019_P.BMS_Reset != 0.0) ||
    Racing_2019_B.LogicalOperator1_g);
  Racing_2019_B.LogicalOperator_c = (Racing_2019_B.LogicalOperator1_e &&
    (Racing_2019_P.BMS_Reset_Enable != 0.0));
  Racing_2019_B.DataTypeConversion1_nd = Racing_2019_B.LogicalOperator_c;
  dio_tp4_digout_write(DIO_TP4_1_MODULE_ADDR, 1, DIO_TP4_MASK_CH4, (UInt16)
                       (Racing_2019_B.DataTypeConversion1_nd << 3));
  Racing_2019_B.DataTypeConversion4_b = Racing_2019_B.DataTypeConversion1_nd;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(BMS_Reset_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion4_b);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion7_f = Racing_2019_B.BMS;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(BMS_Status_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion7_f);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion69 = Racing_2019_B.SFunction1_o2_ah;
  Racing_2019_B.Gain84 = (int16_T)(Racing_2019_P.Gain84_Gain *
    Racing_2019_B.DataTypeConversion69 >> 11);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Idc_Accu_x10_Index_UsbFlRec, (Int32)
      Racing_2019_B.Gain84);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion2_k = (Racing_2019_B.SFunction1_o4_a != 0.0);
  Racing_2019_B.UnitDelay_d = Racing_2019_DW.UnitDelay_DSTATE_c;
  switch ((int32_T)Racing_2019_P.EdgeDetector_model_n) {
   case 1:
    Racing_2019_B.MultiportSwitch_i[0] = Racing_2019_P.posedge_Value_l[0];
    Racing_2019_B.MultiportSwitch_i[1] = Racing_2019_P.posedge_Value_l[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_i[0] = Racing_2019_P.negedge_Value_h[0];
    Racing_2019_B.MultiportSwitch_i[1] = Racing_2019_P.negedge_Value_h[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_i[0] = Racing_2019_P.eitheredge_Value_p[0];
    Racing_2019_B.MultiportSwitch_i[1] = Racing_2019_P.eitheredge_Value_p[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_i[0],
    Racing_2019_B.DataTypeConversion2_k, Racing_2019_B.UnitDelay_d,
    &Racing_2019_B.POSITIVEEdge_k);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_i[1],
    Racing_2019_B.DataTypeConversion2_k, Racing_2019_B.UnitDelay_d,
    &Racing_2019_B.NEGATIVEEdge_p);
  Racing_2019_B.LogicalOperator1_gm =
    (Racing_2019_B.POSITIVEEdge_k.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_p.RelationalOperator1);
  Racing_2019_B.DataTypeConversion1_g = Racing_2019_B.LogicalOperator1_gm;
  Racing_2019_B.BMS_CAN_200_Counter =
    Racing_2019_DW.BMS_CAN_200_Counter_PreviousInp;
  Racing_2019_B.Add_n = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion1_g
    + Racing_2019_B.BMS_CAN_200_Counter);
  if ((rt_ZCFcn(ANY_ZERO_CROSSING,&Racing_2019_PrevZCX.BMS_CAN_200_Reset_ZCE,
                (Racing_2019_B.SFunction1_o4_a)) != NO_ZCEVENT) ||
      (Racing_2019_B.SFunction1_o4_a != 0.0)) {
    for (i = 0; i < 2000; i++) {
      Racing_2019_DW.BMS_CAN_200_DSTATE[i] =
        Racing_2019_P.BMS_CAN_200_InitialCondition;
    }
  }

  Racing_2019_B.BMS_CAN_200 = Racing_2019_DW.BMS_CAN_200_DSTATE[0];
  if (Racing_2019_M->Timing.RateInteraction.TID1_4 == 1) {
    Racing_2019_B.CAN_ID200100Hzto5Hz = Racing_2019_B.BMS_CAN_200;
  }

  Racing_2019_B.DataTypeConversion2_o = Racing_2019_B.SFunction1_o3_n2g;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X13A]);
    if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X13A]->processed) {
      can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X13A]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X13A]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X13A]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X13A]->processed) {
        Racing_2019_B.SFunction1_o3_bg = (real_T)
          can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X13A]->processed;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X13A]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_ja = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_la = ((UInt16) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X13A]->processed) {
      Racing_2019_B.SFunction1_o3_bg = 0.0;
    }
  }

  if ((rt_ZCFcn(ANY_ZERO_CROSSING,&Racing_2019_PrevZCX.AUX_CAN_314_Reset_ZCE,
                (Racing_2019_B.SFunction1_o3_bg)) != NO_ZCEVENT) ||
      (Racing_2019_B.SFunction1_o3_bg != 0.0)) {
    for (i = 0; i < 2000; i++) {
      Racing_2019_DW.AUX_CAN_314_DSTATE[i] =
        Racing_2019_P.AUX_CAN_314_InitialCondition;
    }
  }

  Racing_2019_B.AUX_CAN_314 = Racing_2019_DW.AUX_CAN_314_DSTATE[0];
  if (Racing_2019_M->Timing.RateInteraction.TID1_3 == 1) {
    Racing_2019_B.AUX3141kHzto10Hz = Racing_2019_B.AUX_CAN_314;
  }

  Racing_2019_B.DataTypeConversion7_ka = Racing_2019_B.SFunction1_o1_ja;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Susp_RL_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion7_ka);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion8_c = Racing_2019_B.SFunction1_o2_la;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Susp_RR_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion8_c);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.AUX_CAN_314_Counter =
    Racing_2019_DW.AUX_CAN_314_Counter_PreviousInp;
  Racing_2019_B.DataTypeConversion2_n5 = (Racing_2019_B.SFunction1_o3_bg != 0.0);
  Racing_2019_B.UnitDelay_mu = Racing_2019_DW.UnitDelay_DSTATE_c1;
  switch ((int32_T)Racing_2019_P.EdgeDetector_model_l) {
   case 1:
    Racing_2019_B.MultiportSwitch_il[0] = Racing_2019_P.posedge_Value_k[0];
    Racing_2019_B.MultiportSwitch_il[1] = Racing_2019_P.posedge_Value_k[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_il[0] = Racing_2019_P.negedge_Value_ox[0];
    Racing_2019_B.MultiportSwitch_il[1] = Racing_2019_P.negedge_Value_ox[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_il[0] = Racing_2019_P.eitheredge_Value_gw[0];
    Racing_2019_B.MultiportSwitch_il[1] = Racing_2019_P.eitheredge_Value_gw[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_il[0],
    Racing_2019_B.DataTypeConversion2_n5, Racing_2019_B.UnitDelay_mu,
    &Racing_2019_B.POSITIVEEdge_hj);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_il[1],
    Racing_2019_B.DataTypeConversion2_n5, Racing_2019_B.UnitDelay_mu,
    &Racing_2019_B.NEGATIVEEdge_jrj);
  Racing_2019_B.LogicalOperator1_bb =
    (Racing_2019_B.POSITIVEEdge_hj.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_jrj.RelationalOperator1);
  Racing_2019_B.DataTypeConversion63 = Racing_2019_B.LogicalOperator1_bb;
  Racing_2019_B.Add1_fb = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion63
    + Racing_2019_B.AUX_CAN_314_Counter);
  Racing_2019_B.DataTypeConversion7_kt = (real32_T)
    Racing_2019_B.IGBTTempLEFTRaw.In1;
  tmp_0 = Racing_2019_B.DataTypeConversion7_kt;
  tmp = rt_powf_snf(tmp_0, 3.0F);
  tmp_0 = Racing_2019_B.DataTypeConversion7_kt;
  tmp_0 = rt_powf_snf(tmp_0, 2.0F);
  Racing_2019_B.IGBTTempLEFT = ((8.12e-11F * tmp - 5.61e-6F * tmp_0) + 0.1361F *
    Racing_2019_B.DataTypeConversion7_kt) - 1096.0F;
  Racing_2019_B.DataTypeConversion7_ar = (real32_T)
    Racing_2019_B.IGBTTempRIGHTRaw.In1;
  tmp_0 = Racing_2019_B.DataTypeConversion7_ar;
  tmp = rt_powf_snf(tmp_0, 3.0F);
  tmp_0 = Racing_2019_B.DataTypeConversion7_ar;
  tmp_0 = rt_powf_snf(tmp_0, 2.0F);
  Racing_2019_B.IGBTTempRIGHT = ((8.12e-11F * tmp - 5.61e-6F * tmp_0) + 0.1361F *
    Racing_2019_B.DataTypeConversion7_ar) - 1096.0F;
  if (Racing_2019_M->Timing.RateInteraction.TID1_3 == 1) {
    Racing_2019_B.IGBTTempto10Hz = Racing_2019_B.IGBTTempLEFT;
    Racing_2019_B.IGBTTempto10Hz_f = Racing_2019_B.IGBTTempRIGHT;
  }

  Racing_2019_B.Compare_ml = (Racing_2019_B.DataTypeConversion6_dk >=
    Racing_2019_P.Constant_Value_d0);
  Racing_2019_B.Subtract_c = Racing_2019_P.Constant2_Value_c -
    Racing_2019_P.Constant1_Value_m;
  Racing_2019_B.RelationalOperator_c = (Racing_2019_B.DataTypeConversion6_dk <=
    Racing_2019_B.Subtract_c);
  Racing_2019_B.LogicalOperator3_c = !Racing_2019_B.RelationalOperator_c;
  Racing_2019_B.Memory_gz = Racing_2019_DW.Memory_PreviousInput_fq;
  Racing_2019_B.LogicalOperator_m = (Racing_2019_B.LogicalOperator3_c &&
    Racing_2019_B.Memory_gz);
  Racing_2019_B.LogicalOperator2_h5 = (Racing_2019_B.Compare_ml ||
    Racing_2019_B.LogicalOperator_m);
  Racing_2019_B.Memory_k4 = Racing_2019_DW.Memory_PreviousInput_l;
  zcEvent = Racing_2019_B.LogicalOperator2_h5;
  i = zcEvent;
  zcEvent = Racing_2019_B.RelationalOperator_c;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  zcEvent = Racing_2019_B.Memory_k4;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  Racing_2019_B.Logic_g[0U] = Racing_2019_P.Logic_table_hi[(uint32_T)i];
  Racing_2019_B.Logic_g[1U] = Racing_2019_P.Logic_table_hi[i + 8U];
  Racing_2019_B.LogicalOperator1_el = ((Racing_2019_P.Brakelight_Test != 0.0) ||
    Racing_2019_B.Logic_g[0]);
  zcEvent = ((!Racing_2019_B.LogicalOperator1_el) &&
             (Racing_2019_PrevZCX.ResettableDelay50ms_Reset_ZCE_m != ZERO_ZCSIG));
  if (zcEvent) {
    for (i = 0; i < 50; i++) {
      Racing_2019_DW.ResettableDelay50ms_DSTATE_j[i] =
        Racing_2019_P.ResettableDelay50ms_InitialCo_b;
    }
  }

  Racing_2019_PrevZCX.ResettableDelay50ms_Reset_ZCE_m =
    Racing_2019_B.LogicalOperator1_el;
  Racing_2019_B.ResettableDelay50ms_d =
    Racing_2019_DW.ResettableDelay50ms_DSTATE_j[0];
  u1_1 = floor((real_T)Racing_2019_B.ResettableDelay50ms_d *
               Racing_2019_P.Constant_Value_c);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 256.0);
  }

  Racing_2019_B.Brakelight = (uint8_T)(u1_1 < 0.0 ? (int32_T)(uint8_T)-(int8_T)
    (uint8_T)-u1_1 : (int32_T)(uint8_T)u1_1);

  {
    UInt32 CAN_Msg[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    Float32 delayTime = 0.0;
    can_tp1_msg_read(can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XA6]);
    if (can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XA6]->processed) {
      can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XA6]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XA6]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XA6]->timestamp > 0.0) {
      Racing_2019_B.SFunction1_o1_age = (real_T)
        can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XA6]->processed;
      Racing_2019_B.SFunction1_o2_b = (real_T)
        can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XA6]->delaytime;
    }

    {
      rtican_Signal_t CAN_Sgn;
      CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.Brakelight ) + 0.5);
      CAN_Sgn.UnsignedSgn &= 0x000000FF;
      CAN_Msg[0] |= CAN_Sgn.SgnBytes.Byte0;
    }

    can_tp1_msg_send(can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XA6], 8, &(CAN_Msg[0]),
                     delayTime);
  }

  if (Racing_2019_M->Timing.RateInteraction.TID1_3 == 1) {
    Racing_2019_B.RateTransition9 = Racing_2019_B.SFunction1_o1_age;
  }

  Racing_2019_B.Compare_gn = (Racing_2019_B.SFunction1_o2_b >=
    Racing_2019_P.AUX_Error_Time);
  Racing_2019_B.InverterLEFTBaudrateRx =
    Racing_2019_DW.InverterLEFTBaudrateRx_Previous;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(Baudrate_Rx_Accu_Index_UsbFlRec,
      (Float32)Racing_2019_B.InverterLEFTBaudrateRx);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.InverterRIGHTBaudrateRx =
    Racing_2019_DW.InverterRIGHTBaudrateRx_Previou;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32
      (Baudrate_Rx_Inverter_RIGHT_Index_UsbFlRec, (Float32)
       Racing_2019_B.InverterRIGHTBaudrateRx);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.InverterLEFTBaudrateTx =
    Racing_2019_DW.InverterLEFTBaudrateTx_Previous;
  Racing_2019_B.InverterLEFTCANBaudrate = Racing_2019_B.InverterLEFTBaudrateRx +
    (real32_T)Racing_2019_B.InverterLEFTBaudrateTx;
  Racing_2019_B.Output = Racing_2019_DW.Output_DSTATE;
  Racing_2019_B.Compare_ld = (Racing_2019_B.Output >=
    Racing_2019_P.CompareToConstant_const_c);
  Racing_2019_B.FixPtSum1 = (uint16_T)((uint32_T)Racing_2019_B.Output +
    Racing_2019_P.FixPtConstant_Value);
  if (Racing_2019_B.FixPtSum1 > Racing_2019_P.CounterLimited_uplimit) {
    Racing_2019_B.FixPtSwitch = Racing_2019_P.Constant_Value_e;
  } else {
    Racing_2019_B.FixPtSwitch = Racing_2019_B.FixPtSum1;
  }

  Racing_2019_B.Delay2ms = Racing_2019_DW.Delay2ms_DSTATE[0];
  Racing_2019_B.Memory1 = Racing_2019_DW.Memory1_PreviousInput;
  Racing_2019_B.MovingBaudrate = Racing_2019_B.SFunction1_o9 -
    Racing_2019_B.Memory1;
  if (Racing_2019_B.Delay2ms) {
    Racing_2019_B.Switch_j = Racing_2019_B.SFunction1_o9;
  } else {
    Racing_2019_B.Switch_j = Racing_2019_B.Memory1;
  }

  if (Racing_2019_B.Compare_ld) {
    Racing_2019_B.Switch1_k = (real32_T)Racing_2019_B.MovingBaudrate;
  } else {
    Racing_2019_B.Switch1_k = Racing_2019_B.InverterLEFTBaudrateRx;
  }

  Racing_2019_B.Output_a = Racing_2019_DW.Output_DSTATE_f;
  Racing_2019_B.Compare_or = (Racing_2019_B.Output_a >=
    Racing_2019_P.CompareToConstant_const_p);
  Racing_2019_B.FixPtSum1_f = (uint16_T)((uint32_T)Racing_2019_B.Output_a +
    Racing_2019_P.FixPtConstant_Value_e);
  if (Racing_2019_B.FixPtSum1_f > Racing_2019_P.CounterLimited_uplimit_i) {
    Racing_2019_B.FixPtSwitch_d = Racing_2019_P.Constant_Value_ak;
  } else {
    Racing_2019_B.FixPtSwitch_d = Racing_2019_B.FixPtSum1_f;
  }

  Racing_2019_B.Delay2ms_j = Racing_2019_DW.Delay2ms_DSTATE_n[0];
  Racing_2019_B.Memory1_k = Racing_2019_DW.Memory1_PreviousInput_n;
  Racing_2019_B.MovingBaudrate_j = Racing_2019_B.SFunction1_o10 -
    Racing_2019_B.Memory1_k;
  if (Racing_2019_B.Delay2ms_j) {
    Racing_2019_B.Switch_bi = Racing_2019_B.SFunction1_o10;
  } else {
    Racing_2019_B.Switch_bi = Racing_2019_B.Memory1_k;
  }

  if (Racing_2019_B.Compare_or) {
    Racing_2019_B.Switch1_o = Racing_2019_B.MovingBaudrate_j;
  } else {
    Racing_2019_B.Switch1_o = Racing_2019_B.InverterLEFTBaudrateTx;
  }

  Racing_2019_B.InverterLEFTBaudrateTx_b =
    Racing_2019_DW.InverterLEFTBaudrateTx_Previo_o;
  Racing_2019_B.InverterRIGHTCANBaudrate = Racing_2019_B.InverterRIGHTBaudrateRx
    + (real32_T)Racing_2019_B.InverterLEFTBaudrateTx_b;
  Racing_2019_B.Output_l = Racing_2019_DW.Output_DSTATE_c;
  Racing_2019_B.Compare_cx = (Racing_2019_B.Output_l >=
    Racing_2019_P.CompareToConstant_const_f);
  Racing_2019_B.FixPtSum1_d = (uint16_T)((uint32_T)Racing_2019_B.Output_l +
    Racing_2019_P.FixPtConstant_Value_l);
  if (Racing_2019_B.FixPtSum1_d > Racing_2019_P.CounterLimited_uplimit_a) {
    Racing_2019_B.FixPtSwitch_f = Racing_2019_P.Constant_Value_nv;
  } else {
    Racing_2019_B.FixPtSwitch_f = Racing_2019_B.FixPtSum1_d;
  }

  Racing_2019_B.Delay1ms = Racing_2019_DW.Delay1ms_DSTATE;
  Racing_2019_B.Memory1_kk = Racing_2019_DW.Memory1_PreviousInput_m;
  Racing_2019_B.MovingBaudrate_d = Racing_2019_B.SFunction1_o9_j -
    Racing_2019_B.Memory1_kk;
  if (Racing_2019_B.Delay1ms) {
    Racing_2019_B.Switch_d = Racing_2019_B.SFunction1_o9_j;
  } else {
    Racing_2019_B.Switch_d = Racing_2019_B.Memory1_kk;
  }

  if (Racing_2019_B.Compare_cx) {
    Racing_2019_B.Switch1_gc = (real32_T)Racing_2019_B.MovingBaudrate_d;
  } else {
    Racing_2019_B.Switch1_gc = Racing_2019_B.InverterRIGHTBaudrateRx;
  }

  Racing_2019_B.Output_h = Racing_2019_DW.Output_DSTATE_fj;
  Racing_2019_B.Compare_lf = (Racing_2019_B.Output_h >=
    Racing_2019_P.CompareToConstant_const_i);
  Racing_2019_B.FixPtSum1_i = (uint16_T)((uint32_T)Racing_2019_B.Output_h +
    Racing_2019_P.FixPtConstant_Value_g);
  if (Racing_2019_B.FixPtSum1_i > Racing_2019_P.CounterLimited_uplimit_d) {
    Racing_2019_B.FixPtSwitch_c = Racing_2019_P.Constant_Value_er;
  } else {
    Racing_2019_B.FixPtSwitch_c = Racing_2019_B.FixPtSum1_i;
  }

  Racing_2019_B.Delay1ms_n = Racing_2019_DW.Delay1ms_DSTATE_a;
  Racing_2019_B.Memory1_j = Racing_2019_DW.Memory1_PreviousInput_l;
  Racing_2019_B.MovingBaudrate_o = Racing_2019_B.SFunction1_o10_f -
    Racing_2019_B.Memory1_j;
  if (Racing_2019_B.Delay1ms_n) {
    Racing_2019_B.Switch_j2 = Racing_2019_B.SFunction1_o10_f;
  } else {
    Racing_2019_B.Switch_j2 = Racing_2019_B.Memory1_j;
  }

  if (Racing_2019_B.Compare_lf) {
    Racing_2019_B.Switch1_ir = Racing_2019_B.MovingBaudrate_o;
  } else {
    Racing_2019_B.Switch1_ir = Racing_2019_B.InverterLEFTBaudrateTx_b;
  }

  Racing_2019_B.AccuBaudrateRx = Racing_2019_DW.AccuBaudrateRx_PreviousInput;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32
      (Baudrate_Rx_Inverter_LEFT_Index_UsbFlRec, (Float32)
       Racing_2019_B.AccuBaudrateRx);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.AccuBaudrateTx = Racing_2019_DW.AccuBaudrateTx_PreviousInput;
  Racing_2019_B.AccuCANBaudrate = Racing_2019_B.AccuBaudrateRx + (real32_T)
    Racing_2019_B.AccuBaudrateTx;

  {
    UInt32 loop_counter, memory, j;
    for (j=0;j<=9;j++) {
      rtican_type1_tq_error[1][6] = can_tp1_service_read
        (can_type1_service_M2_C1[j]);
      loop_counter = 0;
      while ((rtican_type1_tq_error[1][6] = can_tp1_service_request
              (can_type1_service_M2_C1[j]))== DSMCOM_BUFFER_OVERFLOW) {
        loop_counter++;
        if (loop_counter > MAX_LOOP) {
          memory = rtican_type1_error_level;
          rtican_type1_error_level = 1;
          rtican_type1_tq_err_sig(1, 6);
          rtican_type1_error_level = memory;
          break;
        }
      }

      if (j==CANTP1_M2_C1_RXLost) {
        rtican_type1_tq_error[1][6] = can_tp1_service_read
          (can_type1_service_M2_C1[CANTP1_M2_C1_DataLost]);
        loop_counter = 0;
        while ((rtican_type1_tq_error[1][6] = can_tp1_service_request
                (can_type1_service_M2_C1[CANTP1_M2_C1_DataLost]))==
               DSMCOM_BUFFER_OVERFLOW) {
          loop_counter++;
          if (loop_counter > MAX_LOOP) {
            memory = rtican_type1_error_level;
            rtican_type1_error_level = 1;
            rtican_type1_tq_err_sig(1, 6);
            rtican_type1_error_level = memory;
            break;
          }
        }
      }
    }

    Racing_2019_B.SFunction1_o1_az = (UInt32)
      can_type1_service_M2_C1[CANTP1_M2_C1_Status]->data0;
    Racing_2019_B.SFunction1_o2_am = (UInt32)
      can_type1_service_M2_C1[CANTP1_M2_C1_StuffErrors]->data0;
    Racing_2019_B.SFunction1_o3_ab = (UInt32)
      can_type1_service_M2_C1[CANTP1_M2_C1_FormatErrors]->data0;
    Racing_2019_B.SFunction1_o4_c = (UInt32)
      can_type1_service_M2_C1[CANTP1_M2_C1_AckErrors]->data0;
    Racing_2019_B.SFunction1_o5_mp = (UInt32)
      can_type1_service_M2_C1[CANTP1_M2_C1_Bit0Errors]->data0;
    Racing_2019_B.SFunction1_o6_pn = (UInt32)
      can_type1_service_M2_C1[CANTP1_M2_C1_Bit1Errors]->data0;
    Racing_2019_B.SFunction1_o7_d = (UInt32)
      can_type1_service_M2_C1[CANTP1_M2_C1_CRCErrors]->data0;
    Racing_2019_B.SFunction1_o8_e = (UInt32)
      (can_type1_service_M2_C1[CANTP1_M2_C1_RXLost]->data0 +
       can_type1_service_M2_C1[CANTP1_M2_C1_DataLost]->data0);
    Racing_2019_B.SFunction1_o9_e = (UInt32)
      can_type1_service_M2_C1[CANTP1_M2_C1_RXOK]->data0;
    Racing_2019_B.SFunction1_o10_l = (UInt32)
      can_type1_service_M2_C1[CANTP1_M2_C1_TXOK]->data0;
  }

  Racing_2019_B.Compare_ex = (Racing_2019_B.SFunction1_o1_az >=
    Racing_2019_P.CompareToConstant8_const);
  Racing_2019_B.Compare_f2 = (Racing_2019_B.SFunction1_o2_am >
    Racing_2019_P.CompareToConstant7_const);
  Racing_2019_B.Compare_ft = (Racing_2019_B.SFunction1_o3_ab >
    Racing_2019_P.CompareToConstant6_const_c);
  Racing_2019_B.Compare_hp = (Racing_2019_B.SFunction1_o4_c >
    Racing_2019_P.CompareToConstant5_const);
  Racing_2019_B.Compare_ab = (Racing_2019_B.SFunction1_o5_mp >
    Racing_2019_P.CompareToConstant4_const);
  Racing_2019_B.Compare_ork = (Racing_2019_B.SFunction1_o6_pn >
    Racing_2019_P.CompareToConstant3_const_e);
  Racing_2019_B.Compare_k5 = (Racing_2019_B.SFunction1_o7_d >
    Racing_2019_P.CompareToConstant2_const);
  Racing_2019_B.Compare_fo = (Racing_2019_B.SFunction1_o8_e >
    Racing_2019_P.CompareToConstant1_const);
  Racing_2019_B.AccuCANError = (Racing_2019_B.Compare_ex ||
    Racing_2019_B.Compare_f2 || Racing_2019_B.Compare_ft ||
    Racing_2019_B.Compare_hp || Racing_2019_B.Compare_ab ||
    Racing_2019_B.Compare_ork || Racing_2019_B.Compare_k5 ||
    Racing_2019_B.Compare_fo);
  Racing_2019_B.Output_aj = Racing_2019_DW.Output_DSTATE_i;
  Racing_2019_B.Compare_jo = (Racing_2019_B.Output_aj >=
    Racing_2019_P.CompareToConstant_const_o);
  Racing_2019_B.FixPtSum1_h = (uint16_T)((uint32_T)Racing_2019_B.Output_aj +
    Racing_2019_P.FixPtConstant_Value_d);
  if (Racing_2019_B.FixPtSum1_h > Racing_2019_P.CounterLimited_uplimit_b) {
    Racing_2019_B.FixPtSwitch_p = Racing_2019_P.Constant_Value_j2;
  } else {
    Racing_2019_B.FixPtSwitch_p = Racing_2019_B.FixPtSum1_h;
  }

  Racing_2019_B.Delay2ms_g = Racing_2019_DW.Delay2ms_DSTATE_nf[0];
  Racing_2019_B.Memory1_f = Racing_2019_DW.Memory1_PreviousInput_f;
  Racing_2019_B.MovingBaudrate_g = Racing_2019_B.SFunction1_o9_e -
    Racing_2019_B.Memory1_f;
  if (Racing_2019_B.Delay2ms_g) {
    Racing_2019_B.Switch_ah = Racing_2019_B.SFunction1_o9_e;
  } else {
    Racing_2019_B.Switch_ah = Racing_2019_B.Memory1_f;
  }

  if (Racing_2019_B.Compare_jo) {
    Racing_2019_B.Switch1_d = (real32_T)Racing_2019_B.MovingBaudrate_g;
  } else {
    Racing_2019_B.Switch1_d = Racing_2019_B.AccuBaudrateRx;
  }

  Racing_2019_B.Output_d = Racing_2019_DW.Output_DSTATE_ix;
  Racing_2019_B.Compare_pq = (Racing_2019_B.Output_d >=
    Racing_2019_P.CompareToConstant_const_b);
  Racing_2019_B.FixPtSum1_iz = (uint16_T)((uint32_T)Racing_2019_B.Output_d +
    Racing_2019_P.FixPtConstant_Value_gi);
  if (Racing_2019_B.FixPtSum1_iz > Racing_2019_P.CounterLimited_uplimit_c) {
    Racing_2019_B.FixPtSwitch_a = Racing_2019_P.Constant_Value_jy;
  } else {
    Racing_2019_B.FixPtSwitch_a = Racing_2019_B.FixPtSum1_iz;
  }

  Racing_2019_B.Delay2ms_e = Racing_2019_DW.Delay2ms_DSTATE_p[0];
  Racing_2019_B.Memory1_l = Racing_2019_DW.Memory1_PreviousInput_g;
  Racing_2019_B.MovingBaudrate_m = Racing_2019_B.SFunction1_o10_l -
    Racing_2019_B.Memory1_l;
  if (Racing_2019_B.Delay2ms_e) {
    Racing_2019_B.Switch_m = Racing_2019_B.SFunction1_o10_l;
  } else {
    Racing_2019_B.Switch_m = Racing_2019_B.Memory1_l;
  }

  if (Racing_2019_B.Compare_pq) {
    Racing_2019_B.Switch1_c = Racing_2019_B.MovingBaudrate_m;
  } else {
    Racing_2019_B.Switch1_c = Racing_2019_B.AccuBaudrateTx;
  }

  Racing_2019_B.DashAuxBaudrateRx =
    Racing_2019_DW.DashAuxBaudrateRx_PreviousInput;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(Baudrate_Rx_Dash_Aux_Index_UsbFlRec,
      (Float32)Racing_2019_B.DashAuxBaudrateRx);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  {
    UInt32 loop_counter, memory, j;
    for (j=0;j<=9;j++) {
      rtican_type1_tq_error[1][6] = can_tp1_service_read
        (can_type1_service_M2_C2[j]);
      loop_counter = 0;
      while ((rtican_type1_tq_error[1][6] = can_tp1_service_request
              (can_type1_service_M2_C2[j]))== DSMCOM_BUFFER_OVERFLOW) {
        loop_counter++;
        if (loop_counter > MAX_LOOP) {
          memory = rtican_type1_error_level;
          rtican_type1_error_level = 1;
          rtican_type1_tq_err_sig(1, 6);
          rtican_type1_error_level = memory;
          break;
        }
      }

      if (j==CANTP1_M2_C2_RXLost) {
        rtican_type1_tq_error[1][6] = can_tp1_service_read
          (can_type1_service_M2_C2[CANTP1_M2_C2_DataLost]);
        loop_counter = 0;
        while ((rtican_type1_tq_error[1][6] = can_tp1_service_request
                (can_type1_service_M2_C2[CANTP1_M2_C2_DataLost]))==
               DSMCOM_BUFFER_OVERFLOW) {
          loop_counter++;
          if (loop_counter > MAX_LOOP) {
            memory = rtican_type1_error_level;
            rtican_type1_error_level = 1;
            rtican_type1_tq_err_sig(1, 6);
            rtican_type1_error_level = memory;
            break;
          }
        }
      }
    }

    Racing_2019_B.SFunction1_o1_d1 = (UInt32)
      can_type1_service_M2_C2[CANTP1_M2_C2_Status]->data0;
    Racing_2019_B.SFunction1_o2_bb = (UInt32)
      can_type1_service_M2_C2[CANTP1_M2_C2_StuffErrors]->data0;
    Racing_2019_B.SFunction1_o3_bm = (UInt32)
      can_type1_service_M2_C2[CANTP1_M2_C2_FormatErrors]->data0;
    Racing_2019_B.SFunction1_o4_ba = (UInt32)
      can_type1_service_M2_C2[CANTP1_M2_C2_AckErrors]->data0;
    Racing_2019_B.SFunction1_o5_p = (UInt32)
      can_type1_service_M2_C2[CANTP1_M2_C2_Bit0Errors]->data0;
    Racing_2019_B.SFunction1_o6_nv = (UInt32)
      can_type1_service_M2_C2[CANTP1_M2_C2_Bit1Errors]->data0;
    Racing_2019_B.SFunction1_o7_k = (UInt32)
      can_type1_service_M2_C2[CANTP1_M2_C2_CRCErrors]->data0;
    Racing_2019_B.SFunction1_o8_f = (UInt32)
      (can_type1_service_M2_C2[CANTP1_M2_C2_RXLost]->data0 +
       can_type1_service_M2_C2[CANTP1_M2_C2_DataLost]->data0);
    Racing_2019_B.SFunction1_o9_i = (UInt32)
      can_type1_service_M2_C2[CANTP1_M2_C2_RXOK]->data0;
    Racing_2019_B.SFunction1_o10_m = (UInt32)
      can_type1_service_M2_C2[CANTP1_M2_C2_TXOK]->data0;
  }

  Racing_2019_B.Compare_pe = (Racing_2019_B.SFunction1_o8_f >
    Racing_2019_P.CompareToConstant25_const);
  Racing_2019_B.Compare_j4 = (Racing_2019_B.SFunction1_o7_k >
    Racing_2019_P.CompareToConstant26_const);
  Racing_2019_B.Compare_l5 = (Racing_2019_B.SFunction1_o6_nv >
    Racing_2019_P.CompareToConstant27_const);
  Racing_2019_B.Compare_oo = (Racing_2019_B.SFunction1_o5_p >
    Racing_2019_P.CompareToConstant28_const);
  Racing_2019_B.Compare_hs = (Racing_2019_B.SFunction1_o4_ba >
    Racing_2019_P.CompareToConstant29_const);
  Racing_2019_B.Compare_id = (Racing_2019_B.SFunction1_o3_bm >
    Racing_2019_P.CompareToConstant30_const);
  Racing_2019_B.Compare_fth = (Racing_2019_B.SFunction1_o2_bb >
    Racing_2019_P.CompareToConstant31_const);
  Racing_2019_B.Compare_ih = (Racing_2019_B.SFunction1_o1_d1 >=
    Racing_2019_P.CompareToConstant32_const);
  Racing_2019_B.DashAuxBaudrateTx =
    Racing_2019_DW.DashAuxBaudrateTx_PreviousInput;
  Racing_2019_B.DashAuxCANBaudrate = Racing_2019_B.DashAuxBaudrateRx + (real32_T)
    Racing_2019_B.DashAuxBaudrateTx;
  Racing_2019_B.DashAuxCANError = (Racing_2019_B.Compare_ih ||
    Racing_2019_B.Compare_fth || Racing_2019_B.Compare_id ||
    Racing_2019_B.Compare_hs || Racing_2019_B.Compare_oo ||
    Racing_2019_B.Compare_l5 || Racing_2019_B.Compare_j4 ||
    Racing_2019_B.Compare_pe);
  Racing_2019_B.Output_p = Racing_2019_DW.Output_DSTATE_e;
  Racing_2019_B.Compare_bu = (Racing_2019_B.Output_p >=
    Racing_2019_P.CompareToConstant_const_g);
  Racing_2019_B.FixPtSum1_j = (uint16_T)((uint32_T)Racing_2019_B.Output_p +
    Racing_2019_P.FixPtConstant_Value_f);
  if (Racing_2019_B.FixPtSum1_j > Racing_2019_P.CounterLimited_uplimit_e) {
    Racing_2019_B.FixPtSwitch_i = Racing_2019_P.Constant_Value_mo;
  } else {
    Racing_2019_B.FixPtSwitch_i = Racing_2019_B.FixPtSum1_j;
  }

  Racing_2019_B.Delay2ms_l = Racing_2019_DW.Delay2ms_DSTATE_a[0];
  Racing_2019_B.Memory1_d = Racing_2019_DW.Memory1_PreviousInput_n3;
  Racing_2019_B.MovingBaudrate_dl = Racing_2019_B.SFunction1_o9_i -
    Racing_2019_B.Memory1_d;
  if (Racing_2019_B.Delay2ms_l) {
    Racing_2019_B.Switch_e = Racing_2019_B.SFunction1_o9_i;
  } else {
    Racing_2019_B.Switch_e = Racing_2019_B.Memory1_d;
  }

  if (Racing_2019_B.Compare_bu) {
    Racing_2019_B.Switch1_b = (real32_T)Racing_2019_B.MovingBaudrate_dl;
  } else {
    Racing_2019_B.Switch1_b = Racing_2019_B.DashAuxBaudrateRx;
  }

  Racing_2019_B.Output_e = Racing_2019_DW.Output_DSTATE_cy;
  Racing_2019_B.Compare_kc = (Racing_2019_B.Output_e >=
    Racing_2019_P.CompareToConstant_const_fk);
  Racing_2019_B.FixPtSum1_n = (uint16_T)((uint32_T)Racing_2019_B.Output_e +
    Racing_2019_P.FixPtConstant_Value_gu);
  if (Racing_2019_B.FixPtSum1_n > Racing_2019_P.CounterLimited_uplimit_g) {
    Racing_2019_B.FixPtSwitch_l = Racing_2019_P.Constant_Value_de;
  } else {
    Racing_2019_B.FixPtSwitch_l = Racing_2019_B.FixPtSum1_n;
  }

  Racing_2019_B.Delay2ms_p = Racing_2019_DW.Delay2ms_DSTATE_nq[0];
  Racing_2019_B.Memory1_e = Racing_2019_DW.Memory1_PreviousInput_lx;
  Racing_2019_B.MovingBaudrate_oi = Racing_2019_B.SFunction1_o10_m -
    Racing_2019_B.Memory1_e;
  if (Racing_2019_B.Delay2ms_p) {
    Racing_2019_B.Switch_o = Racing_2019_B.SFunction1_o10_m;
  } else {
    Racing_2019_B.Switch_o = Racing_2019_B.Memory1_e;
  }

  if (Racing_2019_B.Compare_kc) {
    Racing_2019_B.Switch1_j = Racing_2019_B.MovingBaudrate_oi;
  } else {
    Racing_2019_B.Switch1_j = Racing_2019_B.DashAuxBaudrateTx;
  }

  Racing_2019_B.Compare_dm = (Racing_2019_B.DataTypeConversion5_g >=
    Racing_2019_P.CompareToConstant10_const_g);
  Racing_2019_B.Compare_er = (Racing_2019_B.DataTypeConversion5_g <=
    Racing_2019_P.CompareToConstant11_const_h);
  Racing_2019_B.Compare_e4 = (Racing_2019_B.Switch_e1 <=
    Racing_2019_P.CompareToConstant12_const_c);
  Racing_2019_B.Compare_pv = (Racing_2019_B.DataTypeConversion6_dk >=
    Racing_2019_P.Constant_Value_e1);
  Racing_2019_B.Compare_au = (Racing_2019_B.Switch_e1 >=
    Racing_2019_P.CompareToConstant9_const_k);
  Racing_2019_B.LogicalOperator5 = (Racing_2019_B.Compare_dm &&
    Racing_2019_B.Compare_er);
  Racing_2019_B.LogicalOperator10_c = !Racing_2019_B.LogicalOperator5;
  Racing_2019_B.LogicalOperator11_p = !(Racing_2019_P.DRS_Enable != 0.0);
  Racing_2019_B.LogicalOperator6 = (Racing_2019_B.Compare_au &&
    Racing_2019_B.LogicalOperator5);
  Racing_2019_B.LogicalOperator7 = (Racing_2019_B.LogicalOperator6 ||
    (Racing_2019_P.DRS_Enable != 0.0));
  Racing_2019_B.LogicalOperator9 = (Racing_2019_B.LogicalOperator10_c ||
    Racing_2019_B.Compare_e4 || Racing_2019_B.Compare_pv);
  Racing_2019_B.LogicalOperator8 = (Racing_2019_B.LogicalOperator9 ||
    Racing_2019_B.LogicalOperator11_p);
  Racing_2019_B.Memory_ew = Racing_2019_DW.Memory_PreviousInput_er;
  zcEvent = Racing_2019_B.LogicalOperator7;
  i = zcEvent;
  zcEvent = Racing_2019_B.LogicalOperator8;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  zcEvent = Racing_2019_B.Memory_ew;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  Racing_2019_B.Logic_m4[0U] = Racing_2019_P.Logic_table_bi[(uint32_T)i];
  Racing_2019_B.Logic_m4[1U] = Racing_2019_P.Logic_table_bi[i + 8U];
  if (Racing_2019_B.Logic_m4[0]) {
    Racing_2019_B.Switch5 = Racing_2019_P.DRS_PWM_ON;
  } else {
    Racing_2019_B.Switch5 = Racing_2019_P.DRS_PWM_OFF;
  }

  IcontL = Racing_2019_B.Switch5;
  u1_1 = Racing_2019_P.Saturation2_LowerSat;
  RPM_maxL = Racing_2019_P.Saturation2_UpperSat;
  if (IcontL > RPM_maxL) {
    Racing_2019_B.Saturation2 = RPM_maxL;
  } else if (IcontL < u1_1) {
    Racing_2019_B.Saturation2 = u1_1;
  } else {
    Racing_2019_B.Saturation2 = IcontL;
  }

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(APPS1_Raw_Index_UsbFlRec, (Int32)
      Racing_2019_B.SFunction1_o1_f0);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(APPS2_Raw_Index_UsbFlRec, (Int32)
      Racing_2019_B.SFunction1_o2_o2);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion4_c = Racing_2019_B.Switch_e1;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(APPS_Value_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion4_c);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Brake_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion6_dk);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Brake_Voltage = (uint32_T)Racing_2019_P.Brake_Voltage_Gain *
    Racing_2019_B.SFunction1_o1_gy;
  Racing_2019_B.DataTypeConversion_l = (real32_T)Racing_2019_B.Brake_Voltage *
    2.98023224E-8F;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(Brake_Voltage_Index_UsbFlRec, (Float32)
      Racing_2019_B.DataTypeConversion_l);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Brake_Voltage1 = (uint32_T)Racing_2019_P.Brake_Voltage1_Gain *
    Racing_2019_B.SFunction1_o2_b1;
  Racing_2019_B.DataTypeConversion11 = (real32_T)Racing_2019_B.Brake_Voltage1 *
    2.98023224E-8F;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(DCDC_5V_APPS_Index_UsbFlRec, (Float32)
      Racing_2019_B.DataTypeConversion11);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DASH_CAN_198_Counter =
    Racing_2019_DW.DASH_CAN_198_Counter_PreviousIn;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(DASH_CAN_198_Counter_Index_UsbFlRec,
      (Float32)Racing_2019_B.DASH_CAN_198_Counter);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion10 = Racing_2019_B.SFunction1_o3_a4;
  Racing_2019_B.RPM_FR = 0.0333333351F / (Racing_2019_B.DataTypeConversion10 *
    1.0e-6F) * 60.0F;
  tmp_0 = (real32_T)floor(Racing_2019_B.RPM_FR);
  if (rtIsNaNF(tmp_0) || rtIsInfF(tmp_0)) {
    tmp_0 = 0.0F;
  } else {
    tmp_0 = (real32_T)fmod(tmp_0, 65536.0F);
  }

  Racing_2019_B.DataTypeConversion9_cx = (uint16_T)(tmp_0 < 0.0F ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-tmp_0 : (int32_T)(uint16_T)tmp_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(RPM_FR_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion9_cx);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion2_p4 = (Racing_2019_B.SFunction1_o4 != 0.0);
  Racing_2019_B.Memory_ky = Racing_2019_DW.Memory_PreviousInput_fh;
  switch ((int32_T)Racing_2019_P.EdgeDetector_model_o) {
   case 1:
    Racing_2019_B.MultiportSwitch_c4[0] = Racing_2019_P.posedge_Value_cxl[0];
    Racing_2019_B.MultiportSwitch_c4[1] = Racing_2019_P.posedge_Value_cxl[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_c4[0] = Racing_2019_P.negedge_Value_l[0];
    Racing_2019_B.MultiportSwitch_c4[1] = Racing_2019_P.negedge_Value_l[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_c4[0] = Racing_2019_P.eitheredge_Value_ix[0];
    Racing_2019_B.MultiportSwitch_c4[1] = Racing_2019_P.eitheredge_Value_ix[1];
    break;
  }

  if (Racing_2019_B.MultiportSwitch_c4[0] > 0.0) {
    if (!Racing_2019_DW.POSITIVEEdge_MODE) {
      Racing_2019_DW.POSITIVEEdge_MODE = true;
    }
  } else {
    if (Racing_2019_DW.POSITIVEEdge_MODE) {
      Racing_2019_DW.POSITIVEEdge_MODE = false;
    }
  }

  if (Racing_2019_DW.POSITIVEEdge_MODE) {
    Racing_2019_B.RelationalOperator1 = ((int32_T)Racing_2019_B.Memory_ky <
      (int32_T)Racing_2019_B.DataTypeConversion2_p4);
  }

  if (Racing_2019_B.MultiportSwitch_c4[1] > 0.0) {
    if (!Racing_2019_DW.NEGATIVEEdge_MODE) {
      Racing_2019_DW.NEGATIVEEdge_MODE = true;
    }
  } else {
    if (Racing_2019_DW.NEGATIVEEdge_MODE) {
      Racing_2019_DW.NEGATIVEEdge_MODE = false;
    }
  }

  if (Racing_2019_DW.NEGATIVEEdge_MODE) {
    Racing_2019_B.RelationalOperator1_j = ((int32_T)Racing_2019_B.Memory_ky >
      (int32_T)Racing_2019_B.DataTypeConversion2_p4);
  }

  Racing_2019_B.LogicalOperator1_bk = (Racing_2019_B.RelationalOperator1 ||
    Racing_2019_B.RelationalOperator1_j);
  Racing_2019_B.DataTypeConversion63_f = Racing_2019_B.LogicalOperator1_bk;
  Racing_2019_B.DASH_CAN_101_Counter =
    Racing_2019_DW.DASH_CAN_101_Counter_PreviousIn;
  Racing_2019_B.Add1_l = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion63_f + Racing_2019_B.DASH_CAN_101_Counter);
  Racing_2019_B.DataTypeConversion2_k2 = (Racing_2019_B.SFunction1_o3_a != 0.0);
  Racing_2019_B.UnitDelay_ca = Racing_2019_DW.UnitDelay_DSTATE_di;
  switch ((int32_T)Racing_2019_P.EdgeDetector1_model_f) {
   case 1:
    Racing_2019_B.MultiportSwitch_n[0] = Racing_2019_P.posedge_Value_gx[0];
    Racing_2019_B.MultiportSwitch_n[1] = Racing_2019_P.posedge_Value_gx[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_n[0] = Racing_2019_P.negedge_Value_mv[0];
    Racing_2019_B.MultiportSwitch_n[1] = Racing_2019_P.negedge_Value_mv[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_n[0] = Racing_2019_P.eitheredge_Value_hp[0];
    Racing_2019_B.MultiportSwitch_n[1] = Racing_2019_P.eitheredge_Value_hp[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_n[0],
    Racing_2019_B.DataTypeConversion2_k2, Racing_2019_B.UnitDelay_ca,
    &Racing_2019_B.POSITIVEEdge_kh);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_n[1],
    Racing_2019_B.DataTypeConversion2_k2, Racing_2019_B.UnitDelay_ca,
    &Racing_2019_B.NEGATIVEEdge_ap);
  Racing_2019_B.LogicalOperator1_f1 =
    (Racing_2019_B.POSITIVEEdge_kh.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_ap.RelationalOperator1);
  Racing_2019_B.DataTypeConversion1_j = Racing_2019_B.LogicalOperator1_f1;
  Racing_2019_B.Add2 = (real32_T)Racing_2019_B.DataTypeConversion1_j +
    Racing_2019_B.DASH_CAN_198_Counter;
  if ((rt_ZCFcn(ANY_ZERO_CROSSING,&Racing_2019_PrevZCX.DASH_CAN_101_Reset_ZCE,
                (Racing_2019_B.SFunction1_o4)) != NO_ZCEVENT) ||
      (Racing_2019_B.SFunction1_o4 != 0.0)) {
    for (i = 0; i < 2000; i++) {
      Racing_2019_DW.DASH_CAN_101_DSTATE[i] =
        Racing_2019_P.DASH_CAN_101_InitialCondition;
    }
  }

  Racing_2019_B.DASH_CAN_101 = Racing_2019_DW.DASH_CAN_101_DSTATE[0];
  if (Racing_2019_M->Timing.RateInteraction.TID1_3 == 1) {
    Racing_2019_B.CAN1011kHzto10Hz = Racing_2019_B.DASH_CAN_101;
  }

  if ((rt_ZCFcn(ANY_ZERO_CROSSING,&Racing_2019_PrevZCX.DASH_CAN_198_Reset_ZCE,
                (Racing_2019_B.SFunction1_o3_a)) != NO_ZCEVENT) ||
      (Racing_2019_B.SFunction1_o3_a != 0.0)) {
    for (i = 0; i < 2000; i++) {
      Racing_2019_DW.DASH_CAN_198_DSTATE[i] =
        Racing_2019_P.DASH_CAN_198_InitialCondition;
    }
  }

  Racing_2019_B.DASH_CAN_198 = Racing_2019_DW.DASH_CAN_198_DSTATE[0];
  if (Racing_2019_M->Timing.RateInteraction.TID1_3 == 1) {
    Racing_2019_B.CAN1981kHzto10Hz = Racing_2019_B.DASH_CAN_198;
  }

  Racing_2019_B.Clock = Racing_2019_M->Timing.t[0];
  zcEvent = (Racing_2019_B.LogicalOperator1_bk &&
             (Racing_2019_PrevZCX.TriggeredSubsystem_Trig_ZCE != POS_ZCSIG));
  if (zcEvent) {
    Racing_2019_B.In1 = Racing_2019_B.Clock;
  }

  Racing_2019_PrevZCX.TriggeredSubsystem_Trig_ZCE =
    Racing_2019_B.LogicalOperator1_bk;
  Racing_2019_B.Sum = Racing_2019_B.In1 + Racing_2019_P.Constant_Value_a;
  Racing_2019_B.RelationalOperator_l = (Racing_2019_B.Sum > Racing_2019_B.Clock);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Steering_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion5_g);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion13 = 0.0F;
  Racing_2019_B.Dash_Core_Temp = (3.3F * Racing_2019_B.DataTypeConversion13 /
    4096.0F - 0.76F) * 1000.0F / 2.5F + 25.0F;
  tmp_0 = (real32_T)floor(Racing_2019_B.Dash_Core_Temp);
  if (rtIsNaNF(tmp_0) || rtIsInfF(tmp_0)) {
    tmp_0 = 0.0F;
  } else {
    tmp_0 = (real32_T)fmod(tmp_0, 65536.0F);
  }

  Racing_2019_B.DataTypeConversion7_an = (uint16_T)(tmp_0 < 0.0F ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-tmp_0 : (int32_T)(uint16_T)tmp_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Core_Thermistor_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion7_an);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  {
    adc_tp4_single_new_read(ADC_TP4_1_MODULE_ADDR,
      ADC_TP4_CH7,
      (dsfloat *)&Racing_2019_B.SFunction1_m);
  }

  Racing_2019_B.TSMSVoltage2Gain = Racing_2019_P.TSMSVoltage2Gain_Gain *
    Racing_2019_B.SFunction1_m;
  if (Racing_2019_M->Timing.RateInteraction.TID1_3 == 1) {
    Racing_2019_B.RateTransition2_j = Racing_2019_B.TSMSVoltage2Gain;
  }

  {
    adc_tp4_single_new_read(ADC_TP4_1_MODULE_ADDR,
      ADC_TP4_CH3,
      (dsfloat *)&Racing_2019_B.SFunction1_e);
  }

  Racing_2019_B.TSMSVoltage1Gain = Racing_2019_P.TSMSVoltage1Gain_Gain *
    Racing_2019_B.SFunction1_e;
  if (Racing_2019_M->Timing.RateInteraction.TID1_3 == 1) {
    Racing_2019_B.RateTransition1_b = Racing_2019_B.TSMSVoltage1Gain;
    Racing_2019_B.to10Hz2 = Racing_2019_B.ResettableDelay50ms_k;
  }

  Racing_2019_B.Gain4 = Racing_2019_P.Gain4_Gain *
    Racing_2019_B.VDC_Transfer_Function;
  u1_1 = floor(Racing_2019_B.Gain4);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 65536.0);
  }

  Racing_2019_B.DataTypeConversion2_nc = (int16_T)(u1_1 < 0.0 ? (int32_T)
    (int16_T)-(int16_T)(uint16_T)-u1_1 : (int32_T)(int16_T)(uint16_T)u1_1);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(VDC_Datalogger_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion2_nc);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.MemoryLEMVDC = Racing_2019_DW.MemoryLEMVDC_PreviousInput;
  Racing_2019_B.Add_h = Racing_2019_B.MemoryLEMVDC + Racing_2019_B.LEMVDCGain;
  Racing_2019_B.Output_lf = Racing_2019_DW.Output_DSTATE_g;
  Racing_2019_B.AverageOffsetLEMVDC = Racing_2019_B.MemoryLEMVDC / (real_T)
    Racing_2019_B.Output_lf;
  Racing_2019_B.Compare_gx = (Racing_2019_B.Output_lf >=
    Racing_2019_P.CompareToConstant_const_a);
  Racing_2019_B.Compare_fy = (Racing_2019_B.Output_lf <=
    Racing_2019_P.CompareToConstant1_const_k);
  Racing_2019_B.FixPtSum1_jw = (uint16_T)((uint16_T)((uint32_T)
    Racing_2019_B.Output_lf + Racing_2019_P.FixPtConstant_Value_lr) & 16383);
  if (Racing_2019_B.FixPtSum1_jw > Racing_2019_P.WrapToZero_Threshold) {
    Racing_2019_B.FixPtSwitch_e = Racing_2019_P.Constant_Value_fs;
  } else {
    Racing_2019_B.FixPtSwitch_e = Racing_2019_B.FixPtSum1_jw;
  }

  Racing_2019_B.Delay = Racing_2019_DW.Delay_DSTATE;
  Racing_2019_B.LogicalOperator_b = ((Racing_2019_P.Constant_Value_p != 0.0) ||
    (Racing_2019_P.Calibrate != 0.0));
  Racing_2019_B.LogicalOperator1_l = !Racing_2019_B.Compare_gx;
  Racing_2019_B.LogicalOperator2_e = (Racing_2019_B.Compare_gx &&
    Racing_2019_B.Compare_fy);
  Racing_2019_B.Memory_h = Racing_2019_DW.Memory_PreviousInput_bp;
  zcEvent = Racing_2019_B.LogicalOperator2_e;
  i = zcEvent;
  zcEvent = Racing_2019_B.LogicalOperator_b;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  zcEvent = Racing_2019_B.Memory_h;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  Racing_2019_B.Logic_km[0U] = Racing_2019_P.Logic_table_hw[(uint32_T)i];
  Racing_2019_B.Logic_km[1U] = Racing_2019_P.Logic_table_hw[i + 8U];
  if (Racing_2019_B.Logic_km[0]) {
    Racing_2019_B.Switch_l2 = Racing_2019_B.DynamicOffsetLEMVDC;
  } else {
    Racing_2019_B.Switch_l2 = Racing_2019_B.AverageOffsetLEMVDC;
  }

  if (Racing_2019_B.Delay) {
    Racing_2019_B.Switch1_n = Racing_2019_B.Add_h;
  } else {
    Racing_2019_B.Switch1_n = Racing_2019_P.Constant2_Value_o;
  }

  Racing_2019_B.Gain5 = Racing_2019_P.Gain5_Gain *
    Racing_2019_B.IDC_Transfer_Function;
  u1_1 = floor(Racing_2019_B.Gain5);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 65536.0);
  }

  Racing_2019_B.DataTypeConversion3_n = (int16_T)(u1_1 < 0.0 ? (int32_T)(int16_T)
    -(int16_T)(uint16_T)-u1_1 : (int32_T)(int16_T)(uint16_T)u1_1);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(IDC_Datalogger_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion3_n);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.MemoryLEMIDC = Racing_2019_DW.MemoryLEMIDC_PreviousInput;
  Racing_2019_B.Add_o = Racing_2019_B.MemoryLEMIDC + Racing_2019_B.LEMIDCGain;
  Racing_2019_B.Output_a1 = Racing_2019_DW.Output_DSTATE_k;
  Racing_2019_B.AverageOffsetLEMIDC = Racing_2019_B.MemoryLEMIDC / (real_T)
    Racing_2019_B.Output_a1;
  Racing_2019_B.Compare_cs = (Racing_2019_B.Output_a1 >=
    Racing_2019_P.CompareToConstant_const_gm);
  Racing_2019_B.Compare_cv = (Racing_2019_B.Output_a1 <=
    Racing_2019_P.CompareToConstant1_const_b);
  Racing_2019_B.FixPtSum1_fy = (uint16_T)((uint16_T)((uint32_T)
    Racing_2019_B.Output_a1 + Racing_2019_P.FixPtConstant_Value_p) & 16383);
  if (Racing_2019_B.FixPtSum1_fy > Racing_2019_P.WrapToZero_Threshold_k) {
    Racing_2019_B.FixPtSwitch_j = Racing_2019_P.Constant_Value_bd;
  } else {
    Racing_2019_B.FixPtSwitch_j = Racing_2019_B.FixPtSum1_fy;
  }

  Racing_2019_B.Delay_c = Racing_2019_DW.Delay_DSTATE_k;
  Racing_2019_B.LogicalOperator_j = ((Racing_2019_P.Constant_Value_b != 0.0) ||
    (Racing_2019_P.Calibrate != 0.0));
  Racing_2019_B.LogicalOperator1_ei = !Racing_2019_B.Compare_cs;
  Racing_2019_B.LogicalOperator2_mj = (Racing_2019_B.Compare_cs &&
    Racing_2019_B.Compare_cv);
  Racing_2019_B.Memory_ba = Racing_2019_DW.Memory_PreviousInput_kz;
  zcEvent = Racing_2019_B.LogicalOperator2_mj;
  i = zcEvent;
  zcEvent = Racing_2019_B.LogicalOperator_j;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  zcEvent = Racing_2019_B.Memory_ba;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  Racing_2019_B.Logic_kb[0U] = Racing_2019_P.Logic_table_a[(uint32_T)i];
  Racing_2019_B.Logic_kb[1U] = Racing_2019_P.Logic_table_a[i + 8U];
  if (Racing_2019_B.Logic_kb[0]) {
    Racing_2019_B.Switch_i = Racing_2019_B.DynamicOffsetLEMIDC;
  } else {
    Racing_2019_B.Switch_i = Racing_2019_B.AverageOffsetLEMIDC;
  }

  if (Racing_2019_B.Delay_c) {
    Racing_2019_B.Switch1_g = Racing_2019_B.Add_o;
  } else {
    Racing_2019_B.Switch1_g = Racing_2019_P.Constant2_Value_e;
  }

  {
    adc_tp4_single_new_read(ADC_TP4_1_MODULE_ADDR,
      ADC_TP4_CH1,
      (dsfloat *)&Racing_2019_B.SFunction1_c);
  }

  Racing_2019_B.LEMLeftGain = Racing_2019_P.LEMLeftGain_Gain *
    Racing_2019_B.SFunction1_c;
  Racing_2019_B.DynamicOffsetLEMLeft =
    Racing_2019_DW.DynamicOffsetLEMLeft_PreviousIn;
  Racing_2019_B.RemoveIACLeftOffset = Racing_2019_B.LEMLeftGain -
    Racing_2019_B.DynamicOffsetLEMLeft;
  Racing_2019_B.IAC_Left_Transfer_Function =
    Racing_2019_P.IAC_Left_Transfer_Function_Gain *
    Racing_2019_B.RemoveIACLeftOffset;
  u1_1 = floor(Racing_2019_B.IAC_Left_Transfer_Function);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 65536.0);
  }

  Racing_2019_B.DataTypeConversion_o = (int16_T)(u1_1 < 0.0 ? (int32_T)(int16_T)
    -(int16_T)(uint16_T)-u1_1 : (int32_T)(int16_T)(uint16_T)u1_1);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(IAC_Left_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion_o);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.MemoryLEMIACLeft = Racing_2019_DW.MemoryLEMIACLeft_PreviousInput;
  Racing_2019_B.Add_b5 = Racing_2019_B.MemoryLEMIACLeft +
    Racing_2019_B.LEMLeftGain;
  Racing_2019_B.Output_p4 = Racing_2019_DW.Output_DSTATE_a;
  Racing_2019_B.AverageOffsetLEMLeft = Racing_2019_B.MemoryLEMIACLeft / (real_T)
    Racing_2019_B.Output_p4;
  Racing_2019_B.Compare_aj = (Racing_2019_B.Output_p4 >=
    Racing_2019_P.CompareToConstant_const_j);
  Racing_2019_B.Compare_g4 = (Racing_2019_B.Output_p4 <=
    Racing_2019_P.CompareToConstant1_const_o);
  Racing_2019_B.FixPtSum1_c = (uint16_T)((uint16_T)((uint32_T)
    Racing_2019_B.Output_p4 + Racing_2019_P.FixPtConstant_Value_ln) & 16383);
  if (Racing_2019_B.FixPtSum1_c > Racing_2019_P.WrapToZero_Threshold_j) {
    Racing_2019_B.FixPtSwitch_lr = Racing_2019_P.Constant_Value_l;
  } else {
    Racing_2019_B.FixPtSwitch_lr = Racing_2019_B.FixPtSum1_c;
  }

  Racing_2019_B.Delay_h = Racing_2019_DW.Delay_DSTATE_e;
  Racing_2019_B.LogicalOperator_db = ((Racing_2019_P.Constant_Value_ab != 0.0) ||
    (Racing_2019_P.Calibrate != 0.0));
  Racing_2019_B.LogicalOperator1_lv = !Racing_2019_B.Compare_aj;
  Racing_2019_B.LogicalOperator2_c = (Racing_2019_B.Compare_aj &&
    Racing_2019_B.Compare_g4);
  Racing_2019_B.Memory_m = Racing_2019_DW.Memory_PreviousInput_mu;
  zcEvent = Racing_2019_B.LogicalOperator2_c;
  i = zcEvent;
  zcEvent = Racing_2019_B.LogicalOperator_db;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  zcEvent = Racing_2019_B.Memory_m;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  Racing_2019_B.Logic_a[0U] = Racing_2019_P.Logic_table_j[(uint32_T)i];
  Racing_2019_B.Logic_a[1U] = Racing_2019_P.Logic_table_j[i + 8U];
  if (Racing_2019_B.Logic_a[0]) {
    Racing_2019_B.Switch_b = Racing_2019_B.DynamicOffsetLEMLeft;
  } else {
    Racing_2019_B.Switch_b = Racing_2019_B.AverageOffsetLEMLeft;
  }

  if (Racing_2019_B.Delay_h) {
    Racing_2019_B.Switch1_nc = Racing_2019_B.Add_b5;
  } else {
    Racing_2019_B.Switch1_nc = Racing_2019_P.Constant2_Value_n;
  }

  {
    adc_tp4_single_new_read(ADC_TP4_1_MODULE_ADDR,
      ADC_TP4_CH2,
      (dsfloat *)&Racing_2019_B.SFunction1_o);
  }

  Racing_2019_B.LEMRightGain = Racing_2019_P.LEMRightGain_Gain *
    Racing_2019_B.SFunction1_o;
  Racing_2019_B.DynamicOffsetLEMRight =
    Racing_2019_DW.DynamicOffsetLEMRight_PreviousI;
  Racing_2019_B.RemoveIACRightOffset = Racing_2019_B.LEMRightGain -
    Racing_2019_B.DynamicOffsetLEMRight;
  Racing_2019_B.IAC_Right_Transfer_Function =
    Racing_2019_P.IAC_Right_Transfer_Function_Gai *
    Racing_2019_B.RemoveIACRightOffset;
  u1_1 = floor(Racing_2019_B.IAC_Right_Transfer_Function);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 65536.0);
  }

  Racing_2019_B.DataTypeConversion1 = (int16_T)(u1_1 < 0.0 ? (int32_T)(int16_T)
    -(int16_T)(uint16_T)-u1_1 : (int32_T)(int16_T)(uint16_T)u1_1);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(IAC_Right_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion1);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.MemoryLEMIACRight =
    Racing_2019_DW.MemoryLEMIACRight_PreviousInput;
  Racing_2019_B.Add_i = Racing_2019_B.MemoryLEMIACRight +
    Racing_2019_B.LEMRightGain;
  Racing_2019_B.Output_i = Racing_2019_DW.Output_DSTATE_j;
  Racing_2019_B.AverageOffsetLEMRight = Racing_2019_B.MemoryLEMIACRight /
    (real_T)Racing_2019_B.Output_i;
  Racing_2019_B.Compare_oc = (Racing_2019_B.Output_i >=
    Racing_2019_P.CompareToConstant_const_ls);
  Racing_2019_B.Compare_bm = (Racing_2019_B.Output_i <=
    Racing_2019_P.CompareToConstant1_const_j);
  Racing_2019_B.FixPtSum1_dc = (uint16_T)((uint16_T)((uint32_T)
    Racing_2019_B.Output_i + Racing_2019_P.FixPtConstant_Value_pk) & 16383);
  if (Racing_2019_B.FixPtSum1_dc > Racing_2019_P.WrapToZero_Threshold_f) {
    Racing_2019_B.FixPtSwitch_lp = Racing_2019_P.Constant_Value_c5;
  } else {
    Racing_2019_B.FixPtSwitch_lp = Racing_2019_B.FixPtSum1_dc;
  }

  Racing_2019_B.Delay_p = Racing_2019_DW.Delay_DSTATE_h;
  Racing_2019_B.LogicalOperator_ir = ((Racing_2019_P.Constant_Value_m != 0.0) ||
    (Racing_2019_P.Calibrate != 0.0));
  Racing_2019_B.LogicalOperator1_hn = !Racing_2019_B.Compare_oc;
  Racing_2019_B.LogicalOperator2_cx = (Racing_2019_B.Compare_oc &&
    Racing_2019_B.Compare_bm);
  Racing_2019_B.Memory_j = Racing_2019_DW.Memory_PreviousInput_df;
  zcEvent = Racing_2019_B.LogicalOperator2_cx;
  i = zcEvent;
  zcEvent = Racing_2019_B.LogicalOperator_ir;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  zcEvent = Racing_2019_B.Memory_j;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  Racing_2019_B.Logic_p[0U] = Racing_2019_P.Logic_table_o[(uint32_T)i];
  Racing_2019_B.Logic_p[1U] = Racing_2019_P.Logic_table_o[i + 8U];
  if (Racing_2019_B.Logic_p[0]) {
    Racing_2019_B.Switch_a = Racing_2019_B.DynamicOffsetLEMRight;
  } else {
    Racing_2019_B.Switch_a = Racing_2019_B.AverageOffsetLEMRight;
  }

  if (Racing_2019_B.Delay_p) {
    Racing_2019_B.Switch1_l = Racing_2019_B.Add_i;
  } else {
    Racing_2019_B.Switch1_l = Racing_2019_P.Constant2_Value_f;
  }

  Racing_2019_B.DiscreteTimeIntegrator =
    Racing_2019_DW.DiscreteTimeIntegrator_DSTATE;
  Racing_2019_B.KWh_Consumed = Racing_2019_P.KWh_Consumed_Gain *
    Racing_2019_B.DiscreteTimeIntegrator;
  Racing_2019_B.DiscreteTimeIntegrator1 =
    Racing_2019_DW.DiscreteTimeIntegrator1_DSTATE;
  Racing_2019_B.KWh_Regen = Racing_2019_P.KWh_Regen_Gain *
    Racing_2019_B.DiscreteTimeIntegrator1;
  Racing_2019_B.Kwh = Racing_2019_B.KWh_Consumed - Racing_2019_B.KWh_Regen;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(KWh_Index_UsbFlRec, (Float32)
      Racing_2019_B.Kwh);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(KWh_Consumed_Index_UsbFlRec, (Float32)
      Racing_2019_B.KWh_Consumed);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(KWh_Regen_Index_UsbFlRec, (Float32)
      Racing_2019_B.KWh_Regen);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Kph_Max = Racing_2019_P.Kph_Max_Gain * Racing_2019_B.Switch_n;
  Racing_2019_B.DataTypeConversion2_i = (uint16_T)(Racing_2019_B.Kph_Max >> 20);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Kph_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion2_i);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Kph_Min = Racing_2019_P.Kph_Min_Gain * Racing_2019_B.Switch1_gi;
  Racing_2019_B.DataTypeConversion4_fn = (uint16_T)(Racing_2019_B.Kph_Min >> 20);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Kph_Min_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion4_fn);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.KW = Racing_2019_B.VDC_Transfer_Function *
    Racing_2019_B.IDC_Transfer_Function / Racing_2019_P.Constant4_Value_h;
  Racing_2019_B.DataTypeConversion6_k = (real32_T)Racing_2019_B.KW;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(Kw_Index_UsbFlRec, (Float32)
      Racing_2019_B.DataTypeConversion6_k);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Meters_Max = Racing_2019_DW.Meters_Max_DSTATE;
  Racing_2019_B.RateTransition1_m = Racing_2019_B.Meters_Max;
  Racing_2019_B.DataTypeConversion1_i = (uint16_T)mul_s32_hiSR
    (Racing_2019_B.RateTransition1_m, 274877907, 27U);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Meters_Max_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion1_i);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Meters_Min = Racing_2019_DW.Meters_Min_DSTATE;
  Racing_2019_B.RateTransition2_d = Racing_2019_B.Meters_Min;
  Racing_2019_B.DataTypeConversion3_c = (uint16_T)mul_s32_hiSR
    (Racing_2019_B.RateTransition2_d, 274877907, 27U);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Meters_Min_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion3_c);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DMeters = Racing_2019_B.Meters_Max - Racing_2019_B.Meters_Min;
  Racing_2019_B.Compare_ob = (Racing_2019_B.Switch_n >=
    Racing_2019_P.Moving_const);
  if (Racing_2019_M->Timing.RateInteraction.TID1_2 == 1) {
    Racing_2019_B.to1kHz = Racing_2019_DW.to1kHz_Buffer0;
  }

  Racing_2019_B.OnlyConsumed = !Racing_2019_B.RegenAND;
  Racing_2019_B.LogicalOperator4_du = (Racing_2019_B.Compare_ob &&
    Racing_2019_B.to1kHz && Racing_2019_B.OnlyConsumed);
  if (Racing_2019_B.LogicalOperator4_du) {
    Racing_2019_B.Switch2_h = Racing_2019_B.KW;
  } else {
    Racing_2019_B.Switch2_h = Racing_2019_P.Constant5_Value_o;
  }

  Racing_2019_B.DataTypeConversion_e = (real32_T)Racing_2019_B.Switch2_h;
  if (Racing_2019_B.RegenAND) {
    Racing_2019_B.Switch3_i = Racing_2019_B.KW;
  } else {
    Racing_2019_B.Switch3_i = Racing_2019_P.Constant7_Value_j;
  }

  Racing_2019_B.DataTypeConversion5_e = (real32_T)Racing_2019_B.Switch3_i;
  Racing_2019_B.Gain_n = Racing_2019_P.Gain_Gain_h * Racing_2019_B.Switch_n;
  Racing_2019_B.Gain1_e = Racing_2019_P.Gain1_Gain_d * Racing_2019_B.Switch1_gi;
  Racing_2019_B.FixPtUnitDelay1 = Racing_2019_DW.FixPtUnitDelay1_DSTATE;
  IcontL = Racing_2019_B.KW;
  u1_1 = Racing_2019_B.FixPtUnitDelay1;
  if ((IcontL > u1_1) || rtIsNaN(u1_1)) {
    u1_1 = IcontL;
  }

  Racing_2019_B.MinMax = u1_1;
  if (Racing_2019_P.KW_Max_Reset != 0.0) {
    Racing_2019_B.Reset = Racing_2019_P.KW_MAX_vinit;
  } else {
    Racing_2019_B.Reset = Racing_2019_B.MinMax;
  }

  Racing_2019_B.FixPtUnitDelay1_a = Racing_2019_DW.FixPtUnitDelay1_DSTATE_a;
  IcontL = Racing_2019_B.KW;
  u1_1 = Racing_2019_B.FixPtUnitDelay1_a;
  if ((IcontL < u1_1) || rtIsNaN(u1_1)) {
    u1_1 = IcontL;
  }

  Racing_2019_B.MinMax_b = u1_1;
  if (Racing_2019_P.KW_Max_Regen_Reset != 0.0) {
    Racing_2019_B.Reset_o = Racing_2019_P.KW_MAX_Regen_vinit;
  } else {
    Racing_2019_B.Reset_o = Racing_2019_B.MinMax_b;
  }

  Racing_2019_B.DataTypeConversion7_h = (real32_T)Racing_2019_B.SFunction1_o2_p;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(Accel_X_Index_UsbFlRec, (Float32)
      Racing_2019_B.DataTypeConversion7_h);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion8 = (real32_T)Racing_2019_B.SFunction1_o3_h0;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(Accel_Y_Index_UsbFlRec, (Float32)
      Racing_2019_B.DataTypeConversion8);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion9_m = (real32_T)Racing_2019_B.SFunction1_o4_mo;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(Accel_Z_Index_UsbFlRec, (Float32)
      Racing_2019_B.DataTypeConversion9_m);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion_c = (real32_T)Racing_2019_B.IrmsLEFTRaw.In1;
  Racing_2019_B.IrmsLEFT = Racing_2019_P.IrmsLEFT_Gain *
    Racing_2019_B.DataTypeConversion_c;
  tmp_0 = (real32_T)floor(Racing_2019_B.IrmsLEFT);
  if (rtIsNaNF(tmp_0) || rtIsInfF(tmp_0)) {
    tmp_0 = 0.0F;
  } else {
    tmp_0 = (real32_T)fmod(tmp_0, 65536.0F);
  }

  Racing_2019_B.DataTypeConversion3_l = (int16_T)(tmp_0 < 0.0F ? (int32_T)
    (int16_T)-(int16_T)(uint16_T)-tmp_0 : (int32_T)(int16_T)(uint16_T)tmp_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Irms_LEFT_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion3_l);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion16 = (real32_T)Racing_2019_B.VoutLEFT.In1;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(Vout_LEFT_Index_UsbFlRec, (Float32)
      Racing_2019_B.DataTypeConversion16);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion5_p = (real32_T)
    Racing_2019_B.MotorTempLEFTRaw.In1;
  Racing_2019_B.MotorTempLEFT = 0.01746F * Racing_2019_B.DataTypeConversion5_p -
    171.5F;
  tmp_0 = (real32_T)floor(Racing_2019_B.MotorTempLEFT);
  if (rtIsNaNF(tmp_0) || rtIsInfF(tmp_0)) {
    tmp_0 = 0.0F;
  } else {
    tmp_0 = (real32_T)fmod(tmp_0, 65536.0F);
  }

  Racing_2019_B.DataTypeConversion6_d = (int16_T)(tmp_0 < 0.0F ? (int32_T)
    (int16_T)-(int16_T)(uint16_T)-tmp_0 : (int32_T)(int16_T)(uint16_T)tmp_0);
  if (Racing_2019_M->Timing.RateInteraction.TID1_5 == 1) {
    Racing_2019_B.MotorTempto1Hz = Racing_2019_B.DataTypeConversion6_d;
  }

  Racing_2019_B.DataTypeConversion9_l = (real32_T)
    Racing_2019_B.AirTempLEFTRaw.In1;
  Racing_2019_B.AirTempLEFT = 0.02F * Racing_2019_B.DataTypeConversion9_l -
    216.0F;
  tmp_0 = (real32_T)floor(Racing_2019_B.AirTempLEFT);
  if (rtIsNaNF(tmp_0) || rtIsInfF(tmp_0)) {
    tmp_0 = 0.0F;
  } else {
    tmp_0 = (real32_T)fmod(tmp_0, 65536.0F);
  }

  Racing_2019_B.DataTypeConversion10_k = (int16_T)(tmp_0 < 0.0F ? (int32_T)
    (int16_T)-(int16_T)(uint16_T)-tmp_0 : (int32_T)(int16_T)(uint16_T)tmp_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Inverter_Air_Temp_LEFT_Index_UsbFlRec,
      (Int32)Racing_2019_B.DataTypeConversion10_k);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  u1_1 = floor(Racing_2019_B.ErrorLEFTRaw.In1);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 256.0);
  }

  Racing_2019_B.DataTypeConversion11_b5 = (int8_T)(u1_1 < 0.0 ? (int32_T)(int8_T)
    -(int8_T)(uint8_T)-u1_1 : (int32_T)(int8_T)(uint8_T)u1_1);
  if (Racing_2019_M->Timing.RateInteraction.TID1_3 == 1) {
    Racing_2019_B.RateTransition = Racing_2019_B.DataTypeConversion11_b5;
  }

  u1_1 = floor(Racing_2019_B.BTBLEFTRaw.In1);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 256.0);
  }

  Racing_2019_B.DataTypeConversion12_iy = (int8_T)(u1_1 < 0.0 ? (int32_T)(int8_T)
    -(int8_T)(uint8_T)-u1_1 : (int32_T)(int8_T)(uint8_T)u1_1);
  if (Racing_2019_M->Timing.RateInteraction.TID1_3 == 1) {
    Racing_2019_B.RateTransition1_k = Racing_2019_B.DataTypeConversion12_iy;
  }

  u1_1 = floor(Racing_2019_B.MotorPowerLEFTRaw.In1);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 65536.0);
  }

  Racing_2019_B.DataTypeConversion13_a = (int16_T)(u1_1 < 0.0 ? (int32_T)
    (int16_T)-(int16_T)(uint16_T)-u1_1 : (int32_T)(int16_T)(uint16_T)u1_1);
  if (Racing_2019_M->Timing.RateInteraction.TID1_3 == 1) {
    Racing_2019_B.RateTransition2_k = Racing_2019_B.DataTypeConversion13_a;
  }

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(RPM_LEFT_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion14_n);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion15 = (real32_T)
    Racing_2019_B.CommandedTorqueLEFT.In1;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(Commanded_Torque_Left_Index_UsbFlRec,
      (Float32)Racing_2019_B.DataTypeConversion15);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion2_ca = (Racing_2019_B.SFunction1_o3 != 0.0);
  Racing_2019_B.UnitDelay_iq = Racing_2019_DW.UnitDelay_DSTATE_od;
  switch ((int32_T)Racing_2019_P.EdgeDetector_model_nc) {
   case 1:
    Racing_2019_B.MultiportSwitch_dt[0] = Racing_2019_P.posedge_Value_d[0];
    Racing_2019_B.MultiportSwitch_dt[1] = Racing_2019_P.posedge_Value_d[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_dt[0] = Racing_2019_P.negedge_Value_lu[0];
    Racing_2019_B.MultiportSwitch_dt[1] = Racing_2019_P.negedge_Value_lu[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_dt[0] = Racing_2019_P.eitheredge_Value_gh[0];
    Racing_2019_B.MultiportSwitch_dt[1] = Racing_2019_P.eitheredge_Value_gh[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_dt[0],
    Racing_2019_B.DataTypeConversion2_ca, Racing_2019_B.UnitDelay_iq,
    &Racing_2019_B.POSITIVEEdge_pn);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_dt[1],
    Racing_2019_B.DataTypeConversion2_ca, Racing_2019_B.UnitDelay_iq,
    &Racing_2019_B.NEGATIVEEdge_br);
  Racing_2019_B.LogicalOperator1_c =
    (Racing_2019_B.POSITIVEEdge_pn.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_br.RelationalOperator1);
  Racing_2019_B.DataTypeConversion1_m = Racing_2019_B.LogicalOperator1_c;
  Racing_2019_B.Inverter_LEFT_CAN_Rx_Counter =
    Racing_2019_DW.Inverter_LEFT_CAN_Rx_Counter_Pr;
  Racing_2019_B.Add_a = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion1_m
    + Racing_2019_B.Inverter_LEFT_CAN_Rx_Counter);
  Racing_2019_B.DataTypeConversion_ei = (real32_T)Racing_2019_B.IrmsRIGHTRaw.In1;
  Racing_2019_B.IrmsRIGHT = Racing_2019_P.IrmsRIGHT_Gain *
    Racing_2019_B.DataTypeConversion_ei;
  tmp_0 = (real32_T)floor(Racing_2019_B.IrmsRIGHT);
  if (rtIsNaNF(tmp_0) || rtIsInfF(tmp_0)) {
    tmp_0 = 0.0F;
  } else {
    tmp_0 = (real32_T)fmod(tmp_0, 65536.0F);
  }

  Racing_2019_B.DataTypeConversion3_e = (int16_T)(tmp_0 < 0.0F ? (int32_T)
    (int16_T)-(int16_T)(uint16_T)-tmp_0 : (int32_T)(int16_T)(uint16_T)tmp_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Irms_RIGHT_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion3_e);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion16_a = (real32_T)
    Racing_2019_B.VoutRIGHTRaw.In1;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(Vout_RIGHT_Index_UsbFlRec, (Float32)
      Racing_2019_B.DataTypeConversion16_a);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion5_k = (real32_T)
    Racing_2019_B.MotorTempRIGHTRaw.In1;
  Racing_2019_B.MotorTempRIGHT = 0.01746F * Racing_2019_B.DataTypeConversion5_k
    - 171.5F;
  tmp_0 = (real32_T)floor(Racing_2019_B.MotorTempRIGHT);
  if (rtIsNaNF(tmp_0) || rtIsInfF(tmp_0)) {
    tmp_0 = 0.0F;
  } else {
    tmp_0 = (real32_T)fmod(tmp_0, 65536.0F);
  }

  Racing_2019_B.DataTypeConversion6_kl = (int16_T)(tmp_0 < 0.0F ? (int32_T)
    (int16_T)-(int16_T)(uint16_T)-tmp_0 : (int32_T)(int16_T)(uint16_T)tmp_0);
  if (Racing_2019_M->Timing.RateInteraction.TID1_5 == 1) {
    Racing_2019_B.MotorTempto1Hz_o = Racing_2019_B.DataTypeConversion6_kl;
  }

  Racing_2019_B.DataTypeConversion9_i = (real32_T)
    Racing_2019_B.AirTempRIGHTRaw.In1;
  Racing_2019_B.AirTempRIGHT = 0.02F * Racing_2019_B.DataTypeConversion9_i -
    216.0F;
  tmp_0 = (real32_T)floor(Racing_2019_B.AirTempRIGHT);
  if (rtIsNaNF(tmp_0) || rtIsInfF(tmp_0)) {
    tmp_0 = 0.0F;
  } else {
    tmp_0 = (real32_T)fmod(tmp_0, 65536.0F);
  }

  Racing_2019_B.DataTypeConversion10_l = (int16_T)(tmp_0 < 0.0F ? (int32_T)
    (int16_T)-(int16_T)(uint16_T)-tmp_0 : (int32_T)(int16_T)(uint16_T)tmp_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Inverter_Air_Temp_RIGHT_Index_UsbFlRec,
      (Int32)Racing_2019_B.DataTypeConversion10_l);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  u1_1 = floor(Racing_2019_B.ErrorRIGHTRaw.In1);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 256.0);
  }

  Racing_2019_B.DataTypeConversion11_jp = (int8_T)(u1_1 < 0.0 ? (int32_T)(int8_T)
    -(int8_T)(uint8_T)-u1_1 : (int32_T)(int8_T)(uint8_T)u1_1);
  if (Racing_2019_M->Timing.RateInteraction.TID1_3 == 1) {
    Racing_2019_B.RateTransition_h = Racing_2019_B.DataTypeConversion11_jp;
  }

  u1_1 = floor(Racing_2019_B.BTBRIGHTRaw.In1);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 256.0);
  }

  Racing_2019_B.DataTypeConversion12_dy = (int8_T)(u1_1 < 0.0 ? (int32_T)(int8_T)
    -(int8_T)(uint8_T)-u1_1 : (int32_T)(int8_T)(uint8_T)u1_1);
  if (Racing_2019_M->Timing.RateInteraction.TID1_3 == 1) {
    Racing_2019_B.RateTransition1_f = Racing_2019_B.DataTypeConversion12_dy;
  }

  u1_1 = floor(Racing_2019_B.MotorPowerRIGHTRaw.In1);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 65536.0);
  }

  Racing_2019_B.DataTypeConversion13_a5 = (int16_T)(u1_1 < 0.0 ? (int32_T)
    (int16_T)-(int16_T)(uint16_T)-u1_1 : (int32_T)(int16_T)(uint16_T)u1_1);
  if (Racing_2019_M->Timing.RateInteraction.TID1_3 == 1) {
    Racing_2019_B.RateTransition2_kl = Racing_2019_B.DataTypeConversion13_a5;
  }

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(RPM_RIGHT_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion14);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion15_o = (real32_T)
    Racing_2019_B.CommandTorqueRIGHT.In1;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(Commanded_Torque_Right_Index_UsbFlRec,
      (Float32)Racing_2019_B.DataTypeConversion15_o);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion2_de = (Racing_2019_B.SFunction1_o3_h != 0.0);
  Racing_2019_B.UnitDelay_gg = Racing_2019_DW.UnitDelay_DSTATE_e;
  switch ((int32_T)Racing_2019_P.EdgeDetector_model_i) {
   case 1:
    Racing_2019_B.MultiportSwitch_d0[0] = Racing_2019_P.posedge_Value_o1[0];
    Racing_2019_B.MultiportSwitch_d0[1] = Racing_2019_P.posedge_Value_o1[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_d0[0] = Racing_2019_P.negedge_Value_d[0];
    Racing_2019_B.MultiportSwitch_d0[1] = Racing_2019_P.negedge_Value_d[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_d0[0] = Racing_2019_P.eitheredge_Value_en[0];
    Racing_2019_B.MultiportSwitch_d0[1] = Racing_2019_P.eitheredge_Value_en[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_d0[0],
    Racing_2019_B.DataTypeConversion2_de, Racing_2019_B.UnitDelay_gg,
    &Racing_2019_B.POSITIVEEdge_ex);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_d0[1],
    Racing_2019_B.DataTypeConversion2_de, Racing_2019_B.UnitDelay_gg,
    &Racing_2019_B.NEGATIVEEdge_o3);
  Racing_2019_B.LogicalOperator1_km =
    (Racing_2019_B.POSITIVEEdge_ex.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_o3.RelationalOperator1);
  Racing_2019_B.DataTypeConversion1_cw = Racing_2019_B.LogicalOperator1_km;
  Racing_2019_B.Inverter_RIGHT_CAN_Rx_Counter =
    Racing_2019_DW.Inverter_RIGHT_CAN_Rx_Counter_P;
  Racing_2019_B.Add_pj = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion1_cw +
    Racing_2019_B.Inverter_RIGHT_CAN_Rx_Counter);
  u1_1 = floor(Racing_2019_B.LeftTorqueSwitch);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 65536.0);
  }

  Racing_2019_B.DataTypeConversion9_ji = (uint16_T)(u1_1 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_1 : (int32_T)(uint16_T)u1_1);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Torque_Left_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion9_ji);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  u1_1 = floor(Racing_2019_B.RightTorqueSwitch);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 65536.0);
  }

  Racing_2019_B.DataTypeConversion8_f4 = (uint16_T)(u1_1 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_1 : (int32_T)(uint16_T)u1_1);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Torque_Right_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion8_f4);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.u0HzPulse = (Racing_2019_DW.clockTickCounter <
    Racing_2019_P.u0HzPulse_Duty) && (Racing_2019_DW.clockTickCounter >= 0) ?
    Racing_2019_P.u0HzPulse_Amp : 0.0;
  if (Racing_2019_DW.clockTickCounter >= Racing_2019_P.u0HzPulse_Period - 1.0) {
    Racing_2019_DW.clockTickCounter = 0;
  } else {
    Racing_2019_DW.clockTickCounter++;
  }

  Racing_2019_B.LogicalOperator1_m4 = !Racing_2019_B.Compare;
  Racing_2019_B.LogicalOperator2_b = ((Racing_2019_B.u0HzPulse != 0.0) &&
    Racing_2019_B.LogicalOperator1_m4);
  Racing_2019_B.DataTypeConversion7_e1 = Racing_2019_B.LogicalOperator2_b;
  if (Racing_2019_P.Set_Inverter_Settings > Racing_2019_P.Switch1_Threshold) {
    Racing_2019_B.Switch1_i = Racing_2019_P.Set_ID;
  } else {
    Racing_2019_B.Switch1_i = Racing_2019_B.Memory;
  }

  Racing_2019_B.Add_hp = (real_T)Racing_2019_B.DataTypeConversion7_e1 +
    Racing_2019_B.Switch1_i;
  Racing_2019_B.DataTypeConversion2_ek = (Racing_2019_B.SFunction1_kx != 0.0);
  Racing_2019_B.UnitDelay_f2 = Racing_2019_DW.UnitDelay_DSTATE_og;
  switch ((int32_T)Racing_2019_P.EdgeDetector_model_g) {
   case 1:
    Racing_2019_B.MultiportSwitch_l5[0] = Racing_2019_P.posedge_Value_h[0];
    Racing_2019_B.MultiportSwitch_l5[1] = Racing_2019_P.posedge_Value_h[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_l5[0] = Racing_2019_P.negedge_Value_co[0];
    Racing_2019_B.MultiportSwitch_l5[1] = Racing_2019_P.negedge_Value_co[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_l5[0] = Racing_2019_P.eitheredge_Value_hl[0];
    Racing_2019_B.MultiportSwitch_l5[1] = Racing_2019_P.eitheredge_Value_hl[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_l5[0],
    Racing_2019_B.DataTypeConversion2_ek, Racing_2019_B.UnitDelay_f2,
    &Racing_2019_B.POSITIVEEdge_cj);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_l5[1],
    Racing_2019_B.DataTypeConversion2_ek, Racing_2019_B.UnitDelay_f2,
    &Racing_2019_B.NEGATIVEEdge_po);
  Racing_2019_B.LogicalOperator1_lu =
    (Racing_2019_B.POSITIVEEdge_cj.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_po.RelationalOperator1);
  Racing_2019_B.DataTypeConversion3_pq = Racing_2019_B.LogicalOperator1_lu;
  Racing_2019_B.Inverter_LEFT_CAN_Tx_Counter =
    Racing_2019_DW.Inverter_LEFT_CAN_Tx_Counter_Pr;
  Racing_2019_B.Add1_ff = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion3_pq +
    Racing_2019_B.Inverter_LEFT_CAN_Tx_Counter);
  Racing_2019_B.DataTypeConversion2_ch = (Racing_2019_B.SFunction1_g != 0.0);
  Racing_2019_B.UnitDelay_jr = Racing_2019_DW.UnitDelay_DSTATE_bdf;
  switch ((int32_T)Racing_2019_P.EdgeDetector1_model_o4) {
   case 1:
    Racing_2019_B.MultiportSwitch_bm[0] = Racing_2019_P.posedge_Value_km[0];
    Racing_2019_B.MultiportSwitch_bm[1] = Racing_2019_P.posedge_Value_km[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_bm[0] = Racing_2019_P.negedge_Value_g0[0];
    Racing_2019_B.MultiportSwitch_bm[1] = Racing_2019_P.negedge_Value_g0[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_bm[0] = Racing_2019_P.eitheredge_Value_ln[0];
    Racing_2019_B.MultiportSwitch_bm[1] = Racing_2019_P.eitheredge_Value_ln[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_bm[0],
    Racing_2019_B.DataTypeConversion2_ch, Racing_2019_B.UnitDelay_jr,
    &Racing_2019_B.POSITIVEEdge_as);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_bm[1],
    Racing_2019_B.DataTypeConversion2_ch, Racing_2019_B.UnitDelay_jr,
    &Racing_2019_B.NEGATIVEEdge_gi);
  Racing_2019_B.LogicalOperator1_gl =
    (Racing_2019_B.POSITIVEEdge_as.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_gi.RelationalOperator1);
  Racing_2019_B.DataTypeConversion4_eq = Racing_2019_B.LogicalOperator1_gl;
  Racing_2019_B.Inverter_RIGHT_CAN_Tx_Counter =
    Racing_2019_DW.Inverter_RIGHT_CAN_Tx_Counter_P;
  Racing_2019_B.Add2_hz = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion4_eq +
    Racing_2019_B.Inverter_RIGHT_CAN_Tx_Counter);
  Racing_2019_B.DataTypeConversion_a = Racing_2019_B.RegenAND;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Regen_AND_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion_a);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion2_nv = Racing_2019_B.Brake_Error_OR;
  Racing_2019_B.UnitDelay_cu = Racing_2019_DW.UnitDelay_DSTATE_m0;
  switch ((int32_T)Racing_2019_P.EdgeDetector4_model_e) {
   case 1:
    Racing_2019_B.MultiportSwitch_hm[0] = Racing_2019_P.posedge_Value_fz[0];
    Racing_2019_B.MultiportSwitch_hm[1] = Racing_2019_P.posedge_Value_fz[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_hm[0] = Racing_2019_P.negedge_Value_ji[0];
    Racing_2019_B.MultiportSwitch_hm[1] = Racing_2019_P.negedge_Value_ji[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_hm[0] = Racing_2019_P.eitheredge_Value_id[0];
    Racing_2019_B.MultiportSwitch_hm[1] = Racing_2019_P.eitheredge_Value_id[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_hm[0],
    Racing_2019_B.DataTypeConversion2_nv, Racing_2019_B.UnitDelay_cu,
    &Racing_2019_B.POSITIVEEdge_oo);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_hm[1],
    Racing_2019_B.DataTypeConversion2_nv, Racing_2019_B.UnitDelay_cu,
    &Racing_2019_B.NEGATIVEEdge_i5);
  Racing_2019_B.LogicalOperator1_et =
    (Racing_2019_B.POSITIVEEdge_oo.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_i5.RelationalOperator1);
  Racing_2019_B.DataTypeConversion13_d = Racing_2019_B.LogicalOperator1_et;
  Racing_2019_B.Brake_Error_Counter =
    Racing_2019_DW.Brake_Error_Counter_PreviousInp;
  Racing_2019_B.Add5 = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion13_d
    + Racing_2019_B.Brake_Error_Counter);
  Racing_2019_B.APPS1_Error_Counter =
    Racing_2019_DW.APPS1_Error_Counter_PreviousInp;
  Racing_2019_B.DataTypeConversion2_ep = Racing_2019_B.APPS1_Error_OR;
  Racing_2019_B.UnitDelay_os = Racing_2019_DW.UnitDelay_DSTATE_hx;
  switch ((int32_T)Racing_2019_P.EdgeDetector4_model_l) {
   case 1:
    Racing_2019_B.MultiportSwitch_cd[0] = Racing_2019_P.posedge_Value_md[0];
    Racing_2019_B.MultiportSwitch_cd[1] = Racing_2019_P.posedge_Value_md[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_cd[0] = Racing_2019_P.negedge_Value_j4[0];
    Racing_2019_B.MultiportSwitch_cd[1] = Racing_2019_P.negedge_Value_j4[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_cd[0] = Racing_2019_P.eitheredge_Value_f5[0];
    Racing_2019_B.MultiportSwitch_cd[1] = Racing_2019_P.eitheredge_Value_f5[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_cd[0],
    Racing_2019_B.DataTypeConversion2_ep, Racing_2019_B.UnitDelay_os,
    &Racing_2019_B.POSITIVEEdge_gm1);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_cd[1],
    Racing_2019_B.DataTypeConversion2_ep, Racing_2019_B.UnitDelay_os,
    &Racing_2019_B.NEGATIVEEdge_n3);
  Racing_2019_B.LogicalOperator1_h1 =
    (Racing_2019_B.POSITIVEEdge_gm1.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_n3.RelationalOperator1);
  Racing_2019_B.DataTypeConversion13_d0 = Racing_2019_B.LogicalOperator1_h1;
  Racing_2019_B.Add5_f = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion13_d0 + Racing_2019_B.APPS1_Error_Counter);
  Racing_2019_B.APPS_NotAgree_Error_Counter =
    Racing_2019_DW.APPS_NotAgree_Error_Counter_Pre;
  Racing_2019_B.Substract = (uint16_T)(Racing_2019_B.SFunction1_o2_o2 -
    Racing_2019_B.SFunction1_o1_f0);
  Racing_2019_B.Compare_iqw = (Racing_2019_B.Substract <
    Racing_2019_P.CompareToConstant10_const_b);
  Racing_2019_B.Compare_ja = (Racing_2019_B.Substract >
    Racing_2019_P.CompareToConstant11_const_e);
  Racing_2019_B.APPS_NotAgree_Error_OR = (Racing_2019_B.Compare_iqw ||
    Racing_2019_B.Compare_ja);
  Racing_2019_B.DataTypeConversion2_nq = Racing_2019_B.APPS_NotAgree_Error_OR;
  Racing_2019_B.UnitDelay_fl = Racing_2019_DW.UnitDelay_DSTATE_fb;
  switch ((int32_T)Racing_2019_P.EdgeDetector4_model_ar) {
   case 1:
    Racing_2019_B.MultiportSwitch_c5[0] = Racing_2019_P.posedge_Value_aq[0];
    Racing_2019_B.MultiportSwitch_c5[1] = Racing_2019_P.posedge_Value_aq[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_c5[0] = Racing_2019_P.negedge_Value_dy[0];
    Racing_2019_B.MultiportSwitch_c5[1] = Racing_2019_P.negedge_Value_dy[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_c5[0] = Racing_2019_P.eitheredge_Value_jx[0];
    Racing_2019_B.MultiportSwitch_c5[1] = Racing_2019_P.eitheredge_Value_jx[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_c5[0],
    Racing_2019_B.DataTypeConversion2_nq, Racing_2019_B.UnitDelay_fl,
    &Racing_2019_B.POSITIVEEdge_a0);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_c5[1],
    Racing_2019_B.DataTypeConversion2_nq, Racing_2019_B.UnitDelay_fl,
    &Racing_2019_B.NEGATIVEEdge_phu);
  Racing_2019_B.LogicalOperator1_by =
    (Racing_2019_B.POSITIVEEdge_a0.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_phu.RelationalOperator1);
  Racing_2019_B.DataTypeConversion13_ii = Racing_2019_B.LogicalOperator1_by;
  Racing_2019_B.Add5_fm = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion13_ii +
    Racing_2019_B.APPS_NotAgree_Error_Counter);
  Racing_2019_B.APPS2_Error_Counter =
    Racing_2019_DW.APPS2_Error_Counter_PreviousInp;
  Racing_2019_B.DataTypeConversion2_es = Racing_2019_B.APPS2_Error_OR;
  Racing_2019_B.UnitDelay_ec = Racing_2019_DW.UnitDelay_DSTATE_hr;
  switch ((int32_T)Racing_2019_P.EdgeDetector4_model_c) {
   case 1:
    Racing_2019_B.MultiportSwitch_ez[0] = Racing_2019_P.posedge_Value_hc[0];
    Racing_2019_B.MultiportSwitch_ez[1] = Racing_2019_P.posedge_Value_hc[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_ez[0] = Racing_2019_P.negedge_Value_ae[0];
    Racing_2019_B.MultiportSwitch_ez[1] = Racing_2019_P.negedge_Value_ae[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_ez[0] = Racing_2019_P.eitheredge_Value_a4[0];
    Racing_2019_B.MultiportSwitch_ez[1] = Racing_2019_P.eitheredge_Value_a4[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_ez[0],
    Racing_2019_B.DataTypeConversion2_es, Racing_2019_B.UnitDelay_ec,
    &Racing_2019_B.POSITIVEEdge_iyn);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_ez[1],
    Racing_2019_B.DataTypeConversion2_es, Racing_2019_B.UnitDelay_ec,
    &Racing_2019_B.NEGATIVEEdge_b4);
  Racing_2019_B.LogicalOperator1_bq =
    (Racing_2019_B.POSITIVEEdge_iyn.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_b4.RelationalOperator1);
  Racing_2019_B.DataTypeConversion13_gf = Racing_2019_B.LogicalOperator1_bq;
  Racing_2019_B.Add5_g = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion13_gf + Racing_2019_B.APPS2_Error_Counter);
  Racing_2019_B.DataTypeConversion2_cyg = Racing_2019_B.ResettableDelay50ms_k;
  Racing_2019_B.UnitDelay_hb = Racing_2019_DW.UnitDelay_DSTATE_pzg;
  switch ((int32_T)Racing_2019_P.EdgeDetector4_model_p) {
   case 1:
    Racing_2019_B.MultiportSwitch_am[0] = Racing_2019_P.posedge_Value_ew[0];
    Racing_2019_B.MultiportSwitch_am[1] = Racing_2019_P.posedge_Value_ew[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_am[0] = Racing_2019_P.negedge_Value_ik[0];
    Racing_2019_B.MultiportSwitch_am[1] = Racing_2019_P.negedge_Value_ik[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_am[0] = Racing_2019_P.eitheredge_Value_d1[0];
    Racing_2019_B.MultiportSwitch_am[1] = Racing_2019_P.eitheredge_Value_d1[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_am[0],
    Racing_2019_B.DataTypeConversion2_cyg, Racing_2019_B.UnitDelay_hb,
    &Racing_2019_B.POSITIVEEdge_ms);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_am[1],
    Racing_2019_B.DataTypeConversion2_cyg, Racing_2019_B.UnitDelay_hb,
    &Racing_2019_B.NEGATIVEEdge_f);
  Racing_2019_B.LogicalOperator1_kh =
    (Racing_2019_B.POSITIVEEdge_ms.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_f.RelationalOperator1);
  Racing_2019_B.DataTypeConversion13_nr = Racing_2019_B.LogicalOperator1_kh;
  Racing_2019_B.Sensor_Error_Counter =
    Racing_2019_DW.Sensor_Error_Counter_PreviousIn;
  Racing_2019_B.Add5_d = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion13_nr + Racing_2019_B.Sensor_Error_Counter);
  Racing_2019_B.DataTypeConversion_g = Racing_2019_B.ResettableDelay50ms_k;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Sensor_Error_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion_g);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Compare_hu = (Racing_2019_P.Constant6_Value <
    Racing_2019_P.CompareToConstant12_const);
  Racing_2019_B.Compare_ib = (Racing_2019_P.Constant6_Value >
    Racing_2019_P.CompareToConstant13_const);
  Racing_2019_B.Steering_Error_OR = (Racing_2019_B.Compare_hu ||
    Racing_2019_B.Compare_ib);
  Racing_2019_B.DataTypeConversion2_j2 = Racing_2019_B.Steering_Error_OR;
  Racing_2019_B.UnitDelay_iw = Racing_2019_DW.UnitDelay_DSTATE_bo;
  switch ((int32_T)Racing_2019_P.EdgeDetector4_model_px) {
   case 1:
    Racing_2019_B.MultiportSwitch_ep[0] = Racing_2019_P.posedge_Value_np[0];
    Racing_2019_B.MultiportSwitch_ep[1] = Racing_2019_P.posedge_Value_np[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_ep[0] = Racing_2019_P.negedge_Value_c4[0];
    Racing_2019_B.MultiportSwitch_ep[1] = Racing_2019_P.negedge_Value_c4[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_ep[0] = Racing_2019_P.eitheredge_Value_nu[0];
    Racing_2019_B.MultiportSwitch_ep[1] = Racing_2019_P.eitheredge_Value_nu[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_ep[0],
    Racing_2019_B.DataTypeConversion2_j2, Racing_2019_B.UnitDelay_iw,
    &Racing_2019_B.POSITIVEEdge_f5);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_ep[1],
    Racing_2019_B.DataTypeConversion2_j2, Racing_2019_B.UnitDelay_iw,
    &Racing_2019_B.NEGATIVEEdge_op);
  Racing_2019_B.LogicalOperator1_bbq =
    (Racing_2019_B.POSITIVEEdge_f5.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_op.RelationalOperator1);
  Racing_2019_B.DataTypeConversion13_ol = Racing_2019_B.LogicalOperator1_bbq;
  Racing_2019_B.Steering_Error_Counter =
    Racing_2019_DW.Steering_Error_Counter_Previous;
  Racing_2019_B.Add5_o = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion13_ol + Racing_2019_B.Steering_Error_Counter);
  Racing_2019_B.DataTypeConversion_fs = Racing_2019_B.EDEnable;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(ED_Enable_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion_fs);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.TorqueLimitPercentage = Racing_2019_P.TorqueLimitPercentage_Gain
    * Racing_2019_B.TorqueLimiter;
  u1_1 = floor(Racing_2019_B.TorqueLimitPercentage);
  if (rtIsNaN(u1_1) || rtIsInf(u1_1)) {
    u1_1 = 0.0;
  } else {
    u1_1 = fmod(u1_1, 256.0);
  }

  Racing_2019_B.conversion8 = (uint8_T)(u1_1 < 0.0 ? (int32_T)(uint8_T)-(int8_T)
    (uint8_T)-u1_1 : (int32_T)(uint8_T)u1_1);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32
      (PL_Torque_Limiter_Percentage_Index_UsbFlRec, (Int32)
       Racing_2019_B.conversion8);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  IcontL = Racing_2019_B.Switch2;
  u1_1 = Racing_2019_P.IrmsSaturation_LowerSat;
  RPM_maxL = Racing_2019_P.IrmsSaturation_UpperSat;
  if (IcontL > RPM_maxL) {
    Racing_2019_B.IrmsSaturation = RPM_maxL;
  } else if (IcontL < u1_1) {
    Racing_2019_B.IrmsSaturation = u1_1;
  } else {
    Racing_2019_B.IrmsSaturation = IcontL;
  }

  if (Racing_2019_M->Timing.RateInteraction.TID1_3 == 1) {
    Racing_2019_B.RateTransition1_n = Racing_2019_B.TorqueLeftLimiter2;
  }

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(Torue_before_mul_Index_UsbFlRec,
      (Float32)Racing_2019_B.TorqueLeftLimiter1);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.FixPtUnitDelay1_p = Racing_2019_DW.FixPtUnitDelay1_DSTATE_d;
  IcontL = Racing_2019_B.IDC_Transfer_Function;
  u1_1 = Racing_2019_B.FixPtUnitDelay1_p;
  if ((IcontL < u1_1) || rtIsNaN(u1_1)) {
    u1_1 = IcontL;
  }

  Racing_2019_B.MinMax_f = u1_1;
  zcEvent = (Racing_2019_B.RegenAND &&
             (Racing_2019_PrevZCX.ResettableDelay_Reset_ZCE_c != POS_ZCSIG));
  if (zcEvent) {
    Racing_2019_DW.ResettableDelay_DSTATE_j =
      Racing_2019_P.ResettableDelay_InitialCondit_a;
  }

  Racing_2019_PrevZCX.ResettableDelay_Reset_ZCE_c = Racing_2019_B.RegenAND;
  Racing_2019_B.ResettableDelay_b = Racing_2019_DW.ResettableDelay_DSTATE_j;
  Racing_2019_B.RPMAND2 = !Racing_2019_B.ResettableDelay_b;
  if (Racing_2019_B.RPMAND2) {
    Racing_2019_B.Reset_c = Racing_2019_P.IDC_Regen_last_max_vinit;
  } else {
    Racing_2019_B.Reset_c = Racing_2019_B.MinMax_f;
  }

  Racing_2019_B.FixPtUnitDelay1_g = Racing_2019_DW.FixPtUnitDelay1_DSTATE_g;
  IcontL = Racing_2019_B.Reset_c;
  u1_1 = Racing_2019_B.FixPtUnitDelay1_g;
  if ((IcontL < u1_1) || rtIsNaN(u1_1)) {
    u1_1 = IcontL;
  }

  Racing_2019_B.MinMax_n = u1_1;
  if (Racing_2019_P.Regen_IDC_Reset) {
    Racing_2019_B.Reset_a = Racing_2019_P.IDC_Regen_max_vinit;
  } else {
    Racing_2019_B.Reset_a = Racing_2019_B.MinMax_n;
  }

  if (Racing_2019_M->Timing.RateInteraction.TID1_4 == 1) {
    Racing_2019_B.RateTransition_e = Racing_2019_B.DataTypeConversion2_o;
  }

  zcEvent_0 = rt_ZCFcn(RISING_ZERO_CROSSING,
                       &Racing_2019_PrevZCX.USB_FLIGHT_REC_EJECT_Trig_ZCE,
                       (Racing_2019_P.Eject_USB));
  if (zcEvent_0 != NO_ZCEVENT) {
    dsflrec_usb_eject();
  }
}

void Racing_2019_update0(void)
{
  int_T idxDelay;
  Racing_2019_DW.Memory_PreviousInput = Racing_2019_B.Add_hp;
  Racing_2019_DW.DynamicOffsetLEMIDC_PreviousInp = Racing_2019_B.Switch_i;
  Racing_2019_DW.IrmsPrevious_PreviousInput = Racing_2019_B.IrmsSaturation;
  Racing_2019_DW.DynamicOffsetLEMVDC_PreviousInp = Racing_2019_B.Switch_l2;
  Racing_2019_DW.Memory_PreviousInput_e = Racing_2019_B.TorqueRightFiltered1;
  for (idxDelay = 0; idxDelay < 49; idxDelay++) {
    Racing_2019_DW.Delay50ms_DSTATE[idxDelay] =
      Racing_2019_DW.Delay50ms_DSTATE[idxDelay + 1];
  }

  Racing_2019_DW.Delay50ms_DSTATE[49] = Racing_2019_B.u0HzPulse;
  for (idxDelay = 0; idxDelay < 999; idxDelay++) {
    Racing_2019_DW.Inverter_RIGHT_CAN_0x162_DSTATE[idxDelay] =
      Racing_2019_DW.Inverter_RIGHT_CAN_0x162_DSTATE[idxDelay + 1];
    Racing_2019_DW.Inverter_LEFT_CAN_0x161_DSTATE[idxDelay] =
      Racing_2019_DW.Inverter_LEFT_CAN_0x161_DSTATE[idxDelay + 1];
  }

  Racing_2019_DW.Inverter_RIGHT_CAN_0x162_DSTATE[999] =
    Racing_2019_P.Constant4_Value_hp;
  Racing_2019_DW.Inverter_LEFT_CAN_0x161_DSTATE[999] =
    Racing_2019_P.Constant5_Value_oo;
  for (idxDelay = 0; idxDelay < 9999; idxDelay++) {
    Racing_2019_DW.Inverter_LEFT_CAN_0x181_DSTATE[idxDelay] =
      Racing_2019_DW.Inverter_LEFT_CAN_0x181_DSTATE[idxDelay + 1];
    Racing_2019_DW.Inverter_RIGHT_CAN_0x182_DSTATE[idxDelay] =
      Racing_2019_DW.Inverter_RIGHT_CAN_0x182_DSTATE[idxDelay + 1];
  }

  Racing_2019_DW.Inverter_LEFT_CAN_0x181_DSTATE[9999] =
    Racing_2019_P.Constant2_Value_ox;
  Racing_2019_DW.Inverter_RIGHT_CAN_0x182_DSTATE[9999] =
    Racing_2019_P.Constant2_Value_i;
  for (idxDelay = 0; idxDelay < 49; idxDelay++) {
    Racing_2019_DW.ResettableDelay50ms_DSTATE_h[idxDelay] =
      Racing_2019_DW.ResettableDelay50ms_DSTATE_h[idxDelay + 1];
  }

  Racing_2019_DW.ResettableDelay50ms_DSTATE_h[49] =
    Racing_2019_B.Sensor_Error_OR;
  for (idxDelay = 0; idxDelay < 349; idxDelay++) {
    Racing_2019_DW.ResettableDelay350ms_DSTATE[idxDelay] =
      Racing_2019_DW.ResettableDelay350ms_DSTATE[idxDelay + 1];
  }

  Racing_2019_DW.ResettableDelay350ms_DSTATE[349] =
    Racing_2019_B.LogicalOperator_i;
  Racing_2019_DW.Memory_PreviousInput_h = Racing_2019_B.Logic_j[0];
  Racing_2019_DW.UnitDelay_DSTATE = Racing_2019_B.DataTypeConversion2_d;
  Racing_2019_DW.UnitDelay_DSTATE_c = Racing_2019_B.DataTypeConversion2_k;
  Racing_2019_DW.BMS_CAN_200_Counter_PreviousInp = Racing_2019_B.Add_n;
  for (idxDelay = 0; idxDelay < 1999; idxDelay++) {
    Racing_2019_DW.BMS_CAN_200_DSTATE[idxDelay] =
      Racing_2019_DW.BMS_CAN_200_DSTATE[idxDelay + 1];
    Racing_2019_DW.AUX_CAN_314_DSTATE[idxDelay] =
      Racing_2019_DW.AUX_CAN_314_DSTATE[idxDelay + 1];
  }

  Racing_2019_DW.BMS_CAN_200_DSTATE[1999] = Racing_2019_P.Constant2_Value_b;
  Racing_2019_DW.AUX_CAN_314_DSTATE[1999] = Racing_2019_P.Constant2_Value_j;
  Racing_2019_DW.AUX_CAN_314_Counter_PreviousInp = Racing_2019_B.Add1_fb;
  Racing_2019_DW.UnitDelay_DSTATE_c1 = Racing_2019_B.DataTypeConversion2_n5;
  Racing_2019_DW.Memory_PreviousInput_fq = Racing_2019_B.Logic_g[0];
  Racing_2019_DW.Memory_PreviousInput_l = Racing_2019_B.Logic_g[0];
  for (idxDelay = 0; idxDelay < 49; idxDelay++) {
    Racing_2019_DW.ResettableDelay50ms_DSTATE_j[idxDelay] =
      Racing_2019_DW.ResettableDelay50ms_DSTATE_j[idxDelay + 1];
  }

  Racing_2019_DW.ResettableDelay50ms_DSTATE_j[49] =
    Racing_2019_B.LogicalOperator1_el;
  Racing_2019_DW.InverterLEFTBaudrateRx_Previous = Racing_2019_B.Switch1_k;
  Racing_2019_DW.InverterRIGHTBaudrateRx_Previou = Racing_2019_B.Switch1_gc;
  Racing_2019_DW.InverterLEFTBaudrateTx_Previous = Racing_2019_B.Switch1_o;
  Racing_2019_DW.Output_DSTATE = Racing_2019_B.FixPtSwitch;
  Racing_2019_DW.Delay2ms_DSTATE[0] = Racing_2019_DW.Delay2ms_DSTATE[1];
  Racing_2019_DW.Delay2ms_DSTATE[1] = Racing_2019_B.Compare_ld;
  Racing_2019_DW.Memory1_PreviousInput = Racing_2019_B.Switch_j;
  Racing_2019_DW.Output_DSTATE_f = Racing_2019_B.FixPtSwitch_d;
  Racing_2019_DW.Delay2ms_DSTATE_n[0] = Racing_2019_DW.Delay2ms_DSTATE_n[1];
  Racing_2019_DW.Delay2ms_DSTATE_n[1] = Racing_2019_B.Compare_or;
  Racing_2019_DW.Memory1_PreviousInput_n = Racing_2019_B.Switch_bi;
  Racing_2019_DW.InverterLEFTBaudrateTx_Previo_o = Racing_2019_B.Switch1_ir;
  Racing_2019_DW.Output_DSTATE_c = Racing_2019_B.FixPtSwitch_f;
  Racing_2019_DW.Delay1ms_DSTATE = Racing_2019_B.Compare_cx;
  Racing_2019_DW.Memory1_PreviousInput_m = Racing_2019_B.Switch_d;
  Racing_2019_DW.Output_DSTATE_fj = Racing_2019_B.FixPtSwitch_c;
  Racing_2019_DW.Delay1ms_DSTATE_a = Racing_2019_B.Compare_lf;
  Racing_2019_DW.Memory1_PreviousInput_l = Racing_2019_B.Switch_j2;
  Racing_2019_DW.AccuBaudrateRx_PreviousInput = Racing_2019_B.Switch1_d;
  Racing_2019_DW.AccuBaudrateTx_PreviousInput = Racing_2019_B.Switch1_c;
  Racing_2019_DW.Output_DSTATE_i = Racing_2019_B.FixPtSwitch_p;
  Racing_2019_DW.Delay2ms_DSTATE_nf[0] = Racing_2019_DW.Delay2ms_DSTATE_nf[1];
  Racing_2019_DW.Delay2ms_DSTATE_nf[1] = Racing_2019_B.Compare_jo;
  Racing_2019_DW.Memory1_PreviousInput_f = Racing_2019_B.Switch_ah;
  Racing_2019_DW.Output_DSTATE_ix = Racing_2019_B.FixPtSwitch_a;
  Racing_2019_DW.Delay2ms_DSTATE_p[0] = Racing_2019_DW.Delay2ms_DSTATE_p[1];
  Racing_2019_DW.Delay2ms_DSTATE_p[1] = Racing_2019_B.Compare_pq;
  Racing_2019_DW.Memory1_PreviousInput_g = Racing_2019_B.Switch_m;
  Racing_2019_DW.DashAuxBaudrateRx_PreviousInput = Racing_2019_B.Switch1_b;
  Racing_2019_DW.DashAuxBaudrateTx_PreviousInput = Racing_2019_B.Switch1_j;
  Racing_2019_DW.Output_DSTATE_e = Racing_2019_B.FixPtSwitch_i;
  Racing_2019_DW.Delay2ms_DSTATE_a[0] = Racing_2019_DW.Delay2ms_DSTATE_a[1];
  Racing_2019_DW.Delay2ms_DSTATE_a[1] = Racing_2019_B.Compare_bu;
  Racing_2019_DW.Memory1_PreviousInput_n3 = Racing_2019_B.Switch_e;
  Racing_2019_DW.Output_DSTATE_cy = Racing_2019_B.FixPtSwitch_l;
  Racing_2019_DW.Delay2ms_DSTATE_nq[0] = Racing_2019_DW.Delay2ms_DSTATE_nq[1];
  Racing_2019_DW.Delay2ms_DSTATE_nq[1] = Racing_2019_B.Compare_kc;
  Racing_2019_DW.Memory1_PreviousInput_lx = Racing_2019_B.Switch_o;
  Racing_2019_DW.Memory_PreviousInput_er = Racing_2019_B.Logic_m4[0];
  Racing_2019_DW.DASH_CAN_198_Counter_PreviousIn = Racing_2019_B.Add2;
  Racing_2019_DW.Memory_PreviousInput_fh = Racing_2019_B.DataTypeConversion2_p4;
  Racing_2019_DW.DASH_CAN_101_Counter_PreviousIn = Racing_2019_B.Add1_l;
  Racing_2019_DW.UnitDelay_DSTATE_di = Racing_2019_B.DataTypeConversion2_k2;
  for (idxDelay = 0; idxDelay < 1999; idxDelay++) {
    Racing_2019_DW.DASH_CAN_101_DSTATE[idxDelay] =
      Racing_2019_DW.DASH_CAN_101_DSTATE[idxDelay + 1];
    Racing_2019_DW.DASH_CAN_198_DSTATE[idxDelay] =
      Racing_2019_DW.DASH_CAN_198_DSTATE[idxDelay + 1];
  }

  Racing_2019_DW.DASH_CAN_101_DSTATE[1999] = Racing_2019_P.Constant3_Value;
  Racing_2019_DW.DASH_CAN_198_DSTATE[1999] = Racing_2019_P.Constant2_Value_m;
  Racing_2019_DW.MemoryLEMVDC_PreviousInput = Racing_2019_B.Switch1_n;
  Racing_2019_DW.Output_DSTATE_g = Racing_2019_B.FixPtSwitch_e;
  Racing_2019_DW.Delay_DSTATE = Racing_2019_B.LogicalOperator1_l;
  Racing_2019_DW.Memory_PreviousInput_bp = Racing_2019_B.Logic_km[0];
  Racing_2019_DW.MemoryLEMIDC_PreviousInput = Racing_2019_B.Switch1_g;
  Racing_2019_DW.Output_DSTATE_k = Racing_2019_B.FixPtSwitch_j;
  Racing_2019_DW.Delay_DSTATE_k = Racing_2019_B.LogicalOperator1_ei;
  Racing_2019_DW.Memory_PreviousInput_kz = Racing_2019_B.Logic_kb[0];
  Racing_2019_DW.DynamicOffsetLEMLeft_PreviousIn = Racing_2019_B.Switch_b;
  Racing_2019_DW.MemoryLEMIACLeft_PreviousInput = Racing_2019_B.Switch1_nc;
  Racing_2019_DW.Output_DSTATE_a = Racing_2019_B.FixPtSwitch_lr;
  Racing_2019_DW.Delay_DSTATE_e = Racing_2019_B.LogicalOperator1_lv;
  Racing_2019_DW.Memory_PreviousInput_mu = Racing_2019_B.Logic_a[0];
  Racing_2019_DW.DynamicOffsetLEMRight_PreviousI = Racing_2019_B.Switch_a;
  Racing_2019_DW.MemoryLEMIACRight_PreviousInput = Racing_2019_B.Switch1_l;
  Racing_2019_DW.Output_DSTATE_j = Racing_2019_B.FixPtSwitch_lp;
  Racing_2019_DW.Delay_DSTATE_h = Racing_2019_B.LogicalOperator1_hn;
  Racing_2019_DW.Memory_PreviousInput_df = Racing_2019_B.Logic_p[0];
  Racing_2019_DW.DiscreteTimeIntegrator_DSTATE +=
    Racing_2019_P.DiscreteTimeIntegrator_gainval *
    Racing_2019_B.DataTypeConversion_e;
  Racing_2019_DW.DiscreteTimeIntegrator1_DSTATE +=
    Racing_2019_P.DiscreteTimeIntegrator1_gainval *
    Racing_2019_B.DataTypeConversion5_e;
  Racing_2019_DW.Meters_Max_DSTATE += Racing_2019_B.Gain_n;
  Racing_2019_DW.Meters_Min_DSTATE += Racing_2019_B.Gain1_e;
  Racing_2019_DW.FixPtUnitDelay1_DSTATE = Racing_2019_B.Reset;
  Racing_2019_DW.FixPtUnitDelay1_DSTATE_a = Racing_2019_B.Reset_o;
  Racing_2019_DW.UnitDelay_DSTATE_od = Racing_2019_B.DataTypeConversion2_ca;
  Racing_2019_DW.Inverter_LEFT_CAN_Rx_Counter_Pr = Racing_2019_B.Add_a;
  Racing_2019_DW.UnitDelay_DSTATE_e = Racing_2019_B.DataTypeConversion2_de;
  Racing_2019_DW.Inverter_RIGHT_CAN_Rx_Counter_P = Racing_2019_B.Add_pj;
  Racing_2019_DW.UnitDelay_DSTATE_og = Racing_2019_B.DataTypeConversion2_ek;
  Racing_2019_DW.Inverter_LEFT_CAN_Tx_Counter_Pr = Racing_2019_B.Add1_ff;
  Racing_2019_DW.UnitDelay_DSTATE_bdf = Racing_2019_B.DataTypeConversion2_ch;
  Racing_2019_DW.Inverter_RIGHT_CAN_Tx_Counter_P = Racing_2019_B.Add2_hz;
  Racing_2019_DW.UnitDelay_DSTATE_m0 = Racing_2019_B.DataTypeConversion2_nv;
  Racing_2019_DW.Brake_Error_Counter_PreviousInp = Racing_2019_B.Add5;
  Racing_2019_DW.APPS1_Error_Counter_PreviousInp = Racing_2019_B.Add5_f;
  Racing_2019_DW.UnitDelay_DSTATE_hx = Racing_2019_B.DataTypeConversion2_ep;
  Racing_2019_DW.APPS_NotAgree_Error_Counter_Pre = Racing_2019_B.Add5_fm;
  Racing_2019_DW.UnitDelay_DSTATE_fb = Racing_2019_B.DataTypeConversion2_nq;
  Racing_2019_DW.APPS2_Error_Counter_PreviousInp = Racing_2019_B.Add5_g;
  Racing_2019_DW.UnitDelay_DSTATE_hr = Racing_2019_B.DataTypeConversion2_es;
  Racing_2019_DW.UnitDelay_DSTATE_pzg = Racing_2019_B.DataTypeConversion2_cyg;
  Racing_2019_DW.Sensor_Error_Counter_PreviousIn = Racing_2019_B.Add5_d;
  Racing_2019_DW.UnitDelay_DSTATE_bo = Racing_2019_B.DataTypeConversion2_j2;
  Racing_2019_DW.Steering_Error_Counter_Previous = Racing_2019_B.Add5_o;
  Racing_2019_DW.FixPtUnitDelay1_DSTATE_d = Racing_2019_B.Reset_c;
  Racing_2019_DW.ResettableDelay_DSTATE_j = Racing_2019_B.RegenAND;
  Racing_2019_DW.FixPtUnitDelay1_DSTATE_g = Racing_2019_B.Reset_a;
  if (!(++Racing_2019_M->Timing.clockTick0)) {
    ++Racing_2019_M->Timing.clockTickH0;
  }

  Racing_2019_M->Timing.t[0] = Racing_2019_M->Timing.clockTick0 *
    Racing_2019_M->Timing.stepSize0 + Racing_2019_M->Timing.clockTickH0 *
    Racing_2019_M->Timing.stepSize0 * 4294967296.0;
  Racing_2019_M->Timing.clockTick1++;
  if (!Racing_2019_M->Timing.clockTick1) {
    Racing_2019_M->Timing.clockTickH1++;
  }
}

void Racing_2019_output2(void)
{
  boolean_T zcEvent;
  int32_T i;
  (Racing_2019_M->Timing.RateInteraction.TID2_3)++;
  if ((Racing_2019_M->Timing.RateInteraction.TID2_3) > 9) {
    Racing_2019_M->Timing.RateInteraction.TID2_3 = 0;
  }

  (Racing_2019_M->Timing.RateInteraction.TID2_4)++;
  if ((Racing_2019_M->Timing.RateInteraction.TID2_4) > 19) {
    Racing_2019_M->Timing.RateInteraction.TID2_4 = 0;
  }

  if (Racing_2019_M->Timing.RateInteraction.TID2_3 == 1) {
    Racing_2019_B.to100Hz = Racing_2019_DW.to100Hz_Buffer0;
    Racing_2019_B.to100Hz1 = Racing_2019_DW.to100Hz1_Buffer0;
  }

  Racing_2019_B.DashCANTx = ((Racing_2019_P.Constant13_Value != 0.0) ||
    (Racing_2019_B.to100Hz != 0.0));
  Racing_2019_B.AuxCANTx = ((Racing_2019_P.Constant13_Value != 0.0) ||
    Racing_2019_B.to100Hz1);
  if (Racing_2019_M->Timing.RateInteraction.TID2_3 == 1) {
    Racing_2019_B.to100Hz2 = Racing_2019_DW.to100Hz2_Buffer0;
    Racing_2019_B.to100Hz5 = Racing_2019_DW.to100Hz5_Buffer0;
  }

  Racing_2019_B.AccuCANTx = ((Racing_2019_P.Constant13_Value != 0.0) ||
    (Racing_2019_B.to100Hz2 != 0.0));
  Racing_2019_B.LogicalOperator10 = !(Racing_2019_P.CAN_Tx_FMEA_Enable != 0.0);
  Racing_2019_B.TorqueCANTx = (Racing_2019_B.LogicalOperator10 ||
    Racing_2019_B.to100Hz3);
  Racing_2019_B.LogicalOperator12 = !(Racing_2019_P.CAN_Status_FMEA_Enable !=
    0.0);
  Racing_2019_B.CANChannelsStatus = (Racing_2019_B.LogicalOperator12 ||
    Racing_2019_B.to100Hz4);
  Racing_2019_B.DashCANRx = ((Racing_2019_P.Constant14_Value != 0.0) ||
    Racing_2019_B.to100Hz5);
  if (Racing_2019_M->Timing.RateInteraction.TID2_3 == 1) {
    Racing_2019_B.to100Hz6 = Racing_2019_DW.to100Hz6_Buffer0;
  }

  Racing_2019_B.AuxCANRx = ((Racing_2019_P.Constant14_Value != 0.0) ||
    Racing_2019_B.to100Hz6);
  if (Racing_2019_M->Timing.RateInteraction.TID2_4 == 1) {
    Racing_2019_B.to100Hz7 = Racing_2019_DW.to100Hz7_Buffer0;
  }

  Racing_2019_B.AccuCANRx = ((Racing_2019_P.Constant14_Value != 0.0) ||
    Racing_2019_B.to100Hz7);
  Racing_2019_B.LogicalOperator11 = !(Racing_2019_P.CAN_Rx_FMEA_Enable != 0.0);
  Racing_2019_B.InvLEFTCANRx = (Racing_2019_B.LogicalOperator11 ||
    (Racing_2019_B.to100Hz8 != 0.0));
  Racing_2019_B.InvRIGHTCANRx = (Racing_2019_B.LogicalOperator11 ||
    (Racing_2019_B.to100Hz9 != 0.0));
  if (Racing_2019_M->Timing.RateInteraction.TID2_3 == 1) {
    Racing_2019_B.EnableToggle = Racing_2019_DW.EnableToggle_Buffer0;
    Racing_2019_B.StartButton = Racing_2019_DW.StartButton_Buffer0;
  }

  Racing_2019_B.Compare_g3 = (Racing_2019_B.to100Hz12 >=
    Racing_2019_P.Constant_Value_o);
  Racing_2019_B.Compare_gl = (Racing_2019_B.to100Hz13 >=
    Racing_2019_P.TSOn_const);
  Racing_2019_B.StartUpAND = (Racing_2019_B.EnableToggle &&
    Racing_2019_B.StartButton && Racing_2019_B.Compare_g3 &&
    Racing_2019_B.Compare_gl);
  zcEvent = ((!Racing_2019_B.StartUpAND) &&
             (Racing_2019_PrevZCX.ResettableDelay50ms_Reset_ZCE != ZERO_ZCSIG));
  if (zcEvent) {
    for (i = 0; i < 5; i++) {
      Racing_2019_DW.ResettableDelay50ms_DSTATE[i] =
        Racing_2019_P.ResettableDelay50ms_InitialCond;
    }
  }

  Racing_2019_PrevZCX.ResettableDelay50ms_Reset_ZCE = Racing_2019_B.StartUpAND;
  Racing_2019_B.ResettableDelay50ms = Racing_2019_DW.ResettableDelay50ms_DSTATE
    [0];
  Racing_2019_B.EnableToggleNOT = !Racing_2019_B.EnableToggle;
  zcEvent = (Racing_2019_B.EnableToggleNOT &&
             (Racing_2019_PrevZCX.ResettableDelay50ms2_Reset_ZCE != POS_ZCSIG));
  if (zcEvent) {
    for (i = 0; i < 5; i++) {
      Racing_2019_DW.ResettableDelay50ms2_DSTATE[i] =
        Racing_2019_P.ResettableDelay50ms2_InitialCon;
    }
  }

  Racing_2019_PrevZCX.ResettableDelay50ms2_Reset_ZCE =
    Racing_2019_B.EnableToggleNOT;
  Racing_2019_B.ResettableDelay50ms2 =
    Racing_2019_DW.ResettableDelay50ms2_DSTATE[0];
  Racing_2019_B.TSOff = !Racing_2019_B.Compare_gl;
  zcEvent = (Racing_2019_B.TSOff &&
             (Racing_2019_PrevZCX.ResettableDelay50ms1_Reset_ZCE != POS_ZCSIG));
  if (zcEvent) {
    for (i = 0; i < 5; i++) {
      Racing_2019_DW.ResettableDelay50ms1_DSTATE[i] =
        Racing_2019_P.ResettableDelay50ms1_InitialCon;
    }
  }

  Racing_2019_PrevZCX.ResettableDelay50ms1_Reset_ZCE = Racing_2019_B.TSOff;
  Racing_2019_B.ResettableDelay50ms1 =
    Racing_2019_DW.ResettableDelay50ms1_DSTATE[0];
  Racing_2019_B.StartUpOR = (Racing_2019_B.ResettableDelay50ms2 ||
    Racing_2019_B.ResettableDelay50ms1);
  Racing_2019_B.Memory_c = Racing_2019_DW.Memory_PreviousInput_c;
  zcEvent = Racing_2019_B.ResettableDelay50ms;
  i = zcEvent;
  zcEvent = Racing_2019_B.StartUpOR;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  zcEvent = Racing_2019_B.Memory_c;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  Racing_2019_B.Logic[0U] = Racing_2019_P.Logic_table[(uint32_T)i];
  Racing_2019_B.Logic[1U] = Racing_2019_P.Logic_table[i + 8U];
  Racing_2019_B.StartUpProc = (Racing_2019_B.Logic[0] ||
    (Racing_2019_P.Start_Up_Hack != 0.0));
  Racing_2019_B.LogicalOperator_o = !Racing_2019_B.to100Hz14;
  Racing_2019_B.SensorError = (Racing_2019_B.LogicalOperator_o ||
    (Racing_2019_P.Sensor_Error_Bypass != 0.0));
  Racing_2019_B.LogicalOperator1 = !Racing_2019_B.to100Hz15;
  Racing_2019_B.Plausibility = (Racing_2019_B.LogicalOperator1 ||
    (Racing_2019_P.Plausibility_Bypass != 0.0));
  if (Racing_2019_M->Timing.RateInteraction.TID2_3 == 1) {
    Racing_2019_B.BSPDState = Racing_2019_DW.to100Hz16_Buffer0;
    Racing_2019_B.to100Hz17 = Racing_2019_DW.to100Hz17_Buffer0;
  }

  Racing_2019_B.BSPDState_h = (Racing_2019_B.BSPDState ||
    (Racing_2019_P.BSPD_State_Bypass != 0.0));
  Racing_2019_B.LogicalOperator2_h = !Racing_2019_B.to100Hz17;
  Racing_2019_B.TSALSafeState = (Racing_2019_B.LogicalOperator2_h ||
    (Racing_2019_P.Safe_State_Bypass != 0.0));
  Racing_2019_B.LogicalOperator3 = !Racing_2019_B.to100Hz18;
  Racing_2019_B.BMSStatus = (Racing_2019_B.LogicalOperator3 ||
    (Racing_2019_P.BMS_Status_Bypass != 0.0));
  Racing_2019_B.EnableAND = (Racing_2019_B.DashCANTx && Racing_2019_B.AuxCANTx &&
    Racing_2019_B.AccuCANTx && Racing_2019_B.TorqueCANTx &&
    Racing_2019_B.CANChannelsStatus && Racing_2019_B.DashCANRx &&
    Racing_2019_B.AuxCANRx && Racing_2019_B.AccuCANRx &&
    Racing_2019_B.InvLEFTCANRx && Racing_2019_B.InvRIGHTCANRx &&
    Racing_2019_B.StartUpProc && Racing_2019_B.SensorError &&
    Racing_2019_B.Plausibility && Racing_2019_B.BSPDState_h &&
    Racing_2019_B.TSALSafeState && Racing_2019_B.BMSStatus);
  Racing_2019_B.LogicalOperator16 = !(Racing_2019_P.Enable_Kill != 0.0);
  Racing_2019_B.LogicalOperator15 = (Racing_2019_B.EnableAND &&
    Racing_2019_B.LogicalOperator16);
  zcEvent = ((!Racing_2019_B.LogicalOperator15) &&
             (Racing_2019_PrevZCX.ResettableDelay15s_Reset_ZCE != ZERO_ZCSIG));
  if (zcEvent) {
    for (i = 0; i < 150; i++) {
      Racing_2019_DW.ResettableDelay15s_DSTATE[i] =
        Racing_2019_P.ResettableDelay15s_InitialCondi;
    }
  }

  Racing_2019_PrevZCX.ResettableDelay15s_Reset_ZCE =
    Racing_2019_B.LogicalOperator15;
  Racing_2019_B.ResettableDelay15s = Racing_2019_DW.ResettableDelay15s_DSTATE[0];
  Racing_2019_B.DataTypeConversion_g5 = Racing_2019_B.ResettableDelay15s;
  dio_tp4_digout_write(DIO_TP4_1_MODULE_ADDR, 1, DIO_TP4_MASK_CH5, (UInt16)
                       (Racing_2019_B.DataTypeConversion_g5 << 4));
  Racing_2019_B.DataTypeConversion3_d = Racing_2019_B.DataTypeConversion_g5;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(ENABLE_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion3_d);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.BuzzerSet = (Racing_2019_B.LogicalOperator15 &&
    Racing_2019_B.StartUpProc);
  Racing_2019_B.BuzerReset = !Racing_2019_B.StartUpProc;
  Racing_2019_B.Memory_du = Racing_2019_DW.Memory_PreviousInput_eb;
  zcEvent = Racing_2019_B.BuzzerSet;
  i = zcEvent;
  zcEvent = Racing_2019_B.BuzerReset;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  zcEvent = Racing_2019_B.Memory_du;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  Racing_2019_B.Logic_ok[0U] = Racing_2019_P.Logic_table_f[(uint32_T)i];
  Racing_2019_B.Logic_ok[1U] = Racing_2019_P.Logic_table_f[i + 8U];
  zcEvent = (Racing_2019_B.Logic_ok[0] &&
             (Racing_2019_PrevZCX.ResettableDelay1500ms_Reset_ZCE != POS_ZCSIG));
  if (zcEvent) {
    for (i = 0; i < 150; i++) {
      Racing_2019_DW.ResettableDelay1500ms_DSTATE[i] =
        Racing_2019_P.ResettableDelay1500ms_InitialCo;
    }
  }

  Racing_2019_PrevZCX.ResettableDelay1500ms_Reset_ZCE = Racing_2019_B.Logic_ok[0];
  Racing_2019_B.ResettableDelay1500ms =
    Racing_2019_DW.ResettableDelay1500ms_DSTATE[0];
  Racing_2019_B.BuzzerAND = ((Racing_2019_P.Buzzer_Silent != 0.0) &&
    Racing_2019_B.Logic_ok[0] && (Racing_2019_B.ResettableDelay1500ms != 0.0));
  Racing_2019_B.LogicalOperator13_h = ((Racing_2019_P.Buzzer != 0.0) ||
    Racing_2019_B.BuzzerAND);
  if (Racing_2019_M->Timing.RateInteraction.TID2_3 == 1) {
    Racing_2019_B.to10Hz1 = Racing_2019_B.LogicalOperator13_h;
    Racing_2019_B.to10Hz3 = Racing_2019_B.ResettableDelay15s;
  }

  Racing_2019_B.DataTypeConversion7_d = Racing_2019_B.AccuCANRx;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(ENABLE_Accu_CAN_Rx_Index_UsbFlRec,
      (Int32)Racing_2019_B.DataTypeConversion7_d);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion8_g = Racing_2019_B.InvLEFTCANRx;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(ENABLE_Inv_LEFT_CAN_Rx_Index_UsbFlRec,
      (Int32)Racing_2019_B.DataTypeConversion8_g);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion9_k = Racing_2019_B.InvRIGHTCANRx;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(ENABLE_Inv_RIGHT_CAN_Rx_Index_UsbFlRec,
      (Int32)Racing_2019_B.DataTypeConversion9_k);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion10_ic = Racing_2019_B.SensorError;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(ENABLE_Sensor_Error_Index_UsbFlRec,
      (Int32)Racing_2019_B.DataTypeConversion10_ic);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion11_e = Racing_2019_B.Plausibility;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(ENABLE_Plausibility_Index_UsbFlRec,
      (Int32)Racing_2019_B.DataTypeConversion11_e);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion12_h = Racing_2019_B.BSPDState_h;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(ENABLE_BSPD_State_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion12_h);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion13_kk = Racing_2019_B.TSALSafeState;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(ENABLE_TSAL_Safe_State_Index_UsbFlRec,
      (Int32)Racing_2019_B.DataTypeConversion13_kk);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion14_po = Racing_2019_B.BMSStatus;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(ENABLE_BMS_Status_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion14_po);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion_k = Racing_2019_B.DashCANTx;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(ENABLE_Dash_CAN_Tx_Index_UsbFlRec,
      (Int32)Racing_2019_B.DataTypeConversion_k);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion1_n = Racing_2019_B.AuxCANTx;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(ENABLE_Aux_CAN_Tx_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion1_n);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion2_jh = Racing_2019_B.AccuCANTx;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(ENABLE_Accu_CAN_Tx_Index_UsbFlRec,
      (Int32)Racing_2019_B.DataTypeConversion2_jh);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion3_h = Racing_2019_B.TorqueCANTx;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(ENABLE_Torque_CAN_Tx_Index_UsbFlRec,
      (Int32)Racing_2019_B.DataTypeConversion3_h);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion4_je = Racing_2019_B.CANChannelsStatus;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(ENABLE_CAN_Status_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion4_je);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion5_ig = Racing_2019_B.DashCANRx;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(ENABLE_Dash_CAN_Rx_Index_UsbFlRec,
      (Int32)Racing_2019_B.DataTypeConversion5_ig);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion6_dy = Racing_2019_B.AuxCANRx;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(ENABLE_Aux_CAN_Rx_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion6_dy);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }
}

void Racing_2019_update2(void)
{
  int_T idxDelay;
  Racing_2019_DW.ResettableDelay50ms_DSTATE[0] =
    Racing_2019_DW.ResettableDelay50ms_DSTATE[1];
  Racing_2019_DW.ResettableDelay50ms_DSTATE[1] =
    Racing_2019_DW.ResettableDelay50ms_DSTATE[2];
  Racing_2019_DW.ResettableDelay50ms_DSTATE[2] =
    Racing_2019_DW.ResettableDelay50ms_DSTATE[3];
  Racing_2019_DW.ResettableDelay50ms_DSTATE[3] =
    Racing_2019_DW.ResettableDelay50ms_DSTATE[4];
  Racing_2019_DW.ResettableDelay50ms_DSTATE[4] = Racing_2019_B.StartUpAND;
  Racing_2019_DW.ResettableDelay50ms2_DSTATE[0] =
    Racing_2019_DW.ResettableDelay50ms2_DSTATE[1];
  Racing_2019_DW.ResettableDelay50ms2_DSTATE[1] =
    Racing_2019_DW.ResettableDelay50ms2_DSTATE[2];
  Racing_2019_DW.ResettableDelay50ms2_DSTATE[2] =
    Racing_2019_DW.ResettableDelay50ms2_DSTATE[3];
  Racing_2019_DW.ResettableDelay50ms2_DSTATE[3] =
    Racing_2019_DW.ResettableDelay50ms2_DSTATE[4];
  Racing_2019_DW.ResettableDelay50ms2_DSTATE[4] = Racing_2019_B.EnableToggleNOT;
  Racing_2019_DW.ResettableDelay50ms1_DSTATE[0] =
    Racing_2019_DW.ResettableDelay50ms1_DSTATE[1];
  Racing_2019_DW.ResettableDelay50ms1_DSTATE[1] =
    Racing_2019_DW.ResettableDelay50ms1_DSTATE[2];
  Racing_2019_DW.ResettableDelay50ms1_DSTATE[2] =
    Racing_2019_DW.ResettableDelay50ms1_DSTATE[3];
  Racing_2019_DW.ResettableDelay50ms1_DSTATE[3] =
    Racing_2019_DW.ResettableDelay50ms1_DSTATE[4];
  Racing_2019_DW.ResettableDelay50ms1_DSTATE[4] = Racing_2019_B.TSOff;
  Racing_2019_DW.Memory_PreviousInput_c = Racing_2019_B.Logic[0];
  for (idxDelay = 0; idxDelay < 149; idxDelay++) {
    Racing_2019_DW.ResettableDelay15s_DSTATE[idxDelay] =
      Racing_2019_DW.ResettableDelay15s_DSTATE[idxDelay + 1];
    Racing_2019_DW.ResettableDelay1500ms_DSTATE[idxDelay] =
      Racing_2019_DW.ResettableDelay1500ms_DSTATE[idxDelay + 1];
  }

  Racing_2019_DW.ResettableDelay15s_DSTATE[149] =
    Racing_2019_B.LogicalOperator15;
  Racing_2019_DW.Memory_PreviousInput_eb = Racing_2019_B.Logic_ok[0];
  Racing_2019_DW.ResettableDelay1500ms_DSTATE[149] =
    Racing_2019_P.Constant9_Value;
  Racing_2019_DW.to1kHz_Buffer0 = Racing_2019_B.ResettableDelay15s;
}

void Racing_2019_output3(void)
{
  boolean_T zcEvent;
  int32_T i;
  real_T tmp;
  real32_T u0;
  real32_T u1;
  real32_T u2;
  uint8_T u0_0;
  uint8_T u1_0;
  uint8_T u2_0;
  (Racing_2019_M->Timing.RateInteraction.TID3_4)++;
  if ((Racing_2019_M->Timing.RateInteraction.TID3_4) > 1) {
    Racing_2019_M->Timing.RateInteraction.TID3_4 = 0;
  }

  {
    UInt32 CAN_Msg[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    Float32 delayTime = 0.0;
    can_tp1_msg_read(can_type1_msg_M2[CANTP1_M2_C1_TX_STD_0XC9]);
    if (can_type1_msg_M2[CANTP1_M2_C1_TX_STD_0XC9]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_TX_STD_0XC9]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_TX_STD_0XC9]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_TX_STD_0XC9]->timestamp > 0.0) {
      Racing_2019_B.SFunction1_k = (real_T)
        can_type1_msg_M2[CANTP1_M2_C1_TX_STD_0XC9]->processed;
    }

    {
      rtican_Signal_t CAN_Sgn;
      CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_P.Constant1_Value_h ) + 0.5);
      CAN_Sgn.UnsignedSgn &= 0x000000FF;
      CAN_Msg[0] |= CAN_Sgn.SgnBytes.Byte0;
    }

    can_tp1_msg_send(can_type1_msg_M2[CANTP1_M2_C1_TX_STD_0XC9], 1, &(CAN_Msg[0]),
                     delayTime);
  }

  if ((rt_ZCFcn(ANY_ZERO_CROSSING,&Racing_2019_PrevZCX.BMS_CAN_201_Reset_ZCE,
                (Racing_2019_B.SFunction1_k)) != NO_ZCEVENT) ||
      (Racing_2019_B.SFunction1_k != 0.0)) {
    for (i = 0; i < 10; i++) {
      Racing_2019_DW.BMS_CAN_201_DSTATE[i] =
        Racing_2019_P.BMS_CAN_201_InitialCondition;
    }
  }

  Racing_2019_B.BMS_CAN_201 = Racing_2019_DW.BMS_CAN_201_DSTATE[0];
  tmp = floor(Racing_2019_B.AUX3141kHzto10Hz);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 256.0);
  }

  Racing_2019_B.DataTypeConversion12_n = (uint8_T)(tmp < 0.0 ? (int32_T)(uint8_T)
    -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Aux_CAN_314_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion12_n);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X165]);
    if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X165]->processed) {
      can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X165]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X165]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X165]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X165]->processed) {
        Racing_2019_B.SFunction1_o4_n = (real_T)
          can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X165]->processed;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X165]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_dq = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_pi = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_gi = ((UInt16) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X165]->processed) {
      Racing_2019_B.SFunction1_o4_n = 0.0;
    }
  }

  if ((rt_ZCFcn(ANY_ZERO_CROSSING,&Racing_2019_PrevZCX.AUX_CAN_357_Reset_ZCE,
                (Racing_2019_B.SFunction1_o4_n)) != NO_ZCEVENT) ||
      (Racing_2019_B.SFunction1_o4_n != 0.0)) {
    for (i = 0; i < 20; i++) {
      Racing_2019_DW.AUX_CAN_357_DSTATE[i] =
        Racing_2019_P.AUX_CAN_357_InitialCondition;
    }
  }

  Racing_2019_B.AUX_CAN_357 = Racing_2019_DW.AUX_CAN_357_DSTATE[0];
  tmp = floor(Racing_2019_B.AUX_CAN_357);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 256.0);
  }

  Racing_2019_B.DataTypeConversion13_m = (uint8_T)(tmp < 0.0 ? (int32_T)(uint8_T)
    -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Aux_CAN_357_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion13_m);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X180]);
    if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X180]->processed) {
      can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X180]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X180]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X180]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X180]->processed) {
        Racing_2019_B.SFunction1_o6_jk = (real_T)
          can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X180]->processed;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X180]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_mv = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_mt = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte0 = CAN_Msg[4];
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          Racing_2019_B.SFunction1_o3_bp = ((UInt8) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte0 = CAN_Msg[5];
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          Racing_2019_B.SFunction1_o4_lg = ((UInt8) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte0 = CAN_Msg[6];
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          Racing_2019_B.SFunction1_o5_gf = ((UInt8) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X180]->processed) {
      Racing_2019_B.SFunction1_o6_jk = 0.0;
    }
  }

  if ((rt_ZCFcn(ANY_ZERO_CROSSING,&Racing_2019_PrevZCX.AUX_CAN_384_Reset_ZCE,
                (Racing_2019_B.SFunction1_o6_jk)) != NO_ZCEVENT) ||
      (Racing_2019_B.SFunction1_o6_jk != 0.0)) {
    for (i = 0; i < 20; i++) {
      Racing_2019_DW.AUX_CAN_384_DSTATE[i] =
        Racing_2019_P.AUX_CAN_384_InitialCondition;
    }
  }

  Racing_2019_B.AUX_CAN_384 = Racing_2019_DW.AUX_CAN_384_DSTATE[0];
  tmp = floor(Racing_2019_B.AUX_CAN_384);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 256.0);
  }

  Racing_2019_B.DataTypeConversion14_bw = (uint8_T)(tmp < 0.0 ? (int32_T)
    (uint8_T)-(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Aux_CAN_412_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion14_bw);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion3_oi = Racing_2019_B.SFunction1_o2_pi;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Aux_Thermistor_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion3_oi);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Compare_c1u = (Racing_2019_B.SFunction1_o3_bp ==
    Racing_2019_P.BSPD_Status_const);
  Racing_2019_B.DataTypeConversion10_h = Racing_2019_B.Compare_c1u;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(BSPD_Status_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion10_h);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion9 = Racing_2019_B.SFunction1_o3_gi;
  Racing_2019_B.Aux_Core_Temp = (3.3F * Racing_2019_B.DataTypeConversion9 /
    4096.0F - 0.76F) * 1000.0F / 2.5F + 25.0F;
  u0 = (real32_T)floor(Racing_2019_B.Aux_Core_Temp);
  if (rtIsNaNF(u0) || rtIsInfF(u0)) {
    u0 = 0.0F;
  } else {
    u0 = (real32_T)fmod(u0, 65536.0F);
  }

  Racing_2019_B.DataTypeConversion_b = (uint16_T)(u0 < 0.0F ? (int32_T)(uint16_T)
    -(int16_T)(uint16_T)-u0 : (int32_T)(uint16_T)u0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Core_Aux_Thermistor_Index_UsbFlRec,
      (Int32)Racing_2019_B.DataTypeConversion_b);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion4_e = Racing_2019_B.SFunction1_o1_dq;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(DCDC_Thermistor_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion4_e);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Right_Flow_Ticks_Milliseconds1 = (uint32_T)
    Racing_2019_P.Right_Flow_Ticks_Milliseconds1_ *
    Racing_2019_B.SFunction1_o2_mt;
  Racing_2019_B.DataTypeConversion6_g = (uint16_T)
    (Racing_2019_B.Right_Flow_Ticks_Milliseconds1 >> 3);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Flow_Meter_Left_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion6_g);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Right_Flow_Ticks_Milliseconds = (uint32_T)
    Racing_2019_P.Right_Flow_Ticks_Milliseconds_G *
    Racing_2019_B.SFunction1_o1_mv;
  Racing_2019_B.DataTypeConversion5_l = (uint16_T)
    (Racing_2019_B.Right_Flow_Ticks_Milliseconds >> 3);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Flow_Meter_Right_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion5_l);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Compare_av = (Racing_2019_B.SFunction1_o5_gf ==
    Racing_2019_P.Safe_State_const);
  Racing_2019_B.DataTypeConversion11_jf = Racing_2019_B.Compare_av;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Safe_State_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion11_jf);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.AUXCANRxErrorOR = ((Racing_2019_B.AUX_CAN_384 != 0.0) &&
    (Racing_2019_B.AUX_CAN_357 != 0.0) && (Racing_2019_B.AUX3141kHzto10Hz != 0.0));
  Racing_2019_B.AUX_CAN_357_Counter =
    Racing_2019_DW.AUX_CAN_357_Counter_PreviousInp;
  Racing_2019_B.AUX_CAN_384_Counter =
    Racing_2019_DW.AUX_CAN_384_Counter_PreviousInp;
  Racing_2019_B.DataTypeConversion2_av = (Racing_2019_B.SFunction1_o4_n != 0.0);
  Racing_2019_B.UnitDelay_dq = Racing_2019_DW.UnitDelay_DSTATE_cl;
  switch ((int32_T)Racing_2019_P.EdgeDetector1_model_hq) {
   case 1:
    Racing_2019_B.MultiportSwitch_mk[0] = Racing_2019_P.posedge_Value_p1[0];
    Racing_2019_B.MultiportSwitch_mk[1] = Racing_2019_P.posedge_Value_p1[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_mk[0] = Racing_2019_P.negedge_Value_m2l[0];
    Racing_2019_B.MultiportSwitch_mk[1] = Racing_2019_P.negedge_Value_m2l[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_mk[0] = Racing_2019_P.eitheredge_Value_er[0];
    Racing_2019_B.MultiportSwitch_mk[1] = Racing_2019_P.eitheredge_Value_er[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_mk[0],
    Racing_2019_B.DataTypeConversion2_av, Racing_2019_B.UnitDelay_dq,
    &Racing_2019_B.POSITIVEEdge_d);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_mk[1],
    Racing_2019_B.DataTypeConversion2_av, Racing_2019_B.UnitDelay_dq,
    &Racing_2019_B.NEGATIVEEdge_gu);
  Racing_2019_B.LogicalOperator1_pc =
    (Racing_2019_B.POSITIVEEdge_d.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_gu.RelationalOperator1);
  Racing_2019_B.DataTypeConversion1_gq = Racing_2019_B.LogicalOperator1_pc;
  Racing_2019_B.Add2_a = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion1_gq + Racing_2019_B.AUX_CAN_357_Counter);
  Racing_2019_B.DataTypeConversion2_nr = (Racing_2019_B.SFunction1_o6_jk != 0.0);
  Racing_2019_B.UnitDelay_eo = Racing_2019_DW.UnitDelay_DSTATE_do;
  switch ((int32_T)Racing_2019_P.EdgeDetector2_model_j) {
   case 1:
    Racing_2019_B.MultiportSwitch_a[0] = Racing_2019_P.posedge_Value_nm[0];
    Racing_2019_B.MultiportSwitch_a[1] = Racing_2019_P.posedge_Value_nm[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_a[0] = Racing_2019_P.negedge_Value_fi4[0];
    Racing_2019_B.MultiportSwitch_a[1] = Racing_2019_P.negedge_Value_fi4[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_a[0] = Racing_2019_P.eitheredge_Value_b[0];
    Racing_2019_B.MultiportSwitch_a[1] = Racing_2019_P.eitheredge_Value_b[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_a[0],
    Racing_2019_B.DataTypeConversion2_nr, Racing_2019_B.UnitDelay_eo,
    &Racing_2019_B.POSITIVEEdge_o4);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_a[1],
    Racing_2019_B.DataTypeConversion2_nr, Racing_2019_B.UnitDelay_eo,
    &Racing_2019_B.NEGATIVEEdge_je);
  Racing_2019_B.LogicalOperator1_iq =
    (Racing_2019_B.POSITIVEEdge_o4.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_je.RelationalOperator1);
  Racing_2019_B.DataTypeConversion2_i3 = Racing_2019_B.LogicalOperator1_iq;
  Racing_2019_B.Add3_p = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion2_i3 + Racing_2019_B.AUX_CAN_384_Counter);
  Racing_2019_B.Compare_fn = (Racing_2019_B.SFunction1_o4_lg ==
    Racing_2019_P.Enable_Compare_const);
  Racing_2019_B.Gain_c = Racing_2019_P.Gain_Gain_a *
    Racing_2019_P.Pump_Signal_Left;
  u0 = Racing_2019_B.Gain_c;
  u1 = Racing_2019_P.Saturation_LowerSat;
  u2 = Racing_2019_P.Saturation_UpperSat;
  if (u0 > u2) {
    Racing_2019_B.Saturation = u2;
  } else if (u0 < u1) {
    Racing_2019_B.Saturation = u1;
  } else {
    Racing_2019_B.Saturation = u0;
  }

  Racing_2019_B.Compare_i3 = (Racing_2019_B.IGBTTempto10Hz <=
    Racing_2019_P.CompareToConstant3_const);
  if (Racing_2019_B.Compare_i3) {
    Racing_2019_B.Switch_lw = Racing_2019_B.IGBTTempto10Hz;
  } else {
    Racing_2019_B.Switch_lw = Racing_2019_P.Constant10_Value;
  }

  Racing_2019_B.Compare_i21 = (Racing_2019_B.Switch_lw >=
    Racing_2019_P.IGBT_Temp_High_Threshold);
  Racing_2019_B.Compare_ke = (Racing_2019_B.Switch_lw <=
    Racing_2019_P.IGBT_Temp_Low_Threshold);
  Racing_2019_B.Memory_e = Racing_2019_DW.Memory_PreviousInput_b;
  zcEvent = Racing_2019_B.Compare_i21;
  i = zcEvent;
  zcEvent = Racing_2019_B.Compare_ke;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  zcEvent = Racing_2019_B.Memory_e;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  Racing_2019_B.Logic_k[0U] = Racing_2019_P.Logic_table_p[(uint32_T)i];
  Racing_2019_B.Logic_k[1U] = Racing_2019_P.Logic_table_p[i + 8U];
  Racing_2019_B.LogicalOperator2_m = ((Racing_2019_P.Pump_Left_ON != 0.0) ||
    Racing_2019_B.Logic_k[0]);
  Racing_2019_B.LogicalOperator1_dk = (Racing_2019_B.LogicalOperator2_m &&
    (Racing_2019_P.Pump_Left_Enable != 0.0));
  if (Racing_2019_B.LogicalOperator1_dk) {
    Racing_2019_B.Switch1 = Racing_2019_B.Saturation;
  } else {
    Racing_2019_B.Switch1 = Racing_2019_P.Constant13_Value_m;
  }

  Racing_2019_B.RateTransition1 = Racing_2019_B.Switch1;
  tmp = floor(Racing_2019_B.RateTransition1);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 256.0);
  }

  Racing_2019_B.DataTypeConversion3_i = (uint8_T)(tmp < 0.0 ? (int32_T)(uint8_T)
    -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp);
  Racing_2019_B.Gain1 = Racing_2019_P.Gain1_Gain *
    Racing_2019_P.Pump_Signal_Right;
  u0 = Racing_2019_B.Gain1;
  u1 = Racing_2019_P.Saturation1_LowerSat;
  u2 = Racing_2019_P.Saturation1_UpperSat;
  if (u0 > u2) {
    Racing_2019_B.Saturation1 = u2;
  } else if (u0 < u1) {
    Racing_2019_B.Saturation1 = u1;
  } else {
    Racing_2019_B.Saturation1 = u0;
  }

  Racing_2019_B.Compare_mt = (Racing_2019_B.IGBTTempto10Hz_f <=
    Racing_2019_P.CompareToConstant6_const);
  if (Racing_2019_B.Compare_mt) {
    Racing_2019_B.Switch2_g = Racing_2019_B.IGBTTempto10Hz_f;
  } else {
    Racing_2019_B.Switch2_g = Racing_2019_P.Constant15_Value;
  }

  Racing_2019_B.Compare_dg = (Racing_2019_B.Switch2_g >=
    Racing_2019_P.IGBT_Temp_High_Threshold);
  Racing_2019_B.Compare_p1 = (Racing_2019_B.Switch2_g <=
    Racing_2019_P.IGBT_Temp_Low_Threshold);
  Racing_2019_B.Memory_d = Racing_2019_DW.Memory_PreviousInput_m;
  zcEvent = Racing_2019_B.Compare_dg;
  i = zcEvent;
  zcEvent = Racing_2019_B.Compare_p1;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  zcEvent = Racing_2019_B.Memory_d;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  Racing_2019_B.Logic_m[0U] = Racing_2019_P.Logic_table_h[(uint32_T)i];
  Racing_2019_B.Logic_m[1U] = Racing_2019_P.Logic_table_h[i + 8U];
  Racing_2019_B.LogicalOperator4 = ((Racing_2019_P.Pump_Right_ON != 0.0) ||
    Racing_2019_B.Logic_m[0]);
  Racing_2019_B.LogicalOperator3_he = (Racing_2019_B.LogicalOperator4 &&
    (Racing_2019_P.Pump_Right_Enable != 0.0));
  if (Racing_2019_B.LogicalOperator3_he) {
    Racing_2019_B.Switch3 = Racing_2019_B.Saturation1;
  } else {
    Racing_2019_B.Switch3 = Racing_2019_P.Constant18_Value;
  }

  Racing_2019_B.RateTransition2 = Racing_2019_B.Switch3;
  tmp = floor(Racing_2019_B.RateTransition2);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 256.0);
  }

  Racing_2019_B.DataTypeConversion4_o = (uint8_T)(tmp < 0.0 ? (int32_T)(uint8_T)
    -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp);
  if (Racing_2019_M->Timing.RateInteraction.TID3_4 == 1) {
    Racing_2019_B.RateTransition3 = Racing_2019_DW.RateTransition3_Buffer0;
  }

  tmp = floor(Racing_2019_B.RateTransition3);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 256.0);
  }

  Racing_2019_B.DataTypeConversion5_i = (uint8_T)(tmp < 0.0 ? (int32_T)(uint8_T)
    -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp);
  u0_0 = Racing_2019_P.Fans_Left_PWM;
  u1_0 = Racing_2019_P.Saturation3_LowerSat;
  u2_0 = Racing_2019_P.Saturation3_UpperSat;
  if (u0_0 > u2_0) {
    Racing_2019_B.Saturation3 = u2_0;
  } else if (u0_0 < u1_0) {
    Racing_2019_B.Saturation3 = u1_0;
  } else {
    Racing_2019_B.Saturation3 = u0_0;
  }

  Racing_2019_B.Compare_jf = (Racing_2019_B.IGBTTempto10Hz <=
    Racing_2019_P.CompareToConstant14_const);
  if (Racing_2019_B.Compare_jf) {
    Racing_2019_B.Switch4 = Racing_2019_B.IGBTTempto10Hz;
  } else {
    Racing_2019_B.Switch4 = Racing_2019_P.Constant1_Value_e;
  }

  Racing_2019_B.Compare_bv = (Racing_2019_B.Switch4 >=
    Racing_2019_P.IGBT_Temp_High_Threshold);
  Racing_2019_B.Compare_ak = (Racing_2019_B.Switch4 <=
    Racing_2019_P.IGBT_Temp_Low_Threshold);
  Racing_2019_B.Memory_b = Racing_2019_DW.Memory_PreviousInput_d;
  zcEvent = Racing_2019_B.Compare_bv;
  i = zcEvent;
  zcEvent = Racing_2019_B.Compare_ak;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  zcEvent = Racing_2019_B.Memory_b;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  Racing_2019_B.Logic_b[0U] = Racing_2019_P.Logic_table_n[(uint32_T)i];
  Racing_2019_B.Logic_b[1U] = Racing_2019_P.Logic_table_n[i + 8U];
  Racing_2019_B.LogicalOperator13 = ((Racing_2019_P.Fans_Left_ON != 0.0) ||
    Racing_2019_B.Logic_b[0]);
  Racing_2019_B.LogicalOperator12_e = (Racing_2019_B.LogicalOperator13 &&
    (Racing_2019_P.Fans_Left_Enable != 0.0));
  if (Racing_2019_B.LogicalOperator12_e) {
    Racing_2019_B.Switch6 = Racing_2019_B.Saturation3;
  } else {
    Racing_2019_B.Switch6 = Racing_2019_P.Constant24_Value;
  }

  Racing_2019_B.RateTransition4 = Racing_2019_B.Switch6;
  tmp = floor(Racing_2019_B.RateTransition4);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 256.0);
  }

  Racing_2019_B.DataTypeConversion6_i = (uint8_T)(tmp < 0.0 ? (int32_T)(uint8_T)
    -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp);
  u0_0 = Racing_2019_P.Fans_Right_PWM;
  u1_0 = Racing_2019_P.Saturation4_LowerSat;
  u2_0 = Racing_2019_P.Saturation4_UpperSat;
  if (u0_0 > u2_0) {
    Racing_2019_B.Saturation4 = u2_0;
  } else if (u0_0 < u1_0) {
    Racing_2019_B.Saturation4 = u1_0;
  } else {
    Racing_2019_B.Saturation4 = u0_0;
  }

  Racing_2019_B.Compare_ji = (Racing_2019_B.IGBTTempto10Hz_f <=
    Racing_2019_P.CompareToConstant17_const);
  if (Racing_2019_B.Compare_ji) {
    Racing_2019_B.Switch7 = Racing_2019_B.IGBTTempto10Hz_f;
  } else {
    Racing_2019_B.Switch7 = Racing_2019_P.Constant26_Value;
  }

  Racing_2019_B.Compare_ns = (Racing_2019_B.Switch7 >=
    Racing_2019_P.IGBT_Temp_High_Threshold);
  Racing_2019_B.Compare_a2 = (Racing_2019_B.Switch7 <=
    Racing_2019_P.IGBT_Temp_Low_Threshold);
  Racing_2019_B.Memory_i = Racing_2019_DW.Memory_PreviousInput_k;
  zcEvent = Racing_2019_B.Compare_ns;
  i = zcEvent;
  zcEvent = Racing_2019_B.Compare_a2;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  zcEvent = Racing_2019_B.Memory_i;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  Racing_2019_B.Logic_o[0U] = Racing_2019_P.Logic_table_b[(uint32_T)i];
  Racing_2019_B.Logic_o[1U] = Racing_2019_P.Logic_table_b[i + 8U];
  Racing_2019_B.LogicalOperator15_l = ((Racing_2019_P.Fans_Right_ON != 0.0) ||
    Racing_2019_B.Logic_o[0]);
  Racing_2019_B.LogicalOperator14 = (Racing_2019_B.LogicalOperator15_l &&
    (Racing_2019_P.Fans_Right_Enable != 0.0));
  if (Racing_2019_B.LogicalOperator14) {
    Racing_2019_B.Switch8 = Racing_2019_B.Saturation4;
  } else {
    Racing_2019_B.Switch8 = Racing_2019_P.Constant29_Value;
  }

  Racing_2019_B.RateTransition5 = Racing_2019_B.Switch8;
  tmp = floor(Racing_2019_B.RateTransition5);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 256.0);
  }

  Racing_2019_B.DataTypeConversion7_l = (uint8_T)(tmp < 0.0 ? (int32_T)(uint8_T)
    -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp);
  if (Racing_2019_M->Timing.RateInteraction.TID3_4 == 1) {
    Racing_2019_B.RateTransition6 = Racing_2019_DW.RateTransition6_Buffer0;
  }

  Racing_2019_B.Gain_a = (uint8_T)(Racing_2019_B.RateTransition6 ? (int32_T)
    Racing_2019_P.Gain_Gain_f : 0);
  Racing_2019_B.DataTypeConversion8_o = (uint8_T)((uint32_T)Racing_2019_B.Gain_a
    >> 4);
  Racing_2019_B.RateTransition7 = Racing_2019_B.LogicalOperator12_e;
  Racing_2019_B.Gain1_g = (uint8_T)(Racing_2019_B.RateTransition7 ? (int32_T)
    Racing_2019_P.Gain1_Gain_j : 0);
  Racing_2019_B.DataTypeConversion9_n = (uint8_T)((uint32_T)
    Racing_2019_B.Gain1_g >> 4);
  Racing_2019_B.RateTransition8 = Racing_2019_B.LogicalOperator14;
  Racing_2019_B.Gain2_i = (uint8_T)(Racing_2019_B.RateTransition8 ? (int32_T)
    Racing_2019_P.Gain2_Gain : 0);
  Racing_2019_B.DataTypeConversion10_a = (uint8_T)((uint32_T)
    Racing_2019_B.Gain2_i >> 4);

  {
    UInt32 CAN_Msg[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    Float32 delayTime = 0.0;
    can_tp1_msg_read(can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0X19C]);
    if (can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0X19C]->processed) {
      can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0X19C]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0X19C]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0X19C]->timestamp > 0.0) {
      Racing_2019_B.SFunction1_ks = (real_T)
        can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0X19C]->processed;
    }

    {
      rtican_Signal_t CAN_Sgn;
      CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.DataTypeConversion3_i ) +
        0.5);
      CAN_Sgn.UnsignedSgn &= 0x000000FF;
      CAN_Msg[0] |= CAN_Sgn.SgnBytes.Byte0;
      CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.DataTypeConversion4_o ) +
        0.5);
      CAN_Sgn.UnsignedSgn &= 0x000000FF;
      CAN_Msg[1] |= CAN_Sgn.SgnBytes.Byte0;
      CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.DataTypeConversion5_i ) +
        0.5);
      CAN_Sgn.UnsignedSgn &= 0x000000FF;
      CAN_Msg[2] |= CAN_Sgn.SgnBytes.Byte0;
      CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.DataTypeConversion6_i ) +
        0.5);
      CAN_Sgn.UnsignedSgn &= 0x000000FF;
      CAN_Msg[3] |= CAN_Sgn.SgnBytes.Byte0;
      CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.DataTypeConversion7_l ) +
        0.5);
      CAN_Sgn.UnsignedSgn &= 0x000000FF;
      CAN_Msg[4] |= CAN_Sgn.SgnBytes.Byte0;
      CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.DataTypeConversion8_o ) +
        0.5);
      CAN_Sgn.UnsignedSgn &= 0x000000FF;
      CAN_Msg[5] |= CAN_Sgn.SgnBytes.Byte0;
      CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.DataTypeConversion9_n ) +
        0.5);
      CAN_Sgn.UnsignedSgn &= 0x000000FF;
      CAN_Msg[6] |= CAN_Sgn.SgnBytes.Byte0;
      CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.DataTypeConversion10_a ) +
        0.5);
      CAN_Sgn.UnsignedSgn &= 0x000000FF;
      CAN_Msg[7] |= CAN_Sgn.SgnBytes.Byte0;
    }

    can_tp1_msg_send(can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0X19C], 8, &(CAN_Msg[0]),
                     delayTime);
  }

  Racing_2019_B.AUXCANTxErrorOR = ((Racing_2019_B.SFunction1_ks != 0.0) &&
    (Racing_2019_B.RateTransition9 != 0.0));
  if ((rt_ZCFcn(ANY_ZERO_CROSSING,&Racing_2019_PrevZCX.AUX_CAN_412_Reset_ZCE,
                (Racing_2019_B.SFunction1_ks)) != NO_ZCEVENT) ||
      (Racing_2019_B.SFunction1_ks != 0.0)) {
    for (i = 0; i < 10; i++) {
      Racing_2019_DW.AUX_CAN_412_DSTATE[i] =
        Racing_2019_P.AUX_CAN_412_InitialCondition;
    }
  }

  Racing_2019_B.AUX_CAN_412 = Racing_2019_DW.AUX_CAN_412_DSTATE[0];

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X117]);
    if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X117]->processed) {
      can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X117]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X117]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X117]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X117]->processed) {
        Racing_2019_B.SFunction1_o8 = (real_T)
          can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X117]->processed;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X117]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte0 = CAN_Msg[0];
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          Racing_2019_B.SFunction1_o1_em = ((UInt8) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte0 = CAN_Msg[1];
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          Racing_2019_B.SFunction1_o2_gb = ((UInt8) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte0 = CAN_Msg[2];
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          Racing_2019_B.SFunction1_o3_p = ((UInt8) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte0 = CAN_Msg[3];
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          Racing_2019_B.SFunction1_o4_ag = ((UInt8) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte0 = CAN_Msg[4];
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          Racing_2019_B.SFunction1_o5_i0 = ((UInt8) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte0 = CAN_Msg[5];
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          Racing_2019_B.SFunction1_o6_l = ((UInt8) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte0 = CAN_Msg[6];
          CAN_Sgn.UnsignedSgn &= 0x000000FF;
          Racing_2019_B.SFunction1_o7_a = ((UInt8) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X117]->processed) {
      Racing_2019_B.SFunction1_o8 = 0.0;
    }
  }

  Racing_2019_B.Compare_ovh = (Racing_2019_B.SFunction1_o5_i0 ==
    Racing_2019_P.Ad_Act_Compare_const);
  Racing_2019_B.DataTypeConversion2_eu = (Racing_2019_B.SFunction1_o8 != 0.0);
  Racing_2019_B.UnitDelay_lp = Racing_2019_DW.UnitDelay_DSTATE_k;
  switch ((int32_T)Racing_2019_P.EdgeDetector3_model_j) {
   case 1:
    Racing_2019_B.MultiportSwitch_my[0] = Racing_2019_P.posedge_Value_l5[0];
    Racing_2019_B.MultiportSwitch_my[1] = Racing_2019_P.posedge_Value_l5[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_my[0] = Racing_2019_P.negedge_Value_g3[0];
    Racing_2019_B.MultiportSwitch_my[1] = Racing_2019_P.negedge_Value_g3[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_my[0] = Racing_2019_P.eitheredge_Value_ou[0];
    Racing_2019_B.MultiportSwitch_my[1] = Racing_2019_P.eitheredge_Value_ou[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_my[0],
    Racing_2019_B.DataTypeConversion2_eu, Racing_2019_B.UnitDelay_lp,
    &Racing_2019_B.POSITIVEEdge_e);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_my[1],
    Racing_2019_B.DataTypeConversion2_eu, Racing_2019_B.UnitDelay_lp,
    &Racing_2019_B.NEGATIVEEdge_ps);
  Racing_2019_B.LogicalOperator1_pd =
    (Racing_2019_B.POSITIVEEdge_e.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_ps.RelationalOperator1);
  Racing_2019_B.DataTypeConversion3_ch = Racing_2019_B.LogicalOperator1_pd;
  Racing_2019_B.DASH_CAN_279_Counter =
    Racing_2019_DW.DASH_CAN_279_Counter_PreviousIn;
  Racing_2019_B.Add4_ms = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion3_ch + Racing_2019_B.DASH_CAN_279_Counter);
  if ((rt_ZCFcn(ANY_ZERO_CROSSING,&Racing_2019_PrevZCX.DASH_CAN_279_Reset_ZCE,
                (Racing_2019_B.SFunction1_o8)) != NO_ZCEVENT) ||
      (Racing_2019_B.SFunction1_o8 != 0.0)) {
    for (i = 0; i < 20; i++) {
      Racing_2019_DW.DASH_CAN_279_DSTATE[i] =
        Racing_2019_P.DASH_CAN_279_InitialCondition;
    }
  }

  Racing_2019_B.DASH_CAN_279 = Racing_2019_DW.DASH_CAN_279_DSTATE[0];
  Racing_2019_B.DASHCANRxErrorOR = ((Racing_2019_B.DASH_CAN_279 != 0.0) &&
    (Racing_2019_P.Constant7_Value != 0.0) && (Racing_2019_B.CAN1981kHzto10Hz !=
    0.0) && (Racing_2019_B.CAN1011kHzto10Hz != 0.0));
  Racing_2019_B.Compare_nd = (Racing_2019_B.SFunction1_o1_em ==
    Racing_2019_P.Enable_Compare_const_g);
  Racing_2019_B.Compare_mr = (Racing_2019_B.SFunction1_o6_l ==
    Racing_2019_P.Green_TSAL_Compare_const);
  Racing_2019_B.Compare_kg = (Racing_2019_B.SFunction1_o7_a ==
    Racing_2019_P.SC_State_Compare_const);
  Racing_2019_B.Compare_il = (Racing_2019_B.SFunction1_o2_gb ==
    Racing_2019_P.Second_Compare_const);
  Racing_2019_B.Compare_kr = (Racing_2019_B.SFunction1_o4_ag ==
    Racing_2019_P.Start_Compare_const);
  Racing_2019_B.Compare_bf = (Racing_2019_B.SFunction1_o3_p ==
    Racing_2019_P.Third_Compare_const);

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XF6]);
    if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XF6]->processed) {
      can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XF6]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XF6]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XF6]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XF6]->processed) {
        Racing_2019_B.SFunction1_o5_np = (real_T)
          can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XF6]->processed;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XF6]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_i3 = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_et = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_fy = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_cf = ((UInt16) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XF6]->processed) {
      Racing_2019_B.SFunction1_o5_np = 0.0;
    }
  }

  Racing_2019_B.DataTypeConversion2_af = (Racing_2019_B.SFunction1_o5_np != 0.0);
  Racing_2019_B.UnitDelay_hy = Racing_2019_DW.UnitDelay_DSTATE_hk;
  switch ((int32_T)Racing_2019_P.EdgeDetector2_model_a) {
   case 1:
    Racing_2019_B.MultiportSwitch_j2[0] = Racing_2019_P.posedge_Value_ce[0];
    Racing_2019_B.MultiportSwitch_j2[1] = Racing_2019_P.posedge_Value_ce[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_j2[0] = Racing_2019_P.negedge_Value_a5[0];
    Racing_2019_B.MultiportSwitch_j2[1] = Racing_2019_P.negedge_Value_a5[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_j2[0] = Racing_2019_P.eitheredge_Value_bj[0];
    Racing_2019_B.MultiportSwitch_j2[1] = Racing_2019_P.eitheredge_Value_bj[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_j2[0],
    Racing_2019_B.DataTypeConversion2_af, Racing_2019_B.UnitDelay_hy,
    &Racing_2019_B.POSITIVEEdge_fb);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_j2[1],
    Racing_2019_B.DataTypeConversion2_af, Racing_2019_B.UnitDelay_hy,
    &Racing_2019_B.NEGATIVEEdge_pj);
  Racing_2019_B.LogicalOperator1_ek =
    (Racing_2019_B.POSITIVEEdge_fb.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_pj.RelationalOperator1);
  Racing_2019_B.DataTypeConversion2_c = Racing_2019_B.LogicalOperator1_ek;
  Racing_2019_B.DASH_CAN_246_Counter =
    Racing_2019_DW.DASH_CAN_246_Counter_PreviousIn;
  Racing_2019_B.Add3_i = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion2_c
    + Racing_2019_B.DASH_CAN_246_Counter);
  if ((rt_ZCFcn(ANY_ZERO_CROSSING,&Racing_2019_PrevZCX.DASH_CAN_246_Reset_ZCE,
                (Racing_2019_B.SFunction1_o5_np)) != NO_ZCEVENT) ||
      (Racing_2019_B.SFunction1_o5_np != 0.0)) {
    for (i = 0; i < 20; i++) {
      Racing_2019_DW.DASH_CAN_246_DSTATE[i] =
        Racing_2019_P.DASH_CAN_246_InitialCondition;
    }
  }

  Racing_2019_B.DASH_CAN_246 = Racing_2019_DW.DASH_CAN_246_DSTATE[0];
  Racing_2019_B.DataTypeConversion5_n = (real32_T)
    Racing_2019_B.RateTransition2_j;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(TSMS_Previous_Index_UsbFlRec, (Float32)
      Racing_2019_B.DataTypeConversion5_n);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion2_f = (real32_T)
    Racing_2019_B.RateTransition1_b;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(TSMS_After_Index_UsbFlRec, (Float32)
      Racing_2019_B.DataTypeConversion2_f);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion6_ln = Racing_2019_B.Compare_kg;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(SC_State_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion6_ln);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion7_py = Racing_2019_B.Compare_ovh;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(SC_Enable_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion7_py);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.to10Hz = Racing_2019_B.Compare_av;
  Racing_2019_B.DataTypeConversion_eb = Racing_2019_B.to10Hz;
  Racing_2019_B.LogicalOperator_d = ((Racing_2019_B.DataTypeConversion_eb != 0) ||
    (Racing_2019_P.Safe_State_LED_Test != 0));
  Racing_2019_B.Gain_j = (uint8_T)(Racing_2019_B.LogicalOperator_d ? (int32_T)
    ((uint32_T)Racing_2019_P.Gain_Gain_p >> 4) : 0);
  Racing_2019_B.DataTypeConversion1_j3 = Racing_2019_B.to10Hz1;
  Racing_2019_B.LogicalOperator1_gc = ((Racing_2019_B.DataTypeConversion1_j3 !=
    0) || (Racing_2019_P.Buzzer_Test != 0));
  Racing_2019_B.Gain1_h = (uint8_T)(Racing_2019_B.LogicalOperator1_gc ? (int32_T)
    ((uint32_T)Racing_2019_P.Gain1_Gain_i >> 4) : 0);
  Racing_2019_B.DataTypeConversion3_b = Racing_2019_B.to10Hz2;
  Racing_2019_B.LogicalOperator2_ht = ((Racing_2019_B.DataTypeConversion3_b != 0)
    || (Racing_2019_P.Sensor_Error_LED_Test != 0));
  Racing_2019_B.Gain2 = (uint8_T)(Racing_2019_B.LogicalOperator2_ht ? (int32_T)
    ((uint32_T)Racing_2019_P.Gain2_Gain_d >> 4) : 0);
  Racing_2019_B.DataTypeConversion4_h3 = Racing_2019_B.to10Hz3;
  Racing_2019_B.LogicalOperator3_i = ((Racing_2019_B.DataTypeConversion4_h3 != 0)
    || (Racing_2019_P.Enable_LED_Test != 0));
  Racing_2019_B.Gain3 = (uint8_T)(Racing_2019_B.LogicalOperator3_i ? (int32_T)
    ((uint32_T)Racing_2019_P.Gain3_Gain >> 4) : 0);
  Racing_2019_B.RateTransition3_j = Racing_2019_B.Compare_il;
  Racing_2019_B.DataTypeConversion8_a = Racing_2019_B.RateTransition3_j;
  Racing_2019_B.Delay400ms = Racing_2019_DW.Delay400ms_DSTATE[0];
  Racing_2019_B.LogicalOperator6_d = (Racing_2019_B.DataTypeConversion8_a &&
    Racing_2019_B.Delay400ms);
  Racing_2019_B.LogicalOperator5_i = !Racing_2019_B.DataTypeConversion8_a;
  Racing_2019_B.Memory_bi = Racing_2019_DW.Memory_PreviousInput_k0;
  zcEvent = Racing_2019_B.LogicalOperator6_d;
  i = zcEvent;
  zcEvent = Racing_2019_B.LogicalOperator5_i;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  zcEvent = Racing_2019_B.Memory_bi;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  Racing_2019_B.Logic_e[0U] = Racing_2019_P.Logic_table_nj[(uint32_T)i];
  Racing_2019_B.Logic_e[1U] = Racing_2019_P.Logic_table_nj[i + 8U];
  Racing_2019_B.SCEnableAND = ((Racing_2019_B.DataTypeConversion4_h3 != 0) &&
    Racing_2019_B.Logic_e[0]);
  Racing_2019_B.Compare_ba = (Racing_2019_B.RateTransition1_b <=
    Racing_2019_P.TSMSPreviousComparison_const);
  Racing_2019_B.Compare_kk = (Racing_2019_B.RateTransition2_j <=
    Racing_2019_P.TSMSAfterComparison_const);
  Racing_2019_B.SCSet = (Racing_2019_B.Compare_ba && Racing_2019_B.Compare_kk &&
    Racing_2019_B.Compare_kg && Racing_2019_B.Compare_ovh);
  Racing_2019_B.Memory1_c = Racing_2019_DW.Memory1_PreviousInput_a;
  zcEvent = (Racing_2019_B.Compare_kk &&
             (Racing_2019_PrevZCX.ResettableDelay_Reset_ZCE != POS_ZCSIG));
  if (zcEvent) {
    for (i = 0; i < 500; i++) {
      Racing_2019_DW.ResettableDelay_DSTATE[i] =
        Racing_2019_P.ResettableDelay_InitialConditio;
    }
  }

  Racing_2019_PrevZCX.ResettableDelay_Reset_ZCE = Racing_2019_B.Compare_kk;
  Racing_2019_B.ResettableDelay = Racing_2019_DW.ResettableDelay_DSTATE[0];
  Racing_2019_B.SCReset = (Racing_2019_B.Memory1_c &&
    Racing_2019_B.ResettableDelay);
  Racing_2019_B.Memory_l = Racing_2019_DW.Memory_PreviousInput_e2;
  zcEvent = Racing_2019_B.SCSet;
  i = zcEvent;
  zcEvent = Racing_2019_B.SCReset;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  zcEvent = Racing_2019_B.Memory_l;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  Racing_2019_B.Logic_kf[0U] = Racing_2019_P.Logic_table_nx[(uint32_T)i];
  Racing_2019_B.Logic_kf[1U] = Racing_2019_P.Logic_table_nx[i + 8U];
  Racing_2019_B.LogicalOperator4_d = (Racing_2019_B.SCEnableAND ||
    (Racing_2019_P.SC_Enable != 0.0) || Racing_2019_B.Logic_kf[0]);
  Racing_2019_B.Gain4_m = (uint8_T)(Racing_2019_B.LogicalOperator4_d ? (int32_T)
    ((uint32_T)Racing_2019_P.Gain4_Gain_k >> 4) : 0);

  {
    UInt32 CAN_Msg[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    Float32 delayTime = 0.0;
    can_tp1_msg_read(can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XCC]);
    if (can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XCC]->processed) {
      can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XCC]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XCC]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XCC]->timestamp > 0.0) {
      Racing_2019_B.SFunction1_iu = (real_T)
        can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XCC]->processed;
    }

    {
      rtican_Signal_t CAN_Sgn;
      CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_P.Dash_Fan_PWM ) + 0.5);
      CAN_Sgn.UnsignedSgn &= 0x000000FF;
      CAN_Msg[0] |= CAN_Sgn.SgnBytes.Byte0;
      CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.Gain_j ) + 0.5);
      CAN_Sgn.UnsignedSgn &= 0x0000000F;
      CAN_Msg[1] |= CAN_Sgn.SgnBytes.Byte0;
      CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.Gain1_h ) + 0.5);
      CAN_Sgn.UnsignedSgn &= 0x0000000F;
      CAN_Sgn.UnsignedSgn = ((UInt32)CAN_Sgn.UnsignedSgn) << 4;
      CAN_Msg[1] |= CAN_Sgn.SgnBytes.Byte0;
      CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.Gain2 ) + 0.5);
      CAN_Sgn.UnsignedSgn &= 0x0000000F;
      CAN_Msg[2] |= CAN_Sgn.SgnBytes.Byte0;
      CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.Gain3 ) + 0.5);
      CAN_Sgn.UnsignedSgn &= 0x0000000F;
      CAN_Sgn.UnsignedSgn = ((UInt32)CAN_Sgn.UnsignedSgn) << 4;
      CAN_Msg[2] |= CAN_Sgn.SgnBytes.Byte0;
      CAN_Sgn.UnsignedSgn = (UInt32) (( Racing_2019_B.Gain4_m ) + 0.5);
      CAN_Sgn.UnsignedSgn &= 0x000000FF;
      CAN_Msg[3] |= CAN_Sgn.SgnBytes.Byte0;
    }

    can_tp1_msg_send(can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XCC], 4, &(CAN_Msg[0]),
                     delayTime);
  }

  if ((rt_ZCFcn(ANY_ZERO_CROSSING,&Racing_2019_PrevZCX.DASH_CAN_204_Reset_ZCE,
                (Racing_2019_B.SFunction1_iu)) != NO_ZCEVENT) ||
      (Racing_2019_B.SFunction1_iu != 0.0)) {
    for (i = 0; i < 1000; i++) {
      Racing_2019_DW.DASH_CAN_204_DSTATE[i] =
        Racing_2019_P.DASH_CAN_204_InitialCondition;
    }
  }

  Racing_2019_B.DASH_CAN_204 = Racing_2019_DW.DASH_CAN_204_DSTATE[0];
  Racing_2019_B.DataTypeConversion9_my = (Racing_2019_P.Constant7_Value_k != 0.0);
  Racing_2019_B.Memory_g = Racing_2019_DW.Memory_PreviousInput_f;
  Racing_2019_B.Memory_iw = Racing_2019_DW.Memory_PreviousInput_kl;
  zcEvent = Racing_2019_B.DataTypeConversion8_a;
  i = zcEvent;
  zcEvent = Racing_2019_B.DataTypeConversion9_my;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  zcEvent = Racing_2019_B.Memory_iw;
  i = (int32_T)(((uint32_T)i << 1) + zcEvent);
  Racing_2019_B.Logic_f[0U] = Racing_2019_P.Logic_table_ne[(uint32_T)i];
  Racing_2019_B.Logic_f[1U] = Racing_2019_P.Logic_table_ne[i + 8U];
  u0 = (real32_T)floor(Racing_2019_B.IGBTTempto10Hz);
  if (rtIsNaNF(u0) || rtIsInfF(u0)) {
    u0 = 0.0F;
  } else {
    u0 = (real32_T)fmod(u0, 256.0F);
  }

  Racing_2019_B.DataTypeConversion8_n = (uint8_T)(u0 < 0.0F ? (int32_T)(uint8_T)
    -(int8_T)(uint8_T)-u0 : (int32_T)(uint8_T)u0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(IGBT_Temp_LEFT_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion8_n);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Inverter_Error_LEFT_Index_UsbFlRec,
      (Int32)Racing_2019_B.RateTransition);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Inverter_btb_LEFT_Index_UsbFlRec, (Int32)
      Racing_2019_B.RateTransition1_k);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Motor_Power_LEFT_Index_UsbFlRec, (Int32)
      Racing_2019_B.RateTransition2_k);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  u0 = (real32_T)floor(Racing_2019_B.IGBTTempto10Hz_f);
  if (rtIsNaNF(u0) || rtIsInfF(u0)) {
    u0 = 0.0F;
  } else {
    u0 = (real32_T)fmod(u0, 256.0F);
  }

  Racing_2019_B.DataTypeConversion8_be = (uint8_T)(u0 < 0.0F ? (int32_T)(uint8_T)
    -(int8_T)(uint8_T)-u0 : (int32_T)(uint8_T)u0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(IGBT_Temp_RIGHT_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion8_be);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Inverter_Error_RIGHT_Index_UsbFlRec,
      (Int32)Racing_2019_B.RateTransition_h);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Inverter_BTB_RIGHT_Index_UsbFlRec,
      (Int32)Racing_2019_B.RateTransition1_f);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Motor_Power_RIGHT_Index_UsbFlRec, (Int32)
      Racing_2019_B.RateTransition2_kl);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Braking_Torque_Index_UsbFlRec, (Int32)
      Racing_2019_B.RateTransition1_n);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }
}

void Racing_2019_update3(void)
{
  int_T idxDelay;
  Racing_2019_DW.to100Hz_Buffer0 = Racing_2019_B.Memory_g;
  Racing_2019_DW.to100Hz1_Buffer0 = Racing_2019_B.AUXCANTxErrorOR;
  Racing_2019_DW.to100Hz2_Buffer0 = Racing_2019_B.SFunction1_k;
  Racing_2019_DW.RateTransition13_Buffer0 = Racing_2019_B.Compare_il;
  Racing_2019_DW.to100Hz5_Buffer0 = Racing_2019_B.DASHCANRxErrorOR;
  Racing_2019_DW.to100Hz6_Buffer0 = Racing_2019_B.AUXCANRxErrorOR;
  Racing_2019_DW.EnableToggle_Buffer0 = Racing_2019_B.Compare_nd;
  Racing_2019_DW.StartButton_Buffer0 = Racing_2019_B.Compare_kr;
  Racing_2019_DW.to100Hz16_Buffer0 = Racing_2019_B.Compare_c1u;
  Racing_2019_DW.to100Hz17_Buffer0 = Racing_2019_B.Compare_av;
  for (idxDelay = 0; idxDelay < 9; idxDelay++) {
    Racing_2019_DW.BMS_CAN_201_DSTATE[idxDelay] =
      Racing_2019_DW.BMS_CAN_201_DSTATE[idxDelay + 1];
  }

  Racing_2019_DW.BMS_CAN_201_DSTATE[9] = Racing_2019_P.Constant4_Value;
  for (idxDelay = 0; idxDelay < 19; idxDelay++) {
    Racing_2019_DW.AUX_CAN_357_DSTATE[idxDelay] =
      Racing_2019_DW.AUX_CAN_357_DSTATE[idxDelay + 1];
    Racing_2019_DW.AUX_CAN_384_DSTATE[idxDelay] =
      Racing_2019_DW.AUX_CAN_384_DSTATE[idxDelay + 1];
  }

  Racing_2019_DW.AUX_CAN_357_DSTATE[19] = Racing_2019_P.Constant4_Value_c;
  Racing_2019_DW.AUX_CAN_384_DSTATE[19] = Racing_2019_P.Constant1_Value_i;
  Racing_2019_DW.AUX_CAN_357_Counter_PreviousInp = Racing_2019_B.Add2_a;
  Racing_2019_DW.AUX_CAN_384_Counter_PreviousInp = Racing_2019_B.Add3_p;
  Racing_2019_DW.UnitDelay_DSTATE_cl = Racing_2019_B.DataTypeConversion2_av;
  Racing_2019_DW.UnitDelay_DSTATE_do = Racing_2019_B.DataTypeConversion2_nr;
  Racing_2019_DW.Memory_PreviousInput_b = Racing_2019_B.Logic_k[0];
  Racing_2019_DW.Memory_PreviousInput_m = Racing_2019_B.Logic_m[0];
  Racing_2019_DW.Memory_PreviousInput_d = Racing_2019_B.Logic_b[0];
  Racing_2019_DW.Memory_PreviousInput_k = Racing_2019_B.Logic_o[0];
  for (idxDelay = 0; idxDelay < 9; idxDelay++) {
    Racing_2019_DW.AUX_CAN_412_DSTATE[idxDelay] =
      Racing_2019_DW.AUX_CAN_412_DSTATE[idxDelay + 1];
  }

  Racing_2019_DW.AUX_CAN_412_DSTATE[9] = Racing_2019_P.Constant4_Value_l;
  Racing_2019_DW.UnitDelay_DSTATE_k = Racing_2019_B.DataTypeConversion2_eu;
  Racing_2019_DW.DASH_CAN_279_Counter_PreviousIn = Racing_2019_B.Add4_ms;
  for (idxDelay = 0; idxDelay < 19; idxDelay++) {
    Racing_2019_DW.DASH_CAN_279_DSTATE[idxDelay] =
      Racing_2019_DW.DASH_CAN_279_DSTATE[idxDelay + 1];
    Racing_2019_DW.DASH_CAN_246_DSTATE[idxDelay] =
      Racing_2019_DW.DASH_CAN_246_DSTATE[idxDelay + 1];
  }

  Racing_2019_DW.DASH_CAN_279_DSTATE[19] = Racing_2019_P.Constant5_Value;
  Racing_2019_DW.UnitDelay_DSTATE_hk = Racing_2019_B.DataTypeConversion2_af;
  Racing_2019_DW.DASH_CAN_246_Counter_PreviousIn = Racing_2019_B.Add3_i;
  Racing_2019_DW.DASH_CAN_246_DSTATE[19] = Racing_2019_P.Constant4_Value_n;
  Racing_2019_DW.Delay400ms_DSTATE[0] = Racing_2019_DW.Delay400ms_DSTATE[1];
  Racing_2019_DW.Delay400ms_DSTATE[1] = Racing_2019_DW.Delay400ms_DSTATE[2];
  Racing_2019_DW.Delay400ms_DSTATE[2] = Racing_2019_DW.Delay400ms_DSTATE[3];
  Racing_2019_DW.Delay400ms_DSTATE[3] = Racing_2019_B.Logic_f[1];
  Racing_2019_DW.Memory_PreviousInput_k0 = Racing_2019_B.Logic_e[0];
  Racing_2019_DW.Memory1_PreviousInput_a = Racing_2019_B.Logic_kf[0];
  for (idxDelay = 0; idxDelay < 499; idxDelay++) {
    Racing_2019_DW.ResettableDelay_DSTATE[idxDelay] =
      Racing_2019_DW.ResettableDelay_DSTATE[idxDelay + 1];
  }

  Racing_2019_DW.ResettableDelay_DSTATE[499] = Racing_2019_B.Compare_kk;
  Racing_2019_DW.Memory_PreviousInput_e2 = Racing_2019_B.Logic_kf[0];
  for (idxDelay = 0; idxDelay < 999; idxDelay++) {
    Racing_2019_DW.DASH_CAN_204_DSTATE[idxDelay] =
      Racing_2019_DW.DASH_CAN_204_DSTATE[idxDelay + 1];
  }

  Racing_2019_DW.DASH_CAN_204_DSTATE[999] = Racing_2019_P.Constant5_Value_a;
  Racing_2019_DW.Memory_PreviousInput_f = Racing_2019_B.SFunction1_iu;
  Racing_2019_DW.Memory_PreviousInput_kl = Racing_2019_B.Logic_f[0];
}

void Racing_2019_output4(void)
{
  uint32_T maxV;
  int32_T rowIdx;
  uint32_T tmp;
  boolean_T tmp_0;
  uint64m_T tmp_1;
  uint64m_T tmp_2;
  uint64m_T tmp_3;
  uint64m_T tmp_4;
  uint64m_T tmp_5;
  uint64m_T tmp_6;
  uint64m_T tmp_7;
  uint64m_T tmp_8;
  uint64m_T tmp_9;
  uint64m_T tmp_a;
  uint64m_T tmp_b;
  uint64m_T tmp_c;
  uint64m_T tmp_d;
  uint8_T u0;
  uint8_T u1;
  uint8_T u2;
  real_T u0_0;
  real32_T u0_1;
  real_T u1_0;
  real32_T u1_1;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCE]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCE]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCE]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCE]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCE]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCE]->processed) {
        Racing_2019_B.SFunction1_o5 = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCE]->processed;
        Racing_2019_B.SFunction1_o6 = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCE]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCE]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_ke = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_mj = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_hq = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_pz = ((UInt16) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCE]->processed) {
      Racing_2019_B.SFunction1_o5 = 0.0;
    }
  }

  Racing_2019_B.s1c12 = (uint32_T)Racing_2019_P.s1c12_Gain *
    Racing_2019_B.SFunction1_o4_pz;
  Racing_2019_B.s1c11 = (uint32_T)Racing_2019_P.s1c11_Gain *
    Racing_2019_B.SFunction1_o3_hq;
  Racing_2019_B.s1c10 = (uint32_T)Racing_2019_P.s1c10_Gain *
    Racing_2019_B.SFunction1_o2_mj;
  Racing_2019_B.s1c9 = (uint32_T)Racing_2019_P.s1c9_Gain *
    Racing_2019_B.SFunction1_o1_ke;
  Racing_2019_B.Add_Voltage_s1q3 = ((Racing_2019_B.s1c12 + Racing_2019_B.s1c11)
    + Racing_2019_B.s1c10) + Racing_2019_B.s1c9;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCD]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCD]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCD]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCD]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCD]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCD]->processed) {
        Racing_2019_B.SFunction1_o5_o = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCD]->processed;
        Racing_2019_B.SFunction1_o6_o = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCD]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCD]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_ha = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_b4 = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_mk = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_ov = ((UInt16) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCD]->processed) {
      Racing_2019_B.SFunction1_o5_o = 0.0;
    }
  }

  Racing_2019_B.s1c8 = (uint32_T)Racing_2019_P.s1c8_Gain *
    Racing_2019_B.SFunction1_o4_ov;
  Racing_2019_B.s1c7 = (uint32_T)Racing_2019_P.s1c7_Gain *
    Racing_2019_B.SFunction1_o3_mk;
  Racing_2019_B.s1c6 = (uint32_T)Racing_2019_P.s1c6_Gain *
    Racing_2019_B.SFunction1_o2_b4;
  Racing_2019_B.s1c5 = (uint32_T)Racing_2019_P.s1c5_Gain *
    Racing_2019_B.SFunction1_o1_ha;
  Racing_2019_B.Add_Voltage_s1q2 = ((Racing_2019_B.s1c8 + Racing_2019_B.s1c7) +
    Racing_2019_B.s1c6) + Racing_2019_B.s1c5;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCC]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCC]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCC]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCC]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCC]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCC]->processed) {
        Racing_2019_B.SFunction1_o5_c = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCC]->processed;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCC]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_br = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_jf = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_ap = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_bw = ((UInt16) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCC]->processed) {
      Racing_2019_B.SFunction1_o5_c = 0.0;
    }
  }

  Racing_2019_B.s1c4 = (uint32_T)Racing_2019_P.s1c4_Gain *
    Racing_2019_B.SFunction1_o4_bw;
  Racing_2019_B.s1c3 = (uint32_T)Racing_2019_P.s1c3_Gain *
    Racing_2019_B.SFunction1_o3_ap;
  Racing_2019_B.s1c2 = (uint32_T)Racing_2019_P.s1c2_Gain *
    Racing_2019_B.SFunction1_o2_jf;
  Racing_2019_B.s1c1 = (uint32_T)Racing_2019_P.s1c1_Gain *
    Racing_2019_B.SFunction1_o1_br;
  Racing_2019_B.Add_Voltage_s1q1 = ((Racing_2019_B.s1c4 + Racing_2019_B.s1c3) +
    Racing_2019_B.s1c2) + Racing_2019_B.s1c1;
  Racing_2019_B.Add_Voltage_s1 = (Racing_2019_B.Add_Voltage_s1q3 +
    Racing_2019_B.Add_Voltage_s1q2) + Racing_2019_B.Add_Voltage_s1q1;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD1]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD1]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD1]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD1]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD1]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD1]->processed) {
        Racing_2019_B.SFunction1_o5_cj = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD1]->processed;
        Racing_2019_B.SFunction1_o6_e = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD1]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD1]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_e = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_hx = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_m = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_i = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD1]->processed) {
      Racing_2019_B.SFunction1_o5_cj = 0.0;
    }
  }

  Racing_2019_B.s2c12 = Racing_2019_P.s2c12_Gain * Racing_2019_B.SFunction1_o4_i;
  Racing_2019_B.s2c11 = Racing_2019_P.s2c11_Gain * Racing_2019_B.SFunction1_o3_m;
  Racing_2019_B.s2c10 = Racing_2019_P.s2c10_Gain *
    Racing_2019_B.SFunction1_o2_hx;
  Racing_2019_B.s2c9 = Racing_2019_P.s2c9_Gain * Racing_2019_B.SFunction1_o1_e;
  Racing_2019_B.Add_Voltage_s2q3 = ((Racing_2019_B.s2c12 + Racing_2019_B.s2c11)
    + Racing_2019_B.s2c10) + Racing_2019_B.s2c9;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD0]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD0]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD0]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD0]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD0]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD0]->processed) {
        Racing_2019_B.SFunction1_o5_g = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD0]->processed;
        Racing_2019_B.SFunction1_o6_i = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD0]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD0]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_b = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_h5 = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_l = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_b = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD0]->processed) {
      Racing_2019_B.SFunction1_o5_g = 0.0;
    }
  }

  Racing_2019_B.s2c8 = Racing_2019_P.s2c8_Gain * Racing_2019_B.SFunction1_o4_b;
  Racing_2019_B.s2c7 = Racing_2019_P.s2c7_Gain * Racing_2019_B.SFunction1_o3_l;
  Racing_2019_B.s2c6 = Racing_2019_P.s2c6_Gain * Racing_2019_B.SFunction1_o2_h5;
  Racing_2019_B.s2c5 = Racing_2019_P.s2c5_Gain * Racing_2019_B.SFunction1_o1_b;
  Racing_2019_B.Add_Voltage_s2q2 = ((Racing_2019_B.s2c8 + Racing_2019_B.s2c7) +
    Racing_2019_B.s2c6) + Racing_2019_B.s2c5;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCF]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCF]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCF]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCF]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCF]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCF]->processed) {
        Racing_2019_B.SFunction1_o5_m = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCF]->processed;
        Racing_2019_B.SFunction1_o6_h = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCF]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCF]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_o = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_g = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_d = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_o = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCF]->processed) {
      Racing_2019_B.SFunction1_o5_m = 0.0;
    }
  }

  Racing_2019_B.s2c4 = Racing_2019_P.s2c4_Gain * Racing_2019_B.SFunction1_o4_o;
  Racing_2019_B.s2c3 = Racing_2019_P.s2c3_Gain * Racing_2019_B.SFunction1_o3_d;
  Racing_2019_B.s2c2 = Racing_2019_P.s2c2_Gain * Racing_2019_B.SFunction1_o2_g;
  Racing_2019_B.s2c1 = Racing_2019_P.s2c1_Gain * Racing_2019_B.SFunction1_o1_o;
  Racing_2019_B.Add_Voltage_s2q1 = ((Racing_2019_B.s2c4 + Racing_2019_B.s2c3) +
    Racing_2019_B.s2c2) + Racing_2019_B.s2c1;
  Racing_2019_B.Add_Voltage_s2 = (Racing_2019_B.Add_Voltage_s2q3 +
    Racing_2019_B.Add_Voltage_s2q2) + Racing_2019_B.Add_Voltage_s2q1;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD4]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD4]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD4]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD4]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD4]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD4]->processed) {
        Racing_2019_B.SFunction1_o5_l = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD4]->processed;
        Racing_2019_B.SFunction1_o6_id = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD4]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD4]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_h = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_e = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_g = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_d = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD4]->processed) {
      Racing_2019_B.SFunction1_o5_l = 0.0;
    }
  }

  Racing_2019_B.s3c12 = Racing_2019_P.s3c12_Gain * Racing_2019_B.SFunction1_o4_d;
  Racing_2019_B.s3c11 = Racing_2019_P.s3c11_Gain * Racing_2019_B.SFunction1_o3_g;
  Racing_2019_B.s3c10 = Racing_2019_P.s3c10_Gain * Racing_2019_B.SFunction1_o2_e;
  Racing_2019_B.s3c9 = Racing_2019_P.s3c9_Gain * Racing_2019_B.SFunction1_o1_h;
  Racing_2019_B.Add_Voltage_s3q3 = ((Racing_2019_B.s3c12 + Racing_2019_B.s3c11)
    + Racing_2019_B.s3c10) + Racing_2019_B.s3c9;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD3]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD3]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD3]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD3]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD3]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD3]->processed) {
        Racing_2019_B.SFunction1_o5_gd = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD3]->processed;
        Racing_2019_B.SFunction1_o6_c = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD3]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD3]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_mx = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_c = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_mo = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_ah = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD3]->processed) {
      Racing_2019_B.SFunction1_o5_gd = 0.0;
    }
  }

  Racing_2019_B.s3c8 = Racing_2019_P.s3c8_Gain * Racing_2019_B.SFunction1_o4_ah;
  Racing_2019_B.s3c7 = Racing_2019_P.s3c7_Gain * Racing_2019_B.SFunction1_o3_mo;
  Racing_2019_B.s3c6 = Racing_2019_P.s3c6_Gain * Racing_2019_B.SFunction1_o2_c;
  Racing_2019_B.s3c5 = Racing_2019_P.s3c5_Gain * Racing_2019_B.SFunction1_o1_mx;
  Racing_2019_B.Add_Voltage_s3q2 = ((Racing_2019_B.s3c8 + Racing_2019_B.s3c7) +
    Racing_2019_B.s3c6) + Racing_2019_B.s3c5;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD2]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD2]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD2]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD2]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD2]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD2]->processed) {
        Racing_2019_B.SFunction1_o5_n = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD2]->processed;
        Racing_2019_B.SFunction1_o6_j = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD2]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD2]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_b3 = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_j = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_c = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_h = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD2]->processed) {
      Racing_2019_B.SFunction1_o5_n = 0.0;
    }
  }

  Racing_2019_B.s3c4 = Racing_2019_P.s3c4_Gain * Racing_2019_B.SFunction1_o4_h;
  Racing_2019_B.s3c3 = Racing_2019_P.s3c3_Gain * Racing_2019_B.SFunction1_o3_c;
  Racing_2019_B.s3c2 = Racing_2019_P.s3c2_Gain * Racing_2019_B.SFunction1_o2_j;
  Racing_2019_B.s3c1 = Racing_2019_P.s3c1_Gain * Racing_2019_B.SFunction1_o1_b3;
  Racing_2019_B.Add_Voltage_s3q1 = ((Racing_2019_B.s3c4 + Racing_2019_B.s3c3) +
    Racing_2019_B.s3c2) + Racing_2019_B.s3c1;
  Racing_2019_B.Add_Voltage_s3 = (Racing_2019_B.Add_Voltage_s3q3 +
    Racing_2019_B.Add_Voltage_s3q2) + Racing_2019_B.Add_Voltage_s3q1;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD7]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD7]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD7]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD7]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD7]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD7]->processed) {
        Racing_2019_B.SFunction1_o5_a = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD7]->processed;
        Racing_2019_B.SFunction1_o6_m = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD7]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD7]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_a = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_k = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_k = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_l = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD7]->processed) {
      Racing_2019_B.SFunction1_o5_a = 0.0;
    }
  }

  Racing_2019_B.s4c12 = Racing_2019_P.s4c12_Gain * Racing_2019_B.SFunction1_o4_l;
  Racing_2019_B.s4c11 = Racing_2019_P.s4c11_Gain * Racing_2019_B.SFunction1_o3_k;
  Racing_2019_B.s4c10 = Racing_2019_P.s4c10_Gain * Racing_2019_B.SFunction1_o2_k;
  Racing_2019_B.s4c9 = Racing_2019_P.s4c9_Gain * Racing_2019_B.SFunction1_o1_a;
  Racing_2019_B.Add_Voltage_s4q3 = ((Racing_2019_B.s4c12 + Racing_2019_B.s4c11)
    + Racing_2019_B.s4c10) + Racing_2019_B.s4c9;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD6]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD6]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD6]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD6]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD6]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD6]->processed) {
        Racing_2019_B.SFunction1_o5_b = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD6]->processed;
        Racing_2019_B.SFunction1_o6_p = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD6]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD6]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_es = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_a = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_j = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_l0 = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD6]->processed) {
      Racing_2019_B.SFunction1_o5_b = 0.0;
    }
  }

  Racing_2019_B.s4c8 = Racing_2019_P.s4c8_Gain * Racing_2019_B.SFunction1_o4_l0;
  Racing_2019_B.s4c7 = Racing_2019_P.s4c7_Gain * Racing_2019_B.SFunction1_o3_j;
  Racing_2019_B.s4c6 = Racing_2019_P.s4c6_Gain * Racing_2019_B.SFunction1_o2_a;
  Racing_2019_B.s4c5 = Racing_2019_P.s4c5_Gain * Racing_2019_B.SFunction1_o1_es;
  Racing_2019_B.Add_Voltage_s4q2 = ((Racing_2019_B.s4c8 + Racing_2019_B.s4c7) +
    Racing_2019_B.s4c6) + Racing_2019_B.s4c5;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD5]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD5]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD5]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD5]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD5]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD5]->processed) {
        Racing_2019_B.SFunction1_o5_f = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD5]->processed;
        Racing_2019_B.SFunction1_o6_j0 = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD5]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD5]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_l = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_cm = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_kc = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_d0 = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD5]->processed) {
      Racing_2019_B.SFunction1_o5_f = 0.0;
    }
  }

  Racing_2019_B.s4c4 = Racing_2019_P.s4c4_Gain * Racing_2019_B.SFunction1_o4_d0;
  Racing_2019_B.s4c3 = Racing_2019_P.s4c3_Gain * Racing_2019_B.SFunction1_o3_kc;
  Racing_2019_B.s4c2 = Racing_2019_P.s4c2_Gain * Racing_2019_B.SFunction1_o2_cm;
  Racing_2019_B.s4c1 = Racing_2019_P.s4c1_Gain * Racing_2019_B.SFunction1_o1_l;
  Racing_2019_B.Add_Voltage_s4q1 = ((Racing_2019_B.s4c4 + Racing_2019_B.s4c3) +
    Racing_2019_B.s4c2) + Racing_2019_B.s4c1;
  Racing_2019_B.Add_Voltage_s4 = (Racing_2019_B.Add_Voltage_s4q3 +
    Racing_2019_B.Add_Voltage_s4q2) + Racing_2019_B.Add_Voltage_s4q1;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDA]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDA]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDA]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDA]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDA]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDA]->processed) {
        Racing_2019_B.SFunction1_o5_k = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDA]->processed;
        Racing_2019_B.SFunction1_o6_n = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDA]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDA]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_k = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_jl = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_i = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_e = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDA]->processed) {
      Racing_2019_B.SFunction1_o5_k = 0.0;
    }
  }

  Racing_2019_B.s5c12 = Racing_2019_P.s5c12_Gain * Racing_2019_B.SFunction1_o4_e;
  Racing_2019_B.s5c11 = Racing_2019_P.s5c11_Gain * Racing_2019_B.SFunction1_o3_i;
  Racing_2019_B.s5c10 = Racing_2019_P.s5c10_Gain *
    Racing_2019_B.SFunction1_o2_jl;
  Racing_2019_B.s5c9 = Racing_2019_P.s5c9_Gain * Racing_2019_B.SFunction1_o1_k;
  Racing_2019_B.Add_Voltage_s5q3 = ((Racing_2019_B.s5c12 + Racing_2019_B.s5c11)
    + Racing_2019_B.s5c10) + Racing_2019_B.s5c9;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD9]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD9]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD9]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD9]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD9]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD9]->processed) {
        Racing_2019_B.SFunction1_o5_d = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD9]->processed;
        Racing_2019_B.SFunction1_o6_d = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD9]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD9]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_ag = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_m = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_f = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_p = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD9]->processed) {
      Racing_2019_B.SFunction1_o5_d = 0.0;
    }
  }

  Racing_2019_B.s5c8 = Racing_2019_P.s5c8_Gain * Racing_2019_B.SFunction1_o4_p;
  Racing_2019_B.s5c7 = Racing_2019_P.s5c7_Gain * Racing_2019_B.SFunction1_o3_f;
  Racing_2019_B.s5c6 = Racing_2019_P.s5c6_Gain * Racing_2019_B.SFunction1_o2_m;
  Racing_2019_B.s5c5 = Racing_2019_P.s5c5_Gain * Racing_2019_B.SFunction1_o1_ag;
  Racing_2019_B.Add_Voltage_s5q2 = ((Racing_2019_B.s5c8 + Racing_2019_B.s5c7) +
    Racing_2019_B.s5c6) + Racing_2019_B.s5c5;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD8]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD8]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD8]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD8]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD8]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD8]->processed) {
        Racing_2019_B.SFunction1_o5_ke = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD8]->processed;
        Racing_2019_B.SFunction1_o6_a = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD8]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD8]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_kl = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_n = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_jo = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_m = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD8]->processed) {
      Racing_2019_B.SFunction1_o5_ke = 0.0;
    }
  }

  Racing_2019_B.s5c4 = Racing_2019_P.s5c4_Gain * Racing_2019_B.SFunction1_o4_m;
  Racing_2019_B.s5c3 = Racing_2019_P.s5c3_Gain * Racing_2019_B.SFunction1_o3_jo;
  Racing_2019_B.s5c2 = Racing_2019_P.s5c2_Gain * Racing_2019_B.SFunction1_o2_n;
  Racing_2019_B.s5c1 = Racing_2019_P.s5c1_Gain * Racing_2019_B.SFunction1_o1_kl;
  Racing_2019_B.Add_Voltage_s5q1 = ((Racing_2019_B.s5c4 + Racing_2019_B.s5c3) +
    Racing_2019_B.s5c2) + Racing_2019_B.s5c1;
  Racing_2019_B.Add_Voltage_s5 = (Racing_2019_B.Add_Voltage_s5q3 +
    Racing_2019_B.Add_Voltage_s5q2) + Racing_2019_B.Add_Voltage_s5q1;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDD]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDD]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDD]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDD]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDD]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDD]->processed) {
        Racing_2019_B.SFunction1_o5_bo = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDD]->processed;
        Racing_2019_B.SFunction1_o6_is = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDD]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDD]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_eh = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_nq = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_jb = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_i2 = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDD]->processed) {
      Racing_2019_B.SFunction1_o5_bo = 0.0;
    }
  }

  Racing_2019_B.s6c12 = Racing_2019_P.s6c12_Gain *
    Racing_2019_B.SFunction1_o4_i2;
  Racing_2019_B.s6c11 = Racing_2019_P.s6c11_Gain *
    Racing_2019_B.SFunction1_o3_jb;
  Racing_2019_B.s6c10 = Racing_2019_P.s6c10_Gain *
    Racing_2019_B.SFunction1_o2_nq;
  Racing_2019_B.s6c9 = Racing_2019_P.s6c9_Gain * Racing_2019_B.SFunction1_o1_eh;
  Racing_2019_B.Add_Voltage_s6q3 = ((Racing_2019_B.s6c12 + Racing_2019_B.s6c11)
    + Racing_2019_B.s6c10) + Racing_2019_B.s6c9;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDC]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDC]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDC]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDC]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDC]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDC]->processed) {
        Racing_2019_B.SFunction1_o5_cb = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDC]->processed;
        Racing_2019_B.SFunction1_o6_ii = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDC]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDC]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_os = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_l = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_o = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_g = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDC]->processed) {
      Racing_2019_B.SFunction1_o5_cb = 0.0;
    }
  }

  Racing_2019_B.s6c8 = Racing_2019_P.s6c8_Gain * Racing_2019_B.SFunction1_o4_g;
  Racing_2019_B.s6c7 = Racing_2019_P.s6c7_Gain * Racing_2019_B.SFunction1_o3_o;
  Racing_2019_B.s6c6 = Racing_2019_P.s6c6_Gain * Racing_2019_B.SFunction1_o2_l;
  Racing_2019_B.s6c5 = Racing_2019_P.s6c5_Gain * Racing_2019_B.SFunction1_o1_os;
  Racing_2019_B.Add_Voltage_s6q2 = ((Racing_2019_B.s6c8 + Racing_2019_B.s6c7) +
    Racing_2019_B.s6c6) + Racing_2019_B.s6c5;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDB]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDB]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDB]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDB]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDB]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDB]->processed) {
        Racing_2019_B.SFunction1_o5_bu = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDB]->processed;
        Racing_2019_B.SFunction1_o6_k = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDB]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDB]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_f = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_m3 = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_j5 = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_ev = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDB]->processed) {
      Racing_2019_B.SFunction1_o5_bu = 0.0;
    }
  }

  Racing_2019_B.s6c4 = Racing_2019_P.s6c4_Gain * Racing_2019_B.SFunction1_o4_ev;
  Racing_2019_B.s6c3 = Racing_2019_P.s6c3_Gain * Racing_2019_B.SFunction1_o3_j5;
  Racing_2019_B.s6c2 = Racing_2019_P.s6c2_Gain * Racing_2019_B.SFunction1_o2_m3;
  Racing_2019_B.s6c1 = Racing_2019_P.s6c1_Gain * Racing_2019_B.SFunction1_o1_f;
  Racing_2019_B.Add_Voltage_s6q1 = ((Racing_2019_B.s6c4 + Racing_2019_B.s6c3) +
    Racing_2019_B.s6c2) + Racing_2019_B.s6c1;
  Racing_2019_B.Add_Voltage_s6 = (Racing_2019_B.Add_Voltage_s6q3 +
    Racing_2019_B.Add_Voltage_s6q2) + Racing_2019_B.Add_Voltage_s6q1;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE0]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE0]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE0]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE0]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE0]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE0]->processed) {
        Racing_2019_B.SFunction1_o5_j = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE0]->processed;
        Racing_2019_B.SFunction1_o6_f = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE0]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE0]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_n = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_na = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_g4 = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_bc = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE0]->processed) {
      Racing_2019_B.SFunction1_o5_j = 0.0;
    }
  }

  Racing_2019_B.s7c12 = Racing_2019_P.s7c12_Gain *
    Racing_2019_B.SFunction1_o4_bc;
  Racing_2019_B.s7c11 = Racing_2019_P.s7c11_Gain *
    Racing_2019_B.SFunction1_o3_g4;
  Racing_2019_B.s7c10 = Racing_2019_P.s7c10_Gain *
    Racing_2019_B.SFunction1_o2_na;
  Racing_2019_B.s7c9 = Racing_2019_P.s7c9_Gain * Racing_2019_B.SFunction1_o1_n;
  Racing_2019_B.Add_Voltage_s7q3 = ((Racing_2019_B.s7c12 + Racing_2019_B.s7c11)
    + Racing_2019_B.s7c10) + Racing_2019_B.s7c9;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDF]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDF]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDF]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDF]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDF]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDF]->processed) {
        Racing_2019_B.SFunction1_o5_be = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDF]->processed;
        Racing_2019_B.SFunction1_o6_hb = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDF]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDF]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_d = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_cj = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_n = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_e0 = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDF]->processed) {
      Racing_2019_B.SFunction1_o5_be = 0.0;
    }
  }

  Racing_2019_B.s7c8 = Racing_2019_P.s7c8_Gain * Racing_2019_B.SFunction1_o4_e0;
  Racing_2019_B.s7c7 = Racing_2019_P.s7c7_Gain * Racing_2019_B.SFunction1_o3_n;
  Racing_2019_B.s7c6 = Racing_2019_P.s7c6_Gain * Racing_2019_B.SFunction1_o2_cj;
  Racing_2019_B.s7c5 = Racing_2019_P.s7c5_Gain * Racing_2019_B.SFunction1_o1_d;
  Racing_2019_B.Add_Voltage_s7q2 = ((Racing_2019_B.s7c8 + Racing_2019_B.s7c7) +
    Racing_2019_B.s7c6) + Racing_2019_B.s7c5;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDE]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDE]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDE]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDE]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDE]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDE]->processed) {
        Racing_2019_B.SFunction1_o5_nf = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDE]->processed;
        Racing_2019_B.SFunction1_o6_g = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDE]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDE]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_j = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_k2 = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_io = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_ar = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDE]->processed) {
      Racing_2019_B.SFunction1_o5_nf = 0.0;
    }
  }

  Racing_2019_B.s7c4 = Racing_2019_P.s7c4_Gain * Racing_2019_B.SFunction1_o4_ar;
  Racing_2019_B.s7c3 = Racing_2019_P.s7c3_Gain * Racing_2019_B.SFunction1_o3_io;
  Racing_2019_B.s7c2 = Racing_2019_P.s7c2_Gain * Racing_2019_B.SFunction1_o2_k2;
  Racing_2019_B.s7c1 = Racing_2019_P.s7c1_Gain * Racing_2019_B.SFunction1_o1_j;
  Racing_2019_B.Add_Voltage_s7q1 = ((Racing_2019_B.s7c4 + Racing_2019_B.s7c3) +
    Racing_2019_B.s7c2) + Racing_2019_B.s7c1;
  Racing_2019_B.Add_Voltage_s7 = (Racing_2019_B.Add_Voltage_s7q3 +
    Racing_2019_B.Add_Voltage_s7q2) + Racing_2019_B.Add_Voltage_s7q1;
  Racing_2019_B.HVVoltage = ((((((real_T)Racing_2019_B.Add_Voltage_s1 *
    2.9802322387695313E-8 + Racing_2019_B.Add_Voltage_s2) +
    Racing_2019_B.Add_Voltage_s3) + Racing_2019_B.Add_Voltage_s4) +
    Racing_2019_B.Add_Voltage_s5) + Racing_2019_B.Add_Voltage_s6) +
    Racing_2019_B.Add_Voltage_s7;
  u1_0 = floor(Racing_2019_B.HVVoltage);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion_nd = (int16_T)(u1_0 < 0.0 ? (int32_T)(int16_T)
    -(int16_T)(uint16_T)-u1_0 : (int32_T)(int16_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(VDC_BMS_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion_nd);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Compare_ov = (Racing_2019_B.SFunction1_o6 >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.Compare_m0 = (Racing_2019_B.SFunction1_o6_o >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.Compare_dy = (0.0 >= Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.Compare_g14 = (0.0 >= Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.CAN_s1_Error = (Racing_2019_B.Compare_ov ||
    Racing_2019_B.Compare_m0 || Racing_2019_B.Compare_dy ||
    Racing_2019_B.Compare_g14);
  Racing_2019_B.Compare_la = (Racing_2019_B.SFunction1_o6_e >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.Compare_nf = (Racing_2019_B.SFunction1_o6_i >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.Compare_glu = (Racing_2019_B.SFunction1_o6_h >=
    Racing_2019_P.BMS_Error_Time);

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE2]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE2]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE2]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE2]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE2]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE2]->processed) {
        Racing_2019_B.SFunction1_o5_i = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE2]->processed;
        Racing_2019_B.SFunction1_o6_jd = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE2]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE2]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_g = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_ge = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_cn = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_hv = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE2]->processed) {
      Racing_2019_B.SFunction1_o5_i = 0.0;
    }
  }

  Racing_2019_B.Compare_a0 = (Racing_2019_B.SFunction1_o6_jd >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.CAN_s2_Error = (Racing_2019_B.Compare_la ||
    Racing_2019_B.Compare_nf || Racing_2019_B.Compare_glu ||
    Racing_2019_B.Compare_a0);
  Racing_2019_B.Compare_ai = (Racing_2019_B.SFunction1_o6_id >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.Compare_aw = (Racing_2019_B.SFunction1_o6_c >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.Compare_pa = (Racing_2019_B.SFunction1_o6_j >=
    Racing_2019_P.BMS_Error_Time);

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE3]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE3]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE3]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE3]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE3]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE3]->processed) {
        Racing_2019_B.SFunction1_o5_ok = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE3]->processed;
        Racing_2019_B.SFunction1_o6_as = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE3]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE3]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_fb = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_h5w = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_me = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_ih = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE3]->processed) {
      Racing_2019_B.SFunction1_o5_ok = 0.0;
    }
  }

  Racing_2019_B.Compare_gb = (Racing_2019_B.SFunction1_o6_as >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.CAN_s3_Error = (Racing_2019_B.Compare_ai ||
    Racing_2019_B.Compare_aw || Racing_2019_B.Compare_pa ||
    Racing_2019_B.Compare_gb);
  Racing_2019_B.Compare_pn = (Racing_2019_B.SFunction1_o6_m >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.Compare_fk = (Racing_2019_B.SFunction1_o6_p >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.Compare_mj = (Racing_2019_B.SFunction1_o6_j0 >=
    Racing_2019_P.BMS_Error_Time);

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE4]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE4]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE4]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE4]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE4]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE4]->processed) {
        Racing_2019_B.SFunction1_o5_mk = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE4]->processed;
        Racing_2019_B.SFunction1_o6_dw = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE4]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE4]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_gu = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_mx = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_b = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_hj = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE4]->processed) {
      Racing_2019_B.SFunction1_o5_mk = 0.0;
    }
  }

  Racing_2019_B.Compare_go = (Racing_2019_B.SFunction1_o6_dw >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.CAN_s4_Error = (Racing_2019_B.Compare_pn ||
    Racing_2019_B.Compare_fk || Racing_2019_B.Compare_mj ||
    Racing_2019_B.Compare_go);
  Racing_2019_B.Compare_f4 = (Racing_2019_B.SFunction1_o6_n >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.Compare_kq = (Racing_2019_B.SFunction1_o6_d >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.Compare_lg = (Racing_2019_B.SFunction1_o6_a >=
    Racing_2019_P.BMS_Error_Time);

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE5]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE5]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE5]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE5]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE5]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE5]->processed) {
        Racing_2019_B.SFunction1_o5_ja = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE5]->processed;
        Racing_2019_B.SFunction1_o6_hg = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE5]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE5]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_e4 = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_ja = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_bu = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_b3 = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE5]->processed) {
      Racing_2019_B.SFunction1_o5_ja = 0.0;
    }
  }

  Racing_2019_B.Compare_c2 = (Racing_2019_B.SFunction1_o6_hg >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.CAN_s5_Error = (Racing_2019_B.Compare_f4 ||
    Racing_2019_B.Compare_kq || Racing_2019_B.Compare_lg ||
    Racing_2019_B.Compare_c2);
  Racing_2019_B.Compare_cn = (Racing_2019_B.SFunction1_o6_is >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.Compare_g5 = (Racing_2019_B.SFunction1_o6_ii >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.Compare_jw = (Racing_2019_B.SFunction1_o6_k >=
    Racing_2019_P.BMS_Error_Time);

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE6]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE6]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE6]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE6]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE6]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE6]->processed) {
        Racing_2019_B.SFunction1_o5_m0 = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE6]->processed;
        Racing_2019_B.SFunction1_o6_eb = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE6]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE6]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_fz = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_lj = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_j50 = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_f = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE6]->processed) {
      Racing_2019_B.SFunction1_o5_m0 = 0.0;
    }
  }

  Racing_2019_B.Compare_dh = (Racing_2019_B.SFunction1_o6_eb >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.CAN_s6_Error = (Racing_2019_B.Compare_cn ||
    Racing_2019_B.Compare_g5 || Racing_2019_B.Compare_jw ||
    Racing_2019_B.Compare_dh);
  Racing_2019_B.Compare_cq = (Racing_2019_B.SFunction1_o6_f >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.Compare_c1 = (Racing_2019_B.SFunction1_o6_hb >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.Compare_md = (Racing_2019_B.SFunction1_o6_g >=
    Racing_2019_P.BMS_Error_Time);

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE7]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE7]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE7]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE7]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE7]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE7]->processed) {
        Racing_2019_B.SFunction1_o5_iw = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE7]->processed;
        Racing_2019_B.SFunction1_o6_gh = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE7]->deltatime;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE7]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_p = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_cn = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_km = ((real_T) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_fl = ((real_T) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE7]->processed) {
      Racing_2019_B.SFunction1_o5_iw = 0.0;
    }
  }

  Racing_2019_B.Compare_iq = (Racing_2019_B.SFunction1_o6_gh >=
    Racing_2019_P.BMS_Error_Time);
  Racing_2019_B.CAN_s7_Error = (Racing_2019_B.Compare_cq ||
    Racing_2019_B.Compare_c1 || Racing_2019_B.Compare_md ||
    Racing_2019_B.Compare_iq);
  Racing_2019_B.CANSegmentsRxError = (Racing_2019_B.CAN_s1_Error ||
    Racing_2019_B.CAN_s2_Error || Racing_2019_B.CAN_s3_Error ||
    Racing_2019_B.CAN_s4_Error || Racing_2019_B.CAN_s5_Error ||
    Racing_2019_B.CAN_s6_Error || Racing_2019_B.CAN_s7_Error ||
    (Racing_2019_B.CAN_ID200100Hzto5Hz != 0.0));
  tmp = Racing_2019_B.s1c12;
  maxV = Racing_2019_B.s1c11;
  if (tmp > maxV) {
    maxV = tmp;
  }

  tmp = Racing_2019_B.s1c10;
  if (!(maxV > tmp)) {
    maxV = tmp;
  }

  tmp = Racing_2019_B.s1c9;
  if (!(maxV > tmp)) {
    maxV = tmp;
  }

  Racing_2019_B.Max_Voltage_s1q3 = maxV;
  tmp = Racing_2019_B.s1c8;
  maxV = Racing_2019_B.s1c7;
  if (tmp > maxV) {
    maxV = tmp;
  }

  tmp = Racing_2019_B.s1c6;
  if (!(maxV > tmp)) {
    maxV = tmp;
  }

  tmp = Racing_2019_B.s1c5;
  if (!(maxV > tmp)) {
    maxV = tmp;
  }

  Racing_2019_B.Max_Voltage_s1q2 = maxV;
  tmp = Racing_2019_B.s1c4;
  maxV = Racing_2019_B.s1c3;
  if (tmp > maxV) {
    maxV = tmp;
  }

  tmp = Racing_2019_B.s1c2;
  if (!(maxV > tmp)) {
    maxV = tmp;
  }

  tmp = Racing_2019_B.s1c1;
  if (!(maxV > tmp)) {
    maxV = tmp;
  }

  Racing_2019_B.Max_Voltage_s1q1 = maxV;
  tmp = Racing_2019_B.Max_Voltage_s1q3;
  maxV = Racing_2019_B.Max_Voltage_s1q2;
  if (tmp > maxV) {
    maxV = tmp;
  }

  tmp = Racing_2019_B.Max_Voltage_s1q1;
  if (!(maxV > tmp)) {
    maxV = tmp;
  }

  Racing_2019_B.Max_Voltage_s1 = maxV;
  u0_0 = Racing_2019_B.s2c12;
  u1_0 = Racing_2019_B.s2c11;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s2c10;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s2c9;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s2q3 = u1_0;
  u0_0 = Racing_2019_B.s2c8;
  u1_0 = Racing_2019_B.s2c7;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s2c6;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s2c5;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s2q2 = u1_0;
  u0_0 = Racing_2019_B.s2c4;
  u1_0 = Racing_2019_B.s2c3;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s2c2;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s2c1;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s2q1 = u1_0;
  u0_0 = Racing_2019_B.Max_Voltage_s2q3;
  u1_0 = Racing_2019_B.Max_Voltage_s2q2;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Max_Voltage_s2q1;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s2 = u1_0;
  u0_0 = Racing_2019_B.s3c12;
  u1_0 = Racing_2019_B.s3c11;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s3c10;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s3c9;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s3q3 = u1_0;
  u0_0 = Racing_2019_B.s3c8;
  u1_0 = Racing_2019_B.s3c7;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s3c6;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s3c5;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s3q2 = u1_0;
  u0_0 = Racing_2019_B.s3c4;
  u1_0 = Racing_2019_B.s3c3;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s3c2;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s3c1;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s3q1 = u1_0;
  u0_0 = Racing_2019_B.Max_Voltage_s3q3;
  u1_0 = Racing_2019_B.Max_Voltage_s3q2;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Max_Voltage_s3q1;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s3 = u1_0;
  u0_0 = Racing_2019_B.s4c12;
  u1_0 = Racing_2019_B.s4c11;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s4c10;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s4c9;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s4q3 = u1_0;
  u0_0 = Racing_2019_B.s4c8;
  u1_0 = Racing_2019_B.s4c7;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s4c6;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s4c5;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s4q2 = u1_0;
  u0_0 = Racing_2019_B.s4c4;
  u1_0 = Racing_2019_B.s4c3;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s4c2;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s4c1;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s4q1 = u1_0;
  u0_0 = Racing_2019_B.Max_Voltage_s4q3;
  u1_0 = Racing_2019_B.Max_Voltage_s4q2;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Max_Voltage_s4q1;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s4 = u1_0;
  u0_0 = Racing_2019_B.s5c12;
  u1_0 = Racing_2019_B.s5c11;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s5c10;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s5c9;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s5q3 = u1_0;
  u0_0 = Racing_2019_B.s5c8;
  u1_0 = Racing_2019_B.s5c7;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s5c6;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s5c5;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s5q2 = u1_0;
  u0_0 = Racing_2019_B.s5c4;
  u1_0 = Racing_2019_B.s5c3;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s5c2;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s5c1;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s5q1 = u1_0;
  u0_0 = Racing_2019_B.Max_Voltage_s5q3;
  u1_0 = Racing_2019_B.Max_Voltage_s5q2;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Max_Voltage_s5q1;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s5 = u1_0;
  u0_0 = Racing_2019_B.s6c12;
  u1_0 = Racing_2019_B.s6c11;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s6c10;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s6c9;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s6q3 = u1_0;
  u0_0 = Racing_2019_B.s6c8;
  u1_0 = Racing_2019_B.s6c7;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s6c6;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s6c5;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s6q2 = u1_0;
  u0_0 = Racing_2019_B.s6c4;
  u1_0 = Racing_2019_B.s6c3;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s6c2;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s6c1;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s6q1 = u1_0;
  u0_0 = Racing_2019_B.Max_Voltage_s6q3;
  u1_0 = Racing_2019_B.Max_Voltage_s6q2;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Max_Voltage_s6q1;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s6 = u1_0;
  u0_0 = Racing_2019_B.s7c12;
  u1_0 = Racing_2019_B.s7c11;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s7c10;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s7c9;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s7q3 = u1_0;
  u0_0 = Racing_2019_B.s7c8;
  u1_0 = Racing_2019_B.s7c7;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s7c6;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s7c5;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s7q2 = u1_0;
  u0_0 = Racing_2019_B.s7c4;
  u1_0 = Racing_2019_B.s7c3;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s7c2;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s7c1;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s7q1 = u1_0;
  u0_0 = Racing_2019_B.Max_Voltage_s7q3;
  u1_0 = Racing_2019_B.Max_Voltage_s7q2;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Max_Voltage_s7q1;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Max_Voltage_s7 = u1_0;
  u0_0 = (real_T)Racing_2019_B.Max_Voltage_s1 * 2.9802322387695313E-8;
  u1_0 = Racing_2019_B.Max_Voltage_s2;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Max_Voltage_s3;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Max_Voltage_s4;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Max_Voltage_s5;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Max_Voltage_s6;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Max_Voltage_s7;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.MaxBatteryVoltage = u1_0;
  tmp = Racing_2019_B.s1c12;
  maxV = Racing_2019_B.s1c11;
  if (tmp < maxV) {
    maxV = tmp;
  }

  tmp = Racing_2019_B.s1c10;
  if (!(maxV < tmp)) {
    maxV = tmp;
  }

  tmp = Racing_2019_B.s1c9;
  if (!(maxV < tmp)) {
    maxV = tmp;
  }

  Racing_2019_B.Min_Voltage_s1q3 = maxV;
  tmp = Racing_2019_B.s1c8;
  maxV = Racing_2019_B.s1c7;
  if (tmp < maxV) {
    maxV = tmp;
  }

  tmp = Racing_2019_B.s1c6;
  if (!(maxV < tmp)) {
    maxV = tmp;
  }

  tmp = Racing_2019_B.s1c5;
  if (!(maxV < tmp)) {
    maxV = tmp;
  }

  Racing_2019_B.Min_Voltage_s1q2 = maxV;
  tmp = Racing_2019_B.s1c4;
  maxV = Racing_2019_B.s1c3;
  if (tmp < maxV) {
    maxV = tmp;
  }

  tmp = Racing_2019_B.s1c2;
  if (!(maxV < tmp)) {
    maxV = tmp;
  }

  tmp = Racing_2019_B.s1c1;
  if (!(maxV < tmp)) {
    maxV = tmp;
  }

  Racing_2019_B.Min_Voltage_s1q1 = maxV;
  tmp = Racing_2019_B.Min_Voltage_s1q3;
  maxV = Racing_2019_B.Min_Voltage_s1q2;
  if (tmp < maxV) {
    maxV = tmp;
  }

  tmp = Racing_2019_B.Min_Voltage_s1q1;
  if (!(maxV < tmp)) {
    maxV = tmp;
  }

  Racing_2019_B.Min_Voltage_s1 = maxV;
  u0_0 = (real_T)Racing_2019_B.Min_Voltage_s1 * 2.9802322387695313E-8;
  u1_0 = Racing_2019_B.Add_Voltage_s2;
  if ((u0_0 > u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Add_Voltage_s3;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Add_Voltage_s4;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Add_Voltage_s5;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Add_Voltage_s6;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Add_Voltage_s7;
  if (!((u1_0 > u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.MaxSegmentVoltage = u1_0;

  {
    UInt32 *CAN_Msg;
    can_tp1_msg_read_from_mem(can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE1]);
    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE1]->processed) {
      can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE1]->timestamp =
        rtk_dsts_time_to_simtime_convert
        (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE1]->timestamp);
    }

    if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE1]->timestamp > 0.0) {
      if (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE1]->processed) {
        Racing_2019_B.SFunction1_o5_az = (real_T)
          can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE1]->processed;
        CAN_Msg = can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE1]->data;

        {
          rtican_Signal_t CAN_Sgn;
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[1];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[0];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o1_bi = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[3];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[2];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o2_d = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[5];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[4];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o3_na = ((UInt16) CAN_Sgn.UnsignedSgn);
          CAN_Sgn.SgnBytes.Byte3 = CAN_Msg[7];
          CAN_Sgn.SgnBytes.Byte2 = CAN_Msg[6];
          CAN_Sgn.SgnBytes.Byte0 = CAN_Sgn.SgnBytes.Byte3;
          CAN_Sgn.SgnBytes.Byte1 = CAN_Sgn.SgnBytes.Byte2;
          CAN_Sgn.UnsignedSgn &= 0x0000FFFF;
          Racing_2019_B.SFunction1_o4_bd = ((UInt16) CAN_Sgn.UnsignedSgn);
        }
      }
    }

    if (!can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE1]->processed) {
      Racing_2019_B.SFunction1_o5_az = 0.0;
    }
  }

  Racing_2019_B.DataTypeConversion7 = Racing_2019_B.SFunction1_o4_bd;
  Racing_2019_B.s1temp4 = Racing_2019_P.s1temp4_Gain *
    Racing_2019_B.DataTypeConversion7;
  Racing_2019_s1t4(Racing_2019_B.s1temp4, &Racing_2019_B.sf_s1t4);
  Racing_2019_B.DataTypeConversion3 = Racing_2019_B.SFunction1_o3_na;
  Racing_2019_B.s1temp3 = Racing_2019_P.s1temp3_Gain *
    Racing_2019_B.DataTypeConversion3;
  Racing_2019_s1t1(Racing_2019_B.s1temp3, &Racing_2019_B.sf_s1t3);
  Racing_2019_B.DataTypeConversion2 = Racing_2019_B.SFunction1_o2_d;
  Racing_2019_B.s1temp2 = Racing_2019_P.s1temp2_Gain *
    Racing_2019_B.DataTypeConversion2;
  Racing_2019_s1t1(Racing_2019_B.s1temp2, &Racing_2019_B.sf_s1t2);
  Racing_2019_B.DataTypeConversion = Racing_2019_B.SFunction1_o1_bi;
  Racing_2019_B.s1temp1 = Racing_2019_P.s1temp1_Gain *
    Racing_2019_B.DataTypeConversion;
  Racing_2019_s1t1(Racing_2019_B.s1temp1, &Racing_2019_B.sf_s1t1);
  u0_1 = Racing_2019_B.sf_s1t4.y;
  u1_1 = Racing_2019_B.sf_s1t3.y;
  if ((u0_1 > u1_1) || rtIsNaNF(u1_1)) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s1t2.y;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s1t1.y;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  Racing_2019_B.Max_Temp_s1t = u1_1;
  Racing_2019_B.RateTransition4_e = Racing_2019_B.Max_Temp_s1t;
  Racing_2019_B.DataTypeConversion7_k = (real32_T)Racing_2019_B.SFunction1_o4_hv;
  Racing_2019_B.s2temp4 = Racing_2019_P.s2temp4_Gain *
    Racing_2019_B.DataTypeConversion7_k;
  Racing_2019_s1t4(Racing_2019_B.s2temp4, &Racing_2019_B.sf_s2t4);
  Racing_2019_B.DataTypeConversion3_o = (real32_T)Racing_2019_B.SFunction1_o3_cn;
  Racing_2019_B.s2temp3 = Racing_2019_P.s2temp3_Gain *
    Racing_2019_B.DataTypeConversion3_o;
  Racing_2019_s1t1(Racing_2019_B.s2temp3, &Racing_2019_B.sf_s2t3);
  Racing_2019_B.DataTypeConversion2_n = (real32_T)Racing_2019_B.SFunction1_o2_ge;
  Racing_2019_B.s2temp2 = Racing_2019_P.s2temp2_Gain *
    Racing_2019_B.DataTypeConversion2_n;
  Racing_2019_s1t1(Racing_2019_B.s2temp2, &Racing_2019_B.sf_s2t2);
  Racing_2019_B.DataTypeConversion_f = (real32_T)Racing_2019_B.SFunction1_o1_g;
  Racing_2019_B.s2temp1 = Racing_2019_P.s2temp1_Gain *
    Racing_2019_B.DataTypeConversion_f;
  Racing_2019_s1t1(Racing_2019_B.s2temp1, &Racing_2019_B.sf_s2t1);
  u0_1 = Racing_2019_B.sf_s2t4.y;
  u1_1 = Racing_2019_B.sf_s2t3.y;
  if ((u0_1 > u1_1) || rtIsNaNF(u1_1)) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s2t2.y;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s2t1.y;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  Racing_2019_B.Max_Temp_s2t = u1_1;
  Racing_2019_B.DataTypeConversion7_a = (real32_T)Racing_2019_B.SFunction1_o4_ih;
  Racing_2019_B.s3temp4 = Racing_2019_P.s3temp4_Gain *
    Racing_2019_B.DataTypeConversion7_a;
  Racing_2019_s1t4(Racing_2019_B.s3temp4, &Racing_2019_B.sf_s3t4);
  Racing_2019_B.DataTypeConversion3_m = (real32_T)Racing_2019_B.SFunction1_o3_me;
  Racing_2019_B.s3temp3 = Racing_2019_P.s3temp3_Gain *
    Racing_2019_B.DataTypeConversion3_m;
  Racing_2019_s1t1(Racing_2019_B.s3temp3, &Racing_2019_B.sf_s3t3);
  Racing_2019_B.DataTypeConversion2_p = (real32_T)
    Racing_2019_B.SFunction1_o2_h5w;
  Racing_2019_B.s3temp2 = Racing_2019_P.s3temp2_Gain *
    Racing_2019_B.DataTypeConversion2_p;
  Racing_2019_s1t1(Racing_2019_B.s3temp2, &Racing_2019_B.sf_s3t2);
  Racing_2019_B.DataTypeConversion_p = (real32_T)Racing_2019_B.SFunction1_o1_fb;
  Racing_2019_B.s3temp1 = Racing_2019_P.s3temp1_Gain *
    Racing_2019_B.DataTypeConversion_p;
  Racing_2019_s1t1(Racing_2019_B.s3temp1, &Racing_2019_B.sf_s3t1);
  u0_1 = Racing_2019_B.sf_s3t4.y;
  u1_1 = Racing_2019_B.sf_s3t3.y;
  if ((u0_1 > u1_1) || rtIsNaNF(u1_1)) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s3t2.y;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s3t1.y;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  Racing_2019_B.Max_Temp_s3t = u1_1;
  Racing_2019_B.DataTypeConversion7_p = (real32_T)Racing_2019_B.SFunction1_o4_hj;
  Racing_2019_B.s4temp4 = Racing_2019_P.s4temp4_Gain *
    Racing_2019_B.DataTypeConversion7_p;
  Racing_2019_s1t4(Racing_2019_B.s4temp4, &Racing_2019_B.sf_s4t4);
  Racing_2019_B.DataTypeConversion3_j = (real32_T)Racing_2019_B.SFunction1_o3_b;
  Racing_2019_B.s4temp3 = Racing_2019_P.s4temp3_Gain *
    Racing_2019_B.DataTypeConversion3_j;
  Racing_2019_s1t1(Racing_2019_B.s4temp3, &Racing_2019_B.sf_s4t3);
  Racing_2019_B.DataTypeConversion2_a = (real32_T)Racing_2019_B.SFunction1_o2_mx;
  Racing_2019_B.s4temp2 = Racing_2019_P.s4temp2_Gain *
    Racing_2019_B.DataTypeConversion2_a;
  Racing_2019_s1t1(Racing_2019_B.s4temp2, &Racing_2019_B.sf_s4t2);
  Racing_2019_B.DataTypeConversion_n = (real32_T)Racing_2019_B.SFunction1_o1_gu;
  Racing_2019_B.s4temp1 = Racing_2019_P.s4temp1_Gain *
    Racing_2019_B.DataTypeConversion_n;
  Racing_2019_s1t1(Racing_2019_B.s4temp1, &Racing_2019_B.sf_s4t1);
  u0_1 = Racing_2019_B.sf_s4t4.y;
  u1_1 = Racing_2019_B.sf_s4t3.y;
  if ((u0_1 > u1_1) || rtIsNaNF(u1_1)) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s4t2.y;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s4t1.y;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  Racing_2019_B.Max_Temp_s4t = u1_1;
  Racing_2019_B.DataTypeConversion7_i = (real32_T)Racing_2019_B.SFunction1_o4_b3;
  Racing_2019_B.s5temp4 = Racing_2019_P.s5temp4_Gain *
    Racing_2019_B.DataTypeConversion7_i;
  Racing_2019_s1t4(Racing_2019_B.s5temp4, &Racing_2019_B.sf_s5t4);
  Racing_2019_B.DataTypeConversion3_g = (real32_T)Racing_2019_B.SFunction1_o3_bu;
  Racing_2019_B.s5temp3 = Racing_2019_P.s5temp3_Gain *
    Racing_2019_B.DataTypeConversion3_g;
  Racing_2019_s1t1(Racing_2019_B.s5temp3, &Racing_2019_B.sf_s5t3);
  Racing_2019_B.DataTypeConversion2_j = (real32_T)Racing_2019_B.SFunction1_o2_ja;
  Racing_2019_B.s5temp2 = Racing_2019_P.s5temp2_Gain *
    Racing_2019_B.DataTypeConversion2_j;
  Racing_2019_s1t1(Racing_2019_B.s5temp2, &Racing_2019_B.sf_s5t2);
  Racing_2019_B.DataTypeConversion_d = (real32_T)Racing_2019_B.SFunction1_o1_e4;
  Racing_2019_B.s5temp1 = Racing_2019_P.s5temp1_Gain *
    Racing_2019_B.DataTypeConversion_d;
  Racing_2019_s1t1(Racing_2019_B.s5temp1, &Racing_2019_B.sf_s5t1);
  u0_1 = Racing_2019_B.sf_s5t4.y;
  u1_1 = Racing_2019_B.sf_s5t3.y;
  if ((u0_1 > u1_1) || rtIsNaNF(u1_1)) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s5t2.y;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s5t1.y;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  Racing_2019_B.Max_Temp_s5t = u1_1;
  Racing_2019_B.DataTypeConversion7_e = (real32_T)Racing_2019_B.SFunction1_o4_f;
  Racing_2019_B.s6temp4 = Racing_2019_P.s6temp4_Gain *
    Racing_2019_B.DataTypeConversion7_e;
  Racing_2019_s1t4(Racing_2019_B.s6temp4, &Racing_2019_B.sf_s6t4);
  Racing_2019_B.DataTypeConversion3_mt = (real32_T)
    Racing_2019_B.SFunction1_o3_j50;
  Racing_2019_B.s6temp3 = Racing_2019_P.s6temp3_Gain *
    Racing_2019_B.DataTypeConversion3_mt;
  Racing_2019_s1t1(Racing_2019_B.s6temp3, &Racing_2019_B.sf_s6t3);
  Racing_2019_B.DataTypeConversion2_b = (real32_T)Racing_2019_B.SFunction1_o2_lj;
  Racing_2019_B.s6temp2 = Racing_2019_P.s6temp2_Gain *
    Racing_2019_B.DataTypeConversion2_b;
  Racing_2019_s1t1(Racing_2019_B.s6temp2, &Racing_2019_B.sf_s6t2);
  Racing_2019_B.DataTypeConversion_h = (real32_T)Racing_2019_B.SFunction1_o1_fz;
  Racing_2019_B.s6temp1 = Racing_2019_P.s6temp1_Gain *
    Racing_2019_B.DataTypeConversion_h;
  Racing_2019_s1t1(Racing_2019_B.s6temp1, &Racing_2019_B.sf_s6t1);
  u0_1 = Racing_2019_B.sf_s6t4.y;
  u1_1 = Racing_2019_B.sf_s6t3.y;
  if ((u0_1 > u1_1) || rtIsNaNF(u1_1)) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s6t2.y;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s6t1.y;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  Racing_2019_B.Max_Temp_s6t = u1_1;
  Racing_2019_B.DataTypeConversion7_n = (real32_T)Racing_2019_B.SFunction1_o4_fl;
  Racing_2019_B.s7temp4 = Racing_2019_P.s7temp4_Gain *
    Racing_2019_B.DataTypeConversion7_n;
  Racing_2019_B.y = 1.0F / (((real32_T)log(10000.0F * Racing_2019_B.s7temp4 /
    (5.0F - Racing_2019_B.s7temp4 * 0.0015F) / 100000.0F) * 2.60597E-6F *
    (real32_T)log(10000.0F * Racing_2019_B.s7temp4 / (5.0F -
    Racing_2019_B.s7temp4) / 10000.0F) + ((real32_T)log(10000.0F *
    Racing_2019_B.s7temp4 / (5.0F - Racing_2019_B.s7temp4) / 10000.0F) *
    0.000256524F + 0.00335401599F)) + (real32_T)log(100000.0F *
    Racing_2019_B.s7temp4 / (5.0F - Racing_2019_B.s7temp4) / 10000.0F) *
    6.32926E-8F * (real32_T)log(10000.0F * Racing_2019_B.s7temp4 / (5.0F -
    Racing_2019_B.s7temp4) / 10000.0F) * (real32_T)log(10000.0F *
    Racing_2019_B.s7temp4 / (5.0F - Racing_2019_B.s7temp4) / 10000.0F)) -
    272.15F;
  Racing_2019_B.DataTypeConversion3_p = (real32_T)Racing_2019_B.SFunction1_o3_km;
  Racing_2019_B.s7temp3 = Racing_2019_P.s7temp3_Gain *
    Racing_2019_B.DataTypeConversion3_p;
  Racing_2019_s7t1(Racing_2019_B.s7temp3, &Racing_2019_B.sf_s7t3);
  Racing_2019_B.DataTypeConversion2_ps = (real32_T)
    Racing_2019_B.SFunction1_o2_cn;
  Racing_2019_B.s7temp2 = Racing_2019_P.s7temp2_Gain *
    Racing_2019_B.DataTypeConversion2_ps;
  Racing_2019_s7t1(Racing_2019_B.s7temp2, &Racing_2019_B.sf_s7t2);
  Racing_2019_B.DataTypeConversion_ng = (real32_T)Racing_2019_B.SFunction1_o1_p;
  Racing_2019_B.s7temp1 = Racing_2019_P.s7temp1_Gain *
    Racing_2019_B.DataTypeConversion_ng;
  Racing_2019_s7t1(Racing_2019_B.s7temp1, &Racing_2019_B.sf_s7t1);
  u0_1 = Racing_2019_B.y;
  u1_1 = Racing_2019_B.sf_s7t3.y;
  if ((u0_1 > u1_1) || rtIsNaNF(u1_1)) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s7t2.y;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s7t1.y;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  Racing_2019_B.Max_Temp_s7t = u1_1;
  u0_1 = Racing_2019_B.RateTransition4_e;
  u1_1 = Racing_2019_B.Max_Temp_s2t;
  if ((u0_1 > u1_1) || rtIsNaNF(u1_1)) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.Max_Temp_s3t;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.Max_Temp_s4t;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.Max_Temp_s5t;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.Max_Temp_s6t;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.Max_Temp_s7t;
  if (!((u1_1 > u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  Racing_2019_B.MaxTemperature = u1_1;
  u0_0 = Racing_2019_B.s2c12;
  u1_0 = Racing_2019_B.s2c11;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s2c10;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s2c9;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s2q3 = u1_0;
  u0_0 = Racing_2019_B.s2c8;
  u1_0 = Racing_2019_B.s2c7;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s2c6;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s2c5;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s2q2 = u1_0;
  u0_0 = Racing_2019_B.s2c4;
  u1_0 = Racing_2019_B.s2c3;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s2c2;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s2c1;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s2q1 = u1_0;
  u0_0 = Racing_2019_B.Min_Voltage_s2q3;
  u1_0 = Racing_2019_B.Min_Voltage_s2q2;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Min_Voltage_s2q1;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s2 = u1_0;
  u0_0 = Racing_2019_B.s3c12;
  u1_0 = Racing_2019_B.s3c11;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s3c10;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s3c9;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s3q3 = u1_0;
  u0_0 = Racing_2019_B.s3c8;
  u1_0 = Racing_2019_B.s3c7;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s3c6;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s3c5;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s3q2 = u1_0;
  u0_0 = Racing_2019_B.s3c4;
  u1_0 = Racing_2019_B.s3c3;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s3c2;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s3c1;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s3q1 = u1_0;
  u0_0 = Racing_2019_B.Min_Voltage_s3q3;
  u1_0 = Racing_2019_B.Min_Voltage_s3q2;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Min_Voltage_s3q1;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s3 = u1_0;
  u0_0 = Racing_2019_B.s4c12;
  u1_0 = Racing_2019_B.s4c11;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s4c10;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s4c9;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s4q3 = u1_0;
  u0_0 = Racing_2019_B.s4c8;
  u1_0 = Racing_2019_B.s4c7;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s4c6;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s4c5;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s4q2 = u1_0;
  u0_0 = Racing_2019_B.s4c4;
  u1_0 = Racing_2019_B.s4c3;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s4c2;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s4c1;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s4q1 = u1_0;
  u0_0 = Racing_2019_B.Min_Voltage_s4q3;
  u1_0 = Racing_2019_B.Min_Voltage_s4q2;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Min_Voltage_s4q1;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s4 = u1_0;
  u0_0 = Racing_2019_B.s5c12;
  u1_0 = Racing_2019_B.s5c11;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s5c10;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s5c9;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s5q3 = u1_0;
  u0_0 = Racing_2019_B.s5c8;
  u1_0 = Racing_2019_B.s5c7;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s5c6;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s5c5;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s5q2 = u1_0;
  u0_0 = Racing_2019_B.s5c4;
  u1_0 = Racing_2019_B.s5c3;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s5c2;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s5c1;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s5q1 = u1_0;
  u0_0 = Racing_2019_B.Min_Voltage_s5q3;
  u1_0 = Racing_2019_B.Min_Voltage_s5q2;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Min_Voltage_s5q1;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s5 = u1_0;
  u0_0 = Racing_2019_B.s6c12;
  u1_0 = Racing_2019_B.s6c11;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s6c10;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s6c9;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s6q3 = u1_0;
  u0_0 = Racing_2019_B.s6c8;
  u1_0 = Racing_2019_B.s6c7;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s6c6;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s6c5;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s6q2 = u1_0;
  u0_0 = Racing_2019_B.s6c4;
  u1_0 = Racing_2019_B.s6c3;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s6c2;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s6c1;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s6q1 = u1_0;
  u0_0 = Racing_2019_B.Min_Voltage_s6q3;
  u1_0 = Racing_2019_B.Min_Voltage_s6q2;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Min_Voltage_s6q1;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s6 = u1_0;
  u0_0 = Racing_2019_B.s7c12;
  u1_0 = Racing_2019_B.s7c11;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s7c10;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s7c9;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s7q3 = u1_0;
  u0_0 = Racing_2019_B.s7c8;
  u1_0 = Racing_2019_B.s7c7;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s7c6;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s7c5;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s7q2 = u1_0;
  u0_0 = Racing_2019_B.s7c4;
  u1_0 = Racing_2019_B.s7c3;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s7c2;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.s7c1;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s7q1 = u1_0;
  u0_0 = Racing_2019_B.Min_Voltage_s7q3;
  u1_0 = Racing_2019_B.Min_Voltage_s7q2;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Min_Voltage_s7q1;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.Min_Voltage_s7 = u1_0;
  u0_0 = (real_T)Racing_2019_B.Min_Voltage_s1 * 2.9802322387695313E-8;
  u1_0 = Racing_2019_B.Min_Voltage_s2;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Min_Voltage_s3;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Min_Voltage_s4;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Min_Voltage_s5;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Min_Voltage_s6;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Min_Voltage_s7;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.MinBatteryVoltage = u1_0;
  u0_0 = (real_T)Racing_2019_B.Add_Voltage_s1 * 2.9802322387695313E-8;
  u1_0 = Racing_2019_B.Add_Voltage_s2;
  if ((u0_0 < u1_0) || rtIsNaN(u1_0)) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Add_Voltage_s3;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Add_Voltage_s4;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Add_Voltage_s5;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Add_Voltage_s6;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  u0_0 = Racing_2019_B.Add_Voltage_s7;
  if (!((u1_0 < u0_0) || rtIsNaN(u0_0))) {
    u1_0 = u0_0;
  }

  Racing_2019_B.MinSegmentVoltage = u1_0;
  u0_1 = Racing_2019_B.sf_s1t4.y;
  u1_1 = Racing_2019_B.sf_s1t3.y;
  if ((u0_1 < u1_1) || rtIsNaNF(u1_1)) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s1t2.y;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s1t1.y;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  Racing_2019_B.Min_Temp_s1t = u1_1;
  Racing_2019_B.RateTransition5_h = Racing_2019_B.Min_Temp_s1t;
  u0_1 = Racing_2019_B.sf_s2t4.y;
  u1_1 = Racing_2019_B.sf_s2t3.y;
  if ((u0_1 < u1_1) || rtIsNaNF(u1_1)) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s2t2.y;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s2t1.y;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  Racing_2019_B.Min_Temp_s2t = u1_1;
  u0_1 = Racing_2019_B.sf_s3t4.y;
  u1_1 = Racing_2019_B.sf_s3t3.y;
  if ((u0_1 < u1_1) || rtIsNaNF(u1_1)) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s3t2.y;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s3t1.y;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  Racing_2019_B.Min_Temp_s3t = u1_1;
  u0_1 = Racing_2019_B.sf_s4t4.y;
  u1_1 = Racing_2019_B.sf_s4t3.y;
  if ((u0_1 < u1_1) || rtIsNaNF(u1_1)) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s4t2.y;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s4t1.y;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  Racing_2019_B.Min_Temp_s4t = u1_1;
  u0_1 = Racing_2019_B.sf_s5t4.y;
  u1_1 = Racing_2019_B.sf_s5t3.y;
  if ((u0_1 < u1_1) || rtIsNaNF(u1_1)) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s5t2.y;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s5t1.y;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  Racing_2019_B.Min_Temp_s5t = u1_1;
  u0_1 = Racing_2019_B.sf_s6t4.y;
  u1_1 = Racing_2019_B.sf_s6t3.y;
  if ((u0_1 < u1_1) || rtIsNaNF(u1_1)) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s6t2.y;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s6t1.y;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  Racing_2019_B.Min_Temp_s6t = u1_1;
  u0_1 = Racing_2019_B.y;
  u1_1 = Racing_2019_B.sf_s7t3.y;
  if ((u0_1 < u1_1) || rtIsNaNF(u1_1)) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s7t2.y;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.sf_s7t1.y;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  Racing_2019_B.Min_Temp_s7t = u1_1;
  u0_1 = Racing_2019_B.RateTransition5_h;
  u1_1 = Racing_2019_B.Min_Temp_s2t;
  if ((u0_1 < u1_1) || rtIsNaNF(u1_1)) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.Min_Temp_s3t;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.Min_Temp_s4t;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.Min_Temp_s5t;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.Min_Temp_s6t;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  u0_1 = Racing_2019_B.Min_Temp_s7t;
  if (!((u1_1 < u0_1) || rtIsNaNF(u0_1))) {
    u1_1 = u0_1;
  }

  Racing_2019_B.MinTemperature = u1_1;
  tmp = Racing_2019_P.Gain_s1c1_Gain;
  maxV = Racing_2019_B.s1c1;
  uMultiWordMul(&tmp, 1, &maxV, 1, &tmp_1.chunks[0U], 2);
  Racing_2019_B.Gain_s1c1 = tmp_1;
  tmp_1 = Racing_2019_B.Gain_s1c1;
  uMultiWordShr(&tmp_1.chunks[0U], 2, 47U, &tmp_2.chunks[0U], 2);
  Racing_2019_B.DataTypeConversion14_p = (uint16_T)MultiWord2uLong
    (&tmp_2.chunks[0U]);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s1c1_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion14_p);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  tmp = Racing_2019_P.Gain_s1c10_Gain;
  maxV = Racing_2019_B.s1c10;
  uMultiWordMul(&tmp, 1, &maxV, 1, &tmp_1.chunks[0U], 2);
  Racing_2019_B.Gain_s1c10 = tmp_1;
  tmp_1 = Racing_2019_B.Gain_s1c10;
  uMultiWordShr(&tmp_1.chunks[0U], 2, 47U, &tmp_3.chunks[0U], 2);
  Racing_2019_B.DataTypeConversion23 = (uint16_T)MultiWord2uLong(&tmp_3.chunks
    [0U]);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s1c10_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion23);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  tmp = Racing_2019_P.Gain_s1c11_Gain;
  maxV = Racing_2019_B.s1c11;
  uMultiWordMul(&tmp, 1, &maxV, 1, &tmp_1.chunks[0U], 2);
  Racing_2019_B.Gain_s1c11 = tmp_1;
  tmp_1 = Racing_2019_B.Gain_s1c11;
  uMultiWordShr(&tmp_1.chunks[0U], 2, 47U, &tmp_4.chunks[0U], 2);
  Racing_2019_B.DataTypeConversion20 = (uint16_T)MultiWord2uLong(&tmp_4.chunks
    [0U]);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s1c11_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion20);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  tmp = Racing_2019_P.Gain_s1c12_Gain;
  maxV = Racing_2019_B.s1c12;
  uMultiWordMul(&tmp, 1, &maxV, 1, &tmp_1.chunks[0U], 2);
  Racing_2019_B.Gain_s1c12 = tmp_1;
  tmp_1 = Racing_2019_B.Gain_s1c12;
  uMultiWordShr(&tmp_1.chunks[0U], 2, 47U, &tmp_5.chunks[0U], 2);
  Racing_2019_B.DataTypeConversion21 = (uint16_T)MultiWord2uLong(&tmp_5.chunks
    [0U]);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s1c12_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion21);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  tmp = Racing_2019_P.Gain_s1c2_Gain;
  maxV = Racing_2019_B.s1c2;
  uMultiWordMul(&tmp, 1, &maxV, 1, &tmp_1.chunks[0U], 2);
  Racing_2019_B.Gain_s1c2 = tmp_1;
  tmp_1 = Racing_2019_B.Gain_s1c2;
  uMultiWordShr(&tmp_1.chunks[0U], 2, 47U, &tmp_6.chunks[0U], 2);
  Racing_2019_B.DataTypeConversion15_d = (uint16_T)MultiWord2uLong
    (&tmp_6.chunks[0U]);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s1c2_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion15_d);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  tmp = Racing_2019_P.Gain_s1c3_Gain;
  maxV = Racing_2019_B.s1c3;
  uMultiWordMul(&tmp, 1, &maxV, 1, &tmp_1.chunks[0U], 2);
  Racing_2019_B.Gain_s1c3 = tmp_1;
  tmp_1 = Racing_2019_B.Gain_s1c3;
  uMultiWordShr(&tmp_1.chunks[0U], 2, 47U, &tmp_7.chunks[0U], 2);
  Racing_2019_B.DataTypeConversion12 = (uint16_T)MultiWord2uLong(&tmp_7.chunks
    [0U]);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s1c3_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion12);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  tmp = Racing_2019_P.Gain_s1c4_Gain;
  maxV = Racing_2019_B.s1c4;
  uMultiWordMul(&tmp, 1, &maxV, 1, &tmp_1.chunks[0U], 2);
  Racing_2019_B.Gain_s1c4 = tmp_1;
  tmp_1 = Racing_2019_B.Gain_s1c4;
  uMultiWordShr(&tmp_1.chunks[0U], 2, 47U, &tmp_8.chunks[0U], 2);
  Racing_2019_B.DataTypeConversion13_i = (uint16_T)MultiWord2uLong
    (&tmp_8.chunks[0U]);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s1c4_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion13_i);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  tmp = Racing_2019_P.Gain_s1c5_Gain;
  maxV = Racing_2019_B.s1c5;
  uMultiWordMul(&tmp, 1, &maxV, 1, &tmp_1.chunks[0U], 2);
  Racing_2019_B.Gain_s1c5 = tmp_1;
  tmp_1 = Racing_2019_B.Gain_s1c5;
  uMultiWordShr(&tmp_1.chunks[0U], 2, 47U, &tmp_9.chunks[0U], 2);
  Racing_2019_B.DataTypeConversion18 = (uint16_T)MultiWord2uLong(&tmp_9.chunks
    [0U]);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s1c5_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion18);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  tmp = Racing_2019_P.Gain_s1c6_Gain;
  maxV = Racing_2019_B.s1c6;
  uMultiWordMul(&tmp, 1, &maxV, 1, &tmp_1.chunks[0U], 2);
  Racing_2019_B.Gain_s1c6 = tmp_1;
  tmp_1 = Racing_2019_B.Gain_s1c6;
  uMultiWordShr(&tmp_1.chunks[0U], 2, 47U, &tmp_a.chunks[0U], 2);
  Racing_2019_B.DataTypeConversion19 = (uint16_T)MultiWord2uLong(&tmp_a.chunks
    [0U]);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s1c6_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion19);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  tmp = Racing_2019_P.Gain_s1c7_Gain;
  maxV = Racing_2019_B.s1c7;
  uMultiWordMul(&tmp, 1, &maxV, 1, &tmp_1.chunks[0U], 2);
  Racing_2019_B.Gain_s1c7 = tmp_1;
  tmp_1 = Racing_2019_B.Gain_s1c7;
  uMultiWordShr(&tmp_1.chunks[0U], 2, 47U, &tmp_b.chunks[0U], 2);
  Racing_2019_B.DataTypeConversion16_i = (uint16_T)MultiWord2uLong
    (&tmp_b.chunks[0U]);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s1c7_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion16_i);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  tmp = Racing_2019_P.Gain_s1c8_Gain;
  maxV = Racing_2019_B.s1c8;
  uMultiWordMul(&tmp, 1, &maxV, 1, &tmp_1.chunks[0U], 2);
  Racing_2019_B.Gain_s1c8 = tmp_1;
  tmp_1 = Racing_2019_B.Gain_s1c8;
  uMultiWordShr(&tmp_1.chunks[0U], 2, 47U, &tmp_c.chunks[0U], 2);
  Racing_2019_B.DataTypeConversion17 = (uint16_T)MultiWord2uLong(&tmp_c.chunks
    [0U]);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s1c8_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion17);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  tmp = Racing_2019_P.Gain_s1c9_Gain;
  maxV = Racing_2019_B.s1c9;
  uMultiWordMul(&tmp, 1, &maxV, 1, &tmp_1.chunks[0U], 2);
  Racing_2019_B.Gain_s1c9 = tmp_1;
  tmp_1 = Racing_2019_B.Gain_s1c9;
  uMultiWordShr(&tmp_1.chunks[0U], 2, 47U, &tmp_d.chunks[0U], 2);
  Racing_2019_B.DataTypeConversion22 = (uint16_T)MultiWord2uLong(&tmp_d.chunks
    [0U]);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s1c9_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion22);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion2_ei = (Racing_2019_B.SFunction1_o5_o != 0.0);
  Racing_2019_B.UnitDelay_e = Racing_2019_DW.UnitDelay_DSTATE_a;
  switch ((int32_T)Racing_2019_P.EdgeDetector2_model) {
   case 1:
    Racing_2019_B.MultiportSwitch_c[0] = Racing_2019_P.posedge_Value_p[0];
    Racing_2019_B.MultiportSwitch_c[1] = Racing_2019_P.posedge_Value_p[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_c[0] = Racing_2019_P.negedge_Value_f[0];
    Racing_2019_B.MultiportSwitch_c[1] = Racing_2019_P.negedge_Value_f[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_c[0] = Racing_2019_P.eitheredge_Value_pd[0];
    Racing_2019_B.MultiportSwitch_c[1] = Racing_2019_P.eitheredge_Value_pd[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_c[0],
    Racing_2019_B.DataTypeConversion2_ei, Racing_2019_B.UnitDelay_e,
    &Racing_2019_B.POSITIVEEdge_h);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_c[1],
    Racing_2019_B.DataTypeConversion2_ei, Racing_2019_B.UnitDelay_e,
    &Racing_2019_B.NEGATIVEEdge_pb);
  Racing_2019_B.LogicalOperator1_k =
    (Racing_2019_B.POSITIVEEdge_h.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_pb.RelationalOperator1);
  Racing_2019_B.DataTypeConversion5_em = Racing_2019_B.LogicalOperator1_k;
  Racing_2019_B.BMS_CAN_205_Counter =
    Racing_2019_DW.BMS_CAN_205_Counter_PreviousInp;
  Racing_2019_B.Add1_d = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion5_em + Racing_2019_B.BMS_CAN_205_Counter);
  Racing_2019_B.DataTypeConversion2_kk = (Racing_2019_B.SFunction1_o5 != 0.0);
  Racing_2019_B.UnitDelay_g = Racing_2019_DW.UnitDelay_DSTATE_b;
  switch ((int32_T)Racing_2019_P.EdgeDetector3_model) {
   case 1:
    Racing_2019_B.MultiportSwitch_if[0] = Racing_2019_P.posedge_Value_m[0];
    Racing_2019_B.MultiportSwitch_if[1] = Racing_2019_P.posedge_Value_m[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_if[0] = Racing_2019_P.negedge_Value_p[0];
    Racing_2019_B.MultiportSwitch_if[1] = Racing_2019_P.negedge_Value_p[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_if[0] = Racing_2019_P.eitheredge_Value_c[0];
    Racing_2019_B.MultiportSwitch_if[1] = Racing_2019_P.eitheredge_Value_c[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_if[0],
    Racing_2019_B.DataTypeConversion2_kk, Racing_2019_B.UnitDelay_g,
    &Racing_2019_B.POSITIVEEdge_n);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_if[1],
    Racing_2019_B.DataTypeConversion2_kk, Racing_2019_B.UnitDelay_g,
    &Racing_2019_B.NEGATIVEEdge_h);
  Racing_2019_B.LogicalOperator1_n =
    (Racing_2019_B.POSITIVEEdge_n.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_h.RelationalOperator1);
  Racing_2019_B.DataTypeConversion6_m = Racing_2019_B.LogicalOperator1_n;
  Racing_2019_B.BMS_CAN_206_Counter =
    Racing_2019_DW.BMS_CAN_206_Counter_PreviousInp;
  Racing_2019_B.Add2_f = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion6_m
    + Racing_2019_B.BMS_CAN_206_Counter);
  Racing_2019_B.DataTypeConversion2_kt = (Racing_2019_B.SFunction1_o5_c != 0.0);
  Racing_2019_B.UnitDelay_dt = Racing_2019_DW.UnitDelay_DSTATE_f;
  switch ((int32_T)Racing_2019_P.EdgeDetector1_model) {
   case 1:
    Racing_2019_B.MultiportSwitch_g[0] = Racing_2019_P.posedge_Value_g[0];
    Racing_2019_B.MultiportSwitch_g[1] = Racing_2019_P.posedge_Value_g[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_g[0] = Racing_2019_P.negedge_Value_m[0];
    Racing_2019_B.MultiportSwitch_g[1] = Racing_2019_P.negedge_Value_m[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_g[0] = Racing_2019_P.eitheredge_Value_py[0];
    Racing_2019_B.MultiportSwitch_g[1] = Racing_2019_P.eitheredge_Value_py[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_g[0],
    Racing_2019_B.DataTypeConversion2_kt, Racing_2019_B.UnitDelay_dt,
    &Racing_2019_B.POSITIVEEdge_j);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_g[1],
    Racing_2019_B.DataTypeConversion2_kt, Racing_2019_B.UnitDelay_dt,
    &Racing_2019_B.NEGATIVEEdge_e);
  Racing_2019_B.LogicalOperator1_ka =
    (Racing_2019_B.POSITIVEEdge_j.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_e.RelationalOperator1);
  Racing_2019_B.DataTypeConversion4_co = Racing_2019_B.LogicalOperator1_ka;
  Racing_2019_B.BMS_CAN_204_Counter =
    Racing_2019_DW.BMS_CAN_204_Counter_PreviousInp;
  Racing_2019_B.Add4 = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion4_co
    + Racing_2019_B.BMS_CAN_204_Counter);
  Racing_2019_B.Gain_s1t1 = Racing_2019_P.Gain_s1t1_Gain *
    Racing_2019_B.sf_s1t1.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s1t1_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s1t1);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s1t2 = Racing_2019_P.Gain_s1t2_Gain *
    Racing_2019_B.sf_s1t2.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s1t2_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s1t2);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s1t3 = Racing_2019_P.Gain_s1t3_Gain *
    Racing_2019_B.sf_s1t3.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s1t3_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s1t3);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s1t4 = Racing_2019_P.Gain_s1t4_Gain *
    Racing_2019_B.sf_s1t4.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s1t4_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s1t4);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion2_fv = (Racing_2019_B.SFunction1_o5_az != 0.0);
  Racing_2019_B.UnitDelay_b = Racing_2019_DW.UnitDelay_DSTATE_cv;
  switch ((int32_T)Racing_2019_P.EdgeDetector4_model) {
   case 1:
    Racing_2019_B.MultiportSwitch_cc[0] = Racing_2019_P.posedge_Value_i[0];
    Racing_2019_B.MultiportSwitch_cc[1] = Racing_2019_P.posedge_Value_i[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_cc[0] = Racing_2019_P.negedge_Value_n[0];
    Racing_2019_B.MultiportSwitch_cc[1] = Racing_2019_P.negedge_Value_n[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_cc[0] = Racing_2019_P.eitheredge_Value_n[0];
    Racing_2019_B.MultiportSwitch_cc[1] = Racing_2019_P.eitheredge_Value_n[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_cc[0],
    Racing_2019_B.DataTypeConversion2_fv, Racing_2019_B.UnitDelay_b,
    &Racing_2019_B.POSITIVEEdge_c);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_cc[1],
    Racing_2019_B.DataTypeConversion2_fv, Racing_2019_B.UnitDelay_b,
    &Racing_2019_B.NEGATIVEEdge_i);
  Racing_2019_B.LogicalOperator1_gr =
    (Racing_2019_B.POSITIVEEdge_c.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_i.RelationalOperator1);
  Racing_2019_B.DataTypeConversion1_f = Racing_2019_B.LogicalOperator1_gr;
  Racing_2019_B.BMS_CAN_225_Counter =
    Racing_2019_DW.BMS_CAN_225_Counter_PreviousInp;
  Racing_2019_B.Add3 = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion1_f +
    Racing_2019_B.BMS_CAN_225_Counter);
  Racing_2019_B.Gain_s2c1 = Racing_2019_P.Gain_s2c1_Gain * Racing_2019_B.s2c1;
  u1_0 = floor(Racing_2019_B.Gain_s2c1);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion14_l = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s2c1_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion14_l);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s2c10 = Racing_2019_P.Gain_s2c10_Gain * Racing_2019_B.s2c10;
  u1_0 = floor(Racing_2019_B.Gain_s2c10);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion19_h = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s2c10_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion19_h);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s2c11 = Racing_2019_P.Gain_s2c11_Gain * Racing_2019_B.s2c11;
  u1_0 = floor(Racing_2019_B.Gain_s2c11);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion16_o = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s2c11_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion16_o);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s2c12 = Racing_2019_P.Gain_s2c12_Gain * Racing_2019_B.s2c12;
  u1_0 = floor(Racing_2019_B.Gain_s2c12);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion17_l = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s2c12_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion17_l);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s2c2 = Racing_2019_P.Gain_s2c2_Gain * Racing_2019_B.s2c2;
  u1_0 = floor(Racing_2019_B.Gain_s2c2);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion15_a = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s2c2_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion15_a);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s2c3 = Racing_2019_P.Gain_s2c3_Gain * Racing_2019_B.s2c3;
  u1_0 = floor(Racing_2019_B.Gain_s2c3);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion12_d = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s2c3_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion12_d);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s2c4 = Racing_2019_P.Gain_s2c4_Gain * Racing_2019_B.s2c4;
  u1_0 = floor(Racing_2019_B.Gain_s2c4);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion13_n = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s2c4_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion13_n);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s2c5 = Racing_2019_P.Gain_s2c5_Gain * Racing_2019_B.s2c5;
  u1_0 = floor(Racing_2019_B.Gain_s2c5);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion10_g = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s2c5_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion10_g);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s2c6 = Racing_2019_P.Gain_s2c6_Gain * Racing_2019_B.s2c6;
  u1_0 = floor(Racing_2019_B.Gain_s2c6);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion11_j = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s2c6_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion11_j);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s2c7 = Racing_2019_P.Gain_s2c7_Gain * Racing_2019_B.s2c7;
  u1_0 = floor(Racing_2019_B.Gain_s2c7);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion8_b = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s2c7_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion8_b);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s2c8 = Racing_2019_P.Gain_s2c8_Gain * Racing_2019_B.s2c8;
  u1_0 = floor(Racing_2019_B.Gain_s2c8);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion9_li = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s2c8_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion9_li);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s2c9 = Racing_2019_P.Gain_s2c9_Gain * Racing_2019_B.s2c9;
  u1_0 = floor(Racing_2019_B.Gain_s2c9);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion18_d = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s2c9_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion18_d);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s2t1 = Racing_2019_P.Gain_s2t1_Gain *
    Racing_2019_B.sf_s2t1.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s2t1_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s2t1);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s2t2 = Racing_2019_P.Gain_s2t2_Gain *
    Racing_2019_B.sf_s2t2.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s2t2_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s2t2);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s2t3 = Racing_2019_P.Gain_s2t3_Gain *
    Racing_2019_B.sf_s2t3.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s2t3_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s2t3);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s2t4 = Racing_2019_P.Gain_s2t4_Gain *
    Racing_2019_B.sf_s2t4.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s2t4_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s2t4);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion2_g = (Racing_2019_B.SFunction1_o5_g != 0.0);
  Racing_2019_B.UnitDelay_j = Racing_2019_DW.UnitDelay_DSTATE_ba;
  switch ((int32_T)Racing_2019_P.EdgeDetector2_model_d) {
   case 1:
    Racing_2019_B.MultiportSwitch_k[0] = Racing_2019_P.posedge_Value_n[0];
    Racing_2019_B.MultiportSwitch_k[1] = Racing_2019_P.posedge_Value_n[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_k[0] = Racing_2019_P.negedge_Value_c[0];
    Racing_2019_B.MultiportSwitch_k[1] = Racing_2019_P.negedge_Value_c[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_k[0] = Racing_2019_P.eitheredge_Value_d[0];
    Racing_2019_B.MultiportSwitch_k[1] = Racing_2019_P.eitheredge_Value_d[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_k[0],
    Racing_2019_B.DataTypeConversion2_g, Racing_2019_B.UnitDelay_j,
    &Racing_2019_B.POSITIVEEdge_na);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_k[1],
    Racing_2019_B.DataTypeConversion2_g, Racing_2019_B.UnitDelay_j,
    &Racing_2019_B.NEGATIVEEdge_eh);
  Racing_2019_B.LogicalOperator1_o =
    (Racing_2019_B.POSITIVEEdge_na.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_eh.RelationalOperator1);
  Racing_2019_B.DataTypeConversion5_b = Racing_2019_B.LogicalOperator1_o;
  Racing_2019_B.BMS_CAN_208_Counter =
    Racing_2019_DW.BMS_CAN_208_Counter_PreviousInp;
  Racing_2019_B.Add1_a = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion5_b
    + Racing_2019_B.BMS_CAN_208_Counter);
  Racing_2019_B.DataTypeConversion2_o0 = (Racing_2019_B.SFunction1_o5_cj != 0.0);
  Racing_2019_B.UnitDelay_bp = Racing_2019_DW.UnitDelay_DSTATE_bd;
  switch ((int32_T)Racing_2019_P.EdgeDetector3_model_o) {
   case 1:
    Racing_2019_B.MultiportSwitch_gt[0] = Racing_2019_P.posedge_Value_pl[0];
    Racing_2019_B.MultiportSwitch_gt[1] = Racing_2019_P.posedge_Value_pl[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_gt[0] = Racing_2019_P.negedge_Value_hk[0];
    Racing_2019_B.MultiportSwitch_gt[1] = Racing_2019_P.negedge_Value_hk[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_gt[0] = Racing_2019_P.eitheredge_Value_g[0];
    Racing_2019_B.MultiportSwitch_gt[1] = Racing_2019_P.eitheredge_Value_g[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_gt[0],
    Racing_2019_B.DataTypeConversion2_o0, Racing_2019_B.UnitDelay_bp,
    &Racing_2019_B.POSITIVEEdge_nm);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_gt[1],
    Racing_2019_B.DataTypeConversion2_o0, Racing_2019_B.UnitDelay_bp,
    &Racing_2019_B.NEGATIVEEdge_b);
  Racing_2019_B.LogicalOperator1_m =
    (Racing_2019_B.POSITIVEEdge_nm.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_b.RelationalOperator1);
  Racing_2019_B.DataTypeConversion6_n = Racing_2019_B.LogicalOperator1_m;
  Racing_2019_B.BMS_CAN_209_Counter =
    Racing_2019_DW.BMS_CAN_209_Counter_PreviousInp;
  Racing_2019_B.Add2_e = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion6_n
    + Racing_2019_B.BMS_CAN_209_Counter);
  Racing_2019_B.DataTypeConversion2_dd = (Racing_2019_B.SFunction1_o5_i != 0.0);
  Racing_2019_B.UnitDelay_o = Racing_2019_DW.UnitDelay_DSTATE_n;
  switch ((int32_T)Racing_2019_P.EdgeDetector4_model_d) {
   case 1:
    Racing_2019_B.MultiportSwitch_k5[0] = Racing_2019_P.posedge_Value_p4[0];
    Racing_2019_B.MultiportSwitch_k5[1] = Racing_2019_P.posedge_Value_p4[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_k5[0] = Racing_2019_P.negedge_Value_g[0];
    Racing_2019_B.MultiportSwitch_k5[1] = Racing_2019_P.negedge_Value_g[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_k5[0] = Racing_2019_P.eitheredge_Value_e[0];
    Racing_2019_B.MultiportSwitch_k5[1] = Racing_2019_P.eitheredge_Value_e[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_k5[0],
    Racing_2019_B.DataTypeConversion2_dd, Racing_2019_B.UnitDelay_o,
    &Racing_2019_B.POSITIVEEdge_o);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_k5[1],
    Racing_2019_B.DataTypeConversion2_dd, Racing_2019_B.UnitDelay_o,
    &Racing_2019_B.NEGATIVEEdge_n);
  Racing_2019_B.LogicalOperator1_i =
    (Racing_2019_B.POSITIVEEdge_o.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_n.RelationalOperator1);
  Racing_2019_B.DataTypeConversion1_b = Racing_2019_B.LogicalOperator1_i;
  Racing_2019_B.BMS_CAN_226_Counter =
    Racing_2019_DW.BMS_CAN_226_Counter_PreviousInp;
  Racing_2019_B.Add3_l = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion1_b
    + Racing_2019_B.BMS_CAN_226_Counter);
  Racing_2019_B.DataTypeConversion2_nu = (Racing_2019_B.SFunction1_o5_m != 0.0);
  Racing_2019_B.UnitDelay_n = Racing_2019_DW.UnitDelay_DSTATE_h;
  switch ((int32_T)Racing_2019_P.EdgeDetector1_model_h) {
   case 1:
    Racing_2019_B.MultiportSwitch_e[0] = Racing_2019_P.posedge_Value_j[0];
    Racing_2019_B.MultiportSwitch_e[1] = Racing_2019_P.posedge_Value_j[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_e[0] = Racing_2019_P.negedge_Value_o[0];
    Racing_2019_B.MultiportSwitch_e[1] = Racing_2019_P.negedge_Value_o[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_e[0] = Racing_2019_P.eitheredge_Value_l[0];
    Racing_2019_B.MultiportSwitch_e[1] = Racing_2019_P.eitheredge_Value_l[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_e[0],
    Racing_2019_B.DataTypeConversion2_nu, Racing_2019_B.UnitDelay_n,
    &Racing_2019_B.POSITIVEEdge_oy);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_e[1],
    Racing_2019_B.DataTypeConversion2_nu, Racing_2019_B.UnitDelay_n,
    &Racing_2019_B.NEGATIVEEdge_o);
  Racing_2019_B.LogicalOperator1_k5 =
    (Racing_2019_B.POSITIVEEdge_oy.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_o.RelationalOperator1);
  Racing_2019_B.DataTypeConversion4_d = Racing_2019_B.LogicalOperator1_k5;
  Racing_2019_B.BMS_CAN_207_Counter =
    Racing_2019_DW.BMS_CAN_207_Counter_PreviousInp;
  Racing_2019_B.Add4_j = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion4_d
    + Racing_2019_B.BMS_CAN_207_Counter);
  Racing_2019_B.Gain_s3c1 = Racing_2019_P.Gain_s3c1_Gain * Racing_2019_B.s3c1;
  u1_0 = floor(Racing_2019_B.Gain_s3c1);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion14_lw = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s3c1_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion14_lw);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s3c10 = Racing_2019_P.Gain_s3c10_Gain * Racing_2019_B.s3c10;
  u1_0 = floor(Racing_2019_B.Gain_s3c10);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion19_p = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s3c10_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion19_p);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s3c11 = Racing_2019_P.Gain_s3c11_Gain * Racing_2019_B.s3c11;
  u1_0 = floor(Racing_2019_B.Gain_s3c11);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion16_m = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s3c11_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion16_m);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s3c12 = Racing_2019_P.Gain_s3c12_Gain * Racing_2019_B.s3c12;
  u1_0 = floor(Racing_2019_B.Gain_s3c12);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion17_d = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s3c12_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion17_d);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s3c2 = Racing_2019_P.Gain_s3c2_Gain * Racing_2019_B.s3c2;
  u1_0 = floor(Racing_2019_B.Gain_s3c2);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion15_n = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s3c2_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion15_n);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s3c3 = Racing_2019_P.Gain_s3c3_Gain * Racing_2019_B.s3c3;
  u1_0 = floor(Racing_2019_B.Gain_s3c3);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion12_dp = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s3c3_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion12_dp);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s3c4 = Racing_2019_P.Gain_s3c4_Gain * Racing_2019_B.s3c4;
  u1_0 = floor(Racing_2019_B.Gain_s3c4);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion13_o = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s3c4_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion13_o);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s3c5 = Racing_2019_P.Gain_s3c5_Gain * Racing_2019_B.s3c5;
  u1_0 = floor(Racing_2019_B.Gain_s3c5);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion10_f = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s3c5_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion10_f);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s3c6 = Racing_2019_P.Gain_s3c6_Gain * Racing_2019_B.s3c6;
  u1_0 = floor(Racing_2019_B.Gain_s3c6);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion11_b = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s3c6_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion11_b);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s3c7 = Racing_2019_P.Gain_s3c7_Gain * Racing_2019_B.s3c7;
  u1_0 = floor(Racing_2019_B.Gain_s3c7);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion8_k = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s3c7_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion8_k);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s3c8 = Racing_2019_P.Gain_s3c8_Gain * Racing_2019_B.s3c8;
  u1_0 = floor(Racing_2019_B.Gain_s3c8);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion9_c = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s3c8_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion9_c);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s3c9 = Racing_2019_P.Gain_s3c9_Gain * Racing_2019_B.s3c9;
  u1_0 = floor(Racing_2019_B.Gain_s3c9);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion18_j = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s3c9_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion18_j);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s3t1 = Racing_2019_P.Gain_s3t1_Gain *
    Racing_2019_B.sf_s3t1.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s3t1_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s3t1);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s3t2 = Racing_2019_P.Gain_s3t2_Gain *
    Racing_2019_B.sf_s3t2.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s3t2_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s3t2);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s3t3 = Racing_2019_P.Gain_s3t3_Gain *
    Racing_2019_B.sf_s3t3.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s3t3_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s3t3);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s3t4 = Racing_2019_P.Gain_s3t4_Gain *
    Racing_2019_B.sf_s3t4.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s3t4_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s3t4);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion2_cy = (Racing_2019_B.SFunction1_o5_gd != 0.0);
  Racing_2019_B.UnitDelay_gj = Racing_2019_DW.UnitDelay_DSTATE_g;
  switch ((int32_T)Racing_2019_P.EdgeDetector2_model_e) {
   case 1:
    Racing_2019_B.MultiportSwitch_cb[0] = Racing_2019_P.posedge_Value_m4[0];
    Racing_2019_B.MultiportSwitch_cb[1] = Racing_2019_P.posedge_Value_m4[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_cb[0] = Racing_2019_P.negedge_Value_j[0];
    Racing_2019_B.MultiportSwitch_cb[1] = Racing_2019_P.negedge_Value_j[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_cb[0] = Racing_2019_P.eitheredge_Value_f[0];
    Racing_2019_B.MultiportSwitch_cb[1] = Racing_2019_P.eitheredge_Value_f[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_cb[0],
    Racing_2019_B.DataTypeConversion2_cy, Racing_2019_B.UnitDelay_gj,
    &Racing_2019_B.POSITIVEEdge_k1);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_cb[1],
    Racing_2019_B.DataTypeConversion2_cy, Racing_2019_B.UnitDelay_gj,
    &Racing_2019_B.NEGATIVEEdge_d);
  Racing_2019_B.LogicalOperator1_mv =
    (Racing_2019_B.POSITIVEEdge_k1.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_d.RelationalOperator1);
  Racing_2019_B.DataTypeConversion5_h = Racing_2019_B.LogicalOperator1_mv;
  Racing_2019_B.BMS_CAN_211_Counter =
    Racing_2019_DW.BMS_CAN_211_Counter_PreviousInp;
  Racing_2019_B.Add1_f = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion5_h
    + Racing_2019_B.BMS_CAN_211_Counter);
  Racing_2019_B.DataTypeConversion2_pb = (Racing_2019_B.SFunction1_o5_l != 0.0);
  Racing_2019_B.UnitDelay_c = Racing_2019_DW.UnitDelay_DSTATE_j;
  switch ((int32_T)Racing_2019_P.EdgeDetector3_model_e) {
   case 1:
    Racing_2019_B.MultiportSwitch_m[0] = Racing_2019_P.posedge_Value_e[0];
    Racing_2019_B.MultiportSwitch_m[1] = Racing_2019_P.posedge_Value_e[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_m[0] = Racing_2019_P.negedge_Value_m2[0];
    Racing_2019_B.MultiportSwitch_m[1] = Racing_2019_P.negedge_Value_m2[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_m[0] = Racing_2019_P.eitheredge_Value_cm[0];
    Racing_2019_B.MultiportSwitch_m[1] = Racing_2019_P.eitheredge_Value_cm[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_m[0],
    Racing_2019_B.DataTypeConversion2_pb, Racing_2019_B.UnitDelay_c,
    &Racing_2019_B.POSITIVEEdge_hc);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_m[1],
    Racing_2019_B.DataTypeConversion2_pb, Racing_2019_B.UnitDelay_c,
    &Racing_2019_B.NEGATIVEEdge_a);
  Racing_2019_B.LogicalOperator1_if =
    (Racing_2019_B.POSITIVEEdge_hc.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_a.RelationalOperator1);
  Racing_2019_B.DataTypeConversion6_a = Racing_2019_B.LogicalOperator1_if;
  Racing_2019_B.BMS_CAN_212_Counter =
    Racing_2019_DW.BMS_CAN_212_Counter_PreviousInp;
  Racing_2019_B.Add2_o = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion6_a
    + Racing_2019_B.BMS_CAN_212_Counter);
  Racing_2019_B.DataTypeConversion2_iq = (Racing_2019_B.SFunction1_o5_ok != 0.0);
  Racing_2019_B.UnitDelay_p = Racing_2019_DW.UnitDelay_DSTATE_f2;
  switch ((int32_T)Racing_2019_P.EdgeDetector4_model_a) {
   case 1:
    Racing_2019_B.MultiportSwitch_h[0] = Racing_2019_P.posedge_Value_mc[0];
    Racing_2019_B.MultiportSwitch_h[1] = Racing_2019_P.posedge_Value_mc[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_h[0] = Racing_2019_P.negedge_Value_jf[0];
    Racing_2019_B.MultiportSwitch_h[1] = Racing_2019_P.negedge_Value_jf[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_h[0] = Racing_2019_P.eitheredge_Value_h[0];
    Racing_2019_B.MultiportSwitch_h[1] = Racing_2019_P.eitheredge_Value_h[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_h[0],
    Racing_2019_B.DataTypeConversion2_iq, Racing_2019_B.UnitDelay_p,
    &Racing_2019_B.POSITIVEEdge_b);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_h[1],
    Racing_2019_B.DataTypeConversion2_iq, Racing_2019_B.UnitDelay_p,
    &Racing_2019_B.NEGATIVEEdge_j);
  Racing_2019_B.LogicalOperator1_j =
    (Racing_2019_B.POSITIVEEdge_b.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_j.RelationalOperator1);
  Racing_2019_B.DataTypeConversion1_o = Racing_2019_B.LogicalOperator1_j;
  Racing_2019_B.BMS_CAN_227_Counter =
    Racing_2019_DW.BMS_CAN_227_Counter_PreviousInp;
  Racing_2019_B.Add3_a = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion1_o
    + Racing_2019_B.BMS_CAN_227_Counter);
  Racing_2019_B.DataTypeConversion2_l = (Racing_2019_B.SFunction1_o5_n != 0.0);
  Racing_2019_B.UnitDelay_f = Racing_2019_DW.UnitDelay_DSTATE_fi;
  switch ((int32_T)Racing_2019_P.EdgeDetector1_model_hl) {
   case 1:
    Racing_2019_B.MultiportSwitch_ey[0] = Racing_2019_P.posedge_Value_b[0];
    Racing_2019_B.MultiportSwitch_ey[1] = Racing_2019_P.posedge_Value_b[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_ey[0] = Racing_2019_P.negedge_Value_b[0];
    Racing_2019_B.MultiportSwitch_ey[1] = Racing_2019_P.negedge_Value_b[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_ey[0] = Racing_2019_P.eitheredge_Value_j[0];
    Racing_2019_B.MultiportSwitch_ey[1] = Racing_2019_P.eitheredge_Value_j[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_ey[0],
    Racing_2019_B.DataTypeConversion2_l, Racing_2019_B.UnitDelay_f,
    &Racing_2019_B.POSITIVEEdge_kp);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_ey[1],
    Racing_2019_B.DataTypeConversion2_l, Racing_2019_B.UnitDelay_f,
    &Racing_2019_B.NEGATIVEEdge_ec);
  Racing_2019_B.LogicalOperator1_p =
    (Racing_2019_B.POSITIVEEdge_kp.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_ec.RelationalOperator1);
  Racing_2019_B.DataTypeConversion4_a = Racing_2019_B.LogicalOperator1_p;
  Racing_2019_B.BMS_CAN_210_Counter =
    Racing_2019_DW.BMS_CAN_210_Counter_PreviousInp;
  Racing_2019_B.Add4_c = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion4_a
    + Racing_2019_B.BMS_CAN_210_Counter);
  Racing_2019_B.Gain_s4c1 = Racing_2019_P.Gain_s4c1_Gain * Racing_2019_B.s4c1;
  u1_0 = floor(Racing_2019_B.Gain_s4c1);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion14_d = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s4c1_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion14_d);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s4c10 = Racing_2019_P.Gain_s4c10_Gain * Racing_2019_B.s4c10;
  u1_0 = floor(Racing_2019_B.Gain_s4c10);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion19_f = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s4c10_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion19_f);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s4c11 = Racing_2019_P.Gain_s4c11_Gain * Racing_2019_B.s4c11;
  u1_0 = floor(Racing_2019_B.Gain_s4c11);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion16_oo = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s4c11_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion16_oo);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s4c12 = Racing_2019_P.Gain_s4c12_Gain * Racing_2019_B.s4c12;
  u1_0 = floor(Racing_2019_B.Gain_s4c12);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion17_b = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s4c12_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion17_b);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s4c2 = Racing_2019_P.Gain_s4c2_Gain * Racing_2019_B.s4c2;
  u1_0 = floor(Racing_2019_B.Gain_s4c2);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion15_c = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s4c2_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion15_c);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s4c3 = Racing_2019_P.Gain_s4c3_Gain * Racing_2019_B.s4c3;
  u1_0 = floor(Racing_2019_B.Gain_s4c3);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion12_l = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s4c3_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion12_l);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s4c4 = Racing_2019_P.Gain_s4c4_Gain * Racing_2019_B.s4c4;
  u1_0 = floor(Racing_2019_B.Gain_s4c4);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion13_nh = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s4c4_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion13_nh);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s4c5 = Racing_2019_P.Gain_s4c5_Gain * Racing_2019_B.s4c5;
  u1_0 = floor(Racing_2019_B.Gain_s4c5);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion10_e = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s4c5_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion10_e);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s4c6 = Racing_2019_P.Gain_s4c6_Gain * Racing_2019_B.s4c6;
  u1_0 = floor(Racing_2019_B.Gain_s4c6);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion11_g = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s4c6_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion11_g);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s4c7 = Racing_2019_P.Gain_s4c7_Gain * Racing_2019_B.s4c7;
  u1_0 = floor(Racing_2019_B.Gain_s4c7);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion8_f = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s4c7_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion8_f);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s4c8 = Racing_2019_P.Gain_s4c8_Gain * Racing_2019_B.s4c8;
  u1_0 = floor(Racing_2019_B.Gain_s4c8);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion9_g = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s4c8_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion9_g);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s4c9 = Racing_2019_P.Gain_s4c9_Gain * Racing_2019_B.s4c9;
  u1_0 = floor(Racing_2019_B.Gain_s4c9);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion18_o = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s4c9_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion18_o);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s4t1 = Racing_2019_P.Gain_s4t1_Gain *
    Racing_2019_B.sf_s4t1.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s4t1_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s4t1);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s4t2 = Racing_2019_P.Gain_s4t2_Gain *
    Racing_2019_B.sf_s4t2.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s4t2_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s4t2);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s4t3 = Racing_2019_P.Gain_s4t3_Gain *
    Racing_2019_B.sf_s4t3.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s4t3_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s4t3);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s4t4 = Racing_2019_P.Gain_s4t4_Gain *
    Racing_2019_B.sf_s4t4.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s4t4_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s4t4);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion2_ia = (Racing_2019_B.SFunction1_o5_b != 0.0);
  Racing_2019_B.UnitDelay_m = Racing_2019_DW.UnitDelay_DSTATE_d;
  switch ((int32_T)Racing_2019_P.EdgeDetector2_model_dd) {
   case 1:
    Racing_2019_B.MultiportSwitch_l[0] = Racing_2019_P.posedge_Value_c[0];
    Racing_2019_B.MultiportSwitch_l[1] = Racing_2019_P.posedge_Value_c[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_l[0] = Racing_2019_P.negedge_Value_ml[0];
    Racing_2019_B.MultiportSwitch_l[1] = Racing_2019_P.negedge_Value_ml[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_l[0] = Racing_2019_P.eitheredge_Value_ny[0];
    Racing_2019_B.MultiportSwitch_l[1] = Racing_2019_P.eitheredge_Value_ny[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_l[0],
    Racing_2019_B.DataTypeConversion2_ia, Racing_2019_B.UnitDelay_m,
    &Racing_2019_B.POSITIVEEdge_cx);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_l[1],
    Racing_2019_B.DataTypeConversion2_ia, Racing_2019_B.UnitDelay_m,
    &Racing_2019_B.NEGATIVEEdge_ae);
  Racing_2019_B.LogicalOperator1_px =
    (Racing_2019_B.POSITIVEEdge_cx.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_ae.RelationalOperator1);
  Racing_2019_B.DataTypeConversion5_bw = Racing_2019_B.LogicalOperator1_px;
  Racing_2019_B.BMS_CAN_214_Counter =
    Racing_2019_DW.BMS_CAN_214_Counter_PreviousInp;
  Racing_2019_B.Add1_n = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion5_bw + Racing_2019_B.BMS_CAN_214_Counter);
  Racing_2019_B.DataTypeConversion2_oq = (Racing_2019_B.SFunction1_o5_a != 0.0);
  Racing_2019_B.UnitDelay_dr = Racing_2019_DW.UnitDelay_DSTATE_l;
  switch ((int32_T)Racing_2019_P.EdgeDetector3_model_b) {
   case 1:
    Racing_2019_B.MultiportSwitch_o[0] = Racing_2019_P.posedge_Value_cw[0];
    Racing_2019_B.MultiportSwitch_o[1] = Racing_2019_P.posedge_Value_cw[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_o[0] = Racing_2019_P.negedge_Value_bb[0];
    Racing_2019_B.MultiportSwitch_o[1] = Racing_2019_P.negedge_Value_bb[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_o[0] = Racing_2019_P.eitheredge_Value_lr[0];
    Racing_2019_B.MultiportSwitch_o[1] = Racing_2019_P.eitheredge_Value_lr[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_o[0],
    Racing_2019_B.DataTypeConversion2_oq, Racing_2019_B.UnitDelay_dr,
    &Racing_2019_B.POSITIVEEdge_bs);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_o[1],
    Racing_2019_B.DataTypeConversion2_oq, Racing_2019_B.UnitDelay_dr,
    &Racing_2019_B.NEGATIVEEdge_jr);
  Racing_2019_B.LogicalOperator1_h =
    (Racing_2019_B.POSITIVEEdge_bs.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_jr.RelationalOperator1);
  Racing_2019_B.DataTypeConversion6_f = Racing_2019_B.LogicalOperator1_h;
  Racing_2019_B.BMS_CAN_215_Counter =
    Racing_2019_DW.BMS_CAN_215_Counter_PreviousInp;
  Racing_2019_B.Add2_c = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion6_f
    + Racing_2019_B.BMS_CAN_215_Counter);
  Racing_2019_B.DataTypeConversion2_oc = (Racing_2019_B.SFunction1_o5_mk != 0.0);
  Racing_2019_B.UnitDelay_jc = Racing_2019_DW.UnitDelay_DSTATE_p;
  switch ((int32_T)Racing_2019_P.EdgeDetector4_model_h) {
   case 1:
    Racing_2019_B.MultiportSwitch_p[0] = Racing_2019_P.posedge_Value_o[0];
    Racing_2019_B.MultiportSwitch_p[1] = Racing_2019_P.posedge_Value_o[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_p[0] = Racing_2019_P.negedge_Value_je[0];
    Racing_2019_B.MultiportSwitch_p[1] = Racing_2019_P.negedge_Value_je[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_p[0] = Racing_2019_P.eitheredge_Value_gi[0];
    Racing_2019_B.MultiportSwitch_p[1] = Racing_2019_P.eitheredge_Value_gi[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_p[0],
    Racing_2019_B.DataTypeConversion2_oc, Racing_2019_B.UnitDelay_jc,
    &Racing_2019_B.POSITIVEEdge_g);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_p[1],
    Racing_2019_B.DataTypeConversion2_oc, Racing_2019_B.UnitDelay_jc,
    &Racing_2019_B.NEGATIVEEdge_k);
  Racing_2019_B.LogicalOperator1_f =
    (Racing_2019_B.POSITIVEEdge_g.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_k.RelationalOperator1);
  Racing_2019_B.DataTypeConversion1_gh = Racing_2019_B.LogicalOperator1_f;
  Racing_2019_B.BMS_CAN_228_Counter =
    Racing_2019_DW.BMS_CAN_228_Counter_PreviousInp;
  Racing_2019_B.Add3_e = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion1_gh + Racing_2019_B.BMS_CAN_228_Counter);
  Racing_2019_B.DataTypeConversion2_g2 = (Racing_2019_B.SFunction1_o5_f != 0.0);
  Racing_2019_B.UnitDelay_nw = Racing_2019_DW.UnitDelay_DSTATE_jj;
  switch ((int32_T)Racing_2019_P.EdgeDetector1_model_o) {
   case 1:
    Racing_2019_B.MultiportSwitch_j[0] = Racing_2019_P.posedge_Value_mn[0];
    Racing_2019_B.MultiportSwitch_j[1] = Racing_2019_P.posedge_Value_mn[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_j[0] = Racing_2019_P.negedge_Value_a[0];
    Racing_2019_B.MultiportSwitch_j[1] = Racing_2019_P.negedge_Value_a[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_j[0] = Racing_2019_P.eitheredge_Value_o[0];
    Racing_2019_B.MultiportSwitch_j[1] = Racing_2019_P.eitheredge_Value_o[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_j[0],
    Racing_2019_B.DataTypeConversion2_g2, Racing_2019_B.UnitDelay_nw,
    &Racing_2019_B.POSITIVEEdge_p);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_j[1],
    Racing_2019_B.DataTypeConversion2_g2, Racing_2019_B.UnitDelay_nw,
    &Racing_2019_B.NEGATIVEEdge_g);
  Racing_2019_B.LogicalOperator1_ia =
    (Racing_2019_B.POSITIVEEdge_p.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_g.RelationalOperator1);
  Racing_2019_B.DataTypeConversion4_m = Racing_2019_B.LogicalOperator1_ia;
  Racing_2019_B.BMS_CAN_213_Counter =
    Racing_2019_DW.BMS_CAN_213_Counter_PreviousInp;
  Racing_2019_B.Add4_cd = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion4_m + Racing_2019_B.BMS_CAN_213_Counter);
  Racing_2019_B.Gain_s5c1 = Racing_2019_P.Gain_s5c1_Gain * Racing_2019_B.s5c1;
  u1_0 = floor(Racing_2019_B.Gain_s5c1);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion14_b = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s5c1_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion14_b);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s5c10 = Racing_2019_P.Gain_s5c10_Gain * Racing_2019_B.s5c10;
  u1_0 = floor(Racing_2019_B.Gain_s5c10);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion19_i = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s5c10_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion19_i);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s5c11 = Racing_2019_P.Gain_s5c11_Gain * Racing_2019_B.s5c11;
  u1_0 = floor(Racing_2019_B.Gain_s5c11);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion16_k = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s5c11_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion16_k);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s5c12 = Racing_2019_P.Gain_s5c12_Gain * Racing_2019_B.s5c12;
  u1_0 = floor(Racing_2019_B.Gain_s5c12);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion17_i = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s5c12_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion17_i);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s5c2 = Racing_2019_P.Gain_s5c2_Gain * Racing_2019_B.s5c2;
  u1_0 = floor(Racing_2019_B.Gain_s5c2);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion15_m = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s5c2_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion15_m);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s5c3 = Racing_2019_P.Gain_s5c3_Gain * Racing_2019_B.s5c3;
  u1_0 = floor(Racing_2019_B.Gain_s5c3);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion12_da = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s5c3_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion12_da);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s5c4 = Racing_2019_P.Gain_s5c4_Gain * Racing_2019_B.s5c4;
  u1_0 = floor(Racing_2019_B.Gain_s5c4);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion13_k = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s5c4_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion13_k);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s5c5 = Racing_2019_P.Gain_s5c5_Gain * Racing_2019_B.s5c5;
  u1_0 = floor(Racing_2019_B.Gain_s5c5);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion10_i = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s5c5_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion10_i);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s5c6 = Racing_2019_P.Gain_s5c6_Gain * Racing_2019_B.s5c6;
  u1_0 = floor(Racing_2019_B.Gain_s5c6);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion11_ju = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s5c6_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion11_ju);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s5c7 = Racing_2019_P.Gain_s5c7_Gain * Racing_2019_B.s5c7;
  u1_0 = floor(Racing_2019_B.Gain_s5c7);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion8_e = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s5c7_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion8_e);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s5c8 = Racing_2019_P.Gain_s5c8_Gain * Racing_2019_B.s5c8;
  u1_0 = floor(Racing_2019_B.Gain_s5c8);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion9_b = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s5c8_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion9_b);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s5c9 = Racing_2019_P.Gain_s5c9_Gain * Racing_2019_B.s5c9;
  u1_0 = floor(Racing_2019_B.Gain_s5c9);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion18_p = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s5c9_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion18_p);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s5t1 = Racing_2019_P.Gain_s5t1_Gain *
    Racing_2019_B.sf_s5t1.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s5t1_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s5t1);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s5t2 = Racing_2019_P.Gain_s5t2_Gain *
    Racing_2019_B.sf_s5t2.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s5t2_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s5t2);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s5t3 = Racing_2019_P.Gain_s5t3_Gain *
    Racing_2019_B.sf_s5t3.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s5t3_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s5t3);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s5t4 = Racing_2019_P.Gain_s5t4_Gain *
    Racing_2019_B.sf_s5t4.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s5t4_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s5t4);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion2_pp = (Racing_2019_B.SFunction1_o5_d != 0.0);
  Racing_2019_B.UnitDelay_h = Racing_2019_DW.UnitDelay_DSTATE_cx;
  switch ((int32_T)Racing_2019_P.EdgeDetector2_model_o) {
   case 1:
    Racing_2019_B.MultiportSwitch_b[0] = Racing_2019_P.posedge_Value_l4[0];
    Racing_2019_B.MultiportSwitch_b[1] = Racing_2019_P.posedge_Value_l4[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_b[0] = Racing_2019_P.negedge_Value_k[0];
    Racing_2019_B.MultiportSwitch_b[1] = Racing_2019_P.negedge_Value_k[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_b[0] = Racing_2019_P.eitheredge_Value_do[0];
    Racing_2019_B.MultiportSwitch_b[1] = Racing_2019_P.eitheredge_Value_do[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_b[0],
    Racing_2019_B.DataTypeConversion2_pp, Racing_2019_B.UnitDelay_h,
    &Racing_2019_B.POSITIVEEdge_gm);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_b[1],
    Racing_2019_B.DataTypeConversion2_pp, Racing_2019_B.UnitDelay_h,
    &Racing_2019_B.NEGATIVEEdge_ot);
  Racing_2019_B.LogicalOperator1_b =
    (Racing_2019_B.POSITIVEEdge_gm.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_ot.RelationalOperator1);
  Racing_2019_B.DataTypeConversion5_j = Racing_2019_B.LogicalOperator1_b;
  Racing_2019_B.BMS_CAN_217_Counter =
    Racing_2019_DW.BMS_CAN_217_Counter_PreviousInp;
  Racing_2019_B.Add1_c = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion5_j
    + Racing_2019_B.BMS_CAN_217_Counter);
  Racing_2019_B.DataTypeConversion2_dw = (Racing_2019_B.SFunction1_o5_k != 0.0);
  Racing_2019_B.UnitDelay_ns = Racing_2019_DW.UnitDelay_DSTATE_gg;
  switch ((int32_T)Racing_2019_P.EdgeDetector3_model_g) {
   case 1:
    Racing_2019_B.MultiportSwitch_cf[0] = Racing_2019_P.posedge_Value_f[0];
    Racing_2019_B.MultiportSwitch_cf[1] = Racing_2019_P.posedge_Value_f[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_cf[0] = Racing_2019_P.negedge_Value_i[0];
    Racing_2019_B.MultiportSwitch_cf[1] = Racing_2019_P.negedge_Value_i[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_cf[0] = Racing_2019_P.eitheredge_Value_cmq[0];
    Racing_2019_B.MultiportSwitch_cf[1] = Racing_2019_P.eitheredge_Value_cmq[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_cf[0],
    Racing_2019_B.DataTypeConversion2_dw, Racing_2019_B.UnitDelay_ns,
    &Racing_2019_B.POSITIVEEdge_b4);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_cf[1],
    Racing_2019_B.DataTypeConversion2_dw, Racing_2019_B.UnitDelay_ns,
    &Racing_2019_B.NEGATIVEEdge_ei);
  Racing_2019_B.LogicalOperator1_my =
    (Racing_2019_B.POSITIVEEdge_b4.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_ei.RelationalOperator1);
  Racing_2019_B.DataTypeConversion6_c = Racing_2019_B.LogicalOperator1_my;
  Racing_2019_B.BMS_CAN_218_Counter =
    Racing_2019_DW.BMS_CAN_218_Counter_PreviousInp;
  Racing_2019_B.Add2_l = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion6_c
    + Racing_2019_B.BMS_CAN_218_Counter);
  Racing_2019_B.DataTypeConversion2_ke = (Racing_2019_B.SFunction1_o5_ja != 0.0);
  Racing_2019_B.UnitDelay_nl = Racing_2019_DW.UnitDelay_DSTATE_hq;
  switch ((int32_T)Racing_2019_P.EdgeDetector4_model_b) {
   case 1:
    Racing_2019_B.MultiportSwitch_jh[0] = Racing_2019_P.posedge_Value_ix[0];
    Racing_2019_B.MultiportSwitch_jh[1] = Racing_2019_P.posedge_Value_ix[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_jh[0] = Racing_2019_P.negedge_Value_bz[0];
    Racing_2019_B.MultiportSwitch_jh[1] = Racing_2019_P.negedge_Value_bz[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_jh[0] = Racing_2019_P.eitheredge_Value_i[0];
    Racing_2019_B.MultiportSwitch_jh[1] = Racing_2019_P.eitheredge_Value_i[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_jh[0],
    Racing_2019_B.DataTypeConversion2_ke, Racing_2019_B.UnitDelay_nl,
    &Racing_2019_B.POSITIVEEdge_i);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_jh[1],
    Racing_2019_B.DataTypeConversion2_ke, Racing_2019_B.UnitDelay_nl,
    &Racing_2019_B.NEGATIVEEdge_l);
  Racing_2019_B.LogicalOperator1_g1 =
    (Racing_2019_B.POSITIVEEdge_i.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_l.RelationalOperator1);
  Racing_2019_B.DataTypeConversion1_id = Racing_2019_B.LogicalOperator1_g1;
  Racing_2019_B.BMS_CAN_229_Counter =
    Racing_2019_DW.BMS_CAN_229_Counter_PreviousInp;
  Racing_2019_B.Add3_n = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion1_id + Racing_2019_B.BMS_CAN_229_Counter);
  Racing_2019_B.DataTypeConversion2_ac = (Racing_2019_B.SFunction1_o5_ke != 0.0);
  Racing_2019_B.UnitDelay_mf = Racing_2019_DW.UnitDelay_DSTATE_o;
  switch ((int32_T)Racing_2019_P.EdgeDetector1_model_i) {
   case 1:
    Racing_2019_B.MultiportSwitch_cj[0] = Racing_2019_P.posedge_Value_p2[0];
    Racing_2019_B.MultiportSwitch_cj[1] = Racing_2019_P.posedge_Value_p2[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_cj[0] = Racing_2019_P.negedge_Value_cw[0];
    Racing_2019_B.MultiportSwitch_cj[1] = Racing_2019_P.negedge_Value_cw[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_cj[0] = Racing_2019_P.eitheredge_Value_a[0];
    Racing_2019_B.MultiportSwitch_cj[1] = Racing_2019_P.eitheredge_Value_a[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_cj[0],
    Racing_2019_B.DataTypeConversion2_ac, Racing_2019_B.UnitDelay_mf,
    &Racing_2019_B.POSITIVEEdge_m);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_cj[1],
    Racing_2019_B.DataTypeConversion2_ac, Racing_2019_B.UnitDelay_mf,
    &Racing_2019_B.NEGATIVEEdge_gr);
  Racing_2019_B.LogicalOperator1_mu =
    (Racing_2019_B.POSITIVEEdge_m.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_gr.RelationalOperator1);
  Racing_2019_B.DataTypeConversion4_j = Racing_2019_B.LogicalOperator1_mu;
  Racing_2019_B.BMS_CAN_216_Counter =
    Racing_2019_DW.BMS_CAN_216_Counter_PreviousInp;
  Racing_2019_B.Add4_m = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion4_j
    + Racing_2019_B.BMS_CAN_216_Counter);
  Racing_2019_B.Gain_s6c1 = Racing_2019_P.Gain_s6c1_Gain * Racing_2019_B.s6c1;
  u1_0 = floor(Racing_2019_B.Gain_s6c1);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion14_k = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s6c1_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion14_k);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s6c10 = Racing_2019_P.Gain_s6c10_Gain * Racing_2019_B.s6c10;
  u1_0 = floor(Racing_2019_B.Gain_s6c10);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion19_l = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s6c10_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion19_l);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s6c11 = Racing_2019_P.Gain_s6c11_Gain * Racing_2019_B.s6c11;
  u1_0 = floor(Racing_2019_B.Gain_s6c11);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion16_m5 = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s6c11_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion16_m5);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s6c12 = Racing_2019_P.Gain_s6c12_Gain * Racing_2019_B.s6c12;
  u1_0 = floor(Racing_2019_B.Gain_s6c12);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion17_m = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s6c12_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion17_m);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s6c2 = Racing_2019_P.Gain_s6c2_Gain * Racing_2019_B.s6c2;
  u1_0 = floor(Racing_2019_B.Gain_s6c2);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion15_h = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s6c2_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion15_h);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s6c3 = Racing_2019_P.Gain_s6c3_Gain * Racing_2019_B.s6c3;
  u1_0 = floor(Racing_2019_B.Gain_s6c3);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion12_b = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s6c3_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion12_b);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s6c4 = Racing_2019_P.Gain_s6c4_Gain * Racing_2019_B.s6c4;
  u1_0 = floor(Racing_2019_B.Gain_s6c4);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion13_g = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s6c4_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion13_g);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s6c5 = Racing_2019_P.Gain_s6c5_Gain * Racing_2019_B.s6c5;
  u1_0 = floor(Racing_2019_B.Gain_s6c5);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion10_ej = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s6c5_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion10_ej);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s6c6 = Racing_2019_P.Gain_s6c6_Gain * Racing_2019_B.s6c6;
  u1_0 = floor(Racing_2019_B.Gain_s6c6);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion11_n = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s6c6_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion11_n);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s6c7 = Racing_2019_P.Gain_s6c7_Gain * Racing_2019_B.s6c7;
  u1_0 = floor(Racing_2019_B.Gain_s6c7);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion8_h = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s6c7_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion8_h);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s6c8 = Racing_2019_P.Gain_s6c8_Gain * Racing_2019_B.s6c8;
  u1_0 = floor(Racing_2019_B.Gain_s6c8);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion9_j = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s6c8_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion9_j);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s6c9 = Racing_2019_P.Gain_s6c9_Gain * Racing_2019_B.s6c9;
  u1_0 = floor(Racing_2019_B.Gain_s6c9);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion18_i = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s6c9_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion18_i);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s6t1 = Racing_2019_P.Gain_s6t1_Gain *
    Racing_2019_B.sf_s6t1.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s6t1_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s6t1);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s6t2 = Racing_2019_P.Gain_s6t2_Gain *
    Racing_2019_B.sf_s6t2.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s6t2_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s6t2);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s6t3 = Racing_2019_P.Gain_s6t3_Gain *
    Racing_2019_B.sf_s6t3.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s6t3_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s6t3);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s6t4 = Racing_2019_P.Gain_s6t4_Gain *
    Racing_2019_B.sf_s6t4.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s6t4_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s6t4);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion2_pu = (Racing_2019_B.SFunction1_o5_cb != 0.0);
  Racing_2019_B.UnitDelay_hi = Racing_2019_DW.UnitDelay_DSTATE_l5;
  switch ((int32_T)Racing_2019_P.EdgeDetector2_model_i) {
   case 1:
    Racing_2019_B.MultiportSwitch_jo[0] = Racing_2019_P.posedge_Value_pz[0];
    Racing_2019_B.MultiportSwitch_jo[1] = Racing_2019_P.posedge_Value_pz[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_jo[0] = Racing_2019_P.negedge_Value_bu[0];
    Racing_2019_B.MultiportSwitch_jo[1] = Racing_2019_P.negedge_Value_bu[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_jo[0] = Racing_2019_P.eitheredge_Value_k[0];
    Racing_2019_B.MultiportSwitch_jo[1] = Racing_2019_P.eitheredge_Value_k[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_jo[0],
    Racing_2019_B.DataTypeConversion2_pu, Racing_2019_B.UnitDelay_hi,
    &Racing_2019_B.POSITIVEEdge_n3);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_jo[1],
    Racing_2019_B.DataTypeConversion2_pu, Racing_2019_B.UnitDelay_hi,
    &Racing_2019_B.NEGATIVEEdge_kq);
  Racing_2019_B.LogicalOperator1_d =
    (Racing_2019_B.POSITIVEEdge_n3.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_kq.RelationalOperator1);
  Racing_2019_B.DataTypeConversion5_le = Racing_2019_B.LogicalOperator1_d;
  Racing_2019_B.BMS_CAN_220_Counter =
    Racing_2019_DW.BMS_CAN_220_Counter_PreviousInp;
  Racing_2019_B.Add1_a5 = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion5_le + Racing_2019_B.BMS_CAN_220_Counter);
  Racing_2019_B.DataTypeConversion2_if = (Racing_2019_B.SFunction1_o5_bo != 0.0);
  Racing_2019_B.UnitDelay_l = Racing_2019_DW.UnitDelay_DSTATE_ju;
  switch ((int32_T)Racing_2019_P.EdgeDetector3_model_a) {
   case 1:
    Racing_2019_B.MultiportSwitch_mx[0] = Racing_2019_P.posedge_Value_a[0];
    Racing_2019_B.MultiportSwitch_mx[1] = Racing_2019_P.posedge_Value_a[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_mx[0] = Racing_2019_P.negedge_Value_hy[0];
    Racing_2019_B.MultiportSwitch_mx[1] = Racing_2019_P.negedge_Value_hy[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_mx[0] = Racing_2019_P.eitheredge_Value_gf[0];
    Racing_2019_B.MultiportSwitch_mx[1] = Racing_2019_P.eitheredge_Value_gf[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_mx[0],
    Racing_2019_B.DataTypeConversion2_if, Racing_2019_B.UnitDelay_l,
    &Racing_2019_B.POSITIVEEdge_bsv);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_mx[1],
    Racing_2019_B.DataTypeConversion2_if, Racing_2019_B.UnitDelay_l,
    &Racing_2019_B.NEGATIVEEdge_bl);
  Racing_2019_B.LogicalOperator1_gp =
    (Racing_2019_B.POSITIVEEdge_bsv.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_bl.RelationalOperator1);
  Racing_2019_B.DataTypeConversion6_l = Racing_2019_B.LogicalOperator1_gp;
  Racing_2019_B.BMS_CAN_221_Counter =
    Racing_2019_DW.BMS_CAN_221_Counter_PreviousInp;
  Racing_2019_B.Add2_la = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion6_l + Racing_2019_B.BMS_CAN_221_Counter);
  Racing_2019_B.DataTypeConversion2_ly = (Racing_2019_B.SFunction1_o5_m0 != 0.0);
  Racing_2019_B.UnitDelay_oe = Racing_2019_DW.UnitDelay_DSTATE_bm;
  switch ((int32_T)Racing_2019_P.EdgeDetector4_model_j) {
   case 1:
    Racing_2019_B.MultiportSwitch_gr[0] = Racing_2019_P.posedge_Value_ak[0];
    Racing_2019_B.MultiportSwitch_gr[1] = Racing_2019_P.posedge_Value_ak[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_gr[0] = Racing_2019_P.negedge_Value_mlc[0];
    Racing_2019_B.MultiportSwitch_gr[1] = Racing_2019_P.negedge_Value_mlc[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_gr[0] = Racing_2019_P.eitheredge_Value_dm[0];
    Racing_2019_B.MultiportSwitch_gr[1] = Racing_2019_P.eitheredge_Value_dm[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_gr[0],
    Racing_2019_B.DataTypeConversion2_ly, Racing_2019_B.UnitDelay_oe,
    &Racing_2019_B.POSITIVEEdge_f);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_gr[1],
    Racing_2019_B.DataTypeConversion2_ly, Racing_2019_B.UnitDelay_oe,
    &Racing_2019_B.NEGATIVEEdge_id);
  Racing_2019_B.LogicalOperator1_fv =
    (Racing_2019_B.POSITIVEEdge_f.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_id.RelationalOperator1);
  Racing_2019_B.DataTypeConversion1_c = Racing_2019_B.LogicalOperator1_fv;
  Racing_2019_B.BMS_CAN_230_Counter =
    Racing_2019_DW.BMS_CAN_230_Counter_PreviousInp;
  Racing_2019_B.Add3_o = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion1_c
    + Racing_2019_B.BMS_CAN_230_Counter);
  Racing_2019_B.DataTypeConversion2_nn = (Racing_2019_B.SFunction1_o5_bu != 0.0);
  Racing_2019_B.UnitDelay_i = Racing_2019_DW.UnitDelay_DSTATE_m;
  switch ((int32_T)Racing_2019_P.EdgeDetector1_model_hu) {
   case 1:
    Racing_2019_B.MultiportSwitch_id[0] = Racing_2019_P.posedge_Value_ln[0];
    Racing_2019_B.MultiportSwitch_id[1] = Racing_2019_P.posedge_Value_ln[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_id[0] = Racing_2019_P.negedge_Value_hf[0];
    Racing_2019_B.MultiportSwitch_id[1] = Racing_2019_P.negedge_Value_hf[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_id[0] = Racing_2019_P.eitheredge_Value_lv[0];
    Racing_2019_B.MultiportSwitch_id[1] = Racing_2019_P.eitheredge_Value_lv[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_id[0],
    Racing_2019_B.DataTypeConversion2_nn, Racing_2019_B.UnitDelay_i,
    &Racing_2019_B.POSITIVEEdge_a);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_id[1],
    Racing_2019_B.DataTypeConversion2_nn, Racing_2019_B.UnitDelay_i,
    &Racing_2019_B.NEGATIVEEdge_h5);
  Racing_2019_B.LogicalOperator1_b5 =
    (Racing_2019_B.POSITIVEEdge_a.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_h5.RelationalOperator1);
  Racing_2019_B.DataTypeConversion4_h = Racing_2019_B.LogicalOperator1_b5;
  Racing_2019_B.BMS_CAN_219_Counter =
    Racing_2019_DW.BMS_CAN_219_Counter_PreviousInp;
  Racing_2019_B.Add4_l = (uint8_T)((uint32_T)Racing_2019_B.DataTypeConversion4_h
    + Racing_2019_B.BMS_CAN_219_Counter);
  Racing_2019_B.Gain_s7c1 = Racing_2019_P.Gain_s7c1_Gain * Racing_2019_B.s7c1;
  u1_0 = floor(Racing_2019_B.Gain_s7c1);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion14_nu = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s7c1_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion14_nu);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s7c10 = Racing_2019_P.Gain_s7c10_Gain * Racing_2019_B.s7c10;
  u1_0 = floor(Racing_2019_B.Gain_s7c10);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion19_o = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s7c10_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion19_o);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s7c11 = Racing_2019_P.Gain_s7c11_Gain * Racing_2019_B.s7c11;
  u1_0 = floor(Racing_2019_B.Gain_s7c11);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion16_c = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s7c11_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion16_c);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s7c12 = Racing_2019_P.Gain_s7c12_Gain * Racing_2019_B.s7c12;
  u1_0 = floor(Racing_2019_B.Gain_s7c12);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion17_c = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s7c12_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion17_c);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s7c2 = Racing_2019_P.Gain_s7c2_Gain * Racing_2019_B.s7c2;
  u1_0 = floor(Racing_2019_B.Gain_s7c2);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion15_e = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s7c2_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion15_e);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s7c3 = Racing_2019_P.Gain_s7c3_Gain * Racing_2019_B.s7c3;
  u1_0 = floor(Racing_2019_B.Gain_s7c3);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion12_i = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s7c3_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion12_i);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s7c4 = Racing_2019_P.Gain_s7c4_Gain * Racing_2019_B.s7c4;
  u1_0 = floor(Racing_2019_B.Gain_s7c4);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion13_l = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s7c4_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion13_l);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s7c5 = Racing_2019_P.Gain_s7c5_Gain * Racing_2019_B.s7c5;
  u1_0 = floor(Racing_2019_B.Gain_s7c5);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion10_j = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s7c5_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion10_j);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s7c6 = Racing_2019_P.Gain_s7c6_Gain * Racing_2019_B.s7c6;
  u1_0 = floor(Racing_2019_B.Gain_s7c6);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion11_i = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s7c6_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion11_i);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s7c7 = Racing_2019_P.Gain_s7c7_Gain * Racing_2019_B.s7c7;
  u1_0 = floor(Racing_2019_B.Gain_s7c7);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion8_p = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s7c7_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion8_p);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s7c8 = Racing_2019_P.Gain_s7c8_Gain * Racing_2019_B.s7c8;
  u1_0 = floor(Racing_2019_B.Gain_s7c8);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion9_mj = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s7c8_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion9_mj);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s7c9 = Racing_2019_P.Gain_s7c9_Gain * Racing_2019_B.s7c9;
  u1_0 = floor(Racing_2019_B.Gain_s7c9);
  if (rtIsNaN(u1_0) || rtIsInf(u1_0)) {
    u1_0 = 0.0;
  } else {
    u1_0 = fmod(u1_0, 65536.0);
  }

  Racing_2019_B.DataTypeConversion18_n = (uint16_T)(u1_0 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u1_0 : (int32_T)(uint16_T)u1_0);

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(s7c9_Index_UsbFlRec, (Int32)
      Racing_2019_B.DataTypeConversion18_n);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s7t1 = Racing_2019_P.Gain_s7t1_Gain *
    Racing_2019_B.sf_s7t1.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s7t1_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s7t1);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s7t2 = Racing_2019_P.Gain_s7t2_Gain *
    Racing_2019_B.sf_s7t2.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s7t2_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s7t2);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s7t3 = Racing_2019_P.Gain_s7t3_Gain *
    Racing_2019_B.sf_s7t3.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s7t3_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s7t3);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.Gain_s74 = Racing_2019_P.Gain_s74_Gain * Racing_2019_B.y;

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_float32(s7t4_Index_UsbFlRec, (Float32)
      Racing_2019_B.Gain_s74);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  Racing_2019_B.DataTypeConversion2_m = (Racing_2019_B.SFunction1_o5_be != 0.0);
  Racing_2019_B.UnitDelay_jq = Racing_2019_DW.UnitDelay_DSTATE_pv;
  switch ((int32_T)Racing_2019_P.EdgeDetector2_model_c) {
   case 1:
    Racing_2019_B.MultiportSwitch_d[0] = Racing_2019_P.posedge_Value_l2[0];
    Racing_2019_B.MultiportSwitch_d[1] = Racing_2019_P.posedge_Value_l2[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_d[0] = Racing_2019_P.negedge_Value_is[0];
    Racing_2019_B.MultiportSwitch_d[1] = Racing_2019_P.negedge_Value_is[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_d[0] = Racing_2019_P.eitheredge_Value_es[0];
    Racing_2019_B.MultiportSwitch_d[1] = Racing_2019_P.eitheredge_Value_es[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_d[0],
    Racing_2019_B.DataTypeConversion2_m, Racing_2019_B.UnitDelay_jq,
    &Racing_2019_B.POSITIVEEdge_iy);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_d[1],
    Racing_2019_B.DataTypeConversion2_m, Racing_2019_B.UnitDelay_jq,
    &Racing_2019_B.NEGATIVEEdge_m);
  Racing_2019_B.LogicalOperator1_hq =
    (Racing_2019_B.POSITIVEEdge_iy.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_m.RelationalOperator1);
  Racing_2019_B.DataTypeConversion5_d = Racing_2019_B.LogicalOperator1_hq;
  Racing_2019_B.BMS_CAN_223_Counter =
    Racing_2019_DW.BMS_CAN_223_Counter_PreviousInp;
  Racing_2019_B.Add1_dm = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion5_d + Racing_2019_B.BMS_CAN_223_Counter);
  Racing_2019_B.DataTypeConversion2_ko = (Racing_2019_B.SFunction1_o5_j != 0.0);
  Racing_2019_B.UnitDelay_la = Racing_2019_DW.UnitDelay_DSTATE_i;
  switch ((int32_T)Racing_2019_P.EdgeDetector3_model_gm) {
   case 1:
    Racing_2019_B.MultiportSwitch_kt[0] = Racing_2019_P.posedge_Value_fx[0];
    Racing_2019_B.MultiportSwitch_kt[1] = Racing_2019_P.posedge_Value_fx[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_kt[0] = Racing_2019_P.negedge_Value_fi[0];
    Racing_2019_B.MultiportSwitch_kt[1] = Racing_2019_P.negedge_Value_fi[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_kt[0] = Racing_2019_P.eitheredge_Value_ir[0];
    Racing_2019_B.MultiportSwitch_kt[1] = Racing_2019_P.eitheredge_Value_ir[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_kt[0],
    Racing_2019_B.DataTypeConversion2_ko, Racing_2019_B.UnitDelay_la,
    &Racing_2019_B.POSITIVEEdge_hw);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_kt[1],
    Racing_2019_B.DataTypeConversion2_ko, Racing_2019_B.UnitDelay_la,
    &Racing_2019_B.NEGATIVEEdge_ph);
  Racing_2019_B.LogicalOperator1_bo =
    (Racing_2019_B.POSITIVEEdge_hw.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_ph.RelationalOperator1);
  Racing_2019_B.DataTypeConversion6_nx = Racing_2019_B.LogicalOperator1_bo;
  Racing_2019_B.BMS_CAN_221_Counter_j =
    Racing_2019_DW.BMS_CAN_221_Counter_PreviousI_n;
  Racing_2019_B.Add2_h = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion6_nx + Racing_2019_B.BMS_CAN_221_Counter_j);
  Racing_2019_B.DataTypeConversion2_om = (Racing_2019_B.SFunction1_o5_iw != 0.0);
  Racing_2019_B.UnitDelay_oh = Racing_2019_DW.UnitDelay_DSTATE_nn;
  switch ((int32_T)Racing_2019_P.EdgeDetector4_model_n) {
   case 1:
    Racing_2019_B.MultiportSwitch_lj[0] = Racing_2019_P.posedge_Value_cs[0];
    Racing_2019_B.MultiportSwitch_lj[1] = Racing_2019_P.posedge_Value_cs[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_lj[0] = Racing_2019_P.negedge_Value_os[0];
    Racing_2019_B.MultiportSwitch_lj[1] = Racing_2019_P.negedge_Value_os[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_lj[0] = Racing_2019_P.eitheredge_Value_lb[0];
    Racing_2019_B.MultiportSwitch_lj[1] = Racing_2019_P.eitheredge_Value_lb[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_lj[0],
    Racing_2019_B.DataTypeConversion2_om, Racing_2019_B.UnitDelay_oh,
    &Racing_2019_B.POSITIVEEdge_fy);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_lj[1],
    Racing_2019_B.DataTypeConversion2_om, Racing_2019_B.UnitDelay_oh,
    &Racing_2019_B.NEGATIVEEdge_o5);
  Racing_2019_B.LogicalOperator1_je =
    (Racing_2019_B.POSITIVEEdge_fy.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_o5.RelationalOperator1);
  Racing_2019_B.DataTypeConversion1_gg = Racing_2019_B.LogicalOperator1_je;
  Racing_2019_B.BMS_CAN_231_Counter =
    Racing_2019_DW.BMS_CAN_231_Counter_PreviousInp;
  Racing_2019_B.Add3_b = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion1_gg + Racing_2019_B.BMS_CAN_231_Counter);
  Racing_2019_B.DataTypeConversion2_kg = (Racing_2019_B.SFunction1_o5_nf != 0.0);
  Racing_2019_B.UnitDelay_k = Racing_2019_DW.UnitDelay_DSTATE_pz;
  switch ((int32_T)Racing_2019_P.EdgeDetector1_model_ov) {
   case 1:
    Racing_2019_B.MultiportSwitch_hh[0] = Racing_2019_P.posedge_Value_cx[0];
    Racing_2019_B.MultiportSwitch_hh[1] = Racing_2019_P.posedge_Value_cx[1];
    break;

   case 2:
    Racing_2019_B.MultiportSwitch_hh[0] = Racing_2019_P.negedge_Value_ke[0];
    Racing_2019_B.MultiportSwitch_hh[1] = Racing_2019_P.negedge_Value_ke[1];
    break;

   default:
    Racing_2019_B.MultiportSwitch_hh[0] = Racing_2019_P.eitheredge_Value_cx[0];
    Racing_2019_B.MultiportSwitch_hh[1] = Racing_2019_P.eitheredge_Value_cx[1];
    break;
  }

  Racing_2019_POSITIVEEdge(Racing_2019_B.MultiportSwitch_hh[0],
    Racing_2019_B.DataTypeConversion2_kg, Racing_2019_B.UnitDelay_k,
    &Racing_2019_B.POSITIVEEdge_ji);
  Racing_2019_NEGATIVEEdge(Racing_2019_B.MultiportSwitch_hh[1],
    Racing_2019_B.DataTypeConversion2_kg, Racing_2019_B.UnitDelay_k,
    &Racing_2019_B.NEGATIVEEdge_ju);
  Racing_2019_B.LogicalOperator1_i4 =
    (Racing_2019_B.POSITIVEEdge_ji.RelationalOperator1 ||
     Racing_2019_B.NEGATIVEEdge_ju.RelationalOperator1);
  Racing_2019_B.DataTypeConversion4_md = Racing_2019_B.LogicalOperator1_i4;
  Racing_2019_B.BMS_CAN_222_Counter =
    Racing_2019_DW.BMS_CAN_222_Counter_PreviousInp;
  Racing_2019_B.Add4_mu = (uint8_T)((uint32_T)
    Racing_2019_B.DataTypeConversion4_md + Racing_2019_B.BMS_CAN_222_Counter);
  Racing_2019_B.Compare_dp = (Racing_2019_B.MaxTemperature >=
    Racing_2019_P.Batt_Temp_High_Threshold);
  Racing_2019_B.Compare_fq = (Racing_2019_B.MaxTemperature <=
    Racing_2019_P.Batt_Temp_Low_Threshold);
  Racing_2019_B.Compare_hm = (Racing_2019_B.RateTransition_e >=
    Racing_2019_P.LV_DCDC_Temp_High_Threshold);
  Racing_2019_B.Compare_gr = (Racing_2019_B.RateTransition_e <=
    Racing_2019_P.LV_DCDC_Temp_Low_Threshold);
  Racing_2019_B.LogicalOperator18 = (Racing_2019_B.Compare_dp ||
    Racing_2019_B.Compare_hm);
  Racing_2019_B.LogicalOperator19 = (Racing_2019_B.Compare_fq &&
    Racing_2019_B.Compare_gr);
  Racing_2019_B.Memory_gt = Racing_2019_DW.Memory_PreviousInput_lh;
  tmp_0 = Racing_2019_B.LogicalOperator18;
  rowIdx = tmp_0;
  tmp_0 = Racing_2019_B.LogicalOperator19;
  rowIdx = (int32_T)(((uint32_T)rowIdx << 1) + tmp_0);
  tmp_0 = Racing_2019_B.Memory_gt;
  rowIdx = (int32_T)(((uint32_T)rowIdx << 1) + tmp_0);
  Racing_2019_B.Logic_jg[0U] = Racing_2019_P.Logic_table_c[(uint32_T)rowIdx];
  Racing_2019_B.Logic_jg[1U] = Racing_2019_P.Logic_table_c[rowIdx + 8U];
  Racing_2019_B.LogicalOperator17 = ((Racing_2019_P.Accu_Fans_ON != 0.0) ||
    Racing_2019_B.Logic_jg[0]);
  Racing_2019_B.LogicalOperator16_e = (Racing_2019_B.LogicalOperator17 &&
    (Racing_2019_P.Accu_Fans_Enable != 0.0));
  u0 = Racing_2019_P.Accu_Fans_PWM;
  u1 = Racing_2019_P.Saturation5_LowerSat;
  u2 = Racing_2019_P.Saturation5_UpperSat;
  if (u0 > u2) {
    Racing_2019_B.Saturation5 = u2;
  } else if (u0 < u1) {
    Racing_2019_B.Saturation5 = u1;
  } else {
    Racing_2019_B.Saturation5 = u0;
  }

  if (Racing_2019_B.LogicalOperator16_e) {
    Racing_2019_B.Switch9 = Racing_2019_B.Saturation5;
  } else {
    Racing_2019_B.Switch9 = Racing_2019_P.Constant33_Value;
  }
}

void Racing_2019_update4(void)
{
  Racing_2019_DW.uHzto1kHz_Buffer0 = Racing_2019_B.MaxTemperature;
  Racing_2019_DW.to100Hz7_Buffer0 = Racing_2019_B.CANSegmentsRxError;
  Racing_2019_DW.UnitDelay_DSTATE_a = Racing_2019_B.DataTypeConversion2_ei;
  Racing_2019_DW.BMS_CAN_205_Counter_PreviousInp = Racing_2019_B.Add1_d;
  Racing_2019_DW.UnitDelay_DSTATE_b = Racing_2019_B.DataTypeConversion2_kk;
  Racing_2019_DW.BMS_CAN_206_Counter_PreviousInp = Racing_2019_B.Add2_f;
  Racing_2019_DW.UnitDelay_DSTATE_f = Racing_2019_B.DataTypeConversion2_kt;
  Racing_2019_DW.BMS_CAN_204_Counter_PreviousInp = Racing_2019_B.Add4;
  Racing_2019_DW.UnitDelay_DSTATE_cv = Racing_2019_B.DataTypeConversion2_fv;
  Racing_2019_DW.BMS_CAN_225_Counter_PreviousInp = Racing_2019_B.Add3;
  Racing_2019_DW.UnitDelay_DSTATE_ba = Racing_2019_B.DataTypeConversion2_g;
  Racing_2019_DW.BMS_CAN_208_Counter_PreviousInp = Racing_2019_B.Add1_a;
  Racing_2019_DW.UnitDelay_DSTATE_bd = Racing_2019_B.DataTypeConversion2_o0;
  Racing_2019_DW.BMS_CAN_209_Counter_PreviousInp = Racing_2019_B.Add2_e;
  Racing_2019_DW.UnitDelay_DSTATE_n = Racing_2019_B.DataTypeConversion2_dd;
  Racing_2019_DW.BMS_CAN_226_Counter_PreviousInp = Racing_2019_B.Add3_l;
  Racing_2019_DW.UnitDelay_DSTATE_h = Racing_2019_B.DataTypeConversion2_nu;
  Racing_2019_DW.BMS_CAN_207_Counter_PreviousInp = Racing_2019_B.Add4_j;
  Racing_2019_DW.UnitDelay_DSTATE_g = Racing_2019_B.DataTypeConversion2_cy;
  Racing_2019_DW.BMS_CAN_211_Counter_PreviousInp = Racing_2019_B.Add1_f;
  Racing_2019_DW.UnitDelay_DSTATE_j = Racing_2019_B.DataTypeConversion2_pb;
  Racing_2019_DW.BMS_CAN_212_Counter_PreviousInp = Racing_2019_B.Add2_o;
  Racing_2019_DW.UnitDelay_DSTATE_f2 = Racing_2019_B.DataTypeConversion2_iq;
  Racing_2019_DW.BMS_CAN_227_Counter_PreviousInp = Racing_2019_B.Add3_a;
  Racing_2019_DW.UnitDelay_DSTATE_fi = Racing_2019_B.DataTypeConversion2_l;
  Racing_2019_DW.BMS_CAN_210_Counter_PreviousInp = Racing_2019_B.Add4_c;
  Racing_2019_DW.UnitDelay_DSTATE_d = Racing_2019_B.DataTypeConversion2_ia;
  Racing_2019_DW.BMS_CAN_214_Counter_PreviousInp = Racing_2019_B.Add1_n;
  Racing_2019_DW.UnitDelay_DSTATE_l = Racing_2019_B.DataTypeConversion2_oq;
  Racing_2019_DW.BMS_CAN_215_Counter_PreviousInp = Racing_2019_B.Add2_c;
  Racing_2019_DW.UnitDelay_DSTATE_p = Racing_2019_B.DataTypeConversion2_oc;
  Racing_2019_DW.BMS_CAN_228_Counter_PreviousInp = Racing_2019_B.Add3_e;
  Racing_2019_DW.UnitDelay_DSTATE_jj = Racing_2019_B.DataTypeConversion2_g2;
  Racing_2019_DW.BMS_CAN_213_Counter_PreviousInp = Racing_2019_B.Add4_cd;
  Racing_2019_DW.UnitDelay_DSTATE_cx = Racing_2019_B.DataTypeConversion2_pp;
  Racing_2019_DW.BMS_CAN_217_Counter_PreviousInp = Racing_2019_B.Add1_c;
  Racing_2019_DW.UnitDelay_DSTATE_gg = Racing_2019_B.DataTypeConversion2_dw;
  Racing_2019_DW.BMS_CAN_218_Counter_PreviousInp = Racing_2019_B.Add2_l;
  Racing_2019_DW.UnitDelay_DSTATE_hq = Racing_2019_B.DataTypeConversion2_ke;
  Racing_2019_DW.BMS_CAN_229_Counter_PreviousInp = Racing_2019_B.Add3_n;
  Racing_2019_DW.UnitDelay_DSTATE_o = Racing_2019_B.DataTypeConversion2_ac;
  Racing_2019_DW.BMS_CAN_216_Counter_PreviousInp = Racing_2019_B.Add4_m;
  Racing_2019_DW.UnitDelay_DSTATE_l5 = Racing_2019_B.DataTypeConversion2_pu;
  Racing_2019_DW.BMS_CAN_220_Counter_PreviousInp = Racing_2019_B.Add1_a5;
  Racing_2019_DW.UnitDelay_DSTATE_ju = Racing_2019_B.DataTypeConversion2_if;
  Racing_2019_DW.BMS_CAN_221_Counter_PreviousInp = Racing_2019_B.Add2_la;
  Racing_2019_DW.UnitDelay_DSTATE_bm = Racing_2019_B.DataTypeConversion2_ly;
  Racing_2019_DW.BMS_CAN_230_Counter_PreviousInp = Racing_2019_B.Add3_o;
  Racing_2019_DW.UnitDelay_DSTATE_m = Racing_2019_B.DataTypeConversion2_nn;
  Racing_2019_DW.BMS_CAN_219_Counter_PreviousInp = Racing_2019_B.Add4_l;
  Racing_2019_DW.UnitDelay_DSTATE_pv = Racing_2019_B.DataTypeConversion2_m;
  Racing_2019_DW.BMS_CAN_223_Counter_PreviousInp = Racing_2019_B.Add1_dm;
  Racing_2019_DW.UnitDelay_DSTATE_i = Racing_2019_B.DataTypeConversion2_ko;
  Racing_2019_DW.BMS_CAN_221_Counter_PreviousI_n = Racing_2019_B.Add2_h;
  Racing_2019_DW.UnitDelay_DSTATE_nn = Racing_2019_B.DataTypeConversion2_om;
  Racing_2019_DW.BMS_CAN_231_Counter_PreviousInp = Racing_2019_B.Add3_b;
  Racing_2019_DW.UnitDelay_DSTATE_pz = Racing_2019_B.DataTypeConversion2_kg;
  Racing_2019_DW.BMS_CAN_222_Counter_PreviousInp = Racing_2019_B.Add4_mu;
  Racing_2019_DW.RateTransition3_Buffer0 = Racing_2019_B.Switch9;
  Racing_2019_DW.RateTransition6_Buffer0 = Racing_2019_B.LogicalOperator16_e;
  Racing_2019_DW.Memory_PreviousInput_lh = Racing_2019_B.Logic_jg[0];
}

void Racing_2019_output5(void)
{
  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Motor_Temp_LEFT_Index_UsbFlRec, (Int32)
      Racing_2019_B.MotorTempto1Hz);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }

  {
    UInt16 tempU;
    Int16 errorCode = DSFLREC_USB_NO_ERROR;
    static UInt16 SecFullWarFlag = 0;
    static UInt16 DataLostWarFlag = 0;
    errorCode = dsflrec_usb_write_int32(Motor_Temp_RIGHT_Index_UsbFlRec, (Int32)
      Racing_2019_B.MotorTempto1Hz_o);
    switch (errorCode)
    {

#ifdef DEBUG_POLL

     case DSFLREC_USB_DATA_SECTION_FULL:
      if (SecFullWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_SECTION_FULL_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        SecFullWarFlag = 1;
      }
      break;

     case DSFLREC_USB_OVERRUN:
      if (DataLostWarFlag == 0) {
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_OKCANCEL);
        rti_msg_warning_set(RTI_USB_FLREC_DATA_LOST_WARNING);
        msg_default_dialog_set(MSG_MC_WARNING, MSG_DLG_NONE);
        DataLostWarFlag = 1;
      }
      break;

     case DSFLREC_USB_FLASH_TIME_OUT:
      rti_msg_error_set(RTI_USB_FLREC_FLASH_ERROR);
      exit (1);
      break;

     case DSFLREC_USB_WRITE_NOT_READY:
      rti_msg_error_set(RTI_USB_FLREC_WR_NOT_RDY_ERROR);
      exit (1);
      break;

#endif

     default:
      break;
    }
  }
}

void Racing_2019_update5(void)
{
}

void Racing_2019_output(int_T tid)
{
  switch (tid) {
   case 0 :
    Racing_2019_output0();
    break;

   case 2 :
    Racing_2019_output2();
    break;

   case 3 :
    Racing_2019_output3();
    break;

   case 4 :
    Racing_2019_output4();
    break;

   case 5 :
    Racing_2019_output5();
    break;

   default :
    break;
  }
}

void Racing_2019_update(int_T tid)
{
  switch (tid) {
   case 0 :
    Racing_2019_update0();
    break;

   case 2 :
    Racing_2019_update2();
    break;

   case 3 :
    Racing_2019_update3();
    break;

   case 4 :
    Racing_2019_update4();
    break;

   case 5 :
    Racing_2019_update5();
    break;

   default :
    break;
  }
}

void Racing_2019_initialize(void)
{
  rt_InitInfAndNaN(sizeof(real_T));
  (void) memset((void *)Racing_2019_M, 0,
                sizeof(RT_MODEL_Racing_2019_T));
  (Racing_2019_M)->Timing.TaskCounters.cLimit[0] = 1;
  (Racing_2019_M)->Timing.TaskCounters.cLimit[1] = 1;
  (Racing_2019_M)->Timing.TaskCounters.cLimit[2] = 10;
  (Racing_2019_M)->Timing.TaskCounters.cLimit[3] = 100;
  (Racing_2019_M)->Timing.TaskCounters.cLimit[4] = 200;
  (Racing_2019_M)->Timing.TaskCounters.cLimit[5] = 1000;

  {
    rtsiSetSimTimeStepPtr(&Racing_2019_M->solverInfo,
                          &Racing_2019_M->Timing.simTimeStep);
    rtsiSetTPtr(&Racing_2019_M->solverInfo, &rtmGetTPtr(Racing_2019_M));
    rtsiSetStepSizePtr(&Racing_2019_M->solverInfo,
                       &Racing_2019_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&Racing_2019_M->solverInfo, (&rtmGetErrorStatus
      (Racing_2019_M)));
    rtsiSetRTModelPtr(&Racing_2019_M->solverInfo, Racing_2019_M);
  }

  rtsiSetSimTimeStep(&Racing_2019_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&Racing_2019_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(Racing_2019_M, &Racing_2019_M->Timing.tArray[0]);
  Racing_2019_M->Timing.stepSize0 = 0.001;
  (void) memset(((void *) &Racing_2019_B), 0,
                sizeof(B_Racing_2019_T));
  (void) memset((void *)&Racing_2019_DW, 0,
                sizeof(DW_Racing_2019_T));

  {
    Racing_2019_rti_init_trc_pointers();
  }

  Racing_2019_B.to100Hz = Racing_2019_P.to100Hz_X0;
  Racing_2019_B.to100Hz1 = Racing_2019_P.to100Hz1_X0;
  Racing_2019_B.to100Hz2 = Racing_2019_P.to100Hz2_X0;
  Racing_2019_B.RateTransition13 = Racing_2019_P.RateTransition13_X0;
  Racing_2019_B.uHzto1kHz = Racing_2019_P.uHzto1kHz_X0;
  Racing_2019_B.to100Hz5 = Racing_2019_P.to100Hz5_X0;
  Racing_2019_B.to100Hz6 = Racing_2019_P.to100Hz6_X0;
  Racing_2019_B.to100Hz7 = Racing_2019_P.to100Hz7_X0;
  Racing_2019_B.EnableToggle = Racing_2019_P.EnableToggle_X0;
  Racing_2019_B.StartButton = Racing_2019_P.StartButton_X0;
  Racing_2019_B.BSPDState = Racing_2019_P.to100Hz16_X0;
  Racing_2019_B.to100Hz17 = Racing_2019_P.to100Hz17_X0;
  Racing_2019_B.RateTransition3 = Racing_2019_P.RateTransition3_X0;
  Racing_2019_B.RateTransition6 = Racing_2019_P.RateTransition6_X0;
  Racing_2019_DW.POSITIVEEdge_MODE = false;
  Racing_2019_DW.NEGATIVEEdge_MODE = false;
  Racing_2019_B.to1kHz = Racing_2019_P.to1kHz_X0;
  Racing_2019_PrevZCX.Inverter_RIGHT_CAN_0x162_Reset_ = UNINITIALIZED_ZCSIG;
  Racing_2019_PrevZCX.Inverter_LEFT_CAN_0x161_Reset_Z = UNINITIALIZED_ZCSIG;
  Racing_2019_PrevZCX.Inverter_LEFT_CAN_0x181_Reset_Z = UNINITIALIZED_ZCSIG;
  Racing_2019_PrevZCX.Inverter_RIGHT_CAN_0x182_Reset_ = UNINITIALIZED_ZCSIG;
  Racing_2019_PrevZCX.ResettableDelay50ms_Reset_ZCE = ZERO_ZCSIG;
  Racing_2019_PrevZCX.ResettableDelay50ms2_Reset_ZCE = POS_ZCSIG;
  Racing_2019_PrevZCX.ResettableDelay50ms1_Reset_ZCE = POS_ZCSIG;
  Racing_2019_PrevZCX.ResettableDelay50ms_Reset_ZCE_d = ZERO_ZCSIG;
  Racing_2019_PrevZCX.ResettableDelay350ms_Reset_ZCE = POS_ZCSIG;
  Racing_2019_PrevZCX.ResettableDelay15s_Reset_ZCE = ZERO_ZCSIG;
  Racing_2019_PrevZCX.BMS_CAN_200_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Racing_2019_PrevZCX.BMS_CAN_201_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Racing_2019_PrevZCX.AUX_CAN_314_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Racing_2019_PrevZCX.AUX_CAN_357_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Racing_2019_PrevZCX.AUX_CAN_384_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Racing_2019_PrevZCX.ResettableDelay50ms_Reset_ZCE_m = ZERO_ZCSIG;
  Racing_2019_PrevZCX.AUX_CAN_412_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Racing_2019_PrevZCX.DASH_CAN_101_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Racing_2019_PrevZCX.DASH_CAN_198_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Racing_2019_PrevZCX.DASH_CAN_279_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Racing_2019_PrevZCX.DASH_CAN_246_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Racing_2019_PrevZCX.ResettableDelay1500ms_Reset_ZCE = POS_ZCSIG;
  Racing_2019_PrevZCX.ResettableDelay_Reset_ZCE = POS_ZCSIG;
  Racing_2019_PrevZCX.DASH_CAN_204_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Racing_2019_PrevZCX.ResettableDelay_Reset_ZCE_c = POS_ZCSIG;
  Racing_2019_PrevZCX.TriggeredSubsystem_Trig_ZCE = POS_ZCSIG;
  Racing_2019_PrevZCX.USB_FLIGHT_REC_EJECT_Trig_ZCE = UNINITIALIZED_ZCSIG;

  {
    int32_T i;
    Racing_2019_DW.to100Hz_Buffer0 = Racing_2019_P.to100Hz_X0;
    Racing_2019_DW.to100Hz1_Buffer0 = Racing_2019_P.to100Hz1_X0;
    Racing_2019_DW.to100Hz2_Buffer0 = Racing_2019_P.to100Hz2_X0;
    Racing_2019_DW.Memory_PreviousInput = Racing_2019_P.Memory_X0;
    Racing_2019_DW.DynamicOffsetLEMIDC_PreviousInp =
      Racing_2019_P.DynamicOffsetLEMIDC_X0;
    Racing_2019_DW.IrmsPrevious_PreviousInput = Racing_2019_P.IrmsPrevious_X0;
    Racing_2019_DW.RateTransition13_Buffer0 = Racing_2019_P.RateTransition13_X0;
    Racing_2019_DW.uHzto1kHz_Buffer0 = Racing_2019_P.uHzto1kHz_X0;
    Racing_2019_DW.DynamicOffsetLEMVDC_PreviousInp =
      Racing_2019_P.DynamicOffsetLEMVDC_X0;
    Racing_2019_DW.Memory_PreviousInput_e = Racing_2019_P.Memory_X0_i;
    for (i = 0; i < 50; i++) {
      Racing_2019_DW.Delay50ms_DSTATE[i] =
        Racing_2019_P.Delay50ms_InitialCondition;
    }

    for (i = 0; i < 1000; i++) {
      Racing_2019_DW.Inverter_RIGHT_CAN_0x162_DSTATE[i] =
        Racing_2019_P.Inverter_RIGHT_CAN_0x162_Initia;
      Racing_2019_DW.Inverter_LEFT_CAN_0x161_DSTATE[i] =
        Racing_2019_P.Inverter_LEFT_CAN_0x161_Initial;
    }

    Racing_2019_DW.to100Hz5_Buffer0 = Racing_2019_P.to100Hz5_X0;
    Racing_2019_DW.to100Hz6_Buffer0 = Racing_2019_P.to100Hz6_X0;
    Racing_2019_DW.to100Hz7_Buffer0 = Racing_2019_P.to100Hz7_X0;
    for (i = 0; i < 10000; i++) {
      Racing_2019_DW.Inverter_LEFT_CAN_0x181_DSTATE[i] =
        Racing_2019_P.Inverter_LEFT_CAN_0x181_Initial;
      Racing_2019_DW.Inverter_RIGHT_CAN_0x182_DSTATE[i] =
        Racing_2019_P.Inverter_RIGHT_CAN_0x182_Initia;
    }

    Racing_2019_DW.EnableToggle_Buffer0 = Racing_2019_P.EnableToggle_X0;
    Racing_2019_DW.StartButton_Buffer0 = Racing_2019_P.StartButton_X0;
    for (i = 0; i < 5; i++) {
      Racing_2019_DW.ResettableDelay50ms_DSTATE[i] =
        Racing_2019_P.ResettableDelay50ms_InitialCond;
      Racing_2019_DW.ResettableDelay50ms2_DSTATE[i] =
        Racing_2019_P.ResettableDelay50ms2_InitialCon;
      Racing_2019_DW.ResettableDelay50ms1_DSTATE[i] =
        Racing_2019_P.ResettableDelay50ms1_InitialCon;
    }

    Racing_2019_DW.Memory_PreviousInput_c =
      Racing_2019_P.SRFlipFlop1_initial_condition;
    for (i = 0; i < 50; i++) {
      Racing_2019_DW.ResettableDelay50ms_DSTATE_h[i] =
        Racing_2019_P.ResettableDelay50ms_InitialCo_f;
    }

    for (i = 0; i < 350; i++) {
      Racing_2019_DW.ResettableDelay350ms_DSTATE[i] =
        Racing_2019_P.ResettableDelay350ms_InitialCon;
    }

    Racing_2019_DW.Memory_PreviousInput_h =
      Racing_2019_P.SRFlipFlop_initial_condition;
    Racing_2019_DW.to100Hz16_Buffer0 = Racing_2019_P.to100Hz16_X0;
    Racing_2019_DW.to100Hz17_Buffer0 = Racing_2019_P.to100Hz17_X0;
    for (i = 0; i < 150; i++) {
      Racing_2019_DW.ResettableDelay15s_DSTATE[i] =
        Racing_2019_P.ResettableDelay15s_InitialCondi;
    }

    Racing_2019_DW.UnitDelay_DSTATE = Racing_2019_P.EdgeDetector_ic;
    Racing_2019_DW.UnitDelay_DSTATE_c = Racing_2019_P.EdgeDetector_ic_f;
    Racing_2019_DW.BMS_CAN_200_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_200_Counter_X0;
    for (i = 0; i < 2000; i++) {
      Racing_2019_DW.BMS_CAN_200_DSTATE[i] =
        Racing_2019_P.BMS_CAN_200_InitialCondition;
    }

    Racing_2019_DW.UnitDelay_DSTATE_a = Racing_2019_P.EdgeDetector2_ic;
    Racing_2019_DW.BMS_CAN_205_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_205_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_b = Racing_2019_P.EdgeDetector3_ic;
    Racing_2019_DW.BMS_CAN_206_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_206_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_f = Racing_2019_P.EdgeDetector1_ic;
    Racing_2019_DW.BMS_CAN_204_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_204_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_cv = Racing_2019_P.EdgeDetector4_ic;
    Racing_2019_DW.BMS_CAN_225_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_225_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_ba = Racing_2019_P.EdgeDetector2_ic_g;
    Racing_2019_DW.BMS_CAN_208_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_208_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_bd = Racing_2019_P.EdgeDetector3_ic_f;
    Racing_2019_DW.BMS_CAN_209_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_209_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_n = Racing_2019_P.EdgeDetector4_ic_o;
    Racing_2019_DW.BMS_CAN_226_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_226_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_h = Racing_2019_P.EdgeDetector1_ic_m;
    Racing_2019_DW.BMS_CAN_207_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_207_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_g = Racing_2019_P.EdgeDetector2_ic_d;
    Racing_2019_DW.BMS_CAN_211_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_211_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_j = Racing_2019_P.EdgeDetector3_ic_o;
    Racing_2019_DW.BMS_CAN_212_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_212_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_f2 = Racing_2019_P.EdgeDetector4_ic_n;
    Racing_2019_DW.BMS_CAN_227_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_227_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_fi = Racing_2019_P.EdgeDetector1_ic_a;
    Racing_2019_DW.BMS_CAN_210_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_210_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_d = Racing_2019_P.EdgeDetector2_ic_c;
    Racing_2019_DW.BMS_CAN_214_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_214_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_l = Racing_2019_P.EdgeDetector3_ic_i;
    Racing_2019_DW.BMS_CAN_215_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_215_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_p = Racing_2019_P.EdgeDetector4_ic_g;
    Racing_2019_DW.BMS_CAN_228_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_228_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_jj = Racing_2019_P.EdgeDetector1_ic_d;
    Racing_2019_DW.BMS_CAN_213_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_213_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_cx = Racing_2019_P.EdgeDetector2_ic_f;
    Racing_2019_DW.BMS_CAN_217_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_217_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_gg = Racing_2019_P.EdgeDetector3_ic_fn;
    Racing_2019_DW.BMS_CAN_218_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_218_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_hq = Racing_2019_P.EdgeDetector4_ic_a;
    Racing_2019_DW.BMS_CAN_229_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_229_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_o = Racing_2019_P.EdgeDetector1_ic_i;
    Racing_2019_DW.BMS_CAN_216_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_216_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_l5 = Racing_2019_P.EdgeDetector2_ic_a;
    Racing_2019_DW.BMS_CAN_220_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_220_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_ju = Racing_2019_P.EdgeDetector3_ic_g;
    Racing_2019_DW.BMS_CAN_221_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_221_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_bm = Racing_2019_P.EdgeDetector4_ic_gb;
    Racing_2019_DW.BMS_CAN_230_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_230_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_m = Racing_2019_P.EdgeDetector1_ic_b;
    Racing_2019_DW.BMS_CAN_219_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_219_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_pv = Racing_2019_P.EdgeDetector2_ic_n;
    Racing_2019_DW.BMS_CAN_223_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_223_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_i = Racing_2019_P.EdgeDetector3_ic_i0;
    Racing_2019_DW.BMS_CAN_221_Counter_PreviousI_n =
      Racing_2019_P.BMS_CAN_221_Counter_X0_k;
    Racing_2019_DW.UnitDelay_DSTATE_nn = Racing_2019_P.EdgeDetector4_ic_i;
    Racing_2019_DW.BMS_CAN_231_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_231_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_pz = Racing_2019_P.EdgeDetector1_ic_g;
    Racing_2019_DW.BMS_CAN_222_Counter_PreviousInp =
      Racing_2019_P.BMS_CAN_222_Counter_X0;
    for (i = 0; i < 10; i++) {
      Racing_2019_DW.BMS_CAN_201_DSTATE[i] =
        Racing_2019_P.BMS_CAN_201_InitialCondition;
    }

    for (i = 0; i < 2000; i++) {
      Racing_2019_DW.AUX_CAN_314_DSTATE[i] =
        Racing_2019_P.AUX_CAN_314_InitialCondition;
    }

    for (i = 0; i < 20; i++) {
      Racing_2019_DW.AUX_CAN_357_DSTATE[i] =
        Racing_2019_P.AUX_CAN_357_InitialCondition;
      Racing_2019_DW.AUX_CAN_384_DSTATE[i] =
        Racing_2019_P.AUX_CAN_384_InitialCondition;
    }

    Racing_2019_DW.AUX_CAN_314_Counter_PreviousInp =
      Racing_2019_P.AUX_CAN_314_Counter_X0;
    Racing_2019_DW.AUX_CAN_357_Counter_PreviousInp =
      Racing_2019_P.AUX_CAN_357_Counter_X0;
    Racing_2019_DW.AUX_CAN_384_Counter_PreviousInp =
      Racing_2019_P.AUX_CAN_384_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_c1 = Racing_2019_P.EdgeDetector_ic_p;
    Racing_2019_DW.UnitDelay_DSTATE_cl = Racing_2019_P.EdgeDetector1_ic_iv;
    Racing_2019_DW.UnitDelay_DSTATE_do = Racing_2019_P.EdgeDetector2_ic_j;
    Racing_2019_DW.Memory_PreviousInput_b =
      Racing_2019_P.SRFlipFlop_initial_condition_f;
    Racing_2019_DW.Memory_PreviousInput_m =
      Racing_2019_P.SRFlipFlop1_initial_condition_j;
    Racing_2019_DW.RateTransition3_Buffer0 = Racing_2019_P.RateTransition3_X0;
    Racing_2019_DW.Memory_PreviousInput_d =
      Racing_2019_P.SRFlipFlop3_initial_condition;
    Racing_2019_DW.Memory_PreviousInput_k =
      Racing_2019_P.SRFlipFlop4_initial_condition;
    Racing_2019_DW.RateTransition6_Buffer0 = Racing_2019_P.RateTransition6_X0;
    Racing_2019_DW.Memory_PreviousInput_fq = Racing_2019_P.Memory_X0_l;
    Racing_2019_DW.Memory_PreviousInput_l =
      Racing_2019_P.SRFlipFlop_initial_condition_o;
    for (i = 0; i < 50; i++) {
      Racing_2019_DW.ResettableDelay50ms_DSTATE_j[i] =
        Racing_2019_P.ResettableDelay50ms_InitialCo_b;
    }

    for (i = 0; i < 10; i++) {
      Racing_2019_DW.AUX_CAN_412_DSTATE[i] =
        Racing_2019_P.AUX_CAN_412_InitialCondition;
    }

    Racing_2019_DW.InverterLEFTBaudrateRx_Previous =
      Racing_2019_P.InverterLEFTBaudrateRx_X0;
    Racing_2019_DW.InverterRIGHTBaudrateRx_Previou =
      Racing_2019_P.InverterRIGHTBaudrateRx_X0;
    Racing_2019_DW.InverterLEFTBaudrateTx_Previous =
      Racing_2019_P.InverterLEFTBaudrateTx_X0;
    Racing_2019_DW.Output_DSTATE = Racing_2019_P.Output_InitialCondition;
    Racing_2019_DW.Memory1_PreviousInput = Racing_2019_P.Memory1_X0;
    Racing_2019_DW.Output_DSTATE_f = Racing_2019_P.Output_InitialCondition_m;
    Racing_2019_DW.Memory1_PreviousInput_n = Racing_2019_P.Memory1_X0_i;
    Racing_2019_DW.InverterLEFTBaudrateTx_Previo_o =
      Racing_2019_P.InverterLEFTBaudrateTx_X0_p;
    Racing_2019_DW.Output_DSTATE_c = Racing_2019_P.Output_InitialCondition_a;
    Racing_2019_DW.Delay1ms_DSTATE = Racing_2019_P.Delay1ms_InitialCondition;
    Racing_2019_DW.Memory1_PreviousInput_m = Racing_2019_P.Memory1_X0_o;
    Racing_2019_DW.Output_DSTATE_fj = Racing_2019_P.Output_InitialCondition_av;
    Racing_2019_DW.Delay1ms_DSTATE_a = Racing_2019_P.Delay1ms_InitialCondition_m;
    Racing_2019_DW.Memory1_PreviousInput_l = Racing_2019_P.Memory1_X0_o0;
    Racing_2019_DW.AccuBaudrateRx_PreviousInput =
      Racing_2019_P.AccuBaudrateRx_X0;
    Racing_2019_DW.AccuBaudrateTx_PreviousInput =
      Racing_2019_P.AccuBaudrateTx_X0;
    Racing_2019_DW.Output_DSTATE_i = Racing_2019_P.Output_InitialCondition_h;
    Racing_2019_DW.Memory1_PreviousInput_f = Racing_2019_P.Memory1_X0_e;
    Racing_2019_DW.Output_DSTATE_ix = Racing_2019_P.Output_InitialCondition_f;
    Racing_2019_DW.Memory1_PreviousInput_g = Racing_2019_P.Memory1_X0_oi;
    Racing_2019_DW.DashAuxBaudrateRx_PreviousInput =
      Racing_2019_P.DashAuxBaudrateRx_X0;
    Racing_2019_DW.DashAuxBaudrateTx_PreviousInput =
      Racing_2019_P.DashAuxBaudrateTx_X0;
    Racing_2019_DW.Output_DSTATE_e = Racing_2019_P.Output_InitialCondition_k;
    Racing_2019_DW.Memory1_PreviousInput_n3 = Racing_2019_P.Memory1_X0_iz;
    Racing_2019_DW.Output_DSTATE_cy = Racing_2019_P.Output_InitialCondition_o;
    Racing_2019_DW.Delay2ms_DSTATE[0] = Racing_2019_P.Delay2ms_InitialCondition;
    Racing_2019_DW.Delay2ms_DSTATE_n[0] =
      Racing_2019_P.Delay2ms_InitialCondition_l;
    Racing_2019_DW.Delay2ms_DSTATE_nf[0] =
      Racing_2019_P.Delay2ms_InitialCondition_ln;
    Racing_2019_DW.Delay2ms_DSTATE_p[0] =
      Racing_2019_P.Delay2ms_InitialCondition_o;
    Racing_2019_DW.Delay2ms_DSTATE_a[0] =
      Racing_2019_P.Delay2ms_InitialCondition_m;
    Racing_2019_DW.Delay2ms_DSTATE_nq[0] =
      Racing_2019_P.Delay2ms_InitialCondition_j;
    Racing_2019_DW.Delay2ms_DSTATE[1] = Racing_2019_P.Delay2ms_InitialCondition;
    Racing_2019_DW.Delay2ms_DSTATE_n[1] =
      Racing_2019_P.Delay2ms_InitialCondition_l;
    Racing_2019_DW.Delay2ms_DSTATE_nf[1] =
      Racing_2019_P.Delay2ms_InitialCondition_ln;
    Racing_2019_DW.Delay2ms_DSTATE_p[1] =
      Racing_2019_P.Delay2ms_InitialCondition_o;
    Racing_2019_DW.Delay2ms_DSTATE_a[1] =
      Racing_2019_P.Delay2ms_InitialCondition_m;
    Racing_2019_DW.Delay2ms_DSTATE_nq[1] =
      Racing_2019_P.Delay2ms_InitialCondition_j;
    Racing_2019_DW.Memory1_PreviousInput_lx = Racing_2019_P.Memory1_X0_k;
    Racing_2019_DW.Memory_PreviousInput_er =
      Racing_2019_P.SRFlipFlop2_initial_condition;
    Racing_2019_DW.DASH_CAN_198_Counter_PreviousIn =
      Racing_2019_P.DASH_CAN_198_Counter_X0;
    Racing_2019_DW.Memory_PreviousInput_fh = Racing_2019_P.EdgeDetector_ic_m;
    Racing_2019_DW.DASH_CAN_101_Counter_PreviousIn =
      Racing_2019_P.DASH_CAN_101_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_di = Racing_2019_P.EdgeDetector1_ic_c;
    Racing_2019_DW.UnitDelay_DSTATE_k = Racing_2019_P.EdgeDetector3_ic_j;
    Racing_2019_DW.DASH_CAN_279_Counter_PreviousIn =
      Racing_2019_P.DASH_CAN_279_Counter_X0;
    for (i = 0; i < 2000; i++) {
      Racing_2019_DW.DASH_CAN_101_DSTATE[i] =
        Racing_2019_P.DASH_CAN_101_InitialCondition;
      Racing_2019_DW.DASH_CAN_198_DSTATE[i] =
        Racing_2019_P.DASH_CAN_198_InitialCondition;
    }

    Racing_2019_DW.UnitDelay_DSTATE_hk = Racing_2019_P.EdgeDetector2_ic_o;
    Racing_2019_DW.DASH_CAN_246_Counter_PreviousIn =
      Racing_2019_P.DASH_CAN_246_Counter_X0;
    for (i = 0; i < 20; i++) {
      Racing_2019_DW.DASH_CAN_279_DSTATE[i] =
        Racing_2019_P.DASH_CAN_279_InitialCondition;
      Racing_2019_DW.DASH_CAN_246_DSTATE[i] =
        Racing_2019_P.DASH_CAN_246_InitialCondition;
    }

    Racing_2019_DW.Memory_PreviousInput_eb =
      Racing_2019_P.RTDS_initial_condition;
    for (i = 0; i < 150; i++) {
      Racing_2019_DW.ResettableDelay1500ms_DSTATE[i] =
        Racing_2019_P.ResettableDelay1500ms_InitialCo;
    }

    Racing_2019_DW.Delay400ms_DSTATE[0] =
      Racing_2019_P.Delay400ms_InitialCondition;
    Racing_2019_DW.Delay400ms_DSTATE[1] =
      Racing_2019_P.Delay400ms_InitialCondition;
    Racing_2019_DW.Delay400ms_DSTATE[2] =
      Racing_2019_P.Delay400ms_InitialCondition;
    Racing_2019_DW.Delay400ms_DSTATE[3] =
      Racing_2019_P.Delay400ms_InitialCondition;
    Racing_2019_DW.Memory_PreviousInput_k0 =
      Racing_2019_P.SRFlipFlop_initial_condition_n;
    Racing_2019_DW.Memory1_PreviousInput_a = Racing_2019_P.Memory1_X0_d;
    for (i = 0; i < 500; i++) {
      Racing_2019_DW.ResettableDelay_DSTATE[i] =
        Racing_2019_P.ResettableDelay_InitialConditio;
    }

    Racing_2019_DW.Memory_PreviousInput_e2 =
      Racing_2019_P.SCCircuitFlipFlop_initial_condi;
    for (i = 0; i < 1000; i++) {
      Racing_2019_DW.DASH_CAN_204_DSTATE[i] =
        Racing_2019_P.DASH_CAN_204_InitialCondition;
    }

    Racing_2019_DW.Memory_PreviousInput_f = Racing_2019_P.Memory_X0_o;
    Racing_2019_DW.Memory_PreviousInput_kl =
      Racing_2019_P.PressedOnce_initial_condition;
    Racing_2019_DW.MemoryLEMVDC_PreviousInput = Racing_2019_P.MemoryLEMVDC_X0;
    Racing_2019_DW.Output_DSTATE_g = Racing_2019_P.Output_InitialCondition_kh;
    Racing_2019_DW.Delay_DSTATE = Racing_2019_P.Delay_InitialCondition;
    Racing_2019_DW.Memory_PreviousInput_bp =
      Racing_2019_P.SRFlipFlopLEMVDC_initial_condit;
    Racing_2019_DW.MemoryLEMIDC_PreviousInput = Racing_2019_P.MemoryLEMIDC_X0;
    Racing_2019_DW.Output_DSTATE_k = Racing_2019_P.Output_InitialCondition_c;
    Racing_2019_DW.Delay_DSTATE_k = Racing_2019_P.Delay_InitialCondition_n;
    Racing_2019_DW.Memory_PreviousInput_kz =
      Racing_2019_P.SRFlipFlopLEMIDC_initial_condit;
    Racing_2019_DW.DynamicOffsetLEMLeft_PreviousIn =
      Racing_2019_P.DynamicOffsetLEMLeft_X0;
    Racing_2019_DW.MemoryLEMIACLeft_PreviousInput =
      Racing_2019_P.MemoryLEMIACLeft_X0;
    Racing_2019_DW.Output_DSTATE_a = Racing_2019_P.Output_InitialCondition_n;
    Racing_2019_DW.Delay_DSTATE_e = Racing_2019_P.Delay_InitialCondition_d;
    Racing_2019_DW.Memory_PreviousInput_mu =
      Racing_2019_P.SRFlipFlopLEMLeft_initial_condi;
    Racing_2019_DW.DynamicOffsetLEMRight_PreviousI =
      Racing_2019_P.DynamicOffsetLEMRight_X0;
    Racing_2019_DW.MemoryLEMIACRight_PreviousInput =
      Racing_2019_P.MemoryLEMIACRight_X0;
    Racing_2019_DW.Output_DSTATE_j = Racing_2019_P.Output_InitialCondition_b;
    Racing_2019_DW.Delay_DSTATE_h = Racing_2019_P.Delay_InitialCondition_dc;
    Racing_2019_DW.Memory_PreviousInput_df =
      Racing_2019_P.SRFlipFlopLEMRight_initial_cond;
    Racing_2019_DW.DiscreteTimeIntegrator_DSTATE =
      Racing_2019_P.DiscreteTimeIntegrator_IC;
    Racing_2019_DW.DiscreteTimeIntegrator1_DSTATE =
      Racing_2019_P.DiscreteTimeIntegrator1_IC;
    Racing_2019_DW.Meters_Max_DSTATE = Racing_2019_P.Meters_Max_IC;
    Racing_2019_DW.Meters_Min_DSTATE = Racing_2019_P.Meters_Min_IC;
    Racing_2019_DW.to1kHz_Buffer0 = Racing_2019_P.to1kHz_X0;
    Racing_2019_DW.FixPtUnitDelay1_DSTATE = Racing_2019_P.KW_MAX_vinit;
    Racing_2019_DW.FixPtUnitDelay1_DSTATE_a = Racing_2019_P.KW_MAX_Regen_vinit;
    Racing_2019_DW.UnitDelay_DSTATE_od = Racing_2019_P.EdgeDetector_ic_k;
    Racing_2019_DW.Inverter_LEFT_CAN_Rx_Counter_Pr =
      Racing_2019_P.Inverter_LEFT_CAN_Rx_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_e = Racing_2019_P.EdgeDetector_ic_g;
    Racing_2019_DW.Inverter_RIGHT_CAN_Rx_Counter_P =
      Racing_2019_P.Inverter_RIGHT_CAN_Rx_Counter_X;
    Racing_2019_DW.clockTickCounter = 0;
    Racing_2019_DW.UnitDelay_DSTATE_og = Racing_2019_P.EdgeDetector_ic_b;
    Racing_2019_DW.Inverter_LEFT_CAN_Tx_Counter_Pr =
      Racing_2019_P.Inverter_LEFT_CAN_Tx_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_bdf = Racing_2019_P.EdgeDetector1_ic_ir;
    Racing_2019_DW.Inverter_RIGHT_CAN_Tx_Counter_P =
      Racing_2019_P.Inverter_RIGHT_CAN_Tx_Counter_X;
    Racing_2019_DW.UnitDelay_DSTATE_m0 = Racing_2019_P.EdgeDetector4_ic_h;
    Racing_2019_DW.Brake_Error_Counter_PreviousInp =
      Racing_2019_P.Brake_Error_Counter_X0;
    Racing_2019_DW.APPS1_Error_Counter_PreviousInp =
      Racing_2019_P.APPS1_Error_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_hx = Racing_2019_P.EdgeDetector4_ic_m;
    Racing_2019_DW.APPS_NotAgree_Error_Counter_Pre =
      Racing_2019_P.APPS_NotAgree_Error_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_fb = Racing_2019_P.EdgeDetector4_ic_iu;
    Racing_2019_DW.APPS2_Error_Counter_PreviousInp =
      Racing_2019_P.APPS2_Error_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_hr = Racing_2019_P.EdgeDetector4_ic_d;
    Racing_2019_DW.UnitDelay_DSTATE_pzg = Racing_2019_P.EdgeDetector4_ic_ng;
    Racing_2019_DW.Sensor_Error_Counter_PreviousIn =
      Racing_2019_P.Sensor_Error_Counter_X0;
    Racing_2019_DW.UnitDelay_DSTATE_bo = Racing_2019_P.EdgeDetector4_ic_g0;
    Racing_2019_DW.Steering_Error_Counter_Previous =
      Racing_2019_P.Steering_Error_Counter_X0;
    Racing_2019_DW.FixPtUnitDelay1_DSTATE_d =
      Racing_2019_P.IDC_Regen_last_max_vinit;
    Racing_2019_DW.ResettableDelay_DSTATE_j =
      Racing_2019_P.ResettableDelay_InitialCondit_a;
    Racing_2019_DW.FixPtUnitDelay1_DSTATE_g = Racing_2019_P.IDC_Regen_max_vinit;
    Racing_2019_DW.Memory_PreviousInput_lh =
      Racing_2019_P.SRFlipFlop5_initial_condition;
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.IrmsLEFTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.IrmsLEFTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.CommandedTorqueLEFT,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.CommandedTorqueLEFT);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.RPMLEFTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.RPMLEFTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.MotorTempLEFTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.MotorTempLEFTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.IGBTTempLEFTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.IGBTTempLEFTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.AirTempLEFTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.AirTempLEFTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.IpeakLEFTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.IpeakLEFTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.IcontLEFTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.IcontLEFTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.VoutLEFT,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.VoutLEFT);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.ErrorLEFTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.ErrorLEFTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.RPMLimitLEFTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.RPMLimitLEFTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.BTBLEFTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.BTBLEFTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.MotorPowerLEFTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.MotorPowerLEFTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.IrmsRIGHTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.IrmsRIGHTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.CommandTorqueRIGHT,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.CommandTorqueRIGHT);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.RPMRIGHTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.RPMRIGHTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.MotorTempRIGHTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.MotorTempRIGHTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.IGBTTempRIGHTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.IGBTTempRIGHTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.AirTempRIGHTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.AirTempRIGHTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.IpeakRIGHTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.IpeakRIGHTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.IcontRIGHTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.IcontRIGHTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.VoutRIGHTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.VoutRIGHTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.ErrorRIGHTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.ErrorRIGHTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.RPMLimitRIGHTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.RPMLimitRIGHTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.BTBRIGHTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.BTBRIGHTRaw);
    Racing_201_IrmsLEFTRaw_Init(&Racing_2019_B.MotorPowerRIGHTRaw,
      (P_IrmsLEFTRaw_Racing_2019_T *)&Racing_2019_P.MotorPowerRIGHTRaw);
    Racing_2019_B.IGBTLosses = Racing_2019_P.IGBTLosses_InitialOutput;
    Racing_2019_B.SFunction1_g = Racing_2019_P.TXstatus_Y0_a;
    Racing_2019_B.SFunction1_kx = Racing_2019_P.TXstatus_Y0;
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_k,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_k);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_p,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_p);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_h,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_h);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_pb,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_pb);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_n,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_n);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_h,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_h);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_j,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_j);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_e,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_e);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_c,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_c);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_i,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_i);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_na,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_na);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_eh,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_eh);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_nm,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_nm);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_b,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_b);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_o,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_o);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_n,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_n);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_oy,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_oy);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_o,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_o);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_k1,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_k1);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_d,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_d);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_hc,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_hc);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_a,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_a);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_b,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_b);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_j,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_j);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_kp,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_kp);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_ec,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_ec);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_cx,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_cx);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_ae,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_ae);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_bs,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_bs);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_jr,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_jr);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_g,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_g);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_k,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_k);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_p,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_p);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_g,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_g);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_gm,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_gm);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_ot,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_ot);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_b4,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_b4);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_ei,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_ei);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_i,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_i);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_l,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_l);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_m,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_m);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_gr,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_gr);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_n3,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_n3);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_kq,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_kq);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_bsv,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_bsv);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_bl,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_bl);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_f,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_f);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_id,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_id);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_a,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_a);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_h5,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_h5);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_iy,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_iy);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_m,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_m);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_hw,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_hw);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_ph,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_ph);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_fy,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_fy);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_o5,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_o5);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_ji,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_ji);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_ju,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_ju);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_hj,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_hj);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_jrj,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_jrj);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_d,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_d);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_gu,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_gu);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_o4,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_o4);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_je,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_je);
    Racing_2019_B.RelationalOperator1 = Racing_2019_P.OUT_Y0_d;
    Racing_2019_B.RelationalOperator1_j = Racing_2019_P.OUT_Y0;
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_kh,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_kh);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_ap,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_ap);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_e,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_e);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_ps,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_ps);
    Racing_2019_B.In1 = Racing_2019_P.Out1_Y0;
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_fb,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_fb);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_pj,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_pj);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_pn,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_pn);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_br,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_br);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_ex,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_ex);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_o3,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_o3);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_cj,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_cj);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_po,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_po);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_as,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_as);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_gi,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_gi);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_oo,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_oo);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_i5,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_i5);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_gm1,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_gm1);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_n3,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_n3);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_a0,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_a0);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_phu,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_phu);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_iyn,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_iyn);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_b4,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_b4);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_ms,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_ms);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_f,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_f);
    Racing_20_POSITIVEEdge_Init(&Racing_2019_B.POSITIVEEdge_f5,
      (P_POSITIVEEdge_Racing_2019_T *)&Racing_2019_P.POSITIVEEdge_f5);
    Racing_20_NEGATIVEEdge_Init(&Racing_2019_B.NEGATIVEEdge_op,
      (P_NEGATIVEEdge_Racing_2019_T *)&Racing_2019_P.NEGATIVEEdge_op);
  }
}

void Racing_2019_terminate(void)
{
  {
    while ((rtican_type1_tq_error[1][0] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X65])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[0][2] = can_tp1_msg_sleep
            (can_type1_msg_M1[CANTP1_M1_C1_RX_STD_0X181])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[0][3] = can_tp1_msg_sleep
            (can_type1_msg_M1[CANTP1_M1_C2_RX_STD_0X182])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[0][1] = can_tp1_msg_sleep
            (can_type1_msg_M1[CANTP1_M1_C2_TX_STD_0X162])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[0][0] = can_tp1_msg_sleep
            (can_type1_msg_M1[CANTP1_M1_C1_TX_STD_0X161])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][0] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XC6])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][0] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XC8])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  dio_tp4_digout_init(DIO_TP4_1_MODULE_ADDR, 1, DIO_TP4_MASK_CH5,
                      DIO_TP4_LS_DISABLE, DIO_TP4_HS_DISABLE);
  dio_tp4_digout_init(DIO_TP4_1_MODULE_ADDR, 1, DIO_TP4_MASK_CH10,
                      DIO_TP4_LS_DISABLE, DIO_TP4_HS_DISABLE);
  dio_tp4_digout_init(DIO_TP4_1_MODULE_ADDR, 1, DIO_TP4_MASK_CH4,
                      DIO_TP4_LS_DISABLE, DIO_TP4_HS_DISABLE);

  {
    while ((rtican_type1_tq_error[1][1] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCE])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][0] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCD])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][0] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCC])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][1] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD1])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][1] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD0])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][1] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCF])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][2] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD4])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][1] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD3])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][1] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD2])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][2] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD7])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][2] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD6])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][2] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD5])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][2] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDA])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][2] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD9])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][2] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD8])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][3] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDD])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][3] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDC])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][3] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDB])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][3] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE0])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][3] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDF])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][3] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDE])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][4] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE2])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][4] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE3])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][4] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE4])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][4] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE5])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][4] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE6])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][4] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE7])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][4] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE1])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][0] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C1_TX_STD_0XC9])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][5] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X13A])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][5] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X165])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][5] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X180])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][5] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0X19C])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][0] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XA6])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][5] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X117])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][5] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XF6])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }

  {
    while ((rtican_type1_tq_error[1][0] = can_tp1_msg_sleep
            (can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XCC])) ==
           DSMCOM_BUFFER_OVERFLOW) ;
  }
}
