#ifndef IOBSERVER_H_
#define IOBSERVER_H_

#include "IObservable.hh"

class IObservable;

class IObserver {
    public:
        virtual ~IObserver() {}
        virtual void Notify(IObservable*) = 0;
};

#endif
