#include "PacMan.hh"
#include "Scene.hh"
#include "TimeManager.hh"
#include "ResourcesManager.hh"
#include "Map.hh"
#include "Item.hh"
#include <sstream>

PacMan::PacMan() {
    Scene &Window = Scene::GetInstance();
    ResourcesManager &rm = ResourcesManager::GetInstance();
    SetLife(3);
    SetScore(0);
    SetDirection(Left);
    SetX(288);
    SetY(512);
    SetAnimation(1, 0);
    SetSpeed(8);
    SetTile(Window.tiles[142]);
    SetTexture(rm.texturePacMan);
    SetTextureRect(0, 0, 32, 32);
    // on ajoute les murs de la map comme observers
    for (int i = 0; i < 212; i++) {
        AddObserver((Map*)Window.GetEntities()[i]);
    }
    // on ajoute les points et les bonus comme observers
    for (int i = 212; i < Window.GetEntities().size(); i++) {
        AddObserver((Item*)Window.GetEntities()[i]);
    }
    // on initialise les textes : score, vie, victoire, défaite, rejouer, ready, l'image de défaite et victoire et les vies pacman
    scoretext.setString("SCORE = ");
    scoretext.setFont(rm.font);
    scoretext.setCharacterSize(30);
    scoretext.setFillColor(sf::Color::White);
    scoretext.setPosition(10, 700);
    lifetext.setString("LIFE = ");
    lifetext.setFont(rm.font);
    lifetext.setCharacterSize(30);
    lifetext.setFillColor(sf::Color::White);
    lifetext.setPosition(370, 700);
    wintext.setString("You Won!");
    wintext.setFont(rm.font);
    wintext.setCharacterSize(30);
    wintext.setFillColor(sf::Color::White);
    wintext.setPosition(230, 444);
    losetext.setString("Game Over!");
    losetext.setFont(rm.font);
    losetext.setCharacterSize(30);
    losetext.setFillColor(sf::Color::White);
    losetext.setPosition(230, 444);
    replay.setString("Replay (CLICK R)");
    replay.setFont(rm.font);
    replay.setCharacterSize(30);
    replay.setFillColor(sf::Color::White);
    replay.setPosition(185, 484);
    SpritePlay.setTexture(rm.TexturePlay);
    SpritePlay.setPosition(sf::Vector2f(0, 0));
    ready.setString("Get Ready!");
    ready.setFont(rm.font);
    ready.setCharacterSize(30);
    ready.setFillColor(sf::Color::White);
    ready.setPosition(220, 380);
    SpriteLife3.setTexture(rm.texturePacMan);
    SpriteLife2.setTexture(rm.texturePacMan);
    SpriteLife.setTexture(rm.texturePacMan);
    SpriteLife3.setTextureRect(sf::IntRect(0, 0, 32, 32));
    SpriteLife2.setTextureRect(sf::IntRect(0, 0, 32, 32));
    SpriteLife.setTextureRect(sf::IntRect(0, 0, 32, 32));
    SpriteLife3.setPosition(sf::Vector2f(460, 700));
    SpriteLife2.setPosition(sf::Vector2f(490, 700));
    SpriteLife.setPosition(sf::Vector2f(520, 700));
}

PacMan::~PacMan() {
    delete this;
}

void PacMan::Draw(){
    ResourcesManager &rm = ResourcesManager::GetInstance();
    Scene &Window = Scene::GetInstance();

    // si ce n'est pas la fin de la partie on affiche pacman
    if (Window.GetIsEnd()  == false)
        Window.draw(this->GetSprite());
    
    // on affiche le score
    std::ostringstream ss;
    ss << GetScore();
    scoretext.setString("SCORE = " + ss.str());
    Window.draw(scoretext);
    Window.draw(lifetext);

    // on affiche les vies
    SpriteLife3.setTexture(rm.texturePacMan);
    SpriteLife2.setTexture(rm.texturePacMan);
    SpriteLife.setTexture(rm.texturePacMan);
    SpriteLife3.setTextureRect(sf::IntRect(0, 0, 32, 32));
    SpriteLife2.setTextureRect(sf::IntRect(0, 0, 32, 32));
    SpriteLife.setTextureRect(sf::IntRect(0, 0, 32, 32));
    if (life == 3)
    {
        Window.draw(SpriteLife3);
        Window.draw(SpriteLife2);
        Window.draw(SpriteLife);
    }
    else if (life == 2)
    {
        Window.draw(SpriteLife3);
        Window.draw(SpriteLife2);
    }
    else if (life == 1)
    {
        Window.draw(SpriteLife3);
    }
    // si on gagne
    if (Window.GetNbDot() == 0 && Window.GetNbBonus() == 0 && GetLife() != 0)
    {
        //Ecran de victoire (img + text + replay)
        Window.clear(sf::Color(0, 0, 0, 0));
        Window.draw(SpritePlay);
        Window.draw(wintext);
        scoretext.setPosition(230, 404);
        Window.draw(scoretext);
        Window.draw(replay);
        // on arrête les musiques
        rm.pacman_siren.stop();
        rm.ghost_turntoblue.stop();
        // on dit que c'est la fin de la partie
        Window.SetIsEnd(true);
        // si on tape R on rejoue si non le programme se ferme
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            Window.Play();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            Window.close();
    }
    //si on perd
    if ((Window.GetNbDot() != 0 || Window.GetNbBonus() != 0) && GetLife() == 0)
    {
        //Ecran de défaite (img + text + replay)
        Window.clear(sf::Color(0, 0, 0, 0));
        Window.draw(SpritePlay);
        Window.draw(losetext);
        scoretext.setPosition(230, 404);
        Window.draw(scoretext);
        Window.draw(replay);
        // on arrête les musiques
        rm.pacman_siren.stop();
        rm.ghost_turntoblue.stop();
        // on dit que c'est la fin de la partie
        Window.SetIsEnd(true);
        // si on tape R on rejoue si non le programme se ferme
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            Window.Play();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            Window.close();
    }
}

