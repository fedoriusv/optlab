#include "MethodsSearch.h"

using namespace metopt;

CMethodsSearch::CMethodsSearch()
	: m_typeExit(TYPE_EXIT_NONE)
	
	, m_countIteration(0)
	, m_maxIteration(100)
	
	, m_countFunc(0)
	, m_maxFunc(100)
	
	, m_countBestPoint(1)
	
	, m_maxTime(10000)
	, m_countTime(0)
	
	, m_delta(0.0f)
	
	, m_funcValue(0.0f)
	, m_prevFuncValue(0.0f)
	
	, m_step(0.01f)
	, m_prevStep(0.0f)
	
	, m_precision(0.001f)
{
}

bool CMethodsSearch::isEndMethod()
{
	//calc func	count
	if ( m_maxFunc <= m_countFunc )
	{
		m_typeExit = TYPE_EXIT_FUNCTION;
		return true;
	}
	//iteration count
	if ( m_maxIteration <= m_countIteration )
	{
		m_typeExit = TYPE_EXIT_ITERATION;
		return true;
	}

	//precision
	switch( m_flagPrecisionExit )
	{
	case 0:
		return false;

	case 1:
		//step
		if ( m_precision > abs( m_step /*- m_prevStep*/ ) )
		{
			m_typeExit = TYPE_EXIT_PRECISION;
			return true;
		}
		break;

	case 2:
		//func
		if ( m_precision > abs( m_funcValue ) )
		{
			m_typeExit = TYPE_EXIT_PRECISION;
			return true;
		}
		break;

	case 3:
		//varable
		if ( m_precision > abs( m_delta ) )
		{
			m_typeExit = TYPE_EXIT_PRECISION;
			return true;
		}
		break;

	default:
		break;
	}

	return false;
}

void CMethodsSearch::setParam( const uInt	_maxIteration, 
							const uInt		_maxFuncCalc, 
							const uInt		_maxTime )
{
	m_maxIteration = _maxIteration;
	m_maxFunc = _maxFuncCalc;
	m_maxTime = _maxTime;
}

void CMethodsSearch::setPrecision( const double _precision )
{
	m_precision = _precision;
}

void CMethodsSearch::setStep( const double _step )
{
	m_step = _step;
}

void CMethodsSearch::setFlagExit( TEP_FLAG _flagExit )
{
	m_flagPrecisionExit = _flagExit;
}

uInt CMethodsSearch::getCountBestPoints() const
{
	return m_countBestPoint;
}

uInt CMethodsSearch::getCountFunc() const
{ 
	return m_countFunc;
}

uInt CMethodsSearch::getCountIteration() const
{ 
	return m_countIteration;
}

void CMethodsSearch::setTitleMethod( cpChar _title )
{
	m_pTitleMethod = _title;
}

cpChar CMethodsSearch::getTitleMethod() const
{
	return m_pTitleMethod;
}
