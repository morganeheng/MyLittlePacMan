#include "ItemFactory.hh"
#include "Bonus.hh"
#include "Dot.hh"

ItemFactory::ItemFactory() {

}

ItemFactory::~ItemFactory() {

}

Item* ItemFactory::Create(const std::string& Item, int x, int y, int left, int top, int width, int height) {
    if (Item.compare("Bonus") == 0) {
        Bonus* b = new Bonus(x, y, left, top, width, height);
        return b;
    }
    if (Item.compare("Dot") == 0) {
        Dot* d = new Dot(x, y, left, top, width, height);
        return d;
    }
    return NULL;
}

