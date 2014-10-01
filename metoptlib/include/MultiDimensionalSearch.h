#ifndef _MULTI_DIMENSION_SEARCH_H_
#define _MULTI_DIMENSION_SEARCH_H_

#include "OneDimensionalSearch.h"

namespace metopt
{
	typedef COneDimensionalSearch		CODS;
	typedef CFuncionMultiDimensional	CFMD;
	typedef CDataMultiDimensional		CDMD;

	class CMultiDimensionalSearch : public CMethodsSearch
	{
	protected:
		CMultiDimensionalSearch();

		uInt				m_dimensions;

		double				m_oneDimPrecision;
		NAME_METHOD			m_nameOneDimMethod;

		CTimer*				m_time;

		inputParam			m_outputParam;
		inputParam			m_optPoint;
		inputParam			m_inputParam;

		CDMD*				m_data;

		CFMD*				m_func;
		double				(*m_function)(double* _x);

		virtual double		newPoint(double* _x, bool _outConsole);
		virtual void		setTypeMesthod(TYPE_METHOD _typeMethod);
		double				getDeltaValue(const Arg& _x) const;
		void				saveHeadData(cpChar _headString);
		void				saveFootData();

	public:
		virtual	void		setOneDimensionalMethod(const NAME_METHOD	_nameMethod);
		virtual	void		setOneDimensionalPrecision(const double _precision);
		virtual	inputParam	calcArgMin(Arg _initialPoint) = 0;
		CDMD*				getData() const;
		inputParam			getOptPoint() const;
	};
}
#endif