#pragma once
#include"c_chess.h"

namespace chesslab {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;




	ChessBoard back_up_chess;
	/// <summary>
	/// Сводка для chess_board
	/// </summary>
	public ref class chess_board : public System::Windows::Forms::Form
	{
	public:
		chess_board(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
		array<Button^, 2>^ chessBoard;
		
		
		void InitializeComponent()
		{
			this->SuspendLayout();
			// 
			// chess_board
			// 
			array<String^>^ columnLabels = gcnew array<String^>{"A", "B", "C", "D", "E", "F", "G", "H"};
			array<String^>^ rowLabels = gcnew array<String^>{"8", "7", "6", "5", "4", "3", "2", "1"};
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(660, 730);
			this->Size = System::Drawing::Size(730, 780);
			this->Name = L"MMM";
			this->Text = L"Slavic sdai aig";
			this->ResumeLayout(false);
			chessBoard = gcnew array<Button^, 2>(8, 8);
			
			int buttonSize = 50;
			int padding = 40;
			int letters_size = 20;
			for (int row = 0; row < 8; row++)
			{
				for (int col = 0; col < 8; col++)
				{
					//
					if (row == 0)
					{
						Label^ columnLabel = gcnew Label();
						columnLabel->Size = Drawing::Size(letters_size, letters_size);
						columnLabel->Location = Drawing::Point(padding +5 + buttonSize / 4 + col * (buttonSize), 10);
						columnLabel->Text = columnLabels[col];
						columnLabel->TextAlign = ContentAlignment::MiddleCenter;
						Controls->Add(columnLabel);
					}

					if (col == 0)
					{
						Label^ rowLabel = gcnew Label();
						rowLabel->Size = Drawing::Size(letters_size, letters_size);
						rowLabel->Location = Drawing::Point(10, padding + buttonSize / 4  + row * (buttonSize));
						rowLabel->Text = rowLabels[row];
						rowLabel->TextAlign = ContentAlignment::MiddleCenter;
						Controls->Add(rowLabel);
					}
					//
					Button^ button = gcnew Button();
					button->Size = Drawing::Size(buttonSize, buttonSize);
					button->Location = Drawing::Point(padding+col * (buttonSize), padding+row * (buttonSize));
					button->Click += gcnew EventHandler(this, &chess_board::OnButtonClicked);
					if (col>5) {
						if ((row + col) % 2 == 0) { // Light square
							button->BackColor = Drawing::Color::White;

							if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Pawn) {
								button->Text = "♟︎";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Rook) {
								button->Text = "♜";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Knight) {
								button->Text = "♞";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Queen) {
								button->Text = "♛";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Bishop) {
								button->Text = "♝";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::King) {
								button->Text = "♚";
							}


						}
						else { // Dark square
							button->BackColor = Drawing::Color::DarkGray;
							if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Pawn) {
								button->Text = "♟︎";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Rook) {
								button->Text = "♜";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Knight) {
								button->Text = "♞";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Queen) {
								button->Text = "♛";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Bishop) {
								button->Text = "♝";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::King) {
								button->Text = "♚";
							}

						}
					}
					else {
						if ((row + col) % 2 == 0) { // Light square
							button->BackColor = Drawing::Color::White;

							if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Pawn) {
								button->Text = "♙";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Rook) {
								button->Text = "♖";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Knight) {
								button->Text = "♘";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Queen) {
								button->Text = "♕";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Bishop) {
								button->Text = "♗";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::King) {
								button->Text = "♔";
							}


						}
						else { // Dark square
							button->BackColor = Drawing::Color::DarkGray;
							if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Pawn) {
								button->Text = "♙";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Rook) {
								button->Text = "♖";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Knight) {
								button->Text = "♘";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Queen) {
								button->Text = "♕";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::Bishop) {
								button->Text = "♗";
							}
							else if (back_up_chess.GetPiece(row, col)->GetType() == PieceType::King) {
								button->Text = "♔";
							}

						}
					}
					
					Controls->Add(button);
					chessBoard[row, col] = button;
				}
			}
		}

	private:
			Button^ selectedPiece;
			Button^ targetPosition;
			Point selectedPiecePosition;
			Color selectedPieceColor;
			void OnButtonClicked(Object^ sender, EventArgs^ e)
			{
				int sel_row = -1, sel_col = -1,tar_row = -1, tar_col = -1;
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						if (selectedPiece == chessBoard[i, j]) {
							sel_row = i;
							sel_col = j;
							break;
						}
					}
					if (sel_row != -1) {
						break;
					}
				}
				Button^ button = dynamic_cast<Button^>(sender);
				if (selectedPiece == nullptr)
				{
					if (button->Text == "")
					{
						MessageBox::Show("Выберите фигуру для перемещения.");
						return;
					}
					// Сохраняем выбранную кнопку и цвет клетки, с которой взяли фигуру
					selectedPiece = button;
					selectedPiecePosition = button->Location;
					selectedPieceColor = selectedPiece->BackColor;
					selectedPiece->BackColor = Drawing::Color::Green;
				}
				else if (targetPosition == nullptr)
				{
					targetPosition = button;
					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							if (targetPosition == chessBoard[i, j]) {
								tar_row = i;
								tar_col = j;
								break;
							}
						}
						if (tar_row != -1) {
							break;
						}
					}
					if (back_up_chess.do_move(sel_row, sel_col, tar_row,tar_col) == true) {
						Drawing::Color targetPositionColor = button->BackColor;
						// Перемещаем фигуру на новую позицию
						targetPosition->Text = selectedPiece->Text;
						selectedPiece->Text = "";
						// Восстанавливаем цвет предыдущей клетки и устанавливаем новый цвет для целевой клетки
						selectedPiece->BackColor = selectedPieceColor;
						targetPosition->BackColor = targetPositionColor;
						back_up_chess.SetPiece(tar_row, tar_col, *back_up_chess.GetPiece(sel_row, sel_col));
						back_up_chess.SetPiece(sel_row, sel_col);
					}
					else {
						MessageBox::Show("Так нельзя.");
					}
					selectedPiece = nullptr;
					targetPosition = nullptr;
					
				}
			}
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~chess_board()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		
#pragma endregion
	
	};
}
