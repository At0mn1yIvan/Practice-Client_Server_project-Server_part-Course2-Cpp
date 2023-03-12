#pragma once
template <class T>
class Queue
{
private:
	T* _data;
	size_t _size;
	size_t _firstInd;
	size_t _lastInd;
	size_t _countElem;
public:
	Queue(const Queue&) = delete;
	Queue& operator=(const Queue&) = delete;

	Queue(size_t size = 10) : _size(size) {
		_data = new T[_size];
		_firstInd = 0;
		_lastInd = 0;
		_countElem = 0;
	}

	bool PriorityPush(const T& el) {
		if (!isFull())
		{
			int index;
			if (_countElem)
			{
				index = _lastInd - 1; // Индекс последнего элемента в очереди
				while (index != _firstInd - 1)
				{
					if (index < 0) index = _size - 1; // Если индекс указывает на начало очереди, значит последний элемент имеет максимальный индекс
					if (el > _data[index])
					{
						_data[(index + 1) % _size] = _data[index];
						index--;
					}
					else break;
				}
				index++;

			}
			else
			{
				index = 0;
			}
			_data[index] = el;
			_lastInd = (_lastInd + 1) % _size;
			_countElem++;
			return true;
		}
		return false;
	}

	bool Push(const T& el)
	{
		if (!isFull())) {
			_data[_lastInd] = el;
			_lastInd = (_lastInd + 1) % _size;
			_countElem++;
			return true;
		}
		return false;
	}

	T Pop()
	{
		const T& elem = _data[_firstInd];
		_firstInd = (_firstInd + 1) % _size;
		_countElem--;
		return elem;
	}

	T Top()
	{
		const T& elem = _data[_firstInd];
		return elem;

	}

	bool isEmpty() const
	{
		return _countElem == 0;
	}

	bool isFull() const
	{
		return _countElem == _size;
	}
};

