#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <ctime>
#include <conio.h>
#include <limits>
#include <algorithm>

using namespace std;

#pragma region defined constants
#define number_of_users_and_admin 1001
#define n 1
#define max_subscription_plans 13
#pragma endregion

#pragma region Global variables, Arrays & Structs
void initializeLocalTime(tm& localTime, time_t& now)
{
    now = time(0);
    if (localtime_s(&localTime, &now) != 0)
    {
        cerr << "Error: Failed to get local time." << endl;
        exit(EXIT_FAILURE);
    }
}
int kit_kat_1_station = 78; // Kit Kat to Rod El Farag
int kit_kat_2_station = 85; // Kit Kat to Cairo University
int Rod_axis_station = 84;
int start_line1 = 1;
int end_line1 = 35;
int start_line2 = 36;
int end_line2 = 55;
int start_line3 = 56;
int end_line3 = 89;
int Al_Shohadaa_line1 = 14;
int Al_Shohadaa_line2 = 43;
int Attaba_line2 = 44;
int Attaba_line3 = 74;
int Nasser_line1 = 16;
int Nasser_line3 = 75;
int stations_of_Rod_branch = 6;
int line1_size = 35, line2_size = 20, line3_size = 23;
int number_of_stations = 85;

// Global Variables
int start_station = 0, end_station = 0, count = 0;
int start_line = 0, end_line = 0, answer = 0;
int numberf_of_trips = 0;
int id;
int temp_register_or_login;
char role;
bool suceess = false;                          // To solve the problem of printing
bool isUnique[number_of_users_and_admin] = {}; // Frequency array to check if the ID exists or not
int global_id;
bool  subscipetion_or_not[number_of_users_and_admin] = {}; // To check if the user has a subscription or not
int Zone1_price = 8, Zone2_price = 10, Zone3_price = 15, Zone4_price = 20;
int New_Zone1_price, New_Zone2_price, New_Zone3_price, New_Zone4_price;
char previoussub[4];
int ride_freq_entry[1000] = {};
int ride_freq_exit[1000] = {};
int numberofsub[3];
int maximumage[150] = {};
string stations_read[1000] = {
    "New Marg", "El-Marg", "Ezbet El-Nakhl", "Ain Shams", "El-Matareyya",
    "Helmeyet El-Zaitoun", "Hadayeq El-Zaitoun", "Saray El-Qobba", "Hammamat El-Qobba", "Kobri El-Qobba",
    "Manshiet El-Sadr", "El-Demerdash", "Ghamra", "Al-Shohadaa", "Orabi", "Nasser", "Sadat", "Saad Zaghloul",
    "Al-Sayeda Zeinab", "El-Malek El-Saleh", "Mar Girgis", "El-Zahraa", "Dar El-Salam", "Hadayek El-Maadi",
    "Maadi", "Sakanat El-Maadi", "Tora El-Balad", "Kozzika", "Tura El-Esmant", "Elmaasara", "Hadayek Helwan",
    "Wadi Hof", "Helwan University", "Ain Helwan", "Helwan", "Shubra El-Khaimah", "Koliet El-Zeraa", "Mezallat",
    "Khalafawy", "St. Teresa", "Rod El-Farag", "Masarra", "Al-Shohadaa", "Attaba", "Mohamed Naguib", "Sadat",
    "Opera", "Dokki", "El Bohoth", "Cairo University", "Faisal", "Giza", "Omm El-Masryeen", "Sakiat Mekky",
    "El Monib", "Adly Mansour", "Haykestep", "Omar Ibn El Khattab", "Qubaa", "Hesham Barakat", "El-Nozha",
    "El-Shams Club", "Alf Maskan", "Heliopolis", "Haroun", "Al-Ahram", "Koleyet El-Banat", "Stadium", "Fair Zone",
    "Abbassiya", "Abdou Pasha", "El-Geish", "Bab El Shaariya", "Attaba", "Nasser", "Maspero", "Safaa Hijazy", "Kit-Kat",
    "Sudan", "Imbaba", "El-Bohy", "Al-Qawmeya Al-Arabiya", "Ring Road", "Rod al-Farag Axis", "El-Tawfikeya", "Wadi El-Nil",
    "Gamaat El Dowal Al-Arabiya", "Bulaq El-Dakroor", "Cairo University"
};
//
string stations[1000] = {
    "New Marg", "El-Marg", "Ezbet El-Nakhl", "Ain Shams", "El-Matareyya",
    "Helmeyet El-Zaitoun", "Hadayeq El-Zaitoun", "Saray El-Qobba", "Hammamat El-Qobba", "Kobri El-Qobba",
    "Manshiet El-Sadr", "El-Demerdash", "Ghamra", "Al-Shohadaa", "Orabi", "Nasser", "Sadat", "Saad Zaghloul",
    "Al-Sayeda Zeinab", "El-Malek El-Saleh", "Mar Girgis", "El-Zahraa", "Dar El-Salam", "Hadayek El-Maadi",
    "Maadi", "Sakanat El-Maadi", "Tora El-Balad", "Kozzika", "Tura El-Esmant", "Elmaasara", "Hadayek Helwan",
    "Wadi Hof", "Helwan University", "Ain Helwan", "Helwan", "Shubra El-Khaimah", "Koliet El-Zeraa", "Mezallat",
    "Khalafawy", "St. Teresa", "Rod El-Farag", "Masarra", "Al-Shohadaa", "Attaba", "Mohamed Naguib", "Sadat",
    "Opera", "Dokki", "El Bohoth", "Cairo University", "Faisal", "Giza", "Omm El-Masryeen", "Sakiat Mekky",
    "El Monib", "Adly Mansour", "Haykestep", "Omar Ibn El Khattab", "Qubaa", "Hesham Barakat", "El-Nozha",
    "El-Shams Club", "Alf Maskan", "Heliopolis", "Haroun", "Al-Ahram", "Koleyet El-Banat", "Stadium", "Fair Zone",
    "Abbassiya", "Abdou Pasha", "El-Geish", "Bab El Shaariya", "Attaba", "Nasser", "Maspero", "Safaa Hijazy", "Kit-Kat"
};
// geographical zones
string zone_1[8] = { "Al-Shohadaa", "Attaba", "Mohamed Naguib", "Sadat", "Opera", "Nasser", "Saad Zaghloul", "Orabi" };
string zone_2[5] = { "Al-Sayeda Zeinab", "El-Malek El-Saleh", "Mar Girgis", "El-Zahraa", "Dar El-Salam" };
string zone_3[8] = { "El Monib", "Sakiat Mekky", "Omm El-Masryeen", "Giza", "Faisal", "Cairo University", "El Bohoth", "Dokki" };
string zone_4[8] = { "Al-Ahram", "Koleyet El-Banat", "Stadium", "Fair Zone", "Abbassiya", "Abdou Pasha", "El-Geish", "Bab El Shaariya" };
string zone_5[6] = { "Saray El-Qobba", "Hammamat El-Qobba", "Kobri El-Qobba", "Manshiet El-Sadr", "El-Demerdash", "Ghamra" };
string zone_6[8] = { "Shubra El-Khaimah", "Koliet El-Zeraa", "Mezallat", "Khalafawy", "St. Teresa", "Rod El-Farag", "Masarra" };
string zone_7[6] = { "Hadayek El-Maadi", "Maadi", "Sakanat El-Maadi", "Tora El-Balad", "Kozzika", "Tura El-Esmant" };
string zone_8[7] = { "New Marg", "El-Marg", "Ezbet El-Nakhl", "Ain Shams", "El-Matareyya", "Helmeyet El-Zaitoun", "Hadayeq El-Zaitoun" };
string zone_9[6] = { "Elmaasara", "Hadayek Helwan", "Wadi Hof", "Helwan University", "Ain Helwan", "Helwan" };
string zone_10[10] = { "Adly Mansour", "Haykestep", "Omar Ibn El Khattab", "Qubaa", "Hesham Barakat", "El-Nozha", "El-Shams Club", "Alf Maskan", "Heliopolis", "Haroun" };
string zone_11[14] = { "Maspero", "Safaa Hijazy", "Kit-Kat", "Sudan", "Imbaba", "El-Bohy", "Al-Qawmeya Al-Arabiya", "Ring Road", "Rod al-Farag Axis", "El-Tawfikeya", "Wadi El-Nil", "Gamaat El Dowal Al-Arabiya", "Bulaq El-Dakroor", "Cairo University" };

// Struct Definitions
struct date
{
    int day;
    int month;
    int year;
    int hour;
    int minute;
} ride_date;

struct activationDate {
    int day;
    int month;
    int year;

    activationDate() {
        time_t now = time(0);
        tm localTime;
        localtime_s(&localTime, &now);
        day = localTime.tm_mday;
        month = localTime.tm_mon + 1;
        year = localTime.tm_year + 1900;
    }
};

struct expiryDate {
    int day = 0;
    int month = 0;
    int year = 0;
};

struct user_and_admin_struct
{
    char role;
    string name;
    int id;
    string password;
    char subscription_type;
    int age;
} arr_user[number_of_users_and_admin];

struct subscription {
    char planType;
    activationDate activationDatedetails;
    expiryDate expiryDatedetails;
    int remainingTrips = 0;
    string zones;
    int payment = 0;
};

struct system_subscriptions {
    string plan_name;
    char plan_symbol = '\0';
    bool is_monthly = false;
    bool is_yearly = false;
    int duration_months = 0;
    int duration_years = 0;
    int monthly_zone_prices[4] = { 0, 0, 0, 0 };
    int yearly_zone_prices[4] = { 0, 0, 0, 0 };
    int monthly_remaining_trips = 0;
    int yearly_remaining_trips = 0;
};
system_subscriptions subscriptions[max_subscription_plans];

int subscription_count = 3; // Start with 3 default plans

struct user_struct {
    int id = 0;
    int balance = 0;
    subscription subscribiondetails;
    int zone = 0; // Added missing member
}users[number_of_users_and_admin];


struct ride_struct {
    int ride_id;
    int start_station;
    int end_station;
    tm ride_date;
} rides[number_of_users_and_admin];

struct Ride_history {
    ride_struct ride_of_user[1000];
} RideHistory[number_of_users_and_admin];



#pragma endregion

#pragma region function decleared
// Utility Functions
void initializeLocalTime(tm& localTime, time_t& now);

// Sign-in, Registration & Admin Capabilities
bool check_name_has_int(string name);
string hidding_password_write(string& password);
string strong_pass();
bool check_if_id_unique(int id);
void initialize_default_subscriptions();
void Base_regiseter_to_user_or_admin();
void register_form();
void storage_the_data_of_user_and_admin();
void restore_the_data_of_user_and_admin();
void Admin_Subscriptions_edit();
void view_all_accounts();
void modifying_account(int ID = 0);
void delete_account();
void Admin_Subscriptions_control(system_subscriptions subscriptions[], int& subscription_count);
void user_main_menu();
void admin_main_menu();
void login_form();
char exit_or_not();

// Subscriptions
void user_data_entry();
void zoneselection(int& numberofstations);
void subscriptiondataentry(int planIndex);
void calculating_payment_and_expirydate();
void deductSubscriptionPayment();
void addFundsToSmartWallet();
void viewPersonalData();
void editPersonalData();
void viewSubscriptionPlan();
void renewSubscriptionPlan();
void changeSubscriptionPlan();
void subscriptions_for_registration();
void subscription_system_for_user_main_menu();
int zone_to_price(int selected_zone);
void changing_price_for_zones__menu();
void changing_prices_for_zones_for_zones_for_zones_for_zones_for_zones();
void subsctriprion_file_output();
void subscription_file_input();



// Rides
void enter_endline();
void enter_startline();
int choose_line(int& line_num, int& station_num);
void input_start_data(int& start_line, int& start);
void input_end_data(int& end_line, int& end_station);
void start_loop_odd_cases(int i, int& start, int& end_station, int trans1, int trans2, string arr[]);
void start_loop_even_cases(int i, int& start, int& end_station, int trans1, int trans2, string arr[]);
void end_loop(int i, int end_station, string arr[]);
void same_line_loop(int i, int start, string arr[]);
void case1(int& start, int& end_station, int trans1, int trans2, string arr[]);
void case2(int& start, int& end_station, int trans1, int trans2, string arr[]);
void case3(int& start, int& end_station, int trans1, int trans2, string arr[]);
void case4(int& start, int& end_station, int trans1, int trans2, string arr[]);
void case5(int& start, int& end_station, int trans1, int trans2, string arr[]);
void case6(int& start, int& end_station, int trans1, int trans2, string arr[]);
void case7(int& start, int& end_station, int trans1, int trans2, string arr[]);
void case8(int& start, int& end_station, int trans1, int trans2, string arr[]);
void cases(int& start, int& end_station, int trans1, int trans2, string arr[]);
void list_intersect_line_1_2(int& start, int& end_station, string arr[], int trans1, int trans2);
void list_intersect_line_2_3(int& start, int& end_station, string arr[], int trans2, int trans3);
void list_intersect_line_1_3(int& start, int& end_station, string arr[], int trans1, int trans3);
int counting_intersected_stations(int& start_station, int& end_station, int trans1, int trans2);
void if_intersection(int& start, int& end_station, int& start_line, int& end_line, string arr[], int answer);
int kit_kat_check(int& end_station, int& start);
void kitkat_branches(int& end_station, int& start);
void list_same_line(int& start, int& end_station, string arr[], user_struct arr_users[]);
void if_same_line(int& start, int& end_station, int& end_line, int& start_line, int answer);
void check_line(int& start_line, int& end_line, int& end_station, int& start, string arr[], int answer);
int counting_Rod_to_Cairo(int& end_station, int& start);
int counting_Cairo_to_Rod(int& end_station, int& start);
void Rod_to_Cairo_list(int& end_station, int& start, int answer);
void Cairo_to_Rod_list(int& end_station, int& start, int answer);
void start_calc(int& start, int& end_station, int& end_line, int& start_line, int answer);
int current_zone_check(string stations);
void zone_checker(string stations[], int& current_zone, int i, int& zone_counter);
int station_to_zone(int numberofstations);
int string_to_int_zone();
bool zone_to_zone_check(int selected_zone);
void trips_deduction_general_or_scholar();
void check_out(int answer, int selected_zone);
void wallet_dedcution(int selected_zone);
void trip_not_valid(int start, int end_station, int end_line, int start_line, int answer);
void system_ride();
void record_ride();
void output_History_user_version();
void output_History_admin_version();
void remove_station(int& line_size, string arr_remove[], int line);
void add_station(int& line_size, string arr[], int line);
void edit(int line_size, string global_line[], int line);
void History_Shift_Handling(bool opperation, int pos);

// History & Statistics
void statistics();
void storage_the_data_of_statistics();
void read_statistics();

#pragma endregion

#pragma region signin,Registration & Admin capabilities

void start_menu()
{
    while (true)
    {
        while (true)
        {
            int choose;

            cout << "Choose 1 to register \n2 to login\n";
            cin >> choose;

            while (cin.fail())
            {
                cin.clear();
                cin.ignore(20, '\n');
                cout << "You have enter a invalid type \nPlease enter int digit\n";
                cin >> choose;
            }
            if (choose == 1)
            {
                cout << "Are you sure you want to register?\n1.complete\n2.Back\n";
                int c;
                cin >> c;
                if (c == 1)
                {
                    cout << "You have chosen to register\n";
                    register_form();
                }
                else
                {
                    cout << "You have chosen not to register\n";
                    start_menu();
                }
            }
            else if (choose == 2)
            {
                cout << "Are you sure you want to sign in?\n1.complete\n2.Back\n";
                int c;
                cin >> c;
                if (c == 1)
                {
                    cout << "You have chosen to sign in\n";
                    login_form();
                }
                else
                {
                    cout << "You have chosen not to register\n";
                    start_menu();
                }
            }
            else
            {
                cout << "Invalid choice !! you must type 1 or 2 only\n";
            }
        }
    }
}

