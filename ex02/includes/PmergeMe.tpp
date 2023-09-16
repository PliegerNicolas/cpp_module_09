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
