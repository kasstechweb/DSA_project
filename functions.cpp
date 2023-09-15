/* ================= 2/6 Functions File ============|
DSA Project 2020 – Borneo Hair Salon                |
Metric #: 68848 Mahmoud Kassab                     |
Description: Borneo Hair Salon System built with C++|
            Manage servces, Appointments, transac-  |
            -tions and display summary report by    |
            service type and total income           |
                                                    |
>> some functions used through the program          |
>> to print seperators in output and to organize    |
    output printf                                   |
// ================================================*/
#include <iomanip>
// ============================ Functions ============//
void sep1(int n) {
    string s(n, '-');
    cout << "\t" << s << endl;
}

void sep2() {
    string s(30, '=');
    cout << "\t" << s << endl;
}

template<typename T> void print(T t, const int& width){
    const char separator    = ' ';
    cout << left << setw(width) << setfill(separator) << t;
}
