#ifndef DOT_H_
#define DOT_H_

#include "Item.hh"
#include "PacMan.hh"

class Dot : public Item {
    public:
        Dot();
        Dot(int, int, int, int, int, int);
        ~Dot();
        virtual void Draw();
        virtual void Update();
        virtual void Notify(IObservable*);
        void CheckCollision(PacMan*);
};

#endif
