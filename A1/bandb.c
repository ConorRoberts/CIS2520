#include "bandb.h"

void getbytes(unsigned char dest[], int bytes, void *src, int reverse)
{
    int i;
    unsigned char *src_copy = src;
    if (reverse)
        for (i = 1; i < bytes; i++)
            src_copy++;

    for (i = reverse ? bytes : 0; reverse ? i > 0 : i < bytes; reverse ? i-- : i++)
    {
        dest[reverse ? bytes - i : i] = reverse ? *src_copy-- : *src_copy++;
    }

    dest += '\0';
}

void getbits(char dest[], int bytes, void *src, int start, int end)
{
    int start_real = (bytes*8)-start-1;
    int end_real = start-end;

    src = *src << start_real;
    printf("GAY %d %d\n",start_real,end_real);
//     for(i=start_real;i<end_real;i++){

//     }

    dest+='\0';
}

unsigned long long bits2ull(char *bits)
{

    unsigned long long result = 0;

    int length = strlen(bits);

    for (int i = 0; bits[i] != '\0'; i++)
    {
        result += (long long) (bits[i] == '1' ? 1 : 0) << (length - i - 1);
    }

    return result;
}

long long bits2ll(char *bits)
{
    long long result = 0;

    int length = strlen(bits);

    for (int i = 0; bits[i] != '\0'; i++)
    {
        result += (long long) (bits[i] == '1' ? i == 0 ? -1 : 1 : 0) << (length - i - 1);
    }

    return result;
}

void spff(char *sign, char *exponent, char *significand, float *src)
{
    // float whole = *src > 0 ? floor(*src) : ceil(*src);
    // float fraction = *src-whole;
    // while (*src > 0 ? floor(fraction)<1 : ceil(fraction)>1){
    //     fraction*=10;
    // }
    // printf("%lf %lf\n",whole,fraction);
}
void dpff(char *sign, char *exponent, char *significand, double *src){

}