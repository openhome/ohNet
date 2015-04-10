/*
   Math functions based on table lookup and/or iterative approach  
 */
   
#include <assert.h>
#include "ffr.h"
#include "count.h"

static const Word16 logDualisTable[LOG_DUALIS_TABLE_SIZE] = {
  (Word16)0x8000,  /* actually, ld 0 is not defined */
  0x0000,  /*  ld(1) / 8  */
  0x1000,  /*  ld(2) / 8  */
  0x195c,  /*  ld(3) / 8  */
  0x2000,  /*  ld(4) / 8  */
  0x2527,  /*  ld(5) / 8  */
  0x295c,  /*  ld(6) / 8  */
  0x2ceb,  /*  ld(7) / 8  */
  0x3000,  /*  ld(8) / 8  */
  0x32b8,  /*  ld(9) / 8  */
  0x3527,  /*  ld(10) / 8  */
  0x375a,  /*  ld(11) / 8  */
  0x395c,  /*  ld(12) / 8  */
  0x3b35,  /*  ld(13) / 8  */
  0x3ceb,  /*  ld(14) / 8  */
  0x3e83,  /*  ld(15) / 8  */
  0x4000,  /*  ld(16) / 8  */
  0x4166,  /*  ld(17) / 8  */
  0x42b8,  /*  ld(18) / 8  */
  0x43f8,  /*  ld(19) / 8  */
  0x4527,  /*  ld(20) / 8  */
  0x4647,  /*  ld(21) / 8  */
  0x475a,  /*  ld(22) / 8  */
  0x4861,  /*  ld(23) / 8  */
  0x495c,  /*  ld(24) / 8  */
  0x4a4d,  /*  ld(25) / 8  */
  0x4b35,  /*  ld(26) / 8  */
  0x4c14,  /*  ld(27) / 8  */
  0x4ceb,  /*  ld(28) / 8  */
  0x4dba,  /*  ld(29) / 8  */
  0x4e83,  /*  ld(30) / 8  */
  0x4f44,  /*  ld(31) / 8  */
  0x5000,  /*  ld(32) / 8  */
  0x50b6,  /*  ld(33) / 8  */
  0x5166,  /*  ld(34) / 8  */
  0x5212,  /*  ld(35) / 8  */
  0x52b8,  /*  ld(36) / 8  */
  0x535a,  /*  ld(37) / 8  */
  0x53f8,  /*  ld(38) / 8  */
  0x5491,  /*  ld(39) / 8  */
  0x5527,  /*  ld(40) / 8  */
  0x55b9,  /*  ld(41) / 8  */
  0x5647,  /*  ld(42) / 8  */
  0x56d2,  /*  ld(43) / 8  */
  0x575a,  /*  ld(44) / 8  */
  0x57df,  /*  ld(45) / 8  */
  0x5861,  /*  ld(46) / 8  */
  0x58e0,  /*  ld(47) / 8  */
  0x595c,  /*  ld(48) / 8  */
  0x59d6,  /*  ld(49) / 8  */
  0x5a4d,  /*  ld(50) / 8  */
  0x5ac2,  /*  ld(51) / 8  */
  0x5b35,  /*  ld(52) / 8  */
  0x5ba6,  /*  ld(53) / 8  */
  0x5c14,  /*  ld(54) / 8  */
  0x5c80,  /*  ld(55) / 8  */
  0x5ceb,  /*  ld(56) / 8  */
  0x5d54,  /*  ld(57) / 8  */
  0x5dba,  /*  ld(58) / 8  */
  0x5e1f,  /*  ld(59) / 8  */
  0x5e83,  /*  ld(60) / 8  */
  0x5ee4,  /*  ld(61) / 8  */
  0x5f44,  /*  ld(62) / 8  */
  0x5fa3,  /*  ld(63) / 8  */
  0x6000   /*  ld(64) / 8  */
};


