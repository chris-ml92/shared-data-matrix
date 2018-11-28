#ifndef MATRIX_TOTRANSPOSE_H
#define MATRIX_TOTRANSPOSE_H
#include "Super_Matrix.h"


template <typename T, class Type>
class Super_Matrix<T, toTranspose<Type>> : private Super_Matrix<T, Type> {

/*friendship declaration, otherwise my starter class won't be able to access to the data of the subclass*/
friend  Super_Matrix<T, Type>;

protected:
	/*use of type def to take track of the type otherwise is difficult to do it manually*/
	typedef Super_Matrix<T, Type> matrix_;
	
	/***********************Constructor***********************/
	Super_Matrix(const Super_Matrix<T, Type> &toCopy) : matrix_(toCopy) {}

public:

	/***********************Get Methods***********************/
	unsigned getNRows() const {
		return matrix_::getNCols();
	}

	unsigned getNCols() const {
		return matrix_::getNRows();
	}

	/*********************** Operator () So I can access the matrix by simply doing A(i,j) ***********************/
	T& operator()(unsigned Rows, unsigned Cols) {
		if(Rows >= matrix_::getNCols() || Cols >= matrix_::getNRows()) throw std::invalid_argument("Error: out of size Transposed!");
		return matrix_::operator()(Cols, Rows);
	}

	/*const version*/
	const T& operator()(unsigned Rows, unsigned Cols) const {
		if (Rows >= matrix_::getNCols() || Cols >= matrix_::getNRows()) throw std::invalid_argument("Error: out of size Transposed!");
		return matrix_::operator()(Cols, Rows);
	}
	
	/**************************TRANSFORMATIONS*****************************/

	/**************************subMatrix Method****************************/

	Super_Matrix<T, subMatrix<toTranspose<Type>>> subMM(unsigned f_R, unsigned to_R, unsigned f_C = 0, unsigned to_C = 1) const {
		return Super_Matrix<T, subMatrix<toTranspose<Type>>>(*this, f_R, to_R, f_C, to_C);
	}

	/**************************Transpose Method****************************/

	matrix_ transpose() const {
		return *this;
	}

	/**************************Diagonal Method*****************************/

	Super_Matrix<T, diagonal<toTranspose<Type>>> diagonalV() const {
		return Super_Matrix<T, diagonal<toTranspose<Type>>>(*this);
	}

	/***********************Diagonal constant Matrix Method*****************/

	Super_Matrix<T, diagMatrix<toTranspose<Type>>> cDiagMatrix() const {
		return Super_Matrix<T, diagMatrix<toTranspose<Type>>>(*this);
	}

	/*************************END TRANSFORMATIONS***************************/


	/*************************ITERATORS*************************************/

	typedef typename  matrix_::rIter cIter;
	typedef typename  matrix_::c_rIter c_cIter;
	typedef typename  matrix_::cIter rIter;
	typedef typename  matrix_::c_cIter c_rIter;

	/*********************** Row Iterators ********************************/
	rIter first_eRowN(unsigned i) {
		return matrix_::first_eColN(i);
	}

	/*Const Override*/
	c_rIter first_eRowN(unsigned i) const {
		return matrix_::first_eColN(i);
	}

	/*Return Last element row, out of bond*/
	rIter last_eRowN() {
		return matrix_::last_eColN();
	}
	/*const override*/
	c_rIter last_eRowN() const {
		return matrix_::last_eColN();
	}

	/*********************** Col Iterators ********************************/

	cIter first_eColN(unsigned i) {
		return matrix_::first_eRowN(i);
	}

	/*Const Override*/
	c_cIter first_eColN(unsigned i) const {
		return matrix_::first_eRowN(i);
	}

	/*Return Last element col, out of bond*/
	cIter last_eColN() {
		return matrix_::last_eRowN();
	}

	/*const override*/
	c_cIter last_eColN() const {
		return matrix_::last_eRowN();
	}


};

#endif // MATRIX_TOTRANSPOSE_H