string hidding_password_write(string& password)
{
    string hidden_password = "";
    char ch;

    while ((ch = _getch()) != '\r') // getch() to get the character without echoing it
    {
        if (ch == '\b')
        {
            if (!hidden_password.empty())
            {
                hidden_password.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            cout << "*";
            hidden_password += ch;
        }
    }
    cout << '\n';
    password = hidden_password;
    return hidden_password;
}

string strong_pass()
{
    string password;
    bool characters = false, Upper = false, lower = false;

    while (1)
    {
        hidding_password_write(password);
        if (password.size() > 7)
        {
            for (int i = 0; i < password.size(); ++i)
            {
                if (password[i] >= 'a' && password[i] <= 'z')
                    lower = true;
                else if (password[i] >= 'A' && password[i] <= 'Z')
                    Upper = true;
                else if (password[i] >= 34 && password[i] <= 47)
                    characters = true;
            }
            if (characters && Upper && lower)
                break;
            else if (!characters && !Upper && !lower)
                cout << "Your password must have upper character, lower character, and special characters\n";
            else if (!Upper)
                cout << "Your password must contain an upper character\n";
            else if (!lower)
                cout << "Your password must contain a lower character\n";
            else
                cout << "Your password must contain a character like # *\n";
        }
        else
            cout << "The length of the password is less than 8 characters\n";
    }

    return password;
}

bool check_if_id_unique(int id)
{
    if (isUnique[id] == 0)
    {
        isUnique[id] = 1;
        return true;
    }
    else
    {
        return false;
    }
}

bool check_name_has_int(string name)
{
    for (char c : name)
    {
        if (isdigit(c))

        {
            return true;
        }
    }
    return false;
}

void initialize_default_subscriptions() {
    // Scholar Pass
    subscriptions[0] = {
        "Scholar Pass", // Plan name
        'S',           // Plan symbol
        true,          // Is monthly-based
        false,         // Is yearly-based
        3,             // Duration in months
        0,             // Duration in years
        {150, 200, 250, 300}, // Monthly zone prices
        {0, 0, 0, 0},  // Yearly zone prices
        180,           // Monthly remaining trips
        0              // Yearly remaining trips
    };

    // General Pass
    subscriptions[1] = {
        "General Pass", // Plan name
        'G',           // Plan symbol
        true,          // Is monthly-based
        true,          // Is yearly-based
        1,             // Duration in months
        1,             // Duration in years
        {310, 365, 425, 600}, // Monthly zone prices
        {3500, 4000, 4500, 5000}, // Yearly zone prices
        60,            // Monthly remaining trips
        730            // Yearly remaining trips
    };

    // Smart Wallet
    subscriptions[2] = {
        "Smart Wallet", // Plan name
        'W',           // Plan symbol
        false,         // Is monthly-based
        false,         // Is yearly-based
        0,             // Duration in months
        0,             // Duration in years
        {0, 0, 0, 0},  // Monthly zone prices (not applicable)
        {0, 0, 0, 0},  // Yearly zone prices (not applicable)
        0,             // Monthly remaining trips (no limit)
        0              // Yearly remaining trips (no limit)
    };

    subscription_count = 3; // Ensure the count is set to 3
}

void Base_regiseter_to_user_or_admin()
{
    int id;
    string name;
    cout << "Please Enter your Name \n";
    cin.ignore();
    getline(cin, name);

    while (check_name_has_int(name) == true)
    {
        cout << "Your name mustn't have an int value\n";
        cout << "Please Enter your Name \n";
        getline(cin, name);
        if (check_name_has_int(name) == false)
            break;
    }
    cout << "Please Enter your ID (form 1 to 1001) \n";
    cin >> id;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << "Enter digits\n";
        cin >> id;
    }
    while (id > 1000 || id <= 0) {
        cout << "Please Enter id in range 1 to 1000\n";
        cin >> id;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Enter a digit\n";
            cin >> id;
        }
    }
    while (check_if_id_unique(id) == false)
    {
        cout << "This ID already exists. Please enter another one\n";
        cin >> id;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Enter a digit\n";
            cin >> id;
        }
    }

    global_id = id;
    arr_user[global_id].id = id;
    arr_user[global_id].name = name;
    arr_user[global_id].role = role;

    cout << "Please Enter your age\n";
    cin >> arr_user[global_id].age;
    while (arr_user[global_id].age <= 0 || arr_user[global_id].age > 115)
    {
        cout << "Invalid age. Please enter a valid age:";
        cin >> arr_user[global_id].age;
    }
    cout << "Please Enter your password. It must be 8 or more characters and digits\n";
    arr_user[global_id].password = strong_pass();
    cout << "Please Enter Password again to confirm\n";
    string confirm = hidding_password_write(confirm);
    int attempts = 0;

    while (arr_user[global_id].password != confirm)
    {
        attempts++;
        if (attempts >= 3)
        {
            cout << "You have entered the wrong password confirmation 3 times. Redirecting to the main menu...\n";
            start_menu();
            return;
        }
        cout << "The password is not the same\n";
        cout << "Please Enter Password again to confirm\n";
        confirm = hidding_password_write(confirm);
    }
}

void register_form()
{
    cout << "Welcome to register a new account \n";

    cout << "Enter your Role admin (a) or user (u)\n";
    cin >> role;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << "You have entered an invalid type \nPlease enter char\n";
        cin >> role;
    }
    role = toupper(role);
    while (role != 'A' && role != 'U')
    {
        cout << "Invalid role! You must type 'a' for admin or 'u' for user\n";
        cin.clear();
        cin.ignore();
        cin >> role;
        role = toupper(role);
    }

    if (role == 'U' || role == 'u')
    {
        Base_regiseter_to_user_or_admin();
        subscriptions_for_registration();
    }
    else if (role == 'A' || role == 'a')
    {
        Base_regiseter_to_user_or_admin();
        suceess = 0;
        while (true)
        {
            int token;
            cout << "Enter the token to verify you are authorized to be an admin\n";
            cin >> token;
            if (token == 1929)
            {
                suceess = true;
                break;
            }
            else
            {
                cout << "You cannot be an admin, sorry\n";
                break;
            }
        }
    }
    if (suceess)
        cout << "Your account has been created successfully\n";
}

void storage_the_data_of_user_and_admin()
{
    ofstream file_user_and_admin_output("file_user_and_admin.txt", ios::trunc);
    // Write the data to the file
    for (int i = 0; i < number_of_users_and_admin; ++i)
    {
        if (isUnique[i])
        {
            if (arr_user[i].role == 'A')
                file_user_and_admin_output << arr_user[i].role << " "
                << arr_user[i].id << " "
                << arr_user[i].password << " "
                << arr_user[i].age
                << endl
                << arr_user[i].name << endl;
            else
                file_user_and_admin_output << arr_user[i].role << " "
                << arr_user[i].id << " "
                << arr_user[i].password << " "
                << users[i].subscribiondetails.planType << " "
                << users[i].balance << " "
                << arr_user[i].age << " " <<
                users[arr_user[i].id].subscribiondetails.payment << " " <<
                users[arr_user[i].id].subscribiondetails.zones << " " <<
                users[arr_user[i].id].subscribiondetails.remainingTrips << " " <<
                users[arr_user[i].id].subscribiondetails.activationDatedetails.day << " "
                << users[arr_user[i].id].subscribiondetails.activationDatedetails.month <<
                " " << users[arr_user[i].id].subscribiondetails.activationDatedetails.year << " "
                << users[arr_user[i].id].subscribiondetails.expiryDatedetails.day
                << " " << users[arr_user[i].id].subscribiondetails.expiryDatedetails.month
                << " " << users[arr_user[i].id].subscribiondetails.expiryDatedetails.year << " " <<
                subscipetion_or_not[arr_user[i].id]
                << endl
                << arr_user[i].name << endl;
        }
    }

    file_user_and_admin_output.close();
}

void restore_the_data_of_user_and_admin()
{
    ifstream file_user_and_admin_input("file_user_and_admin.txt");

    if (!file_user_and_admin_input.is_open())
    {
        cout << "Error: Unable to open file_user_and_admin.txt!" << endl;
        return;
    }

    char role;
    string name;
    while (file_user_and_admin_input >> role)
    {
        if (role == 'A')
        {

            string password;
            if (!(file_user_and_admin_input >> id >> password >> arr_user[id].age) || id <= 0 || id >= number_of_users_and_admin)
            {
                file_user_and_admin_input.clear();
                file_user_and_admin_input.ignore(10000, '\n');
                continue;
            }
            file_user_and_admin_input.ignore(10000, '\n');
            if (!getline(file_user_and_admin_input, name) || name.empty())
            {
                file_user_and_admin_input.clear();
                file_user_and_admin_input.ignore(10000, '\n');
                continue;
            }
            arr_user[id].id = id;
            arr_user[id].role = role;
            arr_user[id].password = password;
            arr_user[id].name = name;
            isUnique[id] = true;
        }
        else if (role == 'U')
        {
            string password;
            char subscription_type;
            double balance;
            string subsZone = {};
            int remainingTrips = 0;
            int age = 0;
            int payment = 0;
            int subs_or_not = 0;
            int day_active = 0, month_active = 0, year_active = 0;
            int day_expire = 0, month_expire = 0, year_expire = 0;
            file_user_and_admin_input >> id >> password >> subscription_type >> balance >> age >> payment
                >> subsZone >>
                remainingTrips >>
                day_active >>
                month_active >>
                year_active >>
                day_expire >>
                month_expire
                >> year_expire >>
                subs_or_not;


            file_user_and_admin_input.ignore(10000, '\n');
            if (!getline(file_user_and_admin_input, name) || name.empty())
            {
                file_user_and_admin_input.clear();
                file_user_and_admin_input.ignore(10000, '\n');
                continue;
            }
            arr_user[id].id = id;
            arr_user[id].role = role;
            arr_user[id].password = password;
            users[id].subscribiondetails.planType = subscription_type;
            users[id].balance = balance;
            arr_user[id].name = name;
            isUnique[id] = true;
            users[id].subscribiondetails.zones = subsZone;
            users[id].subscribiondetails.remainingTrips = remainingTrips;
            arr_user[id].age = age;
            users[id].subscribiondetails.payment = payment;
            subscipetion_or_not[id] = subs_or_not;
            users[id].subscribiondetails.activationDatedetails.day = day_active;
            users[id].subscribiondetails.activationDatedetails.month = month_active;
            users[id].subscribiondetails.activationDatedetails.year = year_active;
            users[id].subscribiondetails.expiryDatedetails.day = day_expire;
            users[id].subscribiondetails.expiryDatedetails.month = month_expire;
            users[id].subscribiondetails.expiryDatedetails.year = year_expire;
        }
        else
        {
            file_user_and_admin_input.clear();
            file_user_and_admin_input.ignore(10000, '\n');
            continue;
        }
    }
    file_user_and_admin_input.close();
}

void Admin_Subscriptions_edit() {
    cout << "You chossed to edit current subscription plans\n";
    cout << "Select the plan you want to edit\n";
    cout << "Available Subscription Plans are:\n";
    for (int i = 0; i < subscription_count; i++) {
        cout << i + 1 << ". " << subscriptions[i].plan_name << " (" << subscriptions[i].plan_symbol << ")\n";

    }
    cout << "Please enter the number of the plan you want to select: ";
    int num;
    cin >> num;
    while (num < 1 || num > subscription_count) {
        cout << "Invalid option. Please enter a valid plan number:" << endl;
        cin >> num;
    }
    cout << "What do you want to edit?: \n";
    cout << "1. Plan name & Symbol\n";
    cout << "2. Is it Monthly-based, Yearly bassed or both\n";
    cout << "3. Duration in for monthly-based option\n";
    cout << "4. Duration in yearly-based option\n";
    cout << "5. Zone prices for monthly option\n";
    cout << "6. Zone prices for yearly option\n";
    cout << "7. Number of remaining trips for the monthly option\n";
    cout << "8. Number of remaining trips for the yearly option\n";
    cout << "9. Back to Subscription Management\n";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 9)
    {
        cout << "Invalid choice! Please enter a number between 1 and 9.\n";
        cin >> choice;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(20, '\n');
            cout << "You have enter a invalid type \nPlease enter int digit\n";
            cin >> choice;
        }
    }
    switch (choice)
    {
    case 1:
    {
        cout << "Enter new plan name: ";
        cin.ignore();
        getline(cin, subscriptions[num - 1].plan_name);
        cout << "Enter new plan symbol: ";
        cin >> subscriptions[num - 1].plan_symbol;
        break;
    }
    case 2:
    {
        cout << "Is the plan monthly-based? (1 for Yes, 0 for No): ";
        cin >> subscriptions[num - 1].is_monthly;
        cout << "Is the plan yearly-based? (1 for Yes, 0 for No): ";
        cin >> subscriptions[num - 1].is_yearly;
        if (subscriptions[num - 1].is_monthly) {
            cout << "Enter duration in months: ";
            cin >> subscriptions[num - 1].duration_months;
        }
        if (subscriptions[num - 1].is_yearly) {
            cout << "Enter duration in years: ";
            cin >> subscriptions[num - 1].duration_years;
        }
        break;
    }

    case 3:
    {
        cout << "Enter duration in months: ";
        cin >> subscriptions[num - 1].duration_months;
        break;
    }

    case 4:
    {
        cout << "Enter duration in years: ";
        cin >> subscriptions[num - 1].duration_years;
        break;
    }
    case 5:
    {
        cout << "Enter zone prices for monthly option (Zone 1 to Zone 4): ";
        for (int i = 0; i < 4; i++) {
            cin >> subscriptions[num - 1].monthly_zone_prices[i];
        }
        break;
    }
    case 6:
    {
        cout << "Enter zone prices for yearly option (Zone 1 to Zone 4): ";
        for (int i = 0; i < 4; i++) {
            cin >> subscriptions[num - 1].yearly_zone_prices[i];
        }
        break;
    }
    case 7:
    {
        cout << "Enter the number of remaining trips for the monthly plan: ";
        cin >> subscriptions[num - 1].monthly_remaining_trips;
        break;
    }
    case 8:
    {
        cout << "Enter the number of remaining trips for the yearly plan: ";
        cin >> subscriptions[num - 1].yearly_remaining_trips;
        break;
    }
    case 9:
    {
        cout << "You have chosen to go back to Subscription Management\n";
        Admin_Subscriptions_control(subscriptions, subscription_count);
        break;
    }
    default:
        cout << "Invalid choice! Please try again.\n";
        break;
    }

}

void Admin_Subscriptions_control(system_subscriptions subscriptions[], int& subscription_count) {
    while (true) {
        cout << "Subscription Management:\n";
        cout << "1. Add a new subscription plan\n";
        cout << "2. Remove a subscription plan\n";
        cout << "3. Edit the current subscription plans\n";
        cout << "4. Back to Admin Menu\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) { // Add a new plan
            if (subscription_count >= max_subscription_plans) {
                cout << "Cannot add more than " << max_subscription_plans << " subscription plans.\n";
                continue;
            }

            system_subscriptions new_plan;
            cout << "Enter plan name: ";
            cin.ignore();
            getline(cin, new_plan.plan_name);
            cout << "Enter plan symbol (unique): ";
            cin >> new_plan.plan_symbol;

            // Ensure unique symbol
            bool is_unique = true;
            for (int i = 0; i < subscription_count; i++) {
                if (subscriptions[i].plan_symbol == new_plan.plan_symbol) {
                    is_unique = false;
                    break;
                }
            }
            if (!is_unique) {
                cout << "Plan symbol must be unique!\n";
                continue;
            }

            cout << "Is the plan monthly-based? (1 for Yes, 0 for No): ";
            cin >> new_plan.is_monthly;
            if (new_plan.is_monthly) {
                cout << "Enter duration in months: ";
                cin >> new_plan.duration_months;
                cout << "Enter zone prices for monthly option (Zone 1 to Zone 4): ";
                for (int i = 0; i < 4; i++) {
                    cin >> new_plan.monthly_zone_prices[i];
                }
                cout << "Enter the number of remaining trips for the monthly plan: ";
                cin >> new_plan.monthly_remaining_trips;
            }

            cout << "Is the plan yearly-based? (1 for Yes, 0 for No): ";
            cin >> new_plan.is_yearly;
            if (new_plan.is_yearly) {
                cout << "Enter duration in years: ";
                cin >> new_plan.duration_years;
                cout << "Enter zone prices for yearly option (Zone 1 to Zone 4): ";
                for (int i = 0; i < 4; i++) {
                    cin >> new_plan.yearly_zone_prices[i];
                }
                cout << "Enter the number of remaining trips for the yearly plan: ";
                cin >> new_plan.yearly_remaining_trips;
            }

            subscriptions[subscription_count++] = new_plan;
            cout << "New subscription plan added successfully!\n";

        }
        else if (choice == 2) { // Remove a plan
            cout << "Available Plans:\n";
            for (int i = 0; i < subscription_count; i++) {
                cout << i + 1 << ". " << subscriptions[i].plan_name << " (" << subscriptions[i].plan_symbol << ")\n";
            }
            cout << "Enter the index of the plan to remove: ";
            int index;
            cin >> index;

            if (index < 1 || index > subscription_count) {
                cout << "Invalid selection!\n";
                continue;
            }

            // Remove the plan by shifting the array
            for (int i = index - 1; i < subscription_count - 1; i++) {
                subscriptions[i] = subscriptions[i + 1];
            }
            subscription_count--;
            cout << "Subscription plan removed successfully!\n";

        }
        else if (choice == 3) {
            Admin_Subscriptions_edit();
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "Invalid choice! Please try again.\n";
        }
    }
}

