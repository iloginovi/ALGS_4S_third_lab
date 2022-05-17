#ifndef MAP_H
#define MAP_H

#include <iostream>
#include "string"
#include "stack.h"
#include "list.h"
#include "pair.h"



template <typename first_typename, typename second_typename>

// class CustomMap based on RBTree
class Map {
private:

	// class Node for RBTree element storage
	class Node {
	public:
		first_typename key; // holds the key
		second_typename value; // holds the value
		Node* parent; // pointer to the parent
		Node* left; // pointer to left child
		Node* right; // pointer to right child
		int color; // 0 is Black, 1 is Red

		Node() {
			color = 0;
			left = nullptr;
			right = nullptr;
		}

		Node(first_typename outside_key, second_typename outside_value) {
			parent = nullptr;
			key = outside_key;
			value = outside_value;
			color = 1; // inserting node must be red
		}
	};

	Node* root;  // pointer to the root of RBTree
	Node* Nil; // pointer to the NULL

	// move moving_node to the host_node place
	void moving(Node* host_node, Node* moving_node) {
		if (host_node->parent == nullptr) {
			root = moving_node;
		}
		else if (host_node == host_node->parent->left) {
			host_node->parent->left = moving_node;
		}
		else {
			host_node->parent->right = moving_node;
		}
		moving_node->parent = host_node->parent;
	}

	// left-rotation at node current_node
	void left_rotate(Node* current_node) {
		Node* right_child = current_node->right;
		current_node->right = right_child->left;
		if (right_child->left != Nil) {
			right_child->left->parent = current_node;
		}
		right_child->parent = current_node->parent;
		if (current_node->parent == nullptr) {
			root = right_child;
		}
		else if (current_node == current_node->parent->left) {
			current_node->parent->left = right_child;
		}
		else {
			current_node->parent->right = right_child;
		}
		right_child->left = current_node;
		current_node->parent = right_child;
	}

	// right-rotation at node current_node
	void right_rotate(Node* current_node) {
		Node* left_child = current_node->left;
		current_node->left = left_child->right;
		if (left_child->right != Nil) {
			left_child->right->parent = current_node;
		}
		left_child->parent = current_node->parent;
		if (current_node->parent == nullptr) {
			root = left_child;
		}
		else if (current_node == current_node->parent->right) {
			current_node->parent->right = left_child;
		}
		else {
			current_node->parent->left = left_child;
		}
		left_child->right = current_node;
		current_node->parent = left_child;
	}

	// fix the RBTree modified by the insert operation
	void fix_after_insert(Node* x) {
		Node* uncle;
		while (x->parent->color == 1) {
			if (x->parent == x->parent->parent->right) {
				uncle = x->parent->parent->left;
				if (uncle->color == 1) {
					// parent becomes black, uncle becomes black, grandparent becomes red
					uncle->color = 0;
					x->parent->color = 0;
					x->parent->parent->color = 1;
					x = x->parent->parent;
				}
				else {
					if (x == x->parent->left) {
						// do the right-rotation at parent of current_node
						x = x->parent;
						right_rotate(x);
					}
					x->parent->color = 0; // parent becomes black
					x->parent->parent->color = 1; // grandparent becomes red
					left_rotate(x->parent->parent); // do the left-rotation at grandparent, grandparent becomes brother of current_node
				}
			}
			else {
				uncle = x->parent->parent->right;

				if (uncle->color == 1) {
					// parent becomes black, uncle becomes black, grandparent becomes red
					uncle->color = 0;
					x->parent->color = 0;
					x->parent->parent->color = 1;
					x = x->parent->parent;
				}
				else {
					if (x == x->parent->right) {
						// do the left-rotation at parent of current_node
						x = x->parent;
						left_rotate(x);
					}

					x->parent->color = 0; // parent becomes black
					x->parent->parent->color = 1; // grandparent becomes red
					right_rotate(x->parent->parent); // do the right-rotation at grandparent, grandparent becomes brother of current_node
				}
			}
			if (x == root) {
				break;
			}
		}
		root->color = 0; // root must be black
	}

