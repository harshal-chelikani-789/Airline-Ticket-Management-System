#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <algorithm>

using namespace std;

// Flight class definition
class Flight {
public:
    int flightID;
    string departureCity;
    string arrivalCity;
    string departureTime;
    string arrivalTime;
    double price;
    int availableSeats;

    Flight(int id, string depCity, string arrCity, string depTime, string arrTime, double prc, int seats)
        : flightID(id), departureCity(depCity), arrivalCity(arrCity), departureTime(depTime), arrivalTime(arrTime), price(prc), availableSeats(seats) {}

    void displayFlightInfo() const {
        cout << "\n-------------------------------------------\n";
        cout << "Flight ID: " << flightID << "\n"
             << "From: " << departureCity << " To: " << arrivalCity << "\n"
             << "Departure Time: " << departureTime << " Arrival Time: " << arrivalTime << "\n"
             << "Price: $" << fixed << setprecision(2) << price << "  Available Seats: " << availableSeats << "\n";
        cout << "-------------------------------------------\n";
    }

    static void searchFlight(vector<Flight>& flights, string depCity, string arrCity) {
        bool found = false;
        for (auto& flight : flights) {
            if (flight.departureCity == depCity && flight.arrivalCity == arrCity) {
                flight.displayFlightInfo();
                found = true;
            }
        }
        if (!found) {
            cout << "\nNo flights found for the given route.\n";
        }
    }
};

// User class definition
class User {
public:
    string username;
    string password;
    string email;
    Flight* currentBooking = nullptr;

    User(string uname, string pass, string mail)
        : username(uname), password(pass), email(mail) {}

    User() : username(""), password(""), email(""), currentBooking(nullptr) {}

    bool login(string uname, string pass) {
        if (uname == username && pass == password) {
            cout << "\nLogin successful!\n";
            return true;
        }
        cout << "\nInvalid username or password.\n";
        return false;
    }

    void displayBooking() const {
        if (currentBooking) {
            cout << "\n--- Your Current Booking ---\n";
            currentBooking->displayFlightInfo();
        } else {
            cout << "\nYou have no current bookings.\n";
        }
    }
};

// Booking class definition
class Booking {
public:
    static void bookFlight(User& user, Flight& flight) {
        if (flight.availableSeats > 0) {
            flight.availableSeats--;
            user.currentBooking = &flight;
            cout << "\nBooking successful!\n";
            cout << "Your flight details are as follows:\n";
            flight.displayFlightInfo();
        } else {
            cout << "\nSorry, no available seats for this flight.\n";
        }
    }

    static void cancelBooking(User& user) {
        if (user.currentBooking) {
            user.currentBooking->availableSeats++;
            cout << "\nBooking for Flight ID " << user.currentBooking->flightID << " has been canceled.\n";
            user.currentBooking = nullptr;
        } else {
            cout << "\nYou have no current booking to cancel.\n";
        }
    }

    static void modifyBooking(User& user, vector<Flight>& flights) {
        if (user.currentBooking) {
            cout << "\nYour current booking details:\n";
            user.currentBooking->displayFlightInfo();
            int newFlightID;
            cout << "\nEnter new flight ID to modify booking: ";
            cin >> newFlightID;
            for (auto& flight : flights) {
                if (flight.flightID == newFlightID) {
                    cancelBooking(user);
                    bookFlight(user, flight);
                    return;
                }
            }
            cout << "\nInvalid flight ID.\n";
        } else {
            cout << "\nYou have no current booking to modify.\n";
        }
    }
};

// Payment class definition
class Payment {
public:
    static bool processPayment(double amount) {
        cout << "\nProcessing payment of $" << fixed << setprecision(2) << amount << "...\n";
        cout << "Payment successful!\n";
        return true;
    }
};

// Admin class definition
class Admin {
public:
    static void addFlight(vector<Flight>& flights) {
        int id;
        string depCity, arrCity, depTime, arrTime;
        double price;
        int seats;

        cout << "\n--- Add New Flight ---\n";
        cout << "Enter Flight ID: ";
        cin >> id;
        cout << "Enter Departure City: ";
        cin >> depCity;
        cout << "Enter Arrival City: ";
        cin >> arrCity;
        cout << "Enter Departure Time: ";
        cin >> depTime;
        cout << "Enter Arrival Time: ";
        cin >> arrTime;
        cout << "Enter Price: ";
        cin >> price;
        cout << "Enter Available Seats: ";
        cin >> seats;

        Flight newFlight(id, depCity, arrCity, depTime, arrTime, price, seats);
        flights.push_back(newFlight);
        cout << "\nFlight added successfully!\n";
    }

    static void cancelFlight(vector<Flight>& flights) {
        int flightID;
        cout << "\nEnter the Flight ID to cancel: ";
        cin >> flightID;
        auto it = find_if(flights.begin(), flights.end(), [flightID](const Flight& flight) {
            return flight.flightID == flightID;
        });

        if (it != flights.end()) {
            flights.erase(it);
            cout << "\nFlight ID " << flightID << " has been canceled.\n";
        } else {
            cout << "\nFlight ID not found.\n";
        }
    }

