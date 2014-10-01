#ifndef _FUNC_LIST_H_
#define _FUNC_LIST_H_

#include "Methods.h"

extern metopt::CFuncionOneDimensional*		Parabola;
extern metopt::CFuncionOneDimensional*		Polynomial3D;
extern metopt::CFuncionOneDimensional*		Parabola4D;
extern metopt::CFuncionOneDimensional*		FractionalRational;
extern metopt::CFuncionOneDimensional*		NonSmooth;

extern metopt::CFuncionMultiDimensional*	Paraboloid3d;
extern metopt::CFuncionMultiDimensional*	ExtendedParaboloid3d;
extern metopt::CFuncionMultiDimensional*	RotatedParaboloid3d;
extern metopt::CFuncionMultiDimensional*	Rosenbrock3d;
extern metopt::CFuncionMultiDimensional*	Z3d;
extern metopt::CFuncionMultiDimensional*	W3d;

extern metopt::CFuncionMultiDimensional*	RosenbrockMOD3d;
extern metopt::CFuncionMultiDimensional*	FuncWithSin3d;
extern metopt::CFuncionMultiDimensional*	Rastring3d;
extern metopt::CFuncionMultiDimensional*	Schwefel3d;
extern metopt::CFuncionMultiDimensional*	Ackley3d;
extern metopt::CFuncionMultiDimensional*	Michal3d;
extern metopt::CFuncionMultiDimensional*	Negnevitsky3d;

void createFunctions();



#endif