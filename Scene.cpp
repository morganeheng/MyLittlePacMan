#include "Scene.hh"
#include "TimeManager.hh"
#include "ResourcesManager.hh"
#include "ItemFactory.hh"
#include "CharacterFactory.hh"
#include "Item.hh"
#include "Map.hh"
#include <sstream>

Scene Scene::sc = Scene();

Scene::Scene() {
    ResourcesManager &rm = ResourcesManager::GetInstance();
    this->create(sf::VideoMode(610, 750), "PacMan");
    this->setPosition(sf::Vector2i(0, 0));
    this->setFramerateLimit(10);
    this->setVerticalSyncEnabled(true);
    this->setKeyRepeatEnabled(false);
    // on initialse le texte du fps
    fpstext.setString("FPS ");
    fpstext.setFont(rm.font);
    fpstext.setCharacterSize(30);
    fpstext.setFillColor(sf::Color::White);
    fpstext.setPosition(230, 700);
}

Scene::~Scene() {

}

Scene& Scene::GetInstance() {
    return sc;
}

std::vector<AbstractEntity*> Scene::GetEntities() const {
    return this->Entities;
}

void Scene::AddEntity(AbstractEntity* Entity) {
    this->Entities.push_back(Entity);
}

void Scene::RemoveEntity(AbstractEntity* Entity) {
    this->Entities.erase(std::remove(this->Entities.begin(), this->Entities.end(), Entity), this->Entities.end());

}

void Scene::Update() {
    TimeManager &tm = TimeManager::GetInstance();
    tm.Update();
    ResourcesManager &rm = ResourcesManager::GetInstance();

    // on calcule le fps
    int framerate = 1 / (tm.GetElapsedTime() * 0.001);
    std::ostringstream ff;
    ff << framerate;
    fpstext.setString("FPS = " + ff.str());
    this->draw(fpstext);

    this->clignote = this->clignote + 1;
    // on joue la musique de fond 
    if (this->clignote == 5) {
        this->clignote = 0;
        if (tm.GetStartedTime() > 4000  && this->isEnd == false)
            rm.pacman_siren.play();
    }
    // on met a jour tout les éléments de la scene et on les affiche
    for (int i = 0; i < this->Entities.size(); i++) {
        this->Entities[i]->Update();
        this->Entities[i]->Draw();
    }
}

int Scene::GetClignote() const {
    return this->clignote;
}

void Scene::SetClignote(int newClignote) {
    this->clignote = newClignote;
}

int Scene::GetNbDot() const {
    return this->nbDot;
}

void Scene::SetNbDot(int newNbDot) {
    this->nbDot = newNbDot;
}

int Scene::GetNbBonus() const {
    return this->nbBonus;
}

void Scene::SetNbBonus(int newNbBonus) {
    this->nbBonus = newNbBonus;
}

void Scene::GetPath(int end, std::string pas) {
    Scene &Window = Scene::GetInstance();

    // on calcule le nombre de pas des fantomes
    for (int i = 0; i < 191; i++) {
        Window.tiles[i].checked = false;
        Window.tiles[i].done = false;
    }
    // on initialise le nombre de pas de la tuile qu'on vise à zéro
    int currentTile = end;
	if (pas.compare("pas_blinky") == 0)
		Window.tiles[currentTile].pas_blinky = 0;
	if (pas.compare("pas_pinky_up") == 0)
		Window.tiles[currentTile].pas_pinky_up = 0;
	if (pas.compare("pas_pinky_down") == 0)
		Window.tiles[currentTile].pas_pinky_down = 0;
	if (pas.compare("pas_pinky_left") == 0)
		Window.tiles[currentTile].pas_pinky_left = 0;
	if (pas.compare("pas_pinky_right") == 0)
		Window.tiles[currentTile].pas_pinky_right = 0;
	if (pas.compare("pas_inky_up") == 0)
		Window.tiles[currentTile].pas_inky_up = 0;
	if (pas.compare("pas_inky_down") == 0)
		Window.tiles[currentTile].pas_inky_down = 0;
	if (pas.compare("pas_inky_left") == 0)
		Window.tiles[currentTile].pas_inky_left = 0;
	if (pas.compare("pas_inky_right") == 0)
		Window.tiles[currentTile].pas_inky_right = 0;
	if (pas.compare("pas_clyde") == 0)
		Window.tiles[currentTile].pas_pinky_right = 0;
    Window.tiles[currentTile].done = true;
    // la list1 contient les tuiles auxquelles on va calculer les pas
    int list1[4];
    std::vector<int> list2;
    // la list2 contient les tuiles dont on n'a pas encore vérifié les tuile adjacentes
    list2.push_back(currentTile);

    // pour chaque tuile de la list2 on ajoute ses tuiles adjacentes dans la list1 et list2
    while (list2.size() != 0) {
        list1[0] = Window.tiles[currentTile].up_tile;
        list1[1] = Window.tiles[currentTile].down_tile;
        list1[2] = Window.tiles[currentTile].left_tile;
        list1[3] = Window.tiles[currentTile].right_tile;
        if (Window.tiles[currentTile].up_tile != -1 && Window.tiles[Window.tiles[currentTile].up_tile].checked == false)
            list2.push_back(Window.tiles[currentTile].up_tile);
        if (Window.tiles[currentTile].down_tile != -1 && Window.tiles[Window.tiles[currentTile].down_tile].checked == false)
            list2.push_back(Window.tiles[currentTile].down_tile);
        if (Window.tiles[currentTile].left_tile != -1 && Window.tiles[Window.tiles[currentTile].left_tile].checked == false)
            list2.push_back(Window.tiles[currentTile].left_tile);
        if (Window.tiles[currentTile].right_tile != -1 && Window.tiles[Window.tiles[currentTile].right_tile].checked == false)
            list2.push_back(Window.tiles[currentTile].right_tile);
        // pour chaque tuile de la list1 on calcule le nombre de pas, on ajoute 1 au nombre de pas de la tuile actuelle
        for (int j = 0; j < 4; j++) {
            if (list1[j] != -1 && Window.tiles[list1[j]].done == false) {
                if (pas.compare("pas_blinky") == 0)
                    Window.tiles[list1[j]].pas_blinky = Window.tiles[currentTile].pas_blinky + 1;
                if (pas.compare("pas_pinky_up") == 0)
                    Window.tiles[list1[j]].pas_pinky_up = Window.tiles[currentTile].pas_pinky_up + 1;
                if (pas.compare("pas_pinky_down") == 0)
                    Window.tiles[list1[j]].pas_pinky_down = Window.tiles[currentTile].pas_pinky_down + 1;
                if (pas.compare("pas_pinky_left") == 0)
                    Window.tiles[list1[j]].pas_pinky_left = Window.tiles[currentTile].pas_pinky_left + 1;
                if (pas.compare("pas_pinky_right") == 0)
                    Window.tiles[list1[j]].pas_pinky_right = Window.tiles[currentTile].pas_pinky_right + 1;
                if (pas.compare("pas_inky_up") == 0)
                    Window.tiles[list1[j]].pas_inky_up = Window.tiles[currentTile].pas_inky_up + 1;
                if (pas.compare("pas_inky_down") == 0)
                    Window.tiles[list1[j]].pas_inky_down = Window.tiles[currentTile].pas_inky_down + 1;
                if (pas.compare("pas_inky_left") == 0)
                    Window.tiles[list1[j]].pas_inky_left = Window.tiles[currentTile].pas_inky_left + 1;
                if (pas.compare("pas_inky_right") == 0)
                    Window.tiles[list1[j]].pas_inky_right = Window.tiles[currentTile].pas_inky_right + 1;
                if (pas.compare("pas_clyde") == 0)
                    Window.tiles[list1[j]].pas_clyde = Window.tiles[currentTile].pas_clyde + 1;
                // quand on a finit de calculer le nombre de pas de la tuile adjacente on met done à true
                Window.tiles[list1[j]].done = true;
            }
        }
        // quand on a finit de vérifier cette tuile on met checked à true et on l'enlève de la list2
        Window.tiles[currentTile].checked = true;
        list2.erase(std::remove(list2.begin(), list2.end(), currentTile), list2.end());
        // on prend la prochaine tuile sur la liste et on recommence
        currentTile = list2[0];
    }
}

void Scene::Start() {
    TimeManager& tm = TimeManager::GetInstance();
    // on remet à zéro le timeManager
    tm.Start();
    // on initialise les personnages
    initCharacter((Character*)this->Entities[this->Entities.size() - 5], 288, 512, 142, 1, 0);
    initCharacter((Character*)this->Entities[this->Entities.size() - 4], 288, 256, 73, -1, 2);
    initCharacter((Character*)this->Entities[this->Entities.size() - 3], 288, 320, 192, 1, 2);
    initCharacter((Character*)this->Entities[this->Entities.size() - 2], 256, 320, 191, 5, 2);
    initCharacter((Character*)this->Entities[this->Entities.size() - 1], 320, 320, 193, 3, 2);
}

void Scene::initCharacter(Character* character, int x, int y, int tile, int animx, int animy) {
    character->SetX(x);
    character->SetY(y);
    character->SetTile(tiles[tile]);
    character->SetCanMove(false);
    character->SetCanMoveUp(false);
    character->SetCanMoveDown(false);
    character->SetCanMoveLeft(false);
    character->SetCanMoveRight(false);
    if (animy == 0)
        character->SetDirection(Left);
    if (animy == 2)
        character->SetDirection(Up);
    character->SetAnimation(animx, animy);
}

void Scene::SetPrey(Ghost* ghost) {
    TimeManager& tm = TimeManager::GetInstance();
    // les fantome deviennent des proies
    ghost->SetIsPrey(true);
    // on met à jour leur timer, lorsque 10 secondes seront écoulé les fantomes ne seront plus des proies
    ghost->SetTime(tm.GetStartedTime());
    // on change leur mode
    ghost->SetMode(Mode::Flee);
}

void Scene::Play() {
    // Initialisation d'une nouvelle partie
    this->isEnd = false;
    // on supprime tout les éléments de la scène
    Entities.clear();
    // on ajoute la map, les points et les bonus dans la scène
    fillArray();
    this->clignote = 1;
    this->nbDot = 152;
    this->nbBonus = 4;
    // on initialise les tuiles
    initTile();
    // on crée les personnages
    CharacterFactory Factory;
    Character *PacMan = Factory.Create("PacMan");
    Character *Blinky = Factory.Create("Blinky");
    Character *Pinky = Factory.Create("Pinky");
    Character *Inky = Factory.Create("Inky");
    Character *Clyde = Factory.Create("Clyde");
    // on ajoute les fantomes comme observers de pacman
    PacMan->AddObserver((IObserver*)Blinky);
    PacMan->AddObserver((IObserver*)Pinky);
    PacMan->AddObserver((IObserver*)Inky);
    PacMan->AddObserver((IObserver*)Clyde);
    // on ajoute les personnages dans la scene
    AddEntity(PacMan);
    AddEntity(Blinky);
    AddEntity(Pinky);
    AddEntity(Inky);
    AddEntity(Clyde);
    // on comment la partie
    Start();
}

bool Scene::GetIsEnd() const {
    return this->isEnd;
}

void Scene::SetIsEnd(bool newIsEnd) {
    this->isEnd = newIsEnd;
}

