#include <sstream>
#include "types.hpp"
#include "constants.hpp"
#include "print.hpp"
#include "board.hpp"

Board::Board() {
    init(STARTING_FEN);
}

void Board::init(std::string_view fen) {
    for(int i = 0; i < 64; i++) {
        state.squares[i] = Piece::None;
    }
    BoardState state = parseFen(fen);
    this->state = state;

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


    evalPieceMaterial();
    DEBUG::printUnicodeBoard(state.squares);
};

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

Board::BoardState Board::parseFen(std::string_view fen) {
    // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0
    // lowercase is black, uppercase is white

    std::array<Piece, 64> squares;
    Color nextMove;
    bool castlingRightsWhiteShort = 0;
    bool castlingRightsWhiteLong = 0;
    bool castlingRightsBlackShort = 0;
    bool castlingRightsBlackLong = 0;
    int croissant;
    int halfMoves;
    int fullMoves;

    enum Fields {
        squares = 0,
        nextMove,
        castling,
        croissant,
        halfMoves,
        fullMoves = 6
    };
    std::string sfen = std::string(fen);
    std::istringstream ss(sfen);
    std::string field;
    std::array<std::string_view, 7> fields; 

    int index = 0;
    while(ss >> field) {
        fields[index++] = field;
    }

    // pieces
    std::string_view p = fields[Fields::squares];
    int index = 0;
    for(int i = 0; i < p.length(); i++) {
        if('a' <= p[i] <= 'Z') {
            squares[index++] = charToPiece(p[i]);
        } else if('0' <= p[i] - '0' <= '9') {
            index += i;
        } else if(p[i] == '/') {
            continue;
        }
    }
    // nextMove
    switch(fields[Fields::nextMove].front()) {
        case 'w': nextMove = Color::White; break;
        case 'b': nextMove = Color::Black; break;
        default: throw "should never throw";
    }

    // castlingRights;
    for(auto c: fields[Fields::castling]) {
        switch(c) {
            case 'k': castlingRightsBlackShort = true; break;
            case 'q': castlingRightsBlackLong  = true; break;
            case 'K': castlingRightsWhiteShort = true; break;
            case 'Q': castlingRightsBlackShort = true; break;
            case '-': break;
            default: throw "should never throw";
        }
    }
    // croissant
    // get index of piece string
    croissant = fields[Fields::croissant].front() == '-' ? 0
        : std::distance(SQUARE_NAMES.begin(), std::find(SQUARE_NAMES.begin(), SQUARE_NAMES.end(), fields[Fields::croissant].data()));
    // halfMoves
    halfMoves = std::stoi(fields[Fields::halfMoves].data());

    // fullMoves
    fullMoves = std::stoi(fields[Fields::fullMoves].data());

    return {
        squares,
        nextMove,
        castlingRightsWhiteLong,
        castlingRightsWhiteLong,
        castlingRightsBlackShort,
        castlingRightsBlackLong,
        croissant,
        halfMoves,
        fullMoves
    }
}

Color Board::oppColor(Color color) {
    return static_cast<Color>(!static_cast<int>(color));
}
Piece Board::charToPiece(char c) {
    using enum Piece;
    switch(c) {
        case 'p':   return BlackPawn; break;
        case 'n': return BlackKnight; break;
        case 'b': return BlackBishop; break;
        case 'r':   return BlackRook; break;
        case 'q':  return BlackQueen; break;
        case 'k':   return BlackKing; break;

        case 'P':   return WhitePawn; break;
        case 'N': return WhiteKnight; break;
        case 'B': return WhiteBishop; break;
        case 'R':   return WhiteRook; break;
        case 'Q':  return WhiteQueen; break;
        case 'K':   return WhiteKing; break;
        default: throw "should never throw";
    }
}