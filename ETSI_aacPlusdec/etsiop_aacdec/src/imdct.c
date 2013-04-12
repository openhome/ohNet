/*
   IMDCT transform
*/

#include "imdct.h"
#include "aac_rom.h"
#include "intrinsics.h"
#include "count.h"
#include "basic_op.h"
#include "oper_32b.h"

extern const Word16 trigData[513];

/* bitreversal */

static void shuffle512 (Word32 x [])
{
  Word16 i;

  static const UWord16 permutationTable [480] =
  {
      2,  512,    4,  256,    6,  768,    8,  128,   10,  640,   12,  384,   14,  896,   16,   64,
     18,  576,   20,  320,   22,  832,   24,  192,   26,  704,   28,  448,   30,  960,   34,  544,
     36,  288,   38,  800,   40,  160,   42,  672,   44,  416,   46,  928,   48,   96,   50,  608,
     52,  352,   54,  864,   56,  224,   58,  736,   60,  480,   62,  992,   66,  528,   68,  272,
     70,  784,   72,  144,   74,  656,   76,  400,   78,  912,   82,  592,   84,  336,   86,  848,
     88,  208,   90,  720,   92,  464,   94,  976,   98,  560,  100,  304,  102,  816,  104,  176,
    106,  688,  108,  432,  110,  944,  114,  624,  116,  368,  118,  880,  120,  240,  122,  752,
    124,  496,  126, 1008,  130,  520,  132,  264,  134,  776,  138,  648,  140,  392,  142,  904,
    146,  584,  148,  328,  150,  840,  152,  200,  154,  712,  156,  456,  158,  968,  162,  552,
    164,  296,  166,  808,  170,  680,  172,  424,  174,  936,  178,  616,  180,  360,  182,  872,
    184,  232,  186,  744,  188,  488,  190, 1000,  194,  536,  196,  280,  198,  792,  202,  664,
    204,  408,  206,  920,  210,  600,  212,  344,  214,  856,  218,  728,  220,  472,  222,  984,
    226,  568,  228,  312,  230,  824,  234,  696,  236,  440,  238,  952,  242,  632,  244,  376,
    246,  888,  250,  760,  252,  504,  254, 1016,  258,  516,  262,  772,  266,  644,  268,  388,
    270,  900,  274,  580,  276,  324,  278,  836,  282,  708,  284,  452,  286,  964,  290,  548,
    294,  804,  298,  676,  300,  420,  302,  932,  306,  612,  308,  356,  310,  868,  314,  740,
    316,  484,  318,  996,  322,  532,  326,  788,  330,  660,  332,  404,  334,  916,  338,  596,
    342,  852,  346,  724,  348,  468,  350,  980,  354,  564,  358,  820,  362,  692,  364,  436,
    366,  948,  370,  628,  374,  884,  378,  756,  380,  500,  382, 1012,  386,  524,  390,  780,
    394,  652,  398,  908,  402,  588,  406,  844,  410,  716,  412,  460,  414,  972,  418,  556,
    422,  812,  426,  684,  430,  940,  434,  620,  438,  876,  442,  748,  444,  492,  446, 1004,
    450,  540,  454,  796,  458,  668,  462,  924,  466,  604,  470,  860,  474,  732,  478,  988,
    482,  572,  486,  828,  490,  700,  494,  956,  498,  636,  502,  892,  506,  764,  510, 1020,
    518,  770,  522,  642,  526,  898,  530,  578,  534,  834,  538,  706,  542,  962,  550,  802,
    554,  674,  558,  930,  562,  610,  566,  866,  570,  738,  574,  994,  582,  786,  586,  658,
    590,  914,  598,  850,  602,  722,  606,  978,  614,  818,  618,  690,  622,  946,  630,  882,
    634,  754,  638, 1010,  646,  778,  654,  906,  662,  842,  666,  714,  670,  970,  678,  810,
    686,  938,  694,  874,  698,  746,  702, 1002,  710,  794,  718,  922,  726,  858,  734,  986,
    742,  826,  750,  954,  758,  890,  766, 1018,  782,  902,  790,  838,  798,  966,  814,  934,
    822,  870,  830,  998,  846,  918,  862,  982,  878,  950,  894, 1014,  926,  974,  958, 1006
  } ;

  for (i = 0 ; i < 480 ; i += 2)
  {                                                                   
    Word16 m, j;
    Word32 tmp;

    m= permutationTable [i];        move16();
    j = permutationTable [i+1];     move16();

    tmp = x [m] ;                   move32();
    x [m] = x [j] ;                 move32();
    x [j] = tmp ;                   move32();

    tmp = x [m+1] ;                 move32();
    x [m+1] = x [j+1] ;             move32();
    x [j+1] = tmp ;                 move32();
  }
}

