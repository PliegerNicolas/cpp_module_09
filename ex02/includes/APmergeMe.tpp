/* Constructors & Destructors */

// Public

template <typename T>
APmergeMe<T>::APmergeMe(void)
{
	std::cout << CYAN;
	std::cout << "APmergeMe : default constructor called";
	std::cout << WHITE << std::endl;

	startTimer();
	_elapsedTime = getStartTime();
}

template <typename T>
APmergeMe<T>::APmergeMe(const APmergeMe &other):
	_startTime(other._startTime),
	_elapsedTime(other._elapsedTime)
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
		_elapsedTime = other._elapsedTime;
	}
	return (*this);
}

template <typename T>
APmergeMe<T>::~APmergeMe(void)
{
	std::cout << CYAN;
	std::cout << "APmergeMe : default destructor called";
	std::cout << WHITE << std::endl;
}

// Protected

// Private

/* Member functions */

// Public

// Protected

// Setters
template <typename T>
void	APmergeMe<T>::setStartTime(void)
{
	_startTime = clock();
}

// Getters
template <typename T>
clock_t	APmergeMe<T>::getStartTime(void) const
{
	return (_startTime);
}

// Other
template <typename T>
void	APmergeMe<T>::startTimer(void)
{
	setStartTime();
}

template <typename T>
clock_t	APmergeMe<T>::getElapsedTime(void) const
{
	return (clock() - _startTime);
}

// Private
