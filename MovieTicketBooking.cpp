// header files
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include <limits>
#include <time.h>
#include <windows.h>
#include <mysql.h>
#include <iomanip>
#include <regex>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

using namespace std;

const char * query;
MYSQL * conn;
MYSQL_RES * res;
MYSQL_ROW row;
int choice;
int enteredPin;
char ans;
std::regex pattern( "([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

//Class definition for ticket
class ticket {
  public: int movieid;
  string name;
  string cno;
  string email;
  int time;
  int seatingclass;
  int ticket;
  int pin;
  int date;
}
t; //object definition for ticket

// Function to execute a query and return results
//////////////////////////////////////////////////////////
//
//Function Name:    MYSQL_RES executeQuery
//Description:      execute query in mysql database
//Input:            mysql connection, query
//Output:           mysql result
//Date:             09/12/2023
//Author:           Karan Sambhaji Babar
//
//////////////////////////////////////////////////////////
MYSQL_RES * executeQuery(MYSQL * conn, const char * query) {
  if (mysql_query(conn, query)) {
    cerr << "Error: " << mysql_error(conn) << endl;
    return nullptr;
  } else {
    MYSQL_RES * res = mysql_store_result(conn);
    return res;
  }
}

//////////////////////////////////////////////////////////
//
//Function Name:    Void currentmovie
//Description:      select current movielist from database and print those data in output screen
//Input:            -
//Output:           -
//Date:             09/12/2023
//Author:           Karan Sambhaji Babar
//
//////////////////////////////////////////////////////////
void currentmovie()
{

    query = "SELECT * FROM movielist";
    // Call the function to execute and print the query result
    res = executeQuery(conn, query);
    std::cout << "\t\t\t\t" << std::setw(10) << "Movie ID" << std::setw(20) << "Title" << std::setw(20) << "Language"<< std::setw(20) << "Description"<< std::endl;
    std::cout << std::setfill(' ') << std::setw(45) << "" << std::endl;

    while ((row = mysql_fetch_row(res))) {
      std::cout << "\t\t\t\t" << std::setw(10) << row[0] << std::setw(25) << row[1]<< std::setw(10) << row[3]<< std::setw(30) << row[2] << std::endl;
    }
}

//////////////////////////////////////////////////////////
//
//Function Name:    Void upcoming
//Description:      select upcoming movielist from database and print those data in output screen
//Input:            -
//Output:           -
//Date:             09/12/2023
//Author:           Karan Sambhaji Babar
//
//////////////////////////////////////////////////////////
void upcoming() {
  cout << "\t\t\t\t upcoming movie list\n\n";

  query = "SELECT * FROM upcoming";
  // Call the function to execute and print the query result
  res = executeQuery(conn, query);
  std::cout << "\t\t\t\t" << std::setw(10) << "Date" << std::setw(20) << "Movie Name" << std::setw(20) << "Language" << std::setw(20) << "Description" << std::endl;
  std::cout << std::setfill(' ') << std::setw(45) << "" << std::endl;

  while ((row = mysql_fetch_row(res))) {
    std::cout << "\t\t\t\t" << std::setw(10) << row[0] << std::setw(20) << row[1] << std::setw(20) << row[2] << std::setw(20) << row[3] << std::endl;
  }
}

//////////////////////////////////////////////////////////
//
//Function Name:    Void menu
//Description:      display menu options in output screen
//Input:            -
//Output:           -
//Date:             09/12/2023
//Author:           Karan Sambhaji Babar
//
//////////////////////////////////////////////////////////
void menu() {
  cout << "\n\t\t\t =================================================================";
  cout << "\n\t\t\t\t\t\tMOVIE TICKET BOOKING SYSTEM";
  cout << "\n\t\t\t =================================================================";
  cout << "\n";
  cout << "\n\t\t\t\t WELCOME CUSTOMER HOW CAN I HELP YOU!!!!!!"; //Menu for the user
  cout << "\n\n\t\t\t\t <1> BOOK TICKET ";
  cout << "\n\t\t\t\t <2> CURRENTLY RUNNING MOVIE";
  cout << "\n\t\t\t\t <3> UPCOMING MOVIE";
  cout << "\n\t\t\t\t <4> ADMIN USER";
  cout << "\n\t\t\t\t <5> ABOUT US ";
  cout << "\n\t\t\t\t <6> EXIT \n\n";
  cout << "\t\t\t\tEnter Your Choice :" << "\t";
}

//////////////////////////////////////////////////////////
//
//Function Name:    Void admin_menu
//Description:      display admin menu options in output screen
//Input:            -
//Output:           -
//Date:             09/12/2023
//Author:           Karan Sambhaji Babar
//
//////////////////////////////////////////////////////////
void admin_menu() {
  cout << "\n\t\t\t =================================================================";
  cout << "\n\t\t\t\t\t\tWelcome Admin User ";
  cout << "\n\t\t\t =================================================================";
  cout << "\n\t\t\t\t "; //Menu for the user
  cout << "\n\n\t\t\t\t <1> INSERT NEW MOVIE ";
  cout << "\n\t\t\t\t <2> UPDATE EXISITING MOVIE";
  cout << "\n\t\t\t\t <3> DELETE EXISITING MOVIE";
  cout << "\n\t\t\t\t <4> EXIT \n\n";
  cout << "\t\t\t\tEnter Your Choice :" << "\t";
}

//////////////////////////////////////////////////////////
//
//Function Name:    int generateRandomPin
//Description:      generate a random 4-digit ticket id
//Input:            -
//Output:           int
//Date:             09/12/2023
//Author:           Karan Sambhaji Babar
//
//////////////////////////////////////////////////////////
int generateRandomPin() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution < > dis(1000, 9999);
  return dis(gen);
}

