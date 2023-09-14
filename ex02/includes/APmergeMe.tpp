/* Constructors & Destructors */

// Public

template <typename T>
APmergeMe<T>::~APmergeMe(void)
{
	if (!DEBUG)
		return ;
	std::cout << CYAN;
	std::cout << "APmergeMe : default destructor called";
	std::cout << WHITE << std::endl;
}

// Protected

template <typename T>
APmergeMe<T>::APmergeMe(void):
	_startTime(0),
	_endTime(0)
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "APmergeMe : default constructor called";
		std::cout << WHITE << std::endl;
	}

	_straggler.has = false;
	_straggler.value = 0;
}

template <typename T>
APmergeMe<T>::APmergeMe(const APmergeMe &other):
	_startTime(other._startTime),
	_endTime(other._endTime),
	_straggler(other._straggler)
{
	if (!DEBUG)
		return ;
	std::cout << CYAN;
	std::cout << "APmergeMe : copy constructor called";
	std::cout << WHITE << std::endl;
}

template <typename T>
APmergeMe<T>	&APmergeMe<T>::operator=(const APmergeMe &other)
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "APmergeMe : assignment operator called";
		std::cout << WHITE << std::endl;
	}

	if (this != &other)
	{
		_startTime = other._startTime;
		_endTime = other._endTime;
		_straggler.has = false;
		_straggler.value = 0;
	}
	return (*this);
}

// Private

/* Member functions */

// Public

template <typename T>
double	APmergeMe<T>::getElapsedTime(void) const
{
	// In milliseconds
	return (static_cast<double>(_endTime - _startTime) * 1000 / CLOCKS_PER_SEC);
}

// Protected

// Setters

// Getters

// Other
template <typename T>
void	APmergeMe<T>::startTimer(void)
{
	_startTime = clock();
}

template <typename T>
void	APmergeMe<T>::stopTimer(void)
{
	_endTime = clock();
}

template <typename T>
size_t	APmergeMe<T>::getJacobsthalValue(size_t n) const
{
	if (n <= 1)
		return (n);
	return (getJacobsthalValue(n - 1) + 2 * getJacobsthalValue(n - 2));
}

// Private
