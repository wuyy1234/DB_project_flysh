//following head files must be added
#include <iostream>
#include <stdlib.h>  
#include <time.h> 
#include <memory.h>
#include <fstream>

#include "Matrix.h"

//this struct must be added too
struct MyStruct {
	double value;
	size_t subscripts;
};

Matrix& randomMatrix(size_t k) {
	//assum that M is the target matrix
	DenseMatrix M("source.txt");


	size_t ROW = M.getRow();
	size_t COL = M.getColumn();


	srand((unsigned)time(NULL));
	size_t* ran = new size_t[k];
	size_t* r = new size_t[COL];

	size_t j = 0, temp = 0;

	//find the random k columns
	for (size_t i = 0; i<COL; i++) {
		r[i] = i;
	}
	for (size_t i = 0; i < k; i++) {
		j = rand() % ROW;
		temp = r[i];
		r[i] = r[j];
		r[j] = temp;
	}
	for (size_t i = 0; i < k; i++) {
		ran[i] = r[i];
	}

	//save the corresponding columns
	DenseMatrix*  matrixAfter = new DenseMatrix("randomMatrix.txt", ROW, k);

	size_t currentCol = 0;
	for (size_t i = 0; i<k; i++) {

		DenseRow row( k, i,nullptr);
		//DenseRow row((size_t)k, (size_t)i);

		currentCol = ran[i];
		for (size_t x = 0; x < ROW; x++) {
			row[x] = M[x][currentCol];
		}
		matrixAfter->setRow(row);
	}


	delete[] ran;
	delete[] r;
	return *matrixAfter;
}



DenseMatrix& WTAMatrix(size_t k) {
	//assum that M is the target matrix
	DenseMatrix M("source.txt");
	size_t ROW = M.getRow();
	size_t COL = M.getColumn();

	bool* isDelete = new bool[COL];//record if the certain column shou be delete

	
	DenseMatrix*  matrixAfter = new DenseMatrix("WTAMatrix.txt", ROW, COL);

	//find the top k in every row
	for (size_t i = 0; i < ROW; i++) {
		MyStruct* rowStruct=new MyStruct[COL];
		MyStruct temp;
		memset(isDelete, true, sizeof(bool)*COL);//initialize that every col will be delete   
		for (size_t j = 0; j < COL; j++) {
			rowStruct[j].value = M[i][j];
			rowStruct[j].subscripts = j;
		}

		for (size_t x = 0; x < COL; x++) {
			for (size_t y = x; y < COL; y++) {
				if (rowStruct[x].value < rowStruct[y].value) {//sort from big to small
					temp = rowStruct[x];
					rowStruct[x] = rowStruct[y];
					rowStruct[y] = temp;
				}
			}
		}
		for (size_t x = 0; x <k; x++) {//make the top k num not delete
			isDelete[rowStruct[x].subscripts] = false;
		}

		DenseRow row( COL, i,nullptr);

		for (size_t x = 0; x < COL; x++) {
			if (isDelete[x]) {
				row[x] = 0;
			}
			else {
				row[x] = M[i][x];
			}
		}
		matrixAfter->setRow(row);
	}


	delete[] isDelete;
	return *matrixAfter;
}
DenseMatrix& binaryMatrix(size_t k) {
	//assum that M is the target matrix
	DenseMatrix M("source.txt");
	size_t ROW = M.getRow();
	size_t COL = M.getColumn();

	bool* isDelete = new bool[COL];//record if the certain column shou be delete   
	
	DenseMatrix*  matrixAfter = new DenseMatrix("binaryMatrix.txt", ROW, COL);
	//find the top k in every row

	for (size_t i = 0; i < ROW; i++) {
		MyStruct* rowStruct=new MyStruct[COL];
		MyStruct temp;
		memset(isDelete, true, sizeof(bool)*COL);//initialize that every col will be delete   
		for (size_t j = 0; j < COL; j++) {
			rowStruct[j].value = M[i][j];
			rowStruct[j].subscripts = j;
		}

		for (size_t x = 0; x < COL; x++) {
			for (size_t y = x; y < COL; y++) {
				if (rowStruct[x].value < rowStruct[y].value) {//sort from big to small
					temp = rowStruct[x];
					rowStruct[x] = rowStruct[y];
					rowStruct[y] = temp;
				}
			}
		}
		for (size_t x = 0; x <k; x++) {//make the top k num not delete
			isDelete[rowStruct[x].subscripts] = false;
		}
		

		DenseRow row(COL, i,nullptr);

		for (size_t x = 0; x < COL; x++) {
			if (isDelete[x]) {
				row[x] = 0;
			}
			else {
				row[x] = 1;
			}
		}
		matrixAfter->setRow(row);



	}
	

	delete[] isDelete;
	return *matrixAfter;
}
