/* ================= 4/6 Appointments class=========|
DSA Project 2020 – Borneo Hair Salon                |
Metric #: 68848 Mahmoud Kassab                     |
Description: Borneo Hair Salon System built with C++|
            Manage servces, Appointments, transac-  |
            -tions and display summary report by    |
            service type and total income           |
                                                    |
>> functions for appointment, add, manipulate       |
>> complete and delete appointment using queue DS   |
    search for an appointment by id, enqueu, dequeue|
>> adding new transaction if complete appointment   |
// ================================================*/
class Appointments: public Services{
    private:
        struct node{
            int ID;
            string user;
            string date;
            string time;
            string status;
            int serviceID;
            node *next;
        };
    public:
    node *front, *current, *rear;
    string user;int service_id;
    Services srvs;
    Appointments();
    void menu();
    void add_appointment();
    void list_all_appointments();
    void edit_appointment();
    void cancel_appointment();
    void delete_appointment();
    void complete_appointment();
    bool search_appointment(int app_ID);
    void enQ(string user, string date, string time, string status, int serviceID); // set appointment
    void deQ();
};

Appointments::Appointments() { // initialize front and rear
  front = rear = NULL;
}

void Appointments::menu() {
    int num = 0;
    sep1(30);
    cout << "\t>> /main/Manage appintments/" << endl;
    sep1(30);
    cout << "\t\t1. List all appointments" << endl;
    cout << "\t\t2. Add an appointment" << endl;
    cout << "\t\t3. Edit an appintment" << endl;
    cout << "\t\t4. Cancel an appointment" << endl;
    cout << "\t\t5. Delete an appointment" << endl;
    cout << "\t\t6. Complete an appointment" << endl;
    cout << "\t\t7. Main menu" << endl;
    cout << "\t\t8. Exit" << endl;

    cin.clear(); cin.sync();
    cout << "\tChoose option: ";
    cin >> num;

    switch(num) {
        case 1:
            sep2();
            this->list_all_appointments();
            this->menu();
            break;
        case 2:
            sep2();
            this->add_appointment();
            break;
        case 3:
            sep2();
            this->edit_appointment();
            break;
        case 4:
            sep2();
            this->cancel_appointment();
            break;
        case 5:
            sep2();
            this->delete_appointment();
            break;
        case 6:
            sep2();
            this->complete_appointment();
            break;
        case 7:
            sep2();
            cout << endl;
            main_menu();
            break;
        case 8:
            exit(1);

        default:
            cout << "\n\n\tPlease enter a valid number and try again!...\n";
            sep2();
            this->menu();
    }
}

void Appointments::add_appointment() { // adding new appointment
    string name, date, time;int serviceID;
    char delim, delim2;
    int day, month, year = 0, hour, minute = 0;

    //display service list
    srvs.services_list();
    cout << "\n\tChoose service #: ";
    cin >> serviceID;
    if(!cin.good()) {   // check service not integer
        cout << "\n\t\t Service number is not valid, try again..." << endl;
        this->menu();
    }else {
        // check if service id found
        if(srvs.search_list(serviceID)) { // if service id found
            cin.clear(); cin.sync();
            cout << "\tType user name: ";
            getline(cin, name);
            cout << "\tType appointment date (DD/MM/YYYY): ";
            getline(cin, date);
            // dividing date in day, month and year
            istringstream stm(date) ;
            stm >> day >> delim ;
            stm >> month >> delim ;
            stm >> year ;
            // check date format
            if(day < 1 || month < 1 || year == 0 || year < 1900) {
                cout << "\n\tdate is not in a propper format (DD/MM/YYYY)..." << endl;
                this->menu();
            }else {
                cout << "\tType appointment time (HH:MM AM/PM): ";
                getline(cin, time);
                // dividing time in hours, minutes
                istringstream ss(time) ;
                ss >> hour >> delim2 ;
                ss >> minute ;
                // check time format
                if(hour < 1 || minute < 1) {
                    cout << "\n\tTime is not in a propper format (HH:MM AM/PM)..." << endl;
                    this->menu();
                }else {
                    this->enQ(name, date, time, "Pending", serviceID);
                    cout << "\n\t\t Adding is successful" << endl;
                }
            }
        }else { // service id not found
            cout << "\n\t\t Service # not found, try again..." << endl;
            this->menu();
        }

    }
    this->menu();
}// end add appointments

void Appointments::list_all_appointments(){ // printing appointment list
    cout << "\n\t\tAll Appointments" << endl;
    sep1(90);
    cout << "\t";
    print("ID#", 5);print("User Name", 20);print("Service", 20);
    print("Date", 15);print("Time", 10);print("Price", 10);
    print("Status", 10);
    cout << endl;
    sep1(90);

    if(front != NULL) {
        node *tmp = front;
        while (tmp != NULL ){
            if(srvs.search_list(tmp->serviceID)) { // search service id for each appointment
                cout << "\t" ;
                print(tmp->ID, 5);print(tmp->user, 20);print(srvs.name, 20);
                print(tmp->date, 15);print(tmp->time, 10);print(srvs.price, 10);
                print(tmp->status, 10);
                cout << endl;
                tmp = tmp->next; // move to the next appointment
            }
        }
    }else {
        cout << " The list is empty!..." << endl;
    }
    cout << endl;
}