/* 1/x-table

   The table covers an input range from 0.5 to 1.0 with a step size of 1/512,
   starting at 0.5 + 1/512.
   Each table entry corresponds to an input interval starting 1/1024 below the
   exact value and ending 1/1024 above it.

   The table is actually a 0.5/x-table, so that the output range is again
   0.5...1.0 and the exponent of the result must be increased by 1.

   Input range           Index in table      result
   -------------------------------------------------------------------
   0.500000...0.500976          -            0.5 / 0.500000 = 1.000000
   0.500976...0.502930          0            0.5 / 0.501953 = 0.996109
   0.502930...0.500488          1            0.5 / 0.503906 = 0.992248
           ...
   0.999023...1.000000         255           0.5 / 1.000000 = 0.500000
*/
static const Word16 invTable[INV_TABLE_SIZE] = {
  0x7f80,  /*  0.5 / 0.501953125  */
  0x7f02,  /*  0.5 / 0.503906250  */
  0x7e84,  /*  0.5 / 0.505859375  */
  0x7e08,  /*  0.5 / 0.507812500  */
  0x7d8c,  /*  0.5 / 0.509765625  */
  0x7d12,  /*  0.5 / 0.511718750  */
  0x7c98,  /*  0.5 / 0.513671875  */
  0x7c1f,  /*  0.5 / 0.515625000  */
  0x7ba7,  /*  0.5 / 0.517578125  */
  0x7b30,  /*  0.5 / 0.519531250  */
  0x7aba,  /*  0.5 / 0.521484375  */
  0x7a45,  /*  0.5 / 0.523437500  */
  0x79d0,  /*  0.5 / 0.525390625  */
  0x795d,  /*  0.5 / 0.527343750  */
  0x78ea,  /*  0.5 / 0.529296875  */
  0x7878,  /*  0.5 / 0.531250000  */
  0x7808,  /*  0.5 / 0.533203125  */
  0x7797,  /*  0.5 / 0.535156250  */
  0x7728,  /*  0.5 / 0.537109375  */
  0x76ba,  /*  0.5 / 0.539062500  */
  0x764c,  /*  0.5 / 0.541015625  */
  0x75df,  /*  0.5 / 0.542968750  */
  0x7573,  /*  0.5 / 0.544921875  */
  0x7507,  /*  0.5 / 0.546875000  */
  0x749d,  /*  0.5 / 0.548828125  */
  0x7433,  /*  0.5 / 0.550781250  */
  0x73ca,  /*  0.5 / 0.552734375  */
  0x7361,  /*  0.5 / 0.554687500  */
  0x72fa,  /*  0.5 / 0.556640625  */
  0x7293,  /*  0.5 / 0.558593750  */
  0x722d,  /*  0.5 / 0.560546875  */
  0x71c7,  /*  0.5 / 0.562500000  */
  0x7162,  /*  0.5 / 0.564453125  */
  0x70fe,  /*  0.5 / 0.566406250  */
  0x709b,  /*  0.5 / 0.568359375  */
  0x7038,  /*  0.5 / 0.570312500  */
  0x6fd6,  /*  0.5 / 0.572265625  */
  0x6f75,  /*  0.5 / 0.574218750  */
  0x6f14,  /*  0.5 / 0.576171875  */
  0x6eb4,  /*  0.5 / 0.578125000  */
  0x6e54,  /*  0.5 / 0.580078125  */
  0x6df6,  /*  0.5 / 0.582031250  */
  0x6d98,  /*  0.5 / 0.583984375  */
  0x6d3a,  /*  0.5 / 0.585937500  */
  0x6cdd,  /*  0.5 / 0.587890625  */
  0x6c81,  /*  0.5 / 0.589843750  */
  0x6c25,  /*  0.5 / 0.591796875  */
  0x6bca,  /*  0.5 / 0.593750000  */
  0x6b70,  /*  0.5 / 0.595703125  */
  0x6b16,  /*  0.5 / 0.597656250  */
  0x6abc,  /*  0.5 / 0.599609375  */
  0x6a64,  /*  0.5 / 0.601562500  */
  0x6a0c,  /*  0.5 / 0.603515625  */
  0x69b4,  /*  0.5 / 0.605468750  */
  0x695d,  /*  0.5 / 0.607421875  */
  0x6907,  /*  0.5 / 0.609375000  */
  0x68b1,  /*  0.5 / 0.611328125  */
  0x685b,  /*  0.5 / 0.613281250  */
  0x6807,  /*  0.5 / 0.615234375  */
  0x67b2,  /*  0.5 / 0.617187500  */
  0x675e,  /*  0.5 / 0.619140625  */
  0x670b,  /*  0.5 / 0.621093750  */
  0x66b9,  /*  0.5 / 0.623046875  */
  0x6666,  /*  0.5 / 0.625000000  */
  0x6615,  /*  0.5 / 0.626953125  */
  0x65c4,  /*  0.5 / 0.628906250  */
  0x6573,  /*  0.5 / 0.630859375  */
  0x6523,  /*  0.5 / 0.632812500  */
  0x64d3,  /*  0.5 / 0.634765625  */
  0x6484,  /*  0.5 / 0.636718750  */
  0x6435,  /*  0.5 / 0.638671875  */
  0x63e7,  /*  0.5 / 0.640625000  */
  0x6399,  /*  0.5 / 0.642578125  */
  0x634c,  /*  0.5 / 0.644531250  */
  0x62ff,  /*  0.5 / 0.646484375  */
  0x62b3,  /*  0.5 / 0.648437500  */
  0x6267,  /*  0.5 / 0.650390625  */
  0x621c,  /*  0.5 / 0.652343750  */
  0x61d1,  /*  0.5 / 0.654296875  */
  0x6186,  /*  0.5 / 0.656250000  */
  0x613c,  /*  0.5 / 0.658203125  */
  0x60f2,  /*  0.5 / 0.660156250  */
  0x60a9,  /*  0.5 / 0.662109375  */
  0x6060,  /*  0.5 / 0.664062500  */
  0x6018,  /*  0.5 / 0.666015625  */
  0x5fd0,  /*  0.5 / 0.667968750  */
  0x5f89,  /*  0.5 / 0.669921875  */
  0x5f41,  /*  0.5 / 0.671875000  */
  0x5efb,  /*  0.5 / 0.673828125  */
  0x5eb5,  /*  0.5 / 0.675781250  */
  0x5e6f,  /*  0.5 / 0.677734375  */
  0x5e29,  /*  0.5 / 0.679687500  */
  0x5de4,  /*  0.5 / 0.681640625  */
  0x5d9f,  /*  0.5 / 0.683593750  */
  0x5d5b,  /*  0.5 / 0.685546875  */
  0x5d17,  /*  0.5 / 0.687500000  */
  0x5cd4,  /*  0.5 / 0.689453125  */
  0x5c91,  /*  0.5 / 0.691406250  */
  0x5c4e,  /*  0.5 / 0.693359375  */
  0x5c0c,  /*  0.5 / 0.695312500  */
  0x5bca,  /*  0.5 / 0.697265625  */
  0x5b88,  /*  0.5 / 0.699218750  */
  0x5b47,  /*  0.5 / 0.701171875  */
  0x5b06,  /*  0.5 / 0.703125000  */
  0x5ac5,  /*  0.5 / 0.705078125  */
  0x5a85,  /*  0.5 / 0.707031250  */
  0x5a45,  /*  0.5 / 0.708984375  */
  0x5a06,  /*  0.5 / 0.710937500  */
  0x59c6,  /*  0.5 / 0.712890625  */
  0x5988,  /*  0.5 / 0.714843750  */
  0x5949,  /*  0.5 / 0.716796875  */
  0x590b,  /*  0.5 / 0.718750000  */
  0x58cd,  /*  0.5 / 0.720703125  */
  0x5890,  /*  0.5 / 0.722656250  */
  0x5853,  /*  0.5 / 0.724609375  */
  0x5816,  /*  0.5 / 0.726562500  */
  0x57da,  /*  0.5 / 0.728515625  */
  0x579d,  /*  0.5 / 0.730468750  */
  0x5762,  /*  0.5 / 0.732421875  */
  0x5726,  /*  0.5 / 0.734375000  */
  0x56eb,  /*  0.5 / 0.736328125  */
  0x56b0,  /*  0.5 / 0.738281250  */
  0x5676,  /*  0.5 / 0.740234375  */
  0x563b,  /*  0.5 / 0.742187500  */
  0x5601,  /*  0.5 / 0.744140625  */
  0x55c8,  /*  0.5 / 0.746093750  */
  0x558e,  /*  0.5 / 0.748046875  */
  0x5555,  /*  0.5 / 0.750000000  */
  0x551d,  /*  0.5 / 0.751953125  */
  0x54e4,  /*  0.5 / 0.753906250  */
  0x54ac,  /*  0.5 / 0.755859375  */
  0x5474,  /*  0.5 / 0.757812500  */
  0x543d,  /*  0.5 / 0.759765625  */
  0x5405,  /*  0.5 / 0.761718750  */
  0x53ce,  /*  0.5 / 0.763671875  */
  0x5398,  /*  0.5 / 0.765625000  */
  0x5361,  /*  0.5 / 0.767578125  */
  0x532b,  /*  0.5 / 0.769531250  */
  0x52f5,  /*  0.5 / 0.771484375  */
  0x52bf,  /*  0.5 / 0.773437500  */
  0x528a,  /*  0.5 / 0.775390625  */
  0x5255,  /*  0.5 / 0.777343750  */
  0x5220,  /*  0.5 / 0.779296875  */
  0x51ec,  /*  0.5 / 0.781250000  */
  0x51b7,  /*  0.5 / 0.783203125  */
  0x5183,  /*  0.5 / 0.785156250  */
  0x514f,  /*  0.5 / 0.787109375  */
  0x511c,  /*  0.5 / 0.789062500  */
  0x50e9,  /*  0.5 / 0.791015625  */
  0x50b6,  /*  0.5 / 0.792968750  */
  0x5083,  /*  0.5 / 0.794921875  */
  0x5050,  /*  0.5 / 0.796875000  */
  0x501e,  /*  0.5 / 0.798828125  */
  0x4fec,  /*  0.5 / 0.800781250  */
  0x4fba,  /*  0.5 / 0.802734375  */
  0x4f89,  /*  0.5 / 0.804687500  */
  0x4f57,  /*  0.5 / 0.806640625  */
  0x4f26,  /*  0.5 / 0.808593750  */
  0x4ef6,  /*  0.5 / 0.810546875  */
  0x4ec5,  /*  0.5 / 0.812500000  */
  0x4e95,  /*  0.5 / 0.814453125  */
  0x4e64,  /*  0.5 / 0.816406250  */
  0x4e35,  /*  0.5 / 0.818359375  */
  0x4e05,  /*  0.5 / 0.820312500  */
  0x4dd5,  /*  0.5 / 0.822265625  */
  0x4da6,  /*  0.5 / 0.824218750  */
  0x4d77,  /*  0.5 / 0.826171875  */
  0x4d48,  /*  0.5 / 0.828125000  */
  0x4d1a,  /*  0.5 / 0.830078125  */
  0x4cec,  /*  0.5 / 0.832031250  */
  0x4cbd,  /*  0.5 / 0.833984375  */
  0x4c90,  /*  0.5 / 0.835937500  */
  0x4c62,  /*  0.5 / 0.837890625  */
  0x4c34,  /*  0.5 / 0.839843750  */
  0x4c07,  /*  0.5 / 0.841796875  */
  0x4bda,  /*  0.5 / 0.843750000  */
  0x4bad,  /*  0.5 / 0.845703125  */
  0x4b81,  /*  0.5 / 0.847656250  */
  0x4b54,  /*  0.5 / 0.849609375  */
  0x4b28,  /*  0.5 / 0.851562500  */
  0x4afc,  /*  0.5 / 0.853515625  */
  0x4ad0,  /*  0.5 / 0.855468750  */
  0x4aa4,  /*  0.5 / 0.857421875  */
  0x4a79,  /*  0.5 / 0.859375000  */
  0x4a4e,  /*  0.5 / 0.861328125  */
  0x4a23,  /*  0.5 / 0.863281250  */
  0x49f8,  /*  0.5 / 0.865234375  */
  0x49cd,  /*  0.5 / 0.867187500  */
  0x49a3,  /*  0.5 / 0.869140625  */
  0x4979,  /*  0.5 / 0.871093750  */
  0x494e,  /*  0.5 / 0.873046875  */
  0x4925,  /*  0.5 / 0.875000000  */
  0x48fb,  /*  0.5 / 0.876953125  */
  0x48d1,  /*  0.5 / 0.878906250  */
  0x48a8,  /*  0.5 / 0.880859375  */
  0x487f,  /*  0.5 / 0.882812500  */
  0x4856,  /*  0.5 / 0.884765625  */
  0x482d,  /*  0.5 / 0.886718750  */
  0x4805,  /*  0.5 / 0.888671875  */
  0x47dc,  /*  0.5 / 0.890625000  */
  0x47b4,  /*  0.5 / 0.892578125  */
  0x478c,  /*  0.5 / 0.894531250  */
  0x4764,  /*  0.5 / 0.896484375  */
  0x473c,  /*  0.5 / 0.898437500  */
  0x4715,  /*  0.5 / 0.900390625  */
  0x46ed,  /*  0.5 / 0.902343750  */
  0x46c6,  /*  0.5 / 0.904296875  */
  0x469f,  /*  0.5 / 0.906250000  */
  0x4678,  /*  0.5 / 0.908203125  */
  0x4651,  /*  0.5 / 0.910156250  */
  0x462b,  /*  0.5 / 0.912109375  */
  0x4604,  /*  0.5 / 0.914062500  */
  0x45de,  /*  0.5 / 0.916015625  */
  0x45b8,  /*  0.5 / 0.917968750  */
  0x4592,  /*  0.5 / 0.919921875  */
  0x456c,  /*  0.5 / 0.921875000  */
  0x4547,  /*  0.5 / 0.923828125  */
  0x4521,  /*  0.5 / 0.925781250  */
  0x44fc,  /*  0.5 / 0.927734375  */
  0x44d7,  /*  0.5 / 0.929687500  */
  0x44b2,  /*  0.5 / 0.931640625  */
  0x448d,  /*  0.5 / 0.933593750  */
  0x4469,  /*  0.5 / 0.935546875  */
  0x4444,  /*  0.5 / 0.937500000  */
  0x4420,  /*  0.5 / 0.939453125  */
  0x43fc,  /*  0.5 / 0.941406250  */
  0x43d8,  /*  0.5 / 0.943359375  */
  0x43b4,  /*  0.5 / 0.945312500  */
  0x4390,  /*  0.5 / 0.947265625  */
  0x436d,  /*  0.5 / 0.949218750  */
  0x4349,  /*  0.5 / 0.951171875  */
  0x4326,  /*  0.5 / 0.953125000  */
  0x4303,  /*  0.5 / 0.955078125  */
  0x42e0,  /*  0.5 / 0.957031250  */
  0x42bd,  /*  0.5 / 0.958984375  */
  0x429a,  /*  0.5 / 0.960937500  */
  0x4277,  /*  0.5 / 0.962890625  */
  0x4255,  /*  0.5 / 0.964843750  */
  0x4233,  /*  0.5 / 0.966796875  */
  0x4211,  /*  0.5 / 0.968750000  */
  0x41ee,  /*  0.5 / 0.970703125  */
  0x41cd,  /*  0.5 / 0.972656250  */
  0x41ab,  /*  0.5 / 0.974609375  */
  0x4189,  /*  0.5 / 0.976562500  */
  0x4168,  /*  0.5 / 0.978515625  */
  0x4146,  /*  0.5 / 0.980468750  */
  0x4125,  /*  0.5 / 0.982421875  */
  0x4104,  /*  0.5 / 0.984375000  */
  0x40e3,  /*  0.5 / 0.986328125  */
  0x40c2,  /*  0.5 / 0.988281250  */
  0x40a2,  /*  0.5 / 0.990234375  */
  0x4081,  /*  0.5 / 0.992187500  */
  0x4061,  /*  0.5 / 0.994140625  */
  0x4040,  /*  0.5 / 0.996093750  */
  0x4020,  /*  0.5 / 0.998046875  */
  0x4000   /*  0.5 / 1.000000000  */
};