	// fix the RBTree modified by the remove operation
	void fix_after_remove(Node* x) {
		Node* brother;
		while (x != root && x->color == 0) {
			// if brother is right brother of x
			if (x == x->parent->left) {
				brother = x->parent->right; // brother is right brother of x
				if (brother->color == 1) {
					// if x's brother color is red
					brother->color = 0;
					x->parent->color = 1;
					left_rotate(x->parent);
					brother = x->parent->right;
				}

				if (brother->left->color == 0 && brother->right->color == 0) {
					// if x's brother color is red, and both of xs brother's children are black
					brother->color = 1;
					x = x->parent;
				}
				else {
					if (brother->right->color == 0) {
						// if x's brother color is red, xs brother's right child is black, xs brother's left child is red
						brother->left->color = 0;
						brother->color = 1;
						right_rotate(brother);
						brother = x->parent->right;
					}

					// if x's brother color is black, xs brother's right child is red
					brother->color = x->parent->color;
					x->parent->color = 0;
					brother->right->color = 0;
					left_rotate(x->parent);
					x = root;
				}
			}
			// if brother is left brother of x = mirror of brother is right brother of x
			else {
				brother = x->parent->left; // brother is left brother of x
				if (brother->color == 1) {
					// if x's brother color is red
					brother->color = 0;
					x->parent->color = 1;
					right_rotate(x->parent);
					brother = x->parent->left;
				}

				if (brother->right->color == 0 && brother->left->color == 0) {
					// if x's brother color is red, and both of xs brother's children are black
					brother->color = 1;
					x = x->parent;
				}
				else {
					if (brother->left->color == 0) {
						// if x's brother color is red, xs brother's right child is red, xs brother's left child is black
						brother->right->color = 0;
						brother->color = 1;
						left_rotate(brother);
						brother = x->parent->left;
					}

					// if x's brother color is black, xs brother's left child is red
					brother->color = x->parent->color;
					x->parent->color = 0;
					brother->left->color = 0;
					right_rotate(x->parent);
					x = root;
				}
			}
		}
		x->color = 0; // root must be black
	}

	//algorithm part of find operation
	Node* find_algorithm(Node* current_node, first_typename key) {
		if (key == current_node->key) {
			return current_node;
		}

		// check that tree contains the node with looking for key
		if (current_node == Nil) {
			throw out_of_range("Couldn't find key in the RBTree");
		}

		if (key < current_node->key) {
			return find_algorithm(current_node->left, key);
		}
		return find_algorithm(current_node->right, key);
	}

	//algorithm part of contains operation
	bool contains_algorithm(Node* current_node, first_typename key) {
		if (key == current_node->key) {
			return true;
		}

		if (current_node == Nil) {
			return false;
		}

		if (key < current_node->key) {
			return contains_algorithm(current_node->left, key);
		}
		return contains_algorithm(current_node->right, key);
	}

	// record RBTree keys in stack to clear the RBTree
	void RBTree_to_stack(Node* node, Stack<first_typename>& MyStack) {
		if (node != Nil) {
			MyStack.push(node->key);
			RBTree_to_stack(node->left, MyStack);
			RBTree_to_stack(node->right, MyStack);
		}
	}

	//algorithm part of get keys operation
	void get_keys_algorithm(Node* node, List<first_typename>& MyLinked_list) {
		if (node != Nil) {
			MyLinked_list.insert_node(node->key);
			get_keys_algorithm(node->left, MyLinked_list);
			get_keys_algorithm(node->right, MyLinked_list);
		}
	}

	//algorithm part of get values operation
	void get_values_algorithm(Node* node, List<second_typename>& MyLinked_list) {
		if (node != Nil) {
			MyLinked_list.insert_node(node->value);
			get_values_algorithm(node->left, MyLinked_list);
			get_values_algorithm(node->right, MyLinked_list);
		}
	}

