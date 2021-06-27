#include <cstddef>
#include <iostream>
using namespace std;
class RowOfCells{
	public:
		RowOfCells(const int, int);
		void nextStep();
		int seek(int);
	private:
		int* arr = NULL;
		int* arrCopy = NULL;
		int sizeOfRow = 0;
		int rowPosition = 0;
		int midIndex = 0;
		void initialStep();
		void copyArr(int*, int*);
};
