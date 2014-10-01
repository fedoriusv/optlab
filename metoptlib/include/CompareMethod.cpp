#include "CompareMethod.h"
#include "Func.h"
#include "CompareData.h"

using namespace metopt;

//////////////////////////////////////////////////////////////////////////////////////////////////////

TYPE_METHOD getDimMethodByMethodType(const NAME_METHOD _name)
{
	switch (_name)
	{
		/*One Dimensional*/
		case NAME_METHOD_SVEN:
		case NAME_METHOD_ADAPTATION_STEP:
		case NAME_METHOD_UNIFORM:
		case NAME_METHOD_DIVISION:
		case NAME_METHOD_DICHOTOMY:
		case NAME_METHOD_FIBONACCI:
		case NAME_METHOD_GOLDEN_SECTION:
		case NAME_METHOD_QUADRATIC_INTERPOLATION:
		case NAME_METHOD_CUBIC_INTERPOLATION:
		{
			return TYPE_ONE_DIMENSIONAL;
		}

			/*Multi Dimensional*/
		case NAME_METHOD_HOOKE_JEEVES:
		case NAME_METHOD_NELDER_MEAD:
		case NAME_METHOD_SIMPLEX_METHOD:
		case NAME_METHOD_BOX:
		case NAME_METHOD_CYCLIC_MINMIN:
		case NAME_METHOD_GAUSS_SEIDEL:
		case NAME_METHOD_POWELL_SEARCH:
		case NAME_METHOD_RANDOM_SEARCH:
		case NAME_METHOD_WEIL_PI_SEARCH:
		case NAME_METHOD_WEIL_E_SEARCH:
		case NAME_METHOD_FASTEST_DESCENT:
		case NAME_METHOD_FLETCHER_REEVES:
		case NAME_METHOD_POLAK_RIBIERE:
		case NAME_METHOD_DFP_SEARCH:
		case NAME_METHOD_NEWTON_SEARCH:
		case NAME_METHOD_NEWTON_RAPHSON:
		case NAME_METHOD_BIN_GENETIC_ALGORITHM:
		case NAME_METHOD_CON_GENETIC_ALGORITHM:
		{
			return TYPE_MULTI_DIMENSIONAL;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

CCompareMethods::CCompareMethods(CFunc* _func)
: m_func(_func)
, m_comData(NULL)
, m_precision(0.01)
, m_step(0.1)
, m_maxIteration(100)
, m_maxFuncCalc(100)
, m_maxTime(10000)
, m_flagExit(TYPE_EXIT_PRECISION_FUNC)
{
}

CCompareMethods::~CCompareMethods()
{
}

void CCompareMethods::pushMethod(NAME_METHOD _method)
{
	m_methodList.push_back(_method);
}

bool CCompareMethods::removeMethod(NAME_METHOD _method)
{
	std::vector<NAME_METHOD>::iterator iter = std::remove(m_methodList.begin(), m_methodList.end(), _method);

	return (iter != m_methodList.end()) ? true : false;
}

void CCompareMethods::clearList()
{
	m_methodList.clear();
}

CFunc*	CCompareMethods::getFunc() const
{
	return m_func;
}

CCompareData* CCompareMethods::getCompareData() const
{
	return m_comData;
}

void CCompareMethods::setPrecision(const double _precision)
{
	m_precision = _precision;
}

void CCompareMethods::setStep(const double _step)
{
	m_step = _step;
}

void CCompareMethods::setParam(const uInt _maxIteration, const uInt	 _maxFuncCalc, const uInt _maxTime)
{
	m_maxIteration = _maxIteration;
	m_maxFuncCalc = _maxFuncCalc;
	m_maxTime = _maxTime;
}

void CCompareMethods::setFlagExit(TEP_FLAG _flagExit)
{
	m_flagExit = _flagExit;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

CCompareSingleMethods::CCompareSingleMethods(CFunc* _func)
: CCompareMethods(_func)
{
}

CCompareSingleMethods::~CCompareSingleMethods()
{
}

void CCompareSingleMethods::calcMethods(const metopt::Arg& _initPoint)
{
	if (m_comData)
	{
		delete m_comData;
		m_comData = NULL;
	} 
	m_comData = new CCompareSingleData();

	for (std::vector<NAME_METHOD>::iterator iter = m_methodList.begin(); iter < m_methodList.end(); ++iter)
	{
		NAME_METHOD methodName = (*iter);

		if (getDimMethodByMethodType(methodName) != TYPE_ONE_DIMENSIONAL)
		{
			continue;
		}

		m_func->setMethod(methodName);

		m_func->setPrecision(m_precision);
		m_func->setStep(m_step);
		m_func->setParam(m_maxIteration, m_maxFuncCalc, m_maxTime);
		m_func->setFlagExit(m_flagExit);

		m_func->calcArgMin(_initPoint);
		metopt::CDataOneDimensional* data = m_func->getData();
		
		data->printToFile("methodCp.log");
		m_comData->pushData(data);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

CCompareMultiMethods::CCompareMultiMethods(CFunc* _func)
: CCompareMethods(_func)
, m_OnePrecision(0.01)
{
}

CCompareMultiMethods::~CCompareMultiMethods()
{
}

void CCompareMultiMethods::setOneDimensionalMethod(NAME_METHOD _nameMethod)
{
	m_nameOneMethod = _nameMethod;
}

void CCompareMultiMethods::setOneDimensionalPrecision(const double _precision)
{
	m_OnePrecision = _precision;
}

void CCompareMultiMethods::setInterval(const Arg& _A, const Arg& _B)
{
	m_interval.m_pointA = _A;
	m_interval.m_pointB = _B;
}

void CCompareMultiMethods::calcMethods(const metopt::Arg& _initPoint)
{
	if (m_comData)
	{
		delete m_comData;
		m_comData = NULL;
	}
	m_comData = new CCompareMultiData();

	for (std::vector<NAME_METHOD>::iterator iter = m_methodList.begin(); iter < m_methodList.end(); ++iter)
	{
		NAME_METHOD methodName = (*iter);

		if (getDimMethodByMethodType(methodName) != TYPE_MULTI_DIMENSIONAL)
		{
			continue;
		}

		m_func->setMethod(methodName);

		m_func->setPrecision(m_precision);
		m_func->setStep(m_step);
		m_func->setParam(m_maxIteration, m_maxFuncCalc, m_maxTime);
		m_func->setFlagExit(m_flagExit);

		m_func->setOneDimensionalMethod(m_nameOneMethod);
		m_func->setOneDimensionalPrecision(m_OnePrecision);

		m_func->getMultiFunc()->setInterval(m_interval.m_pointA, m_interval.m_pointB);
		
		m_func->calcArgMin(_initPoint);
		metopt::CDataMultiDimensional* data = m_func->getMultiData();

		data->printToFile("methodCp.log");
		m_comData->pushData(data);
	}
}