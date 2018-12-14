#include "Dot.hh"
#include "Scene.hh"
#include "ResourcesManager.hh"

Dot::Dot() {

}

Dot::Dot(int x, int y, int left, int top, int width, int height) {
    ResourcesManager &rm = ResourcesManager::GetInstance();
    SetTexture(rm.textureDot);
    SetTextureRect(left, top, width, height);
    SetX(x);
    SetY(y);
}

Dot::~Dot() {
    delete this;
}

void Dot::Draw() {
    Scene &Window = Scene::GetInstance();
    Window.draw(this->GetSprite());
}

void Dot::Update() {
    Scene &Window = Scene::GetInstance();
    // si le point se fait manger on le supprime de la scène
    if (GetIsDestroy() == true)
        Window.RemoveEntity(this);
}

void Dot::Notify(IObservable* IObservable) {
    CheckCollision((PacMan *)IObservable);
}

void Dot::CheckCollision(PacMan* IObservable) {
    Scene &Window = Scene::GetInstance();
    ResourcesManager &rm = ResourcesManager::GetInstance();

    // si le point se fait mangé
    if (GetSprite().getGlobalBounds().intersects(IObservable->GetSprite().getGlobalBounds()))
    {
        // on joue la musique de pacman en train de manger
        rm.pacman_munch.play();
        // on augmente le score
        IObservable->SetScore(IObservable->GetScore() + 10);
        // le nombre de point diminue
        Window.SetNbDot(Window.GetNbDot() - 1);
        // on dit que le point s'est fait mangé
        SetIsDestroy(true);
        // on l'enlève de la liste des observers
        IObservable->RemoveObserver(this);
    }
}
