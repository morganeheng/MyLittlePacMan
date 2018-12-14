#include "Ghost.hh"
#include "TimeManager.hh"
#include "ResourcesManager.hh"
#include "Scene.hh"
#include "Map.hh"

Ghost::Ghost() {
    Scene &Window = Scene::GetInstance();
    SetSpeed(8);
    SetMode(Mode::Corner);
    SetDirection(Up);
    for (int i = 0; i < 212; i++) {
        AddObserver((Map*)Window.GetEntities()[i]);
    }
}

Ghost::Ghost(int x, int y, int left, int top, int width, int height, int tile, std::string name) {
    Scene &Window = Scene::GetInstance();
    ResourcesManager &rm = ResourcesManager::GetInstance();
    SetName(name);
    SetMode(Mode::Corner);
    SetSpeed(8);
    SetDirection(Up);
    SetAnimation((left / 32) - 2, 2);
    SetTexture(rm.textureGhost);
    SetTextureRect(left, top, width, height);
    SetX(x);
    SetY(y);
    SetTile(Window.tiles[tile]);
    // on ajoute les murs de la map comme observer
    for (int i = 0; i < 212; i++) {
        AddObserver((Map*)Window.GetEntities()[i]);
    }
}

Ghost::~Ghost() {
    delete this;
}

void Ghost::Draw(){
    Scene &Window = Scene::GetInstance();
    // si la partie n'est pas terminé on affiche les fantomes
    if (Window.GetIsEnd() == false)
        Window.draw(this->GetSprite());
}

