#ifndef RESOURCESMANAGER_H_
#define RESOURCESMANAGER_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ResourcesManager {
    private:
        static ResourcesManager rm;
    public:
        ~ResourcesManager();
        static ResourcesManager& GetInstance();
        sf::Font font;
        sf::Music pacman_siren;
        sf::Music pacman_beginning;
        sf::Music pacman_death;
        sf::Music pacman_eatghost;
        sf::Music ghost_turntoblue;
        sf::Music pacman_munch;
        sf::Texture TexturePlay;
        sf::Texture texturePacMan;
        sf::Texture textureGhost;
        sf::Texture textureBonus;
        sf::Texture textureDot;
        sf::Texture textureMap;
        sf::Image icon;
    protected:
        ResourcesManager();
        ResourcesManager& operator=(const ResourcesManager&);
        ResourcesManager(const ResourcesManager&);
};

#endif
