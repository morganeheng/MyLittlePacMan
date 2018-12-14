#ifndef GHOST_H_
#define GHOST_H_

#include "Character.hh"
#include "PacMan.hh"
#include "Mode.hh"
#include <string>

class Ghost : public Character {
    public:
        Ghost();
        Ghost(int, int, int, int, int, int, int, std::string);
        ~Ghost();
        virtual void Draw();
        virtual void Update();
        std::string GetName() const;
        void SetName(std::string);
        bool GetIsPrey() const;
        void SetIsPrey(bool);
        bool GetIsCatch() const;
        void SetIsCatch(bool);
        int GetTime() const;
        void SetTime(int);
        Mode GetMode() const;
        void SetMode(Mode);
        virtual void Notify(IObservable*);
        void CheckCollision(PacMan*);
        int GetTilePinky(int, int, int);
        int GetTileInky(int, int, int, Character*);
        int GetTileClyde(PacMan*);
        std::vector<int> FillPasArray(Ghost*, int);
        void Chase();
        void Flee();
    private:
        std::string name;
        bool isPrey = false;
        bool isCatch = false;
        int time;
        Mode mode;
};

#endif

