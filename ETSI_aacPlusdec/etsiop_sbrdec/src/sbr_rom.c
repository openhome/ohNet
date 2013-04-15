/*
   definition of constant tables
 */

#include <stdlib.h>
#include "sbrdecoder.h"
#include "sbr_rom.h"
#include "qmf_dec.h"


/*!
  \name   StartBands
  \brief  Start subbands of the highband.

*/
const Word8 sbr_start_freq_44[16] = { 8, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 23, 25, 28, 32};
const Word8 sbr_start_freq_48[16] = { 7,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20, 22, 24, 27, 31};
const Word8 sbr_start_freq_16[16] = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
const Word8 sbr_start_freq_22[16] = {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 26, 28, 30};
const Word8 sbr_start_freq_24[16] = {11, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 27, 29, 32};
const Word8 sbr_start_freq_32[16] = {10, 12, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 27, 29, 32};



/*!
  \name   EnvAdj
  \brief  Constants and tables used for envelope adjustment
*/

/*! Mantissas of gain limits */
const Word16 sbr_limGains_m[4] = 
{
  (Word16)0x4027,   /*!< -3 dB. Gain limit when limiterGains in frameData is 0 */
  (Word16)0x4000,   /*!< 0 dB.  Gain limit when limiterGains in frameData is 1 */
  (Word16)0x7fb2,   /*!< +3 dB. Gain limit when limiterGains in frameData is 2 */
  (Word16)0x56bc    /*!< Inf.   Gain limit when limiterGains in frameData is 3 */
};

/*! Exponents of gain limits */
const Word16 sbr_limGains_e[4] = 
{
  0, 1, 1, 67
};

/*! Constants for calculating the number of limiter bands */
const Word16 sbr_limiterBandsPerOctaveDiv4[4] =
{
  (Word16)0x2000,
  (Word16)0x2666,
  (Word16)0x4000,
  (Word16)0x6000
};

/*! Ratio of old gains and noise levels for the first 4 timeslots of an envelope */
const Word16 sbr_smoothFilter[4] = {
  (Word16)0x5555,
  (Word16)0x461d,
  (Word16)0x3387,
  (Word16)0x1bb8
};


/*! Lookup-table for inverse of integers */
const Word16 sbr_invIntTable[INV_INT_TABLE_SIZE] = {
  (Word16)0x7fff,  /*!< 1/0  should be inf */
  (Word16)0x7fff,
  (Word16)0x4000,
  (Word16)0x2aab,
  (Word16)0x2000,
  (Word16)0x199a,
  (Word16)0x1555,
  (Word16)0x1249,
  (Word16)0x1000,
  (Word16)0x0e39,
  (Word16)0x0ccd,
  (Word16)0x0ba3,
  (Word16)0x0aab,
  (Word16)0x09d9,
  (Word16)0x0925,
  (Word16)0x0889,
  (Word16)0x0800,
  (Word16)0x0788,
  (Word16)0x071c,
  (Word16)0x06bd,
  (Word16)0x0666,
  (Word16)0x0618,
  (Word16)0x05d1,
  (Word16)0x0591,
  (Word16)0x0555,
  (Word16)0x051f,
  (Word16)0x04ec,
  (Word16)0x04be,
  (Word16)0x0492,
  (Word16)0x046a,
  (Word16)0x0444,
  (Word16)0x0421,
  (Word16)0x0400,
  (Word16)0x03e1,
  (Word16)0x03c4,
  (Word16)0x03a8,
  (Word16)0x038e,
  (Word16)0x0376,
  (Word16)0x035e,
  (Word16)0x0348,
  (Word16)0x0333,
  (Word16)0x031f,
  (Word16)0x030c,
  (Word16)0x02fa,
  (Word16)0x02e9,
  (Word16)0x02d8,
  (Word16)0x02c8,
  (Word16)0x02b9
};


#ifdef LP_SBR_ONLY
/*! This is a predefined random noise which will be modulated to the desired level.
  The accuracy is limited to 12 bits (which is sufficient) due to an implicit
  scale of 1/16.
*/
const Word16 sbr_randomPhase[SBR_NF_NO_RANDOM_VAL + MAX_FREQ_COEFFS] = {
  (Word16)0xf801,  /*   0 */
  (Word16)0x07c5,  /*   1 */
  (Word16)0x0121,  /*   2 */
  (Word16)0xfc3d,  /*   3 */
  (Word16)0x0675,  /*   4 */
  (Word16)0xfce2,  /*   5 */
  (Word16)0xffea,  /*   6 */
  (Word16)0xf8b3,  /*   7 */
  (Word16)0x0463,  /*   8 */
  (Word16)0x0333,  /*   9 */
  (Word16)0xf803,  /*  10 */
  (Word16)0xf85c,  /*  11 */
  (Word16)0xfc58,  /*  12 */
  (Word16)0xfa2a,  /*  13 */
  (Word16)0x060d,  /*  14 */
  (Word16)0x0091,  /*  15 */
  (Word16)0x05f6,  /*  16 */
  (Word16)0xf849,  /*  17 */
  (Word16)0x026f,  /*  18 */
  (Word16)0x0553,  /*  19 */
  (Word16)0x0756,  /*  20 */
  (Word16)0xfa57,  /*  21 */
  (Word16)0xfa65,  /*  22 */
  (Word16)0xf80a,  /*  23 */
  (Word16)0x07da,  /*  24 */
  (Word16)0xfba0,  /*  25 */
  (Word16)0xffdd,  /*  26 */
  (Word16)0xf91c,  /*  27 */
  (Word16)0xf817,  /*  28 */
  (Word16)0x0424,  /*  29 */
  (Word16)0xf807,  /*  30 */
  (Word16)0xf801,  /*  31 */
  (Word16)0x046c,  /*  32 */
  (Word16)0x02c4,  /*  33 */
  (Word16)0x0503,  /*  34 */
  (Word16)0xf9d4,  /*  35 */
  (Word16)0xf8ac,  /*  36 */
  (Word16)0xf9e6,  /*  37 */
  (Word16)0x0662,  /*  38 */
  (Word16)0x045c,  /*  39 */
  (Word16)0xf926,  /*  40 */
  (Word16)0xf892,  /*  41 */
  (Word16)0xff10,  /*  42 */
  (Word16)0x01b5,  /*  43 */
  (Word16)0xf9e8,  /*  44 */
  (Word16)0x07d9,  /*  45 */
  (Word16)0xf920,  /*  46 */
  (Word16)0xf889,  /*  47 */
  (Word16)0x0270,  /*  48 */
  (Word16)0x06d3,  /*  49 */
  (Word16)0x074e,  /*  50 */
  (Word16)0xff87,  /*  51 */
  (Word16)0x0246,  /*  52 */
  (Word16)0x079f,  /*  53 */
  (Word16)0xf9b7,  /*  54 */
  (Word16)0xf856,  /*  55 */
  (Word16)0x0698,  /*  56 */
  (Word16)0xfac9,  /*  57 */
  (Word16)0xf882,  /*  58 */
  (Word16)0x0750,  /*  59 */
  (Word16)0xfa5e,  /*  60 */
  (Word16)0x000c,  /*  61 */
  (Word16)0x0720,  /*  62 */
  (Word16)0xfa81,  /*  63 */
  (Word16)0x05c6,  /*  64 */
  (Word16)0xfaf7,  /*  65 */
  (Word16)0x0265,  /*  66 */
  (Word16)0xf8a8,  /*  67 */
  (Word16)0x07f2,  /*  68 */
  (Word16)0x0697,  /*  69 */
  (Word16)0xf81e,  /*  70 */
  (Word16)0xf854,  /*  71 */
  (Word16)0xfe4a,  /*  72 */
  (Word16)0xfa7f,  /*  73 */
  (Word16)0x0759,  /*  74 */
  (Word16)0xf851,  /*  75 */
  (Word16)0x0422,  /*  76 */
  (Word16)0x04e4,  /*  77 */
  (Word16)0x03c9,  /*  78 */
  (Word16)0x0748,  /*  79 */
  (Word16)0x0396,  /*  80 */
  (Word16)0x0554,  /*  81 */
  (Word16)0x05fe,  /*  82 */
  (Word16)0xf809,  /*  83 */
  (Word16)0x07cb,  /*  84 */
  (Word16)0x05d1,  /*  85 */
  (Word16)0x07a2,  /*  86 */
  (Word16)0xfa2a,  /*  87 */
  (Word16)0xf92c,  /*  88 */
  (Word16)0xf97d,  /*  89 */
  (Word16)0xf8f7,  /*  90 */
  (Word16)0xfa46,  /*  91 */
  (Word16)0x06af,  /*  92 */
  (Word16)0xfc27,  /*  93 */
  (Word16)0x07c5,  /*  94 */
  (Word16)0x0429,  /*  95 */
  (Word16)0xffef,  /*  96 */
  (Word16)0xfa60,  /*  97 */
  (Word16)0xf854,  /*  98 */
  (Word16)0x07c4,  /*  99 */
  (Word16)0xf89c,  /* 100 */
  (Word16)0xfa71,  /* 101 */
  (Word16)0x0220,  /* 102 */
  (Word16)0x023e,  /* 103 */
  (Word16)0xfa12,  /* 104 */
  (Word16)0xffdc,  /* 105 */
  (Word16)0xfb97,  /* 106 */
  (Word16)0x07d6,  /* 107 */
  (Word16)0xf810,  /* 108 */
  (Word16)0xfa96,  /* 109 */
  (Word16)0x00bb,  /* 110 */
  (Word16)0xfa44,  /* 111 */
  (Word16)0x067b,  /* 112 */
  (Word16)0x0340,  /* 113 */
  (Word16)0xfa96,  /* 114 */
  (Word16)0x06f3,  /* 115 */
  (Word16)0xf80a,  /* 116 */
  (Word16)0x06bf,  /* 117 */
  (Word16)0xff43,  /* 118 */
  (Word16)0x07ff,  /* 119 */
  (Word16)0xf99f,  /* 120 */
  (Word16)0x07b5,  /* 121 */
  (Word16)0xf99b,  /* 122 */
  (Word16)0xff13,  /* 123 */
  (Word16)0xfcce,  /* 124 */
  (Word16)0x07ed,  /* 125 */
  (Word16)0x024a,  /* 126 */
  (Word16)0xf956,  /* 127 */
  (Word16)0x07a2,  /* 128 */
  (Word16)0xff7c,  /* 129 */
  (Word16)0xf809,  /* 130 */
  (Word16)0xfac3,  /* 131 */
  (Word16)0xf980,  /* 132 */
  (Word16)0xf807,  /* 133 */
  (Word16)0x0006,  /* 134 */
  (Word16)0x059d,  /* 135 */
  (Word16)0x07b5,  /* 136 */
  (Word16)0xfa7d,  /* 137 */
  (Word16)0xfd36,  /* 138 */
  (Word16)0x075c,  /* 139 */
  (Word16)0xf814,  /* 140 */
  (Word16)0x0582,  /* 141 */
  (Word16)0xf80b,  /* 142 */
  (Word16)0x078a,  /* 143 */
  (Word16)0xfa9b,  /* 144 */
  (Word16)0xfc36,  /* 145 */
  (Word16)0x0125,  /* 146 */
  (Word16)0xfda9,  /* 147 */
  (Word16)0x0381,  /* 148 */
  (Word16)0xfd18,  /* 149 */
  (Word16)0xff4d,  /* 150 */
  (Word16)0xf848,  /* 151 */
  (Word16)0x0471,  /* 152 */
  (Word16)0x05e2,  /* 153 */
  (Word16)0xfd87,  /* 154 */
  (Word16)0x0049,  /* 155 */
  (Word16)0x07e6,  /* 156 */
  (Word16)0xf977,  /* 157 */
  (Word16)0x056e,  /* 158 */
  (Word16)0xfebc,  /* 159 */
  (Word16)0x0675,  /* 160 */
  (Word16)0x03d3,  /* 161 */
  (Word16)0x07b6,  /* 162 */
  (Word16)0xf812,  /* 163 */
  (Word16)0x06a6,  /* 164 */
  (Word16)0xfb4d,  /* 165 */
  (Word16)0x07a5,  /* 166 */
  (Word16)0xf848,  /* 167 */
  (Word16)0xf837,  /* 168 */
  (Word16)0x0750,  /* 169 */
  (Word16)0xf802,  /* 170 */
  (Word16)0xf90d,  /* 171 */
  (Word16)0xfde7,  /* 172 */
  (Word16)0xfe07,  /* 173 */
  (Word16)0x0031,  /* 174 */
  (Word16)0x0691,  /* 175 */
  (Word16)0x0715,  /* 176 */
  (Word16)0xfe8c,  /* 177 */
  (Word16)0x00c0,  /* 178 */
  (Word16)0xfba0,  /* 179 */
  (Word16)0x02f7,  /* 180 */
  (Word16)0xfa5f,  /* 181 */
  (Word16)0xfd3b,  /* 182 */
  (Word16)0xfa7f,  /* 183 */
  (Word16)0xfdda,  /* 184 */
  (Word16)0x03ed,  /* 185 */
  (Word16)0x031e,  /* 186 */
  (Word16)0xf82e,  /* 187 */
  (Word16)0xfe9d,  /* 188 */
  (Word16)0x07ff,  /* 189 */
  (Word16)0xface,  /* 190 */
  (Word16)0xff0a,  /* 191 */
  (Word16)0xfb49,  /* 192 */
  (Word16)0xfca8,  /* 193 */
  (Word16)0x07fe,  /* 194 */
  (Word16)0xfb78,  /* 195 */
  (Word16)0x0788,  /* 196 */
  (Word16)0xf9f1,  /* 197 */
  (Word16)0x01a5,  /* 198 */
  (Word16)0x0800,  /* 199 */
  (Word16)0x0254,  /* 200 */
  (Word16)0xfaf9,  /* 201 */
  (Word16)0x037a,  /* 202 */
  (Word16)0xf823,  /* 203 */
  (Word16)0x0190,  /* 204 */
  (Word16)0xf85d,  /* 205 */
  (Word16)0x0778,  /* 206 */
  (Word16)0xf92e,  /* 207 */
  (Word16)0xf916,  /* 208 */
  (Word16)0x031c,  /* 209 */
  (Word16)0x075d,  /* 210 */
  (Word16)0x0722,  /* 211 */
  (Word16)0xfd0e,  /* 212 */
  (Word16)0x0783,  /* 213 */
  (Word16)0x07f1,  /* 214 */
  (Word16)0xf87a,  /* 215 */
  (Word16)0x07fb,  /* 216 */
  (Word16)0xfd21,  /* 217 */
  (Word16)0x006b,  /* 218 */
  (Word16)0x02f0,  /* 219 */
  (Word16)0x0755,  /* 220 */
  (Word16)0x0585,  /* 221 */
  (Word16)0xfce8,  /* 222 */
  (Word16)0xfda9,  /* 223 */
  (Word16)0xfb2f,  /* 224 */
  (Word16)0xf835,  /* 225 */
  (Word16)0x0714,  /* 226 */
  (Word16)0x006a,  /* 227 */
  (Word16)0xfbb8,  /* 228 */
  (Word16)0xfc0c,  /* 229 */
  (Word16)0xf816,  /* 230 */
  (Word16)0xf827,  /* 231 */
  (Word16)0xfdd0,  /* 232 */
  (Word16)0x0081,  /* 233 */
  (Word16)0xfe5d,  /* 234 */
  (Word16)0x054c,  /* 235 */
  (Word16)0xf938,  /* 236 */
  (Word16)0xf8e0,  /* 237 */
  (Word16)0x07ac,  /* 238 */
  (Word16)0x05e1,  /* 239 */
  (Word16)0xfd76,  /* 240 */
  (Word16)0xfd45,  /* 241 */
  (Word16)0x03d3,  /* 242 */
  (Word16)0x07dd,  /* 243 */
  (Word16)0xfd86,  /* 244 */
  (Word16)0x0800,  /* 245 */
  (Word16)0xf88c,  /* 246 */
  (Word16)0x07fe,  /* 247 */
  (Word16)0xfdeb,  /* 248 */
  (Word16)0xfd25,  /* 249 */
  (Word16)0xf802,  /* 250 */
  (Word16)0x06ed,  /* 251 */
  (Word16)0x02ac,  /* 252 */
  (Word16)0x07ec,  /* 253 */
  (Word16)0xfaaa,  /* 254 */
  (Word16)0x051f,  /* 255 */
  (Word16)0x07f7,  /* 256 */
  (Word16)0xfaed,  /* 257 */
  (Word16)0xff62,  /* 258 */
  (Word16)0x07e3,  /* 259 */
  (Word16)0x0668,  /* 260 */
  (Word16)0x0645,  /* 261 */
  (Word16)0x00b2,  /* 262 */
  (Word16)0xf90e,  /* 263 */
  (Word16)0xfcd8,  /* 264 */
  (Word16)0x07d4,  /* 265 */
  (Word16)0xf866,  /* 266 */
  (Word16)0x015c,  /* 267 */
  (Word16)0xf9d9,  /* 268 */
  (Word16)0x07fb,  /* 269 */
  (Word16)0x07a3,  /* 270 */
  (Word16)0x07f7,  /* 271 */
  (Word16)0x023f,  /* 272 */
  (Word16)0x06d2,  /* 273 */
  (Word16)0xfbf4,  /* 274 */
  (Word16)0xf839,  /* 275 */
  (Word16)0x07a2,  /* 276 */
  (Word16)0xf83f,  /* 277 */
  (Word16)0x0278,  /* 278 */
  (Word16)0xfe0a,  /* 279 */
  (Word16)0xfd4c,  /* 280 */
  (Word16)0xff89,  /* 281 */
  (Word16)0xfe2b,  /* 282 */
  (Word16)0xfe85,  /* 283 */
  (Word16)0xff29,  /* 284 */
  (Word16)0xfa40,  /* 285 */
  (Word16)0x07fc,  /* 286 */
  (Word16)0x049b,  /* 287 */
  (Word16)0x0250,  /* 288 */
  (Word16)0x0360,  /* 289 */
  (Word16)0x0778,  /* 290 */
  (Word16)0xf83c,  /* 291 */
  (Word16)0x02f0,  /* 292 */
  (Word16)0xf983,  /* 293 */
  (Word16)0xfde7,  /* 294 */
  (Word16)0x06b8,  /* 295 */
  (Word16)0xf802,  /* 296 */
  (Word16)0x05f9,  /* 297 */
  (Word16)0xfa05,  /* 298 */
  (Word16)0x07aa,  /* 299 */
  (Word16)0x07a3,  /* 300 */
  (Word16)0x03e6,  /* 301 */
  (Word16)0x03b5,  /* 302 */
  (Word16)0xf9e1,  /* 303 */
  (Word16)0x0497,  /* 304 */
  (Word16)0x0608,  /* 305 */
  (Word16)0xfb44,  /* 306 */
  (Word16)0x0602,  /* 307 */
  (Word16)0xf81d,  /* 308 */
  (Word16)0xfcbd,  /* 309 */
  (Word16)0x055b,  /* 310 */
  (Word16)0xf834,  /* 311 */
  (Word16)0x0736,  /* 312 */
  (Word16)0xf905,  /* 313 */
  (Word16)0xf8ad,  /* 314 */
  (Word16)0xffbc,  /* 315 */
  (Word16)0x0094,  /* 316 */
  (Word16)0x07f6,  /* 317 */
  (Word16)0xfa02,  /* 318 */
  (Word16)0x005e,  /* 319 */
  (Word16)0xf8e0,  /* 320 */
  (Word16)0xf94c,  /* 321 */
  (Word16)0x02ad,  /* 322 */
  (Word16)0xf806,  /* 323 */
  (Word16)0xfe2c,  /* 324 */
  (Word16)0x0561,  /* 325 */
  (Word16)0xff97,  /* 326 */
  (Word16)0x07ff,  /* 327 */
  (Word16)0x055b,  /* 328 */
  (Word16)0xf808,  /* 329 */
  (Word16)0x0692,  /* 330 */
  (Word16)0x07ef,  /* 331 */
  (Word16)0xfac7,  /* 332 */
  (Word16)0x0783,  /* 333 */
  (Word16)0x07bd,  /* 334 */
  (Word16)0xfe39,  /* 335 */
  (Word16)0xfc78,  /* 336 */
  (Word16)0xf925,  /* 337 */
  (Word16)0x0758,  /* 338 */
  (Word16)0x05ce,  /* 339 */
  (Word16)0xf806,  /* 340 */
  (Word16)0x0636,  /* 341 */
  (Word16)0x009e,  /* 342 */
  (Word16)0xfb84,  /* 343 */
  (Word16)0x07df,  /* 344 */
  (Word16)0x03ce,  /* 345 */
  (Word16)0x0541,  /* 346 */
  (Word16)0x0043,  /* 347 */
  (Word16)0xfce8,  /* 348 */
  (Word16)0xf836,  /* 349 */
  (Word16)0xfbbd,  /* 350 */
  (Word16)0x07fc,  /* 351 */
  (Word16)0xfbfb,  /* 352 */
  (Word16)0x0029,  /* 353 */
  (Word16)0x07ff,  /* 354 */
  (Word16)0x06a2,  /* 355 */
  (Word16)0xfb4f,  /* 356 */
  (Word16)0xfe98,  /* 357 */
  (Word16)0x06ad,  /* 358 */
  (Word16)0x007a,  /* 359 */
  (Word16)0x0685,  /* 360 */
  (Word16)0xfc67,  /* 361 */
  (Word16)0xf8d2,  /* 362 */
  (Word16)0x032d,  /* 363 */
  (Word16)0xff65,  /* 364 */
  (Word16)0x061c,  /* 365 */
  (Word16)0xfa0a,  /* 366 */
  (Word16)0x0531,  /* 367 */
  (Word16)0x04fc,  /* 368 */
  (Word16)0x0361,  /* 369 */
  (Word16)0x0037,  /* 370 */
  (Word16)0x0666,  /* 371 */
  (Word16)0xf9a7,  /* 372 */
  (Word16)0x051c,  /* 373 */
  (Word16)0x043b,  /* 374 */
  (Word16)0x05f0,  /* 375 */
  (Word16)0x07ed,  /* 376 */
  (Word16)0xf991,  /* 377 */
  (Word16)0xfad5,  /* 378 */
  (Word16)0x00ef,  /* 379 */
  (Word16)0xf865,  /* 380 */
  (Word16)0xfb06,  /* 381 */
  (Word16)0x003e,  /* 382 */
  (Word16)0xf829,  /* 383 */
  (Word16)0xf800,  /* 384 */
  (Word16)0x0721,  /* 385 */
  (Word16)0x00d5,  /* 386 */
  (Word16)0x07ad,  /* 387 */
  (Word16)0x0411,  /* 388 */
  (Word16)0x015c,  /* 389 */
  (Word16)0x0212,  /* 390 */
  (Word16)0xffe9,  /* 391 */
  (Word16)0xf9a2,  /* 392 */
  (Word16)0xf80f,  /* 393 */
  (Word16)0xf803,  /* 394 */
  (Word16)0xfa56,  /* 395 */
  (Word16)0xfa5d,  /* 396 */
  (Word16)0x07fd,  /* 397 */
  (Word16)0xfaee,  /* 398 */
  (Word16)0xfeb3,  /* 399 */
  (Word16)0xfc82,  /* 400 */
  (Word16)0xf803,  /* 401 */
  (Word16)0xfea8,  /* 402 */
  (Word16)0xf8f6,  /* 403 */
  (Word16)0x0389,  /* 404 */
  (Word16)0x0777,  /* 405 */
  (Word16)0xf87c,  /* 406 */
  (Word16)0xf8ea,  /* 407 */
  (Word16)0x07ff,  /* 408 */
  (Word16)0xf9f8,  /* 409 */
  (Word16)0x0783,  /* 410 */
  (Word16)0x06cf,  /* 411 */
  (Word16)0x032d,  /* 412 */
  (Word16)0xfd0a,  /* 413 */
  (Word16)0xfd1e,  /* 414 */
  (Word16)0xf887,  /* 415 */
  (Word16)0xfac7,  /* 416 */
  (Word16)0x00f5,  /* 417 */
  (Word16)0x078b,  /* 418 */
  (Word16)0x0602,  /* 419 */
  (Word16)0x048a,  /* 420 */
  (Word16)0x03c0,  /* 421 */
  (Word16)0x07c9,  /* 422 */
  (Word16)0xfcf0,  /* 423 */
  (Word16)0x0348,  /* 424 */
  (Word16)0x00c5,  /* 425 */
  (Word16)0xf92d,  /* 426 */
  (Word16)0x071c,  /* 427 */
  (Word16)0xfc25,  /* 428 */
  (Word16)0x0235,  /* 429 */
  (Word16)0xfabb,  /* 430 */
  (Word16)0x07e8,  /* 431 */
  (Word16)0xfe59,  /* 432 */
  (Word16)0xfb08,  /* 433 */
  (Word16)0x01a0,  /* 434 */
  (Word16)0xf82d,  /* 435 */
  (Word16)0x00e4,  /* 436 */
  (Word16)0xfcb1,  /* 437 */
  (Word16)0x01ee,  /* 438 */
  (Word16)0xfab0,  /* 439 */
  (Word16)0xfbb4,  /* 440 */
  (Word16)0xf839,  /* 441 */
  (Word16)0x06fe,  /* 442 */
  (Word16)0x0186,  /* 443 */
  (Word16)0xfc4b,  /* 444 */
  (Word16)0xff6f,  /* 445 */
  (Word16)0xf89b,  /* 446 */
  (Word16)0xf94b,  /* 447 */
  (Word16)0x0604,  /* 448 */
  (Word16)0xfca2,  /* 449 */
  (Word16)0xfa3b,  /* 450 */
  (Word16)0x064f,  /* 451 */
  (Word16)0x07cb,  /* 452 */
  (Word16)0x07f0,  /* 453 */
  (Word16)0x0625,  /* 454 */
  (Word16)0xf971,  /* 455 */
  (Word16)0x068e,  /* 456 */
  (Word16)0xfddd,  /* 457 */
  (Word16)0xfc89,  /* 458 */
  (Word16)0x07f0,  /* 459 */
  (Word16)0xf98b,  /* 460 */
  (Word16)0x0372,  /* 461 */
  (Word16)0x056b,  /* 462 */
  (Word16)0x047e,  /* 463 */
  (Word16)0x00de,  /* 464 */
  (Word16)0x074c,  /* 465 */
  (Word16)0xfc15,  /* 466 */
  (Word16)0xf8e1,  /* 467 */
  (Word16)0x0539,  /* 468 */
  (Word16)0x0565,  /* 469 */
  (Word16)0xfc2e,  /* 470 */
  (Word16)0xf806,  /* 471 */
  (Word16)0xf8bb,  /* 472 */
  (Word16)0xff78,  /* 473 */
  (Word16)0x07f4,  /* 474 */
  (Word16)0x07d1,  /* 475 */
  (Word16)0x0796,  /* 476 */
  (Word16)0xf85e,  /* 477 */
  (Word16)0xfc12,  /* 478 */
  (Word16)0x07fe,  /* 479 */
  (Word16)0x0409,  /* 480 */
  (Word16)0x03c6,  /* 481 */
  (Word16)0xfb09,  /* 482 */
  (Word16)0xfc7e,  /* 483 */
  (Word16)0x07e4,  /* 484 */
  (Word16)0xfb14,  /* 485 */
  (Word16)0xffb1,  /* 486 */
  (Word16)0xfd98,  /* 487 */
  (Word16)0x035a,  /* 488 */
  (Word16)0xf91c,  /* 489 */
  (Word16)0x0561,  /* 490 */
  (Word16)0xfa57,  /* 491 */
  (Word16)0x0786,  /* 492 */
  (Word16)0xf969,  /* 493 */
  (Word16)0xfd6f,  /* 494 */
  (Word16)0x049c,  /* 495 */
  (Word16)0xfd18,  /* 496 */
  (Word16)0x0800,  /* 497 */
  (Word16)0xf89c,  /* 498 */
  (Word16)0xfc6e,  /* 499 */
  (Word16)0x038a,  /* 500 */
  (Word16)0x004b,  /* 501 */
  (Word16)0x042d,  /* 502 */
  (Word16)0xf86d,  /* 503 */
  (Word16)0xf819,  /* 504 */
  (Word16)0x06ff,  /* 505 */
  (Word16)0xf887,  /* 506 */
  (Word16)0x07af,  /* 507 */
  (Word16)0x07ce,  /* 508 */
  (Word16)0x07f9,  /* 509 */
  (Word16)0xf86c,  /* 510 */
  (Word16)0x0754,  /* 511 */
  /* MAX_FREQ_COEFFS values from the beginning of the table are repeated here */
  (Word16)0xf801,  /*   0 */
  (Word16)0x07c5,  /*   1 */
  (Word16)0x0121,  /*   2 */
  (Word16)0xfc3d,  /*   3 */
  (Word16)0x0675,  /*   4 */
  (Word16)0xfce2,  /*   5 */
  (Word16)0xffea,  /*   6 */
  (Word16)0xf8b3,  /*   7 */
  (Word16)0x0463,  /*   8 */
  (Word16)0x0333,  /*   9 */
  (Word16)0xf803,  /*  10 */
  (Word16)0xf85c,  /*  11 */
  (Word16)0xfc58,  /*  12 */
  (Word16)0xfa2a,  /*  13 */
  (Word16)0x060d,  /*  14 */
  (Word16)0x0091,  /*  15 */
  (Word16)0x05f6,  /*  16 */
  (Word16)0xf849,  /*  17 */
  (Word16)0x026f,  /*  18 */
  (Word16)0x0553,  /*  19 */
  (Word16)0x0756,  /*  20 */
  (Word16)0xfa57,  /*  21 */
  (Word16)0xfa65,  /*  22 */
  (Word16)0xf80a,  /*  23 */
  (Word16)0x07da,  /*  24 */
  (Word16)0xfba0,  /*  25 */
  (Word16)0xffdd,  /*  26 */
  (Word16)0xf91c,  /*  27 */
  (Word16)0xf817,  /*  28 */
  (Word16)0x0424,  /*  29 */
  (Word16)0xf807,  /*  30 */
  (Word16)0xf801,  /*  31 */
  (Word16)0x046c,  /*  32 */
  (Word16)0x02c4,  /*  33 */
  (Word16)0x0503,  /*  34 */
  (Word16)0xf9d4,  /*  35 */
  (Word16)0xf8ac,  /*  36 */
  (Word16)0xf9e6,  /*  37 */
  (Word16)0x0662,  /*  38 */
  (Word16)0x045c,  /*  39 */
  (Word16)0xf926,  /*  40 */
  (Word16)0xf892,  /*  41 */
  (Word16)0xff10,  /*  42 */
  (Word16)0x01b5,  /*  43 */
  (Word16)0xf9e8,  /*  44 */
  (Word16)0x07d9,  /*  45 */
  (Word16)0xf920,  /*  46 */
  (Word16)0xf889   /*  47 */
};

