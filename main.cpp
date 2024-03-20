#include <iostream>
#include <string>
using namespace std;

// Define a class for the car park system
class CarParkSystem {
private:
    // Define pricing information for each day and time period
    float prices[7][2]; // 7 days, 2 time periods (08:00 - 15:59 and 16:00 - Midnight)
    float dailyTotalPayments;



    // Method to get the index of the day of the week (0 for Sunday, 1 for Monday, etc.)
    int getDayIndex(string dayOfWeek) {
        // Convert day of the week string to lowercase for case-insensitive comparison
        for (char& c : dayOfWeek) {
            c = tolower(c);
        }

        // Check day of the week and return corresponding index
        if (dayOfWeek == "sunday") {
            return 0;
        } else if (dayOfWeek == "monday") {
            return 1;
        } else if (dayOfWeek == "tuesday") {
            return 2;
        } else if (dayOfWeek == "wednesday") {
            return 3;
        } else if (dayOfWeek == "thursday") {
            return 4;
        } else if (dayOfWeek == "friday") {
            return 5;
        } else if (dayOfWeek == "saturday") {
            return 6;
        } else {
        // If day of the week is not recognized, return -1 (or handle it according to your requirement)
            return -1;
        }
    }



public:
    // Constructor to initialize pricing information
    CarParkSystem() {
        // Initialize prices array with specified values based on the problem statement
        prices[0][0] = 2.00; // Sunday, 08:00 - 15:59 price
        prices[0][1] = 2.00; // Sunday, 16:00 - Midnight price
        prices[1][0] = 10.00; // Monday, 08:00 - 15:59 price
        prices[1][1] = 2.00; // Monday, 16:00 - Midnight price
        prices[2][0] = 10.00; // Tuesday, 08:00 - 15:59 price
        prices[2][1] = 2.00; // Tuesday, 16:00 - Midnight price
        prices[3][0] = 10.00; // Wednesday, 08:00 - 15:59 price
        prices[3][1] = 2.00; // Wednesday, 16:00 - Midnight price
        prices[4][0] = 10.00; // Thursday, 08:00 - 15:59 price
        prices[4][1] = 2.00; // Thursday, 16:00 - Midnight price
        prices[5][0] = 10.00; // Friday, 08:00 - 15:59 price
        prices[5][1] = 2.00; // Friday, 16:00 - Midnight price
        prices[6][0] = 3.00; // Saturday, 08:00 - 15:59 price
        prices[6][1] = 2.00; // Saturday, 16:00 - Midnight price
    
        dailyTotalPayments = 0.0;
    
    }

    // Method to calculate parking price considering fairer pricing
    float calculateParkingPrice(string dayOfWeek, int arrivalHour, int numHours, bool hasFrequentParkingNumber, const string& frequentParkingNumber) {
    int dayIndex = getDayIndex(dayOfWeek);
    float price = 0.0;

    // Validate frequent parking number if provided
    if (hasFrequentParkingNumber && !isValidFrequentParkingNumber(frequentParkingNumber)) {
        cout << "Invalid frequent parking number. No discount will be applied." << endl;
        hasFrequentParkingNumber = false; // Disable discount if frequent parking number is invalid
    }

    // Check arrival time and calculate price accordingly
    if (arrivalHour >= 16) {
        // Calculate price for parking entirely during the evening
        price = prices[dayIndex][1] * numHours; // Evening price
    } else if (arrivalHour < 16 && arrivalHour + numHours <= 16) {
        // Calculate price for parking entirely during the daytime
        price = prices[dayIndex][0] * numHours; // Daytime price
    } else {
        // Calculate price for split parking between daytime and evening
        int daytimeHours = 16 - arrivalHour;
        int eveningHours = numHours - daytimeHours;
        float daytimePrice = prices[dayIndex][0] * daytimeHours;
        float eveningPrice = prices[dayIndex][1] * eveningHours;
        price = daytimePrice + eveningPrice;
    }

    // Apply discount if applicable
    if (arrivalHour >= 16 && hasFrequentParkingNumber) {
        price *= 0.5; // Apply 50% discount for evening arrivals with valid frequent parking number
    } else if (hasFrequentParkingNumber) {
        price *= 0.9; // Apply 10% discount for other arrivals with valid frequent parking number
    }

    // Update daily total payments
    dailyTotalPayments += price;

    return price;
}

    
    // Function to validate frequent parking number
    bool isValidFrequentParkingNumber(const string& number) {
    // Check if the number is of the correct length (5 digits)
    if (number.length() != 5) {
        return false;
    }

    // Check if all characters are digits
    for (char c : number) {
        if (c < '0' || c > '9') {
            return false;
        }
    }

    return true;
}


    // Method to update daily total payments
    void updateDailyTotalPayments(float payment) {
        dailyTotalPayments += payment;
    }
    
    
    // Method to display daily total payments
    void displayDailyTotalPayments() {
        cout << "Daily total payments: $" << dailyTotalPayments << endl;
    }
    
};



int main() {
    // Create CarParkSystem object
    CarParkSystem carPark;

    // Prompt user for input
    string dayOfWeek;
    int arrivalHour, numHours;
    bool hasFrequentParkingNumber;
    string frequentParkingNumber;

    cout << "Enter the day of the week (e.g., Sunday): ";
    cin >> dayOfWeek;
    cout << "Enter the arrival hour (0-23): ";
    cin >> arrivalHour;
    cout << "Enter the number of hours to park: ";
    cin >> numHours;
    cout << "Do you have a frequent parking number? (1 for yes, 0 for no): ";
    cin >> hasFrequentParkingNumber;

    // If user has a frequent parking number, prompt for it and validate
    if (hasFrequentParkingNumber) {
        cout << "Enter your frequent parking number (5 digits): ";
        cin >> frequentParkingNumber;

        // Validate frequent parking number
        if (!carPark.isValidFrequentParkingNumber(frequentParkingNumber)) {
            cout << "Invalid frequent parking number. No discount will be applied." << endl;
            hasFrequentParkingNumber = false; // Disable discount if frequent parking number is invalid
        }
    }

    // Calculate parking price
    float totalPrice = carPark.calculateParkingPrice(dayOfWeek, arrivalHour, numHours, hasFrequentParkingNumber, frequentParkingNumber);

    // Display result
    cout << "Total parking price: $" << totalPrice << endl;

    // Prompt the customer for their payment
    float customerPayment;
    cout << "Enter your payment: $";
    cin >> customerPayment;

    // Validate the payment against the calculated parking price
    if (customerPayment < totalPrice) {
    cout << "Insufficient payment. Please pay at least $" << totalPrice << "." << endl;
    } else {
    // Add the payment to the daily total payments
    carPark.updateDailyTotalPayments(customerPayment);
    cout << "Thank you for your payment!" << endl;
    }
    
    carPark.displayDailyTotalPayments();

    return 0;
}
