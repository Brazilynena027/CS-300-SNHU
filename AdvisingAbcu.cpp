//============================================================================
// Name        : AdvisingAbcu.cpp
// Author      : Danielle Sousa
// Version     :
// Copyright   : 2023
// Description : Hello World in C++, Ansi-style
//============================================================================


	#include <iostream>
	#include <string>
	#include <algorithm>
	#include <vector>
	#include <sstream>
	#include <fstream>

	#include "CSVparser.hpp"


	using namespace std;




	// Creates the Course, with course ID,course name and  prereq.
	struct Course {
	    string courseId;
	    string courseName;
	    vector<string> preReq;
	};


	// Structure for the tree node
	struct Node {
	    Course course;
	    Node* left;
	    Node* right;

	    // constructor
	    Node() {
	        left = nullptr;
	        right = nullptr;
	    }
	    // Initialize with the course
	    Node(Course abcuCourse) : Node() {
	        this->course = abcuCourse;
	    }


	};


	// Define a class containing data members and
	// binary search tree
	class BinarySearchTree {


	private:


	    void Destruct(Node* node);


	public:
	    Node* root;
	    BinarySearchTree();
	    virtual ~BinarySearchTree();
	    void Insert(BinarySearchTree* tree, Node* node);
	    void Search(string courseId);
	    void printCourse(Node* node);
	};


	//  constructor
	BinarySearchTree::BinarySearchTree() {
	    root = nullptr;
	};


	// Destruct
	BinarySearchTree::~BinarySearchTree() {
	    Destruct(root);
	};


	//  Destruct left and right pointer nodes and deletes them
	void BinarySearchTree::Destruct(Node* node) {
	    if (node != nullptr) {
	        Destruct(node->left);
	        node->left = nullptr;
	        Destruct(node->right);
	        node->right = nullptr;
	        delete node;
	    }
	};




	// Search for a course
	void BinarySearchTree::Search(string courseId) {
	    Node* currNode = root;


	    while (currNode != nullptr) {
	        if (currNode->course.courseId == courseId) {
	            // prints course id, name
	            cout << currNode->course.courseId << ", ";
	            cout << currNode->course.courseName;
	            cout << endl;
	            cout << "Prerequisites: ";
	            // prints any prerequisites, followed by , if there are more than 1
	            for (string preRequisite : currNode->course.preReq) {
	                if (preRequisite == currNode->course.preReq.back()) {


	                    cout << preRequisite << endl;
	                }
	                else {
	                    cout << preRequisite << ", ";
	                }
	            }


	            return;
	        }
	        // Searches left pointer if not found
	        else if (courseId < currNode->course.courseId) {


	            if (currNode->left != nullptr) {
	                currNode = currNode->left;
	            }
	        }
	        // searches right pointer if not found
	        else {


	            currNode = currNode->right;
	        }
	    }
	    // Course is not in the list
	    cout << "Course " << courseId << "not found. " << endl;
	    return;
	}


	// Inserts course into a course list
	void BinarySearchTree::Insert(BinarySearchTree* tree, Node* node) {


	    if (tree->root == nullptr) {
	        tree->root = node;
	    }
	    else {
	        Node* curr = tree->root;
	        while (curr != nullptr) {


	            if (node->course.courseId < curr->course.courseId) {
	                if (curr->left == nullptr) {
	                    curr->left = node;
	                    curr = nullptr;
	                }
	                else {
	                    curr = curr->left;
	                }
	            }
	            else {


	                if (curr->right == nullptr) {
	                    curr->right = node;
	                    curr = nullptr;
	                }
	                else {
	                    curr = curr->right;
	                }
	            }


	        }


	    }
	}
	// Prints course list
	void BinarySearchTree::printCourse(Node* node) {


	    // Traverse and print entire tree
	    if (node == nullptr) {
	        return;
	    }


	    //Left node, prints course id, course name, then look at next node
	    printCourse(node->left);
	    cout << node->course.courseId << ", ";
	    cout << node->course.courseName << endl;
	    printCourse(node->right);
	};


	// Loads file and creates course list
	void loadCourse(string filename, BinarySearchTree* bst) {
	    ifstream file(filename);
	    if (file.is_open()) {
	        cout << "File loaded." << endl;


	        int num;
	        string line;
	        string word;


	        while (getline(file, line)) {


	            num = 0;
	            Node* node = new Node();
	            stringstream str(line);


	            while (num < 2) {
	                getline(str, word, ',');
	                if (num == 0) {
	                    node->course.courseId = word;
	                }
	                else {
	                    node->course.courseName = word;
	                }
	                num++;
	            }
	            while (getline(str, word, ',')) {
	                node->course.preReq.push_back(word);
	            }


	            // Inserts node into BST
	            bst->Insert(bst, node);
	        }
	    }
	    // File error if file not found
	    else {
	        cout << "File error, please try again. " << endl;
	        return;
	    }


	}


	// This function displays the programs menu
	void DisMenu() {
	    cout << "1. Load Data Structure" << endl;
	    cout << "2. Print Course List" << endl;
	    cout << "3. Print Course" << endl;
	    cout << "9. Exit" << endl << endl;
	    cout << "What would you like to do? ";
	}


	int main(){


	    BinarySearchTree* bst = new BinarySearchTree();


	    string fin;
	    string courseChoice;


	 int userInput = 0;


	    cout << "Welcome to the course planner." << endl << endl;
	    // Main while loop to keep program open as long as choice is not 9
	    while (userInput != 9) {
	        DisMenu();
	        cin >> userInput;


	        switch (userInput) {
	            // Loads the ABCU_Advising_Program_ Input.csv file
	        case 1:
	            cout << endl;
	            fin = "ABCU_Advising_Program_Input.csv";
	            loadCourse(fin, bst);
	            cout << endl;
	            break;


	            // Prints courses in alphanumeric order
	        case 2:
	            cout << endl;
	            cout << "Here is the schedule: " << endl << endl;
	            // Prints course starting at root
	            bst->printCourse(bst->root);
	            cout << endl;
	            break;


	            //prints course that user chooses with any prerequisites
	        case 3:
	            cout << endl;
	            cout << "What course do you want to know about? ";
	            cin >> courseChoice;
	            cout << endl;


	            std::transform(courseChoice.begin(), courseChoice.end(), courseChoice.begin(), ::toupper);
	            bst->Search(courseChoice);


	            cout << endl;
	            break;


	            // Exit the program
	        case 9:
	            cout << "Thank you for using the course planner!" << endl;
	            break;


	            //statement to let user know choice is not valid.
	        default:
	            cout << userInput << " is not a valid choice." << endl << endl;
	            break;
	        }
	    }
	}