/* Squareroot-table

   The table covers an input range from 0.5 to 1.0 with a step size of 1/512,
   starting at 0.5 + 1/512.
   Each table entry corresponds to an input interval starting 1/1024 below the
   exact value and ending 1/1024 above it.

   Input range           Index in table      result
   -------------------------------------------------------------------
   0.500000...0.500976          -            sqrt(0.500000) = 0.707107
   0.500976...0.502930          0            sqrt(0.501953) = 0.708486
   0.502930...0.500488          1            sqrt(0.503906) = 0.709863
           ...
   0.999023...1.000000         255           sqrt(1.000000) = 1.000000
*/
const Word16 sqrtTable[SQRT_TABLE_SIZE] = {
  0x5ab0,  /*  sqrt(0.501953125)  */
  0x5add,  /*  sqrt(0.503906250)  */
  0x5b0a,  /*  sqrt(0.505859375)  */
  0x5b37,  /*  sqrt(0.507812500)  */
  0x5b64,  /*  sqrt(0.509765625)  */
  0x5b90,  /*  sqrt(0.511718750)  */
  0x5bbd,  /*  sqrt(0.513671875)  */
  0x5bea,  /*  sqrt(0.515625000)  */
  0x5c16,  /*  sqrt(0.517578125)  */
  0x5c43,  /*  sqrt(0.519531250)  */
  0x5c6f,  /*  sqrt(0.521484375)  */
  0x5c9b,  /*  sqrt(0.523437500)  */
  0x5cc8,  /*  sqrt(0.525390625)  */
  0x5cf4,  /*  sqrt(0.527343750)  */
  0x5d20,  /*  sqrt(0.529296875)  */
  0x5d4c,  /*  sqrt(0.531250000)  */
  0x5d77,  /*  sqrt(0.533203125)  */
  0x5da3,  /*  sqrt(0.535156250)  */
  0x5dcf,  /*  sqrt(0.537109375)  */
  0x5dfb,  /*  sqrt(0.539062500)  */
  0x5e26,  /*  sqrt(0.541015625)  */
  0x5e52,  /*  sqrt(0.542968750)  */
  0x5e7d,  /*  sqrt(0.544921875)  */
  0x5ea8,  /*  sqrt(0.546875000)  */
  0x5ed3,  /*  sqrt(0.548828125)  */
  0x5eff,  /*  sqrt(0.550781250)  */
  0x5f2a,  /*  sqrt(0.552734375)  */
  0x5f55,  /*  sqrt(0.554687500)  */
  0x5f80,  /*  sqrt(0.556640625)  */
  0x5fab,  /*  sqrt(0.558593750)  */
  0x5fd5,  /*  sqrt(0.560546875)  */
  0x6000,  /*  sqrt(0.562500000)  */
  0x602b,  /*  sqrt(0.564453125)  */
  0x6055,  /*  sqrt(0.566406250)  */
  0x6080,  /*  sqrt(0.568359375)  */
  0x60aa,  /*  sqrt(0.570312500)  */
  0x60d4,  /*  sqrt(0.572265625)  */
  0x60ff,  /*  sqrt(0.574218750)  */
  0x6129,  /*  sqrt(0.576171875)  */
  0x6153,  /*  sqrt(0.578125000)  */
  0x617d,  /*  sqrt(0.580078125)  */
  0x61a7,  /*  sqrt(0.582031250)  */
  0x61d1,  /*  sqrt(0.583984375)  */
  0x61fb,  /*  sqrt(0.585937500)  */
  0x6225,  /*  sqrt(0.587890625)  */
  0x624e,  /*  sqrt(0.589843750)  */
  0x6278,  /*  sqrt(0.591796875)  */
  0x62a1,  /*  sqrt(0.593750000)  */
  0x62cb,  /*  sqrt(0.595703125)  */
  0x62f4,  /*  sqrt(0.597656250)  */
  0x631e,  /*  sqrt(0.599609375)  */
  0x6347,  /*  sqrt(0.601562500)  */
  0x6370,  /*  sqrt(0.603515625)  */
  0x6399,  /*  sqrt(0.605468750)  */
  0x63c2,  /*  sqrt(0.607421875)  */
  0x63ec,  /*  sqrt(0.609375000)  */
  0x6414,  /*  sqrt(0.611328125)  */
  0x643d,  /*  sqrt(0.613281250)  */
  0x6466,  /*  sqrt(0.615234375)  */
  0x648f,  /*  sqrt(0.617187500)  */
  0x64b8,  /*  sqrt(0.619140625)  */
  0x64e0,  /*  sqrt(0.621093750)  */
  0x6509,  /*  sqrt(0.623046875)  */
  0x6531,  /*  sqrt(0.625000000)  */
  0x655a,  /*  sqrt(0.626953125)  */
  0x6582,  /*  sqrt(0.628906250)  */
  0x65ab,  /*  sqrt(0.630859375)  */
  0x65d3,  /*  sqrt(0.632812500)  */
  0x65fb,  /*  sqrt(0.634765625)  */
  0x6623,  /*  sqrt(0.636718750)  */
  0x664b,  /*  sqrt(0.638671875)  */
  0x6673,  /*  sqrt(0.640625000)  */
  0x669b,  /*  sqrt(0.642578125)  */
  0x66c3,  /*  sqrt(0.644531250)  */
  0x66eb,  /*  sqrt(0.646484375)  */
  0x6713,  /*  sqrt(0.648437500)  */
  0x673a,  /*  sqrt(0.650390625)  */
  0x6762,  /*  sqrt(0.652343750)  */
  0x678a,  /*  sqrt(0.654296875)  */
  0x67b1,  /*  sqrt(0.656250000)  */
  0x67d9,  /*  sqrt(0.658203125)  */
  0x6800,  /*  sqrt(0.660156250)  */
  0x6827,  /*  sqrt(0.662109375)  */
  0x684f,  /*  sqrt(0.664062500)  */
  0x6876,  /*  sqrt(0.666015625)  */
  0x689d,  /*  sqrt(0.667968750)  */
  0x68c4,  /*  sqrt(0.669921875)  */
  0x68eb,  /*  sqrt(0.671875000)  */
  0x6912,  /*  sqrt(0.673828125)  */
  0x6939,  /*  sqrt(0.675781250)  */
  0x6960,  /*  sqrt(0.677734375)  */
  0x6987,  /*  sqrt(0.679687500)  */
  0x69ae,  /*  sqrt(0.681640625)  */
  0x69d4,  /*  sqrt(0.683593750)  */
  0x69fb,  /*  sqrt(0.685546875)  */
  0x6a22,  /*  sqrt(0.687500000)  */
  0x6a48,  /*  sqrt(0.689453125)  */
  0x6a6f,  /*  sqrt(0.691406250)  */
  0x6a95,  /*  sqrt(0.693359375)  */
  0x6abc,  /*  sqrt(0.695312500)  */
  0x6ae2,  /*  sqrt(0.697265625)  */
  0x6b08,  /*  sqrt(0.699218750)  */
  0x6b2f,  /*  sqrt(0.701171875)  */
  0x6b55,  /*  sqrt(0.703125000)  */
  0x6b7b,  /*  sqrt(0.705078125)  */
  0x6ba1,  /*  sqrt(0.707031250)  */
  0x6bc7,  /*  sqrt(0.708984375)  */
  0x6bed,  /*  sqrt(0.710937500)  */
  0x6c13,  /*  sqrt(0.712890625)  */
  0x6c39,  /*  sqrt(0.714843750)  */
  0x6c5f,  /*  sqrt(0.716796875)  */
  0x6c84,  /*  sqrt(0.718750000)  */
  0x6caa,  /*  sqrt(0.720703125)  */
  0x6cd0,  /*  sqrt(0.722656250)  */
  0x6cf5,  /*  sqrt(0.724609375)  */
  0x6d1b,  /*  sqrt(0.726562500)  */
  0x6d41,  /*  sqrt(0.728515625)  */
  0x6d66,  /*  sqrt(0.730468750)  */
  0x6d8b,  /*  sqrt(0.732421875)  */
  0x6db1,  /*  sqrt(0.734375000)  */
  0x6dd6,  /*  sqrt(0.736328125)  */
  0x6dfb,  /*  sqrt(0.738281250)  */
  0x6e21,  /*  sqrt(0.740234375)  */
  0x6e46,  /*  sqrt(0.742187500)  */
  0x6e6b,  /*  sqrt(0.744140625)  */
  0x6e90,  /*  sqrt(0.746093750)  */
  0x6eb5,  /*  sqrt(0.748046875)  */
  0x6eda,  /*  sqrt(0.750000000)  */
  0x6eff,  /*  sqrt(0.751953125)  */
  0x6f24,  /*  sqrt(0.753906250)  */
  0x6f49,  /*  sqrt(0.755859375)  */
  0x6f6d,  /*  sqrt(0.757812500)  */
  0x6f92,  /*  sqrt(0.759765625)  */
  0x6fb7,  /*  sqrt(0.761718750)  */
  0x6fdb,  /*  sqrt(0.763671875)  */
  0x7000,  /*  sqrt(0.765625000)  */
  0x7025,  /*  sqrt(0.767578125)  */
  0x7049,  /*  sqrt(0.769531250)  */
  0x706e,  /*  sqrt(0.771484375)  */
  0x7092,  /*  sqrt(0.773437500)  */
  0x70b6,  /*  sqrt(0.775390625)  */
  0x70db,  /*  sqrt(0.777343750)  */
  0x70ff,  /*  sqrt(0.779296875)  */
  0x7123,  /*  sqrt(0.781250000)  */
  0x7147,  /*  sqrt(0.783203125)  */
  0x716b,  /*  sqrt(0.785156250)  */
  0x7190,  /*  sqrt(0.787109375)  */
  0x71b4,  /*  sqrt(0.789062500)  */
  0x71d8,  /*  sqrt(0.791015625)  */
  0x71fc,  /*  sqrt(0.792968750)  */
  0x721f,  /*  sqrt(0.794921875)  */
  0x7243,  /*  sqrt(0.796875000)  */
  0x7267,  /*  sqrt(0.798828125)  */
  0x728b,  /*  sqrt(0.800781250)  */
  0x72af,  /*  sqrt(0.802734375)  */
  0x72d2,  /*  sqrt(0.804687500)  */
  0x72f6,  /*  sqrt(0.806640625)  */
  0x731a,  /*  sqrt(0.808593750)  */
  0x733d,  /*  sqrt(0.810546875)  */
  0x7361,  /*  sqrt(0.812500000)  */
  0x7384,  /*  sqrt(0.814453125)  */
  0x73a8,  /*  sqrt(0.816406250)  */
  0x73cb,  /*  sqrt(0.818359375)  */
  0x73ee,  /*  sqrt(0.820312500)  */
  0x7412,  /*  sqrt(0.822265625)  */
  0x7435,  /*  sqrt(0.824218750)  */
  0x7458,  /*  sqrt(0.826171875)  */
  0x747b,  /*  sqrt(0.828125000)  */
  0x749e,  /*  sqrt(0.830078125)  */
  0x74c2,  /*  sqrt(0.832031250)  */
  0x74e5,  /*  sqrt(0.833984375)  */
  0x7508,  /*  sqrt(0.835937500)  */
  0x752b,  /*  sqrt(0.837890625)  */
  0x754e,  /*  sqrt(0.839843750)  */
  0x7570,  /*  sqrt(0.841796875)  */
  0x7593,  /*  sqrt(0.843750000)  */
  0x75b6,  /*  sqrt(0.845703125)  */
  0x75d9,  /*  sqrt(0.847656250)  */
  0x75fc,  /*  sqrt(0.849609375)  */
  0x761e,  /*  sqrt(0.851562500)  */
  0x7641,  /*  sqrt(0.853515625)  */
  0x7664,  /*  sqrt(0.855468750)  */
  0x7686,  /*  sqrt(0.857421875)  */
  0x76a9,  /*  sqrt(0.859375000)  */
  0x76cb,  /*  sqrt(0.861328125)  */
  0x76ee,  /*  sqrt(0.863281250)  */
  0x7710,  /*  sqrt(0.865234375)  */
  0x7733,  /*  sqrt(0.867187500)  */
  0x7755,  /*  sqrt(0.869140625)  */
  0x7777,  /*  sqrt(0.871093750)  */
  0x7799,  /*  sqrt(0.873046875)  */
  0x77bc,  /*  sqrt(0.875000000)  */
  0x77de,  /*  sqrt(0.876953125)  */
  0x7800,  /*  sqrt(0.878906250)  */
  0x7822,  /*  sqrt(0.880859375)  */
  0x7844,  /*  sqrt(0.882812500)  */
  0x7866,  /*  sqrt(0.884765625)  */
  0x7888,  /*  sqrt(0.886718750)  */
  0x78aa,  /*  sqrt(0.888671875)  */
  0x78cc,  /*  sqrt(0.890625000)  */
  0x78ee,  /*  sqrt(0.892578125)  */
  0x7910,  /*  sqrt(0.894531250)  */
  0x7932,  /*  sqrt(0.896484375)  */
  0x7953,  /*  sqrt(0.898437500)  */
  0x7975,  /*  sqrt(0.900390625)  */
  0x7997,  /*  sqrt(0.902343750)  */
  0x79b9,  /*  sqrt(0.904296875)  */
  0x79da,  /*  sqrt(0.906250000)  */
  0x79fc,  /*  sqrt(0.908203125)  */
  0x7a1d,  /*  sqrt(0.910156250)  */
  0x7a3f,  /*  sqrt(0.912109375)  */
  0x7a60,  /*  sqrt(0.914062500)  */
  0x7a82,  /*  sqrt(0.916015625)  */
  0x7aa3,  /*  sqrt(0.917968750)  */
  0x7ac5,  /*  sqrt(0.919921875)  */
  0x7ae6,  /*  sqrt(0.921875000)  */
  0x7b07,  /*  sqrt(0.923828125)  */
  0x7b29,  /*  sqrt(0.925781250)  */
  0x7b4a,  /*  sqrt(0.927734375)  */
  0x7b6b,  /*  sqrt(0.929687500)  */
  0x7b8c,  /*  sqrt(0.931640625)  */
  0x7bad,  /*  sqrt(0.933593750)  */
  0x7bce,  /*  sqrt(0.935546875)  */
  0x7bef,  /*  sqrt(0.937500000)  */
  0x7c11,  /*  sqrt(0.939453125)  */
  0x7c32,  /*  sqrt(0.941406250)  */
  0x7c52,  /*  sqrt(0.943359375)  */
  0x7c73,  /*  sqrt(0.945312500)  */
  0x7c94,  /*  sqrt(0.947265625)  */
  0x7cb5,  /*  sqrt(0.949218750)  */
  0x7cd6,  /*  sqrt(0.951171875)  */
  0x7cf7,  /*  sqrt(0.953125000)  */
  0x7d18,  /*  sqrt(0.955078125)  */
  0x7d38,  /*  sqrt(0.957031250)  */
  0x7d59,  /*  sqrt(0.958984375)  */
  0x7d7a,  /*  sqrt(0.960937500)  */
  0x7d9a,  /*  sqrt(0.962890625)  */
  0x7dbb,  /*  sqrt(0.964843750)  */
  0x7ddb,  /*  sqrt(0.966796875)  */
  0x7dfc,  /*  sqrt(0.968750000)  */
  0x7e1c,  /*  sqrt(0.970703125)  */
  0x7e3d,  /*  sqrt(0.972656250)  */
  0x7e5d,  /*  sqrt(0.974609375)  */
  0x7e7e,  /*  sqrt(0.976562500)  */
  0x7e9e,  /*  sqrt(0.978515625)  */
  0x7ebe,  /*  sqrt(0.980468750)  */
  0x7edf,  /*  sqrt(0.982421875)  */
  0x7eff,  /*  sqrt(0.984375000)  */
  0x7f1f,  /*  sqrt(0.986328125)  */
  0x7f3f,  /*  sqrt(0.988281250)  */
  0x7f60,  /*  sqrt(0.990234375)  */
  0x7f80,  /*  sqrt(0.992187500)  */
  0x7fa0,  /*  sqrt(0.994140625)  */
  0x7fc0,  /*  sqrt(0.996093750)  */
  0x7fe0,  /*  sqrt(0.998046875)  */
  0x7fff   /*  sqrt(1.000000000)  */
};



