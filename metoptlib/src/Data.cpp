#include "Data.h"

using namespace metopt;

CData::CData()
	: m_file(NULL)
	, m_pNameFile("")
	, m_typeMethod( TYPE_ONE_DIMENSIONAL )
	, m_typeExit( TYPE_EXIT_NONE )
	, m_exitFlag( TYPE_EXIT_PRECISION_NONE )
	, m_nameMethod( NAME_METHOD_NONE )
	, m_step(0.0f)
	, m_precision(0.0f)
	, m_time(0)
{
}

CData::~CData()
{
}

cpChar CData::getStringExit() const
{
	switch( m_typeExit )	
	{
	case 0:
		return "Begin point";
	case 1:
		return "Reached the maximum number of iterations";
	case 2:
		return "Reached the allowed number of function evaluations";
	case 3:
		return "limit time over";
	case 4:
		switch( m_exitFlag )
		{
		case 0:
			return "None precision";
		case 1:
			return "Achieved a given accuracy of the step";
		case 2:
			return "Achieved a given accuracy in function";
		case 3:
			return "Given accuracy is reached the variables";
		default:
			return "Precision";
		}
	default:
		return "None limit";
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CDataOneDimensional::CDataOneDimensional()
{
	m_typeMethod = TYPE_ONE_DIMENSIONAL;
	m_nameMethod = NAME_METHOD_NONE;
}

int CDataOneDimensional::getCountIteration() const
{
	return m_funcIteration[m_funcIteration.size() - 1];
}

int CDataOneDimensional::getCountBest() const
{
	return m_funcBestPoint[m_funcIteration.size() - 1];
}

int CDataOneDimensional::getCountCalc() const
{
	return m_funcCalc[m_funcCalc.size() - 1];
}

double CDataOneDimensional::getElapsedTime() const
{
	return (double)m_time / 1000.0f;
}

void CDataOneDimensional::setInitData( const double&	_step,
									const double&		_precision,
									const inputParam2D& _beginPoint,
									const inputParam2D& _optPoint,
									const uInt&			_maxIteration,
									const uInt&			_maxFunc,
									const uInt&			_maxTime)
{
	m_step = _step;
	m_precision = _precision;
	m_beginPoint = _beginPoint;
	m_optPoint = _optPoint;
	m_maxIteration = _maxIteration;
	m_maxFunc = _maxFunc;
	m_maxTime = _maxTime;
}

void CDataOneDimensional::setNewPointData( const uInt&		_funcIteration,
										const uInt&			_funcBestPoint,
										const uInt&			_funcCalc,
										const double&		_step,
										const double&		_delta,
										const inputParam2D& _point,
										const char*			_state )
{
	m_funcIteration.push_back( _funcIteration );
	m_funcBestPoint.push_back( _funcBestPoint );
	m_funcCalc.push_back( _funcCalc );
	m_stepArray.push_back( _step );
	m_delta.push_back( _delta );
	m_points.push_back( _point );
	m_state.push_back( _state );
}

void CDataOneDimensional::setEndMethodData( const TYPE_EXIT				_typeExit,
										const TYPE_EXIT_PRECISION_FLAG	_exitFlag,
										const outputParam2D&			_finalPoint,
										const uInt&						_time,
										cpChar							_pFuncName,
										cpChar							_pMethodName )
{
	m_typeExit = _typeExit;
	m_exitFlag = _exitFlag;
	m_finalPoint = _finalPoint;
	m_time = _time;
	m_pFuncName = _pFuncName;
	m_pMethodName = _pMethodName;
}

outputParam2D CDataOneDimensional::getSearchPoint() const
{
	return m_finalPoint;
}

inputParam2D CDataOneDimensional::getInputPoint() const
{
	return m_beginPoint;
}

double** CDataOneDimensional::getPointsPointer() const
{
	double** points = new double*[2];
	for ( uInt i = 0; i < m_points.size(); ++i )
	{
		points[i] = new double[m_points.size()];
	}

	for ( uInt i = 0; i < m_points.size(); ++i )
	{
		points[0][i] = m_points[i].x;
		points[1][i] = m_points[i].fx;
	}

	return points;
}

int CDataOneDimensional::getCountPoints() const
{
	return m_points.size();
}

void CDataOneDimensional::addCalcData( const CDataOneDimensional* _data )
{
	m_funcCalc = _data->m_funcCalc;
	m_funcCalc.pop_back();
	m_funcBestPoint = _data->m_funcBestPoint;
	m_funcBestPoint.pop_back();
	m_funcIteration = _data->m_funcIteration;
	m_funcIteration.pop_back();

	m_stepArray = _data->m_stepArray;
	m_stepArray.pop_back();
	m_delta = _data->m_delta;
	m_delta.pop_back();
	m_points = _data->m_points;
	m_points.pop_back();
	m_state = _data->m_state;
	m_state.pop_back();
}

void CDataOneDimensional::printToFile( cpChar _nameFile )
{
	m_pNameFile = _nameFile;

	m_file = fopen( m_pNameFile , "w+");
	fprintf( m_file, m_pFuncName );
	fprintf( m_file, "  " );
	fprintf( m_file, m_pMethodName );
	fprintf( m_file, "\n\nH = %f, Tol = %f, Nfm = %i, Nim = %i, Tm = %.3f\n", m_step, m_precision, m_maxFunc, m_maxIteration, (double)m_maxTime/1000.0f );
	fprintf( m_file, "------------------------------------------------------------------------\n");
	fprintf( m_file, " Ni    Nb    Nf      H         Dx        F1         x1		   State   \n");
	fprintf( m_file, "------------------------------------------------------------------------\n");
	
	for ( uInt i = 0; i < m_points.size(); ++i )
	{
		fprintf( m_file, "  %2i   %2i   %2i   %8.5f   %8.4f    %8.5f    %8.5f	",
			m_funcIteration[i], m_funcBestPoint[i], m_funcCalc[i], m_stepArray[i], m_delta[i], m_points[i].fx, m_points[i].x);
		fprintf( m_file, m_state[i] );
		fprintf( m_file,"\n" );
	}
	
	fprintf( m_file, "------------------------------------------------------------------------\n");
	fprintf( m_file, "Type Exit: %i \n" , m_typeExit );
	fprintf( m_file, getStringExit());
	fprintf( m_file, "\nNi = %i, Nf = %i, T = %.3f sec\n", m_funcIteration[m_funcIteration.size()-1], m_funcCalc[m_funcCalc.size()-1], (double)m_time/1000.0f );
	fprintf( m_file, "x = %.12f\nFx = %.12f\n", m_finalPoint.c.x, m_finalPoint.c.fx );
	fprintf( m_file, "\nExp: \nx = %.12e\nFx = %.12e\n", m_finalPoint.c.x, m_finalPoint.c.fx );
	fclose( m_file );
}

CDataOneDimensional::~CDataOneDimensional()
{
	m_funcCalc.clear();
	m_funcBestPoint.clear();
	m_funcIteration.clear();
	
	m_stepArray.clear();
	m_delta.clear();
	m_points.clear();
	m_state.clear();
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CDataMultiDimensional::CDataMultiDimensional()
	: m_usedOneDimMethod(false)
	, m_usedGrad(false)
	, m_coutDimensions(0)
{
	m_typeMethod = TYPE_MULTI_DIMENSIONAL;
	m_nameMethod = NAME_METHOD_NONE;
}

void CDataMultiDimensional::setInitData( const uInt&			_coutDimensions, 
											const double&		_step,
											const double&		_precision,
											const inputParam&	_beginPoint,
											const inputParam&	_optPoint,
											const uInt&			_maxIteration,
											const uInt&			_maxFunc,
											const uInt&			_maxTime )
{
	m_coutDimensions = _coutDimensions;
	m_step = _step;
	m_precision = _precision;
	m_beginPoint = _beginPoint;
	m_optPoint = _optPoint;
	
	m_maxIteration = _maxIteration;
	m_maxFunc = _maxFunc;
	m_maxTime = _maxTime;
}

void CDataMultiDimensional::setNewPointData( const uInt&			_funcIteration,
												const uInt&			_funcBestPoint,
												const uInt&			_funcCalc,
												const double&		_step,
												const double&		_delta,
												const inputParam&	_point,
												const char*			_state )
{
	m_funcIteration.push_back( _funcIteration );
	m_funcBestPoint.push_back( _funcBestPoint );
	m_funcCalc.push_back( _funcCalc );
	m_stepArray.push_back( _step );
	m_delta.push_back( _delta );
	m_points.push_back( _point );
	m_state.push_back( _state );
}

void CDataMultiDimensional::setEndMethodData( const TYPE_EXIT			_typeExit,
												const TYPE_EXIT_PRECISION_FLAG _exitFlag,
												const inputParam&		_finalPoint,
												const uInt&				_time,
												cpChar					_pFuncName,
												cpChar					_pMethodName )
{
	m_typeExit = _typeExit;
	m_exitFlag = _exitFlag;
	m_finalPoint = _finalPoint;
	m_time = _time;
	m_pFuncName = _pFuncName;
	m_pMethodName = _pMethodName;
}

inputParam CDataMultiDimensional::getSearchPoint() const
{
	return m_optPoint;
}

inputParam CDataMultiDimensional::getInputPoint() const
{
	return m_beginPoint;
}

double** CDataMultiDimensional::getPointsPointer()
{
	double** points = new double*[m_coutDimensions + 1];
	for ( uInt i = 0; i < m_coutDimensions + 1; ++i )
	{
		points[i] = new double[m_points.size()];
	}

	for ( uInt j = 0; j < m_points.size(); ++j )
	{
		points[ m_coutDimensions ][j] = m_points[j].fx;
	}
	
	for ( uInt j = 0; j < m_points.size(); ++j )
	{
		for ( uInt i = 0; i < m_coutDimensions; ++i )
		{
			points[i][j] = m_points[j].x[i];
		}
	}
	
	

	return points;
}

int CDataMultiDimensional::getCountPoints() const
{
	return m_points.size();
}

int CDataMultiDimensional::getCountIteration() const
{
	return m_funcIteration[m_funcIteration.size() - 1];
}

int CDataMultiDimensional::getCountCalc() const
{
	return m_funcCalc[m_funcCalc.size() - 1];
}

int CDataMultiDimensional::getCountBest() const
{
	return m_funcBestPoint[m_funcBestPoint.size() - 1];
}

double CDataMultiDimensional::getElapsedTime() const
{
	return (double)m_time / 1000.0f;
}

void CDataMultiDimensional::addCalcData( const CDataMultiDimensional* _data )
{
	m_funcCalc = _data->m_funcCalc;
	m_funcCalc.pop_back();
	m_funcBestPoint = _data->m_funcBestPoint;
	m_funcBestPoint.pop_back();
	m_funcIteration = _data->m_funcIteration;
	m_funcIteration.pop_back();

	m_stepArray = _data->m_stepArray;
	m_stepArray.pop_back();
	m_delta = _data->m_delta;
	m_delta.pop_back();
	m_points = _data->m_points;
	m_points.pop_back();
	m_state = _data->m_state;
	m_state.pop_back();
}

void CDataMultiDimensional::copyCalcData( const CDataMultiDimensional* _data )
{
	m_funcCalc.reserve( _data->m_funcCalc.size() + m_funcCalc.size() );
	m_funcCalc.insert( m_funcCalc.end(), _data->m_funcCalc.begin(), _data->m_funcCalc.end() );

	m_funcBestPoint.reserve( _data->m_funcBestPoint.size() + m_funcBestPoint.size() );
	m_funcBestPoint.insert( m_funcBestPoint.end(), _data->m_funcBestPoint.begin(), _data->m_funcBestPoint.end() );

	m_funcIteration.reserve( _data->m_funcIteration.size() + m_funcIteration.size() );
	m_funcIteration.insert( m_funcIteration.end(), _data->m_funcIteration.begin(), _data->m_funcIteration.end() );


	m_stepArray.reserve( _data->m_funcCalc.size() + m_stepArray.size() );
	m_stepArray.insert( m_stepArray.end(), _data->m_stepArray.begin(), _data->m_stepArray.end() );

	m_delta.reserve( _data->m_delta.size() + m_delta.size() );
	m_delta.insert( m_delta.end(), _data->m_delta.begin(), _data->m_delta.end() );

	m_points.reserve( _data->m_points.size() + m_points.size() );
	m_points.insert( m_points.end(), _data->m_points.begin(), _data->m_points.end() );

	m_state.reserve( _data->m_state.size() + m_state.size() );
	m_state.insert( m_state.end(), _data->m_state.begin(), _data->m_state.end() );
}

void CDataMultiDimensional::setOneDimensionalMethod( bool _used, cpChar _nameMethod )
{
	m_usedOneDimMethod = _used;
	m_pOneDimMethodName = _nameMethod;
}

void CDataMultiDimensional::setDirectionGrad( const Arg& _grad, bool _used )
{
	m_usedGrad = _used;
	m_grad = _grad;
}

void CDataMultiDimensional::printToFile( cpChar _nameFile )
{
	m_pNameFile = _nameFile;

	m_file = fopen( m_pNameFile , "w+");
	fprintf( m_file, m_pFuncName );
	fprintf( m_file, "  " );
	if ( m_usedOneDimMethod )
		fprintf( m_file, m_pOneDimMethodName );
	fprintf( m_file, "  " );
	fprintf( m_file, m_pMethodName );
	
	fprintf( m_file, "\n\nH = %f, Tol = %f, Nfm = %i, Nim = %i\n", m_step, m_precision, m_maxFunc, m_maxIteration );
	fprintf( m_file, "-----------------------------------------------------------------------");
	for ( uInt j = 1; j < m_coutDimensions; ++j )
	{
		fprintf( m_file,"-------------");
	}
	fprintf( m_file,"--------------\n");
	fprintf( m_file, "    Ni    Nb    Nf       H          Dx           F1           x1    ");
	for ( uInt j = 1; j < m_coutDimensions; ++j )
	{
		fprintf( m_file,"       x%i",j+1);
	}
	fprintf( m_file,"         State   \n");
	fprintf( m_file, "-----------------------------------------------------------------------");
	for ( uInt j = 1; j < m_coutDimensions; ++j )
	{
		fprintf( m_file,"-------------");
	}
	fprintf( m_file,"--------------\n");
	
	for ( uInt i = 0; i < m_points.size(); ++i )
	{
		fprintf( m_file, "   %3i   %3i   %3i   %8.5f	%8.4f   %10.5f ",
			m_funcIteration[i], m_funcBestPoint[i], m_funcCalc[i], m_stepArray[i], m_delta[i], m_points[i].fx );
		for ( uInt j = 0; j < m_coutDimensions; ++j )
		{
			fprintf( m_file, "   %10.5f ",	m_points[i].x[j] );
		}
		fprintf( m_file,"    %s", m_state[i] );
		fprintf( m_file,"\n" );
	}
	
	fprintf( m_file, "------------------------------------------------------------------------");
	for ( uInt j = 1; j < m_coutDimensions; ++j )
	{
		fprintf( m_file,"-------------");
	}
	fprintf( m_file,"--------------\n");
	fprintf( m_file, "Type Exit: %i \n" , m_typeExit );
	fprintf( m_file, getStringExit());
	fprintf( m_file, "\nNi = %i, Nf= %i, T = %.4f sec\n", m_funcIteration[m_funcIteration.size()-1], m_funcCalc[m_funcCalc.size()-1], (double)m_time/1000.0f  );
	for ( uInt j = 0; j < m_coutDimensions; ++j )
		{
			fprintf( m_file, "x%i = %.12f ",j+1, m_finalPoint.x[j] );
		}
	fprintf( m_file, "\nFx = %.12f\n", m_finalPoint.fx );

	if ( m_usedGrad )
	{
		fprintf( m_file, "Grad:\n");
		for ( uInt j = 0; j < m_coutDimensions; ++j )
			{
				fprintf( m_file, "g%i = %.6f ",j+1, m_grad.x[j] );
			}
	}

	fprintf( m_file, "\nExp:\n");
	for ( uInt j = 0; j < m_coutDimensions; ++j )
		{
			fprintf( m_file, "x%i = %.12e ",j+1, m_finalPoint.x[j] );
		}
	fprintf( m_file, "\nFx = %.12e\n", m_finalPoint.fx );
	fclose( m_file );
}

CDataMultiDimensional::~CDataMultiDimensional()
{
	m_funcCalc.clear();
	m_funcBestPoint.clear();
	m_funcIteration.clear();
	
	m_stepArray.clear();
	m_delta.clear();
	m_points.clear();
	m_state.clear();
}