void view_all_accounts()
{
    bool has_accounts = false;
    for (int i = 0; i < number_of_users_and_admin; i++)
    {
        if (isUnique[i] && !arr_user[i].name.empty())
        {
            has_accounts = true;
            cout << "------------\n"
                << "Name: " << arr_user[i].name << '\n'
                << "Id: " << arr_user[i].id << '\n'
                << "Password: " << arr_user[i].password << '\n'
                << "Role: " << arr_user[i].role << '\n'
                << "Age: " << arr_user[i].age << '\n';
            if (arr_user[i].role == 'U')
            {
                cout << "Subscription Type: " << users[i].subscribiondetails.planType << '\n'
                    << "Balance: " << users[i].balance << '\n';
            }
            cout << "------------\n";
        }
    }

    if (!has_accounts)
        cout << "No accounts found.\n";
    cout << "Press 1 for MAIN MENU: ";
    int c;
    cin >> c;
    while (cin.fail() && c != 1)
    {
        cout << "Press 1 only for MAIN MENU: ";
        cin >> c;
    }
    admin_main_menu();
}

void modifying_account(int ID)
{
    while (true)
    {
        if (arr_user[global_id].role == 'A')
        {
            cout << "Please Enter the ID of the account you want to modify\n";
            cin >> id;
        }
        char again;
        char modify;
        if (isUnique[id] == 1)
        {
            do
            {
                cout << "Select what to modify?\n";
                cout << "n for name\n";
                cout << "p for password\n";
                cout << "b for balance\n";
                if (arr_user[global_id].role == 'A')
                {
                    cout << "e for modifing another account\n";
                }
                cout << "M to go back to the MAIN MENU\n";
                cout << "Enter a letter: ";
                cin >> modify;
                modify = tolower(modify);
                switch (modify)
                {
                case 'e':
                    if (arr_user[global_id].role == 'A')
                    {
                        cout << "Please Enter the ID of the account you want to modify\n";
                        cin >> id;
                    }
                    modifying_account(id);

                case 'n':
                    cout << "Please Enter the new name\n";
                    cin.ignore();
                    getline(cin, arr_user[id].name);
                    while (cin.fail())
                    {
                        cin.clear();
                        cin.ignore();
                        getline(cin, arr_user[id].name);
                        cout << "Successful Modification\n";
                    }
                    break;
                case 'p':
                    cout << "Please Enter the new password\n";
                    hidding_password_write(arr_user[id].password);
                    arr_user[global_id].password = hidding_password_write(arr_user[id].password);
                    cout << "Successful Modification\n";
                    break;
                case 'b':
                    cout << "Please Enter the new balance\n";
                    cin >> users[id].balance;
                    while (cin.fail())
                    {
                        cin.clear();
                        cin.ignore();
                        cout << "enter a digit\n";
                        cin >> users[id].balance;
                        cout << "Successful Modification\n";
                    }
                    break;
                case 'm':
                    cout << "going back to the main menu\n";
                    if (arr_user[global_id].role == 'U')
                    {
                        user_main_menu();
                    }
                    else if (arr_user[global_id].role == 'A')
                    {
                        admin_main_menu();
                    }
                    break;
                default:
                    cout << "invalid input\n";
                }

                cout << "want to modify something else(y/n)\n";
                cin >> again;
                again = tolower(again);
            } while (again == 'y');
        }
        else
            cout << "user doesn't exist\n";
    }
}

void delete_account()
{
    int id;
    cout << "Please Enter the ID of the account you want to delete\n";
    cin >> id;
    if (isUnique[id] == 1)
    {
        isUnique[id] = 0;
        arr_user[id].name = "";
        arr_user[id].id = 0;
        arr_user[id].password = "";
        arr_user[id].role = ' ';
        arr_user[id].subscription_type = ' ';
        users[id].balance = 0;

        cout << "The account has been deleted successfully\n";
        isUnique[id] = 0;
    }
    else
        cout << "user doesn't exist\n";
    cout << "Press 1 for MAIN MENU: ";
    int c;
    cin >> c;
    while (cin.fail() && c != 1)
    {
        cout << "Press 1 only for MAIN MENU: ";
        cin >> c;
    }
    admin_main_menu();
}

void add_station(int& line_size, string arr[], int line)
{
    if (line == 1)
    {
        for (int i = start_line1 - 1; i < end_line1; ++i) {
            cout << i + 1 << '.' << stations_read[i] << endl;

        }
    }
    else if (line == 2)
    {
        for (int i = start_line2 - 1; i < end_line2; ++i) {
            cout << i + 1 << '.' << stations_read[i] << endl;

        }
    }
    else if (line == 3)
    {
        for (int i = start_line3 - 1; i < number_of_stations; ++i) {
            cout << i + 1 << '.' << stations_read[i] << endl;

        }
    }
    cout << "\nAt which position do you want to add a station" << '\n';
    int pos_new_station;

    while (true) {
        cin >> pos_new_station;
        if (!(pos_new_station >= start_line1 && pos_new_station <= end_line1)) {
            if (line == 1)
            {

                if (pos_new_station >= start_line1 && pos_new_station <= end_line1)
                    break;
                else
                    cout << "You entered a position outside line " << line << endl;
            }
            else if (line == 2)
            {

                if (pos_new_station >= start_line2 && pos_new_station <= end_line2)
                    break;
                else
                    cout << "You entered a position outside line " << line << endl;
            }
            else if (line == 3)
            {

                if (pos_new_station >= start_line3 && pos_new_station <= number_of_stations)
                    break;
                else
                    cout << "You entered a position outside line " << line << endl;
            }
        }

    }
    // Shift elements in arr to make space for the new station
    for (int i = number_of_stations; i > pos_new_station - 1; i--)
    {
        stations_read[i] = stations_read[i - 1];
    }

    cout << "Enter a name for the added station" << endl;
    string new_station_name;
    cin.ignore();
    getline(cin, new_station_name);
    arr[pos_new_station - 1] = new_station_name;
    ++line_size;

    // Update Rod_axis_station if necessary
    if (pos_new_station <= Rod_axis_station)
    {
        ++Rod_axis_station;
    }

    ++number_of_stations;

    // Update line indices
    if (pos_new_station <= end_line1 && pos_new_station >= start_line1)
    {
        ++Al_Shohadaa_line2;
        ++Attaba_line2;
        ++Attaba_line3;
        ++Nasser_line3;
        ++start_line2;
        ++start_line3;
        ++end_line2;
        ++end_line3;
        kit_kat_1_station++;
        kit_kat_2_station++;
        History_Shift_Handling(1, pos_new_station);

        if (pos_new_station < Al_Shohadaa_line1)
        {
            ++Al_Shohadaa_line1;
            ++Nasser_line1;
            ++end_line1;
        }
        else if (pos_new_station < Nasser_line1 && pos_new_station > Al_Shohadaa_line1)
        {
            ++Nasser_line1;
            ++end_line1;
        }
        else
        {
            ++end_line1;
        }
    }
    else if (pos_new_station <= end_line2 && pos_new_station >= start_line2)
    {
        ++Attaba_line3;
        ++Nasser_line3;
        ++end_line3;
        ++start_line3;
        kit_kat_1_station++;
        kit_kat_2_station++;
        start_station++;
        History_Shift_Handling(1, pos_new_station);
        if (start_station > pos_new_station)
            start_station++;
        if (pos_new_station < Al_Shohadaa_line2)
        {
            ++Al_Shohadaa_line2;
            ++Attaba_line2;
            ++end_line2;
        }
        else if (pos_new_station < Attaba_line2)
        {
            ++Attaba_line2;
            ++end_line2;
        }
        else
        {
            ++end_line2;
        }
    }
    else if (pos_new_station <= end_line3 && pos_new_station >= start_line3)
    {
        ++end_line3;
        kit_kat_1_station++;
        kit_kat_2_station++;
        start_station++;
        History_Shift_Handling(1, pos_new_station);
        if (start_station > pos_new_station)
            start_station++;
        if (pos_new_station < Attaba_line3)
        {
            ++Attaba_line3;
            ++Nasser_line3;
        }
        else if (pos_new_station < Nasser_line3)
        {
            ++Nasser_line3;
        }
    }
    cout << '\n';
    cout << "you added this station : " << new_station_name << '\n';

    if (line == 1)
    {
        for (int i = start_line1 - 1; i < end_line1; ++i) {
            cout << i + 1 << '.' << stations_read[i] << endl;

        }
    }
    else if (line == 2)
    {
        for (int i = start_line2 - 1; i < end_line2; ++i) {
            cout << i + 1 << '.' << stations_read[i] << endl;

        }
    }
    else if (line == 3)
    {
        for (int i = start_line3 - 1; i < number_of_stations; ++i) {
            cout << i + 1 << '.' << stations_read[i] << endl;

        }
    }

    admin_main_menu();
}

void remove_station(int& line_size, string arr_remove[], int line)
{

    while (true)
    {

        if (line == 1)
        {
            for (int i = start_line1 - 1; i < end_line1; ++i) {
                cout << i + 1 << '.' << stations_read[i] << endl;

            }
        }
        else if (line == 2)
        {
            for (int i = start_line2 - 1; i < end_line2; ++i) {
                cout << i + 1 << '.' << stations_read[i] << endl;

            }
        }
        else if (line == 3)
        {
            for (int i = start_line3 - 1; i < number_of_stations; ++i) {
                cout << i + 1 << '.' << stations_read[i] << endl;

            }
        }
        cout << "\nwhich position do you want to remove a station" << '\n';
        int pos_removed_station;
        cin >> pos_removed_station;
        if (!(pos_removed_station >= start_line1 && pos_removed_station <= end_line1))
        {
            do {

                cin >> pos_removed_station;
                if (line == 1)
                {
                    if (pos_removed_station >= start_line1 && pos_removed_station <= end_line1)
                        break;
                    else
                        cout << "You entered a position outside line " << line << endl;
                }
                else if (line == 2)
                {
                    if (pos_removed_station >= start_line2 && pos_removed_station <= end_line2)
                        break;
                    else
                        cout << "You entered a position outside line " << line << endl;
                }
                else if (line == 3)
                {
                    if (pos_removed_station >= start_line3 && pos_removed_station <= number_of_stations)
                        break;
                    else
                        cout << "You entered a position outside line " << line << endl;
                }
            } while (true);
        }

        if (!(pos_removed_station == Nasser_line3 || pos_removed_station == Nasser_line1 ||
            pos_removed_station == Attaba_line3 || pos_removed_station == Attaba_line2 ||
            pos_removed_station == Al_Shohadaa_line2 || pos_removed_station == Al_Shohadaa_line1))
        {
            string removedsation = stations_read[pos_removed_station - 1];
            for (int i = pos_removed_station - 1; i < number_of_stations - 1; ++i)
            {
                stations_read[i] = stations_read[i + 1];
            }

            --number_of_stations;

#if 1

            if (pos_removed_station <= end_line1 && pos_removed_station >= start_line1)
            {

                --Al_Shohadaa_line2;
                --Attaba_line2;
                --Attaba_line3;
                --Nasser_line3;
                --start_line2;
                --start_line3;
                --end_line2;
                --end_line3;
                --end_line1;
                kit_kat_1_station--;
                kit_kat_2_station--;
                History_Shift_Handling(0, pos_removed_station);
                if (pos_removed_station < Al_Shohadaa_line1)
                {
                    --Al_Shohadaa_line1;
                    --Nasser_line1;

                }
                else if (pos_removed_station < Nasser_line1 && pos_removed_station > Al_Shohadaa_line1)
                {
                    --Nasser_line1;

                }

            }
            else if (pos_removed_station <= end_line2 && pos_removed_station >= start_line2)
            {
                --Attaba_line3;
                --Nasser_line3;
                --end_line3;
                --start_line3;
                kit_kat_1_station--;
                kit_kat_2_station--;
                History_Shift_Handling(0, pos_removed_station);
                if (pos_removed_station < Al_Shohadaa_line2)
                {
                    --Al_Shohadaa_line2;
                    --Attaba_line2;
                    --end_line2;
                }
                else if (pos_removed_station < Attaba_line2)
                {
                    --Attaba_line2;
                    --end_line2;
                }
                else
                {
                    --end_line2;
                }
            }
            else if (pos_removed_station <= end_line3 && pos_removed_station >= start_line3)
            {
                --end_line3;
                kit_kat_1_station--;
                kit_kat_2_station--;
                History_Shift_Handling(0, pos_removed_station);
                if (pos_removed_station < Attaba_line3)
                {
                    --Attaba_line3;
                    --Nasser_line3;
                }
                else if (pos_removed_station < Nasser_line3)
                {
                    --Nasser_line3;
                }
            }
#endif

            cout << "\nthe removed station is : " << removedsation << '\n';
            break;
        }
        else
        {
            cout << "you can not remove transaction station\n";
        }
    }
    cout << '\n';
    if (line == 1)
    {
        for (int i = start_line1 - 1; i < end_line1; ++i) {
            cout << i + 1 << '.' << stations_read[i] << endl;

        }
    }
    else if (line == 2)
    {
        for (int i = start_line2 - 1; i < end_line2; ++i) {
            cout << i + 1 << '.' << stations_read[i] << endl;

        }
    }
    else if (line == 3)
    {
        for (int i = start_line3 - 1; i < number_of_stations; ++i) {
            cout << i + 1 << '.' << stations_read[i] << endl;

        }
    }
    cout << endl;
    admin_main_menu();
}

void edit(int line_size, string global_line[], int line)
{

    int number;
    int count = 0;
    cout << '\n';
    if (line == 1)
    {
        for (int i = start_line1 - 1; i < end_line1; ++i) {
            cout << i + 1 << '.' << stations_read[i] << endl;

        }
    }
    else if (line == 2)
    {
        for (int i = start_line2 - 1; i < end_line2; ++i) {
            cout << i + 1 << '.' << stations_read[i] << endl;

        }
    }
    else if (line == 3)
    {
        for (int i = start_line3 - 1; i < number_of_stations; ++i) {
            cout << i + 1 << '.' << stations_read[i] << endl;

        }
    }
    cout << "\nenter which station you want to change it is name : ";
    cin >> number;
    cout << '\n';
    string currentname = stations_read[number - 1];
    cin.ignore();
    cout << "the new name of the station : ";
    getline(cin, stations_read[number - 1]);
    cout << '\n';
    if (line == 1)
    {
        for (int i = start_line1 - 1; i < end_line1; ++i) {
            cout << i + 1 << '.' << stations_read[i] << endl;

        }
    }
    else if (line == 2)
    {
        for (int i = start_line2 - 1; i < end_line2; ++i) {
            cout << i + 1 << '.' << stations_read[i] << endl;

        }
    }
    else if (line == 3)
    {
        for (int i = start_line3 - 1; i < number_of_stations; ++i) {
            cout << i + 1 << '.' << stations_read[i] << endl;

        }
    }
    cout << "\nyou changed the name of station from " << currentname << " into " << stations_read[number - 1] << '\n';
    admin_main_menu();
}

