#include <iostream>
#include <exception>      // std::set_terminate
#include <cstdlib> 

template<typename T, bool unique = false>
class Stack {
public:
	class inputIterator;
	class reverseIterator;
	class randomAccessIterator;
	class S;
	Stack() {
		front = nullptr;
		back = nullptr;
	}
	~Stack() {
		while (!empty()) {
			pop();
		}
	}
	void push(T value) {
		try {
			if (unique && find(value) != nullptr)throw std::string("duplicate_keys_exception");
			S* obj = new S;
			if (front != nullptr)front->previous = obj;
			obj->value = value;
			obj->previous = nullptr;
			obj->next = front;
			front = obj;
			if (back == nullptr)back = front;
		}
		catch (std::string& str) {
			std::cerr << "\nCaught an exception: " << str << "\n";
		}
	}
	T& top() {
		try {
			if (empty()) throw std::string("empy_stack_exception");
			return front->value;

		}
		catch (std::string& str) {
			std::cerr << "\nCaught an exception: " << str << "\n";
		}
		static T obj;
		return obj;
	}
	void pop() {
		try {
			if (empty()) throw std::string("empy_stack_exception");
			S* obj = front;
			front = front->next;
			if (front == nullptr)back = nullptr;
			else front->previous = nullptr;
			delete obj;
		}
		catch (std::string& str) {
			std::cerr << "\nCaught an exception: " << str << "\n";

		}
	}
	T* find(T x) {
		S* f = front;
		while (f != nullptr && f->value != x)f = f->next;
		if (f != nullptr)return &(f->value);
		else return nullptr;
	}
	bool empty() {
		return front == nullptr;
	}
	void sort() {
		randomAccessIterator I = randomAccessEnd();
		I--;

		while (I != randomAccessBegin()) {
			I--;
			T obj = *I;
			randomAccessIterator J = I;
			J++;
			while (J != randomAccessEnd() && *J < obj) {
				*(J - 1) = *J;
				J++;
			}
			*(J - 1) = obj;
		}
	}
	void show() {
		std::cout << "In stack ";
		inputIterator I = inputBegin();
		while (I != inputEnd())
			std::cout << *I++ << " ";
		std::cout << "\n";
	}

	T operator--() {
		pop();
		return top();
	}
	T operator--(int) {
		T tmp = top();
		pop();
		return tmp;
	}
	void operator +=(T val) {

		push(val);
	}

	inputIterator inputBegin() {
		inputIterator I(front);
		return I;
	}
	inputIterator inputEnd() {
		inputIterator I(nullptr);
		return I;
	}
	reverseIterator reverseBegin() {
		reverseIterator I(back);
		return I;
	}
	reverseIterator reverseEnd() {
		reverseIterator I(nullptr);
		return I;
	}
	randomAccessIterator randomAccessBegin() {
		randomAccessIterator I(front, back, front);
		return I;
	}
	randomAccessIterator randomAccessEnd() {
		randomAccessIterator I(front, back, nullptr);
		return I;
	}

	class randomAccessIterator {
	private:
		S* start;
		S* end;
		S* cur;

	public:
		randomAccessIterator() {
		}

		randomAccessIterator(S* first, S* last, S* now) {
			cur = now;
			start = first;
			end = last;
		}
		randomAccessIterator& operator++() {
			try {
				if (!this->cur)throw std::string("out_of_range_exception");
				this->cur = this->cur->next;
				return *this;
			}
			catch (std::string& str) {
				std::cerr << "\nCaught an exception: " << str << "\n";
			}
			return *this;
		}
		randomAccessIterator operator++(int) {
			randomAccessIterator tmp = *this;
			try {
				if (!this->cur)throw std::string("out_of_range_exception");
				this->cur = this->cur->next;
			}
			catch (std::string& str) {
				std::cerr << "\nCaught an exception: " << str << "\n";
			}
			return tmp;
		}
		randomAccessIterator& operator--() {
			if (this->cur == nullptr)this->cur = end;
			else {
				try {
					if (!this->cur)throw std::string("out_of_range_exception");
					this->cur = this->cur->previous;
					return *this;
				}
				catch (std::string& str) {
					std::cerr << "\nCaught an exception: " << str << "\n";
				}
			}
			return *this;
		}
		randomAccessIterator operator--(int) {
			randomAccessIterator tmp = *this;
			if (this->cur == nullptr)this->cur = end;
			else {
				try {
					if (!this->cur)throw std::string("out_of_range_exception");
					this->cur = this->cur->previous;
				}
				catch (std::string& str) {
					std::cerr << "\nCaught an exception: " << str << "\n";
				}
			}
			return tmp;
		}
		randomAccessIterator operator-(int count) {
			randomAccessIterator tmp = *this;
			for (int i = 0; i < count; i++)--tmp;
			return tmp;
		}
		void operator=(randomAccessIterator obj) {
			this->cur = obj.cur;
			this->end = obj.end;
			this->start = obj.start;
		}
		T& operator*() {

			try {
				if (!this->cur)throw std::string("out_of_range_exception");
				return this->cur->value;
			}
			catch (std::string& str) {
				std::cerr << "\nCaught an exception: " << str << "\n";
			}
			static T tmp;
			return tmp;
		}
		T& operator[](const int index) {
			try {
				this->cur = this->start;
				if (index < 0)throw std::string("out_of_range_exception");
				for (int i = 0; i < index; i++) {
					if (!this->cur)throw std::string("out_of_range_exception");
					this->cur = this->cur->next;
				}

				return **this;
			}
			catch (std::string& str) {
				std::cerr << "\nCaught an exception: " << str << "\n";
			}
			static T obj;
			return obj;
		}
		bool operator!=(randomAccessIterator cmp) {
			return this->cur != cmp.cur;
		}
	};

