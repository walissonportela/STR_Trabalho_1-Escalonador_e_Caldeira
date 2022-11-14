#ifndef SENSOR_H
#define SENSOR_H

/******* FUNÇÕES PARA A TEMPERATURA (T) *******/
void sensorTemp_put(double valor_lido);
double sensorTemp_get(char s[5]);

/******* FUNÇÕES PARA A TEMPERATURA AMBIENTE (Ta) *******/
void sensorTempAmbiente_put( double valor_lido );
double sensorTempAmbiente_get( char s[5]);

/******* FUNÇÕES PARA A TEMPERATURA DE ENTRADA (Ti) *******/
void sensorTempEntrada_put(double valor_lido);
double sensorTempEntrada_get(char s[5]);

/******* FUNÇÕES PARA O SENSOR DE SÁIDA (No) *******/
void sensorSaida_put(double valor_lido);
double sensorSaida_get(char s[5]);

/******* FUNÇÕES PARA O SENSOR DE ALTURA (H) *******/
void sensorNivel_put(double v_lido);
double sensorNivel_get(char s[5]);

/******* FUNÇÕES PARA O SENSOR DE ALARME *******/
void sensor_alarme( double limite);

#endif

