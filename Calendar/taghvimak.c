#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COLOR_RESET  "\033[0m"  
#define BOLD         "\033[1m"
#define UNDER_LINE   "\033[4m"

#define COLOR_GRAY   "\033[0;30m"
#define COLOR_RED    "\033[0;31m"
#define COLOR_GREEN  "\033[0;32m"
#define COLOR_YELLOW "\033[0;33m"  
#define COLOR_BLUE   "\033[0;34m"
#define COLOR_PURPLE "\033[0;35m" 

#define BACK_GROUND_RED    "\033[0;41m"
#define BACK_GROUND_GREEN  "\033[0;42m"
#define BACK_GROUND_YELLOW "\033[0;43m"
#define BACK_GROUND_BLUE   "\033[0;44m"
#define BACK_GROUND_PURPLE "\033[0;45m"

void shamsiToGregorian();
void gregorianToLunar();

int daysInShamsiMonth[] = {0, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29, 29};
int sumShamsi[] = {31, 62, 93, 124, 155, 186, 216, 246, 276, 306, 336, 365};
int gregorianDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char *week_days_shamsi[] = {"Shanbeh", "Yekshanbeh", "Doshanbeh", "Seshanbeh", "Chaharshanbeh", "Panjshanbeh", "Jomeh"};

void print_menu() {
    printf("[0] "COLOR_PURPLE">>>"COLOR_RESET" Quit\n");
    printf("[1] "COLOR_PURPLE">>>"COLOR_RESET" Calendar\n");
    printf("[2] "COLOR_PURPLE">>>"COLOR_RESET" Age\n");
    printf("[3] "COLOR_PURPLE">>>"COLOR_RESET" Conversion\n");
    printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");    
    printf("Select Option:");
}

int isLeapYear(int year) {
if((year % 4 == 0  &&  year % 100 != 0) || year % 400 == 0)
  return 1;
else
  return 0;
}

int calculateStartingDay(int year, int month) 
{
    int startingDay = ((year * 365) + (year / 4) + 1) % 7;

    if (year >= 1206 && year <= 1218)
    {
        startingDay += 2;
    }

    if (year >= 1208 && year <= 1218 && year != 1211 && year != 1215)
    {
        startingDay = (startingDay - 1) % 7;
    }

    if (year == 1219)
    {
        startingDay = (startingDay + 2) % 7;
    }

    if (year >= 1220 && year < 1300)
    {
        startingDay = (startingDay + 1) % 7;
    }

    for (int i = 1; i < month; i++)
    {
        startingDay = (startingDay + daysInShamsiMonth[i]) % 7;
    }

    return startingDay;
}


void printCalendar(int month, int year) 
{
    int day;
    int startingDay = calculateStartingDay(year, month);

    switch (month) {
        case 1:
            printf(COLOR_RED BOLD"\t\t     FARVARDIN"COLOR_RESET);
            break;
        case 2:
            printf(COLOR_RED BOLD"\t\t    ORDIBEHESHT"COLOR_RESET);
            break;
        case 3:
            printf(COLOR_RED BOLD"\t\t      KHORDAD"COLOR_RESET);
            break;
        case 4:
            printf(COLOR_RED BOLD"\t\t        TIR"COLOR_RESET);
            break;
        case 5:
            printf(COLOR_RED BOLD"\t\t      MORDAD"COLOR_RESET);
            break;
        case 6:
            printf(COLOR_RED BOLD"\t\t     SHAHRIVAR"COLOR_RESET);
            break;
        case 7:
            printf(COLOR_RED BOLD"\t\t       MEHR"COLOR_RESET);
            break;
        case 8:
            printf(COLOR_RED BOLD"\t\t       ABAN"COLOR_RESET);
            break;
        case 9:
            printf(COLOR_RED BOLD"\t\t       AZAR"COLOR_RESET);
            break;
        case 10:
            printf(COLOR_RED BOLD"\t\t       DEY"COLOR_RESET);
            break;
        case 11:
            printf(COLOR_RED BOLD"\t\t      BAHMAN"COLOR_RESET);
            break;
        case 12:
            printf(COLOR_RED BOLD"\t\t      ESFAND"COLOR_RESET);
            break;
        default:
            printf("\t\tInvalid input!\n");
            return;
    }
    printf("\n\n");

    printf(COLOR_RED UNDER_LINE"SH\tYE\tDO\tSE\tCH\tPA\tJO\n"COLOR_RESET);

    int dayCounter = 0;
    for(int i = 0 ; i < startingDay ; i++){
        printf("\t");
        dayCounter++;
    }

    for(day = 1 ; day <= daysInShamsiMonth[month] ; day++){
        printf("%d\t", day);
        dayCounter++;

        if(dayCounter == 7){
            dayCounter = 0;
            printf("\n");
        }
    }
    printf("\n\n");
}

void calculateAge(int birth_year, int birth_month, int birth_day, int currentYear, int currentMonth, int currentDay)
{
    int gregorianYear, gregorianMonth, gregorianDay;

    int age_years = currentYear - birth_year;
    int age_months = currentMonth - birth_month;
    int age_days = currentDay - birth_day;

    // if the current day is earlier than the birthday
    if (age_days < 0)
    {
        age_months--;
        age_days += daysInShamsiMonth[currentMonth];
    }

    // if the current month is earlier than the birth month
    if (age_months < 0)
    {
        age_years--;
        age_months += 12;
    }

    int days_passed = 0;
    
    while (birth_day != currentDay || birth_month != currentMonth || birth_year != currentYear)
    {
        days_passed++;

        currentDay--;
        
        // correcting tday's date if needed
        if (currentDay == 0) {
            currentMonth--;
            
            if (currentMonth == 0) {
                currentYear--;
                currentMonth = 12;
            }
            
            // the last day of the previous month
            if (currentMonth == 1 || currentMonth == 3 || currentMonth == 5 || currentMonth == 7 || currentMonth == 8 || currentMonth == 10 || currentMonth == 12)
                currentDay = 31;
            else if (currentMonth == 4 || currentMonth == 6 || currentMonth == 9 || currentMonth == 11)
                currentDay = 30;
            else {
                if ((currentYear % 4 == 0 && currentYear % 100 != 0) || currentYear % 400 == 0)
                    currentDay = 29;
                else
                    currentDay = 28;
            }
        }
    }

    int startingDay = calculateStartingDay(birth_year, birth_month);

    int i = (startingDay + birth_day - 1) % 7;

    
    // Print the age result
    printf("Your Age:                     ");
    printf(COLOR_PURPLE BOLD"%d years, %d months, %d days\n"COLOR_RESET, age_years, age_months, age_days);
              
    printf("It is equal to:               ");
    printf(COLOR_PURPLE BOLD"%d days\n"COLOR_RESET, days_passed);
           
    printf("You were born on:             ");
    printf(COLOR_PURPLE BOLD"%s\n\n"COLOR_RESET, week_days_shamsi[i]);


    shamsiToGregorian(birth_year, birth_month, birth_day, &gregorianYear, &gregorianMonth, &gregorianDay);
    printf("Your date of birth in AD:     ");
    printf(COLOR_PURPLE BOLD"%d/%.02d/%.02d\n"COLOR_RESET, gregorianYear, gregorianMonth, gregorianDay);
    printf("Your date of birth in lunar:  ");
    gregorianToLunar(gregorianYear, gregorianMonth, gregorianDay);
}

void shamsiToGregorian(int shamsiYear, int shamsiMonth, int shamsiDay,
                      int *gregorianYear, int *gregorianMonth, int *gregorianDay)
{                      
    int gYear, gMonth, dayCount;
    dayCount = shamsiDay;
    if (shamsiMonth > 1)
        // the total days passed
        dayCount = dayCount + sumShamsi[shamsiMonth - 2];

    gYear = shamsiYear + 621;
    // the difference between Solar and Gregorian calendars is 79 days
    dayCount = dayCount + 79;

    if (isLeapYear(gYear) == 1)
    {
        if (dayCount > 366)
        {
            // if there is a leap year
            dayCount = dayCount - 366;
            gYear = gYear + 1;
        }
    }
    else if (dayCount > 365)
    {
        // if not a leap year
        dayCount = dayCount - 365;
        gYear = gYear + 1;
    }

    if (isLeapYear(gYear) == 1)
        gregorianDays[1] = 29;

    gMonth = 0;
    while (dayCount > gregorianDays[gMonth])
    {
        dayCount = dayCount - gregorianDays[gMonth];
        gMonth = gMonth + 1;
    }

    *gregorianYear = gYear;
    *gregorianMonth = gMonth + 1;
    *gregorianDay = dayCount;
}

