#pragma once

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

template <typename T, template <typename, typename> class Container, typename Alloc>
const std::string	PmergeMe<T, Container, Alloc>::printSortedData(void) const
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

template <typename T, template <typename, typename> class Container, typename Alloc>
void	PmergeMe<T, Container, Alloc>::fordJohnsonSort(void)
{

	startTimer();

	// Step 1
	generatePairs();
	// Step 2
	sortPairs();
	// Step 3
	mergeSort(_pairedData.begin(), _pairedData.end());
	// Step 4
	splitPairs();
	// Step 5
	insertPendingData();

	stopTimer();
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
	ConstIterator	it = _unsortedData.begin();
	ConstIterator	it_end = _unsortedData.end();

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

// Step 2
template <typename T, template <typename, typename> class Container, typename Alloc>
void	PmergeMe<T, Container, Alloc>::sortPairs(void)
{
	PairIterator	it = _pairedData.begin();

	while (it != _pairedData.end())
	{
		if (it->first < it->second)
			std::swap(it->first, it->second);
		it++;
	}
}

// Step 3

template <typename T, template <typename, typename> class Container, typename Alloc>
void	PmergeMe<T, Container, Alloc>::mergeSort(PairIterator begin, PairIterator end)
{
	if (std::distance(begin, end) <= 1)
		return ;
	
	PairIterator	middle = begin;
	std::advance(middle, std::distance(begin, end) / 2);

	mergeSort(begin, middle);
	mergeSort(middle, end);

	merge(begin, middle, end);
}

template <typename T, template <typename, typename> class Container, typename Alloc>
void	PmergeMe<T, Container, Alloc>::merge(PairIterator begin, PairIterator middle,
	PairIterator end)
{
	Container<std::pair<T, T>, Alloc>	left(begin, middle);
	Container<std::pair<T, T>, Alloc>	right(middle, end);

	PairIterator	leftIt = left.begin();
	PairIterator	rightIt = right.begin();
	PairIterator	currentIt = begin;

	while (leftIt != left.end() && rightIt != right.end())
	{
		if (*leftIt <= *rightIt)
			*currentIt++ = *leftIt++;
		else
			*currentIt++ = *rightIt++;
	}

	while (leftIt != left.end())
		*currentIt++ = *leftIt++;

	while (rightIt != right.end())
		*currentIt++ = *rightIt++;
}

// Step 4

template <typename T, template <typename, typename> class Container, typename Alloc>
void	PmergeMe<T, Container, Alloc>::splitPairs(void)
{

	_sortedData.clear();
	_pendingData.clear();

	if (_pairedData.empty() && !_straggler.has)
		return ;
	
	PairIterator	it =_pairedData.begin();

	while (it != _pairedData.end())
	{
		if (it == _pairedData.begin())
			_sortedData.push_back(it->second);
		else
			_pendingData.push_back(it->second);
		_sortedData.push_back(it->first);
		it++;
	}

	if (_straggler.has)
	{
		_pendingData.push_back(_straggler.value);
		_straggler.has = false;
		_straggler.value = 0;
	}
	
	_pairedData.clear();
}

// Step 5

template <typename T, template <typename, typename> class Container, typename Alloc>
void	PmergeMe<T, Container, Alloc>::insertPendingData(void)
{
	ConstIterator	pendingIt;
	Iterator		insertionPos;

	for (pendingIt = _pendingData.begin(); pendingIt != _pendingData.end(); pendingIt++)
	{
		insertionPos = higherboundBinarySearch(_sortedData, *pendingIt);

		_sortedData.insert(insertionPos, *pendingIt);
	}

	_pendingData.clear();
}

template <typename T, template <typename, typename> class Container, typename Alloc>
typename PmergeMe<T, Container, Alloc>::Iterator	PmergeMe<T, Container, Alloc>::higherboundBinarySearch(
	Container<T, Alloc> &container,
	const T &target)
{
	Iterator	left = container.begin();
	Iterator	right = container.end();

	while (std::distance(left, right) > 0)
	{
		Iterator	middle;
		
		middle = left;
		std::advance(middle, (std::distance(left, right) / 2));
		if (*middle < target)
		{
			left = middle;
			std::advance(left, 1);
		}
		else
			right = middle;
	}
	return (left);
}
