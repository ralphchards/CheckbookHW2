#include <iostream>
#include <cstdlib>

using namespace std;

// should this have been located somewhere else or was this fine?
const int N = 5;

// Create check struct
struct Check{

    int CheckNum;
    string CheckMemo;
    float CheckAmount;
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

    // display all checks
    void displayChecks(){
        for(int i = numOfChecks-1; i >= 0; i--){
            cout << "\nCheck " << checkArray[i].CheckNum +1 << endl; // the +1 is just for readability because Check 0 sounds dumb
            cout << "Memo: " << checkArray[i].CheckMemo << endl;
            cout << "Amount: " << checkArray[i].CheckAmount << endl;
        }
    }
    //string for selecting random memo
    string dumbMemos[3] = {"purchasing a ryzen 5800x3d", "lottery ticket", "chick-fil-a"};

    // write check function
    bool writeCheck(float amount){

        if (numOfChecks >= checkBookSize / 2) {
            // if half of the check book is used, double the size of the array
            int newSize = checkBookSize * 2;
            Check* newCheckArray = new Check[newSize];
            for (int i = 0; i < numOfChecks; i++) {
                newCheckArray[i] = checkArray[i];
            }
            checkBookSize = newSize;

            cout << "Warning: Check book is half full. A new check book has been ordered. " << newSize << endl;
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

int main(){
    CheckBook cb1; // create checkbook constructor

    cb1.deposit(500); // deposit 500

    // test checks
    cb1.writeCheck(30);
    cb1.writeCheck(60);
    cb1.writeCheck(100);

    // print all checks
    cb1.displayChecks();
}
