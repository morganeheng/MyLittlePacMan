#ifndef ITEMFACTORY_H_
#define ITEMFACTORY_H_

#include "Item.hh"
#include <string>

class ItemFactory {
    public:
        ItemFactory();
        ~ItemFactory();
        Item* Create(const std::string&, int x, int y, int left, int top, int width, int height);
};

#endif

