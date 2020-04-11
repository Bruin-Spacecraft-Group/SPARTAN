#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

namespace spartan {
    // Standard getter for timestamp
    unsigned long getTimeMillis();

    // Extremely GPS-specific function checking whether a C-string starts with a specified prefix
    bool strStartsWith(const char *str, const std::string &prefix);
}

#endif // UTILS_H_INCLUDED