void PacMan::Update(){
    Scene &Window = Scene::GetInstance();
    TimeManager &tm = TimeManager::GetInstance();
    ResourcesManager &rm = ResourcesManager::GetInstance();

    // on joue la musique de début au début du jeu
    if (tm.GetStartedTime() >= 0 && tm.GetStartedTime() < 100 && Window.GetIsEnd() == false)
        rm.pacman_beginning.play();
    // on affiche le texte "Get ready"
    if (tm.GetStartedTime() < 4000)
        Window.draw(ready);
    // au bout de 4 secondes PacMan a le droit de bouger
    if (tm.GetStartedTime() >= 4000 && tm.GetStartedTime() < 5000) {
        SetCanMove(true);
        SetCanMoveUp(true);
        SetCanMoveDown(true);
        SetCanMoveLeft(true);
        SetCanMoveRight(true);
    }
    
    // on met à jour la tuile sur laquelle est pacman
    for (int i = 0; i < 191; i++) {
        if (GetX() < 64 && (Window.tiles[i].x == GetX() - (GetX() % 32) + 32) && (Window.tiles[i].y == GetY() - (GetY() % 32)))
            SetTile(Window.tiles[i]);
        if (GetY() < 64 && (Window.tiles[i].x == GetX() - (GetX() % 32)) && (Window.tiles[i].y == GetY() - (GetY() % 32) + 32))
            SetTile(Window.tiles[i]);
        if (GetX() >= 64 && GetY() >= 64 && (Window.tiles[i].x == GetX() - (GetX() % 32)) && (Window.tiles[i].y == GetY() - (GetY() % 32)))
            SetTile(Window.tiles[i]);
    }
    // on met l'animation
    SetAnimation(GetAnimation().x + 1, GetAnimation().y);
    if(GetAnimation().x * 32 >= 64)
        SetAnimation(0, GetAnimation().y);
    SetTextureRect(GetAnimation().x * 32, GetAnimation().y * 32, 32, 32);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        SetDirection(Left);
        SetAnimation(GetAnimation().x, 0);
        SetCanMove(true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        SetDirection(Right);
        SetAnimation(GetAnimation().x, 1);
        SetCanMove(true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        SetDirection(Up);
        SetAnimation(GetAnimation().x, 2);
        SetCanMove(true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        SetDirection(Down);
        SetAnimation(GetAnimation().x, 3);
        SetCanMove(true);
    }
    // gestion du portal
    if(GetX() <= 0 && GetY() >= 310 && GetY() <= 362 && GetDirection() == Left)
    {
        SetX(576);
        SetY(320);
        SetDirection(Left);
    }
    if(GetX()>= 576 && GetY() >= 310 && GetY() <= 362 && GetDirection() == Right)
    {
        SetX(0);
        SetY(320);
        SetDirection(Right);
    }
    switch(GetDirection())
    {
        case Right:
            if (GetCanMove() == true && GetCanMoveRight() == true)
            {
                Move(GetSpeed(), 0);
                SetCanMoveUp(true);
                SetCanMoveDown(true);
                SetCanMoveLeft(true);
                SetCanMoveRight(true);
            }
            break;
        case Left:
            if (GetCanMove() == true && GetCanMoveLeft() == true)
            {
                Move(-GetSpeed(), 0);
                SetCanMoveUp(true);
                SetCanMoveDown(true);
                SetCanMoveLeft(true);
                SetCanMoveRight(true);
            }
            break;
        case Up:
            if (GetCanMove() == true && GetCanMoveUp() == true)
            {
                Move(0, -GetSpeed());
                SetCanMoveUp(true);
                SetCanMoveDown(true);
                SetCanMoveLeft(true);
                SetCanMoveRight(true);
            }
            break;
        case Down:
            if (GetCanMove() == true && GetCanMoveDown() == true)
            {
                Move(0, GetSpeed());
                SetCanMoveUp(true);
                SetCanMoveDown(true);
                SetCanMoveLeft(true);
                SetCanMoveRight(true);
            }
            break;
    }
    // on préviens tout les observers que pacman à bougé
    for (int i = 0; i < GetObservers().size();  i++) {
        GetObservers()[i]->Notify(this);
    }
}

int PacMan::GetLife() const {
    return this->life;
}

void PacMan::SetLife(int newLife) {
    this->life = newLife;
}

int PacMan::GetScore() const {
    return this->score;
}

void PacMan::SetScore(int newScore){
    this->score = newScore;
}