void Ghost::Update(){
    TimeManager &tm = TimeManager::GetInstance();
    Scene &Window = Scene::GetInstance();
    
    // Blinky peut bouger à 4 secondes du début
    if (tm.GetStartedTime() >= 4000 && tm.GetStartedTime() < 5000 && GetName().compare("Blinky") == 0) {
        SetCanMove(true);
        SetCanMoveUp(true);
        SetCanMoveDown(true);
        SetCanMoveLeft(true);
        SetCanMoveRight(true);
    }
    // à 15, 40, 65, 90 secondes du début les fantomes sont en mode chase 
    if (((tm.GetStartedTime() >= 15000 && tm.GetStartedTime() < 16000) ||
         (tm.GetStartedTime() >= 40000 && tm.GetStartedTime() < 41000) ||
         (tm.GetStartedTime() >= 65000 && tm.GetStartedTime() < 66000) ||
          tm.GetStartedTime() >= 90000) && GetIsPrey() == false) {
            SetMode(Mode::Chase);
    }
    // Pinky peut bouger à 7 secondes du début
    if (tm.GetStartedTime() >= 7000 && tm.GetStartedTime() < 8000 && GetName().compare("Pinky") == 0) {
        SetCanMove(true);
        SetCanMoveUp(true);
        SetCanMoveDown(true);
        SetCanMoveLeft(true);
        SetCanMoveRight(true);
    }
    // Blinky peut bouger à 9 secondes du début
    if (tm.GetStartedTime() >= 9000 && tm.GetStartedTime() < 10000 && GetName().compare("Inky") == 0) {
        SetCanMove(true);
        SetCanMoveUp(true);
        SetCanMoveDown(true);
        SetCanMoveLeft(true);
        SetCanMoveRight(true);
    }
    // Blinky peut bouger à 11 secondes du début
    if (tm.GetStartedTime() >= 11000 && tm.GetStartedTime() < 12000 && GetName().compare("Clyde") == 0) {
        SetCanMove(true);
        SetCanMoveUp(true);
        SetCanMoveDown(true);
        SetCanMoveLeft(true);
        SetCanMoveRight(true);
    }
    // à 0, 33, 60, 85 secondes du début les fantomes sont en mode corner 
    if (((tm.GetStartedTime() >= 0 && tm.GetStartedTime() < 14000) ||
         (tm.GetStartedTime() >= 33000 && tm.GetStartedTime() < 34000) ||
         (tm.GetStartedTime() >= 60000 && tm.GetStartedTime() < 61000) ||
         (tm.GetStartedTime() >= 85000 && tm.GetStartedTime() < 86000)) && GetIsPrey() == false) {
            SetMode(Mode::Corner);
    }
    // on fait bouger les fantomes en fonction de leur mode
    if (Window.GetClignote() == 0 && Window.GetIsEnd() == false) {
        if (GetMode() == Mode::Chase || GetMode() == Mode::Corner) {
            if (tm.GetStartedTime() >= 4000 && GetName().compare("Blinky") == 0)
                Chase();
            if (tm.GetStartedTime() >= 7000 && GetName().compare("Pinky") == 0)
                Chase();
            if (tm.GetStartedTime() >= 9000 && GetName().compare("Inky") == 0)
                Chase();
            if (tm.GetStartedTime() >= 11000 && GetName().compare("Clyde") == 0)
                Chase();
        } else {
            if (tm.GetStartedTime() >= 4000 && GetName().compare("Blinky") == 0)
                Flee();
            if (tm.GetStartedTime() >= 7000 && GetName().compare("Pinky") == 0)
                Flee();
            if (tm.GetStartedTime() >= 9000 && GetName().compare("Inky") == 0)
                Flee();
            if (tm.GetStartedTime() >= 11000 && GetName().compare("Clyde") == 0)
                Flee();
        }
    }
    // si le fantome devient une proie
    if (GetIsPrey() == true) {
        // et qu'il se fait manger, on ne verra que ses yeux, si non il sera bleu et blanc
        if (GetIsCatch() == true) {
            if (GetAnimation().x * 32 >= 448)
                SetAnimation(12, GetAnimation().y);
        } else {
            if (GetAnimation().x * 32 >= 384)
                SetAnimation(8, GetAnimation().y);
        }
        // au bout de 10 secondes, il redevient normal
        if (GetTime() + 10000 <= tm.GetStartedTime()) {
            if (GetName().compare("Blinky") == 0)
                SetTextureRect(0, 0, 32, 32);
            if (GetName().compare("Pinky") == 0)
                SetTextureRect(64, 0, 32, 32);
            if (GetName().compare("Inky") == 0)
                SetTextureRect(192, 0, 32, 32);
            if (GetName().compare("Clyde") == 0)
                SetTextureRect(128, 0, 32, 32);
            SetIsPrey(false);
            SetIsCatch(false);
            SetMode(Mode::Chase);
            SetTime(0);
        }
    }
    
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
    // on met l'animation
    SetAnimation(GetAnimation().x + 1, GetAnimation().y);
    SetTextureRect(GetAnimation().x * 32, GetAnimation().y * 32, 32, 32);
    if (GetName().compare("Blinky") == 0) {
        if (GetAnimation().x * 32 >= 32 && GetIsPrey() == false && GetIsCatch() == false)
            SetAnimation(-1, GetAnimation().y);
    }
    if (GetName().compare("Pinky") == 0) {
        if (GetAnimation().x * 32 >= 96 && GetIsPrey() == false && GetIsCatch() == false)
            SetAnimation(1, GetAnimation().y);
    }
    if (GetName().compare("Inky") == 0) {
        if (GetAnimation().x * 32 >= 224 && GetIsPrey() == false && GetIsCatch() == false)
            SetAnimation(5, GetAnimation().y);
    }
    if (GetName().compare("Clyde") == 0) {
        if (GetAnimation().x * 32 >= 160 && GetIsPrey() == false && GetIsCatch() == false)
            SetAnimation(3, GetAnimation().y);
    }

    switch(GetDirection())
    {
        case Right:
            if (GetCanMove() == true && GetCanMoveRight() == true) {
                Move((GetTile().x - GetX()), 0);
                SetAnimation(GetAnimation().x, 1);
                SetCanMoveUp(true);
                SetCanMoveDown(true);
                SetCanMoveLeft(true);
                SetCanMoveRight(true);
            }
            break;
        case Left:
            if (GetCanMove() == true && GetCanMoveLeft() == true) {
                Move((GetTile().x - GetX()), 0);
                SetAnimation(GetAnimation().x, 0);
                SetCanMoveUp(true);
                SetCanMoveDown(true);
                SetCanMoveLeft(true);
                SetCanMoveRight(true);
            }
            break;
        case Up:
            if (GetCanMove() == true && GetCanMoveUp() == true) {
                Move(0 , (GetTile().y - GetY()));
                SetAnimation(GetAnimation().x, 2);
                SetCanMoveUp(true);
                SetCanMoveDown(true);
                SetCanMoveLeft(true);
                SetCanMoveRight(true);
            }
            break;
        case Down:
            if (GetCanMove() == true && GetCanMoveDown() == true) {
                Move(0 , (GetTile().y - GetY()));
                SetAnimation(GetAnimation().x, 3);
                SetCanMoveUp(true);
                SetCanMoveDown(true);
                SetCanMoveLeft(true);
                SetCanMoveRight(true);
            }
            break;
    }
    // on prévient les observers que les fantomes ont bougé
    for (int i = 0; i < GetObservers().size();  i++) {
        GetObservers()[i]->Notify(this);
    }
}

