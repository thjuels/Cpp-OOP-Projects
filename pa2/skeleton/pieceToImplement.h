// TASK 3: Implement the 4 Piece-derived classes here
// All classes will inherit the NamedPiece class 
// and implement the remaining pure virtual functions


// TODO 3.1: Leaper class
template <char N, int F, int R> 
class Leaper: public NamedPiece<N> {
    public:
        Leaper(Color color): NamedPiece<N>(color) {}
        // char name() const override { return N; }
        virtual Piece* clone() const override {
            return new Leaper<N,F,R>(*this);
        }
        virtual BooleanMap getMoves(const Board &board) const override {
            Position curr = this->getPosition();
            Vector vec {F,R};
            if (this->isWhite()){
                if (board.piece(vec + curr) == nullptr){
                    //if nullptr, no piece, so valid move
                    BooleanMap map {};
                    map.cell(vec + curr) = true;
                    // std::cout << "gay1" << std::endl;
                    return map;
                }
                else if (board.piece(vec + curr)->getColor() == BLACK){
                    BooleanMap map {};
                    map.cell(vec + curr) = true;
                    return map;
                } else {
                    BooleanMap map {};
                    return map;
                }
            } 
            else {
                if (board.piece(vec * -1 + curr) == nullptr){
                    //if nullptr, no piece, so valid move
                    BooleanMap map {};
                    map.cell(vec * -1 + curr) = true;
                    return map;
                }
                if (board.piece(vec * -1 + curr)->getColor() == WHITE){
                    BooleanMap map {};
                    map.cell(vec * -1 + curr) = true;
                    return map;
                } else {
                    BooleanMap map {};
                    return map;
                }
            }
        }
        
};


// TODO 3.2: Rider class
template <char N, int F, int R, int RANGE> 
class Rider: public NamedPiece<N> {
    public:
        Rider(Color color): NamedPiece<N>(color) {}
        // char name() const override { return N; }
        virtual BooleanMap getMoves(const Board &board) const override {
            // Vector move_dir{F,R};
            Position pos = this->getPosition();
            BooleanMap map;
            Vector vec; // Define the variable 'vec' outside the conditional statement
            if (Piece::isWhite()) {
                vec = Vector{F, R};  // If 'isWhite()' is true, assign {F, R} to 'vec'
            } else {
                vec = Vector{-F, -R};  // If 'isWhite()' is false, assign {-F, -R} to 'vec'
            }
            for (int i = 1; i <= RANGE; ++i){
                if (!board.piece(vec * i + pos)){
                    //if piece that position is nullptr
                    map.cell(vec * i + pos) = true;
                } else if (this->getColor() != board.piece(vec * i + pos)->getColor()) { // board.piece(vec * i + pos)->isOpponent(*this)
                    // Piece::isOpponent(*board.piece(pos))
                    //we know not nullptr, so now must check if not same color as current piece
                    // check same color
                    //implies take the piece
                    map.cell(vec * i + pos) = true;
                    return map;

                } else {
                    //piece exists but same color
                    return map;
                }
            }
            return map;
        }
        Piece* clone() const override {
            return new Rider<N,F,R,RANGE>(*this);
        }

};

//TASK 3.3
template <char N, typename P1, typename P2> 
class Compound: public NamedPiece<N> {
    public:
        Compound(Color color): NamedPiece<N>(color) {}
        // char name() const override { return N; }
        virtual BooleanMap getMoves(const Board &board) const override {
            P1 p1temp {this->getColor()};
            P2 p2temp {this->getColor()};
            Piece* piece1ptr = p1temp.clone();
            Piece* piece2ptr = p2temp.clone();
            Position curr = this->getPosition();

            Board temp1 = board.getTempBoard(piece1ptr,curr);
            Board temp2 = board.getTempBoard(piece2ptr,curr);

            BooleanMap tempboard1 = piece1ptr->getMoves(temp1);
            BooleanMap tempboard2 = piece2ptr->getMoves(temp2);
            // delete piece1ptr; delete piece2ptr;
            tempboard1 |= tempboard2;
            return tempboard1;
        }
        Piece* clone() const override {
            return new Compound<N,P1,P2>(*this);
        }
};


// TODO 3.4: Divergent class
template <char N, typename M, typename C> 
class Divergent: public NamedPiece<N> {
    public:
        Divergent(Color color): NamedPiece<N>(color) {}
        // char name() const override { return N; }
        virtual BooleanMap getMoves(const Board &board) const override{
            C ctemp {this->getColor()};
            M mtemp {this->getColor()};
            Piece* capPiece = ctemp.clone();
            Piece* movePiece = mtemp.clone();
            Position curr = Piece::getPosition();

            Board temp1 = board.getTempBoard(capPiece, curr);
            Board temp2 = board.getTempBoard(movePiece, curr);

            // const Piece* temppiece1 = temp1.piece(curr);
            // const Piece* temppiece2 = temp2.piece(curr);
            BooleanMap tempboard1 = capPiece->getMoves(temp1);
            BooleanMap tempboard2 = movePiece->getMoves(temp2);
            
            BooleanMap oppMap = board.getOpponentMap(this->isWhite());
            BooleanMap capMoves = tempboard1 &= oppMap;
            BooleanMap moveMoves = tempboard2 &= ~oppMap;
            
            // delete capPiece; delete movePiece;
            moveMoves |= capMoves;
            return moveMoves;
            // M m(this->getColor());
            // C c(this->getColor());

            // m.setPosition(this->getPosition());
            // c.setPosition(this->getPosition());

            // //Board TempBoard1 = board.getTempBoard(&m, this->getPosition());
            // //Board TempBoard2 = board.getTempBoard(&c, this->getPosition());

            // BooleanMap movesm = m.getMoves(board);
            // BooleanMap movesc = c.getMoves(board);

            // BooleanMap opponentmap = board.getOpponentMap(this->getColor());

            // BooleanMap finalmoves;
            // finalmoves = (movesc &= opponentmap) |= (movesm &= (~opponentmap));
            // std::cout<<"amazing11"<<std::endl;
            // return finalmoves;
        }   
        Piece* clone()const override{
            return new Divergent<N,M,C>(*this);
        }
};