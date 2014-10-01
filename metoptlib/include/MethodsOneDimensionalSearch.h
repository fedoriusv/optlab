#ifndef _METHODS_ONE_DIMENSION_SEARCH_H_
#define _METHODS_ONE_DIMENSION_SEARCH_H_

#include "OneDimensionalSearch.h"

namespace metopt
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*Поиск интервала неопределенности методом Свенна*/
	class CSvenSearch : public COneDimensionalSearch
	{
	public:
		CSvenSearch(CFuncionOneDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		virtual outputParam2D calcArgMin(double _initialPoint);
	protected:
		bool checkExit(double& _funcValue);
	};

	/*Метод адаптации шага (минимин)*/
	class CAdaptationStepSearch : public COneDimensionalSearch
	{
	public:
		CAdaptationStepSearch(CFuncionOneDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		virtual outputParam2D calcArgMin(double _initialPoint);
	protected:
		bool checkExit(double& _funcValue);
	};

	/*Метод равномерного поиска (Uniform Search)*/
	class CUniformSearch : public COneDimensionalSearch
	{
	public:
		CUniformSearch(CFuncionOneDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		virtual outputParam2D calcArgMin(double _initialPoint);
	};

	/*Метод деления интервала пополам (Division 2)*/
	class CDivisionSearch : public COneDimensionalSearch
	{
	public:
		CDivisionSearch(CFuncionOneDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		virtual outputParam2D calcArgMin(double _initialPoint);
	};

	/* Метод дихотомии (Dichotomy) */
	class CDichotomySearch : public COneDimensionalSearch
	{
	public:
		CDichotomySearch(CFuncionOneDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		virtual outputParam2D calcArgMin(double _initialPoint);
	};

	/*Метод Фибоначчи*/
	class CFibonacciSearch : public COneDimensionalSearch
	{
	public:
		CFibonacciSearch(CFuncionOneDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		virtual outputParam2D calcArgMin(double _initialPoint);
	};

	/*Метод золотого сечения (Golden Section)*/
	class CGoldenSectionSearch : public COneDimensionalSearch
	{
	public:
		CGoldenSectionSearch(CFuncionOneDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		virtual outputParam2D calcArgMin(double _initialPoint);
	};

	/*Метод квадратичной интерполяции*/
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

	/*Метод кубической интерполяции*/
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