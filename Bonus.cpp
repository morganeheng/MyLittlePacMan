#include "Bonus.hh"
#include "Scene.hh"
#include "ResourcesManager.hh"

Bonus::Bonus() {

}

Bonus::Bonus(int x, int y, int left, int top, int width, int height) {
    ResourcesManager &rm = ResourcesManager::GetInstance();
    SetTexture(rm.textureBonus);
    SetTextureRect(left, top, width, height);
    SetX(x);
    SetY(y);
}

Bonus::~Bonus() {
    delete this;
}

void Bonus::Draw() {
    Scene &Window = Scene::GetInstance();
    Window.draw(this->GetSprite());
}

void Bonus::Update() {
    Scene &Window = Scene::GetInstance();
    // pour faire clignotter les bonus
    if (GetIsDestroy() == false)
    {
        if (Window.GetClignote() % 5 == 0) {
            SetTextureRect(10, 10, 12, 12);
            SetX(GetX() + 1);
            SetY(GetY() + 1);
        } else if (Window.GetClignote() % 5 == 2) {
            SetTextureRect(41, 9, 15, 16);
            SetX(GetX() - 1);
            SetY(GetY() - 1);
        }
    } else {
        // on enlève le bonus de la scène lorsqu'il se fait manger
        Window.RemoveEntity(this);
    }
}

void Bonus::Notify(IObservable* IObservable) {
    CheckCollision((PacMan *)IObservable);
}

void Bonus::CheckCollision(PacMan* IObservable) {
    Scene &Window = Scene::GetInstance();
    ResourcesManager &rm = ResourcesManager::GetInstance();
    
    // si Pacman mange un bonus
    if (GetSprite().getGlobalBounds().intersects(IObservable->GetSprite().getGlobalBounds()))
    {
        // on joue la musique des fantômes qui sont des proies
        rm.ghost_turntoblue.play();
        // le score augmente
        IObservable->SetScore(IObservable->GetScore() + 50);
        // le nombre de bonus diminue
        Window.SetNbBonus(Window.GetNbBonus() - 1);
        // on dit que le bonus s'est fait mangé
        SetIsDestroy(true);
        // on l'enlève de la liste des observers
        IObservable->RemoveObserver(this);
        for (int i = Window.GetEntities().size() - 4; i < Window.GetEntities().size(); i++) {
            // fantômes deviennent des proies
            Window.SetPrey((Ghost*)Window.GetEntities()[i]);
        }
    }
}