//////////////////////////////////////////////////////////
//
//Function Name:    string showclass
//Description:      movie class
//Input:            int
//Output:           string
//Date:             09/12/2023
//Author:           Karan Sambhaji Babar
//
//////////////////////////////////////////////////////////
string showclass(int choice) {
  if (choice == 1) {
    return "Normal Class";
  } else if (choice == 2) {
    return "Gold Class";
  }
}

//////////////////////////////////////////////////////////
//
//Function Name:    void ticketcost
//Description:      ticket cost
//Input:            int, int
//Output:           -
//Date:             09/12/2023
//Author:           Karan Sambhaji Babar
//
//////////////////////////////////////////////////////////
void ticketcost(int ticket, int choice) {
  if (choice == 1) {
    std::cout << ticket * 100;
  } else if (choice == 2) {
    std::cout << ticket * 150;
  }
}

//////////////////////////////////////////////////////////
//
//Function Name:    void admin_choice
//Description:      admin choice
//Input:            -
//Output:           -
//Date:             09/12/2023
//Author:           Karan Sambhaji Babar
//
//////////////////////////////////////////////////////////
void admin_choice() {
  admin_menu();
  while ((cin >> choice) && (choice < 1 || choice > 5)) {
    cout << "\n\t\t\t\tInvalid selection - Please input 1 to 4 only.\n\t\t\t\tPlease Reenter correct Choice :";
    cin.clear();
    cin.ignore(numeric_limits < streamsize > ::max(), '\n');
  }

  if (choice == 1) {
    string name, date, language, description;
    cout << "\n\n\t\t\t\t Movie Name: ";
    cin >> name;
    cout << "\n\t\t\t\t Date:";
    cin >> date;
    cout << "\n\t\t\t\t  Language:";
    cin >> language;
    cout << "\n\t\t\t\t Description:";
    cin >> description;
    cout << "\n\t\t\t\t  EXIT \n\n";

    std::string result = "INSERT INTO `upcoming` (`date`, `movie_name`, `language`, `description`) VALUES ('" + date + "', '" + name + "', '" + language + "', '" + description + "')";
    res = executeQuery(conn, result.c_str());
    cout << "successfully Insert in database";

  } else if (choice == 2) {
    string mname, date, language, description;
    upcoming();
    cout << "Please Enter Movie Name Which You Want to update:";
    cin >> mname;

    cout << "\n\t\t\t\t Date:";
    cin >> date;
    cout << "\n\t\t\t\t  Language:";
    cin >> language;

    std::string result = "UPDATE `upcoming` SET `date`='" + date + "', `language`='" + language + "' WHERE `movie_name`='" + mname + "';";
    res = executeQuery(conn, result.c_str());
    cout << "successfully updated in database\n";
  } else if (choice == 3) {
    string mname;
    upcoming();
    cout << "Please Enter Movie Name Which You Want to delete:";
    cin >> mname;
    std::string result = "DELETE FROM `upcoming` WHERE `movie_name`='" + mname + "';";
    res = executeQuery(conn, result.c_str());
    cout << "successfully deleted from database\n";
  }
}

