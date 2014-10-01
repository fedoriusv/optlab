#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include "Param.h"

namespace metopt
{
	typedef double(*PTRFUNCONEDIM)(double& _x);
	typedef double(*PTRFUNCMULTDIM)(double* _x);

	///////////////////////////////////////////////////////////////////////////////////////////////////

	class CFunction
	{
	protected:
		CFunction(char* _name);
		char*		m_funcName;
	public:
		char*		getFuncionName() const;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////

	class CFuncionOneDimensional : public CFunction
	{
	public:
		enum TYPE_FUNC
		{
			TYPE_FUNC_1 = 0,
			TYPE_FUNC_2,
			TYPE_FUNC_3
		};
		CFuncionOneDimensional(double(*_function)(double& _x), inputParam2D& _optPoint, char* _name = "unknown");
		void			setFunctionType(TYPE_FUNC _type);
		TYPE_FUNC		getFunctionType() const;
		void			setInitPoint(inputParam2D& _initPoint);
		inputParam2D	getInitPoint() const;
		inputParam2D	getOptPoint() const;
		PTRFUNCONEDIM	getFunction() const;
		void			setOneDimensionalMethod(NAME_METHOD _nameMethod);
	private:
		TYPE_FUNC		m_typeFunc;
		inputParam2D	m_initPoint;
		inputParam2D	m_optPoint;
		double(*m_function)(double& _x);
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////

	class CFuncionMultiDimensional : public CFunction
	{
	public:
		CFuncionMultiDimensional(double(*_function)(double* _x), inputParam& _optPoint, char* _name = "unknown");

		void			setInitPoint(inputParam& _initPoint);
		inputParam		getInitPoint() const;

		void			setInterval(const Arg& _A, const Arg& _B);
		interval		getInterval() const;

		inputParam		getOptPoint() const;
		PTRFUNCMULTDIM	getFunction() const;
	private:

		interval		m_interval;
		inputParam		m_initPoint;
		inputParam		m_optPoint;
		double(*m_function)(double* _x);
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
