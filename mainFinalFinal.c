//
//  main.c
//  PODA
//
//  Created by Thiago Henrique on 03/09/2018.
//  Copyright © 2018 Thiago Henrique. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define f(x) ((x*x*x)-18) //RegulaFalsi

#define EQUATION(x) (x)*(x)*(x) - 3*(x) - 8 //secantes

#define I 2 //muller

float g(float x)
{
    return cos(x) - x*exp(x);
}


int main(void) {
    int escolha=0;
    while (escolha!= '4'){
        printf("\n\tMENU PRINCIPAL - METODOS:");
        printf("\n\t-------------------------------------");
        printf("\n\t1. Falsa Posicao");
        printf("\n\t2. Secantes");
        printf("\n\t3. Muller");
        printf("\n\t4. SAIR");
        printf("\n\tDIGITE SUA ESCOLHA:");
        scanf("%d", &escolha);
        switch(escolha){
                case 1:
                printf("\nMetodo da falsa posicao selecionado %c \n", 1 );
                regulaFalsi();
                break;
                case 2:
                printf("\nMetodo das secantes selecionado %c \n", 2);
                secantes();
                break;
                case 3:
                printf("\nMetodo de Muller selecionado %c \n", 3);
                muller();
                break;
                case 4:
                printf("\nFinalizando a aplicacao... %c", 4);
                exit(0);
                default:
                printf("\n\nSELECAO INVALIDA... TENTAR NOVAMENTE");
        }
    }
    return 0;
}

int regulaFalsi (){
 float a=0,b=0,error=0,c,cold;
    int i=0;
    printf("Digite o intervalo: ");
    scanf("%f %f",&a,&b); //valores iniciais do intervalo (resolver eq)
    if((f(a)*f(b))>0){ //a*b não pode ser positivo
        printf("Saida de intervalo invalida!");
        exit(1);
    }
    else if(f(a)==0 || f(b)==0){
        printf("Raiz e uma das fronteiras do intervalo. Raiz igual a %f\n",f(a)==0?a:b);
        exit(0);
    }
    printf("Ite\ta\t\tb\t\tc\t\tf(c)\t\terror\n"); //print da tabela
    do{
        cold=c; //C old guarda C para que assuma um novo valor
        c=(((a*f(b))-(b*f(a)))/(f(b)-f(a)));
        printf("%2d\t%4.6f\t%4.6f\t%4.6f\t%4.6f\t",i++,a,b,c,f(c)); //iteracao, valor de A, B, C atual e func C
        if(f(c)==0){
            break;
        }else if(f(a)*f(c)<0){
            b=c;
        }else a=c;
        error=fabs(c-cold);
        if(i==1){
            printf("----\n");
        }else printf("%4.6f\n",error);
        
    }while(error>0.00005); //erro minimo
    printf(" Raiz igual a %4.6f \n",c);
    return 0;
}

int secantes(){
     float interval_start, interval_end, midpoint; //intervalos e ponto médio
    float a, b, temp, allowed_error;
    printf("\nDigite o valor de partida do intervalo:\t");
    scanf("%f", &interval_start);
    printf("\nDigite o valor final do intervalo:\t");
    scanf("%f", &interval_end);
    printf("\nDigite o erro permitido:\t");
    scanf("%f", &allowed_error);
    printf("\n");
    printf("\nInicio\t\tFim\t\tMediana\tfunc(Inicio)\tfunction(Final)");
    printf("\n");
    while(temp > allowed_error)
    {
        a = EQUATION(interval_start);
        b = EQUATION(interval_end);
        midpoint = interval_end - ((b * (interval_end - interval_start)) / (b - a)); //ponto médio
        printf("\n%f\t%f\t%f\t%f\t%f", interval_start, interval_end, midpoint, a, b); //informações
        interval_start = interval_end;
        interval_end = midpoint;
        if(b < 0)
        {
            temp = fabs(b); //valor absoluto
        }
        else
        {
            temp = b;
        }
    }
    printf("\n\nRaiz da equacao: %f\n", midpoint);
}

 muller(){ //coeficiente da parabolaa que passa por 3 pontos
    int i, itr, maxmitr; //contador, iteracao, iteracao maxima
    float x[4], li, di, mu, s, l, allerr; //array de aprox inicial
    printf("\nDigite os tres valores de tentativa:\n"); //valores a serem substituidos na formula para obter
                                                       //a intersecao com o eixo x
    for (i=I-2; i<3; i++)
        scanf("%f", &x[i]);
    printf("Digite o erro permitido e o maximo de iteracoes:\n");
    scanf("%f %d", &allerr, &maxmitr); //erro absoluto, maximo de iteracoes
    for (itr=1; itr<=maxmitr; itr++)
    {
        li = (x[I] - x[I-1]) / (x[I-1] - x[I-2]);
        di = (x[I] - x[I-2]) / (x[I-1] - x[I-2]);
        mu = g(x[I-2])*li*li - g(x[I-1])*di*di + g(x[I])*(di+li);
        s = sqrt ((mu*mu - 4*g(x[I])*di*li*(g(x[I-2])*li - g(x[I-1])*di + g(x[I]))));
        if (mu < 0)
            l = (2*g(x[I])*di)/(-mu+s);
        else
            l = (2*g(x[I])*di)/(-mu-s);
        x[I+1] = x[I] + l*(x[I] - x[I-1]);
        printf("Na iteracao no. %3d, x = %7.5f\n", itr, x[I+1]);
        if (fabs (x[I+1] - x[I]) < allerr)
        {
            printf("Apos %3d iteracoes, a raiz e %6.4f\n", itr, x[I+1]);
            return 0;
        }
        for (i=I-2; i<3; i++)
            x[i] = x[i+1];
    }
    printf("A solucao requerida nao converge ou iteracoes sao insuficientes\n");
    return 1;
}
