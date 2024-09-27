#pragma once

#include <Arduino.h>

class Scheduler
{
    typedef void (*Callback)();

private:
    unsigned long _interval;
    unsigned long _lastCallbackExecution;
    Callback _callback;

public:
    Scheduler(unsigned long interval, Callback callback);
    void handle();
};