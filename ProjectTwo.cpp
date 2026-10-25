//============================================================================
// Name        : ProjectTwo.cpp
// Author      : William Burns
// Version     : 1.0
// Description : CS 300 Project Two - Advising Assistance Program
//============================================================================

#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Remove leading and trailing whitespace from a string
string trim(string text) {
	size_t first = text.find_first_not_of(" \t\r\n");

	if (first == string::npos) {
		return "";
	}

	size_t last = text.find_last_not_of(" \t\r\n");

	return text.substr(first, last - first + 1);
}

// Structure used to store course information
struct Course {
	string courseNumber;
	string courseName;
	vector<string> prerequisites;
};

// Node used by the binary search tree
struct Node {
	Course course;
	Node *left;
	Node *right;

	Node(Course aCourse) {
		course = aCourse;
		left = nullptr;
		right = nullptr;
	}
};

class BinarySearchTree {
private:
	Node *root;

	void inOrder(Node *node);

	void destroyTree(Node *node);

public:
	BinarySearchTree();

	void insert(Course course);
	Course *search(string courseNumber);
	void printCourseList();
	~BinarySearchTree();
};

BinarySearchTree::BinarySearchTree() { root = nullptr; }

void BinarySearchTree::insert(Course course) {
	Node *newNode = new Node(course);

	// If the tree is empty, the new node becomes the root
	if (root == nullptr) {
		root = newNode;
		return;
	}

	Node *currentNode = root;

	while (true) {
		// Insert smaller course numbers into the left subtree
		if (course.courseNumber < currentNode->course.courseNumber) {
			if (currentNode->left == nullptr) {
				currentNode->left = newNode;
				return;
			}

			currentNode = currentNode->left;
		}

		// Insert larger course numbers into the right subtree
		else {
			if (currentNode->right == nullptr) {
				currentNode->right = newNode;
				return;
			}

			currentNode = currentNode->right;
		}
	}
}

Course *BinarySearchTree::search(string courseNumber) {
	Node *currentNode = root;

	while (currentNode != nullptr) {
		if (courseNumber == currentNode->course.courseNumber) {
			return &(currentNode->course);
		} else if (courseNumber < currentNode->course.courseNumber) {
			currentNode = currentNode->left;
		} else {
			currentNode = currentNode->right;
		}
	}

	return nullptr;
}

void BinarySearchTree::inOrder(Node *node) {
	if (node != nullptr) {
		inOrder(node->left);

		cout << node->course.courseNumber << ", " << node->course.courseName
			 << endl;

		inOrder(node->right);
	}
}

void BinarySearchTree::printCourseList() { inOrder(root); }

void BinarySearchTree::destroyTree(Node *node) {
	if (node != nullptr) {
		destroyTree(node->left);
		destroyTree(node->right);
		delete node;
	}
}

BinarySearchTree::~BinarySearchTree() { destroyTree(root); }

bool loadCourses(string fileName, BinarySearchTree &courseTree) {
	ifstream file(fileName);

	if (!file.is_open()) {
		cout << "Error: Unable to open course data file." << endl;
		return false;
	}

	vector<Course> courseRecords;
	string line;

	// Read each course record from the file
	while (getline(file, line)) {
		stringstream lineStream(line);
		vector<string> fields;
		string field;

		while (getline(lineStream, field, ',')) {
			fields.push_back(trim(field));
		}

		// Every record must contain at least a course number and name
		if (fields.size() < 2) {
			cout << "Error: Each line must contain a course number and course "
					"name."
				 << endl;
			file.close();
			return false;
		}

		if (fields[0].empty() || fields[1].empty()) {
			cout << "Error: Course number and course name cannot be empty."
				 << endl;
			file.close();
			return false;
		}

		Course currentCourse;
		currentCourse.courseNumber = fields[0];
		currentCourse.courseName = fields[1];

		// Any remaining nonempty fields are prerequisites
		for (size_t i = 2; i < fields.size(); ++i) {
			if (!fields[i].empty()) {
				currentCourse.prerequisites.push_back(fields[i]);
			}
		}

		courseRecords.push_back(currentCourse);
	}

	file.close();

	// Validate that every prerequisite exists in the course data
	for (const Course &course : courseRecords) {
		for (const string &prerequisite : course.prerequisites) {
			bool prerequisiteExists = false;

			for (const Course &possibleCourse : courseRecords) {
				if (possibleCourse.courseNumber == prerequisite) {
					prerequisiteExists = true;
					break;
				}
			}

			if (!prerequisiteExists) {
				cout << "Error: Prerequisite " << prerequisite
					 << " does not exist as a course in the file." << endl;
				return false;
			}
		}
	}

	// Insert validated courses into the binary search tree
	for (const Course &course : courseRecords) {
		courseTree.insert(course);
	}

	return true;
}

string toUpper(string text) {
	for (char &character : text) {
		character =
			static_cast<char>(toupper(static_cast<unsigned char>(character)));
	}

	return text;
}

void printCourseInformation(BinarySearchTree &courseTree, string courseNumber) {
	courseNumber = toUpper(trim(courseNumber));

	Course *course = courseTree.search(courseNumber);

	if (course == nullptr) {
		cout << "Course not found." << endl;
		return;
	}

	cout << course->courseNumber << ", " << course->courseName << endl;

	cout << "Prerequisites: ";

	if (course->prerequisites.empty()) {
		cout << "None";
	} else {
		for (size_t i = 0; i < course->prerequisites.size(); ++i) {
			string prerequisiteNumber = course->prerequisites[i];

			Course *prerequisiteCourse = courseTree.search(prerequisiteNumber);

			if (prerequisiteCourse != nullptr) {
				cout << prerequisiteCourse->courseNumber << ", "
					 << prerequisiteCourse->courseName;
			} else {
				cout << prerequisiteNumber;
			}

			if (i < course->prerequisites.size() - 1) {
				cout << "; ";
			}
		}
	}

	cout << endl;
}

int main() {
	BinarySearchTree courseTree;
	bool coursesLoaded = false;
	int choice = 0;

	cout << "Welcome to the course planner." << endl;

	while (choice != 9) {
		cout << endl;
		cout << "1. Load Data Structure." << endl;
		cout << "2. Print Course List." << endl;
		cout << "3. Print Course." << endl;
		cout << "9. Exit" << endl;
		cout << endl;
		cout << "What would you like to do? ";

		// Validate that the menu input is a number
		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Invalid menu option." << endl;
			continue;
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (choice) {
		case 1: {
			if (coursesLoaded) {
				cout << "Course data has already been loaded." << endl;
				break;
			}

			string fileName;

			cout << "Enter the course data file name: ";
			getline(cin, fileName);

			if (loadCourses(fileName, courseTree)) {
				coursesLoaded = true;
				cout << "Course data loaded successfully." << endl;
			}

			break;
		}

		case 2:
			if (!coursesLoaded) {
				cout << "Please load course data first." << endl;
			} else {
				cout << "Here is a sample schedule:" << endl;
				courseTree.printCourseList();
			}

			break;

		case 3: {
			if (!coursesLoaded) {
				cout << "Please load course data first." << endl;
			} else {
				string courseNumber;

				cout << "What course do you want to know about? ";
				getline(cin, courseNumber);

				printCourseInformation(courseTree, courseNumber);
			}

			break;
		}

		case 9:
			cout << "Thank you for using the course planner!" << endl;
			break;

		default:
			cout << choice << " is not a valid option." << endl;
			break;
		}
	}

	return 0;
}