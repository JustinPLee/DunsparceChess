all:

debug:
	g++ -Og -Wall --std=c++20 main.cpp src/board.cpp src/move.cpp src/uci.cpp src/utils.cpp src/engine/movegen/attacks.cpp src/engine/movegen/magic.cpp src/engine/movegen/movegen.cpp src/timer.cpp src/perft.cpp

clang:
	clang -Og -Wall --std=c++20 main.cpp src/board.cpp src/move.cpp src/uci.cpp src/utils.cpp src/engine/movegen/attacks.cpp src/engine/movegen/magic.cpp src/engine/movegen/movegen.cpp src/timer.cpp src/perft.cpp
