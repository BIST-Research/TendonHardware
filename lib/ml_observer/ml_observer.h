#ifndef ML_OBSERVER_H
#define ML_OBSERVER_H

typedef void (*NotifyObserver)(void* instance, const int arg);

typedef struct
{
    void* instance;
    NotifyObserver notification;
} Ovserver;

#endif // ML_OBSERVER_H