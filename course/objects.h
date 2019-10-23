#ifndef OBJECTS_H
#define OBJECTS_H

#include <vector>
#include "iterators.h"

using namespace std;

class Object
{
public:
    Object() {}
    ~Object() {}

    virtual bool is_visible() = 0;
};

class Visible_object : public Object
{
public:
    Visible_object() {}
    ~Visible_object() {}

    bool is_visible() override {return true;}
};

class Unvisible_object : public Object
{
public:
    Unvisible_object() {}
    ~Unvisible_object() {}

    bool is_visible() override {return false;}
};

#endif // OBJECTS_H
