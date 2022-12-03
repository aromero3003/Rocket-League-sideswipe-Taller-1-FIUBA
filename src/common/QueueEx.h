#ifndef __QUEUEEx_H__
#define __QUEUEEx_H__

#include <stdexcept>
#include <string>

class QueueEx : public std::exception {

    public:
    QueueEx() {}
    char * what () {
        return nullptr;
    }
};
#endif
