#include "board.hpp"

namespace dunsparce {
    Board::Board() {

    }

    Board::Board(std::string_view fen) : state{parseFen(fen)}, fen_{std::string{fen}} {
        move_list_.reserve(256);
    }

    void Board::clear() {
        state.pieces.fill(bits::u64Zero);
        state.occupancies.fill(bits::u64Zero);
        move_list_.clear();
    }

    void Board::printMoves() const {
        for(size_t i = 0; i < move_list_.size(); ++i) {
            if(move_list_[i] == NullMove) continue;
            std::cout << "Move #" << i+1 << ": " << move_list_[i] << '\n';
        }
    }

    void Board::reversePov() {
        pov_ = Color(pov_^1);
    }

    void Board::pprint() const {
        if(pov_ == White) {
            for(int rank = 0; rank < 8; ++rank) {
                for(int file = 0; file < 8; ++file) {
                    if(file == 0) std::cout << "  " << 8-rank;
                    std::string piece_repr = ".";
                    for(int i = 0; i < NPieces; ++i) {
                        if(state.pieces[i] & bits::oneBitMask(index_of(rank, file))) {
                            piece_repr = pieceToUnicode(Piece{i});
                            break;
                        }
                    }
                    std::cout << " " << piece_repr;
                }
                std::cout << '\n';
            }
            std::cout << "    a b c d e f g h\n\n";
        }
        std::cout << " FEN: " << fen_ << '\n';
        std::cout << " Side to move: " << ((state.side == White) ? "White" : "Black") << '\n';
        std::cout << " Croissant square: " << ((state.croissant != NullSquare) ? squareToCoordinates(state.croissant) : "Null") << '\n';
        std::cout << " Castling: "   << ((state.castling & tables::castling::wk)  ? 'K' : '-')
                                    << ((state.castling & tables::castling::wq)  ? 'Q' : '-')
                                    << ((state.castling & tables::castling::bk)  ? 'k' : '-')
                                    << ((state.castling & tables::castling::bq)  ? 'q' : '-');
        std::cout << "\n\n";
    }

    void Board::addMove(const Move& move) {
        move_list_.push_back(move);
    }
    void Board::addMove(Move&& move) {
        move_list_.push_back(std::move(move));
    }
    Board::BoardState Board::parseFen(std::string_view fen) {
        Board::BoardState state{};
        state.pieces.fill(bits::u64Zero);
        state.occupancies.fill(bits::u64Zero);

        std::string fen_s {fen.cbegin(), fen.cend()};

        std::vector<std::string> fields;
        std::istringstream ss(fen_s);
        std::string value;
        while(ss >> value) {
            fields.push_back(value);
        }

        std::string piece_str {fields[0]};
        int square_idx{};
        for(size_t idx = 0; idx < piece_str.length(); ++idx) {
            std::cout << piece_str[idx] << "\n";
            if(std::isalpha(piece_str[idx])) {
                const Piece piece {charToPiece(piece_str[idx])};
                state.pieces[piece] |= bits::oneBitMask(square_idx);
                state.occupancies[color_of(piece)] |= bits::oneBitMask(square_idx);
                ++square_idx;
            } else if(std::isdigit(piece_str[idx])) {
                square_idx += piece_str[idx] - '0';
            }
        }

        std::string castling {fields[2]};
        for(auto c: castling) {
            if(c == 'K') {
                state.castling |= tables::castling::wk;
            } else if(c == 'Q') {
                state.castling |= tables::castling::wq;
            } else if(c == 'k') {
                state.castling |= tables::castling::bk;
            } else if(c == 'q') {
                state.castling |= tables::castling::bq;
            }
        }

        if(fields[1] == "w") {
            state.side = White; 
        } else {
            state.side = Black;
        }

        std::string croissant {fields[3]};
        if(croissant != "-") {
            state.croissant = static_cast<Square>(index_of(8 - (croissant[1] - '0'), croissant[0] - 'a'));
        } else {
            state.croissant = NullSquare;
        }

        state.occupancies[Both] = (state.occupancies[Black] | state.occupancies[White]);
        return state;
    }
    Board::BoardState Board::exportFen() const {
        return {};
    }
}