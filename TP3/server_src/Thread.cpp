#include "Thread.h"

//--------------------------------------------------------------------------------------
Thread::Thread() {}

void Thread::start() { thread = std::thread(&Thread::run, this); }

void Thread::join() { thread.join(); }

Thread::~Thread() {}
//--------------------------------------------------------------------------------------
