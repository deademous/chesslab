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
    Black
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

        // Установка пешек
        for (int col = 0; col < 8; ++col) {
            for (int row = 0; row < 8;++row) {
                SetPiece(row, col, ChessPiece(PieceType::Pusto, PieceColor::White));
            }

        }
        for (int col = 0; col < 8; ++col) {
            SetPiece(1, col, ChessPiece(PieceType::Pawn, PieceColor::White));
            SetPiece(6, col, ChessPiece(PieceType::Pawn, PieceColor::Black));

        }

        // Установка остальных фигур

        // Белые фигуры
        SetPiece(0, 0, ChessPiece(PieceType::Rook, PieceColor::White));
        SetPiece(0, 1, ChessPiece(PieceType::Knight, PieceColor::White));
        SetPiece(0, 2, ChessPiece(PieceType::Bishop, PieceColor::White));
        SetPiece(0, 3, ChessPiece(PieceType::Queen, PieceColor::White));
        SetPiece(0, 4, ChessPiece(PieceType::King, PieceColor::White));
        SetPiece(0, 5, ChessPiece(PieceType::Bishop, PieceColor::White));
        SetPiece(0, 6, ChessPiece(PieceType::Knight, PieceColor::White));
        SetPiece(0, 7, ChessPiece(PieceType::Rook, PieceColor::White));

        // Черные фигуры
        SetPiece(7, 0, ChessPiece(PieceType::Rook, PieceColor::Black));
        SetPiece(7, 1, ChessPiece(PieceType::Knight, PieceColor::Black));
        SetPiece(7, 2, ChessPiece(PieceType::Bishop, PieceColor::Black));
        SetPiece(7, 3, ChessPiece(PieceType::Queen, PieceColor::Black));
        SetPiece(7, 4, ChessPiece(PieceType::King, PieceColor::Black));
        SetPiece(7, 5, ChessPiece(PieceType::Bishop, PieceColor::Black));
        SetPiece(7, 6, ChessPiece(PieceType::Knight, PieceColor::Black));
        SetPiece(7, 7, ChessPiece(PieceType::Rook, PieceColor::Black));
    }

    ChessPiece* GetPiece(int row, int col) {
        return &m_board[row][col];
    }
    void SetPiece(int row, int col, const ChessPiece& piece) {
        m_board[row][col] = piece;
    }
    void SetPiece(int row, int col) {
        m_board[row][col] = ChessPiece(PieceType::Pusto, PieceColor::White);
    }

private:
    ChessPiece m_board[8][8];
};
class ChessGame {
public:
    ChessGame();

    void Start();
    void MovePiece(int sourceRow, int sourceCol, int destinationRow, int destinationCol);
    void Restart();

private:
    ChessBoard m_board;
    PieceColor m_currentPlayer;
    std::vector<ChessPiece> m_capturedPieces;

    void SwitchPlayer();
    bool IsMoveValid(int sourceRow, int sourceCol, int destinationRow, int destinationCol);
    void CapturePiece(const ChessPiece& piece);
    void PromotePawn(int row, int col, PieceType newType);
    bool IsInCheck(PieceColor color);
    bool IsCheckmate(PieceColor color);
    bool IsStalemate();
};
