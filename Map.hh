#ifndef MAP_H_
#define MAP_H_

#include "AbstractEntity.hh"
#include "IObserver.hh"
#include "IObservable.hh"
#include "Character.hh"
#include <SFML/Graphics.hpp>

class Map : public AbstractEntity, public IObserver{
    public:
        Map();
        Map(int, int, int, int, int, int);
        ~Map();
        virtual void Draw();
        virtual void Update();
        double GetX() const;
        void SetX(double);
        double GetY() const;
        void SetY(double);
        sf::Sprite GetSprite() const;
        void SetSprite(sf::Sprite);
        sf::Texture GetTexture() const;
        void SetTexture(sf::Texture);
        void SetTextureRect(int, int, int, int);
        virtual void Notify(IObservable*);
        void CheckCollision(Character*);
    private:
        sf::Sprite sprite;
        sf::Texture texture;
};

#endif

