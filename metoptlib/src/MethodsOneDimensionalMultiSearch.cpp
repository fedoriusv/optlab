#include "MethodsOneDimensionalMultiSearch.h"

using namespace metopt;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

COneDimensionalMultiSearch::COneDimensionalMultiSearch()
	: m_searchDirection( m_dimensions )
{
}

void COneDimensionalMultiSearch::setDirection( const Arg& _direction )
{
	m_searchDirection = _direction;
}

void COneDimensionalMultiSearch::setNoIteration( const uInt& _noIteration )
{
	m_countIteration = _noIteration;
}

void COneDimensionalMultiSearch::setNoFunc( const uInt& _noFunc )
{
	m_countFunc = _noFunc;
}

void COneDimensionalMultiSearch::setNoBestPoints( const uInt& _noBestPoints )
{
	m_countBestPoint = _noBestPoints;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Многомерный поиск интервала неопределенности методом Свенна*/
CSvenMultiSearch::CSvenMultiSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
{
	m_nameMethod = NAME_METHOD_SVEN;
	m_step = _step;
	m_precision = _precision;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

outputParam2D CSvenMultiSearch::calcArgMin( const inputParam& _initialPoint, Arg _direction )
{
	saveHeadData( " Sven MultiSearch " );
	setDirection( _direction );
		
	m_multiParam.c.x = m_multiParam.a.x = 0;
	m_multiParam.a.fx = m_multiParam.c.fx = _initialPoint.fx;
	
	Arg Y;

	m_step = 1.0f;
	m_state = "interval";

	m_multiParam.b.x = m_multiParam.c.x + m_step;
	Y = _initialPoint.x + _direction * m_multiParam.b.x; 
	m_multiParam.b.fx = newPoint( Y.getPointer(), false );

	if ( m_multiParam.b.fx < m_multiParam.c.fx )
	{
		while( m_multiParam.b.fx < m_multiParam.c.fx )
		{
			m_state = "foward";
			m_multiParam.a = m_multiParam.c;
			m_multiParam.c = m_multiParam.b;
			m_step += m_step;
			m_multiParam.b.x += m_step;

			Y = _initialPoint.x + _direction * m_multiParam.b.x; 
			m_multiParam.b.fx = newPoint( Y.getPointer(), false );
			if ( isEndMethod())
			{
				m_outputParam.fx = m_multiParam.b.fx;
				m_outputParam.x = Y;
				break;
			}
		}
	}
	else
	{
		m_state = "back";
		m_step *= -1;
		m_multiParam.a.x = m_multiParam.c.x + m_step;
		Y = _initialPoint.x + _direction * m_multiParam.a.x;
		m_multiParam.a.fx = newPoint( Y.getPointer(), false );
		if ( isEndMethod())
		{
			m_outputParam.fx = m_multiParam.a.fx;
			m_outputParam.x = Y;
		}

		while( m_multiParam.a.fx < m_multiParam.c.fx )
		{
			m_multiParam.b = m_multiParam.c;
			m_multiParam.c = m_multiParam.a;
			m_step += m_step;
			m_multiParam.a.x += m_step;
			Y = _initialPoint.x + _direction * m_multiParam.a.x;
			m_multiParam.a.fx = newPoint( Y.getPointer(), false );
			if ( isEndMethod())
			{
				m_outputParam.fx = m_multiParam.a.fx;
				m_outputParam.x = Y;
				break;
			}
		}
	}

	if ( !isEndMethod())
	{
		m_outputParam.fx = m_multiParam.c.fx;
		m_outputParam.x	= Y;
	}

	m_state = "end";
	saveFootData();
		
	return m_multiParam;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод адаптации шага (минимин) для многомерного поиска*/
CAdaptationStepMultiSearch::CAdaptationStepMultiSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
{
	m_nameMethod = NAME_METHOD_ADAPTATION_STEP;
	m_step = _step;
	m_precision = _precision;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

outputParam2D CAdaptationStepMultiSearch::calcArgMin( const inputParam& _initialPoint, Arg _direction )
{
	saveHeadData( " AdaptationStep MultiSearch " );
	setDirection( _direction );
	
	double r = 0;
	double x = 0;
	m_step = 1.0f;

	inputParam fx = _initialPoint;
	inputParam y;
	
	m_state = "foward";
	Arg Y;

	while ( abs(m_step) > m_precision )
	{
		x += m_step;
		Y = _initialPoint.x + _direction * x;
		y.fx = newPoint( Y.getPointer(), false );
		if ( isEndMethod())
		{
			m_outputParam.fx = y.fx;
			m_outputParam.x = Y;
			break;
		}
		if ( y.fx < fx.fx )
		{
			fx.fx = y.fx;
			m_state = "foward";
			if ( r >= 0.5f )
			{
				r = 2.0f;
			}
			else
			{
				r = 0.5f;
			}
		}
		else
		{
			x -= m_step;
			m_state = "back";
			if ( r ==2.0 )
			{
				r = 0.25f;
			}
			else
			{
				r = -0.5f;
			}
		}
		m_step *= r;
	}

	if ( abs(m_step) < m_precision )
	{
		m_outputParam.fx = y.fx;
		m_outputParam.x = Y;
	}

	return m_multiParam;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод равномерного поиска (Uniform Search)*/
CUniformMultiSearch::CUniformMultiSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
{
	m_nameMethod = NAME_METHOD_UNIFORM;
	m_step = _step;
	m_precision = _precision;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
	m_prevFuncValue = m_inputParam.fx;
}

outputParam2D CUniformMultiSearch::calcArgMin( const inputParam& _initialPoint, Arg _direction )
{
	saveHeadData(" Uniform MultiSearch ");
	setDirection( _direction );
	
	COneDimensionalMultiSearch* searchInterval = new CSvenMultiSearch( m_func, m_step, m_precision );
	searchInterval->setParam( m_maxIteration, m_maxFunc, m_maxTime );

	searchInterval->setNoIteration( m_countIteration );
	searchInterval->setNoFunc( m_countFunc );
	searchInterval->setNoBestPoints( m_countBestPoint );

	m_multiParam = searchInterval->calcArgMin( _initialPoint, m_searchDirection );
	
	m_prevFuncValue = m_multiParam.c.fx;
	m_countFunc = searchInterval->getCountFunc();
	m_countBestPoint = searchInterval->getCountBestPoints();
	m_countIteration = searchInterval->getCountIteration();
	m_outputParam = _initialPoint;

	m_data->addCalcData( searchInterval->getData() );
	Arg Y;

	double d = m_multiParam.b.x - m_multiParam.a.x;
	m_state = "uniform";
	double n = d / 0.5f;
	m_step = d / ( n + 1);
	m_multiParam.c.x = m_multiParam.a.x + m_step;
	Y = _initialPoint.x + m_searchDirection * m_multiParam.c.x;
	m_multiParam.c.fx = newPoint( Y.getPointer(), false );
	if ( isEndMethod())
	{
		m_outputParam.fx = m_multiParam.c.fx;
		m_outputParam.x = Y;
	}

	inputParam2D v;
	v = m_multiParam.c;

	for ( uInt i = 1; i < n; ++i )
	{
		v.x += m_step;
		Y = _initialPoint.x + m_searchDirection * v.x;
		v.fx = newPoint( Y.getPointer(), false );

		if ( v.fx < m_outputParam.fx )
		{
			m_outputParam.fx = v.fx;
			m_outputParam.x = Y;
		}

		if ( isEndMethod())
		{
			m_outputParam.fx = v.fx;
			m_outputParam.x = Y;
			break;
		}

		if ( m_multiParam.c.fx < v.fx )
		{
			m_multiParam.c = v;
		}
	}
	
	/*m_outputParam.fx = v.fx;
	m_outputParam.x = Y;*/

	return m_multiParam;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод деления интервала пополам (Division 2)*/
CDivisionMultiSearch::CDivisionMultiSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
{
	m_nameMethod = NAME_METHOD_DIVISION;
	m_step = _step;
	m_precision = _precision;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

outputParam2D CDivisionMultiSearch::calcArgMin( const inputParam& _initialPoint, Arg _direction )
{
	saveHeadData(" Division MultiSearch ");
	
	setDirection( _direction );

	COneDimensionalMultiSearch* searchInterval = new CSvenMultiSearch( m_func, m_step, m_precision );
	searchInterval->setParam( m_maxIteration, m_maxFunc, m_maxTime );

	searchInterval->setNoIteration( m_countIteration );
	searchInterval->setNoFunc( m_countFunc );
	searchInterval->setNoBestPoints( m_countBestPoint );

	outputParam2D param;
	param = searchInterval->calcArgMin( _initialPoint, m_searchDirection );
	
	m_prevFuncValue = param.c.fx;
	m_countFunc = searchInterval->getCountFunc();
	m_countBestPoint = searchInterval->getCountBestPoints();
	m_countIteration = searchInterval->getCountIteration();
	
	m_multiParam = param; 
	m_data->addCalcData( searchInterval->getData() );
	

	Arg Y;
	inputParam2D u;
	inputParam2D v;

	m_state = "division";
	m_multiParam.c.x = ( m_multiParam.a.x + m_multiParam.b.x ) / 2.0f;
	Y = _initialPoint.x + m_searchDirection * m_multiParam.c.x;
	m_multiParam.c.fx = newPoint( Y.getPointer(), false );
	if ( isEndMethod())
	{
		m_outputParam.fx = m_multiParam.c.fx;
		m_outputParam.x = Y;
	}
	double d = m_multiParam.b.x - m_multiParam.a.x;

	while  ( abs(d) > m_precision )
	{
		u.x = ( m_multiParam.a.x + m_multiParam.c.x ) / 2.0f;
		d = u.x - m_multiParam.a.x;
		m_step = u.x - m_multiParam.a.x;
		Y = _initialPoint.x + m_searchDirection * u.x;
		u.fx = newPoint( Y.getPointer(), false );
		if ( isEndMethod())
		{
			m_outputParam.fx = u.fx;
			m_outputParam.x = Y;
			break;
		}
		if ( u.fx < m_multiParam.c.fx )
		{
			m_state = "left";
			m_multiParam.b.x = m_multiParam.c.x;
			m_multiParam.c = u;
		}
		else
		{
			v.x = ( m_multiParam.c.x + m_multiParam.b.x ) / 2.0f;
			Y = _initialPoint.x + m_searchDirection * v.x;
			v.fx = newPoint( Y.getPointer(), false );
			if ( isEndMethod())
			{
				m_outputParam.fx = v.fx;
				m_outputParam.x = Y;
				break;
			}
			if ( v.fx < m_multiParam.c.fx )
			{
				m_state = "right";
				m_multiParam.a.x = m_multiParam.c.x;
				m_multiParam.c = v;
			}
			else
			{
				m_state = "middle";
				m_multiParam.a.x = u.x;
				m_multiParam.b.x = v.x;
			}
		}
	}

	if ( abs(d) < m_precision )
	{
		m_outputParam.fx = m_multiParam.c.fx;
		m_outputParam.x = Y;
	}

	return m_multiParam;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод дихотомии для многомерного поиска (Dichotomy)*/
CDichotomyMultiSearch::CDichotomyMultiSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
{
	m_nameMethod = NAME_METHOD_DICHOTOMY;
	m_step = _step;
	m_precision = _precision;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

outputParam2D CDichotomyMultiSearch::calcArgMin( const inputParam& _initialPoint, Arg _direction )
{
	saveHeadData(" Dichotomy MultiSearch ");
	setDirection( _direction );
	
	COneDimensionalMultiSearch* searchInterval = new CSvenMultiSearch( m_func, m_step, m_precision );
	searchInterval->setParam( m_maxIteration, m_maxFunc, m_maxTime );

	searchInterval->setNoIteration( m_countIteration );
	searchInterval->setNoFunc( m_countFunc );
	searchInterval->setNoBestPoints( m_countBestPoint );

	m_multiParam = searchInterval->calcArgMin( _initialPoint, m_searchDirection );
	
	m_prevFuncValue = m_multiParam.c.fx;
	m_countFunc = searchInterval->getCountFunc();
	m_countBestPoint = searchInterval->getCountBestPoints();
	m_countIteration = searchInterval->getCountIteration();
	
		
	m_data->addCalcData( searchInterval->getData() );
	Arg Y;
	inputParam2D u;
	inputParam2D v;

	m_state = "dichotomy";
	m_step = m_precision / 8.0f;
	double d = m_multiParam.b.x - m_multiParam.a.x;

	while ( abs(d) > m_precision )
	{
		m_multiParam.c.x = ( m_multiParam.a.x + m_multiParam.b.x ) / 2.0f;
		u.x = m_multiParam.c.x - m_step;
		Y = _initialPoint.x + m_searchDirection * u.x;
		u.fx = newPoint( Y.getPointer(), false );
		if ( isEndMethod())
		{
			m_outputParam.fx = u.fx;
			m_outputParam.x = Y;
			break;
		}
		v.x = m_multiParam.c.x + m_step;
		Y = _initialPoint.x + m_searchDirection * v.x;
		d = v.x - m_multiParam.a.x;
		v.fx = newPoint( Y.getPointer(), false );
		if ( isEndMethod())
		{
			m_outputParam.fx = v.fx;
			m_outputParam.x = Y;
			break;
		}

		if ( u.fx < v.fx )
		{
			m_state = "left";
			m_multiParam.b.x = v.x;
		}
		else
		{
			m_state = "right";
			m_multiParam.a.x = u.x;
		}
	}
	
	if ( abs(d) < m_precision )
	{
		m_outputParam.fx = u.fx;
		m_outputParam.x = Y;
	}

	return m_multiParam;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод Фибоначчи для многомерного поиска*/
CFibonacciMultiSearch::CFibonacciMultiSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
{
	m_nameMethod = NAME_METHOD_FIBONACCI;
	m_step = _step;
	m_precision = _precision;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

outputParam2D CFibonacciMultiSearch::calcArgMin( const inputParam& _initialPoint, Arg _direction )
{
	saveHeadData(" Fibonacci MultiSearch ");
	setDirection( _direction );
	
	COneDimensionalMultiSearch* searchInterval = new CSvenMultiSearch( m_func, m_step, m_precision );
	searchInterval->setParam( m_maxIteration, m_maxFunc, m_maxTime );

	searchInterval->setNoIteration( m_countIteration );
	searchInterval->setNoFunc( m_countFunc );
	searchInterval->setNoBestPoints( m_countBestPoint );

	m_multiParam = searchInterval->calcArgMin( _initialPoint, m_searchDirection );
	
	m_prevFuncValue = m_multiParam.c.fx;
	m_countFunc = searchInterval->getCountFunc();
	m_countBestPoint = searchInterval->getCountBestPoints();
	m_countIteration = searchInterval->getCountIteration();
		
	m_data->addCalcData( searchInterval->getData() );
	
	inputParam2D u;
	inputParam2D v;

	Arg Y;

	double d = m_multiParam.b.x - m_multiParam.a.x;
	double F0 = 1;
	double F1 = 1;
	double F = F0 + F1;

	while( d > m_precision * F )
	{
		F0 = F1;
		F1 = F;
		F = F0 + F1;
	}

	m_state = "fibonacci";
	d = d * F0 / F;
	m_step = d;
	u.x = m_multiParam.a.x + d;
	Y = _initialPoint.x + m_searchDirection * u.x;
	u.fx = newPoint( Y.getPointer(), false );
	if ( isEndMethod())
	{
		m_outputParam.fx = u.fx;
		m_outputParam.x = Y;
	}

	v.x = m_multiParam.b.x - d;
	Y = _initialPoint.x + m_searchDirection * v.x;
	v.fx = newPoint( Y.getPointer(), false );
	if ( isEndMethod())
	{
		m_outputParam.fx = v.fx;
		m_outputParam.x = Y;
	}

	while ( abs(d) > m_precision )
	{
		d = v.x - u.x;
		m_step = d;
		if ( u.fx < v.fx )
		{
			m_state = "left";
			m_multiParam.b.x = v.x;
			v = u;
			u.x = m_multiParam.a.x + d;
			Y = _initialPoint.x + m_searchDirection * u.x;
			u.fx = newPoint( Y.getPointer(), false );
			if ( isEndMethod())
			{
				m_outputParam.fx =u.fx;
				m_outputParam.x = Y;
				break;
			}
		}
		else
		{
			m_state = "right";
			m_multiParam.a.x = u.x;
			u = v;
			v.x = m_multiParam.b.x - d;
			Y = _initialPoint.x + m_searchDirection * v.x;
			v.fx = newPoint( Y.getPointer(), false );
			if ( isEndMethod())
			{
				m_outputParam.fx = v.fx;
				m_outputParam.x = Y;
				break;
			}
		}
	}

	if ( abs(d) < m_precision )
	{
		m_outputParam.fx = v.fx;
		m_outputParam.x = Y;
	}
		
	return m_multiParam;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод золотого сечения для многомерного поиска*/
CGoldenSectionMultiSearch::CGoldenSectionMultiSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
{
	m_nameMethod = NAME_METHOD_GOLDEN_SECTION;
	m_step = _step;
	m_precision = _precision;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

outputParam2D CGoldenSectionMultiSearch::calcArgMin( const inputParam& _initialPoint, Arg _direction )
{
	saveHeadData(" GoldenSection MultiSearch ");
	setDirection( _direction );
	
	COneDimensionalMultiSearch* searchInterval = new CSvenMultiSearch( m_func, m_step, m_precision );
	searchInterval->setParam( m_maxIteration, m_maxFunc, m_maxTime );

	searchInterval->setNoIteration( m_countIteration );
	searchInterval->setNoFunc( m_countFunc );
	searchInterval->setNoBestPoints( m_countBestPoint );

	m_multiParam = searchInterval->calcArgMin( _initialPoint, m_searchDirection );
	
	m_prevFuncValue = m_multiParam.c.fx;
	m_countFunc = searchInterval->getCountFunc();
	m_countBestPoint = searchInterval->getCountBestPoints();
	m_countIteration = searchInterval->getCountIteration();
		
	m_data->addCalcData( searchInterval->getData() );
	
	Arg Y;
	inputParam2D x;
	inputParam2D y;

	m_state = "section";
	double t = ( sqrt(5.0f) - 1 ) / 2.0f;
	m_step = t * ( m_multiParam.b.x - m_multiParam.a.x );
	x.x = m_multiParam.b.x - m_step;
	y.x = m_multiParam.a.x + m_step;
	double d = m_step;
	m_step = y.x - x.x;

	Y = _initialPoint.x + m_searchDirection * x.x;
	x.fx = newPoint( Y.getPointer(), false );
	if ( isEndMethod())
	{
		m_outputParam.fx = x.fx;
		m_outputParam.x = Y;
	}
	Y = _initialPoint.x + m_searchDirection * y.x;
	y.fx = newPoint( Y.getPointer(), false );
	if ( isEndMethod())
	{
		m_outputParam.fx = y.fx;
		m_outputParam.x = Y;
	}

	while ( abs(d) > m_precision )
	{
		if ( x.fx < y.fx )
		{
			m_state = "left";
			m_multiParam.b.x = y.x;
			y = x;
			d = m_multiParam.b.x - m_multiParam.a.x;
			x.x = m_multiParam.b.x - t * d;
			m_step = y.x - x.x;

			Y = _initialPoint.x + m_searchDirection * x.x;
			x.fx = newPoint( Y.getPointer(), false );
			if ( isEndMethod())
			{
				m_outputParam.fx = x.fx;
				m_outputParam.x = Y;
				break;
			}
		}
		else
		{
			m_state = "right";
			m_multiParam.a.x = x.x;
			x = y;
			d = m_multiParam.b.x - m_multiParam.a.x;
			y.x = m_multiParam.a.x + t * d;
			m_step = y.x - x.x;

			Y = _initialPoint.x + m_searchDirection * y.x;
			y.fx = newPoint( Y.getPointer(), false );
			if ( isEndMethod())
			{
				m_outputParam.fx = y.fx;
				m_outputParam.x = Y;
				break;
			}
		}
	}

	if ( abs(d) < m_precision )
	{
		m_outputParam.fx = y.fx;
		m_outputParam.x = Y;
	}
	
	return m_multiParam;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод квадратичной интерполяции*/
CQuadraticInterpolationMultiSearch::CQuadraticInterpolationMultiSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
{
	m_nameMethod = NAME_METHOD_QUADRATIC_INTERPOLATION;
	m_step = _step;
	m_precision = _precision;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

outputParam2D CQuadraticInterpolationMultiSearch::calcArgMin( const inputParam& _initialPoint, Arg _direction )
{
	saveHeadData(" QuadraticInterpolation MultiSearch ");
	setDirection( _direction );
	
	COneDimensionalMultiSearch* searchInterval = new CSvenMultiSearch( m_func, m_step, m_precision );
	searchInterval->setParam( m_maxIteration, m_maxFunc, m_maxTime );

	searchInterval->setNoIteration( m_countIteration );
	searchInterval->setNoFunc( m_countFunc );
	searchInterval->setNoBestPoints( m_countBestPoint );

	m_multiParam = searchInterval->calcArgMin( _initialPoint, m_searchDirection );
	
	m_prevFuncValue = m_multiParam.c.fx;
	m_countFunc = searchInterval->getCountFunc();
	m_countBestPoint = searchInterval->getCountBestPoints();
	m_countIteration = searchInterval->getCountIteration();
	m_outputParam = _initialPoint;	
	m_data->addCalcData( searchInterval->getData() );
	
	Arg Y;
	m_step = m_multiParam.b.x - m_multiParam.a.x;
	m_state = "parabola";
	
	inputParam2D v(0,0);
	double B(0);

	while( abs(m_step) > m_precision )
	{
		v = formQuadraticInterpolation( m_multiParam );

		if (m_interPoint)
		{
			m_state = "target non reached";
		}
		m_step = v.x - m_multiParam.c.x;
		Y = _initialPoint.x + m_searchDirection * v.x;
		v.fx = newPoint( Y.getPointer(), true );
		if ( isEndMethod( ) )
		{
			m_outputParam.fx = v.fx;
			m_outputParam.x = Y;
			break;
		}

		B = max(sign(m_step),0);
		if ( v.fx < m_multiParam.c.fx )
		{
			if (B)
			{
				m_multiParam.a = m_multiParam.c;
				m_state = "right";
			}
			else
			{
				m_multiParam.b = m_multiParam.c;
				m_state = "left";
			}
			m_multiParam.c = v;
		}
		else
		{
			if (B)
			{
				m_multiParam.b = v;
				m_state = "left";
			}
			else
			{
				m_multiParam.a = v;
				m_state = "right";
			}
		}
	}

	if ( abs(m_step) < m_precision )
	{
		if ( v.fx < _initialPoint.fx )
		{
			m_outputParam.fx = v.fx;
			m_outputParam.x = Y;
		}
	}
	
	return m_multiParam;
}

double CQuadraticInterpolationMultiSearch::max(double _value0, double _value1 )
{
	return ( _value0 >= _value1 ) ? _value0 : _value1;
};

inputParam2D CQuadraticInterpolationMultiSearch::formQuadraticInterpolation( outputParam2D _param )
{
	m_interPoint  = false;
	inputParam2D v(0,0);

	v.x = _param.c.x;
	double p;
	double q;
	double s;

	p = ( _param.b.x - _param.c.x ) * ( _param.a.fx - _param.c.fx );
	q = ( _param.c.x - _param.a.x ) * ( _param.b.fx - _param.c.fx );
	s = p + q;

	if ( s <= 0 )
	{
		m_interPoint = true;
		return v;
	}

	v.x = ( p * (_param.b.x + _param.c.x) + q * (_param.a.x + _param.c.x) ) / ( 2.0f * s );
	if ( v.x <= _param.a.x || v.x >= _param.b.x )
	{
		m_interPoint = true;
	}

	return v;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод кубической интерполяции*/
CCubicInterpolationMultiSearch::CCubicInterpolationMultiSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
	:
CQuadraticInterpolationMultiSearch( _func, _step, _precision )
{
	m_nameMethod = NAME_METHOD_CUBIC_INTERPOLATION;
	m_step = _step;
	m_precision = _precision;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

outputParam2D CCubicInterpolationMultiSearch::calcArgMin( const inputParam& _initialPoint, Arg _direction )
{
	saveHeadData(" CubicInterpolation MultiSearch ");
	setDirection( _direction );
	
	COneDimensionalMultiSearch* searchInterval = new CSvenMultiSearch( m_func, m_step, m_precision );
	searchInterval->setParam( m_maxIteration, m_maxFunc, m_maxTime );

	searchInterval->setNoIteration( m_countIteration );
	searchInterval->setNoFunc( m_countFunc );
	searchInterval->setNoBestPoints( m_countBestPoint );

	m_multiParam = searchInterval->calcArgMin( _initialPoint, m_searchDirection );
	
	m_prevFuncValue = m_multiParam.c.fx;
	m_countFunc = searchInterval->getCountFunc();
	m_countBestPoint = searchInterval->getCountBestPoints();
	m_countIteration = searchInterval->getCountIteration();
	m_outputParam = _initialPoint;	
	m_data->addCalcData( searchInterval->getData() );
	
	Arg Y;
	m_state = "parabola";
	
	inputParam2D v(0,0);
	inputParam2D w(0,0);
	double d(0);
	v = formQuadraticInterpolation( m_multiParam );
	if (m_interPoint)
	{
		m_state = "target non reached";
	}
	d = v.x - m_multiParam.c.x;
	m_step = d;
	if ( abs(d) <= m_precision )
	{
		m_state = "target non reached";
	}

	Y = _initialPoint.x + m_searchDirection * v.x;
	v.fx = newPoint( Y.getPointer(), true );
	if ( isEndMethod( ) )
	{
		m_outputParam.fx = v.fx;
		m_outputParam.x = Y;
	}

	if ( v.x < m_multiParam.c.x )
	{
		w = m_multiParam.c;
		m_multiParam.c = v;
		v = w;
	}
	m_state = "cubic";

	while( abs(d) > m_precision )
	{
		w = formCubicInterpolation( m_multiParam, v );
		if (m_interPoint3D)
		{
			m_state = "target non reached";
		}

		d = min(abs(v.x - m_multiParam.c.x),abs(w.x - m_multiParam.c.x),abs(v.x - w.x));
		if ( d <= m_precision )
		{
			break;
		}
		m_step = d;

		Y = _initialPoint.x + m_searchDirection * w.x;
		w.fx = newPoint( Y.getPointer(), true );
		if ( isEndMethod( ) )
		{
			m_outputParam.fx = w.fx;
			m_outputParam.x = Y;
			break;
		}
		
		if ( m_multiParam.c.fx < v.fx )
		{
			m_multiParam.b = v;

			m_state = "left";
			if ( w.x < m_multiParam.c.x )
			{
				v = m_multiParam.c;
				m_multiParam.c = w;
			}
			else
			{
				v = w;
			}
		}
		else
		{
			m_multiParam.a = m_multiParam.c;
			m_state = "right";
			
			if ( w.x < v.x )
			{
				m_multiParam.c = w;
			}
			else
			{
				m_multiParam.c.x = v.x;
				v = w;
			}
		}
	}

	if ( abs(d) < m_precision )
	{
		if ( v.fx < _initialPoint.fx )
		{
			m_outputParam.fx = v.fx;
			m_outputParam.x = Y;
		}
	}
	
	return m_multiParam;
}

double CCubicInterpolationMultiSearch::min(double _value0, double _value1, double _value2 )
{
	double value = 0;
	if ( _value0 >= _value1 )
	{
		value =  _value1;
	}
	else
	{
		value =  _value0;
	}

	return ( _value2 >= value ) ? value : _value2;

}

inputParam2D CCubicInterpolationMultiSearch::formCubicInterpolation( outputParam2D _param, inputParam2D _qParam )
{
	m_interPoint3D = false;
	inputParam2D w(0,0);
	
	w.x = _param.c.x;
	double fua = _param.c.fx - _param.a.fx;
	double fvu = _qParam.fx - _param.c.fx;
	double fbv = _param.b.fx - _qParam.fx;

	double dua = _param.c.x - _param.a.x;
	double dvu = _qParam.x - _param.c.x;
	double dbv = _param.b.x - _qParam.x;

	double sua = _param.c.x + _param.a.x;
	double svu = _qParam.x + _param.c.x;
	double sbv = _param.b.x + _qParam.x;

	double pua = fua * dvu * dbv;
	double pvu = fvu * dbv * dua;
	double pbv = fbv * dua * dvu;
	double Da = pua * (svu - sbv) + pvu * (sbv - sua) + pbv * (sua - svu);

	if ( Da == 0 )
	{
		m_interPoint3D = true;
		return w;
	}

	double a2 = _param.a.x * _param.a.x;
	double u2 = _param.c.x * _param.c.x;
	double v2 = _qParam.x * _qParam.x;
	double b2 = _param.b.x * _param.b.x;

	double qua = u2 + _param.c.x * _param.a.x + a2;
	double qvu = v2 + _qParam.x * _param.c.x + u2;
	double qbv = b2 + _param.b.x * _qParam.x + v2;
	double Db = pua * (qbv - qvu) + pvu * (qua - qbv) + pbv * (qvu - qua);
	double Dc = pua * (qvu * sbv - qbv * svu) + pvu * (qbv * sua - qua * sbv) + pbv * (qua * svu - qvu * sua);
	double D3 = 3 * Da;
	double D = Db * Db - D3 * Dc;
	
	double SD = 0;
	if ( D < 0 )
	{
		m_interPoint3D = true;
		return w;
	}
	else
	{
		SD = sqrt(D);
		if ( Db > 0 )
		{
			w.x = - ( SD + Db ) / D3;
		}
		else
		{
			w.x = Dc / ( SD - Db );
		}
	}

	if ( w.x <=_param.a.x || w.x >= _param.b.x )
	{
		m_interPoint3D = true;
	}

	return w;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
