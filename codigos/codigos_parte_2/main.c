/****	CONTROLE DE UMA CALDEIRA ****/
  
  /* Trabalho 01 - Disciplina: Software em Tempo Real */
  /* Professor: Reuber Regis
  
  /*	Equipe:												
   *		Daniel Menseses da Rocha - 495307			             
   *		Francisco Silvan Felipe do Carmo - 496641					
   *    	Joaquim Walisson Portela de Sousa - 472152
   */

// Bibliotecas 
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "sensores.h"
#include "socket.h"
#include "bufduplo.h"
#include "tela.h"
#include "atuadores.h"
#include "referenciaTemp.h"
#include "referenciaNivel.h"

#define NSEC_PER_SEC    (1000000000) 	// Numero de nanosegundos em um segundo
#define N_AMOSTRAS      10000 		// Numero de amostras

//Variaveis globais
double usuario_temp = 0;
double usuario_nivel = 0;
double tempo_ini = 0;



/***** ---------- FUNCOES QUE REALIZAM OS REQUISITOS ---------- ****/

/***** ---------- 1º e 3º Requisito - Cria uma tarefa que controla a temperatura  com a ajuda dos atuadores ---------- *****/
void thread_controle_Temperatura (void){
	char msg_enviada[1000];
	long atraso_fim;
	struct timespec t, t_fim;
	long periodo = 50e6; //50ms
	double temp, ref_temp;
    	double nivel, ref_niv;
    	double tol = 0.005;
	// Le a hora atual, coloca em t
	clock_gettime(CLOCK_MONOTONIC ,&t);
	t.tv_sec++;
	
    	while(1){
		// Espera o inicio do proximo periodo
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
		
		temp = sensorTemp_get("t");
    		ref_temp = get_ref_temp();
    		nivel = sensorNivel_get("h");
    		ref_niv = get_ref_nivel();

   
		if(temp > ref_temp+tol) { //se a temperatura estiver alta...     
			if(nivel > ref_niv+tol) { //...e o nivel estiver alto
				//nao pode entrar agua por ni
				sprintf( msg_enviada, "ani%lf", 0.0);
				msg_socket(msg_enviada);
				//tem que sair agua por nf		
				sprintf( msg_enviada, "anf%lf", 100.0);
				msg_socket(msg_enviada);
				//nao pode entrar agua por na
				sprintf( msg_enviada, "ana%lf", 0.0 );
				msg_socket(msg_enviada);
				//temp importa a principio
				sprintf( msg_enviada, "aq-%lf", 0.0 );
				msg_socket(msg_enviada);
			} 

			if(ref_niv-tol <= nivel && nivel <= ref_niv+tol) { //...e o nivel estiver razoavel
				//nao pode entrar agua por ni
				sprintf( msg_enviada, "ani%lf", 100.0);
				msg_socket(msg_enviada);
				//tem que sair agua por nf		
				sprintf( msg_enviada, "anf%lf", 100.0);
				msg_socket(msg_enviada);
				//nao pode entrar agua por na
				sprintf( msg_enviada, "ana%lf", 0.0 );
				msg_socket(msg_enviada);
				//temp importa a principio
				sprintf( msg_enviada, "aq-%lf", 0.0 );
				msg_socket(msg_enviada);
			}   

			if(nivel < ref_niv-tol) { //...e o nivel estiver baixo
				//nao pode entrar agua por ni
				sprintf( msg_enviada, "ani%lf", 100.0);
				msg_socket(msg_enviada);
				//tem que sair agua por nf		
				sprintf( msg_enviada, "anf%lf", 0.0);
				msg_socket(msg_enviada);
				//nao pode entrar agua por na
				sprintf( msg_enviada, "ana%lf", 0.0 );
				msg_socket(msg_enviada);
				//temp importa a principio
				sprintf( msg_enviada, "aq-%lf", 0.0 );
				msg_socket(msg_enviada);            
			}             
		}


		if(ref_temp-tol <= temp && temp <= ref_temp+tol) { //se a temperatura estiver razoavel...
			if(nivel > ref_niv+tol) { //...e o nivel estiver alto
				//nao pode entrar agua por ni
				sprintf( msg_enviada, "ani%lf", 0.0);
				msg_socket(msg_enviada);
				//tem que sair agua por nf		
				sprintf( msg_enviada, "anf%lf", 100.0);
				msg_socket(msg_enviada);
				//nao pode entrar agua por na
				sprintf( msg_enviada, "ana%lf", 0.0 );
				msg_socket(msg_enviada);
				//temp importa a principio
				sprintf( msg_enviada, "aq-%lf", 0.0 );
				msg_socket(msg_enviada);            
			}

			if(ref_niv-tol <= nivel && nivel <= ref_niv+tol) { //...e o nivel estiver razoavel
				//nao pode entrar agua por ni
				sprintf( msg_enviada, "ani%lf", 0.0);
				msg_socket(msg_enviada);
				//tem que sair agua por nf		
				sprintf( msg_enviada, "anf%lf", 0.0);
				msg_socket(msg_enviada);
				//nao pode entrar agua por na
				sprintf( msg_enviada, "ana%lf", 0.0 );
				msg_socket(msg_enviada);
				//temp importa a principio
				sprintf( msg_enviada, "aq-%lf", 0.0 );
				msg_socket(msg_enviada);            
			}   

			if(nivel < ref_niv-tol) { //...e o nivel estiver baixo
				//tem que entrar agua por ni
				sprintf( msg_enviada, "ani%lf", 100.0);
				msg_socket(msg_enviada);
				//nao pode sair agua por nf		
				sprintf( msg_enviada, "anf%lf", 0.0);
				msg_socket(msg_enviada);
				//nao eh interessante entrar agua por n0
				sprintf( msg_enviada, "ana%lf", 0.0 );
				msg_socket(msg_enviada);
				//temp nao importa a principio
				sprintf( msg_enviada, "aq-%lf", 0.0 );
				msg_socket(msg_enviada);            
			}  
		}


		if(temp < ref_temp-tol) { //se a temperatura estiver baixa...
			if(nivel > ref_niv+tol) { //...e o nivel estiver alto
				//nao pode entrar agua por ni
				sprintf( msg_enviada, "ani%lf", 0.0);
				msg_socket(msg_enviada);
				//tem que sair agua por nf		
				sprintf( msg_enviada, "anf%lf", 100.0);
				msg_socket(msg_enviada);
				//nao pode entrar agua por na
				sprintf( msg_enviada, "ana%lf", 0.0 );
				msg_socket(msg_enviada);
				//temp importa a principio
				sprintf( msg_enviada, "aq-%lf", 1000000.0 );
				msg_socket(msg_enviada);                
			} 

			if(ref_niv-tol <= nivel && nivel <= ref_niv+tol) { //...e o nivel estiver razoavel
				//nao pode entrar agua por ni
				sprintf( msg_enviada, "ani%lf", 0.0);
				msg_socket(msg_enviada);
				//tem que sair agua por nf		
				sprintf( msg_enviada, "anf%lf", 10.0);
				msg_socket(msg_enviada);
				//nao pode entrar agua por na
				sprintf( msg_enviada, "ana%lf", 10.0 );
				msg_socket(msg_enviada);
				//temp importa a principio
				sprintf( msg_enviada, "aq-%lf", 1000000.0 );
				msg_socket(msg_enviada);            
			}

			if(nivel < ref_niv-tol) { //...e o nivel estiver baixo
				//nao pode entrar agua por ni
				sprintf( msg_enviada, "ani%lf", 100.0);
				msg_socket(msg_enviada);
				//tem que sair agua por nf		
				sprintf( msg_enviada, "anf%lf", 0.0);
				msg_socket(msg_enviada);
				//nao pode entrar agua por na
				sprintf( msg_enviada, "ana%lf", 0.0 );
				msg_socket(msg_enviada);
				//temp importa a principio
				sprintf( msg_enviada, "aq-%lf", 1000000.0 );
				msg_socket(msg_enviada);
			}                
		}
               
		// Le a hora atual, coloca em t_fim
		clock_gettime(CLOCK_MONOTONIC ,&t_fim);
		
		// Calcula o tempo de resposta observado em microsegundos
		atraso_fim = 1000000*(t_fim.tv_sec - t.tv_sec)   +   (t_fim.tv_nsec - t.tv_nsec)/1000;
		
		bufduplo_insereLeitura(atraso_fim);
		
		// Calcula inicio do proximo periodo
		t.tv_nsec += periodo;
		while (t.tv_nsec >= NSEC_PER_SEC){
			t.tv_nsec -= NSEC_PER_SEC;
			t.tv_sec++;
		}
    }		
}


