#include "generator.h"
#include <iostream>

std::vector<Chess::Move> Chess::Generator::getDiagonalMoves(Chess::Board& board, int x, int y) {
	std::vector<Chess::Move> moves;
	Chess::Color color = board.getSquare(x, y)->getColor();
	int i = 1;
	while (x + i < 8 && y + i < 8) {
		if (board.getSquare(x + i, y + i)->getColor() == color) {
			break;
		}
		moves.push_back(Chess::Move(x, y, x + i, y + i));
		if (board.getSquare(x + i, y + i)->getColor() != Chess::Color::NONE) {
			break;
		}
		i++;
	}
	i = 1;
	while (x - i >= 0 && y - i >= 0) {
		if (board.getSquare(x - i, y - i)->getColor() == color) {
			break;
		}
		moves.push_back(Chess::Move(x, y, x - i, y - i));
		if (board.getSquare(x - i, y - i)->getColor() != Chess::Color::NONE) {
			break;
		}
		i++;
	}
	i = 1;
	while (x + i < 8 && y - i >= 0) {
		if (board.getSquare(x + i, y - i)->getColor() == color) {
			break;
		}
		moves.push_back(Chess::Move(x, y, x + i, y - i));
		if (board.getSquare(x + i, y - i)->getColor() != Chess::Color::NONE) {
			break;
		}
		i++;
	}
	i = 1;
	while (x - i >= 0 && y + i < 8) {
		if (board.getSquare(x - i, y + i)->getColor() == color) {
			break;
		}
		moves.push_back(Chess::Move(x, y, x - i, y + i));
		if (board.getSquare(x - i, y + i)->getColor() != Chess::Color::NONE) {
			break;
		}
		i++;
	}
	return moves;
}

std::vector<Chess::Move> Chess::Generator::getStraightMoves(Chess::Board& board, int x, int y) {
	std::vector<Chess::Move> moves;
	Chess::Color color = board.getSquare(x, y)->getColor();
	for (int i = x + 1; i < 8; i++) {
		if (board.getSquare(i, y)->getColor() == color) {
			break;
		}
		moves.push_back(Chess::Move(x, y, i, y));
		if (board.getSquare(i, y)->getColor() != Chess::Color::NONE) {
			break;
		}
	}
	for (int i = x - 1; i >= 0; i--) {
		if (board.getSquare(i, y)->getColor() == color) {
			break;
		}
		moves.push_back(Chess::Move(x, y, i, y));
		if (board.getSquare(i, y)->getColor() != Chess::Color::NONE) {
			break;
		}
	}
	for (int i = y + 1; i < 8; i++) {
		if (board.getSquare(x, i)->getColor() == color) {
			break;
		}
		moves.push_back(Chess::Move(x, y, x, i));
		if (board.getSquare(x, i)->getColor() != Chess::Color::NONE) {
			break;
		}
	}
	for (int i = y - 1; i >= 0; i--) {
		if (board.getSquare(x, i)->getColor() == color) {
			break;
		}
		moves.push_back(Chess::Move(x, y, x, i));
		if (board.getSquare(x, i)->getColor() != Chess::Color::NONE) {
			break;
		}
	}
	return moves;
}

std::vector<Chess::Move> Chess::Generator::getQueenMoves(Chess::Board& board, int x, int y) {
	// use the above functions
	std::vector<Chess::Move> moves;
	std::vector<Chess::Move> diagonalMoves = getDiagonalMoves(board, x, y);
	std::vector<Chess::Move> straightMoves = getStraightMoves(board, x, y);
	moves.insert(moves.end(), diagonalMoves.begin(), diagonalMoves.end());
	moves.insert(moves.end(), straightMoves.begin(), straightMoves.end());
	return moves;
}

std::vector<Chess::Move> Chess::Generator::getBishopMoves(Chess::Board& board, int x, int y) {
	std::vector<Chess::Move> moves;
	std::vector<Chess::Move> diagonalMoves = getDiagonalMoves(board, x, y);
	moves.insert(moves.end(), diagonalMoves.begin(), diagonalMoves.end());
	return moves;
}

std::vector<Chess::Move> Chess::Generator::getRookMoves(Chess::Board& board, int x, int y) {
	std::vector<Chess::Move> moves;
	std::vector<Chess::Move> straightMoves = getStraightMoves(board, x, y);
	moves.insert(moves.end(), straightMoves.begin(), straightMoves.end());
	return moves;
}

