#include "pawn.h"

pawn::pawn(color color)
	: piece(color, color == color::white ? 1 : -1)
{
}