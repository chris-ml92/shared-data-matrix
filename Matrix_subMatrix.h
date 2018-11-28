#ifndef MATRIX_SUBMATRIX_H
#define MATRIX_SUBMATRIX_H
#include "Super_Matrix.h"

template <typename T, class Type>
class Super_Matrix<T, subMatrix<Type>> : private Super_Matrix<T, Type> {

/*friendship declaration, otherwise my starter class won't be able to access to the data of the subclass*/
friend Super_Matrix<T, Type>;

protected:
	/*use of type def to take track of the type otherwise is difficult to do it manually*/
	typedef Super_Matrix<T, Type> matrix_;
	/*Legend f_r = from Row, t_r = to Row, f_c = from Col, t_c = to Col */
	unsigned f_r, t_r, f_c, t_c;
	
	/***********************Constructor***********************/
	Super_Matrix(const Super_Matrix<T, Type> m, unsigned f_R, unsigned t_R, unsigned f_C, unsigned t_C) :
	matrix_(m), f_r(f_R), t_r(t_R), f_c(f_C), t_c(t_C) {}

public:

	/***********************Get Methods***********************/
	unsigned getNRows() const {
		return (t_r-f_r);
	}

	unsigned getNCols() const {
		return (t_c-f_c);
	}

	/*********************** Operator () So I can access the matrix by simply doing A(i,j) ***********************/
	T& operator()(unsigned Rows, unsigned Cols) {
		if ( Rows > (t_r-f_r) || Cols > (t_c-f_c)) throw std::invalid_argument("Error: out of size of SubMatrix!");
		return matrix_::operator()(Rows + f_r, Cols + f_c);
	}
	/*const variation*/
	const T& operator()(unsigned Rows, unsigned Cols) const {
		if (Rows > (t_r - f_r) || Cols > (t_c - f_c)) throw std::invalid_argument("Error: out of size of SubMatrix!");
		return matrix_::operator()(Rows + f_r, Cols + f_c);
	}

	/**************************TRANSFORMATIONS*****************************/

	/**************************subMatrix Method****************************/

	Super_Matrix<T, subMatrix<Type>> subMM(unsigned f_R, unsigned to_R, unsigned f_C = 0, unsigned to_C = 1) const {
		return Super_Matrix<T, subMatrix<Type>>(*this, f_R +f_r , to_R + t_r, f_C + f_c, to_C + t_c);
	}

	/**************************Transpose Method****************************/

	Super_Matrix<T, toTranspose<subMatrix<Type>>> transpose() const {
		return Super_Matrix<T, toTranspose<subMatrix<Type>>>(*this);
	}
	
	/**************************Diagonal Method*****************************/

	Super_Matrix<T, diagonal<subMatrix<Type>>> diagonalV() const {
		return Super_Matrix<T, diagonal<subMatrix<Type>>>(*this);
	}
	
	/***********************Diagonal constant Matrix Method*****************/

	Super_Matrix<T, diagMatrix<subMatrix<Type>>> cdiagMatrix() const {
		return Super_Matrix<T, diagMatrix<subMatrix<Type>>>(*this);
	}

	/*************************END TRANSFORMATIONS***************************/


	/*************************ITERATORS*************************************/

	typedef typename rIterator<T,  subMatrix<Type>> rIter;
	typedef typename crIterator<T, subMatrix<Type>> c_rIter;

	/*********************** Row Iterators ********************************/
	rIter first_eRowN(unsigned i) {
		return rIter(*this, i, 0);
	}
	/*Const*/
	c_rIter first_eRowN(unsigned i) const {
		return c_rIter(*this, i, 0);
	}

	/*Return Last element row, out of bond*/
	rIter last_eRowN() {
		return rIter(*this, (t_r - f_r), 0);
	}

	/*const override*/
	c_rIter last_eRowN() const {
		return c_rIter(*this, (t_r - f_r), 0);
	}

	/*********************** Col Iterators ********************************/

	typedef typename cIterator<T,  subMatrix<Type>> cIter;
	typedef typename ccIterator<T, subMatrix<Type>> c_cIter;

	cIter first_eColN(unsigned i) {
		return cIter(*this, 0, i);
	}
	/*Const*/
	c_cIter first_eColN(unsigned i) const {
		return c_cIter(*this, 0, i);
	}

	/*Return Last element col, out of bond*/
	cIter last_eColN() {
		return cIter(*this, 0, (t_c - f_c));
	}

	/*const override*/
	c_cIter last_eColN() const {
		return c_cIter(*this, 0, (t_c - f_c));
	}

};


#endif // !MATRIX_SUBMATRIX_H
