#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_07_1Iterative.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	static int** MakeMatrix(const int* data, int rows, int cols) {
		int** m = new int* [rows];
		for (int i = 0; i < rows; i++) {
			m[i] = new int[cols];
			for (int j = 0; j < cols; j++)
				m[i][j] = data[i * cols + j];
		}
		return m;
	}

	static void FreeMatrix(int** m, int rows) {
		for (int i = 0; i < rows; i++) delete[] m[i];
		delete[] m;
	}

	static void AssertMatrix(const int* expected, int** m, int rows, int cols) {
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				Assert::AreEqual(expected[i * cols + j], m[i][j]);
	}

	TEST_CLASS(IterativeTests)
	{
	public:
		TEST_METHOD(Create_ValuesInRange)
		{
			const int rows = 7, cols = 9;
			int** R = MakeMatrix(new int[rows * cols](), rows, cols);
			Create(R, rows, cols, -12, 37);
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++) {
					Assert::IsTrue(R[i][j] >= -12);
					Assert::IsTrue(R[i][j] <= 37);
				}
			FreeMatrix(R, rows);
		}

		TEST_METHOD(Change_SwapsWholeColumns)
		{
			int data[] = { 1, 2, 3,
						   4, 5, 6 };
			int expected[] = { 3, 2, 1,
							   6, 5, 4 };
			int** R = MakeMatrix(data, 2, 3);
			Change(R, 0, 2, 2);
			AssertMatrix(expected, R, 2, 3);
			FreeMatrix(R, 2);
		}

		TEST_METHOD(Sort_ByFirstRow)
		{
			int data[] = { 5, 2, 9,
						   1, 8, 3,
						   7, 4, 6 };
			int expected[] = { 2, 5, 9,
							   8, 1, 3,
							   4, 7, 6 };
			int** R = MakeMatrix(data, 3, 3);
			Sort(R, 3, 3);
			AssertMatrix(expected, R, 3, 3);
			FreeMatrix(R, 3);
		}

		TEST_METHOD(Sort_SecondKeyWhenFirstRowEqual)
		{
			int data[] = { 5, 2, 5, 2,
						   7, 9, 3, 1,
						   0, 0, 4, 8 };
			int expected[] = { 2, 2, 5, 5,
							   1, 9, 3, 7,
							   8, 0, 4, 0 };
			int** R = MakeMatrix(data, 3, 4);
			Sort(R, 3, 4);
			AssertMatrix(expected, R, 3, 4);
			FreeMatrix(R, 3);
		}

		TEST_METHOD(Sort_ThirdKeyWhenTwoRowsEqual)
		{
			int data[] = { 1, 1, 0,
						   2, 2, 5,
						   9, 3, 7 };
			int expected[] = { 0, 1, 1,
							   5, 2, 2,
							   7, 3, 9 };
			int** R = MakeMatrix(data, 3, 3);
			Sort(R, 3, 3);
			AssertMatrix(expected, R, 3, 3);
			FreeMatrix(R, 3);
		}

		TEST_METHOD(Calc_SumCountAndZeroing)
		{
			int data[] = { 3, -3, 0,
						  -2, -6, 4 };
			int expected[] = { 0, -3, 0,
							   0, -6, 0 };
			int** R = MakeMatrix(data, 2, 3);
			int S = -1, k = -1;
			Calc(R, 2, 3, S, k);
			Assert::AreEqual(5, S);
			Assert::AreEqual(3, k);
			AssertMatrix(expected, R, 2, 3);
			FreeMatrix(R, 2);
		}
	};
}