std::string Ghost::GetName() const {
    return this->name;
}

void Ghost::SetName(std::string newName) {
    this->name = newName;
}

bool Ghost::GetIsPrey() const {
    return this->isPrey;
}

void Ghost::SetIsPrey(bool newIsPrey) {
    this->isPrey = newIsPrey;
}

bool Ghost::GetIsCatch() const {
    return this->isCatch;
}

void Ghost::SetIsCatch(bool newIsCatch) {
    this->isCatch = newIsCatch;
}

int Ghost::GetTime() const{
    return this->time;
}

void Ghost::SetTime(int newTime){
    this->time = newTime;
}

void Ghost::Notify(IObservable* IObservable) {
    CheckCollision((PacMan *)IObservable);
}

void Ghost::CheckCollision(PacMan* IObservable) {
    Scene &Window = Scene::GetInstance();
    TimeManager &tm = TimeManager::GetInstance();
    ResourcesManager &rm = ResourcesManager::GetInstance();

    // si ils sont en mode Corner, ils vont se diriger vers leur coin respectif
    // blinky en haut à droite, pinky en haut à gauche, inky en bas à droite, clyde en bas à gauche
    if (GetMode() == Corner) {
        Window.GetPath(15, "pas_blinky");
        Window.GetPath(0, "pas_pinky_up");
        Window.GetPath(0, "pas_pinky_down");
        Window.GetPath(0, "pas_pinky_left");
        Window.GetPath(0, "pas_pinky_right");
        Window.GetPath(190, "pas_inky_up");
        Window.GetPath(190, "pas_inky_down");
        Window.GetPath(190, "pas_inky_left");
        Window.GetPath(190, "pas_inky_right");
        Window.GetPath(174, "pas_clyde");
    } else {
        // si non blinky visera pacman, pinky 3 cases avant pacman en fonction de la direction de pacman,
        // inky 2 cases avant pacman en fonction de la direction de pacman et de blinky et clyde visera pacman ou son coin s'il est trop près de pacman 
        Window.GetPath(IObservable->GetTile().nb_tile, "pas_blinky");
        if (IObservable->GetDirection() == Up) {
            if (IObservable->GetY() - 96 > 0) {
                Window.GetPath(GetTilePinky(IObservable->GetTile().nb_tile, 0, -1), "pas_pinky_up");
            } else {
                Window.GetPath(IObservable->GetTile().nb_tile, "pas_pinky_up");
            }
            Window.GetPath(GetTileInky(IObservable->GetTile().nb_tile, 0, -1, (Character*)IObservable->GetObservers()[IObservable->GetObservers().size() - 4]), "pas_inky_up");
        }
        if (IObservable->GetDirection() == Down) {
            if (GetY() + 96 < 672) {
                Window.GetPath(GetTilePinky(IObservable->GetTile().nb_tile, 0, 1), "pas_pinky_down");
            } else {
                Window.GetPath(IObservable->GetTile().nb_tile, "pas_pinky_down");
            }
            Window.GetPath(GetTileInky(IObservable->GetTile().nb_tile, 0, 1, (Character*)IObservable->GetObservers()[IObservable->GetObservers().size() - 4]), "pas_inky_down");
        }
        if (IObservable->GetDirection() == Left) {
            if (IObservable->GetX() - 96 > 0) {
                Window.GetPath(GetTilePinky(IObservable->GetTile().nb_tile, -1, 0), "pas_pinky_left");
            } else {
                Window.GetPath(IObservable->GetTile().nb_tile, "pas_pinky_left");
            }
            Window.GetPath(GetTileInky(IObservable->GetTile().nb_tile, -1, 0, (Character*)IObservable->GetObservers()[IObservable->GetObservers().size() - 4]), "pas_inky_left");
        }
        if (IObservable->GetDirection() == Right) {
            if (IObservable->GetX() + 96 < 576) {
                Window.GetPath(GetTilePinky(IObservable->GetTile().nb_tile, 1, 0), "pas_pinky_right");
            } else {
                Window.GetPath(IObservable->GetTile().nb_tile, "pas_pinky_right");
            }
            Window.GetPath(GetTileInky(IObservable->GetTile().nb_tile, 1, 0, (Character*)IObservable->GetObservers()[IObservable->GetObservers().size() - 4]), "pas_inky_right");
        }
        Window.GetPath(GetTileClyde(IObservable), "pas_clyde");
    }
    // si le fantome et pacman se cognent
    if (GetSprite().getGlobalBounds().intersects(IObservable->GetSprite().getGlobalBounds()))
    {
        // si le fantome est une proie et qu'il ne s'est pas encore fait mangé
        if (GetIsPrey() == true && GetIsCatch() == false) {
            //on joue le son du fantome qui se fait manger par pacman
            rm.pacman_eatghost.play();
            // on dit qu'il fait manger
            SetIsCatch(true);
            // on augmente le score
            IObservable->SetScore(IObservable->GetScore() + 200);
        }
        // si pacman se fait manger
        else if (GetIsPrey() == false && GetIsCatch() == false) {
            //on joue le son du pacman qui se fait manger par le fantome
            rm.pacman_death.play();
            rm.pacman_siren.stop();
            // on retire une vie
            IObservable->SetLife(IObservable->GetLife() - 1);
            SetIsCatch(false);
            SetIsPrey(false);
            SetTime(0);
            // on replace les personnages à leur place et on continue la partie
            Window.Start();
        }
    }
}

