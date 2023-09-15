/* ================= 5/6 Transactions class=========|
DSA Project 2020 – Borneo Hair Salon                |
Metric #: 68848 Mahmoud Kassab                     |
Description: Borneo Hair Salon System built with C++|
            Manage servces, Appointments, transac-  |
            -tions and display summary report by    |
            service type and total income           |
                                                    |
>> functions for transactions, add, list            |
>> storing appointment id for each transaction and  |
    get the data from appointment classe            |
>> search for a transaction by id                   |
// ================================================*/
class Transactions: public Appointments {
    private:
        struct node{
            int ID;
            int appointmentID;
            node *next;
        };
        node *head, *current, *previous;

    public:
        Appointments app;int appointment_id;
        Transactions();
        void menu();
        void add_transaction(int appointmentID);
        void list_all_transactions();
        void search_transaction();
        bool find_transaction(int transaction_id);
};

Transactions::Transactions() {
    head = NULL;
}

void Transactions::menu() {
    int num = 0;
    sep1(30);
    cout << "\t>> /main/List-Search Transactions/" << endl;
    sep1(30);
    cout << "\t\t1. List all Transactions" << endl;
    cout << "\t\t2. Search Transactions" << endl;
    cout << "\t\t3. Main menu" << endl;
    cout << "\t\t4. Exit" << endl;

    cin.clear(); cin.sync();
    cout << "\tChoose option: ";
    cin >> num;

    switch(num) {
        case 1:
            sep2();
            this->list_all_transactions();
            this->menu();
            break;
        case 2:
            sep2();
            this->search_transaction();;
            break;
        case 3:
            sep2();
            cout << endl;
            main_menu();
            break;
        case 4:
            exit(1);

        default:
            cout << "\n\n\tPlease enter a valid number and try again!...\n";
            sep2();
            this->menu();
    }
}

void Transactions::add_transaction(int appointmentID) { // add new transaction, add appointment id inside
    // create a new node
    node *newNode = new node();
    newNode->appointmentID = appointmentID;
    newNode->next = NULL;

    if(head == NULL) { // first transaction
        newNode->ID = 1;    // if new transaction id will be 1
        head = newNode;
    }else {
        current = head;
        while(current->next != NULL) {
            current = current->next;
        }
        newNode->ID = current->ID + 1; // increment id every time visiting a node
        current->next = newNode;
    }
    add_rprt(newNode->ID);
}

void Transactions::list_all_transactions() { // printing transaction list
    current = head;

    cout << "\n\t\t\tAll Transactions" << endl;
    sep1(60);
    cout << "\t";
    print("TID#", 10);print("user", 10);print("service", 15);print("Price", 10);print("appointmentID", 15);
    cout << endl;
    sep1(60);

    if(head != NULL) {
        while (current != NULL ){
            cout << "\t" ;
            print(current->ID, 10);
            app.search_appointment(current->appointmentID); // searching for the appointment id
            // get the user from the appointment and service name, price from services
            print(app.user, 10);
            print(app.srvs.name, 15);
            print(app.srvs.price, 10);
            print(current->appointmentID, 15);
            cout << endl;
            current = current->next;
        }
         cout << endl;
    }
}

bool Transactions::find_transaction(int transaction_id) { // find a transaction by id
    bool found = false;
    current = head;
    if(head != NULL) {
        while (current != NULL && !found){
            if (current->ID == transaction_id) {
                this->appointment_id = current->appointmentID; // store appointment id
                found = true;
            }else {
                current = current->next;
            }
        }
    }
    return found;
}

void Transactions::search_transaction() { // search for a transaction
    int transaction_id;

    cout << "\n\tEnter transaction ID #: ";
    cin >> transaction_id;
    if(!cin.good()) {   // check service not integer
        cout << "\n\t\t transaction ID is not valid, try again..." << endl;
        this->menu();
    }else {
        if(this->find_transaction(transaction_id)) { // if transaction found
            sep1(60);
            cout << "\t";
            print("TID#", 10);print("user", 10);print("service", 15);print("Price", 10);print("appointmentID", 15);
            cout << endl;
            sep1(60);
            cout << "\t" ;
            print(current->ID, 10);
            app.search_appointment(current->appointmentID);
            print(app.user, 10);
            print(app.srvs.name, 15);
            print(app.srvs.price, 10);
            print(current->appointmentID, 15);
            cout << endl;
        }else { // transaction wasn't found
            cout << endl;
            cout << "\n\t\tcan't find this transaction ID, try again..." << endl;
        }
    }
    
    this->menu();
}
