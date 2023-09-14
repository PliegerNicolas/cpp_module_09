/* Constructors & Destructors */

// Public

template <typename T>
MergeDeque<T>::MergeDeque(void):
	APmergeMe<T>()
{
	if (!DEBUG)
		return ;
	std::cout << CYAN;
	std::cout << "MergeDeque : default constructor called";
	std::cout << WHITE << std::endl;
}

template <typename T>
MergeDeque<T>::MergeDeque(const std::string &values):
	APmergeMe<T>()
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "MergeDeque : constructor with values parameter called";
		std::cout << WHITE << std::endl;
	}
	setData(values);
}

template <typename T>
MergeDeque<T>::MergeDeque(const size_t &argc, char **argv):
	APmergeMe<T>()
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "MergeDeque : constructor with argv and argv parameter called";
		std::cout << WHITE << std::endl;
	}
	setData(argc, argv);
}

template <typename T>
MergeDeque<T>::MergeDeque(const MergeDeque &other):
	APmergeMe<T>(other),
	_data(other._data),
	_pairs(other._pairs),
	_sorted(other._sorted),
	_pendingElements(other._pendingElements),
	_jacobsthalSequence(other._jacobsthalSequence)

{
	if (!DEBUG)
		return ;
	std::cout << CYAN;
	std::cout << "MergeDeque : copy constructor called";
	std::cout << WHITE << std::endl;
}

template <typename T>
MergeDeque<T>	&MergeDeque<T>::operator=(const MergeDeque &other)
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "MergeDeque : assignment operator called";
		std::cout << WHITE << std::endl;
	}

	if (this != &other)
	{
		APmergeMe<T>::operator=(other);
		_data = other._data;
		_pairs = other._pairs;
		_sorted = other._sorted;
		_pendingElements = other._pendingElements;
		_jacobsthalSequence = other._jacobsthalSequence;

	}
	return (*this);
}

template <typename T>
MergeDeque<T>::~MergeDeque(void)
{
	if (!DEBUG)
		return ;
	std::cout << CYAN;
	std::cout << "MergeDeque : default destructor called";
	std::cout << WHITE << std::endl;
}

// Protected

// Private

/* Member functions */

// Public

// Getter

template <typename T>
const std::deque<T>	&MergeDeque<T>::getData(void) const
{
	return (_data);
}

template <typename T>
const std::deque<T>	&MergeDeque<T>::getSorted(void) const
{
	return (_sorted);
}

template <typename T>
size_t	MergeDeque<T>::getDataSize(void) const
{
	return (_data.size());
}

// Setter

template <typename T>
void	MergeDeque<T>::setData(const std::string &values)
{
	std::istringstream	iss(values);
	T					value;

	_data.clear();
	_sorted.clear();

	while (iss >> value)
		_data.push_back(value);
	if (!iss.eof())
		throw std::runtime_error(std::string(RED)
			+ "Error: couldn't convert given string to expected type."
			+ WHITE);
}

template <typename T>
void	MergeDeque<T>::setData(const size_t &argc, char **argv)
{
	_data.clear();
	_sorted.clear();

	for (size_t i = 0; i < argc; i++)
	{
		std::istringstream	iss(argv[i]);
		T					value;

		while (iss >> value)
			_data.push_back(value);
		if (!iss.eof())
			throw std::runtime_error(std::string(RED)
				+ "Error: couldn't convert given string to expected type."
				+ WHITE);
	}
}

// Other

template <typename T>
const std::string	MergeDeque<T>::printDeque(const std::deque<T> &deque) const
{
	std::stringstream	ss;

	ss << "{";
	for (size_t i = 0; i < deque.size(); i++)
	{
		ss << deque[i];
		if (i < deque.size() - 1)
			ss << ", ";
	}
	ss << "}";
	return (ss.str());
}

template <typename T>
void	MergeDeque<T>::fordJohnsonSort(void)
{
	if (_data.size() == 0)
		throw std::runtime_error(std::string(RED)
			+ "Error: nothing to sort. Use .setData(\"[...]\")." + WHITE);

	/* Start timer */
	APmergeMe<T>::startTimer();

	if (_data.size() > 1)
	{
		/* Step 1 & 2:	[n comparisons] Split data into pairs and sort the elements of		*/
		/*			these pairs with each other.											*/
		toSortedPairs();

		/* Step 3 & 4:	[n / 2 comparisons] Recursivly sort the pairs and build '_sorted'	*/
		/*				also known as 'S' in Wikipedia and _pendingElements, the unsorted	*/
		/*				values left. 'S' contains n/2 elements. It also inserts at the		*/
		/*				start of S the element that was paired with the first and smallest	*/
		/*				element of 'S'.														*/
		mergeSort(0, _pairs.size() - 1);
		generateSortedAndPending();

		/* Step 5:	insert the remaining [n/2] elements via binary search and jacobsthal	*/
		/*			sequence.																*/
		insertPendingElements();
	}
	else
		_sorted = _data;
	// End timer
	APmergeMe<T>::stopTimer();
}

