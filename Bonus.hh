#ifndef BONUS_H_
#define BONUS_H_

#include "Item.hh"
#include "PacMan.hh"

class Bonus : public Item {
    public:
        Bonus();
        Bonus(int, int, int, int, int, int);
        ~Bonus();
        virtual void Draw();
        virtual void Update();
        virtual void Notify(IObservable*);
        void CheckCollision(PacMan*);
};

#endif


