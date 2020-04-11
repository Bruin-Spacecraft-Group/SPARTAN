#include <chrono>
#include <string>

#include "utils.h"

unsigned long spartan::getTimeMillis() {
    return (unsigned long) std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
}

bool strStartsWith(const char *str, const std::string &prefix) {
    int i = 0;
    while (prefix[i]) {
        if (prefix[i] != str[i])
            return false;
        i++;
    }
    return true;
}
