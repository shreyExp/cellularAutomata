#include <iostream>
#include <fstream>
#include <string>
#include <complex>
#include <json/json.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "cellular.h"

using namespace std;
using namespace cv;
using namespace Json;

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
