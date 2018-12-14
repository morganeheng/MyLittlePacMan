#ifndef CHARACTERFACTORY_H_
#define CHARACTERFACTORY_H_

#include "Character.hh"
#include <string>

class CharacterFactory {
    public:
        CharacterFactory();
        ~CharacterFactory();
        Character* Create(const std::string&);
};

#endif
