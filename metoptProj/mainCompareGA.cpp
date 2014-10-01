#include "conio.h"
#include "FuncList.h"

void mainCompareGA()
{
	createFunctions();

	metopt::inputParam oparam;
	double x[] = { -2.0 };
	metopt::Arg initPoint(x);

	metopt::CFunc* func = new metopt::CFunc(Polynomial3D);

	metopt::CCompareMethods* compare = new metopt::CCompareSingleMethods(func);
	compare->pushMethod(metopt::NAME_METHOD_RANDOM_SEARCH);
	compare->pushMethod(metopt::NAME_METHOD_WEIL_PI_SEARCH);
	compare->pushMethod(metopt::NAME_METHOD_WEIL_E_SEARCH);
	compare->pushMethod(metopt::NAME_METHOD_DICHOTOMY);
	compare->pushMethod(metopt::NAME_METHOD_BIN_GENETIC_ALGORITHM);
	compare->pushMethod(metopt::NAME_METHOD_CON_GENETIC_ALGORITHM);
	

	compare->setPrecision(0.01);
	compare->setStep(0.1);
	compare->setParam(1000, 2000);
	compare->setFlagExit(metopt::TYPE_EXIT_PRECISION_FUNC);

	compare->calcMethods(initPoint);
	compare->getCompareData()->printToFile("CompareMethodsU.log");

};