void Scene::fillArray() {
    // on initialise et ajoute la map, les points et les bonus à la scène
    ItemFactory Factory;
    Map* map1 = new Map(9, 9, 9, 9, 23, 23);
    Entities.push_back(map1);
    Map* map2 = new Map(9, 426, 9, 9, 23, 23);
    Entities.push_back(map2);
    Map* map3 = new Map(489, 234, 9, 9, 23, 23);
    Entities.push_back(map3);
    Map* map4 = new Map(489, 361, 9, 9, 23, 23);
    Entities.push_back(map4);
    Map* map5 = new Map(576, 9, 32, 9, 23, 23);
    Entities.push_back(map5);
    Map* map6 = new Map(576, 426, 32, 9, 23, 23);
    Entities.push_back(map6);
    Map* map7 = new Map(96, 234, 32, 9, 23, 23);
    Entities.push_back(map7);
    Map* map8 = new Map(96, 361, 32, 9, 23, 23);
    Entities.push_back(map8);
    Map* map9 = new Map(77, 77, 77, 13, 19, 19);
    Entities.push_back(map9);
    Map* map10 = new Map(173, 77, 77, 13, 19, 19);
    Entities.push_back(map10);
    Map* map11 = new Map(365, 77, 77, 13, 19, 19);
    Entities.push_back(map11);
    Map* map12 = new Map(493, 77, 77, 13, 19, 19);
    Entities.push_back(map12);
    Map* map13 = new Map(96, 77, 96, 13, 19, 19);
    Entities.push_back(map13);
    Map* map14 = new Map(224, 77, 96, 13, 19, 19);
    Entities.push_back(map14);
    Map* map15 = new Map(416, 77, 96, 13, 19, 19);
    Entities.push_back(map15);
    Map* map16 = new Map(512, 77, 96, 13, 19, 19);
    Entities.push_back(map16);
    Map* map17 = new Map(233, 297, 137, 9, 23, 23);
    Entities.push_back(map17);
    Map* map18 = new Map(352, 297, 160, 9, 23, 23);
    Entities.push_back(map18);
    Map* map19 = new Map(78, 165, 205, 5, 18, 22);
    Entities.push_back(map19);
    Map* map20 = new Map(494, 165, 205, 5, 18, 22);
    Entities.push_back(map20);
    Map* map21 = new Map(174, 485, 205, 5, 18, 22);
    Entities.push_back(map21);
    Map* map22 = new Map(366, 485, 205, 5, 18, 22);
    Entities.push_back(map22);
    Map* map23 = new Map(96, 165, 224, 5, 18, 22);
    Entities.push_back(map23);
    Map* map24 = new Map(512, 165, 224, 5, 18, 22);
    Entities.push_back(map24);
    Map* map25 = new Map(224, 485, 224, 5, 18, 22);
    Entities.push_back(map25);
    Map* map26 = new Map(416, 485, 224, 5, 18, 22);
    Entities.push_back(map26);
    Map* map27 = new Map(288, 165, 256, 5, 32, 27);
    Entities.push_back(map27);
    Map* map28 = new Map(288, 421, 256, 5, 32, 27);
    Entities.push_back(map28);
    Map* map29 = new Map(288, 549, 256, 5, 32, 27);
    Entities.push_back(map29);
    Map* map30 = new Map(160, 608, 288, 0, 32, 27);
    Entities.push_back(map30);
    Map* map31 = new Map(416, 608, 288, 0, 32, 27);
    Entities.push_back(map31);
    Map* map32 = new Map(288, 9, 320, 9, 32, 23);
    Entities.push_back(map32);
    Map* map33 = new Map(9, 224, 9, 32, 23, 23);
    Entities.push_back(map33);
    Map* map34 = new Map(9, 672, 9, 32, 23, 23);
    Entities.push_back(map34);
    Map* map35 = new Map(489, 288, 9, 32, 23, 23);
    Entities.push_back(map35);
    Map* map36 = new Map(489, 416, 9, 32, 23, 23);
    Entities.push_back(map36);
    Map* map37 = new Map(96, 288, 32, 32, 23, 23);
    Entities.push_back(map37);
    Map* map38 = new Map(96, 416, 32, 32, 23, 23);
    Entities.push_back(map38);
    Map* map39 = new Map(576, 224, 32, 32, 23, 23);
    Entities.push_back(map39);
    Map* map40 = new Map(576, 672, 32, 32, 23, 23);
    Entities.push_back(map40);
    Map* map41 = new Map(77, 96, 77, 32, 19, 19);
    Entities.push_back(map41);
    Map* map42 = new Map(173, 96, 77, 32, 19, 19);
    Entities.push_back(map42);
    Map* map43 = new Map(365, 96, 77, 32, 19, 19);
    Entities.push_back(map43);
    Map* map44 = new Map(493, 96, 77, 32, 19, 19);
    Entities.push_back(map44);
    Map* map45 = new Map(96, 96, 96, 32, 19, 19);
    Entities.push_back(map45);
    Map* map46 = new Map(224, 96, 96, 32, 19, 19);
    Entities.push_back(map46);
    Map* map47 = new Map(416, 96, 96, 32, 19, 19);
    Entities.push_back(map47);
    Map* map48 = new Map(512, 96, 96, 32, 19, 19);
    Entities.push_back(map48);
    Map* map49 = new Map(233, 352, 137, 32, 23, 23);
    Entities.push_back(map49);
    Map* map50 = new Map(352, 352, 160, 32, 23, 23);
    Entities.push_back(map50);
    Map* map51 = new Map(164, 171, 196, 43, 23, 21);
    Entities.push_back(map51);
    Map* map52 = new Map(164, 363, 196, 43, 23, 21);
    Entities.push_back(map52);
    Map* map53 = new Map(164, 555, 196, 43, 23, 21);
    Entities.push_back(map53);
    Map* map54 = new Map(420, 171, 196, 43, 23, 21);
    Entities.push_back(map54);
    Map* map55 = new Map(420, 363, 196, 43, 23, 21);
    Entities.push_back(map55);
    Map* map56 = new Map(420, 555, 196, 43, 23, 21);
    Entities.push_back(map56);
    Map* map57 = new Map(100, 544, 228, 32, 23, 21);
    Entities.push_back(map57);
    Map* map58 = new Map(164, 288, 228, 32, 23, 21);
    Entities.push_back(map58);
    Map* map59 = new Map(164, 415, 228, 32, 23, 21);
    Entities.push_back(map59);
    Map* map60 = new Map(292, 96, 228, 32, 23, 21);
    Entities.push_back(map60);
    Map* map61 = new Map(292, 224, 228, 32, 23, 21);
    Entities.push_back(map61);
    Map* map62 = new Map(292, 480, 228, 32, 23, 21);
    Entities.push_back(map62);
    Map* map63 = new Map(292, 608, 228, 32, 23, 21);
    Entities.push_back(map63);
    Map* map64 = new Map(420, 288, 228, 32, 23, 21);
    Entities.push_back(map64);
    Map* map65 = new Map(420, 416, 228, 32, 23, 21);
    Entities.push_back(map65);
    Map* map66 = new Map(484, 544, 228, 32, 23, 21);
    Entities.push_back(map66);
    Map* map67 = new Map(164, 224, 260, 32, 28, 32);
    Entities.push_back(map67);
    Map* map68 = new Map(416, 224, 288, 32, 27, 32);
    Entities.push_back(map68);
    Map* map69 = new Map(9, 32, 9, 64, 14, 32);
    Entities.push_back(map69);
    Map* map70 = new Map(9, 64, 9, 64, 14, 32);
    Entities.push_back(map70);
    Map* map71 = new Map(9, 96, 9, 64, 14, 32);
    Entities.push_back(map71);
    Map* map72 = new Map(9, 128, 9, 64, 14, 32);
    Entities.push_back(map72);
    Map* map73 = new Map(9, 160, 9, 64, 14, 32);
    Entities.push_back(map73);
    Map* map74 = new Map(9, 192, 9, 64, 14, 32);
    Entities.push_back(map74);
    Map* map75 = new Map(9, 448, 9, 64, 14, 32);
    Entities.push_back(map75);
    Map* map76 = new Map(9, 480, 9, 64, 14, 32);
    Entities.push_back(map76);
    Map* map77 = new Map(9, 512, 9, 64, 14, 32);
    Entities.push_back(map77);
    Map* map78 = new Map(9, 576, 9, 64, 14, 32);
    Entities.push_back(map78);
    Map* map79 = new Map(9, 608, 9, 64, 14, 32);
    Entities.push_back(map79);
    Map* map80 = new Map(9, 640, 9, 64, 14, 32);
    Entities.push_back(map80);
    Map* map81 = new Map(489, 256, 9, 64, 14, 32);
    Entities.push_back(map81);
    Map* map82 = new Map(489, 384, 9, 64, 14, 32);
    Entities.push_back(map82);
    Map* map83 = new Map(32, 9, 32, 73, 32, 13);
    Entities.push_back(map83);
    Map* map84 = new Map(64, 9, 32, 73, 32, 13);
    Entities.push_back(map84);
    Map* map85 = new Map(96, 9, 32, 73, 32, 13);
    Entities.push_back(map85);
    Map* map86 = new Map(128, 9, 32, 73, 32, 13);
    Entities.push_back(map86);
    Map* map87 = new Map(160, 9, 32, 73, 32, 13);
    Entities.push_back(map87);
    Map* map88 = new Map(192, 9, 32, 73, 32, 13);
    Entities.push_back(map88);
    Map* map89 = new Map(224, 9, 32, 73, 32, 13);
    Entities.push_back(map89);
    Map* map90 = new Map(256, 9, 32, 73, 32, 13);
    Entities.push_back(map90);
    Map* map91 = new Map(320, 9, 32, 73, 32, 13);
    Entities.push_back(map91);
    Map* map92 = new Map(352, 9, 32, 73, 32, 13);
    Entities.push_back(map92);
    Map* map93 = new Map(384, 9, 32, 73, 32, 13);
    Entities.push_back(map93);
    Map* map94 = new Map(416, 9, 32, 73, 32, 13);
    Entities.push_back(map94);
    Map* map95 = new Map(448, 9, 32, 73, 32, 13);
    Entities.push_back(map95);
    Map* map96 = new Map(480, 9, 32, 73, 32, 13);
    Entities.push_back(map96);
    Map* map97 = new Map(512, 9, 32, 73, 32, 13);
    Entities.push_back(map97);
    Map* map98 = new Map(544, 9, 32, 73, 32, 13);
    Entities.push_back(map98);
    Map* map99 = new Map(0, 361, 32, 73, 32, 13);
    Entities.push_back(map99);
    Map* map100 = new Map(32, 361, 32, 73, 32, 13);
    Entities.push_back(map100);
    Map* map101 = new Map(64, 361, 32, 73, 32, 13);
    Entities.push_back(map101);
    Map* map102 = new Map(512, 361, 32, 73, 32, 13);
    Entities.push_back(map102);
    Map* map103 = new Map(544, 361, 32, 73, 32, 13);
    Entities.push_back(map103);
    Map* map104 = new Map(576, 361, 32, 73, 32, 13);
    Entities.push_back(map104);
    Map* map105 = new Map(192, 77, 64, 77, 32, 4);
    Entities.push_back(map105);
    Map* map106 = new Map(384, 77, 64, 77, 32, 4);
    Entities.push_back(map106);
    Map* map107 = new Map(192, 111, 96, 79, 32, 4);
    Entities.push_back(map107);
    Map* map108 = new Map(384, 111, 96, 79, 32, 4);
    Entities.push_back(map108);
    Map* map109 = new Map(233, 320, 137, 64, 13, 32);
    Entities.push_back(map109);
    Map* map110 = new Map(100, 512, 196, 64, 23, 32);
    Entities.push_back(map110);
    Map* map111 = new Map(164, 192, 196, 64, 23, 32);
    Entities.push_back(map111);
    Map* map112 = new Map(164, 256, 196, 64, 23, 32);
    Entities.push_back(map112);
    Map* map113 = new Map(164, 384, 196, 64, 23, 32);
    Entities.push_back(map113);
    Map* map114 = new Map(164, 576, 196, 64, 23, 32);
    Entities.push_back(map114);
    Map* map115 = new Map(292, 32, 196, 64, 23, 32);
    Entities.push_back(map115);
    Map* map116 = new Map(292, 64, 196, 64, 23, 32);
    Entities.push_back(map116);
    Map* map117 = new Map(292, 192, 196, 64, 23, 32);
    Entities.push_back(map117);
    Map* map118 = new Map(292, 448, 196, 64, 23, 32);
    Entities.push_back(map118);
    Map* map119 = new Map(292, 576, 196, 64, 23, 32);
    Entities.push_back(map119);
    Map* map120 = new Map(420, 192, 196, 64, 23, 32);
    Entities.push_back(map120);
    Map* map121 = new Map(420, 256, 196, 64, 23, 32);
    Entities.push_back(map121);
    Map* map122 = new Map(420, 384, 196, 64, 23, 32);
    Entities.push_back(map122);
    Map* map123 = new Map(420, 576, 196, 64, 23, 32);
    Entities.push_back(map123);
    Map* map124 = new Map(484, 512, 196, 64, 23, 32);
    Entities.push_back(map124);
    Map* map125 = new Map(256, 165, 224, 69, 32, 22);
    Entities.push_back(map125);
    Map* map126 = new Map(320, 165, 224, 69, 32, 22);
    Entities.push_back(map126);
    Map* map127 = new Map(192, 229, 224, 69, 32, 22);
    Entities.push_back(map127);
    Map* map128 = new Map(384, 229, 224, 69, 32, 22);
    Entities.push_back(map128);
    Map* map129 = new Map(256, 421, 224, 69, 32, 22);
    Entities.push_back(map129);
    Map* map130 = new Map(320, 421, 224, 69, 32, 22);
    Entities.push_back(map130);
    Map* map131 = new Map(192, 485, 224, 69, 32, 22);
    Entities.push_back(map131);
    Map* map132 = new Map(384, 485, 224, 69, 32, 22);
    Entities.push_back(map132);
    Map* map133 = new Map(256, 549, 224, 69, 32, 22);
    Entities.push_back(map133);
    Map* map134 = new Map(320, 549, 224, 69, 32, 22);
    Entities.push_back(map134);
    Map* map135 = new Map(96, 613, 224, 69, 32, 22);
    Entities.push_back(map135);
    Map* map136 = new Map(128, 613, 224, 69, 32, 22);
    Entities.push_back(map136);
    Map* map137 = new Map(192, 613, 224, 69, 32, 22);
    Entities.push_back(map137);
    Map* map138 = new Map(384, 613, 224, 69, 32, 22);
    Entities.push_back(map138);
    Map* map139 = new Map(448, 613, 224, 69, 32, 22);
    Entities.push_back(map139);
    Map* map140 = new Map(480, 613, 224, 69, 32, 22);
    Entities.push_back(map140);
    Map* map141 = new Map(9, 544, 265, 64, 23, 32);
    Entities.push_back(map141);
    Map* map142 = new Map(576, 544, 288, 64, 23, 32);
    Entities.push_back(map142);
    Map* map143 = new Map(288, 302,320, 78, 32, 5);
    Entities.push_back(map143);
    Map* map144 = new Map(32, 234, 0, 106, 32, 13);
    Entities.push_back(map144);
    Map* map145 = new Map(64, 234, 0, 106, 32, 13);
    Entities.push_back(map145);
    Map* map146 = new Map(512, 234, 0, 106, 32, 13);
    Entities.push_back(map146);
    Map* map147 = new Map(544, 234, 0, 106, 32, 13);
    Entities.push_back(map147);
    Map* map148 = new Map(0 , 298, 0, 106, 32, 13);
    Entities.push_back(map148);
    Map* map149 = new Map(32, 298, 0, 106, 32, 13);
    Entities.push_back(map149);
    Map* map150 = new Map(64, 298, 0, 106, 32, 13);
    Entities.push_back(map150);
    Map* map151 = new Map(512, 298, 0, 106, 32, 13);
    Entities.push_back(map151);
    Map* map152 = new Map(544, 298, 0, 106, 32, 13);
    Entities.push_back(map152);
    Map* map153 = new Map(576, 298, 0, 106, 32, 13);
    Entities.push_back(map153);
    Map* map154 = new Map(32, 426, 0, 106, 32, 13);
    Entities.push_back(map154);
    Map* map155 = new Map(64, 426, 0, 106, 32, 13);
    Entities.push_back(map155);
    Map* map156 = new Map(512, 426, 0, 106, 32, 13);
    Entities.push_back(map156);
    Map* map157 = new Map(544, 426, 0, 106, 32, 13);
    Entities.push_back(map157);
    Map* map158 = new Map(32, 682, 0, 106, 32, 13);
    Entities.push_back(map158);
    Map* map159 = new Map(64, 682, 0, 106, 32, 13);
    Entities.push_back(map159);
    Map* map160 = new Map(96, 682, 0, 106, 32, 13);
    Entities.push_back(map160);
    Map* map161 = new Map(128, 682, 0, 106, 32, 13);
    Entities.push_back(map161);
    Map* map162 = new Map(160, 682, 0, 106, 32, 13);
    Entities.push_back(map162);
    Map* map163 = new Map(192, 682, 0, 106, 32, 13);
    Entities.push_back(map163);
    Map* map164 = new Map(224, 682, 0, 106, 32, 13);
    Entities.push_back(map164);
    Map* map165 = new Map(256, 682, 0, 106, 32, 13);
    Entities.push_back(map165);
    Map* map166 = new Map(288, 682, 0, 106, 32, 13);
    Entities.push_back(map166);
    Map* map167 = new Map(320, 682, 0, 106, 32, 13);
    Entities.push_back(map167);
    Map* map168 = new Map(352, 682, 0, 106, 32, 13);
    Entities.push_back(map168);
    Map* map169 = new Map(384, 682, 0, 106, 32, 13);
    Entities.push_back(map169);
    Map* map170 = new Map(416, 682, 0, 106, 32, 13);
    Entities.push_back(map170);
    Map* map171 = new Map(448, 682, 0, 106, 32, 13);
    Entities.push_back(map171);
    Map* map172 = new Map(480, 682, 0, 106, 32, 13);
    Entities.push_back(map172);
    Map* map173 = new Map(512, 682, 0, 106, 32, 13);
    Entities.push_back(map173);
    Map* map174 = new Map(544, 682, 0, 106, 32, 13);
    Entities.push_back(map174);
    Map* map175 = new Map(106, 256, 42, 96, 13, 32);
    Entities.push_back(map175);
    Map* map176 = new Map(106, 384, 42, 96, 13, 32);
    Entities.push_back(map176);
    Map* map177 = new Map(586, 32, 42, 96, 13, 32);
    Entities.push_back(map177);
    Map* map178 = new Map(586, 64, 42, 96, 13, 32);
    Entities.push_back(map178);
    Map* map179 = new Map(586, 96, 42, 96, 13, 32);
    Entities.push_back(map179);
    Map* map180 = new Map(586, 128, 42, 96, 13, 32);
    Entities.push_back(map180);
    Map* map181 = new Map(586, 160, 42, 96, 13, 32);
    Entities.push_back(map181);
    Map* map182 = new Map(586, 192, 42, 96, 13, 32);
    Entities.push_back(map182);
    Map* map183 = new Map(586, 448, 42, 96, 13, 32);
    Entities.push_back(map183);
    Map* map184 = new Map(586, 480, 42, 96, 13, 32);
    Entities.push_back(map184);
    Map* map185 = new Map(586, 512, 42, 96, 13, 32);
    Entities.push_back(map185);
    Map* map186 = new Map(586, 576, 42, 96, 13, 32);
    Entities.push_back(map186);
    Map* map187 = new Map(586, 608, 42, 96, 13, 32);
    Entities.push_back(map187);
    Map* map188 = new Map(586, 640, 42, 96, 13, 32);
    Entities.push_back(map188);
    Map* map189 = new Map(256, 298, 64, 106, 32, 13);
    Entities.push_back(map189);
    Map* map190 = new Map(320, 298, 96, 106, 32, 13);
    Entities.push_back(map190);
    Map* map191 = new Map(256, 361, 128, 105, 32, 13);
    Entities.push_back(map191);
    Map* map192 = new Map(288, 361, 128, 105, 32, 13);
    Entities.push_back(map192);
    Map* map193 = new Map(320, 361, 128, 105, 32, 13);
    Entities.push_back(map193);
    Map* map194 = new Map(362, 320, 170, 96, 13, 32);
    Entities.push_back(map194);
    Map* map195 = new Map(484, 485, 196, 101, 28, 27);
    Entities.push_back(map195);
    Map* map196 = new Map(96, 485, 224, 101, 27, 27);
    Entities.push_back(map196);
    Map* map197 = new Map(32, 549, 256, 101, 25, 22);
    Entities.push_back(map197);
    Map* map198 = new Map(224, 229, 256, 101, 25, 22);
    Entities.push_back(map198);
    Map* map199 = new Map(224, 613, 256, 101, 25, 22);
    Entities.push_back(map199);
    Map* map200 = new Map(352, 165, 256, 101, 25, 22);
    Entities.push_back(map200);
    Map* map201 = new Map(352, 421, 256, 101, 25, 22);
    Entities.push_back(map201);
    Map* map202 = new Map(352, 549, 256, 101, 25, 22);
    Entities.push_back(map202);
    Map* map203 = new Map(512, 485, 256, 101, 25, 22);
    Entities.push_back(map203);
    Map* map204 = new Map(512, 613, 256, 101, 25, 22);
    Entities.push_back(map204);
    Map* map205 = new Map(71, 485, 295, 101, 25, 22);
    Entities.push_back(map205);
    Map* map206 = new Map(71, 613, 295, 101, 25, 22);
    Entities.push_back(map206);
    Map* map207 = new Map(231, 165, 295, 101, 25, 22);
    Entities.push_back(map207);
    Map* map208 = new Map(231, 421, 295, 101, 25, 22);
    Entities.push_back(map208);
    Map* map209 = new Map(231, 549, 295, 101, 25, 22);
    Entities.push_back(map209);
    Map* map210 = new Map(359, 229, 295, 101, 25, 22);
    Entities.push_back(map210);
    Map* map211 = new Map(359, 613, 295, 101, 25, 22);
    Entities.push_back(map211);
    Map* map212 = new Map(551, 549, 295, 101, 25, 22);
    Entities.push_back(map212);
    Item* Dot1 = Factory.Create("Dot", 46, 46, 14, 14, 3, 3);
    Entities.push_back(Dot1);
    Item* Dot2 = Factory.Create("Dot", 78, 46, 14, 14, 3, 3);
    Entities.push_back(Dot2);
    Item* Dot3 = Factory.Create("Dot", 110, 46, 14, 14, 3, 3);
    Entities.push_back(Dot3);
    Item* Dot4 = Factory.Create("Dot", 142, 46, 14, 14, 3, 3);
    Entities.push_back(Dot4);
    Item* Dot5 = Factory.Create("Dot", 174, 46, 14, 14, 3, 3);
    Entities.push_back(Dot5);
    Item* Dot6 = Factory.Create("Dot", 206, 46, 14, 14, 3, 3);
    Entities.push_back(Dot6);
    Item* Dot7 = Factory.Create("Dot", 238, 46, 14, 14, 3, 3);
    Entities.push_back(Dot7);
    Item* Dot8 = Factory.Create("Dot", 270, 46, 14, 14, 3, 3);
    Entities.push_back(Dot8);
    Item* Dot9 = Factory.Create("Dot", 334, 46, 14, 14, 3, 3);
    Entities.push_back(Dot9);
    Item* Dot10 = Factory.Create("Dot", 366, 46, 14, 14, 3, 3);
    Entities.push_back(Dot10);
    Item* Dot11 = Factory.Create("Dot", 398, 46, 14, 14, 3, 3);
    Entities.push_back(Dot11);
    Item* Dot12 = Factory.Create("Dot", 430, 46, 14, 14, 3, 3);
    Entities.push_back(Dot12);
    Item* Dot13 = Factory.Create("Dot", 462, 46, 14, 14, 3, 3);
    Entities.push_back(Dot13);
    Item* Dot14 = Factory.Create("Dot", 494, 46, 14, 14, 3, 3);
    Entities.push_back(Dot14);
    Item* Dot15 = Factory.Create("Dot", 526, 46, 14, 14, 3, 3);
    Entities.push_back(Dot15);
    Item* Dot16 = Factory.Create("Dot", 560, 46, 14, 14, 3, 3);
    Entities.push_back(Dot16);
    Item* Dot17 = Factory.Create("Dot", 46, 78, 14, 14, 3, 3);
    Entities.push_back(Dot17);
    Item* Dot18 = Factory.Create("Dot", 142, 78, 14, 14, 3, 3);
    Entities.push_back(Dot18);
    Item* Dot19 = Factory.Create("Dot", 270, 78, 14, 14, 3, 3);
    Entities.push_back(Dot19);
    Item* Dot20 = Factory.Create("Dot", 334, 78, 14, 14, 3, 3);
    Entities.push_back(Dot20);
    Item* Dot21 = Factory.Create("Dot", 462, 78, 14, 14, 3, 3);
    Entities.push_back(Dot21);
    Item* Dot22 = Factory.Create("Dot", 560, 78, 14, 14, 3, 3);
    Entities.push_back(Dot22);
    Item* Dot23 = Factory.Create("Dot", 142, 110, 14, 14, 3, 3);
    Entities.push_back(Dot23);
    Item* Dot24 = Factory.Create("Dot", 270, 110, 14, 14, 3, 3);
    Entities.push_back(Dot24);
    Item* Dot25 = Factory.Create("Dot", 334, 110, 14, 14, 3, 3);
    Entities.push_back(Dot25);
    Item* Dot26 = Factory.Create("Dot", 462, 110, 14, 14, 3, 3);
    Entities.push_back(Dot26);
    Item* Dot27 = Factory.Create("Dot", 46, 142, 14, 14, 3, 3);
    Entities.push_back(Dot27);
    Item* Dot28 = Factory.Create("Dot", 78, 142, 14, 14, 3, 3);
    Entities.push_back(Dot28);
    Item* Dot29 = Factory.Create("Dot", 110, 142, 14, 14, 3, 3);
    Entities.push_back(Dot29);
    Item* Dot30 = Factory.Create("Dot", 142, 142, 14, 14, 3, 3);
    Entities.push_back(Dot30);
    Item* Dot31 = Factory.Create("Dot", 174, 142, 14, 14, 3, 3);
    Entities.push_back(Dot31);
    Item* Dot32 = Factory.Create("Dot", 206, 142, 14, 14, 3, 3);
    Entities.push_back(Dot32);
    Item* Dot33 = Factory.Create("Dot", 238, 142, 14, 14, 3, 3);
    Entities.push_back(Dot33);
    Item* Dot34 = Factory.Create("Dot", 270, 142, 14, 14, 3, 3);
    Entities.push_back(Dot34);
    Item* Dot35 = Factory.Create("Dot", 302, 142, 14, 14, 3, 3);
    Entities.push_back(Dot35);
    Item* Dot36 = Factory.Create("Dot", 334, 142, 14, 14, 3, 3);
    Entities.push_back(Dot36);
    Item* Dot37 = Factory.Create("Dot", 366, 142, 14, 14, 3, 3);
    Entities.push_back(Dot37);
    Item* Dot38 = Factory.Create("Dot", 398, 142, 14, 14, 3, 3);
    Entities.push_back(Dot38);
    Item* Dot39 = Factory.Create("Dot", 430, 142, 14, 14, 3, 3);
    Entities.push_back(Dot39);
    Item* Dot40 = Factory.Create("Dot", 462, 142, 14, 14, 3, 3);
    Entities.push_back(Dot40);
    Item* Dot41 = Factory.Create("Dot", 494, 142, 14, 14, 3, 3);
    Entities.push_back(Dot41);
    Item* Dot42 = Factory.Create("Dot", 526, 142, 14, 14, 3, 3);
    Entities.push_back(Dot42);
    Item* Dot43 = Factory.Create("Dot", 560, 142, 14, 14, 3, 3);
    Entities.push_back(Dot43);
    Item* Dot44 = Factory.Create("Dot", 46, 174, 14, 14, 3, 3);
    Entities.push_back(Dot44);
    Item* Dot45 = Factory.Create("Dot", 142, 174, 14, 14, 3, 3);
    Entities.push_back(Dot45);
    Item* Dot46 = Factory.Create("Dot", 206, 174, 14, 14, 3, 3);
    Entities.push_back(Dot46);
    Item* Dot47 = Factory.Create("Dot", 398, 174, 14, 14, 3, 3);
    Entities.push_back(Dot47);
    Item* Dot48 = Factory.Create("Dot", 462, 174, 14, 14, 3, 3);
    Entities.push_back(Dot48);
    Item* Dot49 = Factory.Create("Dot", 560, 174, 14, 14, 3, 3);
    Entities.push_back(Dot49);
    Item* Dot50 = Factory.Create("Dot", 46, 206, 14, 14, 3, 3);
    Entities.push_back(Dot50);
    Item* Dot51 = Factory.Create("Dot", 78, 206, 14, 14, 3, 3);
    Entities.push_back(Dot51);
    Item* Dot52 = Factory.Create("Dot", 110, 206, 14, 14, 3, 3);
    Entities.push_back(Dot52);
    Item* Dot53 = Factory.Create("Dot", 142, 206, 14, 14, 3, 3);
    Entities.push_back(Dot53);
    Item* Dot54 = Factory.Create("Dot", 206, 206, 14, 14, 3, 3);
    Entities.push_back(Dot54);
    Item* Dot55 = Factory.Create("Dot", 238, 206, 14, 14, 3, 3);
    Entities.push_back(Dot55);
    Item* Dot56 = Factory.Create("Dot", 270, 206, 14, 14, 3, 3);
    Entities.push_back(Dot56);
    Item* Dot57 = Factory.Create("Dot", 334, 206, 14, 14, 3, 3);
    Entities.push_back(Dot57);
    Item* Dot58 = Factory.Create("Dot", 366, 206, 14, 14, 3, 3);
    Entities.push_back(Dot58);
    Item* Dot59 = Factory.Create("Dot", 398, 206, 14, 14, 3, 3);
    Entities.push_back(Dot59);
    Item* Dot60 = Factory.Create("Dot", 462, 206, 14, 14, 3, 3);
    Entities.push_back(Dot60);
    Item* Dot61 = Factory.Create("Dot", 494, 206, 14, 14, 3, 3);
    Entities.push_back(Dot61);
    Item* Dot62 = Factory.Create("Dot", 526, 206, 14, 14, 3, 3);
    Entities.push_back(Dot62);
    Item* Dot63 = Factory.Create("Dot", 560, 206, 14, 14, 3, 3);
    Entities.push_back(Dot63);
    Item* Dot64 = Factory.Create("Dot", 142, 238, 14, 14, 3, 3);
    Entities.push_back(Dot64);
    Item* Dot65 = Factory.Create("Dot", 462, 238, 14, 14, 3, 3);
    Entities.push_back(Dot65);
    Item* Dot66 = Factory.Create("Dot", 142, 270, 14, 14, 3, 3);
    Entities.push_back(Dot66);
    Item* Dot67 = Factory.Create("Dot", 462, 270, 14, 14, 3, 3);
    Entities.push_back(Dot67);
    Item* Dot68 = Factory.Create("Dot", 142, 302, 14, 14, 3, 3);
    Entities.push_back(Dot68);
    Item* Dot69 = Factory.Create("Dot", 462, 302, 14, 14, 3, 3);
    Entities.push_back(Dot69);
    Item* Dot70 = Factory.Create("Dot", 142, 334, 14, 14, 3, 3);
    Entities.push_back(Dot70);
    Item* Dot71 = Factory.Create("Dot", 462, 334, 14, 14, 3, 3);
    Entities.push_back(Dot71);
    Item* Dot72 = Factory.Create("Dot", 142, 366, 14, 14, 3, 3);
    Entities.push_back(Dot72);
    Item* Dot73 = Factory.Create("Dot", 462, 366, 14, 14, 3, 3);
    Entities.push_back(Dot73);
    Item* Dot74 = Factory.Create("Dot", 142, 398, 14, 14, 3, 3);
    Entities.push_back(Dot74);
    Item* Dot75 = Factory.Create("Dot", 462, 398, 14, 14, 3, 3);
    Entities.push_back(Dot75);
    Item* Dot76 = Factory.Create("Dot", 142, 430, 14, 14, 3, 3);
    Entities.push_back(Dot76);
    Item* Dot77 = Factory.Create("Dot", 462, 430, 14, 14, 3, 3);
    Entities.push_back(Dot77);
    Item* Dot78 = Factory.Create("Dot", 46, 462, 14, 14, 3, 3);
    Entities.push_back(Dot78);
    Item* Dot79 = Factory.Create("Dot", 78, 462, 14, 14, 3, 3);
    Entities.push_back(Dot79);
    Item* Dot80 = Factory.Create("Dot", 110, 462, 14, 14, 3, 3);
    Entities.push_back(Dot80);
    Item* Dot81 = Factory.Create("Dot", 142, 462, 14, 14, 3, 3);
    Entities.push_back(Dot81);
    Item* Dot82 = Factory.Create("Dot", 174, 462, 14, 14, 3, 3);
    Entities.push_back(Dot82);
    Item* Dot83 = Factory.Create("Dot", 206, 462, 14, 14, 3, 3);
    Entities.push_back(Dot83);
    Item* Dot84 = Factory.Create("Dot", 238, 462, 14, 14, 3, 3);
    Entities.push_back(Dot84);
    Item* Dot85 = Factory.Create("Dot", 270, 462, 14, 14, 3, 3);
    Entities.push_back(Dot85);
    Item* Dot86 = Factory.Create("Dot", 334, 462, 14, 14, 3, 3);
    Entities.push_back(Dot86);
    Item* Dot87 = Factory.Create("Dot", 366, 462, 14, 14, 3, 3);
    Entities.push_back(Dot87);
    Item* Dot88 = Factory.Create("Dot", 398, 462, 14, 14, 3, 3);
    Entities.push_back(Dot88);
    Item* Dot89 = Factory.Create("Dot", 430, 462, 14, 14, 3, 3);
    Entities.push_back(Dot89);
    Item* Dot90 = Factory.Create("Dot", 462, 462, 14, 14, 3, 3);
    Entities.push_back(Dot90);
    Item* Dot91 = Factory.Create("Dot", 494, 462, 14, 14, 3, 3);
    Entities.push_back(Dot91);
    Item* Dot92 = Factory.Create("Dot", 526, 462, 14, 14, 3, 3);
    Entities.push_back(Dot92);
    Item* Dot93 = Factory.Create("Dot", 560, 462, 14, 14, 3, 3);
    Entities.push_back(Dot93);
    Item* Dot94 = Factory.Create("Dot", 46, 494, 14, 14, 3, 3);
    Entities.push_back(Dot94);
    Item* Dot95 = Factory.Create("Dot", 142, 494, 14, 14, 3, 3);
    Entities.push_back(Dot95);
    Item* Dot96 = Factory.Create("Dot", 270, 494, 14, 14, 3, 3);
    Entities.push_back(Dot96);
    Item* Dot97 = Factory.Create("Dot", 334, 494, 14, 14, 3, 3);
    Entities.push_back(Dot97);
    Item* Dot98 = Factory.Create("Dot", 462, 494, 14, 14, 3, 3);
    Entities.push_back(Dot98);
    Item* Dot99 = Factory.Create("Dot", 560, 494, 14, 14, 3, 3);
    Entities.push_back(Dot99);
    Item* Dot100 = Factory.Create("Dot", 78, 526, 14, 14, 3, 3);
    Entities.push_back(Dot100);
    Item* Dot101 = Factory.Create("Dot", 142, 526, 14, 14, 3, 3);
    Entities.push_back(Dot101);
    Item* Dot102 = Factory.Create("Dot", 174, 526, 14, 14, 3, 3);
    Entities.push_back(Dot102);
    Item* Dot103 = Factory.Create("Dot", 206, 526, 14, 14, 3, 3);
    Entities.push_back(Dot103);
    Item* Dot104 = Factory.Create("Dot", 238, 526, 14, 14, 3, 3);
    Entities.push_back(Dot104);
    Item* Dot105 = Factory.Create("Dot", 270, 526, 14, 14, 3, 3);
    Entities.push_back(Dot105);
    Item* Dot106 = Factory.Create("Dot", 334, 526, 14, 14, 3, 3);
    Entities.push_back(Dot106);
    Item* Dot107 = Factory.Create("Dot", 366, 526, 14, 14, 3, 3);
    Entities.push_back(Dot107);
    Item* Dot108 = Factory.Create("Dot", 398, 526, 14, 14, 3, 3);
    Entities.push_back(Dot108);
    Item* Dot109 = Factory.Create("Dot", 430, 526, 14, 14, 3, 3);
    Entities.push_back(Dot109);
    Item* Dot110 = Factory.Create("Dot", 462, 526, 14, 14, 3, 3);
    Entities.push_back(Dot110);
    Item* Dot111 = Factory.Create("Dot", 526, 526, 14, 14, 3, 3);
    Entities.push_back(Dot111);
    Item* Dot112 = Factory.Create("Dot", 78, 560, 14, 14, 3, 3);
    Entities.push_back(Dot112);
    Item* Dot113 = Factory.Create("Dot", 142, 560, 14, 14, 3, 3);
    Entities.push_back(Dot113);
    Item* Dot114 = Factory.Create("Dot", 206, 560, 14, 14, 3, 3);
    Entities.push_back(Dot114);
    Item* Dot115 = Factory.Create("Dot", 398, 560, 14, 14, 3, 3);
    Entities.push_back(Dot115);
    Item* Dot116 = Factory.Create("Dot", 462, 560, 14, 14, 3, 3);
    Entities.push_back(Dot116);
    Item* Dot117 = Factory.Create("Dot", 526, 560, 14, 14, 3, 3);
    Entities.push_back(Dot117);
    Item* Dot118 = Factory.Create("Dot", 46, 590, 14, 14, 3, 3);
    Entities.push_back(Dot118);
    Item* Dot119 = Factory.Create("Dot", 78, 590, 14, 14, 3, 3);
    Entities.push_back(Dot119);
    Item* Dot120 = Factory.Create("Dot", 110, 590, 14, 14, 3, 3);
    Entities.push_back(Dot120);
    Item* Dot121 = Factory.Create("Dot", 142, 590, 14, 14, 3, 3);
    Entities.push_back(Dot121);
    Item* Dot122 = Factory.Create("Dot", 206, 590, 14, 14, 3, 3);
    Entities.push_back(Dot122);
    Item* Dot123 = Factory.Create("Dot", 238, 590, 14, 14, 3, 3);
    Entities.push_back(Dot123);
    Item* Dot124 = Factory.Create("Dot", 270, 590, 14, 14, 3, 3);
    Entities.push_back(Dot124);
    Item* Dot125 = Factory.Create("Dot", 334, 590, 14, 14, 3, 3);
    Entities.push_back(Dot125);
    Item* Dot126 = Factory.Create("Dot", 366, 590, 14, 14, 3, 3);
    Entities.push_back(Dot126);
    Item* Dot127 = Factory.Create("Dot", 398, 590, 14, 14, 3, 3);
    Entities.push_back(Dot127);
    Item* Dot128 = Factory.Create("Dot", 462, 590, 14, 14, 3, 3);
    Entities.push_back(Dot128);
    Item* Dot129 = Factory.Create("Dot", 494, 590, 14, 14, 3, 3);
    Entities.push_back(Dot129);
    Item* Dot130 = Factory.Create("Dot", 526, 590, 14, 14, 3, 3);
    Entities.push_back(Dot130);
    Item* Dot131 = Factory.Create("Dot", 560, 590, 14, 14, 3, 3);
    Entities.push_back(Dot131);
    Item* Dot132 = Factory.Create("Dot", 46, 622, 14, 14, 3, 3);
    Entities.push_back(Dot132);
    Item* Dot133 = Factory.Create("Dot", 270, 622, 14, 14, 3, 3);
    Entities.push_back(Dot133);
    Item* Dot134 = Factory.Create("Dot", 334, 622, 14, 14, 3, 3);
    Entities.push_back(Dot134);
    Item* Dot135 = Factory.Create("Dot", 560, 622, 14, 14, 3, 3);
    Entities.push_back(Dot135);
    Item* Dot136 = Factory.Create("Dot", 46, 654, 14, 14, 3, 3);
    Entities.push_back(Dot136);
    Item* Dot137 = Factory.Create("Dot", 78, 654, 14, 14, 3, 3);
    Entities.push_back(Dot137);
    Item* Dot138 = Factory.Create("Dot", 110, 654, 14, 14, 3, 3);
    Entities.push_back(Dot138);
    Item* Dot139 = Factory.Create("Dot", 142, 654, 14, 14, 3, 3);
    Entities.push_back(Dot139);
    Item* Dot140 = Factory.Create("Dot", 174, 654, 14, 14, 3, 3);
    Entities.push_back(Dot140);
    Item* Dot141 = Factory.Create("Dot", 206, 654, 14, 14, 3, 3);
    Entities.push_back(Dot141);
    Item* Dot142 = Factory.Create("Dot", 238, 654, 14, 14, 3, 3);
    Entities.push_back(Dot142);
    Item* Dot143 = Factory.Create("Dot", 270, 654, 14, 14, 3, 3);
    Entities.push_back(Dot143);
    Item* Dot144 = Factory.Create("Dot", 302, 654, 14, 14, 3, 3);
    Entities.push_back(Dot144);
    Item* Dot145 = Factory.Create("Dot", 334, 654, 14, 14, 3, 3);
    Entities.push_back(Dot145);
    Item* Dot146 = Factory.Create("Dot", 366, 654, 14, 14, 3, 3);
    Entities.push_back(Dot146);
    Item* Dot147 = Factory.Create("Dot", 398, 654, 14, 14, 3, 3);
    Entities.push_back(Dot147);
    Item* Dot148 = Factory.Create("Dot", 430, 654, 14, 14, 3, 3);
    Entities.push_back(Dot148);
    Item* Dot149 = Factory.Create("Dot", 462, 654, 14, 14, 3, 3);
    Entities.push_back(Dot149);
    Item* Dot150 = Factory.Create("Dot", 494, 654, 14, 14, 3, 3);
    Entities.push_back(Dot150);
    Item* Dot151 = Factory.Create("Dot", 526, 654, 14, 14, 3, 3);
    Entities.push_back(Dot151);
    Item* Dot152 = Factory.Create("Dot", 560, 654, 14, 14, 3, 3);
    Entities.push_back(Dot152);
    Item* Bonus1 = Factory.Create("Bonus", 42, 106, 10, 10, 12, 12);
    Entities.push_back(Bonus1);
    Item* Bonus2 = Factory.Create("Bonus", 554, 106, 10, 10, 12, 12);
    Entities.push_back(Bonus2);
    Item* Bonus3 = Factory.Create("Bonus", 42, 522, 10, 10, 12, 12);
    Entities.push_back(Bonus3);
    Item* Bonus4 = Factory.Create("Bonus", 554, 522, 10, 10, 12, 12);
    Entities.push_back(Bonus4);
}

