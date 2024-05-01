#include "userPiece.h"

// TASK 4.2: isRoyal(const Piece*)
// TODO
bool isRoyal(const Piece* piece){
    if (dynamic_cast<const King*>(piece) != nullptr){
        return true;
    }
    return false;
}

// TASK 4.3: Implement any Pawn function(s) here if needed

BooleanMap Pawn::getMoves(const Board &board) const {
    BooleanMap map;
    if (this->isWhite()){
        Vector startVec{0,1};
        if (this->getPosition().rank == _2){
            if (board.piece(startVec + getPosition()) == nullptr){
                // map.cell(startVec + getPosition()) = true;
                if (board.piece(startVec * 2 + getPosition()) == nullptr){
                    map.cell(startVec * 2 + getPosition()) = true;
                }
            }
            map |= PwnBase::getMoves(board);
            return map;
        } else {
            return PwnBase::getMoves(board);
        }
    } else {
        Vector startVec{0,-1};
        if (this->getPosition().rank == _7){
            if (board.piece(startVec + getPosition()) == nullptr){
                // map.cell(startVec + getPosition()) = true;
                if (board.piece(startVec * 2 + getPosition()) == nullptr){
                    map.cell(startVec * 2 + getPosition()) = true;
                }
            }
            map |= PwnBase::getMoves(board);
            return map;
        } else {
            map |= PwnBase::getMoves(board);
            return map;
        }
    }
}