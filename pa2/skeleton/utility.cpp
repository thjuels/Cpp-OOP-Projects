#include <iostream>
#include "utility.h"
using namespace std;

ostream& operator<<(ostream& os, const Position& pos)
{
    os << static_cast<char>(pos.file + 'a') << static_cast<char>(pos.rank + '1');
    return os;
}

// TASK 1: Implement the 6 operator overloading functions of Position, Vector and BooleanMap
// You need to write the full function prototypes and implementations


// TODO 1.1: Position::operator==(const Position&) const
bool Position::operator==(const Position& pos) const {
    return (pos.rank == this->rank && pos.file == this->file);
}

// TODO 1.2: Vector::operator+(const Position&) const
Position Vector::operator+(const Position& pos) const {
    //checks within range
    if (rank + pos.rank > 7 || file + pos.file > 7 || rank + pos.rank < 0 || file + pos.file < 0){ 
        return pos;
    } else {
        return Position{_FILE(file + pos.file),_RANK(rank + pos.rank)};
    }
}

// TODO 1.3: Vector::operator*(int) const
Vector Vector::operator*(int mul) const {
    return Vector{_FILE(mul * file),_RANK(mul * rank)};
    //or
    // if (rank * mul > _8 || file * mul > _H || rank * mul < _1 || file * mul < _A){ 
    //     return pos;
    // } else {
    //     return Position{static_cast<_FILE>(file * mul),static_cast<_RANK>(rank * mul)};
    // }
}

// TODO 1.4: BooleanMap::operator|=(const BooleanMap&)
BooleanMap& BooleanMap::operator|=(const BooleanMap& other) {
    for (int fileInt = 0; fileInt < 8 ; fileInt++ ){
        for (int rankInt = 0; rankInt < 8; rankInt++){
            _FILE file = _FILE(fileInt);
            _RANK rank = _RANK(rankInt);
            if (cells[rank][file] || other.cell(file,rank)){
                //if either sell is true
                cells[rank][file] = true;
            }
        }
    }
    return *this;
}

// TODO 1.5: BooleanMap::operator&=(const BooleanMap&)
BooleanMap& BooleanMap::operator&=(const BooleanMap& other) {
    for (int fileInt = 0; fileInt < 8 ; fileInt++ ){
        for (int rankInt = 0; rankInt < 8; rankInt++){
            _FILE file = _FILE(fileInt);
            _RANK rank = _RANK(rankInt);
            if (cell(file,rank) && other.cell(file,rank)){
                //if either sell is true
                cell(file,rank) = true;
            } else {
                cell(file,rank) = false;
            }
        }
    }
    return *this;
}

// TODO 1.6: BooleanMap::operator~() const
BooleanMap BooleanMap::operator~() const {
    BooleanMap newMap;
    for (int fileInt = 0; fileInt < 8 ; fileInt++ ){
        for (int rankInt = 0; rankInt < 8; rankInt++){
            newMap.cell(_FILE(fileInt),_RANK(rankInt)) = !cell(_FILE(fileInt),_RANK(rankInt));
        }
    }
    return newMap;
}
