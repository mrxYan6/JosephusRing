#include <iostream>

template<typename Type>
class Node {
public:
	Type data;
	Node* nxt;

	Node(Type x) {
		data = x;
		nxt = nullptr;
	}
};


//template class circular linked type
template<typename Type>
class MyQueue {
	Node<Type>* head, * tail;
	size_t len;
public:
	using node = Node<Type>;

	MyQueue() {
		len = 0;
		head = tail = nullptr;
	}

	void push_back(Type x) {
		if (head == nullptr) {
			head = new node(x);
			tail = head;
			head->nxt = head;
		} else {
			auto tmp = new node(x);
			tmp->nxt = tail->nxt;
			tail->nxt = tmp;
			tail = tmp;
		}
	}

	void pop_front() {
		if (head == head->nxt) {
			delete head;
			head = tail = nullptr;
		} else {
			auto del = head;
			head = head->nxt;
			tail->nxt = head;
			delete del;
		}
	}

	Type front() {
		return head->data;
	}

	size_t size() const {
		return len;
	}

	bool empty() const {
		return head == nullptr;
	}

	~MyQueue() {
		if (!empty()) {
			while (head->nxt != head) {
				auto nxt = head->nxt;
				head->nxt = nxt->nxt;
				delete nxt;
			}
			delete head;
		}
	}

	MyQueue(const MyQueue& rhs) = delete;

	MyQueue& operator =(const MyQueue& rhs) = delete;

};

int main() {
	int m, n;
	std::cin >> m >> n;
	MyQueue<std::pair<int, int>> lst;
	for (int i = 1; i <= n; ++i) {
		int cur;
		std::cin >> cur;
		lst.push_back({i, cur});
	}
	int number = 1;//报数报到第几号了
	while (!lst.empty()) {
		if (number != m) {
			auto alive = lst.front();
			lst.push_back(alive);//没死，出队并排到队尾
			lst.pop_front();
			number++;
		} else {
			auto alive = lst.front();
			lst.pop_front();//死了，出队
			std::cout << alive.first << ' ';//输出编号
			m = alive.second;//m改变
			number = 1;//重新计数
		}
	}
}