//01/24/2025 Thomas Comer CS-210 Project One
//This program will output 2 clocks, a 12 hour and a 24 hour clock, and allow the user to change the time of the clocks through hours, minutes and second increments. 

#include <iostream>
#include <iomanip> //allows for use of setfill for formatting the visuals of the clocks
#include <ctime> //allows the program to reference the local machine's current time before the user changes any of the time functions.
using namespace std;

//function to create a visual layout for the 2 clocks with asterisks and padding

class Clock { //Deckares a class for use throughout the program related to clock functions, will be used for both clocks 
public: //Declares upcoming variables as public
	int hour;
	int minute;
	int second; //Declares 3 int variables for use of the clock's time
	int hour12; //int for displaying the 12 hour clock's hours as 1-12 based on the 24 hour clock as input, also for displaying hour 0 as 12
	string afternoon; //string for if it is am or pm
	Clock() { //Constructor for the clock's object
		time_t systemTime = time(0); //creates a variable that allows the clocks to begin with the current time of the system the clocks are running on. Uses the value of seconds since the UNIX time epoch. Innitializes as 0.
		tm* local = localtime(&systemTime); //uses the above variable to reference the unix time epoch and the current localtime of the system to create a calander variable from ctime that the clocks will reference for initialization. Note that this uses UTC time, which for most users is not their timezone.
		hour = local->tm_hour; //initializes hour to the local time's hour
		minute = local->tm_min;//initializes hour to the local time's minute
		second = local->tm_sec; //initializes hour to the local time's second
		if (hour > 12) { //loops the hour value when past 24 for the 12 hour clock
			hour12 = hour - 12;
			afternoon = "P.M.";
		}
		else if (hour == 0) { //sets the 12 hour clock's hours to 12 when it is 0 on the 24 hour clock
			hour12 = 12;
			afternoon = "A.M.";
		}
		else { //if neither condition is met for changing the 12 hour clock, sets the 12 hour clock's hours to the value of the 24 hour clock
			hour12 = hour;
			afternoon = "A.M.";
		}
	}
	void changeHour(int changeH) { //Uses user input for changing the current hour to something else.
		hour += changeH; //changes the hour value by the amount requested
		if (hour >= 24) { //loops the hour value when past 24 
			hour -= 24;
		}
		if (hour > 12) { //loops the hour value when past 24 for the 12 hour clock
			hour12 = hour - 12;
			afternoon = "P.M.";
		}
		else if (hour == 0) { //sets the 12 hour clock's hours to 12 when it is 0 on the 24 hour clock
			hour12 = 12;
			afternoon = "A.M.";
		}
		else { //if neither condition is met for changing the 12 hour clock, sets the 12 hour clock's hours to the value of the 24 hour clock
			hour12 = hour + 0;
			afternoon = "A.M.";
		}
	}
	void changeMinute(int changeM) { //Uses user input for changing the current minute to something else.
		minute += changeM;  //changes the minute value by the amount requested
		if (minute >= 60) {  //loops the minute value when past 60
			int changeH = minute / 60; //for changing the hour value when minutes have to loop over
			minute -= 60 * changeH;
			changeHour(changeH); //uses the void changeHour previously defined
		}
	}

	void changeSecond(int changeS) { //Uses user input for changing the current second to something else.
		second += changeS;  //changes the second value by the amount requested
		if (second >= 60) {  //loops the second value when past 60
			int changeM = second / 60; //for changing the minute value when seconds have to loop over
			second -= 60 * changeM;
			changeMinute(changeM); //uses the void changeMinute previously defined
		}
	}

};

void displayClock(Clock clock) { //Function for the display of the 2 clocks
	for (int i = 0; i < 25; i++) { //asterisks for the top border of the 12 hour clock
		cout << "*";
	}
	cout << "\t"; //spacing between the clocks 
	for (int i = 0; i < 25; i++) { //asterisks for the top border of the 24 hour clock
		cout << "*";
	}
	cout << endl; //newline
	cout << "*\t12-Hour Clock\t*\t*\t24-Hour Clock\t*" << endl; // heading for the two clocks
	cout << "*\t" << setw(2) << setfill('0') << clock.hour12 << ":" << setw(2) << setfill('0') << clock.minute << ":" << setw(2) << setfill('0') << clock.second << " " << clock.afternoon << "\t*\t"; //12-hour clock display. The setfill is for if the numbers are ever single digit, so that we always display a 0 in the tenth place if that occurs
	cout << "*\t" << setw(2) << setfill('0') << clock.hour << ":" << setw(2) << setfill('0') << clock.minute << ":" << setw(2) << setfill('0') << clock.second << "\t*" << endl; //24-hour clock display. The setfill is for if the numbers are ever single digit, so that we always display a 0 in the tenth place if that occurs
	for (int i = 0; i < 25; i++) { //asterisks for the bottom border of the 12 hour clock
		cout << "*";
	}
	cout << "\t"; //spacing between the clocks 
	for (int i = 0; i < 25; i++) { //asterisks for the bottom border of the 24 hour clock
		cout << "*";
	}
	cout << endl; //newline
}
void displayOptions() { //Function for the display of the 4 options the user has after seeing the clocks.
	cout << endl << "\t\t"; //newline and spacing for the options box
	for (int i = 0; i < 25; i++) { //asterisks for the top border of the options box
		cout << "*";
	}
	cout << endl; //newline
	cout << "\t\t* 1 - Add One Hour\t*" << endl;  //option to add one hour
	cout << "\t\t* 2 - Add One Minute\t*" << endl;  //option to add one minute
	cout << "\t\t* 3 - Add One Second\t*" << endl;  //option to add one second
	cout << "\t\t* 4 - Exit Program\t*" << endl;  //option to exit program
	cout << "\t\t"; //spacing for the bottom of the options box
	for (int i = 0; i < 25; i++) { //asterisks for the bottom border of the options box
		cout << "*";
	}
	cout << endl; //newline
}

void userinput(int input, Clock clock) {
	while (input != 4) {  //Loop continues until user chooses 4th option
		displayClock(clock);  //Displays clocks
		displayOptions();  //Displays menu
		cin >> input;  //Takes user input
		switch (input) {  //Switch statement based on what the user input
		case 1:  //User chose option 1
			clock.changeHour(1);  //Adds one hour to the clock
			break;  //Breaks loop
		case 2:  //User selects add one minute
			clock.changeMinute(1);  //Adds one minute to 12-hour clock
			break;  //Breaks loop
		case 3:  //User selects add one second
			clock.changeSecond(1);  //Adds one second to 12-hour clock
			break;  //Breaks loop
		case 4:  //User selects to exit program
			cout << "Exiting Program" << endl;  //Outputs exit message
			break;  //Breaks loop
		default:  //Default in case user enters invalid option
			cout << "Invalid option. Please choose a valid option from the menu" << endl;  //Outputs error message
		}
	}
}

int main() {
	Clock clock;
	int input = 0;  //int for user input
	userinput(input, clock); //function that reads the users input and output's the clocks to the user based on their input.
	return 0;
}