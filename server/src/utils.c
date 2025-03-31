#include"utils.h"

t_log* logger;

int iniciar_servidor(void)
{

    int socket_servidor;
    int error;
    struct addrinfo hints, *servinfo;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, PUERTO, &hints, &servinfo);

    socket_servidor = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if (socket_servidor == -1) {
        log_error(logger, "Error al crear el socket");
        abort();
    }
    log_info(logger, "Socket creado correctamente");

    if (setsockopt(socket_servidor, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) == -1) {
        log_error(logger, "Error al configurar el socket");
        abort();
    }
    log_info(logger, "Socket configurado correctamente");


    if (bind(socket_servidor, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        log_error(logger, "Error al asociar el socket");
        abort();
    }
    log_info(logger, "Socket asociado correctamente");

    // Escuchamos el socket
    if (listen(socket_servidor, SOMAXCONN) == -1) {
        log_error(logger, "Error al escuchar el socket");
        abort();
    }
    log_info(logger, "Socket escuchando correctamente");

    freeaddrinfo(servinfo);
    log_trace(logger, "Listo para escuchar a mi cliente");

    return socket_servidor;
}

int esperar_cliente(int socket_servidor)
{

    // Aceptamos un nuevo cliente
    int socket_cliente;
    int error;
    // Aceptamos un nuevo cliente
    error = accept(socket_servidor, NULL, NULL);
    if (error == -1) {
        log_error(logger, "Error al aceptar el cliente");
        abort();
    }
    log_info(logger, "Cliente aceptado correctamente");
    log_info(logger, "Se conecto un cliente!");

    return socket_cliente;
}

int recibir_operacion(int socket_cliente)
{
	int cod_op;
	if(recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) > 0)
		return cod_op;
	else
	{
		close(socket_cliente);
		return -1;
	}
}

void* recibir_buffer(int* size, int socket_cliente)
{
	void * buffer;

	recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv(socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}

void recibir_mensaje(int socket_cliente)
{
	int size;
	char* buffer = recibir_buffer(&size, socket_cliente);
	log_info(logger, "Me llego el mensaje %s", buffer);
	free(buffer);
}

t_list* recibir_paquete(int socket_cliente)
{
	int size;
	int desplazamiento = 0;
	void * buffer;
	t_list* valores = list_create();
	int tamanio;

	buffer = recibir_buffer(&size, socket_cliente);
	while(desplazamiento < size)
	{
		memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
		desplazamiento+=sizeof(int);
		char* valor = malloc(tamanio);
		memcpy(valor, buffer+desplazamiento, tamanio);
		desplazamiento+=tamanio;
		list_add(valores, valor);
	}
	free(buffer);
	return valores;
}