// Protected

// Private

// Step 1 & 2

template <typename T>
void	MergeDeque<T>::toSortedPairs(void)
{
	size_t	size;

	_pairs.clear();

	size = _data.size();
	if (size % 2 != 0)
	{
		APmergeMe<T>::_straggler.has = true;
		APmergeMe<T>::_straggler.value = _data.back();
		size--;
	}

	for (size_t i = 0; i < size; i += 2)
	{
		T	first = _data[i];
		T	second = _data[i + 1];
		if (first < second)
			_pairs.push_back(std::pair<T, T>(first, second));
		else
			_pairs.push_back(std::pair<T, T>(second, first));
	}
}

// Step 3 & 4

template <typename T>
void	MergeDeque<T>::mergeSort(size_t begin, size_t end)
{

	if (begin>= end)
		return ;

	size_t	middle = begin + (end - begin) / 2;

	mergeSort(begin, middle);
	mergeSort(middle + 1, end);

	merge(begin, middle, end);
}

template <typename T>
void	MergeDeque<T>::merge(size_t begin, size_t middle, size_t end)
{
	std::deque<std::pair<T, T> >	leftArr(_pairs.begin() + begin, _pairs.begin() + middle + 1);
	std::deque<std::pair<T, T> >	rightArr(_pairs.begin() + middle + 1, _pairs.begin() + end + 1);

	size_t	leftIdx = 0;
	size_t	rightIdx = 0;
	size_t	mergedIdx = begin;

	while (leftIdx < leftArr.size() && rightIdx < rightArr.size())
	{
		if (leftArr[leftIdx].first <= rightArr[rightIdx].first)
			_pairs[mergedIdx++] = leftArr[leftIdx++];
		else
			_pairs[mergedIdx++] = rightArr[rightIdx++];
	}

	while (leftIdx < leftArr.size())
		_pairs[mergedIdx++] = leftArr[leftIdx++];

	while (rightIdx < rightArr.size())
		_pairs[mergedIdx++] = rightArr[rightIdx++];

}

template <typename T>
void	MergeDeque<T>::generateSortedAndPending(void)
{
	if (_pairs.empty())
		return ;

	_sorted.clear();

	if (_pairs.size() > 0)
	{
		if (_pairs[0].first < _pairs[0].second)
		{
			_sorted.push_back(_pairs[0].first);
			_pendingElements.push_back(_pairs[0].second);
		}
		else
		{
			_sorted.push_back(_pairs[0].second);
			_pendingElements.push_back(_pairs[0].first);
		}
	}

	for (size_t i = 1; i < _pairs.size(); i++)
	{
		_sorted.push_back(_pairs[i].first);
		_pendingElements.push_back(_pairs[i].second);
	}

	if (APmergeMe<T>::_straggler.has)
	{
		_pendingElements.push_back(APmergeMe<T>::_straggler.value);
		APmergeMe<T>::_straggler.has = false;
		APmergeMe<T>::_straggler.value = 0;
	}

	_pairs.clear();
}

// Step 5

template <typename T>
void	MergeDeque<T>::insertPendingElements(void)
{
	generateJacobsthalSequence();

	size_t	jacobsthalIdx = 0;
	size_t	sortedIdx = 0;
	typename std::deque<T>::iterator	insertionPos;

	for (size_t i = 0; i < _pendingElements.size(); i++)
	{
		if (jacobsthalIdx < _jacobsthalSequence.size()
			&& sortedIdx == static_cast<size_t>(_jacobsthalSequence[jacobsthalIdx]))
		{
			jacobsthalIdx++;
		}

		insertionPos = _sorted.begin() + lowerboundBinarySearch(_sorted, _pendingElements[i]);
		_sorted.insert(insertionPos, _pendingElements[i]);
		sortedIdx++;
	}

	_pendingElements.clear();
}

template <typename T>
void	MergeDeque<T>::generateJacobsthalSequence(void)
{
	size_t	size = _pendingElements.size();

	if (_jacobsthalSequence.size() >= size)
		return ;

	size_t	index = 3;
	size_t	jacobsthalValue;

	while ((jacobsthalValue = APmergeMe<T>::getJacobsthalValue(index++)) < size - 1)
		_jacobsthalSequence.push_back(jacobsthalValue);
}

template <typename T>
size_t	MergeDeque<T>::lowerboundBinarySearch(const std::deque<T> &arr, const T &target)
{
	size_t	left = 0;
	size_t	right = arr.size();
	size_t	result = arr.size();
	size_t	middle;

	while (left < right)
	{
		middle = left + (right - left) / 2;

		if (arr[middle] == target)
		{
			result = middle;
			right = middle;
		}
		else if (arr[middle] < target)
			left = middle + 1;
		else
		{
			result = middle;
			right = middle;
		}
	}
	return (result);
}
