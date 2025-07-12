#pragma once
#include "piece.h"
#include "square.h"
#include "texture_paths.h"

class pawn : public piece
{
public:
	explicit pawn(color color);

	const char* to_string() override;

	const std::vector<square*> get_possible_moves(const int x, const int y, square* const board[8][8]) const override;
};