/*!***********************************************************************
   \brief   Integer division for DSPs by iteration
   \author  Klaus Peichl

   1. The dividend a is divided by b multiplied with the largest possible power of 2
      <br>
   2. The result accumulated and step 1 is done for the remainder

   \return   a / b  (next lower integer)

*************************************************************************/
Word32 ffr_divideWord32(Word32 a,  /*!< dividend */
                     Word32 b)  /*!< divisor  */
{
  Word32 mult;
  Word16 shift, shift_M1;
  Word32 result;
  Word32 a_orig; /* debug */

  result = 0;  move32();
  a = L_min(a, 0x7ffffffe);
  a_orig = a;  /* debug */


  /* Designed for positive numbers only */
  assert(a>=0);
  assert(b>=0);

  L_sub(b,a); test();
  while (b <= a) {
    L_sub(b,a); test();
    shift = 0;  move32();
    L_sub(0,0); test();
    while (L_shl(b, shift) <= a) {
      L_sub(0,0); test();
      shift = add(shift, 1);
    }
    shift_M1 = sub(shift,1);
    mult = L_shl(1, shift_M1);
    result = L_add(result, mult);
    a = L_sub(a, L_shl(b, shift_M1));
  };

  assert( result == a_orig / b );

  return( result );
}


/*!**********************************************************************
   \brief   Scaled Logarithm dualis by table lookup
   \author  Klaus Peichl
   
   The valid range for a is 1 to LOG_DUALIS_TABLE_SIZE.
   For a=0, the result will be -1 (should be -inf).

   \return   ld(a) / 8
*************************************************************************/
Word16 ffr_logDualisDiv8(Word32 a)  /*!< Index for logarithm table */
{
  assert( a>=0 && a<LOG_DUALIS_TABLE_SIZE );
  return (logDualisTable[a]);
}


