#pragma once

/** Public **/

/* Constructors & Destructors */
// Default constructor
template <typename T, template <typename, typename> class C>
PmergeMe<T, C>::PmergeMe(void):
	_startTime(0),
	_endTime(0)
{
	if (!DEBUG)
		return ;
	std::cout << CYAN;
	std::cout << "PmergeMe : default constructor called";
	std::cout << WHITE << std::endl;
}

// Type constructor
template <typename T, template <typename, typename> class C>
PmergeMe<T, C>::PmergeMe(const std::string &str):
	_startTime(0),
	_endTime(0)
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "PmergeMe : constructor with str parameter called";
		std::cout << WHITE << std::endl;
	}
	setUnsortedData(str);
}

// Type constructor
template <typename T, template <typename, typename> class C>
PmergeMe<T, C>::PmergeMe(const int &argc, char **argv):
	_startTime(0),
	_endTime(0)
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "PmergeMe : constructor with argc and argv parameters called";
		std::cout << WHITE << std::endl;
	}
	setUnsortedData(argc, argv);
}

// Copy constructor
template <typename T, template <typename, typename> class C>
PmergeMe<T, C>::PmergeMe(const PmergeMe &other):
	_unsortedData(other._unsortedData),
	_sortedData(other._sortedData),
	_startTime(other._startTime),
	_endTime(other._endTime)
{
	if (!DEBUG)
		return ;
	std::cout << CYAN;
	std::cout << "PmergeMe : copy constructor called";
	std::cout << WHITE << std::endl;
}

// Assignment operator
template <typename T, template <typename, typename> class C>
PmergeMe<T, C>	&PmergeMe<T, C>::operator=(const PmergeMe &other)
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "PmergeMe : assignment operator called";
		std::cout << WHITE << std::endl;
	}

	if (this != &other)
	{
		_unsortedData = other._unsortedData;
		_sortedData = other._sortedData;
		_startTime = other._startTime;
		_endTime = other._endTime;
	}

	return (*this);
}

// Default destructor
template <typename T, template <typename, typename> class C>
PmergeMe<T, C>::~PmergeMe(void)
{
	if (!DEBUG)
		return ;
	std::cout << CYAN;
	std::cout << "PmergeMe : default destructor called";
	std::cout << WHITE << std::endl;
}

/* Member functions */

// ::Getters

// getUnsortedData()
template <typename T, template <typename, typename> class C>
const typename PmergeMe<T, C>::Container&
PmergeMe<T, C>::getUnsortedData(void) const
{
	return (_unsortedData);
}

// getSortedData()
template <typename T, template <typename, typename> class C>
const typename PmergeMe<T, C>::Container&
PmergeMe<T, C>::getSortedData(void) const
{
	return (_sortedData);
}

// getElapsedTime()
template <typename T, template <typename, typename> class C>
double	PmergeMe<T, C>::getElapsedTime(void) const
{
	// In milliseconds.
	return (static_cast<double>(_endTime - _startTime) * 1000 / CLOCKS_PER_SEC);
}

// ::Setters

// setUnsortedData()
template <typename T, template <typename, typename> class C>
void	PmergeMe<T, C>::setUnsortedData(const std::string &str)
{
	std::istringstream	iss;
	T					val;

	_unsortedData.clear();
	_sortedData.clear();

	iss.clear();
	iss.str(str);
	while (iss >> val)
		_unsortedData.push_back(val);

	if (!iss.eof())
	{
		_unsortedData.clear();
		throw std::runtime_error(
			std::string(RED)
			+ "Error: invalid data passed."
			+ WHITE
		);
	}
}

// setUnsortedData()
template <typename T, template <typename, typename> class C>
void	PmergeMe<T, C>::setUnsortedData(const int &argc, char **argv)
{
	std::istringstream	iss;
	T					val;

	_unsortedData.clear();
	_sortedData.clear();

	for (size_t i = 1; i < static_cast<size_t>(argc); i++)
	{
		iss.clear();
		iss.str(argv[i]);

		while (iss >> val)
			_unsortedData.push_back(val);

		if (!iss.eof())
		{
			_unsortedData.clear();
			throw std::runtime_error(
				std::string(RED)
				+ "Error: invalid data passed."
				+ WHITE
			);
		}
	}
}

// :Other

// printUnsortedData()
template <typename T, template <typename, typename> class C>
const std::string	PmergeMe<T, C>::printUnsortedData(void) const
{
	std::stringstream	ss;
	ConstIterator		it;

	ss << "{";
	for (it = _unsortedData.begin(); it != _unsortedData.end(); it++)
	{
		ss << *it;
		if (it != --_unsortedData.end())
			ss << ", ";
	}
	ss << "}";
	return (ss.str());
}

// printSortedData()
template <typename T, template <typename, typename> class C>
const std::string	PmergeMe<T, C>::printSortedData(void) const
{
	std::stringstream	ss;
	ConstIterator		it;

	ss << "{";
	for (it = _sortedData.begin(); it != _sortedData.end(); it++)
	{
		ss << *it;
		if (it != --_sortedData.end())
			ss << ", ";
	}
	ss << "}";
	return (ss.str());
}

/** Protected **/

/* Constructors & Destructors */
/* Member functions */

/** Private **/

/* Constructors & Destructors */
/* Member functions */

// startTimer()
template <typename T, template <typename, typename> class C>
void	PmergeMe<T, C>::startTimer(void)
{
	_startTime = clock();
}

// stopTimer()
template <typename T, template <typename, typename> class C>
void	PmergeMe<T, C>::stopTimer(void)
{
	_endTime = clock();
}

/* ************************************************************************** */
/* *               Ford-Johnson Merge Insertion sort Algorythm              * */
/* ************************************************************************** */

// fordJohnsonSort()
template <typename T, template <typename, typename> class C>
void	PmergeMe<T, C>::fordJohnsonSort(void)
{
	startTimer();

	stopTimer();
}

