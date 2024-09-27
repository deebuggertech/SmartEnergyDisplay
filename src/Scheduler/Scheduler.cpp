#include "./Scheduler.hpp"

Scheduler::Scheduler(unsigned long interval, Callback callback)
    : _interval(interval), _lastCallbackExecution(millis()), _callback(callback)
{
}

void Scheduler::handle()
{
    if (millis() - _lastCallbackExecution > _interval)
    {
        _callback(); 
        _lastCallbackExecution = millis();
    }
}