	// helper method to print the RBTree
	void print_with_indent(Node* node, int level = 0)
	{
		if (node != Nil)
		{
			print_with_indent(node->left, level + 1);
			for (int i = 0; i < level; i++) cout << "   ";
			cout << setw(3) << node->key;
			if (node->color == 0) { cout << " (Black)" << '\n'; }
			else { cout << " (Red)" << '\n'; }
			print_with_indent(node->right, level + 1);
		}
	}

public:
	// CustomMap class Constructor 
	Map() {
		Nil = new Node;
		/*Nil->color = 0;
		Nil->left = nullptr;
		Nil->right = nullptr;*/
		root = Nil;
	}

	// CustomMap class Destructor 
	~Map() {
		clear();
	}

	// insert the node with user's key and value to the RBTree in its appropriate position and fix the RBTree after insertion
	void insert(first_typename key, second_typename value) {

		Node* inserting_node = new Node(key, value);
		inserting_node->left = Nil;
		inserting_node->right = Nil;

		Node* y = nullptr;
		Node* x = root;

		while (x != Nil) {
			y = x;
			if (inserting_node->key < x->key) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}

		// if y is parent of x
		inserting_node->parent = y;
		if (y == nullptr) {
			root = inserting_node;
		}
		else if (inserting_node->key < y->key) {
			y->left = inserting_node;
		}
		else {
			y->right = inserting_node;
		}

		// if inserting_node is a root node
		if (inserting_node->parent == nullptr) {
			inserting_node->color = 0;
			return;
		}

		// if the grandparent is null
		if (inserting_node->parent->parent == nullptr) {
			return;
		}

		// fix the tree
		fix_after_insert(inserting_node);
	}

	// remove the node with user's key from the RBTree and fix the RBTree after deletion
	void remove(first_typename key) {
		Node* node_to_be_deleted = Nil;
		Node* x;
		Node* y;

		// finding the node with looking for key
		node_to_be_deleted = find(key);

		y = node_to_be_deleted;
		int y_original_color = y->color; // save the node_to_be_deleted color
		if (node_to_be_deleted->left == Nil) {
			x = node_to_be_deleted->right;
			moving(node_to_be_deleted, node_to_be_deleted->right); // move x to the node_to_be_deleted place
		}
		else if (node_to_be_deleted->right == Nil) {
			x = node_to_be_deleted->left;
			moving(node_to_be_deleted, node_to_be_deleted->left); // move x to the node_to_be_deleted place
		}
		else {
			// y becomes the minimum key in node_to_be_deleted right subtree
			y = node_to_be_deleted->right;
			while (y->left != Nil) {
				y = y->left;
			}
			// save the y color
			y_original_color = y->color;
			x = y->right;
			if (y->parent == node_to_be_deleted) {
				x->parent = y;
			}
			else {
				moving(y, y->right); // move y right child to the y place
				y->right = node_to_be_deleted->right;
				y->right->parent = y;
			}

			moving(node_to_be_deleted, y); // move y to the node_to_be_deleted place
			y->left = node_to_be_deleted->left;
			y->left->parent = y;
			y->color = node_to_be_deleted->color;
		}
		delete node_to_be_deleted;

		// if y_original_color is black
		if (y_original_color == 0) {
			fix_after_remove(x);
		}
	}

	// search the node with user's key
	Node* find(first_typename key) {
		return find_algorithm(root, key);
	}

	// clear the RBTree by remove nodes step be step
	void clear() {
		Stack<first_typename> MyStack;
		RBTree_to_stack(root, MyStack);
		while (MyStack.size()) {
			remove(MyStack.top());
			MyStack.pop();
		}
	}

	// return the list of RBTree keys
	List<first_typename> get_keys() {
		List<first_typename> MyLinked_list;
		get_keys_algorithm(root, MyLinked_list);
		return MyLinked_list;
	}

	// return the list of RBTree values
	List<second_typename> get_values() {
		List<second_typename> MyLinked_list;
		get_values_algorithm(root, MyLinked_list);
		return MyLinked_list;
	}

	// print the RBTree on the screen
	void print() {
		return print_with_indent(root);
	}

	bool contains(first_typename key) {
		return contains_algorithm(root, key);
	}
};
#endif