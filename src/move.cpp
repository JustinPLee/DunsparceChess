#include "move.hpp"

namespace dunsparce {
    uint32_t encodeMove(const Move& move) {
        uint32_t encoded{};
        encoded |= (move.source_square << 0);
        encoded |= (move.target_square << 6);
        encoded |= (move.actor << 12);
        encoded |= (move.promoted_piece << 16);
        encoded |= (move.capture_flag << 20);
        encoded |= (move.double_push_flag << 21);
        encoded |= (move.croissant_flag << 22);
        encoded |= (move.castling_flag << 23);
        return encoded; 
    }

    Move decodeMove(uint32_t data) {
        const Square source_square {Square(data & 0x3f)};
        const Square target_square {Square((data & 0xfc0) >> 6)  };
        const Piece actor {Piece((data & 0xf000) >> 12) };
        const Piece promoted_piece { Piece((data & 0xF0000) >> 16) };
        const bool capture_flag {(data & 0x100000) != 0};
        const bool double_push_flag {(data & 0x200000) != 0};
        const bool croissant_flag {(data & 0x400000) != 0};
        const bool castling_flag {(data & 0x800000) != 0};

        return Move{
            .source_square = source_square,
            .target_square = target_square,
            .actor = actor,
            .promoted_piece = promoted_piece,
            .capture_flag = capture_flag,
            .double_push_flag = double_push_flag,
            .croissant_flag = croissant_flag,
            .castling_flag = castling_flag
        };
    }

    std::ostream& operator<<(std::ostream& out, const Move& move) {
        std::cout << "("
                << "From: "            << squareToCoordinates(move.source_square) << ", "
                << "To: "              << squareToCoordinates(move.target_square) << ", "
                << "Piece: "           << pieceToUnicode(move.actor) << ", "
                << "Promotion piece: " << pieceToUnicode(move.promoted_piece) << ", "
                << "Capture: "         << (move.capture_flag ? 'T' : 'F') << ", "
                << "Double push: "     << (move.double_push_flag ? 'T' : 'F') << ", "
                << "Croissant: "       << (move.croissant_flag ? 'T' : 'F') << ", "
                << "Castle: "          << (move.castling_flag ? 'T' : 'F')
                << ")";
        return out;
    }

    bool operator==(const Move& lhs, const Move& rhs) {
        return (
            lhs.source_square == rhs.source_square &&
            lhs.target_square == rhs.target_square &&
            lhs.actor == rhs.actor &&
            lhs.promoted_piece == rhs.promoted_piece &&
            lhs.capture_flag == rhs.capture_flag &&
            lhs.double_push_flag == rhs.double_push_flag &&
            lhs.croissant_flag == rhs.croissant_flag &&
            lhs.castling_flag == rhs.castling_flag
        );
    }
}