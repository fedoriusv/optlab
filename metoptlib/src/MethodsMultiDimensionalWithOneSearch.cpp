#include "MethodsMultiDimensionalWithOneSearch.h"

using namespace metopt;

CMultiDimensionalWithOneSearch::CMultiDimensionalWithOneSearch()
	: m_exitFlag( false )
	, m_interval( true )
	, m_S(0.0f)
	, m_H(0.0f)
{
}

CODMS* CMultiDimensionalWithOneSearch::createOneDimMethod() const
{
	CODMS* method;
	switch ( m_nameOneDimMethod )
	{
	case 0:
		return 0;
	case 1:
		method = 0;//new CSvenMultiSearch( m_func, m_step, m_oneDimPrecision );
		break;
	case 2:
		method	= new CAdaptationStepMultiSearch( m_func, m_step, m_oneDimPrecision );
		break;
	case 3:
		method = new CUniformMultiSearch( m_func, m_step, m_oneDimPrecision );
		break;
	case 4:
		method = new CDivisionMultiSearch( m_func, m_step, m_oneDimPrecision );
		break;
	case 5:
		method = new CDichotomyMultiSearch( m_func, m_step, m_oneDimPrecision );
		break;
	case 6:
		method = new CFibonacciMultiSearch( m_func, m_step, m_oneDimPrecision );
		break;
	case 7:
		method = new CGoldenSectionMultiSearch( m_func, m_step, m_oneDimPrecision );
		break;
	case 8:
		method = new CQuadraticInterpolationMultiSearch( m_func, m_step, m_oneDimPrecision );
		break;
	case 9:
		method = new CCubicInterpolationMultiSearch( m_func, m_step, m_oneDimPrecision );
		break;
	default:
		method = 0;
	}

	method->setParam( m_maxIteration, m_maxFunc, m_maxTime );
	return method;
}

Arg CMultiDimensionalWithOneSearch::getAgrad(  inputParam& _input )
{
	double xm = _input.x.getNormInf();
	double e100 = 100 * pow( 2.0f, -52.0f );
	double dh = abs(m_step) / 1000.0f;
	double dx = xm * e100;
	double d = max( dh, dx, e100 );
	
	double k = 1.0f / d;
	inputParam y = _input;
	Arg g = _input.x;
	
	for ( uInt i = 0; i < m_dimensions; ++i )
	{
		y.x[i] = _input.x[i] + d;
		y.fx = getFuncValue( y.x.getPointer());
		if ( isEndMethod() )
		{
			break;
		}
		g[i] = ( _input.fx - y.fx ) * k;
		y.x[i] =  _input.x[i];
	}

	/*m_grad = g;*/
	m_data->setDirectionGrad( g, true );
	return g;
}

Arg* CMultiDimensionalWithOneSearch::getHes( const inputParam& _input, Arg* _Hes )
{
	double xm = _input.x.getNormInf();
	double e100 = 1000000.0f * pow( 2.0f, -52.0f );
	double dh = abs(m_step) / 1000.0f;
	double dx = xm * e100;
	double d = max( dh, dx, e100 );
	
	double a = 1.0f / ( 2.0f * d );
	double b = 1.0f / ( d * d );
	inputParam y = _input;
	inputParam z = _input;
	m_grad = _input.x;

	Arg F;
	F.setFillIn(0,m_dimensions);
	setEye(_Hes);

	for ( uInt i = 0; i < m_dimensions; ++i )
	{
		y.x[i] = _input.x.x[i] + d;
		y.fx = getFuncValue( y.x.getPointer());
		if ( isEndMethod() )
		{
			m_exitFlag = true;
			break;
		}

		F[i] = y.fx;

		z.x[i] = _input.x.x[i] - d;
		z.fx = getFuncValue( z.x.getPointer());
		if ( isEndMethod() )
		{
			m_exitFlag = true;
			break;
		}

		m_grad[i] = ( z.fx - y.fx ) * a;
		_Hes[i].x[i] = ( (y.fx - _input.fx) + (z.fx - _input.fx) ) * b;
		y.x[i] = _input.x.x[i];
		z.x[i] = _input.x.x[i];
	}

	for ( uInt i = 0; i < m_dimensions - 1; ++i )
	{
		z.x[i] = z.x[i] + d;
		for ( uInt j = i + 1; j < m_dimensions; ++j )
		{
			z.x[j] = z.x[j] + d;
			z.fx = getFuncValue( z.x.getPointer());
			if ( isEndMethod() )
			{
				m_exitFlag = true;
				break;
			}
			_Hes[i].x[j] = ( (z.fx - F[i]) + (_input.fx - F[j]) ) * b;
			_Hes[j].x[i] = _Hes[i].x[j];
			z.x[i] = _input.x.x[i];
		}
		z.x[i] = _input.x.x[i];
	}

	/*m_grad = g;*/
	m_data->setDirectionGrad( m_grad, true );
	return _Hes;
}


