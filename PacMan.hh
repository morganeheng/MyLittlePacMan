#ifndef PACMAN_H_
#define PACMAN_H_

#include "Character.hh"

class PacMan : public Character {
    public:
        PacMan();
        ~PacMan();
        virtual void Draw();
        virtual void Update();
        int GetLife() const;
        void SetLife(int);
        int GetScore() const;
        void SetScore(int);
    private:
        int life;
        int score;
        sf::Text scoretext;
        sf::Text lifetext;
        sf::Text wintext;
        sf::Text losetext;
        sf::Text replay;
        sf::Text ready;
        sf::Sprite SpritePlay;
        sf::Sprite SpriteLife;
        sf::Sprite SpriteLife2;
        sf::Sprite SpriteLife3;
};

#endif
