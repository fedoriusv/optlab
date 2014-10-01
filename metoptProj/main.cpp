#include "conio.h"
#include "FuncList.h"

void main()
{
	createFunctions();
	//==============================
	metopt::inputParam oparam1;
	double x[] = { -1.2, -0.4 }; 
	//double x[] = { 4, 1 }; 
	metopt::Arg initPoint1(x);
	
	metopt::CFunc* func = new metopt::CFunc(RotatedParaboloid3d);
	func->setMethod(metopt::NAME_METHOD_GAUSS_SEIDEL);
	func->setPrecision( 0.01 );
	func->setStep( 0.1 );
	func->setParam( 200, 500 );
	func->setFlagExit(metopt::TYPE_EXIT_PRECISION_FUNC);
	func->setOneDimensionalMethod(metopt::NAME_METHOD_DIVISION);
	func->setOneDimensionalPrecision( 0.01 );
	oparam1 = func->calcArgMin( initPoint1 );
	metopt::CDataMultiDimensional* data1;// = new metopt::CDataMultiDimensional();
	data1 = func->getMultiData();
	data1->printToFile("methodsNEW.log");
	//===============================
	metopt::inputParam oparam2;
	double x2[] = { -2.0 }; 
	metopt::Arg initPoint2(x2);

	metopt::CFunc* func1 = new metopt::CFunc(Polynomial3D);
	func1->setMethod(metopt::NAME_METHOD_ADAPTATION_STEP);
	func1->setPrecision( 0.01 );
	func1->setStep( 0.1 );
	func1->setParam( 200, 500 );
	func1->setFlagExit(metopt::TYPE_EXIT_PRECISION_FUNC);
	oparam2 = func1->calcArgMin( initPoint2 );
	metopt::CDataOneDimensional* data2;// = new metopt::CDataOneDimensional();
	data2 = func1->getData();
	data2->printToFile("methodsNEW2.log");
	//================================

	//getch();
};