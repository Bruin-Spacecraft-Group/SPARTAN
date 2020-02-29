#include <chrono>

#include "utils.h"

unsigned long spartan::getTimeMillis() {
    return (unsigned long) std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
}
