/* Monitor sensor, no arquivo sensor.c */ 
#include <math.h>
#include <pthread.h>
#include <string.h>
#include "sensor.h"

static pthread_mutex_t exclusao_mutua = PTHREAD_MUTEX_INITIALIZER; 
static pthread_cond_t alarme = PTHREAD_COND_INITIALIZER; 
static double sensor_lido = 0; 
static double limite_atual = HUGE_VAL;

/* FUNÇÕES BASES PARA OS SENSORES*/
/* Chamado pela thread que le o sensor e disponibiliza aqui o valor lido */
 void sensor_put( double lido) {
	 pthread_mutex_lock( &exclusao_mutua); 
	 sensor_lido = lido; 
	 if( sensor_lido >= limite_atual) 
	 	pthread_cond_signal( &alarme); 
	 pthread_mutex_unlock( &exclusao_mutua); 
 }
 
 /* Chamado por qualquer thread que precisa do valor lido do sensor */ 
 double sensor_get( void) {
	 double aux; 
	 pthread_mutex_lock( &exclusao_mutua); 
	 aux = sensor_lido; 
	 pthread_mutex_unlock( &exclusao_mutua); 
	 return aux; 
 }

/* Thread fica bloqueada até o valor do sensor chegar em limite */ 
void sensor_alarme( double limite) {
	pthread_mutex_lock( &exclusao_mutua); 
	limite_atual = limite; 
	while( sensor_lido < limite_atual) 
		pthread_cond_wait( &alarme, &exclusao_mutua); 
	limite_atual = HUGE_VAL; 
	pthread_mutex_unlock( &exclusao_mutua); 
}

/****************************** FUNÇÕES PARA OS SENSORES ******************************/

/******* FUNÇÕES PARA A TEMPERATURA REFERÊNCIAL *******/
static double ref_lido = 0;

/*Chama a thread que le o sensor e fornece o valor lido */
void referenciaTemp_put(double ref) {
  pthread_mutex_lock(&exclusao_mutua);
  ref_ent = ref;
  pthread_mutex_unlock(&exclusao_mutua);
}

/*Chama qualquer thread que precisa do valor lido do sensor */ 
double referenciaTemp_get(void) {
  double aux;
  pthread_mutex_lock(&exclusao_mutua);
  aux = ref_lido;
  pthread_mutex_unlock(&exclusao_mutua);
  return aux;
}

/******* FUNÇÕES PARA A TEMPERATURA *******/
//Variáveis globais para amezanar os valores dos sensores, só são acessado por esse modulo do monitor sensor
static double s_temp = 0;
static double limite_atual = HUGE_VAL;

/* Chamado pela thread que le o sensor e disponibiliza aqui o valor lido */
void sensorTemp_put( double temp_lido) {
	//Seção crítica
	pthread_mutex_lock( &exclusao_mutua); //Exclusão mútua dos recursos
	s_temp = temp_lido;//Aloca o valor de temperatura na variável global
	if(s_temp >= limite_atual){
		pthread_cond_signal(&alarme);
	}
	pthread_mutex_unlock( &exclusao_mutua);//Libera os recursos exclusos

}

/* Chamado por qualquer thread que precisa do valor lido do sensor */ 
double sensorTemp_get(void) {
	double aux; 
	pthread_mutex_lock(&exclusao_mutua); 
	aux = s_temp; //Armazena localmente o valor da variável global temperatura
	pthread_mutex_unlock(&exclusao_mutua); 
	return aux;//Retorna o valor da temperatura
}

//Thread fica bloqueada até o valor do sensor chegar em limite 
void sensorTemp_alarme( double limite) {
	pthread_mutex_lock( &exclusao_mutua); 
	limite_atual = limite; 
	while( s_temp < limite_atual){ 
		pthread_cond_wait( &alarme, &exclusao_mutua); 
	}
	limite_atual = HUGE_VAL; 
	pthread_mutex_unlock( &exclusao_mutua); 
} 

/******* FUNÇÕES PARA A TEMPERATURA DE ENTRADA *******/
//Variáveis globais para amezanar os valores dos sensores, só são acessado por esse modulo do monitor sensor
static double s_temp_entrada = 0; 

/* Chamado pela thread que le o sensor e disponibiliza aqui o valor lido */
void sensorTempEntrada_put( double temp_entr ) {
	//Seção crítica
	pthread_mutex_lock( &exclusao_mutua); //Exclusão mútua dos recursos
	s_temp_entrada = temp_entr;//Aloca o valor de temperatura na variável global
	pthread_mutex_unlock( &exclusao_mutua);//Libera os recursos exclusos

}

/* Chamado por qualquer thread que precisa do valor lido do sensor */ 
double sensorTempEntrada_get(void) {
	double aux; 
	pthread_mutex_lock(&exclusao_mutua); 
	aux = s_temp_entrada; //Armazena localmente o valor da variável global temperatura
	pthread_mutex_unlock(&exclusao_mutua); 
	return aux;//Retorna o valor da temperatura
}

/******* FUNÇÕES PARA A TEMPERATURA AMBIENTE *******/
//Variáveis globais para amezanar os valores dos sensores, só são acessado por esse modulo do monitor sensor
static double s_temp_ambiente = 0;

/* Chamado pela thread que le o sensor e disponibiliza aqui o valor lido */
void sensorTempAmbiente_put( double temp_amb ) {
	//Seção crítica
	pthread_mutex_lock(&exclusao_mutua); //Exclusão mútua dos recursos
	s_temp_ambiente = temp_amb;//Aloca o valor de temperatura na variável global
	pthread_mutex_unlock(&exclusao_mutua);//Libera os recursos exclusos

}

/* Chamado por qualquer thread que precisa do valor lido do sensor */ 
double sensorTempAmbiente_get(void) {
	double aux; 
	pthread_mutex_lock(&exclusao_mutua); 
	aux = s_temp_ambiente; //Armazena localmente o valor da variável global temperatura
	pthread_mutex_unlock(&exclusao_mutua); 
	return aux;//Retorna o valor da temperatura
}
