#include "Matrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

Matrix::Matrix(int num_rows, int num_cols)
{
	// TODO:
	float* temp = new float[num_rows * num_cols] {0.0f};
	this->values_ = temp;
	this->num_rows_ = num_rows;
	this->num_cols_ = num_cols;

	temp = nullptr;
}

// 복사 생성자 (b를 복사)
Matrix::Matrix(const Matrix& b)
{
	// TODO:
	this->values_ = b.values_;
	this->num_cols_ = b.num_cols_;
	this->num_rows_ = b.num_rows_;

}

Matrix::~Matrix()
{
	// TODO:
	delete[] this->values_;
	this->num_cols_ = 0;
	this->num_rows_ = 0;
}

void Matrix::SetValue(int row, int col, float value)
{
	// values_[TODO] = value;
	this->values_[col + row * this -> num_cols_] = value;
}

float Matrix::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	return this->values_[col + row * this->num_cols_];
}

Matrix Matrix::Transpose()
{
	Matrix temp(num_cols_, num_rows_); // num_cols_, num_rows_ 순서 주의

	// TODO:
	for (int r = 0; r < num_rows_; ++r) 
	{
		for (int c = 0; c < num_cols_; ++c)
			temp.SetValue(c,r, GetValue(r, c));
	}

	return temp;
}

Matrix Matrix::Add(const Matrix& b)
{
	assert(b.num_cols_ == num_cols_);
	assert(b.num_rows_ == num_rows_);

	// TODO:
	Matrix temp(num_rows_, num_cols_);

	for (int i = 0; i < num_rows_ * num_cols_; ++i) 
	{
		temp.values_[i] = this->values_[i] + b.values_[i];
	}

	return temp;
}

void Matrix::Print()
{
	for (int r = 0; r < num_rows_; r++)
	{
		for (int c = 0; c < num_cols_; c++) 
		{
			cout << GetValue(r, c) << " ";
		}

		cout << endl;
	}
}