/***** ---------- 2º e 3º Requisito - Cria uma tarefa que controla o nivel da agua com a ajuda dos atuadores ---------- *****/
void thread_controle_Nivel (void){
	char msg_enviada[1000];
	long atraso_fim;
	struct timespec t, t_fim;
	long periodo = 70e6; //70ms
	double nivel, ref_niv;
    	double temp, ref_temp;
    	double tol = 0.005;
	// Le a hora atual, coloca em t
	clock_gettime(CLOCK_MONOTONIC ,&t);
	t.tv_sec++;
	while(1){
		// Espera o inicio do proximo periodo
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
		
		temp = sensorTemp_get("t");
		ref_temp = get_ref_temp();
		nivel = sensorNivel_get("h");
		ref_niv = get_ref_nivel();
		
		if(nivel > ref_niv+tol) { //se o nivel estiver alto...   
		    if(temp > ref_temp+tol){ //...e a temperatura estiver alta
			//nao pode entrar agua por ni
			sprintf( msg_enviada, "ani%lf", 0.0);
				    msg_socket(msg_enviada);
				    //tem que sair agua por nf		
				    sprintf( msg_enviada, "anf%lf", 100.0);
				    msg_socket(msg_enviada);
				    //nao pode entrar agua por na
				    sprintf( msg_enviada, "ana%lf", 0.0 );
				    msg_socket(msg_enviada);
			//temp importa a principio
			sprintf( msg_enviada, "aq-%lf", 0.0 );
				    msg_socket(msg_enviada);
		    }     
		    if(ref_temp-tol <= temp && temp <= ref_temp+tol){ //...e a temperatura estiver razoavel
			//nao pode entrar agua por ni
			sprintf( msg_enviada, "ani%lf", 0.0);
				    msg_socket(msg_enviada);
				    //tem que sair agua por nf		
				    sprintf( msg_enviada, "anf%lf", 100.0);
				    msg_socket(msg_enviada);
				    //nao pode entrar agua por na
				    sprintf( msg_enviada, "ana%lf", 0.0 );
				    msg_socket(msg_enviada);
			//temp importa a principio
			sprintf( msg_enviada, "aq-%lf", 0.0 );
				    msg_socket(msg_enviada);
		    }   
		    if(temp < ref_temp-tol){ //...e a temperatura estiver baixa
			//nao pode entrar agua por ni
			sprintf( msg_enviada, "ani%lf", 0.0);
				    msg_socket(msg_enviada);
				    //tem que sair agua por nf		
				    sprintf( msg_enviada, "anf%lf", 100.0);
				    msg_socket(msg_enviada);
				    //nao pode entrar agua por na
				    sprintf( msg_enviada, "ana%lf", 0.0 );
				    msg_socket(msg_enviada);
			//temp importa a principio
			sprintf( msg_enviada, "aq-%lf", 1000000.0 );
				    msg_socket(msg_enviada);
		    }       
	}


        if(ref_niv-tol <= nivel && nivel <= ref_niv+tol){ //se o nivel estiver razoavel...
            if(temp > ref_temp+tol){ //...e a temperatura estiver alta
                //nao pode entrar agua por ni
                sprintf( msg_enviada, "ani%lf", 100.0);
			    msg_socket(msg_enviada);
			    //tem que sair agua por nf		
			    sprintf( msg_enviada, "anf%lf", 100.0);
			    msg_socket(msg_enviada);
			    //nao pode entrar agua por na
			    sprintf( msg_enviada, "ana%lf", 0.0 );
			    msg_socket(msg_enviada);
                //temp importa a principio
                sprintf( msg_enviada, "aq-%lf", 0.0 );
			    msg_socket(msg_enviada);
            }     
            if(ref_temp-tol <= temp && temp <= ref_temp+tol){ //...e a temperatura estiver razoavel
                //tem que entrar agua por ni
                sprintf( msg_enviada, "ani%lf", 0.0);
			    msg_socket(msg_enviada);
			    //nao pode sair agua por nf		
			    sprintf( msg_enviada, "anf%lf", 0.0);
			    msg_socket(msg_enviada);
			    //nao eh interessante entrar agua por n0
			    sprintf( msg_enviada, "ana%lf", 0.0 );
			    msg_socket(msg_enviada);
                //temp nao importa a principio
                sprintf( msg_enviada, "aq-%lf", 0.0 );
			    msg_socket(msg_enviada);
            }   
            if(temp < ref_temp-tol){ //...e a temperatura estiver baixa
                //nao pode entrar agua por ni
                sprintf( msg_enviada, "ani%lf", 0.0);
			    msg_socket(msg_enviada);
			    //tem que sair agua por nf		
			    sprintf( msg_enviada, "anf%lf", 10.0);
			    msg_socket(msg_enviada);
			    //nao pode entrar agua por na
			    sprintf( msg_enviada, "ana%lf", 10.0 );
			    msg_socket(msg_enviada);
                //temp importa a principio
                sprintf( msg_enviada, "aq-%lf", 1000000.0 );
			    msg_socket(msg_enviada);
            }      
        }

        if(nivel < ref_niv-tol) { //e se o nivel estiver baixo...   
             if(temp > ref_temp+tol){ //...e a temperatura estiver alta
                //nao pode entrar agua por ni
                sprintf( msg_enviada, "ani%lf", 100.0);
			    msg_socket(msg_enviada);
			    //tem que sair agua por nf		
			    sprintf( msg_enviada, "anf%lf", 0.0);
			    msg_socket(msg_enviada);
			    //nao pode entrar agua por na
			    sprintf( msg_enviada, "ana%lf", 0.0 );
			    msg_socket(msg_enviada);
                //temp importa a principio
                sprintf( msg_enviada, "aq-%lf", 0.0 );
			    msg_socket(msg_enviada);
                }     
            if(ref_temp-tol <= temp && temp <= ref_temp+tol){ //...e a temperatura estiver razoÃ¡vel
                //tem que entrar agua por ni
                sprintf( msg_enviada, "ani%lf", 100.0);
			    msg_socket(msg_enviada);
			    //nao pode sair Ã¡gua por nf		
			    sprintf( msg_enviada, "anf%lf", 0.0);
			    msg_socket(msg_enviada);
			    //nao eh interessante entrar agua por n0
			    sprintf( msg_enviada, "ana%lf", 0.0 );
			    msg_socket(msg_enviada);
                //temp nao importa a principio
                sprintf( msg_enviada, "aq-%lf", 0.0 );
			    msg_socket(msg_enviada);
            }   
            if(temp < ref_temp-tol){ //...e a temperatura estiver baixa
                //nao pode entrar agua por ni
                sprintf( msg_enviada, "ani%lf", 100.0);
			    msg_socket(msg_enviada);
			    //tem que sair agua por nf		
			    sprintf( msg_enviada, "anf%lf", 0.0);
			    msg_socket(msg_enviada);
			    //nao pode entrar agua por na
			    sprintf( msg_enviada, "ana%lf", 0.0 );
			    msg_socket(msg_enviada);
                //temp importa a principio
                sprintf( msg_enviada, "aq-%lf", 1000000.0 );
			    msg_socket(msg_enviada);
            }                      
	}

	// Le a hora atual, coloca em t_fim
	clock_gettime(CLOCK_MONOTONIC ,&t_fim);

	// Calcula o tempo de resposta observado em microsegundos
	atraso_fim = 1000000*(t_fim.tv_sec - t.tv_sec)   +   (t_fim.tv_nsec - t.tv_nsec)/1000;

	bufduplo_insereLeitura(atraso_fim);

	// Calcula inicio do proximo periodo
	t.tv_nsec += periodo;
	while (t.tv_nsec >= NSEC_PER_SEC) {
		t.tv_nsec -= NSEC_PER_SEC;
		t.tv_sec++;
	}
    }
}


