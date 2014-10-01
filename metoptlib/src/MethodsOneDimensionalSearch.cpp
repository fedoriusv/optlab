#include "MethodsOneDimensionalSearch.h"

using namespace metopt;

CSvenSearch::CSvenSearch( CFuncionOneDimensional* _func, double _step, double _precision )
	:
COneDimensionalSearch()
{
	m_nameMethod = NAME_METHOD_SVEN;
	m_step = _step;
	m_precision = _precision;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

bool CSvenSearch::checkExit( double& _funcValue )
{
	if ( abs(_funcValue) > abs(m_prevFuncValue) )
	{
		m_typeExit = TYPE_EXIT_PRECISION;
		return true;
	}
		
	return false;
}

/*Поиск интервала неопределенности методом Свенна*/
outputParam2D CSvenSearch::calcArgMin( double _initialPoint )
{
	saveHeadData( " Sven Search " );
	m_time->start();
	//------------------------------------------------
	m_state = "begin";
	m_inputParam.x = _initialPoint;
	//m_outputParam.c.x = m_inputParam.x;
	m_inputParam.fx = newPoint( _initialPoint, true );
	//------------------------------------------------
	
	m_outputParam.a = m_outputParam.c = m_inputParam;

	m_outputParam.b.x = m_outputParam.c.x + m_step;
	m_state = "interval";
	m_outputParam.b.fx = newPoint( m_outputParam.b.x, true );
	
	inputParam2D swap;
	if (m_outputParam.b.fx < m_outputParam.c.fx)
		while (m_outputParam.b.fx < m_outputParam.c.fx)
		{
			m_state = "forward";
					
			m_outputParam.a = m_outputParam.c;
			m_outputParam.c = m_outputParam.b;
			
			m_step += m_step;
			m_outputParam.b.x += m_step;
			m_outputParam.b.fx = newPoint(m_outputParam.b.x, true );
			if (isEndMethod())// || checkExit(m_outputParam.b.fx)) 
			{
				swap = m_outputParam.b;
				m_outputParam.b = m_outputParam.c;
				m_outputParam.c = swap;
				break;
			}
		}
	else
	{
		m_state = "back";
		m_step = -m_step;
		m_outputParam.a.x = m_outputParam.c.x + m_step;
		m_outputParam.a.fx = newPoint(m_outputParam.a.x, true );
		
		while (m_outputParam.a.fx < m_outputParam.c.fx)
		{
			m_outputParam.b = m_outputParam.c;
			m_outputParam.c = m_outputParam.a;
			
			m_step += m_step;
			m_outputParam.a.x += m_step;
			m_outputParam.a.fx = newPoint(m_outputParam.a.x,true);
			if (isEndMethod())// || checkExit(m_outputParam.a.fx)) 
			{
				swap = m_outputParam.a;
				m_outputParam.a = m_outputParam.c;
				m_outputParam.c = swap;
				break;
			}
		}
	}

	m_time->stop();
	m_state = "end";
	saveFootData();
		
	return m_outputParam;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CAdaptationStepSearch::CAdaptationStepSearch( CFuncionOneDimensional* _func, double _step, double _precision )
	:
COneDimensionalSearch()
{
	m_nameMethod = NAME_METHOD_ADAPTATION_STEP;
	m_precision = _precision;
	m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

bool CAdaptationStepSearch::checkExit( double& _step)
{
	if ( abs(_step) <= m_precision )
	{
		m_typeExit = TYPE_EXIT_PRECISION;
		return true;
	}
		
	return false;
}

/*Метод адаптации шага (минимин)*/
outputParam2D  CAdaptationStepSearch::calcArgMin( double _initialPoint  )
{
	saveHeadData(" Adaptation Step Search ");
	m_time->start();
	//------------------------------------------------
	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint( _initialPoint, true );
	//------------------------------------------------
	inputParam2D fy(0,0);

	m_outputParam.c = m_inputParam;
	fy = m_outputParam.c;

	double r = 0;
	m_state = "forward";
	
	while(1)
	{
		m_countIteration++;

		fy.x += m_step;
		fy.fx = newPoint( fy.x, true );
		
		if (isEndMethod())// || checkExit( m_step ))
		{
			m_outputParam.c = fy;
			break;
		}
		
		if ( fy.fx < m_outputParam.c.fx )
		{
			m_outputParam.c = fy;
			m_state = "forward";
			if ( r >= 0.5f )
				r = 2.0f;
			else
				r = 0.5f;
		}
		else
		{
			fy.x -= m_step;
			m_state = "back";
			if ( r== 2.0f )
				r = 0.25f;
			else
				r = -0.5f;
		}

		m_step *= r;
	}

	m_time->stop();
	m_state = "end";
	saveFootData();
	
	return m_outputParam;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CUniformSearch::CUniformSearch( CFuncionOneDimensional* _func, double _step, double _precision )
	:
COneDimensionalSearch()
{
	m_nameMethod = NAME_METHOD_UNIFORM;
	m_step = _step;
	m_precision = _precision;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

/*Метод равномерного поиска (Uniform Search)*/
outputParam2D  CUniformSearch::calcArgMin( double _initialPoint )
{
	saveHeadData(" Uniform Search ");
	
	COneDimensionalSearch* searchInterval = new CSvenSearch(m_func ,m_step, m_precision );
	
	m_time->start();
	outputParam2D param;
	param = searchInterval->calcArgMin( _initialPoint );
	m_countFunc = searchInterval->getCountFunc();
	m_countBestPoint = searchInterval->getCountBestPoints();
	m_outputParam = param; 
	
	m_data->addCalcData(searchInterval->getData());

	inputParam2D v;
	double d = m_outputParam.b.x - m_outputParam.a.x;
	m_state = "uniform";
	double n = d/m_precision;
	m_step = d/( n + 1 );
	m_outputParam.c.x = m_outputParam.a.x + m_step;
	m_outputParam.c.fx = newPoint( m_outputParam.c.x, true );
	v.x = m_outputParam.c.x;

	for (int i = 0; i < n; ++i )
	{
		m_countIteration++;
		
		v.x = v.x + m_step;
		v.fx = newPoint( v.x, true );
		if ( isEndMethod( ) ) 
		{
			m_outputParam.c = v;
			break;
		}
		
		if ( m_outputParam.c.fx < v.fx )
		{
			
			m_outputParam.c = v;
		}
	}

	m_time->stop();
	if ( param.c < m_outputParam.c )
		m_outputParam = param;
	m_state = "end";
	saveFootData();
	
	return m_outputParam;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CDichotomySearch::CDichotomySearch( CFuncionOneDimensional* _func, double _step, double _precision )
	:
COneDimensionalSearch()
{
	m_nameMethod = NAME_METHOD_DICHOTOMY;
	m_step = _step;
	m_precision = _precision;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}
/* Метод дихотомии (Dichotomy) */
outputParam2D  CDichotomySearch::calcArgMin( double _initialPoint )
{
	saveHeadData(" Dichotomy ");

	COneDimensionalSearch* searchInterval = new CSvenSearch(m_func ,m_step, m_precision );
	
	m_time->start();
	outputParam2D param;
	param = searchInterval->calcArgMin( _initialPoint );
	m_countFunc = searchInterval->getCountFunc();
	m_countBestPoint = searchInterval->getCountBestPoints();
	m_outputParam = param; 

	m_data->addCalcData(searchInterval->getData());
	
	m_state = "Dichotomy";
	double h = m_precision/8;
	
	inputParam2D u(0,0);
	inputParam2D v(0,0);
	while(1)
	{
		m_countIteration++;
		
		m_outputParam.c.x = ( m_outputParam.a.x + m_outputParam.b.x)/2;
		u.x = m_outputParam.c.x - h;
		u.fx = newPoint( u.x, true );
		if ( isEndMethod( ) ) 
		{
			m_outputParam.c = u;
			break;
		}
		
		v.x = m_outputParam.c.x + h;
		m_step = v.x - m_outputParam.a.x;
		v.fx = newPoint( v.x, true );
		if ( isEndMethod ( ) )
		{
			m_outputParam.c = v;
			break;
		}

		if ( u.fx < v.fx )
		{
			m_state = "left";
			m_outputParam.b.x = v.x;
		}
		else
		{
			m_state = "right";
			m_outputParam.a.x = u.x;
		}

	}

	m_time->stop();
	if ( param.c < m_outputParam.c )
		m_outputParam = param;
	m_state = "end";
	saveFootData();
	
	return m_outputParam;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
CDivisionSearch::CDivisionSearch( CFuncionOneDimensional* _func, double _step, double _precision )
	:
COneDimensionalSearch()
{
	m_nameMethod = NAME_METHOD_DIVISION;
	m_step = _step;
	m_precision = _precision;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}
/*Метод деления интервала пополам (Division 2)*/
outputParam2D  CDivisionSearch::calcArgMin( double _initialPoint )
{
	saveHeadData(" Division 2 ");

	COneDimensionalSearch* searchInterval = new CSvenSearch(m_func ,m_step, m_precision );
	
	m_time->start();
	outputParam2D param;
	param = searchInterval->calcArgMin( _initialPoint );
	m_countFunc = searchInterval->getCountFunc();
	m_countBestPoint = searchInterval->getCountBestPoints();
	m_outputParam = param; 

	m_data->addCalcData(searchInterval->getData());
		
	m_state = "division";
	m_outputParam.c.x = ( m_outputParam.a.x + m_outputParam.b.x )/2;
	m_outputParam.c.fx = newPoint( m_outputParam.c.x, true );
	
	inputParam2D u(0,0);
	inputParam2D v(0,0);
	while(1)
	{
		m_countIteration++;
		
		u.x = ( m_outputParam.a.x + m_outputParam.c.x )/2;
		m_step = u.x - m_outputParam.a.x;
		u.fx =  newPoint( u.x, true );
		
		if ( isEndMethod( ) )
		{
			m_outputParam.c = u;
			break;
		}
		
		if ( u.fx < m_outputParam.c.fx )
		{
			m_state = "left";
			m_outputParam.b = m_outputParam.c;
			
			m_outputParam.c = u;
		}
		else
		{
			v.x = ( m_outputParam.c.x + m_outputParam.b.x )/2;
			v.fx = newPoint( v.x, true );
			if ( isEndMethod() )
			{
				m_outputParam.c = v;
				break;
			}
			
			if ( v.fx < m_outputParam.c.fx )
			{
				m_state = "right";
				m_outputParam.a = m_outputParam.c;
				
				m_outputParam.c = v;
			}
			else
			{
				m_state = "middle";
				m_outputParam.a.x = u.x;
				m_outputParam.b.x = v.x;
			}
		}
	}
	
	m_time->stop();
	if ( param.c < m_outputParam.c )
		m_outputParam = param;
	m_state = "end";
	saveFootData();
	
	return m_outputParam;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
CFibonacciSearch::CFibonacciSearch( CFuncionOneDimensional* _func, double _step, double _precision )
	:
COneDimensionalSearch()
{
	m_nameMethod = NAME_METHOD_FIBONACCI;
	m_step = _step;
	m_precision = _precision;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}
/*Метод Фибоначчи*/
outputParam2D  CFibonacciSearch::calcArgMin( double _initialPoint )
{
	saveHeadData(" Fibonacci Search ");

	COneDimensionalSearch* searchInterval = new CSvenSearch(m_func ,m_step, m_precision );
	
	m_time->start();
	outputParam2D param;
	param = searchInterval->calcArgMin( _initialPoint );
	m_countFunc = searchInterval->getCountFunc();
	m_countBestPoint = searchInterval->getCountBestPoints();
	m_outputParam = param; 

	m_data->addCalcData(searchInterval->getData());
	
	double d =  m_outputParam.b.x - m_outputParam.a.x;
	double F0 = 1;
	double F1 = 1;
	double F = F0 + F1;

	while( d > F*m_precision )
	{
		F0 = F1;
		F1 = F;
		F = F0 + F1;
	}
	m_state = "fibonacci";
	d = d*F0/F;
	m_step = d;

	inputParam2D u(0,0);
	inputParam2D v(0,0);
	u.x = m_outputParam.a.x + d;
	u.fx = newPoint( u.x, true );

	v.x = m_outputParam.b.x - d;
	v.fx = newPoint( v.x, true );

	while(1)
	{
		m_countIteration++;
		
		d = v.x - u.x;
		m_step = d;

		if ( u.fx < v.fx )
		{
			m_state = "left";
			m_outputParam.b.x = v.x;
			v.x = u.x;
			v.fx = u.fx;
			u.x = m_outputParam.a.x + d;
			u.fx = newPoint( u.x, true );
			//m_outputParam.c = u;
			if ( isEndMethod( ) )
			{
				m_outputParam.c = u;
				break;
			}
		}
		else
		{
			m_state = "right";
			m_outputParam.a.x = u.x;
			u.x = v.x;
			u.fx = v.fx;
			m_outputParam.c = v;
			v.x = m_outputParam.b.x - d;
			v.fx = newPoint( v.x, true );
			if ( isEndMethod( ) )
			{
				m_outputParam.c = v;
				break;
			}
		
		}
	}
	
	m_time->stop();
	if ( param.c < m_outputParam.c )
		m_outputParam = param;
	m_state = "end";
	saveFootData();
	
	return m_outputParam;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
CGoldenSectionSearch::CGoldenSectionSearch( CFuncionOneDimensional* _func, double _step, double _precision )
	:
COneDimensionalSearch()
{
	m_nameMethod = NAME_METHOD_GOLDEN_SECTION;
	m_step = _step;
	m_precision = _precision;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}
/*Метод золотого сечения (Golden Section)*/
outputParam2D  CGoldenSectionSearch::calcArgMin( double _initialPoint )
{
	saveHeadData(" Golden Section ");

	COneDimensionalSearch* searchInterval = new CSvenSearch(m_func ,m_step, m_precision );
	
	m_time->start();
	outputParam2D param;
	param = searchInterval->calcArgMin( _initialPoint );
	m_countFunc = searchInterval->getCountFunc();
	m_countBestPoint = searchInterval->getCountBestPoints();
	m_outputParam = param;

	m_data->addCalcData(searchInterval->getData());
	
	m_state = "section";
	double t = ( sqrt(5.0f) - 1.0f ) / 2.0f;
	m_step = t * ( m_outputParam.b.x - m_outputParam.a.x );

	inputParam2D u(0,0);
	inputParam2D v(0,0);
	
	u.x = m_outputParam.b.x - m_step;
	u.fx = newPoint( u.x, true );

	v.x = m_outputParam.a.x + m_step;
	v.fx = newPoint( v.x, true ); 

	while(1)
	{
		m_countIteration++;

		if ( u.fx < v.fx )
		{
			m_state = "left";
			m_outputParam.b.x = v.x;
			
			v = u;

			m_step = u.x - m_outputParam.a.x;
			u.x = m_outputParam.b.x - m_step;
			u.fx = newPoint( u.x, true );
			if ( isEndMethod( ) )
			{
				m_outputParam.c = u;
				break;
			}
		}
		else
		{
			m_state = "right";
			m_outputParam.a.x = u.x;
			
			u = v;
			m_step = m_outputParam.b.x - v.x;
			v.x = m_outputParam.a.x + m_step;
			v.fx = newPoint( v.x, true );
			if ( isEndMethod( ) )
			{
				m_outputParam.c = v;
				break;
			}
		}
	}

	m_time->stop();
	if ( param.c < m_outputParam.c )
		m_outputParam = param;
	m_state = "end";
	saveFootData();
	
	return m_outputParam;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CQuadraticInterpolationSearch::CQuadraticInterpolationSearch( CFuncionOneDimensional* _func, double _step, double _precision )
	:
COneDimensionalSearch()
{
	m_nameMethod = NAME_METHOD_QUADRATIC_INTERPOLATION;
	m_step = _step;
	m_precision = _precision;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

/*Метод квадратичной интерполяции*/
outputParam2D  CQuadraticInterpolationSearch::calcArgMin( double _initialPoint )
{
	saveHeadData(" Quadratic Interpolation Search ");

	COneDimensionalSearch* searchInterval = new CSvenSearch(m_func ,m_step);
	
	m_time->start();
	outputParam2D param;
	param = searchInterval->calcArgMin( _initialPoint );
	m_countFunc = searchInterval->getCountFunc();
	m_countBestPoint = searchInterval->getCountBestPoints();
	m_outputParam = param;

	m_data->addCalcData(searchInterval->getData());
	
	m_step = m_outputParam.b.x - m_outputParam.a.x;
	
	m_state = "parabola";
	inputParam2D v(0,0);
	double d(0);
	double B(0);

	while(1)
	{
		m_countIteration++;
		v = formQuadraticInterpolation( m_outputParam );

		if (m_interPoint)
		{
			m_state = "target non reached";
			//break;
		}
		d = v.x - m_outputParam.c.x;
		v.fx = newPoint( v.x, true );
		
		if ( isEndMethod( ) )
		{
			m_outputParam.c = v;
			break;
		}
		
		B = max(sign(d),0);
		if ( v.fx < m_outputParam.c.fx )
		{
			if (B)
			{
				m_outputParam.a = m_outputParam.c;
				m_state = "right";
			}
			else
			{
				m_outputParam.b = m_outputParam.c;
				m_state = "left";
			}
						
			m_outputParam.c = v;

		}
		else
		{
			if (B)
			{
				m_outputParam.b = v;
				m_state = "left";
			}
			else
			{
				m_outputParam.a = v;
				m_state = "right";
			}
		}
				
	}

	m_time->stop();
	if ( param.c < m_outputParam.c )
		m_outputParam = param;
	m_state = "end";
	saveFootData();
	
	return m_outputParam;
};

double CQuadraticInterpolationSearch::max(double _value0, double _value1 )
{
	return ( _value0 >= _value1 ) ? _value0 : _value1;
};

inputParam2D CQuadraticInterpolationSearch::formQuadraticInterpolation( outputParam2D _param )
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CCubicInterpolationSearch::CCubicInterpolationSearch( CFuncionOneDimensional* _func, double _step, double _precision )
	:
CQuadraticInterpolationSearch( _func, _step, _precision )
{
	m_nameMethod = NAME_METHOD_CUBIC_INTERPOLATION;
	m_step = _step;
	m_precision = _precision;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

/*Метод кубической интерполяции*/
outputParam2D  CCubicInterpolationSearch::calcArgMin( double _initialPoint )
{
	saveHeadData(" Cubic Interpolation Search ");

	COneDimensionalSearch* searchInterval = new CSvenSearch(m_func ,m_step);
	
	m_time->start();
	outputParam2D param;
	param = searchInterval->calcArgMin( _initialPoint );
	m_countFunc = searchInterval->getCountFunc();
	m_countBestPoint = searchInterval->getCountBestPoints();
	m_outputParam = param;

	m_data->addCalcData(searchInterval->getData());
	
	m_state = "parabola";
	
	inputParam2D v(0,0);
	inputParam2D w(0,0);
	double d(0);
	v = formQuadraticInterpolation( m_outputParam );
	if (m_interPoint)
	{
		m_state = "target non reached";
		//break;
	}
	d = v.x - m_outputParam.c.x;
	m_step = abs(d);
	v.fx = newPoint( v.x, true );
	
	if ( v.x < m_outputParam.c.x )
	{
		w = m_outputParam.c;

		m_outputParam.c = v;

		v = w;
	}

	m_state = "cubic";
	while(1)
	{
		m_countIteration++;

		w = formCubicInterpolation( m_outputParam, v );
		if (m_interPoint3D)
		{
			m_state = "target non reached";
			//break;
		}
		double d = min(abs(v.x - m_outputParam.c.x),abs(w.x - m_outputParam.c.x),abs(v.x - w.x));
		w.fx = newPoint( w.x, true );
		
		if ( isEndMethod( ) )
		{
			m_outputParam.c = w;
			break;
		}
		
		if ( m_outputParam.c.fx < v.fx )
		{
			m_outputParam.b = v;

			m_state = "left";
			if ( w.x < m_outputParam.c.x )
			{
				v = m_outputParam.c;

				m_outputParam.c = w;
			}
			else
			{
				v = w;
			}
		}
		else
		{
			m_outputParam.a = m_outputParam.c;
			m_state = "right";
			
			if ( w.x < v.x )
			{
				m_outputParam.c = w;
			}
			else
			{
				m_outputParam.c.x = v.x;
				
				v = w;
			}
		}
	}

	m_time->stop();
	if ( param.c < m_outputParam.c )
		m_outputParam = param;
	m_state = "end";
	saveFootData();
	
	return m_outputParam;
};

double CCubicInterpolationSearch::min(double _value0, double _value1, double _value2 )
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

inputParam2D CCubicInterpolationSearch::formCubicInterpolation( outputParam2D _param, inputParam2D _qParam )
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