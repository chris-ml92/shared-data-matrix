#ifndef MATRIX_DECLARATIONS_H
#define MATRIX_DECLARATIONS_H

using std::vector; using std::shared_ptr; using std::make_shared; /*Not nice, but nicer than doing std:: n times*/
using std::cout; using std::endl;

struct starterM; /*I need always a type to count on*/

/*Starter Class like suggested at lesson*/
template <typename T, class matrix_Type = starterM> class Super_Matrix; 

template<class Type> struct subMatrix;
template<class Type> struct toTranspose;
template<class Type> struct diagonal;
template<class Type> struct diagMatrix;

#endif // !MATRIX_DECLARATIONS_H
