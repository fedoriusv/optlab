#include "OneDimensionalSearch.h"
#include <iostream>

using namespace metopt;

COneDimensionalSearch::COneDimensionalSearch()
	: m_function(0)
	
	, m_outputParam()
	, m_inputParam(0,0)
{
	m_data = new CDataOneDimensional();
	m_time = new CTimer();
	setTypeMesthod( TYPE_ONE_DIMENSIONAL );
}	

CDOD* COneDimensionalSearch::getData() const
{ 
	return m_data;
};

void COneDimensionalSearch::setTypeMesthod( TYPE_METHOD _typeMethod )
{
	m_typeMethod = _typeMethod;
}

double COneDimensionalSearch::getDeltaValue( const double& _x ) const
{
	return abs( m_optPoint.x - _x );
}

double COneDimensionalSearch::newPoint( double _x, bool _outConsole )
{
	double fx = 0;
	fx = m_function(_x);
	m_funcValue = fx;
	m_prevStep = m_step;
	//m_prevFuncValue = m_outputParam.c.fx;
	m_countFunc++;

	if ( abs(fx) < abs(m_prevFuncValue) )
	{
		m_countBestPoint++;
	}
	m_delta = getDeltaValue( _x );

	m_data->setNewPointData(m_countIteration, m_countBestPoint, m_countFunc, m_step, m_delta, inputParam2D(_x,fx), m_state);
	m_prevFuncValue = fx;

	return fx;
}

void COneDimensionalSearch::saveHeadData( cpChar _headString )
{
	m_pTitleMethod = _headString;
	m_data->setInitData( m_step, m_precision, m_inputParam, m_optPoint, m_maxIteration, m_maxFunc, m_maxTime );
};

void COneDimensionalSearch::saveFootData()
{
	m_pFuncName = m_func->getFuncionName();
	m_data->setNewPointData( m_countIteration, m_countBestPoint, m_countFunc, m_step, m_delta, m_outputParam.c, m_state );
	m_data->setEndMethodData( m_typeExit, m_flagPrecisionExit, m_outputParam, m_time->milliseconds(), m_pFuncName, m_pTitleMethod );
}