/*!**********************************************************************
   \brief   Get number of octaves between frequencies a and b
   \author  Klaus Peichl
   
   The Result is scaled with 1/8.
   The valid range for a and b is 1 to LOG_DUALIS_TABLE_SIZE.

   \return   ld(a/b) / 8
*************************************************************************/
Word16 ffr_getNumOctavesDiv8(Word32 a, /*!< lower band */
                             Word32 b) /*!< upper band */
{
  return (sub(ffr_logDualisDiv8(b), ffr_logDualisDiv8(a)));
}


/*!**********************************************************************
   \brief   Add two values given by mantissa and exponent.
   \author  Klaus Peichl

   Mantissas are in 16-bit-fractional format with values between 0 and 1. <br>
   The base for exponents is 2.  Example:  \f$  a = a\_m * 2^{a\_e}  \f$<br>

************************************************************************/
void ffr_add_MantExp(Word16  a_m,       /*!< Mantissa of 1st operand a */
                     Word16  a_e,       /*!< Exponent of 1st operand a */
                     Word16  b_m,       /*!< Mantissa of 2nd operand b */
                     Word16  b_e,       /*!< Exponent of 2nd operand b */
                     Word16  *ptrSum_m, /*!< Mantissa of result */
                     Word16  *ptrSum_e) /*!< Exponent of result */
{
  Word32   accu;
  Word16  shift;

  /* Equalize exponents of the summands.
     For the smaller summand, the exponent is adapted and
     for compensation, the mantissa is shifted right. */

  shift = sub(a_e, b_e);
  test();
  if (shift>0) {
    test(); sub(shift, 31);
    if (shift > 31)
    {
      shift = 31; move16();
    }
    b_m = shr(b_m, shift);

    *ptrSum_e = a_e;  move16();
  }
  else {
    test(); sub(shift, -31);
    if (shift < -31)
    {
      shift = -31;  move16();
    }
    a_m = shr(a_m, negate((Word16)shift));

    *ptrSum_e = b_e;  move16();
  }

  /*
    Shift input values down by one bit to avoid overflows
  */
  accu = L_deposit_l(add(shr(a_m, 1), shr(b_m, 1)));

  test(); test();
  if ( L_sub(accu,0x00003fff) >= 0 || (L_sub(accu,0xffffc000) <= 0 ) ) {
    *ptrSum_e = add(*ptrSum_e, 1);  move16();
  }
  else {
    /* no shift necessary => recalculate sum without prior shifting */
    accu = L_deposit_l(add(a_m, b_m));
  }

  *ptrSum_m = extract_l(accu); move16();
}


