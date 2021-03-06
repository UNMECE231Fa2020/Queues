#include <iostream>

template <typename Q>
class Queue {
	private:
		size_t _size;
		Q *_data;
	public:
		Queue() : _size{0}, _data{nullptr} { }
		Queue(Q value) : _size{1} {
			_data = new Q(value);
		}
		Queue(const Queue &q) {
			if (q.empty()) {
				_size = 0;
				_data = nullptr;
			}
			else {
				size_t q_size = q.size();
				Q *q_data_copy = new Q[q_size];
				size_t i;
				for (i=0; i<q_size; i++) {
					*(q_data_copy + i) = *(q._data + i);
				}

				if (q_size == 1) {
					_data = new Q(*q_data_copy);
					_size = 1;
				}
				else {
					_data = new Q[q_size];
					for (i=0; i<q_size; i++) {
						*(_data + i) = *(q_data_copy + i);
					}
				}
				_size = q_size;
				if (q_size == 1) {
					delete q_data_copy;
				}
				else {
					delete [] q_data_copy;
				}
			}
		}

		~Queue() {
			if ((size() < 2) && (_data != nullptr)) {
				delete _data;
			}
			else {
				delete [] _data;
			}
		}

		size_t size() const {
			return _size;
		}

		Q front() const {
			return *_data;
		}

		Q back() const {
			return *(_data + size() - 1);
		}

		void enqueue(Q value) {
			if (empty()) {
				_size = 1;
				_data = new Q(value);
			}
			else {
				size_t data_size = size();
				Q *data_copy = new Q[data_size];
				size_t i;
				for (i=0; i<data_size; i++) {
					*(data_copy + i) = *(_data + i);
				}

				delete [] _data;
				_data = new Q[data_size + 1];
				for (i=0; i<data_size; i++) {
					*(_data + i) = *(data_copy + i);
				}
				*(_data + i) = value;
				_size += 1;
				delete [] data_copy;
			}
		}

		void dequeue() {
			if (empty()) {
				std::cout << "Queue is empty\n";
				return;
			}
			else if (size() == 1) {
				_size = 0;
				delete _data;
				_data = nullptr;
			}
			else {
				size_t data_size = size();
				Q *data_copy = new Q[data_size - 1];
				size_t i;
				for (i=1; i<data_size; i++) {
					*(data_copy + i-1) = *(_data + i);
				}

				delete [] _data;
				_data = new Q[data_size -1];

				for (i=0; i<data_size - 1; i++) {
					*(_data + i) = *(data_copy + i);
				}
				_size -= 1;
				delete [] data_copy;
			}
		}

		void print() const {
			for (size_t i=0; i<size(); i++) {
				std::cout << *(_data + i) << ' ';
			}
			std::cout << '\n';
		}

		bool empty() const {
			return ((_size == 0) && (_data == nullptr));
		}

		bool search(Q value) {
			for (size_t i=0; i<size(); i++) {
				if (value == *(_data + i)) {
					return true;
				}
			}
			return false;
		}

		Queue<Q> &operator=(const Queue<Q> &q) {
			if (q.empty()) {
				if (size() == 1) {
					delete _data;
				}
				else {
					delete [] _data;
				}
				_size = 0;
				_data = nullptr;
			}
			else if (q.size() == 1) {
				Q q_value = *q._data;
				if (size() == 1) {
					delete _data;
				}
				else {
					delete [] _data;
				}
				_data = new Q(q_value);
				_size = 1;
			}
			else {
				size_t q_size = q.size();
				Q q_data_copy = new Q[q_size];
				size_t i;
				for (i=0; i<q_size; i++) {
					*(q_data_copy + i) = *(q._data + i);
				}

				if (size() == 1) {
					delete _data;
				}
				else {
					delete [] _data;
				}

				_data = new Q[q_size];
				for (i=0; i<q_size; i++) {
					*(_data + i) = *(q_data_copy + i);
				}

				_size = q_size;
				delete [] q_data_copy;
			}
			return *this;
		}

		template <typename T>
		friend std::ostream &operator<<(std::ostream &out, const Queue<T> &q) {
				for (size_t i=0; i<q.size(); i++) {
					out << *(q._data + i) << ' ';
				}
				return out;
		}

		template <typename T>
		friend bool operator==(const Queue<T> &a, const Queue<T> &b);

		template <typename T>
		friend bool operator!=(const Queue<T> &a, const Queue<T> &b) {
			return !(a==b);
		}
};

template <typename T>
bool operator==(const Queue<T> &a, const Queue<T> &b) {
	if (a.size() != b.size()) {
		return false;
	}

	for (size_t i=0; i<b.size(); i++) {
		if ( (*(a._data + i)) != (*(b._data + i))) {
			return false;
		}
	}
	return true;
}
