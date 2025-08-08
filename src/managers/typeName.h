#pragma once

#include <string>
#include <typeinfo>

template<typename T>
struct TypeName {
    static std::string get() {
        return typeid(T).name();
    }
};

// Macro to define specializations easily
#define DEFINE_TYPE_NAME(TYPE) \
    template<>                 \
    struct TypeName<TYPE> {    \
        static std::string get() { return #TYPE; } \
    };
