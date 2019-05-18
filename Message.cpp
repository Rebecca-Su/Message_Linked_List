//============================================================================
// Name        : Message.cpp
// Author      : Rebecca Su
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Message.h"

#ifndef MARMOSET_TESTING
int main();
#endif

#ifndef MARMOSET_TESTING
int main()
{
	Message message_1;
	int input{0};
	std::string frag;

	while(input != -2)
	{
		std::cin >> input;

		if(input == -2)
			return 0;
		else if(input == -1)
			message_1.print_message();
		else
		{
			std::cin >> frag;
			message_1.insert(input, frag);
		}
	}

	return 0;
}
#endif

Node::Node(unsigned int id, std::string frag)
{
	identifier = id;
	fragment = frag;
	p_next = nullptr;
}

std::string Node::get_fragment()
{
	return fragment;
}

Node *Node::get_next()
{
	return p_next;
}

Message::Message()
{
	head = nullptr;
}

Message::~Message()
{
	Node *current{nullptr};
	Node *traverse{nullptr};

	current = head;
	while(current != nullptr)
	{
		traverse = current->p_next;
		delete current;
		current = traverse;
	}
	delete current;
	current = nullptr;
	delete traverse;
	traverse = nullptr;
}

void Message::insert(unsigned int id, std::string fragment)
{
	Node *traverse{head};
	bool is_here{false};
	Node *new_node{new Node(id, fragment)};

	if(head == nullptr)
		head = new_node;
	else if(new_node -> identifier < traverse -> identifier)
	{
		new_node->p_next = traverse;
		head = new_node;

	}
	else
	{
		while(is_here == false)
		{
			if(traverse->p_next == nullptr || traverse->p_next->identifier > new_node ->identifier)
			{
				new_node->p_next = traverse->p_next;
				traverse->p_next = new_node;
				is_here = true;
			}
			if(is_here == false)
				traverse = traverse -> p_next;
		}
	}
}

void Message::print_message()
{
	Node *traverse{head};
	unsigned int id;
	bool is_end{false};
	bool is_EOT{true};

	if(traverse == nullptr)
		std::cout << "???";
	else if(traverse->p_next == nullptr)
	{
		if(traverse->identifier != 0)
		{
			for(int k = 0; k < traverse->identifier - 1; k++)
				std::cout << "... ";
		}

		if(traverse->fragment == "EOT" && traverse->identifier != 0)
			std::cout << "...";
		else if(traverse->fragment != "EOT")
			std::cout << "... " << traverse->fragment << " ???";
	}
	else
	{
		while(is_end == false)
		{
			if(traverse->p_next == nullptr)
			{
				id = traverse->identifier;
				if(traverse->fragment != "EOT")
					is_EOT = false;
				is_end = true;
			}
			else
				traverse = traverse->p_next;
		}

		traverse = head;

		for(int k = 0; k < id - 1; k++)
		{
			if(traverse->identifier != k)
				std::cout << "... ";
			else if(traverse->identifier == k)
			{
				std::cout << traverse->fragment << " ";
				traverse = traverse->p_next;
			}
		}

		if(traverse->identifier != id - 1)
			std::cout << "...";
		else if(traverse->identifier == id - 1)
			std::cout << traverse->fragment;

		if(is_EOT == false)
			std::cout << " ???";
	}
	std::cout << std::endl;
}
