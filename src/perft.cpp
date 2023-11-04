#include "perft.hpp"

namespace dunsparce::perft {

Perft::Perft(const Board& board) {
    board_ = board;
}


void Perft::profile(int depth) {
    Timer timer;
    timer.start();
    nodes_ = 0;
    run(depth);
    std::cout << "\nNodes: " << nodes_ << '\n';
    timer.print();
    std::cout << "NPS: " << std::fixed << nodes_/(timer.get_elasped()/1000.0) << '\n';
    std::cout << "Depth: " << depth << '\n';
    board_.print();
}

void Perft::run(int depth) {
    if(depth == 0) {
        ++nodes_;
        return;
    }
    movegen::populateAllPseudoLegalMoves(Both, board_);
    for(size_t i = 0; i < board_.get_moves().size(); ++i) {
        Board::BoardState copy{ board_.copyBoardState() };
        if(!board_.makeMove(board_.get_move(i), move::Type::All, copy)) {
            continue;
        }
        uint64_t cum_nodes{ nodes_ };
        run(depth - 1);
        board_.restoreBoardState(std::move(copy));
        std::cout << utils::squareToCoordinates(board_.get_move(i).get_from_square()) << utils::squareToCoordinates(board_.get_move(i).get_to_square())
                  << " " << utils::pieceToUnicode(board_.get_move(i).get_promotion_piece())
                  << " Nodes: " << (nodes_ - cum_nodes) << '\n';
    }
}

Perft::Timer::Timer(bool start_now) {
    if(start_now) {
        start();
    }
}

void Perft::Timer::start() {
    start_ = std::chrono::high_resolution_clock::now();
}

uint64_t Perft::Timer::get_elasped() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_).count();
}

void Perft::Timer::print() const {
    std::cout << "Time: " << get_elasped() << "ms\n";
}


} // namespace dunsparce::perft