/* Constructors & Destructors */

// Public

template <typename T>
MergeVector<T>::MergeVector(const std::string &values):
	APmergeMe<T>()
{
	std::cout << CYAN;
	std::cout << "MergeVector : constructor with values parameter called";
	std::cout << WHITE << std::endl;

	std::istringstream	iss(values);
	T					value;

	while (iss >> value)
		_data.push_back(value);

	fordJohnsonSort();
}

template <typename T>
MergeVector<T>::MergeVector(const MergeVector &other):
	APmergeMe<T>(other),
	_data(other._data),
	_pairs(other._pairs)
{
	std::cout << CYAN;
	std::cout << "MergeVector : copy constructor called";
	std::cout << WHITE << std::endl;
}

template <typename T>
MergeVector<T>	&MergeVector<T>::operator=(const MergeVector &other)
{
	std::cout << CYAN;
	std::cout << "MergeVector : assignment operator called";
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
MergeVector<T>::~MergeVector(void)
{
	std::cout << CYAN;
	std::cout << "MergeVector : default destructor called";
	std::cout << WHITE << std::endl;
}

// Protected

// Private

template <typename T>
MergeVector<T>::MergeVector(void):
	APmergeMe<T>()
{
	std::cout << CYAN;
	std::cout << "MergeVector : default constructor called";
	std::cout << WHITE << std::endl;
}

/* Member functions */

// Public

template <typename T>
void	MergeVector<T>::fordJohnsonSort(void)
{
	APmergeMe<T>::startTimer();

	// Step 1: Split into sorted pairs
	toSortedPairs();

	// Step 2: Recursivly soort by highest value (main chain)
	sortMainChain(0, _pairs.size() -1);

	// Step 3: Insert pend elements into the main chain
	insertPendElements();

	// Step 4: push to _sorted
	_sorted.clear();
	for (unsigned long int i = 0; i < _pairs.size(); i++)
	{
		_sorted.push_back(_pairs[i].first);
		_sorted.push_back(_pairs[i].second);
	}
	_pairs.clear();
	_pendElements.clear();

	APmergeMe<T>::stopTimer();

	std::cout << "Vector = " << APmergeMe<T>::getElapsedTime() << " seconds" << std::endl;
}

// Protected

template <typename T>
void	MergeVector<T>::toSortedPairs(void)
{
	_pairs.clear();

	unsigned long int	dataSize = _data.size();
	if (dataSize % 2 != 0)
		dataSize--;
	
	_pairs.reserve(dataSize / 2);

	for (unsigned long int i = 0; i < dataSize; i += 2)
	{
		T	first = _data[i];
		T	second = _data[i + 1];
		if (first > second)
			_pairs.push_back(std::pair<T, T>(second, first));
		else
			_pairs.push_back(std::pair<T, T>(first, second));
	}
}

template <typename T>
void	MergeVector<T>::sortMainChain(unsigned long int low, unsigned long int high)
{
	if (low < high)
	{
		unsigned long int	middle = (low + high) / 2;
	
		sortMainChain(low, middle);
		sortMainChain(middle + 1, high);

		mergeMainChain(low, middle, high);
	}
}

template <typename T>
void	MergeVector<T>::mergeMainChain(unsigned long int low, unsigned long int middle,
	unsigned long int high)
{
	std::vector<std::pair<T, T> > mergedPairs;
	
	unsigned long int	left = low;
	unsigned long int	right = middle + 1;

	while (left <= middle && right <= high)
	{
		if (_pairs[left].second >= _pairs[right].second)
			mergedPairs.push_back(_pairs[left++]);
		else
			mergedPairs.push_back(_pairs[right++]);
	}

	while (left <= middle)
		mergedPairs.push_back(_pairs[left++]);

	while (right <= high)
		mergedPairs.push_back(_pairs[right++]);
	
	for (unsigned long int i = 0; i < mergedPairs.size(); ++i)
		_pairs[low + i] = mergedPairs[i];
}

template <typename T>
void	MergeVector<T>::insertPendElements(void)
{
    std::vector<T> pendElements;

    unsigned long int i = _pairs.size() - 1;
    while (i > 0 && _pairs[i - 1].second <= _pairs[i].second)
    {
        pendElements.push_back(_pairs[i].first);
        pendElements.push_back(_pairs[i].second);
        i--;
    }

    // Insert pendElements into _sorted while keeping it sorted
    for (unsigned long int j = 0; j < pendElements.size(); j += 2)
    {
        T first = pendElements[j];
        T second = pendElements[j + 1];

        unsigned long int insertionIndex = _sorted.size();

        // Find the correct insertion index in _sorted
        while (insertionIndex > 0 && second < _sorted[insertionIndex - 1])
        {
            insertionIndex--;
        }

        // Insert the elements at the correct position
        _sorted.insert(_sorted.begin() + insertionIndex, second);
        _sorted.insert(_sorted.begin() + insertionIndex, first);
    }
}

// Private
