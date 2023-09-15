/* ================= 3/6 Services class=============|
DSA Project 2020 – Borneo Hair Salon                |
Metric #: 68848 Mahmoud Kassab                     |
Description: Borneo Hair Salon System built with C++|
            Manage servces, Appointments, transac-  |
            -tions and display summary report by    |
            service type and total income           |
                                                    |
>> functions for services, add, manipulate services |
>> search by a service id and print services list   |
    getting service id, price to be used in other   |
    classes                                         |
// ================================================*/
class Services{
    private:
        struct node{
            int ID;
            string name;
            double price;
            node *next;
        };
        node *head, *current, *previous, *tmp;
    public:
        string name;double price;
        Services();
        void menu();
        void list_all_services();
        void services_list();
        bool search_list(int ID);
        void display_services_list();
        void add_service();
        void update_service();
        void delete_service();

        void set_service(string service_name, double price);
};

void Services::menu() {
    int num = 0;
    sep1(30);
    cout << "\t>> /main/Manage services/" << endl;
    sep1(30);
    cout << "\t\t1. List all services" << endl;
    cout << "\t\t2. Add a service" << endl;
    cout << "\t\t3. Update a service" << endl;
    cout << "\t\t4. Delete a service" << endl;
    cout << "\t\t5. Main menu" << endl;
    cout << "\t\t6. Exit" << endl;

    cin.clear(); cin.sync();
    cout << "\tChoose option: ";
    cin >> num;

    switch(num) {
        case 1:
            sep2();
            this->display_services_list();
            break;
        case 2:
            sep2();
            this->add_service();
            break;
        case 3:
            sep2();
            this->update_service();
            break;
        case 4:
            sep2();
            this->delete_service();
            break;
        case 5:
            sep2();
            cout << endl;
            main_menu();
            break;
        case 6:
            exit(1);

        default:
            cout << "\n\n\tPlease enter a valid number and try again!...\n";
            sep2();
            this->menu();
    }
}

Services::Services() {
    head = NULL;
}

void Services::set_service(string service_name, double price){
    node *newNode;
    newNode = new node;

    newNode->name = service_name;
    newNode->price = price;
    // newNode->ID = 11;
    newNode->next = NULL;
    if(head == NULL) {      // first node
        newNode->ID = 1;    // first id = 1
        head = newNode;     // head points to first node
    }else {     //not first node
        current = head;
        while(current->next != NULL) {
            current = current->next;
        }
        newNode->ID = current->ID + 1; // increment id
        current->next = newNode;
    }
}

void Services::add_service() { // add a service to the services linked list
    string name;double price;

    cin.clear(); cin.sync(); // clearing and sync for get line
    cout << "\n\tType service name: ";
    getline(cin, name);
    cout << "\tType service price (1.20): ";
    cin >> price;

    if(!cin.good()) { // check prc not double
        cout << "\n\t\t Price must be a number" << endl;
        this->menu();
    }else {
        this->set_service(name, price);
        cout << endl;
        cout << "\t\t Adding is successful" << endl;
        sep2();
        this->menu();
    }
}

void Services::services_list() { // print all services list
    current = head;

    cout << "\n\t\t\tAll Services" << endl;
    sep1(60);
    cout << "\t";
    print("Service ID", 20);print("Name", 20);print("Price", 10);
    cout << endl;
    sep1(60);

    if(head != NULL) {
        while (current != NULL ){ // loop till the end of the list
            cout << "\t" ;
            print(current->ID, 20);
            print(current->name, 20);
            cout << "RM " ;
            print(current->price, 10);
            cout << endl;
            current = current->next;
        }
    }else {
        cout << "\t\t The list is empty!..." << endl;
    }
    cout << endl;
}

void Services::display_services_list() { // to display the list and go back to services mmenu
    this->services_list();
    this->menu();
}

bool Services::search_list(int ID) { // search for a service by id
    current = head;
    if(head != NULL) {
        while(current != NULL) {
            if(current->ID == ID) {  // if id is found
                this->name = current->name;
                this->price = current->price;
                return true;
            }else {
                previous = current;
                current = current->next;
            }
        }
    }
    return false;
}

void Services::update_service(){ // update service data
    int service_id;
    this->services_list();

    // get user input for service number
    cout << "\tEnter service ID: ";
    cin >> service_id;

    if(!cin.good()) {   // check service not integer
        cout << "\n\t\t Service ID is not valid, try again..." << endl;
        this->menu();
    }else {
        current = head;
        if(head != NULL) { // not first node
            while(current != NULL) {  // search till list end
                if(current->ID == service_id) {  // search for service id
                    cin.clear(); cin.sync(); // clearing and sync for get line
                    cout << "\tEnter new service name: ";
                    getline(cin, current->name);
                    cout << "\tEnter new service price: ";
                    cin >> current->price;
                    break;
                }else { // keep moving to next node
                    current = current->next;
                }
            }
            this->display_services_list(); // after editing display new list
        }
    }
}

void Services::delete_service() { // to delete a service from the list
    int service_id;
    this->services_list();

    // get user input for service number
    cout << "\tEnter service ID: ";
    cin >> service_id;

    if(!cin.good()) {   // check service not integer
        cout << "\n\t\t Service ID is not valid, try again..." << endl;
        this->menu();
    }else {
        if(this->search_list(service_id)) { // if found service id
            if(head->ID == current->ID) { // first node
                tmp = current;
                head = NULL;
                delete tmp;
            }else {
                tmp = current;
                previous->next = current->next;
                delete tmp;
            }
            cout << endl;
            sep2();
            cout << "\t\t Delete is successful" << endl;
            this->display_services_list();
        }else { // not found service id
            cout << "\t\t service id can't be found." << endl;
        }
    }
    this->menu();
}
