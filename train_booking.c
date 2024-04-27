#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//train details
typedef struct {
    int serial_number,train_number,platform_number;
    char boarding[50],destination[50],train_name[50],departure_time[10],arrival_time[10],date[11],distance; 
} Train;

//passenger details
typedef struct {
    int age,seat_number;
    char compartment_class[20],seat_type[20],gender[10],name[50]
} Passenger;

//display available trains in tabular coloumn
void displayTrains(Train trains[], int num_trains) {
    printf("Available Trains:\n");
    printf("---------------------------------------------------------------------------------------------------")
    printf("|SL.NO.|  DATE   |  BOARDING   |  DESTINATION  | TRAIN NAME | TRAIN NO. | DEPARTURE\n TIME |  ARRIVAL\n TIME  | PLATFORM NO.|\n");
    for (int i = 0; i < num_trains; i++) {
        printf("|%-7d|%-10s|%-14s|%-16s|%-21s|%-14d|%-9s|%-8s|%-8d|\n",trains[i].serial_number, trains[i].date,trains[i].boarding,trains[i].destination,
               trains[i].train_name, trains[i].train_number, trains[i].departure_time, trains[i].arrival_time, trains[i].platform_number);
    }
}

void displayAvailableSeats(char compartment_class[], int num_seats) {
    printf("AVAILABLE SEATS IN COMPARTMENT:\n");
    if (strcmp(compartment_class, "FIRST CLASS") == 0) {
        printf("CABINS:\n");
        for (int i = 1; i <= 5; i++) {
            printf("%-5d", i);
            if (i % 5 == 0) //newline after every 5 cabins
                printf("\n");
        }
        printf("\n\nCOUPES:\n");
        for (int i = 6; i <= 8; i++) {
            printf("%-5d", i);
            if (i % 8 == 0) 
                printf("\n");
        }
        printf("\n");
    } else if (strcmp(compartment_class, "SLEEPER CLASS") == 0) {
        printf("BERTHS:\n");
        int count = 0;
        for (int i = 1; i <= 81; i++) {
            printf("%-5d", i);
            count++;
            if (count % 4 == 0) //newline after every 4 berths
                printf("\n");
        }
        printf("\n");
    } else if (strcmp(compartment_class, "GENERAL COMPARTMENT") == 0) {
        printf("SEATS:\n");
        for (int i = 1; i <= num_seats; i++) {
            printf("%-5d", i);
            if (i % 10 == 0) //newline after every 10 seats
                printf("\n");
        }
        printf("\n");
    }
}
//generates a random PNR number
int generatePNR() {
    srand(time(NULL));
    return rand() % 90000000 + 10000000; // 8-digit PNR
}

