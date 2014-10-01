#include "Function.h"

using namespace metopt;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CFunction::CFunction( char* _name )
	:
m_funcName( _name )
{
}

char* CFunction::getFuncionName() const
{
	return m_funcName;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CFuncionOneDimensional::CFuncionOneDimensional	( double (*_function)(double& _x), inputParam2D& _optPoint, char* _name )
	:
CFunction( _name ),
m_optPoint(_optPoint),
m_initPoint(inputParam2D(0,0))
{
	m_function = _function;
	m_funcName = _name;
	m_typeFunc = TYPE_FUNC_1;
}

void CFuncionOneDimensional::setFunctionType( TYPE_FUNC _type )
{
	_type = m_typeFunc;
}

CFuncionOneDimensional::TYPE_FUNC	CFuncionOneDimensional::getFunctionType() const
{
	return m_typeFunc; 
}

void CFuncionOneDimensional::setInitPoint( inputParam2D& _initPoint )
{
	m_initPoint = _initPoint;
}

inputParam2D CFuncionOneDimensional::getInitPoint() const
{
	return m_initPoint;
}

PTRFUNCONEDIM	CFuncionOneDimensional::getFunction() const
{
	return m_function;
}

inputParam2D CFuncionOneDimensional::getOptPoint() const
{
	return m_optPoint;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CFuncionMultiDimensional::CFuncionMultiDimensional	( double (*_function)(double* _x), inputParam& _optPoint, char* _name )
	:
CFunction( _name ),
m_optPoint(_optPoint)
//m_initPoint(inputParam(0,NULL))
{
	m_function = _function;
	m_funcName = _name;
}

void CFuncionMultiDimensional::setInitPoint( inputParam& _initPoint )
{
	m_initPoint = _initPoint;
}

inputParam CFuncionMultiDimensional::getInitPoint() const
{
	return m_initPoint;
}

inputParam CFuncionMultiDimensional::getOptPoint() const
{
	return m_optPoint;
}

PTRFUNCMULTDIM	CFuncionMultiDimensional::getFunction() const
{
	return m_function;
}

void CFuncionMultiDimensional::setInterval( const Arg& _A, const Arg& _B )
{
	m_interval.m_pointA = _A;
	m_interval.m_pointB = _B;
}

interval CFuncionMultiDimensional::getInterval() const
{
	return m_interval;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////