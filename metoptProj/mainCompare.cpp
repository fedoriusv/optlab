#include "conio.h"
#include "FuncList.h"

void mainCompare()
{
	/*createFunctions();

	metopt::inputParam oparam;
	double x[] = { -2.0 };
	metopt::Arg initPoint(x);

	metopt::CFunc* func = new metopt::CFunc(Polynomial3D);

	metopt::CCompareMethods* compare = new metopt::CCompareSingleMethods(func);
	compare->pushMethod(metopt::NAME_METHOD_ADAPTATION_STEP);
	compare->pushMethod(metopt::NAME_METHOD_UNIFORM);
	compare->pushMethod(metopt::NAME_METHOD_DIVISION);
	compare->pushMethod(metopt::NAME_METHOD_DICHOTOMY);
	compare->pushMethod(metopt::NAME_METHOD_GOLDEN_SECTION);
	compare->pushMethod(metopt::NAME_METHOD_FIBONACCI);
	compare->pushMethod(metopt::NAME_METHOD_QUADRATIC_INTERPOLATION);
	compare->pushMethod(metopt::NAME_METHOD_CUBIC_INTERPOLATION);

	compare->setPrecision(0.01);
	compare->setStep(0.1);
	compare->setParam(200, 500);
	compare->setFlagExit(metopt::TYPE_EXIT_PRECISION_FUNC);

	compare->calcMethods(initPoint);
	compare->getCompareData()->printToFile("CompareMethods.log");*/

	createFunctions();

	double x[] = { -1.0, 1.0 };
	metopt::Arg initPoint(x);
	metopt::Arg a({ -2.0, 2.0 });
	metopt::Arg b({ -1.0, 1.0 });

	metopt::CFunc* func = new metopt::CFunc(Rosenbrock3d);

	metopt::CCompareMultiMethods* compare = new metopt::CCompareMultiMethods(func);
	compare->pushMethod(metopt::NAME_METHOD_RANDOM_SEARCH);
	compare->pushMethod(metopt::NAME_METHOD_WEIL_PI_SEARCH);
	compare->pushMethod(metopt::NAME_METHOD_WEIL_E_SEARCH);
	compare->pushMethod(metopt::NAME_METHOD_BIN_GENETIC_ALGORITHM);
	//compare->pushMethod(metopt::NAME_METHOD_CON_GENETIC_ALGORITHM);

	compare->setInterval(a, b);
	compare->setPrecision(0.01);
	compare->setStep(0.1);
	compare->setParam(2000, 3000);
	compare->setFlagExit(metopt::TYPE_EXIT_PRECISION_FUNC);

	compare->calcMethods(initPoint);
	compare->getCompareData()->printToFile("CompareMethodsU.log");

};