void user_main_menu()
{
    while (true)
    {
        cout << "What do you want to do\npress 1 to go to subscription System \n";
        cout << "press 2 to Modify your account data\n";
        cout << "press 3 to go ride\n";
        cout << "press 4 to show history\n";
        cout << "press 5 to log out\n";
        cout << "Press 6 to terminate the system\n";
        int choicee;
        cin >> choicee;
        while (cin.fail() || choicee < 1 || choicee > 6)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid choice! Please enter 1, 2, 3, 4 or 5: \n";
            cin >> choicee;
        }
        if (choicee == 1)
        {
            subscription_system_for_user_main_menu();
        }
        else if (choicee == 2)
        {
            editPersonalData();
        }
        else if (choicee == 3)
        {
            if (subscipetion_or_not[global_id] == 0) {
                cout << "Available Subscription Plans:\n";
                for (int i = 0; i < subscription_count; i++) {
                    cout << i + 1 << ". " << subscriptions[i].plan_name << " (" << subscriptions[i].plan_symbol << ")\n";
                }
                cout << "Please enter the number of the plan you want to select: ";
                int num;
                cin >> num;
                while (num < 1 || num > subscription_count) {
                    cout << "Invalid option. Please enter a valid plan number:" << endl;
                    cin >> num;
                }

                subscriptiondataentry(num - 1); // Pass the index of the selected plan
                calculating_payment_and_expirydate();

                if (users[global_id].subscribiondetails.planType == 'W') {
                    addFundsToSmartWallet();
                }
                else {
                    deductSubscriptionPayment();
                }
                cout << "Your subscription has been successfully created!" << endl;
                subscipetion_or_not[global_id] = 1; // Mark as subscribed
            }

            while (subscipetion_or_not[global_id] == 1)
            {
                system_ride();
                cout << "Do you want to user home agian or book another ride (y/n)\n";
                char choice;
                cin >> choice;
                choice = toupper(choice);
                while (choice != 'Y' && choice != 'N')
                {
                    cout << "Invalid choice! Please enter 'y' for Yes or 'n' for No: \n";
                    cin >> choice;
                    choice = toupper(choice);
                }
                if (choice == 'N')
                {
                    system_ride();
                }
                else if (choice == 'Y')
                {
                    break;
                }
                else
                {
                    cout << "Invalid choice! Please enter 'y' for Yes or 'n' for No: \n";
                }
            }
        }
        else if (choicee == 4)
        {
            output_History_user_version();
            user_main_menu();
        }
        else if (choicee == 5)
        {
            start_menu();
        }
        else if (choicee == 6)
        {
            storage_the_data_of_user_and_admin();
            storage_the_data_of_statistics();
            subsctriprion_file_output();

            exit(0);
        }
    }
}

void admin_main_menu()
{
    while (true)
    {
        cout << "What do you want to do\n";
        cout << "press 1 to view all accounts \n";
        cout << "press 2 to Modify account data\n";
        cout << "press 3 to delete account\n";
        cout << "press 4 to System History\n";
        cout << "press 5 to system statistics\n";
        cout << "press 6 to Subscriptions & Zones Management\n";
        cout << "press 7 to modify stations\n";
        cout << "Press 8 to log out\n";
        cout << "Press 9 to terminate the system\n";
        int choicee;
        cin >> choicee;
        while (cin.fail() || choicee < 1 || choicee > 10)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid choice! Please enter from 1 to 10: \n";
            cin >> choicee;
        }
        if (choicee == 1)
        {
            view_all_accounts();
        }
        else if (choicee == 2)
        {
            modifying_account(id);
        }
        else if (choicee == 3)
        {
            delete_account();
        }
        else if (choicee == 4)
        {
            output_History_admin_version();
        }
        else if (choicee == 5)
        {
            statistics();
        }
        else if (choicee == 6)
        {
            cout << "Press 1 to Edit Subscription\nPress 2 to Edit Zones control\n";
            int choose;
            cin >> choose;
            while (cin.fail() || choose < 1 || choose > 2)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid choice! Please enter from 1 to 2:\nPress 1 to Edit Subscription\nPress 2 to Edit Zones control\n";
                cin >> choose;
            }
            if (choose == 1)
            {
                Admin_Subscriptions_control(subscriptions, subscription_count);

            }
            else if (choose == 2)
            {
                changing_prices_for_zones_for_zones_for_zones_for_zones_for_zones();
            }
        }
        else if (choicee == 7)
        {
            int choiceee;
            cout << "choose 1 to add a station 2 to remove station 3 to edit station's name\n";
            cin >> choiceee;
            int line;
            if (choiceee == 1)
            {
                cout << "which line you want to add the station to 1 , 2 or 3\n"; cin >> line;
                if (line == 1)
                {
                    add_station(line1_size, stations_read, line);
                }
                else if (line == 2)
                {
                    add_station(line2_size, stations_read, line);
                }
                else if (line == 3)
                    add_station(line3_size, stations_read, line);
                else
                    cout << "invalid number it got to be between 1 to 3\n";
            }

            else if (choiceee == 2) {

                cout << "which line you want to add the station to 1 , 2 or 3\n";
                cin >> line;
                if (line == 1)
                {
                    remove_station(line1_size, stations_read, line);
                }
                else if (line == 2)
                {
                    remove_station(line2_size, stations_read, line);
                }
                else if (line == 3)
                    remove_station(line3_size, stations_read, line);
                else
                    cout << "invalid number it got to be between 1 to 3\n";
            }

            else if (choiceee == 3)
                cout << "which line you want to add the station to 1 , 2 or 3\n"; cin >> line;
            if (line == 1)
            {
                edit(line1_size, stations_read, line);
            }
            else if (line == 2)
            {
                edit(line2_size, stations_read, line);
            }
            else if (line == 3)
                edit(line3_size, stations_read, line);
            else
                cout << "invalid number it got to be between 1 to 3\n";
        }
        else if (choicee == 8)
        {
            start_menu();
        }
        else if (choicee == 9)
        {
            storage_the_data_of_user_and_admin();
            storage_the_data_of_statistics();
            subsctriprion_file_output();

            exit(0);
        }
    }
}

void login_form()
{
    int itration = 0;
    while (true)
    {
        int id;
        string password;
        cout << "Please Enter your ID \n";
        cin >> id;

        while (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a valid ID (digits only): \n";
            cin >> id;
            itration++;
            if (itration > 2)
            {
                cout << "Trials error you Entered 3 times wrong id\n";
                start_menu();
            }
        }

        if (!isUnique[id])
        {
            itration++;
            cout << "This ID does not exist! Please try again.\n";
            if (itration > 2)
            {
                cout << "Trials error you Entered 3 times wrong id\n";
                start_menu();
            }
            continue;
        }

        global_id = id;

        cout << "Please Enter your password \n";
        hidding_password_write(password);

        if (arr_user[id].role == 'A')
        {
            admin_main_menu();
        }

        else if (arr_user[id].role == 'U')
        {
            if (password == arr_user[id].password)
            {
                cout << "\nYou have logged in successfully as User\n";
                cout << "Hello " << arr_user[id].name << endl;
                user_main_menu();
                break;
            }
            else
            {
                cout << "Incorrect password for User! Please try again.\n";
            }
        }
        else
        {
            cout << "Invalid role for this ID! Please contact support.\n";
        }
    }
}

char exit_or_not()
{
    char exit;
    cout << "do you want to terminate the system(Y/N)\n";
    cin >> exit;
    exit = toupper(exit);
    return exit;
}

void changing_price_for_zones__menu()
{
    int answer;
    cout << "Which zone do you want to change it's price?\n";
    cout << "Press 1 to change zone-1 price\nPress 2 to change zone-2 price\nPress 3 to change zone-3 price\nPress 4 to change zone-4 price\nor 0 to exit\n";
    cin >> answer;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    if (answer == 1)
    {
        do
        {
            cout << "enter your new price for this zone: ";
            cin >> New_Zone1_price;
            cout << "+-----------------------------------------------------------------------------+" << endl;

            if (New_Zone1_price == Zone1_price)
            {
                cout << "it's already current price!\n";
                cout << "Press 1 to enter another price\n2 to exit\n";
                cin >> answer;
                cout << "+-----------------------------------------------------------------------------+" << endl;
            }

            else if (New_Zone1_price < 0)
            {
                cout << "you must make it a postive price!\n";
                cout << "Press 1 to enter another price\nPress 2 to exit\n";
                cin >> answer;
                cout << "+-----------------------------------------------------------------------------+" << endl;
            }
            else if (cin.fail())
            {
                cin.clear();

                // leave the rest of the line
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // Ask the user to enter a valid int number only
                cout << "Wrong input,Please enter a number" << endl;
            }
            else if (New_Zone1_price >= 0)
            {
                Zone1_price = New_Zone1_price;
                break;
            }
            else
            {
                cout << "Please Enter a vaild choice" << endl;
            }
        } while (true);
    }
    else if (answer == 2)
    {
        do
        {
            cout << "enter your new price for this zone: ";
            cin >> New_Zone2_price;
            cout << "+-----------------------------------------------------------------------------+" << endl;

            if (New_Zone2_price == Zone2_price)
            {
                cout << "it's already current price!\n";
                cout << "Press 1 to enter anther price\nPress 2 to exit\n";
                cin >> answer;
                cout << "+-----------------------------------------------------------------------------+" << endl;
            }

            else if (New_Zone2_price < 0)
            {
                cout << "you must make it a postive price!\n";
                cout << "Press 1 to enter anther price\nPress 2 to exit\n";
                cin >> answer;
                cout << "+-----------------------------------------------------------------------------+" << endl;
                if (answer == 2)
                {
                    changing_price_for_zones__menu();
                }
            }
            else if (cin.fail())
            {
                cin.clear();

                // leave the rest of the line
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // Ask the user to enter a valid int number only
                cout << "Wrong input,Please enter a number" << endl;
            }
            else if (New_Zone2_price >= 0)
            {
                Zone2_price = New_Zone2_price;
                break;
            }
            else
            {
                cout << "Please Enter a vaild choice" << endl;
            }
        } while (true);
    }
    else if (answer == 3)
    {
        do
        {
            cout << "enter your new price for this zone.\n";
            cin >> New_Zone3_price;
            cout << "+-----------------------------------------------------------------------------+" << endl;

            if (New_Zone3_price == Zone3_price)
            {
                cout << "it's already current price!\n";
                cout << "Press 1 to enter anther price\nPress 2 to exit\n";
                cin >> answer;
                cout << "+-----------------------------------------------------------------------------+" << endl;
            }

            else if (New_Zone3_price < 0)
            {
                cout << "you must make it a postive price!\n";
                cout << "Press 1 to enter anther price\nPress 2 to exit\n";
                cin >> answer;
                cout << "+-----------------------------------------------------------------------------+" << endl;
            }
            else if (cin.fail())
            {
                cin.clear();

                // leave the rest of the line
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // Ask the user to enter a valid int number only
                cout << "Wrong input,Please enter a number" << endl;
            }
            else if (New_Zone3_price >= 0)
            {
                Zone3_price = New_Zone3_price;
                break;
            }
            else
            {
                cout << "Please Enter a vaild choice" << endl;
            }
        } while (true);
    }
    else if (answer == 4)
    {
        do
        {
            cout << "enter your new price for this zone.\n";
            cin >> New_Zone4_price;
            cout << "+-----------------------------------------------------------------------------+" << endl;

            if (New_Zone4_price == Zone4_price)
            {
                cout << "it's already current price!\n";
                cout << "Press 1 to enter anther price\nPress 2 to exit\n";
                cin >> answer;
                cout << "+-----------------------------------------------------------------------------+" << endl;
            }

            else if (New_Zone4_price < 0)
            {
                cout << "you must make it a postive price!\n";
                cout << "Press 1 to enter anther price\nPress 2 to exit\n";
                cin >> answer;
            }
            else if (cin.fail())
            {
                cin.clear();

                // leave the rest of the line
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // Ask the user to enter a valid int number only
                cout << "Wrong input,Please enter a number" << endl;
            }
            else if (New_Zone4_price >= 0)
            {
                Zone4_price = New_Zone4_price;
                break;
            }
            else
            {
                cout << "Please Enter a vaild choice" << endl;
            }
        } while (true);
    }
    else if (answer == 0)
    {
        changing_prices_for_zones_for_zones_for_zones_for_zones_for_zones();
    }
    else if (cin.fail())
    {
        cin.clear();

        // leave the rest of the line
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Ask the user to enter a valid int number only
        cout << "Wrong input,Please enter a number" << endl;
    }
    else
    {
        cout << "Please Enter a vaild choice" << endl;
    }
}

void changing_prices_for_zones_for_zones_for_zones_for_zones_for_zones()
{
    int New_Zone1_price;
    int New_Zone2_price;
    int New_Zone3_price;
    int New_Zone4_price;
    int answer;
    do
    {
        cout << "Press 1 to view zones with prices\nPress 2 to edit zones prices\nPress 3 to return to main menu\n";
        cin >> answer;
        cout << "+-----------------------------------------------------------------------------+" << endl;

        if (answer == 1)
        {
            cout << "zone-1 price: " << Zone1_price << endl;
            cout << "zone-2 price: " << Zone2_price << endl;
            cout << "zone-3 price: " << Zone3_price << endl;
            cout << "zone-4 price: " << Zone4_price << endl;
            cout << "+-----------------------------------------------------------------------------+" << endl;
            changing_prices_for_zones_for_zones_for_zones_for_zones_for_zones();
        }
        else if (answer == 2)
        {
            do
            {
                changing_price_for_zones__menu();
            } while (true);
        }
        else if (answer == 3)
        {
            cout << "return to main menu" << endl;
            admin_main_menu();
        }
        else if (cin.fail())
        {
            cin.clear();

            // leave the rest of the line
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Ask the user to enter a valid int number only
            cout << "Wrong input,Please enter a number" << endl;
        }
        else
        {
            cout << "Please Enter a vaild choice" << endl;
        }
    } while (answer > 0 || answer < 3);
}

int zone_to_price(int selected_zone)
{
    if (arr_user[global_id].age >= 60) // Apply 50% discount for age >= 60
    {
        if (selected_zone == 1)
            return Zone1_price / 2;
        else if (selected_zone == 2)
            return Zone2_price / 2;
        else if (selected_zone == 3)
            return Zone3_price / 2;
        else if (selected_zone == 4)
            return Zone4_price / 2;
    }
    else
    {
        if (selected_zone == 1)
            return Zone1_price;
        else if (selected_zone == 2)
            return Zone2_price;
        else if (selected_zone == 3)
            return Zone3_price;
        else if (selected_zone == 4)
            return Zone4_price;
    }
    return -1;
}
#pragma endregion

#pragma region subscriptions


void user_data_entry()
{
    // User data entry

    cout << "Please Enter balance you want to add : ";
    cin >> users[global_id].balance;
    while (users[global_id].balance < 0)
    {
        cout << "Invalid balance. Please enter a valid balance:";
        cin >> users[global_id].balance;
    }
}

void zoneselection(int& numberofstations)
{
    if (numberofstations >= 1 && numberofstations <= 9)
    {
        users[global_id].subscribiondetails.zones = "Zone-1";
    }
    else if (numberofstations >= 10 && numberofstations <= 16)
    {
        users[global_id].subscribiondetails.zones = "Zone-2";
    }
    else if (numberofstations >= 17 && numberofstations <= 23)
    {
        users[global_id].subscribiondetails.zones = "Zone-3";
    }
    else if (numberofstations > 23)
    {
        users[global_id].subscribiondetails.zones = "Zone-4";
    }
}

void subscriptiondataentry(int planIndex) {
    users[global_id].subscribiondetails.planType = subscriptions[planIndex].plan_symbol;
    cout << "You have selected: " << subscriptions[planIndex].plan_name << endl;
    // Use monthly or yearly prices based on the plan type
    int zone;
    if (users[global_id].subscribiondetails.zones == "Zone-1")
        zone = 1;
    else if (users[global_id].subscribiondetails.zones == "Zone-2")
        zone = 2;
    else if (users[global_id].subscribiondetails.zones == "Zone-3")
        zone = 3;
    else if (users[global_id].subscribiondetails.zones == "Zone-4")
        zone = 4;

    if (subscriptions[planIndex].is_monthly) {
        users[global_id].subscribiondetails.payment = subscriptions[planIndex].monthly_zone_prices[zone - 1];
    }
    else if (subscriptions[planIndex].is_yearly) {
        users[global_id].subscribiondetails.payment = subscriptions[planIndex].yearly_zone_prices[zone - 1];
    }

    else {
        // Use the already selected zone to calculate payment
        int zone = string_to_int_zone(); // Convert the selected zone to an integer
        if (subscriptions[planIndex].is_monthly) {
            users[global_id].subscribiondetails.payment = subscriptions[planIndex].monthly_zone_prices[zone - 1];
        }
        else if (subscriptions[planIndex].is_yearly) {
            users[global_id].subscribiondetails.payment = subscriptions[planIndex].yearly_zone_prices[zone - 1];
        }
    }
}

