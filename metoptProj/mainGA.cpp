#include "conio.h"
#include "FuncList.h"

void mainGA()
{
	createFunctions();

	metopt::inputParam oparam;
	double x[] = { -1.2, 1.0 };
	metopt::Arg initPoint(x);

	metopt::Arg a({ -1.5, -1.5 });
	metopt::Arg b({ 1.5, 1.5 });

	metopt::CFunc* func = new metopt::CFunc(RosenbrockMOD3d);
	func->setMethod(metopt::NAME_METHOD_BIN_GENETIC_ALGORITHM);
	func->getMultiFunc()->setInterval(a,b);
	func->setPrecision(0.01);
	func->setStep(0.1);
	func->setParam(200, 1000);
	func->setFlagExit(metopt::TYPE_EXIT_PRECISION_FUNC);
	
	oparam = func->calcArgMin(initPoint);
	metopt::CDataMultiDimensional* data = func->getMultiData();
	data->printToFile("methodsGA.log");
};