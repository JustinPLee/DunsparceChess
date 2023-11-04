all:
	g++ -Og -std=c++20 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -fsanitize=undefined,address -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wformat=2 -Wimport -Winvalid-pch -Wlogical-op -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wpacked -Wpointer-arith -Wredundant-decls -Wstack-protector -Wstrict-null-sentinel -Wundef -Wwrite-strings -Wdisabled-optimization -Wstrict-aliasing=2 -Wstrict-overflow=5 -Wunused -Wunused-parameter main.cpp src/board.cpp src/move.cpp src/uci.cpp src/engine/movegen.cpp && ./a.out

