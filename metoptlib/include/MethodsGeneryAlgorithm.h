#ifndef _METHODS_GENERY_ALGORITHM_SEARCH_H_
#define _METHODS_GENERY_ALGORITHM_SEARCH_H_

#include "MultiDimensionalSearch.h"

namespace metopt
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*Бинарный генетический алгоритм*/
	class CBinaryGenAlgorithmSearch : public CMultiDimensionalSearch
	{
	protected:
		bool		m_flagExit;

		const Arg*	binDecode(const Arg* _binMatrix, int _nElements, const Arg& _point, int _bits);

		double		rangedRand(const double& _rangeMin, const double& _rangeMax) const;

		Arg*		reshape(const Arg* _inputMatrix, int size, int col, int row);
		Arg*		reshape(const Arg& _inputVector, int size, int _col, int _row);

		Arg			matrixProduct(const Arg* _matrix, const Arg& _vector) const;

		Arg			getPoint(const Arg* _matrix, uInt index) const;
		double		getStep(const Arg* _par, int _size);

		Arg*		sortPopulation(const Arg* _matrix, int _size, const std::vector<inputParam>& _array);

	public:
		CBinaryGenAlgorithmSearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		inputParam	calcArgMin(Arg _initialPoint);
	};

	/*Непрерывный генетический алгоритм*/
	class CConGeneticAlgorithmSearch : public CMultiDimensionalSearch
	{
	protected:
		bool		m_flagExit;

		const Arg*	cross(const Arg* _binMatrix, int _nElements, const Arg& _point, int _bits);

		double		rangedRand(const double& _rangeMin, const double& _rangeMax) const;
		Arg*		reshape(const Arg* _inputMatrix, int size, int col, int row);
		Arg*		reshape(const Arg& _inputVector, int size, int _col, int _row);
		Arg			matrixProduct(const Arg* _matrix, const Arg& _vector) const;
		Arg			getPoint(const Arg* _matrix, uInt index) const;
		double		getStep(const Arg* _par, int _size);

		Arg*		sortPopulation(const Arg* _matrix, int _size, const std::vector<inputParam>& _array);

	public:
		CConGeneticAlgorithmSearch(CFuncionMultiDimensional* _func, double _step = 2.0f / 3.0f, double _precision = 0.001f);
		inputParam	calcArgMin(Arg _initialPoint);
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif