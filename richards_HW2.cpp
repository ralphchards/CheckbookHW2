#include <iostream>
#include <cstdlib>
#include <ctime>

/*************************************************************************
** Author : Ralph Richards
** Program : hw2, q1
** Date Created : February 22, 2024
** Date Last Modified : February 23, 2024
** Usage : No command line arguments
**
** Problem:
Create a "checkbook" using a struct and class that doubles in size when needed
Write out small checks to see this used
Generate random memos
Display all checks using an overloaded operator

*************************************************************************/


using namespace std;

const int N = 100;

// Create check struct
struct Check{

    int CheckNum;
    string CheckMemo;
    float CheckAmount;

    bool operator>(float value) const {
        return CheckAmount > value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Check& check) {
        os << "Check Number: " << check.CheckNum << ", Memo: " << check.CheckMemo << ", Amount: $" << check.CheckAmount;
        return os;
    }
};

// Create checkbook class
class CheckBook{

public:

    //initialize variables
    float balance, lastDeposit;
    Check *chkPtr;
    Check checkArray[N];
    int numOfChecks, checkBookSize;

    // Constructors to create with either 0 or a desired balance
    CheckBook(): balance(0), numOfChecks(0), checkBookSize(4), chkPtr(nullptr) {}
    CheckBook(float balance_amount): balance(balance_amount), numOfChecks(0), checkBookSize(2), chkPtr(nullptr) {}

    // destructor
    ~CheckBook() {
        delete[] chkPtr; // Free memory allocated for dynamic array
    }

    // copy constructor
    CheckBook(const CheckBook& other) {
        balance = other.balance;
        lastDeposit = other.lastDeposit;
        numOfChecks = other.numOfChecks;
        checkBookSize = other.checkBookSize;

        chkPtr = new Check[checkBookSize];
        for (int i = 0; i < numOfChecks; ++i) {
            chkPtr[i] = other.chkPtr[i];
        }
    }

    // deposit function to add to balance
    void deposit(float amount){
        balance += amount;
    }

    // display all checks with overloaded operator
    void displayChecks(){
        for (int i = numOfChecks - 1; i >= 0; i--) {
        cout << checkArray[i] << endl;
        }
    }

    //string for selecting random memo
    string dumbMemos[3] = {"purchasing a ryzen 5800x3d", "lottery ticket", "chick-fil-a"};

    // write check function
    bool writeCheck(float amount){
        cout << "\nCurrent number of checks: " << numOfChecks << endl;
        cout << "Current balance: $" << balance << endl;

        if (numOfChecks >= checkBookSize / 2) {
            // if half of the check book is used, double the size of the array
            int newSize = checkBookSize * 2;
            Check* newCheckArray = new Check[newSize];
            for (int i = 0; i < numOfChecks; i++) {
                newCheckArray[i] = checkArray[i];
            }
            chkPtr = newCheckArray;
            checkBookSize = newSize;

            cout << "\nWarning: Check book is half full. A new check book has been ordered. " << newSize << endl;
        }

        if(amount <= balance){
                checkArray[numOfChecks].CheckAmount = amount;
                checkArray[numOfChecks].CheckNum = numOfChecks;
                checkArray[numOfChecks].CheckMemo = dumbMemos[rand() % 3];

                balance -= amount;
                numOfChecks += 1;
        }else{
            return false;
        }
    }

};

    void checkTest(CheckBook& checkBook) {

    // write checks until balance is exhausted
    while (checkBook.balance > 0) {
        if (checkBook.writeCheck(25)) {
            cout << "\nCheck of amount $" << 25 << " successfully written." << endl;
            checkBook.balance -= 25;
        } else {
            cout << "Insufficient balance to write check of amount $" << 25 << "." << endl;
            break;
        }

        cout << "displaying all checks:" << endl;
        checkBook.displayChecks();
        }
    }


int main(){
    //random seed
    srand(time(0));

    CheckBook cb1; // create checkbook constructor

    cb1.deposit(500); // deposit 500

    // test checks
    checkTest(cb1);

}
