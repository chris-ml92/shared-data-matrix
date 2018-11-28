#ifndef SUPER_MATRIX_H
#define SUPER_MATRIX_H

#include <memory>
#include <vector>
#include "Matrix_Declarations.h"
#include "Iterators_Row.h"
#include "Iterators_Col.h"
#include "Matrix_cDiagonal.h"
#include <cstdlib>
#include <cassert>


template <typename T>
class Super_Matrix<T,starterM> {
protected:
	unsigned s_Row;
	unsigned s_Col;	
	unsigned sizeM;
	shared_ptr<vector<T>> mElements;
public:

/***********************Default Constructor & Destructor***********************/
	 Super_Matrix() {}
	~Super_Matrix() {}

	/*Super_Matrix(unsigned Rows, unsigned Cols) { // I tried to implement the decorator directly from the starter class,
		s_Row = Rows;							   // However this caused the call of my copy and/or assignment constructors
		s_Col = Cols;							   // This would be a nice implementation to getrid of the matrix class if the assignement											 //	didn't require to share the data. 
		sizeM = Rows * Cols;					   
		mElements = make_shared<vector<T>>(sizeM);
	}*/

/*	template<class Generic>
	Super_Matrix(const Super_Matrix<T, Generic>&X) {
		s_Row = X.getNRows();
		s_Col = X.getNCols();
		sizeM = s_Row*s_Col;
		//cout << typeid(X).name() << endl;
		mElements = make_shared<vector<T>>(sizeM);
		auto curr = X.first_eRowN(0);
		
		for (int i = 0; i < sizeM; i++) {
			mElements->operator[](i) = *curr;
			++curr;
		}
		cout << "DCC\n";
	}

	template<class Generic>
	Super_Matrix& operator =(const Super_Matrix<T, Generic>&X) {
		s_Row = X.getNRows();
		s_Col = X.getNCols();
		sizeM = s_Row * s_Col;
		//cout << s_Row<< " "<<s_Col<<" "<<typeid(X.first_eRowN(0)).name() << endl;
		mElements = make_shared<vector<T>>(sizeM);
		auto curr = X.first_eRowN(0);

		for (int i = 0; i < sizeM; i++) {
			//cout << *curr << endl;
			mElements->operator[](i) = *curr;
			++curr;
		}
		cout << "ADCC\n";
		return *this;
	}*/


/***********************Get Methods***********************/
	unsigned getNRows() const { return s_Row; }
	unsigned getNCols() const { return s_Col; }
	unsigned getSize() const { return sizeM; }
	unsigned get_Element(unsigned i) const { return mElements->operator[](i); } // TODO check if I used it, or let it die

/*********************** Operator () So I can access the matrix by simply doing A(i,j) ***********************/
	T& operator()(unsigned Rows, unsigned Cols) {
		
		return mElements->operator[](Rows*s_Col + Cols);
	}
	/*const version*/
	const T& operator()(unsigned Rows, unsigned Cols) const {
		return mElements->operator[](Rows*s_Col + Cols);
	}

/**************************TRANSFORMATIONS*****************************/

/**************************subMatrix Method****************************/

	Super_Matrix<T, subMatrix<starterM>> subMM(unsigned f_R, unsigned to_R, unsigned f_C, unsigned to_C) const {
		return Super_Matrix<T, subMatrix<starterM>>(*this, f_R, to_R, f_C, to_C);
	}

/**************************Transpose Method****************************/
	Super_Matrix<T, toTranspose<starterM>> transpose() const {
		return Super_Matrix<T, toTranspose<starterM>>(*this);
	}

/**************************Diagonal Method*****************************/
	Super_Matrix<T, diagonal<starterM>> diagonalV() const {
		return Super_Matrix<T, diagonal<starterM>>(*this);
	}

/***********************Diagonal constant Matrix Method*****************/
	const Super_Matrix<T, diagMatrix<starterM>> cDiagMatrix() const {
		return Super_Matrix<T, diagMatrix<starterM>>(*this);
	}

/*************************END TRANSFORMATIONS***************************/


/*************************ITERATORS*************************************/

/*********************** Row Iterators *********************************/
	using rIter = rIterator<T,starterM>;
	using c_rIter = crIterator<T,starterM>;

	/*Return First Element at the Selected row*/
	rIter first_eRowN(unsigned i) {
		return rIter(*this,i,0);
	}
	/*Const Override*/
	c_rIter first_eRowN(unsigned i) const {
		return c_rIter(*this,i,0);
	}

	/*Return Last element row, out of bond*/
	rIter last_eRowN() {
		return rIter(*this, s_Row , 0);
	}
	/*const override*/
	c_rIter last_eRowN() const {
		return c_rIter(*this, s_Row, 0);
	}

/*********************** Col Iterators ***********************/
	using cIter = cIterator<T, starterM>;
	using c_cIter = ccIterator<T, starterM>;
	
	cIter first_eColN(unsigned i) {
		return cIter(*this, 0, i);
	}

	c_cIter first_eColN(unsigned i) const{
		return c_cIter(*this, 0, i);
	}

	/*Return Last element col, out of bond*/
	cIter last_eColN() {
		return cIter(*this, 0, s_Col);
	}

	/*const override*/
	c_cIter last_eColN() const {
		return c_cIter(*this, 0, s_Col);
	}

/*************************END ITERATORS*************************/

/***********************Print method****************************/
	void printMatrix() const {
		for (unsigned i = 0; i < s_Row; i++) {
			for (unsigned j = 0; j < s_Col; j++)
				cout << (mElements->operator[](i*s_Col + j)) << " ";
			cout << endl;
		}
		cout << endl;
	}


/******************Fill Matrix method with random numbers***********************/
	void fillMatrix() const {
		
		for (unsigned i = 0; i < s_Row; i++) 
			for (unsigned j = 0; j < s_Col; j++) {
				srand(i+j);
				unsigned random = (rand() % 100) + 1;
				mElements->operator[](i*s_Col + j) = random +i*j;
			
			}
		}

/***********************Fill Matrix method with vector***********************/
	void fillMatrix(vector<T>& V) {

		if (sizeM != V.size())
			throw std::invalid_argument("Error: Vector size must be equal to Matrix Size!.");
		for (unsigned i = 0; i < s_Row; i++)
			for (unsigned j = 0; j < s_Col; j++) 
				mElements->operator[](i*s_Col + j) = V[i*s_Col + j];

	}

};

#endif // SUPER_MATRIX_H