static void shuffle64 (Word32 x [])
{
  Word16 i;

  static const UWord16 permutationTable [56] =
  {
      2,  64,   4,  32,   6,  96,   8,  16,
     10,  80,  12,  48,  14, 112,  18,  72,
     20,  40,  22, 104,  26,  88,  28,  56,
     30, 120,  34,  68,  38, 100,  42,  84,
     44,  52,  46, 116,  50,  76,  54, 108,
     58,  92,  62, 124,  70,  98,  74,  82,
     78, 114,  86, 106,  94, 122, 110, 118
  } ;

  for (i = 0 ; i < 56 ; i += 2)
  {                               
    Word16 m, j;
    Word32 tmp;
    m = permutationTable [i];           move16();
    j = permutationTable [i+1] ;        move16();

    tmp = x [m] ;                       move32();
    x [m] = x [j] ;                     move32();
    x [j] = tmp ;                       move32();

    tmp = x [m+1] ;                     move32();
    x [m+1] = x [j+1] ;                 move32();
    x [j+1] = tmp ;                     move32();
  }
}

static void preTwiddle (Word32 x [], Word16 m, const Word16 sineWindow [])
{
  Word16 i, j;
  Word16 shift;
  Word16 count = shr(m, 1);
  shift = 9;                                                                               move16();

                                                                                           test();
  if(sub(m,128) == 0) {
    shift = 6;                                                                             move16();
  }

  j = 0; move16();
  for (i = 0; i < count ; i+=2, j += 4)
  {                                                             
    Word32 xtmp = x[i+1];                                                                  move32();

    x[i+1] = L_sub(L_shr(fixmul_32x16b(x[m-i-1], sineWindow[m-1-i]), shift),
                   L_shr(fixmul_32x16b(x[i], sineWindow[i]), shift));
    x[i] = L_add(L_shr(fixmul_32x16b(x[m-i-1], sineWindow[i]), shift),
                 L_shr(fixmul_32x16b(x[i], sineWindow[m-1-i]), shift));

    x[m-1-i] = L_sub(L_shr(fixmul_32x16b(xtmp, sineWindow[i+1]), shift),
                     L_shr(fixmul_32x16b(x[m-i-2], sineWindow[m-i-2]), shift));
    x[m-2-i] = L_add(L_shr(fixmul_32x16b(xtmp, sineWindow[m-i-2]), shift),
                     L_shr(fixmul_32x16b(x[m-i-2], sineWindow[i+1]), shift));
  }

}

static void postTwiddle (Word32 x [], Word16 m, Word16 step, const Word16 sineTable [], Word16 tableSize)
{
  Word16 i, j, count;

  const Word16 *sinPtr = sineTable ;
  const Word16 *cosPtr = sineTable + tableSize ;
                                                                                            move16(); move16();
  count = shr(m, 1);
                                                                                            test();
  if(sub(step,8) == 0)
  {
    j = 0; move16();
    for (i = 0; i < count  ; i+=2, j+= 4)
    {                                                                               
      Word32 xtmp = x[m-1-i];                                   move32();

      x [m-1-i] = L_sub(L_shr(fixmul_32x16b(x[i], *sinPtr), 1),
                        L_shr(fixmul_32x16b(x[i+1], *cosPtr), 1));  move32();
      x [i] = L_add(L_shr(fixmul_32x16b(x[i], *cosPtr), 1),
                    L_shr(fixmul_32x16b(x[i+1], *sinPtr), 1));      move32();
            
      sinPtr += 8 ;                                                                                                                                         
      cosPtr -= 8 ;                                                                                                                                         
      x [i+1] = L_sub(L_shr(fixmul_32x16b(x[m-i-2], *cosPtr), 1), 
                      L_shr(fixmul_32x16b(xtmp, *sinPtr), 1));            move32();
      x [m-2-i] = L_add(L_shr(fixmul_32x16b(x[m-i-2], *sinPtr), 1),
                        L_shr(fixmul_32x16b(xtmp, *cosPtr), 1));          move32();
    }
  }
  else
  {
    j = 0; move16();
    for (i = 0; i < count  ; i+=2, j+= 4)
    {                                                                               
      Word32 xtmp = x[m-1-i];                                           move32();

      x [m-1-i] = L_sub(L_shr(fixmul_32x16b(x[i], *sinPtr), 1),
                        L_shr(fixmul_32x16b(x[i+1], *cosPtr), 1));  move32();
      x [i] = L_add(L_shr(fixmul_32x16b(x[i], *cosPtr), 1),
                    L_shr(fixmul_32x16b(x[i+1], *sinPtr), 1));      move32();
 
      sinPtr += 1 ;                                                                                                                                         
      cosPtr -= 1 ;                                                                                                                                         
                                                                                                                                                  
      x [i+1] = L_sub(L_shr(fixmul_32x16b(x[m-i-2], *cosPtr), 1), 
                      L_shr(fixmul_32x16b(xtmp, *sinPtr), 1));            move32();
      x [m-2-i] = L_add(L_shr(fixmul_32x16b(x[m-i-2], *sinPtr), 1),
                        L_shr(fixmul_32x16b(xtmp, *cosPtr), 1));          move32();
    }
  }
}