int main() {
    Train trains[] = {
        {1, "MS", "CBE", "Coimbatore Shatabdi Express", 12243, "08:00", "10:00", "08/05/2024", 1, "484 KM"},
        {2, "MS", "CAPE", "Kanyakumari Express", 12634, "09:00", "11:30", "08/05/2024", 2, "746 KM"},
        {3, "MS", "TPJ", "Tiruchirappalli Rockfort Express", 12653, "10:30", "13:00", "09/05/2024", 3, "312 KM"}
        {4, "MS", "NJT", "Nagercoil Guruvayur Express", 16344, "10:30", "13:00", "09/05/2024", 2, "726 KM"}
        {5, "MS", "KKDI", "Karaikudi Pallavan Express", 12605, "10:30", "13:00", "08/05/2024", 3, "426 KM"}
        {6, "MS", "MDU", "Madurai Pandian Express", 12637, "10:30", "13:00", "09/05/2024", 1, "493 KM"}
        {7, "MS", "TJ", "Thanjavur Uzhavan Express", 16184, "10:30", "13:00", "10/05/2024", 3, "351 KM"}
        {8, "MS", "KMU", "Kumbakonam Express", "MS to KMU", 16182, "10:30", "13:00", "10/05/2024", 2, "312 KM"}
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
    printf("Select compartment (1-3): ");
    int compartment_number;
    scanf("%d", &compartment_number);

    system("clear");

    //display available seats in the selected compartment in tabular coloumn
    printf("Selected Compartment: %d\n", compartment_number);
    displayAvailableSeats(50); //50 seats in each compartment

    system("clear");

    displayAvailableSeats(compartment_class, num_seats);

    // display additional information for passenger details input
   printf("TRAIN NAME: %s\n", trains[selected_train - 1].train_name);
    printf("BOARDING: %s\n", trains[selected_train - 1].boarding);
    printf("DESTINATION: %s\n", trains[selected_train - 1].destination);
    printf("TRAIN NO: %d\n", trains[selected_train - 1].train_number);
    printf("DATE OF BOARDING: %s\n", trains[selected_train - 1].date);

    //passenger details input based on number of tickets
    int num_tickets;
    printf("Enter number of tickets: ");
    scanf("%d", &num_tickets);

    Passenger passengers[num_tickets];
    for (int i = 0; i < num_tickets; i++) {
        printf("ENTER DETAILS FOR PASSENGER %d:\n", i + 1);
        printf("NAME: ");
        scanf("%s", passengers[i].name);
        printf("AGE: ");
        scanf("%d", &passengers[i].age);
        printf("GENDER: ");
        scanf("%s", passengers[i].gender);
        strcpy(passengers[i].compartment_class, compartment_class);
        if (strcmp(compartment_class, "FIRST CLASS") == 0 || strcmp(compartment_class, "SLEEPER CLASS") == 0) {
            printf("SELECT SEAT TYPE (CABIN/COUPE): ");
            scanf("%s", passengers[i].seat_type);
            printf("SELECT SEAT NUMBER: ");
            scanf("%d", &passengers[i].seat_number);
        } else {
            strcpy(passengers[i].seat_type, "SEATER"); // Default seat type for general compartment
            printf("SELECT SEAT NUMBER: ");
            scanf("%d", &passengers[i].seat_number);
        }
    }
// Generate a single PNR for the entire ticket
    int pnr = generatePNR()

// Print combined ticket details
    printf("\n=================================================================\n");
    printf("                    TICKET DETAILS\n");
    printf("=================================================================\n");
    printf("%s",trains[selected_train - 1].boarding"-----------------------------------------------%s",trains[selected_train - 1].destination"\n);
    printf("(%s)",trains[selected_train - 1].departure_time"                                        (%s)",trains[selected_train - 1].arrival_time"\n);
    printf("TRAIN NAME: %s\n", trains[selected_train - 1].train_name);
    printf("TRAIN NO: %d\n", trains[selected_train - 1].train_number);
    printf("DATE OF BOARDING: %s\n", trains[selected_train - 1].date);
    printf("\n");
    printf("+-----------------------+-----+-------+-----------+------------------+-------------+----------------+\n");
    printf("|     PASSENGER NAME     | AGE | GENDER| COMP.CLASS|   SEAT TYPE      | SEAT NUMBER |  COMPARTMENT   |\n");
    printf("+-----------------------+-----+-------+-----------+------------------+-------------+----------------+\n");
    for (int i = 0; i < num_tickets; i++) {
        printf("|   %-20s | %-3d | %-5s | %-9s | %-16s | %-11d | %-14d |\n", passengers[i].name, passengers[i].age, passengers[i].gender, passengers[i].compartment_class,
               passengers[i].seat_type, passengers[i].seat_number, compartment_number);
    }
    printf("+-----------------------+-----+-------+-----------+------------------+-------------+----------------+\n");
    printf("\n");
    
// Calculate and display total fare
    float total_fare = 0.0;
    printf("=================================================================\n");
    printf("                    TOTAL FARE CALCULATION\n");
    printf("=================================================================\n");
    printf("| SEAT TYPE       | FARE PER HEAD |\n");
    printf("-----------------------------------------------------------------\n");
    if (strcmp(compartment_class, "FIRST CLASS") == 0) {
        printf("| CABIN           | Rs. 1671      |\n");
        printf("| COUPE           | Rs. 836       |\n");
        total_fare += (1671 + 836) * num_tickets;
    } else if (strcmp(compartment_class, "SLEEPER CLASS") == 0) {
        printf("| SLEEPER BERTH   | Rs. 298       |\n");
        total_fare += 298 * num_tickets;
    } else if (strcmp(compartment_class, "GENERAL COMPARTMENT") == 0) {
        printf("| SEATER          | Rs. 265       |\n");
        total_fare += 265 * num_tickets;
    }
    printf("-----------------------------------------------------------------\n");
    printf("| TOTAL FARE      | Rs. %.2f       |\n", total_fare);
    printf("-----------------------------------------------------------------\n");

    return 0;
}
