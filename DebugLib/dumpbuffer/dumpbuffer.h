#ifndef dumpbuffer_h
#define dumpbuffer_h 1
// dumpbuffer is a function that will print out the buffer from the first argument.
// gcc
#ifdef __cplusplus //if c++ we need to extern
extern "C" {
#endif
    void dumpbuffer(const void *buffer, const int size);
#ifdef __cplusplus //removes the closing bracket for c compiler
};
#endif
#endif // dumpbuffer_h

