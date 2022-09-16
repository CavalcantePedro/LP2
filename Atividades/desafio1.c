/*Faça um programa em C que solicite do usuário um valor inteiro e crie (clone) este valor recebido em quantidade de processos. 
Os processos executarão uma função para que durmam 60s. 
O processo original (em sua função principal) posteriormente deve dormir por 20s e depois finalizar todos os processos clonados antes que estes acordem.*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>

int main()
{
    int quant_procs_clonados;
    int original_pid = getpid(); //Guardando o pid do processo original
    int rtn_fork;

    printf("O pid do pocesso orginal é: %d\n", original_pid);
    printf("Qual a quantidade de clones que vai ser criados ?");
    scanf("%d", &quant_procs_clonados);
    int pids_clones[quant_procs_clonados];

    if(quant_procs_clonados > 0) 
    {
        rtn_fork = fork(); // primeiro clone criado
        pids_clones[0] = rtn_fork;
        quant_procs_clonados --; //subtraindo a quantidade de processos que tem que ser clonados
        if(rtn_fork > 0)//garantindo que so o processo original irá criar clones
        {
            for (int i = 0; i < quant_procs_clonados; i++)
            {
                if(rtn_fork > 0)//garantindo (mais uma vez) que so o processo original irá criar clones
                {
                    rtn_fork = fork();//criando mais clones
                    pids_clones[i+1] = rtn_fork;
                }
            } 
        } 
    }

    if (getpid() != original_pid) //Dizendo o quanto os clones tem que dormir
    { 
        printf("Sou um clone e meu pid é: %d\n", getpid());
        sleep(60);
        printf("Sou um clone e acordei antes de ser finalizado :)");
           
    }
    else//dizendo o quanto o original deve dormir
    {
        printf("Sou o original e meu pid é: %d\n", getpid());
        sleep(20);
        printf("Finalizando os processos clonados antes deles acordarem\n");
        for (int i = 0; i < quant_procs_clonados+1; i++)
        {
            int rtn_kill;
            rtn_kill = kill(pids_clones[i], SIGHUP);
            if (!rtn_kill)
            {
                printf("O clone foi encerrado com sucesso, seu pid era: %d\n",pids_clones[i]);
            }
            else
            {
                printf("ERRO AO FINALIZAR");
            }
        }
    }
    printf("Processo original se finalizando, meu pid era: %d\n", getpid());

    return 0;
}