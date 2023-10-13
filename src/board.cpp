#include "types.hpp"
#include "constants.hpp"
#include "print.hpp"
#include "board.hpp"

Board::Board() {
    init();
}

void Board::init() {
    using enum Piece;
    for(int i = 0; i < 64; i++) {
        state.squares[i] = static_cast<Piece>(STARTING_POSITION[i]);
    }

    initState({
        .squares = state.squares,
        .nextMove = Color::White,
        .fiftyMoves = 0,
        .castlingRightsWhiteShort = true,
        .castlingRightsWhiteLong = true,
        .castlingRightsBlackShort = true,
        .castlingRightsBlackLong = true,
    }); // yay c++20
};
void Board::initFromFen(std::string_view fen) {

    initState({
        // .squares = state.squares,
        // .nextMove = Color::White,
        // .fiftyMoves = 0,
        // .castlingRightsWhiteShort = true,
        // .castlingRightsWhiteLong = true,
        // .castlingRightsBlackShort = true,
        // .castlingRightsBlackLong = true,
    });
};

void Board::initState(const BoardState& state) {
    // initializing bitboards
    whitePawnsBB    = 0ULL;
    whiteKnightsBB  = 0ULL;
    whiteBishopsBB  = 0ULL;
    whiteRooksBB    = 0ULL;
    whiteQueensBB   = 0ULL;
    whiteKingBB     = 0ULL;
       
    blackPawnsBB    = 0ULL;
    blackKnightsBB  = 0ULL;
    blackBishopsBB  = 0ULL;
    blackRooksBB    = 0ULL;
    blackQueensBB   = 0ULL;
    blackKingBB     = 0ULL;

    whitePiecesBB   = 0ULL;
    blackPiecesBB   = 0ULL;
    occupiedBB      = 0ULL;

    using enum Piece;
    for(int i = 0; i < 64; i++) {
        if(state.squares[i] == WhitePawn)   {   whitePawnsBB   |= (1ULL << i); continue; }
        if(state.squares[i] == BlackPawn)   {   blackPawnsBB   |= (1ULL << i); continue; }
        if(state.squares[i] == WhiteKnight) {   whiteKnightsBB |= (1ULL << i); continue; }
        if(state.squares[i] == BlackKnight) {   blackKnightsBB |= (1ULL << i); continue; }
        if(state.squares[i] == WhiteBishop) {   whiteBishopsBB |= (1ULL << i); continue; }
        if(state.squares[i] == BlackBishop) {   blackBishopsBB |= (1ULL << i); continue; }
        if(state.squares[i] == WhiteRook)   {   whiteRooksBB   |= (1ULL << i); continue; }
        if(state.squares[i] == BlackRook)   {   blackRooksBB   |= (1ULL << i); continue; }
        if(state.squares[i] == WhiteQueen)  {   whiteQueensBB  |= (1ULL << i); continue; }
        if(state.squares[i] == BlackQueen)  {   blackQueensBB  |= (1ULL << i); continue; }
        if(state.squares[i] == WhiteKing)   {   whiteKingBB    |= (1ULL << i); continue; }
        if(state.squares[i] == BlackKing)   {   blackKingBB    |= (1ULL << i); continue; }
    }

    whitePiecesBB = whitePawnsBB | whiteKnightsBB | whiteBishopsBB | whiteRooksBB | whiteQueensBB | whiteKingBB;
    blackPiecesBB = blackPawnsBB | blackKnightsBB | blackBishopsBB | blackRooksBB | blackQueensBB | blackKingBB;

    this->state.nextMove = state.nextMove;
    this->state.castlingRightsWhiteShort = state.castlingRightsWhiteShort;
    this->state.castlingRightsWhiteLong = state.castlingRightsWhiteLong;
    this->state.castlingRightsBlackShort = state.castlingRightsBlackShort;
    this->state.castlingRightsBlackLong = state.castlingRightsBlackLong;
    this->state.croissant = state.croissant;
    this->state.fiftyMoves = state.fiftyMoves;

    evalPieceMaterial();
    DEBUG::printUnicodeBoard(state.squares);
}

int Board::evalPieceMaterial() {
    this->pieceMaterial =  whitePawnsBB.popcount()   * PAWN_VALUE   +
                           whiteKnightsBB.popcount() * KNIGHT_VALUE +
                           whiteBishopsBB.popcount() * BISHOP_VALUE +
                           whiteRooksBB.popcount()   * ROOK_VALUE   +
                           whiteQueensBB.popcount()  * QUEEN_VALUE;
    this->pieceMaterial -= blackPawnsBB.popcount()   * PAWN_VALUE   +
                           blackKnightsBB.popcount() * KNIGHT_VALUE +
                           blackBishopsBB.popcount() * BISHOP_VALUE +
                           blackRooksBB.popcount()   * ROOK_VALUE   +
                           blackQueensBB.popcount()  * QUEEN_VALUE;
    return this->pieceMaterial;
}

char Board::pieceToChar(Piece piece) {
    using enum Piece;
    switch(piece) {
        case BlackPawn:   return 'p'; break;
        case BlackKnight: return 'n'; break;
        case BlackBishop: return 'b'; break;
        case BlackRook:   return 'r'; break;
        case BlackQueen:  return 'q'; break;
        case BlackKing:   return 'k'; break;

        case WhitePawn:   return 'P'; break;
        case WhiteKnight: return 'N'; break;
        case WhiteBishop: return 'B'; break;
        case WhiteRook:   return 'R'; break;
        case WhiteQueen:  return 'Q'; break;
        case WhiteKing:   return 'K'; break;

        case None:        return ' '; break;
        default: throw "should never throw";
    }
}

Color Board::oppColor(Color color) {
    return static_cast<Color>(!static_cast<int>(color));
}

// 
//     char basePieceToChar(BasePiece piece) {
//         using enum BasePiece;
//         switch(piece) {
//             case Pawn:   return 'p'; break;
//             case Knight: return 'n'; break;
//             case Bishop: return 'b'; break;
//             case Rook:   return 'r'; break;
//             case Queen:  return 'q'; break;
//             case King:   return 'k'; break;
//             case None:   return ' '; break;

//             default: throw "should never throw";
//         }
//     }
