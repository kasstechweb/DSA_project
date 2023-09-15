/* ================= 6/6 Report class ==============|
DSA Project 2020 – Borneo Hair Salon                |
Metric #: 68848 Mahmoud Kassab                     |
Description: Borneo Hair Salon System built with C++|
            Manage servces, Appointments, transac-  |
            -tions and display summary report by    |
            service type and total income           |
                                                    |
>> functions for displaying report                  |
>> sorting the report by service type               |
    or by total income in a descending order        |
// ================================================*/
class Report: public Transactions {
    private:
        struct node{
            int service_id;
            string service_name;
            int sales_num;
            double income;
            node *next;
        };
        node *head, *current, *previous;

    public:
        Transactions trns;
        Report();
        void menu();
        void add_report(int transaction_id);
        void list_report(string name_income);
        node* MergeSortedList(node* lst1, node* lst2, string name_income);
        void SplitList(node* source, node** front, node** back);
        void MergeSort(node** thead, string name_income);

};

void Report::menu() {
    int num = 0;
    sep1(30);
    cout << "\t>> /main/Summary report/" << endl;
    sep1(30);
    cout << "\t\t1. Sort by service type" << endl;
    cout << "\t\t2. Sort by total income" << endl;
    cout << "\t\t3. Main menu" << endl;
    cout << "\t\t4. Exit" << endl;

    cin.clear(); cin.sync();
    cout << "\tChoose option: ";
    cin >> num;

    switch(num) {
        case 1:
            sep2();
            this->MergeSort(&head, "name"); // merge sort by name
            this->list_report("name");  // list the summary report
            this->menu();
            break;
        case 2:
            sep2();
            this->MergeSort(&head, "income");   // merge sort by name
            this->list_report("income");    // list the summary report
            this->menu();
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

Report::Report() {
    head = NULL;
}

void Report::add_report(int transaction_id) { // adding new report
    if(trns.find_transaction(transaction_id)) { // searching for the transaction id
        trns.app.search_appointment(trns.appointment_id);
    }

    node *newNode = new node();
    newNode->service_id = trns.app.service_id;
    newNode->service_name = trns.app.srvs.name;
    newNode->sales_num = 1;
    newNode->income = trns.app.srvs.price;
    newNode->next = NULL;

    if(head == NULL) { // first transaction
        head = newNode;
    }else {
        current = head;
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void Report::list_report(string name_income) { // listing the report by name or by income
    current = head;

    if(name_income == "name") { // different title
        cout << "\n\t\tSummary Report By service Name" << endl;
    }else {
        cout << "\n\t\tSummary Report By Total income (Descending)" << endl;
    }

    sep1(60);
    cout << "\t";
    print("Service Name", 25);print("Sales Number", 25);print("income", 10);
    cout << endl;
    sep1(60);

    if(head != NULL) {
        while (current != NULL ){
            cout << "\t" ;
            print(current->service_name, 25);
            print(current->sales_num, 25);
            print(current->income, 10);
            cout << endl;
            current = current->next;
        }
         cout << endl;
    }
}

// Merging two sorted lists.
Report::node* Report::MergeSortedList(node* lst1, node* lst2, string name_income)
{
	node* result = NULL;

	// Base Cases
	if (lst1 == NULL){
        return (lst2);
    }else if (lst2 == NULL){
        return (lst1);
    }

    if (name_income == "name") {
        // recursively merging two lists
    	if (lst1->service_id < lst2->service_id) { // sort based on service id 1, 2, 3, ...
    		result = lst1;
    		result->next = MergeSortedList(lst1->next, lst2, name_income); // recursion
    	}
        else if(lst1->service_id == lst2->service_id) { // if two service ids found
    		lst1->sales_num += lst2->sales_num;   // increment sales number
    		lst1->income += lst2->income;         // add the income together
    		result = lst1;
    		result->next = MergeSortedList(lst1->next, lst2->next, name_income); // recursion
    	}
    	else {
    		result = lst2;
    		result->next = MergeSortedList(lst1, lst2->next, name_income);
    	}
    }else if(name_income == "income") { // if sorting by income
        // recursively merging two lists
    	if (lst1->income > lst2->income) { // sorting by income descending
    		result = lst1;
    		result->next = MergeSortedList(lst1->next, lst2, name_income);
    	}
        else if(lst1->service_id == lst2->service_id) { // if two service ids found
    		lst1->sales_num += lst2->sales_num;    // increment sales number
    		lst1->income += lst2->income;         // add the income together
    		result = lst1;
    		result->next = MergeSortedList(lst1->next, lst2->next, name_income);
    	}
    	else {
    		result = lst2;
    		result->next = MergeSortedList(lst1, lst2->next, name_income);
    	}
    }

	return result;
}

void Report::SplitList(node* source, node** front, node** back) { // split two lists
	node* ptr1;
	node* ptr2;
	ptr2 = source;
	ptr1 = source->next;

	// ptr1 is incrmented twice and ptr2 is icremented once.
	while (ptr1 != NULL) {
		ptr1 = ptr1->next;
		if (ptr1 != NULL) {
			ptr2 = ptr2->next;
			ptr1 = ptr1->next;
		}
	}

	// ptr2 is at the midpoint.
	*front = source;
	*back = ptr2->next;
	ptr2->next = NULL;
}

void Report::MergeSort(node** thead, string name_income) { // merge after sort
	node* head = *thead;
	node* ptr1;
	node* ptr2;

  // Base Case
	if ((head == NULL) || (head->next == NULL)) {
		return;
	}

	// Splitting list
	SplitList(head, &ptr1, &ptr2);

	// Recursively sorting two lists.
	MergeSort(&ptr1, name_income);
	MergeSort(&ptr2, name_income);

	// Sorted List.
	*thead = MergeSortedList(ptr1, ptr2, name_income); // store in thead
}
