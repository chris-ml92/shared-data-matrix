#ifndef MATRIX_IMPLEMENTED_H
#define MATRIX_IMPLEMENTED_H
#include"Super_Matrix.h"
#include"Matrix_subMatrix.h"
#include"Matrix_toTranspose.h"
#include"Matrix_DiagonalV.h"
#include"Matrix_cDiagonal.h"


template <class T>
class Matrix : public Super_Matrix<T, starterM> {
public:
	using Super_Matrix<T, starterM>::mElements; /*Used "Using" in order to avoid typing "this->" n times*/
	using Super_Matrix<T, starterM>::s_Row;
	using Super_Matrix<T, starterM>::s_Col;
	using Super_Matrix<T, starterM>::sizeM;

	Matrix(unsigned Rows, unsigned Cols) {
		s_Row = Rows;
		s_Col = Cols;
		sizeM = Rows * Cols;
		mElements = make_shared<vector<T>>(Rows*Cols);
	}

	Matrix(const Matrix<T>&X) {
		s_Row = X.getNRows();
		s_Col = X.getNCols();
		sizeM = s_Row * s_Col;
		//cout << typeid(X).name() << endl;
		mElements = make_shared<vector<T>>(sizeM);
		auto curr = X.first_eRowN(0);
		for (int i = 0; i < sizeM; i++) {
			mElements->operator[](i) = *curr;
			++curr;
		}
		cout << "The Deep Copy Constructor has been used\n";
	}

	template<class Generic>
	Matrix(const Super_Matrix<T, Generic>&X) {
		s_Row = X.getNRows();
		s_Col = X.getNCols();
		sizeM = s_Row * s_Col;
		//cout << typeid(X).name() << sizeM << endl;
		mElements = make_shared<vector<T>>(sizeM);
		auto curr = X.first_eRowN(0);

		for (int i = 0; i < sizeM; i++) {
			mElements->operator[](i) = *curr;
			++curr;
		}
		cout << "The Generic Deep Copy Constructor has been used\n";
	}

	Matrix& operator =(const Matrix<T>&X) {
		s_Row = X.getNRows();
		s_Col = X.getNCols();
		sizeM = s_Row * s_Col;
		//cout << s_Row<< " "<<s_Col<<" "<<typeid(X.first_eRowN(0)).name() << endl;
		mElements = make_shared<vector<T>>(sizeM);
		auto curr = X.first_eRowN(0);

		for (unsigned i = 0; i < sizeM; i++) {
			//cout << *curr << endl;
			mElements->operator[](i) = *curr;
			++curr;
		}
		cout << "The Deep Copy Assignment has been used\n";
		return *this;
	}

	template<class Generic>
	Matrix& operator =(const Super_Matrix<T, Generic>&X) {
		s_Row = X.getNRows();
		s_Col = X.getNCols();
		sizeM = s_Row * s_Col;
		mElements = make_shared<vector<T>>(sizeM);
		auto curr = X.first_eRowN(0);

		for (unsigned i = 0; i < sizeM; i++) {
			//cout << *curr << endl;
			mElements->operator[](i) = *curr;
			++curr;
		}
		cout << "The Generic Deep Copy Assignment has been used\n";
		return *this;
	}

};

#endif // MATRIX_IMPLEMENTED_H
