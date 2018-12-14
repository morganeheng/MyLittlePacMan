#include "Character.hh"
#include "Scene.hh"

Character::Character() {

}

Character::~Character() {
    delete this;
}

void Character::Draw() {
    Scene &Window = Scene::GetInstance();
    Window.draw(this->sprite);
}

void Character::Update() {

}

int Character::GetX() const {
    return this->sprite.getPosition().x;
}

void Character::SetX(int newX) {
    this->sprite.setPosition(newX, sprite.getPosition().y);
}

int Character::GetY() const {
    return this->sprite.getPosition().y;
}

void Character::SetY(int newY) {
    this->sprite.setPosition(sprite.getPosition().x, newY);
}

Direction Character::GetDirection() const {
    return this->direction;
}

void Character::SetDirection(Direction newDirection) {
    this->direction = newDirection;
}

sf::Sprite Character::GetSprite() const {
    return this->sprite;
}

void Character::SetSprite(sf::Sprite newSprite) {
    this->sprite = newSprite;
}

sf::Texture Character::GetTexture() const {
    return this->texture;
}

void Character::SetTexture(sf::Texture newTexture) {
    this->texture = newTexture;
    this->sprite.setTexture(newTexture);
}

void Character::SetTextureRect(int left, int top, int width, int height) {
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(left,top, width, height));
}

float Character::GetSpeed() const {
    return this->speed;
}

void Character::SetSpeed(float newSpeed) {
    this->speed = newSpeed;
}

sf::Vector2i Character::GetAnimation() const {
    return this->animation;
}

void Character::SetAnimation(int newX, int newY) {
    this->animation.x = newX;
    this->animation.y = newY;
}

bool Character::GetCanMove() const {
	return this->canMove;
}

void Character::SetCanMove(bool newCanMove) {
	this->canMove = newCanMove;
}

bool Character::GetCanMoveUp() const {
	return this->canMoveUp;
}

void Character::SetCanMoveUp(bool newCanMoveUp) {
	this->canMoveUp = newCanMoveUp;
}

bool Character::GetCanMoveDown() const {
	return this->canMoveDown;
}

void Character::SetCanMoveDown(bool newCanMoveDown) {
	this->canMoveDown = newCanMoveDown;
}

bool Character::GetCanMoveLeft() const {
	return this->canMoveLeft;
}

void Character::SetCanMoveLeft(bool newCanMoveLeft) {
	this->canMoveLeft = newCanMoveLeft;
}

bool Character::GetCanMoveRight() const {
	return this->canMoveRight;
}

void Character::SetCanMoveRight(bool newCanMoveRight) {
	this->canMoveRight = newCanMoveRight;
}

void Character::Move(float x, float y) {
    this->sprite.move(x, y);
}

Tile Character::GetTile() const {
    return this->tile;
}

void Character::SetTile(Tile newTile) {
    this->tile = newTile;
}

void Character::AddObserver(IObserver* IObserver) {
    this->IObservers.push_back(IObserver);
}

void Character::RemoveObserver(IObserver* IObserver) {
    this->IObservers.erase(std::remove(this->IObservers.begin(), this->IObservers.end(), IObserver), this->IObservers.end());
}

std::vector<IObserver*> Character::GetObservers() const {
    return this->IObservers;
}

void Character::Notify(IObservable*) {

}
