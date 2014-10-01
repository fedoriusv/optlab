#include "Param.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int sign(double _value)
{
	if (_value > 0)
	{
		return 1;
	}
	else if (_value < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace metopt;

//OneDimensional
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//output
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
outputParam2D& outputParam2D::operator=(const outputParam2D& _param )
{
	if ( this == &_param )
		return *this;
	
	this->a = _param.a;
	this->b = _param.b;
	this->c = _param.c;

	return *this;
};

bool outputParam2D::operator==(const outputParam2D& _param )
{
	return ( (a == _param.a) && (b == _param.b) && (c == _param.c) );
};

//input
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inputParam2D& inputParam2D::operator=(const inputParam2D& _param )
{
	if ( this == &_param )
		return *this;
	
	this->x = _param.x;
	this->fx = _param.fx;

	return *this;
};

inputParam2D inputParam2D::operator+(const inputParam2D& _param )
{
	inputParam2D param(0,0);
	param.x = x + _param.x;
	param.fx = fx + _param.fx;

	return param;
};

inputParam2D inputParam2D::operator-(const inputParam2D& _param )
{
	inputParam2D param(0,0);
	param.x = x - _param.x;
	param.fx = fx - _param.fx;

	return param;
};

bool inputParam2D::operator==(const inputParam2D& _param )
{
	return ( (x == _param.x) && (fx == _param.fx) );
};

bool inputParam2D::operator<(const inputParam2D& _param )
{
	return ( this->fx < _param.fx  );
}

//MultiDimensional
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//X
Arg::Arg( const double* _x )
{
	for ( uInt i = 0; i < sizeof(_x)/2; ++i )
	{
		x.push_back(_x[i]);
	}
}

Arg::Arg( const uInt _dimension )
{
	x.reserve( _dimension );
	for ( uInt i = 0; i < _dimension; ++i )
	{
		x.push_back( 0 );
	}
}

Arg::Arg( const Arg& _X )
{
	for ( uInt i = 0; i < _X.getSize(); ++i )
	{
		x.push_back( _X.x[i] );
	}
}

uInt Arg::getSize() const
{
	return x.size();
}

double* Arg::getPointer()
{
	return &x[0];
}

void Arg::setPointer( const double* _x )
{
	if (!x.size() == 0)
	{
		for ( uInt i = 0; i < sizeof(_x)/2; ++i )
		{
			x[i] = _x[i];
		}
	}
	else
	{
		for ( uInt i = 0; i < sizeof(_x)/2; ++i )
		{
			x.push_back( _x[i] );
		}
	}
}

void Arg::deleteElement( const uInt& _index )
{
	x.erase( x.begin() + _index );
}

void Arg::abs()
{
	for ( uInt i = 0; i < x.size(); ++i )
	{
		x[i] = fabs( x[i] );
	} 
}

double Arg::getMax() const
{
	double max = x[0];
	for ( uInt i = 0; i < x.size(); ++i )
	{
		if ( max < x[i] )
		{
			max = x[i];
		}
	}

	return max;
}

double Arg::getSum() const
{
	double sum = 0;
	for (uInt i = 0; i < x.size(); ++i)
	{
		sum += x[i];
	}

	return sum;
}

bool Arg::isNull() const
{
	for ( uInt i = 0; i < x.size(); ++i )
	{
		if ( x[i] != 0 )
		{
			return false;
		}
	}
	return true;
}

double&	Arg::operator[]( const uInt& _index )
{
	static double value = -1;

	if ( _index >= 0 && _index < x.size() )
	{
		return x[ _index ];
	}

	return value;
}

const double& Arg::operator[](const uInt& _index) const
{
	static double value = -1;

	if (_index >= 0 && _index < x.size())
	{
		return x[_index];
	}

	return value;
}

Arg& Arg::operator=( const Arg& _X )
{
	if ( this == &_X )
		return *this;

	if (!x.size() == 0)
	{
		for ( uInt i = 0; i < _X.x.size(); ++i )
		{
			x[i] = _X.x[i];
		}
	}
	else
	{
		for ( uInt i = 0; i < _X.x.size(); ++i )
		{
			x.push_back( _X.x[i] );
		}
	}

	return *this;
}

Arg Arg::operator+( const Arg& _X ) const
{
	Arg objX;
	for ( uInt i = 0; i < x.size(); ++i )
	{
		objX.x.push_back( x[i] + _X.x[i] );
	}

	return objX;
}

Arg	Arg::operator+( const double& _scalar ) const
{
	Arg objX;
	for ( uInt i = 0; i < x.size(); ++i )
	{
		objX.x.push_back( x[i] + _scalar );
	}

	return objX;
}

Arg Arg::operator-( const Arg& _X ) const
{
	Arg objX;
	for ( uInt i = 0; i < x.size(); ++i )
	{
		objX.x.push_back( x[i] - _X.x[i] );
	}

	return objX;
}

Arg Arg::operator*( const double& _scalar ) const
{
	Arg objX;
	for ( uInt i = 0; i < x.size(); ++i )
	{
		objX.x.push_back( x[i] * _scalar );
	}

	return objX;
}

Arg	Arg::operator/( const Arg& _X ) const
{
	Arg result;
	for ( uInt i = 0; i < x.size(); ++i )
	{
		if ( _X.x[i] == 0 )
		{
			result.x[i] = 0;
		}
		else
		{
			result.x.push_back( x[i] / _X.x[i] );
		}
	}

	return result;
}

Arg Arg::operator/( const double& _scalar ) const
{
	Arg result;
	for ( uInt i = 0; i < x.size(); ++i )
	{
		if ( _scalar == 0 )
		{
			result.x[i] = 0;
		}
		else
		{
			result.x.push_back( x[i] / _scalar );
		}
	}

	return result;
}

Arg	Arg::operator*( const Arg& _X ) const
{
	Arg result;
	for ( uInt i = 0; i < x.size(); ++i )
	{
		result.x.push_back( x[i] * _X.x[i] );
	}

	return result;
}

double	Arg::getDotProduct( const Arg& _X ) const
{
	double scalar = 0;

	for ( uInt i = 0; i < x.size(); ++i )
	{
		scalar += ( _X.x[i] - x[i] ) * ( _X.x[i] - x[i] );
	}

	return sqrt( scalar );
}

void Arg::setFillIn( const double& _value, const uInt& _size )
{
	for ( uInt i = 0; i < _size; ++i )
	{
		x.push_back(_value);
	}
}

void Arg::setRendom(const double& _rangeMin, const double& _rangeMax)
{
	for (uInt i = 0; i < x.size(); ++i)
	{
		double u = (double)rand() / (RAND_MAX + 1) * (_rangeMax - _rangeMin) + _rangeMin;
		x[i] = u;
	}
}

bool Arg::operator==( const Arg& _X ) const
{
	for ( uInt i = 0; i < x.size(); ++i )
	{
		if (x[i] != _X.x[i])
		{
			return false;
		}
	}
	return true;
}

double Arg::getNorm() const
{
	double norm = 0;
	for ( uInt i = 0; i < x.size(); ++i )
	{
		norm += ( x[i] * x[i] );
	}

	return sqrt( norm );
}

double Arg::getNormInf() const
{
	double norm = 0;
	for ( uInt i = 0; i < x.size(); ++i )
	{
		if ( norm < fabs(x[i]) )
		{
			norm = fabs(x[i]);
		}
	}

	return norm;
}

//Arg::~Arg()
//{ 
//	x.clear();
//};

////inputParam
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inputParam::inputParam( double _fx, double* _x )
	: x(_x)
{
	fx = _fx;
	//x.setPointer(_x);	
};

inputParam::inputParam( double _fx, std::vector<double> _x )
{
	fx = _fx;
	x = _x;
};

//inputParam::~inputParam()
//{
//	x.~Arg();
//}

uInt inputParam::getSize() const
{
	return x.getSize();
}

inputParam& inputParam::operator=(const inputParam& _param )
{
	if ( this == &_param )
		return *this;
	
	fx = _param.fx;
	x = _param.x;
	
	return *this;
};

bool inputParam::operator==( inputParam& _param )
{
	for ( uInt i = 0; i < x.getSize(); ++i )
	{
		if (x[i] != _param.x[i])
		{
			return false;
		}
	}
	return ( fx == _param.fx );
};

bool inputParam::operator<(const inputParam& _param )
{
	return ( this->fx < _param.fx  );
}

bool inputParam::sortByFunc(const inputParam& _x1, const inputParam& _x2)
{
	return _x1.fx < _x2.fx;
}

//CTimer
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CTimer::CTimer()
{
	m_time = new timeb();
}
void CTimer::start()
{ 
	ftime( m_time );
	m_start._time = (int)m_time->time;
	m_start._millisec = (int)m_time->millitm;
}

void CTimer::stop()
{ 
	ftime( m_time ); 
	m_stop._time = (int)m_time->time;
	m_stop._millisec = (int)m_time->millitm;
}

int CTimer::seconds() const
{ 
	return  (m_stop._time - m_start._time); 
}

int CTimer::milliseconds() const
{ 
	return 1000*seconds() + (m_stop._millisec - m_start._millisec); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////