void calculating_payment_and_expirydate() {
    int duration = 0;

    // Find the selected subscription plan
    for (int i = 0; i < subscription_count; i++) {
        if (subscriptions[i].plan_symbol == users[global_id].subscribiondetails.planType) {
            // Case 1: Both monthly and yearly options
            if (subscriptions[i].is_monthly && subscriptions[i].is_yearly) {
                cout << "Press 1 for Monthly Plan\nPress 2 for Yearly Plan\n";
                cout << "Please select the duration of the plan: ";
                cin >> duration;
                while (duration < 1 || duration > 2) {
                    cout << "Invalid option. Please select 1 for Monthly Plan or 2 for Yearly Plan: ";
                    cin >> duration;
                }

                if (duration == 1) { // Monthly Plan
                    users[global_id].subscribiondetails.remainingTrips = subscriptions[i].monthly_remaining_trips;
                    users[global_id].subscribiondetails.payment = subscriptions[i].monthly_zone_prices[string_to_int_zone() - 1];

                    // Set expiry date based on duration_months
                    users[global_id].subscribiondetails.expiryDatedetails.day = users[global_id].subscribiondetails.activationDatedetails.day;
                    users[global_id].subscribiondetails.expiryDatedetails.month = (users[global_id].subscribiondetails.activationDatedetails.month + subscriptions[i].duration_months) % 12;
                    users[global_id].subscribiondetails.expiryDatedetails.year = users[global_id].subscribiondetails.activationDatedetails.year + (users[global_id].subscribiondetails.activationDatedetails.month + subscriptions[i].duration_months) / 12;
                }
                else if (duration == 2) { // Yearly Plan
                    users[global_id].subscribiondetails.remainingTrips = subscriptions[i].yearly_remaining_trips;
                    users[global_id].subscribiondetails.payment = subscriptions[i].yearly_zone_prices[string_to_int_zone() - 1];

                    // Set expiry date based on duration_years
                    users[global_id].subscribiondetails.expiryDatedetails.day = users[global_id].subscribiondetails.activationDatedetails.day;
                    users[global_id].subscribiondetails.expiryDatedetails.month = users[global_id].subscribiondetails.activationDatedetails.month;
                    users[global_id].subscribiondetails.expiryDatedetails.year = users[global_id].subscribiondetails.activationDatedetails.year + subscriptions[i].duration_years;
                }
            }
            // Case 2: Only Monthly Option
            else if (subscriptions[i].is_monthly) {
                users[global_id].subscribiondetails.remainingTrips = subscriptions[i].monthly_remaining_trips;
                users[global_id].subscribiondetails.payment = subscriptions[i].monthly_zone_prices[string_to_int_zone() - 1];

                // Set expiry date based on duration_months
                users[global_id].subscribiondetails.expiryDatedetails.day = users[global_id].subscribiondetails.activationDatedetails.day;
                users[global_id].subscribiondetails.expiryDatedetails.month = (users[global_id].subscribiondetails.activationDatedetails.month + subscriptions[i].duration_months) % 12;
                users[global_id].subscribiondetails.expiryDatedetails.year = users[global_id].subscribiondetails.activationDatedetails.year + (users[global_id].subscribiondetails.activationDatedetails.month + subscriptions[i].duration_months) / 12;
            }
            // Case 3: Only Yearly Option
            else if (subscriptions[i].is_yearly) {
                users[global_id].subscribiondetails.remainingTrips = subscriptions[i].yearly_remaining_trips;
                users[global_id].subscribiondetails.payment = subscriptions[i].yearly_zone_prices[string_to_int_zone() - 1];

                // Set expiry date based on duration_years
                users[global_id].subscribiondetails.expiryDatedetails.day = users[global_id].subscribiondetails.activationDatedetails.day;
                users[global_id].subscribiondetails.expiryDatedetails.month = users[global_id].subscribiondetails.activationDatedetails.month;
                users[global_id].subscribiondetails.expiryDatedetails.year = users[global_id].subscribiondetails.activationDatedetails.year + subscriptions[i].duration_years;
            }
            return; // Exit after processing the selected plan
        }
    }

    cout << "Error: Unable to calculate payment and expiry date for the selected plan.\n";
}

void deductSubscriptionPayment()
{

    while (users[global_id].balance < users[global_id].subscribiondetails.payment)
    {
        cout << "Insufficient balance to pay for the subscription plan!\n";
        cout << "Please add funds to your balance, the required payment for this subscription plan is: " << users[global_id].subscribiondetails.payment << "\n";
        cout << "Current balance: " << users[global_id].balance << " LE\n";
        cout << "Do you want to add money to your balance? (y/n): ";
        char choice;
        cin >> choice;
        choice = toupper(choice);
        while (cin.fail() || (choice != 'Y' && choice != 'N'))
        {
            cout << "Invalid choice! Please enter 'y' for Yes or 'n' for No: ";
            cin >> choice;
            choice = toupper(choice);
        }
        float addAmount;
        if (choice == 'N')
        {
            subscription_system_for_user_main_menu();
        }

        else if (choice == 'Y')
        {
            cout << "Add to balance amount of: ";
            cin >> addAmount;
        }
        if (addAmount <= 0)
        {
            cout << "Invalid amount! Please enter a positive value.\n";
            continue;
        }

        users[global_id].balance += addAmount;
    }

    users[global_id].balance -= users[global_id].subscribiondetails.payment;
    cout << "Subscription payment of " << users[global_id].subscribiondetails.payment << " LE deducted successfully!\n";
    cout << "Remaining balance: " << users[global_id].balance << " LE\n";
}

void addFundsToSmartWallet()
{
    int amount;
    cout << "Enter the amount to add to your Smart Wallet (in multiples of 10 LE): ";
    cin >> amount;

    while (amount % 10 != 0 || amount <= 0 || amount > 400 || (users[global_id].subscribiondetails.payment + amount > 400))
    {
        if (users[global_id].subscribiondetails.payment + amount > 400)
        {
            cout << "Cannot add " << amount << " LE. Maximum Smart Wallet balance of 400 LE exceeded!\n";
            cout << "Please enter an amount that is less than or equal to 400: ";
        }
        else
        {
            cout << "Invalid amount! Please enter a positive amount in multiples of 10 LE: ";
        }
        cin >> amount;
    }

    if (users[global_id].balance < amount)
    {
        cout << "Insufficient user balance! Please ensure you have enough funds to add to the Smart Wallet.\n";
        return;
    }

    users[global_id].balance -= amount;
    users[global_id].subscribiondetails.payment += amount;
    cout << "Funds added successfully! Current Smart Wallet balance: " << users[global_id].subscribiondetails.payment << " LE\n";
    cout << "Remaining user balance: " << users[global_id].balance << " LE\n";
}

void viewPersonalData()
{
    cout << "Personal Data:\n";
    cout << "Name: " << arr_user[global_id].name << "\n";
    cout << "Age: " << arr_user[global_id].age << "\n";
    cout << "ID: " << arr_user[global_id].id << "\n";
    cout << "Balance: " << users[global_id].balance << " LE\n";
    cout << "Zone: " << users[global_id].subscribiondetails.zones << "\n";
}

void editPersonalData()
{
    cout << "Editing Personal Data:\n";
    int option;
    cout << "Please select the field you want to edit:\n1. Name\n2. Age\n3. ID\n4. Balance\n5. Zone\n";
    cin >> option;
    while (option < 1 || option > 5)
    {
        cout << "Invalid option. Please select a valid field to edit:\n";
        cin >> option;
    }

    switch (option)
    {
    case 1:
        cout << "Enter new name: ";
        cin >> arr_user[global_id].name;
        break;
    case 2:
        cout << "Enter new age: ";
        cin >> arr_user[global_id].age;
        break;
    case 3:
        cout << "Enter new ID: ";
        int newID;
        cin >> newID;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Invalid ID! Please enter a valid ID: ";
            cin >> newID;
        }
        // Check if the new ID is unique
        while (!check_if_id_unique(newID))
        {
            cout << "This ID already exists! Please enter a unique ID: ";
            cin >> newID;
            while (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << "Invalid ID! Please enter a valid ID: ";
                cin >> newID;
            }
        }
        isUnique[newID] = 1;                  // Mark the new ID as unique
        isUnique[arr_user[global_id].id] = 0; // Mark the old ID as not unique
        break;

    case 4:
    {
        cout << "Enter new balance: ";
        cin >> users[global_id].balance;
        break;
    }

    case 5:
    {
        cout << "Enter new zone: ";
        cout << "Press 1 for Zone-1\n2 for Zone-2\n3 for Zone-3\n4 for Zone-4\n";
        int newZone;
        cin >> newZone;

        string newZoneName;
        // Determine the new zone name and payment
        switch (newZone)
        {
        case 1:
            newZoneName = "Zone-1";
            break;
        case 2:
            newZoneName = "Zone-2";
            break;
        case 3:
            newZoneName = "Zone-3";
            break;
        case 4:
            newZoneName = "Zone-4";
            break;
        default:
            cout << "Invalid option. Zone not changed.\n";
            return;
        }
        users[global_id].subscribiondetails.zones = newZoneName;
        cout << "Zone changed successfully to " << newZoneName << ".\n";
        break;
    }
    default:
        cout << "Invalid option! Please select a valid field to edit.\n";
        break;
    }
    cout << "Personal data updated successfully!\n";
}

void viewSubscriptionPlan() {
    if (users[global_id].subscribiondetails.planType == '\0') {
        cout << "You do not have an active subscription plan.\n";
        return;
    }

    string planType;
    bool planFound = false;
    for (int i = 0; i < subscription_count; i++) {
        if (subscriptions[i].plan_symbol == users[global_id].subscribiondetails.planType) {
            planType = subscriptions[i].plan_name;
            planFound = true;
            break;
        }
    }

    if (!planFound) {
        cout << "Error: The subscription plan you are using is no longer available.\n";
        return;
    }

    cout << "Subscription Plan:\n";
    cout << "Plan Name: " << planType << endl;
    cout << "Activation Date: " << users[global_id].subscribiondetails.activationDatedetails.day << "/"
        << users[global_id].subscribiondetails.activationDatedetails.month << "/"
        << users[global_id].subscribiondetails.activationDatedetails.year << endl;
    cout << "Expiry Date: " << users[global_id].subscribiondetails.expiryDatedetails.day << "/"
        << users[global_id].subscribiondetails.expiryDatedetails.month << "/"
        << users[global_id].subscribiondetails.expiryDatedetails.year << endl;
    cout << "Remaining Trips: " << users[global_id].subscribiondetails.remainingTrips << endl;
    cout << "Zones: " << users[global_id].subscribiondetails.zones << endl;
    cout << "Payment: " << users[global_id].subscribiondetails.payment << " LE" << endl;
}

void renewSubscriptionPlan() {
    if (users[global_id].subscribiondetails.planType == '\0') {
        cout << "You do not have an active subscription plan to renew.\n";
        return;
    }

    for (int i = 0; i < subscription_count; i++) {
        if (subscriptions[i].plan_symbol == users[global_id].subscribiondetails.planType) {
            cout << "Renewing subscription plan: " << subscriptions[i].plan_name << "...\n";
            calculating_payment_and_expirydate(); // Recalculate payment and expiry date
            deductSubscriptionPayment(); // Deduct payment from the user's balance
            cout << "Subscription plan renewed successfully!\n";
            return;
        }
    }

    cout << "Error: Unable to renew subscription plan. The plan may no longer exist.\n";
}

void changeSubscriptionPlan() {
    cout << "Change Subscription Plan:\n";
    cout << "Available Subscription Plans:\n";
    for (int i = 0; i < subscription_count; i++) {
        cout << i + 1 << ". " << subscriptions[i].plan_name << " (" << subscriptions[i].plan_symbol << ")\n";
    }

    cout << "Please enter the number of the new plan you want to select: ";
    int num;
    cin >> num;
    while (num < 1 || num > subscription_count) {
        cout << "Invalid option. Please enter a valid plan number:\n";
        cin >> num;
    }

    // Save the current plan type to history
    for (int i = 0; i < 4; i++) {
        if (previoussub[i] == '\0') {
            previoussub[i] = users[global_id].subscribiondetails.planType;
            break;
        }
    }

    // Update to the new plan
    users[global_id].subscribiondetails.planType = subscriptions[num - 1].plan_symbol;
    subscriptiondataentry(num - 1); // Update subscription details
    calculating_payment_and_expirydate(); // Recalculate payment and expiry date
    deductSubscriptionPayment(); // Deduct payment from the user's balance
    cout << "Subscription plan changed successfully to " << subscriptions[num - 1].plan_name << "!\n";
}

void subscription_system_for_user_main_menu() {
    while (true) {
        cout << "Subscription System Menu:\n";
        cout << "1. View Subscription Plan\n";
        cout << "2. Renew Subscription Plan\n";
        cout << "3. Change Subscription Plan\n";
        cout << "4. Back to Main Menu\n";
        cout << "Please select an option: ";
        int option;
        cin >> option;

        switch (option) {
        case 1:
            viewSubscriptionPlan();
            break;
        case 2:
            renewSubscriptionPlan();
            break;
        case 3:
            changeSubscriptionPlan();
            break;
        case 4:
            user_main_menu();
            return;
        default:
            cout << "Invalid option! Please select a valid option.\n";
        }
    }
}

void subscriptions_for_registration() {
    if (subscipetion_or_not[global_id] == 0) {
        user_data_entry();

        cout << "Thank you for your data, now moving to the zones step" << endl;

        // User zone
        cout << "1 to 9 stations\n10 to 16 stations\n17 to 23 stations\nMore than 23 stations" << endl;
        cout << "Enter the number for stations are in your way: ";
        int numberofstations;
        cin >> numberofstations;
        while (numberofstations < 1 || numberofstations > 88) {
            cout << "Invalid number of stations. Please enter a valid number of stations:" << endl;
            cin >> numberofstations;
        }
        zoneselection(numberofstations);

        cout << "Your zone is " << users[global_id].subscribiondetails.zones << endl;
        cout << "Now, Your zone is selected, move to the subscription step" << endl;
    }

    int option;
    cout << "1. Buy Travel Plan" << '\n';
    cout << "2. Back to Main Menu" << '\n';
    cout << "Please select an option: ";
    cin >> option;

    switch (option) {
    case 1:
        if (subscipetion_or_not[global_id] == 0) {
            cout << "Available Subscription Plans:\n";
            for (int i = 0; i < subscription_count; i++) {
                cout << i + 1 << ". " << subscriptions[i].plan_name << " (" << subscriptions[i].plan_symbol << ")\n";
            }
            cout << "Please enter the number of the plan you want to select: ";
            int num;
            cin >> num;
            while (num < 1 || num > subscription_count) {
                cout << "Invalid option. Please enter a valid plan number:" << endl;
                cin >> num;
            }

            subscriptiondataentry(num - 1); // Pass the index of the selected plan
            calculating_payment_and_expirydate();

            if (users[global_id].subscribiondetails.planType == 'W') {
                addFundsToSmartWallet();
            }
            else {
                deductSubscriptionPayment();
            }
            cout << "Your subscription has been successfully created!" << endl;
            subscipetion_or_not[global_id] = 1; // Mark as subscribed
        }
        else {
            cout << "You already subscribed.\n";
        }
        break;
    case 2:
        user_main_menu();
        break;
    default:
        cout << "Invalid option! Please select a valid option." << endl;
    }
    cout << endl;
    cout << "----------------------------------------" << endl;

    cout << "Thank you for using the Subscription System!" << endl;
}
void subsctriprion_file_output() {
    ofstream subs_output("subscriptions.txt", ios::out);
    for (int i = 0; i < max_subscription_plans; i++) {
        subs_output << subscriptions[i].plan_name << endl;
        subs_output << subscriptions[i].plan_symbol << endl;
        subs_output << subscriptions[i].duration_months << endl;
        subs_output << subscriptions[i].duration_years << endl;
        subs_output << subscriptions[i].is_monthly << endl;
        subs_output << subscriptions[i].is_yearly << endl;
        subs_output << subscriptions[i].monthly_remaining_trips << endl;
        subs_output << subscriptions[i].yearly_remaining_trips << endl;
        subs_output << subscriptions[i].monthly_zone_prices[0] << endl;
        subs_output << subscriptions[i].monthly_zone_prices[1] << endl;
        subs_output << subscriptions[i].monthly_zone_prices[2] << endl;
        subs_output << subscriptions[i].monthly_zone_prices[3] << endl;
        subs_output << subscriptions[i].yearly_zone_prices[0] << endl;
        subs_output << subscriptions[i].yearly_zone_prices[1] << endl;
        subs_output << subscriptions[i].yearly_zone_prices[2] << endl;
        subs_output << subscriptions[i].yearly_zone_prices[3] << endl;

    }
    subs_output.close();

}
void subscription_file_input() {
    ifstream subs_input("subscriptions.txt");
    string plan_name;
    char symbol;
    int duration_month;
    int duration_year;
    bool is_month;
    bool is_year;
    int m_remaing_trip;
    int y_remaing_trip;
    for (int i = 0; i < max_subscription_plans; i++) {
        getline(subs_input, plan_name);
        subs_input >> symbol;
        subs_input >> duration_month;
        subs_input >> duration_year;
        subs_input >> is_month;
        subs_input >> is_year;
        subs_input >> m_remaing_trip;
        subs_input >> y_remaing_trip;
        int n1;
        int y1;
        subscriptions[i].duration_years = duration_year;
        subscriptions[i].plan_name = plan_name;
        subscriptions[i].plan_symbol = symbol;
        subscriptions[i].duration_months = duration_month;
        subscriptions[i].is_monthly = is_month;
        subscriptions[i].is_yearly = is_year;
        subscriptions[i].monthly_remaining_trips = m_remaing_trip;
        subscriptions[i].yearly_remaining_trips = y_remaing_trip;
        for (int j = 0; j < 4; j++) {
            subs_input >> n1;
            subscriptions[i].monthly_zone_prices[j] = n1;
        }
        for (int j = 0; j < 4; j++) {
            subs_input >> y1;
            subscriptions[i].yearly_zone_prices[j] = y1;
        }
        subs_input.ignore(numeric_limits<streamsize>::max(), '\n');
    }


    subs_input.close();
}

