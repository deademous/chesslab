#pragma once
#include<vector>
enum class PieceType {
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King,
    Pusto
};

enum class PieceColor {
    White,
    Black,
    None
};

class ChessPiece {
public:
    ChessPiece(){}
    ChessPiece(PieceType type, PieceColor color):m_type(type), m_color(color){}

    PieceType GetType() const {
        return m_type;
    }
    PieceColor GetColor() const {
        return m_color;
    }

private:
    PieceType m_type;
    PieceColor m_color;
};

class ChessBoard {
public:
    ChessBoard() {
        // Устанавливаем начальное расположение фигур на доске
        for (int col = 0; col < 8; ++col) {
            for (int row = 0; row < 8; ++row) {
                SetPiece(row, col, ChessPiece(PieceType::Pusto, PieceColor::None));
            }
        }
        // Установка пешек
        for (int row = 0; row < 8; ++row) {
            SetPiece(row, 1, ChessPiece(PieceType::Pawn, PieceColor::Black));
            SetPiece(row, 6, ChessPiece(PieceType::Pawn, PieceColor::White));
        }
        // Установка остальных фигур

        // Белые фигуры
        SetPiece(0, 0, ChessPiece(PieceType::Rook, PieceColor::Black));
        SetPiece(1, 0, ChessPiece(PieceType::Knight, PieceColor::Black));
        SetPiece(2, 0, ChessPiece(PieceType::Bishop, PieceColor::Black));
        SetPiece(3, 0, ChessPiece(PieceType::Queen, PieceColor::Black));
        SetPiece(4, 0, ChessPiece(PieceType::King, PieceColor::Black));
        SetPiece(5, 0, ChessPiece(PieceType::Bishop, PieceColor::Black));
        SetPiece(6, 0, ChessPiece(PieceType::Knight, PieceColor::Black));
        SetPiece(7, 0, ChessPiece(PieceType::Rook, PieceColor::Black));

        // Черные фигуры
        SetPiece(0, 7, ChessPiece(PieceType::Rook, PieceColor::White));
        SetPiece(1, 7, ChessPiece(PieceType::Knight, PieceColor::White));
        SetPiece(2, 7, ChessPiece(PieceType::Bishop, PieceColor::White));
        SetPiece(3, 7, ChessPiece(PieceType::Queen, PieceColor::White));
        SetPiece(4, 7, ChessPiece(PieceType::King, PieceColor::White));
        SetPiece(5, 7, ChessPiece(PieceType::Bishop, PieceColor::White));
        SetPiece(6, 7, ChessPiece(PieceType::Knight, PieceColor::White));
        SetPiece(7, 7, ChessPiece(PieceType::Rook, PieceColor::White));
    }

