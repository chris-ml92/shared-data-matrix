#ifndef MATRIX_DIAGONALV_H
#define MATRIX_DIAGONALV_H
#include"Super_Matrix.h"

template <typename T, class Type>
class Super_Matrix<T, diagonal<Type>> : private Super_Matrix<T, Type> {

/*friendship declaration, otherwise my starter class won't be able to access to the data of the subclass*/
friend  Super_Matrix<T, Type>;

protected:
	/*use of type def to take track of the type otherwise is difficult to do it manually*/
	typedef Super_Matrix<T, Type> matrix_;

	/***********************Constructor***********************/
	Super_Matrix(const Super_Matrix<T, Type> &m) : matrix_(m) {}
	
public:

	/***********************Get Methods***********************/
	unsigned getNRows() const {
		if (matrix_::getNRows() > matrix_::getNCols()) /* I have two possible solutions, accept only squared matrix*/
			return matrix_::getNCols();				   /* Or change the view of the matrix, to see it like a square one, since I am only checking the */
		return matrix_::getNRows();				   /* I prefer the second option, because in this way, I can accept any matrix*/
	}

	unsigned getNCols() const {
		return 1;
	}


	/*********************** Operator () So I can access the matrix by simply doing A(i,j) ***********************/
	T& operator() (unsigned Row, unsigned Col = 0) { /*return elements from the diagonal of the matrix yA(0,0)....A(n,n)*/
		if (((matrix_::getNRows() > matrix_::getNCols()) && Row >= matrix_::getNCols()) || ((matrix_::getNRows() <= matrix_::getNCols()) && Row >= matrix_::getNRows())) throw std::invalid_argument("Error: out of size limit for Vector!");
		else
		return matrix_::operator() (Row, Row);
	}
	/*const variation*/
	const T& operator() (unsigned Row, unsigned Col = 0) const {
		if (((matrix_::getNRows() > matrix_::getNCols()) && Row >= matrix_::getNCols())||((matrix_::getNRows() <= matrix_::getNCols()) && Row >= matrix_::getNRows())) throw std::invalid_argument("Error: out of size limit for Vector!");
		else
		return matrix_::operator() (Row, Row);
	}



	/**************************TRANSFORMATIONS*****************************/

	/**************************subMatrix Method****************************/

	Super_Matrix<T, subMatrix<diagonal<Type>>> subMM(unsigned f_R, unsigned to_R, unsigned f_C = 0, unsigned to_C = 1) const {
		return Super_Matrix<T, subMatrix<diagonal<Type>>>(*this, f_R, to_R, f_C, to_C);
	}

	/**************************Transpose Method****************************/

	Super_Matrix<T, toTranspose<diagonal<Type>>> transpose() const {
		return Super_Matrix<T, toTranspose<diagonal<Type>>>(*this);
	}

	/**************************Diagonal Method*****************************/

	Super_Matrix<T, diagonal<diagonal<Type>>> diagonalV() const {
		return Super_Matrix<T, diagonal<diagonal<Type>>>(*this);
	}

	/***********************Diagonal constant Matrix Method*****************/

	Super_Matrix<T, diagMatrix<diagonal<Type>>> cDiagMatrix() const {
		return Super_Matrix<T, diagMatrix<diagonal<Type>>>(*this);
	}

	/*************************END TRANSFORMATIONS***************************/


	/*************************ITERATORS*************************************/
	
	typedef typename rIterator<T, diagonal<Type>> rIter;
	typedef typename crIterator<T, diagonal<Type>> c_rIter;

	/*********************** Row Iterators ********************************/
	rIter first_eRowN(unsigned i) {
		return rIter(*this, i, 0);
	}

	/*Const*/
	c_rIter first_eRowN(unsigned i) const {
		return c_rIter(*this,i,0);
	}

	/*Return Last element row, out of bond*/
	rIter last_eRowN() {
		return rIter(*this, matrix_::getNRows(), 0);
	}
	/*const override*/
	c_rIter last_eRowN() const {
		return c_rIter(*this, matrix_::getNRows(), 0);
	}

	/*********************** Col Iterators ***********************/
	typedef typename cIterator<T, diagonal<Type>> cIter;
	typedef typename ccIterator<T, diagonal<Type>> c_cIter;

	cIter first_eColN(unsigned i) {
		return cIter(*this, 0, i);
	}
	/*const*/
	c_cIter first_eColN(unsigned i) const {
		return c_cIter(*this, 0, i);
	}

	cIter last_eColN() {
		return cIter(*this, 0, 1);
	}
	c_cIter last_eColN() const {
		return c_cIter(*this, 0, 1);
	}

};



#endif // MATRIX_DIAGONALV_H