std::vector<Chess::Move> Chess::Generator::getKnightMoves(Chess::Board& board, int x, int y) {
	std::vector<Chess::Move> moves;
	Chess::Color color = board.getSquare(x, y)->getColor();
	if (x > 1) {
		if (y > 0) {
			if (board.getSquare(x - 2, y - 1)->getColor() != color) {
				moves.push_back(Chess::Move(x, y, x - 2, y - 1));
			}
		}
		if (y < 7) {
			if (board.getSquare(x - 2, y + 1)->getColor() != color) {
				moves.push_back(Chess::Move(x, y, x - 2, y + 1));
			}
		}
	}
	if (x < 6) {
		if (y > 0) {
			if (board.getSquare(x + 2, y - 1)->getColor() != color) {
				moves.push_back(Chess::Move(x, y, x + 2, y - 1));
			}
		}
		if (y < 7) {
			if (board.getSquare(x + 2, y + 1)->getColor() != color) {
				moves.push_back(Chess::Move(x, y, x + 2, y + 1));
			}
		}
	}
	if (y > 1) {
		if (x > 0) {
			if (board.getSquare(x - 1, y - 2)->getColor() != color) {
				moves.push_back(Chess::Move(x, y, x - 1, y - 2));
			}
		}
		if (x < 7) {
			if (board.getSquare(x + 1, y - 2)->getColor() != color) {
				moves.push_back(Chess::Move(x, y, x + 1, y - 2));
			}
		}
	}
	if (y < 6) {
		if (x > 0) {
			if (board.getSquare(x - 1, y + 2)->getColor() != color) {
				moves.push_back(Chess::Move(x, y, x - 1, y + 2));
			}
		}
		if (x < 7) {
			if (board.getSquare(x + 1, y + 2)->getColor() != color) {
				moves.push_back(Chess::Move(x, y, x + 1, y + 2));
			}
		}
	}
	return moves;
}

std::vector<Chess::Move> Chess::Generator::getKingMoves(Chess::Board& board, int x, int y) {
	std::vector<Chess::Move> moves;
	Chess::Color color = board.getSquare(x, y)->getColor();
	if (x > 0) {
		if (board.getSquare(x - 1, y)->getColor() != color) {
			moves.push_back(Chess::Move(x, y, x - 1, y));
		}
		if (y > 0) {
			if (board.getSquare(x - 1, y - 1)->getColor() != color) {
				moves.push_back(Chess::Move(x, y, x - 1, y - 1));
			}
		}
		if (y < 7) {
			if (board.getSquare(x - 1, y + 1)->getColor() != color) {
				moves.push_back(Chess::Move(x, y, x - 1, y + 1));
			}
		}
	}
	if (x < 7) {
		if (board.getSquare(x + 1, y)->getColor() != color) {
			moves.push_back(Chess::Move(x, y, x + 1, y));
		}
		if (y > 0) {
			if (board.getSquare(x + 1, y - 1)->getColor() != color) {
				moves.push_back(Chess::Move(x, y, x + 1, y - 1));
			}
		}
		if (y < 7) {
			if (board.getSquare(x + 1, y + 1)->getColor() != color) {
				moves.push_back(Chess::Move(x, y, x + 1, y + 1));
			}
		}
	}
	if (y > 0) {
		if (board.getSquare(x, y - 1)->getColor() != color) {
			moves.push_back(Chess::Move(x, y, x, y - 1));
		}
	}
	if (y < 7) {
		if (board.getSquare(x, y + 1)->getColor() != color) {
			moves.push_back(Chess::Move(x, y, x, y + 1));
		}
	}
	// castling
	if (color == Chess::Color::WHITE) {
		if (board.getSquare(5, 7)->getPiece() == Chess::Piece::EMPTY && board.getSquare(6, 7)->getPiece() == Chess::Piece::EMPTY) {
			if (board.getSquare(7, 7)->getPiece() == Chess::Piece::ROOK && !board.getSquare(7, 7)->getMoved() && board.getSquare(7, 7)->getColor() == Chess::Color::WHITE) {
				moves.push_back(Chess::Move(4, 7, 6, 7, true));
			}
		}
		if (board.getSquare(3, 7)->getPiece() == Chess::Piece::EMPTY && board.getSquare(2, 7)->getPiece() == Chess::Piece::EMPTY && board.getSquare(1, 7)->getPiece() == Chess::Piece::EMPTY) {
			if (board.getSquare(0, 7)->getPiece() == Chess::Piece::ROOK && !board.getSquare(0, 7)->getMoved() && board.getSquare(0, 7)->getColor() == Chess::Color::WHITE) {
				moves.push_back(Chess::Move(4, 7, 2, 7, true));
			}
		}
	} else {
		if (board.getSquare(5, 0)->getPiece() == Chess::Piece::EMPTY && board.getSquare(6, 0)->getPiece() == Chess::Piece::EMPTY) {
			if (board.getSquare(7, 0)->getPiece() == Chess::Piece::ROOK && !board.getSquare(7, 0)->getMoved() && board.getSquare(7, 0)->getColor() == Chess::Color::BLACK) {
				moves.push_back(Chess::Move(4, 0, 6, 0, true));
			}
		}
		if (board.getSquare(3, 0)->getPiece() == Chess::Piece::EMPTY && board.getSquare(2, 0)->getPiece() == Chess::Piece::EMPTY && board.getSquare(1, 0)->getPiece() == Chess::Piece::EMPTY) {
			if (board.getSquare(0, 0)->getPiece() == Chess::Piece::ROOK && !board.getSquare(0, 0)->getMoved() && board.getSquare(0, 0)->getColor() == Chess::Color::BLACK) {
				moves.push_back(Chess::Move(4, 0, 2, 0, true));
			}
		}
	}
	return moves;
}