double CMultiDimensionalWithOneSearch::getFuncValue( double * _x )
{
	m_countFunc ++;
	return m_function( _x );
}

double CMultiDimensionalWithOneSearch::max( const double& _value0, const double& _value1, const double& _value2 ) const
{
	double value = 0;
	if ( _value0 <= _value1 )
	{
		value =  _value1;
	}
	else
	{
		value =  _value0;
	}

	return ( _value2 <= value ) ? value : _value2;

}

bool CMultiDimensionalWithOneSearch::iterGrad( const Arg& _input )
{
	m_exitFlag = false;

	m_countIteration ++;
	if ( itSearch( _input ))
	{
		m_exitFlag = true;
	}
	m_step = stepSearch( m_prevOutputParam, m_outputParam );

	m_grad = getAgrad( m_outputParam );
	if ( isEndMethod() )
	{
		m_exitFlag = true;
	}
	return m_exitFlag;
}

double CMultiDimensionalWithOneSearch::stepSearch( const inputParam& _input, const inputParam& _output )
{
	m_H = (_output.x - _input.x).getNorm();
	m_S = 0.25f * ( m_S + 3.0f * m_H );
	if ( m_S == 0 )
	{
		m_state = "step = 0 ";
		m_exitFlag = true;
	}
	return m_H;
}

void CMultiDimensionalWithOneSearch::applyParam( const CODMS* _method )
{
	m_countFunc = _method->getCountFunc();
	m_countBestPoint = _method->getCountBestPoints();
	m_countIteration = _method->getCountIteration();
	
	m_prevOutputParam = m_outputParam;
	m_outputParam = _method->getOptPoint();
	m_delta = getDeltaValue( m_outputParam.x );
	m_funcValue = m_outputParam.fx;

}

bool CMultiDimensionalWithOneSearch::itSearch ( const Arg& _direction )
{
	m_exitFlag = false;
	double nd = _direction.getNorm();
	Arg dn = _direction;
	
	if ( nd > 0 )
	{
		dn = _direction * ( m_S / nd );
	}
	else
	{
		m_state = "vector direction of the zero";
		m_exitFlag = true;
	}

	m_oneDimMultiSearch = createOneDimMethod();
	m_oneDimMultiSearch->setFlagExit( m_flagPrecisionExit );

	m_oneDimMultiSearch->setNoIteration( m_countIteration );
	m_oneDimMultiSearch->setNoFunc( m_countFunc );
	m_oneDimMultiSearch->setNoBestPoints( m_countBestPoint + 1 );

	m_oneDimMultiSearch->calcArgMin( m_outputParam, dn );
	applyParam( m_oneDimMultiSearch );

	m_data->copyCalcData( m_oneDimMultiSearch->getData() );
	m_data->setOneDimensionalMethod( true, m_oneDimMultiSearch->getTitleMethod() );
		
	if ( isEndMethod() )
	{
		m_exitFlag = true;
	}

	return m_exitFlag;
}

