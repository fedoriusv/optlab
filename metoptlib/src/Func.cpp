#include "Func.h"

using namespace metopt;

CFunc::CFunc( CFOD* _func )
{
	m_nameMethod = NAME_METHOD_DIVISION;
	m_oneFunc = _func;
}

CFunc::CFunc( CFMD* _func )
{
	m_nameMethod = NAME_METHOD_BOX;
	m_multiFunc = _func;
}

void CFunc::setMethod( NAME_METHOD _nameMethod )
{
	m_nameMethod = _nameMethod;
	if ( m_nameMethod != 0 && m_nameMethod < 10 )
	{
		m_typeMethod = TYPE_ONE_DIMENSIONAL;
	}
	else
	{
		m_typeMethod = TYPE_MULTI_DIMENSIONAL;
	}

	bool suss = false;
	suss = createMethod();
}

bool CFunc::createMethod()
{
	switch( m_nameMethod )
	{
	case 0:
		return false;
	case NAME_METHOD_SVEN:
		m_oneMethod = new CSvenSearch( m_oneFunc );
		return true;
	case NAME_METHOD_ADAPTATION_STEP:
		m_oneMethod = new CAdaptationStepSearch( m_oneFunc );
		return true;
	case NAME_METHOD_UNIFORM:
		m_oneMethod = new CUniformSearch( m_oneFunc );
		return true;
	case NAME_METHOD_DIVISION:
		m_oneMethod = new CDivisionSearch( m_oneFunc );
		return true;
	case NAME_METHOD_DICHOTOMY:
		m_oneMethod = new CDichotomySearch( m_oneFunc );
		return true;
	case NAME_METHOD_FIBONACCI:
		m_oneMethod = new CFibonacciSearch( m_oneFunc );
		return true;
	case NAME_METHOD_GOLDEN_SECTION:
		m_oneMethod = new CGoldenSectionSearch( m_oneFunc );
		return true;
	case NAME_METHOD_QUADRATIC_INTERPOLATION:
		m_oneMethod = new CQuadraticInterpolationSearch( m_oneFunc );
		return true;
	case NAME_METHOD_CUBIC_INTERPOLATION:
		m_oneMethod = new CCubicInterpolationSearch( m_oneFunc );
		return true;
//---------------------------------------------------------------------------//
	case NAME_METHOD_HOOKE_JEEVES:
		m_multiMethod = new CHookeJeevesSearch( m_multiFunc );
		return true;
	case NAME_METHOD_NELDER_MEAD:
		m_multiMethod = new CNelderMeadSearch( m_multiFunc );
		return true;
	case NAME_METHOD_SIMPLEX_METHOD:
		m_multiMethod = new CSimplexSearch( m_multiFunc );
		return true;
	case NAME_METHOD_BOX:
		m_multiMethod = new CBoxingSearch( m_multiFunc );
		return true;
	case NAME_METHOD_CYCLIC_MINMIN:
		m_multiMethod = new CCyclicMinminSearch( m_multiFunc );
		return true;
	case NAME_METHOD_GAUSS_SEIDEL:
		m_multiMethod = new GaussSeidelSearch( m_multiFunc );
		return true;
	case NAME_METHOD_POWELL_SEARCH:
		m_multiMethod = new CPowellSearch( m_multiFunc );
		return true;
	case NAME_METHOD_RANDOM_SEARCH:
		m_multiMethod = new CRandomSearch( m_multiFunc );
		return true;
	case NAME_METHOD_WEIL_PI_SEARCH:
		m_multiMethod = new CWeilPISearch( m_multiFunc );
		return true;
	case NAME_METHOD_WEIL_E_SEARCH:
		m_multiMethod = new CWeilESearch( m_multiFunc );
		return true;

	case NAME_METHOD_FASTEST_DESCENT:
		m_multiMethod = new CFastestDescentSearch( m_multiFunc );
		return true;
	case NAME_METHOD_FLETCHER_REEVES:
		m_multiMethod = new CFletcherReevesSearch( m_multiFunc );
		return true;
	case NAME_METHOD_POLAK_RIBIERE:
		m_multiMethod = new CPolakRibiereSearch( m_multiFunc );
		return true;
	case NAME_METHOD_DFP_SEARCH:
		m_multiMethod = new CDFPSearch( m_multiFunc );
		return true;
	case NAME_METHOD_NEWTON_SEARCH:
		m_multiMethod = new CNewtonSearch( m_multiFunc );
		return true;
	case NAME_METHOD_NEWTON_RAPHSON:
		m_multiMethod = new CNewtonRaphsonSearch( m_multiFunc );
		return true;

	case NAME_METHOD_BIN_GENETIC_ALGORITHM:
		m_multiMethod = new CBinaryGenAlgorithmSearch(m_multiFunc);
		return true;
	case NAME_METHOD_CON_GENETIC_ALGORITHM:
		m_multiMethod = new CConGeneticAlgorithmSearch(m_multiFunc);
		return true;

	default:
		return false;
	}
}