void Scene::initTile() {
    // on initialise les tuiles
    tiles[0].nb_tile = 0;
    tiles[0].x = 32;
    tiles[0].y = 32;
    tiles[0].up_tile = -1;
    tiles[0].down_tile = 16;
    tiles[0].left_tile = -1;
    tiles[0].right_tile = 1;

    tiles[1].nb_tile = 1;
    tiles[1].x = 64;
    tiles[1].y = 32;
    tiles[1].up_tile = -1;
    tiles[1].down_tile = -1;
    tiles[1].left_tile = 0;
    tiles[1].right_tile = 2;

    tiles[2].nb_tile = 2;
    tiles[2].x = 96;
    tiles[2].y = 32;
    tiles[2].up_tile = -1;
    tiles[2].down_tile = -1;
    tiles[2].left_tile = 1;
    tiles[2].right_tile = 3;

    tiles[3].nb_tile = 3;
    tiles[3].x = 128;
    tiles[3].y = 32;
    tiles[3].up_tile = -1;
    tiles[3].down_tile = 17;
    tiles[3].left_tile = 2;
    tiles[3].right_tile = 4;

    tiles[4].nb_tile = 4;
    tiles[4].x = 160;
    tiles[4].y = 32;
    tiles[4].up_tile = -1;
    tiles[4].down_tile = -1;
    tiles[4].left_tile = 3;
    tiles[4].right_tile = 5;

    tiles[5].nb_tile = 5;
    tiles[5].x = 192;
    tiles[5].y = 32;
    tiles[5].up_tile = -1;
    tiles[5].down_tile = -1;
    tiles[5].left_tile = 4;
    tiles[5].right_tile = 6;

    tiles[6].nb_tile = 6;
    tiles[6].x = 224;
    tiles[6].y = 32;
    tiles[6].up_tile = -1;
    tiles[6].down_tile = -1;
    tiles[6].left_tile = 5;
    tiles[6].right_tile = 7;

    tiles[7].nb_tile = 7;
    tiles[7].x = 256;
    tiles[7].y = 32;
    tiles[7].up_tile = -1;
    tiles[7].down_tile = 18;
    tiles[7].left_tile = 6;
    tiles[7].right_tile = -1;

    tiles[8].nb_tile = 8;
    tiles[8].x = 320;
    tiles[8].y = 32;
    tiles[8].up_tile = -1;
    tiles[8].down_tile = 19;
    tiles[8].left_tile = -1;
    tiles[8].right_tile = 9;

    tiles[9].nb_tile = 9;
    tiles[9].x = 352;
    tiles[9].y = 32;
    tiles[9].up_tile = -1;
    tiles[9].down_tile = -1;
    tiles[9].left_tile = 8;
    tiles[9].right_tile = 10;

    tiles[10].nb_tile = 10;
    tiles[10].x = 384;
    tiles[10].y = 32;
    tiles[10].up_tile = -1;
    tiles[10].down_tile = -1;
    tiles[10].left_tile = 9;
    tiles[10].right_tile = 11;

    tiles[11].nb_tile = 11;
    tiles[11].x = 416;
    tiles[11].y = 32;
    tiles[11].up_tile = -1;
    tiles[11].down_tile = -1;
    tiles[11].left_tile = 10;
    tiles[11].right_tile = 12;

    tiles[12].nb_tile = 12;
    tiles[12].x = 448;
    tiles[12].y = 32;
    tiles[12].up_tile = -1;
    tiles[12].down_tile = 20;
    tiles[12].left_tile = 11;
    tiles[12].right_tile = 13;

    tiles[13].nb_tile = 13;
    tiles[13].x = 480;
    tiles[13].y = 32;
    tiles[13].up_tile = -1;
    tiles[13].down_tile = -1;
    tiles[13].left_tile = 12;
    tiles[13].right_tile = 14;

    tiles[14].nb_tile = 14;
    tiles[14].x = 512;
    tiles[14].y = 32;
    tiles[14].up_tile = -1;
    tiles[14].down_tile = -1;
    tiles[14].left_tile = 13;
    tiles[14].right_tile = 15;

    tiles[15].nb_tile = 15;
    tiles[15].x = 544;
    tiles[15].y = 32;
    tiles[15].up_tile = -1;
    tiles[15].down_tile = 21;
    tiles[15].left_tile = 14;
    tiles[15].right_tile = -1;

    tiles[16].nb_tile = 16;
    tiles[16].x = 32;
    tiles[16].y = 64;
    tiles[16].up_tile = 0;
    tiles[16].down_tile = 22;
    tiles[16].left_tile = -1;
    tiles[16].right_tile = -1;

    tiles[17].nb_tile = 17;
    tiles[17].x = 128;
    tiles[17].y = 64;
    tiles[17].up_tile = 3;
    tiles[17].down_tile = 23;
    tiles[17].left_tile = -1;
    tiles[17].right_tile = -1;

    tiles[18].nb_tile = 18;
    tiles[18].x = 256;
    tiles[18].y = 64;
    tiles[18].up_tile = 7;
    tiles[18].down_tile = 24;
    tiles[18].left_tile = -1;
    tiles[18].right_tile = -1;

    tiles[19].nb_tile = 19;
    tiles[19].x = 320;
    tiles[19].y = 64;
    tiles[19].up_tile = 8;
    tiles[19].down_tile = 25;
    tiles[19].left_tile = -1;
    tiles[19].right_tile = -1;

    tiles[20].nb_tile = 20;
    tiles[20].x = 448;
    tiles[20].y = 64;
    tiles[20].up_tile = 12;
    tiles[20].down_tile = 26;
    tiles[20].left_tile = -1;
    tiles[20].right_tile = -1;

    tiles[21].nb_tile = 21;
    tiles[21].x = 544;
    tiles[21].y = 64;
    tiles[21].up_tile = 15;
    tiles[21].down_tile = 27;
    tiles[21].left_tile = -1;
    tiles[21].right_tile = -1;

    tiles[22].nb_tile = 22;
    tiles[22].x = 32;
    tiles[22].y = 96;
    tiles[22].up_tile = 16;
    tiles[22].down_tile = 28;
    tiles[22].left_tile = -1;
    tiles[22].right_tile = -1;

    tiles[23].nb_tile = 23;
    tiles[23].x = 128;
    tiles[23].y = 96;
    tiles[23].up_tile = 17;
    tiles[23].down_tile = 31;
    tiles[23].left_tile = -1;
    tiles[23].right_tile = -1;

    tiles[24].nb_tile = 24;
    tiles[24].x = 256;
    tiles[24].y = 96;
    tiles[24].up_tile = 18;
    tiles[24].down_tile = 35;
    tiles[24].left_tile = -1;
    tiles[24].right_tile = -1;

    tiles[25].nb_tile = 25;
    tiles[25].x = 320;
    tiles[25].y = 96;
    tiles[25].up_tile = 19;
    tiles[25].down_tile = 37;
    tiles[25].left_tile = -1;
    tiles[25].right_tile = -1;

    tiles[26].nb_tile = 26;
    tiles[26].x = 448;
    tiles[26].y = 96;
    tiles[26].up_tile = 20;
    tiles[26].down_tile = 41;
    tiles[26].left_tile = -1;
    tiles[26].right_tile = -1;

    tiles[27].nb_tile = 27;
    tiles[27].x = 544;
    tiles[27].y = 96;
    tiles[27].up_tile = 21;
    tiles[27].down_tile = 44;
    tiles[27].left_tile = -1;
    tiles[27].right_tile = -1;

    tiles[28].nb_tile = 28;
    tiles[28].x = 32;
    tiles[28].y = 128;
    tiles[28].up_tile = 22;
    tiles[28].down_tile = 45;
    tiles[28].left_tile = -1;
    tiles[28].right_tile = 29;

    tiles[29].nb_tile = 29;
    tiles[29].x = 64;
    tiles[29].y = 128;
    tiles[29].up_tile = -1;
    tiles[29].down_tile = -1;
    tiles[29].left_tile = 28;
    tiles[29].right_tile = 30;

    tiles[30].nb_tile = 30;
    tiles[30].x = 96;
    tiles[30].y = 128;
    tiles[30].up_tile = -1;
    tiles[30].down_tile = -1;
    tiles[30].left_tile = 29;
    tiles[30].right_tile = 31;

    tiles[31].nb_tile = 31;
    tiles[31].x = 128;
    tiles[31].y = 128;
    tiles[31].up_tile = 23;
    tiles[31].down_tile = 46;
    tiles[31].left_tile = 30;
    tiles[31].right_tile = 32;

    tiles[32].nb_tile = 32;
    tiles[32].x = 160;
    tiles[32].y = 128;
    tiles[32].up_tile = -1;
    tiles[32].down_tile = -1;
    tiles[32].left_tile = 31;
    tiles[32].right_tile = 33;

    tiles[33].nb_tile = 33;
    tiles[33].x = 192;
    tiles[33].y = 128;
    tiles[33].up_tile = -1;
    tiles[33].down_tile = 47;
    tiles[33].left_tile = 32;
    tiles[33].right_tile = 34;

    tiles[34].nb_tile = 34;
    tiles[34].x = 224;
    tiles[34].y = 128;
    tiles[34].up_tile = -1;
    tiles[34].down_tile = -1;
    tiles[34].left_tile = 32;
    tiles[34].right_tile = 35;

    tiles[35].nb_tile = 35;
    tiles[35].x = 256;
    tiles[35].y = 128;
    tiles[35].up_tile = 24;
    tiles[35].down_tile = -1;
    tiles[35].left_tile = 34;
    tiles[35].right_tile = 36;

    tiles[36].nb_tile = 36;
    tiles[36].x = 288;
    tiles[36].y = 128;
    tiles[36].up_tile = -1;
    tiles[36].down_tile = -1;
    tiles[36].left_tile = 35;
    tiles[36].right_tile = 37;

    tiles[37].nb_tile = 37;
    tiles[37].x = 320;
    tiles[37].y = 128;
    tiles[37].up_tile = 25;
    tiles[37].down_tile = -1;
    tiles[37].left_tile = 36;
    tiles[37].right_tile = 38;

    tiles[38].nb_tile = 38;
    tiles[38].x = 352;
    tiles[38].y = 128;
    tiles[38].up_tile = -1;
    tiles[38].down_tile = -1;
    tiles[38].left_tile = 37;
    tiles[38].right_tile = 39;

    tiles[39].nb_tile = 39;
    tiles[39].x = 384;
    tiles[39].y = 128;
    tiles[39].up_tile = -1;
    tiles[39].down_tile = 48;
    tiles[39].left_tile = 38;
    tiles[39].right_tile = 40;

    tiles[40].nb_tile = 40;
    tiles[40].x = 416;
    tiles[40].y = 128;
    tiles[40].up_tile = -1;
    tiles[40].down_tile = -1;
    tiles[40].left_tile = 39;
    tiles[40].right_tile = 41;

    tiles[41].nb_tile = 41;
    tiles[41].x = 448;
    tiles[41].y = 128;
    tiles[41].up_tile = 26;
    tiles[41].down_tile = 49;
    tiles[41].left_tile = 40;
    tiles[41].right_tile = 42;

    tiles[42].nb_tile = 42;
    tiles[42].x = 480;
    tiles[42].y = 128;
    tiles[42].up_tile = -1;
    tiles[42].down_tile = -1;
    tiles[42].left_tile = 41;
    tiles[42].right_tile = 43;

    tiles[43].nb_tile = 43;
    tiles[43].x = 512;
    tiles[43].y = 128;
    tiles[43].up_tile = -1;
    tiles[43].down_tile = -1;
    tiles[43].left_tile = 42;
    tiles[43].right_tile = 44;

    tiles[44].nb_tile = 44;
    tiles[44].x = 544;
    tiles[44].y = 128;
    tiles[44].up_tile = 27;
    tiles[44].down_tile = 50;
    tiles[44].left_tile = 43;
    tiles[44].right_tile = -1;

    tiles[45].nb_tile = 45;
    tiles[45].x = 32;
    tiles[45].y = 160;
    tiles[45].up_tile = 28;
    tiles[45].down_tile = 51;
    tiles[45].left_tile = -1;
    tiles[45].right_tile = -1;

    tiles[46].nb_tile = 46;
    tiles[46].x = 128;
    tiles[46].y = 160;
    tiles[46].up_tile = 31;
    tiles[46].down_tile = 54;
    tiles[46].left_tile = -1;
    tiles[46].right_tile = -1;

    tiles[47].nb_tile = 47;
    tiles[47].x = 192;
    tiles[47].y = 160;
    tiles[47].up_tile = 33;
    tiles[47].down_tile = 55;
    tiles[47].left_tile = -1;
    tiles[47].right_tile = -1;

    tiles[48].nb_tile = 48;
    tiles[48].x = 384;
    tiles[48].y = 160;
    tiles[48].up_tile = 39;
    tiles[48].down_tile = 60;
    tiles[48].left_tile = -1;
    tiles[48].right_tile = -1;

    tiles[49].nb_tile = 49;
    tiles[49].x = 448;
    tiles[49].y = 160;
    tiles[49].up_tile = 41;
    tiles[49].down_tile = 61;
    tiles[49].left_tile = -1;
    tiles[49].right_tile = -1;

    tiles[50].nb_tile = 50;
    tiles[50].x = 544;
    tiles[50].y = 160;
    tiles[50].up_tile = 44;
    tiles[50].down_tile = 64;
    tiles[50].left_tile = -1;
    tiles[50].right_tile = -1;

    tiles[51].nb_tile = 51;
    tiles[51].x = 32;
    tiles[51].y = 192;
    tiles[51].up_tile = 45;
    tiles[51].down_tile = -1;
    tiles[51].left_tile = -1;
    tiles[51].right_tile = 52;

    tiles[52].nb_tile = 52;
    tiles[52].x = 64;
    tiles[52].y = 192;
    tiles[52].up_tile = -1;
    tiles[52].down_tile = -1;
    tiles[52].left_tile = 51;
    tiles[52].right_tile = 53;

    tiles[53].nb_tile = 53;
    tiles[53].x = 96;
    tiles[53].y = 192;
    tiles[53].up_tile = -1;
    tiles[53].down_tile = -1;
    tiles[53].left_tile = 52;
    tiles[53].right_tile = 54;

    tiles[54].nb_tile = 54;
    tiles[54].x = 128;
    tiles[54].y = 192;
    tiles[54].up_tile = 46;
    tiles[54].down_tile = 65;
    tiles[54].left_tile = 53;
    tiles[54].right_tile = -1;

    tiles[55].nb_tile = 55;
    tiles[55].x = 192;
    tiles[55].y = 192;
    tiles[55].up_tile = 47;
    tiles[55].down_tile = -1;
    tiles[55].left_tile = -1;
    tiles[55].right_tile = 56;

    tiles[56].nb_tile = 56;
    tiles[56].x = 224;
    tiles[56].y = 192;
    tiles[56].up_tile = -1;
    tiles[56].down_tile = -1;
    tiles[56].left_tile = 55;
    tiles[56].right_tile = 57;

    tiles[57].nb_tile = 57;
    tiles[57].x = 256;
    tiles[57].y = 192;
    tiles[57].up_tile = -1;
    tiles[57].down_tile = 66;
    tiles[57].left_tile = 56;
    tiles[57].right_tile = -1;

    tiles[58].nb_tile = 58;
    tiles[58].x = 320;
    tiles[58].y = 192;
    tiles[58].up_tile = -1;
    tiles[58].down_tile = 67;
    tiles[58].left_tile = -1;
    tiles[58].right_tile = 59;

    tiles[59].nb_tile = 59;
    tiles[59].x = 352;
    tiles[59].y = 192;
    tiles[59].up_tile = -1;
    tiles[59].down_tile = -1;
    tiles[59].left_tile = 58;
    tiles[59].right_tile = 60;

    tiles[60].nb_tile = 60;
    tiles[60].x = 384;
    tiles[60].y = 192;
    tiles[60].up_tile = 48;
    tiles[60].down_tile = -1;
    tiles[60].left_tile = 59;
    tiles[60].right_tile = -1;

    tiles[61].nb_tile = 61;
    tiles[61].x = 448;
    tiles[61].y = 192;
    tiles[61].up_tile = 49;
    tiles[61].down_tile = 68;
    tiles[61].left_tile = -1;
    tiles[61].right_tile = 62;

    tiles[62].nb_tile = 62;
    tiles[62].x = 480;
    tiles[62].y = 192;
    tiles[62].up_tile = -1;
    tiles[62].down_tile = -1;
    tiles[62].left_tile = 61;
    tiles[62].right_tile = 63;

    tiles[63].nb_tile = 63;
    tiles[63].x = 512;
    tiles[63].y = 192;
    tiles[63].up_tile = -1;
    tiles[63].down_tile = -1;
    tiles[63].left_tile = 62;
    tiles[63].right_tile = 64;

    tiles[64].nb_tile = 64;
    tiles[64].x = 544;
    tiles[64].y = 192;
    tiles[64].up_tile = 50;
    tiles[64].down_tile = -1;
    tiles[64].left_tile = 63;
    tiles[64].right_tile = -1;

    tiles[65].nb_tile = 65;
    tiles[65].x = 128;
    tiles[65].y = 224;
    tiles[65].up_tile = 54;
    tiles[65].down_tile = 69;
    tiles[65].left_tile = -1;
    tiles[65].right_tile = -1;

    tiles[66].nb_tile = 66;
    tiles[66].x = 156;
    tiles[66].y = 224;
    tiles[66].up_tile = 57;
    tiles[66].down_tile = 72;
    tiles[66].left_tile = -1;
    tiles[66].right_tile = -1;

    tiles[67].nb_tile = 67;
    tiles[67].x = 320;
    tiles[67].y = 224;
    tiles[67].up_tile = 58;
    tiles[67].down_tile = 74;
    tiles[67].left_tile = -1;
    tiles[67].right_tile = -1;

    tiles[68].nb_tile = 68;
    tiles[68].x = 448;
    tiles[68].y = 224;
    tiles[68].up_tile = 61;
    tiles[68].down_tile = 77;
    tiles[68].left_tile = -1;
    tiles[68].right_tile = -1;

    tiles[69].nb_tile = 69;
    tiles[69].x = 128;
    tiles[69].y = 256;
    tiles[69].up_tile = 65;
    tiles[69].down_tile = 78;
    tiles[69].left_tile = -1;
    tiles[69].right_tile = -1;

    tiles[70].nb_tile = 70;
    tiles[70].x = 192;
    tiles[70].y = 256;
    tiles[70].up_tile = -1;
    tiles[70].down_tile = 79;
    tiles[70].left_tile = -1;
    tiles[70].right_tile = 71;

    tiles[71].nb_tile = 71;
    tiles[71].x = 224;
    tiles[71].y = 256;
    tiles[71].up_tile = -1;
    tiles[71].down_tile = -1;
    tiles[71].left_tile = 70;
    tiles[71].right_tile = 72;

    tiles[72].nb_tile = 72;
    tiles[72].x = 256;
    tiles[72].y = 256;
    tiles[72].up_tile = 66;
    tiles[72].down_tile = -1;
    tiles[72].left_tile = 71;
    tiles[72].right_tile = 73;

    tiles[73].nb_tile = 73;
    tiles[73].x = 288;
    tiles[73].y = 256;
    tiles[73].up_tile = -1;
    tiles[73].down_tile = -1;
    tiles[73].left_tile = 72;
    tiles[73].right_tile = 74;

    tiles[74].nb_tile = 74;
    tiles[74].x = 320;
    tiles[74].y = 256;
    tiles[74].up_tile = 67;
    tiles[74].down_tile = -1;
    tiles[74].left_tile = 73;
    tiles[74].right_tile = 75;

    tiles[75].nb_tile = 75;
    tiles[75].x = 352;
    tiles[75].y = 256;
    tiles[75].up_tile = -1;
    tiles[75].down_tile = -1;
    tiles[75].left_tile = 74;
    tiles[75].right_tile = 76;

    tiles[76].nb_tile = 76;
    tiles[76].x = 384;
    tiles[76].y = 256;
    tiles[76].up_tile = -1;
    tiles[76].down_tile = 80;
    tiles[76].left_tile = 75;
    tiles[76].right_tile = -1;

    tiles[77].nb_tile = 77;
    tiles[77].x = 448;
    tiles[77].y = 256;
    tiles[77].up_tile = 68;
    tiles[77].down_tile = 81;
    tiles[77].left_tile = -1;
    tiles[77].right_tile = -1;

    tiles[78].nb_tile = 78;
    tiles[78].x = 128;
    tiles[78].y = 288;
    tiles[78].up_tile = 69;
    tiles[78].down_tile = 86;
    tiles[78].left_tile = -1;
    tiles[78].right_tile = -1;

    tiles[79].nb_tile = 79;
    tiles[79].x = 192;
    tiles[79].y = 288;
    tiles[79].up_tile = 70;
    tiles[79].down_tile = 88;
    tiles[79].left_tile = -1;
    tiles[79].right_tile = -1;

    tiles[80].nb_tile = 80;
    tiles[80].x = 384;
    tiles[80].y = 288;
    tiles[80].up_tile = 76;
    tiles[80].down_tile = 89;
    tiles[80].left_tile = -1;
    tiles[80].right_tile = -1;

    tiles[81].nb_tile = 81;
    tiles[81].x = 448;
    tiles[81].y = 288;
    tiles[81].up_tile = 77;
    tiles[81].down_tile = 91;
    tiles[81].left_tile = -1;
    tiles[81].right_tile = -1;

    tiles[82].nb_tile = 82;
    tiles[82].x = 0;
    tiles[82].y = 320;
    tiles[82].up_tile = -1;
    tiles[82].down_tile = -1;
    tiles[82].left_tile = -1;
    tiles[82].right_tile = 83;

    tiles[83].nb_tile = 83;
    tiles[83].x = 32;
    tiles[83].y = 320;
    tiles[83].up_tile = -1;
    tiles[83].down_tile = -1;
    tiles[83].left_tile = 82;
    tiles[83].right_tile = 84;

    tiles[84].nb_tile = 84;
    tiles[84].x = 64;
    tiles[84].y = 320;
    tiles[84].up_tile = -1;
    tiles[84].down_tile = -1;
    tiles[84].left_tile = 83;
    tiles[84].right_tile = 85;

    tiles[85].nb_tile = 85;
    tiles[85].x = 96;
    tiles[85].y = 320;
    tiles[85].up_tile = -1;
    tiles[85].down_tile = -1;
    tiles[85].left_tile = 84;
    tiles[85].right_tile = 86;

    tiles[86].nb_tile = 86;
    tiles[86].x = 128;
    tiles[86].y = 320;
    tiles[86].up_tile = 78;
    tiles[86].down_tile = 96;
    tiles[86].left_tile = 85;
    tiles[86].right_tile = 87;

    tiles[87].nb_tile = 87;
    tiles[87].x = 160;
    tiles[87].y = 320;
    tiles[87].up_tile = -1;
    tiles[87].down_tile = -1;
    tiles[87].left_tile = 86;
    tiles[87].right_tile = 88;

    tiles[88].nb_tile = 88;
    tiles[88].x = 192;
    tiles[88].y = 320;
    tiles[88].up_tile = 79;
    tiles[88].down_tile = 97;
    tiles[88].left_tile = 87;
    tiles[88].right_tile = -1;

    tiles[89].nb_tile = 89;
    tiles[89].x = 384;
    tiles[89].y = 320;
    tiles[89].up_tile = 80;
    tiles[89].down_tile = 98;
    tiles[89].left_tile = -1;
    tiles[89].right_tile = 90;

    tiles[90].nb_tile = 90;
    tiles[90].x = 416;
    tiles[90].y = 320;
    tiles[90].up_tile = -1;
    tiles[90].down_tile = -1;
    tiles[90].left_tile = 89;
    tiles[90].right_tile = 91;

    tiles[91].nb_tile = 91;
    tiles[91].x = 448;
    tiles[91].y = 320;
    tiles[91].up_tile = 81;
    tiles[91].down_tile = 99;
    tiles[91].left_tile = 90;
    tiles[91].right_tile = 92;

    tiles[92].nb_tile = 92;
    tiles[92].x = 480;
    tiles[92].y = 320;
    tiles[92].up_tile = -1;
    tiles[92].down_tile = -1;
    tiles[92].left_tile = 91;
    tiles[92].right_tile = 93;

    tiles[93].nb_tile = 93;
    tiles[93].x = 512;
    tiles[93].y = 320;
    tiles[93].up_tile = -1;
    tiles[93].down_tile = -1;
    tiles[93].left_tile = 92;
    tiles[93].right_tile = 94;

    tiles[94].nb_tile = 94;
    tiles[94].x = 544;
    tiles[94].y = 320;
    tiles[94].up_tile = -1;
    tiles[94].down_tile = -1;
    tiles[94].left_tile = 93;
    tiles[94].right_tile = 95;

    tiles[95].nb_tile = 95;
    tiles[95].x = 576;
    tiles[95].y = 320;
    tiles[95].up_tile = -1;
    tiles[95].down_tile = -1;
    tiles[95].left_tile = 94;
    tiles[95].right_tile = -1;

    tiles[96].nb_tile = 96;
    tiles[96].x = 128;
    tiles[96].y = 352;
    tiles[96].up_tile = 86;
    tiles[96].down_tile = 100;
    tiles[96].left_tile = -1;
    tiles[96].right_tile = -1;

    tiles[97].nb_tile = 97;
    tiles[97].x = 192;
    tiles[97].y = 352;
    tiles[97].up_tile = 88;
    tiles[97].down_tile = 101;
    tiles[97].left_tile = -1;
    tiles[97].right_tile = -1;

    tiles[98].nb_tile = 98;
    tiles[98].x = 384;
    tiles[98].y = 352;
    tiles[98].up_tile = 89;
    tiles[98].down_tile = 107;
    tiles[98].left_tile = -1;
    tiles[98].right_tile = -1;

    tiles[99].nb_tile = 99;
    tiles[99].x = 448;
    tiles[99].y = 352;
    tiles[99].up_tile = 91;
    tiles[99].down_tile = 108;
    tiles[99].left_tile = -1;
    tiles[99].right_tile = -1;

    tiles[100].nb_tile = 100;
    tiles[100].x = 128;
    tiles[100].y = 384;
    tiles[100].up_tile = 96;
    tiles[100].down_tile = 109;
    tiles[100].left_tile = -1;
    tiles[100].right_tile = -1;

    tiles[101].nb_tile = 101;
    tiles[101].x = 192;
    tiles[101].y = 384;
    tiles[101].up_tile = 97;
    tiles[101].down_tile = 110;
    tiles[101].left_tile = -1;
    tiles[101].right_tile = 102;

    tiles[102].nb_tile = 102;
    tiles[102].x = 224;
    tiles[102].y = 384;
    tiles[102].up_tile = -1;
    tiles[102].down_tile = -1;
    tiles[102].left_tile = 101;
    tiles[102].right_tile = 103;

    tiles[103].nb_tile = 103;
    tiles[103].x = 256;
    tiles[103].y = 384;
    tiles[103].up_tile = -1;
    tiles[103].down_tile = -1;
    tiles[103].left_tile = 102;
    tiles[103].right_tile = 104;

    tiles[104].nb_tile = 104;
    tiles[104].x = 288;
    tiles[104].y = 384;
    tiles[104].up_tile = -1;
    tiles[104].down_tile = -1;
    tiles[104].left_tile = 103;
    tiles[104].right_tile = 105;

    tiles[105].nb_tile = 105;
    tiles[105].x = 320;
    tiles[105].y = 384;
    tiles[105].up_tile = -1;
    tiles[105].down_tile = -1;
    tiles[105].left_tile = 104;
    tiles[105].right_tile = 106;

    tiles[106].nb_tile = 106;
    tiles[106].x = 352;
    tiles[106].y = 384;
    tiles[106].up_tile = -1;
    tiles[106].down_tile = -1;
    tiles[106].left_tile = 105;
    tiles[106].right_tile = 107;

    tiles[107].nb_tile = 107;
    tiles[107].x = 384;
    tiles[107].y = 384;
    tiles[107].up_tile = 98;
    tiles[107].down_tile = 111;
    tiles[107].left_tile = 106;
    tiles[107].right_tile = -1;

    tiles[108].nb_tile = 108;
    tiles[108].x = 448;
    tiles[108].y = 384;
    tiles[108].up_tile = 99;
    tiles[108].down_tile = 112;
    tiles[108].left_tile = -1;
    tiles[108].right_tile = -1;

    tiles[109].nb_tile = 109;
    tiles[109].x = 128;
    tiles[109].y = 416;
    tiles[109].up_tile = -1;
    tiles[109].down_tile = -1;
    tiles[109].left_tile = 100;
    tiles[109].right_tile = 116;

    tiles[110].nb_tile = 110;
    tiles[110].x = 192;
    tiles[110].y = 416;
    tiles[110].up_tile = 101;
    tiles[110].down_tile = 118;
    tiles[110].left_tile = -1;
    tiles[110].right_tile = -1;

    tiles[111].nb_tile = 111;
    tiles[111].x = 384;
    tiles[111].y = 416;
    tiles[111].up_tile = 107;
    tiles[111].down_tile = 123;
    tiles[111].left_tile = -1;
    tiles[111].right_tile = -1;

    tiles[112].nb_tile = 112;
    tiles[112].x = 448;
    tiles[112].y = 416;
    tiles[112].up_tile = 108;
    tiles[112].down_tile = 125;
    tiles[112].left_tile = -1;
    tiles[112].right_tile = -1;

    tiles[113].nb_tile = 113;
    tiles[113].x = 32;
    tiles[113].y = 448;
    tiles[113].up_tile = -1;
    tiles[113].down_tile = 129;
    tiles[113].left_tile = -1;
    tiles[113].right_tile = 114;

    tiles[114].nb_tile = 114;
    tiles[114].x = 64;
    tiles[114].y = 448;
    tiles[114].up_tile = -1;
    tiles[114].down_tile = -1;
    tiles[114].left_tile = 113;
    tiles[114].right_tile = 115;

    tiles[115].nb_tile = 115;
    tiles[115].x = 96;
    tiles[115].y = 448;
    tiles[115].up_tile = -1;
    tiles[115].down_tile = -1;
    tiles[115].left_tile = 114;
    tiles[115].right_tile = 116;

    tiles[116].nb_tile = 116;
    tiles[116].x = 128;
    tiles[116].y = 448;
    tiles[116].up_tile = 109;
    tiles[116].down_tile = 130;
    tiles[116].left_tile = 115;
    tiles[116].right_tile = 117;

    tiles[117].nb_tile = 117;
    tiles[117].x = 160;
    tiles[117].y = 448;
    tiles[117].up_tile = -1;
    tiles[117].down_tile = -1;
    tiles[117].left_tile = 116;
    tiles[117].right_tile = 118;

    tiles[118].nb_tile = 118;
    tiles[118].x = 192;
    tiles[118].y = 448;
    tiles[118].up_tile = 110;
    tiles[118].down_tile = -1;
    tiles[118].left_tile = 117;
    tiles[118].right_tile = 119;

    tiles[119].nb_tile = 119;
    tiles[119].x = 224;
    tiles[119].y = 448;
    tiles[119].up_tile = -1;
    tiles[119].down_tile = -1;
    tiles[119].left_tile = 118;
    tiles[119].right_tile = 120;

    tiles[120].nb_tile = 120;
    tiles[120].x = 256;
    tiles[120].y = 448;
    tiles[120].up_tile = -1;
    tiles[120].down_tile = 131;
    tiles[120].left_tile = 119;
    tiles[120].right_tile = -1;

    tiles[121].nb_tile = 121;
    tiles[121].x = 320;
    tiles[121].y = 448;
    tiles[121].up_tile = -1;
    tiles[121].down_tile = 132;
    tiles[121].left_tile = -1;
    tiles[121].right_tile = 122;

    tiles[122].nb_tile = 122;
    tiles[122].x = 352;
    tiles[122].y = 448;
    tiles[122].up_tile = -1;
    tiles[122].down_tile = -1;
    tiles[122].left_tile = 121;
    tiles[122].right_tile = 123;

    tiles[123].nb_tile = 123;
    tiles[123].x = 384;
    tiles[123].y = 448;
    tiles[123].up_tile = 111;
    tiles[123].down_tile = -1;
    tiles[123].left_tile = 122;
    tiles[123].right_tile = 124;

    tiles[124].nb_tile = 124;
    tiles[124].x = 416;
    tiles[124].y = 448;
    tiles[124].up_tile = -1;
    tiles[124].down_tile = -1;
    tiles[124].left_tile = 123;
    tiles[124].right_tile = 125;

    tiles[125].nb_tile = 125;
    tiles[125].x = 448;
    tiles[125].y = 448;
    tiles[125].up_tile = 112;
    tiles[125].down_tile = 133;
    tiles[125].left_tile = 124;
    tiles[125].right_tile = 126;

    tiles[126].nb_tile = 126;
    tiles[126].x = 480;
    tiles[126].y = 448;
    tiles[126].up_tile = -1;
    tiles[126].down_tile = -1;
    tiles[126].left_tile = 125;
    tiles[126].right_tile = 127;

    tiles[127].nb_tile = 127;
    tiles[127].x = 512;
    tiles[127].y = 448;
    tiles[127].up_tile = -1;
    tiles[127].down_tile = -1;
    tiles[127].left_tile = 126;
    tiles[127].right_tile = 128;

    tiles[128].nb_tile = 128;
    tiles[128].x = 544;
    tiles[128].y = 448;
    tiles[128].up_tile = -1;
    tiles[128].down_tile = 134;
    tiles[128].left_tile = 127;
    tiles[128].right_tile = -1;

    tiles[129].nb_tile = 129;
    tiles[129].x = 32;
    tiles[129].y = 480;
    tiles[129].up_tile = 113;
    tiles[129].down_tile = 135;
    tiles[129].left_tile = -1;
    tiles[129].right_tile = -1;

    tiles[130].nb_tile = 130;
    tiles[130].x = 128;
    tiles[130].y = 480;
    tiles[130].up_tile = 116;
    tiles[130].down_tile = 137;
    tiles[130].left_tile = -1;
    tiles[130].right_tile = -1;

    tiles[131].nb_tile = 131;
    tiles[131].x = 256;
    tiles[131].y = 480;
    tiles[131].up_tile = 120;
    tiles[131].down_tile = 141;
    tiles[131].left_tile = -1;
    tiles[131].right_tile = -1;

    tiles[132].nb_tile = 132;
    tiles[132].x = 320;
    tiles[132].y = 480;
    tiles[132].up_tile = 121;
    tiles[132].down_tile = 143;
    tiles[132].left_tile = -1;
    tiles[132].right_tile = -1;

    tiles[133].nb_tile = 133;
    tiles[133].x = 448;
    tiles[133].y = 480;
    tiles[133].up_tile = 125;
    tiles[133].down_tile = 147;
    tiles[133].left_tile = -1;
    tiles[133].right_tile = -1;

    tiles[134].nb_tile = 134;
    tiles[134].x = 544;
    tiles[134].y = 480;
    tiles[134].up_tile = 128;
    tiles[134].down_tile = 149;
    tiles[134].left_tile = -1;
    tiles[134].right_tile = -1;

    tiles[135].nb_tile = 135;
    tiles[135].x = 32;
    tiles[135].y = 512;
    tiles[135].up_tile = 129;
    tiles[135].down_tile = -1;
    tiles[135].left_tile = -1;
    tiles[135].right_tile = 136;

    tiles[136].nb_tile = 136;
    tiles[136].x = 64;
    tiles[136].y = 512;
    tiles[136].up_tile = -1;
    tiles[136].down_tile = 150;
    tiles[136].left_tile = 135;
    tiles[136].right_tile = -1;

    tiles[137].nb_tile = 137;
    tiles[137].x = 128;
    tiles[137].y = 512;
    tiles[137].up_tile = 130;
    tiles[137].down_tile = 151;
    tiles[137].left_tile = -1;
    tiles[137].right_tile = 138;

    tiles[138].nb_tile = 138;
    tiles[138].x = 160;
    tiles[138].y = 512;
    tiles[138].up_tile = -1;
    tiles[138].down_tile = -1;
    tiles[138].left_tile = 137;
    tiles[138].right_tile = 139;

    tiles[139].nb_tile = 139;
    tiles[139].x = 192;
    tiles[139].y = 512;
    tiles[139].up_tile = -1;
    tiles[139].down_tile = 152;
    tiles[139].left_tile = 138;
    tiles[139].right_tile = 140;

    tiles[140].nb_tile = 140;
    tiles[140].x = 224;
    tiles[140].y = 512;
    tiles[140].up_tile = -1;
    tiles[140].down_tile = -1;
    tiles[140].left_tile = 139;
    tiles[140].right_tile = 141;

    tiles[141].nb_tile = 141;
    tiles[141].x = 256;
    tiles[141].y = 512;
    tiles[141].up_tile = 131;
    tiles[141].down_tile = -1;
    tiles[141].left_tile = 140;
    tiles[141].right_tile = 142;

    tiles[142].nb_tile = 142;
    tiles[142].x = 288;
    tiles[142].y = 512;
    tiles[142].up_tile = -1;
    tiles[142].down_tile = -1;
    tiles[142].left_tile = 141;
    tiles[142].right_tile = 143;

    tiles[143].nb_tile = 143;
    tiles[143].x = 320;
    tiles[143].y = 512;
    tiles[143].up_tile = 132;
    tiles[143].down_tile = -1;
    tiles[143].left_tile = 142;
    tiles[143].right_tile = 144;

    tiles[144].nb_tile = 144;
    tiles[144].x = 352;
    tiles[144].y = 512;
    tiles[144].up_tile = -1;
    tiles[144].down_tile = -1;
    tiles[144].left_tile = 143;
    tiles[144].right_tile = 145;

    tiles[145].nb_tile = 145;
    tiles[145].x = 384;
    tiles[145].y = 512;
    tiles[145].up_tile = -1;
    tiles[145].down_tile = 153;
    tiles[145].left_tile = 144;
    tiles[145].right_tile = 146;

    tiles[146].nb_tile = 146;
    tiles[146].x = 416;
    tiles[146].y = 512;
    tiles[146].up_tile = -1;
    tiles[146].down_tile = -1;
    tiles[146].left_tile = 145;
    tiles[146].right_tile = 147;

    tiles[147].nb_tile = 147;
    tiles[147].x = 448;
    tiles[147].y = 512;
    tiles[147].up_tile = 133;
    tiles[147].down_tile = 154;
    tiles[147].left_tile = 146;
    tiles[147].right_tile = -1;

    tiles[148].nb_tile = 148;
    tiles[148].x = 512;
    tiles[148].y = 512;
    tiles[148].up_tile = -1;
    tiles[148].down_tile = 155;
    tiles[148].left_tile = -1;
    tiles[148].right_tile = 149;

    tiles[149].nb_tile = 149;
    tiles[149].x = 544;
    tiles[149].y = 512;
    tiles[149].up_tile = 134;
    tiles[149].down_tile = -1;
    tiles[149].left_tile = 148;
    tiles[149].right_tile = -1;

    tiles[150].nb_tile = 150;
    tiles[150].x = 64;
    tiles[150].y = 544;
    tiles[150].up_tile = 136;
    tiles[150].down_tile = 157;
    tiles[150].left_tile = -1;
    tiles[150].right_tile = -1;

    tiles[151].nb_tile = 151;
    tiles[151].x = 128;
    tiles[151].y = 544;
    tiles[151].up_tile = 137;
    tiles[151].down_tile = 159;
    tiles[151].left_tile = -1;
    tiles[151].right_tile = -1;

    tiles[152].nb_tile = 152;
    tiles[152].x = 192;
    tiles[152].y = 544;
    tiles[152].up_tile = 139;
    tiles[152].down_tile = 160;
    tiles[152].left_tile = -1;
    tiles[152].right_tile = -1;

    tiles[153].nb_tile = 153;
    tiles[153].x = 384;
    tiles[153].y = 544;
    tiles[153].up_tile = 145;
    tiles[153].down_tile = 165;
    tiles[153].left_tile = -1;
    tiles[153].right_tile = -1;

    tiles[154].nb_tile = 154;
    tiles[154].x = 448;
    tiles[154].y = 544;
    tiles[154].up_tile = 147;
    tiles[154].down_tile = 166;
    tiles[154].left_tile = -1;
    tiles[154].right_tile = -1;

    tiles[155].nb_tile = 155;
    tiles[155].x = 512;
    tiles[155].y = 544;
    tiles[155].up_tile = 148;
    tiles[155].down_tile = 168;
    tiles[155].left_tile = -1;
    tiles[155].right_tile = -1;

    tiles[156].nb_tile = 156;
    tiles[156].x = 32;
    tiles[156].y = 576;
    tiles[156].up_tile = -1;
    tiles[156].down_tile = 170;
    tiles[156].left_tile = -1;
    tiles[156].right_tile = 157;

    tiles[157].nb_tile = 157;
    tiles[157].x = 64;
    tiles[157].y = 576;
    tiles[157].up_tile = 150;
    tiles[157].down_tile = -1;
    tiles[157].left_tile = 156;
    tiles[157].right_tile = 158;

    tiles[158].nb_tile = 158;
    tiles[158].x = 96;
    tiles[158].y = 576;
    tiles[158].up_tile = -1;
    tiles[158].down_tile = -1;
    tiles[158].left_tile = 157;
    tiles[158].right_tile = 159;

    tiles[159].nb_tile = 159;
    tiles[159].x = 128;
    tiles[159].y = 576;
    tiles[159].up_tile = 151;
    tiles[159].down_tile = -1;
    tiles[159].left_tile = 158;
    tiles[159].right_tile = -1;

    tiles[160].nb_tile = 160;
    tiles[160].x = 192;
    tiles[160].y = 576;
    tiles[160].up_tile = 152;
    tiles[160].down_tile = -1;
    tiles[160].left_tile = -1;
    tiles[160].right_tile = 161;

    tiles[161].nb_tile = 161;
    tiles[161].x = 224;
    tiles[161].y = 576;
    tiles[161].up_tile = -1;
    tiles[161].down_tile = -1;
    tiles[161].left_tile = 160;
    tiles[161].right_tile = 162;

    tiles[162].nb_tile = 162;
    tiles[162].x = 256;
    tiles[162].y = 576;
    tiles[162].up_tile = -1;
    tiles[162].down_tile = 171;
    tiles[162].left_tile = 161;
    tiles[162].right_tile = -1;

    tiles[163].nb_tile = 163;
    tiles[163].x = 320;
    tiles[163].y = 576;
    tiles[163].up_tile = -1;
    tiles[163].down_tile = 172;
    tiles[163].left_tile = -1;
    tiles[163].right_tile = 164;

    tiles[164].nb_tile = 164;
    tiles[164].x = 352;
    tiles[164].y = 576;
    tiles[164].up_tile = -1;
    tiles[164].down_tile = -1;
    tiles[164].left_tile = 163;
    tiles[164].right_tile = 165;

    tiles[165].nb_tile = 165;
    tiles[165].x = 384;
    tiles[165].y = 576;
    tiles[165].up_tile = 153;
    tiles[165].down_tile = -1;
    tiles[165].left_tile = 164;
    tiles[165].right_tile = -1;

    tiles[166].nb_tile = 166;
    tiles[166].x = 448;
    tiles[166].y = 576;
    tiles[166].up_tile = 154;
    tiles[166].down_tile = -1;
    tiles[166].left_tile = -1;
    tiles[166].right_tile = 167;

    tiles[167].nb_tile = 167;
    tiles[167].x = 480;
    tiles[167].y = 576;
    tiles[167].up_tile = -1;
    tiles[167].down_tile = -1;
    tiles[167].left_tile = 166;
    tiles[167].right_tile = 168;

    tiles[168].nb_tile = 168;
    tiles[168].x = 512;
    tiles[168].y = 576;
    tiles[168].up_tile = 155;
    tiles[168].down_tile = -1;
    tiles[168].left_tile = 167;
    tiles[168].right_tile = 169;

    tiles[169].nb_tile = 169;
    tiles[169].x = 544;
    tiles[169].y = 576;
    tiles[169].up_tile = -1;
    tiles[169].down_tile = 173;
    tiles[169].left_tile = 168;
    tiles[169].right_tile = -1;

    tiles[170].nb_tile = 170;
    tiles[170].x = 32;
    tiles[170].y = 608;
    tiles[170].up_tile = 156;
    tiles[170].down_tile = 174;
    tiles[170].left_tile = -1;
    tiles[170].right_tile = -1;

    tiles[171].nb_tile = 171;
    tiles[171].x = 256;
    tiles[171].y = 608;
    tiles[171].up_tile = 162;
    tiles[171].down_tile = 181;
    tiles[171].left_tile = -1;
    tiles[171].right_tile = -1;

    tiles[172].nb_tile = 172;
    tiles[172].x = 320;
    tiles[172].y = 608;
    tiles[172].up_tile = 163;
    tiles[172].down_tile = 183;
    tiles[172].left_tile = -1;
    tiles[172].right_tile = -1;

    tiles[173].nb_tile = 173;
    tiles[173].x = 544;
    tiles[173].y = 608;
    tiles[173].up_tile = 169;
    tiles[173].down_tile = 190;
    tiles[173].left_tile = -1;
    tiles[173].right_tile = -1;

    tiles[174].nb_tile = 174;
    tiles[174].x = 32;
    tiles[174].y = 640;
    tiles[174].up_tile = 170;
    tiles[174].down_tile = -1;
    tiles[174].left_tile = -1;
    tiles[174].right_tile = 175;

    tiles[175].nb_tile = 175;
    tiles[175].x = 64;
    tiles[175].y = 640;
    tiles[175].up_tile = -1;
    tiles[175].down_tile = -1;
    tiles[175].left_tile = 174;
    tiles[175].right_tile = 176;

    tiles[176].nb_tile = 176;
    tiles[176].x = 96;
    tiles[176].y = 640;
    tiles[176].up_tile = -1;
    tiles[176].down_tile = -1;
    tiles[176].left_tile = 175;
    tiles[176].right_tile = 177;

    tiles[177].nb_tile = 177;
    tiles[177].x = 128;
    tiles[177].y = 640;
    tiles[177].up_tile = -1;
    tiles[177].down_tile = -1;
    tiles[177].left_tile = 176;
    tiles[177].right_tile = 178;

    tiles[178].nb_tile = 178;
    tiles[178].x = 160;
    tiles[178].y = 640;
    tiles[178].up_tile = -1;
    tiles[178].down_tile = -1;
    tiles[178].left_tile = 177;
    tiles[178].right_tile = 179;

    tiles[179].nb_tile = 179;
    tiles[179].x = 192;
    tiles[179].y = 640;
    tiles[179].up_tile = -1;
    tiles[179].down_tile = -1;
    tiles[179].left_tile = 178;
    tiles[179].right_tile = 180;

    tiles[180].nb_tile = 180;
    tiles[180].x = 224;
    tiles[180].y = 640;
    tiles[180].up_tile = -1;
    tiles[180].down_tile = -1;
    tiles[180].left_tile = 179;
    tiles[180].right_tile = 181;

    tiles[181].nb_tile = 181;
    tiles[181].x = 256;
    tiles[181].y = 640;
    tiles[181].up_tile = 171;
    tiles[181].down_tile = -1;
    tiles[181].left_tile = 180;
    tiles[181].right_tile = 182;

    tiles[182].nb_tile = 182;
    tiles[182].x = 288;
    tiles[182].y = 640;
    tiles[182].up_tile = -1;
    tiles[182].down_tile = -1;
    tiles[182].left_tile = 181;
    tiles[182].right_tile = 183;

    tiles[183].nb_tile = 183;
    tiles[183].x = 320;
    tiles[183].y = 640;
    tiles[183].up_tile = 172;
    tiles[183].down_tile = -1;
    tiles[183].left_tile = 182;
    tiles[183].right_tile = 184;

    tiles[184].nb_tile = 184;
    tiles[184].x = 352;
    tiles[184].y = 640;
    tiles[184].up_tile = -1;
    tiles[184].down_tile = -1;
    tiles[184].left_tile = 183;
    tiles[184].right_tile = 185;

    tiles[185].nb_tile = 185;
    tiles[185].x = 384;
    tiles[185].y = 640;
    tiles[185].up_tile = -1;
    tiles[185].down_tile = -1;
    tiles[185].left_tile = 184;
    tiles[185].right_tile = 186;

    tiles[186].nb_tile = 186;
    tiles[186].x = 416;
    tiles[186].y = 640;
    tiles[186].up_tile = -1;
    tiles[186].down_tile = -1;
    tiles[186].left_tile = 185;
    tiles[186].right_tile = 187;

    tiles[187].nb_tile = 187;
    tiles[187].x = 448;
    tiles[187].y = 640;
    tiles[187].up_tile = -1;
    tiles[187].down_tile = -1;
    tiles[187].left_tile = 186;
    tiles[187].right_tile = 188;

    tiles[188].nb_tile = 188;
    tiles[188].x = 480;
    tiles[188].y = 640;
    tiles[188].up_tile = -1;
    tiles[188].down_tile = -1;
    tiles[188].left_tile = 187;
    tiles[188].right_tile = 189;

    tiles[189].nb_tile = 189;
    tiles[189].x = 512;
    tiles[189].y = 640;
    tiles[189].up_tile = -1;
    tiles[189].down_tile = -1;
    tiles[189].left_tile = 188;
    tiles[189].right_tile = 190;

    tiles[190].nb_tile = 190;
    tiles[190].x = 544;
    tiles[190].y = 640;
    tiles[190].up_tile = 173;
    tiles[190].down_tile = -1;
    tiles[190].left_tile = 189;
    tiles[190].right_tile = -1;

    tiles[191].nb_tile = 191;
    tiles[191].pas_blinky = 3;
    tiles[191].pas_pinky_up = 3;
    tiles[191].pas_pinky_down = 3;
    tiles[191].pas_pinky_left = 3;
    tiles[191].pas_pinky_right = 3;
    tiles[191].pas_inky_up = 3;
    tiles[191].pas_inky_down = 3;
    tiles[191].pas_inky_left = 3;
    tiles[191].pas_inky_right = 3;
    tiles[191].pas_clyde = 3;
    tiles[191].x = 256;
    tiles[191].y = 320;
    tiles[191].up_tile = -1;
    tiles[191].down_tile = -1;
    tiles[191].left_tile = -1;
    tiles[191].right_tile = 192;

    tiles[192].nb_tile = 192;
    tiles[192].pas_blinky = 2;
    tiles[192].pas_pinky_up = 2;
    tiles[192].pas_pinky_down = 2;
    tiles[192].pas_pinky_left = 2;
    tiles[192].pas_pinky_right = 2;
    tiles[192].pas_inky_up = 2;
    tiles[192].pas_inky_down = 2;
    tiles[192].pas_inky_left = 2;
    tiles[192].pas_inky_right = 2;
    tiles[192].pas_clyde = 2;
    tiles[192].x = 288;
    tiles[192].y = 320;
    tiles[192].up_tile = 194;
    tiles[192].down_tile = -1;
    tiles[192].left_tile = -1;
    tiles[192].right_tile = -1;

    tiles[193].nb_tile = 193;
    tiles[193].pas_blinky = 3;
    tiles[193].pas_pinky_up = 3;
    tiles[193].pas_pinky_down = 3;
    tiles[193].pas_pinky_left = 3;
    tiles[193].pas_pinky_right = 3;
    tiles[193].pas_inky_up = 3;
    tiles[193].pas_inky_down = 3;
    tiles[193].pas_inky_left = 3;
    tiles[193].pas_inky_right = 3;
    tiles[193].pas_clyde = 3;
    tiles[193].x = 320;
    tiles[193].y = 320;
    tiles[193].up_tile = -1;
    tiles[193].down_tile = -1;
    tiles[193].left_tile = 192;
    tiles[193].right_tile = -1;

    tiles[194].nb_tile = 194;
    tiles[194].pas_blinky = 1;
    tiles[194].pas_pinky_up = 1;
    tiles[194].pas_pinky_down = 1;
    tiles[194].pas_pinky_left = 1;
    tiles[194].pas_pinky_right = 1;
    tiles[194].pas_inky_up = 1;
    tiles[194].pas_inky_down = 1;
    tiles[194].pas_inky_left = 1;
    tiles[194].pas_inky_right = 1;
    tiles[194].pas_clyde = 1;
    tiles[194].x = 288;
    tiles[194].y = 288;
    tiles[194].up_tile = 73;
    tiles[194].down_tile = -1;
    tiles[194].left_tile = -1;
    tiles[194].right_tile = -1;
}
