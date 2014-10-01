#ifndef _COMPARE_METHOD_H_
#define _COMPARE_METHOD_H_

#include "Param.h"


namespace metopt
{
	class CFunc;
	class CCompareData;

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	class CCompareMethods
	{
	protected:
		CFunc*						m_func;
		CCompareData*				m_comData;
		std::vector<NAME_METHOD>	m_methodList;

		double						m_precision;
		double						m_step;
		uInt						m_maxIteration;
		uInt						m_maxFuncCalc;
		uInt						m_maxTime;
		TEP_FLAG					m_flagExit;
		
	public:
		CCompareMethods(CFunc* _func);
		virtual ~CCompareMethods();

		void	pushMethod(NAME_METHOD _method);
		bool	removeMethod(NAME_METHOD _method);
		CFunc*	getFunc() const;
		void	clearList();
		CCompareData* getCompareData() const;

		void		setPrecision(const double _precision = 0.01);
		/*Задать шаг*/
		void		setStep(const double _step = 0.1);
		/*Задание параметров:
		param\n
		_maxIteration - макс. клоичество итераций
		_maxFuncCalc - макс. вычисление функций
		_maxTime - макс. время счета*/
		void		setParam(const uInt _maxIteration = 100,
			const uInt	 _maxFuncCalc = 100,
			const uInt	 _maxTime = 10000);
		/*Флаг выхода:
		список параметров в файле Param.h*/
		void		setFlagExit(TEP_FLAG _flagExit = TYPE_EXIT_PRECISION_FUNC);
		
		virtual void	calcMethods(const metopt::Arg& _initPoint) = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	class CCompareSingleMethods : public CCompareMethods
	{
	public:
		CCompareSingleMethods(CFunc* _func);
		virtual ~CCompareSingleMethods();

		virtual void	calcMethods(const metopt::Arg& _initPoint);
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	class CCompareMultiMethods : public CCompareMethods
	{
	private:
		NAME_METHOD	m_nameOneMethod;
		double		m_OnePrecision;
		interval	m_interval;

	public:
		CCompareMultiMethods(CFunc* _func);
		virtual ~CCompareMultiMethods();

		/*Задать одномерный метод для многомерног метода*/
		void			setOneDimensionalMethod(NAME_METHOD _nameMethod);
		/*Задать точность для одномерного метода*/
		void			setOneDimensionalPrecision(const double _precision = 0.01);
		void			setInterval(const Arg& _A, const Arg& _B);

		virtual void	calcMethods(const metopt::Arg& _initPoint);
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif