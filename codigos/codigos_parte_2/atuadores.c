// ATUADORES PARA GUARDAR OS FLUXOS
#include <math.h>
#include <pthread.h>
#include <string.h>

static pthread_mutex_t exclusao_atuador = PTHREAD_MUTEX_INITIALIZER; 
static pthread_cond_t alarme = PTHREAD_COND_INITIALIZER; 

//Variaveis para os atuadores solicitados Ni, Q, Na e Nf.
static double atuador_fluxo_entrada = 0;
static double atuador_fluxo_aquecido = 0;
static double atuador_fluxo_aquecedor = 0;
static double atuador_fluxo_saida = 0;

static double limite_atual = HUGE_VAL;

/* Chamado pela thread que le o Atuador Ni e disponibiliza aqui o valor lido */
 void atuadorFluxoEntrada_put(double valor_lido) {
	 pthread_mutex_lock( &exclusao_atuador); 
	 atuador_fluxo_entrada = valor_lido;
	 if( atuador_fluxo_entrada >= limite_atual) 
	 	  pthread_cond_signal( &alarme); 
	 pthread_mutex_unlock( &exclusao_atuador); 
 }
 
 /* Chamado por qualquer thread que precisa do valor lido do Atuador Ni */ 
 double atuadorFluxoEntrada_get(char s[6]) {
	 double aux; 
	 pthread_mutex_lock( &exclusao_atuador); 
	 if(strncmp(s,"ani",1)==0){
	 	aux = atuador_fluxo_entrada; 
	 }
	 pthread_mutex_unlock( &exclusao_atuador); 
	 return aux; 
 }
 
 /* Chamado pela thread que le o Atuador Q e disponibiliza aqui o valor lido */
 void atuadorFluxoAquecido_put(double valor_lido) {
	 pthread_mutex_lock( &exclusao_atuador); 
	 atuador_fluxo_aquecido = valor_lido;
	 if( atuador_fluxo_aquecido >= limite_atual){
	 	pthread_cond_signal( &alarme); 
	 }
	 pthread_mutex_unlock( &exclusao_atuador); 
 }
 
 /* Chamado por qualquer thread que precisa do valor lido do Atuador Q */ 
 double atuadorFluxoAquecido_get(char s[6]) {
	 double aux; 
	 pthread_mutex_lock( &exclusao_atuador); 
	 if(strncmp(s,"aq-",1)==0){
	 	aux = atuador_fluxo_aquecido; 
	 }
	 pthread_mutex_unlock( &exclusao_atuador); 
	 return aux; 
 }
 
 /* Chamado pela thread que le o Atuador Na e disponibiliza aqui o valor lido */
 void atuadorFluxoAquecedor_put(double valor_lido) {
	 pthread_mutex_lock( &exclusao_atuador); 
	 atuador_fluxo_aquecedor = valor_lido;
	 if( atuador_fluxo_aquecedor >= limite_atual){ 
	 	pthread_cond_signal( &alarme);
	 }
	 pthread_mutex_unlock( &exclusao_atuador); 
 }
 
 /* Chamado por qualquer thread que precisa do valor lido do Atuador Na */ 
 double atuadorFluxoAquecedor_get(char s[6]) {
	 double aux; 
	 pthread_mutex_lock( &exclusao_atuador); 
	 if(strncmp(s,"ana",1)==0){
	 	aux = atuador_fluxo_aquecedor; 
	 }
	 pthread_mutex_unlock( &exclusao_atuador); 
	 return aux; 
 }
 
 /* Chamado pela thread que le o Atuador Nf e disponibiliza aqui o valor lido */
 void atuadorFluxoSaida_put(double valor_lido) {
	 pthread_mutex_lock( &exclusao_atuador); 
	 atuador_fluxo_saida = valor_lido;
	 if( atuador_fluxo_saida >= limite_atual){
	 	pthread_cond_signal( &alarme);
	 }
	 pthread_mutex_unlock( &exclusao_atuador); 
 }
 
 /* Chamado por qualquer thread que precisa do valor lido do Atuador Nf */ 
 double atuadorFluxoSaida_get(char s[6]) {
	 double aux; 
	 pthread_mutex_lock( &exclusao_atuador); 
	 if(strncmp(s,"anf",1)==0){
	 	aux = atuador_fluxo_saida; 
	 }
	 pthread_mutex_unlock( &exclusao_atuador); 
	 return aux; 
 }
