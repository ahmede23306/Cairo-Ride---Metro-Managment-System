CairoRide
A console-based C++ application simulating a metro transit system, allowing users to manage subscriptions and rides, with robust admin controls for system management.
Overview
CairoRide is a comprehensive metro transit simulation built in C++ that enables users to register accounts, select from three subscription plans (Scholar Pass, General Pass, Smart Wallet), and plan rides across three metro lines with zone-based pricing (8-20 LE for 1-9 to 23+ stations). Admins can manage user accounts, subscriptions, stations, fare rates, and access detailed ride logs. The system leverages arrays of structures for efficient data management, supports ride history tracking, statistical analysis, and persists data using file I/O. Designed for ease of use, it provides a text-based interface with potential for GUI enhancements.
Features
User Functionalities

Account Management:
Register with a unique ID (1-1000), name, password (8+ characters with upper, lower, and special characters), and age.
Login securely with ID and password; supports password hiding during input.
Edit personal details (name, password, balance) and view account information.


Subscription Plans:
Scholar Pass: 180 trips over 3 months, priced at 150, 200, 250, or 300 LE for Zones 1-4.
General Pass: 60 trips/month (310, 365, 425, 600 LE for Zones 1-4) or 730 trips/year (3500, 4000, 4500, 5000 LE).
Smart Wallet: Pay-per-ride with funds added in 10 LE increments (max 400 LE), no trip limits.
Users can purchase, renew, or change plans, with zone-based restrictions for Scholar and General Passes.


Ride Planning:
Select start and end stations across three metro lines (Line 1: 35 stations, Line 2: 20 stations, Line 3: 23 stations).
Supports interchange stations (e.g., Al-Shohadaa, Nasser, Attaba) and Kit-Kat branches (Rod El-Farag, Cairo University).
Displays metro map with stations and zones traversed; calculates fares based on zones (1-9 stations: 8 LE, 10-16: 10 LE, 17-23: 15 LE, 23+: 20 LE).
Deducts trips (Scholar/General) or balance (Smart Wallet) upon checkout.


Ride History:
Records ride details (ride ID, start/end stations, date/time) for each user.
Users can view their ride history; admins can access system-wide logs.


Wallet Management:
Add funds to Smart Wallet or pay for subscriptions via balance.
Ensures sufficient balance for rides or renewals.



Admin Functionalities

User Control:
View, modify, or delete user accounts (requires admin token: 1929).
Access user details (name, ID, password, role, subscription, balance, age).


Subscription Management:
Add, edit, or remove subscription plans (up to 13 plans).
Modify plan details (name, symbol, duration, zone prices, trip limits).


Station Management:
Add or remove stations on any line, updating line indices and interchange points.
Prevents removal of critical interchange stations (e.g., Al-Shohadaa, Nasser).


Fare Adjustments:
Update zone prices (e.g., Zone 1 from 8 LE to new value).
Changes apply to Smart Wallet deductions and subscription pricing.


System Analytics:
Generate statistics on user age distribution, subscription popularity, and station usage (most entered/exited stations).
Tracks total trips across the system.



Technical Details

Data Structures:
user_struct: Stores user ID, balance, subscription details, and zone.
subscription: Holds plan type, activation/expiry dates, remaining trips, zones, and payment.
ride_struct: Records ride ID, start/end stations, and date/time.
system_subscriptions: Manages subscription plan details (name, symbol, duration, prices, trips).
Arrays (arr_user, users, rides, RideHistory) for up to 1001 users, with boolean arrays (isUnique, subscipetion_or_not) for tracking.


Metro System:
85 stations across 3 lines (Line 1: New Marg to Helwan, Line 2: Shubra El-Khaimah to El Monib, Line 3: Adly Mansour to Kit-Kat/Cairo University).
11 geographical zones for fare calculation, with interchange stations for line transitions.
Kit-Kat station branches into Rod El-Farag and Cairo University paths on Line 3.


