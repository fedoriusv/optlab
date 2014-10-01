#include "MultiDimensionalSearch.h"

using namespace metopt;

CMultiDimensionalSearch::CMultiDimensionalSearch()
	: m_dimensions(0)
	
	, m_oneDimPrecision(0.01)
	, m_nameOneDimMethod( NAME_METHOD_SVEN )
	
	, m_function(0)
{	
	m_data = new CDataMultiDimensional();
	m_time = new CTimer();
	setTypeMesthod( TYPE_MULTI_DIMENSIONAL );
}

CDMD* CMultiDimensionalSearch::getData() const
{
	return m_data;
}

void CMultiDimensionalSearch::setTypeMesthod( TYPE_METHOD _typeMethod )
{
	m_typeMethod = _typeMethod;
}

void CMultiDimensionalSearch::setOneDimensionalMethod( const NAME_METHOD _nameMethod )
{
	m_nameOneDimMethod = _nameMethod;
}

void CMultiDimensionalSearch::setOneDimensionalPrecision ( const double _precision )
{
	m_oneDimPrecision = _precision;
}

inputParam CMultiDimensionalSearch::getOptPoint() const
{
	return m_outputParam;
}

double CMultiDimensionalSearch::getDeltaValue( const Arg& _x ) const
{
	return m_optPoint.x.getDotProduct( _x );
}

double CMultiDimensionalSearch::newPoint( double* _x, bool _outConsole )
{
	double fx = 0;
	fx = m_function(_x);
	m_funcValue = fx;
	m_prevStep = m_step;
	//m_prevFuncValue = m_outputParam.fx;
	m_countFunc++;

	if ( abs(fx) < abs(m_prevFuncValue) )
	{
		m_countBestPoint++;
	}
	m_delta = getDeltaValue( _x );

	m_data->setNewPointData( m_countIteration, m_countBestPoint, m_countFunc, m_step, m_delta, inputParam( fx,_x ), m_state );
	
	m_prevFuncValue = fx;
	return fx;
}

void CMultiDimensionalSearch::saveHeadData( cpChar _headString )
{
	m_pTitleMethod = _headString;
	m_data->setInitData( m_dimensions, m_step , m_precision, m_inputParam , m_optPoint, m_maxIteration, m_maxFunc, m_maxTime );
};

void CMultiDimensionalSearch::saveFootData()
{
	m_pFuncName = m_func->getFuncionName();
	m_data->setNewPointData( m_countIteration, m_countBestPoint, m_countFunc, m_step, m_delta, m_outputParam, m_state );
	m_data->setEndMethodData( m_typeExit, m_flagPrecisionExit, m_outputParam, m_time->milliseconds(), m_pFuncName, m_pTitleMethod );
}