#ifndef JSON_DEFINES_H
#define JSON_DEFINES_H

// The library namespace. This value can be changed here if there is already a json namespace defined in the environment.
#define JSONLIB_NAMESPACE json

// Max size of a json_int. Changing this value to another signed int representation shouldn't be a problem.
#define JSONLIB_INT_TYPE std::int64_t

// Define this to get verbose warning / error output written into std::cout and std::cerr.
// #define JSONLIB_VERBOSE_DEBUG

#endif // JSON_LIBRARY_H