std::vector<Chess::Move> Chess::Generator::getPawnMoves(Chess::Board& board, int x, int y) {
	std::vector<Chess::Move> moves;
	Chess::Color color = board.getSquare(x, y)->getColor();
	// including en passant from lastmove
	if (color == Chess::Color::WHITE) {
		if (y == 1) {
			if (board.getSquare(x, y + 1)->getColor() == Chess::Color::NONE && board.getSquare(x, y + 2)->getColor() == Chess::Color::NONE) {
				moves.push_back(Chess::Move(x, y, x, y + 2));
			}
		}
		if (board.getSquare(x, y + 1)->getColor() == Chess::Color::NONE) {
			moves.push_back(Chess::Move(x, y, x, y + 1));
		}
		if (x > 0) {
			if (board.getSquare(x - 1, y + 1)->getColor() == Chess::Color::BLACK) {
				moves.push_back(Chess::Move(x, y, x - 1, y + 1));
			}
		}
		if (x < 7) {
			if (board.getSquare(x + 1, y + 1)->getColor() == Chess::Color::BLACK) {
				moves.push_back(Chess::Move(x, y, x + 1, y + 1));
			}
		}
		if (board.getLastMove().getX2() == x - 1 && board.getLastMove().getY2() == y && board.getLastMove().getY1() == y + 2) {
			moves.push_back(Chess::Move(x, y, x - 1, y + 1, true));
		}
		if (board.getLastMove().getX2() == x + 1 && board.getLastMove().getY2() == y && board.getLastMove().getY1() == y + 2) {
			moves.push_back(Chess::Move(x, y, x + 1, y + 1, true));
		}
	} else {
		if (y == 6) {
			if (board.getSquare(x, y - 1)->getColor() == Chess::Color::NONE && board.getSquare(x, y - 2)->getColor() == Chess::Color::NONE) {
				moves.push_back(Chess::Move(x, y, x, y - 2));
			}
		}
		if (board.getSquare(x, y - 1)->getColor() == Chess::Color::NONE) {
			moves.push_back(Chess::Move(x, y, x, y - 1));
		}
		if (x > 0) {
			if (board.getSquare(x - 1, y - 1)->getColor() == Chess::Color::WHITE) {
				moves.push_back(Chess::Move(x, y, x - 1, y - 1));
			}
		}
		if (x < 7) {
			if (board.getSquare(x + 1, y - 1)->getColor() == Chess::Color::WHITE) {
				moves.push_back(Chess::Move(x, y, x + 1, y - 1));
			}
		}
		if (board.getLastMove().getX2() == x - 1 && board.getLastMove().getY2() == y && board.getLastMove().getY1() == y - 2) {
			moves.push_back(Chess::Move(x, y, x - 1, y - 1, true));
		}
		if (board.getLastMove().getX2() == x + 1 && board.getLastMove().getY2() == y && board.getLastMove().getY1() == y - 2) {
			moves.push_back(Chess::Move(x, y, x + 1, y - 1, true));
		}
	}
	return moves;
}

std::vector<Chess::Move> Chess::Generator::getPseudoLegalMoves(Chess::Board& board) {
	std::vector<Chess::Move> moves = {};
	for (int i = 0; i < 64; i++) {
		int x = i % 8;
		int y = i / 8;
		std::vector<Chess::Move> squareMoves = getPseudoLegalMoves(board, x, y);
		moves.insert(moves.end(), squareMoves.begin(), squareMoves.end());
	}
	return moves;
}

std::vector<Chess::Move> Chess::Generator::getPseudoLegalMoves(Chess::Board& board, int x, int y) {
	std::vector<Chess::Move> moves = {};
	Chess::Square* square = board.getSquare(x, y);
	if (square->getColor() == board.getTurn()) {
		switch (square->getPiece()) {
			case Chess::Piece::PAWN:
				return getPawnMoves(board, x, y);
			case Chess::Piece::KNIGHT:
				return getKnightMoves(board, x, y);
			case Chess::Piece::BISHOP:
				return getBishopMoves(board, x, y);
			case Chess::Piece::ROOK:
				return getRookMoves(board, x, y);
			case Chess::Piece::QUEEN:
				return getQueenMoves(board, x, y);
			case Chess::Piece::KING:
				return getKingMoves(board, x, y);
			default:
				return moves;
		}
	}
	return moves;
}

std::vector<Chess::Move> Chess::Generator::getLegalMoves(Chess::Board& board) {
	std::vector<Chess::Move> moves = getPseudoLegalMoves(board);
	std::vector<Chess::Move> legalMoves = moves;
	return legalMoves;
}