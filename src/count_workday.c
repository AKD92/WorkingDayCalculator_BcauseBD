
/**********************************************************************************************************************
 *      A console program which will calculate total working days for B-cause Bangladesh Ltd.
 *      Saturdays are not included into the calculation, only days between Mon to Fri will be taken account of.
 *      Author: Ashis Kr. Das
 *********************************************************************************************************************/



#include <stdio.h>                  /* Provides IO functions */
#include <stdlib.h>                 /* Provides 'system()' function */
#include <time.h>                   /* Provides primitive functions for date/time calculation */


int main(void) {

    /* Declare necessary variables */
    time_t rawtime_x, rawtime_y;
    double dtime;
    struct tm * timeinfo;
    struct tm time_x, time_y;
    unsigned int t_wday;
    unsigned int t_friday, t_saturday;
    unsigned int daytotal;
    unsigned int i;
    unsigned int weekday_x, weekday_i, yday_a, yday_b;
    int day_x, month_x, year_x;
    int day_y, month_y, year_y;
    char strx[100], stry[100];

    /* Take input from user as two dates */
    /* First one is the starting date and the second one is the ending date */
    /* Total working days will be calculated from starting date to ending date (inclusive) */
    printf("\n** WorkDay Calculator (B-cause BD Ltd) **\n\n");
    printf("Enter starting date as MM DD YYYY : ");
    scanf("%u %u %u", &month_x, &day_x, &year_x);
    if (month_x > 12 || day_x > 31) {
        printf("Input is not valid for starting date\n");
        goto END;
    }

    printf("Enter ending date as MM DD YYYY : ");
    scanf("%u %u %u", &month_y, &day_y, &year_y);
    printf("\n");
    if (month_y > 12 || day_y > 31) {
        printf("Input is not valid for ending date\n");
        goto END;
    }

    /* Calculate day of week and day of year for starting date */
    time(&rawtime_x);
    timeinfo = localtime(&rawtime_x);
    timeinfo->tm_year = year_x - 1900;
    timeinfo->tm_mon = month_x - 1;
    timeinfo->tm_mday = day_x;
    rawtime_x = mktime(timeinfo);
    weekday_x = timeinfo->tm_wday;
    yday_a = timeinfo->tm_yday;
    time_x = *timeinfo;

    /* Calculate day of year for ending date */
    time(&rawtime_y);
    timeinfo = localtime(&rawtime_y);
    timeinfo->tm_year = year_y - 1900;
    timeinfo->tm_mon = month_y - 1;
    timeinfo->tm_mday = day_y;
    rawtime_y = mktime(timeinfo);
    yday_b = timeinfo->tm_yday;
    time_y = *timeinfo;

    dtime = difftime(rawtime_y, rawtime_x);
    if (dtime < 0.0L) {
        printf("Invalid input (ending date is past to starting date)\n");
        goto END;
    }

    /* Calculate total number of days exist between starting and ending date (inclusive) */
    daytotal = yday_b - yday_a + 1;

    /* Based on the results derived above */
    /* Start calculating total number of working days */
    /* This will be done by enumerating through total number of days */
    t_wday = 0;
    weekday_i = weekday_x;
    t_friday = t_saturday = 0;
    for(i = 0; i < daytotal; i++) {
        weekday_i = weekday_i % 7;                    /* Cerculate incrementally between 0 and 6 */
        if (weekday_i > 0 && weekday_i < 6) {         /* between Monday = 1 and Friday = 5 inclusive */
            t_wday += 1;
        }
        if (weekday_i == 5) {
            t_friday += 1;
        }
        if (weekday_i == 6) {
            t_saturday += 1;
        }
        weekday_i += 1;
    }

    /* Complete, show the calculation to the user */
    strftime(strx, 100, "%B %d, %Y", &time_x);
    strftime(stry, 100, "%B %d, %Y", &time_y);
    printf("RESULT: from %s to %s\n", strx, stry);
    printf("\t%-45s: %-3u days\n", "Number of days", daytotal);
    printf("\t%-45s: %-3u days\n", "Total working days", t_wday);
    printf("\t%-45s: %-3u days (%u Saturdays)\n",
                "Total working days (including Saturdays)", t_wday + t_saturday, t_saturday);


    END:
    system("pause");
    return 0;
}



