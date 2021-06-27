#include <iostream>
#include "cellular.h"
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
