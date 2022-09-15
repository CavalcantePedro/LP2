#include <stdio.h>

int main(void)
{
    printf("pid do Pai: %d\n", getpid());
    execv("teste", NULL); //executa arqv de nome "teste"
    printf("EU TENHO UM SEGREDO PRA CONTAR\n"); // não chega nessa linha pois o arqv aberto mata o processo em andamento e pega seu pid
}