	class inputIterator {
	private:
		S* cur;
	public:

		inputIterator() {
		}
		inputIterator(S* first) {
			cur = first;
		}
		inputIterator& operator++() {
			try {
				if (!this->cur)throw std::string("out_of_range_exception");
				this->cur = this->cur->next;
				return *this;
			}
			catch (std::string& str) {
				std::cerr << "\nCaught an exception: " << str << "\n";
			}
			return *this;
		}

		inputIterator operator++(int) {
			inputIterator tmp = *this;
			try {
				if (!this->cur)throw std::string("out_of_range_exception");
				this->cur = this->cur->next;
			}
			catch (std::string& str) {
				std::cerr << "\nCaught an exception: " << str << "\n";
			}
			return tmp;
		}

		T& operator*() {
			return this->cur->value;
		}
		bool operator!=(inputIterator right) {
			return (this->cur != right.cur);
		}
	};

	class reverseIterator {
	private:
		S* cur;
	public:
		reverseIterator() {
		}
		reverseIterator(S* first) {
			cur = first;
		}

		reverseIterator& operator++() {
			try {
				if (!this->cur)throw std::string("out_of_range_exception");
				this->cur = this->cur->previous;
				return *this;
			}
			catch (std::string& str) {
				std::cerr << "\nCaught an exception: " << str << "\n";
			}
			return *this;
		}

		reverseIterator operator++(int) {
			reverseIterator tmp = *this;
			try {
				if (!this->cur)throw std::string("out_of_range_exception");
				this->cur = this->cur->previous;
			}
			catch (std::string& str) {
				std::cerr << "\nCaught an exception: " << str << "\n";
			}
			return tmp;
		}

		bool operator!=(reverseIterator obj) {
			return this->cur != obj.cur;
		}

		T& operator*() {
			return this->cur->value;
		}
	};

private:
	class S {

	public:
		S() {
			next = NULL;
			previous = NULL;
		}
		T value;
		S* next;
		S* previous;
		//friend Stack;

	};
	S* back;
	S* front;
};

class movie {
public:

	std::string name;
	std::string review;
	movie() {
		name = "noname";
		review = "";
		id = 0;
	}
	bool operator!=(movie obj) {
		return this->name != obj.name;
	}
	bool operator==(movie obj) {
		return this->name == obj.name;
	}
	friend std::ostream& operator<<(std::ostream& out, movie obj);

private:
	int id;
};

std::ostream& operator<<(std::ostream& out, movie obj) {
	return out << "{Name: \"" << obj.name << "\", Review: \"" << obj.review << "\"} ";
}

int main()
{
	/* // TERMINATE
	std::set_terminate(terminate_handler([]() {
		std::cerr << "abort";
		exit(0);
	}));
	//std::set_unexpected(unexpected_handler(b));
	throw 1;
	*/

	// TEST 1 -----------------------------------------------
	std::cout << "\nTest 1-------------------------------------\n";
	int* ptr1;
	Stack<int> a;
	a += 10;
	a += 10;
	a += 11;

	a.show();

	ptr1 = a.find(11);
	if (!ptr1)std::cout << "not found\n";
	else std::cout << "found: " << *ptr1 << "\n";

	a--;

	ptr1 = a.find(11);
	if (!ptr1)std::cout << "not found\n";
	else std::cout << "found: " << *ptr1 << "\n";

	a.show();
	std::cout << "sort: ";
	a += 12;
	a += 1;
	a += 11;
	a.show();
	a.sort();
	a.show();

	std::cout << "Input iterator: ";
	for (Stack<int>::inputIterator I = a.inputBegin(); I != a.inputEnd(); I++)
		std::cout << *I << " ";

	// TEST 2 -----------------------------------------------
	std::cout << "\nTest 2-------------------------------------";
	double* ptr2;
	Stack<double, true> b;
	b += 10.1;
	b += 10.1;
	b += 8.1;
	b += 16.1;
	b += 11.1;
	b.show();

	ptr2 = b.find(11.1);
	if (!ptr2)std::cout << "not found\n";
	else std::cout << "found: " << *ptr2 << "\n";

	b--;

	ptr2 = b.find(11.1);
	if (!ptr2)std::cout << "not found\n";
	else std::cout << "found: " << *ptr2 << "\n";

	b.show();

	std::cout << "Reverse iterator: ";
	for (Stack<double,true>::reverseIterator I = b.reverseBegin(); I != b.reverseEnd(); I++)
		std::cout << *I << " ";

	// TEST 3 -----------------------------------------------
	std::cout << "\nTest 3-------------------------------------\n";
	movie* ptr3;
	Stack<movie> c;
	movie tmp;
	tmp.name = "first";
	c += tmp;
	tmp.name = "second";
	c += tmp;
	c.show();

	ptr3 = c.find(tmp);
	if (!ptr3)std::cout << "not found\n";
	else std::cout << "found: " << *ptr3 << "\n";

	c--;

	ptr3 = c.find(tmp);
	if (!ptr3)std::cout << "not found\n";
	else std::cout << "found: " << *ptr3 << "\n";

	c.show();

	std::cout << "Random access iterator ";
	Stack<movie>::randomAccessIterator I = c.randomAccessBegin();
	std::cout << I[0] << "\n";
	std::cout << I[2] << "\n";

}