File I/O:
Stores user data (file_user_and_admin.txt), subscriptions (Subscriptions.txt), and statistics (statistics.txt).
Supports data restoration on startup and saving on exit.


Input Validation:
Ensures valid inputs for IDs, passwords, station selections, and numeric values.
Handles errors (e.g., duplicate IDs, invalid station choices) with clear prompts.


Code Organization:
Modular design with functions for account management (register_form, login_form), ride planning (system_ride, start_calc), subscription handling (subscriptiondataentry, renewSubscriptionPlan), and admin tasks (Admin_Subscriptions_control, add_station).
Uses #pragma region for grouping related code (e.g., sign-in, rides, statistics).



Code Explanation
The main.cpp file (over 47,000 characters) is the core of CairoRide, structured as follows:

Global Variables and Constants:

Defines metro lines (start_line1, end_line1, etc.), station counts (85 total), and zone prices (8-20 LE).
Arrays for stations (stations, stations_read), zones (zone_1 to zone_11), and user data (arr_user, users).
Constants like number_of_users_and_admin (1001) and max_subscription_plans (13).


Data Structures:

user_and_admin_struct: Stores role ('U' for user, 'A' for admin), name, ID, password, subscription type, and age.
subscription: Tracks plan type, dates, trips, zones, and payment.
ride_struct and Ride_history: Log ride details per user.
system_subscriptions: Defines subscription blueprints (e.g., Scholar Pass with 180 trips).


Key Functions:

Account Management:
start_menu: Entry point for registration or login.
register_form: Validates user input (unique ID, strong password) and assigns subscriptions.
login_form: Authenticates users/admins and directs to respective menus.
storage_the_data_of_user_and_admin: Saves user data to file.


Subscription Handling:
initialize_default_subscriptions: Sets up Scholar, General, and Smart Wallet plans.
subscriptiondataentry: Guides users through plan and zone selection.
Admin_Subscriptions_control: Allows admins to add/edit/remove plans.


Ride Planning:
system_ride: Initiates ride planning with start_calc.
start_calc and check_line: Handle station/line selection and route calculation.
list_intersect_line_1_2, list_same_line: Display metro maps for inter-line or same-line trips.
check_out: Deducts trips or balance based on subscription type.


Station Management:
add_station, remove_station: Modify station lists, updating indices and history.
History_Shift_Handling: Adjusts ride history when stations are added/removed.


Statistics:
statistics: Analyzes user ages, subscription types, and station frequencies.
storage_the_data_of_statistics: Saves analytics to file.




Execution Flow:

main(): Initializes data (restores from files, sets default subscriptions), displays welcome message, and starts the menu loop.
Users navigate through text prompts, with input validation ensuring robust operation.
Data is saved to files on exit, preserving user and system state.



Installation

Clone the Repository:
git clone https://github.com/<your-username>/CairoRide.git


Compile the Code:

Ensure a C++ compiler (e.g., g++) is installed.

Navigate to the project directory:
cd CairoRide
g++ -o CairoRide main.cpp




Run the Application:
./CairoRide



Usage

Users:
Register with a unique ID and password, then select a subscription plan.
Plan rides by choosing start/end stations and lines; confirm to deduct trips or balance.
View/edit profile, subscription, or ride history via the user menu.


Admins:
Register with admin role and use token (1929) to access admin menu.
Manage users, subscriptions, stations, and fares; view system logs and statistics.


Data Persistence:
User data, subscriptions, and statistics are saved to file_user_and_admin.txt, Subscriptions.txt, and statistics.txt.
Files are loaded on startup to restore system state.



Future Enhancements

Implement a Graphical User Interface (GUI) for improved user experience.
Support zone-based subscriptions (e.g., restrict Scholar Pass to specific zones).
Generate detailed analytical reports (e.g., peak travel times, zone usage trends).
Add multi-language support for broader accessibility.

Contributing
Contributions are welcome! Please fork the repository, create a feature branch, and submit a pull request with your changes. Ensure code follows the existing style and includes relevant comments.