//////////////////////////////////////////////////////////
//
//Function Name:    string showtiming
//Description:      show timing
//Input:            int
//Output:           string
//Date:             09/12/2023
//Author:           Karan Sambhaji Babar
//
//////////////////////////////////////////////////////////
string showtiming(int choice) {
  if (choice == 1) {
    return "9.00 AM";
  } else if (choice == 2) {
    return "12.00 PM";
  } else if (choice == 3) {
    return "3.00 PM";
  } else if (choice == 4) {
    return "6.00 PM";
  }
}

//////////////////////////////////////////////////////////
//
//Function Name:    bool payment
//Description:      payment
//Input:            int
//Output:           bool
//Date:             09/12/2023
//Author:           Karan Sambhaji Babar
//
//////////////////////////////////////////////////////////
bool payment(int amount) {
  std::string cardNumber, cardHolder, expirationDate, cvv;
  while (true) {
    std::cout << "\n\t\t\t\tEnter Card Number: ";
    std::cin >> cardNumber;

    if (cardNumber.length() == 16) {
      break; // Exit the loop if the card number is valid
    } else {
      std::cout << "\n\t\t\t\tInvalid card number. Please type 16 digit card number try again." << std::endl;
      // Clear the input buffer to avoid infinite loop on input failure
      std::cin.clear();
      std::cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
    }
  }
  std::cout << "\n\t\t\t\tEnter Card Holder Name: ";
  std::cin.ignore(); // To clear the newline character from the buffer
  std::getline(std::cin, cardHolder);

  std::cout << "\n\t\t\t\tEnter Expiration Date (MM/YY): ";
  std::cin >> expirationDate;

  while (true) {
    std::cout << "\n\t\t\t\tEnter CVV: ";
    std::cin >> cvv;

    if (cvv.length() == 3) {
      break; // Exit the loop if the CVV is valid
    } else {
      std::cout << "\n\t\t\t\tInvalid CVV, length should be 3 digit. Please try again." << std::endl;
      // Clear the input buffer to avoid infinite loop on input failure
      std::cin.clear();
      std::cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
    }
  }
  return true;
}

