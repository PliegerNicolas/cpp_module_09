/* Constructors & Destructors */

// Public

template <typename T>
APmergeMe<T>::APmergeMe(void)
{
	std::cout << CYAN;
	std::cout << "APmergeMe : default constructor called";
	std::cout << WHITE << std::endl;
}

template <typename T>
APmergeMe<T>::APmergeMe(const APmergeMe &other)
{
	std::cout << CYAN;
	std::cout << "APmergeMe : copy constructor called";
	std::cout << WHITE << std::endl;

	(void)other;
}

template <typename T>
APmergeMe<T>	&APmergeMe<T>::operator=(const APmergeMe &other)
{
	std::cout << CYAN;
	std::cout << "APmergeMe : assignment operator called";
	std::cout << WHITE << std::endl;

	if (this != &other)
	{
		(void)other;
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