Mode Ghost::GetMode() const {
    return this->mode;
}

void Ghost::SetMode(Mode newMode){
    this->mode = newMode;
}

int Ghost::GetTilePinky(int end, int x, int y) {
	Scene &Window = Scene::GetInstance();
	int currentTile = 191;
    // on vérifie que la 3ème tuiles avant pacman est accessible ou pas
	for (int i = 0; i < 191; i++) {
		if (Window.tiles[i].x == (Window.tiles[end].x + (96 * x)) && Window.tiles[i].y == (Window.tiles[end].y + (96 * y)))
			currentTile = i;
	}
    // si non on regarde si la tuile juste en bas est accessible ou pas
	if (currentTile == 191) {
		for (int i = 0; i < 191; i++) {
			if (Window.tiles[i].x == (Window.tiles[end].x + (128 * x)) && Window.tiles[i].y == (Window.tiles[end].y + (128 * y)))
				currentTile = i;
		}
	}
    // si non on regarde si la tuile juste en haut est accessible ou pas
	if (currentTile == 191) {
		for (int i = 0; i < 191; i++) {
			if (Window.tiles[i].x == (Window.tiles[end].x + (64 * x)) && Window.tiles[i].y == (Window.tiles[end].y + (64 * y)))
				currentTile = i;
		}
	}
    // si non on regarde si la tuile juste à gauche est accessible ou pas
	if (currentTile == 191) {
		for (int i = 0; i < 191; i++) {
			if (Window.tiles[i].x == (Window.tiles[end].x + (96 * x) - (y * 32)) && Window.tiles[i].y == (Window.tiles[end].y + (96 * y) - (x * 32)))
				currentTile = i;
		}
	}
    // si non on regarde si la tuile juste à droite est accessible ou pas
	if (currentTile == 191) {
		for (int i = 0; i < 191; i++) {
			if (Window.tiles[i].x == (Window.tiles[end].x + (96 * x) + (y * 32)) && Window.tiles[i].y == (Window.tiles[end].y + (96 * y) + (x * 32)))
				currentTile = i;
		}
	}
    // on retourne la tuile que pinky doit viser
	return currentTile;
}

