#include "src/common/socket.h"

#include <iostream>

#define FC *(float*)

void send_instructions(Socket &s) {

}

int main(int argc, const char *argv[]) {
    Socket s(argv[1], argv[2]);

    char data[39];
    bool was_closed = false;
    while (std::cin && not was_closed) {
        s.recvall(data, 39, &was_closed);
        std::cout << "Flag: " << (int)data[0] << std::endl;
        std::cout << "Ball: (x,y) = (" << FC(data + 1)  << " | " <<  FC(data + 5) << ") angle: " << FC (data+9) << std::endl;
        std::cout << "car1: (x,y) = ("<< FC(data + 17) << " | " << FC(data + 13) << ") angle: " << FC (data+21) << " orientation: " << (int)data[25] << std::endl;
        std::cout << "car1: (x,y) = ("<< FC(data + 30) << " | " << FC(data + 26) << ") angle: " << FC (data+34) << " orientation: " << (int)data[38] << std::endl;

        //std::cout << "car2: (x,y) = "<< FC(data + 26) << FC(data + 30) << "angle: " << FC (data+34) << "orientation: " << (int)data[38] << std::endl;
        std::cout << "Termina iteración\n" << std::endl;
    }
}
