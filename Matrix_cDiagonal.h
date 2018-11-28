#ifndef MATRIX_CDIAGONAL_H
#define MATRIX_CDIAGONAL_H

#include"Super_Matrix.h"

template <typename T, class Type>
class Super_Matrix<T, diagMatrix<Type>> : private Super_Matrix<T, Type> {

/*friendship declaration, otherwise my starter class won't be able to access to the data of the subclass*/
friend Super_Matrix<T, Type>;

protected:
	int val = 0; /*need it to fill matrix*/
	
	/*use of type def to take track of the type otherwise is difficult to do it manually*/
	typedef Super_Matrix<T, Type> matrix_;
	
	/***********************Constructor***********************/
	Super_Matrix(const Super_Matrix<T, Type> &m) : matrix_(m) {}

public:
	/***********************Get Methods***********************/

	/***********************getNRows Method*******************/
	unsigned getNRows() const {
		return matrix_::getNRows();
	}

	/***********************getNCols Method ******************/
	unsigned getNCols() const {
		return matrix_::getNRows();
	}

	/*********************** Operator () So I can access the matrix by simply doing A(i,j) ***********************/
	const T& operator() (unsigned Row, unsigned Col) const {
		if ( Row >= matrix_::getNRows() || Col >= matrix_::getNRows()) throw std::invalid_argument("Error: out of size!");
		if (Col != Row) return val;
		return matrix_::operator()(Row, 0);
	}/* Also since I can see every matrix as a vector, I don't care what I pass to the constant diagonal matrix, I just see it as a vector*/


	/**************************TRANSFORMATIONS*****************************/

	/**************************subMatrix Method****************************/

	Super_Matrix<T, subMatrix<diagMatrix<Type>>> subMM(unsigned f_R, unsigned to_R, unsigned f_C, unsigned to_C) const {
		return Super_Matrix<T, subMatrix<diagMatrix<Type>>>(*this, f_R, to_R, f_C, to_C);
	}

	/**************************Transpose Method****************************/

	Super_Matrix<T, toTranspose<diagMatrix<Type>>> transpose() const {
		return Super_Matrix<T, toTranspose<diagMatrix<Type>>>(*this);
	}

	 /**************************Diagonal Method*****************************/

	Super_Matrix<T, diagonal<diagMatrix<Type>>> diagonalV() const {
		return Super_Matrix<T, diagonal<diagMatrix<Type>>>(*this);
	}

	/***********************Diagonal constant Matrix Method*****************/

	const Super_Matrix<T, diagMatrix<Type>> cDiagMatrix() const {
		return *this;
	}

	/*************************END TRANSFORMATIONS***************************/


	/*************************ITERATORS*************************************/

	/*********************** Row Iterators *********************************/
	typedef crIterator<T, diagMatrix<Type>> c_rIter;

	c_rIter first_eRowN(unsigned i) const {
		return c_rIter(*this, i, 0);
	}

	c_rIter last_eRowN() const {
		return c_rIter(*this, matrix_::getNRows(), 0);
	}

	/*********************** Col Iterators ********************************/
	typedef ccIterator<T, diagMatrix<Type>> c_cIter;


	c_cIter first_eColN(unsigned i) const {
		return c_cIter(*this, 0, i);
	}

	c_cIter last_eColN() const {
		return c_cIter(*this, 0, matrix_::getNRows());
	}

};





#endif // !MATRIX_CDIAGONAL_H