#else

/*! This is a predefined random noise which will be modulated to the desired level.
  The most significant 16 bits of each array entry contain the real part, the lower
  16 bits contain the imaginary part. The accuracy is limited to 12 bits (which is
  sufficient) due to an implicit scale of 1/16.
*/
const Word32 sbr_randomPhase[SBR_NF_NO_RANDOM_VAL + MAX_FREQ_COEFFS] = {
  ((Word32)0xf801 << 16) | ((Word32)0xfb3e & 0xFFFF),   /*   0 */
  ((Word32)0x07c5 << 16) | ((Word32)0xfa99 & 0xFFFF),   /*   1 */
  ((Word32)0x0121 << 16) | ((Word32)0xf865 & 0xFFFF),   /*   2 */
  ((Word32)0xfc3d << 16) | ((Word32)0xfd03 & 0xFFFF),   /*   3 */
  ((Word32)0x0675 << 16) | ((Word32)0x025f & 0xFFFF),   /*   4 */
  ((Word32)0xfce2 << 16) | ((Word32)0x072a & 0xFFFF),   /*   5 */
  ((Word32)0xffea << 16) | ((Word32)0xfaa5 & 0xFFFF),   /*   6 */
  ((Word32)0xf8b3 << 16) | ((Word32)0xff14 & 0xFFFF),   /*   7 */
  ((Word32)0x0463 << 16) | ((Word32)0x0605 & 0xFFFF),   /*   8 */
  ((Word32)0x0333 << 16) | ((Word32)0xf816 & 0xFFFF),   /*   9 */
  ((Word32)0xf803 << 16) | ((Word32)0xf8f3 & 0xFFFF),   /*  10 */
  ((Word32)0xf85c << 16) | ((Word32)0x0746 & 0xFFFF),   /*  11 */
  ((Word32)0xfc58 << 16) | ((Word32)0xfb76 & 0xFFFF),   /*  12 */
  ((Word32)0xfa2a << 16) | ((Word32)0xf829 & 0xFFFF),   /*  13 */
  ((Word32)0x060d << 16) | ((Word32)0x01ad & 0xFFFF),   /*  14 */
  ((Word32)0x0091 << 16) | ((Word32)0xf9bd & 0xFFFF),   /*  15 */
  ((Word32)0x05f6 << 16) | ((Word32)0xf8b5 & 0xFFFF),   /*  16 */
  ((Word32)0xf849 << 16) | ((Word32)0xf86c & 0xFFFF),   /*  17 */
  ((Word32)0x026f << 16) | ((Word32)0xfc0c & 0xFFFF),   /*  18 */
  ((Word32)0x0553 << 16) | ((Word32)0x052c & 0xFFFF),   /*  19 */
  ((Word32)0x0756 << 16) | ((Word32)0x0167 & 0xFFFF),   /*  20 */
  ((Word32)0xfa57 << 16) | ((Word32)0x0434 & 0xFFFF),   /*  21 */
  ((Word32)0xfa65 << 16) | ((Word32)0xfc5f & 0xFFFF),   /*  22 */
  ((Word32)0xf80a << 16) | ((Word32)0xf8cb & 0xFFFF),   /*  23 */
  ((Word32)0x07da << 16) | ((Word32)0xf9ce & 0xFFFF),   /*  24 */
  ((Word32)0xfba0 << 16) | ((Word32)0xffcb & 0xFFFF),   /*  25 */
  ((Word32)0xffdd << 16) | ((Word32)0x0006 & 0xFFFF),   /*  26 */
  ((Word32)0xf91c << 16) | ((Word32)0x0367 & 0xFFFF),   /*  27 */
  ((Word32)0xf817 << 16) | ((Word32)0xf8f8 & 0xFFFF),   /*  28 */
  ((Word32)0x0424 << 16) | ((Word32)0x055b & 0xFFFF),   /*  29 */
  ((Word32)0xf807 << 16) | ((Word32)0xfb5a & 0xFFFF),   /*  30 */
  ((Word32)0xf801 << 16) | ((Word32)0x07df & 0xFFFF),   /*  31 */
  ((Word32)0x046c << 16) | ((Word32)0x04c2 & 0xFFFF),   /*  32 */
  ((Word32)0x02c4 << 16) | ((Word32)0x0797 & 0xFFFF),   /*  33 */
  ((Word32)0x0503 << 16) | ((Word32)0xfa0c & 0xFFFF),   /*  34 */
  ((Word32)0xf9d4 << 16) | ((Word32)0xfd4a & 0xFFFF),   /*  35 */
  ((Word32)0xf8ac << 16) | ((Word32)0x004c & 0xFFFF),   /*  36 */
  ((Word32)0xf9e6 << 16) | ((Word32)0xf8b1 & 0xFFFF),   /*  37 */
  ((Word32)0x0662 << 16) | ((Word32)0xf88c & 0xFFFF),   /*  38 */
  ((Word32)0x045c << 16) | ((Word32)0xff0c & 0xFFFF),   /*  39 */
  ((Word32)0xf926 << 16) | ((Word32)0x0365 & 0xFFFF),   /*  40 */
  ((Word32)0xf892 << 16) | ((Word32)0x023b & 0xFFFF),   /*  41 */
  ((Word32)0xff10 << 16) | ((Word32)0xf804 & 0xFFFF),   /*  42 */
  ((Word32)0x01b5 << 16) | ((Word32)0xf8be & 0xFFFF),   /*  43 */
  ((Word32)0xf9e8 << 16) | ((Word32)0x07fb & 0xFFFF),   /*  44 */
  ((Word32)0x07d9 << 16) | ((Word32)0xf855 & 0xFFFF),   /*  45 */
  ((Word32)0xf920 << 16) | ((Word32)0x07a9 & 0xFFFF),   /*  46 */
  ((Word32)0xf889 << 16) | ((Word32)0x03f4 & 0xFFFF),   /*  47 */
  ((Word32)0x0270 << 16) | ((Word32)0xfa5b & 0xFFFF),   /*  48 */
  ((Word32)0x06d3 << 16) | ((Word32)0x03be & 0xFFFF),   /*  49 */
  ((Word32)0x074e << 16) | ((Word32)0xf803 & 0xFFFF),   /*  50 */
  ((Word32)0xff87 << 16) | ((Word32)0x05a9 & 0xFFFF),   /*  51 */
  ((Word32)0x0246 << 16) | ((Word32)0x02c5 & 0xFFFF),   /*  52 */
  ((Word32)0x079f << 16) | ((Word32)0xfb9c & 0xFFFF),   /*  53 */
  ((Word32)0xf9b7 << 16) | ((Word32)0xf9f4 & 0xFFFF),   /*  54 */
  ((Word32)0xf856 << 16) | ((Word32)0xfe5e & 0xFFFF),   /*  55 */
  ((Word32)0x0698 << 16) | ((Word32)0x07bb & 0xFFFF),   /*  56 */
  ((Word32)0xfac9 << 16) | ((Word32)0xf8e7 & 0xFFFF),   /*  57 */
  ((Word32)0xf882 << 16) | ((Word32)0x07fd & 0xFFFF),   /*  58 */
  ((Word32)0x0750 << 16) | ((Word32)0xf823 & 0xFFFF),   /*  59 */
  ((Word32)0xfa5e << 16) | ((Word32)0x04b4 & 0xFFFF),   /*  60 */
  ((Word32)0x000c << 16) | ((Word32)0x04f1 & 0xFFFF),   /*  61 */
  ((Word32)0x0720 << 16) | ((Word32)0x0439 & 0xFFFF),   /*  62 */
  ((Word32)0xfa81 << 16) | ((Word32)0x0677 & 0xFFFF),   /*  63 */
  ((Word32)0x05c6 << 16) | ((Word32)0xfa76 & 0xFFFF),   /*  64 */
  ((Word32)0xfaf7 << 16) | ((Word32)0x0117 & 0xFFFF),   /*  65 */
  ((Word32)0x0265 << 16) | ((Word32)0xfc51 & 0xFFFF),   /*  66 */
  ((Word32)0xf8a8 << 16) | ((Word32)0xfa14 & 0xFFFF),   /*  67 */
  ((Word32)0x07f2 << 16) | ((Word32)0x0344 & 0xFFFF),   /*  68 */
  ((Word32)0x0697 << 16) | ((Word32)0xfa14 & 0xFFFF),   /*  69 */
  ((Word32)0xf81e << 16) | ((Word32)0xf801 & 0xFFFF),   /*  70 */
  ((Word32)0xf854 << 16) | ((Word32)0xf810 & 0xFFFF),   /*  71 */
  ((Word32)0xfe4a << 16) | ((Word32)0xf887 & 0xFFFF),   /*  72 */
  ((Word32)0xfa7f << 16) | ((Word32)0xfdd9 & 0xFFFF),   /*  73 */
  ((Word32)0x0759 << 16) | ((Word32)0x00c0 & 0xFFFF),   /*  74 */
  ((Word32)0xf851 << 16) | ((Word32)0x02e3 & 0xFFFF),   /*  75 */
  ((Word32)0x0422 << 16) | ((Word32)0xfa4a & 0xFFFF),   /*  76 */
  ((Word32)0x04e4 << 16) | ((Word32)0x03c2 & 0xFFFF),   /*  77 */
  ((Word32)0x03c9 << 16) | ((Word32)0xfdd0 & 0xFFFF),   /*  78 */
  ((Word32)0x0748 << 16) | ((Word32)0x07bd & 0xFFFF),   /*  79 */
  ((Word32)0x0396 << 16) | ((Word32)0x07f0 & 0xFFFF),   /*  80 */
  ((Word32)0x0554 << 16) | ((Word32)0x07ba & 0xFFFF),   /*  81 */
  ((Word32)0x05fe << 16) | ((Word32)0xf8cf & 0xFFFF),   /*  82 */
  ((Word32)0xf809 << 16) | ((Word32)0x0439 & 0xFFFF),   /*  83 */
  ((Word32)0x07cb << 16) | ((Word32)0xfea7 & 0xFFFF),   /*  84 */
  ((Word32)0x05d1 << 16) | ((Word32)0xfc28 & 0xFFFF),   /*  85 */
  ((Word32)0x07a2 << 16) | ((Word32)0x0582 & 0xFFFF),   /*  86 */
  ((Word32)0xfa2a << 16) | ((Word32)0xf9df & 0xFFFF),   /*  87 */
  ((Word32)0xf92c << 16) | ((Word32)0x0719 & 0xFFFF),   /*  88 */
  ((Word32)0xf97d << 16) | ((Word32)0xf834 & 0xFFFF),   /*  89 */
  ((Word32)0xf8f7 << 16) | ((Word32)0x05fb & 0xFFFF),   /*  90 */
  ((Word32)0xfa46 << 16) | ((Word32)0xf81d & 0xFFFF),   /*  91 */
  ((Word32)0x06af << 16) | ((Word32)0x06b2 & 0xFFFF),   /*  92 */
  ((Word32)0xfc27 << 16) | ((Word32)0xf818 & 0xFFFF),   /*  93 */
  ((Word32)0x07c5 << 16) | ((Word32)0x0668 & 0xFFFF),   /*  94 */
  ((Word32)0x0429 << 16) | ((Word32)0x066b & 0xFFFF),   /*  95 */
  ((Word32)0xffef << 16) | ((Word32)0xf9de & 0xFFFF),   /*  96 */
  ((Word32)0xfa60 << 16) | ((Word32)0x046e & 0xFFFF),   /*  97 */
  ((Word32)0xf854 << 16) | ((Word32)0xfc8a & 0xFFFF),   /*  98 */
  ((Word32)0x07c4 << 16) | ((Word32)0x00bf & 0xFFFF),   /*  99 */
  ((Word32)0xf89c << 16) | ((Word32)0x06d7 & 0xFFFF),   /* 100 */
  ((Word32)0xfa71 << 16) | ((Word32)0x07e4 & 0xFFFF),   /* 101 */
  ((Word32)0x0220 << 16) | ((Word32)0x05dd & 0xFFFF),   /* 102 */
  ((Word32)0x023e << 16) | ((Word32)0x012a & 0xFFFF),   /* 103 */
  ((Word32)0xfa12 << 16) | ((Word32)0x07f2 & 0xFFFF),   /* 104 */
  ((Word32)0xffdc << 16) | ((Word32)0xf964 & 0xFFFF),   /* 105 */
  ((Word32)0xfb97 << 16) | ((Word32)0xf817 & 0xFFFF),   /* 106 */
  ((Word32)0x07d6 << 16) | ((Word32)0xf87a & 0xFFFF),   /* 107 */
  ((Word32)0xf810 << 16) | ((Word32)0x055d & 0xFFFF),   /* 108 */
  ((Word32)0xfa96 << 16) | ((Word32)0x0103 & 0xFFFF),   /* 109 */
  ((Word32)0x00bb << 16) | ((Word32)0xfe5b & 0xFFFF),   /* 110 */
  ((Word32)0xfa44 << 16) | ((Word32)0xf82d & 0xFFFF),   /* 111 */
  ((Word32)0x067b << 16) | ((Word32)0x044c & 0xFFFF),   /* 112 */
  ((Word32)0x0340 << 16) | ((Word32)0xfde2 & 0xFFFF),   /* 113 */
  ((Word32)0xfa96 << 16) | ((Word32)0x078f & 0xFFFF),   /* 114 */
  ((Word32)0x06f3 << 16) | ((Word32)0xfe89 & 0xFFFF),   /* 115 */
  ((Word32)0xf80a << 16) | ((Word32)0xffca & 0xFFFF),   /* 116 */
  ((Word32)0x06bf << 16) | ((Word32)0x00d5 & 0xFFFF),   /* 117 */
  ((Word32)0xff43 << 16) | ((Word32)0x0590 & 0xFFFF),   /* 118 */
  ((Word32)0x07ff << 16) | ((Word32)0xff03 & 0xFFFF),   /* 119 */
  ((Word32)0xf99f << 16) | ((Word32)0xf8ac & 0xFFFF),   /* 120 */
  ((Word32)0x07b5 << 16) | ((Word32)0x07bb & 0xFFFF),   /* 121 */
  ((Word32)0xf99b << 16) | ((Word32)0x0525 & 0xFFFF),   /* 122 */
  ((Word32)0xff13 << 16) | ((Word32)0x0249 & 0xFFFF),   /* 123 */
  ((Word32)0xfcce << 16) | ((Word32)0x0788 & 0xFFFF),   /* 124 */
  ((Word32)0x07ed << 16) | ((Word32)0xf8a3 & 0xFFFF),   /* 125 */
  ((Word32)0x024a << 16) | ((Word32)0xf8b8 & 0xFFFF),   /* 126 */
  ((Word32)0xf956 << 16) | ((Word32)0xfa9d & 0xFFFF),   /* 127 */
  ((Word32)0x07a2 << 16) | ((Word32)0x03ef & 0xFFFF),   /* 128 */
  ((Word32)0xff7c << 16) | ((Word32)0x0043 & 0xFFFF),   /* 129 */
  ((Word32)0xf809 << 16) | ((Word32)0x0364 & 0xFFFF),   /* 130 */
  ((Word32)0xfac3 << 16) | ((Word32)0x069b & 0xFFFF),   /* 131 */
  ((Word32)0xf980 << 16) | ((Word32)0xfbdf & 0xFFFF),   /* 132 */
  ((Word32)0xf807 << 16) | ((Word32)0x06c2 & 0xFFFF),   /* 133 */
  ((Word32)0x0006 << 16) | ((Word32)0x052e & 0xFFFF),   /* 134 */
  ((Word32)0x059d << 16) | ((Word32)0xfe5d & 0xFFFF),   /* 135 */
  ((Word32)0x07b5 << 16) | ((Word32)0x0342 & 0xFFFF),   /* 136 */
  ((Word32)0xfa7d << 16) | ((Word32)0x074f & 0xFFFF),   /* 137 */
  ((Word32)0xfd36 << 16) | ((Word32)0x05b8 & 0xFFFF),   /* 138 */
  ((Word32)0x075c << 16) | ((Word32)0x0552 & 0xFFFF),   /* 139 */
  ((Word32)0xf814 << 16) | ((Word32)0x06df & 0xFFFF),   /* 140 */
  ((Word32)0x0582 << 16) | ((Word32)0x0474 & 0xFFFF),   /* 141 */
  ((Word32)0xf80b << 16) | ((Word32)0xfe65 & 0xFFFF),   /* 142 */
  ((Word32)0x078a << 16) | ((Word32)0xf806 & 0xFFFF),   /* 143 */
  ((Word32)0xfa9b << 16) | ((Word32)0x03f7 & 0xFFFF),   /* 144 */
  ((Word32)0xfc36 << 16) | ((Word32)0xf921 & 0xFFFF),   /* 145 */
  ((Word32)0x0125 << 16) | ((Word32)0xf878 & 0xFFFF),   /* 146 */
  ((Word32)0xfda9 << 16) | ((Word32)0x0076 & 0xFFFF),   /* 147 */
  ((Word32)0x0381 << 16) | ((Word32)0xf9b0 & 0xFFFF),   /* 148 */
  ((Word32)0xfd18 << 16) | ((Word32)0x0531 & 0xFFFF),   /* 149 */
  ((Word32)0xff4d << 16) | ((Word32)0x07d1 & 0xFFFF),   /* 150 */
  ((Word32)0xf848 << 16) | ((Word32)0xfbaf & 0xFFFF),   /* 151 */
  ((Word32)0x0471 << 16) | ((Word32)0x0650 & 0xFFFF),   /* 152 */
  ((Word32)0x05e2 << 16) | ((Word32)0x07b7 & 0xFFFF),   /* 153 */
  ((Word32)0xfd87 << 16) | ((Word32)0xf98c & 0xFFFF),   /* 154 */
  ((Word32)0x0049 << 16) | ((Word32)0xf837 & 0xFFFF),   /* 155 */
  ((Word32)0x07e6 << 16) | ((Word32)0x03df & 0xFFFF),   /* 156 */
  ((Word32)0xf977 << 16) | ((Word32)0xf8bc & 0xFFFF),   /* 157 */
  ((Word32)0x056e << 16) | ((Word32)0x0681 & 0xFFFF),   /* 158 */
  ((Word32)0xfebc << 16) | ((Word32)0x06d3 & 0xFFFF),   /* 159 */
  ((Word32)0x0675 << 16) | ((Word32)0xfe06 & 0xFFFF),   /* 160 */
  ((Word32)0x03d3 << 16) | ((Word32)0xfc4b & 0xFFFF),   /* 161 */
  ((Word32)0x07b6 << 16) | ((Word32)0x0314 & 0xFFFF),   /* 162 */
  ((Word32)0xf812 << 16) | ((Word32)0xfe01 & 0xFFFF),   /* 163 */
  ((Word32)0x06a6 << 16) | ((Word32)0xf86b & 0xFFFF),   /* 164 */
  ((Word32)0xfb4d << 16) | ((Word32)0x001a & 0xFFFF),   /* 165 */
  ((Word32)0x07a5 << 16) | ((Word32)0xf928 & 0xFFFF),   /* 166 */
  ((Word32)0xf848 << 16) | ((Word32)0xfae1 & 0xFFFF),   /* 167 */
  ((Word32)0xf837 << 16) | ((Word32)0x00fe & 0xFFFF),   /* 168 */
  ((Word32)0x0750 << 16) | ((Word32)0x04a3 & 0xFFFF),   /* 169 */
  ((Word32)0xf802 << 16) | ((Word32)0x05b0 & 0xFFFF),   /* 170 */
  ((Word32)0xf90d << 16) | ((Word32)0xfe60 & 0xFFFF),   /* 171 */
  ((Word32)0xfde7 << 16) | ((Word32)0xfa8a & 0xFFFF),   /* 172 */
  ((Word32)0xfe07 << 16) | ((Word32)0xf8fd & 0xFFFF),   /* 173 */
  ((Word32)0x0031 << 16) | ((Word32)0x022d & 0xFFFF),   /* 174 */
  ((Word32)0x0691 << 16) | ((Word32)0xf931 & 0xFFFF),   /* 175 */
  ((Word32)0x0715 << 16) | ((Word32)0xf8d4 & 0xFFFF),   /* 176 */
  ((Word32)0xfe8c << 16) | ((Word32)0xfde8 & 0xFFFF),   /* 177 */
  ((Word32)0x00c0 << 16) | ((Word32)0x0463 & 0xFFFF),   /* 178 */
  ((Word32)0xfba0 << 16) | ((Word32)0x07ae & 0xFFFF),   /* 179 */
  ((Word32)0x02f7 << 16) | ((Word32)0xfb35 & 0xFFFF),   /* 180 */
  ((Word32)0xfa5f << 16) | ((Word32)0x074c & 0xFFFF),   /* 181 */
  ((Word32)0xfd3b << 16) | ((Word32)0xf80b & 0xFFFF),   /* 182 */
  ((Word32)0xfa7f << 16) | ((Word32)0xfd95 & 0xFFFF),   /* 183 */
  ((Word32)0xfdda << 16) | ((Word32)0x06a6 & 0xFFFF),   /* 184 */
  ((Word32)0x03ed << 16) | ((Word32)0xfc5f & 0xFFFF),   /* 185 */
  ((Word32)0x031e << 16) | ((Word32)0x07a4 & 0xFFFF),   /* 186 */
  ((Word32)0xf82e << 16) | ((Word32)0x006d & 0xFFFF),   /* 187 */
  ((Word32)0xfe9d << 16) | ((Word32)0xf894 & 0xFFFF),   /* 188 */
  ((Word32)0x07ff << 16) | ((Word32)0x04aa & 0xFFFF),   /* 189 */
  ((Word32)0xface << 16) | ((Word32)0x057e & 0xFFFF),   /* 190 */
  ((Word32)0xff0a << 16) | ((Word32)0xfb6e & 0xFFFF),   /* 191 */
  ((Word32)0xfb49 << 16) | ((Word32)0xfd36 & 0xFFFF),   /* 192 */
  ((Word32)0xfca8 << 16) | ((Word32)0x014d & 0xFFFF),   /* 193 */
  ((Word32)0x07fe << 16) | ((Word32)0x00e4 & 0xFFFF),   /* 194 */
  ((Word32)0xfb78 << 16) | ((Word32)0xf8c3 & 0xFFFF),   /* 195 */
  ((Word32)0x0788 << 16) | ((Word32)0x02d3 & 0xFFFF),   /* 196 */
  ((Word32)0xf9f1 << 16) | ((Word32)0x044b & 0xFFFF),   /* 197 */
  ((Word32)0x01a5 << 16) | ((Word32)0xf872 & 0xFFFF),   /* 198 */
  ((Word32)0x0800 << 16) | ((Word32)0x0663 & 0xFFFF),   /* 199 */
  ((Word32)0x0254 << 16) | ((Word32)0x02d5 & 0xFFFF),   /* 200 */
  ((Word32)0xfaf9 << 16) | ((Word32)0x031a & 0xFFFF),   /* 201 */
  ((Word32)0x037a << 16) | ((Word32)0xf81e & 0xFFFF),   /* 202 */
  ((Word32)0xf823 << 16) | ((Word32)0x01af & 0xFFFF),   /* 203 */
  ((Word32)0x0190 << 16) | ((Word32)0xf876 & 0xFFFF),   /* 204 */
  ((Word32)0xf85d << 16) | ((Word32)0x07df & 0xFFFF),   /* 205 */
  ((Word32)0x0778 << 16) | ((Word32)0xfa54 & 0xFFFF),   /* 206 */
  ((Word32)0xf92e << 16) | ((Word32)0xff55 & 0xFFFF),   /* 207 */
  ((Word32)0xf916 << 16) | ((Word32)0xfc56 & 0xFFFF),   /* 208 */
  ((Word32)0x031c << 16) | ((Word32)0x07c8 & 0xFFFF),   /* 209 */
  ((Word32)0x075d << 16) | ((Word32)0xfb01 & 0xFFFF),   /* 210 */
  ((Word32)0x0722 << 16) | ((Word32)0x0465 & 0xFFFF),   /* 211 */
  ((Word32)0xfd0e << 16) | ((Word32)0x07b7 & 0xFFFF),   /* 212 */
  ((Word32)0x0783 << 16) | ((Word32)0xf8cd & 0xFFFF),   /* 213 */
  ((Word32)0x07f1 << 16) | ((Word32)0xffb3 & 0xFFFF),   /* 214 */
  ((Word32)0xf87a << 16) | ((Word32)0x034e & 0xFFFF),   /* 215 */
  ((Word32)0x07fb << 16) | ((Word32)0xfea7 & 0xFFFF),   /* 216 */
  ((Word32)0xfd21 << 16) | ((Word32)0xfc45 & 0xFFFF),   /* 217 */
  ((Word32)0x006b << 16) | ((Word32)0xfdf3 & 0xFFFF),   /* 218 */
  ((Word32)0x02f0 << 16) | ((Word32)0xfce8 & 0xFFFF),   /* 219 */
  ((Word32)0x0755 << 16) | ((Word32)0xfd8e & 0xFFFF),   /* 220 */
  ((Word32)0x0585 << 16) | ((Word32)0x0747 & 0xFFFF),   /* 221 */
  ((Word32)0xfce8 << 16) | ((Word32)0x07f6 & 0xFFFF),   /* 222 */
  ((Word32)0xfda9 << 16) | ((Word32)0x02ff & 0xFFFF),   /* 223 */
  ((Word32)0xfb2f << 16) | ((Word32)0x06f1 & 0xFFFF),   /* 224 */
  ((Word32)0xf835 << 16) | ((Word32)0x07b8 & 0xFFFF),   /* 225 */
  ((Word32)0x0714 << 16) | ((Word32)0x049a & 0xFFFF),   /* 226 */
  ((Word32)0x006a << 16) | ((Word32)0x01b4 & 0xFFFF),   /* 227 */
  ((Word32)0xfbb8 << 16) | ((Word32)0x07c8 & 0xFFFF),   /* 228 */
  ((Word32)0xfc0c << 16) | ((Word32)0x07db & 0xFFFF),   /* 229 */
  ((Word32)0xf816 << 16) | ((Word32)0xfcc8 & 0xFFFF),   /* 230 */
  ((Word32)0xf827 << 16) | ((Word32)0xfa2c & 0xFFFF),   /* 231 */
  ((Word32)0xfdd0 << 16) | ((Word32)0x07ff & 0xFFFF),   /* 232 */
  ((Word32)0x0081 << 16) | ((Word32)0xfba3 & 0xFFFF),   /* 233 */
  ((Word32)0xfe5d << 16) | ((Word32)0xfedd & 0xFFFF),   /* 234 */
  ((Word32)0x054c << 16) | ((Word32)0x05cd & 0xFFFF),   /* 235 */
  ((Word32)0xf938 << 16) | ((Word32)0x0031 & 0xFFFF),   /* 236 */
  ((Word32)0xf8e0 << 16) | ((Word32)0x071c & 0xFFFF),   /* 237 */
  ((Word32)0x07ac << 16) | ((Word32)0x0624 & 0xFFFF),   /* 238 */
  ((Word32)0x05e1 << 16) | ((Word32)0xffb3 & 0xFFFF),   /* 239 */
  ((Word32)0xfd76 << 16) | ((Word32)0xfd0e & 0xFFFF),   /* 240 */
  ((Word32)0xfd45 << 16) | ((Word32)0x0338 & 0xFFFF),   /* 241 */
  ((Word32)0x03d3 << 16) | ((Word32)0xfcd9 & 0xFFFF),   /* 242 */
  ((Word32)0x07dd << 16) | ((Word32)0x0029 & 0xFFFF),   /* 243 */
  ((Word32)0xfd86 << 16) | ((Word32)0xfe8e & 0xFFFF),   /* 244 */
  ((Word32)0x0800 << 16) | ((Word32)0xfde6 & 0xFFFF),   /* 245 */
  ((Word32)0xf88c << 16) | ((Word32)0xf823 & 0xFFFF),   /* 246 */
  ((Word32)0x07fe << 16) | ((Word32)0xf997 & 0xFFFF),   /* 247 */
  ((Word32)0xfdeb << 16) | ((Word32)0xf9ec & 0xFFFF),   /* 248 */
  ((Word32)0xfd25 << 16) | ((Word32)0x018b & 0xFFFF),   /* 249 */
  ((Word32)0xf802 << 16) | ((Word32)0x05f9 & 0xFFFF),   /* 250 */
  ((Word32)0x06ed << 16) | ((Word32)0x0473 & 0xFFFF),   /* 251 */
  ((Word32)0x02ac << 16) | ((Word32)0x06e5 & 0xFFFF),   /* 252 */
  ((Word32)0x07ec << 16) | ((Word32)0x005e & 0xFFFF),   /* 253 */
  ((Word32)0xfaaa << 16) | ((Word32)0xf8ab & 0xFFFF),   /* 254 */
  ((Word32)0x051f << 16) | ((Word32)0x0141 & 0xFFFF),   /* 255 */
  ((Word32)0x07f7 << 16) | ((Word32)0x03ab & 0xFFFF),   /* 256 */
  ((Word32)0xfaed << 16) | ((Word32)0x01b0 & 0xFFFF),   /* 257 */
  ((Word32)0xff62 << 16) | ((Word32)0xf8d5 & 0xFFFF),   /* 258 */
  ((Word32)0x07e3 << 16) | ((Word32)0x070f & 0xFFFF),   /* 259 */
  ((Word32)0x0668 << 16) | ((Word32)0xfd0d & 0xFFFF),   /* 260 */
  ((Word32)0x0645 << 16) | ((Word32)0x03a4 & 0xFFFF),   /* 261 */
  ((Word32)0x00b2 << 16) | ((Word32)0x067a & 0xFFFF),   /* 262 */
  ((Word32)0xf90e << 16) | ((Word32)0x0326 & 0xFFFF),   /* 263 */
  ((Word32)0xfcd8 << 16) | ((Word32)0xfaa8 & 0xFFFF),   /* 264 */
  ((Word32)0x07d4 << 16) | ((Word32)0xfa34 & 0xFFFF),   /* 265 */
  ((Word32)0xf866 << 16) | ((Word32)0x072a & 0xFFFF),   /* 266 */
  ((Word32)0x015c << 16) | ((Word32)0x0460 & 0xFFFF),   /* 267 */
  ((Word32)0xf9d9 << 16) | ((Word32)0xf84d & 0xFFFF),   /* 268 */
  ((Word32)0x07fb << 16) | ((Word32)0x036a & 0xFFFF),   /* 269 */
  ((Word32)0x07a3 << 16) | ((Word32)0x07c3 & 0xFFFF),   /* 270 */
  ((Word32)0x07f7 << 16) | ((Word32)0xfbac & 0xFFFF),   /* 271 */
  ((Word32)0x023f << 16) | ((Word32)0xf92c & 0xFFFF),   /* 272 */
  ((Word32)0x06d2 << 16) | ((Word32)0xfad6 & 0xFFFF),   /* 273 */
  ((Word32)0xfbf4 << 16) | ((Word32)0xfabb & 0xFFFF),   /* 274 */
  ((Word32)0xf839 << 16) | ((Word32)0xfe27 & 0xFFFF),   /* 275 */
  ((Word32)0x07a2 << 16) | ((Word32)0xf810 & 0xFFFF),   /* 276 */
  ((Word32)0xf83f << 16) | ((Word32)0x05e7 & 0xFFFF),   /* 277 */
  ((Word32)0x0278 << 16) | ((Word32)0x0352 & 0xFFFF),   /* 278 */
  ((Word32)0xfe0a << 16) | ((Word32)0x050e & 0xFFFF),   /* 279 */
  ((Word32)0xfd4c << 16) | ((Word32)0xfce8 & 0xFFFF),   /* 280 */
  ((Word32)0xff89 << 16) | ((Word32)0xff72 & 0xFFFF),   /* 281 */
  ((Word32)0xfe2b << 16) | ((Word32)0x07c4 & 0xFFFF),   /* 282 */
  ((Word32)0xfe85 << 16) | ((Word32)0x03ce & 0xFFFF),   /* 283 */
  ((Word32)0xff29 << 16) | ((Word32)0xf8fa & 0xFFFF),   /* 284 */
  ((Word32)0xfa40 << 16) | ((Word32)0x063e & 0xFFFF),   /* 285 */
  ((Word32)0x07fc << 16) | ((Word32)0x0734 & 0xFFFF),   /* 286 */
  ((Word32)0x049b << 16) | ((Word32)0xf8b8 & 0xFFFF),   /* 287 */
  ((Word32)0x0250 << 16) | ((Word32)0x07b4 & 0xFFFF),   /* 288 */
  ((Word32)0x0360 << 16) | ((Word32)0x03da & 0xFFFF),   /* 289 */
  ((Word32)0x0778 << 16) | ((Word32)0xfc84 & 0xFFFF),   /* 290 */
  ((Word32)0xf83c << 16) | ((Word32)0x06ee & 0xFFFF),   /* 291 */
  ((Word32)0x02f0 << 16) | ((Word32)0x0539 & 0xFFFF),   /* 292 */
  ((Word32)0xf983 << 16) | ((Word32)0x00b4 & 0xFFFF),   /* 293 */
  ((Word32)0xfde7 << 16) | ((Word32)0xf894 & 0xFFFF),   /* 294 */
  ((Word32)0x06b8 << 16) | ((Word32)0x0478 & 0xFFFF),   /* 295 */
  ((Word32)0xf802 << 16) | ((Word32)0xf851 & 0xFFFF),   /* 296 */
  ((Word32)0x05f9 << 16) | ((Word32)0x00f9 & 0xFFFF),   /* 297 */
  ((Word32)0xfa05 << 16) | ((Word32)0xfdd9 & 0xFFFF),   /* 298 */
  ((Word32)0x07aa << 16) | ((Word32)0xf9ad & 0xFFFF),   /* 299 */
  ((Word32)0x07a3 << 16) | ((Word32)0xff50 & 0xFFFF),   /* 300 */
  ((Word32)0x03e6 << 16) | ((Word32)0x0800 & 0xFFFF),   /* 301 */
  ((Word32)0x03b5 << 16) | ((Word32)0x00e1 & 0xFFFF),   /* 302 */
  ((Word32)0xf9e1 << 16) | ((Word32)0x0723 & 0xFFFF),   /* 303 */
  ((Word32)0x0497 << 16) | ((Word32)0x02d3 & 0xFFFF),   /* 304 */
  ((Word32)0x0608 << 16) | ((Word32)0x07bd & 0xFFFF),   /* 305 */
  ((Word32)0xfb44 << 16) | ((Word32)0xf8d9 & 0xFFFF),   /* 306 */
  ((Word32)0x0602 << 16) | ((Word32)0xfda2 & 0xFFFF),   /* 307 */
  ((Word32)0xf81d << 16) | ((Word32)0x0201 & 0xFFFF),   /* 308 */
  ((Word32)0xfcbd << 16) | ((Word32)0xf8cc & 0xFFFF),   /* 309 */
  ((Word32)0x055b << 16) | ((Word32)0x07e4 & 0xFFFF),   /* 310 */
  ((Word32)0xf834 << 16) | ((Word32)0xfffc & 0xFFFF),   /* 311 */
  ((Word32)0x0736 << 16) | ((Word32)0x07fc & 0xFFFF),   /* 312 */
  ((Word32)0xf905 << 16) | ((Word32)0x07f0 & 0xFFFF),   /* 313 */
  ((Word32)0xf8ad << 16) | ((Word32)0xfebe & 0xFFFF),   /* 314 */
  ((Word32)0xffbc << 16) | ((Word32)0xfd06 & 0xFFFF),   /* 315 */
  ((Word32)0x0094 << 16) | ((Word32)0xf8e5 & 0xFFFF),   /* 316 */
  ((Word32)0x07f6 << 16) | ((Word32)0x07c4 & 0xFFFF),   /* 317 */
  ((Word32)0xfa02 << 16) | ((Word32)0x0800 & 0xFFFF),   /* 318 */
  ((Word32)0x005e << 16) | ((Word32)0x07fc & 0xFFFF),   /* 319 */
  ((Word32)0xf8e0 << 16) | ((Word32)0xfd75 & 0xFFFF),   /* 320 */
  ((Word32)0xf94c << 16) | ((Word32)0x07d0 & 0xFFFF),   /* 321 */
  ((Word32)0x02ad << 16) | ((Word32)0xf91a & 0xFFFF),   /* 322 */
  ((Word32)0xf806 << 16) | ((Word32)0x0776 & 0xFFFF),   /* 323 */
  ((Word32)0xfe2c << 16) | ((Word32)0x0183 & 0xFFFF),   /* 324 */
  ((Word32)0x0561 << 16) | ((Word32)0xffb5 & 0xFFFF),   /* 325 */
  ((Word32)0xff97 << 16) | ((Word32)0xf898 & 0xFFFF),   /* 326 */
  ((Word32)0x07ff << 16) | ((Word32)0x077d & 0xFFFF),   /* 327 */
  ((Word32)0x055b << 16) | ((Word32)0x07ea & 0xFFFF),   /* 328 */
  ((Word32)0xf808 << 16) | ((Word32)0xfc6d & 0xFFFF),   /* 329 */
  ((Word32)0x0692 << 16) | ((Word32)0x07f7 & 0xFFFF),   /* 330 */
  ((Word32)0x07ef << 16) | ((Word32)0x05c3 & 0xFFFF),   /* 331 */
  ((Word32)0xfac7 << 16) | ((Word32)0x042d & 0xFFFF),   /* 332 */
  ((Word32)0x0783 << 16) | ((Word32)0xfa02 & 0xFFFF),   /* 333 */
  ((Word32)0x07bd << 16) | ((Word32)0x0745 & 0xFFFF),   /* 334 */
  ((Word32)0xfe39 << 16) | ((Word32)0x0492 & 0xFFFF),   /* 335 */
  ((Word32)0xfc78 << 16) | ((Word32)0xf896 & 0xFFFF),   /* 336 */
  ((Word32)0xf925 << 16) | ((Word32)0x071c & 0xFFFF),   /* 337 */
  ((Word32)0x0758 << 16) | ((Word32)0xfc4b & 0xFFFF),   /* 338 */
  ((Word32)0x05ce << 16) | ((Word32)0xf802 & 0xFFFF),   /* 339 */
  ((Word32)0xf806 << 16) | ((Word32)0x04a8 & 0xFFFF),   /* 340 */
  ((Word32)0x0636 << 16) | ((Word32)0x078c & 0xFFFF),   /* 341 */
  ((Word32)0x009e << 16) | ((Word32)0x04b1 & 0xFFFF),   /* 342 */
  ((Word32)0xfb84 << 16) | ((Word32)0x069a & 0xFFFF),   /* 343 */
  ((Word32)0x07df << 16) | ((Word32)0x0328 & 0xFFFF),   /* 344 */
  ((Word32)0x03ce << 16) | ((Word32)0x057d & 0xFFFF),   /* 345 */
  ((Word32)0x0541 << 16) | ((Word32)0x0177 & 0xFFFF),   /* 346 */
  ((Word32)0x0043 << 16) | ((Word32)0xfa01 & 0xFFFF),   /* 347 */
  ((Word32)0xfce8 << 16) | ((Word32)0x041b & 0xFFFF),   /* 348 */
  ((Word32)0xf836 << 16) | ((Word32)0xf847 & 0xFFFF),   /* 349 */
  ((Word32)0xfbbd << 16) | ((Word32)0xf8b0 & 0xFFFF),   /* 350 */
  ((Word32)0x07fc << 16) | ((Word32)0x04e4 & 0xFFFF),   /* 351 */
  ((Word32)0xfbfb << 16) | ((Word32)0xf8e5 & 0xFFFF),   /* 352 */
  ((Word32)0x0029 << 16) | ((Word32)0x06d1 & 0xFFFF),   /* 353 */
  ((Word32)0x07ff << 16) | ((Word32)0x0791 & 0xFFFF),   /* 354 */
  ((Word32)0x06a2 << 16) | ((Word32)0xff7e & 0xFFFF),   /* 355 */
  ((Word32)0xfb4f << 16) | ((Word32)0x07bf & 0xFFFF),   /* 356 */
  ((Word32)0xfe98 << 16) | ((Word32)0xfc26 & 0xFFFF),   /* 357 */
  ((Word32)0x06ad << 16) | ((Word32)0xfef5 & 0xFFFF),   /* 358 */
  ((Word32)0x007a << 16) | ((Word32)0x01a4 & 0xFFFF),   /* 359 */
  ((Word32)0x0685 << 16) | ((Word32)0xf86d & 0xFFFF),   /* 360 */
  ((Word32)0xfc67 << 16) | ((Word32)0x0346 & 0xFFFF),   /* 361 */
  ((Word32)0xf8d2 << 16) | ((Word32)0x07fd & 0xFFFF),   /* 362 */
  ((Word32)0x032d << 16) | ((Word32)0xfa03 & 0xFFFF),   /* 363 */
  ((Word32)0xff65 << 16) | ((Word32)0x05ed & 0xFFFF),   /* 364 */
  ((Word32)0x061c << 16) | ((Word32)0x0357 & 0xFFFF),   /* 365 */
  ((Word32)0xfa0a << 16) | ((Word32)0x0794 & 0xFFFF),   /* 366 */
  ((Word32)0x0531 << 16) | ((Word32)0x034f & 0xFFFF),   /* 367 */
  ((Word32)0x04fc << 16) | ((Word32)0xf88d & 0xFFFF),   /* 368 */
  ((Word32)0x0361 << 16) | ((Word32)0xff62 & 0xFFFF),   /* 369 */
  ((Word32)0x0037 << 16) | ((Word32)0xff91 & 0xFFFF),   /* 370 */
  ((Word32)0x0666 << 16) | ((Word32)0x0753 & 0xFFFF),   /* 371 */
  ((Word32)0xf9a7 << 16) | ((Word32)0xfd1a & 0xFFFF),   /* 372 */
  ((Word32)0x051c << 16) | ((Word32)0x00a6 & 0xFFFF),   /* 373 */
  ((Word32)0x043b << 16) | ((Word32)0x04ce & 0xFFFF),   /* 374 */
  ((Word32)0x05f0 << 16) | ((Word32)0x005c & 0xFFFF),   /* 375 */
  ((Word32)0x07ed << 16) | ((Word32)0xfe72 & 0xFFFF),   /* 376 */
  ((Word32)0xf991 << 16) | ((Word32)0xf8eb & 0xFFFF),   /* 377 */
  ((Word32)0xfad5 << 16) | ((Word32)0x05c7 & 0xFFFF),   /* 378 */
  ((Word32)0x00ef << 16) | ((Word32)0xf94f & 0xFFFF),   /* 379 */
  ((Word32)0xf865 << 16) | ((Word32)0xf83f & 0xFFFF),   /* 380 */
  ((Word32)0xfb06 << 16) | ((Word32)0x069f & 0xFFFF),   /* 381 */
  ((Word32)0x003e << 16) | ((Word32)0xf805 & 0xFFFF),   /* 382 */
  ((Word32)0xf829 << 16) | ((Word32)0x02ec & 0xFFFF),   /* 383 */
  ((Word32)0xf800 << 16) | ((Word32)0xfd1e & 0xFFFF),   /* 384 */
  ((Word32)0x0721 << 16) | ((Word32)0xf82b & 0xFFFF),   /* 385 */
  ((Word32)0x00d5 << 16) | ((Word32)0x0630 & 0xFFFF),   /* 386 */
  ((Word32)0x07ad << 16) | ((Word32)0xfd2a & 0xFFFF),   /* 387 */
  ((Word32)0x0411 << 16) | ((Word32)0x07b0 & 0xFFFF),   /* 388 */
  ((Word32)0x015c << 16) | ((Word32)0xf9da & 0xFFFF),   /* 389 */
  ((Word32)0x0212 << 16) | ((Word32)0x07fe & 0xFFFF),   /* 390 */
  ((Word32)0xffe9 << 16) | ((Word32)0x07e1 & 0xFFFF),   /* 391 */
  ((Word32)0xf9a2 << 16) | ((Word32)0x07c5 & 0xFFFF),   /* 392 */
  ((Word32)0xf80f << 16) | ((Word32)0xf809 & 0xFFFF),   /* 393 */
  ((Word32)0xf803 << 16) | ((Word32)0x0026 & 0xFFFF),   /* 394 */
  ((Word32)0xfa56 << 16) | ((Word32)0x02b2 & 0xFFFF),   /* 395 */
  ((Word32)0xfa5d << 16) | ((Word32)0x0776 & 0xFFFF),   /* 396 */
  ((Word32)0x07fd << 16) | ((Word32)0xf81a & 0xFFFF),   /* 397 */
  ((Word32)0xfaee << 16) | ((Word32)0xfeaf & 0xFFFF),   /* 398 */
  ((Word32)0xfeb3 << 16) | ((Word32)0xf853 & 0xFFFF),   /* 399 */
  ((Word32)0xfc82 << 16) | ((Word32)0xf86a & 0xFFFF),   /* 400 */
  ((Word32)0xf803 << 16) | ((Word32)0x07b3 & 0xFFFF),   /* 401 */
  ((Word32)0xfea8 << 16) | ((Word32)0xf815 & 0xFFFF),   /* 402 */
  ((Word32)0xf8f6 << 16) | ((Word32)0xfa43 & 0xFFFF),   /* 403 */
  ((Word32)0x0389 << 16) | ((Word32)0xf884 & 0xFFFF),   /* 404 */
  ((Word32)0x0777 << 16) | ((Word32)0xf802 & 0xFFFF),   /* 405 */
  ((Word32)0xf87c << 16) | ((Word32)0xfb7d & 0xFFFF),   /* 406 */
  ((Word32)0xf8ea << 16) | ((Word32)0x03cf & 0xFFFF),   /* 407 */
  ((Word32)0x07ff << 16) | ((Word32)0xf94a & 0xFFFF),   /* 408 */
  ((Word32)0xf9f8 << 16) | ((Word32)0x0011 & 0xFFFF),   /* 409 */
  ((Word32)0x0783 << 16) | ((Word32)0xff19 & 0xFFFF),   /* 410 */
  ((Word32)0x06cf << 16) | ((Word32)0x0430 & 0xFFFF),   /* 411 */
  ((Word32)0x032d << 16) | ((Word32)0x068b & 0xFFFF),   /* 412 */
  ((Word32)0xfd0a << 16) | ((Word32)0xf909 & 0xFFFF),   /* 413 */
  ((Word32)0xfd1e << 16) | ((Word32)0x02c6 & 0xFFFF),   /* 414 */
  ((Word32)0xf887 << 16) | ((Word32)0xf93e & 0xFFFF),   /* 415 */
  ((Word32)0xfac7 << 16) | ((Word32)0xfe86 & 0xFFFF),   /* 416 */
  ((Word32)0x00f5 << 16) | ((Word32)0x07fe & 0xFFFF),   /* 417 */
  ((Word32)0x078b << 16) | ((Word32)0x06a7 & 0xFFFF),   /* 418 */
  ((Word32)0x0602 << 16) | ((Word32)0xfd28 & 0xFFFF),   /* 419 */
  ((Word32)0x048a << 16) | ((Word32)0xfe13 & 0xFFFF),   /* 420 */
  ((Word32)0x03c0 << 16) | ((Word32)0xfd97 & 0xFFFF),   /* 421 */
  ((Word32)0x07c9 << 16) | ((Word32)0xf809 & 0xFFFF),   /* 422 */
  ((Word32)0xfcf0 << 16) | ((Word32)0x07e2 & 0xFFFF),   /* 423 */
  ((Word32)0x0348 << 16) | ((Word32)0x002b & 0xFFFF),   /* 424 */
  ((Word32)0x00c5 << 16) | ((Word32)0x005a & 0xFFFF),   /* 425 */
  ((Word32)0xf92d << 16) | ((Word32)0x0751 & 0xFFFF),   /* 426 */
  ((Word32)0x071c << 16) | ((Word32)0xf805 & 0xFFFF),   /* 427 */
  ((Word32)0xfc25 << 16) | ((Word32)0xf841 & 0xFFFF),   /* 428 */
  ((Word32)0x0235 << 16) | ((Word32)0x04b1 & 0xFFFF),   /* 429 */
  ((Word32)0xfabb << 16) | ((Word32)0x04b5 & 0xFFFF),   /* 430 */
  ((Word32)0x07e8 << 16) | ((Word32)0x0800 & 0xFFFF),   /* 431 */
  ((Word32)0xfe59 << 16) | ((Word32)0x045e & 0xFFFF),   /* 432 */
  ((Word32)0xfb08 << 16) | ((Word32)0xfb35 & 0xFFFF),   /* 433 */
  ((Word32)0x01a0 << 16) | ((Word32)0xf90d & 0xFFFF),   /* 434 */
  ((Word32)0xf82d << 16) | ((Word32)0x07b4 & 0xFFFF),   /* 435 */
  ((Word32)0x00e4 << 16) | ((Word32)0x01b8 & 0xFFFF),   /* 436 */
  ((Word32)0xfcb1 << 16) | ((Word32)0x0242 & 0xFFFF),   /* 437 */
  ((Word32)0x01ee << 16) | ((Word32)0x041b & 0xFFFF),   /* 438 */
  ((Word32)0xfab0 << 16) | ((Word32)0xff57 & 0xFFFF),   /* 439 */
  ((Word32)0xfbb4 << 16) | ((Word32)0xf830 & 0xFFFF),   /* 440 */
  ((Word32)0xf839 << 16) | ((Word32)0x01c4 & 0xFFFF),   /* 441 */
  ((Word32)0x06fe << 16) | ((Word32)0xfefa & 0xFFFF),   /* 442 */
  ((Word32)0x0186 << 16) | ((Word32)0x0021 & 0xFFFF),   /* 443 */
  ((Word32)0xfc4b << 16) | ((Word32)0xf861 & 0xFFFF),   /* 444 */
  ((Word32)0xff6f << 16) | ((Word32)0xf871 & 0xFFFF),   /* 445 */
  ((Word32)0xf89b << 16) | ((Word32)0xff2a & 0xFFFF),   /* 446 */
  ((Word32)0xf94b << 16) | ((Word32)0xffdd & 0xFFFF),   /* 447 */
  ((Word32)0x0604 << 16) | ((Word32)0xf801 & 0xFFFF),   /* 448 */
  ((Word32)0xfca2 << 16) | ((Word32)0x07fa & 0xFFFF),   /* 449 */
  ((Word32)0xfa3b << 16) | ((Word32)0xfd33 & 0xFFFF),   /* 450 */
  ((Word32)0x064f << 16) | ((Word32)0x043a & 0xFFFF),   /* 451 */
  ((Word32)0x07cb << 16) | ((Word32)0xfddd & 0xFFFF),   /* 452 */
  ((Word32)0x07f0 << 16) | ((Word32)0xfb70 & 0xFFFF),   /* 453 */
  ((Word32)0x0625 << 16) | ((Word32)0xf9e1 & 0xFFFF),   /* 454 */
  ((Word32)0xf971 << 16) | ((Word32)0xfa1e & 0xFFFF),   /* 455 */
  ((Word32)0x068e << 16) | ((Word32)0x07fa & 0xFFFF),   /* 456 */
  ((Word32)0xfddd << 16) | ((Word32)0x0583 & 0xFFFF),   /* 457 */
  ((Word32)0xfc89 << 16) | ((Word32)0x06d3 & 0xFFFF),   /* 458 */
  ((Word32)0x07f0 << 16) | ((Word32)0x075a & 0xFFFF),   /* 459 */
  ((Word32)0xf98b << 16) | ((Word32)0xfd64 & 0xFFFF),   /* 460 */
  ((Word32)0x0372 << 16) | ((Word32)0xfe3f & 0xFFFF),   /* 461 */
  ((Word32)0x056b << 16) | ((Word32)0xf85d & 0xFFFF),   /* 462 */
  ((Word32)0x047e << 16) | ((Word32)0xfa58 & 0xFFFF),   /* 463 */
  ((Word32)0x00de << 16) | ((Word32)0xff4f & 0xFFFF),   /* 464 */
  ((Word32)0x074c << 16) | ((Word32)0xfab9 & 0xFFFF),   /* 465 */
  ((Word32)0xfc15 << 16) | ((Word32)0x0481 & 0xFFFF),   /* 466 */
  ((Word32)0xf8e1 << 16) | ((Word32)0xfa44 & 0xFFFF),   /* 467 */
  ((Word32)0x0539 << 16) | ((Word32)0x0546 & 0xFFFF),   /* 468 */
  ((Word32)0x0565 << 16) | ((Word32)0xf977 & 0xFFFF),   /* 469 */
  ((Word32)0xfc2e << 16) | ((Word32)0xfea8 & 0xFFFF),   /* 470 */
  ((Word32)0xf806 << 16) | ((Word32)0xf884 & 0xFFFF),   /* 471 */
  ((Word32)0xf8bb << 16) | ((Word32)0x04f6 & 0xFFFF),   /* 472 */
  ((Word32)0xff78 << 16) | ((Word32)0xfe18 & 0xFFFF),   /* 473 */
  ((Word32)0x07f4 << 16) | ((Word32)0x0181 & 0xFFFF),   /* 474 */
  ((Word32)0x07d1 << 16) | ((Word32)0xfdb5 & 0xFFFF),   /* 475 */
  ((Word32)0x0796 << 16) | ((Word32)0xf833 & 0xFFFF),   /* 476 */
  ((Word32)0xf85e << 16) | ((Word32)0xf9a2 & 0xFFFF),   /* 477 */
  ((Word32)0xfc12 << 16) | ((Word32)0x02a2 & 0xFFFF),   /* 478 */
  ((Word32)0x07fe << 16) | ((Word32)0x071f & 0xFFFF),   /* 479 */
  ((Word32)0x0409 << 16) | ((Word32)0xf91f & 0xFFFF),   /* 480 */
  ((Word32)0x03c6 << 16) | ((Word32)0xfe81 & 0xFFFF),   /* 481 */
  ((Word32)0xfb09 << 16) | ((Word32)0x0600 & 0xFFFF),   /* 482 */
  ((Word32)0xfc7e << 16) | ((Word32)0x0800 & 0xFFFF),   /* 483 */
  ((Word32)0x07e4 << 16) | ((Word32)0xfbb7 & 0xFFFF),   /* 484 */
  ((Word32)0xfb14 << 16) | ((Word32)0xf8d7 & 0xFFFF),   /* 485 */
  ((Word32)0xffb1 << 16) | ((Word32)0xfa69 & 0xFFFF),   /* 486 */
  ((Word32)0xfd98 << 16) | ((Word32)0xff63 & 0xFFFF),   /* 487 */
  ((Word32)0x035a << 16) | ((Word32)0x002d & 0xFFFF),   /* 488 */
  ((Word32)0xf91c << 16) | ((Word32)0x07ea & 0xFFFF),   /* 489 */
  ((Word32)0x0561 << 16) | ((Word32)0xfeec & 0xFFFF),   /* 490 */
  ((Word32)0xfa57 << 16) | ((Word32)0xf9e0 & 0xFFFF),   /* 491 */
  ((Word32)0x0786 << 16) | ((Word32)0x00b9 & 0xFFFF),   /* 492 */
  ((Word32)0xf969 << 16) | ((Word32)0x00b7 & 0xFFFF),   /* 493 */
  ((Word32)0xfd6f << 16) | ((Word32)0x0403 & 0xFFFF),   /* 494 */
  ((Word32)0x049c << 16) | ((Word32)0xf815 & 0xFFFF),   /* 495 */
  ((Word32)0xfd18 << 16) | ((Word32)0x0098 & 0xFFFF),   /* 496 */
  ((Word32)0x0800 << 16) | ((Word32)0xfedf & 0xFFFF),   /* 497 */
  ((Word32)0xf89c << 16) | ((Word32)0xf829 & 0xFFFF),   /* 498 */
  ((Word32)0xfc6e << 16) | ((Word32)0xfba9 & 0xFFFF),   /* 499 */
  ((Word32)0x038a << 16) | ((Word32)0x05b5 & 0xFFFF),   /* 500 */
  ((Word32)0x004b << 16) | ((Word32)0x0517 & 0xFFFF),   /* 501 */
  ((Word32)0x042d << 16) | ((Word32)0xf92b & 0xFFFF),   /* 502 */
  ((Word32)0xf86d << 16) | ((Word32)0xffdb & 0xFFFF),   /* 503 */
  ((Word32)0xf819 << 16) | ((Word32)0x0695 & 0xFFFF),   /* 504 */
  ((Word32)0x06ff << 16) | ((Word32)0x0727 & 0xFFFF),   /* 505 */
  ((Word32)0xf887 << 16) | ((Word32)0x034f & 0xFFFF),   /* 506 */
  ((Word32)0x07af << 16) | ((Word32)0x0773 & 0xFFFF),   /* 507 */
  ((Word32)0x07ce << 16) | ((Word32)0x06e4 & 0xFFFF),   /* 508 */
  ((Word32)0x07f9 << 16) | ((Word32)0x059d & 0xFFFF),   /* 509 */
  ((Word32)0xf86c << 16) | ((Word32)0xfda2 & 0xFFFF),   /* 510 */
  ((Word32)0x0754 << 16) | ((Word32)0xf826 & 0xFFFF),   /* 511 */
  /* MAX_FREQ_COEFFS values from the beginning of the table are repeated here */
  ((Word32)0xf801 << 16) | ((Word32)0xfb3e & 0xFFFF),   /*   0 */
  ((Word32)0x07c5 << 16) | ((Word32)0xfa99 & 0xFFFF),   /*   1 */
  ((Word32)0x0121 << 16) | ((Word32)0xf865 & 0xFFFF),   /*   2 */
  ((Word32)0xfc3d << 16) | ((Word32)0xfd03 & 0xFFFF),   /*   3 */
  ((Word32)0x0675 << 16) | ((Word32)0x025f & 0xFFFF),   /*   4 */
  ((Word32)0xfce2 << 16) | ((Word32)0x072a & 0xFFFF),   /*   5 */
  ((Word32)0xffea << 16) | ((Word32)0xfaa5 & 0xFFFF),   /*   6 */
  ((Word32)0xf8b3 << 16) | ((Word32)0xff14 & 0xFFFF),   /*   7 */
  ((Word32)0x0463 << 16) | ((Word32)0x0605 & 0xFFFF),   /*   8 */
  ((Word32)0x0333 << 16) | ((Word32)0xf816 & 0xFFFF),   /*   9 */
  ((Word32)0xf803 << 16) | ((Word32)0xf8f3 & 0xFFFF),   /*  10 */
  ((Word32)0xf85c << 16) | ((Word32)0x0746 & 0xFFFF),   /*  11 */
  ((Word32)0xfc58 << 16) | ((Word32)0xfb76 & 0xFFFF),   /*  12 */
  ((Word32)0xfa2a << 16) | ((Word32)0xf829 & 0xFFFF),   /*  13 */
  ((Word32)0x060d << 16) | ((Word32)0x01ad & 0xFFFF),   /*  14 */
  ((Word32)0x0091 << 16) | ((Word32)0xf9bd & 0xFFFF),   /*  15 */
  ((Word32)0x05f6 << 16) | ((Word32)0xf8b5 & 0xFFFF),   /*  16 */
  ((Word32)0xf849 << 16) | ((Word32)0xf86c & 0xFFFF),   /*  17 */
  ((Word32)0x026f << 16) | ((Word32)0xfc0c & 0xFFFF),   /*  18 */
  ((Word32)0x0553 << 16) | ((Word32)0x052c & 0xFFFF),   /*  19 */
  ((Word32)0x0756 << 16) | ((Word32)0x0167 & 0xFFFF),   /*  20 */
  ((Word32)0xfa57 << 16) | ((Word32)0x0434 & 0xFFFF),   /*  21 */
  ((Word32)0xfa65 << 16) | ((Word32)0xfc5f & 0xFFFF),   /*  22 */
  ((Word32)0xf80a << 16) | ((Word32)0xf8cb & 0xFFFF),   /*  23 */
  ((Word32)0x07da << 16) | ((Word32)0xf9ce & 0xFFFF),   /*  24 */
  ((Word32)0xfba0 << 16) | ((Word32)0xffcb & 0xFFFF),   /*  25 */
  ((Word32)0xffdd << 16) | ((Word32)0x0006 & 0xFFFF),   /*  26 */
  ((Word32)0xf91c << 16) | ((Word32)0x0367 & 0xFFFF),   /*  27 */
  ((Word32)0xf817 << 16) | ((Word32)0xf8f8 & 0xFFFF),   /*  28 */
  ((Word32)0x0424 << 16) | ((Word32)0x055b & 0xFFFF),   /*  29 */
  ((Word32)0xf807 << 16) | ((Word32)0xfb5a & 0xFFFF),   /*  30 */
  ((Word32)0xf801 << 16) | ((Word32)0x07df & 0xFFFF),   /*  31 */
  ((Word32)0x046c << 16) | ((Word32)0x04c2 & 0xFFFF),   /*  32 */
  ((Word32)0x02c4 << 16) | ((Word32)0x0797 & 0xFFFF),   /*  33 */
  ((Word32)0x0503 << 16) | ((Word32)0xfa0c & 0xFFFF),   /*  34 */
  ((Word32)0xf9d4 << 16) | ((Word32)0xfd4a & 0xFFFF),   /*  35 */
  ((Word32)0xf8ac << 16) | ((Word32)0x004c & 0xFFFF),   /*  36 */
  ((Word32)0xf9e6 << 16) | ((Word32)0xf8b1 & 0xFFFF),   /*  37 */
  ((Word32)0x0662 << 16) | ((Word32)0xf88c & 0xFFFF),   /*  38 */
  ((Word32)0x045c << 16) | ((Word32)0xff0c & 0xFFFF),   /*  39 */
  ((Word32)0xf926 << 16) | ((Word32)0x0365 & 0xFFFF),   /*  40 */
  ((Word32)0xf892 << 16) | ((Word32)0x023b & 0xFFFF),   /*  41 */
  ((Word32)0xff10 << 16) | ((Word32)0xf804 & 0xFFFF),   /*  42 */
  ((Word32)0x01b5 << 16) | ((Word32)0xf8be & 0xFFFF),   /*  43 */
  ((Word32)0xf9e8 << 16) | ((Word32)0x07fb & 0xFFFF),   /*  44 */
  ((Word32)0x07d9 << 16) | ((Word32)0xf855 & 0xFFFF),   /*  45 */
  ((Word32)0xf920 << 16) | ((Word32)0x07a9 & 0xFFFF),   /*  46 */
  ((Word32)0xf889 << 16) | ((Word32)0x03f4 & 0xFFFF)    /*  47 */
};
#endif


