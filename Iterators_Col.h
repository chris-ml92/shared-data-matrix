#ifndef ITERATORS_COL_H
#define ITERATORS_COL_H
#include "Matrix_Declarations.h"
#include "Super_Matrix.h"


/***************************Col Iterator******************************/

template<typename T, class matrix_Type>
class cIterator {
private:

	unsigned nRow, nCol;
	Super_Matrix<T, matrix_Type> &matrix_;
	typedef cIterator typeTracker;

public:

	/****************************Constructor ****************************/
	cIterator(Super_Matrix<T, matrix_Type> &matrix, unsigned Row, unsigned Col) : matrix_(matrix), nRow(Row), nCol(Col) {}

	/****************************Operator *() ****************************/

	T& operator *() {
		return matrix_(nRow, nCol);
	}

	/**************************** operator == ****************************/

	bool operator== (const typeTracker& Iter) const {
		return (Iter.nCol == nCol && Iter.nRow == nRow);
	}


	/**************************** operator != ****************************/

	bool operator!= (const typeTracker& Iter) const {
		return !(Iter.nCol == nCol && Iter.nRow == nRow);
	}

	/**************************** operator ++ ****************************/

	typeTracker& operator++ () {

		nRow++;

		if (nRow >= matrix_.getNCols()) {
			nRow = 0;
			nCol++;
		}

		return *this;
	}


};



/************************Const Col Iterator************************/

template<typename T, class matrix_Type>
class ccIterator {

private:

	unsigned nRow, nCol;
	const Super_Matrix<T, matrix_Type> &matrix_;
	typedef ccIterator typeTracker;

public:

	/****************************Constructor ****************************/
	ccIterator(const Super_Matrix<T, matrix_Type> &matrix, unsigned Row, unsigned Col) :
		matrix_(matrix), nRow(Row), nCol(Col) {}


	/**************************** operator *() ****************************/

	const T& operator *() {
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

		nRow++;

		if (nRow >= matrix_.getNCols()) {
			nCol++;
			nRow = 0;
		}

		return *this;
	}

};


#endif // !ITERATORS_COL_H