double CMultiDimensionalWithOneSearch::getGradProduct( const Arg& _transpGrad, const Arg& _grad ) const
{
	double result = 0;
	for (uInt i = 0; i < m_dimensions; ++i )
	{
		result += _transpGrad.x[i] * _grad.x[i];
	}

	return result;
}

Arg* CMultiDimensionalWithOneSearch::getVectorProduct( const Arg& _vector, const Arg& _transpVector, Arg* _matrix ) const
{
	for (uInt i = 0; i < m_dimensions; ++i )
	{
		for (uInt j = 0; j < m_dimensions; ++j )
		{
			_matrix[i].x[j] = _vector.x[j] * _transpVector.x[i];
		}
	}

	return _matrix;
}

Arg* CMultiDimensionalWithOneSearch::getInvMatrix( const Arg* _matrix, Arg* _invMatrix ) const
{
	double denumenator = 1,numenator = 1;
	denumenator = gedMatixDeter( _matrix, m_dimensions );
    if ( denumenator == 0)
	{
		return _invMatrix;
	}

	if ( m_dimensions == 2 )
	{
		_invMatrix[0].x[0] = _matrix[1].x[1] / denumenator;
		_invMatrix[0].x[1] =- _matrix[0].x[1] / denumenator;
		_invMatrix[1].x[0] =- _matrix[1].x[0] / denumenator;
		_invMatrix[1].x[1] = _matrix[0].x[0] / denumenator;
	}
	else
	{
		int iSign=1;
		if ( denumenator == 0 ) 
		{
			return _invMatrix;
		}
		for ( uInt i = 0; i < m_dimensions; ++i )
		{
			for ( uInt j = 0; j < m_dimensions; ++j )
			{
				if ( ( (i + j) % 2 ) != 0 ) 
				{
					iSign =- 1;
				}
				else
				{
					iSign = 1;
				}
				numenator = iSign * gedMatixDeter( subMatrix(_matrix, j, i), m_dimensions );
				_invMatrix[i].x[j] = numenator / denumenator;
			}
		}
	}
	return _invMatrix;
}

Arg* CMultiDimensionalWithOneSearch::subMatrix(const Arg* _matrix, const uInt _col,uInt _row ) const
{
	int n = 0, m = 0;
	Arg* result  = new Arg[m_dimensions - 1];

	for ( uInt i = 0; i < m_dimensions - 1; ++i )
	{
		m = 0;
		for ( uInt j = 0; j < m_dimensions; ++j )
		{
			if ( (_col != i) && (_row != j) )
			{
				result[n][m] = _matrix[i].x[j];
				m ++;
			}
		}
		if ( _col != i ) n ++;
	}
	return result;
}

double CMultiDimensionalWithOneSearch::gedMatixDeter( const Arg* _matrix,const int& _count) const
{
	Arg* aMasInput;
	int a = 0,b = 1;
	double alg = 0;
	aMasInput = new Arg[_count];
	for( int i = 0; i < _count; ++i )
	{
		aMasInput[i].setFillIn(0,_count);
	}

	if (m_dimensions==2)
	{
		return _matrix[0].x[0] * _matrix[1].x[1] - _matrix[0].x[1] * _matrix[1].x[0];
	}

	for ( int n = _count; n > 0; n--)
	{
		for( int i = 0; i < _count - 1; ++i )
		{
			a = 0;
			for ( int j = 0; j < _count; ++j )
				if ( j != n - 1 )
				{
					aMasInput[i][a] = _matrix[i].x[j];
					a ++;
				}
		}
		b ++;
		alg += powl(-1,b) * _matrix[_count - 1].x[n - 1] * gedMatixDeter( aMasInput,_count - 1 );
	}

	return alg;
}

Arg* CMultiDimensionalWithOneSearch::setEye( Arg* _matrix ) const 
{
	for ( uInt i = 0; i < m_dimensions; ++i )
	{
		for ( uInt j = 0; j < m_dimensions; ++j )
		{
			if ( i == j )
			{
				_matrix[i].x[j] = 1.0f;
			}
			else
			{
				_matrix[i].x[j] = 0.0f;
			}
		}
	}

	return _matrix;
}