    ChessPiece* GetPiece(int row, int col) {
        return &m_board[row][col];
    }
    void SetPiece(int row, int col, const ChessPiece& piece) {
        m_board[row][col] = piece;
    }
    void SetPiece(int row, int col) {
        m_board[row][col] = ChessPiece(PieceType::Pusto, PieceColor::None);
    }
    bool do_move(int selected_row, int selected_col, int target_row, int target_col) {
        bool stop = false;
        while (!stop)
        {
            if (turn_white == true) {
                if (m_board[selected_row][selected_col].GetColor() != PieceColor::White) {
                    return false;
                }
            }
            else if (turn_white == false) {
                if (m_board[selected_row][selected_col].GetColor() != PieceColor::Black) {
                    return false;
                }
            }
        }
        if (m_board[target_row][target_col].GetType() == PieceType::King)
            if (m_board[selected_row][selected_col].GetColor() == PieceColor::White)
            {//белые выйграли
                return false;
            }
            else
            {//негерс винс
                return false;
            }

        if (turn_white == true)
            turn_white = false;
        else
            turn_white = true;
        return true;
        ChessPiece* selected_piece = GetPiece(selected_row, selected_col);
        // Проверяем, что выбранная клетка содержит фигуру
        ChessPiece* target_piece = GetPiece(target_row, target_col);
        if (target_piece->GetColor() == selected_piece->GetColor()) {
            return false;
        }
        if (selected_piece->GetType() == PieceType::Pawn) {
            return move_pawn(selected_row, selected_col, target_row, target_col);
        }
        else if (selected_piece->GetType() == PieceType::Rook) {
            return move_rook(selected_row, selected_col, target_row, target_col);
        }
        else if (selected_piece->GetType() == PieceType::Knight) {
            return move_knight(selected_row, selected_col, target_row, target_col);
        }
        else if (selected_piece->GetType() == PieceType::Bishop) {
            return move_bishop(selected_row, selected_col, target_row, target_col);
        }
        else if (selected_piece->GetType() == PieceType::Queen) {
            return move_queen(selected_row, selected_col, target_row, target_col);
        }
        else if (selected_piece->GetType() == PieceType::King) {
            return move_king(selected_row, selected_col, target_row, target_col);
        }
        return false;
    }
    bool move_bishop(int bishopY, int bishopX, int thatY, int thatX) {
        bool invalid = false;

        if (abs(bishopX - thatX) == abs(bishopY - thatY))
        {
            int xIncrement = (thatX - bishopX) / (abs(thatX - bishopX));
            int yIncrement = (thatY - bishopY) / (abs(thatY - bishopY));

            for (int i = 1; i < abs(bishopX - thatX); i++)
            {
                if (m_board[bishopX + xIncrement * i][bishopY + yIncrement * i].GetColor() != PieceColor::None)
                    return false;

            }
        }
        else
            return false;

        if (invalid == false)
        {
            if (turn_white == true) {
                SetPiece(thatY, thatX, ChessPiece(PieceType::Bishop, PieceColor::White));
                SetPiece(bishopY, bishopX);
            }
            else {
                SetPiece(thatY, thatX, ChessPiece(PieceType::Bishop, PieceColor::Black));
                SetPiece(bishopY, bishopX);
            }
            
            return true;
        }
        else
        {
            return false;
        }
    }
    bool move_pawn(int pawnY, int pawnX, int thatY, int thatX) {
        bool invalid = false;
        if (m_board[pawnY][pawnX].GetColor() == PieceColor::White)
        {

            if (pawnX == thatX && thatY == pawnY + 1 && m_board[thatY][thatX].GetColor() == PieceColor::None)
            {
                if (turn_white == true) {
                    SetPiece(thatY, thatX, ChessPiece(PieceType::Pawn, PieceColor::White));
                    SetPiece(pawnY, pawnX);
                }
                else {
                    SetPiece(thatY, thatX, ChessPiece(PieceType::Pawn, PieceColor::Black));
                    SetPiece(pawnY, pawnX);
                }
                return true;
            }
            else
                if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY + 1 == thatY && m_board[thatY][thatX].GetColor() == PieceColor::Black)
                {
                    if (turn_white == true) {
                        SetPiece(thatY, thatX, ChessPiece(PieceType::Pawn, PieceColor::White));
                        SetPiece(pawnY, pawnX);
                    }
                    else {
                        SetPiece(thatY, thatX, ChessPiece(PieceType::Pawn, PieceColor::Black));
                        SetPiece(pawnY, pawnX);
                    }
                    return true;
                }
                else
                    return false;
        }
        else
            if (m_board[pawnY][pawnX].GetColor() == PieceColor::Black)
            {
                if (pawnX == thatX && thatY == pawnY - 1 && m_board[thatY][thatX].GetColor() == PieceColor::None)
                {
                    if (turn_white == true) {
                        SetPiece(thatY, thatX, ChessPiece(PieceType::Pawn, PieceColor::White));
                        SetPiece(pawnY, pawnX);
                    }
                    else {
                        SetPiece(thatY, thatX, ChessPiece(PieceType::Pawn, PieceColor::Black));
                        SetPiece(pawnY, pawnX);
                    }
                    return true;
                }
                else
                    if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY - 1 == thatY && m_board[thatY][thatX].GetColor() == PieceColor::White)
                    {
                        if (turn_white == true) {
                            SetPiece(thatY, thatX, ChessPiece(PieceType::Pawn, PieceColor::White));
                            SetPiece(pawnY, pawnX);
                        }
                        else {
                            SetPiece(thatY, thatX, ChessPiece(PieceType::Pawn, PieceColor::Black));
                            SetPiece(pawnY, pawnX);
                        }
                        return true;
                    }
                    else
                        return false;
            }
            else
                return false;
    }
    bool move_king(int selected_row, int selected_col, int target_row, int target_col) {
        if (abs(selected_row - target_row) <= 1)
            if (abs(selected_col - target_col) <= 1)
            {
                if (turn_white == true) {
                    SetPiece(target_row, target_col, ChessPiece(PieceType::King, PieceColor::White));
                    SetPiece(selected_row, selected_col);
                }
                else {
                    SetPiece(target_row, target_col, ChessPiece(PieceType::King, PieceColor::Black));
                    SetPiece(selected_row, selected_col);
                }
                
                return true;
            }
            else return false;
        else return false;
    }
    bool move_queen(int queenY, int queenX, int thatY, int thatX) {
        int yIncrement;
        int xIncrement;
        bool invalid = false;

        if (queenX != thatX || queenY != thatY)
	{

		if (queenX == thatX)
		{
			yIncrement = (thatY - queenY) / (abs(thatY - queenY));
			for (int i = queenY + yIncrement; i != thatY; i += yIncrement)
			{

				if (m_board[thatX][i].GetColor() != PieceColor::None)
					return false;

			}
		}
		else
			if (queenY == thatY)
			{

				xIncrement = (thatX - queenX) / (abs(thatX - queenX));
				for (int i = queenX + xIncrement; i != thatX; i += xIncrement)
				{
					if (m_board[i][thatY].GetColor() != PieceColor::None)
						return false;
				}
			}
			else
				if (abs(queenX - thatX) == abs(queenY - thatY))
				{
					xIncrement = (thatX - queenX) / (abs(thatX - queenX));
					yIncrement = (thatY - queenY) / (abs(thatY - queenY));

					for (int i = 1; i < abs(queenX - thatX); i++)
					{
						if (m_board[queenX + xIncrement*i][queenY + yIncrement*i].GetColor() != PieceColor::None)
							return false;

					}
				}
				else
					return false;
		//if()
	}



	if (invalid == false)
	{
        if (turn_white == true) {
            SetPiece(thatY, thatX, ChessPiece(PieceType::Queen, PieceColor::White));
            SetPiece(queenY, queenX);
        }
        else {
            SetPiece(thatY, thatX, ChessPiece(PieceType::Queen, PieceColor::Black));
            SetPiece(queenY, queenX);
        }
       
		return true;
	}
	else
	{
		return false;
	}
}
    bool move_knight(int knightY, int knightX, int thatY, int thatX) {
        if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) || (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2))
        {
            if (turn_white == true) {
                SetPiece(thatY, thatX, ChessPiece(PieceType::Knight, PieceColor::White));
                SetPiece(knightY, knightX);
            }
            else {
                SetPiece(thatY, thatX, ChessPiece(PieceType::Knight, PieceColor::Black));
                SetPiece(knightY, knightX);
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    bool move_rook(int rookY, int rookX, int thatY, int thatX) {
        bool invalid = false;
        if (rookX != thatX || rookY != thatY)
        {

            if (rookX == thatX)
            {
                int yIncrement = (thatY - rookY) / (abs(thatY - rookY));
                for (int i = rookY + yIncrement; i != thatY; i += yIncrement)
                {

                    if (m_board[thatX][i].GetColor() != PieceColor::None)
                        return false;

                }
            }
            else
                if (rookY == thatY)
                {

                    int xIncrement = (thatX - rookX) / (abs(thatX - rookX));
                    for (int i = rookX + xIncrement; i != thatX; i += xIncrement)
                    {
                        if (m_board[i][thatY].GetColor() != PieceColor::None)
                            return false;
                    }
                }
                else
                    return false;
        }
        if (invalid == false)
        {
            if (turn_white == true) {
                SetPiece(thatY, thatX, ChessPiece(PieceType::Rook, PieceColor::White));
                SetPiece(rookY, rookX);
            }
            else {
                SetPiece(thatY, thatX, ChessPiece(PieceType::Rook, PieceColor::Black));
                SetPiece(rookY, rookX);
            }
            return true;
        }
        else
        {//Return some erorr or something. Probably return false;
            return false;
        }
    }
private:
    ChessPiece m_board[8][8];
    bool turn_white = true;
};