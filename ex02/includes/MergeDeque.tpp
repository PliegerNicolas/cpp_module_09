/* Constructors & Destructors */

// Public

template <typename T>
MergeDeque<T>::MergeDeque(const std::string &values):
	APmergeMe<T>()
{
	std::cout << CYAN;
	std::cout << "MergeDeque : constructor with values parameter called";
	std::cout << WHITE << std::endl;

	std::istringstream	iss(values);
	T					value;

	while (iss >> value)
		_data.push_back(value);

	fordJohnsonSort();
}

template <typename T>
MergeDeque<T>::MergeDeque(const MergeDeque &other):
	APmergeMe<T>(other),
	_data(other._data),
	_pairs(other._pairs)
{
	std::cout << CYAN;
	std::cout << "MergeDeque : copy constructor called";
	std::cout << WHITE << std::endl;
}

template <typename T>
MergeDeque<T>	&MergeDeque<T>::operator=(const MergeDeque &other)
{
	std::cout << CYAN;
	std::cout << "MergeDeque : assignment operator called";
	std::cout << WHITE << std::endl;

	if (this != &other)
	{
		APmergeMe<T>::operator=(other);
		_data = other._data;
		_pairs = other._pairs;
	}
	return (*this);
}

template <typename T>
MergeDeque<T>::~MergeDeque(void)
{
	std::cout << CYAN;
	std::cout << "MergeDeque : default destructor called";
	std::cout << WHITE << std::endl;
}

// Protected

// Private

template <typename T>
MergeDeque<T>::MergeDeque(void):
	APmergeMe<T>()
{
	std::cout << CYAN;
	std::cout << "MergeDeque : default constructor called";
	std::cout << WHITE << std::endl;
}

/* Member functions */

// Public

template <typename T>
void	MergeDeque<T>::fordJohnsonSort(void)
{
	APmergeMe<T>::startTimer();

	// split and sort pairs
	toSortedPairs();

	APmergeMe<T>::stopTimer();
	std::cout << "Vector = " << APmergeMe<T>::getElapsedTime() << " seconds" << std::endl;
}

// Protected

template <typename T>
void	MergeDeque<T>::toSortedPairs(void)
{
	_pairs.clear();

	typename std::deque<T>::iterator	it = _data.begin();

	while (it < _data.end() - 1)
	{
		if (*it > *(it + 1))
			_pairs.push_back(std::pair<T, T>(*(it + 1), *it));
		else
			_pairs.push_back(std::pair<T, T>(*it, *(it + 1)));
		it = _data.erase(it, it + 2);
	}
}