Arg CMultiDimensionalWithOneSearch::matrixProduct( const Arg* _matrix, const Arg& _vector ) const
{
	Arg result;
	result.setFillIn(0 ,m_dimensions);
	for ( uInt i = 0; i < m_dimensions; ++i )
	{
		for ( uInt j = 0; j < m_dimensions; ++j )
		{
			result[i] += _matrix[j].x[i] * _vector.x[j];
		}
	}
	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод Гаусса-Зейделя покоординатного спуска*/
GaussSeidelSearch::GaussSeidelSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
{
	m_nameMethod = NAME_METHOD_GAUSS_SEIDEL;
	m_precision = _precision;
	m_S = m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

inputParam GaussSeidelSearch::calcArgMin( Arg _initialPoint )
{
	m_dimensions = _initialPoint.getSize();
	saveHeadData( " Gauss-Seidel Search " );
	m_time->start();
	
	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint( _initialPoint.getPointer(), true );
	m_outputParam = m_inputParam;
	Arg d;
	d.setFillIn( 0.0f, m_dimensions );

	while ( 1 )
	{
		m_countIteration ++;

		for ( uInt i = 0; i < m_dimensions; ++i )
		{
			d[i] = 1;
			if ( itSearch( d ) )
			{
				m_exitFlag = true;
				break;
			}
			d[i] = 0;
		}

		stepSearch( m_inputParam, m_outputParam );
		if ( isEndMethod()  || m_exitFlag )
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
/*Метод Пауэлла сопряженных направлений*/
CPowellSearch::CPowellSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
{
	m_nameMethod = NAME_METHOD_FASTEST_DESCENT;
	m_precision = _precision;
	m_S = m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

inputParam CPowellSearch::calcArgMin( Arg _initialPoint )
{
	m_dimensions = _initialPoint.getSize();
	saveHeadData( " Powell Search " );
	m_time->start();
	
	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint( _initialPoint.getPointer(), true );
	m_outputParam = m_inputParam;
	
	Arg* D = new Arg[ m_dimensions ];
	
	for ( uInt i = 0; i < m_dimensions; ++i )
	{
		D[i].setFillIn( 0, m_dimensions );
	}
	setEye( D );
	Arg x;
	Arg y;
	Arg d;

	while(1)
	{
		m_countIteration ++;

		if ( itSearch(D[m_dimensions - 1]) )
		{
			break;
		}
		y = m_outputParam.x;

		for ( uInt i = 0; i < m_dimensions; ++i )
		{
			if ( itSearch(D[i]) )
			{
				m_exitFlag = true;
				break;
			}
		}
		x = m_outputParam.x;
		d = x - y;
		if ( d.getNormInf() == 0 )
		{
			m_state = "best point was not found";
			break;
		}

		for ( uInt i = 0; i < m_dimensions - 1; ++i )
		{
			D[i] = D[i + 1];
		}
		D[m_dimensions - 1] = d;

		m_step = stepSearch( m_inputParam, m_outputParam );
		if ( isEndMethod()  || m_exitFlag )
		{
			break;
		}
	}

	m_time->stop();
	m_state = "end";
	saveFootData();
		
	return m_outputParam;
}

Arg* CPowellSearch::setEye( Arg* _matrix )
{
	for ( uInt i = 0; i < m_dimensions; ++i )
	{
		for ( uInt j = 0; j < m_dimensions; ++j )
		{
			if ( i == j )
			{
				_matrix[i].x[j] = 1.0f;
			}
			else
			{
				_matrix[i].x[j] = 0.0f;
			}
		}
	}

	return _matrix;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод наискорейшего спуска*/
CFastestDescentSearch::CFastestDescentSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
	:
m_flagExit(false)
{
	m_nameMethod = NAME_METHOD_FASTEST_DESCENT;
	m_precision = _precision;
	m_S = m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

inputParam CFastestDescentSearch::calcArgMin( Arg _initialPoint )
{
	m_dimensions = _initialPoint.getSize();

	saveHeadData( " Fastest-Descent Search " );
	m_time->start();

	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint( _initialPoint.getPointer(), true );
	m_prevOutputParam = m_outputParam = m_inputParam;
	/*Arg d;
	d = getAgrad( m_outputParam );*/
	
	m_grad = getAgrad( m_outputParam );

	while(1)
	{
		if ( iterGrad(m_grad) )
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
/*Метод Флетчера-Ривса сопряженных градиентов*/
CFletcherReevesSearch::CFletcherReevesSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
	:
m_flagExit(false)
{
	m_nameMethod = NAME_METHOD_FLETCHER_REEVES;
	m_precision = _precision;
	m_S = m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

inputParam CFletcherReevesSearch::calcArgMin( Arg _initialPoint )
{
	m_dimensions = _initialPoint.getSize();

	saveHeadData( " Fletcher-Reeves Search " );
	m_time->start();

	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint( _initialPoint.getPointer(), true );
	m_outputParam = m_inputParam;
	Arg d;
	Arg g;

	g = d = getAgrad( m_outputParam );

	double a = getGradProduct( g, g );
	double b;
	double c;

	while(1)
	{
		if ( iterGrad(d) )
		{
			break;
		}
		g = getAgrad( m_outputParam );
		b = getGradProduct( g, g );
		c = b / a;
		d = g + d * c;
		a = b;
	}
		
	m_time->stop();
	m_state = "end";
	saveFootData();
		
	return m_outputParam;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод Полака-Рибьера сопряженных градиентов*/
CPolakRibiereSearch::CPolakRibiereSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
	:
m_flagExit(false)
{
	m_nameMethod = NAME_METHOD_POLAK_RIBIERE;
	m_precision = _precision;
	m_S = m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

inputParam CPolakRibiereSearch::calcArgMin( Arg _initialPoint )
{
	m_dimensions = _initialPoint.getSize();

	saveHeadData( " Polak-Ribiere Search " );
	m_time->start();

	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint( _initialPoint.getPointer(), true );
	m_outputParam = m_inputParam;
	Arg d;
	Arg gx;
	Arg gy;
	d = gx = getAgrad( m_outputParam );
	
	double c;

	while(1)
	{
		if ( iterGrad(d) )
		{
			break;
		}
		gy = getAgrad( m_outputParam );
		
		c = getGradProduct( gy, (gy - gx) ) / getGradProduct( gx, gx );
		d = gy + d * c;
		gx = gy;
	}
		
	m_time->stop();
	m_state = "end";
	saveFootData();
		
	return m_outputParam;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод ДФП переменной метрики*/
CDFPSearch::CDFPSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
	:
m_flagExit(false)
{
	m_nameMethod = NAME_METHOD_DFP_SEARCH;
	m_precision = _precision;
	m_S = m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

inputParam CDFPSearch::calcArgMin( Arg _initialPoint )
{
	m_dimensions = _initialPoint.getSize();

	saveHeadData( " DFP Search " );
	m_time->start();

	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint( _initialPoint.getPointer(), true );
	m_outputParam = m_inputParam;
	
	Arg gx = getAgrad( m_outputParam );
	Arg d = gx;
	Arg* G = new Arg[m_dimensions];
	Arg* mats = new  Arg[m_dimensions]; 
	Arg* matu = new  Arg[m_dimensions];
	for ( uInt i = 0; i < m_dimensions; ++i )
	{
		G[i].setFillIn(0,m_dimensions);
		mats[i].setFillIn(0,m_dimensions);
		matu[i].setFillIn(0,m_dimensions);
	}
	setEye(G);

	Arg s, p, u;
	Arg x, y;
	x = y = m_outputParam.x;

	while (1)
	{
		if ( iterGrad(d) )
		{
			break;
		}
		y = m_outputParam.x;
		s = y - x;
		p = gx - m_grad;

		if ( (!s.isNull()) && (!p.isNull()) )
		{
			u = matrixProduct( G, p );

			mats = getVectorProduct( s, s, mats );
			matu = getVectorProduct( u, u, matu );
			for ( uInt i = 0; i < m_dimensions; ++i )
			{
				
				G[i] = G[i] + mats[i] / getGradProduct(s, p)
					- matu[i] / getGradProduct(p, u);
			}
			d = matrixProduct( G,  m_grad );
		}
		else
		{
			setEye(G);
			d = m_grad;
		}
		x = y;
		gx = m_grad;
	}

	m_time->stop();
	m_state = "end";
	saveFootData();
		
	return m_outputParam;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод Ньютона*/
CNewtonSearch::CNewtonSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
	:
m_flagExit(false)
{
	m_nameMethod = NAME_METHOD_NEWTON_SEARCH;
	m_precision = _precision;
	m_S = m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

inputParam CNewtonSearch::calcArgMin( Arg _initialPoint )
{
	m_dimensions = _initialPoint.getSize();

	saveHeadData( " Newton Search " );
	m_time->start();

	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint( _initialPoint.getPointer(), true );
	m_outputParam = m_inputParam;
	
	m_Hes = new Arg[m_dimensions];
	Arg* invH = new Arg[m_dimensions];
	for ( uInt i = 0; i < m_dimensions; ++i )
	{
		m_Hes[i].setFillIn(0,m_dimensions);
		invH[i].setFillIn(0,m_dimensions);
	}
	Arg s;

	while (1)
	{
		m_countIteration ++;
		m_Hes = getHes( m_outputParam, m_Hes );
		if ( isEndMethod() )
		{
			break;
		}
		invH = getInvMatrix( m_Hes, invH);
		s = matrixProduct( invH, m_grad );
		m_outputParam.x = m_outputParam.x + s;
		m_step = s.getNorm();
		m_state = "iteration";
		m_outputParam.fx = newPoint( m_outputParam.x.getPointer(), false );
	}

	m_time->stop();
	m_state = "end";
	saveFootData();
		
	return m_outputParam;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Метод Ньютона-Рафсона*/
CNewtonRaphsonSearch::CNewtonRaphsonSearch( CFuncionMultiDimensional* _func, double _step, double _precision )
	:
m_flagExit(false)
{
	m_nameMethod = NAME_METHOD_NEWTON_RAPHSON;
	m_precision = _precision;
	m_S = m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

inputParam CNewtonRaphsonSearch::calcArgMin( Arg _initialPoint )
{
	m_dimensions = _initialPoint.getSize();

	saveHeadData( " Newton-Raphson Search " );
	m_time->start();

	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint( _initialPoint.getPointer(), true );
	m_outputParam = m_inputParam;
	
	Arg d = getAgrad( m_outputParam );
	
	m_Hes = new Arg[m_dimensions];
	Arg* invH = new Arg[m_dimensions];
	for ( uInt i = 0; i < m_dimensions; ++i )
	{
		m_Hes[i].setFillIn(0,m_dimensions);
		invH[i].setFillIn(0,m_dimensions);
	}
	
	while (1)
	{
		m_countIteration ++;

		if ( iterGrad(d) )
		{
			break;
		}
		m_Hes = getHes( m_outputParam, m_Hes );
		if ( isEndMethod() )
		{
			break;
		}
		if ( (uInt)getRank(m_Hes) < m_dimensions )
		{
			d = m_grad;
		}
		else
		{
			invH = getInvMatrix( m_Hes, invH);
			d = matrixProduct( invH, m_grad );
		}
	}

	m_time->stop();
	m_state = "end";
	saveFootData();
		
	return m_outputParam;
}

int CNewtonRaphsonSearch::getRank( const Arg* _matrix ) const
{
	int r = 0;
	for ( uInt i = 0; i < m_dimensions ; i++ )
	{
		if (_matrix[i].x[i] != 0 )
		{
			r ++;
		}
	}
	
	return r;
}
