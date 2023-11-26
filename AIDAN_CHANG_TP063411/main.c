#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// AIDAN_CHANG_TP063411

// STRUCTS USED IN PROGRAM

typedef struct staff { // declaring struct for staff
    char staff_username[50];
    char staff_password[20];
    char staff_type[50];
    int staff_ID;
    int annualLeave;
    int compLeave;
    int emergLeave;
    int matLeave;
    int medLeave;
}staff;

typedef struct approver { // declaring struct for approver
    char approver_username[50];
    char approver_password[20];
    int app_ID;
}approver;

typedef struct leaves{ // declaring struct for leaves
    char typeLeave[50];
    char statusLeave[20];
    int leaveStaff_ID;
    int day;
    int month;
    int year;
    int duration;
}leaves;

// REGISTER FUNCTIONS

int incrementOFStaffID(){
    int StaffID = 100;
    staff st;

    FILE *fptr_staff = fopen("staffDetails.txt", "r");
    if (fptr_staff == NULL){
        printf("File not found!\n");
        return;
    }
    while (fscanf(fptr_staff, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d,", &st.staff_ID, st.staff_username, st.staff_password, st.staff_type, &st.annualLeave, &st.compLeave, &st.emergLeave, &st.matLeave, &st.medLeave) != EOF){
        StaffID = st.staff_ID;
    }
    fclose(fptr_staff);
    return StaffID + 1;
}

int incrementOFApproverID(){
    int ApproverID = 200;
    approver app;

    FILE *fptr_approver = fopen("approverDetails.txt", "r");
    if (fptr_approver == NULL){
        printf("File not found!\n");
        return;
    }
    approver a;
    while (fscanf(fptr_approver, "%d, %[^,], %s\n", &app.app_ID, app.approver_username, app.approver_password) != EOF){
        ApproverID = app.app_ID;
    }
    fclose(fptr_approver);
    return ApproverID + 1;
}

void registerStaff() {
    char dummy_password[50];
    int type_staffCh;
    staff st;

    FILE *fptr_staff = fopen("staffDetails.txt", "a+");
    if (fptr_staff == NULL){
        printf("File not found!\n");
        return;
    }

    fflush(stdin);
    printf("Which of the following staff are you?\n");
    printf("1. Academic\n");
    printf("2. Management\n");
    printf("3. Technical\n");
    printf("4. Administrative\n");
    scanf("%d", &type_staffCh);
    if (type_staffCh == 1){
        strcpy(st.staff_type, "Academic");
    }else if (type_staffCh == 2){
        strcpy(st.staff_type, "Management");
    }else if (type_staffCh == 3){
        strcpy(st.staff_type, "Technical");
    }else if (type_staffCh == 4){
        strcpy(st.staff_type, "Administrative");
    }else{
        printf("Invalid option.\n");
        return;
    }

    fflush(stdin);
    printf("Enter a username: \n");
    scanf("%[^\n]", st.staff_username);

    // checking if the username already exists
    rewind(fptr_staff);
    staff currSt; // redeclare staff struct to compare
    while (fscanf(fptr_staff, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d\n", &currSt.staff_ID, currSt.staff_username, currSt.staff_password, currSt.staff_type, &currSt.annualLeave, &currSt.compLeave, &currSt.emergLeave, &currSt.matLeave, &currSt.medLeave) == 9) {
        if (strcmp(currSt.staff_username, st.staff_username) == 0) {
            printf("Username already exists, try a different one.\n");
            return;
        }
    }

    while (1){
        fflush(stdin);
        printf("Enter a password: \n");
        scanf("%s", dummy_password);
        if (strlen(dummy_password) < 8 || strlen(dummy_password) > 20 || strchr(dummy_password, ' ') != NULL) { // strchr function in this case checks if there are spaces
            printf("Invalid password, must be between 8 and 20 characters and cannot contain spaces.\n");
            continue;
        }else{
            fflush(stdin);
            printf("Confirm your password: \n");
            scanf("%s", st.staff_password);

            if (!strcmp(st.staff_password, dummy_password)){
                st.staff_ID = incrementOFStaffID(); // calls incrementOFStaffID function to increment staff ID by 1 every new staff
                st.annualLeave = 16; // declare these values to be stored into struct bc cannot store values in struct, also can use #DEFINE for same results
                st.compLeave = 7;
                st.emergLeave = 3;
                st.matLeave = 98;
                st.medLeave = 22;
                fprintf(fptr_staff, "%d, %s, %s, %s, %d, %d, %d, %d, %d\n", st.staff_ID, st.staff_username, st.staff_password, st.staff_type, st.annualLeave, st.compLeave, st.emergLeave, st.matLeave, st.medLeave);
                rewind(fptr_staff);
                printf("Staff registered successfully with ID %d.\n", st.staff_ID);
                fclose(fptr_staff);
                break;
            }else{
                printf("Passwords do not match!\n");
                continue;
            }
        }
    }
    menu();
}

void registerApprover() {
    char dummy_password[50];
    approver app;

    FILE *fptr_approver = fopen("approverDetails.txt", "a+");
    if (fptr_approver == NULL){
        printf("File not found!\n");
        return;
    }

    fflush(stdin);
    printf("Enter a username: \n");
    scanf("%[^\n]", app.approver_username);

    // Check if the username already exists
    rewind(fptr_approver);
    approver currApp;
    while (fscanf(fptr_approver, "%d, %[^,], %s\n", &currApp.app_ID, currApp.approver_username, currApp.approver_password) == 3) {
        if (strcmp(currApp.approver_username, app.approver_username) == 0) {
            printf("Username already exists, try a different one.\n");
            return;
        }
    }

    while (1){
        fflush(stdin);
        printf("Enter a password: \n");
        scanf("%s", dummy_password);
        if (strlen(dummy_password) < 8 || strlen(dummy_password) > 20 || strchr(dummy_password, ' ') != NULL) {
            printf("Invalid password, must be between 8 and 20 characters and cannot contain spaces.\n");
            continue;
        }else{
            fflush(stdin);
            printf("Confirm your password: \n");
            scanf("%s", app.approver_password);
            if (!strcmp(app.approver_password, dummy_password)){
                app.app_ID = incrementOFApproverID();
                fprintf(fptr_approver, "%d, %s, %s\n", app.app_ID, app.approver_username, app.approver_password);
                rewind(fptr_approver);
                printf("Approver registered successfully with ID %d.\n", app.app_ID);
                fclose(fptr_approver);
                break;
            }else{
                printf("Passwords do not match!\n");
                continue;
            }
        }
    }
    menu();
}

// LOGIN FUNCTIONS

int staffLogin() {
    char s_username[50], s_password[20];
    int tries = 3, s_id = 0;

    staff st;

    FILE *fptr_staff = fopen("staffDetails.txt", "r");
    if (fptr_staff == NULL){
        printf("File not found!\n");
        return;
    }

    while (tries > 0) {
        fflush(stdin);
        printf("Enter your Staff ID: \n");
        scanf("%d", &s_id);

        fflush(stdin);
        printf("Enter username: \n");
        scanf("%[^\n]s", s_username); //[^\n]s means read all characters/input until new line (when u press enter)

        fflush(stdin);
        printf("Enter password: \n");
        scanf("%s", s_password);

        rewind(fptr_staff);
        while (fscanf(fptr_staff, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d", &st.staff_ID, st.staff_username, st.staff_password, st.staff_type, &st.annualLeave, &st.compLeave, &st.emergLeave, &st.matLeave, &st.medLeave)!= EOF) {
            if ((s_id == st.staff_ID) && (strcmp(s_username, st.staff_username) == 0) && (strcmp(s_password, st.staff_password) == 0)) {
                printf("Login successful! Redirecting to the staff homepage...\n");
                int *s_id_ptr = &st.staff_ID; // declare staff ID as pointer to be used in other functions, can also declare as global var but i didn't in case assignment doesn't accept and bc im not good with it
                fclose(fptr_staff);
                staffHomepage(s_id_ptr);
            }
        }
        printf("Login failed. %d attempts left.\n", --tries); // if false credentials, no. of tries gets subtracted by one (tries--)
    }
    printf("No attempts left. Returning to main menu...\n");
    fclose(fptr_staff);
    return 0;
}

int approverLogin() {
    char a_username[50], a_password[20];
    int tries = 3, a_id;
    approver app;

    FILE *fptr_approver = fopen("approverDetails.txt", "r");
    if (fptr_approver == NULL){
        printf("File not found!\n");
        return;
    }

    while (tries > 0) {
        fflush(stdin);
        printf("Enter your Approver ID: \n");
        scanf("%d", &a_id);

        fflush(stdin);
        printf("Enter username: \n");
        scanf("%[^\n]s", a_username);

        fflush(stdin);
        printf("Enter password: \n");
        scanf("%s", a_password);

        rewind(fptr_approver);
        while (fscanf(fptr_approver, "%d, %[^,], %s\n", &app.app_ID, app.approver_username, app.approver_password) == 3) {
        if ((a_id == app.app_ID) && strcmp(a_username, app.approver_username) == 0 && strcmp(a_password, app.approver_password) == 0) {
            printf("Login successful! Redirecting to the approver homepage...\n");
            fclose(fptr_approver);
            approverHomepage();
            break;
            }
        }
        printf("Login failed. %d attempts left.\n", --tries);
    }
    printf("No attempts left. Returning to main menu...\n");
    fclose(fptr_approver);
    return 0;
}

int adminLogin() {
    char adm_username[50], adm_password[20];
    int tries = 3;

    while (tries > 0) {
        fflush(stdin);
        printf("Enter username: \n");
        scanf("%[^\n]s", adm_username);

        fflush(stdin);
        printf("Enter password: \n");
        scanf("%s", adm_password);

        if (!strcmp(adm_username, "admin") && !strcmp(adm_password, "password")) {
            printf("Login successful! Redirecting to the Admin homepage...\n");
            adminHomepage();
          }else{
            printf("Login failed. %d attempts left.\n", --tries);
            }
        }
    printf("No attempts left. Returning to main menu...\n");
    return 0;
}

void leaveCalander(int *day, int *month, int *year){
    time_t now = time(NULL); // get current time in seconds
    struct tm *local = localtime(&now); // convert the time to a struct tm representing the local time

    while (1){
        fflush(stdin);
        printf("\nPlease enter your starting day in DD format: \n");
        scanf("%d", day);
        fflush(stdin);
        printf("Please enter your starting month in MM format: \n");
        scanf("%d", month);
        fflush(stdin);
        printf("Please enter your starting year in YYYY format: \n");
        scanf("%d", year);

        // check if the entered date is in the future
        if (*year > local->tm_year+1900 || (*year == local->tm_year+1900 && (*month > local->tm_mon+1 || (*month == local->tm_mon+1 && *day > local->tm_mday)))) {
            if (*year >= 2023 && *year <= 2025){
                if (1 <= *month || *month <= 12){
                    if ((1 <= *day && *day <= 31) && (*month == 1 || *month == 3 || *month == 5 || *month == 7 || *month == 8 || *month == 10 || *month == 12 )){
                        printf("Valid date!\n");
                        break;
                    }else if ((1 <= *day && *day <= 30) && (*month == 4 || *month == 6 || *month == 9 || *month == 11)){
                        printf("Valid date!\n");
                        break;
                    }else if ((1 <= *day && *day <= 28) && (*month == 2)){
                        printf("Valid date!\n");
                        break;
                    }else if ((1 <= *day && *day <= 29) && (*year%4 == 0)){
                        printf("Valid date!\n"); // leap year
                        break;
                    }else{
                        printf("Invalid date!\n");
                        continue;
                    }
                }else{
                    printf("Invalid date!\n");
                    continue;
                }
            }else{
                printf("Invalid date!\n");
                continue;
            }
        } else {
            printf("Invalid date! Please enter a future date.\n");
            continue;
        }
    }
}

// STAFF HOMEPAGE FUNCTIONS

void applyLeave(int *s_id_ptr){
    int applyLeaveChoice;
    int day = 0;
    int month = 0;
    int year = 0;

    char buff[10];

    staff st;
    leaves lv;

    while (1) {
    printf("\n-------------------------------------------------\n");
    printf("***WELCOME TO THE APU LEAVE APPLICATION SYSTEM***\n");
    printf("-------------------------------------------------\n");
    printf("1. Annual Leave\n");
    printf("2. Compassionate Leave\n");
    printf("3. Emergency Leave\n");
    printf("4. Maternity Leave\n");
    printf("5. Medical Leave\n");
    printf("6. Back\n");
    printf("Please enter your choice: \n");
    fflush(stdin);
    scanf("%s", buff);
    applyLeaveChoice = atoi(buff);

    switch (applyLeaveChoice) {
        case 1: ;
            leaveCalander(&day, &month, &year);
            FILE *fptr_leave  = fopen("leaveDetails.txt", "r");
            if (fptr_leave == NULL){
                printf("File not found!\n");
                staffHomepage(s_id_ptr);
            }
            while (fscanf(fptr_leave, "%d, %[^,], %[^,], %d-%d-%d, %d days\n", &lv.leaveStaff_ID, lv.typeLeave, lv.statusLeave, &lv.day, &lv.month, &lv.year, &lv.duration) != EOF){
                if (lv.leaveStaff_ID == *s_id_ptr && lv.day == day && lv.month == month && lv.year == year && (strcmp(lv.statusLeave, "Canceled"))){
                    printf("Sorry, this is a duplicate leave.\n");
                    fclose(fptr_leave);
                    staffHomepage(s_id_ptr);
                }
            }
            fclose(fptr_leave);
            fflush(stdin);
            printf("\nPlease enter the amount of days you would like to take leave for: \n");
            scanf("%d", &lv.duration);
            FILE *fptr_staff = fopen("staffDetails.txt", "r");
            if (fptr_staff == NULL){
                printf("File not found!\n");
                return;
            }
            FILE *fptr_temp = fopen("temp.txt", "w+");
            if (fptr_temp == NULL){
                printf("File not found!\n");
                return;
            }
            while (fscanf(fptr_staff, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d", &st.staff_ID, st.staff_username, st.staff_password, st.staff_type, &st.annualLeave, &st.compLeave, &st.emergLeave, &st.matLeave, &st.medLeave)!= EOF){
                if (*s_id_ptr == st.staff_ID){ // get value of staff ID to edit that particular staff ID's info in struct + add the staff ID as the ID in leave struct
                    if (st.annualLeave >= lv.duration){
                        st.annualLeave -= lv.duration;
                        lv.leaveStaff_ID = st.staff_ID;
                        strcpy(lv.typeLeave, "Annual Leave");
                        strcpy(lv.statusLeave, "Pending");
                        lv.day = day;
                        lv.month = month;
                        lv.year = year;
                        FILE *fptr_leave = fopen("leaveDetails.txt", "a+");
                        if (fptr_leave == NULL){
                            printf("File not found!\n");
                            return;
                        }
                        fprintf(fptr_leave, "%d, %s, %s, %d-%d-%d, %d days\n", lv.leaveStaff_ID, lv.typeLeave, lv.statusLeave, lv.day, lv.month, lv.year, lv.duration);
                        fclose(fptr_leave);
                        printf("Leave applied!\n");
                    }else{
                        printf("Leave duration exceeds balance!\n");
                        fclose(fptr_leave);
                        fclose(fptr_staff);
                        fclose(fptr_temp);
                        remove("temp.txt");
                        staffHomepage(s_id_ptr);
                    }
                }
                fprintf(fptr_temp, "%d, %s, %s, %s, %d, %d, %d, %d, %d\n", st.staff_ID, st.staff_username, st.staff_password, st.staff_type, st.annualLeave, st.compLeave, st.emergLeave, st.matLeave, st.medLeave);
            }
            fclose(fptr_staff);
            fclose(fptr_temp);
            remove("staffDetails.txt");
            rename("temp.txt", "staffDetails.txt"); // last 5 lines means temp file will write the latest info, staffDetails file will get deleted and temp file will get renamed as the new staffDetails file
            break;
        case 2:
            leaveCalander(&day, &month, &year);
            FILE *fptr_leave2  = fopen("leaveDetails.txt", "r");
            if (fptr_leave2 == NULL){
                printf("File not found!\n");
                staffHomepage(s_id_ptr);
            }
            rewind(fptr_leave2);
            while (fscanf(fptr_leave2, "%d, %[^,], %[^,], %d-%d-%d, %d days\n", &lv.leaveStaff_ID, lv.typeLeave, lv.statusLeave, &lv.day, &lv.month, &lv.year, &lv.duration) != EOF){
                if (lv.leaveStaff_ID == *s_id_ptr && lv.day == day && lv.month == month && lv.year == year && (strcmp(lv.statusLeave, "Canceled"))){
                    printf("Sorry, this is a duplicate leave.\n");
                    fclose(fptr_leave2);
                    staffHomepage(s_id_ptr);
                }
            }
            fclose(fptr_leave2);
            fflush(stdin);
            printf("Please enter the amount of days you would like to take leave for: \n");
            scanf("%d", &lv.duration);
            FILE *fptr_staff2 = fopen("staffDetails.txt", "r");
            if (fptr_staff2 == NULL){
                printf("File not found!\n");
                return;
            }
            FILE *fptr_temp2 = fopen("temp.txt", "w+");
            if (fptr_temp2 == NULL){
                printf("File not found!\n");
                return;
            }
            while (fscanf(fptr_staff2, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d", &st.staff_ID, st.staff_username, st.staff_password, st.staff_type, &st.annualLeave, &st.compLeave, &st.emergLeave, &st.matLeave, &st.medLeave)!= EOF){
                if (*s_id_ptr == st.staff_ID){
                    if (st.compLeave >= lv.duration){
                        st.compLeave -= lv.duration;
                        lv.leaveStaff_ID = st.staff_ID;
                        strcpy(lv.typeLeave, "Compassionate Leave");
                        strcpy(lv.statusLeave, "Pending");
                        lv.day = day;
                        lv.month = month;
                        lv.year = year;
                        FILE *fptr_leave2 = fopen("leaveDetails.txt", "a+");
                        if (fptr_leave2 == NULL){
                            printf("File not found!\n");
                            return;
                        }
                        fprintf(fptr_leave2, "%d, %s, %s, %d-%d-%d, %d days\n", lv.leaveStaff_ID, lv.typeLeave, lv.statusLeave, lv.day, lv.month, lv.year, lv.duration);
                        fclose(fptr_leave2);
                        printf("Leave applied!\n");
                    }else{
                        printf("Leave duration exceeds balance!\n");
                        fclose(fptr_leave2);
                        fclose(fptr_staff2);
                        fclose(fptr_temp2);
                        remove("temp.txt");
                        staffHomepage(s_id_ptr);
                    }
                }
                fprintf(fptr_temp2, "%d, %s, %s, %s, %d, %d, %d, %d, %d\n", st.staff_ID, st.staff_username, st.staff_password, st.staff_type, st.annualLeave, st.compLeave, st.emergLeave, st.matLeave, st.medLeave);
            }
            fclose(fptr_staff2);
            fclose(fptr_temp2);
            remove("staffDetails.txt");
            rename("temp.txt", "staffDetails.txt");
        break;
        case 3:
            leaveCalander(&day, &month, &year);
            FILE *fptr_leave3  = fopen("leaveDetails.txt", "r");
            if (fptr_leave3 == NULL){
                printf("File not found!\n");
                staffHomepage(s_id_ptr);
            }
            rewind(fptr_leave3);
            while (fscanf(fptr_leave3, "%d, %[^,], %[^,], %d-%d-%d, %d days\n", &lv.leaveStaff_ID, lv.typeLeave, lv.statusLeave, &lv.day, &lv.month, &lv.year, &lv.duration) != EOF){
                if (lv.leaveStaff_ID == *s_id_ptr && lv.day == day && lv.month == month && lv.year == year && (strcmp(lv.statusLeave, "Canceled"))){
                    printf("Sorry, this is a duplicate leave.\n");
                    fclose(fptr_leave3);
                    staffHomepage(s_id_ptr);
                }
            }
            fclose(fptr_leave3);
            fflush(stdin);
            printf("Please enter the amount of days you would like to take leave for: \n");
            scanf("%d", &lv.duration);
            FILE *fptr_staff3 = fopen("staffDetails.txt", "r");
            if (fptr_staff3 == NULL){
                printf("File not found!\n");
                return;
            }
            FILE *fptr_temp3 = fopen("temp.txt", "w+");
            if (fptr_temp3 == NULL){
                printf("File not found!\n");
                return;
            }
            while (fscanf(fptr_staff3, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d", &st.staff_ID, st.staff_username, st.staff_password, st.staff_type, &st.annualLeave, &st.compLeave, &st.emergLeave, &st.matLeave, &st.medLeave)!= EOF){
                if (*s_id_ptr == st.staff_ID){
                    if (st.emergLeave >= lv.duration){
                        st.emergLeave -= lv.duration;
                        lv.leaveStaff_ID = st.staff_ID;
                        strcpy(lv.typeLeave, "Emergency Leave");
                        strcpy(lv.statusLeave, "Pending");
                        lv.day = day;
                        lv.month = month;
                        lv.year = year;
                        FILE *fptr_leave3 = fopen("leaveDetails.txt", "a+");
                        if (fptr_leave3 == NULL){
                            printf("File not found!\n");
                            return;
                        }
                        fprintf(fptr_leave3, "%d, %s, %s, %d-%d-%d, %d days\n", lv.leaveStaff_ID, lv.typeLeave, lv.statusLeave, lv.day, lv.month, lv.year, lv.duration);
                        fclose(fptr_leave3);
                        printf("Leave applied!\n");
                    }else{
                        printf("Leave duration exceeds balance!\n");
                        fclose(fptr_leave3);
                        fclose(fptr_staff3);
                        fclose(fptr_temp3);
                        remove("temp.txt");
                        staffHomepage(s_id_ptr);
                    }
                }
                fprintf(fptr_temp3, "%d, %s, %s, %s, %d, %d, %d, %d, %d\n", st.staff_ID, st.staff_username, st.staff_password, st.staff_type, st.annualLeave, st.compLeave, st.emergLeave, st.matLeave, st.medLeave);
            }
            fclose(fptr_staff3);
            fclose(fptr_temp3);
            remove("staffDetails.txt");
            rename("temp.txt", "staffDetails.txt");
        break;
        case 4:
            leaveCalander(&day, &month, &year);
            FILE *fptr_leave4  = fopen("leaveDetails.txt", "r");
            if (fptr_leave4 == NULL){
                printf("File not found!\n");
                staffHomepage(s_id_ptr);
            }
            rewind(fptr_leave4);
            while (fscanf(fptr_leave4, "%d, %[^,], %[^,], %d-%d-%d, %d days\n", &lv.leaveStaff_ID, lv.typeLeave, lv.statusLeave, &lv.day, &lv.month, &lv.year, &lv.duration) != EOF){
                if (lv.leaveStaff_ID == *s_id_ptr && lv.day == day && lv.month == month && lv.year == year && (strcmp(lv.statusLeave, "Canceled"))){
                    printf("Sorry, this is a duplicate leave.\n");
                    fclose(fptr_leave4);
                    staffHomepage(s_id_ptr);
                }
            }
            fclose(fptr_leave4);
            fflush(stdin);
            printf("Please enter the amount of days you would like to take leave for: \n");
            scanf("%d", &lv.duration);
            FILE *fptr_staff4 = fopen("staffDetails.txt", "r");
            if (fptr_staff4 == NULL){
                printf("File not found!\n");
                return;
            }
            FILE *fptr_temp4 = fopen("temp.txt", "w+");
            if (fptr_temp4 == NULL){
                printf("File not found!\n");
                return;
            }
            while (fscanf(fptr_staff4, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d", &st.staff_ID, st.staff_username, st.staff_password, st.staff_type, &st.annualLeave, &st.compLeave, &st.emergLeave, &st.matLeave, &st.medLeave)!= EOF){
                if (*s_id_ptr == st.staff_ID){
                    if (st.matLeave >= lv.duration){
                        st.matLeave -= lv.duration;
                        lv.leaveStaff_ID = st.staff_ID;
                        strcpy(lv.typeLeave, "Maternity Leave");
                        strcpy(lv.statusLeave, "Pending");
                        lv.day = day;
                        lv.month = month;
                        lv.year = year;
                        FILE *fptr_leave4 = fopen("leaveDetails.txt", "a+");
                        if (fptr_leave4 == NULL){
                            printf("File not found!\n");
                            return;
                        }
                        fprintf(fptr_leave4, "%d, %s, %s, %d-%d-%d, %d days\n", lv.leaveStaff_ID, lv.typeLeave, lv.statusLeave, lv.day, lv.month, lv.year, lv.duration);
                        fclose(fptr_leave4);
                        printf("Leave applied!\n");
                    }else{
                        printf("Leave duration exceeds balance!\n");
                        fclose(fptr_leave4);
                        fclose(fptr_staff4);
                        fclose(fptr_temp4);
                        remove("temp.txt");
                        staffHomepage(s_id_ptr);
                    }
                }
                fprintf(fptr_temp4, "%d, %s, %s, %s, %d, %d, %d, %d, %d\n", st.staff_ID, st.staff_username, st.staff_password, st.staff_type, st.annualLeave, st.compLeave, st.emergLeave, st.matLeave, st.medLeave);
            }
            fclose(fptr_staff4);
            fclose(fptr_temp4);
            remove("staffDetails.txt");
            rename("temp.txt", "staffDetails.txt");
        break;
        case 5:
            leaveCalander(&day, &month, &year);
            FILE *fptr_leave5  = fopen("leaveDetails.txt", "r");
            if (fptr_leave5 == NULL){
                printf("File not found!\n");
                staffHomepage(s_id_ptr);
            }
            rewind(fptr_leave5);
            while (fscanf(fptr_leave5, "%d, %[^,], %[^,], %d-%d-%d, %d days\n", &lv.leaveStaff_ID, lv.typeLeave, lv.statusLeave, &lv.day, &lv.month, &lv.year, &lv.duration) != EOF){
                if (lv.leaveStaff_ID == *s_id_ptr && lv.day == day && lv.month == month && lv.year == year && (strcmp(lv.statusLeave, "Canceled"))){
                    printf("Sorry, this is a duplicate leave.\n");
                    fclose(fptr_leave5);
                    staffHomepage(s_id_ptr);
                }
            }
            fclose(fptr_leave5);
            fflush(stdin);
            printf("Please enter the amount of days you would like to take leave for: \n");
            scanf("%d", &lv.duration);
            FILE *fptr_staff5 = fopen("staffDetails.txt", "r");
            if (fptr_staff5 == NULL){
                printf("File not found!\n");
                return;
            }
            FILE *fptr_temp5 = fopen("temp.txt", "w+");
            if (fptr_temp5 == NULL){
                printf("File not found!\n");
                return;
            }
            while (fscanf(fptr_staff5, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d", &st.staff_ID, st.staff_username, st.staff_password, st.staff_type, &st.annualLeave, &st.compLeave, &st.emergLeave, &st.matLeave, &st.medLeave)!= EOF){
                if (*s_id_ptr == st.staff_ID){
                    if (st.medLeave >= lv.duration){
                        st.medLeave -= lv.duration;
                        lv.leaveStaff_ID = st.staff_ID;
                        strcpy(lv.typeLeave, "Medical Leave");
                        strcpy(lv.statusLeave, "Pending");
                        lv.day = day;
                        lv.month = month;
                        lv.year = year;
                        FILE *fptr_leave5 = fopen("leaveDetails.txt", "a+");
                        if (fptr_leave5 == NULL){
                            printf("File not found!\n");
                            return;
                        }
                        fprintf(fptr_leave5, "%d, %s, %s, %d-%d-%d, %d days\n", lv.leaveStaff_ID, lv.typeLeave, lv.statusLeave, lv.day, lv.month, lv.year, lv.duration);
                        fclose(fptr_leave5);
                        printf("Leave applied!\n");
                    }else{
                        printf("Leave duration exceeds balance!\n");
                        fclose(fptr_leave5);
                        fclose(fptr_staff5);
                        fclose(fptr_temp5);
                        remove("temp.txt");
                        staffHomepage(s_id_ptr);
                    }
                }
                fprintf(fptr_temp5, "%d, %s, %s, %s, %d, %d, %d, %d, %d\n", st.staff_ID, st.staff_username, st.staff_password, st.staff_type, st.annualLeave, st.compLeave, st.emergLeave, st.matLeave, st.medLeave);
            }
            fclose(fptr_staff5);
            fclose(fptr_temp5);
            remove("staffDetails.txt");
            rename("temp.txt", "staffDetails.txt");
        break;
        case 6:
            staffHomepage(s_id_ptr);
        default:
        printf("Invalid choice.\n");
        continue;
        }
    }
}

void summaryLeave(int *s_id_ptr){
    int matchFound = 0;
    int i = 0;
    int cancelled = 0;

    leaves lv[sizeof(leaves)]; // declared as array bc there is going to be a lot of leave entries in the file
    staff st;

    FILE *fptr_leave = fopen("leaveDetails.txt", "r");
    if (fptr_leave == NULL){
        printf("File not found!\n");
        staffHomepage(s_id_ptr);
    }
    rewind(fptr_leave);
    while(fscanf(fptr_leave, "%d, %[^,], %[^,], %d-%d-%d, %d days\n", &lv[i].leaveStaff_ID, lv[i].typeLeave, lv[i].statusLeave, &lv[i].day, &lv[i].month, &lv[i].year, &lv[i].duration) != EOF){
        if (*s_id_ptr == lv[i].leaveStaff_ID){
            matchFound = 1;
            i++;
        }
    }
    fclose(fptr_leave);
    if (matchFound){
        int leaveIndex;
        int cancelSelect;
        int numberLeave = 1;

        printf("\n----------------------------------------------------------------------\n");
        printf("NUMBER     ID     TYPE OF LEAVE     LEAVE STATUS     DATE     DURATION");
        printf("\n----------------------------------------------------------------------");
        for (int j = 0; j < i; j++){
            printf("\n%2d. %10d %18s %12s %5d-%d-%d %5d days\n", numberLeave, lv[j].leaveStaff_ID, lv[j].typeLeave, lv[j].statusLeave, lv[j].day, lv[j].month, lv[j].year, lv[j].duration); // display/print out all leaves
            numberLeave++;
        }
        fflush(stdin);
        printf("\nWould you like to cancel a leave?\n");
        printf("1. Yes\n");
        printf("Press anything to go back\n");
        scanf("%d", &cancelSelect);

        if (cancelSelect == 1){
            fflush(stdin);
            printf("Enter the number you wish to cancel: \n");
            scanf("%d", &leaveIndex);
            leaveIndex = leaveIndex - 1;
            FILE *fptr_staff = fopen("staffDetails.txt", "r");
            if (fptr_staff == NULL){
                printf("File not found!\n");
                return;
            }
            FILE *fptr_temp = fopen("temp.txt", "w+");
            if (fptr_temp == NULL){
                printf("File not found!\n");
                return;
            }

            FILE *fptr_leave = fopen("leaveDetails.txt", "r");
            if (fptr_leave == NULL){
                printf("File not found!\n");
                return;
            }

            FILE *fptr_tempLeave = fopen("templeave.txt", "w+");
            if (fptr_tempLeave == NULL){
                printf("File not found!\n");
                return;
            }

            if (leaveIndex >= 0 && leaveIndex < i){
                time_t t = time(NULL);
                struct tm currentTime = *localtime(&t);
                if (currentTime.tm_year + 1900 > lv[leaveIndex].year || // separated to make it less confusing
                    (currentTime.tm_year + 1900 == lv[leaveIndex].year && currentTime.tm_mon + 1 > lv[leaveIndex].month) ||
                    (currentTime.tm_year + 1900 == lv[leaveIndex].year && currentTime.tm_mon + 1 == lv[leaveIndex].month && currentTime.tm_mday > lv[leaveIndex].day)) {
                        printf("Leave cannot be canceled because it has already passed.\n");
                        fclose(fptr_staff);
                        fclose(fptr_leave);
                        fclose(fptr_temp);
                        fclose(fptr_tempLeave);
                        remove("temp.txt");
                        remove("templeave.txt");
                        staffHomepage(s_id_ptr);
                }
                while (fscanf(fptr_staff, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d", &st.staff_ID, st.staff_username, st.staff_password, st.staff_type, &st.annualLeave, &st.compLeave, &st.emergLeave, &st.matLeave, &st.medLeave)!= EOF){
                    if (*s_id_ptr == st.staff_ID){
                        if (!strcmp(lv[leaveIndex].statusLeave, "Pending") || !strcmp(lv[leaveIndex].statusLeave, "Approved")){
                            if (!strcmp(lv[leaveIndex].typeLeave, "Annual Leave")){
                                st.annualLeave += lv[leaveIndex].duration;
                            }else if (!strcmp(lv[leaveIndex].typeLeave, "Compassionate Leave")){
                                st.compLeave += lv[leaveIndex].duration;
                            }else if (!strcmp(lv[leaveIndex].typeLeave, "Emergency Leave")){
                                st.emergLeave += lv[leaveIndex].duration;
                            }else if (!strcmp(lv[leaveIndex].typeLeave, "Maternity Leave")){
                                st.matLeave += lv[leaveIndex].duration;
                            }else if (!strcmp(lv[leaveIndex].typeLeave, "Medical Leave")){
                                st.medLeave += lv[leaveIndex].duration;
                            }


                            while (fscanf(fptr_leave, "%d, %[^,], %[^,], %d-%d-%d, %d days\n", &lv[i].leaveStaff_ID, lv[i].typeLeave, lv[i].statusLeave, &lv[i].day, &lv[i].month, &lv[i].year, &lv[i].duration) != EOF){
                                int flag = 0; // flags duplicates
                                for (int j = 0; j < i; j++){
                                    if (j == leaveIndex) {
                                        if (lv[j].leaveStaff_ID == *s_id_ptr && !strcmp(lv[j].statusLeave, "Pending") && !strcmp(lv[j].typeLeave, lv[leaveIndex].typeLeave) && lv[i].leaveStaff_ID == lv[leaveIndex].leaveStaff_ID && lv[i].day == lv[leaveIndex].day && lv[i].month == lv[leaveIndex].month && lv[i].year == lv[leaveIndex].year && lv[i].duration == lv[leaveIndex].duration){
                                            strcpy(lv[j].statusLeave, "Canceled");
                                            fprintf(fptr_tempLeave, "%d, %s, %s, %d-%d-%d, %d days\n", lv[j].leaveStaff_ID, lv[j].typeLeave, lv[j].statusLeave, lv[j].day, lv[j].month, lv[j].year, lv[j].duration);
                                            fflush(fptr_tempLeave);
                                            flag = 1;
                                        }else if (lv[j].leaveStaff_ID == *s_id_ptr && !strcmp(lv[j].statusLeave, "Approved") && !strcmp(lv[j].typeLeave, lv[leaveIndex].typeLeave) && lv[i].leaveStaff_ID == lv[leaveIndex].leaveStaff_ID && lv[i].day == lv[leaveIndex].day && lv[i].month == lv[leaveIndex].month && lv[i].year == lv[leaveIndex].year && lv[i].duration == lv[leaveIndex].duration){
                                            strcpy(lv[j].statusLeave, "Canceled");
                                            fprintf(fptr_tempLeave, "%d, %s, %s, %d-%d-%d, %d days\n", lv[j].leaveStaff_ID, lv[j].typeLeave, lv[j].statusLeave, lv[j].day, lv[j].month, lv[j].year, lv[j].duration);
                                            fflush(fptr_tempLeave);
                                            flag = 1;
                                        }
                                    }
                                }
                                if (!flag) {
                                    fprintf(fptr_tempLeave, "%d, %s, %s, %d-%d-%d, %d days\n", lv[i].leaveStaff_ID, lv[i].typeLeave, lv[i].statusLeave, lv[i].day, lv[i].month, lv[i].year, lv[i].duration);
                                    fflush(fptr_tempLeave);
                                }
                            }
                                cancelled = 1;
                            }else{
                                printf("Cannot cancel leave as leave is %s!\n", lv[leaveIndex].statusLeave);
                                fclose(fptr_leave);
                                fclose(fptr_staff);
                                fclose(fptr_temp);
                                fclose(fptr_tempLeave);
                                remove("temp.txt");
                                remove("templeave.txt");
                                staffHomepage(s_id_ptr);
                            }
                    }
                    fprintf(fptr_temp, "%d, %s, %s, %s, %d, %d, %d, %d, %d\n", st.staff_ID, st.staff_username, st.staff_password, st.staff_type, st.annualLeave, st.compLeave, st.emergLeave, st.matLeave, st.medLeave);
                }
            }else{
                fclose(fptr_temp);
                fclose(fptr_tempLeave);
                fclose(fptr_leave);
                fclose(fptr_leave);
                fclose(fptr_staff);
                remove("templeave.txt");
                remove("temp.txt");
                printf("Invalid index.\n");
            }
            if (cancelled){
                fclose(fptr_leave);
                fclose(fptr_tempLeave);
                fclose(fptr_leave);
                remove("leaveDetails.txt");
                rename("templeave.txt", "leaveDetails.txt");

                printf("Leave successfully canceled!\n");
                fclose(fptr_temp);
                fclose(fptr_staff);
                remove("staffDetails.txt");
                rename("temp.txt", "staffDetails.txt");
                staffHomepage(s_id_ptr);
            }
        }else{
            fclose(fptr_leave);
            staffHomepage(s_id_ptr);
        }
    }else{
        printf("No leaves applied!\n");
        fclose(fptr_leave);
        staffHomepage(s_id_ptr);
    }
}

void deleteLeave(int *s_id_ptr){
    int matchFound = 0;
    int i = 0;
    int deleted = 0;

    leaves lv[sizeof(leaves)]; // declared as array bc there is going to be a lot of leave entries in the file
    staff st;

    FILE *fptr_leave = fopen("leaveDetails.txt", "r");
    if (fptr_leave == NULL){
        printf("File not found!\n");
        staffHomepage(s_id_ptr);
    }
    rewind(fptr_leave);
    while(fscanf(fptr_leave, "%d, %[^,], %[^,], %d-%d-%d, %d days\n", &lv[i].leaveStaff_ID, lv[i].typeLeave, lv[i].statusLeave, &lv[i].day, &lv[i].month, &lv[i].year, &lv[i].duration) != EOF){
        if (*s_id_ptr == lv[i].leaveStaff_ID){
            matchFound = 1;
            i++;
        }
    }
    fclose(fptr_leave);
    if (matchFound){
        int leaveIndex;
        int cancelSelect;
        int numberLeave = 1;

        printf("\n----------------------------------------------------------------------\n");
        printf("NUMBER     ID     TYPE OF LEAVE     LEAVE STATUS     DATE     DURATION");
        printf("\n----------------------------------------------------------------------");
        for (int j = 0; j < i; j++){
            printf("\n%2d. %10d %18s %12s %5d-%d-%d %5d days\n", numberLeave, lv[j].leaveStaff_ID, lv[j].typeLeave, lv[j].statusLeave, lv[j].day, lv[j].month, lv[j].year, lv[j].duration); // display/print out all leaves
            numberLeave++;
        }
        fflush(stdin);
            printf("Enter the number you wish to delete, enter any character to go back to the homepage: \n");
            scanf("%d", &leaveIndex);
            leaveIndex = leaveIndex - 1;
            FILE *fptr_staff = fopen("staffDetails.txt", "r");
            if (fptr_staff == NULL){
                printf("File not found!\n");
                return;
            }
            FILE *fptr_temp = fopen("temp.txt", "w+");
            if (fptr_temp == NULL){
                printf("File not found!\n");
                return;
            }

            FILE *fptr_leave = fopen("leaveDetails.txt", "r");
            if (fptr_leave == NULL){
                printf("File not found!\n");
                return;
            }

            FILE *fptr_tempLeave = fopen("templeave.txt", "w+");
            if (fptr_tempLeave == NULL){
                printf("File not found!\n");
                return;
            }

            if (leaveIndex >= 0 && leaveIndex < i){
                while (fscanf(fptr_staff, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d", &st.staff_ID, st.staff_username, st.staff_password, st.staff_type, &st.annualLeave, &st.compLeave, &st.emergLeave, &st.matLeave, &st.medLeave)!= EOF){
                    if (*s_id_ptr == st.staff_ID){
                        if (!strcmp(lv[leaveIndex].statusLeave, "Canceled") || !strcmp(lv[leaveIndex].statusLeave, "Rejected")){
                            int flag = 0;
                            while (fscanf(fptr_leave, "%d, %[^,], %[^,], %d-%d-%d, %d days\n", &lv[i].leaveStaff_ID, lv[i].typeLeave, lv[i].statusLeave, &lv[i].day, &lv[i].month, &lv[i].year, &lv[i].duration) != EOF){
                                if (lv[i].leaveStaff_ID == lv[leaveIndex].leaveStaff_ID && strcmp(lv[i].typeLeave, lv[leaveIndex].typeLeave) == 0 && strcmp(lv[i].statusLeave, lv[leaveIndex].statusLeave) == 0 && lv[i].day == lv[leaveIndex].day && lv[i].month == lv[leaveIndex].month && lv[i].year == lv[leaveIndex].year && lv[i].duration == lv[leaveIndex].duration) {
                                    flag = 1; // set flag to indicate that the leave has been found
                                }else {
                                    fprintf(fptr_tempLeave, "%d, %s, %s, %d-%d-%d, %d days\n", lv[i].leaveStaff_ID, lv[i].typeLeave, lv[i].statusLeave, lv[i].day, lv[i].month, lv[i].year, lv[i].duration);
                                }
                                i++;
                            }
                            if (!flag) {
                                printf("Leave not found!\n");
                            }

                            deleted = 1;
                            }else{
                                printf("Cannot delete leave as leave is %s!\n", lv[leaveIndex].statusLeave);
                                fclose(fptr_leave);
                                fclose(fptr_staff);
                                fclose(fptr_temp);
                                fclose(fptr_tempLeave);
                                remove("temp.txt");
                                remove("templeave.txt");
                                staffHomepage(s_id_ptr);
                            }
                    }
                    fprintf(fptr_temp, "%d, %s, %s, %s, %d, %d, %d, %d, %d\n", st.staff_ID, st.staff_username, st.staff_password, st.staff_type, st.annualLeave, st.compLeave, st.emergLeave, st.matLeave, st.medLeave);
                }
            }else{
                fclose(fptr_temp);
                fclose(fptr_tempLeave);
                fclose(fptr_leave);
                fclose(fptr_leave);
                fclose(fptr_staff);
                remove("templeave.txt");
                remove("temp.txt");
                printf("Invalid index.\n");
            }
            if (deleted){
                fclose(fptr_leave);
                fclose(fptr_tempLeave);
                fclose(fptr_leave);
                remove("leaveDetails.txt");
                rename("templeave.txt", "leaveDetails.txt");

                printf("Leave successfully deleted!\n");
                fclose(fptr_temp);
                fclose(fptr_staff);
                remove("staffDetails.txt");
                rename("temp.txt", "staffDetails.txt");
                staffHomepage(s_id_ptr);
            }
    }else{
        printf("No leaves applied!\n");
        fclose(fptr_leave);
        staffHomepage(s_id_ptr);
    }
}

// ADMIN HOMEPAGE FUNCTIONS

void updateLeaves(){
    char buff[10];
    int search_staffID, updateLeaveType;
    int i = 0;
    int matchFound = 0;

    staff st;
    st.staff_ID = 0;
    FILE *fptr_staff = fopen("staffDetails.txt", "r");
    if (fptr_staff == NULL){
        printf("File not found!\n");
        return;
    }
    FILE *fptr_temp  = fopen("temp.txt", "w+");
    if (fptr_temp == NULL){
        printf("File not found!\n");
        return;
    }

    rewind(fptr_staff);
    printf("\nSTAFF ID    USERNAME    TYPE OF STAFF    ANNUAL    COMPASSIONATE    EMERGENCY    MATERNITY    MEDICAL");
    printf("\n------------------------------------------------------------------------------------------------------------------------\n");
    while (fscanf(fptr_staff, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d", &st.staff_ID, st.staff_username, st.staff_password, st.staff_type, &st.annualLeave, &st.compLeave, &st.emergLeave, &st.matLeave, &st.medLeave)!= EOF){
        printf("%5d %12s %14s %10d %13d %13d %12d %11d\n", st.staff_ID, st.staff_username, st.staff_type, st.annualLeave, st.compLeave, st.emergLeave, st.matLeave, st.medLeave);
    }

    printf("Enter the Staff ID to update the leave balance, enter 1 to go back: \n");
    scanf("%d", &search_staffID);

    rewind(fptr_staff);
    while (fscanf(fptr_staff, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d", &st.staff_ID, st.staff_username, st.staff_password, st.staff_type, &st.annualLeave, &st.compLeave, &st.emergLeave, &st.matLeave, &st.medLeave)!= EOF){
        fflush(stdin);
        if (search_staffID != 1){
            if (search_staffID == st.staff_ID){
                matchFound = 1;
                printf("Please select which type of leave you would like to update\n");
                printf("1. Annual Leave\n");
                printf("2. Compassionate Leave\n");
                printf("3. Emergency Leave\n");
                printf("4. Maternity Leave\n");
                printf("5. Medical Leave\n");
                printf("6. Back\n");
                scanf("%s", buff);
                updateLeaveType = atoi(buff);

                switch(updateLeaveType){
                case 1:
                    printf("Enter the new amount of leaves you would like to update it to: \n");
                    scanf("%d", &st.annualLeave);
                break;
                case 2:
                    printf("Enter the new amount of leaves you would like to update it to: \n");
                    scanf("%d", &st.compLeave);
                break;
                case 3:
                    printf("Enter the new amount of leaves you would like to update it to: \n");
                    scanf("%d", &st.emergLeave);
                break;
                case 4:
                    printf("Enter the new amount of leaves you would like to update it to: \n");
                    scanf("%d", &st.matLeave);
                break;
                case 5:
                    printf("Enter the new amount of leaves you would like to update it to: \n");
                    scanf("%d", &st.medLeave);
                break;
                default:
                    printf("Invalid option.\n");
                }
            }
        }
        fprintf(fptr_temp, "%d, %s, %s, %s, %d, %d, %d, %d, %d\n", st.staff_ID, st.staff_username, st.staff_password, st.staff_type, st.annualLeave, st.compLeave, st.emergLeave, st.matLeave, st.medLeave);
    }
    if (matchFound){ // if matchFound, will update the leave balance
        fclose(fptr_staff);
        fclose(fptr_temp);
        remove("staffDetails.txt");
        rename("temp.txt", "staffDetails.txt");
        printf("Leave balance updated successfully!\n");
    }else if (search_staffID != 1){
        fclose(fptr_staff);
        fclose(fptr_temp);
        remove("temp.txt");
        printf("Staff ID not found!\n");
    }else {
        fclose(fptr_staff);
        fclose(fptr_temp);
        remove("temp.txt");
    }
adminHomepage();
}

void searchStaffLeaves(){
    int matchFound = 0;
    int i = 0;
    int searchInput;
    leaves lv[100];

    FILE *fptr_leave = fopen("leaveDetails.txt", "r");
    if (fptr_leave == NULL){
        printf("File not found!\n");
        return;
    }
    rewind(fptr_leave);
    fflush(stdin);
    printf("Please enter the staff ID to view their leave details: \n");
    scanf("%d", &searchInput);

    while(fscanf(fptr_leave, "%d, %[^,], %[^,], %d-%d-%d, %d days\n", &lv[i].leaveStaff_ID, lv[i].typeLeave, lv[i].statusLeave, &lv[i].day, &lv[i].month, &lv[i].year, &lv[i].duration) != EOF){
        if (searchInput == lv[i].leaveStaff_ID){
            matchFound = 1;
            i++;
        }
    }
    if (matchFound){
        int j = 0;

        printf("\n-------------------------------------------------------------\n");
        printf("ID       TYPE OF LEAVE     LEAVE STATUS     DATE     DURATION");
        printf("\n-------------------------------------------------------------");
        for (int j = 0; j < i; j++){
            printf("\n%2d %18s %12s %5d-%d-%d %5d days\n", lv[j].leaveStaff_ID, lv[j].typeLeave, lv[j].statusLeave, lv[j].day, lv[j].month, lv[j].year, lv[j].duration); // display/print out all leaves
        }
    }else{
        printf("Staff ID not found or leave not applied!\n");
        return;
    }
    fclose(fptr_leave);
    adminHomepage();
}

void generateReport(){
    srand(time(0));
    time_t now = time(NULL);
    struct tm *current_time = localtime(&now);
    leaves lv;

    FILE *fptr_leave = fopen("leaveDetails.txt", "r");
    if (fptr_leave == NULL){
        printf("File not found!\n");
        return;
    }

    FILE *fptr_report = fopen("ApuLeaveReport.txt", "w+");
    if (fptr_report == NULL){
        printf("File not found!\n");
        return;
    }

    int leave_count = 0;
    while (fscanf(fptr_leave, "%d, %[^,], %[^,], %d-%d-%d, %d days\n", &lv.leaveStaff_ID, lv.typeLeave, lv.statusLeave, &lv.day, &lv.month, &lv.year, &lv.duration) != EOF){
        if (lv.month == current_time->tm_mon + 1 && lv.year == current_time->tm_year + 1900) {
            leave_count++;
        }
    }

    fprintf(fptr_report, "***********MONTHLY REPORT FOR LEAVE APPLICATIONS***********\n");
    fprintf(fptr_report, "-----------------------------------------------------------\n");
    fprintf(fptr_report, "Department/Faculty                Leaves Applied\n");
    fprintf(fptr_report, "-----------------------------------------------------------\n");
    fprintf(fptr_report, "    Accounting                        %-5d\n", rand() % (3 + 1));
    fprintf(fptr_report, "      Admin                           %-5d\n", rand() % (3 + 1)); // upper bound is 3 and lower bound is 0, hence why there is no 0 in formula
    fprintf(fptr_report, "       Arts                           %-5d\n", rand() % (3 + 1));
    fprintf(fptr_report, "     Business                         %-5d\n", rand() % (3 + 1));
    fprintf(fptr_report, "    Computing                         %-5d\n", leave_count); // i chose school of computing, hence why this only reflects the leave numbers
    fprintf(fptr_report, "    Engineering                       %-5d\n", rand() % (3 + 1));
    fprintf(fptr_report, "    Psychology                        %-5d\n", rand() % (3 + 1));
    fclose(fptr_report);
    fclose(fptr_leave);
    printf("Report successfully generated!\n");
    adminHomepage();
}

// APPROVER HOMEPAGE FUNCTIONS

void approveLeaves(){
    int matchFound = 0;
    int i = 0;
    int approved = 0;
    int numberLeave = 1;
    int leaveIndex;

    leaves lv[sizeof(leaves)];
    staff st;

    FILE *fptr_leave = fopen("leaveDetails.txt", "r");
    if (fptr_leave == NULL){
        printf("File not found!\n");
    }
    rewind(fptr_leave);

    printf("\n----------------------------------------------------------------------\n");
    printf("NUMBER     ID     TYPE OF LEAVE     LEAVE STATUS     DATE     DURATION");
    printf("\n----------------------------------------------------------------------");
    while(fscanf(fptr_leave, "%d, %[^,], %[^,], %d-%d-%d, %d days\n", &lv[i].leaveStaff_ID, lv[i].typeLeave, lv[i].statusLeave, &lv[i].day, &lv[i].month, &lv[i].year, &lv[i].duration) != EOF){
        printf("\n%2d. %10d %18s %12s %5d-%d-%d %5d days\n", numberLeave, lv[i].leaveStaff_ID, lv[i].typeLeave, lv[i].statusLeave, lv[i].day, lv[i].month, lv[i].year, lv[i].duration);
        i++;
        numberLeave++;
    }
    fclose(fptr_leave);

    fflush(stdin);
    printf("\nWhich leave would you like to approve? Enter any character to go back to the homepage. \n");
    scanf("%d", &leaveIndex);
    leaveIndex = leaveIndex - 1;

    FILE *fptr_staff = fopen("staffDetails.txt", "r");
    if (fptr_staff == NULL){
        printf("File not found!\n");
        return;
    }
    FILE *fptr_temp = fopen("temp.txt", "w+");
    if (fptr_temp == NULL){
        printf("File not found!\n");
        return;
    }

    FILE *fptr_leave2 = fopen("leaveDetails.txt", "r");
    if (fptr_leave2 == NULL){
        printf("File not found!\n");
        return;
    }

    FILE *fptr_tempLeave2 = fopen("templeave.txt", "w+");
    if (fptr_tempLeave2 == NULL){
        printf("File not found!\n");
        return;
    }

    if (leaveIndex >= 0 && leaveIndex < i){
        time_t t = time(NULL);
        struct tm currentTime = *localtime(&t);
        if (currentTime.tm_year + 1900 > lv[leaveIndex].year ||
            (currentTime.tm_year + 1900 == lv[leaveIndex].year && currentTime.tm_mon + 1 > lv[leaveIndex].month) ||
            (currentTime.tm_year + 1900 == lv[leaveIndex].year && currentTime.tm_mon + 1 == lv[leaveIndex].month && currentTime.tm_mday > lv[leaveIndex].day)) {
                printf("Leave cannot be approved because it has already passed.\n");
                fclose(fptr_staff);
                fclose(fptr_leave2);
                fclose(fptr_temp);
                fclose(fptr_tempLeave2);
                remove("temp.txt");
                remove("templeave.txt");
                approverHomepage();
        }

        while (fscanf(fptr_staff, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d", &st.staff_ID, st.staff_username, st.staff_password, st.staff_type, &st.annualLeave, &st.compLeave, &st.emergLeave, &st.matLeave, &st.medLeave)!= EOF){
            if (st.staff_ID == lv[leaveIndex].leaveStaff_ID){
                if (!strcmp(lv[leaveIndex].statusLeave, "Pending") || !strcmp(lv[leaveIndex].statusLeave, "Rejected")){
                    while (fscanf(fptr_leave2, "%d, %[^,], %[^,], %d-%d-%d, %d days\n", &lv[i].leaveStaff_ID, lv[i].typeLeave, lv[i].statusLeave, &lv[i].day, &lv[i].month, &lv[i].year, &lv[i].duration) != EOF){
                        int duplicate = 0;
                        for (int j = 0; j < i; j++){
                            if (j == leaveIndex) {
                                if (lv[j].leaveStaff_ID == lv[leaveIndex].leaveStaff_ID && !strcmp(lv[j].statusLeave, "Pending") && !strcmp(lv[j].typeLeave, lv[leaveIndex].typeLeave) && lv[i].leaveStaff_ID == lv[leaveIndex].leaveStaff_ID && lv[i].day == lv[leaveIndex].day && lv[i].month == lv[leaveIndex].month && lv[i].year == lv[leaveIndex].year && lv[i].duration == lv[leaveIndex].duration){
                                    strcpy(lv[j].statusLeave, "Approved");
                                    fprintf(fptr_tempLeave2, "%d, %s, %s, %d-%d-%d, %d days\n", lv[j].leaveStaff_ID, lv[j].typeLeave, lv[j].statusLeave, lv[j].day, lv[j].month, lv[j].year, lv[j].duration);
                                    fflush(fptr_tempLeave2);
                                    duplicate = 1;
                                }else if (lv[j].leaveStaff_ID == lv[leaveIndex].leaveStaff_ID && !strcmp(lv[j].statusLeave, "Rejected") && !strcmp(lv[j].typeLeave, lv[leaveIndex].typeLeave) && lv[i].leaveStaff_ID == lv[leaveIndex].leaveStaff_ID && lv[i].day == lv[leaveIndex].day && lv[i].month == lv[leaveIndex].month && lv[i].year == lv[leaveIndex].year && lv[i].duration == lv[leaveIndex].duration){
                                    strcpy(lv[j].statusLeave, "Approved");
                                    if (!strcmp(lv[leaveIndex].typeLeave, "Annual Leave")){
                                        if (st.annualLeave >= lv[leaveIndex].duration){
                                           st.annualLeave -= lv[leaveIndex].duration;
                                        }else{
                                            fclose(fptr_temp);
                                            fclose(fptr_tempLeave2);
                                            fclose(fptr_leave2);
                                            fclose(fptr_leave);
                                            fclose(fptr_staff);
                                            remove("templeave.txt");
                                            remove("temp.txt");
                                            printf("Leave balance would be less than 0!\n"); // if leave balance is less than duration of leave, cannot approve as it would be negative number
                                            approverHomepage();
                                        }
                                    }else if (!strcmp(lv[leaveIndex].typeLeave, "Compassionate Leave")){
                                        if (st.compLeave >= lv[leaveIndex].duration){
                                           st.compLeave -= lv[leaveIndex].duration;
                                        }else{
                                            fclose(fptr_temp);
                                            fclose(fptr_tempLeave2);
                                            fclose(fptr_leave2);
                                            fclose(fptr_leave);
                                            fclose(fptr_staff);
                                            remove("templeave.txt");
                                            remove("temp.txt");
                                            printf("Leave balance would be less than 0!\n");
                                            approverHomepage();
                                        }
                                    }else if (!strcmp(lv[leaveIndex].typeLeave, "Emergency Leave")){
                                        if (st.emergLeave >= lv[leaveIndex].duration){
                                           st.emergLeave -= lv[leaveIndex].duration;
                                        }else{
                                            fclose(fptr_temp);
                                            fclose(fptr_tempLeave2);
                                            fclose(fptr_leave2);
                                            fclose(fptr_leave);
                                            fclose(fptr_staff);
                                            remove("templeave.txt");
                                            remove("temp.txt");
                                            printf("Leave balance would be less than 0!\n");
                                            approverHomepage();
                                        }
                                    }else if (!strcmp(lv[leaveIndex].typeLeave, "Maternity Leave")){
                                        if (st.matLeave >= lv[leaveIndex].duration){
                                           st.matLeave -= lv[leaveIndex].duration;
                                        }else{
                                            fclose(fptr_temp);
                                            fclose(fptr_tempLeave2);
                                            fclose(fptr_leave2);
                                            fclose(fptr_leave);
                                            fclose(fptr_staff);
                                            remove("templeave.txt");
                                            remove("temp.txt");
                                            printf("Leave balance would be less than 0!\n");
                                            approverHomepage();
                                        }
                                    }else if (!strcmp(lv[leaveIndex].typeLeave, "Medical Leave")){
                                        if (st.medLeave >= lv[leaveIndex].duration){
                                           st.medLeave -= lv[leaveIndex].duration;
                                        }else{
                                            fclose(fptr_temp);
                                            fclose(fptr_tempLeave2);
                                            fclose(fptr_leave2);
                                            fclose(fptr_leave);
                                            fclose(fptr_staff);
                                            remove("templeave.txt");
                                            remove("temp.txt");
                                            printf("Leave balance would be less than 0!\n");
                                            approverHomepage();
                                        }
                                    }
                                    fprintf(fptr_tempLeave2, "%d, %s, %s, %d-%d-%d, %d days\n", lv[j].leaveStaff_ID, lv[j].typeLeave, lv[j].statusLeave, lv[j].day, lv[j].month, lv[j].year, lv[j].duration);
                                    fflush(fptr_tempLeave2);
                                    duplicate = 1;
                                }
                            }
                        }
                        if (!duplicate) {
                            fprintf(fptr_tempLeave2, "%d, %s, %s, %d-%d-%d, %d days\n", lv[i].leaveStaff_ID, lv[i].typeLeave, lv[i].statusLeave, lv[i].day, lv[i].month, lv[i].year, lv[i].duration);
                            fflush(fptr_tempLeave2);
                        }
                    }
                    approved = 1;
                    }else{
                        fclose(fptr_temp);
                        fclose(fptr_tempLeave2);
                        fclose(fptr_leave2);
                        fclose(fptr_leave);
                        fclose(fptr_staff);
                        remove("templeave.txt");
                        remove("temp.txt");
                        printf("Cannot approve leave as leave is %s!\n", lv[leaveIndex].statusLeave);
                        approverHomepage();
                    }
            }
            fprintf(fptr_temp, "%d, %s, %s, %s, %d, %d, %d, %d, %d\n", st.staff_ID, st.staff_username, st.staff_password, st.staff_type, st.annualLeave, st.compLeave, st.emergLeave, st.matLeave, st.medLeave);
        }
        fclose(fptr_leave);
        fclose(fptr_tempLeave2);
        fclose(fptr_leave2);
        remove("leaveDetails.txt");
        rename("templeave.txt", "leaveDetails.txt");
        fclose(fptr_temp);
        fclose(fptr_staff);
        remove("staffDetails.txt");
        rename("temp.txt", "staffDetails.txt");
    }else{
        fclose(fptr_temp);
        fclose(fptr_tempLeave2);
        fclose(fptr_leave2);
        fclose(fptr_leave);
        fclose(fptr_staff);
        remove("templeave.txt");
        remove("temp.txt");
        printf("Invalid index.\n");
    }
    if (approved){
        printf("Leave has been approved!\n");
    }
    approverHomepage();
}

void rejectLeaves(){
    int matchFound = 0;
    int i = 0;
    int rejected = 0;
    int numberLeave = 1;
    int leaveIndex;

    leaves lv[sizeof(leaves)];
    staff st;

    FILE *fptr_leave = fopen("leaveDetails.txt", "r");
    if (fptr_leave == NULL){
        printf("File not found!\n");
    }
    rewind(fptr_leave);

    printf("\n----------------------------------------------------------------------\n");
    printf("NUMBER     ID     TYPE OF LEAVE     LEAVE STATUS     DATE     DURATION");
    printf("\n----------------------------------------------------------------------");
    while(fscanf(fptr_leave, "%d, %[^,], %[^,], %d-%d-%d, %d days\n", &lv[i].leaveStaff_ID, lv[i].typeLeave, lv[i].statusLeave, &lv[i].day, &lv[i].month, &lv[i].year, &lv[i].duration) != EOF){
        printf("\n%2d. %10d %18s %12s %5d-%d-%d %5d days\n", numberLeave, lv[i].leaveStaff_ID, lv[i].typeLeave, lv[i].statusLeave, lv[i].day, lv[i].month, lv[i].year, lv[i].duration);
        i++;
        numberLeave++;
    }
    fclose(fptr_leave);

    fflush(stdin);
    printf("\nWhich leave would you like to reject? Enter any character to go back to the homepage. \n");
    scanf("%d", &leaveIndex);
    leaveIndex = leaveIndex - 1;

    FILE *fptr_staff = fopen("staffDetails.txt", "r");
    if (fptr_staff == NULL){
        printf("File not found!\n");
        return;
    }
    FILE *fptr_temp = fopen("temp.txt", "w+");
    if (fptr_temp == NULL){
        printf("File not found!\n");
        return;
    }

    FILE *fptr_leave2 = fopen("leaveDetails.txt", "r");
    if (fptr_leave2 == NULL){
        printf("File not found!\n");
        return;
    }

    FILE *fptr_tempLeave2 = fopen("templeave.txt", "w+");
    if (fptr_tempLeave2 == NULL){
        printf("File not found!\n");
        return;
    }

    if (leaveIndex >= 0 && leaveIndex < i){
        time_t t = time(NULL);
        struct tm currentTime = *localtime(&t);
        if (currentTime.tm_year + 1900 > lv[leaveIndex].year ||
            (currentTime.tm_year + 1900 == lv[leaveIndex].year && currentTime.tm_mon + 1 > lv[leaveIndex].month) ||
            (currentTime.tm_year + 1900 == lv[leaveIndex].year && currentTime.tm_mon + 1 == lv[leaveIndex].month && currentTime.tm_mday > lv[leaveIndex].day)) {
                printf("Leave cannot be rejected because it has already passed.\n");
                fclose(fptr_staff);
                fclose(fptr_leave2);
                fclose(fptr_temp);
                fclose(fptr_tempLeave2);
                remove("temp.txt");
                remove("templeave.txt");
                approverHomepage();
        }

        while (fscanf(fptr_staff, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d", &st.staff_ID, st.staff_username, st.staff_password, st.staff_type, &st.annualLeave, &st.compLeave, &st.emergLeave, &st.matLeave, &st.medLeave)!= EOF){
            if (st.staff_ID == lv[leaveIndex].leaveStaff_ID){
                if (!strcmp(lv[leaveIndex].statusLeave, "Pending") || !strcmp(lv[leaveIndex].statusLeave, "Approved")){
                    if (!strcmp(lv[leaveIndex].typeLeave, "Annual Leave")){
                        st.annualLeave += lv[leaveIndex].duration;
                    }else if (!strcmp(lv[leaveIndex].typeLeave, "Compassionate Leave")){
                        st.compLeave += lv[leaveIndex].duration;
                    }else if (!strcmp(lv[leaveIndex].typeLeave, "Emergency Leave")){
                        st.emergLeave += lv[leaveIndex].duration;
                    }else if (!strcmp(lv[leaveIndex].typeLeave, "Maternity Leave")){
                        st.matLeave += lv[leaveIndex].duration;
                    }else if (!strcmp(lv[leaveIndex].typeLeave, "Medical Leave")){
                        st.medLeave += lv[leaveIndex].duration;
                    }

                    while (fscanf(fptr_leave2, "%d, %[^,], %[^,], %d-%d-%d, %d days\n", &lv[i].leaveStaff_ID, lv[i].typeLeave, lv[i].statusLeave, &lv[i].day, &lv[i].month, &lv[i].year, &lv[i].duration) != EOF){
                        int duplicate = 0;
                        for (int j = 0; j < i; j++){
                            if (j == leaveIndex) {
                                if (lv[j].leaveStaff_ID == lv[leaveIndex].leaveStaff_ID && !strcmp(lv[j].statusLeave, "Pending") && !strcmp(lv[j].typeLeave, lv[leaveIndex].typeLeave) && lv[i].leaveStaff_ID == lv[leaveIndex].leaveStaff_ID && lv[i].day == lv[leaveIndex].day && lv[i].month == lv[leaveIndex].month && lv[i].year == lv[leaveIndex].year && lv[i].duration == lv[leaveIndex].duration){
                                    strcpy(lv[j].statusLeave, "Rejected");
                                    fprintf(fptr_tempLeave2, "%d, %s, %s, %d-%d-%d, %d days\n", lv[j].leaveStaff_ID, lv[j].typeLeave, lv[j].statusLeave, lv[j].day, lv[j].month, lv[j].year, lv[j].duration);
                                    fflush(fptr_tempLeave2);
                                    duplicate = 1;
                                }else if (lv[j].leaveStaff_ID == lv[leaveIndex].leaveStaff_ID && !strcmp(lv[j].statusLeave, "Approved") && !strcmp(lv[j].typeLeave, lv[leaveIndex].typeLeave) && lv[i].leaveStaff_ID == lv[leaveIndex].leaveStaff_ID && lv[i].day == lv[leaveIndex].day && lv[i].month == lv[leaveIndex].month && lv[i].year == lv[leaveIndex].year && lv[i].duration == lv[leaveIndex].duration){
                                    strcpy(lv[j].statusLeave, "Rejected");
                                    fprintf(fptr_tempLeave2, "%d, %s, %s, %d-%d-%d, %d days\n", lv[j].leaveStaff_ID, lv[j].typeLeave, lv[j].statusLeave, lv[j].day, lv[j].month, lv[j].year, lv[j].duration);
                                    fflush(fptr_tempLeave2);
                                    duplicate = 1;
                                }
                            }
                        }
                        if (!duplicate) {
                            fprintf(fptr_tempLeave2, "%d, %s, %s, %d-%d-%d, %d days\n", lv[i].leaveStaff_ID, lv[i].typeLeave, lv[i].statusLeave, lv[i].day, lv[i].month, lv[i].year, lv[i].duration);
                            fflush(fptr_tempLeave2);
                        }
                    }
                    rejected = 1;
                    }else{
                        fclose(fptr_temp);
                        fclose(fptr_tempLeave2);
                        fclose(fptr_leave2);
                        fclose(fptr_leave);
                        fclose(fptr_staff);
                        remove("templeave.txt");
                        remove("temp.txt");
                        printf("Cannot reject leave as leave is %s!\n", lv[leaveIndex].statusLeave);
                        approverHomepage();
                    }
            }
            fprintf(fptr_temp, "%d, %s, %s, %s, %d, %d, %d, %d, %d\n", st.staff_ID, st.staff_username, st.staff_password, st.staff_type, st.annualLeave, st.compLeave, st.emergLeave, st.matLeave, st.medLeave);
        }
        fclose(fptr_leave);
        fclose(fptr_tempLeave2);
        fclose(fptr_leave2);
        remove("leaveDetails.txt");
        rename("templeave.txt", "leaveDetails.txt");
        fclose(fptr_temp);
        fclose(fptr_staff);
        remove("staffDetails.txt");
        rename("temp.txt", "staffDetails.txt");
    }else{
        fclose(fptr_temp);
        fclose(fptr_tempLeave2);
        fclose(fptr_leave2);
        fclose(fptr_leave);
        fclose(fptr_staff);
        remove("templeave.txt");
        remove("temp.txt");
        printf("Invalid index.\n");
    }
    if (rejected){
        printf("Leave has been rejected!\n");
    }
    approverHomepage();
}

void searchDate(){
    int day, month, year;
    int matchFound = 0;
    int i = 0;
    int searchInput;
    leaves lv[100];

    while (1){
        fflush(stdin);
        printf("\nPlease enter your starting day in DD format: \n");
        scanf("%d", &day);
        fflush(stdin);
        printf("Please enter your starting month in MM format: \n");
        scanf("%d", &month);
        fflush(stdin);
        printf("Please enter your starting year in YYYY format: \n");
        scanf("%d", &year);

        if (year >= 2023 && year <= 2025){ // same function as calendar function but without current time since dates may be passed but approver still wants to look at them
            if (1 <= month || month <= 12){
                if ((1 <= day && day <= 31) && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12 )){
                    printf("Valid date!\n");
                    break;
                }else if ((1 <= day && day <= 30) && (month == 4 || month == 6 || month == 9 || month == 11)){
                    printf("Valid date!\n");
                    break;
                }else if ((1 <= day && day <= 28) && (month == 2)){
                    printf("Valid date!\n");
                    break;
                }else if ((1 <= day && day <= 29) && (year%4 == 0)){
                    printf("Valid date!\n"); // leap year
                    break;
                }else{
                    printf("Invalid date!\n");
                    continue;
                }
            }else{
                printf("Invalid date!\n");
                continue;
            }
        }else{
            printf("Invalid date!\n");
            continue;
        }
    }

    FILE *fptr_leave = fopen("leaveDetails.txt", "r");
    if (fptr_leave == NULL){
        printf("File not found!\n");
    }
    rewind(fptr_leave);
    fflush(stdin);

    while(fscanf(fptr_leave, "%d, %[^,], %[^,], %d-%d-%d, %d days\n", &lv[i].leaveStaff_ID, lv[i].typeLeave, lv[i].statusLeave, &lv[i].day, &lv[i].month, &lv[i].year, &lv[i].duration) != EOF){
        if (lv[i].day == day && lv[i].month == month && lv[i].year == year){
            matchFound = 1;
            i++;
        }
    }
    if (matchFound){
        int j = 0;
        int numberLeaveDate = 0;

        for (j = 0; j < i; j++){
            numberLeaveDate++;
        }
        printf("%d number of staff applied on that day.", numberLeaveDate);
    }else{
        printf("No leaves applied on that day!\n");
        fclose(fptr_leave);
        return;
    }
    fclose(fptr_leave);
    approverHomepage();
}

// ALL HOMEPAGES

void staffHomepage(int *s_id_ptr){
    int sHomepage_choice;
    char buff[10];

    leaves lv;
    staff st;

    while (1) {
    printf("\n-----------------------------------\n");
    printf("***WELCOME TO THE STAFF HOMEPAGE***\n");
    printf("-----------------------------------\n");
    printf("1. Apply Leaves\n");
    printf("2. View No. of Leaves Available\n");
    printf("3. View/Cancel Applied Leaves\n");
    printf("4. Delete Leaves\n");
    printf("5. Logout\n");
    printf("Please enter your choice: \n");
    fflush(stdin);
    scanf("%s", buff);
    sHomepage_choice = atoi(buff);

    switch (sHomepage_choice) {
        case 1:
            applyLeave(s_id_ptr);
        break;
        case 2: ;
            FILE *fptr_staff = fopen("staffDetails.txt", "r");
            if (fptr_staff == NULL){
                printf("File not found!\n");
                return;
            }
            while (fscanf(fptr_staff, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d", &st.staff_ID, st.staff_username, st.staff_password, st.staff_type, &st.annualLeave, &st.compLeave, &st.emergLeave, &st.matLeave, &st.medLeave)!= EOF){
                if (*s_id_ptr == st.staff_ID){
                    printf("\nAnnual Leave: %d\n", st.annualLeave);
                    printf("Compassionate Leave: %d\n", st.compLeave);
                    printf("Emergency Leave: %d\n", st.emergLeave);
                    printf("Maternity Leave: %d\n", st.matLeave);
                    printf("Medical Leave: %d\n", st.medLeave);
                    fclose(fptr_staff);
                    continue;
                }
            }
        break;
        case 3:
            summaryLeave(s_id_ptr);
        break;
        case 4:
            deleteLeave(s_id_ptr);
        break;
        case 5:
            menu();
        default:
        printf("Invalid choice.\n");
        continue;
        }
    }
}

void adminHomepage(){
    int admHomepage_choice, staffORapp;
    char buff[10], dummy_password[20];
    int type_staffCh;

    leaves lv;
    staff st;

    FILE *fptr_staff;

    while (1) {
    printf("\n-----------------------------------\n");
    printf("***WELCOME TO THE ADMIN HOMEPAGE***\n");
    printf("-----------------------------------\n");
    printf("1. Add New Staff/Approver\n");
    printf("2. Update Leave Balance\n");
    printf("3. Search Staff\n");
    printf("4. Generate Monthly Report\n");
    printf("5. Logout\n");
    printf("Please enter your choice: \n");
    fflush(stdin);
    scanf("%s", buff);
    admHomepage_choice = atoi(buff);

    switch (admHomepage_choice) {
        case 1:
            printf("Would you like to add a staff or an approver?\n");
            while (1) {
                printf("1. Staff\n");
                printf("2. Approver\n");
                printf("3. Back\n");
                fflush(stdin);
                scanf("%s", buff);
                staffORapp = atoi(buff);

                switch(staffORapp) {
                case 1: ;
                        FILE *fptr_staff = fopen("staffDetails.txt", "a+");
                        if (fptr_staff == NULL){
                            printf("File not found!\n");
                            return;
                        }

                        fflush(stdin);
                        printf("Which of the following staff are you?\n");
                        printf("1. Academic\n");
                        printf("2. Management\n");
                        printf("3. Technical\n");
                        printf("4. Administrative\n");
                        scanf("%d", &type_staffCh);
                        if (type_staffCh == 1){
                            strcpy(st.staff_type, "Academic");
                        }else if (type_staffCh == 2){
                            strcpy(st.staff_type, "Management");
                        }else if (type_staffCh == 3){
                            strcpy(st.staff_type, "Technical");
                        }else if (type_staffCh == 4){
                            strcpy(st.staff_type, "Administrative");
                        }else{
                            printf("Invalid option.\n");
                            return;
                        }

                        fflush(stdin);
                        printf("Enter a username: \n");
                        scanf("%[^\n]", st.staff_username);

                        rewind(fptr_staff);
                        staff currSt;
                        while (fscanf(fptr_staff, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d\n", &currSt.staff_ID, currSt.staff_username, currSt.staff_password, currSt.staff_type, &currSt.annualLeave, &currSt.compLeave, &currSt.emergLeave, &currSt.matLeave, &currSt.medLeave) == 9) {
                            if (strcmp(currSt.staff_username, st.staff_username) == 0) {
                                printf("Username already exists, try a different one.\n");
                                fclose(fptr_staff);
                                adminHomepage();
                            }
                        }

                        while (1){
                            fflush(stdin);
                            printf("Enter a password: \n");
                            scanf("%s", dummy_password);
                            if (strlen(dummy_password) < 8 || strlen(dummy_password) > 20 || strchr(dummy_password, ' ') != NULL) {
                                printf("Invalid password, must be between 8 and 20 characters and cannot contain spaces.\n");
                                continue;
                            }else{
                                fflush(stdin);
                                printf("Confirm your password: \n");
                                scanf("%s", st.staff_password);
                                if (!strcmp(st.staff_password, dummy_password)){
                                    st.staff_ID = incrementOFStaffID();
                                    st.annualLeave = 16;
                                    st.compLeave = 7;
                                    st.emergLeave = 3;
                                    st.matLeave = 98;
                                    st.medLeave = 22;
                                    fprintf(fptr_staff, "%d, %s, %s, %s, %d, %d, %d, %d, %d\n", st.staff_ID, st.staff_username, st.staff_password, st.staff_type, st.annualLeave, st.compLeave, st.emergLeave, st.matLeave, st.medLeave);
                                    rewind(fptr_staff);
                                    printf("Staff registered successfully with ID %d.\n", st.staff_ID);
                                    int *s_id_ptr = &st.staff_ID;
                                    fclose(fptr_staff);
                                    int admStApplyLeave;
                                    printf("Would you like to apply for leave?\n");
                                    printf("1. Yes\n");
                                    printf("Anything else to go back to homepage\n");
                                    scanf("%d", &admStApplyLeave);
                                    if (admStApplyLeave == 1){
                                        applyLeave(s_id_ptr);
                                    }else{
                                        fclose(fptr_staff);
                                        adminHomepage();
                                    }
                                    break;
                                }else{
                                    printf("Passwords do not match!\n");
                                    continue;
                                }
                            }
                        }
                break;
                case 2:
                    registerApprover();
                break;
                case 3:
                    adminHomepage();
                break;
                default:
                    printf("Invalid choice.\n");
                    continue;
                    }
                }
        break;
        case 2:
            updateLeaves();
        break;
        case 3:
            searchStaffLeaves();
        break;
        case 4:
            generateReport();
        break;
        case 5:
            menu();
        default:
            printf("Invalid choice.\n");
        continue;
        }
    }
}

void approverHomepage(){
    int appHomepage_choice;
    char buff[10];

    while (1) {
    printf("\n--------------------------------------\n");
    printf("***WELCOME TO THE APPROVER HOMEPAGE***\n");
    printf("--------------------------------------\n");
    printf("1. Approve Leaves\n");
    printf("2. Reject Leaves\n");
    printf("3. Search Leave Dates\n");
    printf("4. Logout\n");
    printf("Please enter your choice: \n");
    fflush(stdin);
    scanf("%s", buff);
    appHomepage_choice = atoi(buff);

    switch (appHomepage_choice) {
        case 1:
            approveLeaves();
        break;
        case 2:
            rejectLeaves();
        break;
        case 3:
            searchDate();
        break;
        case 4:
            menu();
        default:
            printf("Invalid choice.\n");
        continue;
        }
    }
}

int menu() {
    int menu_choice;
    char buff[10];

    while (1) {
    printf("\n------------------------------------------------\n");
    printf("***WELCOME TO THE APU LEAVE MANAGEMENT SYSTEM***\n");
    printf("------------------------------------------------\n");
    printf("1. Admin Login\n");
    printf("2. Staff Login\n");
    printf("3. Staff Registration\n");
    printf("4. Approver Login\n");
    printf("5. Feedback\n");
    printf("6. Terms & Conditions\n");
    printf("7. Exit\n");
    printf("Please enter your choice: \n");
    fflush(stdin);
    scanf("%s", buff);
    menu_choice = atoi(buff);

    switch (menu_choice) {
        case 1:
            adminLogin();
        break;
        case 2:
            staffLogin();
        break;
        case 3:
            registerStaff();
        break;
        case 4:
            approverLogin();
        break;
        case 5:
            system("start https://docs.google.com/forms/d/e/1FAIpQLSfuXAv-LaBdEyGC7hbACPg-wiv7yBt1cTk0svqLSBQcHI-ygw/viewform?usp=sf_link"); // redirect user to feedback form on browser
        continue;
        case 6: ;
            char buffer[255];

            FILE *fptr_readme = fopen("readme.txt", "r");

            if(fptr_readme == NULL) {
                printf("File not found!\n");
                return;
            }

            while(fgets(buffer, 255, fptr_readme)) {
                printf("\n%s", buffer);
            }

            fclose(fptr_readme);
        continue;
        case 7:
            exit(0);
        default:
            printf("Invalid choice.\n");
        continue;
        }
    }
}

int main(){
    menu();
    return 0;
}
