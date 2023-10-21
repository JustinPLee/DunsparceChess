/**
 * This file could become very long very quickly.
*/
#include <iostream>
#include <vector>
#include <functional>
#include <string>

#include "../src/types.hpp"
#include "../src/board.hpp"
#include "../src/bitboard.hpp"
#include "../src/constants.hpp"
#include "../src/move.hpp"
#include "../src/utils.hpp"
#include "../src/piece_tables.hpp"
#include "../src/uci.hpp"

namespace dunsparce::tests {

int pray_index = 0;
struct TestCase {
    std::string description;
    std::function<void()> func;
};
std::vector<TestCase> testCases;

class AAAAAAAAAAAAAAAAAA : public std::exception {
    public:
        AAAAAAAAAAAAAAAAAA() {}
};

void pray(bool cond) {
    ++pray_index;
    if(!cond) throw AAAAAAAAAAAAAAAAAA();
}


template <typename F>
void test(const std::string& description, F&& func) {
    testCases.emplace_back(description, func);
}


/*****************
 * 
 * 
 *   Start Here
 * 
 * 
 ****************/


void testBitboardOperations() {
    std::cout << "Bitboard Operations\n";
    std::cout << "===================\n";

    test("basic operations", []() {
        Bitboard bb{15};
        pray(bb == 0b1111);
        pray(bb == Bitboard{0b1111});
        pray(~bb != 0);
    });

    test("basic popcount", []() {
        Bitboard bb{16};
        bb = 15;
        pray(bb.popcount() == 4);
        bb >>= 2;
        pray(bb.popcount() == 2);
        bb = Bitboard(123456789123);
        pray(bb.popcount() == 37);
    });
}


/**
 * TODO: fix exportFen
*/
void testReadFen() {
    std::cout << "Reading/Exporting FEN\n";
    std::cout << "=====================\n";

    test("no pieces", []() {
        std::string fen = "8/8/8/8/8/8/8/8 w KQkq - 0 0";
        Board board{fen};
        pray(board.pieceAt(Square(0)) == Piece(NONE, NULL_COLOR));
        pray(board.pieceAt(Square(24)) == Piece(NONE, NULL_COLOR));
        pray(board.pieceAt(Square(63)) == Piece(NONE, NULL_COLOR));
    });

    test("pieces", []() {
        std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0";
        Board board{fen};
        pray(board.pieceAt(Square(0)) == Piece(ROOK, BLACK));
        pray(board.pieceAt(Square(30)) == Piece(NONE, NULL_COLOR));
        pray(board.pieceAt(Square(61)) == Piece(BISHOP, WHITE));
    });
}

void testMoveRepr() {
    std::cout << "Move Representation\n";
    std::cout << "===================\n";
    
    Square from_square = Square(7);
    Square to_square = Square(63);
    Piece piece = Piece(KING, BLACK);
    Piece captured_piece = Piece(ROOK, WHITE);
    Piece promoted_piece = Piece(PAWN, BLACK);
    bool is_double_push = true;
    bool is_croissant = false;
    bool is_castle = true;
    
    // variables go out of scope, copy values
    test("init 32-bit move stuff", [=]() {
        Move move{MoveType{ from_square, to_square, piece, captured_piece, promoted_piece, is_double_push, is_croissant, is_castle }};
        pray(move.getFromSquare() == from_square);
        pray(move.getToSquare() == to_square);
        pray(move.getPiece() == piece);
        pray(move.getCapturedPiece() == captured_piece);
        pray(move.getPromotedPiece() == promoted_piece);
        pray(move.isDoublePush() == is_double_push);
        pray(move.isCroissant() == is_croissant);
        pray(move.isCastle() == is_castle);
    });

    test("set 32-bit move stuff", [=]() {
        Move move{MoveType{ Square(0), Square(23), Piece(ROOK, WHITE), Piece(BISHOP, BLACK), Piece(PAWN, WHITE), true, true, true }};
        move.setFromSquare(from_square);
        move.setToSquare(to_square);
        move.setPiece(piece);
        move.setCapturedPiece(captured_piece);
        move.setPromotedPiece(promoted_piece);
        move.setIsDoublePush(is_double_push);
        move.setIsCastle(is_castle);
        move.setIsCroissant(is_croissant);
        pray(move.getFromSquare() == from_square);
        pray(move.getToSquare() == to_square);
        pray(move.getPiece() == piece);
        pray(move.getCapturedPiece() == captured_piece);
        pray(move.getPromotedPiece() == promoted_piece);
        pray(move.isDoublePush() == is_double_push);
        pray(move.isCroissant() == is_croissant);
        pray(move.isCastle() == is_castle);
    });
}

void testSanity() {
    std::cout << "Sanity Check\n";
    std::cout << "============\n";
    test("^", [](){});
}

void executeAll() {
    std::vector<std::function<void()>> allTests {
        testBitboardOperations,
        testReadFen,
        testMoveRepr,
        testSanity
    };
    std::cout << "Starting tests...\n\n";
    int total_tests = 0;
    int errors = 0;
    for(const auto& test : allTests) {
        // for each test category, populate testCases with its specific test cases
        test();
        for(const auto& test_case : testCases) {
            bool err_found = false;
            if(test_case.description != "") {
                std::cout << "[Test Case: \"" << test_case.description << "\"] ";
            }
            try {
                test_case.func();
            } catch (AAAAAAAAAAAAAAAAAA& err) {
                std::cout << " ❌" << "  Prayer #" << pray_index << " failed\n";
                ++errors;
                err_found = true;
            };
            if(!err_found) {
                std::cout << "✅\n";
            }
            pray_index = 0;
        }
        ++total_tests;
        // empty the test cases vector for the next test category
        testCases.clear();
        std::cout << "\n";
    };

    if(errors == 0 || total_tests == 0) {
        std::cout << "🎉🎉🎉 All tests cleared! 🎉🎉🎉\n";
    } else {
        std::cout << 100.0*(total_tests-errors)/total_tests << "% of tests cleared.\n";
    }
}

}

int main() {
    dunsparce::tests::executeAll();
    return 0;
}