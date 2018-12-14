#ifndef ITEM_H_
#define ITEM_H_

#include "AbstractEntity.hh"
#include "IObserver.hh"
#include "IObservable.hh"
#include <SFML/Graphics.hpp>

class Item : public AbstractEntity, public IObserver {
    public:
        virtual ~Item();
        virtual void Draw();
        virtual void Update();
        int GetX() const;
        void SetX(int);
        int GetY() const;
        void SetY(int);
        sf::Sprite GetSprite() const;
        void SetSprite(sf::Sprite);
        sf::Texture GetTexture() const;
        void SetTexture(sf::Texture);
        void SetTextureRect(int, int, int, int);
        bool GetIsDestroy() const;
        void SetIsDestroy(bool);
        virtual void Notify(IObservable*);
    private:
        sf::Sprite sprite;
        sf::Texture texture;
        bool isDestroy = false;
    protected:
        Item();
};

#endif

