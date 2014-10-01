#include "CompareData.h"
#include "Data.h"

using namespace metopt;

CCompareData::CCompareData()
{
}

CCompareData::~CCompareData()
{
}

void CCompareData::pushData(CData* _data)
{
	m_dataList.push_back(_data);
}

int CCompareData::getSize() const
{
	return m_dataList.size();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CCompareSingleData::CCompareSingleData()
{
}

CCompareSingleData::~CCompareSingleData()
{
}

int* CCompareSingleData::getCountIterationArray() const
{
	int* items = new int[m_dataList.size()];
	
	int index = 0;
	for (std::vector<CData*>::const_iterator iter = m_dataList.begin(); iter < m_dataList.end(); ++iter)
	{
		CDataOneDimensional* data = static_cast<CDataOneDimensional*>(*iter);

		items[index] = data->getCountIteration();
		++index;
	}

	return items;
}

int* CCompareSingleData::getCountCalcArray() const
{
	int* items = new int[m_dataList.size()];

	int index = 0;
	for (std::vector<CData*>::const_iterator iter = m_dataList.begin(); iter < m_dataList.end(); ++iter)
	{
		CDataOneDimensional* data = static_cast<CDataOneDimensional*>(*iter);

		items[index] = data->getCountCalc();
		++index;
	}

	return items;
}

double* CCompareSingleData::getElapsedTimeArray() const
{
	double* items = new double[m_dataList.size()];

	int index = 0;
	for (std::vector<CData*>::const_iterator iter = m_dataList.begin(); iter < m_dataList.end(); ++iter)
	{
		CDataOneDimensional* data = static_cast<CDataOneDimensional*>(*iter);

		items[index] = data->getElapsedTime();
		++index;
	}

	return items;
}

double* CCompareSingleData::getPrecisionFuncArray() const
{
	double* items = new double[m_dataList.size()];

	int index = 0;
	for (std::vector<CData*>::const_iterator iter = m_dataList.begin(); iter < m_dataList.end(); ++iter)
	{
		CDataOneDimensional* data = static_cast<CDataOneDimensional*>(*iter);

		items[index] = data->getSearchPoint().c.fx;
		++index;
	}

	return items;
}

double* CCompareSingleData::getPrecisionArgArray() const
{
	double* items = new double[m_dataList.size()];

	int index = 0;
	for (std::vector<CData*>::const_iterator iter = m_dataList.begin(); iter < m_dataList.end(); ++iter)
	{
		CDataOneDimensional* data = static_cast<CDataOneDimensional*>(*iter);

		items[index] = data->getSearchPoint().c.x;
		++index;
	}

	return items;
}

void CCompareSingleData::printToFile(cpChar _nameFile)
{
	m_pNameFile = _nameFile;

	m_file = fopen(m_pNameFile, "w+");
	fprintf(m_file, "Compare Methods.");
	fprintf(m_file, "   Func : ");
	fprintf(m_file, "%s", m_dataList[0]->m_pFuncName);
	fprintf(m_file, "\n\nH = %f, Tol = %f, Nfm = %i, Nim = %i, Tm = %.3f\n", 
		m_dataList[0]->m_step, m_dataList[0]->m_precision, m_dataList[0]->m_maxFunc, m_dataList[0]->m_maxIteration, (double)m_dataList[0]->m_maxTime / 1000.0f);
	fprintf(m_file, "---------------------------------------------------------------------------------------------------------------\n");
	fprintf(m_file, " Name Method                               Ni     Nb     Nf      Tm                       F1               x1\n");
	fprintf(m_file, "---------------------------------------------------------------------------------------------------------------\n");

	for (std::vector<CData*>::iterator iter = m_dataList.begin(); iter < m_dataList.end(); ++iter)
	{
		CDataOneDimensional* data = static_cast<CDataOneDimensional*>(*iter);

		std::string name(data->m_pMethodName);
		int end = name.size();
		name.resize(40);
		std::fill(name.begin() + end, name.end(), ' ');

		int coutIter = data->getCountIteration();
		int coutCalc = data->getCountCalc();
		int cbest = data->getCountBest();
		double coutTime = data->getElapsedTime();
		

		double value = data->getSearchPoint().c.fx;
		double arg = data->getSearchPoint().c.x;

		fprintf(m_file, "%s", name.c_str());
		fprintf(m_file, " %2i    %2i    %2i      %8.5f     %.12e    %.12e\n", coutIter, cbest, coutCalc, coutTime, value, arg);
	}

	fprintf(m_file, "-------------------------------------------------------------------------------------------------------------\n");
	fclose(m_file);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CCompareMultiData::CCompareMultiData()
{
}

CCompareMultiData::~CCompareMultiData()
{
}

int* CCompareMultiData::getCountIterationArray() const
{
	int* items = new int[m_dataList.size()];

	int index = 0;
	for (std::vector<CData*>::const_iterator iter = m_dataList.begin(); iter < m_dataList.end(); ++iter)
	{
		CDataMultiDimensional* data = static_cast<CDataMultiDimensional*>(*iter);

		items[index] = data->getCountIteration();
		++index;
	}

	return items;
}

int* CCompareMultiData::getCountCalcArray() const
{
	int* items = new int[m_dataList.size()];

	int index = 0;
	for (std::vector<CData*>::const_iterator iter = m_dataList.begin(); iter < m_dataList.end(); ++iter)
	{
		CDataMultiDimensional* data = static_cast<CDataMultiDimensional*>(*iter);

		items[index] = data->getCountCalc();
		++index;
	}

	return items;
}

double* CCompareMultiData::getElapsedTimeArray() const
{
	double* items = new double[m_dataList.size()];

	int index = 0;
	for (std::vector<CData*>::const_iterator iter = m_dataList.begin(); iter < m_dataList.end(); ++iter)
	{
		CDataMultiDimensional* data = static_cast<CDataMultiDimensional*>(*iter);

		items[index] = data->getElapsedTime();
		++index;
	}

	return items;
}

double* CCompareMultiData::getPrecisionFuncArray() const
{
	double* items = new double[m_dataList.size()];

	int index = 0;
	for (std::vector<CData*>::const_iterator iter = m_dataList.begin(); iter < m_dataList.end(); ++iter)
	{
		CDataMultiDimensional* data = static_cast<CDataMultiDimensional*>(*iter);

		items[index] = data->getSearchPoint().fx;
		++index;
	}

	return items;
}

double* CCompareMultiData::getPrecisionArgArray() const
{
	double* items = new double[m_dataList.size()];

	int index = 0;
	for (std::vector<CData*>::const_iterator iter = m_dataList.begin(); iter < m_dataList.end(); ++iter)
	{
		CDataMultiDimensional* data = static_cast<CDataMultiDimensional*>(*iter);

		items[index] = data->getSearchPoint().x[0];
		++index;
	}

	return items;
}

void CCompareMultiData::printToFile(cpChar _nameFile)
{
	m_pNameFile = _nameFile;

	m_file = fopen(m_pNameFile, "w+");
	fprintf(m_file, "Compare Methods.");
	fprintf(m_file, "   Func : ");
	fprintf(m_file, "%s", m_dataList[0]->m_pFuncName);
	fprintf(m_file, "\n\nH = %f, Tol = %f, Nfm = %i, Nim = %i, Tm = %.3f\n",
		m_dataList[0]->m_step, m_dataList[0]->m_precision, m_dataList[0]->m_maxFunc, m_dataList[0]->m_maxIteration, (double)m_dataList[0]->m_maxTime / 1000.0f);
	fprintf(m_file, "------------------------------------------------------------------------------------------------------------------------------------\n");
	fprintf(m_file, " Name Method               Ni    Nb     Nf      Tm               F1               x1                  x2\n");
	fprintf(m_file, "------------------------------------------------------------------------------------------------------------------------------------\n");

	for (std::vector<CData*>::iterator iter = m_dataList.begin(); iter < m_dataList.end(); ++iter)
	{
		CDataMultiDimensional* data = static_cast<CDataMultiDimensional*>(*iter);

		std::string name(data->m_pMethodName);
		int end = name.size();
		name.resize(28);
		std::fill(name.begin() + end, name.end(), ' ');

		int coutIter = data->getCountIteration();
		int coutCalc = data->getCountCalc();
		int countBest = data->getCountBest();
		double coutTime = data->getElapsedTime();

		double value = data->getSearchPoint().fx;
		double arg0 = data->getSearchPoint().x[0];
		double arg1 = data->getSearchPoint().x[1];

		fprintf(m_file, "%s", name.c_str());
		fprintf(m_file, " %2i    %2i    %2i     %8.5f",
			coutIter, countBest, coutCalc, coutTime);
		fprintf(m_file, "     %.12e     %.12e     %.12e\n", value, arg0, arg1);
	}

	fprintf(m_file, "-----------------------------------------------------------------------------------------------------------------------------\n");
	fclose(m_file);
}