int Ghost::GetTileInky(int end, int x, int y, Character* Blinky) {
	Scene &Window = Scene::GetInstance();
	int currentTile = 191;
	if (Blinky->GetDirection() == Up) {
        // on vérifie que la tuile en haut de la 2ème tuiles avant pacman est accessible ou pas
		for (int i = 0; i < 191; i++) {
			if (Window.tiles[i].x == (Window.tiles[end].x + (64 * x)) && Window.tiles[i].y == (Window.tiles[end].y + (64 * y) - 32))
				currentTile = i;
		}
        // si non on regarde si la tuile juste en haut est accessible ou pas
		if (currentTile == 191) {
			for (int i = 0; i < 191; i++) {
				if (Window.tiles[i].x == (Window.tiles[end].x + (64 * x)) && Window.tiles[i].y == (Window.tiles[end].y + (64 * y) - 32) - 32)
					currentTile = i;
			}
		}
        // si non il vise pacman
		if (currentTile == 191)
			currentTile = end;
	}
	if (Blinky->GetDirection() == Down) {
        // on vérifie que la tuile en bas de la 2ème tuiles avant pacman est accessible ou pas
		for (int i = 0; i < 191; i++) {
			if (Window.tiles[i].x == (Window.tiles[end].x + (64 * x)) && Window.tiles[i].y == (Window.tiles[end].y + (64 * y) + 32))
				currentTile = i;
		}
        // si non on regarde si la tuile juste en bas est accessible ou pas
		if (currentTile == 191) {
			for (int i = 0; i < 191; i++) {
				if (Window.tiles[i].x == (Window.tiles[end].x + (64 * x)) && Window.tiles[i].y == (Window.tiles[end].y + (64 * y) + 32) + 32)
					currentTile = i;
			}
		}
        // si non il vise pacman
		if (currentTile == 191)
			currentTile = end;
	}
	if (Blinky->GetDirection() == Left) {
        // on vérifie que la tuile à gauche de la 2ème tuiles avant pacman est accessible ou pas
		for (int i = 0; i < 191; i++) {
			if (Window.tiles[i].x == (Window.tiles[end].x + (64 * x) - 32) && Window.tiles[i].y == (Window.tiles[end].y + (64 * y)))
				currentTile = i;
		}
        // si non on regarde si la tuile juste à gauche est accessible ou pas
		if (currentTile == 191) {
			for (int i = 0; i < 191; i++) {
				if (Window.tiles[i].x == (Window.tiles[end].x + (64 * x) - 32) - 32 && Window.tiles[i].y == (Window.tiles[end].y + (64 * y)))
					currentTile = i;
			}
		}
        // si non il vise pacman
		if (currentTile == 191)
			currentTile = end;
	}
	if (Blinky->GetDirection() == Right) {
        // on vérifie que la tuile à droite de la 2ème tuiles avant pacman est accessible ou pas
		for (int i = 0; i < 191; i++) {
			if (Window.tiles[i].x == (Window.tiles[end].x + (64 * x) + 32) && Window.tiles[i].y == (Window.tiles[end].y + (64 * y)))
				currentTile = i;
		}
        // si non on regarde si la tuile juste à droite est accessible ou pas
		if (currentTile == 191) {
			for (int i = 0; i < 191; i++) {
				if (Window.tiles[i].x == (Window.tiles[end].x + (64 * x) + 32) + 32 && Window.tiles[i].y == (Window.tiles[end].y + (64 * y)))
					currentTile = i;
			}
		}
        // si non il vise pacman
		if (currentTile == 191)
			currentTile = end;
	}
    // on retourne la tuile que inky doit viser
	return currentTile;
}

