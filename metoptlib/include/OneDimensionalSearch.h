#ifndef _ONE_DIMENSION_SEARCH_H_
#define _ONE_DIMENSION_SEARCH_H_

#include "MethodsSearch.h"
#include "Function.h"
#include "Data.h"

namespace metopt
{
	typedef CFuncionOneDimensional		CFOD;
	typedef CDataOneDimensional			CDOD;

	class COneDimensionalSearch : public CMethodsSearch
	{
	protected:
		COneDimensionalSearch();

		CTimer*					m_time;

		inputParam2D			m_inputParam;
		inputParam2D			m_optPoint;
		outputParam2D			m_outputParam;

		CDOD*					m_data;

		CFOD*					m_func;
		double					(*m_function)(double& _x);

		virtual double			newPoint(double _x, bool _outConsole);
		virtual void			setTypeMesthod(TYPE_METHOD _typeMethod);
		double					getDeltaValue(const double& _x) const;
		void					saveHeadData(cpChar _headString);
		void					saveFootData();

	public:
		CDOD*					getData() const;
		virtual	outputParam2D	calcArgMin(double _initialPoint) = 0;
	};
}
#endif