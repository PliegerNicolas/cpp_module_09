/** Public **/

/* Constructors & Destructors */
// Default constructor
template <typename T, template <typename, typename> class Container, typename Alloc>
PmergeMe<T, Container, Alloc>::PmergeMe(void):
	_startTime(0),
	_endTime(0)
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "PmergeMe : default constructor called";
		std::cout << WHITE << std::endl;
	}

	_straggler.has = false;
	_straggler.value = 0;
}

// Copy constructor
template <typename T, template <typename, typename> class Container, typename Alloc>
PmergeMe<T, Container, Alloc>::PmergeMe(const PmergeMe &other):
	_unsortedData(other._unsortedData),
	_sortedData(other._sortedData),
	_pairedData(other._pairedData),
	_pendingData(other._pendingData),
	_jacobsthalSequence(other._jacobsthalSequence),
	_startTime(other._startTime),
	_endTime(other._endTime),
	_straggler(other._straggler)
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "PmergeMe : copy constructor called";
		std::cout << WHITE << std::endl;
	}
}

// Assignment operator
template <typename T, template <typename, typename> class Container, typename Alloc>
PmergeMe<T, Container, Alloc>    &PmergeMe<T, Container, Alloc>::operator=(const PmergeMe &other)
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
		_pairedData = other._pairedData;
		_pendingData = other._pendingData;
		_jacobsthalSequence = other._jacobsthalSequence;
		_startTime = other._startTime;
		_endTime = other._endTime;
		_straggler = other._straggler;
	}
	return (*this);
}

// Default destructor
template <typename T, template <typename, typename> class Container, typename Alloc>
PmergeMe<T, Container, Alloc>::~PmergeMe(void)
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "PmergeMe : default destructor called";
		std::cout << WHITE << std::endl;
	}
}

/* Member functions */

// ::Getters
template <typename T, template <typename, typename> class Container, typename Alloc>
const Container<T, Alloc>	&PmergeMe<T, Container, Alloc>::getUnsortedData(void) const
{
	return (_unsortedData);
}

template <typename T, template <typename, typename> class Container, typename Alloc>
const Container<T, Alloc>	&PmergeMe<T, Container, Alloc>::getSortedData(void) const
{
	return (_sortedData);
}

template <typename T, template <typename, typename> class Container, typename Alloc>
double	PmergeMe<T, Container, Alloc>::getElapsedTime(void) const
{
	// In milliseconds.
	return (static_cast<double>(_endTime - _startTime) * 1000 / CLOCKS_PER_SEC);
}

// ::Setters
template <typename T, template <typename, typename> class Container, typename Alloc>
void	PmergeMe<T, Container, Alloc>::setUnsortedData(const std::string &str)
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

template <typename T, template <typename, typename> class Container, typename Alloc>
void	PmergeMe<T, Container, Alloc>::setUnsortedData(const int &argc, char **argv)
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
template <typename T, template <typename, typename> class Container, typename Alloc>
const std::string	PmergeMe<T, Container, Alloc>::printUnsortedData(void) const
{
	std::stringstream								ss;
	typename Container<T, Alloc>::const_iterator	it;

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

template <typename T, template <typename, typename> class Container, typename Alloc>
const std::string	PmergeMe<T, Container, Alloc>::printSortedData(void) const
{
	std::stringstream								ss;
	typename Container<T, Alloc>::const_iterator	it;

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

#include <unistd.h>

template <typename T, template <typename, typename> class Container, typename Alloc>
void	PmergeMe<T, Container, Alloc>::fordJohnsonSort(void)
{
	startTimer();

	generatePairs();
	sortPairs();

	stopTimer();

	_pairedData.clear();
	_pendingData.clear();
	_jacobsthalSequence.clear();
	_straggler.has = false;
	_straggler.value = 0;
}

/** Protected **/

/* Constructors & Destructors */
/* Member functions */

/** Private **/

/* Constructors & Destructors */
/* Member functions */
template <typename T, template <typename, typename> class Container, typename Alloc>
void	PmergeMe<T, Container, Alloc>::startTimer(void)
{
	_startTime = clock();
}

template <typename T, template <typename, typename> class Container, typename Alloc>
void	PmergeMe<T, Container, Alloc>::stopTimer(void)
{
	_endTime = clock();
}

// Step 1
template <typename T, template <typename, typename> class Container, typename Alloc>
void	PmergeMe<T, Container, Alloc>::generatePairs(void)
{
	typename Container<T, Alloc>::const_iterator	it = _unsortedData.begin();
	typename Container<T, Alloc>::const_iterator	it_end = _unsortedData.end();

	if (_unsortedData.size() % 2 != 0)
	{
		_straggler.has = true;
		_straggler.value = _unsortedData.back();
		it_end--;
	}

	while (it != it_end)
	{
		const T	&first = *it++;
		const T	&second = *it++;
		_pairedData.push_back(std::pair<T, T>(first, second));
	}
}

template <typename T, template <typename, typename> class Container, typename Alloc>
void	PmergeMe<T, Container, Alloc>::sortPairs(void)
{
	typename Container<std::pair<T, T>, Alloc>::iterator	it = _pairedData.begin();
	typename Container<std::pair<T, T>, Alloc>::iterator	it_end = _pairedData.end();

	while (it != it_end)
	{
		if (it->first > it->second)
			std::swap(it->first, it->second);
		it++;
	}
}
