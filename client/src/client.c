#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	log_info (logger, "Hola! Soy un log");
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
    if (config == NULL) {
        log_error(logger, "No se pudo abrir el archivo de configuracion");
        abort();
    } else {
        log_info(logger, "Archivo de configuracion abierto correctamente");
    } 
	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	ip = config_get_string_value(config, "IP");
    puerto = config_get_string_value(config, "PUERTO");
    valor = config_get_string_value(config, "CLAVE");

	if (ip == NULL || puerto == NULL || valor == NULL) {
        log_error(logger, "No se pudieron leer todos los valores del archivo de configuracion");
        abort();
    }

    // Loggeamos el valor de config
    log_info(logger, "IP: %s, PUERTO: %s, VALOR: %s", ip, puerto, valor);

	

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);



	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	nuevo_logger = log_create("client.log", "CLIENTE", 1, LOG_LEVEL_INFO);
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
    nuevo_config = config_create("./cliente.config");
    // Usando la función config_create, creamos un config con el nombre "client.config"
    // Si no se pudo abrir el archivo, la función devuelve NULL

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
    char* leido;

    // La primera te la dejo de yapa
    leido = readline("> ");

    // El resto, las vamos leyendo y logueando hasta recibir un string vacío
    while (strcmp(leido, "") != 0) {
        log_info(logger, "Leído: %s", leido);
        // Leemos de nuevo
        leido = readline("> ");
    }
    // Liberamos la memoria ocupada por la última línea leída
    // ¡No te olvides de liberar las lineas antes de regresar!
    log_info(logger,"CONSOLA CERRADA");
    free(leido);

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete


	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