#pragma endregion

#pragma region Rides
void record_ride()
{
    time_t now = time(nullptr);
    struct tm localTime;
    localtime_s(&localTime, &now);
    RideHistory[global_id].ride_of_user[numberf_of_trips].ride_date.tm_mday = localTime.tm_mday;
    RideHistory[global_id].ride_of_user[numberf_of_trips].ride_date.tm_mon = localTime.tm_mon + 1;
    RideHistory[global_id].ride_of_user[numberf_of_trips].ride_date.tm_year = localTime.tm_year + 1900;
    RideHistory[global_id].ride_of_user[numberf_of_trips].ride_date.tm_hour = localTime.tm_hour;
    RideHistory[global_id].ride_of_user[numberf_of_trips].ride_date.tm_min = localTime.tm_min;
    RideHistory[global_id].ride_of_user[numberf_of_trips].ride_date.tm_sec = localTime.tm_sec;
    RideHistory[global_id].ride_of_user[numberf_of_trips].ride_id = rand() % 10000 + 1;
    RideHistory[global_id].ride_of_user[numberf_of_trips].start_station = start_station;
    RideHistory[global_id].ride_of_user[numberf_of_trips].end_station = end_station;
    numberf_of_trips++;
}
void output_History_user_version()
{
    for (int i = 0; i < numberf_of_trips; i++)
    {
        if (RideHistory[global_id].ride_of_user[i].ride_id == 0)
            continue;
        cout << "Ride ID: " << RideHistory[global_id].ride_of_user[i].ride_id << endl;
        cout << "Start Station: " << stations[RideHistory[global_id].ride_of_user[i].start_station - 1] << endl;
        cout << "End Station: " << stations[RideHistory[global_id].ride_of_user[i].end_station - 1] << endl;
        cout << "Date: " << RideHistory[global_id].ride_of_user[i].ride_date.tm_mday << "/"
            << RideHistory[global_id].ride_of_user[i].ride_date.tm_mon << "/"
            << RideHistory[global_id].ride_of_user[i].ride_date.tm_year << endl;
        cout << "Time: " << RideHistory[global_id].ride_of_user[i].ride_date.tm_hour << ":"
            << RideHistory[global_id].ride_of_user[i].ride_date.tm_min << ":"
            << RideHistory[global_id].ride_of_user[i].ride_date.tm_sec << endl;
        cout << endl;
    }
}
void output_History_admin_version()
{
    for (int i = 0; i < number_of_users_and_admin; i++)
    {
        if (isUnique[i] == 1 && arr_user[i].role == 'U')
        {

            cout << "User ID: " << arr_user[i].id << endl;
            cout << "User Name: " << arr_user[i].name << endl;
            cout << "Ride History:" << endl;
            for (int j = 0; j < numberf_of_trips; j++)
            {
                if (RideHistory[i].ride_of_user[j].ride_id == 0)
                    continue;
                cout << "Ride ID: " << RideHistory[i].ride_of_user[j].ride_id << endl;
                cout << "Start Station: " << stations[RideHistory[i].ride_of_user[j].start_station - 1] << endl;
                cout << "End Station: " << stations[RideHistory[i].ride_of_user[j].end_station - 1] << endl;
                cout << "Date: " << RideHistory[i].ride_of_user[j].ride_date.tm_mday << "/"
                    << RideHistory[i].ride_of_user[j].ride_date.tm_mon << "/"
                    << RideHistory[i].ride_of_user[j].ride_date.tm_year << endl;
                cout << "Time: " << RideHistory[i].ride_of_user[j].ride_date.tm_hour << ":"
                    << RideHistory[i].ride_of_user[j].ride_date.tm_min << ":"
                    << RideHistory[i].ride_of_user[j].ride_date.tm_sec << endl;
                cout << endl;
            }
        }
    }
}

void start_loop_odd_cases(int i, int& start, int& end_station, int trans1, int trans2, string arr[])
{

    if (i == trans1 && i != start)
    {
        cout << "\t\t\t\t\t| " << endl
            << "\t\t\t\t\tV " << endl;
        if (trans2 != end_station)
            cout << "\t\t\t\t     " << arr[i - 1] << endl
            << "\n\t\t     =========> Changing Line <=========\n"
            << endl; // Arrow indicating transition between lines
    }
    else if (i != start)
    {
        cout << "\t\t\t\t\t| " << endl
            << "\t\t\t\t\tV " << endl
            << "\t\t\t\t     " << arr[i - 1] << endl;
    }
    else if (i == start_station && i != trans1)
    {
        cout << "\t\t\t\t     " << arr[start_station - 1] << endl;
    }
}

void start_loop_even_cases(int i, int& start, int& end_station, int trans1, int trans2, string arr[])
{
    if (i == trans2 && i != start)
    {
        cout << "\t\t\t\t\t| " << endl
            << "\t\t\t\t\tV " << endl;
        if (trans1 != end_station)
            cout << "\t\t\t\t       " << arr[i - 1] << endl
            << "\n\t\t     =========> Changing Line <=========\n"
            << endl; // Arrow indicating transition between lines
    }
    else if (i != start)
    {
        cout << "\t\t\t\t\t| " << endl
            << "\t\t\t\t\tV " << endl
            << "\t\t\t\t       " << arr[i - 1] << endl;
    }
    else if (i == start_station && i != trans2)
    {
        cout << "\t\t\t\t       " << arr[start_station - 1] << endl;
    }
}

void end_loop(int i, int end_station, string arr[])
{
    if (i != end_station)
    {
        cout << "\t\t\t\t     " << arr[i - 1] << endl
            << "\t\t\t\t\t|" << endl
            << "\t\t\t\t\tV" << endl;
    }

    else
    {
        cout << "\t\t\t\t     " << arr[end_station - 1] << endl;
    }
}

void case1(int& start, int& end_station, int trans1, int trans2, string arr[])
{
    int current_zone = current_zone_check(stations[start_station - 1]);
    int zone_counter = 1;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    cout << "|                                Your Metro MaP                               |" << endl;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    for (int i = start; i <= trans1; i++) // Display stations of first line (from start_stationto trans)
    {

        start_loop_odd_cases(i, start, end_station, trans1, trans2, stations);
        zone_checker(stations, current_zone, i, zone_counter);
    }

    for (int i = trans2; i >= end_station; i--) // Display stations of second line (from trans to end_station)
    {
        end_loop(i, end_station, stations);

        zone_checker(stations, current_zone, i, zone_counter);
    }
    if (users[global_id].subscribiondetails.planType == 'S' || users[global_id].subscribiondetails.planType == 'G')
        cout << endl
        << "Number of geographical zones = " << zone_counter << endl;
}

void case2(int& start, int& end_station, int trans1, int trans2, string arr[])
{
    int current_zone = current_zone_check(stations[start_station - 1]);
    int zone_counter = 1;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    cout << "|                                Your Metro MaP                               |" << endl;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    for (int i = start; i <= trans2; i++) // Display stations of second line (from start_stationto trans)
    {
        start_loop_even_cases(i, start, end_station, trans1, trans2, stations);

        zone_checker(stations, current_zone, i, zone_counter);
    }

    for (int i = trans1; i >= end_station; i--) // Display stations of first line (from trans to end_station)
    {

        end_loop(i, end_station, stations);

        zone_checker(stations, current_zone, i, zone_counter);
    }
    if (users[global_id].subscribiondetails.planType == 'S' || users[global_id].subscribiondetails.planType == 'G')
        cout << endl
        << "Number of geographical zones = " << zone_counter << endl;
}

void case3(int& start, int& end_station, int trans1, int trans2, string arr[]) // start_stationbefore trans and end after trans
{

    int current_zone = current_zone_check(stations[start_station - 1]);
    int zone_counter = 1;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    cout << "|                                Your Metro MaP                               |" << endl;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    for (int i = start; i <= trans1; i++) // Display stations of first line (from start_stationto trans)
    {

        start_loop_odd_cases(i, start, end_station, trans1, trans2, stations);

        zone_checker(stations, current_zone, i, zone_counter);
    }

    for (int i = trans2; i <= end_station; i++) // Display stations of second line (from trans to end_station)
    {

        end_loop(i, end_station, stations);

        zone_checker(stations, current_zone, i, zone_counter);
    }
    if (users[global_id].subscribiondetails.planType == 'S' || users[global_id].subscribiondetails.planType == 'G')
        cout << endl
        << "Number of geographical zones = " << zone_counter << endl;
}

void case4(int& start, int& end_station, int trans1, int trans2, string arr[]) // start_stationbefore trans and end after trans
{
    int current_zone = current_zone_check(stations[start_station - 1]);
    int zone_counter = 1;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    cout << "|                                Your Metro MaP                               |" << endl;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    for (int i = start; i <= trans2; i++) // Display stations of second line (from start_stationto trans)
    {
        start_loop_even_cases(i, start, end_station, trans1, trans2, stations);

        zone_checker(stations, current_zone, i, zone_counter);
    }

    for (int i = trans1; i <= end_station; i++) // Display stations of first line (from trans to end_station)
    {
        end_loop(i, end_station, stations);

        zone_checker(stations, current_zone, i, zone_counter);
    }
    if (users[global_id].subscribiondetails.planType == 'S' || users[global_id].subscribiondetails.planType == 'G')
        cout << endl
        << "Number of geographical zones = " << zone_counter << endl;
}

void case5(int& start, int& end_station, int trans1, int trans2, string arr[])
{
    int current_zone = current_zone_check(stations[start_station - 1]);
    int zone_counter = 1;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    cout << "|                                Your Metro MaP                               |" << endl;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    for (int i = start; i >= trans1; i--) // Display stations of first line (from start_stationto trans)
    {
        start_loop_odd_cases(i, start, end_station, trans1, trans2, stations);
        zone_checker(stations, current_zone, i, zone_counter);
    }

    for (int i = trans2; i >= end_station; i--) // Display stations of second line (from trans to end_station)
    {

        end_loop(i, end_station, stations);

        zone_checker(stations, current_zone, i, zone_counter);
    }
    if (users[global_id].subscribiondetails.planType == 'S' || users[global_id].subscribiondetails.planType == 'G')
        cout << endl
        << "Number of geographical zones = " << zone_counter << endl;
}

void case6(int& start, int& end_station, int trans1, int trans2, string arr[])
{
    int current_zone = current_zone_check(stations[start_station - 1]);
    int zone_counter = 1;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    cout << "|                                Your Metro MaP                               |" << endl;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    for (int i = start; i >= trans2; i--) // Display stations of second line (from start_stationto trans)
    {
        start_loop_even_cases(i, start, end_station, trans1, trans2, stations);

        zone_checker(stations, current_zone, i, zone_counter);
    }

    for (int i = trans1; i >= end_station; i--) // Display stations of first line (from trans to end_station)
    {

        end_loop(i, end_station, stations);

        zone_checker(stations, current_zone, i, zone_counter);
    }
    if (users[global_id].subscribiondetails.planType == 'S' || users[global_id].subscribiondetails.planType == 'G')
        cout << endl
        << "Number of geographical zones = " << zone_counter << endl;
}

void case7(int& start, int& end_station, int trans1, int trans2, string arr[])
{
    int current_zone = current_zone_check(stations[start_station - 1]);
    int zone_counter = 1;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    cout << "|                                Your Metro MaP                               |" << endl;
    cout << "+-----------------------------------------------------------------------------+" << endl;

    for (int i = start; i >= trans1; i--) // Display stations of first line (from start_stationto trans)
    {
        start_loop_odd_cases(i, start, end_station, trans1, trans2, stations);
        zone_checker(stations, current_zone, i, zone_counter);
    }

    for (int i = trans2; i <= end_station; i++) // Display stations of second line (from trans to end_station)
    {

        end_loop(i, end_station, stations);

        zone_checker(stations, current_zone, i, zone_counter);
    }
    if (users[global_id].subscribiondetails.planType == 'S' || users[global_id].subscribiondetails.planType == 'G')
        cout << endl
        << "Number of geographical zones = " << zone_counter << endl;
}

void case8(int& start, int& end_station, int trans1, int trans2, string arr[])
{
    int current_zone = current_zone_check(stations[start_station - 1]);
    int zone_counter = 1;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    cout << "|                                Your Metro MaP                               |" << endl;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    for (int i = start; i >= trans2; i--) // Display stations of second line (from start_stationto trans)
    {
        start_loop_even_cases(i, start, end_station, trans1, trans2, stations);

        zone_checker(stations, current_zone, i, zone_counter);
    }

    for (int i = trans1; i <= end_station; i++) // Display stations of first line (from trans to end_station)
    {
        end_loop(i, end_station, stations);

        zone_checker(stations, current_zone, i, zone_counter);
    }
    if (users[global_id].subscribiondetails.planType == 'S' || users[global_id].subscribiondetails.planType == 'G')
        cout << endl
        << "Number of geographical zones = " << zone_counter << endl;
}

int counting_Rod_to_Cairo(int& end_station, int& start)
{

    int result = ((start_station - kit_kat_1_station) + (end_station - (kit_kat_1_station + 5)));
    return result;
}

int counting_Cairo_to_Rod(int& end_station, int& start)
{

    int result = ((end_station - kit_kat_1_station) + (start_station - (kit_kat_1_station + 5)));

    return result;
}

void Rod_to_Cairo_list(int& end, int& start, int answer)
{
    string Rod_stations[7] = { "Kit-Kat", "Sudan", "Imbaba", "El-Bohy", "Al-Qawmeya Al-Arabiya", "Ring Road", "Rod al-Farag Axis" };
    string Cairo_stations[5] = { "El-Tawfikeya", "Wadi El-Nil", "Gamaat El Dowal Al-Arabiya", "Bulaq El-Dakroor", "Cairo University" };


    int zone_counter = 1;
    int selected_zone = (station_to_zone(counting_Rod_to_Cairo(end, start)));
    cout << "+-----------------------------------------------------------------------------+" << endl;
    cout << "|                                Your Metro MaP                               |" << endl;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    cout << "\t\t\t\t     " << Rod_stations[start - kit_kat_1_station] << endl; // First station

    for (int i = (start - 1 - kit_kat_1_station); i >= 0; i--)
    {
        cout << "\t\t\t\t\t| " << endl <<
            "\t\t\t\t\tV " << endl <<
            "\t\t\t\t     " << Rod_stations[i] << endl;
    }

    cout << "\t\t\t\t\t| " << endl <<
        "\t\t\t\t\tV " << endl;
    cout << "\t\t\t\t     " << Cairo_stations[0] << endl;
    for (int i = 1; i <= end - kit_kat_2_station; i++)
    {
        cout << "\t\t\t\t\t| " << endl <<
            "\t\t\t\t\tV " << endl <<
            "\t\t\t\t     " << Cairo_stations[i] << endl;
    }
    cout << "Number of selected stations = " << counting_Rod_to_Cairo(end, start) << endl;
    if (users[global_id].subscribiondetails.planType == 'S' || users[global_id].subscribiondetails.planType == 'G')
        cout << endl << "Number of geographical zones = " << zone_counter << endl;
    check_out(answer, selected_zone);
}

