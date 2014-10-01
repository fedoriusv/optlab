#include "stdafx.h"
#include "FuncList.h"

using namespace metopt;

CFuncionOneDimensional* Parabola;
CFuncionOneDimensional* Polynomial3D;
CFuncionOneDimensional* Parabola4D;
CFuncionOneDimensional* FractionalRational;
CFuncionOneDimensional* NonSmooth;

CFuncionMultiDimensional* Paraboloid3d;
CFuncionMultiDimensional* ExtendedParaboloid3d;
CFuncionMultiDimensional* RotatedParaboloid3d;
CFuncionMultiDimensional* Rosenbrock3d;
CFuncionMultiDimensional* Z3d;
CFuncionMultiDimensional* W3d;

CFuncionMultiDimensional* RosenbrockMOD3d;
CFuncionMultiDimensional* FuncWithSin3d;
CFuncionMultiDimensional* Schwefel3d;
CFuncionMultiDimensional* Ackley3d;
CFuncionMultiDimensional* Michal3d;
CFuncionMultiDimensional* Negnevitsky3d;

//2D
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*�������� �=�^2*/
double Parabola_func0(double& _x)
{
	/*�������� ������� - �������� �=�^2
	������� ��������� � ����� (0;0)
	��������� ����� ������ - (-1;1)*/
	double func = _x * _x;
	return func;
}

/*������� 3-�� �������*/
double Polynomial3D_func1(double& _x)
{
	/*�������� ������� - ������� 3-�� �������
	������� ��������� � ����� (0;0)
	��������� ����� ������ - (-1;0.5)*/
	double func = 0.25f *_x * _x * ( _x + 3 );
	return func;
}

/*�������� �=�^4*/
double Parabola4D_func2(double& _x)
{
	/*�������� ������� - �������� �=�^4
	������� ��������� � ����� (0;0)
	��������� ����� ������ - (-1;1)	*/
	double func = _x * _x * _x * _x;
	return func;
}

/*������������������ �������*/
double FractionalRational_func3(double& _x)
{
	/*�������� ������� - ������������������ �������
	������� ��������� � ����� (0;0)
	��������� ����� ������ - (-1;1)*/
	double func = (	_x - 1.25f + 1.5625f / (_x + 1.25f) ) / 4.25f;
	return func;
}

/*��������� �������*/
double NonSmooth_func4(double& _x)
{
	/*�������� ������� - ��������� �������
	������� ��������� � ����� (0;0)
	��������� ����� ������ - (-1;0.1)*/
	double func = 0;
	if ( _x < 0 )
		func = -0.1 * _x;
	else
		func = _x;
	
	return func;
}

//3D
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Const_func5( double* _x)
{
	/*�������� ������� - ���������
	��� �������� ������ �� ������������
	�������� ���
	��������� ����� ������ - (0;0)*/	
	double func = 0;
	
	return func;
}

double Paraboloid3d_func6( double* _x )
{

	/*�������� ������� - ���������� ��������
	������� ��������� � ����� (4;4)
	��������� ����� ������ - (0;0)*/
	double func = 0;
	func = ( _x[0] - 4.0f ) * ( _x[0] - 4.0f ) + ( _x[1] - 4 ) * ( _x[1] - 4 );

	return func;
}

double ExtendedParaboloid3d_func7( double* _x )
{

	/*�������� ������� - ��������� ����������
	������� ��������� � ����� (0;0)
	��������� ����� ������ - (4;1)*/
	double func = 0;
	func = _x[0] * _x[0] + 4.0f * _x[1] * _x[1];

	return func;
}

double RotatedParaboloid3d_func8( double* _x )
{

	/*�������� ������� - ���������� ����������
	������� ������ 0 ��������� � ����� (0;0)
	��������� ����� ������ - (4;1)*/
	double func = 0;
	func = _x[0] * _x[0] + _x[1] * _x[1] - 1.2f * _x[0] * _x[1];

	return func;
}

double Rosenbrock3d_func9( double* _x )
{
	/*�������� U-������� ����������
	����� ����� � ���� ����� U � ����� ���������
	������� ��������� � ����� (1;1) � f=0
	��������� ����� ������ - (-1.2;1) � f=24.2*/
	double func = 0;
	func = 100.0f * ( (_x[1] - (_x[0] * _x[0])) * (_x[1] - (_x[0] * _x[0])) )
				+ (1.0f - _x[0]) * (1.0f - _x[0]);

	return func;
}

double Z3d_func10( double* _x )
{
	/*�������� Z-�������
	����� ����� � ���� ����� Z � ����� ����������
	������� ��������� � ����� (1;0)
	��������� ����� ������ - (-1.2;-0.4)*/
	double func = 0;
	func = 100.0f * (_x[1] - (_x[0] * _x[0] *_x[0]) + _x[0] ) *  (_x[1] - (_x[0] * _x[0] *_x[0]) + _x[0] )
			+ (_x[0] - 1.0f) * (_x[0] - 1.0f);
	
	return func;
}