int integer(double number)
{
    if (number < 0)
        return (int)(number - 0.5);
    else 
        return (int)(number + 0.5);
}

void gregorianToLunar(int gregorianYear, int gregorianMonth, int gregorianDay)
{
    int julianCalender;

    if (gregorianYear > 1582 || (gregorianYear == 1582 && (gregorianMonth > 10 || (gregorianMonth == 10 && gregorianDay >= 15))))
    {
        julianCalender = integer((1461 * (gregorianYear + 4800 + integer((gregorianMonth - 14) / 12))) / 4)
                     + integer((367 * (gregorianMonth - 2 - 12 * integer((gregorianMonth - 14) / 12))) / 12)
                     - integer((3 * integer((gregorianYear + 4900 + integer((gregorianMonth - 14) / 12)) / 100)) / 4)
                     + gregorianDay - 32075;
    } else
    {
        julianCalender = 367 * gregorianYear
                     - integer((7 * (gregorianYear + 5001 + integer((gregorianMonth - 9) / 7))) / 4)
                     + integer((275 * gregorianMonth) / 9)
                     + gregorianDay + 1729777;
    }

    int l = julianCalender - 1948440 + 10632;
    int n = integer((l - 1) / 10631);
    l = l - 10631 * n + 354;

    int j = (integer((10985 - l) / 5316)) * (integer((50 * l) / 17719))
            + (integer(l / 5670)) * (integer((43 * l) / 15238));

    l = l - (integer((30 - j) / 15)) * (integer((17719 * j) / 50))
        - (integer(j / 16)) * (integer((15238 * j) / 43)) + 29;

    int lunarMonth = integer((24 * l) / 709);
    int lunarDay = l - integer((709 * lunarMonth) / 24);
    int lunarYear = 30 * n + j - 30;

    printf(COLOR_PURPLE BOLD"%d/%.02d/%.02d\n\n"COLOR_RESET, lunarYear, lunarMonth, lunarDay);
}