/*!
  \name QMF
  \brief  QMF-Table
          64 channels, N = 640, optimized by PE 010516
*/


const Word16 sbr_qmf_64_640[QMF_FILTER_STATE_ANA_SIZE+2*NO_POLY] =
{
  /* Dummy entries to get starting point of window word aligned */
  (Word16)0x0000,(Word16)0x0000,(Word16)0x0000,(Word16)0x0000,(Word16)0x0000,
  (Word16)0x0000,(Word16)0x01b3,(Word16)0x2e3a,(Word16)0xd1c6,(Word16)0xfe4d,
  (Word16)0xffee,(Word16)0x01d8,(Word16)0x2faa,(Word16)0xd333,(Word16)0xfe71,
  (Word16)0xffee,(Word16)0x01fd,(Word16)0x311b,(Word16)0xd4a0,(Word16)0xfe93,
  (Word16)0xfff0,(Word16)0x0224,(Word16)0x328d,(Word16)0xd60a,(Word16)0xfeb5,
  (Word16)0xfff0,(Word16)0x024c,(Word16)0x33ff,(Word16)0xd772,(Word16)0xfed5,
  (Word16)0xfff0,(Word16)0x0275,(Word16)0x3573,(Word16)0xd8d8,(Word16)0xfef4,
  (Word16)0xffef,(Word16)0x029e,(Word16)0x36e7,(Word16)0xda3b,(Word16)0xff12,
  (Word16)0xffef,(Word16)0x02c9,(Word16)0x385a,(Word16)0xdb9b,(Word16)0xff2f,
  (Word16)0xffee,(Word16)0x02f4,(Word16)0x39ce,(Word16)0xdcf9,(Word16)0xff4b,
  (Word16)0xffed,(Word16)0x0320,(Word16)0x3b41,(Word16)0xde53,(Word16)0xff65,
  (Word16)0xffed,(Word16)0x034d,(Word16)0x3cb4,(Word16)0xdfa9,(Word16)0xff7f,
  (Word16)0xffec,(Word16)0x037b,(Word16)0x3e26,(Word16)0xe0fc,(Word16)0xff97,
  (Word16)0xffeb,(Word16)0x03a9,(Word16)0x3f96,(Word16)0xe24c,(Word16)0xffaf,
  (Word16)0xffeb,(Word16)0x03d9,(Word16)0x4106,(Word16)0xe397,(Word16)0xffc5,
  (Word16)0xffea,(Word16)0x0408,(Word16)0x4273,(Word16)0xe4de,(Word16)0xffda,
  (Word16)0xffe9,(Word16)0x0439,(Word16)0x43de,(Word16)0xe621,(Word16)0xffee,
  (Word16)0xffe9,(Word16)0x0469,(Word16)0x4548,(Word16)0xe760,(Word16)0x0001,
  (Word16)0xffe8,(Word16)0x049b,(Word16)0x46af,(Word16)0xe899,(Word16)0x0013,
  (Word16)0xffe8,(Word16)0x04cc,(Word16)0x4813,(Word16)0xe9cf,(Word16)0x0024,
  (Word16)0xffe7,(Word16)0x04fe,(Word16)0x4974,(Word16)0xeaff,(Word16)0x0034,
  (Word16)0xffe7,(Word16)0x0530,(Word16)0x4ad2,(Word16)0xec2a,(Word16)0x0042,
  (Word16)0xffe7,(Word16)0x0562,(Word16)0x4c2d,(Word16)0xed51,(Word16)0x0050,
  (Word16)0xffe6,(Word16)0x0595,(Word16)0x4d84,(Word16)0xee72,(Word16)0x005d,
  (Word16)0xffe7,(Word16)0x05c7,(Word16)0x4ed6,(Word16)0xef8d,(Word16)0x0069,
  (Word16)0xffe6,(Word16)0x05fa,(Word16)0x5025,(Word16)0xf0a4,(Word16)0x0074,
  (Word16)0xffe6,(Word16)0x062c,(Word16)0x516f,(Word16)0xf1b4,(Word16)0x007e,
  (Word16)0xffe7,(Word16)0x065e,(Word16)0x52b4,(Word16)0xf2bf,(Word16)0x0087,
  (Word16)0xffe7,(Word16)0x0690,(Word16)0x53f5,(Word16)0xf3c5,(Word16)0x0090,
  (Word16)0xffe7,(Word16)0x06c1,(Word16)0x5530,(Word16)0xf4c4,(Word16)0x0097,
  (Word16)0xffe8,(Word16)0x06f2,(Word16)0x5665,(Word16)0xf5be,(Word16)0x009e,
  (Word16)0xffe8,(Word16)0x0722,(Word16)0x5795,(Word16)0xf6b2,(Word16)0x00a3,
  (Word16)0xffe9,(Word16)0x0751,(Word16)0x58bf,(Word16)0xf7a0,(Word16)0x00a8,
  (Word16)0xffea,(Word16)0x0780,(Word16)0x59e3,(Word16)0xf887,(Word16)0x00ad,
  (Word16)0xffeb,(Word16)0x07ae,(Word16)0x5b00,(Word16)0xf969,(Word16)0x00b0,
  (Word16)0xffed,(Word16)0x07da,(Word16)0x5c17,(Word16)0xfa45,(Word16)0x00b3,
  (Word16)0xffee,(Word16)0x0806,(Word16)0x5d27,(Word16)0xfb1a,(Word16)0x00b6,
  (Word16)0xffef,(Word16)0x0830,(Word16)0x5e2f,(Word16)0xfbe9,(Word16)0x00b7,
  (Word16)0xfff1,(Word16)0x0859,(Word16)0x5f31,(Word16)0xfcb2,(Word16)0x00b8,
  (Word16)0xfff3,(Word16)0x0881,(Word16)0x602b,(Word16)0xfd74,(Word16)0x00b9,
  (Word16)0xfff5,(Word16)0x08a7,(Word16)0x611d,(Word16)0xfe31,(Word16)0x00b9,
  (Word16)0xfff7,(Word16)0x08cb,(Word16)0x6208,(Word16)0xfee7,(Word16)0x00b8,
  (Word16)0xfff9,(Word16)0x08ee,(Word16)0x62ea,(Word16)0xff97,(Word16)0x00b7,
  (Word16)0xfffb,(Word16)0x090f,(Word16)0x63c4,(Word16)0x0041,(Word16)0x00b6,
  (Word16)0xfffe,(Word16)0x092d,(Word16)0x6496,(Word16)0x00e4,(Word16)0x00b4,
  (Word16)0x0000,(Word16)0x094a,(Word16)0x655f,(Word16)0x0181,(Word16)0x00b2,
  (Word16)0x0004,(Word16)0x0964,(Word16)0x6620,(Word16)0x0218,(Word16)0x00af,
  (Word16)0x0007,(Word16)0x097c,(Word16)0x66d7,(Word16)0x02aa,(Word16)0x00ac,
  (Word16)0x000a,(Word16)0x0991,(Word16)0x6786,(Word16)0x0334,(Word16)0x00a8,
  (Word16)0x000d,(Word16)0x09a4,(Word16)0x682b,(Word16)0x03b9,(Word16)0x00a5,
  (Word16)0x0011,(Word16)0x09b4,(Word16)0x68c7,(Word16)0x0438,(Word16)0x00a1,
  (Word16)0x0014,(Word16)0x09c1,(Word16)0x6959,(Word16)0x04b1,(Word16)0x009d,
  (Word16)0x0018,(Word16)0x09cb,(Word16)0x69e3,(Word16)0x0523,(Word16)0x0099,
  (Word16)0x001c,(Word16)0x09d2,(Word16)0x6a62,(Word16)0x0591,(Word16)0x0094,
  (Word16)0x0020,(Word16)0x09d5,(Word16)0x6ad7,(Word16)0x05f8,(Word16)0x008f,
  (Word16)0x0025,(Word16)0x09d5,(Word16)0x6b43,(Word16)0x0659,(Word16)0x008a,
  (Word16)0x0029,(Word16)0x09d2,(Word16)0x6ba4,(Word16)0x06b5,(Word16)0x0086,
  (Word16)0x002e,(Word16)0x09cb,(Word16)0x6bfc,(Word16)0x070c,(Word16)0x0080,
  (Word16)0x0033,(Word16)0x09c0,(Word16)0x6c49,(Word16)0x075d,(Word16)0x007b,
  (Word16)0x0037,(Word16)0x09b2,(Word16)0x6c8c,(Word16)0x07a8,(Word16)0x0076,
  (Word16)0x003c,(Word16)0x099f,(Word16)0x6cc6,(Word16)0x07ee,(Word16)0x0071,
  (Word16)0x0041,(Word16)0x0988,(Word16)0x6cf4,(Word16)0x082f,(Word16)0x006b,
  (Word16)0x0046,(Word16)0x096d,(Word16)0x6d18,(Word16)0x086b,(Word16)0x0066,
  (Word16)0x004b,(Word16)0x094d,(Word16)0x6d32,(Word16)0x08a2,(Word16)0x0061,
  (Word16)0x0051,(Word16)0x092a,(Word16)0x6d42,(Word16)0x08d4,(Word16)0x005b,
  (Word16)0x0056,(Word16)0x0901,(Word16)0x6d47,(Word16)0x0901,(Word16)0x0056,
};

