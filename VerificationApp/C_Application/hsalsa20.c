#define ROUNDS 20

#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint32;

extern int salsa20_counter;
extern int hsalsa20_counter;

static uint32 rotate(uint32 u,int c)
{
    return (u << c) | (u >> (32 - c));
}

static uint32 load_littleendian(const unsigned char *x)
{
    return
      (uint32) (x[0]) \
    | (((uint32) (x[1])) << 8) \
    | (((uint32) (x[2])) << 16) \
    | (((uint32) (x[3])) << 24)
    ;
}

static void store_littleendian(unsigned char *x,uint32 u)
{
    x[0] = u; u >>= 8;
    x[1] = u; u >>= 8;
    x[2] = u; u >>= 8;
    x[3] = u;
}

int my_crypto_core_hsalsa20(
            unsigned char *out,
      const unsigned char *in,
      const unsigned char *k,
      const unsigned char *c
)
{
    uint32 x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15;
    int i;

    x0 = load_littleendian(c + 0);
    x1 = load_littleendian(k + 0);
    x2 = load_littleendian(k + 4);
    x3 = load_littleendian(k + 8);
    x4 = load_littleendian(k + 12);
    x5 = load_littleendian(c + 4);
    x6 = load_littleendian(in + 0);
    x7 = load_littleendian(in + 4);
    x8 = load_littleendian(in + 8);
    x9 = load_littleendian(in + 12);
    x10 = load_littleendian(c + 8);
    x11 = load_littleendian(k + 16);
    x12 = load_littleendian(k + 20);
    x13 = load_littleendian(k + 24);
    x14 = load_littleendian(k + 28);
    x15 = load_littleendian(c + 12);

    for (i = ROUNDS;i > 0;i -= 2)
    {
         x4 ^= rotate( x0+x12, 7);
         x8 ^= rotate( x4+ x0, 9);
        x12 ^= rotate( x8+ x4,13);
         x0 ^= rotate(x12+ x8,18);
         x9 ^= rotate( x5+ x1, 7);
        x13 ^= rotate( x9+ x5, 9);
         x1 ^= rotate(x13+ x9,13);
         x5 ^= rotate( x1+x13,18);
        x14 ^= rotate(x10+ x6, 7);
         x2 ^= rotate(x14+x10, 9);
         x6 ^= rotate( x2+x14,13);
        x10 ^= rotate( x6+ x2,18);
         x3 ^= rotate(x15+x11, 7);
         x7 ^= rotate( x3+x15, 9);
        x11 ^= rotate( x7+ x3,13);
        x15 ^= rotate(x11+ x7,18);
         x1 ^= rotate( x0+ x3, 7);
         x2 ^= rotate( x1+ x0, 9);
         x3 ^= rotate( x2+ x1,13);
         x0 ^= rotate( x3+ x2,18);
         x6 ^= rotate( x5+ x4, 7);
         x7 ^= rotate( x6+ x5, 9);
         x4 ^= rotate( x7+ x6,13);
         x5 ^= rotate( x4+ x7,18);
        x11 ^= rotate(x10+ x9, 7);
         x8 ^= rotate(x11+x10, 9);
         x9 ^= rotate( x8+x11,13);
        x10 ^= rotate( x9+ x8,18);
        x12 ^= rotate(x15+x14, 7);
        x13 ^= rotate(x12+x15, 9);
        x14 ^= rotate(x13+x12,13);
        x15 ^= rotate(x14+x13,18);
    }

    printf("2ndLevelKey[] is:\n");
    printf("x7 = 0x%08x\n", x9);
    printf("x6 = 0x%08x\n", x8);
    printf("x5 = 0x%08x\n", x7);
    printf("x4 = 0x%08x\n", x6);
    printf("x3 = 0x%08x\n", x15);
    printf("x2 = 0x%08x\n", x10);
    printf("x1 = 0x%08x\n", x5);
    printf("x0 = 0x%08x\n", x0);
    printf("\n");
    
    store_littleendian(out + 0,x0);
    store_littleendian(out + 4,x5);
    store_littleendian(out + 8,x10);
    store_littleendian(out + 12,x15);
    store_littleendian(out + 16,x6);
    store_littleendian(out + 20,x7);
    store_littleendian(out + 24,x8);
    store_littleendian(out + 28,x9);

    hsalsa20_counter++;

    return 0;
}


