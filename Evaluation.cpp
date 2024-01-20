#include <iostream>
#include <string>
#include <sstream>
#include <cmath>


struct Node {
    std::string data;
    Node* next;
};



class Stack {
public:
    Node* top;
    Stack() : top(nullptr) {}

    // Copy constructor
    Stack(const Stack& other) : top(nullptr) {
        Node* temp = other.top;
        Stack reverse;
        while (temp) {
            reverse.push(temp->data);
            temp = temp->next;
        }
        temp = reverse.top;
        while (temp) {
            this->push(temp->data);
            temp = temp->next;
        }
    }

    void push(std::string data) {
        Node* node = new Node();
        node->data = data;
        node->next = top;
        top = node;
    }

    void pop() {
        if (top) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    std::string peek() {
        if (top) return top->data;
        else return "";
    }

    bool isEmpty() {
        return top == nullptr;
    }
};



class Queue {
public:
    Node *front, *rear;
    Queue() : front(nullptr), rear(nullptr) {}

    
    // Copy constructor
    Queue(const Queue& other) : front(nullptr), rear(nullptr) {
        Node* temp = other.front;
        while (temp) {
            this->enqueue(temp->data);
            temp = temp->next;
        }
    }

	void enqueue(std::string data) {
        Node* node = new Node();
        node->data = data;
        node->next = nullptr;

        if (rear) rear->next = node;
        rear = node;
        if (!front) front = rear;
    }

    void dequeue() {
        if (front) {
            Node* temp = front;
            front = front->next;
            if (!front) rear = nullptr;
            delete temp;
        }
    }

    std::string peek() {
        if (front) return front->data;
        else return "";
    }

    bool isEmpty() {
        return front == nullptr;
    }
};


// define our functinos
std::string my_eval(Stack& s) {
	Stack result;

	
	// processing (sin and cos) operation ----------------
    while (!s.isEmpty()) {
		if (s.peek() == "sin") { 
			float a = std::stof(result.peek()) * 3.14159 / 180;
			result.pop();
			s.pop(); 
			//float b = std::stof(s.peek()) * 3.14159 / 180; 
			float c = sin(a); 
			result.push(std::to_string(c)); 
		}
		else {
			result.push(s.peek()); 
		}
		s.pop();
    }
	// ----------------------------------------
	
	// processing (sin and cos) operation ----------------
    while (!result.isEmpty()) {
		if (result.peek() == "cos") { 
			//float a = std::stof(s.peek()) * 3.14159 / 180;
			s.pop();
			result.pop(); 
			float b = std::stof(result.peek()) * 3.14159 / 180; 
			float c = cos(b); 
			s.push(std::to_string(c)); 
		}
		else {
			s.push(result.peek()); 
		}
		result.pop();
    }
	// ----------------------------------------
	

	// processing (*) operation ----------------
    while (!s.isEmpty()) {
		if (s.peek() == "*") {
			float a = std::stof(result.peek());
			result.pop(); 
			s.pop(); 
			float b = std::stof(s.peek()); 
			float c = a * b; 
			result.push(std::to_string(c)); 
		}
		else {
			result.push(s.peek()); 
		}
		s.pop();
    }
	// ----------------------------------------
	
	
	// processing (/) operation ----------------
    while (!result.isEmpty()) {
		if (result.peek() == "/") {
			float a = std::stof(s.peek());
			s.pop(); 
			result.pop(); 
			float b = std::stof(result.peek()); 
			float c = a / b; 
			s.push(std::to_string(c)); 
		}
		else {
			s.push(result.peek()); 
		}
		result.pop();
    }
	// ----------------------------------------
	


	// processing (+) operation ----------------
    while (!s.isEmpty()) {
		if (s.peek() == "+") {
			float a = std::stof(result.peek());
			result.pop(); 
			s.pop(); 
			float b = std::stof(s.peek()); 
			float c = a + b; 
			result.push(std::to_string(c)); 
		}
		else {
			result.push(s.peek()); 
		}
		s.pop();
    }
	// ----------------------------------------
	


	// processing (-) operation ----------------
    while (!result.isEmpty()) {
		if (result.peek() == "-") {
			float a = std::stof(s.peek());
			s.pop(); 
			result.pop(); 
			float b = std::stof(result.peek()); 
			float c = a - b; 
			s.push(std::to_string(c)); 
		}
		else {
			s.push(result.peek()); 
		}
		result.pop();
    }
	// ----------------------------------------
	
	

	return s.peek(); 
}



std::string my_eval2(Queue q) {
	Stack s_eval;
	Stack result; 
	Stack result2;
	int my_counter = 10; 
	int my_flag = 0; 

	while (my_counter > 1) {
		my_flag = 0;


		while (!s_eval.isEmpty()) {
			s_eval.pop();
		}
		while (!result.isEmpty()) {
			result.pop();
		}


		while (!q.isEmpty()) {
			s_eval.push(q.peek());
			result.push(q.peek());
			
			if (q.peek() == "("){
				while (!s_eval.isEmpty()) {
					s_eval.pop();
				}
			}
			else if (q.peek() == ")" && my_flag==0) {
				s_eval.pop();
				std::string my_str = my_eval(s_eval); 
				
				while (result.peek() != "(") {
					result.pop(); 
				}
				result.pop(); 
				result.push(my_str);
				my_flag = 1; 
			}
			q.dequeue();
		}
		if (my_flag == 0) {
			std::string my_str2 = my_eval(s_eval); 
			while (!result.isEmpty()) {
				result.pop();
			}
			result.push(my_str2);
		}
		while (!result.isEmpty()) {
			result2.push(result.peek());
			result.pop();
		}
		my_counter = 0; 
		while (!result2.isEmpty()) {
			q.enqueue(result2.peek());
			result2.pop(); 
			my_counter++; 
		}
	}


	return q.peek(); 


}


int main() {
    

	std::cout << "Please enter inupt : .. " << std::endl; 
	std::string str;
    std::getline(std::cin, str);

    //std::stack<std::string> stk;
	Stack s; 
	Queue q; 
    std::string temp;


	// store all elements in our queue and stack
    for (char& c : str) {
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
            if (!temp.empty()) {
                s.push(temp);
				q.enqueue(temp);
                temp.clear();
            }
            s.push(std::string(1, c));
			q.enqueue(std::string(1, c)); 
        } else if (c != ' ') {
            temp += c;
        } else {
            if (!temp.empty()) {
                s.push(temp);
				q.enqueue(temp); 
                temp.clear();
            }
        }
    }
    if (!temp.empty()) {
        s.push(temp);
		q.enqueue(temp); 
    }
	// ==============================================
	

	Stack s2 = s; 
	Queue q2 = q; 


	std::string my_output = my_eval2(q2); 
	std::cout << "output : " << my_output << std::endl; 


    return 0;
}