    static void modifyFlight(vector<Flight>& flights) {
        int flightID;
        cout << "\nEnter the Flight ID to modify: ";
        cin >> flightID;
        for (auto& flight : flights) {
            if (flight.flightID == flightID) {
                string depCity, arrCity, depTime, arrTime;
                double price;
                int seats;

                cout << "\nEnter new Departure City: ";
                cin >> depCity;
                cout << "Enter new Arrival City: ";
                cin >> arrCity;
                cout << "Enter new Departure Time: ";
                cin >> depTime;
                cout << "Enter new Arrival Time: ";
                cin >> arrTime;
                cout << "Enter new Price: ";
                cin >> price;
                cout << "Enter new Available Seats: ";
                cin >> seats;

                flight.departureCity = depCity;
                flight.arrivalCity = arrCity;
                flight.departureTime = depTime;
                flight.arrivalTime = arrTime;
                flight.price = price;
                flight.availableSeats = seats;

                cout << "\nFlight details updated successfully!\n";
                flight.displayFlightInfo();
                return;
            }
        }
        cout << "\nFlight ID not found.\n";
    }

    static void displayFlights(const vector<Flight>& flights) {
        cout << "\n--- All Flights ---\n";
        for (const auto& flight : flights) {
            flight.displayFlightInfo();
        }
    }
};

int main() {
    vector<Flight> flights = {
        Flight(101, "Delhi", "Visakhapatnam", "10:00 AM", "01:00 PM", 200.00, 5),
        Flight(102, "Chicago", "Miami", "03:00 PM", "06:00 PM", 150.00, 3)
    };

    unordered_map<string, User> users;

    Admin admin;

    int mainChoice;
    do {
        // Display the system heading
        cout << "\n=============================\n";
        cout << "  Airline Ticket Management  \n";
        cout << "        System               \n";
        cout << "=============================\n\n";

        cout << "1. User Login\n";
        cout << "2. User Registration\n";
        cout << "3. Admin Login\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        if (mainChoice == 1) {  // User Login
            string username, password;
            cout << "\n--- User Login ---\n";
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (users.find(username) != users.end()) {
                if (users[username].login(username, password)) {
                    int userChoice;
                    do {
                        cout << "\n--- User Menu ---\n";
                        cout << "1. Search Flights\n";
                        cout << "2. Book Flight\n";
                        cout << "3. Cancel Booking\n";
                        cout << "4. Modify Booking\n";
                        cout << "5. View Current Booking\n";
                        cout << "6. Logout\n";
                        cout << "Enter your choice: ";
                        cin >> userChoice;

                        if (userChoice == 1) {
                            string depCity, arrCity;
                            cout << "\nEnter Departure City: ";
                            cin >> depCity;
                            cout << "Enter Arrival City: ";
                            cin >> arrCity;
                            Flight::searchFlight(flights, depCity, arrCity);
                        }

                        if (userChoice == 2) {
                            int flightID;
                            cout << "\nEnter Flight ID to book: ";
                            cin >> flightID;
                            for (auto& flight : flights) {
                                if (flight.flightID == flightID) {
                                    Booking::bookFlight(users[username], flight);
                                    break;
                                }
                            }
                        }

                        if (userChoice == 3) {
                            Booking::cancelBooking(users[username]);
                        }

                        if (userChoice == 4) {
                            Booking::modifyBooking(users[username], flights);
                        }

                        if (userChoice == 5) {
                            users[username].displayBooking();
                        }

                    } while (userChoice != 6);
                }
            } else {
                cout << "\nUser not found.\n";
            }
        }
        else if (mainChoice == 2) {  // User Registration
            string username, password, email;
            cout << "\n--- User Registration ---\n";
            cout << "Enter new username: ";
            cin >> username;
            cout << "Enter new password: ";
            cin >> password;
            cout << "Enter your email: ";
            cin >> email;
            users[username] = User(username, password, email);
            cout << "\nUser registered successfully!\n";
        }
        else if (mainChoice == 3) {  // Admin Login
            string adminUsername, adminPassword;
            cout << "\n--- Admin Login ---\n";
            cout << "Enter admin username: ";
            cin >> adminUsername;
            cout << "Enter admin password: ";
            cin >> adminPassword;

            if (adminUsername == "admin" && adminPassword == "admin") {
                int adminChoice;
                do {
                    cout << "\n--- Admin Menu ---\n";
                    cout << "1. Add Flight\n";
                    cout << "2. Cancel Flight\n";
                    cout << "3. Modify Flight\n";
                    cout << "4. View All Flights\n";
                    cout << "5. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> adminChoice;

                    if (adminChoice == 1) {
                        admin.addFlight(flights);
                    }

                    if (adminChoice == 2) {
                        admin.cancelFlight(flights);
                    }

                    if (adminChoice == 3) {
                        admin.modifyFlight(flights);
                    }

                    if (adminChoice == 4) {
                        admin.displayFlights(flights);
                    }

                } while (adminChoice != 5);
            } else {
                cout << "\nInvalid admin credentials.\n";
            }
        }

    } while (mainChoice != 4);

    return 0;
}