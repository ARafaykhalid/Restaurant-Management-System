#include <iostream> //input output
#include <vector> //dynamic array
#include <string> //you know it (●'◡'●)
#include <fstream> //to manage files
#include <limits>  //to get cin limits
#include <iomanip> //for formatting
#include <chrono> // to scale time
#include <conio.h> //console funcs like getch 
#include <ctime> //to get time
#include <thread> //to create threads
// we'll guide the libraries in the PPT Slides

using namespace std; //standard lib

//debug cout
template <typename T>
void debug_cout(const T &jo_cout_kerna_hain){ //functions with single parameters, & is used to edit the original variable w/out copying it
    bool __debug = false; // Change this to false to disable debug outputs [for testing if the file is loading or not]
    if (__debug){
        cout << jo_cout_kerna_hain << endl;
    }
}

//extra ui stuff
void __Decuration_Lines(){ //function with no parameters, also we uses void in case of no return of variable from the func
    cout << "------------------------------------"<< endl;
}

void __Clear_Sys(){
    system("cls"); //its use to clear the console
}

void __Invalid_Input(){
    __Decuration_Lines();
    cout << "Invalid choice! Please select a valid option." << endl;
    __Decuration_Lines();
}
//==

// Structure to hold employee details
struct Employee { //its use to structure the vector
    string name;
    string user_name;
    string password;
    int Total_orders = 0;
};

// Structure to hold order details
struct Order{
    string Item;
    int Price;
};

//Shows Time and greeting
void Time_And_Greet(){ 
    // Get the current time
    auto now = chrono::system_clock::now();

    // Convert to time_t for easier manipulation
    time_t currentTime = chrono::system_clock::to_time_t(now);

    // Convert to local time structure
    tm* localTime = localtime(&currentTime);
    
    // Get the current hour
    int hour = localTime->tm_hour;
    string Am_OR_Pm = (hour >= 12) ? "pm" : "am"; //ternary method

    // Greet based on the time of day
    if (hour >= 6 and hour < 12){
        cout << "Good Morning!" << endl;
    } else if (hour >= 18 and hour < 24){
        cout << "Good Night!" << endl;
    } else {
        cout << "Good Afternoon!" << endl;
    }

    // Display the date and time (iomanip = input output manipulator is used to manipulate the string, just like :format in python)
    cout << put_time(localTime, "Date: %Y-%m-%d \nTime: %I:%M ") << Am_OR_Pm << endl;
};


// Function to handle input validation
template <typename T> //to make my own datatype to manipulate the compiler
void cin_handle(T &receiver, const string &prompt){
    while (true){
        cout << prompt;
        if (cin >> receiver){
            // Input successful
            break;
        } else {
            // Handle invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            __Invalid_Input();
        }
    }
}

// Function to save employees to a file
void saveEmployeesToFile(const vector<Employee> &employees, const string &filename){
    ofstream file(filename, ios::trunc); // Open file in truncate mode to overwrite existing content
    if (file.is_open()){
        for (const auto &employee : employees){ // for each loop
            file << employee.name << endl << employee.user_name << endl << employee.password << endl << employee.Total_orders << endl;
        }
        file.close();
        debug_cout("Employee data saved to " + filename + " successfully.");
    } else {
        debug_cout("Error: Unable to open file " + filename + " for writing.");
    }
}

// Function to load employees from a file
void loadEmployeesFromFile(vector<Employee> &employees, const string &filename){
    ifstream file(filename); // Open file in read mode
    if (file.is_open()){
        Employee employee;
        while (getline(file, employee.name) and getline(file, employee.user_name) and getline(file, employee.password) and file >> employee.Total_orders){
            file.ignore(); // Ignore the newline character after the Total_orders
            employees.push_back(employee);
        }
        file.close();
        debug_cout("Employee data loaded from " + filename + " successfully.");
    } else {
        debug_cout("No existing employee data found. Starting fresh.");
    }
}