/*!**********************************************************************
   \brief   Divide two values given by mantissa and exponent.
   \author  Klaus Peichl

   Mantissas are in 16-bit-fractional format with values between 0 and 1. <br>
   The base for exponents is 2.  Example:  \f$  a = a\_m * 2^{a\_e}  \f$<br>

   For performance reasons, the division is based on a table lookup
   which limits accuracy.
************************************************************************/
void ffr_divide_MantExp(Word16  a_m,          /*!< Mantissa of dividend a */
                        Word16  a_e,          /*!< Exponent of dividend a */
                        Word16  b_m,          /*!< Mantissa of divisor b */
                        Word16  b_e,          /*!< Exponent of divisor b */
                        Word16  *ptrResult_m, /*!< Mantissa of quotient a/b */
                        Word16  *ptrResult_e) /*!< Exponent of quotient a/b */

{
  Word16 preShift, postShift, index, shift, bInv_m;
  preShift = sub(ffr_norm32(b_m), 16);

  /*
    Shift b into the range from 0..INV_TABLE_SIZE-1,
  
    E.g. 10 bits must be skipped for INV_TABLE_BITS 8:
    - leave 8 bits as index for table
    - skip sign bit,
    - skip first bit of mantissa, because this is always the same (>0.5)
    
    We are dealing with energies, so we need not care
    about negative numbers
  */

  /*
    The first interval has half width so the lowest bit of the index is
    needed for a doubled resolution.
  */
  shift = sub(SHORT_BITS - 3 - 8, /*INV_TABLE_BITS*/ preShift);
  index = shr(b_m, shift);

  /* The index has INV_TABLE_BITS +1 valid bits here. Clear the other bits. */
  index &= (1 << (8 /*INV_TABLE_BITS*/+1)) - 1; logic16();

  test();
  if (index==0) {
    /* Speed path: Do not look up the inverse for a power of 2. */
    postShift = sub(ffr_norm32(a_m), 16);

    *ptrResult_m = shl(a_m, postShift); move16();

  }
  else {
    Word32   ratio_m;

    /* Remove offset of half an interval */
    index = sub(index, 1);

    /* Now the lowest bit is shifted out */
    index = shr(index, 1);

    /* Fetch inversed mantissa from table: */
    bInv_m = invTable[index]; move16();

    /* Multiply a with the inverse of b: */
    ratio_m = L_mult(bInv_m, a_m);
    postShift = ffr_norm32(ratio_m);
    *ptrResult_m = extract_l(L_shl(ratio_m, sub(postShift, 16)));


  }

  *ptrResult_e = sub(add(add(sub(a_e, b_e), 1), preShift), postShift);  move16();
}


