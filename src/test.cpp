#include "common/blocking_queue/blocking_queue.h"
#include "common/blocking_queue/protected_queue.h"
#include <iostream>



int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    size_t sz = sizeof(arr) / sizeof(*arr);

    BlockingQueue<int> bq;
    for (int i = 0; i < sz; i++) {
        bq.push(arr[i]);
    }
    std::cout << bq.size() << std::endl;
    std::cout << bq.pop() << std::endl;

    ProtectedQueue<int> pq;
    for (int i = 0; i < sz; i++) {
        pq.push(arr[i]);
    }
    std::cout << pq.size() << std::endl;
}
