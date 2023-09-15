/* ================= 1/6 Mail File =================|
DSA Project 2020 – Borneo Hair Salon                |
Metric #: 68848 Mahmoud Kassab                     |
Description: Borneo Hair Salon System built with C++|
            Manage servces, Appointments, transac-  |
            -tions and display summary report by    |
            service type and total income           |
                                                    |
>> include all the classes, create objects          |
>> load 5 presets of services, appointments and     |
    transactions and report                         |
// ================================================*/

#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;
void main_menu();
void add_trns(int);
void add_rprt(int);

#include "functions.cpp"
#include "services.cpp"
#include "appointments.cpp"
#include "transactions.cpp"
#include "report.cpp"

Services srvs;
Appointments app;
Transactions trns;
Report report;
void load_presets();

int main() {
    cout << "\t***Welcome to Borneo Hair Salon***" << endl;

    // load presets
    load_presets();
    main_menu();
    return 0;
}

void main_menu() {
    int num=0;

   sep1(30);
    cout << "\t>> /main/" << endl;
   sep1(30);
    cout << "\t\t1. Manage services" << endl;
    cout << "\t\t2. Manage appointments" << endl;
    cout << "\t\t3. List/Search transactions" << endl;
    cout << "\t\t4. Summary report" << endl;
    cout << "\t\t5. Exit" << endl;

    cin.clear(); cin.sync();    // cleaing cin
    cout << "\tChoose option: ";
    cin >> num;

    app.srvs = srvs;
    trns.app = app;
    report.trns = trns;
    switch(num) {
        case 1:
            srvs.menu();
            sep2();
            break;
        case 2:
            sep2();
            app.menu();
            break;
        case 3:
           sep2();
           trns.menu();
           break;
       case 4:
          sep2();
          report.menu();
          break;
        case 5:
            exit(1);
        default:
            cout << "\n\tPlease enter a valid number and try again!...\n";
            cout << endl;
            sep2();
            main_menu();
    }
}
void load_presets() { // 5 presets of services, appointments, and transactions
    srvs.set_service("first service", 11.34);
    srvs.set_service("second service", 12.66);
    srvs.set_service("third service", 10.00);
    srvs.set_service("fourth service", 10.43);
    srvs.set_service("fifth service", 59.99);

    app.enQ("user 1", "11/11/2020", "11:11 AM", "Pending", 1);
    app.enQ("user 2", "12/12/2020", "12:12 AM", "Completed", 2);
    app.enQ("user 2", "12/12/2020", "12:12 AM", "Completed", 1);
    app.enQ("user 1", "11/11/2020", "11:11 AM", "Completed", 1);
    app.enQ("user 1", "11/11/2020", "11:11 AM", "Completed", 5);

    // when adding transactions, it also add in report
    trns.add_transaction(2);
    trns.add_transaction(3);
    trns.add_transaction(4);
    trns.add_transaction(5);
}

void add_trns(int app_id) { // function to add a new transaction
    trns.add_transaction(app_id);
}
void add_rprt(int trns_id) { // function to add a new report
    app.srvs = srvs;
    trns.app = app;
    report.trns = trns; // connecting the classes
    report.add_report(trns_id);
}
