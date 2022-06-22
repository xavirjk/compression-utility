#ifndef ENTITY_H_
#define ENTITY_H_

class Entity
{
public:
    Entity(){};
    ~Entity(){};

    virtual bool flagged() const = 0;
    virtual int getFrequency() const = 0;
    virtual void flag() = 0;
    virtual bool findSymbol(char ch) const = 0;
    virtual void print() const = 0;
};
#endif //ENTITY_H_