void Cairo_to_Rod_list(int& end, int& start, int answer)
{
    string Rod_stations[7] = { "Kit Kat ", "Sudan", "Imbaba ", "El-Bohy ", "Al-Qawmeya Al-Arabiya ", "Ring Road ", "Rod al-Farag Axis " };
    string Cairo_stations[5] = { "El-Tawfikeya ", "Wadi El-Nil", "Gamaat El Dowal Al-Arabiya ", "Bulaq El-Dakroor ", "Cairo University" };

    int zone_counter = 1;
    int selected_zone = (station_to_zone(counting_Cairo_to_Rod(end, start)));
    cout << "+-----------------------------------------------------------------------------+" << endl;
    cout << "|                                Your Metro MaP                               |" << endl;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    cout << "\t\t\t\t     " << Cairo_stations[start - kit_kat_2_station] << endl; // First station
    for (int i = (start - 1 - kit_kat_2_station); i >= 0; i--) // ( -1 ==> to start from second station )
    {
        cout << "\t\t\t\t\t| " << endl <<
            "\t\t\t\t\tV " << endl <<
            "\t\t\t\t     " << Cairo_stations[i] << endl;
    }
    cout << "\t\t\t\t\t| " << endl <<
        "\t\t\t\t\tV" << endl;
    cout << "\t\t\t\t     " << Rod_stations[0] << endl;
    for (int i = 1; i <= end - kit_kat_1_station; i++)
    {
        cout << "\t\t\t\t\t| " << endl <<
            "\t\t\t\t\tV " << endl <<
            "\t\t\t\t     " << Rod_stations[i] << endl;
    }
    cout << "Number of selected stations = " << counting_Cairo_to_Rod(end, start) << endl;
    if (users[global_id].subscribiondetails.planType == 'S' || users[global_id].subscribiondetails.planType == 'G')
        cout << endl << "Number of geographical zones = " << zone_counter << endl;
    check_out(answer, selected_zone);
}

void cases(int& start, int& end_station, int trans1, int trans2, string arr[])
{
    if (start_station < end_station)
    { // starting ascendingly
        if ((start_station <= trans1) && (end_station <= trans2))
        {
            case1(start, end_station, trans1, trans2, arr);
        }
        else if ((start_station <= trans1) && (end_station >= trans2))
        {
            case3(start, end_station, trans1, trans2, arr);
        }
        else if ((start_station >= trans1) && (end_station <= trans2))
        {
            case5(start, end_station, trans1, trans2, arr);
        }
        else if ((start_station >= trans1) && (end_station >= trans2))
        {
            case7(start, end_station, trans1, trans2, arr);
        }
    }
    else if (start_station > end_station)
    { // starting descendingly
        if ((start_station <= trans2) && (end_station <= trans1))
        {
            case2(start, end_station, trans1, trans2, arr);
        }
        else if ((start_station <= trans2) && (end_station >= trans1))
        {
            case4(start, end_station, trans1, trans2, arr);
        }
        else if ((start_station >= trans2) && (end_station <= trans1))
        {
            case6(start, end_station, trans1, trans2, arr);
        }
        else if ((start_station >= trans2) && (end_station >= trans1))
        {
            case8(start, end_station, trans1, trans2, arr);
        }
    }
}

void list_intersect_line_1_2(int& start, int& end_station, string arr[], int trans1 = Al_Shohadaa_line1, int trans2 = Al_Shohadaa_line2)
{
    cases(start, end_station, trans1, trans2, arr);
}

void list_intersect_line_2_3(int& start, int& end_station, string arr[], int trans2 = Attaba_line2, int trans3 = Attaba_line3)
{
    cases(start, end_station, trans2, trans3, arr);
}

void list_intersect_line_1_3(int& start, int& end_station, string arr[], int trans1 = Nasser_line1, int trans3 = Nasser_line3)
{
    cases(start, end_station, trans1, trans3, arr);
}

int counting_intersected_stations(int& start_station, int& end_station, int trans1, int trans2)
{
    if (start_station > end_station)
    {
        trans2 -= start_station;
        trans1 -= end_station;
        trans1 = abs(trans1);
        trans2 = abs(trans2);
        return trans1 + trans2 + 1;
    }
    else if (start_station < end_station)
    {
        trans1 -= start_station;
        trans2 -= end_station;
        trans1 = abs(trans1);
        trans2 = abs(trans2);
        return trans1 + trans2 + 1;
    }
}

void input_start_data(int& start_line, int& start_station)
{
    do
    {
        enter_startline();
        cin >> start_line;
        if (cin.fail())
        {
            cin.clear();

            // leave the rest of the line
            cin.ignore(numeric_limits<streamsize>::max(),
                '\n');

            // Ask the user to enter a valid int number only
            cout << "Wrong input,";
        }
        else
        {
            if (start_line > 0 && start_line < 4)
            {
                cout << "Please choose start_stationstation" << endl;
                start_station = choose_line(start_line, start_station);
                cout << "+-----------------------------------------------------------------------------+" << endl;

                break;
            }
            else
                cout << "Invalid line" << endl;
        }

    } while (true);
}

void input_end_data(int& end_line, int& end_station)
{
    do
    {
        enter_endline();
        cin >> end_line;
        if (cin.fail())
        {
            cin.clear();

            // leave the rest of the line
            cin.ignore(numeric_limits<streamsize>::max(),
                '\n');

            // Ask the user to enter a valid int number only
            cout << "Wrong input,";
        }
        else
        {
            if (end_line > 0 && end_line < 4)
            {
                cout << "Please choose end station" << endl;
                end_station = choose_line(end_line, end_station);
                cout << "+-----------------------------------------------------------------------------+" << endl;

                break;
            }
            else
                cout << "Invalid line" << endl;
        }

    } while (true);
}

void if_intersection(int& start, int& end_station, int& start_line, int& end_line, string arr[], int answer)
{

    do
    {
        if (arr[start_station - 1] == arr[end_station - 1])
        {
            cout << "Please Enter a different end station or start_stationstation" << endl;
            start_calc(start, end_station, end_line, start_line, answer);
        }
        else
        {
            break;
        }

    } while (true);

    if ((start_station >= start_line1 && start_station <= end_line1) && (end_station >= start_line2 && end_station <= end_line2) || (start_station >= start_line2 && start_station <= end_line2) && (end_station >= start_line1 && end_station <= end_line1)) // line 1 and line 2

    {
        int selected_stations = 0, selected_zone = 0;
        if ((start_station >= start_line1 && start_station <= end_line1) || (start_station >= start_line2 && start_station <= end_line2))
        {
            selected_stations = counting_intersected_stations(start, end_station, Al_Shohadaa_line1, Al_Shohadaa_line2);
            selected_zone = ((station_to_zone(selected_stations))); // converting station to zone
            if (arr_user[global_id].subscription_type != 'W')
            {
                if (zone_to_zone_check(selected_zone)) // comparing the converted zone with user zone
                {
                    cout << "+-----------------------------------------------------------------------------+" << endl;
                    list_intersect_line_1_2(start, end_station, stations_read); // lisiting stations of the trip
                    cout << "Number of selected stations = " << selected_stations << endl
                        << endl;
                    check_out(answer, selected_zone); // check out to deduct according to the user plantype
                }

                else
                {
                    trip_not_valid(start, end_station, end_line, start_line, answer);
                }
            }
            else
            {
                cout << "+-----------------------------------------------------------------------------+" << endl;
                list_intersect_line_1_2(start, end_station, stations_read); // lisiting stations of the trip
                cout << "Number of selected stations = " << selected_stations << endl
                    << endl;
                check_out(answer, selected_zone); // check out to deduct according to the user plantype
            }
        }
    }

    else if ((start_station >= start_line2 && start_station <= end_line2) && (end_station >= start_line3 && end_station <= end_line3) || (start_station >= start_line3 && start_station <= end_line3) && (end_station >= start_line2 && end_station <= end_line2)) // line 2 and line 3
    {

        int selected_stations = 0, selected_zone = 0;
        if ((start_station >= start_line3 && start_station <= end_line3) || (start_station >= start_line2 && start_station <= end_line2))
        {
            selected_stations = counting_intersected_stations(start, end_station, Attaba_line2, Attaba_line3);
            selected_zone = ((station_to_zone(selected_stations)));
            if (zone_to_zone_check(selected_zone))
            {
                cout << "+-----------------------------------------------------------------------------+" << endl;
                list_intersect_line_2_3(start, end_station, stations_read);
                cout << "Number of selected stations = " << selected_stations << endl
                    << endl;
                check_out(answer, selected_zone);
            }

            else
            {
                trip_not_valid(start, end_station, end_line, start_line, answer);
            }
        }
    }

    else if ((start_station >= start_line1 && start_station <= end_line1) && (end_station >= start_line3 && end_station <= end_line3) || (start_station >= start_line3 && start_station <= end_line3) && (end_station >= start_line1 && end_station <= end_line1)) // line 1 and line 3
    {

        int selected_stations = 0, selected_zone = 0;
        if ((start_station >= start_line1 && start_station <= end_line1) || ((start_station >= start_line3 && start_station <= end_line3)))
        {
            selected_stations = counting_intersected_stations(start, end_station, Nasser_line1, Nasser_line3);
            selected_zone = (station_to_zone(selected_stations));
            if (zone_to_zone_check(selected_zone))
            {
                cout << "+-----------------------------------------------------------------------------+" << endl;
                list_intersect_line_1_3(start, end_station, stations_read);
                cout << "Number of selected stations = " << selected_stations << endl
                    << endl;
                check_out(answer, selected_zone);
            }

            else
            {
                trip_not_valid(start, end_station, end_line, start_line, answer);
            }
        }
    }
}

int kit_kat_check(int& end, int& start)
{
    if (start <= Rod_axis_station && end <= Rod_axis_station) // to include Rod- El Farag Branch
        return 1;
    else if (start > Rod_axis_station && end > Rod_axis_station) // Cairo Branch Only 
        return 2;
    else if (((start > kit_kat_1_station && start <= Rod_axis_station) && end > Rod_axis_station)) // start at Rod-El Farag and end at Cairo
        return 5;
    else if ((end > kit_kat_1_station && end <= Rod_axis_station) && start > Rod_axis_station)// start at Cairo and end at Rod
        return 6;
    else if (start > Rod_axis_station)// start only at Cairo Branch
        return 3;
    else if (end > Rod_axis_station)// end only at Cairo Branch
        return 4;
}

void kitkat_branches(int& end, int& start)
{
    if (kit_kat_check(end, start) == 1)
    {
        string rod_El_farag_branch[] = { "Sudan", "Imbaba", "El-Bohy", "Al-Qawmeya Al-Arabiya", "Ring Road", "Rod al-Farag Axis" };
        for (int i = kit_kat_1_station; i < Rod_axis_station; i++)
        {
            rod_El_farag_branch[i] = stations_read[i];
        }
        for (int i = 0; i < 6; i++)
            stations[kit_kat_1_station + i] = rod_El_farag_branch[i];
    }
    else
    {
        string cairo_branch[] = { "El-Tawfikeya", "Wadi El-Nil", "Gamaat El Dowal Al-Arabiya", "Bulaq El-Dakroor", "Cairo University" };
        for (int i = kit_kat_2_station; i < number_of_stations; i++)
        {
            cairo_branch[i] = stations_read[i];
        }
        for (int i = 0; i < 5; i++)
            stations[kit_kat_1_station + i] = cairo_branch[i];

    }
}

void same_line_loop(int i, int start, string arr[])
{
    if (i != start)
    {
        cout << "\t\t\t\t\t| " << endl
            << "\t\t\t\t\tV " << endl
            << "\t\t\t\t     " << arr[i - 1] << endl;
    }
    else
    {
        cout << endl
            << "\t\t\t\t     " << arr[start_station - 1] << endl;
    }
}

void list_same_line(int& start, int& end_station, string arr[], user_struct arr_users[])
{
    int current_zone = current_zone_check(stations[start_station - 1]);
    int zone_counter = 1;

    if (start_station > end_station)
    {

        for (int i = start; i >= end_station; i--)
        {
            same_line_loop(i, start, stations_read);
            zone_checker(stations, current_zone, i, zone_counter);
        }
        if (users[global_id].subscribiondetails.planType == 'S' || users[global_id].subscribiondetails.planType == 'G')
            cout << endl
            << "Number of geographical zones = " << zone_counter << endl;
    }
    else if (start_station < end_station)
    {
        for (int i = start; i <= end_station; i++)
        {
            same_line_loop(i, start, stations_read);
            zone_checker(stations, current_zone, i, zone_counter);
        }
        if (users[global_id].subscribiondetails.planType == 'S' || users[global_id].subscribiondetails.planType == 'G')
            cout << endl
            << "Number of geographical zones = " << zone_counter << endl;
    }
}

void if_same_line(int& start, int& end_station, int& end_line, int& start_line, int answer)
{

    if (end_station - start_station > 0)
    {

        int selected_stations = end_station - start_station + 1;
        int selected_zone = (station_to_zone(selected_stations));
        if (zone_to_zone_check(selected_zone))
        {
            cout << "+-----------------------------------------------------------------------------+" << endl;
            cout << "|                                Your Metro MaP                               |" << endl;
            cout << "+-----------------------------------------------------------------------------+" << endl;
            list_same_line(start, end_station, stations_read, users);
            cout << "\nNumber of selected stations = " << selected_stations << endl;
            check_out(answer, selected_zone);
        }
        else
        {

            trip_not_valid(start, end_station, end_line, start_line, answer);
        }
    }

    else if (end_station - start_station < 0)
    {
        int selected_stations = start_station - end_station + 1;
        int selected_zone = (station_to_zone(selected_stations));
        if (zone_to_zone_check(selected_zone))
        {
            cout << "+-----------------------------------------------------------------------------+" << endl;
            list_same_line(start, end_station, stations_read, users);
            cout << "Number of selected stations = " << selected_stations << endl
                << endl;
            check_out(answer, selected_zone);
        }
        else
        {
            trip_not_valid(start, end_station, end_line, start_line, answer);
        }
    }

    else
    {
        cout << endl
            << "Please enter a different end or start_stationstation" << endl
            << endl;
        start_calc(start, end_station, end_line, start_line, answer);
    }
}

void check_line(int& start_line, int& end_line, int& end_station, int& start, string arr[], int answer)
{
    if (start_line == 3 || end_line == 3) // if line 3 is chosen
    {
        kitkat_branches(end_station, start); // choosing the suitable branch

        if (kit_kat_check(end_station, start) == 5) // start_stationat Rod-El Farag and end at Cairo
        {
            Rod_to_Cairo_list(end_station, start, answer);
        }
        else if (kit_kat_check(end_station, start) == 6) //  start_stationat Cairo and end at Rod-El Farag
        {
            Cairo_to_Rod_list(end_station, start, answer);
        }
        else if (kit_kat_check(end_station, start) == 2) //  Cairo Branch only
        {
            start_station -= stations_of_Rod_branch;
            end_station -= stations_of_Rod_branch;
        }
        else if (kit_kat_check(end_station, start) == 3) // start_stationonly at Cairo Branch
        {
            start_station -= stations_of_Rod_branch;
        }
        else if (kit_kat_check(end_station, start) == 4) // end only at Cairo Branch
        {
            end_station -= stations_of_Rod_branch;
        }
    }
    if (kit_kat_check(end_station, start) != 6 && kit_kat_check(end_station, start) != 5)
    {
        if (start_line == end_line) // if same line
        {
            if_same_line(start, end_station, end_line, start_line, answer);
        }
        else
        {
            if_intersection(start, end_station, start_line, end_line, arr, answer); // if different lines
        }
    }
}

