#include "MethodsMultiDimensionalSearch.h"

using namespace metopt;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Метод Хука-Дживса (Hooke-Jeeves)*/
CHookeJeevesSearch::CHookeJeevesSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
	:
m_flagExit(false)
{
	m_nameMethod = NAME_METHOD_HOOKE_JEEVES;
	m_precision = _precision;
	m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

inputParam CHookeJeevesSearch::calcArgMin( Arg _initialPoint )
{
	m_dimensions = _initialPoint.getSize();

	saveHeadData( " Hooke Jeeves Search " );
	m_time->start();

	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint( _initialPoint.getPointer(), true );
	
	m_outputParam = m_inputParam;
	m_step *= 2;
	inputParam fz;
	inputParam fy;

	while( !m_flagExit )
	{
		fy.fx =  m_outputParam.fx;
		m_state = "disc search 1";

		while ( !(fy.fx <  m_outputParam.fx) )
		{
			m_countIteration++;

			m_step /= 2;
			fy = research( m_outputParam );
			
			if (isEndMethod())
			{
				m_flagExit = true;
				break;
			}
		}

		while ( fy.fx <  m_outputParam.fx )
		{
			fz.x = fy.x * 2 - m_outputParam.x;
			m_state = "pattern";
			fz.fx = newPoint( fz.x.getPointer(), false );
			if (isEndMethod())
			{
				m_flagExit = true;
				m_outputParam = fz;
				break;
			}

			m_outputParam = fy;
			m_state = "disc search 2";
			fy = research( fz );
			if (isEndMethod())
			{
				m_flagExit = true;
				m_outputParam = fy;
				break;
			}
		}
	}

	m_time->stop();
	m_state = "end";
	saveFootData();
		
	return m_outputParam;
}

inputParam CHookeJeevesSearch::research( const inputParam& _param )
{
	inputParam y;
	inputParam u;
	y = _param;
	u = _param; 

	for ( uInt i = 0; i < m_dimensions; ++i )
	{
		u.x[i] = y.x[i] + m_step;
		u.fx = newPoint( u.x.getPointer(), false );
		if ( isEndMethod() )
		{
			m_flagExit = true;
			y = u;
			break;
		}
		if ( u.fx < y.fx )
		{
			y.fx = u.fx;
			y.x[i] = u.x[i];
		}
		else
		{
			u.x[i] = y.x[i] - m_step;
			u.fx = newPoint( u.x.getPointer(), false );
			if ( isEndMethod() )
			{
				m_flagExit = true;
				y = u;
				break;
			}
			if ( u.fx < y.fx )
			{
				y.fx = u.fx;
				y.x[i] = u.x[i];
			}
			else
			{
				u.x[i] = y.x[i];
			}
		}
	}

	return y;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод Нелдера-Мида (Nelder-Mead)*/
CNelderMeadSearch::CNelderMeadSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
	:
m_flagExit(false)
{
	m_nameMethod = NAME_METHOD_NELDER_MEAD;
	m_precision = _precision;
	m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

inputParam CNelderMeadSearch::calcArgMin( Arg _initialPoint )
{
	m_dimensions = _initialPoint.getSize();

	saveHeadData( " Nelder-Mead Search " );
	m_time->start();

	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint( _initialPoint.getPointer(), true );
	m_outputParam = m_inputParam;
	
	uInt m = m_dimensions + 1;
	inputParam* X = new inputParam[m];
	Arg ay;
	m_state = "init polyhedron";

	for ( uInt i = 0; i < m_dimensions; ++i )
	{
		ay = m_outputParam.x;
		ay[i] = ay[i] + m_step;
		X[i].x = ay;
		X[i].fx = newPoint( ay.getPointer(), false );
		if ( isEndMethod() )
		{
			m_flagExit = true;
			break;
		}
	}
	X[m - 1] = m_outputParam;
	//-------------------------------------------------
	Arg onesn;
	onesn.setFillIn( 1, m_dimensions );
	Arg jall(m);
	for ( uInt i = 0; i < m; ++i )
	{
		jall[i] = i;
	}

	int l = m - 1;
	int h = m - 1;
	inputParam x;
	inputParam w;
	
	Arg* Xworse = new Arg[m_dimensions];
	Arg* Xonesn = new Arg[m_dimensions];
	Arg* mabs = new Arg[m_dimensions];
	Arg* jsum  = new Arg[m_dimensions];

	inputParam y;
	inputParam z;
	while (1)
	{
		m_countIteration++;
		x = w = X[m - 1];
		l = m - 1;
		h = m - 1;

		for ( uInt i = 0; i < m_dimensions; ++i )
		{
			if ( X[i].fx < x.fx )
			{
				x.fx = X[i].fx;
				l = i;
			}
			if ( w.fx < X[i].fx )
			{
				w.fx = X[i].fx;
				h = i;
			}
		}
		x.x = X[l].x; 
		w.x = X[h].x;
		Arg jbest;
		jbest = jall;
		jbest.deleteElement(h);
		
		Arg jworse;
		jworse = jall;
		jworse.deleteElement(l);
		
		for ( uInt i = 0; i < m_dimensions; ++i )
		{
			Xworse[i] = X[(int)jworse[i]].x;
			Xonesn[i] = X[(int)( l * onesn[i] )].x;
			mabs[i] = Xworse[i] - Xonesn[i];
			mabs[i].abs();
			jsum[i] = X[(int)jbest[i]].x;
		}
		m_step = maxRow( mabs ).getMax(); 
		Arg c = sumRow( jsum ) / 2;
		
		y.x = c * 2.0f - w.x;
		m_state = "reflection";
		y.fx = newPoint( y.x.getPointer(), false );
		if ( isEndMethod() )
		{
			m_outputParam = y;
			break;
		}
		if ( y.fx < x.fx )
		{
			z.x = y.x * 2.0f - c;
			m_state = "stretching";
			z.fx = newPoint( z.x.getPointer(), false );
			if ( isEndMethod() )
			{
				m_outputParam = z;
				break;
			}
			if ( z.fx < y.fx )
			{
				X[h] = z;
			}
			else
			{
				X[h] = y;
			}
		}
		else
		{
			bool B = false;
			for ( uInt i = 0; i < jbest.getSize(); ++i )
			{
				if ( y.fx < X[(int)jbest[i]].fx )
				{
					B = true;
					break;
				}
			}
			if ( B )
			{
				X[h] = y;
			}
			else
			{
				if ( y.fx < w.fx )
				{
					w = y;
					X[h] = y;
				}
				z.x = (w.x + c) * 0.5f;
				m_state = "compression";
				z.fx = newPoint( z.x.getPointer(), false );
				if ( isEndMethod() )
				{
					m_outputParam = z;
					break;
				}
				if ( z.fx < w.fx )
				{
					X[h] = z;
				}
				else
				{
					for ( uInt i = 0; i < jworse.getSize(); ++i )
					{
						z.x = ( X[(int)jworse[i]].x + x.x ) * 0.5f;
						X[(int)jworse[i]].x = z.x;
						m_state = "reduction";
						X[(int)jworse[i]].fx = newPoint( z.x.getPointer(), false );
						if ( isEndMethod() )
						{
							m_outputParam = X[(int)jworse[i]];
							break;
						}
					}
				}
			}
		}
		if ( isEndMethod() )
		{
			
			break;
		}
	}

	delete[] Xworse;
	delete[] Xonesn;
	delete[] mabs;
	delete[] jsum;
	delete[] X;
	
	m_time->stop();
	m_state = "end";
	saveFootData();
		
	return m_outputParam;
}

Arg CNelderMeadSearch::maxRow( const Arg* _matrix ) const
{
	Arg maxRow(m_dimensions);
	Arg sum;
	sum = sumRow( _matrix );
	double max = sum.getMax();
	uInt maxId = 0;
	for ( uInt i = 0; i < m_dimensions; ++i )
	{
		if (max == sum[i])
		{
			maxId = i;
		}
	}

	for ( uInt i = 0; i < m_dimensions; ++i )
	{
		maxRow[i] = _matrix[i].x[maxId];
	}
	return maxRow;
}

Arg CNelderMeadSearch::sumRow( const Arg* _matrix ) const
{
	Arg sumRow(m_dimensions);
	for ( uInt i = 0; i < m_dimensions; ++i )
	{
		for ( uInt j = 0; j < m_dimensions; ++j )
		{
			sumRow[i] +=  _matrix[j].x[i];
		}
	}

	return sumRow;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод Спендли-Хекста-Химсворта симплексного поиска*/
CSimplexSearch::CSimplexSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
	:
CNelderMeadSearch( _func, _step, _precision )
{
	m_nameMethod = NAME_METHOD_SIMPLEX_METHOD;
	m_precision = _precision;
	m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

inputParam CSimplexSearch::calcArgMin( Arg _initialPoint )
{
	m_dimensions = _initialPoint.getSize();

	saveHeadData( " Simplex Search " );
	m_time->start();

	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint( _initialPoint.getPointer(), true );
	m_outputParam = m_inputParam;
	
	uInt m = m_dimensions + 1;
	inputParam* X = new inputParam[m];
	Arg ones;
	ones.setFillIn( 1, m_dimensions );
	double a = m_step / sqrt(2.0f);
	ones = ones * ( (sqrt( (double)(m_dimensions + 1)) - 1) * a / m_dimensions );
	m_state = "init polyhedron";
	Arg v = m_inputParam.x + ones;
	Arg ay;
	for ( uInt i = 0; i < m_dimensions; ++i )
	{
		ay = v;
		ay[i] = ay[i] + a;
		X[i].x = ay;
		X[i].fx = newPoint( ay.getPointer(), false );
		if ( isEndMethod() )
		{
			m_flagExit = true;
			break;
		}
	}
	X[m - 1] = m_outputParam;
	//------------------------------------------------
	Arg onesn;
	onesn.setFillIn( 1, m_dimensions );
	Arg jall(m);
	for ( uInt i = 0; i < m; ++i )
	{
		jall[i] = i;
	}

	int l = m - 1;
	int h = m - 1;
	inputParam x;
	inputParam w;
	
	Arg* Xworse = new Arg[m_dimensions];
	Arg* Xonesn = new Arg[m_dimensions];
	Arg* mabs = new Arg[m_dimensions];
	Arg* jsum  = new Arg[m_dimensions];

	inputParam y;
	inputParam z;

	while (1)
	{
		m_countIteration++;
		x = w = X[m - 1];
		l = m - 1;
		h = m - 1;

		for ( uInt i = 0; i < m_dimensions; ++i )
		{
			if ( X[i].fx < x.fx )
			{
				x.fx = X[i].fx;
				l = i;
			}
			if ( w.fx < X[i].fx )
			{
				w.fx = X[i].fx;
				h = i;
			}
		}
		x.x = X[l].x; 
		w.x = X[h].x;
		Arg jbest;
		jbest = jall;
		jbest.deleteElement(h);
		
		Arg jworse;
		jworse = jall;
		jworse.deleteElement(l);
		
		for ( uInt i = 0; i < m_dimensions; ++i )
		{
			Xworse[i] = X[(int)jworse[i]].x;
			Xonesn[i] = X[(int)( l * onesn[i] )].x;
			mabs[i] = Xworse[i] - Xonesn[i];
			mabs[i].abs();
			jsum[i] = X[(int)jbest[i]].x;
		}
		m_step = maxRow( mabs ).getMax(); 
		Arg c = sumRow( jsum ) / 2;
		
		y.x = c * 2.0f - w.x;
		m_state = "reflection";
		y.fx = newPoint( y.x.getPointer(), false );
		if ( isEndMethod() )
		{
			m_outputParam = y;
			break;
		}
		if ( y.fx < w.fx )
		{
			//w = y;
			X[h] = y;
		}
		else
		{
			for ( uInt i = 0; i < jworse.getSize(); ++i )
			{
				z.x = ( X[(int)jworse[i]].x + x.x ) * 0.5f;
				X[(int)jworse[i]].x = z.x;
				m_state = "reduction";
				X[(int)jworse[i]].fx = newPoint( z.x.getPointer(), false );
				if ( isEndMethod() )
				{
					m_outputParam = X[(int)jworse[i]];
					break;
				}
			}
		}
		if ( isEndMethod() )
		{
			
			break;
		}
	}
	/*delete Xworse;
	delete Xonesn;
	delete mabs;
	delete jsum;
	delete X;*/
	
	m_time->stop();
	m_state = "end";
	saveFootData();
		
	return m_outputParam;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод Бокса*/
CBoxingSearch::CBoxingSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
	:
m_flagExit(false)
{
	m_nameMethod = NAME_METHOD_BOX;
	m_precision = _precision;
	m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

inputParam CBoxingSearch::calcArgMin( Arg _initialPoint )
{
	m_dimensions = _initialPoint.getSize();

	saveHeadData( " Boxing Search " );
	m_time->start();

	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint( _initialPoint.getPointer(), true );
	m_outputParam = m_inputParam;
	
	double N = powl( 2.0f, (double)m_dimensions );
	Arg k;
	k.setFillIn( 0, m_dimensions );
	Arg c;
	c.setFillIn( 1, m_dimensions );
	Arg I;
	I = c * -1;
	Arg h;
	h = c * m_step;

	m_state = "sample";
	
	double p = 1;
	double r = 2;

	for ( uInt i = 1; i < m_dimensions; ++i )
	{
		p = p * r;
		c[i] = p;
	}

	inputParam y;
	inputParam z;

	while (1)
	{
		m_countIteration++;
		y = m_outputParam;

		for ( int i = 0; i < N; ++i )
		{
			z.x = m_outputParam.x + I * h;
			z.fx = newPoint( z.x.getPointer(), false );
			if ( isEndMethod() )
			{
				m_outputParam = z;
				m_flagExit = true;
				break;
			}

			if ( z.fx < y.fx )
			{
				y = z;
			}
			Arg ik;
			ik.setFillIn( 0, m_dimensions );
			k = k + 1;

			for ( uInt j = 0; j < k.getSize(); ++j )
			{
				if ( k[j] >= c[j] )
				{
					ik[j] = 1; 
				}
			}
			for ( uInt j = 0; j < k.getSize(); ++j )
			{
				if ( ik[j] == 1 )
				{
					I[j] = I[j] * -1;
					k[j] = 0;
				}
			}
		}
		if (m_flagExit) break;
		
		if ( !(y.fx < m_outputParam.fx) )
		{
			m_step *= 0.5f;
			h = h * 0.5f;
			m_state = "reduction";
		}
		if ( isEndMethod() )
		{
			m_outputParam = y;
			break;
		}
		m_outputParam = y;
	}
	
	m_time->stop();
	m_state = "end";
	saveFootData();
		
	return m_outputParam;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод циклического минимина*/
CCyclicMinminSearch::CCyclicMinminSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
	:
m_flagExit(false)
{
	m_nameMethod = NAME_METHOD_CYCLIC_MINMIN;
	m_precision = _precision;
	m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

inputParam CCyclicMinminSearch::calcArgMin( Arg _initialPoint )
{
	m_dimensions = _initialPoint.getSize();

	saveHeadData( " Cyclic Minmin Search " );
	m_time->start();

	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint( _initialPoint.getPointer(), true );
	m_outputParam = m_inputParam;
	
	Arg dx;
	dx.setFillIn( 1.0f, m_dimensions );
	dx = dx * m_step;
	inputParam l = m_outputParam;
	uInt i = 1;
	uInt iv = 0;
	inputParam y;
	inputParam yp;

	while(1)
	{
		m_countIteration++;

		if ( iv < m_dimensions )
		{
			iv ++; 
		}
		else
		{
			iv = 1;
		}
		int dv = 0;
		int jv = 2;
		
		while ( jv > 0 )
		{
			m_state = "iv - descent";
			m_outputParam.x[iv - 1] += dx[iv - 1];
			m_step = dx.getNormInf();
			if ( i < m_dimensions )
			{
				i ++;
			}
			else
			{
				i = 1;
			}
			if ( i == iv )
			{
				if ( i < m_dimensions )
				{
					i++;
				}
				else
				{
					i = 1;
				}
			}
			y.fx = newPoint( m_outputParam.x.getPointer(), false );
			if ( isEndMethod() )
			{
				m_outputParam.fx = y.fx;
				m_flagExit = true;
				break;
			}
			int d = 0;
			int j = 2;
			m_state = "i - descent";

			while ( j > 0 )
			{
				m_outputParam.x[i - 1] += dx[i - 1];
				m_step = dx.getNormInf();
				yp.fx = newPoint( m_outputParam.x.getPointer(), false );
				if ( isEndMethod() )
				{
					m_outputParam.fx = y.fx;
					m_flagExit = true;
					break;
				}
				if ( yp.fx < y.fx )
				{
					y.fx = yp.fx;
					if ( d >= 2)
					{
						d = 8;
					}
					else
					{
						d = 2;
					}
				}
				else
				{
					m_outputParam.x[i - 1] -= dx[i - 1];
					if ( d != 0)
					{
						j--;
					}
					if ( d == 8 )
					{
						d = 1;
					}
					else
					{
						d = -2;
					}
				}
				dx[i - 1] *= ( (double)d / 4.0f );
			}
			if ( y.fx < l.fx )
			{
				l.x[i - 1] = m_outputParam.x[i - 1];
				l.x[iv - 1] = m_outputParam.x[iv - 1];
				l.fx = y.fx;
				if ( dv >= 2 )
				{
					dv = 8;

				}
				else
				{
					dv = 2;
				}
			}
			else
			{
				m_outputParam.x[i - 1] = l.x[i - 1];
				m_outputParam.x[iv - 1] = l.x[iv - 1];
				if ( dv != 0 )
				{
					jv --;
				}
				if ( dv == 8 )
				{
					dv = 1;
				}
				else
				{
					d = -2;
				}
			}
			dx[iv - 1] *= ( (double)dv / 4.0f );
		}
		if ( m_flagExit )
		{
			break;
		}
	}
	
	m_time->stop();
	m_state = "end";
	saveFootData();
		
	return m_outputParam;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод случайного поиска (Random Search)*/
CRandomSearch::CRandomSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
	:
m_flagExit(false)
{
	m_nameMethod = NAME_METHOD_RANDOM_SEARCH;
	m_precision = _precision;
	m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

inputParam CRandomSearch::calcArgMin( Arg _initialPoint )
{
	m_dimensions = _initialPoint.getSize();

	saveHeadData( " Random Search " );
	m_time->start();

	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint( _initialPoint.getPointer(), true );
	m_outputParam = m_inputParam;
	
	m_state = "draped";
	Arg t;
	t.setFillIn( 0, m_dimensions );
	Arg c = m_func->getInterval().m_pointB - m_func->getInterval().m_pointA;
	inputParam y;

	while (1)
	{
		m_countIteration ++;

		y = m_outputParam;
		for ( uInt i = 0; i < m_dimensions; ++i )
		{
			t[i] = rangedRand( 0.0, 1.0 );
		}
		y.x = m_func->getInterval().m_pointA + t * c;
		y.fx = newPoint( y.x.getPointer(), false );
		if ( isEndMethod() )
		{
			//m_outputParam = y;
			if (y.fx < m_outputParam.fx)
			{
				m_outputParam = y;
			}
			break;
		}

		if ( y.fx < m_outputParam.fx )
		{
			m_step = (m_outputParam.x - y.x).getNormInf();
			m_outputParam = y;
		}
	}
	
	m_time->stop();
	m_state = "end";
	saveFootData();
		
	return m_outputParam;
}

double CRandomSearch::rangedRand( const double& _rangeMin, const double& _rangeMax ) const
{
	double u = (double)rand() / (RAND_MAX + 1) * (_rangeMax - _rangeMin)  
		+ _rangeMin;

	return u;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод Вейля с pi*/
CWeilPISearch::CWeilPISearch( CFuncionMultiDimensional* _func, double _step, double _precision )
	:
m_flagExit(false)
{
	m_nameMethod = NAME_METHOD_WEIL_PI_SEARCH;
	m_precision = _precision;
	m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

inputParam CWeilPISearch::calcArgMin( Arg _initialPoint )
{
	m_dimensions = _initialPoint.getSize();

	saveHeadData( " Weil PI Search " );
	m_time->start();

	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint( _initialPoint.getPointer(), true );
	m_outputParam = m_inputParam;
	
	Arg c = m_func->getInterval().m_pointB - m_func->getInterval().m_pointA;
	Arg	g(m_dimensions);
	Arg t;
	inputParam x;
	inputParam y;

	m_state = "draped";
	double r = 4.0f * atan(1.0f) - 2.0f;
	double p = r;
	
	g[0] = getRem(p);

	for ( uInt i = 1; i < m_dimensions; ++i )
	{
		p *= r;
		g[i] = getRem(p);
	}
	t = g;
	x.x = m_func->getInterval().m_pointA + t * c;
	m_step = c.getNormInf();
	x.fx = newPoint( x.x.getPointer(), false );
	if ( isEndMethod() )
	{
		m_outputParam = x;
	}
	else
	{
		m_state = "draped";

		while (1)
		{
			m_countIteration ++;
			
			for ( uInt i = 0; i < m_dimensions; ++i )
			{
				t[i] = getRem( t[i] + g[i] );
			}
			y.x = m_func->getInterval().m_pointA + t * c;
			y.fx = newPoint( y.x.getPointer(), false );
			if ( isEndMethod() )
			{
				m_outputParam = y;
				break;
			}

			if ( y.fx < m_outputParam.fx )
			{
				m_step = (m_outputParam.x - y.x).getNormInf();
			}
		}
	}

	m_time->stop();
	m_state = "end";
	saveFootData();
		
	return m_outputParam;
}

double CWeilPISearch::getRem( const double& _value ) const
{
	double fnum = _value;
	fnum -= (int) fnum;

	return fnum;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод Вейля с e*/
CWeilESearch::CWeilESearch( CFuncionMultiDimensional* _func, double _step, double _precision )
	:
m_flagExit(false)
{
	m_nameMethod = NAME_METHOD_WEIL_E_SEARCH;
	m_precision = _precision;
	m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

inputParam CWeilESearch::calcArgMin( Arg _initialPoint )
{
	m_dimensions = _initialPoint.getSize();

	saveHeadData( " Weil E Search " );
	m_time->start();

	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint( _initialPoint.getPointer(), true );
	m_outputParam = m_inputParam;
	
	Arg c = m_func->getInterval().m_pointB - m_func->getInterval().m_pointA;
	Arg	g = m_func->getInterval().m_pointA;
	Arg t;
	inputParam x;
	inputParam y;

	m_state = "draped";
	double r = exp(1.0f) - 1.0f;
	double p = r;
	
	g[0] = getRem(p);
	for ( uInt i = 1; i < m_dimensions; ++i )
	{
		p *= r;
		g[i] = getRem(p);
	}
	t = g;
	x.x = m_func->getInterval().m_pointA + t * c;
	m_step = c.getNormInf();
	x.fx = newPoint( x.x.getPointer(), false );
	if ( isEndMethod() )
	{
		m_outputParam = x;
	}
	else
	{
		m_state = "draped";

		while (1)
		{
			m_countIteration ++;
			
			for ( uInt i = 0; i < m_dimensions; ++i )
			{
				t[i] = getRem( t[i] + g[i] );
			}
			y.x = m_func->getInterval().m_pointA + t * c;
			y.fx = newPoint( y.x.getPointer(), false );
			if ( isEndMethod() )
			{
				m_outputParam = y;
				break;
			}

			if ( y.fx < m_outputParam.fx )
			{
				m_step = (m_outputParam.x - y.x).getNormInf();
			}
		}
	}

	m_time->stop();
	m_state = "end";
	saveFootData();
		
	return m_outputParam;
}

double CWeilESearch::getRem( const double& _value ) const
{
	double fnum = _value;
	fnum -= (int) fnum;

	return fnum;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