/*! sin (3.14159265358979323 / (2*L) * n) , L=64*/
const Word16 sbr_ralt_sin_twiddle_L64[64]=
{
(Word16)0x0000, (Word16)0x0324, (Word16)0x0648, (Word16)0x096b, 
(Word16)0x0c8c, (Word16)0x0fab, (Word16)0x12c8, (Word16)0x15e2, 
(Word16)0x18f9, (Word16)0x1c0c, (Word16)0x1f1a, (Word16)0x2224, 
(Word16)0x2528, (Word16)0x2827, (Word16)0x2b1f, (Word16)0x2e11,
(Word16)0x30fc, (Word16)0x33df, (Word16)0x36ba, (Word16)0x398d,
(Word16)0x3c57, (Word16)0x3f17, (Word16)0x41ce, (Word16)0x447b,
(Word16)0x471d, (Word16)0x49b4, (Word16)0x4c40, (Word16)0x4ec0,
(Word16)0x5134, (Word16)0x539b, (Word16)0x55f6, (Word16)0x5843,
(Word16)0x5a82, (Word16)0x5cb4, (Word16)0x5ed7, (Word16)0x60ec,
(Word16)0x62f2, (Word16)0x64e9, (Word16)0x66d0, (Word16)0x68a7,
(Word16)0x6a6e, (Word16)0x6c24, (Word16)0x6dca, (Word16)0x6f5f,
(Word16)0x70e3, (Word16)0x7255, (Word16)0x73b6, (Word16)0x7505,
(Word16)0x7642, (Word16)0x776c, (Word16)0x7885, (Word16)0x798a,
(Word16)0x7a7d, (Word16)0x7b5d, (Word16)0x7c2a, (Word16)0x7ce4,
(Word16)0x7d8a, (Word16)0x7e1e, (Word16)0x7e9d, (Word16)0x7f0a,
(Word16)0x7f62, (Word16)0x7fa7, (Word16)0x7fd9, (Word16)0x7ff6
};


