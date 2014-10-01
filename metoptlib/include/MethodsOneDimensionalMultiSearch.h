#ifndef _METHODS_ONE_DIMENSION_MULTI_SEARCH_H_
#define _METHODS_ONE_DIMENSION_MULTI_SEARCH_H_

#include "MultiDimensionalSearch.h"

namespace metopt
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class COneDimensionalMultiSearch : public CMultiDimensionalSearch
	{
	protected:
		Arg						m_searchDirection;
		outputParam2D			m_multiParam;
		virtual	inputParam		calcArgMin(Arg _initialPoint)		{ return inputParam(); };
	public:
		COneDimensionalMultiSearch();
		void					setNoIteration(const uInt& _noIteration);
		void					setNoFunc(const uInt& _noFunc);
		void					setNoBestPoints(const uInt& _noBestPoints);
		virtual void			setDirection(const Arg& _direction);
		virtual	outputParam2D	calcArgMin(const inputParam& _initialPoint, Arg _direction) = 0;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*����������� ����� ��������� ���������������� ������� ������*/
	class CSvenMultiSearch : public COneDimensionalMultiSearch
	{
	public:
		CSvenMultiSearch(CFuncionMultiDimensional* _func, double _step = 0.1, double _precision = 0.01);
		virtual outputParam2D calcArgMin(const inputParam& _initialPoint, Arg _direction);
	};

	/*����� ��������� ���� (�������) ��� ������������ ������*/
	class CAdaptationStepMultiSearch : public COneDimensionalMultiSearch
	{
	public:
		CAdaptationStepMultiSearch(CFuncionMultiDimensional* _func, double _step = 0.1, double _precision = 0.01);
		virtual outputParam2D calcArgMin(const inputParam& _initialPoint, Arg _direction);
	};

	/*����� ������������ ������ (Uniform Search)*/
	class CUniformMultiSearch : public COneDimensionalMultiSearch
	{
	public:
		CUniformMultiSearch(CFuncionMultiDimensional* _func, double _step = 0.1, double _precision = 0.01);
		virtual outputParam2D calcArgMin(const inputParam& _initialPoint, Arg _direction);
	};

	/*����� ������� ��������� ������� (Division 2)*/
	class CDivisionMultiSearch : public COneDimensionalMultiSearch
	{
	public:
		CDivisionMultiSearch(CFuncionMultiDimensional* _func, double _step = 0.1, double _precision = 0.01);
		virtual outputParam2D calcArgMin(const inputParam& _initialPoint, Arg _direction);
	};

	/*����� ��������� ��� ������������ ������ (Dichotomy)*/
	class CDichotomyMultiSearch : public COneDimensionalMultiSearch
	{
	public:
		CDichotomyMultiSearch(CFuncionMultiDimensional* _func, double _step = 0.1, double _precision = 0.01);
		virtual outputParam2D calcArgMin(const inputParam& _initialPoint, Arg _direction);
	};

	/*����� ��������� ��� ������������ ������*/
	class CFibonacciMultiSearch : public COneDimensionalMultiSearch
	{
	public:
		CFibonacciMultiSearch(CFuncionMultiDimensional* _func, double _step = 0.1, double _precision = 0.01);
		virtual outputParam2D	calcArgMin(const inputParam& _initialPoint, Arg _direction);
	};

	/*����� �������� ������� ��� ������������ ������*/
	class CGoldenSectionMultiSearch : public COneDimensionalMultiSearch
	{
	public:
		CGoldenSectionMultiSearch(CFuncionMultiDimensional* _func, double _step = 0.1, double _precision = 0.01);
		virtual outputParam2D	calcArgMin(const inputParam& _initialPoint, Arg _direction);
	};

	/*����� ������������ ������������*/
	class CQuadraticInterpolationMultiSearch : public COneDimensionalMultiSearch
	{
	protected:
		bool m_interPoint;
		double max(double _value0, double _value1);
		inputParam2D formQuadraticInterpolation(outputParam2D _param);
	public:
		CQuadraticInterpolationMultiSearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001);
		virtual outputParam2D	calcArgMin(const inputParam& _initialPoint, Arg _direction);
	};

	/*����� ���������� ������������*/
	class CCubicInterpolationMultiSearch : public CQuadraticInterpolationMultiSearch
	{
	protected:
		bool m_interPoint3D;
		double min(double _value0, double _value1, double _value2);
		inputParam2D formCubicInterpolation(outputParam2D _param, inputParam2D _qParam);
	public:
		CCubicInterpolationMultiSearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001);
		virtual outputParam2D	calcArgMin(const inputParam& _initialPoint, Arg _direction);
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif