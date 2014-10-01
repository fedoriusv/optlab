#ifndef _METHODS_SEARCH_H_
#define _METHODS_SEARCH_H_

#include "Param.h"

namespace metopt
{
	class CMethodsSearch
	{
	protected:

		CMethodsSearch();
		TYPE_METHOD		m_typeMethod;
		TYPE_EXIT		m_typeExit;
		TEP_FLAG		m_flagPrecisionExit;

		NAME_METHOD		m_nameMethod;
		cpChar			m_pFuncName;
		cpChar			m_pTitleMethod;

		uInt			m_countIteration;
		uInt			m_maxIteration;

		uInt			m_countFunc;
		uInt			m_maxFunc;

		uInt			m_countBestPoint;

		uInt			m_maxTime;
		uInt			m_countTime;

		double			m_delta;

		double			m_funcValue;
		double			m_prevFuncValue;

		double			m_step;
		double			m_prevStep;

		double			m_precision;

		char*			m_state;

		virtual void	setTypeMesthod(TYPE_METHOD _typeMethod) = 0;

		virtual bool	isEndMethod();

	public:

		virtual	void	setParam(const uInt _maxIteration = 100,
								const uInt	 _maxFuncCalc = 100,
								const uInt	 _maxTime = 10000);
		virtual void	setPrecision(const double _precision = 0.01);
		virtual	void	setStep(const double _step = 0.1);
		virtual	void	setFlagExit(TEP_FLAG _flagExit = TYPE_EXIT_PRECISION_FUNC);
		uInt			getCountFunc() const;
		uInt			getCountBestPoints() const;
		uInt			getCountIteration() const;
		void			setTitleMethod(cpChar _title);
		cpChar			getTitleMethod() const;

	};
}
#endif