#ifndef IOBSERVABLE_H_
#define IOBSERVABLE_H_

#include "IObserver.hh"

class IObserver;

class IObservable {
    public:
        virtual ~IObservable() {}
        virtual void AddObserver(IObserver*) = 0;
        virtual void RemoveObserver(IObserver*) = 0;
};

#endif