int Ghost::GetTileClyde(PacMan* IObservable) {
    // si clyde est à 4 tuiles ou moins de pacman il fuit vers son coin, sinon il vise pacman
	if (GetX() <= IObservable->GetX() + 128 ||
        GetX() >= IObservable->GetX() - 128 ||
        GetY() <= IObservable->GetY() + 128 ||
        GetY() >= IObservable->GetY() - 128) {
			return 174;
	} else {
		return IObservable->GetTile().nb_tile;
	}
}

std::vector<int> Ghost::FillPasArray(Ghost* Ghost, int minmax) {
    Scene &Window = Scene::GetInstance();
	std::vector<int> pas_ghost;
    // on initialise le vecteur qui va contenir le nombre de pas du fantome
	for (int i = 0; i < 4; i++) {
		pas_ghost.push_back(minmax);
	}
    // en fonction du fantome et de sa direction on remplit le vecteur avec le nombre de pas des tuiles adjacentes
	if (Ghost->GetName().compare("Blinky") == 0) {
		if (Ghost->GetTile().up_tile != -1)
			pas_ghost[0] = Window.tiles[Ghost->GetTile().up_tile].pas_blinky;
		if (Ghost->GetTile().down_tile != -1)
			pas_ghost[1] = Window.tiles[Ghost->GetTile().down_tile].pas_blinky;
		if (Ghost->GetTile().left_tile != -1)
			pas_ghost[2] = Window.tiles[Ghost->GetTile().left_tile].pas_blinky;
		if (Ghost->GetTile().right_tile != -1)
			pas_ghost[3] = Window.tiles[Ghost->GetTile().right_tile].pas_blinky;
	}
	if (Ghost->GetName().compare("Pinky") == 0) {
		if (Ghost->GetDirection() == Up) {
			if (Ghost->GetTile().up_tile != -1)
				pas_ghost[0] = Window.tiles[Ghost->GetTile().up_tile].pas_pinky_up;
			if (Ghost->GetTile().down_tile != -1)
				pas_ghost[1] = Window.tiles[Ghost->GetTile().down_tile].pas_pinky_up;
			if (Ghost->GetTile().left_tile != -1)
				pas_ghost[2] = Window.tiles[Ghost->GetTile().left_tile].pas_pinky_up;
			if (Ghost->GetTile().right_tile != -1)
				pas_ghost[3] = Window.tiles[Ghost->GetTile().right_tile].pas_pinky_up;
		}
		if (Ghost->GetDirection() == Down) {
			if (Ghost->GetTile().up_tile != -1)
				pas_ghost[0] = Window.tiles[Ghost->GetTile().up_tile].pas_pinky_down;
			if (Ghost->GetTile().down_tile != -1)
				pas_ghost[1] = Window.tiles[Ghost->GetTile().down_tile].pas_pinky_down;
			if (Ghost->GetTile().left_tile != -1)
				pas_ghost[2] = Window.tiles[Ghost->GetTile().left_tile].pas_pinky_down;
			if (Ghost->GetTile().right_tile != -1)
				pas_ghost[3] = Window.tiles[Ghost->GetTile().right_tile].pas_pinky_down;
		}
		if (Ghost->GetDirection() == Left) {
			if (Ghost->GetTile().up_tile != -1)
				pas_ghost[0] = Window.tiles[Ghost->GetTile().up_tile].pas_pinky_left;
			if (Ghost->GetTile().down_tile != -1)
				pas_ghost[1] = Window.tiles[Ghost->GetTile().down_tile].pas_pinky_left;
			if (Ghost->GetTile().left_tile != -1)
				pas_ghost[2] = Window.tiles[Ghost->GetTile().left_tile].pas_pinky_left;
			if (Ghost->GetTile().right_tile != -1)
				pas_ghost[3] = Window.tiles[Ghost->GetTile().right_tile].pas_pinky_left;
		}
		if (Ghost->GetDirection() == Right) {
			if (Ghost->GetTile().up_tile != -1)
				pas_ghost[0] = Window.tiles[Ghost->GetTile().up_tile].pas_pinky_right;
			if (Ghost->GetTile().down_tile != -1)
				pas_ghost[1] = Window.tiles[Ghost->GetTile().down_tile].pas_pinky_right;
			if (Ghost->GetTile().left_tile != -1)
				pas_ghost[2] = Window.tiles[Ghost->GetTile().left_tile].pas_pinky_right;
			if (Ghost->GetTile().right_tile != -1)
				pas_ghost[3] = Window.tiles[Ghost->GetTile().right_tile].pas_pinky_right;
		}
	}
	if (Ghost->GetName().compare("Inky") == 0) {
		if (Ghost->GetDirection() == Up) {
			if (Ghost->GetTile().up_tile != -1)
				pas_ghost[0] = Window.tiles[Ghost->GetTile().up_tile].pas_inky_up;
			if (Ghost->GetTile().down_tile != -1)
				pas_ghost[1] = Window.tiles[Ghost->GetTile().down_tile].pas_inky_up;
			if (Ghost->GetTile().left_tile != -1)
				pas_ghost[2] = Window.tiles[Ghost->GetTile().left_tile].pas_inky_up;
			if (Ghost->GetTile().right_tile != -1)
				pas_ghost[3] = Window.tiles[Ghost->GetTile().right_tile].pas_inky_up;
		}
		if (Ghost->GetDirection() == Down) {
			if (Ghost->GetTile().up_tile != -1)
				pas_ghost[0] = Window.tiles[Ghost->GetTile().up_tile].pas_inky_down;
			if (Ghost->GetTile().down_tile != -1)
				pas_ghost[1] = Window.tiles[Ghost->GetTile().down_tile].pas_inky_down;
			if (Ghost->GetTile().left_tile != -1)
				pas_ghost[2] = Window.tiles[Ghost->GetTile().left_tile].pas_inky_down;
			if (Ghost->GetTile().right_tile != -1)
				pas_ghost[3] = Window.tiles[Ghost->GetTile().right_tile].pas_inky_down;
		}
		if (Ghost->GetDirection() == Left) {
			if (Ghost->GetTile().up_tile != -1)
				pas_ghost[0] = Window.tiles[Ghost->GetTile().up_tile].pas_inky_left;
			if (Ghost->GetTile().down_tile != -1)
				pas_ghost[1] = Window.tiles[Ghost->GetTile().down_tile].pas_inky_left;
			if (Ghost->GetTile().left_tile != -1)
				pas_ghost[2] = Window.tiles[Ghost->GetTile().left_tile].pas_inky_left;
			if (Ghost->GetTile().right_tile != -1)
				pas_ghost[3] = Window.tiles[Ghost->GetTile().right_tile].pas_inky_left;
		}
		if (Ghost->GetDirection() == Right) {
			if (Ghost->GetTile().up_tile != -1)
				pas_ghost[0] = Window.tiles[Ghost->GetTile().up_tile].pas_inky_right;
			if (Ghost->GetTile().down_tile != -1)
				pas_ghost[1] = Window.tiles[Ghost->GetTile().down_tile].pas_inky_right;
			if (Ghost->GetTile().left_tile != -1)
				pas_ghost[2] = Window.tiles[Ghost->GetTile().left_tile].pas_inky_right;
			if (Ghost->GetTile().right_tile != -1)
				pas_ghost[3] = Window.tiles[Ghost->GetTile().right_tile].pas_inky_right;
		}
	}
	if (Ghost->GetName().compare("Clyde") == 0) {
		if (Ghost->GetTile().up_tile != -1)
			pas_ghost[0] = Window.tiles[Ghost->GetTile().up_tile].pas_clyde;
		if (Ghost->GetTile().down_tile != -1)
			pas_ghost[1] = Window.tiles[Ghost->GetTile().down_tile].pas_clyde;
		if (Ghost->GetTile().left_tile != -1)
			pas_ghost[2] = Window.tiles[Ghost->GetTile().left_tile].pas_clyde;
		if (Ghost->GetTile().right_tile != -1)
			pas_ghost[3] = Window.tiles[Ghost->GetTile().right_tile].pas_clyde;
	}
    // on renvoit le vecteur
	return pas_ghost;
}

