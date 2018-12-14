#ifndef SCENE_H_
#define SCENE_H_


#include "AbstractEntity.hh"
#include "Tile.hh"
#include "Character.hh"
#include "Ghost.hh"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Scene : public sf::RenderWindow {
    public:
        static Scene& GetInstance();
        ~Scene();
        std::vector<AbstractEntity*> GetEntities() const;
        void AddEntity(AbstractEntity*);
        void RemoveEntity(AbstractEntity*);
        void fillArray();
        void Update();
        void fillArrayBonus();
        int GetClignote() const;
        void SetClignote(int);
        int GetNbDot() const;
        void SetNbDot(int);
        int GetNbBonus() const;
        void SetNbBonus(int);
        Tile tiles[195];
        void initTile();
        void GetPath(int, std::string);
        void Start();
        void initCharacter(Character*, int, int, int, int, int);
        void SetPrey(Ghost*);
        void Play();
        bool GetIsEnd() const;
        void SetIsEnd(bool);
    private:
        static Scene sc;
        std::vector<AbstractEntity*> Entities;
        int clignote;
        int nbDot;
        int nbBonus;
        bool isEnd = false;
        sf::Text fpstext;
    protected:
        Scene();
        Scene& operator=(const Scene&);
        Scene(const Scene&);
};

#endif