double W3d_func11( double* _x )
{
	/* �������� W-�������
	����� ����� � ���� ����� W � ����� ����������
	������� ��������� � ����� (2;0)
	��������� ����� ������ - (-2.4;4)*/
	double func = 0;
	func = 5.0f * (_x[1] - _x[0] * _x[0] * _x[0] * _x[0] + 5.0f * _x[0] * _x[0] - 4.0f)
		*  (_x[1] - _x[0] * _x[0] * _x[0] * _x[0] + 5.0f * _x[0] * _x[0] - 4.0f) + (_x[0] - 2.0) * (_x[0] - 2.0);
	
	return func;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double RosenbrockMod3d_func12(double* _x)
{
	/*����������� �������� U - ������� ����������
	����� ����� � ���� ����� � � ����� ���������
	���������� ������� ��������� � �����(1; 1) � f = 0
	��������� ������� ��������� � �����(1; -1) � f = 0.5
	��������� ����� ������ - (-1.2; 1) � f = 488.4*/
	double func = 0;
	func = 100.0 * ((_x[1] * _x[1] - _x[0]) * (_x[1] * _x[1] - _x[0]))
		+ ((1.0 - _x[0]) * (1.0 - _x[0])) + 0.125 * ((1.0 - _x[1]) * (1.0 - _x[1]));

	return func;
}

double FuncWithSin3d_func13(double* _x)
{
	/*�������� ������� � ��������
	����� ��������� �����������
	���������� ������� ��������� � �����
	x = [9.038991604817884 8.6681889577870734]'
	� fx = [-18.554721077382709]'
	0 <= x <= 10*/
	double func = 0;
	func = _x[0] * sin(4.0 * _x[0]) + 1.1 * _x[1] * sin(2.0 * _x[1]);
	
	return func;
}

double Rastring3d_func14(double* _x)
{
	/*�������� ������� ����������
	����� ��������� �����������
	���������� ������� ��������� � ����� �(0; 0; ...; 0) � f = 0
	-5, 12 <= x <= 5, 12*/
	double func = 0;
	//p2 = 2 * pi;
	//f = 10 * size(x, 1) + sum(x. ^ 2 - 10 * cos(p2.*x), 1);

	return func;
}

double Schwefel3d_func14(double* _x)
{
	/*�������� ������� �������
	Schwefel�s(Sine root) function
	���������� ������� ��������� � ����� � ������������
	4.2096874619338882e2 4.2096874622355651e2]'
	� f = 2.5455132345086895e-5
	-50 <= x <= 500*/
	double func = 0;

	//f = 418.9829*size(x, 1) - sum(x.*sin(sqrt(abs(x))), 1);

	return func;
}

double Ackley3d_func14(double* _x)
{
	/*�������� ������� �����
	? ckley�s function
	���������� ������� ��������� � ����� � � ������������ 0
	� f = 0
	-30 <= x <= 30*/
	double func = 0;

	/*n = size(x, 1);
	r = 1 / n;
	e = exp(1);
	p2 = 2 * pi;
	e1 = exp(-0.2*sqrt(r*sum(x. ^ 2, 1)));
	e2 = exp(r*sum(cos(p2*x), 1));
	f = 20 + e - 20 * e1 - e2;*/

	return func;
}

double Michal3d_func14(double* _x)
{
	/*�������� ������� ����������
		Michalewicz�s function
		���������� ������� ��������� � ����� � � ������������ 0
		� f = 0
		-pi <= x <= pi*/
	double func = 0;

	/*n = size(x,1);
	r = (1:n)'/pi;
	f = - sum(sin(x).*sin(r.*x.^2),1);*/

	return func;
}

double Negnevitsky3d_func14(double* _x)
{
	/*�������� ������� ������������
	Function of Negnevitsky
	���������� ������� ��������� � ����� � ������������ 
	[4.2096874619338882e2 4.2096874622355651e2]'
	� f = 2.5455132345086895e-5
	-3 <= v <= 3*/
	double func = 0;

	/*x = v(1); y = v(2);
	f = (x - x^3 - y^3)*exp(-x^2-y^2) - (1 - x)^2*exp(-x^2-(y+1)^2);*/

	return func;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void createFunctions()
{
	Parabola = new CFuncionOneDimensional( Parabola_func0, inputParam2D(0,0), "Parabola �=�^2" );
	Polynomial3D = new CFuncionOneDimensional( Polynomial3D_func1, inputParam2D(0,0), "Polynomial3D" );
	Parabola4D = new CFuncionOneDimensional( Parabola4D_func2, inputParam2D(0,0), "Parabola �=�^4" );
	FractionalRational = new CFuncionOneDimensional( FractionalRational_func3, inputParam2D(0,0), "FractionalRational" );
	NonSmooth = new CFuncionOneDimensional( NonSmooth_func4, inputParam2D(0,0), "NonSmooth" );

	double x0[] = { 4.0, 4.0 };
	Paraboloid3d = new CFuncionMultiDimensional( Paraboloid3d_func6, inputParam(0,x0), "Paraboloid" );
	double x1[] = { 0.0, 0.0 };
	ExtendedParaboloid3d = new CFuncionMultiDimensional( ExtendedParaboloid3d_func7, inputParam(0,x1), "Extended Paraboloid" );
	double x2[] = { 0.0, 0.0 };
	RotatedParaboloid3d = new CFuncionMultiDimensional( RotatedParaboloid3d_func8, inputParam(0,x2), "Rotated Paraboloid" );
	double x3[] = { 1.0, 1.0 };
	Rosenbrock3d = new CFuncionMultiDimensional( Rosenbrock3d_func9, inputParam(0,x3), "U - func(Rosenbrock)" );
	double x4[] = { 1.0, 0.0 };
	Z3d = new CFuncionMultiDimensional( Z3d_func10, inputParam(0,x4), "Z - func" );
	double x5[] = { 2.0, 0.0 };
	W3d = new CFuncionMultiDimensional( W3d_func11, inputParam(0,x5), "W - func" );

	double x6[] = { 1.0, 1.0 };
	RosenbrockMOD3d = new CFuncionMultiDimensional(RosenbrockMod3d_func12, inputParam(0, x6), "U - func(Rosenbrock MOD)");
	double x7[] = { 9.038991604817884, 8.6681889577870734 };
	FuncWithSin3d = new CFuncionMultiDimensional(FuncWithSin3d_func13, inputParam(0, x7), "FuncWithSin");



}