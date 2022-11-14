/**** MODULO DO MONITOR QUE É RESPONSÁVEL PELO ACESSO A TELA DO COMPUTADOR ****/
#include <pthread.h> // Biblioteca do mutex

static pthread_mutex_t tela = PTHREAD_MUTEX_INITIALIZER; // Variável do tipo mutex e estática e é acessível apenas a esse monitor, inicializada, sendo responsável pela exclusão mutua da seção crítica

void aloca_tela( void) {  // Função que bloqueia os recursos do sistema para o monitor tela
	  pthread_mutex_lock(&tela);
}

void libera_tela( void) {  // Função que libera os recursos do sistema
	pthread_mutex_unlock(&tela);
}