/***** ---------- 4º Requisito - Cria uma tarefa para mostrar as informacoes sobre os sensores ---------- *****/
void thread_mostra_status(void) {
	double ta, t, ti, no, h, ref_temp, ref_nivel;
	while(1){
		//Pega os valores dos sensores
		ta = sensorTempAmbiente_get("ta");
		t = sensorTemp_get("t");
		ti = sensorTempEntrada_get("ti");
		no = sensorSaida_get("no");
		h = sensorNivel_get("h"); 
		
		//Guarda valores lidos do usuarios nas respectivas variaveis
		usuario_temp = get_ref_temp();
		usuario_nivel = get_ref_nivel();
		aloca_tela();
		system("tput reset");
		printf("------------------------------------\n");
		printf("Temperatura digitada do usuario --> %.2lf\n", usuario_temp);
		printf("Nivel da agua digitada do usuario --> %.2lf\n", usuario_nivel);
		printf("Temperatura do ar (Ta)--> %.2lf\n", ta);
		printf("Temperatura interior (T)--> %.2lf\n", t);
		printf("Temperatura da agua que entra (Ti)--> %.2lf\n", ti);
		printf("Fluxo de agua de saida (No)--> %.2lf\n", no);
		printf("Altura do nivel (H)--> %.2lf\n", h);
		printf("------------------------------------\n");
		libera_tela();
		sleep(1);
		}
}


