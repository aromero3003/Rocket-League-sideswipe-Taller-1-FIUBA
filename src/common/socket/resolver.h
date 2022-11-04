#ifndef __RESOLVER_H__
#define __RESOLVER_H__

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
/*
 * Resolver de hostnames y servicenames
 *
 * Por simplificacion el TDA se limita a
 * direcciones IPv4 para TCP
 * */
class Resolver {
 private:
    struct addrinfo *result;
    struct addrinfo *current;

 public:
/*
 * Constructor del resolver, resuelve hostname y servicio.
 *
 * Si `passive` es `true` y `hostname` es `nullptr`
 * las direcciones retornadas seran aptas para hacer un `bind`
 * y poner al socket en modo escucha para recibir conexiones
 *
 * En caso de error se lanza una excepción.
 * */
    Resolver(const char *hostname, const char *servicename, bool passive);

/*
 * Devuelve true si hay más direcciones disponibles para probar
 * `Resolver::next` devuelve la siguiente direccion disponible para probar
 * */
    bool has_next();
    struct addrinfo *next();

/*
 * Constructor por copia y asignacion por copia dehabilitados
 * */
    Resolver(const Resolver &other) = delete;
    Resolver &operator=(const Resolver &other) = delete;    

/*
 * Constructores y asignacion por movimiento 
 * */
    Resolver(Resolver &&other);
    Resolver &operator=(Resolver &&other);

/*
 * Liberacion de recursos
 * */
    ~Resolver();
};

#endif  //  __RESOLVER_H__
