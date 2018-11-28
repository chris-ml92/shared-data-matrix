#include<iostream>
#include "Matrix_Implemented.h"


/*
Project by Christian Bernabe Cabrera.
Date Created : 13/11/2018
Date last modified: 26/11/2018

TODO: Will upload to Git after 27/11/2018

*/


int main() {
	try {
		int nRows = 5, nCols = 5;
		
		Matrix<int> testFill(nRows, nCols);
		testFill.fillMatrix();
		cout << "testFill\n";
		testFill.printMatrix();
		
		vector<int> V{ 100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124 };
		vector<char> CharV{'A', 'B','C','D','E','F','G','H','I'};
		
		Matrix<int> matrix(nRows, nCols);
		Matrix<char>charMatrix(3, 3);

		matrix.fillMatrix(V);
		charMatrix.fillMatrix(CharV);
		cout << "Matrix\n";
		matrix.printMatrix();
		cout << "CharMatrix\n";
		charMatrix.printMatrix();

		cout<<"\nIterator Row order\n";

		for (auto iterator = charMatrix.first_eRowN(0); iterator != charMatrix.last_eRowN(); ++iterator)
			cout << *iterator << " ";
		cout << "\n\nIterator Col order\n";
		for (auto iterator = charMatrix.first_eColN(0); iterator != charMatrix.last_eColN(); ++iterator)
			cout << *iterator << " ";

		auto transposed = charMatrix.transpose();
		cout << "\n\nIterator transposed type Row order\n";
		for (auto it = transposed.first_eRowN(0); it != transposed.last_eRowN(); ++it)
			cout << *it << " ";


		/******************Test shared data***********************/

		/*Transpose method*/
		cout << "\n\nIf I do matrix.transpose()(0, 1) = 42 then matrix(1,0) must be 42" << endl;
		matrix.transpose()(0, 1) = 42;
		cout << "And it is " << matrix(1, 0) <<" indeed\n"<< endl;
		/*DiagonalV method*/
		cout << "If I do matrix.diagonalV()(1) = 18 then matrix(4,4) must be 18" << endl;
		matrix.diagonalV()(4) = 18;
		cout << "And it is " << matrix(4, 4) << " indeed\n" << endl;
		/*SubMM method*/
		cout << "If I do matrix.subMM()(1,3,1,3)(1,2) = 911 then matrix(2,3) must be 911" << endl;
		matrix.subMM(1, 3, 1, 3)(1, 2) = 911;
		cout << "And it is " << matrix(2, 3) << " indeed\n" << endl;
		/*cDiagmatrix() method*/
		cout << "If I do matrix.cDiagmatrix()(1, 1) = 50 then it should result in a compile error" << endl;
		//matrix.cDiagmatrix()(1, 1) = 50;
		cout << "And so it does\n\nI can also use the methods concatenated, since every class implements also every other class using the pattern decorator\n\nFor example matrix.transpose().transpose().transpose().subMM(1,3,1,3).diagonalV()(1) = 15 then matrix(2,2) must be 15 " << endl;
		matrix.transpose().transpose().transpose().subMM(1, 3, 1, 3).diagonalV()(1) = 15;
		cout << "And it is " << matrix(2, 2) << " indeed\n\nDoing some operations like matrix= matrix.transpose() should result in a deep copy assignment.\n\nMatrix before assignment\n";
		matrix.printMatrix();
		matrix = matrix.transpose().transpose().transpose().transpose().transpose();
		cout << "Matrix after assignment\n";
		matrix.printMatrix();
		cout << "\n\nAlso, declaring a new matrix like matrix2 and copying it from matrix, should result in a deep copy.\n";
		Matrix<int> matrix2(matrix);
		matrix2(1, 2) = 1000;
		cout << "If matrix(1,2)!=matrix2(1,2) print 1:\n" << (matrix(1, 2) != matrix2(1, 2)) << "\n\nMatrix<int> matrix3 = matrix2.transpose().diagonalV() will still call the dcc\n";
		Matrix<int> matrix3 = matrix2.transpose().diagonalV();
		cout << "\nmatrix3 is now a vector Nx1\nmatrix3:\n";
		matrix3.printMatrix();
		cout << "I can also copy from a non matrix type, like transposed for example, to a Matrix type, and should still call the dcc\n";
		auto transposedT = matrix.transpose();
		Matrix<int> matrix4 = transposedT;

		cout << "We can also copy the values of a constant diagonal matrix into a matrix\n";
		Matrix<int> matrix5 = matrix4.cDiagMatrix();
		cout << "However something like this: matrix.cDiagMatrix()(1,1) = 50 will result in a compile error because cDiagMatrix is a constant diagonal Matrix\n";
		cout << "\nMatrix copied from constant diagonal Matrix\n";
		matrix5.printMatrix();

		cout << "\nSupports constant too\nconst Matrix<int> constantM = matrix5\ncout << constantM(1, 1)\n";
		const Matrix<int> constantM = matrix5;
		cout << constantM(1, 1);

	}
	catch (const std::invalid_argument& error) {
		std::cerr << "Invalid argument: " << error.what() << "\n";
	}

			

}