// Function to get hidden password input
string getHiddenPassword(){
    string password;
    char ch;

    cout << "Enter Password: ";

    while ((ch = _getch()) != '\r'){ // '\r' = enter
        if (ch == '\b' and !password.empty()){ // \b = backspace
            cout << "\b \b"; // Remove character from console
            password.pop_back();
        } else if (ch != '\b'){
            password += ch; //same as password = password + ch
            cout << '*'; // Display Stars
        }
    }
    cout <<""<< endl;
    return password;
}

// Function to load order main features
int Order_func(int &P_total_orders){ //child function of restaurant
    bool Order_completed = false; // Initialize the variable
    vector<Order> Orders;         // Vector to store the list of orders
    Order new_Order;
    int Order_Options;
    __Clear_Sys();
    while (!Order_completed){
        // Display menu
        __Decuration_Lines();
        cout << "Place Orders: " << endl;
        __Decuration_Lines();
        if (Orders.empty()){ //Empty() clears all the stored member of the array/vector
            cout << "No items in the order." << endl;
        } else {
            __Clear_Sys();
            __Decuration_Lines();
            cout << "Current Order:" << endl;
            __Decuration_Lines();
            int total_price = 0; // initialized it here so whenever the error occurs, the total price resets to 0 again
            for (size_t i = 0; i < Orders.size(); ++i){
                cout << i + 1 << ". " << Orders[i].Item << " - " << Orders[i].Price << " PKR" << endl;
                total_price += Orders[i].Price;
            }
            __Decuration_Lines();
            cout << "Total Price: " << total_price << " PKR" << endl;
        };
        __Decuration_Lines();
        cout << "1. Add New Item" << endl;
        cout << "2. Remove Item" << endl;
        cout << "3. Complete Order" << endl;
        __Decuration_Lines();
        cin_handle(Order_Options, "Enter Your Choice: ");
    
        switch (Order_Options){ //Switch Case
            case 1: {
                // Add a new item
                __Clear_Sys();
                
                cin.ignore(); // Clear newline character from previous input
                cout << "Enter The Item Name: ";
                getline(cin, new_Order.Item); //it also includes spaces in the input
                cin_handle(new_Order.Price, "Enter The Item Price: ");
                Orders.push_back(new_Order);
                __Clear_Sys();
                __Decuration_Lines();
                cout << "Item added successfully!" << endl;
                __Decuration_Lines();
                break;
            }

            case 2: {
                // Remove an item
                if (Orders.empty()){
                    __Clear_Sys();
                    __Decuration_Lines();
                    cout << "No items to remove." << endl;
                } else {
                    cout << "Enter the index of the item to remove (1 to " << Orders.size() << "): ";
                    int index;
                    cin_handle(index, "");
                    if (index > 0 and index <= Orders.size()){
                        Orders.erase(Orders.begin() + (index - 1));
                        __Clear_Sys();
                        __Decuration_Lines();
                        cout << "Item removed successfully!" << endl;
                    } else {
                        __Clear_Sys();
                        __Decuration_Lines();
                        cout << "Invalid index." << endl;
                    }
                }
                break;
            }

            case 3: {
                // Complete the order
                __Clear_Sys();
                __Decuration_Lines();
                if (!Orders.empty()){
                    cout << "Order completed! Thank you." << endl;
                    Order_completed = true; // Exit the loop
                    P_total_orders+=1;
                } else {
                    cout << "Order Cancelled." << endl;
                    Order_completed = true; // Exit the loop
                };
                break;
            }

            default: {
                __Invalid_Input();
                break;
            }
        }
        cout << endl; // Add a line break for readability
    }
    return P_total_orders;
} 


