# 🎬 BookMyShow Console Ticketing System (C++ End-to-End)

A robust, resume-ready console application developed using C++ and Object-Oriented Programming principles. This project simulates the core functionalities of a real-world movie ticket booking platform, including user authentication, real-time seat allocation, and persistent data storage.

***

## ⚙️ Tech Stack & Key Concepts

| Component | Detail | SDE Focus |
| :--- | :--- | :--- |
| **Language** | C++17/20 | Utilized modern C++ features and standard practices. |
| **Data Structures** | **STL `std::map`** (for fast $O(1)$ lookup of Users, Movies, and Bookings by ID) and **`std::vector`** (for flexible seat management). | Demonstrates efficiency and algorithmic thinking. |
| **Storage** | **CSV File Persistence** | Custom implementation of **serialization** (`toCSV`) and **deserialization** (`fromCSV`) using `<fstream>` to maintain data integrity across sessions. |
| **Architecture** | **Object-Oriented Programming (OOP)** | Strict adherence to Encapsulation, Composition (Theatre manages Seats), and Single Responsibility Principle (SRP). |

***

## ✨ Core Features Implemented

The application is a comprehensive, menu-driven system covering both customer and administrative roles:

### 🧑‍🎟️ User (Customer) Features
* **Authentication:** Users can register and log in. User data is persisted in `data/users.txt`.
* **Booking Flow:** Seamless selection process: **View Movies** $\rightarrow$ **Select Theatre** $\rightarrow$ **View Seat Map** $\rightarrow$ **Select Seat**.
* **Seat Management:** Seats are marked as booked in real-time, preventing double-booking errors.
* **Rollback & Security:** Includes a **Payment Simulation** with a failure chance. Upon failure, the application performs a **data rollback**, ensuring the reserved seat is released immediately for consistency.
* **History:** Users can view their complete booking history (`View My Bookings`).

### 🧑‍💼 Admin (Manager) Features
* **Restricted Access:** Access to the Admin Panel is restricted based on the user's role (`ADMIN` vs. `USER`).
* **Content Management:** Admin can **Add New Movies** and **Add New Theatres** to the system.
* **Reporting:** Ability to **View All System Bookings**, providing a complete audit of all transactions recorded in `data/bookings.txt`.

***

## 🏗️ Project Architecture (UML Model)

The system is built around six primary classes, demonstrating clear **Separation of Concerns** (SoC):

| Module | Responsibility | Key Relationship |
| :--- | :--- | :--- |
| **`BookMyShowApp`** | Central controller, menu loop, and data persistence (I/O). | Aggregates all other core classes via `std::map`. |
| **`Theatre`** | Manages theater name, ID, and its seat layout. | **Composes** (`std::vector`) many `Seat` objects. |
| **`Seat`** | Holds status (`Booked`/`Free`) and seat label (`A1`). | Data entity. |
| **`User`** | Holds credentials, role, and handles password verification. | Data entity. |
| **`Booking`** | Records a single confirmed ticket (linking User ID, Movie ID, Seat, etc.). | Association (references other IDs). |

***

## 💻 Getting Started (How to Compile and Run)

### Prerequisites
* A C++ compiler (g++ recommended)
* A UNIX-like terminal (or PowerShell/CMD)

### 1. Compile the Project

Navigate to the root directory of the project (`BookMyShow/`) and compile all source files simultaneously:

```bash
g++ main.cpp classes/*.cpp -o bookmyshow
# OR using specific file names:
# g++ main.cpp classes/Movie.cpp classes/Seat.cpp classes/Theatre.cpp classes/BookMyShowApp.cpp classes/Booking.cpp classes/User.cpp -o bookmyshow