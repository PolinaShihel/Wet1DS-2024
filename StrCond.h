#ifndef WET1_StrCond_H
#define WET1_StrCond_H

class StrCond
{
    int Strength;
    int ID;
public:
    StrCond():Strength(0),ID(0){}
    StrCond(int Strength, int ID): Strength(Strength),ID(ID){}
    StrCond(const StrCond& other) = default;
    StrCond& operator=(const StrCond& other) = default;
    ~StrCond() = default;
    bool operator>(const StrCond& other) const;
    bool operator<(const StrCond& other) const;
    bool operator>=(const StrCond& other) const;
    bool operator<=(const StrCond& other) const;
    bool operator==(const StrCond& other) const;
    operator int() const;
};

#endif //WET1_StrCond_H