void Ghost::Chase() {
    Scene &Window = Scene::GetInstance();
    SetTile(Window.tiles[GetTile().nb_tile]);
    // on récupère le vecteur
    std::vector<int> pas_ghost = FillPasArray(this, 100);
	int i;
	int j;
	int min = 99;
	int id = 3;
    
    // on récupère la tuile qui possède le nombre de pas le plus petit
    i = 0;
	while (i < 4) {
		if (pas_ghost[i] < min) {
			j = i + 1;
			if (i == 3)
				j = 3;
			while (j < 4) {
				if (pas_ghost[i] <= pas_ghost[j]) {
					id = i;
					min = pas_ghost[i];
				}
				j = j + 1;
			}
		}
		i = i + 1;
	}
    // on l'assigne au fantome et on change sa direction pour que le fantome aille vers la direction de la tuile
	if (id == 0) {
		SetTile(Window.tiles[GetTile().up_tile]);
		SetDirection(Up);
	} else if (id == 1) {
		SetTile(Window.tiles[GetTile().down_tile]);
		SetDirection(Down);
	} else if (id == 2) {
		SetTile(Window.tiles[GetTile().left_tile]);
		SetDirection(Left);
	} else {
		SetTile(Window.tiles[GetTile().right_tile]);
		SetDirection(Right);
	}
}

