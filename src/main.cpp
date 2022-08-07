#include<iostream>
#include<pthread.h>
#include<time.h>
#include<cstdlib>
using namespace std;

pthread_mutex_t mtlock;
pthread_t tid;
int ticket_no = 1, customer_count = 0, total_customers = 0;
bool customers[40];

void* th_fun(void* arg) {
	pthread_mutex_lock(&mtlock);

	int check = 0;
	while(check < 4) {
		while(customers[customer_count] != 1 && customer_count < 40) {
			customer_count++;
		}

		if(ticket_no <= 20 && customer_count < 40) {
			cout << "Ticket No # " << ticket_no << endl;
			cout << "Sold to Customer # " << customer_count << endl;
			cout << "Sold by Seller id # " << pthread_self() << endl << endl;
			ticket_no++;
			check++;
			customer_count++;
		}

		else {
			cout << "No More Customers" << endl;
			break;
		}
	}
	
	if (ticket_no > 20 && total_customers != 20) {
		cout << "HouseFull" << endl;
		cout << "Remaining Customers # ";
		for (int i = customer_count ; i < 40 ; i++) {
			if(customers[i] == 1) {
				cout << i << " ";
			}
		}
		cout << endl;
	}

	pthread_mutex_unlock(&mtlock);
	pthread_exit(NULL);
}

int main() {
	pthread_mutex_init(&mtlock, NULL);
	srand(time(NULL));

	for (int i = 0 ; i < 40 ; i++) {
		bool temp = rand() % 2;
		customers[i] = temp;
		
		if (temp == 1) {
			total_customers++;
		}
	}

	cout << "Total Customers = " << total_customers << endl << endl;

	for (int i = 0 ; i < 5 ; ++i) {
		pthread_create(&tid, NULL, th_fun, NULL);
	}

	pthread_mutex_destroy(&mtlock);

	pthread_exit(NULL);
}