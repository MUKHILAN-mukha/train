#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define RESET   "\033[0m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"

// Train details
typedef struct {
    int serial_number, train_number, platform_number;
    char boarding[50], destination[50], train_name[50], departure_time[10], arrival_time[10], date[11], distance[10]; // Corrected: Changed char to char array
} Train;

// Passenger details
typedef struct {
    int age, seat_number;
    char compartment_class[20], seat_type[20], gender[10], name[50];
} Passenger;

// Display available trains in tabular column
void displayTrains(Train trains[], int num_trains) {
    printf(RED "										AVAILABLE TRAINS:										   \n" RESET);
    printf("---------------------------------------------------------------------------------------------------\n");
    printf(GREEN "|SL.NO. |  DATE     |  BOARDING  |  DESTINATION  | TRAIN NAME | TRAIN NO. | DEPARTURE TIME | ARRIVAL TIME | PLATFORM NO.|"RESET"\n");
    for (int i = 0; i < num_trains; i++) {
        printf(GREEN "|" RESET YELLOW "%-7d" RESET GREEN "|" RESET YELLOW "%-10s" RESET GREEN "|" RESET YELLOW "%-14s" RESET GREEN "|" RESET YELLOW "%-16s" RESET GREEN "|" RESET YELLOW "%-21s" RESET GREEN "|" RESET YELLOW "%-11d" RESET GREEN "|" RESET YELLOW "%-15s" RESET GREEN "|" RESET YELLOW "%-13s" RESET GREEN "|" RESET YELLOW "%-12d" RESET GREEN "|" RESET "\n",trains[i].serial_number, trains[i].date, trains[i].boarding, trains[i].destination,
               trains[i].train_name, trains[i].train_number, trains[i].departure_time, trains[i].arrival_time, trains[i].platform_number);
    }
}

void loadingAnimation() {
    int counter;
    
    printf(YELLOW "PROCESSING YOUR TICKET " RESET);
    
    for (counter = 0; counter < 20; ++counter) {
        printf(".");
        fflush(stdout); // Flush the output buffer
        usleep(100000); // Sleep for 100 milliseconds (0.1 second)
    }
    
    printf(GREEN "\nHERE YOU GO.........\nHAVE A GREAT JOURNEY" RESET);
}

