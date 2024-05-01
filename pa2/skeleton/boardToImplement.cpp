#include <iostream>
#include "board.h"
#include "piece.h"
using namespace std;

/**
 * TASK 2.1: Board copy constructor
*/
Board::Board(const Board& board)
{
    // TODO
    for (int fileInt = 0; fileInt < 8 ; fileInt++ ){
        for (int rankInt = 0; rankInt < 8; rankInt++){
            if (board.piece(_FILE(fileInt),_RANK(rankInt))) {
                piece(_FILE(fileInt),_RANK(rankInt)) = board.piece(_FILE(fileInt),_RANK(rankInt))->clone();
            } else {
                piece(_FILE(fileInt),_RANK(rankInt)) = nullptr;
            }
        }
    }
    isWhiteTurn = board.isWhiteTurn;
    moveMap = board.moveMap;
    // cout << "board1" << endl;
    if (board.selectedPiece){
        //in already copied array in current object, find object in same location
        selectedPiece = piece(board.selectedPiece->getPosition());
    } else {
        selectedPiece = nullptr;
    }
    // cout << "board2" << endl;
    if (board.royalPieces[0]){
        //in already copied array in current object, find object in same location
        royalPieces[0] = piece(board.royalPieces[0]->getPosition());
    } else {
        royalPieces[0] = nullptr;
    }
    if (board.royalPieces[1]){
        //in already copied array in current object, find object in same location
        royalPieces[1] = piece(board.royalPieces[1]->getPosition());
    } else {
        royalPieces[1] = nullptr;
    }
    // cout << "board3" << endl;
}

/**
 * TASK 2.2: Board destructor
*/
Board::~Board() 
{
    // TODO
    for (int fileInt = 0; fileInt < 8 ; fileInt++ ){
        for (int rankInt = 0; rankInt < 8; rankInt++){
            delete pieces[rankInt][fileInt];
        }
    }
    // cout << "board4" << endl;
}

/**
 * TASK 5.1: Board::move(const Position&)
*/
void Board::move(const Position& destPos)
{
    // Safeguard against misusage of move()
    if (!selectedPiece) {
        cout << "ERROR: Piece not selected, cannot call move()" << endl;
        return;
    }

    // TODO
    Piece* destp = piece(destPos);

    if (piece(destPos)){
        delete destp;
        piece(destPos) = nullptr;
    }
        piece(destPos) = selectedPiece;


        Position pos = selectedPiece->getPosition();
        piece(pos) = nullptr;
        // cout << selectedPiece->getPosition() << endl;
        // cout << "gay1" <<endl;
        selectedPiece->setPosition(destPos);
        // cout << selectedPiece->getPosition() << endl;
        // cout << royalPieces[isWhiteTurn]->getPosition() << endl;
        
        isWhiteTurn = !isWhiteTurn;
        // selectedPiece = piece(destPos);

//     delete piece(destPos);
//     piece(destPos) = nullptr;

//     Piece *p = selectedPiece->clone();
//     Position pos = selectedPiece->getPosition();
//     bool royal = false;
//     if (royalPieces[isWhiteTurn]){
//         if (pos == royalPieces[isWhiteTurn]->getPosition()){
//             royal = 1;
//         }
//     }

//     if (royal){
//         royalPieces[isWhiteTurn] = nullptr;
//     }

    // addPiece(p,destPos);
//     selectedPiece = p;
//     delete piece(pos);
//     piece(pos) = nullptr;
//     if (royal)
//         royalPieces[isWhiteTurn] = p;
//     isWhiteTurn = !isWhiteTurn;


}

/**
 * TASK 5.2: Board::getAttackingMap() const
*/
BooleanMap Board::getAttackingMap() const
{
    // TODO
    BooleanMap map;
    // BooleanMap attackMap;
    for (int fileInt = 0; fileInt < 8 ; fileInt++ ){
        for (int rankInt = 0; rankInt < 8; rankInt++){
            if (piece(_FILE(fileInt), _RANK(rankInt)) && piece(_FILE(fileInt), _RANK(rankInt))->isWhite() == isWhiteTurn){
                // attackMap = piece(_FILE(fileInt), _RANK(rankInt))->getMoves(*this) &= getOpponentMap(isWhiteTurn);
                // map |= attackMap;
                BooleanMap moves = piece(_FILE(fileInt), _RANK(rankInt))->getMoves(*this);
                moves &= getOpponentMap(isWhiteTurn);
                map |= moves;
                
            }
        }
    }
    return map;
}

/**
 * TASK 5.3: Board::validateMoveMap()
*/
void Board::validateMoveMap()
{

    // TODO
    // cout << "validate" << endl;
    if (royalPieces[isWhiteTurn]==nullptr) return;
    // moveMap = selectedPiece->getMoves(*this);
    for (int fileInt = 0; fileInt < 8 ; fileInt++ ){
        for (int rankInt = 0; rankInt < 8; rankInt++){
            Position pos = Position{_FILE(fileInt),_RANK(rankInt)};

            if (moveMap.cell(pos)){ //possible move location
                Board temp {*this};
                temp.move(pos);
                // cout << "gay1" << endl;
                Piece* curKing = temp.royalPieces[isWhiteTurn];
                // cout << "gay2" << endl;
                // cout << curking->getPosition() << endl;
                BooleanMap attackmap = temp.getAttackingMap();
            

                // cout << "gay3" << endl;
                if (attackmap.cell(curKing->getPosition()) == true){ //attackmap.cell(curking->getPosition()) == true
                    moveMap.cell(pos) = false;
                } 
                // cout << "gay3" << endl;

            }
        }
    }
    // cout << "end validate" << endl;
}

