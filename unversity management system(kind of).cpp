#include <iostream>
#include <iomanip>
#include <map>
#include <string>

using namespace std;

// Define constants
const int MAX_CLASSES = 10;
const int MAX_STUDENTS = 1;
const int MAX_ASSESSMENTS = 5;
const int MAX_PERFORMANCES = 5;
const int MAX_REPORTS = 5;

// Struct for student in Teacher Portal mode
struct Student {
    string name;
    string rollNumber;
    int labPerformance[MAX_PERFORMANCES];
    int labReports[MAX_REPORTS];
    int midterm;
    int cea;
    int finalTerm;
    float totalMarks;
};

// Struct for class in Teacher Portal mode
struct Class {
    string className;
    Student students[MAX_STUDENTS];
    float weights[MAX_ASSESSMENTS];
};
Class classes[MAX_CLASSES];
int numClasses;
void enterClasses() {
    cout << "Enter the number of classes: ";
    cin >> numClasses;
    cin.ignore();

    for (int i = 0; i < numClasses; i++) {
        cout << "Enter class name (e.g., CE-112L MTS II B): ";
        getline(cin, classes[i].className);
    }
};
void displayClasses() {
    cout << "Select a class: " << endl;
    for (int i = 0; i < numClasses; i++) {
        cout << "Press " << i + 1 << " for " << classes[i].className << endl;
    }
};
void enterStudentDetails(Class& selectedClass) {
    for (int i = 0; i < MAX_STUDENTS; i++) {
        cout << "Enter details for student " << i + 1 << endl;
        cout << "Name: ";
        cin.ignore();
        getline(cin, selectedClass.students[i].name);
        cout << "Roll Number: ";
        getline(cin, selectedClass.students[i].rollNumber);

        cout << "Enter marks for 5 lab performances: ";
        for (int j = 0; j < MAX_PERFORMANCES; j++) {
            cin >> selectedClass.students[i].labPerformance[j];
        }

        cout << "Enter marks for 5 lab reports: ";
        for (int j = 0; j < MAX_REPORTS; j++) {
            cin >> selectedClass.students[i].labReports[j];
        }

        cout << "Enter marks for Midterm: ";
        cin >> selectedClass.students[i].midterm;
        cout << "Enter marks for CEA: ";
        cin >> selectedClass.students[i].cea;
        cout << "Enter marks for Final Term: ";
        cin >> selectedClass.students[i].finalTerm;
    }
};
void assignWeights(Class& selectedClass) {
    cout << "Assign weights to each assessment type (in percentage):" << endl;
    cout << "Lab Performance: ";
    cin >> selectedClass.weights[0];
    cout << "Lab Reports: ";
    cin >> selectedClass.weights[1];
    cout << "Midterm: ";
    cin >> selectedClass.weights[2];
    cout << "CEA: ";
    cin >> selectedClass.weights[3];
    cout << "Final Term: ";
    cin >> selectedClass.weights[4];
};
void calculateTotalMarks(Class& selectedClass) {
    for (int i = 0; i < MAX_STUDENTS; i++) {
        float totalLabPerformance = 0, totalLabReports = 0;
        for (int j = 0; j < MAX_PERFORMANCES; j++) {
            totalLabPerformance += selectedClass.students[i].labPerformance[j];
            totalLabReports += selectedClass.students[i].labReports[j];
        }
        totalLabPerformance /= MAX_PERFORMANCES;
        totalLabReports /= MAX_REPORTS;

        selectedClass.students[i].totalMarks = (totalLabPerformance * selectedClass.weights[0] / 100) +
                                               (totalLabReports * selectedClass.weights[1] / 100) +
                                               (selectedClass.students[i].midterm * selectedClass.weights[2] / 100) +
                                               (selectedClass.students[i].cea * selectedClass.weights[3] / 100) +
                                               (selectedClass.students[i].finalTerm * selectedClass.weights[4] / 100);
    }
};
void displayStudentResults(const Class& selectedClass) {
    cout << "Student Results:" << endl;
    cout << setw(20) << "Name" << setw(15) << "Roll Number" << setw(15) << "Total Marks" << endl;
    for (int i = 0; i < MAX_STUDENTS; i++) {
        cout << setw(20) << selectedClass.students[i].name << setw(15) << selectedClass.students[i].rollNumber << setw(15) << selectedClass.students[i].totalMarks << endl;
    }
};


// Define a map to store menu items with their prices for University Cafe mode
map<string, double> cafeMenu = {
    {"coffee", 2.50},
    {"tea", 1.75},
    {"sandwich", 4.50},
    {"salad", 5.75},
    {"cake", 3.25},
    {"pastry", 5.50},
    {"cold drink", 2.75},
    {"pizza slice", 7.50},
    {"samosa", 1.75},
    {"spring roll", 2.25}
};
struct MenuItem {
    string name;
    double price;
};
map<string, MenuItem> menu;