int my_crypto_core_salsa20(
            unsigned char *out,
      const unsigned char *in,
      const unsigned char *k,
      const unsigned char *c
)
{
  uint32 x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15;
  uint32 j0, j1, j2, j3, j4, j5, j6, j7, j8, j9, j10, j11, j12, j13, j14, j15;
  int i;

  j0 = x0 = load_littleendian(c + 0);
  j1 = x1 = load_littleendian(k + 0);
  j2 = x2 = load_littleendian(k + 4);
  j3 = x3 = load_littleendian(k + 8);
  j4 = x4 = load_littleendian(k + 12);
  j5 = x5 = load_littleendian(c + 4);
  j6 = x6 = load_littleendian(in + 0);
  j7 = x7 = load_littleendian(in + 4);
  j8 = x8 = load_littleendian(in + 8);
  j9 = x9 = load_littleendian(in + 12);
  j10 = x10 = load_littleendian(c + 8);
  j11 = x11 = load_littleendian(k + 16);
  j12 = x12 = load_littleendian(k + 20);
  j13 = x13 = load_littleendian(k + 24);
  j14 = x14 = load_littleendian(k + 28);
  j15 = x15 = load_littleendian(c + 12);


    // printf("Salsa20 Init\n", i);
    // printf("x0 = 0x%08x\n", x0);
    // printf("x1 = 0x%08x\n", x1);
    // printf("x2 = 0x%08x\n", x2);
    // printf("x3 = 0x%08x\n", x3);
    // printf("x4 = 0x%08x\n", x4);
    // printf("x5 = 0x%08x\n", x5);
    // printf("x6 = 0x%08x\n", x6);
    // printf("x7 = 0x%08x\n", x7);
    // printf("x8 = 0x%08x\n", x8);
    // printf("x9 = 0x%08x\n", x9);
    // printf("x10 = 0x%08x\n", x10);
    // printf("x11 = 0x%08x\n", x11);
    // printf("x12 = 0x%08x\n", x12);
    // printf("x13 = 0x%08x\n", x13);
    // printf("x14 = 0x%08x\n", x14);
    // printf("x115 = 0x%08x\n", x15);

  for (i = ROUNDS;i > 0;i -= 2) {
     x4 ^= rotate( x0+x12, 7);
     x8 ^= rotate( x4+ x0, 9);
    x12 ^= rotate( x8+ x4,13);
     x0 ^= rotate(x12+ x8,18);
     x9 ^= rotate( x5+ x1, 7);
    x13 ^= rotate( x9+ x5, 9);
     x1 ^= rotate(x13+ x9,13);
     x5 ^= rotate( x1+x13,18);
    x14 ^= rotate(x10+ x6, 7);
     x2 ^= rotate(x14+x10, 9);
     x6 ^= rotate( x2+x14,13);
    x10 ^= rotate( x6+ x2,18);
     x3 ^= rotate(x15+x11, 7);
     x7 ^= rotate( x3+x15, 9);
    x11 ^= rotate( x7+ x3,13);
    x15 ^= rotate(x11+ x7,18);
     x1 ^= rotate( x0+ x3, 7);
     x2 ^= rotate( x1+ x0, 9);
     x3 ^= rotate( x2+ x1,13);
     x0 ^= rotate( x3+ x2,18);
     x6 ^= rotate( x5+ x4, 7);
     x7 ^= rotate( x6+ x5, 9);
     x4 ^= rotate( x7+ x6,13);
     x5 ^= rotate( x4+ x7,18);
    x11 ^= rotate(x10+ x9, 7);
     x8 ^= rotate(x11+x10, 9);
     x9 ^= rotate( x8+x11,13);
    x10 ^= rotate( x9+ x8,18);
    x12 ^= rotate(x15+x14, 7);
    x13 ^= rotate(x12+x15, 9);
    x14 ^= rotate(x13+x12,13);
    x15 ^= rotate(x14+x13,18);
    
  }

    x0 += j0;
    x1 += j1;
    x2 += j2;
    x3 += j3;
    x4 += j4;
    x5 += j5;
    x6 += j6;
    x7 += j7;
    x8 += j8;
    x9 += j9;
    x10 += j10;
    x11 += j11;
    x12 += j12;
    x13 += j13;
    x14 += j14;
    x15 += j15;

    // printf("Salsa20\n", i);
    // printf("x15 = 0x%08x\n", x15);
    // printf("x14 = 0x%08x\n", x14);
    // printf("x13 = 0x%08x\n", x13);
    // printf("x12 = 0x%08x\n", x12);
    // printf("x11 = 0x%08x\n", x11);
    // printf("x10 = 0x%08x\n", x10);
    // printf("x9 = 0x%08x\n", x9);
    // printf("x8 = 0x%08x\n", x8);
    // printf("x7 = 0x%08x\n", x7);    
    // printf("x6 = 0x%08x\n", x6);
    // printf("x5 = 0x%08x\n", x5);
    // printf("x4 = 0x%08x\n", x4);
    // printf("x3 = 0x%08x\n", x3);
    // printf("x2 = 0x%08x\n", x2);
    // printf("x1 = 0x%08x\n", x1);    
    // printf("x0 = 0x%08x\n", x0);

   // getchar();

    store_littleendian(out + 0,x0);
    store_littleendian(out + 4,x1);
    store_littleendian(out + 8,x2);
    store_littleendian(out + 12,x3);
    store_littleendian(out + 16,x4);
    store_littleendian(out + 20,x5);
    store_littleendian(out + 24,x6);
    store_littleendian(out + 28,x7);
    store_littleendian(out + 32,x8);
    store_littleendian(out + 36,x9);
    store_littleendian(out + 40,x10);
    store_littleendian(out + 44,x11);
    store_littleendian(out + 48,x12);
    store_littleendian(out + 52,x13);
    store_littleendian(out + 56,x14);
    store_littleendian(out + 60,x15);

    salsa20_counter++;

    return 0;
}
