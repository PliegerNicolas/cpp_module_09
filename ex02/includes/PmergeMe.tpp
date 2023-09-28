#pragma once

/** Public **/

/* Constructors & Destructors */
// Default constructor
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::PmergeMe(void):
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
	_straggler.value = T();
}

// Type constructor
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::PmergeMe(const std::string &str):
	_startTime(0),
	_endTime(0)
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "PmergeMe : constructor with str parameter called";
		std::cout << WHITE << std::endl;
	}

	_straggler.has = false;
	_straggler.value = T();

	setUnsortedData(str);
}

// Type constructor
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::PmergeMe(const int &argc, char **argv):
	_startTime(0),
	_endTime(0)
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "PmergeMe : constructor with argc and argv parameters called";
		std::cout << WHITE << std::endl;
	}

	_straggler.has = false;
	_straggler.value = T();

	setUnsortedData(argc, argv);
}

// Copy constructor
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::PmergeMe(const PmergeMe &other):
	_unsortedData(other._unsortedData),
	_sortedData(other._sortedData),
	_pairedData(other._pairedData),
	_pendingData(other._pendingData),
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
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>	&PmergeMe<T, Container>::operator=(const PmergeMe &other)
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
		_startTime = other._startTime;
		_endTime = other._endTime;
		_straggler = other._straggler;
	}
	return (*this);
}

// Default destructor
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::~PmergeMe(void)
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

// getUnsortedData()
template <typename T, template <typename, typename> class Container>
const Container<T, typename PmergeMe<T, Container>::Alloc>	&PmergeMe<T, Container>::getUnsortedData(void) const
{
	return (_unsortedData);
}

// getSortedData()
template <typename T, template <typename, typename> class Container>
const Container<T, typename PmergeMe<T, Container>::Alloc>	&PmergeMe<T, Container>::getSortedData(void) const
{
	return (_sortedData);
}

// getElapsedTime()
template <typename T, template <typename, typename> class Container>
double	PmergeMe<T, Container>::getElapsedTime(void) const
{
	// In milliseconds.
	return (static_cast<double>(_endTime - _startTime) * 1000 / CLOCKS_PER_SEC);
}

// ::Setters

// setUnsortedData()
template <typename T, template <typename, typename> class Container>
void	PmergeMe<T, Container>::setUnsortedData(const std::string &str)
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
template <typename T, template <typename, typename> class Container>
void	PmergeMe<T, Container>::setUnsortedData(const int &argc, char **argv)
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
template <typename T, template <typename, typename> class Container>
const std::string	PmergeMe<T, Container>::printUnsortedData(void) const
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
template <typename T, template <typename, typename> class Container>
const std::string	PmergeMe<T, Container>::printSortedData(void) const
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

// fordJohnsonSort()
template <typename T, template <typename, typename> class Container>
void	PmergeMe<T, Container>::fordJohnsonSort(void)
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

// startTimer()
template <typename T, template <typename, typename> class Container>
void	PmergeMe<T, Container>::startTimer(void)
{
	_startTime = clock();
}

// stopTimer()
template <typename T, template <typename, typename> class Container>
void	PmergeMe<T, Container>::stopTimer(void)
{
	_endTime = clock();
}

// Step 1

// generatePairs()
template <typename T, template <typename, typename> class Container>
void	PmergeMe<T, Container>::generatePairs(void)
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

// sortPairs()
template <typename T, template <typename, typename> class Container>
void	PmergeMe<T, Container>::sortPairs(void)
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

// mergeSort()
template <typename T, template <typename, typename> class Container>
void	PmergeMe<T, Container>::mergeSort(PairIterator begin, PairIterator end)
{
	if (std::distance(begin, end) <= 1)
		return ;
	
	PairIterator	middle = begin;
	std::advance(middle, std::distance(begin, end) / 2);

	mergeSort(begin, middle);
	mergeSort(middle, end);

	merge(begin, middle, end);
}

// merge()
template <typename T, template <typename, typename> class Container>
void	PmergeMe<T, Container>::merge(PairIterator begin, PairIterator middle, PairIterator end)
{
	Container<std::pair<T, T>, std::allocator<std::pair<T, T> > >	left(begin, middle);
	Container<std::pair<T, T>, std::allocator<std::pair<T, T> > >	right(middle, end);

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

// splitPairs()
template <typename T, template <typename, typename> class Container>
void	PmergeMe<T, Container>::splitPairs(void)
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
		_straggler.value = T();
	}
	
	_pairedData.clear();
}

// Step 5

// insertPendingData()
template <typename T, template <typename, typename> class Container>
void	PmergeMe<T, Container>::insertPendingData(void)
{
	Container<Container<T, Alloc>, Alloc2d >	elementGroups;
	Container<T, Alloc>				currentGroup;

	for (ConstIterator it = _pendingData.begin(); it != _pendingData.end(); it++)
	{
		
		if (currentGroup.empty()
		|| currentGroup.size() + 1 <= static_cast<ContainerSizeType>(1 << elementGroups.size()))
		{
			currentGroup.push_back(*it);
		}
		else
		{
			elementGroups.push_back(currentGroup);
			currentGroup.clear();
			currentGroup.push_back(*it);
		}
	}

	if (!currentGroup.empty())
		elementGroups.push_back(currentGroup);

	for (Iterator2d groupIt = elementGroups.begin(); groupIt != elementGroups.end(); groupIt++)
		std::reverse(groupIt->begin(), groupIt->end());

	for (ConstIterator2d groupIt = elementGroups.begin(); groupIt != elementGroups.end(); groupIt++)
	{
		for (ConstIterator elemIt = groupIt->begin(); elemIt != groupIt->end(); elemIt++)
		{
			Iterator insertionPos = higherboundBinarySearch(_sortedData, *elemIt);
			_sortedData.insert(insertionPos, *elemIt);
		}
	}

	_pendingData.clear();
}

// higherboundBinarySearch()
template <typename T, template <typename, typename> class Container>
typename Container<T, typename PmergeMe<T, Container>::Alloc>::iterator	PmergeMe<T, Container>::higherboundBinarySearch(Container<T, typename PmergeMe<T, Container>::Alloc> &container, const T &target)
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
