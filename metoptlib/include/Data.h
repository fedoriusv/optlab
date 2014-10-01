#ifndef _DATA_H_
#define _DATA_H_

#include "Param.h"

namespace metopt
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	class CCompareSingleData;
	class CCompareMultiData;

	class CData
	{
	protected:

		friend						CCompareSingleData;
		friend						CCompareMultiData;
		FILE*						m_file;
		cpChar						m_pNameFile;

		TYPE_METHOD					m_typeMethod;

		uInt						m_maxIteration;
		uInt						m_maxFunc;

		TYPE_EXIT					m_typeExit;
		TEP_FLAG					m_exitFlag;
		NAME_METHOD					m_nameMethod;
		cpChar						m_pFuncName;
		cpChar						m_pMethodName;

		double						m_step;
		double						m_precision;

		uInt						m_time;
		uInt						m_maxTime;

		virtual void				printToFile(cpChar _nameFile) = 0;
		cpChar						getStringExit() const;
	public:
		CData();
		virtual ~CData();
	};

	///////////////////////////////////////////////////////////////////////////////////////////////

	class CDataOneDimensional : public CData
	{
	protected:
		friend class COneDimensionalSearch;

		inputParam2D				m_beginPoint;
		inputParam2D				m_optPoint;
		outputParam2D				m_finalPoint;

		arrayInt					m_funcIteration;
		arrayInt					m_funcBestPoint;
		arrayInt					m_funcCalc;
		arrayDouble					m_stepArray;
		arrayDouble					m_delta;
		std::vector< inputParam2D > m_points;
		std::vector< cpChar >		m_state;

		void						setInitData(const double&		_step,
			const double&		_precision,
			const inputParam2D& _beginPoint,
			const inputParam2D& _optPoint,
			const uInt&			_maxIteration,
			const uInt&			_maxFunc,
			const uInt&			_maxTime);

		void						setNewPointData(const uInt&		_funcIteration,
			const uInt&			_funcBestPoint,
			const uInt&			_funcCalc,
			const double&		_step,
			const double&		_delta,
			const inputParam2D& _point,
			const char*			_state);

		void						setEndMethodData(const TYPE_EXIT		_typeExit,
			const TYPE_EXIT_PRECISION_FLAG _exitFlag,
			const outputParam2D&	_finalPoint,
			const uInt&				_time,
			cpChar					_pFuncName,
			cpChar					_pMethodName);

	public:
		void						addCalcData(const CDataOneDimensional* _data);
		CDataOneDimensional();
		outputParam2D				getSearchPoint() const;
		inputParam2D				getInputPoint() const;

		double**					getPointsPointer() const;
		int							getCountPoints() const;
		virtual void				printToFile(cpChar _nameFile);
		virtual ~CDataOneDimensional();

		int							getCountIteration() const;
		int							getCountCalc() const;
		int							getCountBest() const;
		double						getElapsedTime() const;


	};

	///////////////////////////////////////////////////////////////////////////////////////////////

	class CDataMultiDimensional : public CData
	{
	protected:
		friend class CMultiDimensionalSearch;
		friend class CMultiDimensionalWithOneSearch;

		bool						m_usedOneDimMethod;
		cpChar						m_pOneDimMethodName;

		bool						m_usedGrad;
		Arg							m_grad;

		uInt						m_coutDimensions;

		inputParam					m_beginPoint;
		inputParam					m_optPoint;
		inputParam					m_finalPoint;

		arrayInt					m_funcIteration;
		arrayInt					m_funcBestPoint;
		arrayInt					m_funcCalc;
		std::vector< double >		m_stepArray;
		std::vector< double >		m_delta;
		std::vector< inputParam >	m_points;
		std::vector< cpChar >		m_state;


		void						setInitData(const uInt&		_coutDimensions,
			const double&		_step,
			const double&		_precision,
			const inputParam&	_beginPoint,
			const inputParam&	_optPoint,
			const uInt&			_maxIteration,
			const uInt&			_maxFunc,
			const uInt&			_maxTime);

		void						setNewPointData(const uInt&		_funcIteration,
			const uInt&			_funcBestPoint,
			const uInt&			_funcCalc,
			const double&		_step,
			const double&		_delta,
			const inputParam&	_point,
			const char*			_state);

		void						setEndMethodData(const TYPE_EXIT		_typeExit,
			const TYPE_EXIT_PRECISION_FLAG _exitFlag,
			const inputParam&		_finalPoint,
			const uInt&				_time,
			cpChar					_pFuncName,
			cpChar					_pMethodName);
		void						setOneDimensionalMethod(bool _used = false, cpChar _nameMethod = "");
		void						setDirectionGrad(const Arg& _grad, bool _used = false);

	public:
		void						addCalcData(const CDataMultiDimensional* _data);
		void						copyCalcData(const CDataMultiDimensional* _data);
		CDataMultiDimensional();
		inputParam					getSearchPoint() const;
		inputParam					getInputPoint() const;
		double**					getPointsPointer();
		int							getCountPoints() const;
		virtual void				printToFile(cpChar _nameFile);
		virtual ~CDataMultiDimensional();

		int							getCountIteration() const;
		int							getCountCalc() const;
		int							getCountBest() const;
		double						getElapsedTime() const;

	};

	///////////////////////////////////////////////////////////////////////////////////////////////
}
#endif