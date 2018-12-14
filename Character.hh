#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "AbstractEntity.hh"
#include "IObservable.hh"
#include "IObserver.hh"
#include "Direction.hh"
#include "Tile.hh"
#include <SFML/Graphics.hpp>
#include <vector>

class Character : public AbstractEntity, public IObservable, public IObserver {

    public:
        virtual ~Character();
        virtual void Draw();
        virtual void Update();
        int GetX() const;
        void SetX(int);
        int GetY() const;
        void SetY(int);
        Direction GetDirection() const;
        void SetDirection(Direction);
        sf::Sprite GetSprite() const;
        void SetSprite(sf::Sprite);
        sf::Texture GetTexture() const;
        void SetTexture(sf::Texture);
        void SetTextureRect(int, int, int, int);
        float GetSpeed() const;
        void SetSpeed(float);
        sf::Vector2i GetAnimation() const;
        void SetAnimation(int, int);
        bool GetCanMove() const;
        void SetCanMove(bool);
        bool GetCanMoveUp() const;
        void SetCanMoveUp(bool);
        bool GetCanMoveDown() const;
        void SetCanMoveDown(bool);
        bool GetCanMoveLeft() const;
        void SetCanMoveLeft(bool);
        bool GetCanMoveRight() const;
        void SetCanMoveRight(bool);
        void Move(float x, float y);
        Tile GetTile() const;
        void SetTile(Tile);
        virtual void AddObserver(IObserver*);
        virtual void RemoveObserver(IObserver*);
        std::vector<IObserver*> GetObservers() const;
        virtual void Notify(IObservable*);
    private:
        Direction direction;
        sf::Sprite sprite;
        sf::Texture texture;
        float speed;
        sf::Vector2i animation;
        bool canMove = false;
        bool canMoveUp = false;
        bool canMoveDown = false;
        bool canMoveLeft = false;
        bool canMoveRight = false;
        Tile tile;
        std::vector<IObserver*> IObservers;
    protected:
        Character();
};

#endif
