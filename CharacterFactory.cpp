#include "CharacterFactory.hh"
#include "Ghost.hh"
#include "PacMan.hh"

CharacterFactory::CharacterFactory() {

}

CharacterFactory::~CharacterFactory() {

}

Character* CharacterFactory::Create(const std::string& Character) {
    if (Character.compare("Blinky") == 0) {
        Ghost* g = new Ghost(288, 256, 0, 0, 32, 32, 73, "Blinky");
        return g;
    }
    if (Character.compare("Pinky") == 0) {
        Ghost* g = new Ghost(288, 320, 64, 0, 32, 32, 192, "Pinky");
        return g;
    }
    if (Character.compare("Inky") == 0) {
        Ghost* g = new Ghost(256, 320, 192, 0, 32, 32, 191, "Inky");
        return g;
    }
    if (Character.compare("Clyde") == 0) {
        Ghost* g = new Ghost(320, 320, 128, 0, 32, 32, 193, "Clyde");
        return g;
    }
    if (Character.compare("PacMan") == 0) {
        PacMan* p = new PacMan();
        return p;
    }
    return NULL;
}
