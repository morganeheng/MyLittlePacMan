#ifndef ABSTRACTENTITY_H_
#define ABSTRACTENTITY_H_

class AbstractEntity {
    public:
        AbstractEntity();
        virtual ~AbstractEntity();
        virtual void Draw() = 0;
        virtual void Update() = 0;
};

#endif
