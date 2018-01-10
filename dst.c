/*C program to validate date and time  (Check date & time  is valid or not). and apply Daylight Saving as per north america DST shedule*/
/*
North America 
DST Start : 2nd Sunday of March
            so at 2:00Am add 1 hour to Actual local time so new Local time became 3:00AM and this continue uptill 2:00 AM of 1st sunday of November  
Dst End : 1st Sunday of November  
             so at 2:00AM minus 1 hour from new local time  so local actual time become 1:00 AM
*/

 
#include <stdio.h>

int dayofweek(int d, int m, int y); 
void check(int dd,int mm,int yy, int hh,  int mn);
 
int main()
{
    int dd,mm,yy,hh,mn;
    //check year
    while(1)
    {
    	printf("Enter date (DD/MM/YYYY format): ");
        scanf("%d/%d/%d",&dd,&mm,&yy);
        printf("Enter time (hh:mm format): ");
        scanf("%d:%d",&hh,&mn);
    	check(dd,mm,yy,hh,mn);
	}
 
    return 0;    
}

void check(int dd,int mm,int yy,int hh,int mn)
{
	int dow;
	static int count2,count1;
	//check hh
	if(hh > 0 && hh <= 24)
	{
		printf("hh is valid.\n");
		if(mn >=0 && mn <= 60)
		{
			printf("mn is valid.\n");
		}
		else
		{
			printf("mn is not valid.\n");
		}
	}
	else
	{
		printf("hh is not valid.\n");
	}
	
	
	if(yy>=1900 && yy<=9999) //check year is valid or not
    {
        
        if(mm>=1 && mm<=12) //check month is valid or not
        {
            //check days is valid or not
            if( ((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12)) || ((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11)) || ((dd>=1 && dd<=28) && (mm==2)) || (dd==29 && mm==2 && (yy%400==0 ||(yy%4==0 && yy%100!=0))) )
            {
			    printf("Date is valid.\n");
                if(mm==3) //check month is march or not
                {
                	printf("Month is March.\n");
                	dow = dayofweek(dd,mm,yy);
                	printf("Day of Week = %d\n",dow);
                	if(dow==0) // check day of week is sunday or not 
                	{
                		count2++;
                		printf("count2=%d\n",count2);
                		if(count2 == 2) // check if 2nd sunday or not
                		{
                			printf("count2 is 2 add 1 hour dst at 2 Am \n");
                			if(hh== 2 && mn == 00) // check 2:00 AM or not
                			{
                				hh=3;mn=00; // add 1 hour to local time 
                				printf("hh:mn=%d:%d\n",hh,mn);
							}
						}
					}
				}
				else if(mm==11) // check if month is november or not
				{
					printf("Month is November.\n");
					dow = dayofweek(dd,mm,yy);
                	printf("Day of Week = %d\n",dow);
                	if(dow==0) // check if day of the week sunday or not
                	{
                		count1++;
                		printf("count1=%d\n",count1);
                		if(count1 == 1) // check if first sunday or not
                		{
                			printf("count1 is 1 remove one hour dst at 2 Am \n");
                			if(hh==2 && mn == 00) // check time 2:00 AM or not 
                			{
                				hh=1;mn=00; // Remove 1 hour from local time 
                				printf("hh:mn=%d:%d\n",hh,mn);	
							}
						}
					}
				}	
			}
            else
            {
            	printf("Date is not Valid.\n");
			}
        }
        else
        {
            printf("Month is not valid.\n");
        }
    }
    else
    {
        printf("Year is not valid.\n");
    }
}

/*
Function Name : dayofweek
input argument : date in dd/mm/yy forrmat in int data type
return type : int
description : this function return 0 for sun, 1 for mon , 2 for tues , 3 for wed, 4 for thu , 5 for fri and 6 for sat; 
*/

int dayofweek(int d, int m, int y)
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    return ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}