void gregorianToShamsi(int miladiYear, int miladiMonth, int miladiDay)
{
    int countDaysMiladi[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int i, summary;
    int solarYear, solarMonth, solarDay;

    summary = 0;
    for (i = 1; i < miladiMonth; i++)
    {
        // the total days in the Gregorian calendar
        summary = summary + countDaysMiladi[i - 1];
    }
    summary = summary + miladiDay;

    if (isLeapYear(miladiYear) && miladiMonth > 2)
        // if it is a leap year and the month is greater than February(2)
        summary = summary + 1;

    if (summary <= 79)
    {
        if ((miladiYear - 1) % 4 == 0)
            summary = summary + 11;
        else
            summary = summary + 10;

        
        solarYear = miladiYear - 622;

        if (summary % 30 == 0)
        {
            solarMonth = (summary / 30) + 9;
            solarDay = 30;
        }
        else
        {
            solarMonth = (summary / 30) + 10;
            solarDay = summary % 30;
        }
    }
    else
    {
        solarYear = miladiYear - 621;
        summary = summary - 79;

        if (summary <= 186)
        {
            if (summary % 31 == 0)
            {
                solarMonth = summary / 31;
                solarDay = 31;
            }
            else
            {
                solarMonth = (summary / 31) + 1;
                solarDay = summary % 31;
            }
        }
        else
        {
            summary = summary - 186;

            if (summary % 30 == 0)
            {
                solarMonth = (summary / 30) + 7;
                solarDay = 30;
            } else
            {
                solarMonth = (summary / 30) + 8;
                solarDay = summary % 30;
            }
        }
    }
    printf(COLOR_PURPLE BOLD"%d/%.02d/%.02d\n\n"COLOR_RESET, solarYear, solarMonth, solarDay);
}


int main(){

int option, choice, back;
int year, month;
int currentYear, currentMonth, currentDay;
int birth_year, birth_month, birth_day;
int shamsiYear, shamsiMonth, shamsiDay;
int gregorianYear, gregorianMonth, gregorianDay;
int miladiYear, miladiMonth, miladiDay;

printf("===========================================""\n");
printf("\n");
printf(BOLD"WELCOME\n"COLOR_RESET);
printf(BOLD"      TO THE "COLOR_RESET);
printf(COLOR_RED BOLD"CS 1402\n"COLOR_RESET);
printf(BOLD"                   CALENDAR PROJECT\n\n"COLOR_RESET);
printf("===========================================""\n");
printf("Press [1] to start:");
scanf("1");
system("cls");

    do{
        print_menu();
        scanf("%d", &option);

        switch (option){
            case 1:
                system("cls");
                printf("[0] Back to menu\n");
                printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");
                printf("Enter Year:");
                scanf("%d", &year);
                if(year == 0){
                    system("cls");
                    printf(BACK_GROUND_BLUE"Back to menu!\n"COLOR_RESET);
                    printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                    
                    break;
                }
                else if(year < 1206 || year > 1498){
                    system("cls");
                    printf(BACK_GROUND_BLUE"Invalid input!\n"COLOR_RESET);
                    printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                    
                    break;
                }
                else{
                  printf("Enter Month:");
                  scanf("%d", &month);
                  if(month == 0){
                      system("cls");
                      printf(BACK_GROUND_BLUE"Back to menu!\n"COLOR_RESET);
                      printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                      
                      break;
                  }
                  else if(month < 1 || (month > 12 && month != 0)){
                    system("cls");
                    printf(BACK_GROUND_BLUE"Invalid input!\n"COLOR_RESET);
                    printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                    
                    break;
                  }
                  else{
                  system("cls");
                  printCalendar(month, year);
                  printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                  
                  printf("[0] Back to menu!\n");
                  printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                  
                  }
                }

                while(1)
                {
                printf("Enter Year:");
                scanf("%d", &year);
                if(year == 0){
                    system("cls");
                    printf(BACK_GROUND_BLUE"Back to menu!\n"COLOR_RESET);
                    printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                    
                    break;
                }
                else if(year < 1206 || year > 1498){
                    system("cls");
                    printf(BACK_GROUND_BLUE"Invalid input!\n"COLOR_RESET);
                    printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                    
                    break;
                }
                else{
                  printf("Enter Month:");
                  scanf("%d", &month);
                  if(month == 0){
                      system("cls");
                      printf(BACK_GROUND_BLUE"Back to menu!\n"COLOR_RESET);
                      printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                      
                      break;
                  }
                  else if(month < 1 || (month > 12 && month != 0)){
                    system("cls");
                    printf(BACK_GROUND_BLUE"Invalid input!\n"COLOR_RESET);
                    printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                    
                    break;
                  }
                  else{
                  system("cls");
                  printCalendar(month, year);
                  printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                  
                  printf("[0] Back to menu!\n");
                  printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                  
                  }
                }
                }
                break;

            case 2:
                system("cls");
                printf("[0] Back to menu\n");
                printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                
                printf(COLOR_BLUE BOLD"Your date of birth >>>>\n"COLOR_RESET);

                printf("Year:");
                scanf("%d", &birth_year);
                if(birth_year == 0){
                    system("cls");
                    printf(BACK_GROUND_BLUE"Back to menu!\n"COLOR_RESET);
                    printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                    
                    break;
                }
                else if(birth_year < 1206 || birth_year > 1498){
                    system("cls");
                    printf(BACK_GROUND_BLUE"Invalid input!\n"COLOR_RESET);
                    printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                    
                    break;
                }
                else{
                  printf("Month:");
                  scanf("%d", &birth_month);
                  if(birth_month == 0){
                      system("cls");
                      printf(BACK_GROUND_BLUE"Back to menu!\n"COLOR_RESET);
                      printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                      
                      break;
                  }
                  else if(birth_month < 1 || (birth_month > 12 && birth_month != 0)){
                    system("cls");
                    printf(BACK_GROUND_BLUE"Invalid input!\n"COLOR_RESET);
                    printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                    
                    break;
                  }
                  else{
                    printf("Day:");
                    scanf("%d", &birth_day);
                    if(birth_day == 0){
                        system("cls");
                        printf(BACK_GROUND_BLUE"Back to menu!\n"COLOR_RESET);
                        printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                        
                        break;
                    }
                    else if((birth_month == 1 && birth_day > 31) || 
                            (birth_month == 2 && birth_day > 31) ||
                            (birth_month == 3 && birth_day > 31) ||
                            (birth_month == 4 && birth_day > 31) ||
                            (birth_month == 5 && birth_day > 31) ||
                            (birth_month == 6 && birth_day > 31) ||
                            (birth_month == 7 && birth_day > 30) ||
                            (birth_month == 8 && birth_day > 30) ||
                            (birth_month == 9 && birth_day > 30) ||
                            (birth_month == 10 && birth_day > 30) ||
                            (birth_month == 11 && birth_day > 30) ||
                            (birth_month == 12 && isLeapYear(birth_year) == 1 && birth_day > 30) ||
                            (birth_month == 12 && isLeapYear(birth_year) == 0 && birth_day > 29))
                    {
                    system("cls");
                    printf(BACK_GROUND_BLUE"Invalid input!\n"COLOR_RESET);
                    printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                    
                    break;
                    }
                  }  
                }
                printf(COLOR_PURPLE UNDER_LINE"Enter today's date in this format(YYYY/MM/DD):\n"COLOR_RESET);
                scanf("%d/%d/%d", &currentYear, &currentMonth, &currentDay);

                system("cls");

                calculateAge(birth_year, birth_month, birth_day, currentYear, currentMonth, currentDay);

                printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                
                printf(BOLD"<< Press [0] to go back to menu >>\n");
                scanf("%d", &back);

                system("cls");
                printf(BACK_GROUND_BLUE"Back to menu!\n"COLOR_RESET);
                printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                
                break;

            case 3:
                system("cls");
                printf("  ");
                printf(BACK_GROUND_PURPLE"<<< Welcome to the date conversion >>>\n\n");
                printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                
                printf("[0] Back to menu\n");
                printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");
                printf("Choose the type of the date you want to be converted:\n");
                printf(BOLD"Solar     ");
                printf(COLOR_PURPLE">>>"COLOR_RESET" 1\n");
                printf(BOLD"Gregorian ");
                printf(COLOR_PURPLE">>>"COLOR_RESET" 2\n");

                scanf("%d", &choice);

                if(choice == 1)
                {    
                    system("cls");
                    printf(COLOR_RED UNDER_LINE"Enter the Solar date:\n\n"COLOR_RESET);
    
                    printf("Year:");
                    scanf("%d", &shamsiYear);
                    if(shamsiYear == 0){
                        system("cls");
                        printf(BACK_GROUND_BLUE"Back to menu!\n"COLOR_RESET);
                        printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                        
                        break;
                    }
                    else if(shamsiYear < 1206 || shamsiYear > 1498){
                        system("cls");
                        printf(BACK_GROUND_BLUE"Invalid input!\n"COLOR_RESET);
                        printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                        
                        break;
                    }
                    else{
                      printf("Month:");
                      scanf("%d", &shamsiMonth);
                      if(shamsiMonth == 0){
                          system("cls");
                          printf(BACK_GROUND_BLUE"Back to menu!\n"COLOR_RESET);
                          printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                          
                          break;
                      }
                      else if(shamsiMonth < 1 || (shamsiMonth > 12 && shamsiMonth != 0)){
                        system("cls");
                        printf(BACK_GROUND_BLUE"Invalid input!\n"COLOR_RESET);
                        printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                        
                        break;
                      }
                      else{
                        printf("Day:");
                        scanf("%d", &shamsiDay);
                        if(shamsiDay == 0){
                            system("cls");
                            printf(BACK_GROUND_BLUE"Back to menu!\n"COLOR_RESET);
                            printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                            
                            break;
                        }
                        else if((shamsiMonth == 1 && shamsiDay > 31) || 
                                (shamsiMonth == 2 && shamsiDay > 31) ||
                                (shamsiMonth == 3 && shamsiDay > 31) ||
                                (shamsiMonth == 4 && shamsiDay > 31) ||
                                (shamsiMonth == 5 && shamsiDay > 31) ||
                                (shamsiMonth == 6 && shamsiDay > 31) ||
                                (shamsiMonth == 7 && shamsiDay > 30) ||
                                (shamsiMonth == 8 && shamsiDay > 30) ||
                                (shamsiMonth == 9 && shamsiDay > 30) ||
                                (shamsiMonth == 10 && shamsiDay > 30) ||
                                (shamsiMonth == 11 && shamsiDay > 30) ||
                                (shamsiMonth == 12 && isLeapYear(shamsiYear) == 1 && shamsiDay > 30) ||
                                (shamsiMonth == 12 && isLeapYear(shamsiYear) == 0 && shamsiDay > 29))
                        {
                        system("cls");
                        printf(BACK_GROUND_BLUE"Invalid input!\n"COLOR_RESET);
                        printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                        
                        break;
                        }
    
                      }  
                    }

                    system("cls");
                    printf("The Solar date you entered in Gregorian is:\n");
    
                    shamsiToGregorian(shamsiYear, shamsiMonth, shamsiDay,
                                      &gregorianYear, &gregorianMonth, &gregorianDay);
    
                    printf(COLOR_PURPLE BOLD"%d/%.02d/%.02d\n\n"COLOR_RESET, gregorianYear, gregorianMonth, gregorianDay);
    
                    printf("The solar date you entered in Lunar is:\n");
                    shamsiToGregorian(shamsiYear, shamsiMonth, shamsiDay,
                                      &gregorianYear, &gregorianMonth, &gregorianDay);
                    gregorianToLunar(gregorianYear, gregorianMonth, gregorianDay);


                    printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                    
                    printf(BOLD"<< Press [0] to go back to menu >>\n");
                    scanf("%d", &back);
    
                    system("cls");
                    printf(BACK_GROUND_BLUE"Back to menu!\n"COLOR_RESET);
                    printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                    
                    break;
                }

                else if(choice == 2)
                {
                    system("cls");
                    printf(COLOR_RED UNDER_LINE"Enter the Gregorian date:\n\n"COLOR_RESET);
                    printf("Year:");
                    scanf("%d", &miladiYear);
                    if(miladiYear == 0){
                        system("cls");
                        printf(BACK_GROUND_BLUE"Back to menu!\n"COLOR_RESET);
                        printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                        
                        break;
                    }
                    else{
                        printf("Month:");
                        scanf("%d", &miladiMonth);
                        if(miladiMonth == 0){
                            system("cls");
                            printf(BACK_GROUND_BLUE"Back to menu!\n"COLOR_RESET);
                            printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                            
                            break;
                        }
                        else{
                            printf("Day:");
                            scanf("%d", &miladiDay);
                            if(miladiDay == 0){
                                system("cls");
                                printf(BACK_GROUND_BLUE"Back to menu!\n"COLOR_RESET);
                                printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                                break;
                            }
                        }
                    }

                    system("cls");

                    printf("The Gregorian date you entered in Solar is:\n");
                    gregorianToShamsi(miladiYear, miladiMonth, miladiDay);
                    printf("the Gregorian date you entered in Lunar is:\n");
                    gregorianToLunar(miladiYear, miladiMonth, miladiDay);

                    printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");
                    printf(BOLD"<< Press [0] to go back to menu >>\n");
                    scanf("%d", &back);
    
                    system("cls");
                    printf(BACK_GROUND_BLUE"Back to menu!\n"COLOR_RESET);
                    printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                    
                    break;
                }

                else if(choice == 0)
                {
                    system("cls");
                    printf(BACK_GROUND_BLUE"Back to menu!\n"COLOR_RESET);
                    printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                    
                    break;
                }
                else
                {
                    system("cls");
                    printf(BACK_GROUND_BLUE"Invalid input!\n"COLOR_RESET);
                    printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                    
                    break;
                }

            break;
    
            case 0:
                system("cls");
                printf("Bye!\n");
                break;

            default:
                system("cls");
                printf(BACK_GROUND_BLUE"Invalid input!\n"COLOR_RESET);
                printf(COLOR_BLUE"==========================================="COLOR_RESET"\n");                
                break;
        }
                 
    }while (option != 0);

return 0;
}