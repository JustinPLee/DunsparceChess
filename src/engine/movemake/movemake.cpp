#include "movemake.hpp"

#include "../../move.hpp"

namespace dunsparce::movemake {

int makeMove(const move::Move& move, move::MoveType move_type) {
    if(move_type == move::Quiet || move.get_capture_flag()) {

    } else {
        return 0;
    }
}

} // namespace dunsparce::movemake