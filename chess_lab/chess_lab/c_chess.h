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
        // ������������� ��������� ������������ ����� �� �����
        for (int col = 0; col < 8; ++col) {
            for (int row = 0; row < 8; ++row) {
                SetPiece(row, col, ChessPiece(PieceType::Pusto, PieceColor::None));
            }
        }
        // ��������� �����
        for (int row = 0; row < 8; ++row) {
            SetPiece(row, 1, ChessPiece(PieceType::Pawn, PieceColor::Black));
            SetPiece(row, 6, ChessPiece(PieceType::Pawn, PieceColor::White));
        }
        // ��������� ��������� �����

        // ����� ������
        SetPiece(0, 0, ChessPiece(PieceType::Rook, PieceColor::Black));
        SetPiece(1, 0, ChessPiece(PieceType::Knight, PieceColor::Black));
        SetPiece(2, 0, ChessPiece(PieceType::Bishop, PieceColor::Black));
        SetPiece(3, 0, ChessPiece(PieceType::Queen, PieceColor::Black));
        SetPiece(4, 0, ChessPiece(PieceType::King, PieceColor::Black));
        SetPiece(5, 0, ChessPiece(PieceType::Bishop, PieceColor::Black));
        SetPiece(6, 0, ChessPiece(PieceType::Knight, PieceColor::Black));
        SetPiece(7, 0, ChessPiece(PieceType::Rook, PieceColor::Black));

        // ������ ������
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
        ChessPiece* selected_piece = GetPiece(selected_row, selected_col);
        // ���������, ��� ��������� ������ �������� ������
        if (selected_piece->GetType() == PieceType::Pusto || selected_piece->GetColor() == PieceColor::None) {
            // ��� ������ � ��������� ������
            return false;
        }
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
    bool move_bishop(int selected_row, int selected_col, int target_row, int target_col) {
        ChessPiece* selected_piece = GetPiece(selected_row, selected_col);
        if (abs(target_row - selected_row) == abs(target_col - selected_col)) {
            int row_diff = (target_row > selected_row) ? 1 : -1;
            int col_diff = (target_col > selected_col) ? 1 : -1;

            int current_row = selected_row + row_diff;
            int current_col = selected_col + col_diff;

            while (current_row != target_row && current_col != target_col) {
                ChessPiece* current_piece = GetPiece(current_row, current_col);
                if (current_piece->GetColor() != PieceColor::None) {
                    return false;
                }
                current_row += row_diff;
                current_col += col_diff;
            }

            ChessPiece* target_piece = GetPiece(target_row, target_col);
            if (target_piece->GetColor() == PieceColor::None || target_piece->GetColor() != selected_piece->GetColor()) {
                return true;
            }
        }
        return false;
    }
    bool move_pawn(int selected_row, int selected_col, int target_row, int target_col) {
        ChessPiece* selected_piece = GetPiece(selected_row, selected_col);
        int direction = (selected_piece->GetColor() == PieceColor::White) ? -1 : 1;

        if (target_col == selected_col && target_row == selected_row + direction) {
            ChessPiece* target_piece = GetPiece(target_row, target_col);
            if (target_piece->GetColor() == PieceColor::None) {
                SetPiece(target_row, target_col, *selected_piece);
                SetPiece(selected_row, selected_col);
                return true;
            }
        }
        else if (target_col == selected_col && target_row == selected_row + (2 * direction)) {
            ChessPiece* target_piece = GetPiece(target_row, target_col);
            ChessPiece* intermediate_piece = GetPiece(selected_row + direction, selected_col);
            if (target_piece->GetColor() == PieceColor::None && intermediate_piece->GetColor() == PieceColor::None &&
                ((selected_piece->GetColor() == PieceColor::White && selected_row == 1) ||
                    (selected_piece->GetColor() == PieceColor::Black && selected_row == 6))) {
                SetPiece(target_row, target_col, *selected_piece);
                SetPiece(selected_row, selected_col);
                return true;
            }
        }
        else if ((target_col == selected_col + 1 || target_col == selected_col - 1) && target_row == selected_row + direction) {
            ChessPiece* target_piece = GetPiece(target_row, target_col);
            if (target_piece->GetColor() != PieceColor::None && target_piece->GetColor() != selected_piece->GetColor()) {
                return true;
            }
        }
        return false;
    }
    bool move_king(int selected_row, int selected_col, int target_row, int target_col) {
        // ���������, ��� ������� ������ ��������� �� ���������� �� ������ ��� 1 ������ �� ��������� ������
        if (abs(target_row - selected_row) <= 1 && abs(target_col - selected_col) <= 1) {
            // ���������, ��� ������ �� ������ ������ �������
            if (GetPiece(target_row, target_col) == nullptr) {
                // ���������� ����������� ������
                ChessPiece* selected_piece = GetPiece(selected_row, selected_col);
                return true;
            }
        }

        // ��� ���������� ��� ������
        return false;
    }
    bool move_queen(int selected_row, int selected_col, int target_row, int target_col) {
        // ���������, ��� ��������� � �������� ������ ��������� �� ����� �����������, ��������� ��� ���������
        if (selected_row == target_row || selected_col == target_col || abs(target_row - selected_row) == abs(target_col - selected_col)) {
            int delta_row = (target_row - selected_row) > 0 ? 1 : (target_row - selected_row) < 0 ? -1 : 0;
            int delta_col = (target_col - selected_col) > 0 ? 1 : (target_col - selected_col) < 0 ? -1 : 0;

            int current_row = selected_row + delta_row;
            int current_col = selected_col + delta_col;

            // ���������, ��� ���� ��������
            while (current_row != target_row || current_col != target_col) {
                // ���������, ��� ������������� ������ �����
                if (GetPiece(current_row, current_col) != nullptr) {
                    // �� ���� �������� ���� ������ ������
                    return false;
                }

                current_row += delta_row;
                current_col += delta_col;
            }

            // ���������� ����������� ������
            ChessPiece* selected_piece = GetPiece(selected_row, selected_col);
            ChessPiece* target_piece = GetPiece(target_row, target_col);
            // ���� �� ������� ������ ���� ������, ������� �
            if (target_piece != nullptr) {
                delete target_piece;
            }

            return true;
        }

        // ��� ���������� ��� ��������
        return false;
    }
    bool move_knight(int selected_row, int selected_col, int target_row, int target_col) {
        // ��������� ���������� ���� ��� ����
        if ((abs(target_row - selected_row) == 2 && abs(target_col - selected_col) == 1) ||
            (abs(target_row - selected_row) == 1 && abs(target_col - selected_col) == 2)) {
            // ��� ��� ���� �������, ���������� �����������
            ChessPiece* selected_piece = GetPiece(selected_row, selected_col);
            ChessPiece* target_piece = GetPiece(target_row, target_col);
            // ���� �� ������� ������ ���� ������, ������� �
            if (target_piece != nullptr) {
                delete target_piece;
            }
            return true;
        }
        // ��� ���������� ��� ����
        return false;
    }
    bool move_rook(int selected_row, int selected_col, int target_row, int target_col) {
        // ���������, ��� ���� ����� ��������� � �������� ������� ��� ����� ��������
        if (selected_row == target_row || selected_col == target_col) {
            int start_row = selected_row;
            int start_col = selected_col;
            int delta_row = 0;
            int delta_col = 0;
            // ���������� ����������� �������� �����
            if (selected_row == target_row) {
                // �������� �� �����������
                delta_col = (target_col - selected_col) > 0 ? 1 : -1;
            }
            else {
                // �������� �� ���������
                delta_row = (target_row - selected_row) > 0 ? 1 : -1;
            }
            // ���������, ��� ���� ��������
            while (start_row != target_row || start_col != target_col) {
                start_row += delta_row;
                start_col += delta_col;
                // ���������, ��� ������������� ������ �����
                if (GetPiece(start_row, start_col) != nullptr) {
                    // �� ���� ����� ���� ������ ������
                    return false;
                }
            }
            // ���������� ����������� ������
            ChessPiece* selected_piece = GetPiece(selected_row, selected_col);
            ChessPiece* target_piece = GetPiece(target_row, target_col);
            // ���� �� ������� ������ ���� ������, ������� �
            if (target_piece != nullptr) {
                delete target_piece;
            }
            return true;
        }
        // ��� ���������� ��� �����
        return false;
    }
private:
    ChessPiece m_board[8][8];
};