// Display available seats based on compartment class
void displayAvailableSeats(char compartment_class[], int num_seats) {
    printf(RED "AVAILABLE SEATS IN COMPARTMENT:\n" RESET);
    if (strcmp(compartment_class, "FIRST CLASS") == 0) {
        printf(BLUE "CABINS:\n" RESET);
        for (int i = 1; i <= 5; i++) {
            printf("%-5d", i);
            if (i % 5 == 0) // New line after every 5 cabins
                printf("\n");
        }
        printf(BLUE "\n\nCOUPES:\n" RESET);
        for (int i = 6; i <= 8; i++) {
            printf("%-5d", i);
            if (i % 8 == 0)
                printf("\n");
        }
        printf("\n");
    } else if (strcmp(compartment_class, "SLEEPER CLASS") == 0) {
        printf(BLUE "BERTHS:\n" RESET);
        int count = 0;
        for (int i = 1; i <= 81; i++) {
            printf("%-5d", i);
            count++;
            if (count % 4 == 0) // New line after every 4 berths
                printf("\n");
        }
        printf("\n");
    } else if (strcmp(compartment_class, "GENERAL COMPARTMENT") == 0) {
        printf(BLUE "SEATS:\n" RESET);
        for (int i = 1; i <= num_seats; i++) { // Corrected: Use num_seats instead of undeclared variable
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
        {1, 12243, 1, "CHENNAI EGMORE(MS)", "COIMBATORE(CBE)", "Coimbatore Shatabdi Express", "08:00", "10:00", "08/05/2024", "484 KM"},
        {2, 12634, 2, "CHENNAI EGMORE(MS)", "KANYAKUMARI(CAPE)", "Kanyakumari Express", "09:00", "11:30", "08/05/2024", "746 KM"},
        {3, 12653, 3, "CHENNAI EGMORE(MS)", "THIRUCHIRAPALLI(TPJ)", "Tiruchirappalli Rockfort Express", "10:30", "13:00", "09/05/2024", "312 KM"},
        {4, 16344, 2, "CHENNAI EGMORE(MS)", "NAGERCOIL(NJT)", "Nagercoil Guruvayur Express", "10:30", "13:00", "09/05/2024", "726 KM"},
        {5, 12605, 3, "CHENNAI EGMORE(MS)", "KARAIKUDI (KKDI)", "Karaikudi Pallavan Express", "10:30", "13:00", "08/05/2024", "426 KM"},
        {6, 12637, 1, "CHENNAI EGMORE(MS)", "MADURAI (MDU)", "Madurai Pandian Express", "10:30", "13:00", "09/05/2024", "493 KM"},
        {7, 16184, 3, "CHENNAI EGMORE(MS)", "THANJAVUR (TJ)", "Thanjavur Uzhavan Express", "10:30", "13:00", "10/05/2024", "351 KM"},
        {8, 16182, 2, "CHENNAI EGMORE(MS)", "KUMBAKONAM (KMU)", "Kumbakonam Express", "10:30", "13:00", "10/05/2024", "312 KM"}
    };
    int num_trains = sizeof(trains) / sizeof(trains[0]);

    int selected_train;

    // Display available trains in tabular column
    displayTrains(trains, num_trains);

    // User selects a train
    printf("SELECT A TRAIN (1, 2, 3 etc.): ");
    scanf("%d", &selected_train);

    system("cls");

    // Select class of compartment
    printf(RED "SELECT CLASS OF COMPARTMENT (FIRST CLASS, SLEEPER CLASS, GENERAL COMPARTMENT): " RESET);
    char compartment_class[20];
    scanf(GREEN "%s" RESET, compartment_class);

    system("cls");

    // Select compartment
    printf(RED "SELECT A COMPARTMENT (1-3): " RESET);
    int compartment_number;
    scanf(GREEN "%d" RESET, &compartment_number);

    system("cls");

    // Display available seats in the selected compartment
    printf(YELLOW "SELECTED COMPARTMENT: %d\n" RESET, compartment_number);
    displayAvailableSeats(compartment_class, 50); // Assuming 50 seats in each compartment

    system("cls");

    // Display available seats based on selected compartment class
    displayAvailableSeats(compartment_class, 50); // Assuming 50 seats in each compartment
	printf(GREEN "....................CHECK TRAIN DETAILS...................." RESET)
    // Display additional information for passenger details input
    printf(RED "TRAIN NAME		:" RESET YELLOW "%s\n" RESET,trains[selected_train - 1].train_name);
    printf(RED "BOARDING		:" RESET YELLOW "%s\n" RESET,trains[selected_train - 1].boarding);
    printf(RED "DESTINATION		:" RESET YELLOW "%s\n" RESET,trains[selected_train - 1].destination);
    printf(RED "TRAIN NO		:" RESET YELLOW "%d\n" RESET,trains[selected_train - 1].train_number);
    printf(RED "DATE OF BOARDING:" RESET YELLOW "%s\n" RESET,trains[selected_train - 1].date);

    // Passenger details input based on number of tickets
    int num_tickets;
    printf(RED "ENTER NUMBER OF TICKETS: " RESET);
    scanf(GREEN "%d" RESET, &num_tickets);
    
	system("cls");
	
    Passenger passengers[num_tickets];
    for (int i = 0; i < num_tickets; i++) {
        printf(RED "ENTER DETAILS FOR PASSENGER %d:\n" RESET, i + 1);
        printf(BLUE "NAME: " RESET);
        scanf(YELLOW "%s" RESET, passengers[i].name);
        printf(BLUE "AGE: " RESET);
        scanf(YELLOW "%d" RESET, &passengers[i].age);
        printf(BLUE "GENDER: "RESET);
        scanf(YELLOW "%s" RESET, passengers[i].gender);
        strcpy(passengers[i].compartment_class, compartment_class);
        if (strcmp(compartment_class, BLUE "FIRST CLASS" RESET) == 0) {
            if (i % 2 == 0) {
                strcpy(passengers[i].seat_type, YELLOW "CABIN" RESET);
            } else {
                strcpy(passengers[i].seat_type, YELLOW "COUPE" RESET);
            }
        } else if (strcmp(compartment_class, BLUE "SLEEPER CLASS" RESET) == 0) {
            strcpy(passengers[i].seat_type, YELLOW "BERTH" RESET);
        } else {
            strcpy(passengers[i].seat_type, YELLOW "SEATER" RESET); // Default seat type for general compartment
        }
        printf(RED "SELECT SEAT NUMBER: " RESET);
        scanf(YELLOW "%d" RESET, &passengers[i].seat_number);
    }
	
	system("cls");
	
	loadingAnimation();
	
	system("cls");

    // Generate a single PNR for the entire ticket
    int pnr = generatePNR();

	system("cls");
    // Print combined ticket details
    printf("\n=================================================================");
    printf("\n                    	TICKET DETAILS							   ");
    printf("\n=================================================================");
    printf("\n%s ---------------------------------------------------------- %s", trains[selected_train - 1].boarding, trains[selected_train - 1].destination);
    printf("\n(%s)----------------------------(%s)------------------------(%s)", trains[selected_train - 1].departure_time, trains[selected_train - 1].distance), trains[selected_train - 1].arrival_time);
    printf("\nPNR NUMBER			TRAIN NAME/TRAIN NO.			DATE OF BOARDING");
	printf("\n(%d)    		(%s)/			(%s)",pnr,trains[selected_train - 1].train_name,trains[selected_train - 1].date);
    printf("\n				(%d)",trains[selected_train - 1].train_number);
    printf("\n");
    printf("+-----------------------+-----+-------+-----------+------------------+-------------+----------------+\n");
    printf("|    PASSENGER NAME     | AGE | GENDER| COMP.CLASS|   SEAT TYPE      | SEAT NUMBER |  COMPARTMENT   |\n");
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
    printf("| SEAT TYPE       | FARE PER HEAD | NO. OF PASSENGERS | TOTAL FARE |\n");
    printf("-----------------------------------------------------------------\n");
   if (strcmp(compartment_class, "FIRST CLASS") == 0) {
        if (strcmp(passengers[0].seat_type, "CABIN") == 0) {
            printf("| CABIN           | Rs. 1671      | x %d               | Rs. %.2f |\n", num_tickets, 1671.0 * num_tickets);
            total_fare += 1671 * num_tickets;
        } else if (strcmp(passengers[0].seat_type, "COUPE") == 0) {
            printf("| COUPE           | Rs. 836       | x %d               | Rs. %.2f |\n", num_tickets, 836.0 * num_tickets);
            total_fare += 836 * num_tickets;
        }
    } else if (strcmp(compartment_class, "SLEEPER CLASS") == 0) {
        printf("| SLEEPER BERTH   | Rs. 447       | x %d               | Rs. %.2f     |\n", num_tickets, 447.0 * num_tickets);
        total_fare += 447 * num_tickets;
    } else if (strcmp(compartment_class, "GENERAL COMPARTMENT") == 0) {
        printf("| SEATER          | Rs. 438       | x %d               | Rs. %.2f     |\n", num_tickets, 438.0 * num_tickets);
        total_fare += 438 * num_tickets;
    }
    printf("-----------------------------------------------------------------\n");
    printf("| TOTAL FARE      |                   |                    | Rs. %.2f     |\n", total_fare);
    printf("-----------------------------------------------------------------\n");

    return 0;
}