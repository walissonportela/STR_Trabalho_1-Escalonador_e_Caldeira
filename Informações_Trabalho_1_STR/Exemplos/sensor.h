#ifndef SENSOR_H
#define SENSOR_H

/*TEMPERATURA REFERENCIAL*/
void referenciaTemp_put(double ref);
double referenciaTemp_get(void);

/*SENSOR DE TEMPERATURA*/
void sensorTemp_put( double temp_lido);
double sensorTemp_get(void);
void sensorTemp_alarme( double limite);

/*SENSOR DE TEMPERATURA DE ENTRADA*/
void sensorTempEntrada_put( double temp_entr );
double sensorTempEntrada_get(void);

/*SENSOR DE TEMPERATURA AMBIENTE*/
void sensorTempAmbiente_put( double temp_amb );
double sensorTempAmbiente_get(void);

#endif



