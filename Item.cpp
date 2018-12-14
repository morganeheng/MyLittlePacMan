#include "Item.hh"
#include "Scene.hh"

Item::Item() {

}

Item::~Item() {

}

void Item::Draw() {
    Scene &Window = Scene::GetInstance();
    Window.draw(this->GetSprite());
}

void Item::Update() {

}

int Item::GetX() const {
    return this->sprite.getPosition().x;
}

void Item::SetX(int newX) {
    this->sprite.setPosition(newX, sprite.getPosition().y);
}

int Item::GetY() const {
    return this->sprite.getPosition().y;
}

void Item::SetY(int newY) {
    this->sprite.setPosition(sprite.getPosition().x, newY);
}

void Item::Notify(IObservable* IObservable) {

}

sf::Sprite Item::GetSprite() const {
    return this->sprite;
}

void Item::SetSprite(sf::Sprite newSprite) {
    this->sprite = newSprite;
}

sf::Texture Item::GetTexture() const {
    return this->texture;
}

void Item::SetTexture(sf::Texture newTexture) {
    this->texture = newTexture;
    this->sprite.setTexture(newTexture);
}

void Item::SetTextureRect(int left, int top, int width, int height) {
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(left,top, width, height));
}

bool Item::GetIsDestroy() const {
    return this->isDestroy;
}

void Item::SetIsDestroy(bool newIsDestroy) {
    this->isDestroy = newIsDestroy;
}
