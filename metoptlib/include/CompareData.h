#ifndef _COMPARE_DATA_H_
#define _COMPARE_DATA_H_

#include "Param.h"

namespace metopt
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	
	class CData;

	class CCompareData
	{
	protected:
		std::vector<CData*> m_dataList;
		cpChar				m_pNameFile;
		FILE*				m_file;

	public:
		CCompareData();
		virtual ~CCompareData();

		void pushData(CData* _data);
		int	 getSize() const;

		virtual int*	getCountIterationArray() const = 0;
		virtual int*	getCountCalcArray() const = 0;
		virtual double*	getElapsedTimeArray() const = 0;
		virtual double*	getPrecisionFuncArray() const = 0;
		virtual double*	getPrecisionArgArray() const = 0;
		virtual void printToFile(cpChar _nameFile) = 0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////

	class CCompareSingleData : public CCompareData
	{
	public:
		CCompareSingleData();
		virtual ~CCompareSingleData();
		virtual int*	getCountIterationArray() const;
		virtual int*	getCountCalcArray() const;
		virtual double*	getElapsedTimeArray() const;
		virtual double*	getPrecisionFuncArray() const;
		virtual double*	getPrecisionArgArray() const;
		virtual void	printToFile(cpChar _nameFile);
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////

	class CCompareMultiData : public CCompareData
	{

	public:
		CCompareMultiData();
		virtual ~CCompareMultiData();

		virtual int*	getCountIterationArray() const;
		virtual int*	getCountCalcArray() const;
		virtual double*	getElapsedTimeArray() const;
		virtual double*	getPrecisionFuncArray() const;
		virtual double*	getPrecisionArgArray() const;
		virtual void	printToFile(cpChar _nameFile);
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif