#ifndef _FUNC_H_
#define _FUNC_H_

#include "MethodsOneDimensionalSearch.h"
#include "MethodsMultiDimensionalSearch.h"
#include "MethodsMultiDimensionalWithOneSearch.h"
#include "MethodsGeneryAlgorithm.h"
#include "Data.h"
#include "Param.h"

namespace metopt
{
	class CFunc
	{
	private:
		TYPE_METHOD m_typeMethod;
		NAME_METHOD m_nameMethod;
		CODS*		m_oneMethod;
		CMDS*		m_multiMethod;

		CFOD*		m_oneFunc;
		CFMD*		m_multiFunc;
		bool		createMethod();
		inputParam	inputParamFromOutput2D(const outputParam2D& _output2D);
	public:
		CFunc(CFOD* _func);
		CFunc(CFMD* _func);
		/*����� ������:
		������ ������� � ����� Param.h*/
		void		setMethod(NAME_METHOD _nameMethod);
		/*������ ��������*/
		void		setPrecision(const double _precision = 0.01);
		/*������ ���*/
		void		setStep(const double _step = 0.1);
		/*������� ����������:
		param\n
		_maxIteration - ����. ���������� ��������
		_maxFuncCalc - ����. ���������� �������
		_maxTime - ����. ����� �����*/
		void		setParam(const uInt _maxIteration = 100,
			const uInt	 _maxFuncCalc = 100,
			const uInt	 _maxTime = 10000);
		/*���� ������:
		������ ���������� � ����� Param.h*/
		void		setFlagExit(TEP_FLAG _flagExit = TYPE_EXIT_PRECISION_FUNC);
		/*������ ���������� ����� ��� ����������� ������*/
		void		setOneDimensionalMethod(NAME_METHOD _nameMethod);
		/*������ �������� ��� ����������� ������*/
		void		setOneDimensionalPrecision(const double _precision = 0.01);
		/*����� ��������:
		_initialPoint - ��������� �����*/
		inputParam	calcArgMin(const Arg& _initialPoint);
		CDMD*		getMultiData() const;
		CDOD*		getData() const;
		CFMD*		getMultiFunc() const;
		CFOD*		getFunc() const;
	};
}

#endif