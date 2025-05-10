# Metro Management System

A comprehensive C++ console application for managing a metro/subway system, supporting user and admin operations, subscription plans, ride tracking, and system statistics. This project demonstrates modular programming, file I/O, and advanced data handling in C++.

---

## Table of Contents

- [Features](#features)
- [Code Structure](#code-structure)
- [Data Model](#data-model)
- [Metro Lines & Zones](#metro-lines--zones)
- [User Flow](#user-flow)
- [Admin Flow](#admin-flow)
- [Subscription System](#subscription-system)
- [Ride Management](#ride-management)
- [Statistics & Data Persistence](#statistics--data-persistence)
- [Getting Started](#getting-started)

---

## Features

- **User Registration & Login**: Secure, with password strength validation and hidden input.
- **Role-Based Access**: User and admin accounts with distinct privileges.
- **Metro Lines & Stations**: Supports over 80 stations across three lines, with dynamic zone mapping.
- **Subscriptions**: Multiple plans (e.g., Scholar Pass, General Pass), monthly/yearly, zone-based pricing, trip limits.
- **Smart Wallet**: Users can add funds and pay fares or renew subscriptions.
- **Ride Management**: Users can take rides, with fare calculation based on zones and trip history tracking.
- **Admin Tools**: Manage user accounts, edit subscription plans, update station lists, and view system statistics.
- **Data Persistence**: Functions for saving/loading users, subscriptions, and statistics (file I/O stubs provided).
- **Statistics**: Usage analytics, ride frequency, and more.

---

## Code Structure

The code is organized into logical sections using regions and function groups:

- **Global Variables & Constants**: Define system-wide parameters, station lists, zones, and pricing.
- **Structs**: Represent users, admins, subscriptions, rides, and history.
- **Utility Functions**: For time handling, input validation, and password security.
- **User/Admin Functions**: Registration, login, account management, and menu navigation.
- **Subscription Management**: Handling of plans, payments, renewals, and plan editing.
- **Ride Functions**: Route selection, fare calculation, trip deduction, and ride history.
- **Admin Tools**: Account management, plan editing, and statistics.
- **Statistics & File I/O**: Data storage, reading, and analytics (functions provided for extension).

---

## Data Model

| Struct                  | Purpose                                                                 |
|-------------------------|-------------------------------------------------------------------------|
| `user_and_admin_struct` | Stores user/admin details (role, name, ID, password, age, subscription) |
| `subscription`          | Tracks user subscription (type, dates, trips, zones, payment)           |
| `system_subscriptions`  | Defines available plans (name, symbol, duration, pricing, trip limits)  |
| `user_struct`           | User account info (ID, balance, subscription, zone)                     |
| `ride_struct`           | Ride details (ID, start/end stations, date/time)                        |
| `Ride_history`          | Per-user ride history                                                   |

---

## Metro Lines & Zones

- **Stations**: Defined in arrays, with over 80 unique station names.
- **Lines**: Three main lines, with branch logic for special stations (e.g., Kit Kat, Rod El-Farag Axis).
- **Zones**: Stations grouped into 11+ zones, each with its own pricing and trip logic.
- **Zone Pricing**: Default prices are set (e.g., Zone 1: 8, Zone 2: 10, etc.), and can be modified by admins.

---

## User Flow

1. **Registration/Login**:  
   - Unique ID, name (no numbers), strong password (min 8 chars, upper/lower/special).
   - Login requires correct ID and password.

2. **Profile Management**:  
   - View/update personal data.
   - Add funds to the smart wallet.

3. **Subscription**:  
   - Choose from available plans.
   - View, renew, or change subscriptions.
   - Payment from wallet or on renewal.

4. **Taking Rides**:  
   - Select start/end stations.
   - Calculates route, zone, and fare.
   - Deducts fare/trips.
   - Logs ride history.

5. **Ride History**:  
   - View ride history: date, time, stations.

---

## Admin Flow

1. **Account Management**:  
   - View, modify, or delete accounts.
   - Reset passwords, update user data.

2. **Subscription Plans**:  
   - Add/edit/remove plans.
   - Adjust zone pricing and limits.

3. **Station Management**:  
   - Add/remove/edit stations and zones.

4. **Statistics**:  
   - System usage, ride frequencies, analytics.

---

## Subscription System

- **Plan Structure**:  
  Name, symbol, duration, zone-based pricing, trip limits.

- **Default Plans**:  
  - *Scholar Pass*: 3 months, low cost, high trips.
  - *General Pass*: Monthly/yearly, standard pricing.
  - *Custom plans*: Admin-defined.

- **Management**:  
  - Subscribe, renew, or switch.
  - Admins can edit plan data.

---

## Ride Management

- **Route Calculation**:  
  - Handles single/multi-line travel.
  - Determines zones based on stations.

- **Fare Deduction**:  
  - Deducts fare from wallet or subscription.
  - Validates available balance/trips.

- **Ride Logging**:  
  - Records start/end stations and time.
  - Viewable by users/admins.

---

## Statistics & Data Persistence

- **Statistics**:  
  - Rides per station.
  - Subscription and user analytics.

- **Data Storage**:  
  - File I/O stubs for saving/loading data.

---

## Getting Started

### Prerequisites

- C++17 compatible compiler (GCC, MSVC)
- Windows (uses `localtime_s`, `_getch()`)
- Console-based

### Compilation

```bash
g++ -std=c++17 -o metro main.cpp
