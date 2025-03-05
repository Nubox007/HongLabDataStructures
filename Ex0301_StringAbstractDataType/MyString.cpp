#include "MyString.h"

using namespace std;

// 비어 있는 MyString() 생성
MyString::MyString()
{
	str_ = nullptr;
	size_ = 0;
}

// 맨 뒤에 널 캐릭터'\0'가 들어 있는 문자열로부터 초기화
MyString::MyString(const char* init)
{
	// 크기(size_) 결정
	int i = 0;
	while (init[i] != '\0') ++i;
	size_ = i;
	
	// 메모리 할당
	str_ = new char[size_];
	// 데이터 복사
	memcpy(str_, init, size_);
}

// MyString의 다른 instance로부터 초기화
MyString::MyString(const MyString& str)
{
	// 기본 복사 생성자는 포인터 주소만 복사하기 때문에 
	// 소멸시 오류 발생
	// 여기서는 새로 메모리를 할당 받아서 복사
	size_ = str.size_;
	str_ = new char[size_];
	memcpy(str_, str.str_, size_);
}

MyString::MyString(int num) 
{
	str_ = new char[num];
	size_ = num;
}

MyString::~MyString()
{
	if (str_ != nullptr) 
	{
	// 메모리 해제
		delete[] str_;
		size_ = 0;
		str_ = nullptr;
	}
}

bool MyString::IsEmpty()
{
	return Length() == 0;
}

bool MyString::IsEqual(const MyString& str) // 편의상 참조& 사용
{
	if (str.size_ != this->size_) return false;

	// 힌트: str.str_, str.size_ 가능
	for (int i = 0; i < this->size_; ++i) 
		if(this->str_[i] != str.str_[i]) return false;

	return true;
}

int MyString::Length()
{
	return size_;
}

void MyString::Resize(int new_size)
{
	if (new_size != this->size_)
	{
		// 메모리 재할당과 원래 갖고 있던 내용 복사	
		char* temp = new char[new_size];
		memcpy(temp, str_, new_size);

		delete[] this->str_;
		this->str_ = temp;
		this->size_ = new_size;

		delete[] temp;
		temp = nullptr;
	}
	
}

// 인덱스 start위치의 글자부터 num개의 글자로 새로운 문자열 만들기
MyString MyString::Substr(int start, int num)
{
	// 복사할 인덱스: start, start + 1, ... , start + num - 1
	assert(start + num - 1 < this->size_); // 문제를 단순하게 만들기 위해 가정

	MyString temp(num);
	// TODO:
	for (int i = 0; i < num; ++i)
		temp.str_[i] = this->str_[start + i];

	return temp;
}

MyString MyString::Concat(MyString app_str)
{
	int len = this->size_ + app_str.size_;
	MyString temp(len);
	
	// TODO: 
	memcpy(temp.str_, this->str_, this->size_);
	memcpy(&temp.str_[this->size_], app_str.str_, app_str.size_);

	return temp;
}

MyString MyString::Insert(MyString t, int start)
{
	assert(start >= 0);
	assert(start <= this->size_);

	MyString temp(this->size_ + t.size_);

	// TODO:
	for (int i = 0; i < start; ++i)
		temp.str_[i] = this->str_[i];
	for (int i = start; i < start + t.size_; ++i)
		temp.str_[i] = t.str_[i - start];
	for (int i = start + t.size_; i < size_+Length(); ++i)
		temp.str_[i] = this->str_[i - t.size_];


	return temp;
}

int MyString::Find(MyString pat)
{
	//TODO:
	for (int i = 0; i <= Length() - pat.Length(); ++i) 
	{
		for (int j = 0; j < pat.Length(); ++j) 
		{
			if (str_[i + j] != pat.str_[j]) break;
			if (j == pat.Length() - 1) return i;
		}
	}

	return -1;
}

void MyString::Print()
{
	for (int i = 0; i < size_; i++)
		cout << str_[i];
	cout << endl;
}