void Appointments::cancel_appointment() { // cancel appointment
    int appID;
    this->list_all_appointments();
    cout << "\n\tChoose Appointment #: ";
    cin >> appID;

    if(!cin.good()) {   // check service not integer
        cout << "\n\t\t Appointment number is not valid, try again..." << endl;
        this->menu();
    }else { // appID is a number
        if(this->search_appointment(appID)) { // seach for appointment id
            current->status = "Canceled"; // update status to Canceled
            cout << "\n\tCancelation is successful." << endl;
        }else {
            cout << "\n\t\t Appointment number can't be found..." << endl;
        }
        this->menu();
    }

} // end delete appointment

void Appointments::edit_appointment() { // editing appointment
    int appID, option;
    string name, date, time;
    char delim, delim2;
    int day, month, year = 0, hour, minute = 0;
    this->list_all_appointments();
    cout << "\n\tChoose Appointment #: ";
    cin >> appID;

    if(!cin.good()) {   // check service not integer
        cout << "\n\t\t Appointment number is not valid, try again..." << endl;
        this->menu();
    }else { // appID is a number
        if(this->search_appointment(appID)) { // seach for appointment id
            if(current->status == "Pending"){ // check for status
                cin.clear(); cin.sync();
                cout << "\tType new user name: ";
                getline(cin, name);
                cout << "\tType new appointment date (DD/MM/YYYY): ";
                getline(cin, date);
                // dividing date in day, month and year
                istringstream stm(date) ;
                stm >> day >> delim ;
                stm >> month >> delim ;
                stm >> year ;
                // check date format
                if(day < 1 || month < 1 || year == 0 || year < 1900) {
                    cout << "\n\tdate is not in a propper format (DD/MM/YYYY)..." << endl;
                    this->menu();
                }else {
                    cout << "\tType new appointment time (HH:MM AM/PM): ";
                    getline(cin, time);
                    // dividing time in hours, minutes
                    istringstream ss(time) ;
                    ss >> hour >> delim2 ;
                    ss >> minute ;
                    // check time format
                    if(hour < 1 || minute < 1) {
                        cout << "\n\tTime is not in a propper format (HH:MM AM/PM)..." << endl;
                        this->menu();
                    }else { // all good do editing
                        current->user = name;
                        current->date = date;
                        current->time = time;
                        cout << "\n\tEdit is successful." << endl;
                    }
                }
            }else { // not pending
                cout << "\n\tOnly allowed to edit pending appointments." << endl;
            }
        }else {
            cout << "\n\t\t Appointment number can't be found..." << endl;
        }
        this->menu();
    }

}// end edit appointment

void Appointments::delete_appointment() {
    char option;
    this->list_all_appointments();
    cout << "\n\tFirst Appintment will be deleted from the list(Y/N): ";
    cin >> option;

    if(!cin.good()) {   // check service not integer
        cout << "\n\t\t Appointment number is not valid, try again..." << endl;
        this->menu();
    }else {
        if(option == 'Y' or option == 'y') { // if user choose Y or y
            if(front->status == "Completed") { // only delete Completed appointment
                this->deQ(); // when deq delete the first appointment
                cout << "\n\tDeletion is successful." << endl;
            }else {
                cout << "\n\tCan't delete a pending appointment." << endl;
            }
        }
        this->menu();
    }
} // end delete appointment

void Appointments::complete_appointment() {
    int appID;
    this->list_all_appointments();
    cout << "\n\tChoose Appointment #: ";
    cin >> appID;

    if(!cin.good()) {   // check service not integer
        cout << "\n\t\t Appointment number is not valid, try again..." << endl;
        this->menu();
    }else {
        if(this->search_appointment(appID)) { // seach for appointment id
            current->status = "Completed";
            add_trns(appID);    // adding new transaction if appointment is Completed
            cout << "\n\tStatus update is successful." << endl;
        }else {
            cout << "\n\t\t Appointment number can't be found..." << endl;
        }
        this->menu();
    }
}

bool Appointments::search_appointment(int app_ID) { // search for appointment id
    current = front;
    if(front != NULL) {
        while(current != NULL) {
            if(current->ID == app_ID) {  // if appointment id found return true
                this->user = current->user;
                this->service_id = current->serviceID;
                srvs.search_list(current->serviceID);
                return true;
            }else {
                current = current->next;
            }
        }
    }
    return false;
}

// enqueu to add new appointment to the queue rear
void Appointments::enQ(string user, string date, string time, string status, int serviceID) {
  node *tmp = new node();
  tmp->user = user;
  tmp->date = date;
  tmp->time = time;
  tmp->status = status;
  tmp->serviceID = serviceID;

  // If queue is empty, new node is front and rear
  if (rear == NULL) {
      tmp->ID = 1;
      front = rear = tmp;
      return;
  }

  // Add the new node at the end of queue and change rear
  tmp->ID = rear->ID + 1;
  rear->next = tmp;
  rear = tmp;
}

void Appointments::deQ() { // dequeu remove appointment from the front
  // If queue is empty, return NULL.
  if (front == NULL)
      return;

  // Store previous front and move front one node ahead
  node *temp = front;
  front = front->next;

  // If front becomes NULL, then change rear also as NULL
  if (front == NULL)
      rear = NULL;

  delete (temp);
}
