#include "StrCond.h"

bool StrCond::operator>(const StrCond& other) const
{
    if (this->Strength > other.Strength) {
        return true;
    }
    if (this->Strength == other.Strength) {
        if (this->ID > other.ID) {
            return true;
        }
    }
    return false;
}

bool StrCond::operator<(const StrCond& other) const
{
    return other > *this;
}

bool StrCond::operator==(const StrCond& other) const
{
    return ((Strength == other.Strength)&&(ID == other.ID));
}

StrCond::operator int() const
{
    return Strength;
}