int choose_line(int& line_num, int& station_num)
{
    if (line_num == 1)
    {

        cout << "+-----------------------------------------------------------------------------+" << endl;
        cout << "|                                 Line 1 Stations                             |" << endl;
        cout << "+-----------------------------------------------------------------------------+" << endl;
        for (int i = start_line1 - 1; i < end_line1; ++i) {
            cout << i + 1 << '.' << stations_read[i] << '\n';
        }
        cout << "+-----------------------------------------------------------------------------+" << endl;
        do
        {
            cin >> station_num;
            if (cin.fail())
            {
                cin.clear();

                // leave the rest of the line
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // Ask the user to enter a valid int number only
                cout << "Wrong input,Please enter a number" << endl;
            }
            else
            {
                if (station_num >= start_line1 && station_num <= end_line1)
                {
                    break;
                }
                else
                    cout << "Please Enter a valid station for Line 1" << endl;
            }

        } while (true);
    }
    else if (line_num == 2)
    {
        cout << "+-----------------------------------------------------------------------------+" << endl;
        cout << "|                                 Line 2 Stations                             |" << endl;
        cout << "+-----------------------------------------------------------------------------+" << endl;
        for (int i = start_line2 - 1; i < end_line2; ++i) {
            cout << i + 1 << '.' << stations_read[i] << '\n';
        }
        cout << "+-----------------------------------------------------------------------------+" << endl;
        do
        {
            cin >> station_num;
            if (cin.fail())
            {
                cin.clear();

                // leave the rest of the line
                cin.ignore(numeric_limits<streamsize>::max(),
                    '\n');

                // Ask the user to enter a valid int number only
                cout << "Wrong input,Please enter a number" << endl;
            }
            else
            {
                if (station_num >= start_line2 && station_num <= end_line2)
                {
                    break;
                }
                else
                    cout << "Please Enter a valid station for Line 2" << endl;
            }

        } while (true);
    }
    else if (line_num == 3)
    {
        cout << "+-----------------------------------------------------------------------------+" << endl;
        cout << "|                                 Line 3 Stations                             |" << endl;
        cout << "+-----------------------------------------------------------------------------+" << endl;
        for (int i = start_line3 - 1; i < end_line3; ++i) {
            cout << i + 1 << '.' << stations_read[i] << '\n';
        }

        cout << "+-----------------------------------------------------------------------------+" << endl;
        do
        {
            cin >> station_num;
            if (cin.fail())
            {
                cin.clear();

                // leave the rest of the line
                cin.ignore(numeric_limits<streamsize>::max(),
                    '\n');

                // Ask the user to enter a valid int number only
                cout << "Wrong input,Please enter a number" << endl;
            }
            else
            {
                if (station_num >= start_line3 && station_num <= end_line3)
                {
                    break;
                }
                else
                    cout << "Please Enter a valid station for Line 3" << endl;
            }

        } while (true);
    }
    return station_num;
}

void enter_startline()
{
    cout << "Please choose startline" << endl;
    cout << "1. Line 1" << endl
        << "2. Line 2" << endl
        << "3. Line 3" << endl;
}

void enter_endline()
{
    cout << "Please choose endline" << endl;
    cout << "1. Line 1" << endl
        << "2. Line 2" << endl
        << "3. Line 3" << endl;
}

void start_calc(int& start, int& end_station, int& end_line, int& start_line, int answer)
{
    do
    {
        input_start_data(start_line, start);
        input_end_data(end_line, end_station);
        do
        {

            cout << "Enter 1 to confirm your ride or 2 to restart" << endl;
            cin >> answer;
            if (cin.fail())
            {
                cin.clear();

                // leave the rest of the line
                cin.ignore(numeric_limits<streamsize>::max(),
                    '\n');

                // Ask the user to enter a valid int number only
                cout << "+-----------------------------------------------------------------------------+" << endl;
                cout << "Wrong input" << endl;
            }
            else
            {
                if (answer == 1)
                {
                    check_line(start_line, end_line, end_station, start, stations, answer);

                    break;
                }
                else if (answer == 2)
                {
                    break;
                }
                else
                {
                    cout << "+-----------------------------------------------------------------------------+" << endl;
                    cout << "Enter a valid number" << endl;
                }
            }

        } while (true);
        answer = 2; // remove
    } while (answer == 2);
}

int current_zone_check(string stations)
{
    for (int i = 0; i < 8; i++) // zone 1 is checked for all lines (default)
    {
        if (stations == zone_1[i]) // checking if current zone = zone 1
        {
            return 1;
        }
    }
    {

        for (int i = 0; i < 6; i++) //  checking if current zone = zone 5, 7 or 9
        {
            if (stations == zone_5[i])
            {
                return 5;
            }
            if (stations == zone_7[i])
            {
                return 7;
            }
            if (stations == zone_9[i])
            {
                return 9;
            }
        }

        for (int i = 0; i < 7; i++) // checking if current zone = zone 8
        {
            if (stations == zone_8[i])
            {
                return 8;
            }
        }

        for (int i = 0; i < 5; i++) // checking if current zone = zone 2
        {

            if (stations == zone_2[i])
            {
                return 2;
            }
        }
    }
    {
        for (int i = 0; i < 8; i++) // zone 1 is checked for all lines (default)
        {

            if (stations == zone_3[i]) // checking if current zone = zone 3
            {
                return 3;
            }
            if (stations == zone_6[i]) // checking if current zone = zone 6
            {
                return 6;
            }
        }
    }
    {
        for (int i = 0; i < 10; i++)
        {
            if (stations == zone_10[i]) // checking if current zone = zone 10
            {
                return 10;
            }
        }
        for (int i = 0; i < 13; i++)
        {
            if (stations == zone_11[i]) // checking if current zone = zone 11
            {
                return 11;
            }
        }
        for (int i = 0; i < 8; i++)
        {
            if (stations == zone_4[i]) // checking if current zone = zone 4
            {
                return 4;
            }
        }
    }
    return 0;
}

void zone_checker(string stations[], int& current_zone, int i, int& zone_counter)
{

    int new_current_zone = current_zone_check(stations[i - 1]);
    if (new_current_zone != current_zone && new_current_zone != 0)
    {
        current_zone = new_current_zone;
        zone_counter++;
    }
    else
        current_zone = new_current_zone;
}

int station_to_zone(int numberofstations)
{
    if (numberofstations >= 1 && numberofstations <= 9)
    {
        return 1;
    }
    else if (numberofstations >= 10 && numberofstations <= 16)
    {
        return 2;
    }
    else if (numberofstations >= 17 && numberofstations <= 23)
    {
        return 3;
    }
    else if (numberofstations > 23)
    {

        return 4;
    }
}

int string_to_int_zone() // we need integers in calculation
{
    if (users[global_id].subscribiondetails.zones == "Zone-1")
        return 1;
    else if (users[global_id].subscribiondetails.zones == "Zone-2")
        return 2;
    else if (users[global_id].subscribiondetails.zones == "Zone-3")
        return 3;
    else if (users[global_id].subscribiondetails.zones == "Zone-4")
        return 4;
    else
        return -1;
}

bool zone_to_zone_check(int selected_zone)
{
    if (users[global_id].subscribiondetails.planType == 'S' || users[global_id].subscribiondetails.planType == 'G')
    {
        users[global_id].zone = string_to_int_zone();
        if (selected_zone <= users[global_id].zone)
            return 1;
        else
            return 0;
    }
    else if (users[global_id].subscribiondetails.planType == 'W')
    {
        return 1;
    }
}

void trips_deduction_general_or_scholar()
{
    if (users[global_id].subscribiondetails.remainingTrips > 0)
    {
        --users[global_id].subscribiondetails.remainingTrips;
        cout << "+-----------------------------------------------------------------------------+" << endl;
        cout << "Your trip is sucessfully booked" << endl
            << "Remaining trips = " << users[global_id].subscribiondetails.remainingTrips << endl;
        cout << "+-----------------------------------------------------------------------------+" << endl;
    }
    else if (users[global_id].balance < users[global_id].subscribiondetails.payment)
    {
        do
        {
            cout << "+-----------------------------------------------------------------------------+" << endl;
            cout << "You have no more trips" << endl
                << "Please top up your balance and renew subscription" << endl
                << "Enter 1 return to main menu" << endl;
            if (answer == 1)
            {
                user_main_menu();
            }
            cout << "+-----------------------------------------------------------------------------+" << endl;

        } while (true);
    }
    else
    {
        cout << "+-----------------------------------------------------------------------------+" << endl;
        cout << "You have no more trips" << endl
            << "Please renew your subscription" << endl;
        cout << "+-----------------------------------------------------------------------------+" << endl;
    }
}

void wallet_dedcution(int selected_zone)
{
    int price = zone_to_price(selected_zone);
    if (price == -1)
    {
        cout << "Invalid zone selected. Please try again." << endl;
        user_main_menu();
        return;
    }
    if (users[global_id].subscribiondetails.payment >= price)
    {
        users[global_id].subscribiondetails.payment -= price;
        cout << "Your trip is successfully booked and " << price
            << " L.E. is deducted " << endl
            << "Your current balance is " << users[global_id].balance << endl
            << "Your smart wallet holds " << users[global_id].subscribiondetails.payment << "L.E." << endl;
    }
    else
    {
        cout << "Your current balance is " << users[global_id].balance << endl
            << "Your smart wallet holds " << users[global_id].subscribiondetails.payment << "L.E." << endl
            << "Please Recharge and Try again" << endl;
        user_main_menu();
    }
}

void check_out(int answer, int selected_zone)
{
    cout << "+-----------------------------------------------------------------------------+" << endl;
    do
    {
        cout << "Enter 1 to checkout" << endl;
        cout << "Enter 2 to cancel" << endl;
        cin >> answer;

        if (answer == 1 || answer == 2)
        {
            if (answer == 1)
            {
                if (users[global_id].subscribiondetails.planType == 'S' || users[global_id].subscribiondetails.planType == 'G')
                {
                    trips_deduction_general_or_scholar();
                }
                else if (users[global_id].subscribiondetails.planType == 'W')
                {
                    wallet_dedcution(selected_zone);
                }
                ++ride_freq_entry[start_station];
                ++ride_freq_exit[end_station];

                // Redirect based on role
                if (arr_user[global_id].role == 'U')
                {
                    record_ride();
                    user_main_menu();
                }
                else if (arr_user[global_id].role == 'A')
                {
                    admin_main_menu();
                }
            }
            else if (answer == 2)
            {
                --ride_freq_entry[start_station];
                --ride_freq_exit[end_station];

                // Redirect based on role
                if (arr_user[global_id].role == 'U')
                {
                    user_main_menu();
                }
                else if (arr_user[global_id].role == 'A')
                {
                    admin_main_menu();
                }
            }

            break;
        }
        else if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "+-----------------------------------------------------------------------------+" << endl;
            cout << "Wrong input,Please enter a number" << endl;
        }
        else
        {
            cout << "+-----------------------------------------------------------------------------+" << endl;
            cout << "Please Enter a valid choice" << endl;
        }
    } while (true);
}

void trip_not_valid(int start, int end_station, int end_line, int start_line, int answer)
{
    do
    {
        cout << "Number of stations does not match your zone!" << endl;
        cout << "Enter 1 to setup a new trip" << endl;
        cout << "Enter 2 to return back to menu" << endl;
        cin >> answer;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Wrong input,";
        }
        else
        {
            if (answer == 1)
            {
                start_calc(start, end_station, end_line, start_line, answer);
                break;
            }
            else if (answer == 2)
            {
                user_main_menu();
            }
        }
    } while (true);
}

void system_ride()
{

    // initialize_users();
    start_calc(start_station, end_station, end_line, start_line, answer);
}

void History_Shift_Handling(bool opperation, int pos) {  // 1 adding     0 removing
    if (opperation == 1) {
        if (start_station > pos && end_station > pos) {
            start_station++;
            end_station++;
        }
        else if (start_station > pos) {
            start_station++;
        }
        else if (end_station > pos) {
            end_station++;
        }
    }
    else {
        if (start_station > pos && end_station > pos) {
            start_station--;
            end_station--;
        }
        else if (start_station > pos) {
            start_station--;
        }
        else if (end_station > pos) {
            end_station--;
        }
    }
}



#pragma endregion

#pragma region History & Statistics
void statistics()
{
    for (int i = 0; i < 1001; ++i)
    {
        if (isUnique[i] == 1)
        {
            ++maximumage[arr_user[i].age];

            if (users[i].subscribiondetails.planType == 'S')
                ++numberofsub[0];
            else if (users[i].subscribiondetails.planType == 'W')
                ++numberofsub[1];
            else if (users[i].subscribiondetails.planType == 'G')
                ++numberofsub[2];
        }
    }

    ride_freq_entry[Al_Shohadaa_line1] += ride_freq_entry[Al_Shohadaa_line2];
    ride_freq_entry[Al_Shohadaa_line2] = 0;
    ride_freq_entry[Nasser_line1] += ride_freq_entry[Nasser_line3];
    ride_freq_entry[Nasser_line3] = 0;
    ride_freq_entry[17] += ride_freq_entry[46];
    ride_freq_entry[46] = 0;
    ride_freq_entry[Attaba_line2] += ride_freq_entry[Attaba_line3];
    ride_freq_entry[Attaba_line3] = 0;

    ride_freq_exit[Al_Shohadaa_line1] += ride_freq_exit[Al_Shohadaa_line2];
    ride_freq_exit[Al_Shohadaa_line2] = 0;
    ride_freq_exit[Nasser_line1] += ride_freq_exit[75];
    ride_freq_exit[Nasser_line3] = 0;
    ride_freq_exit[17] += ride_freq_exit[46];
    ride_freq_exit[46] = 0;
    ride_freq_exit[Attaba_line2] += ride_freq_exit[Attaba_line3];
    ride_freq_exit[Attaba_line3] = 0;

    cout << "the average age of people using this system is " << max_element(maximumage, maximumage + 150) - maximumage << '\n';
    cout << "the number of users plan type people subscribe to is " << '\n';
    cout << "Scholar plan : " << numberofsub[0] << " Persons\n";
    cout << "Smart Wallet : " << numberofsub[1] << " Persons\n";
    cout << "Genral plan : " << numberofsub[2] << " Persons\n";
    cout << "the common plan type people subscribe to is" << " ";

    if (numberofsub[(max_element(numberofsub, numberofsub + 3) - numberofsub)] == 0) {
        cout << "Scholar plan" << '\n';
    }
    else if (numberofsub[(max_element(numberofsub, numberofsub + 3) - numberofsub)] == 2) {
        cout << "General plan" << '\n';
    }
    else if (numberofsub[(max_element(numberofsub, numberofsub + 3) - numberofsub)] == 1) {
        cout << "Smart Wallet" << '\n';
    }


    cout << "the most Entered station is " << stations[(max_element(ride_freq_entry, ride_freq_entry + 1000) - ride_freq_entry) - 1] << '\n';
    cout << "the most Exit station is " << stations[(max_element(ride_freq_exit, ride_freq_exit + 1000) - ride_freq_exit) - 1] << '\n';
    cout << "The number of trips is " << numberf_of_trips << '\n';

}

void storage_the_data_of_statistics()
{
    ofstream file("statistics.txt", ios::out);
    if (file.is_open())
    {
        for (int i = 1; i <= 89; ++i)
        {
            file << i << " " << ride_freq_entry[i] << " " << ride_freq_exit[i] << endl;
        }
        file.close();
    }
    else
    {
        cout << "Unable to open the file";
    }
}

void read_statistics()
{
    ifstream file("statistics.txt");
    if (file.is_open())
    {
        int station, entry, exit;
        while (file >> station >> entry >> exit)
        {
            ride_freq_entry[station] = entry;
            ride_freq_exit[station] = exit;
        }
        file.close();
    }
    else
    {
        cout << "Unable to open the file";
    }
}

#pragma endregion

int main() {
    restore_the_data_of_user_and_admin();
    subscription_file_input();
    initialize_default_subscriptions(); // Initialize default subscriptions once
    read_statistics();
    cout << "Welcome to Cairo metro app \n";
    start_menu();
    storage_the_data_of_user_and_admin();
    storage_the_data_of_statistics();
    subsctriprion_file_output();
    system("pause");
    return 0;
}
