#ifndef _PARAM_H_
#define _PARAM_H_

#include "common.h"
#include "math.h"

int sign(double _value);

namespace metopt
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	typedef const char*						cpChar;
	typedef unsigned int					uInt;
	typedef	enum TYPE_EXIT_PRECISION_FLAG	TEP_FLAG;
	typedef std::vector< uInt >				arrayInt;
	typedef std::vector< double >			arrayDouble;

	///////////////////////////////////////////////////////////////////////////////////////////////////////

	enum TYPE_METHOD
	{
		TYPE_ONE_DIMENSIONAL = 0,
		TYPE_MULTI_DIMENSIONAL
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////

	enum TYPE_EXIT
	{
		TYPE_EXIT_NONE = 0,

		TYPE_EXIT_ITERATION,
		TYPE_EXIT_FUNCTION,
		TYPE_EXIT_TIME,
		TYPE_EXIT_PRECISION,

		TYPE_EXIT_ID
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////

	enum NAME_METHOD
	{
		NAME_METHOD_NONE = 0,

		/*One Dimensional*/
		NAME_METHOD_SVEN,
		NAME_METHOD_ADAPTATION_STEP,
		NAME_METHOD_UNIFORM,
		NAME_METHOD_DIVISION,
		NAME_METHOD_DICHOTOMY,
		NAME_METHOD_FIBONACCI,
		NAME_METHOD_GOLDEN_SECTION,
		NAME_METHOD_QUADRATIC_INTERPOLATION,
		NAME_METHOD_CUBIC_INTERPOLATION,

		/*Multi Dimensional*/
		NAME_METHOD_HOOKE_JEEVES,
		NAME_METHOD_NELDER_MEAD,
		NAME_METHOD_SIMPLEX_METHOD,
		NAME_METHOD_BOX,
		NAME_METHOD_CYCLIC_MINMIN,
		NAME_METHOD_GAUSS_SEIDEL,
		NAME_METHOD_POWELL_SEARCH,
		NAME_METHOD_RANDOM_SEARCH,
		NAME_METHOD_WEIL_PI_SEARCH,
		NAME_METHOD_WEIL_E_SEARCH,

		NAME_METHOD_FASTEST_DESCENT,
		NAME_METHOD_FLETCHER_REEVES,
		NAME_METHOD_POLAK_RIBIERE,
		NAME_METHOD_DFP_SEARCH,
		NAME_METHOD_NEWTON_SEARCH,
		NAME_METHOD_NEWTON_RAPHSON,

		NAME_METHOD_BIN_GENETIC_ALGORITHM,
		NAME_METHOD_CON_GENETIC_ALGORITHM
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////

	enum TYPE_EXIT_PRECISION_FLAG
	{
		TYPE_EXIT_PRECISION_NONE = 0,

		TYPE_EXIT_PRECISION_STEP,
		TYPE_EXIT_PRECISION_FUNC,
		TYPE_EXIT_PRECISION_VAR,
	};

	
	//OneDimensional
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	class inputParam2D
	{
	public:
		inputParam2D() : x(0), fx(0) {};
		inputParam2D(double _x, double _fx) : x(_x), fx(_fx) {};
		inputParam2D&	operator=(const inputParam2D& _param);
		inputParam2D	operator+(const inputParam2D& _param);
		inputParam2D	operator-(const inputParam2D& _param);
		bool			operator<(const inputParam2D& _param);
		bool			operator==(const inputParam2D& _param);
		double			x, fx;
	};

	class outputParam2D
	{
	public:
		outputParam2D() : a(0, 0), b(0, 0), c(0, 0) {};
		outputParam2D& operator=(const outputParam2D& _param);
		bool operator==(const outputParam2D& _param);
		inputParam2D a;
		inputParam2D b;
		inputParam2D c;
	};

	//MultiDimensional
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class Arg
	{
	public:
		std::vector< double > x;
	public:
		Arg() {};
		Arg(const uInt _dimension);
		Arg(const Arg& _X);
		Arg(const std::vector< double >& _x) : x(_x) {};
		Arg(const double* _x);
		uInt		getSize() const;
		double*		getPointer();
		void		setPointer(const double* _x);
		void		setFillIn(const double& _value, const uInt& _size);
		void		setRendom(const double& _rangeMin, const double& _rangeMax);
		void		deleteElement(const uInt& _index);
		void		abs();
		double		getNorm() const;
		double		getNormInf() const;
		double		getMax() const;
		double		getSum() const;
		double		getDotProduct(const Arg& _X) const;
		bool		isNull() const;
		double&		operator[](const uInt& _index);
		const double&	operator[](const uInt& _index) const;
		Arg&		operator=(const Arg& _X);
		Arg			operator+(const Arg& _X) const;
		Arg			operator+(const double& _scalar) const;
		Arg			operator-(const Arg& _X) const;
		bool		operator==(const Arg& _X) const;
		Arg			operator*(const double& _scalar) const;
		Arg			operator*(const Arg& _X) const;
		Arg			operator/(const Arg& _X) const;
		Arg			operator/(const double& _scalar) const;
		//~Arg();
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////

	class inputParam
	{
	public:
		inputParam() : fx(0), x() {};
		inputParam(double _fx, std::vector< double> _x);
		inputParam(double _fx, double* _x);
		double		fx;
		Arg			x;
		int			ind;
		uInt		getSize() const;
		inputParam&	operator=(const inputParam& _param);
		double		operator*(const inputParam& _param);
		bool		operator==(inputParam& _param);
		bool		operator<(const inputParam& _param);
		static bool	sortByFunc(const inputParam& _x1, const inputParam& _x2);
		//~inputParam();
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////

	struct interval
	{
	public:
		Arg		m_pointA;
		Arg		m_pointB;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	class CTimer
	{
	private:
		struct time
		{
			int	_time;
			int	_millisec;
		};
		time m_start;
		time m_stop;
		timeb* m_time;
	public:
		CTimer();
		void start();
		void stop();

		int seconds() const;
		int milliseconds() const;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif