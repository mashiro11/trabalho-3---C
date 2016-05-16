Trabalho 3 - C 
Integrantes: 
Ana Carolina - 11/0107578
Gabriel Ferreira - 14/0140131 
Thiago André - 12/0079101
Yan Trindade - 11/0152794

1. Expressão Aritmética
  O programa começa recebendo uma expressão aritmética por linha de comando passada pelo usuário. Caso tal expressão não seja passada na hora de chamar o programa, o usuário pode digitá-la. A expressão aritmética é analisada como uma string, podendo conter parênteses, mas deve estar necessariamente correta. A string é então separada em tokens, que irão representar os números e os operandos. 

2. Máquina de pilha
  A máquina de pilha foi implementada como um stack que armazena strings, as quais podem ser numeros de até 256 bits ou operandos. O algoritmo, depois de construida a lista de tokens, poe os operandos e os operadores na ordem pos-fixada na maquina de pilha. Quando um operando eh recebido pela máquina de pilha, a conta eh feita com os operadores no topo da pilha e o resultado eh salvo na pilha. 

3. Representacao de inteiros de 256 bits
  Os inteiros de 256 bits são representados como strings. Para converter uma string para o inteiro correspondente, divide-se a string em blocos de 9 digitos. Cada um desses blocos pode ser entao representado como um inteiro de 32 bits (disponível em C). A string como um todo é convertida entao em um vetor de inteiros de 32 bits. Para conseguirmos representar inteiros de até 256 bits, é suficiente colocar nove elementos para o vetor de inteiros em questao. 
  A técnica utilizada é genérica e pode ser extendia para inteiros maiores que 256 bits, bastando para isso aumentar o número de elementos no vetor de inteiros de 32 bits. As principais dificuldades enfrentadas ocorreram na hora de se realizar a conversao da string para vetor de 32 bits e na hora de se determinar o impacto que um resultado em um bloco de nove digitos teria nos demais blocos de nove digítos. Apesar disso, até onde testamos, conseguimos realizar as quatro operações pedidas :)
