#ifndef ITERATORS_ROW_H
#define MITERATORS_ROW_H
#include "Matrix_Declarations.h"
#include "Super_Matrix.h"

/***************************Row Iterator******************************/

template<typename T, class matrix_Type>
class rIterator {

private:

	unsigned nRow, nCol;
	Super_Matrix<T, matrix_Type> &matrix_;
	typedef rIterator typeTracker;

public:

	/****************************Constructor ****************************/
	rIterator(Super_Matrix<T, matrix_Type> &matrix, unsigned Row, unsigned Col) :
		matrix_(matrix), nRow(Row), nCol(Col) {}


	/**************************** operator *() ****************************/

	T& operator *() {
		return matrix_(nRow, nCol);
	}

	/**************************** operator == ****************************/

	bool operator== (const typeTracker& Iter) const {
		return nRow == Iter.nRow && nCol == Iter.nCol;
	}

	/**************************** operator != ****************************/

	bool operator!= (const typeTracker& Iter) const {
		return !(Iter.nCol == nCol && Iter.nRow == nRow);
	}

	/**************************** operator ++ ****************************/

	typeTracker& operator++ () {

		nCol++;

		if (nCol >= matrix_.getNCols()) {
			nRow++;
			nCol = 0;
		}

		return *this;
	}

};




/************************Const Row Iterator***************************/

template<typename T, class matrix_Type>
class crIterator {
private:

	const Super_Matrix<T, matrix_Type> &matrix_;
	unsigned nRow, nCol;
	typedef crIterator typeTracker;

public:

	/****************************Constructor ****************************/
	crIterator(const Super_Matrix<T, matrix_Type> &matrix, unsigned Row, unsigned Col) :
		matrix_(matrix), nRow(Row), nCol(Col) {}

	/**************************** operator *() ****************************/

	const T& operator *() const {
		return matrix_(nRow, nCol);
	}

	/**************************** operator == ****************************/

	bool operator== (const typeTracker& Iter) const {
		return nRow == Iter.nRow && nCol == Iter.nCol;
	}

	/**************************** operator != ****************************/

	bool operator!= (const typeTracker& Iter) const {
		return !(Iter.nCol == nCol && Iter.nRow == nRow);
	}

	/**************************** operator ++ ****************************/

	typeTracker& operator++ () {

		nCol++;

		if (nCol >= matrix_.getNCols()) {
			nRow++;
			nCol = 0;
		}

		return *this;
	}
};




#endif // !MITERATORS_ROW_H
