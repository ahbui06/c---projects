#pragma once

#include <string>
class Vehicle;

class Item {
public:
    Item(const string &name);
    virtual ~Item();

    const string& getName() const;
    virtual void use(Vehicle &v) {};

private:
    string name;
};