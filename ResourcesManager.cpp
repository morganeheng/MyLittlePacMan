#include "ResourcesManager.hh"
#include "Scene.hh"

ResourcesManager ResourcesManager::rm = ResourcesManager();

ResourcesManager::ResourcesManager() {
    Scene &Window = Scene::GetInstance();
    font.loadFromFile("Resources/crackman.ttf");
    pacman_siren.openFromFile("Resources/pacman_siren.ogg");
    pacman_beginning.openFromFile("Resources/pacman_beginning.wav");
    pacman_beginning.setVolume(40);
    pacman_death.openFromFile("Resources/pacman_death.wav");
    pacman_eatghost.openFromFile("Resources/pacman_eatghost.wav");
    ghost_turntoblue.openFromFile("Resources/ghost_turntoblue.ogg");
    ghost_turntoblue.setVolume(70);
    pacman_munch.openFromFile("Resources/pacman_munch.wav");
    TexturePlay.loadFromFile("Resources/home_screen.jpg");
    texturePacMan.loadFromFile("Resources/pacman-perso1.png");
    textureGhost.loadFromFile("Resources/ghosts.png");
    textureBonus.loadFromFile("Resources/bonus.png");
    textureDot.loadFromFile("Resources/point.png");
    textureMap.loadFromFile("Resources/mapsprite32.png");
    icon.loadFromFile("Resources/pacman_icon.png");
    Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

ResourcesManager::~ResourcesManager() {

}

ResourcesManager& ResourcesManager::GetInstance() {
    return rm;
}
