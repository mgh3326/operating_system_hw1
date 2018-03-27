#include <stdio.h>
#include <stdlib.h>

#define WDSZ 64

/* bit functions */
inline void bit_set(unsigned long *bf, unsigned char n) { *bf |= (1 << n); }
inline void bit_clear(unsigned long *bf, unsigned char n) { *bf &= ~(1 << n); }
inline void bit_toggle(unsigned long *bf, unsigned char n) { *bf ^= (1 << n); }

/* simple return of binary string */
char *binstr(unsigned long n);

int main(int argc, char **argv)
{

    unsigned long bf = (argc > 1) ? strtoul(argv[1], NULL, 10) : 13;

    printf("\n original value  : %3lu  (%s)\n", bf, binstr(bf));

    bit_set(&bf, 1);
    printf(" set bit 1       : %3lu  (%s)\n", bf, binstr(bf));

    bit_clear(&bf, 1);
    printf(" clear bit 1     : %3lu  (%s)\n", bf, binstr(bf));

    bit_toggle(&bf, 1);
    printf(" toggle bit 1    : %3lu  (%s)\n\n", bf, binstr(bf));

    return 0;
}

/* simple return of binary string */
char *binstr(unsigned long n)
{

    static char s[WDSZ + 1] = {0};
    char *p = s + WDSZ;

    while (n)
    {
        p--;
        *p = (n & 1) ? '1' : '0';
        n >>= 1;
    }
    return p;
}
