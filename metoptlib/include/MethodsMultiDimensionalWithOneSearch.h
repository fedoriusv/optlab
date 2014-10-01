#ifndef _METHODS_MULTI_DIMENSION_WITH_ONE_SEARCH_H_
#define _METHODS_MULTI_DIMENSION_WITH_ONE_SEARCH_H_

#include "MethodsOneDimensionalMultiSearch.h"

namespace metopt
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	typedef COneDimensionalMultiSearch	CODMS;
	typedef	CMultiDimensionalSearch		CMDS;

	class CMultiDimensionalWithOneSearch : public CMultiDimensionalSearch
	{
	protected:
		CMultiDimensionalWithOneSearch();
		bool					m_exitFlag;
		bool					m_interval;
		double					m_S;
		double					m_H;

		Arg						m_grad;
		Arg*					m_Hes;

		inputParam				m_prevOutputParam;

		CODMS*					m_oneDimMultiSearch;
		CODMS*					createOneDimMethod() const;
		void					applyParam(const CODMS* _method);

		bool					iterGrad(const Arg& _input);
		Arg						getAgrad(inputParam& _input);
		Arg*					getHes(const inputParam& _input, Arg* _Hes);

		double					max(const double& _value0, const double& _value1, const double& _value2) const;
		double					getFuncValue(double * _x);
		Arg*					setEye(Arg* _matrix) const;

		virtual double			stepSearch(const inputParam& _input, const inputParam& _output);
		Arg						matrixProduct(const Arg* _matrix, const Arg& _vector) const;

		double					getGradProduct(const Arg& _transpGrad, const Arg& _grad) const;
		Arg*					getVectorProduct(const Arg& _vector, const Arg& _transpVector, Arg* _matrix) const;
		Arg*					getInvMatrix(const Arg* _matrix, Arg* _invMatrix) const;
		double					gedMatixDeter(const Arg* _matrix, const int& _count) const;
		Arg*					subMatrix(const Arg* _matrix, const uInt _col, uInt _row) const;
	public:
		virtual	bool			itSearch(const Arg& _direction);
		virtual	inputParam		calcArgMin(Arg _initialPoint) = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*Метод Гаусса-Зейделя покоординатного спуска*/
	class GaussSeidelSearch : public CMultiDimensionalWithOneSearch
	{
	public:
		GaussSeidelSearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		inputParam	calcArgMin(Arg _initialPoint);
	};

	/*Метод Пауэлла сопряженных направлений*/
	class CPowellSearch : public CMultiDimensionalWithOneSearch
	{
	protected:
		Arg* setEye(Arg* _matrix);
	public:
		CPowellSearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		inputParam	calcArgMin(Arg _initialPoint);
	};

	/*Метод наискорейшего спуска*/
	class CFastestDescentSearch : public CMultiDimensionalWithOneSearch
	{
	protected:
		bool m_flagExit;
	public:
		CFastestDescentSearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		inputParam	calcArgMin(Arg _initialPoint);
	};

	/*Метод Флетчера-Ривса сопряженных градиентов*/
	class CFletcherReevesSearch : public CMultiDimensionalWithOneSearch
	{
	protected:
		bool m_flagExit;
	public:
		CFletcherReevesSearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		inputParam	calcArgMin(Arg _initialPoint);
	};

	/*Метод Полака-Рибьера сопряженных градиентов*/
	class CPolakRibiereSearch : public CMultiDimensionalWithOneSearch
	{
	protected:
		bool	m_flagExit;
	public:
		CPolakRibiereSearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		inputParam	calcArgMin(Arg _initialPoint);
	};

	/*Метод ДФП переменной метрики*/
	class CDFPSearch : public CMultiDimensionalWithOneSearch
	{
	protected:
		bool	m_flagExit;
	public:
		CDFPSearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		inputParam	calcArgMin(Arg _initialPoint);
	};

	/*Метод Ньютона*/
	class CNewtonSearch : public CMultiDimensionalWithOneSearch
	{
	protected:
		bool	m_flagExit;
	public:
		CNewtonSearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		inputParam	calcArgMin(Arg _initialPoint);
	};

	/*Метод Ньютона-Рафсона*/
	class CNewtonRaphsonSearch : public CMultiDimensionalWithOneSearch
	{
	protected:
		bool	m_flagExit;
		int		getRank(const Arg* _matrix) const;
	public:
		CNewtonRaphsonSearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		inputParam	calcArgMin(Arg _initialPoint);
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif