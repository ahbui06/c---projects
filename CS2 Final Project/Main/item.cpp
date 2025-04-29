#include "Item.h"

using namespace std;

Item::Item(const string &name)
    : name(name)
{ }

Item::~Item() { }

const string& Item::getName() const {
    return name;
}