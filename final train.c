#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Train details
typedef struct {
    int serial_number, train_number, platform_number;
    char boarding[50], destination[50], train_name[50], departure_time[10], arrival_time[10], date[11], distance; 
} Train;

// Passenger details
typedef struct {
    int age, seat_number;
    char compartment_class[20], seat_type[20], gender[10], name[50];
} Passenger;

// Display available trains in tabular column
void displayTrains(Train trains[], int num_trains) {
    printf("Available Trains:\n");
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("|SL.NO.|  DATE   |  BOARDING   |  DESTINATION  | TRAIN NAME | TRAIN NO. | DEPARTURE TIME | ARRIVAL TIME | PLATFORM NO.|\n");
    for (int i = 0; i < num_trains; i++) {
        printf("|%-7d|%-10s|%-14s|%-16s|%-21s|%-11d|%-15s|%-13s|%-12d|\n", trains[i].serial_number, trains[i].date, trains[i].boarding, trains[i].destination,
               trains[i].train_name, trains[i].train_number, trains[i].departure_time, trains[i].arrival_time, trains[i].platform_number);
    }
}

// Display available seats based on compartment class
void displayAvailableSeats(char compartment_class[], int num_seats) {
    printf("AVAILABLE SEATS IN COMPARTMENT:\n");
    if (strcmp(compartment_class, "FIRST CLASS") == 0) {
        printf("CABINS:\n");
        for (int i = 1; i <= 5; i++) {
            printf("%-5d", i);
            if (i % 5 == 0) // New line after every 5 cabins
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
            if (count % 4 == 0) // New line after every 4 berths
                printf("\n");
        }
        printf("\n");
    } else if (strcmp(compartment_class, "GENERAL COMPARTMENT") == 0) {
        printf("SEATS:\n");
        for (int i = 1; i <= num_seats; i++) {
            printf("%-5d", i);
            if (i % 10 == 0) // New line after every 10 seats
                printf("\n");
        }
        printf("\n");
    }
}

// Generate a random PNR number
int generatePNR() {
    srand(time(NULL));
    return rand() % 90000000 + 10000000; // 8-digit PNR
}

int main() {
    Train trains[] = {
        {1, 12243, 1, "MS", "CBE", "Coimbatore Shatabdi Express", "08:00", "10:00", "08/05/2024", "484 KM"},
        {2, 12634, 2, "MS", "CAPE", "Kanyakumari Express", "09:00", "11:30", "08/05/2024", "746 KM"},
        {3, 12653, 3, "MS", "TPJ", "Tiruchirappalli Rockfort Express", "10:30", "13:00", "09/05/2024", "312 KM"},
        {4, 16344, 2, "MS", "NJT", "Nagercoil Guruvayur Express", "10:30", "13:00", "09/05/2024", "726 KM"},
        {5, 12605, 3, "MS", "KKDI", "Karaikudi Pallavan Express", "10:30", "13:00", "08/05/2024", "426 KM"},
        {6, 12637, 1, "MS", "MDU", "Madurai Pandian Express", "10:30", "13:00", "09/05/2024", "493 KM"},
        {7, 16184, 3, "MS", "TJ", "Thanjavur Uzhavan Express", "10:30", "13:00", "10/05/2024", "351 KM"},
        {8, 16182, 2, "MS", "KMU", "Kumbakonam Express", "10:30", "13:00", "10/05/2024", "312 KM"}
    };
    int num_trains = sizeof(trains) / sizeof(trains[0]);

    int selected_train;

    // Display available trains in tabular column
    displayTrains(trains, num_trains);

    // User selects a train
    printf("Select a train (1, 2, 3 etc.): ");
    scanf("%d", &selected_train);

    system("clear");

    // Select class of compartment
    printf("Select class of compartment (First Class, Sleeper Class, General Compartment): ");
    char compartment_class[20];
    scanf("%s", compartment_class);

    system("clear");

    // Select compartment
    printf("Select compartment (1-3): ");
    int compartment_number;
    scanf("%d", &compartment_number);

    system("clear");

    // Display available seats in the selected compartment
    printf("Selected Compartment: %d\n", compartment_number);
    displayAvailableSeats(compartment_class, 50); // Assuming 50 seats in each compartment

    system("clear");

    // Display available seats based on selected compartment class
    displayAvailableSeats(compartment_class, num_seats);

    // Display additional information for passenger details input
    printf("TRAIN NAME: %s\n", trains[selected_train - 1].train_name);
    printf("BOARDING: %s\n", trains[selected_train - 1].boarding);
    printf("DESTINATION: %s\n", trains[selected_train - 1].destination);
    printf("TRAIN NO: %d\n", trains[selected_train - 1].train_number);
    printf("DATE OF BOARDING: %s\n", trains[selected_train - 1].date);

    // Passenger details input based on number of tickets
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
    int pnr = generatePNR();

    // Print combined ticket details
    printf("\n=================================================================\n");
    printf("                    TICKET DETAILS\n");
    printf("=================================================================\n");
    printf("%s - %s\n", trains[selected_train - 1].boarding, trains[selected_train - 1].destination);
    printf("(%s - %s)\n", trains[selected_train - 1].departure_time, trains[selected_train - 1].arrival_time);
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
        if (strcmp(passengers[0].seat_type, "CABIN") == 0) {
            printf("| CABIN           | Rs. 1671      |\n");
            total_fare += 1671 * num_tickets;
        } else if (strcmp(passengers[0].seat_type, "COUPE") == 0) {
            printf("| COUPE           | Rs. 836       |\n");
            total_fare += 836 * num_tickets;
        }
    } else if (strcmp(compartment_class, "SLEEPER CLASS") == 0) {
        printf("| SLEEPER BERTH   | Rs. 447       |\n");
        total_fare += 447 * num_tickets;
    } else if (strcmp(compartment_class, "GENERAL COMPARTMENT") == 0) {
        printf("| SEATER          | Rs. 438       |\n");
        total_fare += 438 * num_tickets;
    }
    printf("-----------------------------------------------------------------\n");
    printf("| TOTAL FARE      | Rs. %.2f       |\n", total_fare);
    printf("-----------------------------------------------------------------\n");

    return 0;
}

