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
APmergeMe<T>::APmergeMe(void)
{
	std::cout << CYAN;
	std::cout << "APmergeMe : default constructor called";
	std::cout << WHITE << std::endl;

	startTimer();
	_elapsedTime = _startTime;
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
	_elapsedTime = clock() - _startTime;
}

template <typename T>
double	APmergeMe<T>::getElapsedTime(void) const
{
	// In milliseconds
	return (static_cast<double>(_elapsedTime) / CLOCKS_PER_SEC * 1000.0);
}

// Private
