#ifndef DIVIDE_C
#define DIVIDE_C

#include "divide.h"

void divide_controle(char operando1[], char operando2[], no** ppmaq_pilha)
{
    char valor[TAMANHO_MEDIO];

    // string sem o sinal 
    char op1_sem_sinal[TAMANHO_MEDIO];
    char op2_sem_sinal[TAMANHO_MEDIO];
    // pega sinal dos dois operandos
    bool op1_positivo;
    bool op2_positivo;

    // limpa a string contida em valor 
    memset(valor, '\0', TAMANHO_MEDIO);

    // pega sinal dos dois operandos
    op1_positivo = operando_positivo(operando1);
    op2_positivo = operando_positivo(operando2);
    
    // pega os dois inteiros sem sinal 
    obtem_sem_sinal(operando1, op1_sem_sinal);
    obtem_sem_sinal(operando2, op2_sem_sinal);

    // chama funcao conveniente
    if ((op1_positivo && op2_positivo) || (!op1_positivo && !op2_positivo))
    {
        divide(op1_sem_sinal, op2_sem_sinal, valor);
    } 
    else
    {
        divide(op1_sem_sinal, op2_sem_sinal, valor);
        muda_sinal(valor);
    }

    // poe valor na maquina de pilha
    push(valor, ppmaq_pilha);
}

void divide(char dividendo[], char divisor[], char valor[])
{
    uint32_t temp[ELEMENTOS];
    char num_a_dividir[TAMANHO_MEDIO];
    char parte_num_a_dividir[TAMANHO_MEDIO];

    int tam_divisor;
    int digito;

    // inicialmente o numero a dividir eh o dividendo 
    strcpy(num_a_dividir, dividendo);

    // enquanto o numero a dividir for maior que o dividendo
    while (analisa_maior_string(num_a_dividir, divisor) != MENOR)
    {
        // pega comprimento do numero a dividir e do divisor
        tam_divisor = strlen(divisor);

        // obtem parte do numero a dividir a ser analisada 
        strncpy(parte_num_a_dividir, num_a_dividir, tam_divisor);
        parte_num_a_dividir[tam_divisor] = '\0';
        if (analisa_maior_string(parte_num_a_dividir, divisor) == MENOR)
        {
            strncpy(parte_num_a_dividir, num_a_dividir, tam_divisor + 1);
            parte_num_a_dividir[tam_divisor + 1] = '\0';
        }

        // determina digito do quociente a ser anexado a valor
        digito = determina_digito_quociente(parte_num_a_dividir, divisor, valor);

        // pega proximo numero a dividir
        pega_prox_num_dividir(num_a_dividir, parte_num_a_dividir, digito, divisor, valor);

        // limpa o numero a dividir, retirando zeros a esquerda
        converte_operando(num_a_dividir, temp);
        converte_operando_string(temp, num_a_dividir);
    }

    // se valor estiver vazio, poe zero em valor 
    if (strlen(valor) == 0)
    {
        valor[0] = '0';
        valor[1] = '\0';
    }
}

int determina_digito_quociente(char dividendo[], char divisor[], char valor[])
{
    char digito[TAMANHO_PEQUENO];
    char resultado[TAMANHO_MEDIO];

    // itera pelos numeros de 1 a 9 
    for (int i = 1; i < 10; i++)
    {
        // obtem numero atual como string
        sprintf(digito, "%d", i);

        // multiplica divisor pelo digito corrente
        multiplica(divisor, digito, resultado);

        // se o resultado for maior que o dividendo
        if (analisa_maior_string(resultado, dividendo) == MAIOR)
        { 
            // anexa a valor o digito anterior 
            sprintf(digito, "%d", i-1);
            strcat(valor, digito);

            // retorna digito
            return i-1;
        }

        // se o resultado for igual 
        if (analisa_maior_string(resultado, dividendo) == IGUAL)
        { 
            // anexa a valor o digito anterior 
            sprintf(digito, "%d", i);
            strcat(valor, digito);

            // retorna digito
            return i;
        }
    }
    // se chegou aqui, eh um nove
    sprintf(digito, "%d", 9);
    strcat(valor, digito);
    return 9;
}

void pega_prox_num_dividir(char num_a_dividir[], char parte_num_a_dividir[], int dig, char divisor[], char valor[])
{
    char res_mult[TAMANHO_MEDIO]; 
    char res_sub[TAMANHO_MEDIO]; 
    char str_dig[TAMANHO_PEQUENO];
    char temp[TAMANHO_MEDIO];
    int index; 

    // calcula resultado da subtracao entre a parte do numero a ser dividida e o produto do divisor pelo digito
    // anexado ao quociente    
    sprintf(str_dig, "%d", dig);
    multiplica(divisor, str_dig, res_mult);
    subtrai(parte_num_a_dividir, res_mult, res_sub);

    // o proximo numero a dividir sera o resultado da subtracao mais os digitos que caem 
    strcpy(temp, res_sub);

    // pega posicao em que estamos no numero a dividir - eh o indice do primeiro numero apos os digitos
    // que compoe parte_num_a_dividir
    index = strlen(parte_num_a_dividir); // nao coloca o + 1 pois array comeca em zero 

    // enquanto o resultado da subtracao for menor que o divisor
    while (analisa_maior_string(res_sub, divisor) == MENOR)
    {
        // se ainda ha digito para "cair" do numero a dividir 
        if (index < strlen(num_a_dividir))
        {
            // cai o digito, anexa-se ao resultado da subtracao 
            str_dig[0] = num_a_dividir[index];
            str_dig[1] = '\0';
            strcat(res_sub, str_dig);
            
            // incrementa index
            index++;

            // se o divisor continua maior do que o resultado da subtracao 
            if (analisa_maior_string(res_sub, divisor) == MENOR)
            {
                //  acrescenta um zero no valor
                sprintf(str_dig, "%d", 0);
                strcat(valor, str_dig); 
            }
        }

        // senao, sai do loop
        else 
        {
            break;
        } 
    }

    // atualiza o proximo numero a dividir
    index = strlen(parte_num_a_dividir); // necessario, pois index foi alterado la no loop
    for (int i = strlen(temp); index < strlen(num_a_dividir); i++)
    {
        temp[i] = num_a_dividir[index];
        index++;
    }
    temp[strlen(num_a_dividir)] = '\0';
    
    strcpy(num_a_dividir, temp); 
}

int analisa_maior_string(char string1[], char string2[])
{
    uint32_t op1[ELEMENTOS];
    uint32_t op2[ELEMENTOS];

    // converte string para uma sequencia de blocos de 9 digitos cada, representavel em um 
    // inteiro de 32 bits
    converte_operando(string1, op1);
    converte_operando(string2, op2);

    // retorna valor dos operandos 
    return analisa_maior(op1, op2);
}

#endif
