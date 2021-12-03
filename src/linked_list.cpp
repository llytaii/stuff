#include <array>
#include <iostream>
#include <vector>

// implement reverseList(Element* _head) to reverse a linked list

struct Element
{
	Element* next{ nullptr };
	int n{ 0 };
};

void printList(Element* _head)
{
	while (_head != nullptr)
	{
		std::cout << _head->n << ' ';
		_head = _head->next;
	}
	std::cout << std::endl;
}

void reverseListRec(Element* _head)
{
	auto reverse = [&](auto&& reverse, Element* _head) {
		if (_head->next == nullptr)
			return;
		else if (_head->next->next == nullptr)
			_head->next->next = _head;
		else
		{
			reverse(reverse, _head->next);
			_head->next->next = _head;
		}
	};
	reverse(reverse, _head);
	_head->next = nullptr;
}

void reverseListIt(Element* _head)
{
	std::vector<Element*> ptrs;
	Element* tmp{ _head };
	while (tmp != nullptr)
	{

	}
}

int main()
{
	std::array<Element, 10> list; // create
	for (size_t i{ 0 }; i < list.size() - 1; ++i) // connect
		list[i].next = &list[i + 1];
	for (size_t i{ 0 }; i < list.size(); ++i) // set n
		list[i].n = i;
	printList(&list[0]);
	reverseListRec(&list[0]);
	printList(&list[list.size() - 1]);
}