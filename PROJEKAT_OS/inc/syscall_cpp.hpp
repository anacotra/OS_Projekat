//
// Created by os on 1/24/24.
//

#ifndef PROJECT_OS_SYSCALL_CPP_HPP
#define PROJECT_OS_SYSCALL_CPP_HPP

#include "syscall_c.hpp"
#include "TCB.hpp"

void* operator new (size_t size);
void* operator new[] (size_t size);
void operator delete (void* obj);
void operator delete[] (void* obj);

class Thread {
public:
    Thread (void (*body)(void*), void* arg);
    virtual ~Thread ();
    int start ();
    void join();
    static void dispatch ();
    static int sleep (time_t t);
    static void tStart(void* arg);

protected:
    Thread ();
    virtual void run () {}

private:
    thread_t myHandle;
    void (*body)(void*);
    void* arg;
};


class Semaphore {
public:
    Semaphore (unsigned init = 1);
    virtual ~Semaphore ();
    int wait ();
    int signal ();

private:
    sem_t myHandle;
};


class PeriodicThread : public Thread {
public:
    void terminate ();

protected:
    PeriodicThread (time_t period);
    virtual void periodicActivation () {}

private:
    time_t period;
};


class Console {
public:
    static char getc ();
    static void putc (char);
};

#endif //PROJECT_OS_SYSCALL_CPP_HPP
