#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//train details
typedef struct {
    int serial_number,train_number,platform_number;
    char destination[50],train_route[50],departure_time[10],arrival_time[10],date[11];
    float distance; 
} Train;

//passenger details
typedef struct {
    char name[50];
    int age;
    char compartment_class[20];
    char seat_type[20];
    int seat_number;
    int compartment_number;
    int pnr;
} Passenger;

//display available trains in tabular coloumn
void displayTrains(Train trains[], int num_trains) {
    printf("Available Trains:\n");
    printf("---------------------------------------------------------------------------------------------------")
    printf("|Sl.No.|  Date   |    Train Name     |     Train Route   |    Train No. | Departure Arrival  | Platform|\n");
    for (int i = 0; i < num_trains; i++) {
        printf("|%-7d|%-10s|%-20s|%-18s|%-10d|%-9s|%-8s|%-8d|\n",trains[i].serial_number, trains[i].date, trains[i].destination,
               trains[i].train_route, trains[i].train_number, trains[i].departure_time, trains[i].arrival_time, trains[i].platform_number);
    }
}

//display available seats in a compartment in tabular coloumn
void displayAvailableSeats(int num_seats) {
    printf("Available Seats in Compartment:\n");
    printf("  ");
    for (int i = 1; i <= num_seats; i++) {
        printf("%-5d", i);
        if (i % 10 == 0) //newline after every 10 seats
            printf("\n  ");
    }
    printf("\n");
}

//generates a random PNR number
int generatePNR() {
    srand(time(NULL));
    return rand() % 10000 + 1000;
}

int main() {
    Train trains[] = {
        {1, "Coimbatore Shatabdi Express", "MS to CBE", 12243, "08:00", "10:00", "08/05/2024", 1, 200.5},
        {2, "Kanyakumari Express", "MS to CAPE", 12634, "09:00", "11:30", "08/05/2024", 2, 350.2},
        {3, "Tiruchirappalli Rockfort Express", "MS to TPJ", 12653, "10:30", "13:00", "09/05/2024", 3, 500.0}
        {4, "Nagercoil Guruvayur Express", "MS to NJT", 16344, "10:30", "13:00", "09/05/2024", 2, 500.0}
        {5, "Karaikudi Pallavan Express", "MS to KKDI", 12605, "10:30", "13:00", "08/05/2024", 3, 500.0}
        {6, "Madurai Pandian Express", "MS to MDU", 12637, "10:30", "13:00", "09/05/2024", 1, 500.0}
        {7, "Thanjavur Uzhavan Express", "MS to TJ", 16184, "10:30", "13:00", "10/05/2024", 3, 500.0}
        {8, "Kumbakonam Express", "MS to KMU", 16182, "10:30", "13:00", "10/05/2024", 2, 500.0}
    };
    int num_trains = sizeof(trains) / sizeof(trains[0]);

    int selected_train;

    //display available trains in tabular coloumn
    displayTrains(trains, num_trains);

    //user selects a train
    printf("Select a train (1, 2, 3 etc.): ");
    scanf("%d", &selected_train);

    system("clear");

    //select class of compartment
    printf("Select class of compartment (First Class, Second Class, General Compartment): ");
    char compartment_class[20];
    scanf("%s", compartment_class);

    system("clear");

    //select compartment
    printf("Select compartment (1-5): ");
    int compartment_number;
    scanf("%d", &compartment_number);

    system("clear");

    //display available seats in the selected compartment in tabular coloumn
    printf("Selected Compartment: %d\n", compartment_number);
    displayAvailableSeats(50); //50 seats in each compartment

    system("clear");

    // display additional information for passenger details input
    printf("Train Name: %s\n", trains[selected_train - 1].destination);
    printf("Train Route: %s\n", trains[selected_train - 1].train_route);
    printf("Distance to Destination: %.2f\n", trains[selected_train - 1].distance);
    printf("Compartment Number: %d\n", compartment_number);
    printf("Date of Boarding: %s\n", trains[selected_train - 1].date);

    //passenger details input based on number of tickets
    int num_tickets;
    printf("Enter number of tickets: ");
    scanf("%d", &num_tickets);

    Passenger passengers[num_tickets];
    for (int i = 0; i < num_tickets; i++) {
        printf("Enter details for Passenger %d:\n",i+1);
        printf("Name: ");
        scanf("%s", passengers[i].name);
        printf("Age: ");
        scanf("%d", &passengers[i].age);
        strcpy(passengers[i].compartment_class, compartment_class);
        strcpy(passengers[i].seat_type, "Seater"); //all selected seats are Seater
        passengers[i].compartment_number = compartment_number;
        if (i == 0) {
            printf("Select seat number for Passenger 1: ");
            scanf("%d", &selected_seat_1);
            passengers[i].seat_number = selected_seat_1;
        } else if (i == 1) {
            printf("Select seat number for Passenger 2: ");
            scanf("%d", &selected_seat_2);
            passengers[i].seat_number = selected_seat_2;
        } else {
            printf("Select seat number for Passenger 3: ");
            scanf("%d", &selected_seat_3);
            passengers[i].seat_number = selected_seat_3;
        }
        passengers[i].pnr = generatePNR();
    }
}

