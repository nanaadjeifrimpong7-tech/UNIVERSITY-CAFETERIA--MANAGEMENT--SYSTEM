#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

// Function to validate integer input
int getInteger(string message) {
    string input;
    int number;
    char extra;

    while (true) {
        cout << message;
        getline(cin, input);

        stringstream ss(input);

        if (ss >> number && !(ss >> extra)) {
            return number;
        }

        cout << "Invalid input! Please enter a number.\n";
    }
}

// Function to validate customer name
string getCustomerName() {
    string name;
    bool valid;

    while (true) {
        cout << "Enter customer name: ";
        getline(cin, name);

        valid = !name.empty();

        for (char ch : name) {
            if (!isalpha(static_cast<unsigned char>(ch)) && ch != ' ') {
                valid = false;
                break;
            }
        }

        // Prevent names containing only spaces
        if (name.find_first_not_of(' ') == string::npos) {
            valid = false;
        }

        if (valid) {
            return name;
        }

        cout << "Invalid name! Please enter letters only.\n";
    }
}

// Structure for an order
struct Order {
    int orderID;
    string customerName;
    string foodName;
    Order* next;
};

// Queue class
class CafeteriaQueue {

private:
    Order* front;
    Order* rear;
    int nextID;

public:

    // Constructor
    CafeteriaQueue() {
        front = NULL;
        rear = NULL;
        nextID = 1;
    }

    // 1. Add Order
    void addOrder() {

        Order* newOrder = new Order;

        newOrder->orderID = nextID++;

        newOrder->customerName = getCustomerName();

        cout << "Enter food ordered: ";
        getline(cin, newOrder->foodName);

        newOrder->next = NULL;

        if (rear == NULL) {
            front = rear = newOrder;
        }
        else {
            rear->next = newOrder;
            rear = newOrder;
        }

        cout << "\nOrder added successfully!";
        cout << "\nOrder ID: " << newOrder->orderID << endl;
    }

    // 2. Process Order
    void processOrder() {

        if (front == NULL) {
            cout << "\nNo orders available to process.\n";
            return;
        }

        Order* temp = front;

        cout << "\nProcessing Order...\n";
        cout << "Order ID: " << temp->orderID << endl;
        cout << "Customer: " << temp->customerName << endl;
        cout << "Food: " << temp->foodName << endl;

        front = front->next;

        if (front == NULL) {
            rear = NULL;
        }

        delete temp;

        cout << "Order processed successfully!\n";
    }

    // 3. Cancel Order
    void cancelOrder() {

        if (front == NULL) {
            cout << "\nNo orders available to cancel.\n";
            return;
        }

        int id = getInteger("Enter Order ID to cancel: ");

        Order* current = front;
        Order* previous = NULL;

        while (current != NULL && current->orderID != id) {
            previous = current;
            current = current->next;
        }

        if (current == NULL) {
            cout << "Order not found!\n";
            return;
        }

        if (previous == NULL) {
            front = current->next;
        }
        else {
            previous->next = current->next;
        }

        if (current == rear) {
            rear = previous;
        }

        delete current;

        cout << "Order cancelled successfully!\n";
    }

    // 4. View Next Order
    void viewNextOrder() {

        if (front == NULL) {
            cout << "\nNo pending orders.\n";
            return;
        }

        cout << "\nNext Order to be Processed\n";
        cout << "Order ID: " << front->orderID << endl;
        cout << "Customer: " << front->customerName << endl;
        cout << "Food: " << front->foodName << endl;
    }

    // 5. Display Pending Orders
    void displayOrders() {

        if (front == NULL) {
            cout << "\nNo pending orders.\n";
            return;
        }

        Order* temp = front;

        cout << "\n===== PENDING ORDERS =====\n";

        while (temp != NULL) {

            cout << "\nOrder ID: " << temp->orderID << endl;
            cout << "Customer: " << temp->customerName << endl;
            cout << "Food: " << temp->foodName << endl;

            temp = temp->next;
        }

        cout << "\n==========================\n";
    }

    // Destructor
    ~CafeteriaQueue() {

        while (front != NULL) {

            Order* temp = front;
            front = front->next;

            delete temp;
        }

        rear = NULL;
    }
};

// Main Function
int main() {

    CafeteriaQueue cafeteria;

    int choice;

    do {

        cout << "\n================================";
        cout << "\n UNIVERSITY CAFETERIA SYSTEM";
        cout << "\n================================";
        cout << "\n1. Add Order";
        cout << "\n2. Process Order";
        cout << "\n3. Cancel Order";
        cout << "\n4. View Next Order";
        cout << "\n5. Display Pending Orders";
        cout << "\n6. Exit";
        cout << "\n================================\n";

        choice = getInteger("Enter your choice: ");

        switch (choice) {

            case 1:
                cafeteria.addOrder();
                break;

            case 2:
                cafeteria.processOrder();
                break;

            case 3:
                cafeteria.cancelOrder();
                break;

            case 4:
                cafeteria.viewNextOrder();
                break;

            case 5:
                cafeteria.displayOrders();
                break;

            case 6:
                cout << "\nThank you for using the Cafeteria System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please select between 1 and 6.\n";
        }

    } while (choice != 6);

    return 0;
}
