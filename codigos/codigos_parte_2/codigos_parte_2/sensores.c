/* MONITOR SENSORES */ 
#include <math.h>
#include <pthread.h>
#include <string.h>
#include "sensores.h"


static pthread_mutex_t exclusao_mutua = PTHREAD_MUTEX_INITIALIZER; 
static pthread_cond_t alarme = PTHREAD_COND_INITIALIZER; 
static double limite_atual = HUGE_VAL;



/****************************** FUNÇÕES PARA OS SENSORES ******************************/


/******* FUNÇÕES PARA A TEMPERATURA (T) *******/
static double sensor_temp = 0; // Varíavel para o sensor T

/* Chamado pela thread que le o sensor T e disponibiliza aqui o valor lido */
void sensorTemp_put(double valor_lido) {
	pthread_mutex_lock( &exclusao_mutua); 
	sensor_temp = valor_lido;
	if( sensor_temp >= limite_atual){
		pthread_cond_signal( &alarme);
	}
	pthread_mutex_unlock( &exclusao_mutua); 
}
 
/* Chamado por qualquer thread que precisa do valor lido do sensor T */ 
double sensorTemp_get(char s[5]) {
	double aux; 
	pthread_mutex_lock( &exclusao_mutua); 
	if(strncmp(s,"t",1)==0){
		aux = sensor_temp; 
	}
	pthread_mutex_unlock( &exclusao_mutua); 
	return aux; 
}


/******* FUNÇÕES PARA A TEMPERATURA AMBIENTE (Ta) *******/
static double sensor_temp_ambiente = 0; // Variável para o sensor Ta

// Chamado pela thread que le o sensor Ta e disponibiliza aqui o valor lido 
void sensorTempAmbiente_put( double valor_lido ) {
	pthread_mutex_lock( &exclusao_mutua); 
	sensor_temp_ambiente = valor_lido;
	if( sensor_temp_ambiente >= limite_atual) 
		pthread_cond_signal( &alarme); 
	pthread_mutex_unlock( &exclusao_mutua); 
}
 
// Chamado por qualquer thread que precisa do valor lido do sensor Ta 
double sensorTempAmbiente_get( char s[5]) {
	double aux; 
	pthread_mutex_lock( &exclusao_mutua); 
	if(strncmp(s,"ta",1)==0){
		aux = sensor_temp_ambiente; 
	}
	pthread_mutex_unlock( &exclusao_mutua); 
	return aux; 
}
 

/******* FUNÇÕES PARA A TEMPERATURA DE ENTRADA (Ti) *******/
static double sensor_temp_entrada = 0; // Variável para o sensor Ti

// Chamado pela thread que le o sensor Ti e disponibiliza aqui o valor lido 
void sensorTempEntrada_put(double valor_lido) {
	pthread_mutex_lock( &exclusao_mutua); 
	sensor_temp_entrada = valor_lido;
	if( sensor_temp_entrada >= limite_atual){
		pthread_cond_signal(&alarme);
	}
	pthread_mutex_unlock( &exclusao_mutua); 
}
 
// Chamado por qualquer thread que precisa do valor lido do sensor Ti  
double sensorTempEntrada_get(char s[5]) {
	double aux; 
	pthread_mutex_lock( &exclusao_mutua); 
	if(strncmp(s,"ti",1)==0){
		aux = sensor_temp_entrada; 
	}
	pthread_mutex_unlock( &exclusao_mutua); 
	return aux; 
}


/******* FUNÇÕES PARA O SENSOR DE SÁIDA (No) *******/
static double sensor_saida = 0; // Variável para o sensor No
 
// Chamado pela thread que le o sensor No e disponibiliza aqui o valor lido 
void sensorSaida_put(double valor_lido) {
	pthread_mutex_lock( &exclusao_mutua); 
	sensor_saida = valor_lido;
	if( sensor_saida >= limite_atual){
		pthread_cond_signal( &alarme);
	}
	pthread_mutex_unlock( &exclusao_mutua); 
}
 
// Chamado por qualquer thread que precisa do valor lido do sensor No 
double sensorSaida_get(char s[5]) {
	double aux; 
	pthread_mutex_lock( &exclusao_mutua); 
	if(strncmp(s,"no",1)==0){
		aux = sensor_saida; 
	}
	pthread_mutex_unlock( &exclusao_mutua); 
	return aux; 
}


/******* FUNÇÕES PARA O SENSOR DE ALTURA (H) *******/
static double sensor_nivel = 0; // Variável para o sensor H

// Chamado pela thread que le o sensor H e disponibiliza aqui o valor lido 
void sensorNivel_put(double v_lido) {
	pthread_mutex_lock( &exclusao_mutua); 
	sensor_nivel = v_lido;
	if( sensor_nivel >= limite_atual){
		pthread_cond_signal( &alarme);
	}
	pthread_mutex_unlock( &exclusao_mutua); 
}
 
//Chamado por qualquer thread que precisa do valor lido do sensor H  
double sensorNivel_get(char s[5]) {
	double aux; 
	pthread_mutex_lock( &exclusao_mutua); 
	if(strncmp(s,"h",1)==0){
		aux = sensor_nivel; 
	}
	pthread_mutex_unlock( &exclusao_mutua); 
	return aux; 
}


/******* FUNÇÕES PARA O SENSOR DE ALARME *******/

// Thread fica bloqueada até o valor do sensor chegar em limite 
void sensor_alarme( double limite) {
	pthread_mutex_lock( &exclusao_mutua); 
	limite_atual = limite; 
	while(sensor_temp < limite_atual)  
		pthread_cond_wait( &alarme, &exclusao_mutua); 
	limite_atual = HUGE_VAL; 
	pthread_mutex_unlock( &exclusao_mutua); 
}
