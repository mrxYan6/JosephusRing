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


//基于单向循环链表实现的队列
template<typename Type>
class MyQueue {
	Node<Type>* head, * tail;
public:
	using node = Node<Type>;

	MyQueue() {
		head = tail = nullptr;
	}

	//插入队尾
	void push(Type x) {
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

	void pop() {
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
		lst.push({i, cur});
	}

	int number = 1;//报数报到第几号了
	while (!lst.empty()) {
		if (number != m) {
			//没死，出队并排到队尾
			auto alive = lst.front();
			lst.push(alive);
			lst.pop();
			number++;
		} else {
			//死了，出队
			auto died = lst.front();
			lst.pop();
			std::cout << died.first << ' ';//输出编号
			m = died.second;//m改变
			number = 1;//重新计数
		}
	}
}