/*!
  \brief   Calculate the squareroot of a number given by mantissa and exponent

  Mantissa is in 16-bit-fractional format with values between 0 and 1. <br>
  The base for the exponent is 2.  Example:  \f$  a = a\_m * 2^{a\_e}  \f$<br>
  The operand is addressed via pointers and will be overwritten with the result.

  For performance reasons, the square root is based on a table lookup
  which limits accuracy.
*/
void ffr_sqrt_MantExp(Word16  *mantissa,    /*!< Pointer to mantissa */
                      Word16  *exponent)    /*!< Pointer to exponent */
{
  Word16  index;
  Word16  preShift;
  Word16  input_m = *mantissa;
  Word16  input_e = *exponent;
  Word16  result_m;
  Word16  result_e;

  move16(); move16(); 
  test();
  if ( input_m > 0 ) {
    /*
      Shift Mantissa into a right-aligned integer.
      Example for SQRT_TABLE_BITS 8:
      Mantissa=0.5   => index=0
      Mantissa=0.999 => index=255
    */
    preShift = sub(ffr_norm32(input_m), 16);
    
    input_e = sub(input_e, preShift);
    index = shr(input_m, sub(SHORT_BITS - 3 - 8, /*SQRT_TABLE_BITS*/ preShift));

    /* The index has SQRT_TABLE_BITS +1 valid bits here. Clear the other bits. */
    index &= (1 << (8 /*SQRT_TABLE_BITS*/ +1)) - 1; logic16();

    test();
    if (index==0) {
      /* Speed path: Do not look up the square root for a power of 2. */
      result_m = 0x5a82; move16();
    }
    else {
      /* Remove offset of half an interval */
      index = sub(index, 1);

      /* Now the lowest bit is shifted out */
      index = shr(index, 1);

      /* Fetch sqrt(Mantissa) from table: */
      result_m = sqrtTable[index];  move16();
    }

    /* Make exponent even: */
    logic16(); test();
    if ((input_e & 1)!=0) {
      result_m = mult(result_m, 0x5a82);
      input_e = add((Word16)input_e, 1);
    }

    /* Divide exponent by 2 (squareroot) */
    result_e = shr(input_e, 1);

  }
  else {
    result_m = 0; move16();
    result_e = -SHORT_BITS;  move16();
  }

  /* Write result */
  *mantissa = result_m; move16();
  *exponent = result_e; move16();
}


Word32 ffr_divide16 (Word32 op1, /*!< divident */ 
                     Word32 op2  /*!< divisor */
                    )
{
  Word32 quot, v;
  UWord32 u;
  Word16 k, sign;

  quot = 0;                   move32();
  v    = op2;                 move32();
  k    = 16 - 1;              move16();
  sign = 0;                   move16();

  
  test();
  if(op1 < 0){
    u = L_negate(op1);
    sign^=1;  logic16();
  }
  else {
    u = op1;  move32();
  }

  test();
  if(v < 0){
    v = L_negate(v);
    sign^=1;  logic16();
  }

  assert(u < (UWord32) v);

  /* To Overcome the overflow problem */
  u = L_shr(u, 1);
  v = L_shr(v, 1);

  test();
  if (u != 0){
    test(); sub(k,1);
    while (k--){
      test(); sub(k,1);
      quot = L_shl(quot, 1);
      u = L_shl(u, 1); /* u  = u << 1; */
      test(); L_sub(u,v); 
      if (u >= (UWord32) v) {
        u = L_sub(u, v); /* u-= v; */
        quot = L_add(quot, 1);
      }
    }
  }
  
  test();
  if(sign)
    quot = L_negate(quot);


  return quot;
}