/*! sin (3.14159265358979323 / (2*L) * n) , L=32 */
const Word16 sbr_ralt_sin_twiddle_L32[32] = 
{
(Word16)0x0000, (Word16)0x0648, (Word16)0x0c8c, (Word16)0x12c8, 
(Word16)0x18f9, (Word16)0x1f1a, (Word16)0x2528, (Word16)0x2b1f,
(Word16)0x30fc, (Word16)0x36ba, (Word16)0x3c57, (Word16)0x41ce,
(Word16)0x471d, (Word16)0x4c40, (Word16)0x5134, (Word16)0x55f6,
(Word16)0x5a82, (Word16)0x5ed7, (Word16)0x62f2, (Word16)0x66d0,
(Word16)0x6a6e, (Word16)0x6dca, (Word16)0x70e3, (Word16)0x73b6,
(Word16)0x7642, (Word16)0x7885, (Word16)0x7a7d, (Word16)0x7c2a,
(Word16)0x7d8a, (Word16)0x7e9d, (Word16)0x7f62, (Word16)0x7fd9
};

const Word16 p2_6[6] =
{
   (Word16)0x026e, (Word16)0xf6aa,
   (Word16)0x272a, (Word16)0x272a,
   (Word16)0xf6aa, (Word16)0x026e
};

const Word16 p8_13[13] =
{
  (Word16)0xff0c, (Word16)0xfd18, (Word16)0xfa2e, (Word16)0xf6b3,
  (Word16)0xf359, (Word16)0x0f19, (Word16)0x1000, (Word16)0x0f19,
  (Word16)0x0ca7, (Word16)0x094d, (Word16)0x05d2, (Word16)0x02e8,
  (Word16)0x00f4
};

/*! Number of subbands in 1st, 2nd and 3rd QMF channel */
const Word16 pHybridResolution[] = { 8, 2, 2 };

#ifndef LP_SBR_ONLY


/*!
  \name QMF-Synthesis-Twiddle

  \brief QMF synthesis twiddle factors

  L=64, gain=1.0, angle = 1.0
*/
/*! cos (PI / L * (n + 0.25)); */
const Word16 sbr_cos_twiddle_L64[] =
{
  (Word16)0x7ffe,(Word16)0x7fc2,(Word16)0x7f38,(Word16)0x7e60,
  (Word16)0x7d3a,(Word16)0x7bc6,(Word16)0x7a06,(Word16)0x77fb,
  (Word16)0x75a6,(Word16)0x7308,(Word16)0x7023,(Word16)0x6cf9,
  (Word16)0x698c,(Word16)0x65de,(Word16)0x61f1,(Word16)0x5dc8,
  (Word16)0x5964,(Word16)0x54ca,(Word16)0x4ffb,(Word16)0x4afb,
  (Word16)0x45cd,(Word16)0x4074,(Word16)0x3af3,(Word16)0x354e,
  (Word16)0x2f87,(Word16)0x29a4,(Word16)0x23a7,(Word16)0x1d93,
  (Word16)0x176e,(Word16)0x113a,(Word16)0x0afb,(Word16)0x04b6
};

/*! sin (PI / L * (n + 0.25)); */
const Word16 sbr_sin_twiddle_L64[] =
{
  (Word16)0x0192,(Word16)0x07d9,(Word16)0x0e1c,(Word16)0x1455,
  (Word16)0x1a83,(Word16)0x209f,(Word16)0x26a8,(Word16)0x2c99,
  (Word16)0x326e,(Word16)0x3825,(Word16)0x3db8,(Word16)0x4326,
  (Word16)0x486a,(Word16)0x4d81,(Word16)0x5269,(Word16)0x571e,
  (Word16)0x5b9d,(Word16)0x5fe4,(Word16)0x63ef,(Word16)0x67bd,
  (Word16)0x6b4b,(Word16)0x6e97,(Word16)0x719e,(Word16)0x7460,
  (Word16)0x76d9,(Word16)0x790a,(Word16)0x7aef,(Word16)0x7c89,
  (Word16)0x7dd6,(Word16)0x7ed6,(Word16)0x7f87,(Word16)0x7fea,
};

/*! sin (PI / L * n) */
const Word16 sbr_alt_sin_twiddle_L64[] =
{
  (Word16)0x0000,(Word16)0x0648,(Word16)0x0c8c,(Word16)0x12c8,
  (Word16)0x18f9,(Word16)0x1f1a,(Word16)0x2528,(Word16)0x2b1f,
  (Word16)0x30fc,(Word16)0x36ba,(Word16)0x3c57,(Word16)0x41ce,
  (Word16)0x471d,(Word16)0x4c40,(Word16)0x5134,(Word16)0x55f6,
  (Word16)0x5a82,(Word16)0x5ed7,(Word16)0x62f2,(Word16)0x66d0,
  (Word16)0x6a6e,(Word16)0x6dca,(Word16)0x70e3,(Word16)0x73b6,
  (Word16)0x7642,(Word16)0x7885,(Word16)0x7a7d,(Word16)0x7c2a,
  (Word16)0x7d8a,(Word16)0x7e9d,(Word16)0x7f62,(Word16)0x7fd9,
  (Word16)0x7fff
};

const Word16 sbr_cos_twiddle_ds_L32[] =
{
  (Word16)0x7ffe, (Word16)0x7fea, (Word16)0x7fc2, (Word16)0x7f87,
  (Word16)0x7f38, (Word16)0x7ed6, (Word16)0x7e60, (Word16)0x7dd6,
  (Word16)0x7d3a, (Word16)0x7c89, (Word16)0x7bc6, (Word16)0x7aef,
  (Word16)0x7a06, (Word16)0x790a, (Word16)0x77fb, (Word16)0x76d9,
  (Word16)0x75a6, (Word16)0x7460, (Word16)0x7308, (Word16)0x719e,
  (Word16)0x7023, (Word16)0x6e97, (Word16)0x6cf9, (Word16)0x6b4b,
  (Word16)0x698c, (Word16)0x67bd, (Word16)0x65de, (Word16)0x63ef,
  (Word16)0x61f1, (Word16)0x5fe4, (Word16)0x5dc8, (Word16)0x5b9d
};

const Word16 sbr_sin_twiddle_ds_L32[] =
{
  (Word16)0x0192, (Word16)0x04b6, (Word16)0x07d9, (Word16)0x0afb,
  (Word16)0x0e1c, (Word16)0x113a, (Word16)0x1455, (Word16)0x176e,
  (Word16)0x1a83, (Word16)0x1d93, (Word16)0x209f, (Word16)0x23a7,
  (Word16)0x26a8, (Word16)0x29a4, (Word16)0x2c99, (Word16)0x2f87,
  (Word16)0x326e, (Word16)0x354e, (Word16)0x3825, (Word16)0x3af3,
  (Word16)0x3db8, (Word16)0x4074, (Word16)0x4326, (Word16)0x45cd,
  (Word16)0x486a, (Word16)0x4afb, (Word16)0x4d81, (Word16)0x4ffb,
  (Word16)0x5269, (Word16)0x54ca, (Word16)0x571e, (Word16)0x5964
};




/*!
  \name QMF-Analysis-Twiddle

  \brief QMF analysis twiddle factors

  L=32, gain=2.0, angle = 0.75
*/
const Word16 sbr_cos_twiddle_L32[]=
{
  (Word16)0x7ff6,(Word16)0x7f0a,(Word16)0x7ce4,(Word16)0x798a,
  (Word16)0x7505,(Word16)0x6f5f,(Word16)0x68a7,(Word16)0x60ec,
  (Word16)0x5843,(Word16)0x4ec0,(Word16)0x447b,(Word16)0x398d,
  (Word16)0x2e11,(Word16)0x2224,(Word16)0x15e2,(Word16)0x096b
};

const Word16 sbr_sin_twiddle_L32[]=
{
  (Word16)0x0324,(Word16)0x0fab,(Word16)0x1c0c,(Word16)0x2827,
  (Word16)0x33df,(Word16)0x3f17,(Word16)0x49b4,(Word16)0x539b,
  (Word16)0x5cb4,(Word16)0x64e9,(Word16)0x6c24,(Word16)0x7255,
  (Word16)0x776c,(Word16)0x7b5d,(Word16)0x7e1e,(Word16)0x7fa7
};

const Word16 sbr_alt_sin_twiddle_L32[] =
{
  (Word16)0x0000,(Word16)0x0c8c,(Word16)0x18f9,(Word16)0x2528,
  (Word16)0x30fc,(Word16)0x3c57,(Word16)0x471d,(Word16)0x5134,
  (Word16)0x5a82,(Word16)0x62f2,(Word16)0x6a6e,(Word16)0x70e3,
  (Word16)0x7642,(Word16)0x7a7d,(Word16)0x7d8a,(Word16)0x7f62,
  (Word16)0x7fff
};

const Word16 sbr_t_cos_L32[] =
{
  (Word16)0x7fea,(Word16)0x7f38,(Word16)0x7dd6,(Word16)0x7bc6,
  (Word16)0x790a,(Word16)0x75a6,(Word16)0x719e,(Word16)0x6cf9,
  (Word16)0x67bd,(Word16)0x61f1,(Word16)0x5b9d,(Word16)0x54ca,
  (Word16)0x4d81,(Word16)0x45cd,(Word16)0x3db8,(Word16)0x354e,
  (Word16)0x2c99,(Word16)0x23a7,(Word16)0x1a83,(Word16)0x113a,
  (Word16)0x07d9,(Word16)0xfe6e,(Word16)0xf505,(Word16)0xebab,
  (Word16)0xe26d,(Word16)0xd958,(Word16)0xd079,(Word16)0xc7db,
  (Word16)0xbf8c,(Word16)0xb796,(Word16)0xb005,(Word16)0xa8e2
};

const Word16 sbr_t_sin_L32[] =
{
  (Word16)0x04b6,(Word16)0x0e1c,(Word16)0x176e,(Word16)0x209f,
  (Word16)0x29a4,(Word16)0x326e,(Word16)0x3af3,(Word16)0x4326,
  (Word16)0x4afb,(Word16)0x5269,(Word16)0x5964,(Word16)0x5fe4,
  (Word16)0x65de,(Word16)0x6b4b,(Word16)0x7023,(Word16)0x7460,
  (Word16)0x77fb,(Word16)0x7aef,(Word16)0x7d3a,(Word16)0x7ed6,
  (Word16)0x7fc2,(Word16)0x7ffe,(Word16)0x7f87,(Word16)0x7e60,
  (Word16)0x7c89,(Word16)0x7a06,(Word16)0x76d9,(Word16)0x7308,
  (Word16)0x6e97,(Word16)0x698c,(Word16)0x63ef,(Word16)0x5dc8
};

