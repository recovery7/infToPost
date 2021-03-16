#include <iostream>
#include <string>
using namespace std;

struct Node {
	char data;
	Node* next;
};

Node* current = nullptr;
Node* addToStack(Node* current, char data, bool* isEmpty);
Node* delFromStack(Node* current, bool* isEmpty);
int findFinal(Node* findFinal);
string infToPost(string str);

int main() {
	setlocale(LC_ALL, "ru");
	bool isEmpty = true;
	cout << "¬ведите строку:   ";
	string str;
	cin >> str;
	string result = infToPost(str);
	cout << "–езультат:   " << result;
	return 0;
}

Node* addToStack(Node* current, char data, bool* isEmpty) {
	Node* new_data = new Node;
	Node* front = current;
	new_data->data = data;
	new_data->next = nullptr;

	if (*isEmpty == true) {
		*isEmpty = false;
		return new_data;
	}
	else {
		if (current->next == nullptr) {
			current->next = new_data;
			return front;
		}
		while (current->next != nullptr) {
			if (current->next == nullptr) {
				break;
			}
			current = current->next;
		}
		current->next = new_data;
		return front;
	}
}

Node* delFromStack(Node* current, bool* isEmpty) {
	Node* front = current;
	Node* beforeFinal = current;

	if (current->next == nullptr) {
		*isEmpty = true;
		delete current;
		return front;
	}

	while (beforeFinal->next->next != nullptr) {
		beforeFinal = beforeFinal->next;
		current = current->next;
	}

	current = current->next;
	delete current;
	beforeFinal->next = nullptr;
	return front;
}

int findFinal(Node* current) {
	Node* front = current;
	while (front->next != nullptr) {
		front = front->next;
	}
	return front->data;
}

string infToPost(string str) {
	string result;
	Node* current = new Node;
	bool isEmpty = true, negativeElement = false;
	int i = 0, x = 0, step = 0;

	while (str[i] != '\0') {
		switch (str[i]) {
		case '+': {
			if (isEmpty == true) {
				current = addToStack(current, str[i], &isEmpty);
			}
			else {
				if (findFinal(current) == '-' || findFinal(current) == '*' || findFinal(current) == '/') {
					result += findFinal(current);
					current = delFromStack(current, &isEmpty);
					current = addToStack(current, str[i], &isEmpty);
				}
				else {
					current = addToStack(current, str[i], &isEmpty);
				}
			}
		} break;

		case '-': {
			if (isEmpty == true) {
				if (str[0] == '-' && negativeElement == false) {
					negativeElement = true;
					current = addToStack(current, str[0], &isEmpty);
					result += '0';
				}
				else {
					current = addToStack(current, str[i], &isEmpty);
				}
			}
			else {
				if (str[i - 1] == '(') {
					result += '0';
				}
				if (findFinal(current) == '+' || findFinal(current) == '*' || findFinal(current) == '/') {
					result += findFinal(current);
					current = delFromStack(current, &isEmpty);
					current = addToStack(current, str[i], &isEmpty);
				}
				else {
					current = addToStack(current, str[i], &isEmpty);
				}
			}

		}break;

		case '/': {
			if (isEmpty == true) {
				current = addToStack(current, str[i], &isEmpty);
			}
			else {
				if (findFinal(current) == '*' || findFinal(current) == '/') {
					result += findFinal(current);
					current = delFromStack(current, &isEmpty);
					current = addToStack(current, str[i], &isEmpty);
				}
				else {
					current = addToStack(current, str[i], &isEmpty);
				}
			}
		}break;

		case '*': {
			if (isEmpty == true) {
				current = addToStack(current, str[i], &isEmpty);
			}
			else {
				if (findFinal(current) == '*' || findFinal(current) == '/') {
					result += findFinal(current);
					current = delFromStack(current, &isEmpty);
					current = addToStack(current, str[i], &isEmpty);
				}
				else {
					current = addToStack(current, str[i], &isEmpty);
				}
			}
		}break;

		case '(': {
			if (isEmpty == true) {
				current = addToStack(current, str[i], &isEmpty);
			}
			else {
				current = addToStack(current, str[i], &isEmpty);
			}
		}break;

		case ')': {
			while (findFinal(current) != '(') {
				result += findFinal(current);
				current = delFromStack(current, &isEmpty);
			}
			current = delFromStack(current, &isEmpty);
		}break;

		default: {
			if (str[i] >= '0' && str[i] <= '9') {
				result += str[i];
			}
			if (str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '(' || str[i + 1] == ')') {
				result += ' ';
			}
		}break;
		}
		i++;
	}

	while (isEmpty == false) {
		result += findFinal(current);
		current = delFromStack(current, &isEmpty);
	}

	result += ' ';

	return result;
}