/* calculate $1/sqrt(x)$ with a minimax polynomial, and subsequent convergent
 iterations.
 \return 2Q30 representation of result.
*/
static __inline Word32 reciprt(Word32 x) /*!< fixed point operand in [0.25, 1.0] */
{
  static const Word32 PLUSONE2Q30 = 0x40000000;
  Word32 a  = L_add(0x900ebee0, fixmul_32x16b(x, 0x39d9));
  /* a is now 3Q29 */
  Word32 iy = L_add(0x573b645a, fixmul_32x16t(x, a));
  /* iy is 3Q29 + 3Q29 * 1Q31 = 3Q29 */

  iy = L_shl(iy, 1); /* 2Q30 from 3Q29. Cannot overflow since iy <= 1.96. */

  /* now refine result by inverse sqrt iterations:

     iy = iy + (1-x.*iy.*iy).*iy/2

     Each iteration doubles the number of correct digits. */

  a =  fixmul(x,iy); /* 1Q31 * 2Q30 = 2Q30 */
  a =  L_sub(PLUSONE2Q30, L_shl(fixmul(a,iy), 1)); /* 2Q30 * 2Q30 = 3Q29, and back to 2Q30 */
  iy = L_add(iy,fixmul(a,iy)); /* 2Q30 * 2Q30 = 3Q29 = (0.5*2Q30) */

  /* Accuracy now better than 8 bits */

  a =  fixmul(x,iy); /* 1Q31 * 2Q30 = 2Q30 */
  a =  L_sub(PLUSONE2Q30, L_shl(fixmul(a,iy), 1)); /* 2Q30 * 2Q30 = 3Q29, and back to 2Q30 */
  iy = L_add(iy,fixmul(a,iy)); /* 2Q30 * 2Q30 = 3Q29 = (0.5*2Q30) */

  /* Accuracy now better than 16 bits */

  a =  fixmul(x,iy); /* 1Q31 * 2Q30 = 2Q30 */
  a =  L_sub(PLUSONE2Q30, L_shl(fixmul(a,iy), 1)); /* 2Q30 * 2Q30 = 3Q29, and back to 2Q30 */
  iy = L_add(iy,fixmul(a,iy)); /* 2Q30 * 2Q30 = 3Q29 = (0.5*2Q30) */

  /* Accuracy better than +/- 5 ulp */

  return iy;
}

Word32 ffr_sqrt(Word32 op,        /*!< Operand to square root (0.0 ... 1) */
                Word32 accuracy)  /*!< Number of valid bits that will be calculated */
{
  Word32 y;
  Word16 e;
  (void)accuracy; /* disregard accuracy input argument */

  test();
  if (op == 0) return 0; /* treat this as special case */

  /* first, normalize x so that x in [0.25,1] */
  e = ffr_norm32(op) & ~1 ; /* only even exponent allowed */                logic16();
  op = L_shl(op, e);
  e = shr(e, 1); /* sqrt() action on exponent is e/2 */

  /* now calculate op * (1/sqrt(op)) = sqrt(op) */
  op = fixmul(reciprt(op),op) ;

  /* return the normalized result. e-1 because fastisqrt output is 2Q30. */
  y = L_shr(op, sub(e,1));

  return y;
}


Word16 ffr_norm32(Word32 a)
{
  Word16 a16;
  Word16 r = 0 ;      move16();

  test();
  if ( a < 0 ) {
    a = ~a; logic32();
  }

  test(); logic32();
  if (0 == (a & 0x7fff8000)) {
    a16 = extract_l(a);
    r = add(r, 16);
    test(); logic16();
    if (0 == (a16 & 0x7f80)) {
      r = add(r, 8 );
      test(); logic16();
      if (0 == (a16 & 0x0078)) {
        r = add(r, 4 );
        test(); logic16();
        if (0 == (a16 & 0x0006)) {
          r = add(r, 2 );
          test(); logic16();
          if (0 == (a16 & 0x0001)) {
            r = add(r, 1 );
          }
        }
        else {
          test(); logic16();
          if (0 == (a16 & 0x0004)) {
            r = add(r, 1 );
          }
        }
      }
      else {
        test(); logic16();
        if (0 == (a16 & 0x0060)) {
          r = add(r, 2 );
          test(); logic16();
          if (0 == (a16 & 0x0010)) {
            r = add(r, 1 );
          }
        }
        else {
          test(); logic16();
          if (0 == (a16 & 0x0040)) {
            r = add(r, 1 );
          }
        }
      }
    } 
    else { 
      test(); logic16();
      if (0 == (a16 & 0x7800)) {
        r = add(r, 4 );
        test(); logic16();
        if (0 == (a16 & 0x0600)) {
          r = add(r, 2 );
          test(); logic16();
          if (0 == (a16 & 0x0100)) {
            r = add(r, 1 );
          }
        }
        else {
          test(); logic16();
          if (0 == (a16 & 0x0400)) {
            r = add(r, 1 );
          }
        }
      }
      else {
        test(); logic16();
        if (0 == (a16 & 0x6000)) {
          r = add(r, 2 );
          test(); logic16();
          if (0 == (a16 & 0x1000)) {
            r = add(r, 1 );
          }
        }
        else {
          test(); logic16();
          if (0 == (a16 & 0x4000)) {
            r = add(r, 1 );
          }
        }
      }
    }
  }
  else {
    a16 = extract_h(a);
    test(); logic16();
    if (0 == (a16 & 0x7f80)) {
      r = add(r, 8 );
      test(); logic16();
      if (0 == (a16 & 0x0078)) {
        r = add(r, 4 );
        test(); logic16();
        if (0 == (a16 & 0x0006)) {
          r = add(r, 2 );
          test(); logic16();
          if (0 == (a16 & 0x0001)) {
            r = add(r, 1 );
          }
        }
        else {
          test(); logic16();
          if (0 == (a16 & 0x0004)) {
            r = add(r, 1 );
          }
        }
      }
      else {
        test(); logic16();
        if (0 == (a16 & 0x0060)) {
          r = add(r, 2 );
          test(); logic16();
          if (0 == (a16 & 0x0010)) {
            r = add(r, 1 );
          }
        }
        else {
          test(); logic16();
          if (0 == (a16 & 0x0040)) {
            r = add(r, 1 );
          }
        }
      }
    }
    else {
      test(); logic16();
      if (0 == (a16 & 0x7800)) {
        r = add(r, 4 );
        test(); logic16();
        if (0 == (a16 & 0x0600)) {
          r = add(r, 2 );
          test(); logic16();
          if (0 == (a16 & 0x0100)) {
            r = add(r, 1 );
          }
        }
        else {
          test(); logic16();
          if (0 == (a16 & 0x0400)) {
            r = add(r, 1 );
          }
        }
      }
      else {
        test(); logic16();
        if (0 == (a16 & 0x6000)) {
          r = add(r, 2 );
          test(); logic16();
          if (0 == (a16 & 0x1000)) {
            r = add(r, 1 );
          }
        }
        else {
          test(); logic16();
          if (0 == (a16 & 0x4000)) {
            return 1;
          }
        }
      }
    }
  }
  
  return r ;
}