//////////////////////////////////////////////////////////
//
//Function Name:    void main_menu
//Description:      main menu
//Input:            -
//Output:           -
//Date:             09/12/2023
//Author:           Karan Sambhaji Babar
//
//////////////////////////////////////////////////////////
void main_menu() {
  do {
    menu();
    while ((cin >> choice) && (choice < 1 || choice > 6)) {
      cout << "\n\t\t\t\tInvalid choice - Please input 1 to 6 only.\n\t\t\t\tPlease Reenter correct Choice :";
      cin.clear();
      cin.ignore(numeric_limits < streamsize > ::max(), '\n');
    }
  }
  while (ans == 'y');

  if (choice == 1) {
    currentmovie();
    cout << "\n\t\t\t\tEnter Your Choice :" << "\t";

    while ((cin >> t.movieid) && (t.movieid < 1 || t.movieid > 2)) {
      cout << "Invalid selection - Please input 1 to 2 only.\n";
      cout << "\n\t\t\t\tEnter Your Choice :" << "\t";

      cin.clear();

      cin.ignore(numeric_limits < streamsize > ::max(), '\n');
    }
    while ((row = mysql_fetch_row(res))) {
      int k = std::atoi(row[0]);
      if (k == t.movieid)
        t.email = row[1];
    }
    cout << t.email;
    system("CLS");
    cout << "\n\n\t\t\t\t Select the Date: ";
    cout << "\n\t\t\t\t 1. 01/02/2024";
    cout << "\n\t\t\t\t 2. 02/02/2024";
    cout << "\n\t\t\t\t 3. 03/02/2024";
    cout << "\n\t\t\t\t 4. 04/02/2024"; //Timings of the show
    cout << "\n\n\t\t\t\t Please select the Date: ";
    //
    while ((cin >> t.date) && (t.date < 1 || t.date > 4)) {
      cout << "Invalid selection - Please input 1 to 4 only.\n";
      cout << "\n\t\t\t\tEnter Your Choice :" << "\t";

      cin.clear();

      cin.ignore(numeric_limits < streamsize > ::max(), '\n');
    }

    cout << "\n\n\t\t\t\t Select the timings: ";
    cout << "\n\t\t\t\t 1. 9.00 AM";
    cout << "\n\t\t\t\t 2. 12.00 PM";
    cout << "\n\t\t\t\t 3. 3.00 PM";
    cout << "\n\t\t\t\t 4. 6.00 PM"; //Timings of the show
    cout << "\n\n\t\t\t\t Please select the timings: ";

    while ((cin >> t.time) && (t.time < 1 || t.time > 4)) {
      cout << "Invalid timing selection - Please select a valid timing.\n";
      cout << "\n\t\t\t\tEnter Your timing :" << "\t";

      cin.clear();

      cin.ignore(numeric_limits < streamsize > ::max(), '\n');
    }

    system("CLS");
    cout << "\t\tThank you for selecting the show. Now we request you to select your type of seating";
    cout << "\n\n\t\t\t\t 1.Normal Class \n\t\t\t\t  \n\t\t\t\t 2. Gold Class";
    cout << "\n\n\t\t\t\t Please select the seating class: ";

    while ((cin >> t.seatingclass) && (t.seatingclass < 1 || t.seatingclass > 2)) {
      cout << "Invalid timing selection - Please select a valid timing.\n";
      cout << "\n\t\t\t\tEnter Your timing :" << "\t";

      cin.clear();

      cin.ignore(numeric_limits < streamsize > ::max(), '\n');
    }

    cout << "\n\t\t\t\t Enter the number of tickets you want to purchase(max limit 10): ";

    while ((cin >> t.ticket) && (t.ticket < 1 || t.ticket > 10)) {
      cout << "Invalid ticket selection - Please select a valid number of ticket.\n";
      cout << "\n\t\t\t\tEnter the number of tickets you want to purchase(max limit 10):" << "\t";

      cin.clear();

      cin.ignore(numeric_limits < streamsize > ::max(), '\n');
    }

    system("CLS");
    cout << "\n\t\t\t\t Enter your name: ";
    cin >> t.name;
    cin.ignore(numeric_limits < streamsize > ::max(), '\n');

    cout << "\n\t\t\t\t Enter your contact number: ";
    cin >> t.cno;

    cout << "\n\t\t\t\tEnter the email :";
    cin >> t.email;

    while (!std::regex_match(t.email, pattern)) {
      cout << "\n\t\t\t\t invalid email id \n";
      cout << "\n\t\t\t\t please Enter the valid email :" << "\t";
      cin.clear();
      cin.ignore(numeric_limits < streamsize > ::max(), '\n');
      cin >> t.email;
    }

    std::string result = "SELECT name FROM movielist where id=" + std::to_string(t.movieid);
    query = result.c_str();
    res = executeQuery(conn, query);
    row = mysql_fetch_row(res);;
    std::stringstream ss;
    ss << "0" << t.date << "/02/2023";
    std::string date = ss.str();
    cout << "\n\t\t\t\t Name 		  :" << t.name;
    cout << "\n\t\t\t\t Contact No	  :" << t.cno;
    int actualPin = generateRandomPin();
    cout << "\n\t\t\t\t Ticket Id       : " << actualPin;
    cout << "\n\t\t\t\t Movie Name	  :" << row[0];
    cout << "\n\t\t\t\t Show timings 	  :" << showtiming(t.time);
    cout << "\n\t\t\t\t number of ticket :" << t.ticket;
    cout << "\n\t\t\t\t seating class 	  :" << showclass(t.seatingclass);
    cout << "\n\t\t\t\t date             :" << date;
    cout << "\n\t\t\t\t Total amount	  :";
    ticketcost(t.ticket, t.seatingclass);

    cout << "\n\n\t\t Can you please confirm above details are correct, please type 'y' to proceed for payment:";
    char x;
    cin >> x;
    if (x != 'y') {

    }
    else {
      bool k = payment(700);
      std::stringstream ss;
      ss << "0" << t.date << "/02/2023";
      std::string ks = ss.str();
      result = "INSERT INTO `bookingdetails` (`username`, `name`, `mobileno`, `emailid`, `seatingclass`, `timing`, `moviename`, `date`) VALUES ('admin', '" + t.name;

      result += "', '" + t.cno + "', '" + t.email + "', '" + showclass(t.seatingclass) + "', '" + showtiming(t.time) + "', '" + row[0] + "', '" + date + "')";
      res = executeQuery(conn, result.c_str());

      cout << "\n\t\t\t\tPlease enter your PIN: ";
      cin >> enteredPin;

      cout << "\n\t\t\t\tThanks for booking ticket in our website. visit again!!!!";

    }
  } else if (choice == 2) {
    cout << "\n\t\t\t\tcurrently running movie list\n\n";
    currentmovie();
  } else if (choice == 3) {
    upcoming();
  } else if (choice == 4) {
    admin_choice();
  }
    else if(choice == 5) {
    cout<<"\n\t\t\t\t about us\n";
        std::cout << "\t\tAbout Us - Movie Ticket Booking System" << std::endl;
        std::cout << "\t\t-------------------------------------" << std::endl;
        std::cout << "\t\tWelcome to our Movie Ticket Booking System!" << std::endl;
        std::cout << "\t\tWe aim to provide a seamless and enjoyable experience for moviegoers." << std::endl;
        std::cout << "\t\tOur platform allows you to browse, select, and book movie tickets with ease." << std::endl;
        std::cout << "\t\tFeel free to explore the latest movie listings, check showtimes, and choose your preferred seats." << std::endl;
        std::cout << "\t\tWe are committed to making your movie-going experience convenient and enjoyable." << std::endl;
         std::cout << "\t\tContact Us - Movie Ticket Booking System" << std::endl;
        std::cout << "\t\t--------------------------------------" << std::endl;
        std::cout << "\t\tIf you have any questions or concerns, feel free to reach out to us:" << std::endl;
        std::cout << "\t\tEmail: support@movietickets.com" << std::endl;
        std::cout << "\t\tPhone: +1 (800) 123-4567" << std::endl;
        std::cout << "\t\tAddress: 123 Movie Street, Cityville, Country" << std::endl;
        std::cout << "\t\tWe value your feedback and are here to assist you!" << std::endl;
        std::cout << "\t\tThank you for choosing our Movie Ticket Booking System!" << std::endl;
    }
    else if(choice == 6) {
    cout<<"\n\t\t\t\t THANK YOU VIST AGAIN \n";
    exit(0);
    }
}

int main() {

  system("CLS");

  conn = mysql_init(0);
  if (mysql_real_connect(conn, "localhost", "karan", "babar", "moviebooking", 0, nullptr, 0)) {
    std::cout << "Connected" << std::endl;
  } else {
    std::cerr << "Not Connected" << std::endl;
  }
  char s;
  do {
    main_menu();
    cout << "\n\t\t\t\t please press Y if you want to continue :";
    cin >> s;
  } while (s == 'y');

  mysql_close(conn);
  return 0;
}