static void scaledFFT (Word32 x [], Word16 ldn, const Word16 sineTable [], Word16 tableSize)
{
  Word16 ldm, angleStep;

  /* complex-to-complex decimation-in-time radix-2 FFT: */

  /* - expects bitreversed complex input */
  /* - shifts down 1 bit per stage */

  const Word16 n = shl(1, ldn) ;

  Word32 vr, vi, ur, ui ;
  Word16 i, count = shr(n, 3);
  Word16 t1, t2;
  /* stage 1, W = +/-1 */

  t1 = 0;                                 move16(); 
  t2 = 2;                                 move16();
                                      
  for (i = 0 ; i < count; i++)
  {
    ur = x [t1] ;                         move32();
    ui = x [t1+1] ;                       move32();
                                      
    x [t1] = L_add(ur, x [t2]);           move32();
    x [t2] = L_sub(ur, x [t2]);           move32();
    x [t1+1] = L_add(ui , x [t2+1]);      move32();
    x [t2+1] = L_sub(ui, x [t2+1]);       move32();

    ur = x [t1+4] ;                       move32();
    ui = x [t1+5] ;                       move32();

    x [t1+4] = L_add(ur, x [t2+4]);       move32();
    x [t2+4] = L_sub(ur, x [t2+4]);       move32();
    x [t1+5] = L_add(ui, x [t2+5]);       move32();
    x [t2+5] = L_sub(ui, x [t2+5]);       move32();

    ur = x [t1+8] ;                       move32();
    ui = x [t1+9] ;                       move32();

    x [t1+8] = L_add(ur, x [t2+8]);       move32();
    x [t2+8] = L_sub(ur, x [t2+8]);       move32();
    x [t1+9] = L_add(ui, x [t2+9]);       move32();
    x [t2+9] = L_sub(ui, x [t2+9]);       move32();

    ur = x [t1+12] ;                      move32();
    ui = x [t1+13] ;                      move32();

    x [t1+12] = L_add(ur, x [t2+12]);     move32();
    x [t2+12] = L_sub(ur, x [t2+12]);     move32();
    x [t1+13] = L_add(ui, x [t2+13]);     move32();
    x [t2+13] = L_sub(ui, x [t2+13]);     move32();

    t1 = add(t1, 16);
    t2 = add(t2, 16);
  }

  /* stage 2, W = +/-1 */

  t1 = 0;                                 move16();
  t2 = 4 ;                                move16();
  for (i = 0 ; i < count  ; i++)              
  {                                                                                         
    ur = x [t1] ;                         move32();
    ui = x [t1+1] ;                       move32();
                                              
    x [t1] = L_add(ur, x [t2]);           move32();
    x [t2] = L_sub(ur, x [t2]);           move32();
    x [t1+1] = L_add(ui, x [t2+1]);       move32();
    x [t2+1] = L_sub(ui, x [t2+1]);       move32();
                                              
    vr =  x [t2+3] ;                      move32();
                                             
    x [t2+3] = L_add(x [t1+3], x [t2+2]); move32();
    x [t1+3] = L_sub(x [t1+3], x [t2+2]); move32();
    x [t2+2] = L_sub(x [t1+2], vr);       move32();
    x [t1+2] = L_add(x [t1+2], vr);       move32();                                         
                                              
    ur = x [t1+8] ;                       move32();
    ui = x [t1+9] ;                       move32();
                                          
    x [t1+8] = L_add(ur, x [t2+8]);       move32();
    x [t2+8] = L_sub(ur, x [t2+8]);       move32();
    x [t1+9] = L_add(ui,  x [t2+9]);      move32();
    x [t2+9] = L_sub(ui,  x [t2+9]);      move32();
                                              
    vr =  x [t2+11] ;                     move32();

    x [t2+11] = L_add(x [t1+11], x [t2+10]);    move32();
    x [t1+11] = L_sub(x [t1+11], x [t2+10]);    move32();
    x [t2+10] = L_sub(x [t1+10], vr);           move32();
    x [t1+10] = L_add(x [t1+10], vr);           move32();

    t1 = add(t1, 16);
    t2 = add(t2, 16);
  }

  for (ldm = 3 ; ldm <= ldn ; ldm++)
  {                                                                     
    Word16 r, j;
    const Word16 m = shl(1, ldm);
    const Word16 mh = shr(m, 1);
    Word16 c_index, s_index;
                                                                                                                


    for (r = 0 ; r < n ; r += m)
    {                                                                                                 
      t1 = shl(r, 1);
      t2 = add(t1, m);

      ur = x [t1] ;                                               move32();
      ui = x [t1+1] ;                                             move32();

      x [t1] = L_add(ur, x [t2]);                                 move32();
      x [t2] = L_sub(ur, x [t2]);                                 move32();
      x [t1+1] = L_add(ui, x [t2+1]);                             move32();
      x [t2+1] = L_sub(ui, x [t2+1]);                             move32();

      /* symmetrical part */

      t1 = add(t1, mh);
      t2 = add(t1, m);

      vr = x [t2+1] ;                                             move32();

      x [t2+1] = L_add(x [t1+1], x [t2]);                         move32();
      x [t1+1] = L_sub(x [t1+1], x [t2]);                         move32();
      x [t2] = L_sub(x [t1], vr);                                 move32();
      x [t1] = L_add(x [t1], vr);                                 move32();
      
    }



    /* tableSize is known in advance, so no shl(tableSize,2) is necessary */
    angleStep = shr(tableSize<<2, ldm) ;
    count = shr(mh, 1);

    s_index = angleStep; move16();       /* init counter: j*angleStep */
    c_index = sub(tableSize, angleStep); /* init counter: tableSize - j*angleStep */

    for (j = 1 ; j < count ; j++)
    {
      
      for (r = 0 ; r < n ; r += m)
      {                                                                                                             
        t1 = shl(add(r, j), 1);
        t2 = add(t1, m);
        
        vr = L_add(fixmul_32x16b(x[t2], sineTable[c_index]),
                   fixmul_32x16b(x[t2+1], sineTable[s_index]));
        vi = L_sub(fixmul_32x16b(x[t2+1], sineTable[c_index]), 
                   fixmul_32x16b(x[t2], sineTable[s_index]));
        
        x [t2] = L_sub(x [t1], vr);                               move32();
        x [t1] = L_add(x [t1], vr);                               move32();
        x [t2+1] = L_sub(x [t1+1], vi);                           move32();
        x [t1+1] = L_add(x [t1+1], vi);                           move32();

        /* symmetrical part */

        t1 = add(t1, mh);
        t2 = add(t1, m);

        vi = L_add(fixmul_32x16b(x[t2], sineTable[c_index]),
                   fixmul_32x16b(x[t2+1], sineTable[s_index]));
        vr = L_sub(fixmul_32x16b(x[t2+1], sineTable[c_index]), 
                   fixmul_32x16b(x[t2], sineTable[s_index]));
        
        x [t2] = L_sub(x [t1], vr);                               move32();
        x [t1] = L_add(x [t1], vr);                               move32();
        x [t2+1] = L_add(x [t1+1], vi);                           move32();
        x [t1+1] = L_sub(x [t1+1], vi);                           move32();

      }
      c_index -= angleStep;
      s_index += angleStep;
    }
  }
}

void CLongBlock_InverseTransform (Word32 data [], Word16 *imdctScale)
{
  preTwiddle (data, 1024, OnlyLongWindowSine) ;
  shuffle512 (data) ;
  scaledFFT (data, 9, trigData, 512) ;
  postTwiddle (data, 1024, 1, trigData, 512) ;

  *imdctScale=9+1;                                                move16();
}

void CShortBlock_InverseTransform (Word32 data [], Word16 *imdctScale)
{
  preTwiddle (data, 128, OnlyShortWindowSine) ;
  shuffle64 (data) ;
  scaledFFT (data, 6, trigData, 512 ) ;
  postTwiddle (data, 128, 8, trigData, 512) ;

  *imdctScale=6+1;                                                move16();
}
