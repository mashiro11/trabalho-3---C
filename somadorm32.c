#include <stdio.h>
#include <stdint.h>
#define NUM_DOUBLEWORD 3
uint32_t* somaMultiplo32(int*, int*, int);

int main(int argc, char** argv){
    uint32_t numGrande1[]= {0x3fffffff, 0xffffffff, 0xffffffff};//numero grande positivo
    uint32_t numGrande2[]= {0x3fffffff, 0xffffffff, 0xffffffff};
    uint32_t *resultado = somaMultiplo32(numGrande1, numGrande2, NUM_DOUBLEWORD);
    printf("Resultado: ");
    for(int i = 0; i < NUM_DOUBLEWORD; i++) printf("%08x | ", resultado[i]);

}
uint32_t* somaMultiplo32(int *arg1, int *arg2, int multiplo){
    uint8_t overflow = 0;
    uint32_t leak = 0;
    uint32_t *result = (uint32_t*) calloc(multiplo, sizeof(uint32_t));
    for(int i = 0; i < multiplo; i++) *(result + i) = 0;//zera o vetor resultado

    uint32_t max_32bits;
    if(multiplo > 1){
        max_32bits = 0xFFFFFFFF;
    }else if(multiplo < 1){
        return NULL;
    }
    for(int i = multiplo - 1; i > -1; i--){
        if(i==0) max_32bits = 0x7FFFFFFF;
        if( *(arg1 + i) + *(result + i) > max_32bits - *(arg2 + i)){ //maior inteiro com sinal 32 bits
            if(i > 0){
                *(result + i - 1) = 1;
            }else{
                return NULL;
            }
            leak = *(arg1 + i) - 1 - (max_32bits - *(arg2 + i) );
            *(result + i) = leak;
        }else{
            printf("result[%d]: %x | arg1[%d]: %x | arg2[%d]: %x \n", i, *(result+i), i, *(arg1+i), i, *(arg2+i));
            *(result + i) += *(arg1 + i) + *(arg2 + i);//*(result+i) pode valer 1 por conda do overflow
        }
    }
    return result;
}
