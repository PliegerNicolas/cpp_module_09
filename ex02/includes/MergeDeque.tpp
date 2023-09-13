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

	APmergeMe<T>::startTimer();
	toPairs();
	sortPairs();
	APmergeMe<T>::stopTimer();
	std::cout << APmergeMe<T>::getElapsedTime() << std::endl;
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

// Protected

template <typename T>
void	MergeDeque<T>::toPairs(void)
{
	_pairs.clear();

	unsigned long int	dataSize = _data.size();
	if (dataSize % 2 != 0)
		dataSize--;

	// Doesn't has access to .reserve() because doesn't has contiguous memory storage.

	for (unsigned long int i = 0; i < dataSize; i += 2)
		_pairs.push_back(std::pair<T, T>(_data[i], _data[i + 1]));
}

template <typename T>
void	MergeDeque<T>::sortPairs(void)
{
	for (unsigned long int i = 0; i < _pairs.size(); ++i)
	{
		if (_pairs[i].first > _pairs[i].second)
			std::swap(_pairs[i].first, _pairs[i].second);
	}
}