// Function to load restaurant main features
void Restaurant(vector<Employee> &employees, string &username, string &password){
    bool loggedin = true;
    int R_Actions;
    while (loggedin){
        __Decuration_Lines();
        for (auto &employee : employees){
            if (employee.user_name == username and employee.password == password){
                cout << "Welcome!, " << employee.name << "!" << endl;
            }
        };
        Time_And_Greet();
        __Decuration_Lines();
        for (auto &employee : employees){
            if (employee.user_name == username and employee.password == password){
                cout << "Total Orders Of This Month: " << employee.Total_orders << "!" << endl;
            }
        }
        __Decuration_Lines();
        cout << "Options: " << endl;
        __Decuration_Lines();
        cout << "1. Clear This Month's Orders!" << endl;
        cout << "2. Place Order" << endl;
        cout << "3. Log-Out" << endl;
        __Decuration_Lines();

        cin_handle(R_Actions, "Enter your choice: ");
        __Clear_Sys();

        for (auto &employee : employees){
            if (employee.user_name == username and employee.password == password){

                if (R_Actions == 1){
                    employee.Total_orders = 0;
                    __Decuration_Lines();
                    cout << "Orders Cleared!" << endl;
                } else if (R_Actions == 2){
                    //pass
                    int total_order_increment = Order_func(employee.Total_orders);
                    employee.Total_orders = total_order_increment;
                } else if (R_Actions == 3){
                    //Breaks out of the Restaurant function
                    loggedin = false;
                    break;
                } else {
                    __Invalid_Input();
                };
            };
        };
        
    };
}


int main(){
    vector<Employee> employees; // Vector to store newly registered employees or check existing ones
    const string filename = "employees.txt"; // File to store employee data

    // Load existing employee data from file
    loadEmployeesFromFile(employees, filename);

    int Signup;
    bool Programme = true;

    while (Programme){
        // Display menu options
        __Decuration_Lines();
        cout << "Options: " << endl;
        __Decuration_Lines();
        cout << "1. Registration" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;

        // Input validation
        __Decuration_Lines();
        cin_handle(Signup, "Enter your choice: ");
        __Decuration_Lines();

        // Handle menu options
        if (Signup == 1){
            // Registration
            __Clear_Sys();
            Employee newEmployee;
            bool usernameExists;

            __Decuration_Lines();
            cout << "Registration: " << endl;
            __Decuration_Lines();

            cout << "Enter your Name: ";
            cin.ignore();
            getline(cin, newEmployee.name);

            do {  //do while loop
                usernameExists = false;
                cout << "Enter Username: ";
                getline(cin, newEmployee.user_name);

                // Check if the username already exists
                for (const auto &employee : employees){
                    if (employee.user_name == newEmployee.user_name){
                        usernameExists = true;
                        __Decuration_Lines();
                        cout << "Username already exists! Please choose a different username." << endl;
                        __Decuration_Lines();
                        break;
                    }
                }
            } while (usernameExists);

            newEmployee.password = getHiddenPassword();

            // Add the new employee to the list
            employees.push_back(newEmployee);
            __Clear_Sys();
            __Decuration_Lines();
            cout << "Registration successful!" << endl;

        } else if (Signup == 2){
            // Login
            __Clear_Sys();
            __Decuration_Lines();
            cout << "Login: " << endl;
            __Decuration_Lines();
            string username, password;
            cout << "Enter Username: ";
            cin >> username;
            password = getHiddenPassword();
            __Clear_Sys();

            // Check if username and password match any registered employee
            bool loginSuccess = false;
            for (auto &employee : employees){
                if (employee.user_name == username and employee.password == password){
                    __Decuration_Lines();
                    cout << "Login successful!" << endl;
                    __Decuration_Lines();
                    this_thread::sleep_for(chrono::seconds(3));
                    loginSuccess = true;
                    __Clear_Sys();
                    Restaurant(employees, username, password);  // Pass employees to Restaurant
                    break;
                }
            }

            if (!loginSuccess){
                __Decuration_Lines();
                cout << "Invalid username or password. Please try again." << endl;
            }

        } else if (Signup == 3){
            // Exit
            cout << "Exiting program." << endl;
            Programme = false;

        } else {
            __Clear_Sys();
            __Invalid_Input();
        }
    }

    // Save updated employee data to file
    saveEmployeesToFile(employees, filename);

    return 0;
}
