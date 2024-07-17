#include <bits/stdc++.h>


using namespace std;

// Define Student class
class Student {
public:
    string name;
    int id_no;
    string Stream;
    string book1, book2;
    int book_no;

    // Constructor
    Student(string name, int id_no, string Stream) {
        this->name = name;
        this->id_no = id_no;
        this->Stream = Stream;
        this->book1 = "";
        this->book2 = "";
        this->book_no = 0;
    }
};

// Define Node class for BST
class Node {
public:
    string key;
    Node* left;
    Node* right;

    // Constructor
    Node(string item) {
        key = item;
        left = right = nullptr;
    }
};

// Define Library Management System class
class LibraryManagement {
private:
    Node* root;
    // Initialize student details
    Student* students[3] = {
        new Student("Krrish", 220551, "B.Tech-ICT"),
        new Student("Himanshu", 220452, "B.Tech-ICT"),
        new Student("Vansh", 221187, "B.Tech-ICT")
    };

public:
    map<string, int> hashmapping;
    int arr[100][2]; // Assuming maximum 100 different books

    LibraryManagement() {
        root = nullptr;
    }

    // Insert book into BST
    void insert(string key) {
        root = insertRec(root, key);
    }

    Node* insertRec(Node* root, string key) {
        if (root == nullptr) {
            root = new Node(key);
            return root;
        }

        if (key < root->key)
            root->left = insertRec(root->left, key);
        else if (key > root->key)
            root->right = insertRec(root->right, key);
        else
            cout << "Error." << endl;

        return root;
    }

    // Check if book exists in BST
    bool containsNode(string key) {
        return containsNodeRecursive(root, key);
    }

    bool containsNodeRecursive(Node* current, string key) {
        if (current == nullptr)
            return false;

        if (key == current->key)
            return true;

        return key < current->key
            ? containsNodeRecursive(current->left, key)
            : containsNodeRecursive(current->right, key);
    }

    // Print tree in-order
    void printInorder(Node* node) {
        if (node == nullptr)
            return;

        printInorder(node->left);
        cout << node->key << "    ";
        printInorder(node->right);
    }

    void printInorder() {
        printInorder(root);
    }

    // Issue book to student
    void issueBook(int student_id, string book_name) {
        int index = -1;
        for (int i = 0; i < 3; ++i) {
            if (students[i]->id_no == student_id) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            if (students[index]->book_no == 2) {
                cout << "You can't issue more than two books." << endl;
            }
            else {
                if (containsNode(book_name)) {
                    int book_index = hashmapping[book_name];
                    if (arr[book_index][1] > 0) {
                        if (students[index]->book1.empty())
                            students[index]->book1 = book_name;
                        else
                            students[index]->book2 = book_name;

                        cout << "Book issued successfully." << endl;
                        arr[book_index][1]--;
                        time_t now = time(0);
                        tm* current_time = localtime(&now);
                        cout << "Current Date Time: " << put_time(current_time, "%d/%m/%Y %H:%M:%S") << endl;

                        tm* return_time = localtime(&now);
                        return_time->tm_sec += 5;
                        cout << "Due Date Time: " << put_time(return_time, "%d/%m/%Y %H:%M:%S") << endl;

                        ofstream file("append.txt", ios::app);
                        file << "\nStudent name:   " << students[index]->name << endl;
                        file << "Student ID:     " << students[index]->id_no << endl;
                        file << "Issued Book:    " << book_name << endl;
                        file << "Issued date:    " << put_time(current_time, "%d/%m/%Y %H:%M:%S") << endl;
                        file << "Return date:    " << put_time(return_time, "%d/%m/%Y %H:%M:%S") << endl;
                        file.close();

                        students[index]->book_no++;
                    }
                    else {
                        cout << "You cannot issue the book now. Try again later." << endl;
                    }
                }
                else {
                    cout << "Book is not available." << endl;
                }
            }
        }
        else {
            cout << "Invalid ID." << endl;
        }
    }

    // Return book from student
    void returnBook(int student_id, string book_name) {
        int index = -1;
        for (int i = 0; i < 3; ++i) {
            if (students[i]->id_no == student_id && (students[i]->book1 == book_name || students[i]->book2 == book_name)) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            if (containsNode(book_name)) {
                if (students[index]->book1 == book_name)
                    students[index]->book1 = "";
                else
                    students[index]->book2 = "";

                time_t now = time(0);
                tm* return_time = localtime(&now);
                cout << "Book returned successfully." << endl;

                if (difftime(mktime(return_time), mktime(return_time)) > 0) {
                    cout << "Book is overdue." << endl;
                    int noofdays = difftime(mktime(return_time), mktime(return_time));
                    cout << "Due Date Time: " << put_time(return_time, "%d/%m/%Y %H:%M:%S") << endl;
                    cout << "Book is delayed by " << noofdays << " seconds." << endl;
                    double charge = noofdays * 5;
                    cout << "Your charge is: " << charge << " Rs." << endl;
                }

                int book_index = hashmapping[book_name];
                arr[book_index][1]++;
                students[index]->book_no--;
            }
        }
        else {
            cout << "Invalid ID." << endl;
        }
    }
};

int main() {
    LibraryManagement library;

    int choice1, choice2;
    bool exit1 = false;

    while (!exit1) {
        cout << "\n....................................." << endl;
        cout << "1. Librarian Login" << endl;
        cout << "2. User Login" << endl;
        cout << "3. Exit" << endl;
        cout << "\n....................................." << endl;
        cout << "Enter Your choice: ";
        cin >> choice1;

        switch (choice1) {
        case 1: // Librarian Login
            {
                string id1 = "purav@12";
                string pwd1 = "qwer1234";

                cout << "\nEnter UserId: ";
                string id2;
                cin >> id2;

                cout << "Enter Password: ";
                string pwd2;
                cin >> pwd2;

                if (id1 != id2)
                    cout << "Invalid Userid." << endl;
                else if (pwd1 != pwd2)
                    cout << "Invalid Password." << endl;
                else {
                    cout << "Login successfully." << endl;
                    bool exit2 = false;

                    while (!exit2) {
                        cout << "\n....................................." << endl;
                        cout << "1. Add book" << endl;
                        cout << "2. Delete book" << endl;
                        cout << "3. Update book" << endl;
                        cout << "4. Print Books Details" << endl;
                        cout << "5. Print Books In-order" << endl;
                        cout << "6. Exit" << endl;
                        cout << "\n....................................." << endl;
                        cout << "Enter Your choice: ";
                        cin >> choice2;

                        switch (choice2) {
                        case 1: // Add book
                            {
                                ifstream file("x.txt");
                                ifstream file2("y.txt");
                                ifstream file3("z.txt");
                                string line;
                                int i = 0;

                                while (getline(file, line)) {
                                    library.insert(line);
                                    library.hashmapping[line] = i;
                                    i++;
                                }

                                int j = i;
                                int o = 0;
                                string number;

                                while (getline(file2, number)) {
                                    int result = stoi(number);
                                    if (j != o)
                                        library.arr[o][0] = result;
                                    o++;
                                }

                                int pq = 0;
                                string number1;

                                while (getline(file3, number1)) {
                                    int result1 = stoi(number1);
                                    if (j != pq)
                                        library.arr[pq][1] = result1;
                                    pq++;
                                }
                            }
                            break;
                        case 2:
                            // Delete book logic here
                            break;
                        case 3:
                            // Update book logic here
                            break;
                        case 4:
                            // Print Books Details logic here
                            break;
                        case 5:
                            library.printInorder();
                            break;
                        case 6:
                            exit2 = true;
                            break;
                        default:
                            cout << "Invalid choice." << endl;
                        }
                    }
                }
            }
            break;
        case 2: // User Login
            {
                int student_id;
                cout << "Enter Student ID: ";
                cin >> student_id;

                cout << "\n....................................." << endl;
                cout << "1. Issue book" << endl;
                cout << "2. Return book" << endl;
                cout << "3. Exit" << endl;
                cout << "\n....................................." << endl;
                cout << "Enter Your choice: ";
                cin >> choice2;

                switch (choice2) {
                case 1:
                    {
                        string book_name;
                        cout << "Enter Book Name: ";
                        cin >> book_name;
                        library.issueBook(student_id, book_name);
                    }
                    break;
                case 2:
                    {
                        string book_name;
                        cout << "Enter Book Name: ";
                        cin >> book_name;
                        library.returnBook(student_id, book_name);
                    }
                    break;
                case 3:
                    break;
                default:
                    cout << "Invalid choice." << endl;
                }
            }
            break;
        case 3:
            exit1 = true;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
