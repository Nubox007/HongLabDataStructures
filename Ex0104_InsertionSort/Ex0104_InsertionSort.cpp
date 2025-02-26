#include <iostream>
#include <chrono>
using namespace std;

bool CheckSorted(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (arr[i] > arr[i + 1])
			return false;
	}

	return true;
}

void Print(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}
void InsertionSort(int* arr, int size) 
{
	for (int i = 1; i < size; ++i) 
	{
		if (arr[i] < arr[i - 1]) 
		{
			int key = arr[i];
			for (int j = i; j >= 0; j--) 
			{
				if (key > arr[j - 1] || j == 0)
				{
					arr[j] = key;
					break;
				}
				arr[j] = arr[j - 1];
			}

		}
	}
}
int main()
{
	// 오른쪽으로 하나씩 밀기 (삽입 정렬의 중간 단계)
	/*
	{
		int arr[] = { 1, 2, 4, 5, 3, 6 };
		int n = sizeof(arr) / sizeof(arr[0]);

		Print(arr, n);

		// i = 4인 경우에 대해서 구현
		int i = 4;
		int temp = arr[i];
		for (i ; i >= 1 ; --i)
		{
			// TODO:
			if (temp > arr[i - 1]) 
			{
				arr[i] = temp;
				break;
			}
			arr[i] = arr[i - 1];		

			Print(arr, n);
		}

		Print(arr, n);
		cout << endl;
	}


	*/


	int arr[] = { 8, 3, 2, 5, 1, 2 };
	int arr1[] = { 6, 5, 4, 3, 2, 1 }; // Worst
	int arr2[] = { 1, 2, 3, 4, 5, 6 }; // Best
	int n = sizeof(arr) / sizeof(arr[0]);

	// Insertion Sort
	{
		auto start = chrono::high_resolution_clock::now();
		InsertionSort(arr, n);
		
		auto end = chrono::high_resolution_clock::now();
		Print(arr, n);
		std::chrono::duration<double, std::milli> elapsed = end - start;
		cout << "arr time : " << elapsed.count() << "ms\n";

		start = chrono::high_resolution_clock::now();
		InsertionSort(arr1, n);

		end = chrono::high_resolution_clock::now();
		Print(arr1, n);
		elapsed = end - start;
		cout << "arr1 time : " << elapsed.count() << "ms\n";

		start = chrono::high_resolution_clock::now();
		InsertionSort(arr2, n);

		end = chrono::high_resolution_clock::now();
		Print(arr2, n);
		elapsed = end - start;
		cout << "arr2 time : " << elapsed.count() << "ms\n";
	}

	// Stability
}
