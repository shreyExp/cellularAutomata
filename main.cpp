#include <iostream>
#include <fstream>
#include <string>
#include <complex>
#include <json/json.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
using namespace Json;

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
RowOfCells::RowOfCells(const int size, int rowposition){
	arr = new int[size];
	arrCopy = new int[size];
	sizeOfRow = size;
	midIndex = (sizeOfRow + 1)/2;
	rowPosition = rowposition;
	initialStep();
}
void RowOfCells::initialStep(){
	arr[midIndex] = 1;
}
void RowOfCells::nextStep(){
	for(int i = 0; i < sizeOfRow; i++){
		if(i == 0){
			arrCopy[i] = arr[i+1];
		}else if(i == (sizeOfRow - 1)){
			arrCopy[i] = arr[sizeOfRow -2];
		}else if(arr[i-1] ^ arr[i+1]){ 
			arrCopy[i] = 1;
		}else{
			arrCopy[i] = 0;
		}
	}	
	copyArr(arrCopy, arr);
}
void RowOfCells::copyArr(int* arrSource, int* arrDestination){
	for(int i = 0; i < sizeOfRow; i++){
		arrDestination[i] = arrSource[i];
	}
}
int RowOfCells::seek(int index){
	if(index < sizeOfRow && index >= 0)
		return arr[index];
	else{
		cout<<"index out of bounds\n";
		return 0;
	}
}
int main(int argc, char** argv){
	double aspectRatio = 158.0/80.0;
	const int noOfCellRows = 1500;
	const int noOfCellsInRow = (double)noOfCellRows*aspectRatio;
	cout<<"rows "<<noOfCellRows<<" Cols: "<<noOfCellsInRow<<endl;
	const int sizeOfCell = 2000/noOfCellRows; //in each dimension
	const int pixelCols = noOfCellsInRow * sizeOfCell;
	const int pixelRows = noOfCellRows * sizeOfCell;
	int cellSize = 5; //size of the block on the image
	Mat M(pixelRows, pixelCols, CV_8UC3, Scalar(0,0,0));
	RowOfCells cellRow(noOfCellsInRow, 0);
	int cols = M.cols*M.channels();
	int value = 0;
	cout<<"M.rows "<<M.rows<<endl;
	cout<<"M.cols "<<M.cols<<endl;
	for(int i = 0; i < noOfCellRows; i++){
		for(int j = 0; j < noOfCellsInRow; j++){
			value = cellRow.seek(j);
			Mat subset(M, Rect(j*sizeOfCell, i*sizeOfCell, sizeOfCell, sizeOfCell));
			if(value)
				subset = Scalar(255, 255, 255);
		}
		cellRow.nextStep();
	}
	imshow("Cellular Automata", M);
	waitKey(1000);
	imwrite("CellularAutomata.jpg", M);
	return 0;
}
