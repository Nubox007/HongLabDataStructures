#include "SparseMatrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

SparseMatrix::SparseMatrix(int num_rows, int num_cols, int capacity)
{
	// TODO:
	this->terms_ = new MatrixTerm[capacity];
	this->num_rows_ = num_rows;
	this->num_cols_ = num_cols;
	this->capacity_ = capacity;
	this->num_terms_ = 0;


}

// 복사 생성자 (b를 복사)
SparseMatrix::SparseMatrix(const SparseMatrix& b)
{
	// TODO:

	this->num_rows_ = b.num_rows_;
	this->num_cols_ = b.num_cols_;
	this->capacity_ = b.capacity_;
	this->num_terms_ = b.num_terms_;
	this->terms_ = new MatrixTerm[num_rows_ * num_cols_];
	memcpy(this->terms_, b.terms_ , sizeof(MatrixTerm) * num_terms_);
}

SparseMatrix::~SparseMatrix()
{
	// TODO:
	if (terms_) 
	{
		delete[] this->terms_;
		terms_ = nullptr;
	}
}

void SparseMatrix::SetValue(int row, int col, float value)
{
	if (value == 0.0f) return; // value가 0이 아닌 term만 저장

	// TODO:

	int key = row * this->num_cols_ + col;
	
	int i = 0; //인덱스 값을 밖으로 빼놓고 외부에서 사용한다.
	for (; i < num_terms_; ++i) 
	{
		int key_i = this->terms_[i].col + this->terms_[i].row * this->num_cols_;
		if (key == key_i)
		{
			this->terms_[i].value = value;
			this->terms_[i].col = col;
			this->terms_[i].row = row;
		}
		else if (key_i > key) // 키값보다 클 경우, 탐색을 멈추고 계속 뒤로 밀어주는 작업 수행
			break;
	}

	assert(capacity_ > num_terms_);
	num_terms_++;

	for (int j = num_terms_-1; j > i; --j) 
		terms_[j] = terms_[j - 1];

	this->terms_[i].col = col;
	this->terms_[i].row = row;
	this->terms_[i].value = value;	
}

float SparseMatrix::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	// TODO: key = col + num_cols * row;
	int key = col + row * this->num_cols_;
	for (int i = 0; i < num_terms_; ++i)
	{
		int key_i = terms_[i].col + terms_[i].row * num_cols_;

		if (key == key_i) 
			return terms_[i].value;
		else if (key_i > key) 
			return 0.0f;
	}
	return 0.0f;
}

SparseMatrix SparseMatrix::Transpose()
{
	SparseMatrix temp(num_cols_, num_rows_, capacity_); // num_cols_, num_rows_ 순서 주의

	// TODO:
	for (int r = 0; r < this->num_rows_; ++r)
	{
		for (int c = 0; c < this->num_cols_; ++c)
			temp.SetValue(c,r,this->GetValue(r,c));
	}
	return temp;
}

void SparseMatrix::PrintTerms()
{
	for (int i = 0; i < num_terms_; i++)
		cout << "(" << terms_[i].row
		<< ", " << terms_[i].col
		<< ", " << terms_[i].value
		<< ")" << endl;
}

void SparseMatrix::Print()
{
	for (int r = 0; r < num_rows_; r++)
	{
		for (int c = 0; c < num_cols_; c++)
			cout << GetValue(r, c) << " ";
		cout << endl;
	}
}
bool SparseMatrix::IsSorted()
{
	for (int i = 1; i < (this->num_rows_ * this->num_cols_); ++i)
	{
		if (this->terms_[i - 1].row > this->terms_[i].row ||
			(this->terms_[i - 1].row == this->terms_[i].row &&
				this->terms_[i - 1].col > this->terms_[i].col))
			return false;
	}
	return true;
}