#endif /* #ifndef LP_SBR_ONLY */

/*!
  \name FrameInfoDefaults

  Predefined envelope positions for the FIX-FIX case (static framing)
*/
const FRAME_INFO sbr_frame_info1_16 = { 0, 1, {0, 16, 0, 0,0,0}, {1, 0,0,0,0}, -1, 1, {0, 16,0 } };
const FRAME_INFO sbr_frame_info2_16 = { 0, 2, {0, 8, 16, 0,0,0}, {1, 1,0,0,0}, -1, 2, {0, 8, 16} };
const FRAME_INFO sbr_frame_info4_16 = { 0, 4, {0, 4, 8, 12, 16}, {1, 1, 1, 1}, -1, 2, {0, 8, 16} };


/*!
  Default values for the time before the first SBR header is read
*/
const SBR_HEADER_DATA sbr_defaultHeader = 
{
  SBR_NOT_INITIALIZED,      /* syncState */
  0,                        /* frameErrorFlag */
  0,                        /* prevFrameErrorFlag */
  16,                       /* numberTimeSlots */
  2,                        /* timeStep */
  1024,                     /* codecFrameSize */
  44100,                    /* outSampleRate */


  UNDEFINED_CHANNEL_MODE,   /* channelMode */
  SBR_AMP_RES_3_0,          /* ampResolution */


  15,                       /* startFreq */
  6,                        /* stopFreq */
  0,                        /* xover_band */
  SBR_FREQ_SCALE_DEFAULT,   /* freqScale */
  SBR_ALTER_SCALE_DEFAULT,  /* alterScale */
  SBR_NOISE_BANDS_DEFAULT,  /* noise_bands */


  SBR_LIMITER_BANDS_DEFAULT,
  SBR_LIMITER_GAINS_DEFAULT,
  SBR_INTERPOL_FREQ_DEFAULT,
  SBR_SMOOTHING_LENGTH_DEFAULT,

  NULL,                     /* freqBandData */
};


/*!
  \name SBR_HuffmanTables

*/
const Word16 sbr_huffBook_EnvLevel10T[120] = {
  (Word16)((   1&0xff)<<8)|(   2&0xff), (Word16)(( -64&0xff)<<8)|( -65&0xff), (Word16)((   3&0xff)<<8)|(   4&0xff), (Word16)(( -63&0xff)<<8)|( -66&0xff),
  (Word16)((   5&0xff)<<8)|(   6&0xff), (Word16)(( -62&0xff)<<8)|( -67&0xff), (Word16)((   7&0xff)<<8)|(   8&0xff), (Word16)(( -61&0xff)<<8)|( -68&0xff),
  (Word16)((   9&0xff)<<8)|(  10&0xff), (Word16)(( -60&0xff)<<8)|( -69&0xff), (Word16)((  11&0xff)<<8)|(  12&0xff), (Word16)(( -59&0xff)<<8)|( -70&0xff),
  (Word16)((  13&0xff)<<8)|(  14&0xff), (Word16)(( -58&0xff)<<8)|( -71&0xff), (Word16)((  15&0xff)<<8)|(  16&0xff), (Word16)(( -57&0xff)<<8)|( -72&0xff),
  (Word16)((  17&0xff)<<8)|(  18&0xff), (Word16)(( -73&0xff)<<8)|( -56&0xff), (Word16)((  19&0xff)<<8)|(  21&0xff), (Word16)(( -74&0xff)<<8)|(  20&0xff),
  (Word16)(( -55&0xff)<<8)|( -75&0xff), (Word16)((  22&0xff)<<8)|(  26&0xff), (Word16)((  23&0xff)<<8)|(  24&0xff), (Word16)(( -54&0xff)<<8)|( -76&0xff),
  (Word16)(( -77&0xff)<<8)|(  25&0xff), (Word16)(( -53&0xff)<<8)|( -78&0xff), (Word16)((  27&0xff)<<8)|(  34&0xff), (Word16)((  28&0xff)<<8)|(  29&0xff),
  (Word16)(( -52&0xff)<<8)|( -79&0xff), (Word16)((  30&0xff)<<8)|(  31&0xff), (Word16)(( -80&0xff)<<8)|( -51&0xff), (Word16)((  32&0xff)<<8)|(  33&0xff),
  (Word16)(( -83&0xff)<<8)|( -82&0xff), (Word16)(( -81&0xff)<<8)|( -50&0xff), (Word16)((  35&0xff)<<8)|(  57&0xff), (Word16)((  36&0xff)<<8)|(  40&0xff),
  (Word16)((  37&0xff)<<8)|(  38&0xff), (Word16)(( -88&0xff)<<8)|( -84&0xff), (Word16)(( -48&0xff)<<8)|(  39&0xff), (Word16)(( -90&0xff)<<8)|( -85&0xff),
  (Word16)((  41&0xff)<<8)|(  46&0xff), (Word16)((  42&0xff)<<8)|(  43&0xff), (Word16)(( -49&0xff)<<8)|( -87&0xff), (Word16)((  44&0xff)<<8)|(  45&0xff),
  (Word16)(( -89&0xff)<<8)|( -86&0xff), (Word16)((-124&0xff)<<8)|(-123&0xff), (Word16)((  47&0xff)<<8)|(  50&0xff), (Word16)((  48&0xff)<<8)|(  49&0xff),
  (Word16)((-122&0xff)<<8)|(-121&0xff), (Word16)((-120&0xff)<<8)|(-119&0xff), (Word16)((  51&0xff)<<8)|(  54&0xff), (Word16)((  52&0xff)<<8)|(  53&0xff),
  (Word16)((-118&0xff)<<8)|(-117&0xff), (Word16)((-116&0xff)<<8)|(-115&0xff), (Word16)((  55&0xff)<<8)|(  56&0xff), (Word16)((-114&0xff)<<8)|(-113&0xff),
  (Word16)((-112&0xff)<<8)|(-111&0xff), (Word16)((  58&0xff)<<8)|(  89&0xff), (Word16)((  59&0xff)<<8)|(  74&0xff), (Word16)((  60&0xff)<<8)|(  67&0xff),
  (Word16)((  61&0xff)<<8)|(  64&0xff), (Word16)((  62&0xff)<<8)|(  63&0xff), (Word16)((-110&0xff)<<8)|(-109&0xff), (Word16)((-108&0xff)<<8)|(-107&0xff),
  (Word16)((  65&0xff)<<8)|(  66&0xff), (Word16)((-106&0xff)<<8)|(-105&0xff), (Word16)((-104&0xff)<<8)|(-103&0xff), (Word16)((  68&0xff)<<8)|(  71&0xff),
  (Word16)((  69&0xff)<<8)|(  70&0xff), (Word16)((-102&0xff)<<8)|(-101&0xff), (Word16)((-100&0xff)<<8)|( -99&0xff), (Word16)((  72&0xff)<<8)|(  73&0xff),
  (Word16)(( -98&0xff)<<8)|( -97&0xff), (Word16)(( -96&0xff)<<8)|( -95&0xff), (Word16)((  75&0xff)<<8)|(  82&0xff), (Word16)((  76&0xff)<<8)|(  79&0xff),
  (Word16)((  77&0xff)<<8)|(  78&0xff), (Word16)(( -94&0xff)<<8)|( -93&0xff), (Word16)(( -92&0xff)<<8)|( -91&0xff), (Word16)((  80&0xff)<<8)|(  81&0xff),
  (Word16)(( -47&0xff)<<8)|( -46&0xff), (Word16)(( -45&0xff)<<8)|( -44&0xff), (Word16)((  83&0xff)<<8)|(  86&0xff), (Word16)((  84&0xff)<<8)|(  85&0xff),
  (Word16)(( -43&0xff)<<8)|( -42&0xff), (Word16)(( -41&0xff)<<8)|( -40&0xff), (Word16)((  87&0xff)<<8)|(  88&0xff), (Word16)(( -39&0xff)<<8)|( -38&0xff),
  (Word16)(( -37&0xff)<<8)|( -36&0xff), (Word16)((  90&0xff)<<8)|( 105&0xff), (Word16)((  91&0xff)<<8)|(  98&0xff), (Word16)((  92&0xff)<<8)|(  95&0xff),
  (Word16)((  93&0xff)<<8)|(  94&0xff), (Word16)(( -35&0xff)<<8)|( -34&0xff), (Word16)(( -33&0xff)<<8)|( -32&0xff), (Word16)((  96&0xff)<<8)|(  97&0xff),
  (Word16)(( -31&0xff)<<8)|( -30&0xff), (Word16)(( -29&0xff)<<8)|( -28&0xff), (Word16)((  99&0xff)<<8)|( 102&0xff), (Word16)(( 100&0xff)<<8)|( 101&0xff),
  (Word16)(( -27&0xff)<<8)|( -26&0xff), (Word16)(( -25&0xff)<<8)|( -24&0xff), (Word16)(( 103&0xff)<<8)|( 104&0xff), (Word16)(( -23&0xff)<<8)|( -22&0xff),
  (Word16)(( -21&0xff)<<8)|( -20&0xff), (Word16)(( 106&0xff)<<8)|( 113&0xff), (Word16)(( 107&0xff)<<8)|( 110&0xff), (Word16)(( 108&0xff)<<8)|( 109&0xff),
  (Word16)(( -19&0xff)<<8)|( -18&0xff), (Word16)(( -17&0xff)<<8)|( -16&0xff), (Word16)(( 111&0xff)<<8)|( 112&0xff), (Word16)(( -15&0xff)<<8)|( -14&0xff),
  (Word16)(( -13&0xff)<<8)|( -12&0xff), (Word16)(( 114&0xff)<<8)|( 117&0xff), (Word16)(( 115&0xff)<<8)|( 116&0xff), (Word16)(( -11&0xff)<<8)|( -10&0xff),
  (Word16)((  -9&0xff)<<8)|(  -8&0xff), (Word16)(( 118&0xff)<<8)|( 119&0xff), (Word16)((  -7&0xff)<<8)|(  -6&0xff), (Word16)((  -5&0xff)<<8)|(  -4&0xff)
};

const Word16 sbr_huffBook_EnvLevel10F[120] = {
  (Word16)((   1&0xff)<<8)|(   2&0xff), (Word16)(( -64&0xff)<<8)|( -65&0xff), (Word16)((   3&0xff)<<8)|(   4&0xff), (Word16)(( -63&0xff)<<8)|( -66&0xff),
  (Word16)((   5&0xff)<<8)|(   6&0xff), (Word16)(( -67&0xff)<<8)|( -62&0xff), (Word16)((   7&0xff)<<8)|(   8&0xff), (Word16)(( -68&0xff)<<8)|( -61&0xff),
  (Word16)((   9&0xff)<<8)|(  10&0xff), (Word16)(( -69&0xff)<<8)|( -60&0xff), (Word16)((  11&0xff)<<8)|(  13&0xff), (Word16)(( -70&0xff)<<8)|(  12&0xff),
  (Word16)(( -59&0xff)<<8)|( -71&0xff), (Word16)((  14&0xff)<<8)|(  16&0xff), (Word16)(( -58&0xff)<<8)|(  15&0xff), (Word16)(( -72&0xff)<<8)|( -57&0xff),
  (Word16)((  17&0xff)<<8)|(  19&0xff), (Word16)(( -73&0xff)<<8)|(  18&0xff), (Word16)(( -56&0xff)<<8)|( -74&0xff), (Word16)((  20&0xff)<<8)|(  23&0xff),
  (Word16)((  21&0xff)<<8)|(  22&0xff), (Word16)(( -55&0xff)<<8)|( -75&0xff), (Word16)(( -54&0xff)<<8)|( -53&0xff), (Word16)((  24&0xff)<<8)|(  27&0xff),
  (Word16)((  25&0xff)<<8)|(  26&0xff), (Word16)(( -76&0xff)<<8)|( -52&0xff), (Word16)(( -77&0xff)<<8)|( -51&0xff), (Word16)((  28&0xff)<<8)|(  31&0xff),
  (Word16)((  29&0xff)<<8)|(  30&0xff), (Word16)(( -50&0xff)<<8)|( -78&0xff), (Word16)(( -79&0xff)<<8)|( -49&0xff), (Word16)((  32&0xff)<<8)|(  36&0xff),
  (Word16)((  33&0xff)<<8)|(  34&0xff), (Word16)(( -48&0xff)<<8)|( -47&0xff), (Word16)(( -80&0xff)<<8)|(  35&0xff), (Word16)(( -81&0xff)<<8)|( -82&0xff),
  (Word16)((  37&0xff)<<8)|(  47&0xff), (Word16)((  38&0xff)<<8)|(  41&0xff), (Word16)((  39&0xff)<<8)|(  40&0xff), (Word16)(( -83&0xff)<<8)|( -46&0xff),
  (Word16)(( -45&0xff)<<8)|( -84&0xff), (Word16)((  42&0xff)<<8)|(  44&0xff), (Word16)(( -85&0xff)<<8)|(  43&0xff), (Word16)(( -44&0xff)<<8)|( -43&0xff),
  (Word16)((  45&0xff)<<8)|(  46&0xff), (Word16)(( -88&0xff)<<8)|( -87&0xff), (Word16)(( -86&0xff)<<8)|( -90&0xff), (Word16)((  48&0xff)<<8)|(  66&0xff),
  (Word16)((  49&0xff)<<8)|(  56&0xff), (Word16)((  50&0xff)<<8)|(  53&0xff), (Word16)((  51&0xff)<<8)|(  52&0xff), (Word16)(( -92&0xff)<<8)|( -42&0xff),
  (Word16)(( -41&0xff)<<8)|( -39&0xff), (Word16)((  54&0xff)<<8)|(  55&0xff), (Word16)((-105&0xff)<<8)|( -89&0xff), (Word16)(( -38&0xff)<<8)|( -37&0xff),
  (Word16)((  57&0xff)<<8)|(  60&0xff), (Word16)((  58&0xff)<<8)|(  59&0xff), (Word16)(( -94&0xff)<<8)|( -91&0xff), (Word16)(( -40&0xff)<<8)|( -36&0xff),
  (Word16)((  61&0xff)<<8)|(  63&0xff), (Word16)(( -20&0xff)<<8)|(  62&0xff), (Word16)((-115&0xff)<<8)|(-110&0xff), (Word16)((  64&0xff)<<8)|(  65&0xff),
  (Word16)((-108&0xff)<<8)|(-107&0xff), (Word16)((-101&0xff)<<8)|( -97&0xff), (Word16)((  67&0xff)<<8)|(  89&0xff), (Word16)((  68&0xff)<<8)|(  75&0xff),
  (Word16)((  69&0xff)<<8)|(  72&0xff), (Word16)((  70&0xff)<<8)|(  71&0xff), (Word16)(( -95&0xff)<<8)|( -93&0xff), (Word16)(( -34&0xff)<<8)|( -27&0xff),
  (Word16)((  73&0xff)<<8)|(  74&0xff), (Word16)(( -22&0xff)<<8)|( -17&0xff), (Word16)(( -16&0xff)<<8)|(-124&0xff), (Word16)((  76&0xff)<<8)|(  82&0xff),
  (Word16)((  77&0xff)<<8)|(  79&0xff), (Word16)((-123&0xff)<<8)|(  78&0xff), (Word16)((-122&0xff)<<8)|(-121&0xff), (Word16)((  80&0xff)<<8)|(  81&0xff),
  (Word16)((-120&0xff)<<8)|(-119&0xff), (Word16)((-118&0xff)<<8)|(-117&0xff), (Word16)((  83&0xff)<<8)|(  86&0xff), (Word16)((  84&0xff)<<8)|(  85&0xff),
  (Word16)((-116&0xff)<<8)|(-114&0xff), (Word16)((-113&0xff)<<8)|(-112&0xff), (Word16)((  87&0xff)<<8)|(  88&0xff), (Word16)((-111&0xff)<<8)|(-109&0xff),
  (Word16)((-106&0xff)<<8)|(-104&0xff), (Word16)((  90&0xff)<<8)|( 105&0xff), (Word16)((  91&0xff)<<8)|(  98&0xff), (Word16)((  92&0xff)<<8)|(  95&0xff),
  (Word16)((  93&0xff)<<8)|(  94&0xff), (Word16)((-103&0xff)<<8)|(-102&0xff), (Word16)((-100&0xff)<<8)|( -99&0xff), (Word16)((  96&0xff)<<8)|(  97&0xff),
  (Word16)(( -98&0xff)<<8)|( -96&0xff), (Word16)(( -35&0xff)<<8)|( -33&0xff), (Word16)((  99&0xff)<<8)|( 102&0xff), (Word16)(( 100&0xff)<<8)|( 101&0xff),
  (Word16)(( -32&0xff)<<8)|( -31&0xff), (Word16)(( -30&0xff)<<8)|( -29&0xff), (Word16)(( 103&0xff)<<8)|( 104&0xff), (Word16)(( -28&0xff)<<8)|( -26&0xff),
  (Word16)(( -25&0xff)<<8)|( -24&0xff), (Word16)(( 106&0xff)<<8)|( 113&0xff), (Word16)(( 107&0xff)<<8)|( 110&0xff), (Word16)(( 108&0xff)<<8)|( 109&0xff),
  (Word16)(( -23&0xff)<<8)|( -21&0xff), (Word16)(( -19&0xff)<<8)|( -18&0xff), (Word16)(( 111&0xff)<<8)|( 112&0xff), (Word16)(( -15&0xff)<<8)|( -14&0xff),
  (Word16)(( -13&0xff)<<8)|( -12&0xff), (Word16)(( 114&0xff)<<8)|( 117&0xff), (Word16)(( 115&0xff)<<8)|( 116&0xff), (Word16)(( -11&0xff)<<8)|( -10&0xff),
  (Word16)((  -9&0xff)<<8)|(  -8&0xff), (Word16)(( 118&0xff)<<8)|( 119&0xff), (Word16)((  -7&0xff)<<8)|(  -6&0xff), (Word16)((  -5&0xff)<<8)|(  -4&0xff)
};

const Word16 sbr_huffBook_EnvBalance10T[48] = {
  (Word16)(( -64&0xff)<<8)|(   1&0xff), (Word16)(( -63&0xff)<<8)|(   2&0xff), (Word16)(( -65&0xff)<<8)|(   3&0xff), (Word16)(( -62&0xff)<<8)|(   4&0xff),
  (Word16)(( -66&0xff)<<8)|(   5&0xff), (Word16)(( -61&0xff)<<8)|(   6&0xff), (Word16)(( -67&0xff)<<8)|(   7&0xff), (Word16)(( -60&0xff)<<8)|(   8&0xff),
  (Word16)(( -68&0xff)<<8)|(   9&0xff), (Word16)((  10&0xff)<<8)|(  11&0xff), (Word16)(( -69&0xff)<<8)|( -59&0xff), (Word16)((  12&0xff)<<8)|(  13&0xff),
  (Word16)(( -70&0xff)<<8)|( -58&0xff), (Word16)((  14&0xff)<<8)|(  28&0xff), (Word16)((  15&0xff)<<8)|(  21&0xff), (Word16)((  16&0xff)<<8)|(  18&0xff),
  (Word16)(( -57&0xff)<<8)|(  17&0xff), (Word16)(( -71&0xff)<<8)|( -56&0xff), (Word16)((  19&0xff)<<8)|(  20&0xff), (Word16)(( -88&0xff)<<8)|( -87&0xff),
  (Word16)(( -86&0xff)<<8)|( -85&0xff), (Word16)((  22&0xff)<<8)|(  25&0xff), (Word16)((  23&0xff)<<8)|(  24&0xff), (Word16)(( -84&0xff)<<8)|( -83&0xff),
  (Word16)(( -82&0xff)<<8)|( -81&0xff), (Word16)((  26&0xff)<<8)|(  27&0xff), (Word16)(( -80&0xff)<<8)|( -79&0xff), (Word16)(( -78&0xff)<<8)|( -77&0xff),
  (Word16)((  29&0xff)<<8)|(  36&0xff), (Word16)((  30&0xff)<<8)|(  33&0xff), (Word16)((  31&0xff)<<8)|(  32&0xff), (Word16)(( -76&0xff)<<8)|( -75&0xff),
  (Word16)(( -74&0xff)<<8)|( -73&0xff), (Word16)((  34&0xff)<<8)|(  35&0xff), (Word16)(( -72&0xff)<<8)|( -55&0xff), (Word16)(( -54&0xff)<<8)|( -53&0xff),
  (Word16)((  37&0xff)<<8)|(  41&0xff), (Word16)((  38&0xff)<<8)|(  39&0xff), (Word16)(( -52&0xff)<<8)|( -51&0xff), (Word16)(( -50&0xff)<<8)|(  40&0xff),
  (Word16)(( -49&0xff)<<8)|( -48&0xff), (Word16)((  42&0xff)<<8)|(  45&0xff), (Word16)((  43&0xff)<<8)|(  44&0xff), (Word16)(( -47&0xff)<<8)|( -46&0xff),
  (Word16)(( -45&0xff)<<8)|( -44&0xff), (Word16)((  46&0xff)<<8)|(  47&0xff), (Word16)(( -43&0xff)<<8)|( -42&0xff), (Word16)(( -41&0xff)<<8)|( -40&0xff)
};

const Word16 sbr_huffBook_EnvBalance10F[48] = {
  (Word16)(( -64&0xff)<<8)|(   1&0xff), (Word16)(( -65&0xff)<<8)|(   2&0xff), (Word16)(( -63&0xff)<<8)|(   3&0xff), (Word16)(( -66&0xff)<<8)|(   4&0xff),
  (Word16)(( -62&0xff)<<8)|(   5&0xff), (Word16)(( -61&0xff)<<8)|(   6&0xff), (Word16)(( -67&0xff)<<8)|(   7&0xff), (Word16)(( -68&0xff)<<8)|(   8&0xff),
  (Word16)(( -60&0xff)<<8)|(   9&0xff), (Word16)((  10&0xff)<<8)|(  11&0xff), (Word16)(( -69&0xff)<<8)|( -59&0xff), (Word16)(( -70&0xff)<<8)|(  12&0xff),
  (Word16)(( -58&0xff)<<8)|(  13&0xff), (Word16)((  14&0xff)<<8)|(  17&0xff), (Word16)(( -71&0xff)<<8)|(  15&0xff), (Word16)(( -57&0xff)<<8)|(  16&0xff),
  (Word16)(( -56&0xff)<<8)|( -73&0xff), (Word16)((  18&0xff)<<8)|(  32&0xff), (Word16)((  19&0xff)<<8)|(  25&0xff), (Word16)((  20&0xff)<<8)|(  22&0xff),
  (Word16)(( -72&0xff)<<8)|(  21&0xff), (Word16)(( -88&0xff)<<8)|( -87&0xff), (Word16)((  23&0xff)<<8)|(  24&0xff), (Word16)(( -86&0xff)<<8)|( -85&0xff),
  (Word16)(( -84&0xff)<<8)|( -83&0xff), (Word16)((  26&0xff)<<8)|(  29&0xff), (Word16)((  27&0xff)<<8)|(  28&0xff), (Word16)(( -82&0xff)<<8)|( -81&0xff),
  (Word16)(( -80&0xff)<<8)|( -79&0xff), (Word16)((  30&0xff)<<8)|(  31&0xff), (Word16)(( -78&0xff)<<8)|( -77&0xff), (Word16)(( -76&0xff)<<8)|( -75&0xff),
  (Word16)((  33&0xff)<<8)|(  40&0xff), (Word16)((  34&0xff)<<8)|(  37&0xff), (Word16)((  35&0xff)<<8)|(  36&0xff), (Word16)(( -74&0xff)<<8)|( -55&0xff),
  (Word16)(( -54&0xff)<<8)|( -53&0xff), (Word16)((  38&0xff)<<8)|(  39&0xff), (Word16)(( -52&0xff)<<8)|( -51&0xff), (Word16)(( -50&0xff)<<8)|( -49&0xff),
  (Word16)((  41&0xff)<<8)|(  44&0xff), (Word16)((  42&0xff)<<8)|(  43&0xff), (Word16)(( -48&0xff)<<8)|( -47&0xff), (Word16)(( -46&0xff)<<8)|( -45&0xff),
  (Word16)((  45&0xff)<<8)|(  46&0xff), (Word16)(( -44&0xff)<<8)|( -43&0xff), (Word16)(( -42&0xff)<<8)|(  47&0xff), (Word16)(( -41&0xff)<<8)|( -40&0xff)
};