// Function prototypes for different modes
void teacherPortal();
void gamingZone();
void universityCafe();
void displayMenu(){
    cout << "Menu:" << endl;
    cout << setw(20) << "Item" << setw(10) << "Price" << endl;
    for (const auto& pair : menu) {
        cout << setw(20) << pair.second.name << setw(10) << pair.second.price << endl;
    }
};
void displayTotalBill(const map<string, int>& itemsBought){
    double totalBill = 0;
    cout << "Items Bought:" << endl;
    cout << setw(20) << "Item" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
    for (const auto& pair : itemsBought) {
        cout << setw(20) << menu[pair.first].name << setw(10) << pair.second << setw(10) << menu[pair.first].price * pair.second << endl;
        totalBill += menu[pair.first].price * pair.second;
    }
    cout << "Total Bill: $" << totalBill << endl;
};

char board[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
char current_marker;
int current_player;

void drawBoard() {
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = current_marker;
        return true;
    } else {
        return false;
    }
}

int checkWinner() {
    // Rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return current_player;
        }
    }
    // Columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return current_player;
        }
    }
    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return current_player;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return current_player;
    }

    return 0;
}

void swapPlayerAndMarker() {
    if (current_marker == 'X') current_marker = 'O';
    else current_marker = 'X';

    if (current_player == 1) current_player = 2;
    else current_player = 1;
}

void game() {
    cout << "Player 1, choose your marker (X/O): ";
    char marker_p1;
    cin >> marker_p1;

    current_player = 1;
    current_marker = marker_p1;

    if (marker_p1 == 'X') {
        current_marker = 'X';
    } else {
        current_marker = 'O';
    }

    drawBoard();
    int player_won;

    for (int i = 0; i < 9; i++) {
        cout << "It's player " << current_player << "'s turn. Enter your slot: ";
        int slot;
        cin >> slot;

        if (slot < 1 || slot > 9) {
            cout << "Invalid slot! Please try again." << endl;
            i--;
            continue;
        }

        if (!placeMarker(slot)) {
            cout << "Slot occupied! Please try again." << endl;
            i--;
            continue;
        }

        drawBoard();

        player_won = checkWinner();

        if (player_won == 1) {
            cout << "Player 1 wins! Congratulations!" << endl;
            break;
        }
        if (player_won == 2) {
            cout << "Player 2 wins! Congratulations!" << endl;
            break;
        }

        swapPlayerAndMarker();
    }

    if (player_won == 0) {
        cout << "It's a draw!" << endl;
    }
}

// Main function
int main() {
    
    
    
    int choice;
    do {
        // Display menu options
        cout << "Choose a mode:" << endl;
        cout << "1. Teacher Portal" << endl;
        cout << "2. University Cafe" << endl;
        cout << "3. Gaming Zone" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Perform action based on user's choice
        switch (choice) {
            case 1:
                teacherPortal();
                break;
            case 2:
                universityCafe();
                break;
            case 3:
                gamingZone();
                break;
            case 0:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}

// Function definitions for different modes

void teacherPortal() {
    cout << "Welcome to Teacher Portal!" << endl;
    // Add your implementation for Teacher Portal here
    enterClasses();
    displayClasses();

    int classChoice;
    cout << "Enter your choice: ";
    cin >> classChoice;
    Class& selectedClass = classes[classChoice - 1];

    enterStudentDetails(selectedClass);
    assignWeights(selectedClass);
    calculateTotalMarks(selectedClass);
    displayStudentResults(selectedClass);
    

    // Add implementation for Teacher Portal here
}

void gamingZone() {
    cout << "Welcome to Gaming Zone!" << endl;
    // Add your implementation for Gaming Zone here
    // For example:
    game();

    // Add implementation for Gaming Zone here
}

void universityCafe() {
    cout << "Welcome to University Cafe!" << endl;
    // Add your implementation for University Cafe here
    // For example:
    char choice;
    map<string, int> itemsBought;
        // Populate the menu
    menu["coffee"] = {"Coffee", 2.50};
    menu["tea"] = {"Tea", 1.75};
    menu["sandwich"] = {"Sandwich", 4.50};
    menu["salad"] = {"Salad", 5.75};
    menu["cake"] = {"Cake", 3.25};
    menu["pastry"] = {"Pastry", 5.50};
    menu["colddrink"] = {"Cold drink", 2.75};
    menu["pizzaslice"] = {"Pizza slice", 7.50};
    menu["samosa"] = {"Samosa", 1.75};
    menu["springroll"] = {"Spring roll", 2.25};

     do {
        displayMenu();
        cout << "Enter the item you want to buy (or type 'show bill' to display total bill): ";
        string itemName;
        cin >> itemName;

        // Check if the user wants to show the total bill
        if (itemName == "show bill") {
            if (itemsBought.empty()) {
                cout << "No items bought yet." << endl;
            } else {
                displayTotalBill(itemsBought);
            }
            continue;
        }

        // Check if the entered item is in the menu
        if (menu.find(itemName) != menu.end()) {
            cout << "Enter the quantity: ";
            int quantity;
            cin >> quantity;
            itemsBought[itemName] += quantity; // Add item to the list of items bought
        } else {
            cout << "Invalid item. Please choose an item from the menu." << endl;
        }

        cout << "Do you want to buy more items? (y/n): ";
        cin >> choice;
    } while (choice == 'y');

    // Display the final bill
    displayTotalBill(itemsBought);
    }