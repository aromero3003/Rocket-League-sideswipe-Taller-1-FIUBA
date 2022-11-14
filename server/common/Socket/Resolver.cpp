#include <cstring>
#include <netdb.h>
#include <iostream>

#include "ResolverError.h"
#include "Resolver.h"
#include "Liberror.h"

Resolver::Resolver(const char *hostname,
                   const char *servicename,
                   bool passive) {
    struct addrinfo hints;
    ::memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;  //  IPV6
    hints.ai_socktype = SOCK_STREAM;  //  TCP
    hints.ai_flags    = passive ? AI_PASSIVE : 0;

    this->result = this->current = nullptr;

    int s = ::getaddrinfo(hostname, servicename, &hints, &this->result);
    if (s != 0) {
        if (s == EAI_SYSTEM) {
            throw LibError(
                    errno,
                    "Name resolution failed for hostname '%s' y servname '%s'",
                    (hostname ? hostname : ""),
                    (servicename ? servicename : ""));
        } else {
            throw ResolverError(s);
        }
    }
    this->current = this->result;
}


bool Resolver::has_next() {
    return this->current != nullptr;
}

struct addrinfo *Resolver::next() {
    struct addrinfo *aux = this->current;
    this->current = aux->ai_next;
    return aux;
}

Resolver::Resolver(Resolver &&other) {
    this->result =  other.result;
    this->current = other.current;

    other.result = nullptr;
    other.current = nullptr;
}

Resolver &Resolver::operator=(Resolver &&other) {
    if (this == &other)
        return *this;

    if (this->result)
        ::freeaddrinfo(this->result);

    this->result =  other.result;
    this->current = other.current;

    other.result = nullptr;
    other.current = nullptr;

    return *this;
}

Resolver::~Resolver() {
    if (this->result)
        ::freeaddrinfo(this->result);
}
