#pragma once

#include <string>
class Vehicle;

class Item {
public:
    Item(const std::string &name);
    virtual ~Item();

    const std::string& getName() const;
    virtual void use(Vehicle &v) {};

private:
    std::string name;
};