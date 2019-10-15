#include <iostream> // library for input output
#include <string> // library for getline
using namespace std; //standard namespace for cout, cin and endl

//defining methods
void printMonth(int y, int m); // to print and the month
void printYear(int y); // to print a year
bool isLeapYear(int y); // checks if year is a leap Year
int FirstOfTheMonth(int y, int m); // finds the first of the month
int NumberOfDays(int y, int m); // returns the number of days of a month
string Month(int m); // for string output of the month
void spaces(int s); // to print out the spaces for alignment of the dates

int main(){  // this method is good
	int y; // variable for year
	int m; // variable for month
	cout<<"would you like a year calender (yes or no)? : "; // output
	string year; // string variable for year
	getline(cin, year); // getting a string variable
  if(year =="yes"){ // if statemnt  to know if user wants a year calender
		cout<<"please input the year: "; // if yes input year
		cin>>y; // input
		cout<<endl; // creatting space
		if(y < 1582){ // making sure year is not before 1582
			cout<<"Please input a year thats greater than or equal to 1582 "<<endl; // output meassage if it is
			return (0);
		}else
		printYear(y); // calling printYear method
		return (0);
	}else if(year == "no"){  //  if user wants a specific month
	  	cout<<"please input the year and month (as a number): "; //output
			cin>>y;// input
			cin>>m;
			cout<<endl;
			if(y < 1582){ // making sure year is not before 1582
			cout<<"Error. Please enter a year equal to or greater than 1582."<<endl;
			return(0);
			}else{
				printMonth(y,m);// calling printMonth method
				return(0);
			}
		}else
		printf("Error");
		cout<<endl;
	}
void printYear(int y){  /// this method might be fine
	cout<<"Calender year - "<<y<<endl; // output
  for(int x = 1; x <=12; x++){ // for loop to print year which calls printMonth function 12X for each month of the year
		printMonth(y,x);
	}
}
void printMonth(int y, int m){  // print month method // printing out month problem /// this method not fine
	cout<<"=========== "<<Month(m)<< " ==========="<<endl;  //output
	cout<<"Sun Mon Tue Wed Thu Fri Sat "<<endl; // output
	int day = FirstOfTheMonth(y,m); /// to keep track of the day that the month starts on (ex mon, tue wed....etc
	int start = 1; /// counter for how many days are in the month
	int NOD = NumberOfDays(y,m); // getting the number of days from the NumnerOfDays Function
	spaces(day); // calling space funtion

	if((day == 6 && NOD>= 30) || (day == 5 && NOD>= 30)){ // if the day starts on  a sat and the month has 30 or 31 days than the month will have 6 rows of weeks intead of 5
		for(int x = 0; x<6; x++){ // for loop to maintain the number of rows the month has
 		 for(int y = day; y<7; y++){ // for loop to output the day number (ex 1st 2nd ...) and make sure it doesnt go past 7 days
 			 if(NOD == start){ // checking if number of days equals the counter
 				 cout<< " "<<start<<endl; //outputting a space for alignment of days and the last day of the month since start(counter) would equal the number of Days
 				 break; // break statement
			 }else { // else if statement if first f statement isnt true
 					 cout<<" "<<start; // else if start does not equal Number of days output a space for alignment and start(day of the month)
 						if(start<10){ // if statemnent to make spaces if day is less than 10 for alignment
 							cout<<"  ";
 						}else if(start>= 10){ // if statemnent to make spaces if day is greater than 10 for alignment
 							cout<<" ";
 						}
 					}
 			   start++; // adding 1 to start
 				}
 				day = 0; // the first of the month may start on a tue but the second row of a month will always start on a sunday. in this code 0 = sunday , 1 = monnday....6 = sat
 	  		cout<<endl; // to go to the next row of the month
    }
	}else
 for(int x = 0; x<5; x++){ // for rows     /// lines 80 - 98 do the same thing as then line 60 - 77  excepet now there is 1 row less in the month(the month doesnt start on a saturday )
	 for(int y = day; y<7; y++){ // for coloum
		 if(NOD == start){ // checking number of days
			 cout<< " "<<start<<endl;
			 break;
		   }else {
				 cout<<" "<<start; // other wise keep going
					if(start<10){
						cout<<"  ";
					}else if(start>= 10){
						cout<<" ";
					}
				}
		   start++;
		}
		day = 0;
  cout<<endl;
		 }
	 }

bool isLeapYear(int y){ // checks if the year is a leap year
	int cen = (y%100); // checking if year is divisible by 100
	int four = (y%4);// checking if year is divisible by 4
	int fourhun = (y%400);// checking if year is divisible by 400
	if (cen == 0){ // if year is divisible by 100
		if(four == 0 && fourhun == 0){ // check if its divsible by 4 and 400
			return true; // if yes its a leap year return true
		}
	}else if (cen != 0 && four == 0){ // if year is not divsible by 100 but divsible by 4 it a leap year
			return true; // return statemnt
	}else // if both if statements are false, its not a leap year
		return false; // return false
}
// source for code used in FirstOfTheMonth method is https://www.geeksforgeeks.org/tomohiko-sakamotos-algorithm-finding-day-week/
int FirstOfTheMonth(int y, int m){
	int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 }; // these values correspond to the how far ahead the following month is relative to jan (ex feb is 3 days ahead of jan on a leap year)

    // if month is jan or feb reduce year by 1 due to feb having 29 days on a leap year. in order to make sure the reads feb 29 and not jan 0
    if (m < 3)
        y -= 1;
		int a = y/4;
		int b = (y/4);
		int c = 0-y/100;
    int d = y/400;
    int e = t[m-1];
		int total = (y + a + c + d + e + 1)%7;
		//end value changed to 1 in order to always find the first of the month
   return total; // returning total

}
int NumberOfDays(int y, int m){  // returns the number of days in the month
	switch(m) { // switch case which gets the number of months and returns the number of days

		case 1: return 31; // first month has 31 days
		break;
		case 2:
		if(isLeapYear(y)){ // second month if leap year (calls leap year function)has 29 days otherwise it has 28 days
			return 29;
			break;
		}else
		return 28;
		break;
		case 3: return 31; // 3rd month has 31 days .... and so forth
		break;
		case 4: return 30;
		break;
		case 5: return 31;
		break;
		case 6: return 30;
		break;
		case 7: return 31;
		break;
		case 8: return 31;
		break;
		case 9: return 30;
		break;
		case 10: return 31;
		break;
		case 11: return 30;
		break;
		case 12: return 31;
		break;
		default:
		printf("Don't have a month to check "); // error message if none of the cases work
		break;
	}
	return 0;
}
string Month(int m){ // for fanciness , will outout the month as a string
	switch(m) { // switch case, which takes in the month and checks each case
		case 1: return "January";
		break;
		case 2: return "February";
		break;
		case 3: return "March";
		break;
		case 4: return "April";
		break;
		case 5: return "May";
		break;
		case 6: return "June";
		break;
		case 7: return "July";
		break;
		case 8: return "August";
		break;
		case 9: return "September";
		break;
		case 10: return "October";
		break;
		case 11: return "November";
		break;
		case 12: return "December";
		break;
		default:
		printf("Don't have a month to check "); // error message if none of the cases work
		break;
	}
	return 0; // return statemnt
}
void spaces(int s){  // this method will create the number of spaces required for the month to start on (lets say tues) or any other day of the week
	for(int x = 0; x< s; x++){
		cout<<" "; // outputting space
		cout<<"   "; // output space
	}
}
/// end of code
