/* Constructors & Destructors */

// Public

template <typename T>
APmergeMe<T>::~APmergeMe(void)
{
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
	std::cout << CYAN;
	std::cout << "APmergeMe : default constructor called";
	std::cout << WHITE << std::endl;

	_straggler.has = false;
	_straggler.value = 0;
}

template <typename T>
APmergeMe<T>::APmergeMe(const APmergeMe &other):
	_startTime(other._startTime),
	_endTime(other._endTime),
	_straggler(other._straggler)
{
	std::cout << CYAN;
	std::cout << "APmergeMe : copy constructor called";
	std::cout << WHITE << std::endl;
}

template <typename T>
APmergeMe<T>	&APmergeMe<T>::operator=(const APmergeMe &other)
{
	std::cout << CYAN;
	std::cout << "APmergeMe : assignment operator called";
	std::cout << WHITE << std::endl;

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
double	APmergeMe<T>::getElapsedTime(void) const
{
	// In Seconds
	return (static_cast<double>(_endTime - _startTime) / CLOCKS_PER_SEC);
}

template <typename T>
unsigned long int	APmergeMe<T>::jacobsthal(unsigned long int n) const
{
	if (n <= 1)
		return (n);
	return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

// Private
