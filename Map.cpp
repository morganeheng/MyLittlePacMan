#include "Map.hh"
#include "Scene.hh"
#include "TimeManager.hh"
#include "ResourcesManager.hh"

Map::Map() {

}

Map::Map(int x, int y, int left, int top, int width, int height) {
    ResourcesManager &rm = ResourcesManager::GetInstance();
    SetTexture(rm.textureMap);
    SetTextureRect(left, top, width, height);
    SetX(x);
    SetY(y);
}

Map::~Map() {
    delete this;
}

void Map::Draw() {
    Scene &Window = Scene::GetInstance();
    Window.draw(this->GetSprite());
}

void Map::Update() {
    this->sprite.setTexture(this->texture);
}

double Map::GetX() const {
    return this->sprite.getPosition().x;
}

void Map::SetX(double newX) {
    this->sprite.setPosition(newX, sprite.getPosition().y);
}

double Map::GetY() const {
    return this->sprite.getPosition().y;
}

void Map::SetY(double newY) {
    this->sprite.setPosition(sprite.getPosition().x, newY);
}

sf::Sprite Map::GetSprite() const {
    return this->sprite;
}

void Map::SetSprite(sf::Sprite newSprite) {
    this->sprite = newSprite;
}

sf::Texture Map::GetTexture() const {
    return this->texture;
}

void Map::SetTexture(sf::Texture newTexture) {
    this->texture = newTexture;
    this->sprite.setTexture(newTexture);
}

void Map::SetTextureRect(int left, int top, int width, int height) {
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(left,top, width, height));
}

void Map::Notify(IObservable* IObservable) {
    CheckCollision((Character *)IObservable);
}

void Map::CheckCollision(Character* IObservable) {
    TimeManager &tm = TimeManager::GetInstance();

    // si le personnage n'est pas dans le ghost house
    if (IObservable->GetTile().nb_tile < 191) {
        // si le personnage de cogne aux murs
        if (IObservable->GetSprite().getGlobalBounds().intersects(GetSprite().getGlobalBounds()))
        {
            // on lui dit qu'il ne peut plus bouger et on le recule 
            if (IObservable->GetDirection() == Up)
            {
                IObservable->SetCanMoveUp(false);
                IObservable->Move(0, IObservable->GetSpeed());
                IObservable->SetCanMove(false);
            }
            if (IObservable->GetDirection() == Down)
            {
                IObservable->SetCanMoveDown(false);
                IObservable->Move(0, -IObservable->GetSpeed());
                IObservable->SetCanMove(false);
            }
            if (IObservable->GetDirection() == Left)
            {
                IObservable->SetCanMoveLeft(false);
                IObservable->Move(IObservable->GetSpeed(), 0);
                IObservable->SetCanMove(false);
            }
            if (IObservable->GetDirection() == Right)
            {
                IObservable->SetCanMoveRight(false);
                IObservable->Move(-IObservable->GetSpeed(), 0);
                IObservable->SetCanMove(false);
            }
        }
    }
}