/***** 5º Requisito - Tarefa que realiza a verificacao da temperatura a cada 10 ms caso tenha disparo do alarme *****/
void thread_alarme(void) {
	while(1){			
		sensor_alarme(30);		
		aloca_tela();
		printf("=========================\n");
		printf("        ALARME!!!\n");
		printf("==========================\n");
		libera_tela();
		sleep(1);	
	}
}


/***** ---------- 6 Requisito - Cria uma tarefa que altera os dados de referencia 
da temperatura e do nivel de agua atraves do usuario ---------- *****/
void thread_ler_usuario(void){
	printf("Digite um valor de referencia para a Temperatura:\n");
	scanf("%lf", &usuario_temp);
	put_ref_temp(usuario_temp);
	
	printf("Digite um valor de referencia para o nivel de agua:\n");
	scanf("%lf", &usuario_nivel);
	put_ref_nivel(usuario_nivel);
}


/***** ---------- 7º Requisito - Cria uma tarefa que armazena a leitura dos tempos de respostas  ---------- *****/
void thread_grava_temp_resp(void){
	FILE* dados_f;
	dados_f = fopen("dados_tempo_exec.txt", "w");
	if(dados_f == NULL){
		printf("Erro, nao foi possivel abrir o arquivo\n");
		exit(1);
	}

	int amostras = 1;
	int tambuffer = tamBuf();

	while(amostras++ <= N_AMOSTRAS / tambuffer) {
		//Espera o buffer encher para descarregar no arquivo
		long * buf = bufduplo_esperaBufferCheio();

		int n2 = tamBuf();
		int tam = 0;

		while (tam < n2)
			fprintf(dados_f, "%4ld\n", buf[tam++]);
			fflush(dados_f);
			aloca_tela();
			printf("Gravando arquivo...\n");
			libera_tela();
		}

	fclose(dados_f);	
}


