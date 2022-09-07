#include <iostream>
#include <fstream>
using namespace std; 
//helper functions
int pow(int val, int exp) {
    int res = 1;
    for (int i = 0; i < exp; i++) {
        res *= val;
    }
    return res;
}
void shift(int arr[], int arr2[], int element, int &size) {
    for (int i = element; i < size; ++i) {
        arr[i] = arr[i + 1];
    }
    for (int i = element; i < size; ++i) {
        arr2[i] = arr2[i + 1];
    }
    size--;

}
void sort(int rcoef[], int rdeg[], int rterms) {
    int i, j, temp;

    bool swapped;
    for (i = 0; i < rterms - 1; i++)
    {
        swapped = false;
        for (j = 0; j < rterms - i - 1; j++)
        {
            if (rdeg[j] < rdeg[j + 1])
            {
                temp = rcoef[j];
                rcoef[j] = rcoef[j + 1];
                rcoef[j + 1] = temp;
                temp = rdeg[j];
                rdeg[j] = rdeg[j + 1];
                rdeg[j + 1] = temp;
                swapped = true;
            }
        }
        if (swapped == false)
            j = rterms;
    }
}
void copy(int A[], int newA[], int size) {
    
    for (int i = 0; i < size; i++)
    {
        newA[i] = A[i];
    }
}
//test function
void output(int rterms, int rdeg[], int rcoef[]) {
    cout << "Number of terms is " << rterms << endl;
    for (int i = 0; i < rterms; i++) {
        cout << "coefficient: " << rcoef[i] << " degree: " << rdeg[i] << endl;
    }
}
//Assignment
//input/output functions
void Print(int terms, int deg[], int coef[]) {
  
    for (int i = 0; i < terms; i++) {

        if (i > 0 && coef[i] > 0)
            cout << "+";
        if (coef[i] != 0 && coef[i] != 1)
            cout << coef[i];
        if (deg[i] == 1 && coef[i] != 0)
            cout << "x";
        else if (deg[i] != 0 && coef[i] != 0)
            cout << "x^" << deg[i];

    }

}
void Input( int terms, int deg[], int coef[]) {
    deg[0] = 16;
    for (int i = 1; i <= terms; i++) {
        cout << "Input coeffecient of term#" << i << ": ";
        cin >> coef[i];
        cout << "Input degree of term#" << i << ": ";
        cin >> deg[i];
        if (deg[i] > 15) {
            cout << "Size of polynomial cannot be greater than 15.\n";
            i--;
        }
        if (deg[i] > deg[i - 1]) {
            cout << "Polynomials must be in descending order\n";
            i--;
        }
        for (int j = 1; j < i; j++) {
            if (deg[i] == deg[j]) {
                cout << "You have already added a term with degree " << deg[i] << endl;
                i--;
            }
        }

    }
    shift(coef, deg, 0, terms);
    cout << "Polynomial is ";
    terms++;
    Print(terms, deg, coef);
}
void FileInput(int& terms, int deg[], int coef[]) {
    int counter = 1;
    int temp = 0;
    ifstream fin;
    fin.open("Polynomial.txt");
    if (!fin) {
        cout << "Error! File does not exist\n";
    }
    else {
        fin >> terms;
        while (!fin.eof()) {

            if (counter <= terms) {
                fin >> coef[counter];
            }
            else {
                fin >> deg[counter - terms];
            }
            counter++;
        }

    }
    shift(coef, deg, 0, terms);
    terms++;
    
}
//operation functions
int Solve(int terms, int deg[], int coef[], int variable) {
    int counter = 0;
    int result = 0;
    while (counter < terms) {
        result = result + (coef[counter] * pow(variable, deg[counter]));
        counter++;
    }
    return result;
}
void Add(int aterms, int adeg[], int acoef[],
    int bterms, int bdeg[], int bcoef[],
    int rterms, int rdeg[], int rcoef[]) {
    int newaterms = aterms, newadeg[15], newacoef[15];
    int newbterms = bterms, newbdeg[15], newbcoef[15];
    copy(adeg, newadeg, aterms);
    copy(acoef, newacoef, aterms);
    copy(bdeg, newbdeg, bterms);
    copy(bcoef, newbcoef, bterms);
    rterms = 0;
    for (int i = 0; i < newaterms; i++) {
        for (int j = 0; j < newbterms; j++) {
            if (newadeg[i] == newbdeg[j]) {
                rcoef[rterms] = newacoef[i] + newbcoef[j];
                rdeg[rterms] = newadeg[i];
                shift(newacoef, newadeg, i, newaterms);
                i--;
                shift(newbcoef, newbdeg, j, newbterms);
                j--;

                rterms++;
            }

        }
    }
    for (int i = 0; i < newaterms; i++) {
        rcoef[rterms] = newacoef[i];
        rdeg[rterms] = newadeg[i];
        rterms++;
    }
    for (int j = 0; j < newbterms; j++) {
        rcoef[rterms] = newbcoef[j];
        rdeg[rterms] = newbdeg[j];
        rterms++;
    }

    sort(rcoef, rdeg, rterms);
    output(rterms, rdeg, rcoef);
    cout << "Polynomial result of addition is ";
    Print(rterms, rdeg, rcoef);
   
    
}  
void Multiply(int aterms, int adeg[], int acoef[],
    int bterms, int bdeg[], int bcoef[],
    int rterms, int rdeg[], int rcoef[]) {
    
    rterms = 0;
    for (int i = 0; i < aterms; i++){
        for (int j = 0; j < bterms; j++) {
            rdeg[rterms]=adeg[i]+bdeg[j];
            rcoef[rterms] = acoef[i] * bcoef[j];
            rterms++;
        }
    }
   
  
    //add coefficients with same powers and fix the array accordingly
      
    for (int i = 0; i < rterms; i++) {
        for (int j = 0; j < rterms; j++) {
            if (rdeg[i] == rdeg[j] && i != j) {
                rcoef[i] = rcoef[i] + rcoef[j];
                shift(rcoef, rdeg, j, rterms);
            }
        }
    }
    
    sort(rcoef, rdeg, rterms);
    cout << "Polynomial result of multiplication is ";
    Print(rterms, rdeg, rcoef);
}
void Subtract(int aterms, int adeg[], int acoef[],
    int bterms, int bdeg[], int bcoef[],
    int rterms, int rdeg[], int rcoef[]) {
    int newaterms = aterms, newadeg[15], newacoef[15];
    int newbterms = bterms, newbdeg[15], newbcoef[15];
    copy(adeg, newadeg, aterms);
    copy(acoef, newacoef, aterms);
    copy(bdeg, newbdeg, bterms);
    copy(bcoef, newbcoef, bterms);
    rterms = 0;
    for (int i = 0; i < newaterms; i++) {
        for (int j = 0; j < newbterms; j++) {
            if (newadeg[i] == newbdeg[j]) {
                rcoef[rterms] = newacoef[i] - newbcoef[j];
                rdeg[rterms] = newadeg[i];
                shift(newacoef, newadeg, i, newaterms);
                i--;
                shift(newbcoef, newbdeg, j, newbterms);
                j--;

                rterms++;
            }

        }
    }
    for (int i = 0; i < newaterms; i++) {
        rcoef[rterms] = newacoef[i];
        rdeg[rterms] = newadeg[i];
        rterms++;
    }
    for (int j = 0; j < newbterms; j++) {
        rcoef[rterms] = -newbcoef[j];
        rdeg[rterms] = newbdeg[j];
        rterms++;
    }
    
    sort(rcoef, rdeg, rterms);
    cout << "Polynomial result of subtraction is ";
    Print(rterms, rdeg, rcoef);

}
void Equal(int aterms, int adeg[], int acoef[],
    int bterms, int bdeg[], int bcoef[]) {
    
    bool equals = true;
    if (aterms == bterms) {
        for (int i = 0; i < bterms; i++) {
            if (adeg[i] != bdeg[i] || acoef[i] != bcoef[i]) {
                equals = false;
                i = bterms + 1;
            }
        }
    }
    else
        equals = false;
    if (equals == true)
        cout << "Both polynomial are same.";
    else
        cout << "Both are different";
}
//menu function
void Menu(int coef[], int deg[], int &terms, int acoef[], int adeg[], int bcoef[], int bdeg[], int rcoef[], int rdeg[], int &aterms, int &bterms, int &rterms, bool& stop, bool &a, bool &b) {
    
    int answer;
    cout << "0. Exit the program.\n"
        << "1. Input one polynomial from user, first take number of terms from user and then for further\n"
        << "data call Input function.\n"
        << "2. Input second polynomial from file by calling Input function two times.\n"
        << "2. Take input of variable from user and calls solve function.Then print result returned by\n"
        << "solve function.\n"
        << "3. Create a polynomial for storage of result, call add function and then calls print function for\n"
        << "printing result.\n"
        << "4. Create a polynomial for storage of result, call multiply function and then calls print\n"
        << "function for printing result.\n"
        << "5. Create a polynomial for storage of result, call Subtract function and then calls print\n"
        << "function for printing result.\n"
        << "6. Ask user to print first or second polynomial and then call print function accordingly.\n"
        << "7. Calls the Equal function and print gBoth polynomial are sameh if function returned true\n"
        << "and gBoth are differenth if function returned false.\n";
    cin >> answer;
   
    switch (answer) {
    case 0: {
        stop = true;
        break;
    }
    case 1:
    {
        cout << "Input number of terms for polynomial 1: ";
        a = true;
        cin >> aterms;
        Input(aterms, adeg, acoef);
        cout << "Input number of terms for polynomial 2: ";
        b = true;
        cin >> bterms;
        Input(bterms, bdeg, bcoef);
  
        cout << endl;
        break;
    } 
    case 2:
    {
        FileInput(aterms, adeg, acoef);
        cout << "Polynomial in file # 1 is ";
        Print(aterms, adeg, acoef);
        a = true;
        cout << endl;
        FileInput(bterms, bdeg, bcoef);
        cout << "Polynomial in file # 2 is ";
        Print(bterms, bdeg, bcoef);
        b = true;
        cout << endl;
        break;
    }
    case 3:
    {
        int variable;
        cout << "Polynomial 1 or 2?\n";
        cin >> answer;
        cout << "Input variable: ";
        cin >> variable;
        if (answer == 1) {
            if (a == true)
                cout << "Solution for " << variable << " is " << Solve(aterms, adeg, acoef, variable);
            else
                cout << "You must store a Polynomial in 1 first ";
        }

        else if (answer == 2) {
            if (a == true)
                cout << "Solution for " << variable << " is " << Solve(bterms, bdeg, bcoef, variable);
            else
                cout << "You must store a Polynomial in 2 first ";
        }
        else
            cout << "Invalid Input.";
            
        cout << endl;
        break;
    } 
    case 4:
    {
        if (a == true && b == true)
            Add(aterms, adeg, acoef, bterms, bdeg, bcoef, rterms, rdeg, rcoef);
        else
            cout << "You must store a polynomial in 1 and 2 first.";

        cout << endl;
        break;
    }
    case 5:
    {
        if (a == true && b == true)
            Multiply(aterms, adeg, acoef, bterms, bdeg, bcoef, rterms, rdeg, rcoef);
        else
            cout << "You must store a polynomial in 1 and 2 first.";
        
        cout << endl;
        break;
    }
    case 6:
    {

        if (a == true && b == true)
            Subtract(aterms, adeg, acoef, bterms, bdeg, bcoef, rterms, rdeg, rcoef);
        else
            cout << "You must store a polynomial in 1 and 2 first.";

        
        cout << endl;
        break;
    }
    case 7:
    {
        cout << "1 or 2\n";
        int choice;
        cin >> choice;
        
        if (choice == 1)
            Print(aterms, adeg, acoef);
        
        else if (choice == 2)
            Print(bterms, bdeg, bcoef);
        else
            cout << "Invalid output\n";
        cout << endl;
        break;
    } case 8:
    {
        if (a == true && b == true)
            Equal(aterms, adeg, acoef, bterms, bdeg, bcoef);
        else
            cout << "You must store a polynomial in 1 and 2 first.";
        
        break;
    }
   
    default:
        cout << "Invalid Input";
    }

}

int main()
{ 
    int coef[15];
    int deg[15];
    int terms = 15;
    int acoef[15], bcoef[15], adeg[15], bdeg[15], rcoef[15], rdeg[15];
    int aterms = 0, bterms = 0, rterms = 0;
    bool stop=false;
    bool a = false, b = false;
    while (stop == false) {
        Menu(coef, deg, terms, acoef, adeg, bcoef, bdeg, rcoef, rdeg, aterms, bterms, rterms, stop, a, b);
        cout << endl;
    }
   
    return 0;

}