const Word16 sbr_huffBook_EnvLevel11T[62] = {
  (Word16)(( -64&0xff)<<8)|(   1&0xff), (Word16)(( -65&0xff)<<8)|(   2&0xff), (Word16)(( -63&0xff)<<8)|(   3&0xff), (Word16)(( -66&0xff)<<8)|(   4&0xff),
  (Word16)(( -62&0xff)<<8)|(   5&0xff), (Word16)(( -67&0xff)<<8)|(   6&0xff), (Word16)(( -61&0xff)<<8)|(   7&0xff), (Word16)(( -68&0xff)<<8)|(   8&0xff),
  (Word16)(( -60&0xff)<<8)|(   9&0xff), (Word16)((  10&0xff)<<8)|(  11&0xff), (Word16)(( -69&0xff)<<8)|( -59&0xff), (Word16)((  12&0xff)<<8)|(  14&0xff),
  (Word16)(( -70&0xff)<<8)|(  13&0xff), (Word16)(( -71&0xff)<<8)|( -58&0xff), (Word16)((  15&0xff)<<8)|(  18&0xff), (Word16)((  16&0xff)<<8)|(  17&0xff),
  (Word16)(( -72&0xff)<<8)|( -57&0xff), (Word16)(( -73&0xff)<<8)|( -74&0xff), (Word16)((  19&0xff)<<8)|(  22&0xff), (Word16)(( -56&0xff)<<8)|(  20&0xff),
  (Word16)(( -55&0xff)<<8)|(  21&0xff), (Word16)(( -54&0xff)<<8)|( -77&0xff), (Word16)((  23&0xff)<<8)|(  31&0xff), (Word16)((  24&0xff)<<8)|(  25&0xff),
  (Word16)(( -75&0xff)<<8)|( -76&0xff), (Word16)((  26&0xff)<<8)|(  27&0xff), (Word16)(( -78&0xff)<<8)|( -53&0xff), (Word16)((  28&0xff)<<8)|(  29&0xff),
  (Word16)(( -52&0xff)<<8)|( -95&0xff), (Word16)(( -94&0xff)<<8)|(  30&0xff), (Word16)(( -93&0xff)<<8)|( -92&0xff), (Word16)((  32&0xff)<<8)|(  47&0xff),
  (Word16)((  33&0xff)<<8)|(  40&0xff), (Word16)((  34&0xff)<<8)|(  37&0xff), (Word16)((  35&0xff)<<8)|(  36&0xff), (Word16)(( -91&0xff)<<8)|( -90&0xff),
  (Word16)(( -89&0xff)<<8)|( -88&0xff), (Word16)((  38&0xff)<<8)|(  39&0xff), (Word16)(( -87&0xff)<<8)|( -86&0xff), (Word16)(( -85&0xff)<<8)|( -84&0xff),
  (Word16)((  41&0xff)<<8)|(  44&0xff), (Word16)((  42&0xff)<<8)|(  43&0xff), (Word16)(( -83&0xff)<<8)|( -82&0xff), (Word16)(( -81&0xff)<<8)|( -80&0xff),
  (Word16)((  45&0xff)<<8)|(  46&0xff), (Word16)(( -79&0xff)<<8)|( -51&0xff), (Word16)(( -50&0xff)<<8)|( -49&0xff), (Word16)((  48&0xff)<<8)|(  55&0xff),
  (Word16)((  49&0xff)<<8)|(  52&0xff), (Word16)((  50&0xff)<<8)|(  51&0xff), (Word16)(( -48&0xff)<<8)|( -47&0xff), (Word16)(( -46&0xff)<<8)|( -45&0xff),
  (Word16)((  53&0xff)<<8)|(  54&0xff), (Word16)(( -44&0xff)<<8)|( -43&0xff), (Word16)(( -42&0xff)<<8)|( -41&0xff), (Word16)((  56&0xff)<<8)|(  59&0xff),
  (Word16)((  57&0xff)<<8)|(  58&0xff), (Word16)(( -40&0xff)<<8)|( -39&0xff), (Word16)(( -38&0xff)<<8)|( -37&0xff), (Word16)((  60&0xff)<<8)|(  61&0xff),
  (Word16)(( -36&0xff)<<8)|( -35&0xff), (Word16)(( -34&0xff)<<8)|( -33&0xff)
};

const Word16 sbr_huffBook_EnvLevel11F[62] = {
  (Word16)(( -64&0xff)<<8)|(   1&0xff), (Word16)(( -65&0xff)<<8)|(   2&0xff), (Word16)(( -63&0xff)<<8)|(   3&0xff), (Word16)(( -66&0xff)<<8)|(   4&0xff),
  (Word16)(( -62&0xff)<<8)|(   5&0xff), (Word16)(( -67&0xff)<<8)|(   6&0xff), (Word16)((   7&0xff)<<8)|(   8&0xff), (Word16)(( -61&0xff)<<8)|( -68&0xff),
  (Word16)((   9&0xff)<<8)|(  10&0xff), (Word16)(( -60&0xff)<<8)|( -69&0xff), (Word16)((  11&0xff)<<8)|(  12&0xff), (Word16)(( -59&0xff)<<8)|( -70&0xff),
  (Word16)((  13&0xff)<<8)|(  14&0xff), (Word16)(( -58&0xff)<<8)|( -71&0xff), (Word16)((  15&0xff)<<8)|(  16&0xff), (Word16)(( -57&0xff)<<8)|( -72&0xff),
  (Word16)((  17&0xff)<<8)|(  19&0xff), (Word16)(( -56&0xff)<<8)|(  18&0xff), (Word16)(( -55&0xff)<<8)|( -73&0xff), (Word16)((  20&0xff)<<8)|(  24&0xff),
  (Word16)((  21&0xff)<<8)|(  22&0xff), (Word16)(( -74&0xff)<<8)|( -54&0xff), (Word16)(( -53&0xff)<<8)|(  23&0xff), (Word16)(( -75&0xff)<<8)|( -76&0xff),
  (Word16)((  25&0xff)<<8)|(  30&0xff), (Word16)((  26&0xff)<<8)|(  27&0xff), (Word16)(( -52&0xff)<<8)|( -51&0xff), (Word16)((  28&0xff)<<8)|(  29&0xff),
  (Word16)(( -77&0xff)<<8)|( -79&0xff), (Word16)(( -50&0xff)<<8)|( -49&0xff), (Word16)((  31&0xff)<<8)|(  39&0xff), (Word16)((  32&0xff)<<8)|(  35&0xff),
  (Word16)((  33&0xff)<<8)|(  34&0xff), (Word16)(( -78&0xff)<<8)|( -46&0xff), (Word16)(( -82&0xff)<<8)|( -88&0xff), (Word16)((  36&0xff)<<8)|(  37&0xff),
  (Word16)(( -83&0xff)<<8)|( -48&0xff), (Word16)(( -47&0xff)<<8)|(  38&0xff), (Word16)(( -86&0xff)<<8)|( -85&0xff), (Word16)((  40&0xff)<<8)|(  47&0xff),
  (Word16)((  41&0xff)<<8)|(  44&0xff), (Word16)((  42&0xff)<<8)|(  43&0xff), (Word16)(( -80&0xff)<<8)|( -44&0xff), (Word16)(( -43&0xff)<<8)|( -42&0xff),
  (Word16)((  45&0xff)<<8)|(  46&0xff), (Word16)(( -39&0xff)<<8)|( -87&0xff), (Word16)(( -84&0xff)<<8)|( -40&0xff), (Word16)((  48&0xff)<<8)|(  55&0xff),
  (Word16)((  49&0xff)<<8)|(  52&0xff), (Word16)((  50&0xff)<<8)|(  51&0xff), (Word16)(( -95&0xff)<<8)|( -94&0xff), (Word16)(( -93&0xff)<<8)|( -92&0xff),
  (Word16)((  53&0xff)<<8)|(  54&0xff), (Word16)(( -91&0xff)<<8)|( -90&0xff), (Word16)(( -89&0xff)<<8)|( -81&0xff), (Word16)((  56&0xff)<<8)|(  59&0xff),
  (Word16)((  57&0xff)<<8)|(  58&0xff), (Word16)(( -45&0xff)<<8)|( -41&0xff), (Word16)(( -38&0xff)<<8)|( -37&0xff), (Word16)((  60&0xff)<<8)|(  61&0xff),
  (Word16)(( -36&0xff)<<8)|( -35&0xff), (Word16)(( -34&0xff)<<8)|( -33&0xff)
};

const Word16 sbr_huffBook_EnvBalance11T[24] = {
  (Word16)(( -64&0xff)<<8)|(   1&0xff), (Word16)(( -63&0xff)<<8)|(   2&0xff), (Word16)(( -65&0xff)<<8)|(   3&0xff), (Word16)(( -66&0xff)<<8)|(   4&0xff),
  (Word16)(( -62&0xff)<<8)|(   5&0xff), (Word16)(( -61&0xff)<<8)|(   6&0xff), (Word16)(( -67&0xff)<<8)|(   7&0xff), (Word16)(( -68&0xff)<<8)|(   8&0xff),
  (Word16)(( -60&0xff)<<8)|(   9&0xff), (Word16)((  10&0xff)<<8)|(  16&0xff), (Word16)((  11&0xff)<<8)|(  13&0xff), (Word16)(( -69&0xff)<<8)|(  12&0xff),
  (Word16)(( -76&0xff)<<8)|( -75&0xff), (Word16)((  14&0xff)<<8)|(  15&0xff), (Word16)(( -74&0xff)<<8)|( -73&0xff), (Word16)(( -72&0xff)<<8)|( -71&0xff),
  (Word16)((  17&0xff)<<8)|(  20&0xff), (Word16)((  18&0xff)<<8)|(  19&0xff), (Word16)(( -70&0xff)<<8)|( -59&0xff), (Word16)(( -58&0xff)<<8)|( -57&0xff),
  (Word16)((  21&0xff)<<8)|(  22&0xff), (Word16)(( -56&0xff)<<8)|( -55&0xff), (Word16)(( -54&0xff)<<8)|(  23&0xff), (Word16)(( -53&0xff)<<8)|( -52&0xff)
};

const Word16 sbr_huffBook_EnvBalance11F[24] = {
  (Word16)(( -64&0xff)<<8)|(   1&0xff), (Word16)(( -65&0xff)<<8)|(   2&0xff), (Word16)(( -63&0xff)<<8)|(   3&0xff), (Word16)(( -66&0xff)<<8)|(   4&0xff),
  (Word16)(( -62&0xff)<<8)|(   5&0xff), (Word16)(( -61&0xff)<<8)|(   6&0xff), (Word16)(( -67&0xff)<<8)|(   7&0xff), (Word16)(( -68&0xff)<<8)|(   8&0xff),
  (Word16)(( -60&0xff)<<8)|(   9&0xff), (Word16)((  10&0xff)<<8)|(  13&0xff), (Word16)(( -69&0xff)<<8)|(  11&0xff), (Word16)(( -59&0xff)<<8)|(  12&0xff),
  (Word16)(( -58&0xff)<<8)|( -76&0xff), (Word16)((  14&0xff)<<8)|(  17&0xff), (Word16)((  15&0xff)<<8)|(  16&0xff), (Word16)(( -75&0xff)<<8)|( -74&0xff),
  (Word16)(( -73&0xff)<<8)|( -72&0xff), (Word16)((  18&0xff)<<8)|(  21&0xff), (Word16)((  19&0xff)<<8)|(  20&0xff), (Word16)(( -71&0xff)<<8)|( -70&0xff),
  (Word16)(( -57&0xff)<<8)|( -56&0xff), (Word16)((  22&0xff)<<8)|(  23&0xff), (Word16)(( -55&0xff)<<8)|( -54&0xff), (Word16)(( -53&0xff)<<8)|( -52&0xff)
};

const Word16 sbr_huffBook_NoiseLevel11T[62] = {
  (Word16)(( -64&0xff)<<8)|(   1&0xff), (Word16)(( -63&0xff)<<8)|(   2&0xff), (Word16)(( -65&0xff)<<8)|(   3&0xff), (Word16)(( -66&0xff)<<8)|(   4&0xff),
  (Word16)(( -62&0xff)<<8)|(   5&0xff), (Word16)(( -67&0xff)<<8)|(   6&0xff), (Word16)((   7&0xff)<<8)|(   8&0xff), (Word16)(( -61&0xff)<<8)|( -68&0xff),
  (Word16)((   9&0xff)<<8)|(  30&0xff), (Word16)((  10&0xff)<<8)|(  15&0xff), (Word16)(( -60&0xff)<<8)|(  11&0xff), (Word16)(( -69&0xff)<<8)|(  12&0xff),
  (Word16)((  13&0xff)<<8)|(  14&0xff), (Word16)(( -59&0xff)<<8)|( -53&0xff), (Word16)(( -95&0xff)<<8)|( -94&0xff), (Word16)((  16&0xff)<<8)|(  23&0xff),
  (Word16)((  17&0xff)<<8)|(  20&0xff), (Word16)((  18&0xff)<<8)|(  19&0xff), (Word16)(( -93&0xff)<<8)|( -92&0xff), (Word16)(( -91&0xff)<<8)|( -90&0xff),
  (Word16)((  21&0xff)<<8)|(  22&0xff), (Word16)(( -89&0xff)<<8)|( -88&0xff), (Word16)(( -87&0xff)<<8)|( -86&0xff), (Word16)((  24&0xff)<<8)|(  27&0xff),
  (Word16)((  25&0xff)<<8)|(  26&0xff), (Word16)(( -85&0xff)<<8)|( -84&0xff), (Word16)(( -83&0xff)<<8)|( -82&0xff), (Word16)((  28&0xff)<<8)|(  29&0xff),
  (Word16)(( -81&0xff)<<8)|( -80&0xff), (Word16)(( -79&0xff)<<8)|( -78&0xff), (Word16)((  31&0xff)<<8)|(  46&0xff), (Word16)((  32&0xff)<<8)|(  39&0xff),
  (Word16)((  33&0xff)<<8)|(  36&0xff), (Word16)((  34&0xff)<<8)|(  35&0xff), (Word16)(( -77&0xff)<<8)|( -76&0xff), (Word16)(( -75&0xff)<<8)|( -74&0xff),
  (Word16)((  37&0xff)<<8)|(  38&0xff), (Word16)(( -73&0xff)<<8)|( -72&0xff), (Word16)(( -71&0xff)<<8)|( -70&0xff), (Word16)((  40&0xff)<<8)|(  43&0xff),
  (Word16)((  41&0xff)<<8)|(  42&0xff), (Word16)(( -58&0xff)<<8)|( -57&0xff), (Word16)(( -56&0xff)<<8)|( -55&0xff), (Word16)((  44&0xff)<<8)|(  45&0xff),
  (Word16)(( -54&0xff)<<8)|( -52&0xff), (Word16)(( -51&0xff)<<8)|( -50&0xff), (Word16)((  47&0xff)<<8)|(  54&0xff), (Word16)((  48&0xff)<<8)|(  51&0xff),
  (Word16)((  49&0xff)<<8)|(  50&0xff), (Word16)(( -49&0xff)<<8)|( -48&0xff), (Word16)(( -47&0xff)<<8)|( -46&0xff), (Word16)((  52&0xff)<<8)|(  53&0xff),
  (Word16)(( -45&0xff)<<8)|( -44&0xff), (Word16)(( -43&0xff)<<8)|( -42&0xff), (Word16)((  55&0xff)<<8)|(  58&0xff), (Word16)((  56&0xff)<<8)|(  57&0xff),
  (Word16)(( -41&0xff)<<8)|( -40&0xff), (Word16)(( -39&0xff)<<8)|( -38&0xff), (Word16)((  59&0xff)<<8)|(  60&0xff), (Word16)(( -37&0xff)<<8)|( -36&0xff),
  (Word16)(( -35&0xff)<<8)|(  61&0xff), (Word16)(( -34&0xff)<<8)|( -33&0xff)
};

const Word16 sbr_huffBook_NoiseBalance11T[24] = {
  (Word16)(( -64&0xff)<<8)|(   1&0xff), (Word16)(( -65&0xff)<<8)|(   2&0xff), (Word16)(( -63&0xff)<<8)|(   3&0xff), (Word16)((   4&0xff)<<8)|(   9&0xff),
  (Word16)(( -66&0xff)<<8)|(   5&0xff), (Word16)(( -62&0xff)<<8)|(   6&0xff), (Word16)((   7&0xff)<<8)|(   8&0xff), (Word16)(( -76&0xff)<<8)|( -75&0xff),
  (Word16)(( -74&0xff)<<8)|( -73&0xff), (Word16)((  10&0xff)<<8)|(  17&0xff), (Word16)((  11&0xff)<<8)|(  14&0xff), (Word16)((  12&0xff)<<8)|(  13&0xff),
  (Word16)(( -72&0xff)<<8)|( -71&0xff), (Word16)(( -70&0xff)<<8)|( -69&0xff), (Word16)((  15&0xff)<<8)|(  16&0xff), (Word16)(( -68&0xff)<<8)|( -67&0xff),
  (Word16)(( -61&0xff)<<8)|( -60&0xff), (Word16)((  18&0xff)<<8)|(  21&0xff), (Word16)((  19&0xff)<<8)|(  20&0xff), (Word16)(( -59&0xff)<<8)|( -58&0xff),
  (Word16)(( -57&0xff)<<8)|( -56&0xff), (Word16)((  22&0xff)<<8)|(  23&0xff), (Word16)(( -55&0xff)<<8)|( -54&0xff), (Word16)(( -53&0xff)<<8)|( -52&0xff)
};


#ifndef MONO_ONLY


const Word16 aRevLinkDecaySer[NO_SERIAL_ALLPASS_LINKS]= {
  0x5362,
  0x4849,
  0x3ea9
};

const Word16 aRevLinkDelaySer[] = {3,  4,  5};

const Word16 groupBorders[NO_IID_GROUPS + 1] =
{
     4,  5,  0,  1,  2,  3,
     7,  6,
     8,  9,
     3,  4,  5,  6,  7,  8,  9,  11, 14, 18, 23, 35, 64
};

/*! Number of bits to shift down the accumulated energies of the
  uppermost groups which cover several QMF-channels */
const Word16 groupShift[] = { 0, 1, 1, 2, 3, 4 };

const Word16 aGroupToBin[NO_IID_GROUPS] =
{
  0, 1, 2, 3, 1, 0, 5, 4, 6, 7,
  8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
};

const Word16 aHybridToBin[SUBQMF_GROUPS] = 
{
  0, 1, 2, 3, 1, 0, 5, 4, 6, 7
};

const Word16 aDelayToBin[NO_QMF_ALLPASS_CHANNELS] = 
{
  8, 9, 10, 11, 12, 13, 14, 14, 15, 15, 15, 16, 16, 16, 16, 17, 17, 17, 17, 17
};

const Word16 aFractDelayPhaseFactorReQmf[NO_QMF_ALLPASS_CHANNELS]=
{
  (Word16)0xcb54,
  (Word16)0x5bec, (Word16)0x72f3, (Word16)0xf1f4, (Word16)0x8389,
  (Word16)0xb9ba, (Word16)0x4cdb, (Word16)0x7a57, (Word16)0x0608,
  (Word16)0x89be, (Word16)0xa9db, (Word16)0x3be5, (Word16)0x7eb9,
  (Word16)0x19f5, (Word16)0x92dd, (Word16)0x9c1b, (Word16)0x2976,
  (Word16)0x7ffc, (Word16)0x2d3f, (Word16)0x9eab
};

const Word16 aFractDelayPhaseFactorImQmf[NO_QMF_ALLPASS_CHANNELS]=
{
  (Word16)0x74a9,
  (Word16)0x5914, (Word16)0xc7b0, (Word16)0x80c6, (Word16)0xe21e,
  (Word16)0x6afc, (Word16)0x665c, (Word16)0xda5d, (Word16)0x8024,
  (Word16)0xcf04, (Word16)0x5eac, (Word16)0x711f, (Word16)0xedf7,
  (Word16)0x82a9, (Word16)0xbd1f, (Word16)0x5008, (Word16)0x7919,
  (Word16)0x0203, (Word16)0x8843, (Word16)0xacdf
};

const Word16 aFractDelayPhaseFactorReSubQmf[SUBQMF_GROUPS]=
{
   (Word16)0x7e80, (Word16)0x72ba, (Word16)0x5c45, (Word16)0x3d39,
   (Word16)0x72ba, (Word16)0x7e80,
   (Word16)0xba91, (Word16)0x0506, (Word16)0x895d, (Word16)0x834e
};

const Word16 aFractDelayPhaseFactorImSubQmf[SUBQMF_GROUPS]=
{
  (Word16)0xec79, (Word16)0xc73d, (Word16)0xa749, (Word16)0x8f97,
  (Word16)0x38c3, (Word16)0x1387,
  (Word16)0x9478, (Word16)0x8019, (Word16)0xcff2, (Word16)0x1ce7
};

const Word16 aFractDelayPhaseFactorSerReQmf0[NO_QMF_ALLPASS_CHANNELS]=
{
  (Word16)0x0203,
  (Word16)0x7d57, (Word16)0x34ac, (Word16)0x99a4, (Word16)0x9eab,
  (Word16)0x3be5, (Word16)0x7b77, (Word16)0xf9f8, (Word16)0x81e8,
  (Word16)0xcf04, (Word16)0x68b9, (Word16)0x5eac, (Word16)0xc095,
  (Word16)0x85a9, (Word16)0x0a0b, (Word16)0x7eb9, (Word16)0x2d3f,
  (Word16)0x9504, (Word16)0xa414, (Word16)0x42e1
};