void Ghost::Flee() {
    Scene &Window = Scene::GetInstance();
    SetTile(Window.tiles[GetTile().nb_tile]);
    // on récupère le vecteur
    std::vector<int> pas_ghost = FillPasArray(this, -2);
	int i;
	int j;
	int max = -1;
	int id = 3;
    
    // on récupère la tuile qui possède le nombre de pas le plus grand
    i = 0;
	while (i < 4) {
		if (pas_ghost[i] > max) {
			j = i + 1;
			if (i == 3)
				j = 3;
			while (j < 4) {
				if (pas_ghost[i] >= pas_ghost[j]) {
					id = i;
					max = pas_ghost[i];
				}
				j = j + 1;
			}
		}
		i = i + 1;
	}
    // on l'assigne au fantome et on change sa direction pour que le fantome aille vers la direction de la tuile
	if (id == 0) {
		SetTile(Window.tiles[GetTile().up_tile]);
		SetDirection(Up);
	} else if (id == 1) {
		SetTile(Window.tiles[GetTile().down_tile]);
		SetDirection(Down);
	} else if (id == 2) {
		SetTile(Window.tiles[GetTile().left_tile]);
		SetDirection(Left);
	} else {
		SetTile(Window.tiles[GetTile().right_tile]);
		SetDirection(Right);
	}
}
