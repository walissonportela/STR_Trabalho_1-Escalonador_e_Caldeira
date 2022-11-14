/*
SIMULADOR DE ESCALONEMANTO DE TAREFAS PARA RM E EDF
DANIEL MENESES DA ROCHA					495307
FRANCISCO SILVAN FELIPE DO CARMO			496641
JOAQUIM WALISSON PORTELA DE SOUSA			472152
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
//Definimos o numero de tarefas para 3.	
#define N 3

//Estrutura da tarefa	
struct PCD{
	int P;
	int C;
	int D;
};

int i, j;
int metodo;
	
//A main deve receber o arquivo declarado no momento da ezecução;	
int main(int argc, char *argv[]){
	

	struct PCD t1;
	struct PCD t2;
	struct PCD t3;

    FILE *sistema = fopen(argv[1], "r");
	
	if(sistema != NULL){
	    //Faz a leitura das tarefas em ordem de P, C e D dentro do arquivo txt.
	    fscanf(sistema,"P C D\n%d %d %d\n%d %d %d\n%d %d %d", &t1.P,  &t1.C,  &t1.D, &t2.P,  &t2.C,  &t2.D, &t3.P,  &t3.C,  &t3.D);
	    //Imprime as tarefas em ordem de P, C e D.
	    printf("P\tC\tD\n%d\t%d\t%d\n%d\t%d\t%d\n%d\t%d\t%d\n", t1.P,  t1.C,  t1.D, t2.P,  t2.C,  t2.D, t3.P,  t3.C,  t3.D);
	    
	    printf("\nEscolha o metodo de escalonamento \n");
	    printf("<1> EDF\n<2> RM\n<3> Sair\n");
	    scanf("%d", &metodo);
	    //system("clear");
	
	int periodo_total = fmax(t1.P, t2.P);
	    periodo_total = fmax(t3.P, periodo_total);
	
	char graf[N][periodo_total];
	
	for (i=0; i<N; i++){
	    for( j=0; j<periodo_total; j++){
	        graf[i][j]='-';
	    }
	}
	
	double util = ((1.0*t1.C/t1.P)+(1.0*t2.C/t2.P)+(1.0*t3.C/t3.P));
	//printf("%f\n", util);
	
	if(metodo == 1){
	
	    //teste de escalonabilidade
	if(util<=1){
	if(t1.D==t1.P && t2.D==t2.P && t3.D==t3.P){
	printf("\nO sistema e escalonavel.\n");
	}else
	printf("\nO sistema nao e escalonavel.\n");
	
	printf("Taxa de utilizacao = %f\n", util);
	
	int k1=0;
	int k2=0;
	int k3=0;
	int t1d=t1.D;
	int t2d=t2.D;
	int t3d=t3.D;
	int apt1=0;
	int apt2=0;
	int apt3=0;
	bool t1a=1;
	bool t2a=1;
	bool t3a=1;
	
	for(i=0; i<periodo_total; i++){
	    if(i >= apt1){
	        //printf("\n%d\tT1 esta apto.", i);
	        t1a=1;
	    }else{
	        //printf("T1 nao esta apto.");
	        t1a=0;
	    }
	    if(i >= apt2){
	        //printf("\n%d\tT2 esta apto.", i);
	        t2a=1;
	    }else{
	        //printf("T2 nao esta apto.");
	        t2a=0;
	    }
	    if(i >= apt3){
	        //printf("\n%d\tT3 esta apto.", i);
	        t3a=1;
	    }else{
	        //printf("T3 nao esta apto.");
	        t3a=0;
	    }
	    
	    if(t1a && t2a && t3a){
	
	        if((t1d <= t2d) && (t1d <= t3d)){
	        //printf("T1 eh a menor dead line."); 
	        graf[0][i]='o';
	        k1++;
	        }
	
	        if((t2d <= t3d) && (t2d <= t1d)){
	        //printf("T2 eh a menor dead line.");
	        graf[1][i]='o';
	        k2++;        
	        }
	
	        if((t3d <= t2d) && (t3d <= t1d)){
	        //printf("T3 eh a menor dead line.");
	        graf[2][i]='o';
	        k3++;
	        }
	    }
	    if(t1a && t2a && t3a != 1){
	        if(t1d <= t2d){
	        //printf("T1 eh a menor dead line."); 
	        graf[0][i]='o';
	        k1++;
	        }else{
	        //printf("T2 eh a menor dead line.");
	        graf[1][i]='o';
	        k2++;     
	        }
	    }
	    if(t1a && t3a && t2a != 1){
	        if(t3d <= t1d){
	        //printf("T3 eh a menor dead line.");
	        graf[2][i]='o';
	        k3++;
	        }else{
	        //printf("T1 eh a menor dead line."); 
	        graf[0][i]='o';
	        k1++;    
	        }
	    }
	    if(t2a && t3a && t1a != 1){
	        if(t3d <= t2d){
	        //printf("T3 eh a menor dead line.");
	        graf[2][i]='o';
	        k3++;
	        }else{
	        //printf("T2 eh a menor dead line.");
	        graf[1][i]='o';
	        k2++; 
	        }
	    }
	    if (t1a==1 && t2a !=1 && t3a !=1){
	        //printf("T1 eh o unico apto."); 
	        graf[0][i]='o';
	        k1++; 
	    }
	    if (t1a != 1 && t2a == 1 && t3a != 1){
	        //printf("T2 eh o unico apto.");
	        graf[1][i]='o';
	        k2++;
	    }
	    if (t1a != 1 && t2a != 1 && t3a == 1){
	        //printf("T3 eh o unico apto.");
	        graf[2][i]='o';
	        k3++;
	    }
	        if (k1==t1.C){
	            k1=0;
	            t1d=t1d+t1.D;
	            apt1=apt1+t1.P;
	        }
	        
	        if (k2==t2.C){
	            k2=0;
	            t2d=t2d+t2.D;
	            apt2=apt2+t2.P;
	        }
	        
	        if (k3==t3.C){
	            k3=0;
	            t3d=t3d+t3.D;
	            apt3=apt3+t3.P;
	        }
	
	}
	}//end if escalona
	
	}if(metodo == 2){
	
	int k1=0;
	int k2=0;
	int k3=0;
	int apt1=0;
	int apt2=0;
	int apt3=0;
	bool t1a=1;
	bool t2a=1;
	bool t3a=1;
	
	
	    //teste de escalonabilidade
	
	    if (util <=N*((2^(1/N))-1)){
	    printf("O sistema e escalonavel.\n");
	    printf("Taxa de utilizacao = %f\n", util);
	//
	for( i=0; i<periodo_total; i++){
	    if(i >= apt1){
	        //printf("\n%d\tT1 esta apto.", i);
	        t1a=1;
	    }else{
	        //printf("T1 nao esta apto.");
	        t1a=0;
	    }
	    if(i >= apt2){
	        //printf("\n%d\tT2 esta apto.", i);
	        t2a=1;
	    }else{
	        //printf("T2 nao esta apto.");
	        t2a=0;
	    }
	    if(i >= apt3){
	        //printf("\n%d\tT3 esta apto.", i);
	        t3a=1;
	    }else{
	        //printf("T3 nao esta apto.");
	        t3a=0;
	    }
	//
	    if(t1a && t2a && t3a){
	
	        if((t1.P <= t2.P) && (t1.P <= t3.P)){
	        //printf("T1 eh a menor periodo."); 
	        graf[0][i]='o';
	        k1++;
	        }
	
	        if((t2.P <= t3.P) && (t2.P <= t1.P)){
	        //printf("T2 eh o menor periodo");
	        graf[1][i]='o';
	        k2++;        
	        }
	
	        if((t3.P <= t2.P) && (t3.P <= t1.P)){
	        //printf("T3 eh o menor periodo.");
	        graf[2][i]='o';
	        k3++;
	        }
	    }
	    if(t1a && t2a && t3a == 0){
	        if(t1.P <= t2.P){
	        //printf("T1 eh o menor periodo."); 
	        graf[0][i]='o';
	        k1++;
	        }else{
	        //printf("T2 eh o menor periodo.");
	        graf[1][i]='o';
	        k2++;     
	        }
	    }
	    if(t1a && t3a && t2a == 0){
	        if(t3.P <= t1.P){
	        //printf("T3 eh o menor periodo.");
	        graf[2][i]='o';
	        k3++;
	        }else{
	        //printf("T1 eh o menor periodo."); 
	        graf[0][i]='o';
	        k1++;    
	        }
	    }
	    if(t2a && t3a && t1a != 1){
	        if(t3.P <= t2.P){
	        //printf("T3 eh a menor dead line.");
	        graf[2][i]='o';
	        k3++;
	        }else{
	        //printf("T2 eh o menor periodo.");
	        graf[1][i]='o';
	        k2++; 
	        }
	    }
	    if (t1a && t2a !=1 && t3a !=1){
	        //printf("T1 eh o unico apto."); 
	        graf[0][i]='o';
	        k1++; 
	    }
	    if (t1a != 1 && t2a && t3a != 1){
	        //printf("T2 eh o unico apto.");
	        graf[1][i]='o';
	        k2++;
	    }
	    if (t1a != 1 && t2a != 1 && t3a){
	        //printf("T3 eh o unico apto.");
	        graf[2][i]='o';
	        k3++;
	    }
	
	//
	
	    if (k1==t1.C){
	            k1=0;
	            //t1p=t1p+t1.P;
	            apt1=apt1+t1.P;
	        }
	        
	        if (k2==t2.C){
	            k2=0;
	            //t2p=t2p+t2.P;
	            apt2=apt2+t2.P;
	        }
	        
	        if (k3==t3.C){
	            k3=0;
	            //t3p=t3p+t3.P;
	            apt3=apt3+t3.P;
	        }
	
	    }//endif escalonabilidade
	}//end for
	
	
	}
	
	for ( i=0; i<N; i++){
	    for(j=0; j<periodo_total; j++){
	        printf("%c ", graf[i][j]);
	    }printf("\n");
	}
	   
	}else{
	    printf("Erro na leitura do arquivo\nTente novamente\n");
	}
	
	return 0;
}