const Word16 aFractDelayPhaseFactorSerReQmf1[NO_QMF_ALLPASS_CHANNELS]=
{
  (Word16)0xcf04,
  (Word16)0xcf04, (Word16)0x7642, (Word16)0x89be, (Word16)0x30fc,
  (Word16)0x30fc, (Word16)0x89be, (Word16)0x7642, (Word16)0xcf04,
  (Word16)0xcf04, (Word16)0x7642, (Word16)0x89be, (Word16)0x30fc,
  (Word16)0x30fc, (Word16)0x89be, (Word16)0x7642, (Word16)0xcf04,
  (Word16)0xcf04, (Word16)0x7642, (Word16)0x89be
};

const Word16 aFractDelayPhaseFactorSerReQmf2[NO_QMF_ALLPASS_CHANNELS]=
{
  (Word16)0x9bfb,
  (Word16)0x1894, (Word16)0x7abf, (Word16)0x58ef, (Word16)0xd77e,
  (Word16)0x819c, (Word16)0xb3a1, (Word16)0x37c5, (Word16)0x7ff1,
  (Word16)0x3e8b, (Word16)0xb9e5, (Word16)0x80a0, (Word16)0xd052,
  (Word16)0x5348, (Word16)0x7cb2, (Word16)0x2007, (Word16)0xa0ec,
  (Word16)0x880d, (Word16)0xf028, (Word16)0x694c
};

const Word16 aFractDelayPhaseFactorSerImQmf0[NO_QMF_ALLPASS_CHANNELS]=
{
  (Word16)0x7ffc,
  (Word16)0x19f5, (Word16)0x8b57, (Word16)0xb325, (Word16)0x5321,
  (Word16)0x711f, (Word16)0xde39, (Word16)0x8024, (Word16)0xe9fe,
  (Word16)0x7642, (Word16)0x499a, (Word16)0xa9db, (Word16)0x90d1,
  (Word16)0x25a3, (Word16)0x7f9b, (Word16)0x1209, (Word16)0x8843,
  (Word16)0xb9ba, (Word16)0x5914, (Word16)0x6d23
};

const Word16 aFractDelayPhaseFactorSerImQmf1[NO_QMF_ALLPASS_CHANNELS]=
{
  (Word16)0x89be,
  (Word16)0x7642, (Word16)0xcf04, (Word16)0xcf04, (Word16)0x7642,
  (Word16)0x89be, (Word16)0x30fc, (Word16)0x30fc, (Word16)0x89be,
  (Word16)0x7642, (Word16)0xcf04, (Word16)0xcf04, (Word16)0x7642,
  (Word16)0x89be, (Word16)0x30fc, (Word16)0x30fc, (Word16)0x89be,
  (Word16)0x7642, (Word16)0xcf04, (Word16)0xcf04
};

const Word16 aFractDelayPhaseFactorSerImQmf2[NO_QMF_ALLPASS_CHANNELS]=
{
  (Word16)0x4fe0,
  (Word16)0x7d9e, (Word16)0x244a, (Word16)0xa3f1, (Word16)0x8694,
  (Word16)0xebc7, (Word16)0x66b8, (Word16)0x7336, (Word16)0x03d2,
  (Word16)0x9052, (Word16)0x94e8, (Word16)0x0ca5, (Word16)0x76ca,
  (Word16)0x6134, (Word16)0xe319, (Word16)0x8412, (Word16)0xaa4d,
  (Word16)0x2cae, (Word16)0x7f04, (Word16)0x48c7
};

const Word16 aFractDelayPhaseFactorSerReSubQmf0[SUBQMF_GROUPS]=
{
   (Word16)0x7e2e, (Word16)0x6fed, (Word16)0x5506, (Word16)0x3085,
   (Word16)0x6fed, (Word16)0x7e2e,
   (Word16)0xa4c8, (Word16)0xf0f5, (Word16)0x80ab, (Word16)0x9478
};

const Word16 aFractDelayPhaseFactorSerReSubQmf1[SUBQMF_GROUPS]=
{
   (Word16)0x7a7d, (Word16)0x5134, (Word16)0x0c8c, (Word16)0xc3a9,
   (Word16)0x5134, (Word16)0x7a7d,
   (Word16)0xb8e3, (Word16)0x8276, (Word16)0x471d, (Word16)0x7d8a
};

const Word16 aFractDelayPhaseFactorSerReSubQmf2[SUBQMF_GROUPS]=
{
   (Word16)0x7ed0, (Word16)0x7574, (Word16)0x636c, (Word16)0x4a0d,
   (Word16)0x7574, (Word16)0x7ed0,
   (Word16)0xd5af, (Word16)0x1a73, (Word16)0x9d2f, (Word16)0x8152
};

const Word16 aFractDelayPhaseFactorSerImSubQmf0[SUBQMF_GROUPS]=
{
  (Word16)0xea7d, (Word16)0xc1e5, (Word16)0xa052, (Word16)0x898d,
  (Word16)0x3e1b, (Word16)0x1583,
  (Word16)0xa634, (Word16)0x80e3, (Word16)0xf2f4, (Word16)0x456f
};

const Word16 aFractDelayPhaseFactorSerImSubQmf1[SUBQMF_GROUPS]=
{
  (Word16)0xdad8, (Word16)0x9d0e, (Word16)0x809e, (Word16)0x8f1d,
  (Word16)0x62f2, (Word16)0x2528,
  (Word16)0x6a6e, (Word16)0xe707, (Word16)0x6a6e, (Word16)0xe707
};

const Word16 aFractDelayPhaseFactorSerImSubQmf2[SUBQMF_GROUPS]=
{
  (Word16)0xee9d, (Word16)0xcd1e, (Word16)0xaf62, (Word16)0x9799,
  (Word16)0x32e2, (Word16)0x1163,
  (Word16)0x8732, (Word16)0x82c3, (Word16)0xaea4, (Word16)0xedab
};

const Word16 *aaFractDelayPhaseFactorSerReQmf[3]=
{
  aFractDelayPhaseFactorSerReQmf0,
  aFractDelayPhaseFactorSerReQmf1,
  aFractDelayPhaseFactorSerReQmf2
};

const Word16 *aaFractDelayPhaseFactorSerImQmf[3]=
{
  aFractDelayPhaseFactorSerImQmf0,
  aFractDelayPhaseFactorSerImQmf1,
  aFractDelayPhaseFactorSerImQmf2
};

const Word16 *aaFractDelayPhaseFactorSerReSubQmf[3]=
{
  aFractDelayPhaseFactorSerReSubQmf0,
  aFractDelayPhaseFactorSerReSubQmf1,
  aFractDelayPhaseFactorSerReSubQmf2
};

const Word16 *aaFractDelayPhaseFactorSerImSubQmf[3]=
{
  aFractDelayPhaseFactorSerImSubQmf0,
  aFractDelayPhaseFactorSerImSubQmf1,
  aFractDelayPhaseFactorSerImSubQmf2
};

const Word16 scaleFactors[NO_IID_LEVELS]=
{
  (Word16)0x5a5e, (Word16)0x59cd, (Word16)0x58c3, (Word16)0x564c,
  (Word16)0x52a4, (Word16)0x4c8c, (Word16)0x46df, (Word16)0x4000,
  (Word16)0x384c, (Word16)0x304c, (Word16)0x24ea, (Word16)0x1b4a,
  (Word16)0x11b6, (Word16)0x0b4e, (Word16)0x0515
};

const Word16 scaleFactorsFine[NO_IID_LEVELS_FINE] =
{
  (Word16)0x5a82, /* -15 */
  (Word16)0x5a82, /* -14 */
  (Word16)0x5a81, /* -13 */
  (Word16)0x5a7f, /* -12 */
  (Word16)0x5a77, /* -11 */
  (Word16)0x5a5e, /* -10 */
  (Word16)0x5a3a, /*  -9 */
  (Word16)0x59f2, /*  -8 */
  (Word16)0x5965, /*  -7 */
  (Word16)0x5853, /*  -6 */
  (Word16)0x564c, /*  -5 */
  (Word16)0x5417, /*  -4 */
  (Word16)0x50ea, /*  -3 */
  (Word16)0x4c8c, /*  -2 */
  (Word16)0x46df, /*  -1 */
  (Word16)0x4000, /*   0 */
  (Word16)0x384c, /*   1 */
  (Word16)0x304c, /*   2 */
  (Word16)0x288e, /*   3 */
  (Word16)0x217a, /*   4 */
  (Word16)0x1b4a, /*   5 */
  (Word16)0x13c6, /*   6 */
  (Word16)0x0e2b, /*   7 */
  (Word16)0x0a18, /*   8 */
  (Word16)0x072b, /*   9 */
  (Word16)0x0515, /*  10 */
  (Word16)0x02dc, /*  11 */
  (Word16)0x019c, /*  12 */
  (Word16)0x00e8, /*  13 */
  (Word16)0x0082, /*  14 */
  (Word16)0x0049  /*  15 */
};

const Word16 alphas[NO_ICC_LEVELS]=
{
  (Word16)0x0000, (Word16)0x0b6b, (Word16)0x1248, (Word16)0x1da3,
  (Word16)0x2638, (Word16)0x3244, (Word16)0x466b, (Word16)0x6488
};

/* IID & ICC Huffman codebooks */
const Word16 aBookPsIidTimeDecode[28] = {
  (Word16)(( -64&0xff)<<8)|(   1&0xff), (Word16)(( -65&0xff)<<8)|(   2&0xff), (Word16)(( -63&0xff)<<8)|(   3&0xff), (Word16)(( -66&0xff)<<8)|(   4&0xff),
  (Word16)(( -62&0xff)<<8)|(   5&0xff), (Word16)(( -67&0xff)<<8)|(   6&0xff), (Word16)(( -61&0xff)<<8)|(   7&0xff), (Word16)(( -68&0xff)<<8)|(   8&0xff),
  (Word16)(( -60&0xff)<<8)|(   9&0xff), (Word16)(( -69&0xff)<<8)|(  10&0xff), (Word16)(( -59&0xff)<<8)|(  11&0xff), (Word16)(( -70&0xff)<<8)|(  12&0xff),
  (Word16)(( -58&0xff)<<8)|(  13&0xff), (Word16)(( -57&0xff)<<8)|(  14&0xff), (Word16)(( -71&0xff)<<8)|(  15&0xff), (Word16)((  16&0xff)<<8)|(  17&0xff),
  (Word16)(( -56&0xff)<<8)|( -72&0xff), (Word16)((  18&0xff)<<8)|(  21&0xff), (Word16)((  19&0xff)<<8)|(  20&0xff), (Word16)(( -55&0xff)<<8)|( -78&0xff),
  (Word16)(( -77&0xff)<<8)|( -76&0xff), (Word16)((  22&0xff)<<8)|(  25&0xff), (Word16)((  23&0xff)<<8)|(  24&0xff), (Word16)(( -75&0xff)<<8)|( -74&0xff),
  (Word16)(( -73&0xff)<<8)|( -54&0xff), (Word16)((  26&0xff)<<8)|(  27&0xff), (Word16)(( -53&0xff)<<8)|( -52&0xff), (Word16)(( -51&0xff)<<8)|( -50&0xff)
};

const Word16 aBookPsIidFreqDecode[28] = {
  (Word16)(( -64&0xff)<<8)|(   1&0xff), (Word16)((   2&0xff)<<8)|(   3&0xff), (Word16)(( -63&0xff)<<8)|( -65&0xff), (Word16)((   4&0xff)<<8)|(   5&0xff),
  (Word16)(( -62&0xff)<<8)|( -66&0xff), (Word16)((   6&0xff)<<8)|(   7&0xff), (Word16)(( -61&0xff)<<8)|( -67&0xff), (Word16)((   8&0xff)<<8)|(   9&0xff),
  (Word16)(( -68&0xff)<<8)|( -60&0xff), (Word16)(( -59&0xff)<<8)|(  10&0xff), (Word16)(( -69&0xff)<<8)|(  11&0xff), (Word16)(( -58&0xff)<<8)|(  12&0xff),
  (Word16)(( -70&0xff)<<8)|(  13&0xff), (Word16)(( -71&0xff)<<8)|(  14&0xff), (Word16)(( -57&0xff)<<8)|(  15&0xff), (Word16)((  16&0xff)<<8)|(  17&0xff),
  (Word16)(( -56&0xff)<<8)|( -72&0xff), (Word16)((  18&0xff)<<8)|(  19&0xff), (Word16)(( -55&0xff)<<8)|( -54&0xff), (Word16)((  20&0xff)<<8)|(  21&0xff),
  (Word16)(( -73&0xff)<<8)|( -53&0xff), (Word16)((  22&0xff)<<8)|(  24&0xff), (Word16)(( -74&0xff)<<8)|(  23&0xff), (Word16)(( -75&0xff)<<8)|( -78&0xff),
  (Word16)((  25&0xff)<<8)|(  26&0xff), (Word16)(( -77&0xff)<<8)|( -76&0xff), (Word16)(( -52&0xff)<<8)|(  27&0xff), (Word16)(( -51&0xff)<<8)|( -50&0xff)
};

const Word16 aBookPsIccTimeDecode[14] = {
  (Word16)(( -64&0xff)<<8)|(   1&0xff), (Word16)(( -63&0xff)<<8)|(   2&0xff), (Word16)(( -65&0xff)<<8)|(   3&0xff), (Word16)(( -62&0xff)<<8)|(   4&0xff),
  (Word16)(( -66&0xff)<<8)|(   5&0xff), (Word16)(( -61&0xff)<<8)|(   6&0xff), (Word16)(( -67&0xff)<<8)|(   7&0xff), (Word16)(( -60&0xff)<<8)|(   8&0xff),
  (Word16)(( -68&0xff)<<8)|(   9&0xff), (Word16)(( -59&0xff)<<8)|(  10&0xff), (Word16)(( -69&0xff)<<8)|(  11&0xff), (Word16)(( -58&0xff)<<8)|(  12&0xff),
  (Word16)(( -70&0xff)<<8)|(  13&0xff), (Word16)(( -71&0xff)<<8)|( -57&0xff)
};

const Word16 aBookPsIccFreqDecode[14] = {
  (Word16)(( -64&0xff)<<8)|(   1&0xff), (Word16)(( -63&0xff)<<8)|(   2&0xff), (Word16)(( -65&0xff)<<8)|(   3&0xff), (Word16)(( -62&0xff)<<8)|(   4&0xff),
  (Word16)(( -66&0xff)<<8)|(   5&0xff), (Word16)(( -61&0xff)<<8)|(   6&0xff), (Word16)(( -67&0xff)<<8)|(   7&0xff), (Word16)(( -60&0xff)<<8)|(   8&0xff),
  (Word16)(( -59&0xff)<<8)|(   9&0xff), (Word16)(( -68&0xff)<<8)|(  10&0xff), (Word16)(( -58&0xff)<<8)|(  11&0xff), (Word16)(( -69&0xff)<<8)|(  12&0xff),
  (Word16)(( -57&0xff)<<8)|(  13&0xff), (Word16)(( -70&0xff)<<8)|( -71&0xff)
};

const Word16 aBookPsIidFineTimeDecode[60] = {
  (Word16)((   1&0xff)<<8)|( -64&0xff), (Word16)(( -63&0xff)<<8)|(   2&0xff), (Word16)((   3&0xff)<<8)|( -65&0xff), (Word16)((   4&0xff)<<8)|(  59&0xff),
  (Word16)((   5&0xff)<<8)|(   7&0xff), (Word16)((   6&0xff)<<8)|( -67&0xff), (Word16)(( -68&0xff)<<8)|( -60&0xff), (Word16)(( -61&0xff)<<8)|(   8&0xff),
  (Word16)((   9&0xff)<<8)|(  11&0xff), (Word16)(( -59&0xff)<<8)|(  10&0xff), (Word16)(( -70&0xff)<<8)|( -58&0xff), (Word16)((  12&0xff)<<8)|(  41&0xff),
  (Word16)((  13&0xff)<<8)|(  20&0xff), (Word16)((  14&0xff)<<8)|( -71&0xff), (Word16)(( -55&0xff)<<8)|(  15&0xff), (Word16)(( -53&0xff)<<8)|(  16&0xff),
  (Word16)((  17&0xff)<<8)|( -77&0xff), (Word16)((  18&0xff)<<8)|(  19&0xff), (Word16)(( -85&0xff)<<8)|( -84&0xff), (Word16)(( -46&0xff)<<8)|( -45&0xff),
  (Word16)(( -57&0xff)<<8)|(  21&0xff), (Word16)((  22&0xff)<<8)|(  40&0xff), (Word16)((  23&0xff)<<8)|(  29&0xff), (Word16)(( -51&0xff)<<8)|(  24&0xff),
  (Word16)((  25&0xff)<<8)|(  26&0xff), (Word16)(( -83&0xff)<<8)|( -82&0xff), (Word16)((  27&0xff)<<8)|(  28&0xff), (Word16)(( -90&0xff)<<8)|( -38&0xff),
  (Word16)(( -92&0xff)<<8)|( -91&0xff), (Word16)((  30&0xff)<<8)|(  37&0xff), (Word16)((  31&0xff)<<8)|(  34&0xff), (Word16)((  32&0xff)<<8)|(  33&0xff),
  (Word16)(( -35&0xff)<<8)|( -34&0xff), (Word16)(( -37&0xff)<<8)|( -36&0xff), (Word16)((  35&0xff)<<8)|(  36&0xff), (Word16)(( -94&0xff)<<8)|( -93&0xff),
  (Word16)(( -89&0xff)<<8)|( -39&0xff), (Word16)((  38&0xff)<<8)|( -79&0xff), (Word16)((  39&0xff)<<8)|( -81&0xff), (Word16)(( -88&0xff)<<8)|( -40&0xff),
  (Word16)(( -74&0xff)<<8)|( -54&0xff), (Word16)((  42&0xff)<<8)|( -69&0xff), (Word16)((  43&0xff)<<8)|(  44&0xff), (Word16)(( -72&0xff)<<8)|( -56&0xff),
  (Word16)((  45&0xff)<<8)|(  52&0xff), (Word16)((  46&0xff)<<8)|(  50&0xff), (Word16)((  47&0xff)<<8)|( -76&0xff), (Word16)(( -49&0xff)<<8)|(  48&0xff),
  (Word16)(( -47&0xff)<<8)|(  49&0xff), (Word16)(( -87&0xff)<<8)|( -41&0xff), (Word16)(( -52&0xff)<<8)|(  51&0xff), (Word16)(( -78&0xff)<<8)|( -50&0xff),
  (Word16)((  53&0xff)<<8)|( -73&0xff), (Word16)((  54&0xff)<<8)|( -75&0xff), (Word16)((  55&0xff)<<8)|(  57&0xff), (Word16)((  56&0xff)<<8)|( -80&0xff),
  (Word16)(( -86&0xff)<<8)|( -42&0xff), (Word16)(( -48&0xff)<<8)|(  58&0xff), (Word16)(( -44&0xff)<<8)|( -43&0xff), (Word16)(( -66&0xff)<<8)|( -62&0xff)
};

const Word16 aBookPsIidFineFreqDecode[60] = {
  (Word16)((   1&0xff)<<8)|( -64&0xff), (Word16)((   2&0xff)<<8)|(   4&0xff), (Word16)((   3&0xff)<<8)|( -65&0xff), (Word16)(( -66&0xff)<<8)|( -62&0xff),
  (Word16)(( -63&0xff)<<8)|(   5&0xff), (Word16)((   6&0xff)<<8)|(   7&0xff), (Word16)(( -67&0xff)<<8)|( -61&0xff), (Word16)((   8&0xff)<<8)|(   9&0xff),
  (Word16)(( -68&0xff)<<8)|( -60&0xff), (Word16)((  10&0xff)<<8)|(  11&0xff), (Word16)(( -69&0xff)<<8)|( -59&0xff), (Word16)((  12&0xff)<<8)|(  13&0xff),
  (Word16)(( -70&0xff)<<8)|( -58&0xff), (Word16)((  14&0xff)<<8)|(  18&0xff), (Word16)(( -57&0xff)<<8)|(  15&0xff), (Word16)((  16&0xff)<<8)|( -72&0xff),
  (Word16)(( -54&0xff)<<8)|(  17&0xff), (Word16)(( -75&0xff)<<8)|( -53&0xff), (Word16)((  19&0xff)<<8)|(  37&0xff), (Word16)(( -56&0xff)<<8)|(  20&0xff),
  (Word16)((  21&0xff)<<8)|( -73&0xff), (Word16)((  22&0xff)<<8)|(  29&0xff), (Word16)((  23&0xff)<<8)|( -76&0xff), (Word16)((  24&0xff)<<8)|( -78&0xff),
  (Word16)((  25&0xff)<<8)|(  28&0xff), (Word16)((  26&0xff)<<8)|(  27&0xff), (Word16)(( -85&0xff)<<8)|( -43&0xff), (Word16)(( -83&0xff)<<8)|( -45&0xff),
  (Word16)(( -81&0xff)<<8)|( -47&0xff), (Word16)(( -52&0xff)<<8)|(  30&0xff), (Word16)(( -50&0xff)<<8)|(  31&0xff), (Word16)((  32&0xff)<<8)|( -79&0xff),
  (Word16)((  33&0xff)<<8)|(  34&0xff), (Word16)(( -82&0xff)<<8)|( -46&0xff), (Word16)((  35&0xff)<<8)|(  36&0xff), (Word16)(( -90&0xff)<<8)|( -89&0xff),
  (Word16)(( -92&0xff)<<8)|( -91&0xff), (Word16)((  38&0xff)<<8)|( -71&0xff), (Word16)(( -55&0xff)<<8)|(  39&0xff), (Word16)((  40&0xff)<<8)|( -74&0xff),
  (Word16)((  41&0xff)<<8)|(  50&0xff), (Word16)((  42&0xff)<<8)|( -77&0xff), (Word16)(( -49&0xff)<<8)|(  43&0xff), (Word16)((  44&0xff)<<8)|(  47&0xff),
  (Word16)((  45&0xff)<<8)|(  46&0xff), (Word16)(( -86&0xff)<<8)|( -42&0xff), (Word16)(( -88&0xff)<<8)|( -87&0xff), (Word16)((  48&0xff)<<8)|(  49&0xff),
  (Word16)(( -39&0xff)<<8)|( -38&0xff), (Word16)(( -41&0xff)<<8)|( -40&0xff), (Word16)(( -51&0xff)<<8)|(  51&0xff), (Word16)((  52&0xff)<<8)|(  59&0xff),
  (Word16)((  53&0xff)<<8)|(  56&0xff), (Word16)((  54&0xff)<<8)|(  55&0xff), (Word16)(( -35&0xff)<<8)|( -34&0xff), (Word16)(( -37&0xff)<<8)|( -36&0xff),
  (Word16)((  57&0xff)<<8)|(  58&0xff), (Word16)(( -94&0xff)<<8)|( -93&0xff), (Word16)(( -84&0xff)<<8)|( -44&0xff), (Word16)(( -80&0xff)<<8)|( -48&0xff)
};

#endif /* MONO_ONLY */
