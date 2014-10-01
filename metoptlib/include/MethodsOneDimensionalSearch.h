#ifndef _METHODS_ONE_DIMENSION_SEARCH_H_
#define _METHODS_ONE_DIMENSION_SEARCH_H_

#include "OneDimensionalSearch.h"

namespace metopt
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*����� ��������� ���������������� ������� ������*/
	class CSvenSearch : public COneDimensionalSearch
	{
	public:
		CSvenSearch(CFuncionOneDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		virtual outputParam2D calcArgMin(double _initialPoint);
	protected:
		bool checkExit(double& _funcValue);
	};

	/*����� ��������� ���� (�������)*/
	class CAdaptationStepSearch : public COneDimensionalSearch
	{
	public:
		CAdaptationStepSearch(CFuncionOneDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		virtual outputParam2D calcArgMin(double _initialPoint);
	protected:
		bool checkExit(double& _funcValue);
	};

	/*����� ������������ ������ (Uniform Search)*/
	class CUniformSearch : public COneDimensionalSearch
	{
	public:
		CUniformSearch(CFuncionOneDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		virtual outputParam2D calcArgMin(double _initialPoint);
	};

	/*����� ������� ��������� ������� (Division 2)*/
	class CDivisionSearch : public COneDimensionalSearch
	{
	public:
		CDivisionSearch(CFuncionOneDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		virtual outputParam2D calcArgMin(double _initialPoint);
	};

	/* ����� ��������� (Dichotomy) */
	class CDichotomySearch : public COneDimensionalSearch
	{
	public:
		CDichotomySearch(CFuncionOneDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		virtual outputParam2D calcArgMin(double _initialPoint);
	};

	/*����� ���������*/
	class CFibonacciSearch : public COneDimensionalSearch
	{
	public:
		CFibonacciSearch(CFuncionOneDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		virtual outputParam2D calcArgMin(double _initialPoint);
	};

	/*����� �������� ������� (Golden Section)*/
	class CGoldenSectionSearch : public COneDimensionalSearch
	{
	public:
		CGoldenSectionSearch(CFuncionOneDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		virtual outputParam2D calcArgMin(double _initialPoint);
	};

	/*����� ������������ ������������*/
	class CQuadraticInterpolationSearch : public COneDimensionalSearch
	{
	protected:
		bool m_interPoint;
		double max(double _value0, double _value1);
		inputParam2D formQuadraticInterpolation(outputParam2D _param);
	public:
		CQuadraticInterpolationSearch(CFuncionOneDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001);
		virtual outputParam2D calcArgMin(double _initialPoint);
	};

	/*����� ���������� ������������*/
	class CCubicInterpolationSearch : public CQuadraticInterpolationSearch
	{
	protected:
		bool m_interPoint3D;
		double min(double _value0, double _value1, double _value2);
		inputParam2D formCubicInterpolation(outputParam2D _param, inputParam2D _qParam);
	public:
		CCubicInterpolationSearch(CFuncionOneDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001);
		virtual outputParam2D calcArgMin(double _initialPoint);
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif