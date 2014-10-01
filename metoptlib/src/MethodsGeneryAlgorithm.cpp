#include "MethodsGeneryAlgorithm.h"
#include <time.h>

using namespace metopt;

/*Бинарный генетический алгоритм*/
CBinaryGenAlgorithmSearch::CBinaryGenAlgorithmSearch(CFuncionMultiDimensional* _func, double _step, double _precision)
:
m_flagExit(false)
{
	m_nameMethod = NAME_METHOD_BIN_GENETIC_ALGORITHM;
	m_precision = _precision;
	m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

inputParam CBinaryGenAlgorithmSearch::calcArgMin(Arg _initialPoint)
{
	m_dimensions = _initialPoint.getSize();

	saveHeadData(" Binary Genetic Algorithm ");
	m_time->start();

	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint(_initialPoint.getPointer(), true);
	m_outputParam = m_inputParam;

	Arg c = m_func->getInterval().m_pointB - m_func->getInterval().m_pointA;

	////////////////////////////////
	int popsize = 8 * m_dimensions;
	int nbits = 32;
	float selection = 0.5f;
	float mutrate = 0.1f;
	////////////////////////////////

	int Nt = nbits * m_dimensions;

	float keep = floor(selection * popsize);
	float M = ceil((popsize - keep) / 2);
	int nM = (int)M;
	float nmut = ceil((popsize - 1)* Nt * mutrate);

	//New Population
	Arg* pop = new Arg[Nt];
	for (int i = 0; i < Nt; ++i)
	{
		pop[i].setFillIn(0, popsize);
		for (int j = 0; j < popsize; ++j)
		{
			pop[i][j] = rangedRand(0, 1);
		}
	}

	const Arg* par = binDecode(pop, Nt, c, nbits);
	m_state = "begin population";

	inputParam x;
	std::vector<inputParam> xarray;
	for (int i = 0; i < popsize; ++i)
	{
		x.x = getPoint(par, i);
		x.fx = newPoint(x.x.getPointer(), false);
		x.ind = i;
		if (isEndMethod())
		{
			m_flagExit = true;
			m_outputParam = x;
			break;
		}
		xarray.push_back(x);
	}

	if (!m_flagExit)
	{
		//Sort Population
		std::sort(xarray.begin(), xarray.end(), metopt::inputParam::sortByFunc);
		Arg* sortedPop = sortPopulation(pop, Nt, xarray);

		delete[] pop;
		pop = sortedPop;

		m_step = getStep(par, Nt / nbits);

		//Итерационный цикл
		while (1)
		{
			m_countIteration++;

			//Селекция родителей
			//-----------------------------------------------------------------------------//

			//веса хромосом
			Arg prob((int)keep);
			int sumKeep = 0;
			for (int i = 0; i < keep; ++i)
			{
				sumKeep += (i + 1);
			}
			for (int i = 0; i < keep; ++i)
			{
				prob[i] = (keep - i) / sumKeep;
			}

			//колесо рулетки
			Arg odds((int)(keep + 1));
			odds[0] = 0;
			for (int i = 1; i < keep + 1; ++i)
			{
				odds[i] = odds[i - 1] + prob[i - 1];
			}

			//массив первых родителей
			Arg pick1(nM);
			pick1.setRendom(0, 1);
			//массив вторых родителей
			Arg pick2(nM);
			pick2.setRendom(0, 1);

			Arg ma(nM);
			Arg pa(nM);

			int ic = 0;
			while (ic < nM)
			{
				for (int i = 1; i < keep + 1; ++i)
				{
					if ((pick1[ic] <= odds[i]) && (pick1[ic] > odds[i - 1]))
					{
						ma[ic] = i - 1;
					}
					if ((pick2[ic] <= odds[i]) && (pick2[ic] > odds[i - 1]))
					{
						pa[ic] = i - 1;
					}
				}
				++ic;
			}

			//Скрещивание с использованием одноточечного кроссовера
			//--------------------------------------------------------------------------------//

			//индекс первого родителя
			Arg ix(nM);
			for (int i = 0; i < nM; ++i)
			{
				ix[i] = 1 + 2 * i;
			}

			//точки кроссовера
			Arg xp(nM);
			for (int i = 0; i < nM; ++i)
			{
				xp[i] = ceil(rangedRand(0, 1)* Nt - 1);
			}

			//первый потомок
			for (int i = 0; i < nM; ++i)
			{
				int index = (int)keep + (int)ix[i];
				for (int j = 0; j < xp[0]; ++j)
				{
					for (int k = 0; k < M; ++k)
					{
						pop[j][index] = pop[j][(int)ma[k]];
					}
				}
				for (int j = (int)xp[0]; j < Nt; ++j)
				{
					for (int k = 0; k < M; ++k)
					{
						pop[j][index] = pop[j][(int)pa[k]];
					}
				}
			}

			//второй потомок
			for (int i = 0; i < nM; ++i)
			{
				int index = (int)keep + (int)ix[i] + 1;
				for (int j = 0; j < xp[0]; ++j)
				{
					for (int k = 0; k < M; ++k)
					{
						pop[j][index] = pop[j][(int)pa[k]];
					}
				}
				for (int j = (int)xp[0]; j < Nt; ++j)
				{
					for (int k = 0; k < M; ++k)
					{
						pop[j][index] = pop[j][(int)ma[k]];
					}
				}
			}

			//Мутация
			//-------------------------------------------------------------------------------//

			//номера строк, столбцов мутаций
			Arg mrow((int)nmut);
			Arg mcol((int)nmut);
			for (int i = 0; i < (int)nmut; ++i)
			{
				mrow[i] = ceil(rangedRand(0, 1) * (popsize - 1)) + 1;
				mcol[i] = ceil(rangedRand(0, 1) * Nt);
			}

			//переключение битов
			for (int i = 0; i < nmut; ++i)
			{
				int indexRow = (int)mrow[i];
				int indexCol = (int)mcol[i];
				pop[indexRow][indexCol] = abs(pop[indexRow][indexCol] - 1);
			}

			//Перевычисление популяции
			//-------------------------------------------------------------------------------//

			//декодирование
			par = binDecode(pop, Nt, c, nbits);
			m_state = "new population";

			xarray.clear();
			for (int i = 0; i < popsize; ++i)
			{
				x.x = getPoint(par, i);
				x.fx = newPoint(x.x.getPointer(), false);
				x.ind = i;
				if (isEndMethod())
				{
					m_flagExit = true;
					m_outputParam = x;
					break;
				}
				xarray.push_back(x);
			}

			m_step = getStep(par, Nt / nbits);

			if (m_flagExit)
			{
				std::sort(xarray.begin(), xarray.end(), metopt::inputParam::sortByFunc);
				m_outputParam = xarray[0];

				break;
			}
			
			//Сортировка особей популяции
			//-------------------------------------------------------------------------------//
			std::sort(xarray.begin(), xarray.end(), metopt::inputParam::sortByFunc);
			Arg* sortedPop = sortPopulation(pop, Nt, xarray);

			delete[] pop;
			pop = sortedPop;
		}
	}

	m_time->stop();
	m_state = "end";
	saveFootData();

	return m_outputParam;
}

const Arg* CBinaryGenAlgorithmSearch::binDecode(const Arg* _binMatrix, int _nElements, const Arg& _point, int _bits)
{
	int npar = _nElements / _bits;

	Arg quant(_bits);
	for (int i = 0; i < _bits; ++i)
	{
		double value = pow(0.5, i);
		quant[i] = value;
	}

	double sum = quant.getSum();
	quant = quant / sum;

	Arg* out = reshape(_binMatrix, _nElements, _bits, npar * _binMatrix->getSize());

	Arg par = matrixProduct(out, quant);
	Arg* outpar = reshape(par, 1, npar, _binMatrix->getSize());

	for (uInt i = 0; i < _binMatrix->getSize(); ++i)
	{
		outpar[0][i] = outpar[0][i] * _point[0] + m_func->getInterval().m_pointA[0];
		outpar[1][i] = outpar[1][i] * _point[1] + m_func->getInterval().m_pointA[1];
	}

	return outpar;
}

double CBinaryGenAlgorithmSearch::rangedRand(const double& _rangeMin, const double& _rangeMax) const
{
	srand(time(NULL));
	double u = (double)rand() / (RAND_MAX + 1) * (_rangeMax - _rangeMin)
		+ _rangeMin;

	return u;
}

Arg* CBinaryGenAlgorithmSearch::reshape(const Arg* _inputMatrix, int size, int _col, int _row)
{
	Arg* outputMatrix = new Arg[_col];

	for (int i = 0; i < _col; ++i)
	{
		outputMatrix[i].setFillIn(0, _row);
		for (int j = 0; j < _row / 2; ++j)
		{
			outputMatrix[i][j] = _inputMatrix[i][j];
			outputMatrix[i][_row / 2 + j] = _inputMatrix[i + 1][j];
		}
	}

	return outputMatrix;
}

Arg* CBinaryGenAlgorithmSearch::reshape(const Arg& _inputVector, int size, int _col, int _row)
{
	Arg* outputMatrix = new Arg[_col];

	int index = 0;
	for (int j = 0; j < _col; ++j)
	{
		outputMatrix[j].setFillIn(0, _row);

		for (int i = 0; i < _row; ++i)
		{
			outputMatrix[j][i] = _inputVector[index];
			++index;
		}
	}

	return outputMatrix;
}

Arg CBinaryGenAlgorithmSearch::matrixProduct(const Arg* _matrix, const Arg& _vector) const
{
	Arg result;
	result.setFillIn(0, _vector.getSize());
	for (uInt i = 0; i < _vector.getSize(); ++i)
	{
		for (uInt j = 0; j < _vector.getSize(); ++j)
		{
			result[i] += _matrix[j].x[i] * _vector.x[j];
		}
	}
	return result;
}

Arg CBinaryGenAlgorithmSearch::getPoint(const Arg* _matrix, uInt index) const
{
	Arg cx(m_dimensions);
	for (uInt j = 0; j < m_dimensions; ++j)
	{
		cx[j] = _matrix[j][index];
	}

	return cx;
}

Arg* CBinaryGenAlgorithmSearch::sortPopulation(const Arg* _matrix, int _size, const std::vector<inputParam>& _array)
{
	Arg* pop = new Arg[_size];
	for (int i = 0; i < _size; ++i)
	{
		pop[i].setFillIn(0, _matrix->getSize());
	}

	for (uInt i = 0; i < _matrix->getSize(); ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			pop[i][j] = _matrix[_array[i].ind][j];
		}
	}

	return pop;
}

double CBinaryGenAlgorithmSearch::getStep(const Arg* _par, int _size)
{
	Arg* tempMatrix = new Arg[_size];
	for (int i = 0; i < _size; ++i)
	{
		tempMatrix[i].setFillIn(0, _par->getSize());
	}

	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _par->getSize(); ++j)
		{
			tempMatrix[i][j] = abs(_par[i][j] - _par[i][0]);
		}
	}

	Arg max(_size);
	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _par->getSize(); ++j)
		{
			if (max[i] < tempMatrix[i][j])
			{
				max[i] = tempMatrix[i][j];
			}
		}
	}

	double maxValue = max.getMax();

	return maxValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CConGeneticAlgorithmSearch::CConGeneticAlgorithmSearch(CFuncionMultiDimensional* _func, double _step, double _precision)
:
m_flagExit(false)
{
	m_nameMethod = NAME_METHOD_CON_GENETIC_ALGORITHM;
	m_precision = _precision;
	m_step = _step;
	m_func = _func;
	m_function = _func->getFunction();
	m_optPoint = _func->getOptPoint();
}

inputParam CConGeneticAlgorithmSearch::calcArgMin(Arg _initialPoint)
{
	m_dimensions = _initialPoint.getSize();

	saveHeadData(" Binary Genetic Algorithm ");
	m_time->start();

	m_state = "begin";
	m_inputParam.x = _initialPoint;
	m_inputParam.fx = newPoint(_initialPoint.getPointer(), true);
	m_outputParam = m_inputParam;

	Arg c = m_func->getInterval().m_pointB - m_func->getInterval().m_pointA;

	////////////////////////////////
	int popsize = 8 * m_dimensions;
	int nbits = 32;
	float selection = 0.5f;
	float mutrate = 0.1f;
	////////////////////////////////

	int Nt = nbits * m_dimensions;

	float keep = floor(selection * popsize);
	float M = ceil((popsize - keep) / 2);
	int nM = (int)M;
	float nmut = ceil((popsize - 1)* Nt * mutrate);

	//New Population
	Arg* pop = new Arg[Nt];
	for (int i = 0; i < Nt; ++i)
	{
		pop[i].setFillIn(0, popsize);
		for (int j = 0; j < popsize; ++j)
		{
			pop[i][j] = rangedRand(0, 1);
		}
	}

	const Arg* par = cross(pop, Nt, c, nbits);
	m_state = "begin population";

	inputParam x;
	std::vector<inputParam> xarray;
	for (int i = 0; i < popsize; ++i)
	{
		x.x = getPoint(par, i);
		x.fx = newPoint(x.x.getPointer(), false);
		x.ind = i;
		if (isEndMethod())
		{
			m_flagExit = true;
			m_outputParam = x;
			break;
		}
		xarray.push_back(x);
	}

	if (!m_flagExit)
	{
		//Sort Population
		std::sort(xarray.begin(), xarray.end(), metopt::inputParam::sortByFunc);
		Arg* sortedPop = sortPopulation(pop, Nt, xarray);

		delete[] pop;
		pop = sortedPop;

		m_step = getStep(par, Nt / nbits);

		//Итерационный цикл
		while (1)
		{
			m_countIteration++;

			//Селекция родителей
			//-----------------------------------------------------------------------------//

			//веса хромосом
			Arg prob((int)keep);
			int sumKeep = 0;
			for (int i = 0; i < keep; ++i)
			{
				sumKeep += (i + 1);
			}
			for (int i = 0; i < keep; ++i)
			{
				prob[i] = (keep - i) / sumKeep;
			}

			//колесо рулетки
			Arg odds((int)(keep + 1));
			odds[0] = 0;
			for (int i = 1; i < keep + 1; ++i)
			{
				odds[i] = odds[i - 1] + prob[i - 1];
			}

			//массив первых родителей
			Arg pick1(nM);
			pick1.setRendom(0, 1);
			//массив вторых родителей
			Arg pick2(nM);
			pick2.setRendom(0, 1);

			Arg ma(nM);
			Arg pa(nM);

			int ic = 0;
			while (ic < nM)
			{
				for (int i = 1; i < keep + 1; ++i)
				{
					if ((pick1[ic] <= odds[i]) && (pick1[ic] > odds[i - 1]))
					{
						ma[ic] = i - 1;
					}
					if ((pick2[ic] <= odds[i]) && (pick2[ic] > odds[i - 1]))
					{
						pa[ic] = i - 1;
					}
				}
				++ic;
			}

			//Скрещивание с использованием одноточечного кроссовера
			//--------------------------------------------------------------------------------//

			//индекс первого родителя
			Arg ix(nM);
			for (int i = 0; i < nM; ++i)
			{
				ix[i] = 1 + 2 * i;
			}

			//точки кроссовера
			Arg xp(nM);
			for (int i = 0; i < nM; ++i)
			{
				xp[i] = ceil(rangedRand(0, 1)* Nt - 1);
			}

			//первый потомок
			for (int i = 0; i < nM; ++i)
			{
				int index = (int)keep + (int)ix[i];
				for (int j = 0; j < xp[0]; ++j)
				{
					for (int k = 0; k < M; ++k)
					{
						pop[j][index] = pop[j][(int)ma[k]];
					}
				}
				for (int j = (int)xp[0]; j < Nt; ++j)
				{
					for (int k = 0; k < M; ++k)
					{
						pop[j][index] = pop[j][(int)pa[k]];
					}
				}
			}

			//второй потомок
			for (int i = 0; i < nM; ++i)
			{
				int index = (int)keep + (int)ix[i] + 1;
				for (int j = 0; j < xp[0]; ++j)
				{
					for (int k = 0; k < M; ++k)
					{
						pop[j][index] = pop[j][(int)pa[k]];
					}
				}
				for (int j = (int)xp[0]; j < Nt; ++j)
				{
					for (int k = 0; k < M; ++k)
					{
						pop[j][index] = pop[j][(int)ma[k]];
					}
				}
			}

			//Мутация
			//-------------------------------------------------------------------------------//

			//номера строк, столбцов мутаций
			Arg mrow((int)nmut);
			Arg mcol((int)nmut);
			for (int i = 0; i < (int)nmut; ++i)
			{
				mrow[i] = ceil(rangedRand(0, 1) * (popsize - 1)) + 1;
				mcol[i] = ceil(rangedRand(0, 1) * Nt);
			}

			//переключение битов
			for (int i = 0; i < nmut; ++i)
			{
				int indexRow = (int)mrow[i];
				int indexCol = (int)mcol[i];
				pop[indexRow][indexCol] = abs(pop[indexRow][indexCol] - 1);
			}

			//Перевычисление популяции
			//-------------------------------------------------------------------------------//
			par = cross(pop, Nt, c, nbits);
			m_state = "new population";

			xarray.clear();
			for (int i = 0; i < popsize; ++i)
			{
				x.x = getPoint(par, i);
				x.fx = newPoint(x.x.getPointer(), false);
				x.ind = i;
				if (isEndMethod())
				{
					m_flagExit = true;
					m_outputParam = x;
					break;
				}
				xarray.push_back(x);
			}

			m_step = getStep(par, Nt / nbits);

			if (m_flagExit)
			{
				std::sort(xarray.begin(), xarray.end(), metopt::inputParam::sortByFunc);
				m_outputParam = xarray[0];

				break;
			}

			//Сортировка особей популяции
			//-------------------------------------------------------------------------------//
			std::sort(xarray.begin(), xarray.end(), metopt::inputParam::sortByFunc);
			Arg* sortedPop = sortPopulation(pop, Nt, xarray);

			delete[] pop;
			pop = sortedPop;
		}
	}

	m_time->stop();
	m_state = "end";
	saveFootData();

	return m_outputParam;
}

const Arg* CConGeneticAlgorithmSearch::cross(const Arg* _binMatrix, int _nElements, const Arg& _point, int _bits)
{
	int npar = _nElements / _bits;

	Arg quant(_bits);
	for (int i = 0; i < _bits; ++i)
	{
		double value = pow(0.5, i);
		quant[i] = value;
	}

	double sum = quant.getSum();
	quant = quant / sum;

	Arg* out = reshape(_binMatrix, _nElements, _bits, npar * _binMatrix->getSize());

	Arg par = matrixProduct(out, quant);
	Arg* outpar = reshape(par, 1, npar, _binMatrix->getSize());

	for (uInt i = 0; i < _binMatrix->getSize(); ++i)
	{
		outpar[0][i] = outpar[0][i] * _point[0] + m_func->getInterval().m_pointA[0];
		outpar[1][i] = outpar[1][i] * _point[1] + m_func->getInterval().m_pointA[1];
	}

	return outpar;
}

double CConGeneticAlgorithmSearch::rangedRand(const double& _rangeMin, const double& _rangeMax) const
{
	srand(time(NULL));
	double u = (double)rand() / (RAND_MAX + 1) * (_rangeMax - _rangeMin)
		+ _rangeMin;

	return u;
}

Arg* CConGeneticAlgorithmSearch::reshape(const Arg* _inputMatrix, int size, int _col, int _row)
{
	Arg* outputMatrix = new Arg[_col];

	for (int i = 0; i < _col; ++i)
	{
		outputMatrix[i].setFillIn(0, _row);
		for (int j = 0; j < _row / 2; ++j)
		{
			outputMatrix[i][j] = _inputMatrix[i][j];
			outputMatrix[i][_row / 2 + j] = _inputMatrix[i + 1][j];
		}
	}

	return outputMatrix;
}

Arg* CConGeneticAlgorithmSearch::reshape(const Arg& _inputVector, int size, int _col, int _row)
{
	Arg* outputMatrix = new Arg[_col];

	int index = 0;
	for (int j = 0; j < _col; ++j)
	{
		outputMatrix[j].setFillIn(0, _row);

		for (int i = 0; i < _row; ++i)
		{
			outputMatrix[j][i] = _inputVector[index];
			++index;
		}
	}

	return outputMatrix;
}

Arg CConGeneticAlgorithmSearch::matrixProduct(const Arg* _matrix, const Arg& _vector) const
{
	Arg result;
	result.setFillIn(0, _vector.getSize());
	for (uInt i = 0; i < _vector.getSize(); ++i)
	{
		for (uInt j = 0; j < _vector.getSize(); ++j)
		{
			result[i] += _matrix[j].x[i] * _vector.x[j];
		}
	}
	return result;
}

Arg CConGeneticAlgorithmSearch::getPoint(const Arg* _matrix, uInt index) const
{
	Arg cx(m_dimensions);
	for (uInt j = 0; j < m_dimensions; ++j)
	{
		cx[j] = _matrix[j][index];
	}

	return cx;
}

Arg* CConGeneticAlgorithmSearch::sortPopulation(const Arg* _matrix, int _size, const std::vector<inputParam>& _array)
{
	Arg* pop = new Arg[_size];
	for (int i = 0; i < _size; ++i)
	{
		pop[i].setFillIn(0, _matrix->getSize());
	}

	for (uInt i = 0; i < _matrix->getSize(); ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			pop[i][j] = _matrix[_array[i].ind][j];
		}
	}

	return pop;
}

double CConGeneticAlgorithmSearch::getStep(const Arg* _par, int _size)
{
	Arg* tempMatrix = new Arg[_size];
	for (int i = 0; i < _size; ++i)
	{
		tempMatrix[i].setFillIn(0, _par->getSize());
	}

	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _par->getSize(); ++j)
		{
			tempMatrix[i][j] = abs(_par[i][j] - _par[i][0]);
		}
	}

	Arg max(_size);
	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _par->getSize(); ++j)
		{
			if (max[i] < tempMatrix[i][j])
			{
				max[i] = tempMatrix[i][j];
			}
		}
	}

	double maxValue = max.getMax();

	return maxValue;
}