/***** ---------- 8º Requisito - Cria uma tarefa que armazena os valores do sensores de nivel e temperatura,
 depois sao gravado em um arquivo ---------- *****/
void thread_grava_temp_nivel (void) {
	FILE* dados_f;
	dados_f = fopen("valores_nivel_temperatura.txt", "w");
	if(dados_f == NULL){
		printf("Erro, nao foi possivel abrir o arquivo\n");
		exit(1);    
	}

	struct timespec time;
	long periodo = 1000e6; //1s
	double temp, nivel;

	// Le a hora atual, coloca em t
	clock_gettime(CLOCK_MONOTONIC ,&time);
	time.tv_sec++;
	double t ,h; 

	while(1){
		// Espera o inicio do proximo periodo
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &time, NULL);
		
		temp = sensorTemp_get("t");
    	nivel = sensorNivel_get("h");

		fprintf(dados_f, "_________Medicoes__________\n");
		fprintf(dados_f, "Valor temperatura: %lf\n", temp);
		fprintf(dados_f, "Valor nivel: %lf\n\n", nivel);
		fflush(dados_f);
		sleep(1);

		time.tv_nsec += periodo;
		while (time.tv_nsec >= NSEC_PER_SEC){
			time.tv_nsec -= NSEC_PER_SEC;
			time.tv_sec++;
		}
	}	
}


/**** ---------- Cria uma tarefa que le os sensores e envia uma mensagem com os valores ---------- ****/
void thread_le_sensor(void) {
	char msg_enviada[1000];
	struct timespec t;
	long int periodo = 10e6; 	// 10e6ns ou 10ms
	
	//Le a hora atual, coloca em t
	clock_gettime(CLOCK_MONOTONIC ,&t);
	
	while(1){
		//Espera ate o inicio do proximo periodo
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
		
		//Envia mensagem via canal de comunicaçao para receber valores de sensores
		sensorTempAmbiente_put(msg_socket("sta0"));
		sensorTemp_put(msg_socket("st-0"));
		sensorTempEntrada_put(msg_socket("sti0"));
		sensorSaida_put(msg_socket("sno0"));
		sensorNivel_put(msg_socket("sh-0"));
		
		// Calcula inicio do proximo periodo
		t.tv_nsec += periodo;
		while (t.tv_nsec >= NSEC_PER_SEC) {
			t.tv_nsec -= NSEC_PER_SEC;
			t.tv_sec++;
		}	
	}
}


/***** ---------- INICIO DA FUNCAO PRINCIPAL ---------- *****/
int main( int argc, char *argv[]) {
	//Cria socket
	cria_socket(argv[1], atoi(argv[2]));
	
	//criacao das respectivas threads trabalhadas
	pthread_t mostra_status, le_sensor, alarme, ler_usuario, controle_temp, controle_nivel, tempo_resposta_buffd, thread_gravacao;

	pthread_create(&ler_usuario, NULL, (void *) thread_ler_usuario, NULL);
	pthread_join( ler_usuario, NULL);
	pthread_create(&mostra_status, NULL, (void *) thread_mostra_status, NULL);
	pthread_create(&le_sensor, NULL, (void *) thread_le_sensor, NULL);
	pthread_create(&controle_temp, NULL, (void *) thread_controle_Temperatura, NULL);
	pthread_create(&controle_nivel, NULL, (void *) thread_controle_Nivel, NULL);
	pthread_create(&alarme, NULL, (void *) thread_alarme, NULL);
	pthread_create(&tempo_resposta_buffd, NULL, (void *) thread_grava_temp_resp, NULL);
	pthread_create(&thread_gravacao, NULL, (void *) thread_grava_temp_nivel, NULL);
    
	
	pthread_join( mostra_status, NULL);
	pthread_join( le_sensor, NULL);
	pthread_join( alarme, NULL);
	pthread_join( controle_temp, NULL);
	pthread_join( controle_nivel, NULL);
	pthread_join( tempo_resposta_buffd, NULL);
	pthread_join( thread_gravacao, NULL);
}
/***** ---------- FIM DA FUNCAO PRINCIPAL ---------- *****/