void CFunc::setPrecision( const double _precision )
{
	switch ( m_typeMethod )
	{
	case TYPE_ONE_DIMENSIONAL:
		m_oneMethod->setPrecision( _precision );
		break;
	case TYPE_MULTI_DIMENSIONAL:
		m_multiMethod->setPrecision( _precision );
		break;
	default:
		break;
	}
}

void CFunc::setStep( const double _step )
{
	switch ( m_typeMethod )
	{
	case TYPE_ONE_DIMENSIONAL:
		m_oneMethod->setStep( _step );
		break;
	case TYPE_MULTI_DIMENSIONAL:
		m_multiMethod->setStep( _step );
		break;
	default:
		break;
	}
}

void CFunc::setParam( const uInt _maxIteration,
					const uInt	 _maxFuncCalc,
					const uInt	 _maxTime )
{
	switch ( m_typeMethod )
	{
	case TYPE_ONE_DIMENSIONAL:
		m_oneMethod->setParam( _maxIteration, _maxFuncCalc, _maxTime );
		break;
	case TYPE_MULTI_DIMENSIONAL:
		m_multiMethod->setParam( _maxIteration, _maxFuncCalc, _maxTime );
		break;
	default:
		break;
	}
}

void CFunc::setFlagExit( TEP_FLAG _flagExit )
{
	switch ( m_typeMethod )
	{
	case TYPE_ONE_DIMENSIONAL:
		m_oneMethod->setFlagExit( _flagExit );
		break;
	case TYPE_MULTI_DIMENSIONAL:
		m_multiMethod->setFlagExit( _flagExit );
		break;
	default:
		break;
	}
}

void CFunc::setOneDimensionalMethod( NAME_METHOD _nameMethod )
{
	m_multiMethod->setOneDimensionalMethod( _nameMethod );
}

void CFunc::setOneDimensionalPrecision( const double _precision )
{
	m_multiMethod->setOneDimensionalPrecision( _precision );
}

inputParam CFunc::calcArgMin( const Arg& _initialPoint )
{
	switch ( m_typeMethod )
	{
	case TYPE_ONE_DIMENSIONAL:
		return inputParamFromOutput2D( m_oneMethod->calcArgMin( _initialPoint.x[0] ) );
	case TYPE_MULTI_DIMENSIONAL:
		return m_multiMethod->calcArgMin( _initialPoint );
	default:
		return inputParam(0,0);
	}
}

CDMD* CFunc::getMultiData() const
{
	return m_multiMethod->getData();
}

CDOD* CFunc::getData() const
{
	return m_oneMethod->getData();
}

inputParam CFunc::inputParamFromOutput2D( const outputParam2D& _output2D )
{
	inputParam x;
	x.fx = _output2D.c.fx;
	x.x[0] = _output2D.c.x;

	return x;
}

CFMD* CFunc::getMultiFunc() const
{
	return m_multiFunc;
}

CFOD* CFunc::getFunc() const
{
	return m_oneFunc;
}