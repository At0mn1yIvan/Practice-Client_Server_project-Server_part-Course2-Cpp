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

		void PriorityPush(const T& el)	{

		}

		void Push(const T& el) {
			if (_countElem < _size) {
				_data[_lastInd] = el;
				_lastInd = (_lastInd + 1) % _size;
				_countElem++;
			}
		}

		T Pop() {
			const T& elem = _data[_firstInd];
			_firstInd = (_firstInd + 1) & _size;
			_countElem--;
			return elem;
		}

		bool isEmpty() const {
			return _countElem == 0;
		}

		bool isFull() const {
			return _countElem == _size;
		}
	};

