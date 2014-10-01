#ifndef _METHODS_MULTI_DIMENSION_SEARCH_H_
#define _METHODS_MULTI_DIMENSION_SEARCH_H_

#include "MultiDimensionalSearch.h"

namespace metopt
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*����� ����-������ (Hooke-Jeeves)*/
	class CHookeJeevesSearch : public CMultiDimensionalSearch
	{
	protected:
		bool m_flagExit;
	public:
		CHookeJeevesSearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		inputParam	calcArgMin(Arg _initialPoint);
		inputParam  research(const inputParam& _param);
	};

	/*����� �������-���� (Nelder-Mead)*/
	class CNelderMeadSearch : public CMultiDimensionalSearch
	{
	protected:
		bool		m_flagExit;
		Arg			maxRow(const Arg* _matrix) const;
		Arg			sumRow(const Arg* _matrix) const;
	public:
		CNelderMeadSearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		inputParam	calcArgMin(Arg _initialPoint);
	};

	/*����� �������-������-��������� ������������ ������*/
	class CSimplexSearch : public CNelderMeadSearch
	{
	public:
		CSimplexSearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		inputParam	calcArgMin(Arg _initialPoint);
	};

	/*����� �����*/
	class CBoxingSearch : public CMultiDimensionalSearch
	{
	protected:
		bool m_flagExit;
	public:
		CBoxingSearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		inputParam	calcArgMin(Arg _initialPoint);
	};

	/*����� ������������ ��������*/
	class CCyclicMinminSearch : public CMultiDimensionalSearch
	{
	protected:
		bool m_flagExit;
	public:
		CCyclicMinminSearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		inputParam	calcArgMin(Arg _initialPoint);
	};

	/*����� ���������� ������ (Random Search)*/
	class CRandomSearch : public CMultiDimensionalSearch
	{
	protected:
		bool		m_flagExit;
		double		rangedRand(const double& _rangeMin, const double& _rangeMax) const;
	public:
		CRandomSearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		inputParam	calcArgMin(Arg _initialPoint);
	};

	/*����� ����� � pi*/
	class CWeilPISearch : public CMultiDimensionalSearch
	{
	protected:
		bool		m_flagExit;
		double		getRem(const double& _value) const;
	public:
		CWeilPISearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		inputParam	calcArgMin(Arg _initialPoint);
	};

	/*����� ����� � e*/
	class CWeilESearch : public CMultiDimensionalSearch
	{
	protected:
		bool		m_flagExit;
		double		getRem(const double& _value) const;
	public:
		CWeilESearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		inputParam	calcArgMin(Arg _initialPoint);
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif