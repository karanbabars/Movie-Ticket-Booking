"""
# Movie Ticket Booking System

## Overview

This C++ program implements a simple Movie Ticket Booking System. It allows users to browse and book movie tickets, view currently running movies, and check upcoming movies. The system also provides an admin interface for managing movie listings.

## Features

- **User Menu:**
  - Book Tickets
  - View Currently Running Movies
  - View Upcoming Movies
  - Admin Access
  - About Us
  - Exit

- **Admin Menu:**
  - Insert New Movie
  - Update Existing Movie
  - Delete Existing Movie
  - Exit

## How to Use

1. Run the program.
2. Choose an option from the main menu.
3. Follow the on-screen prompts to book tickets, view movie listings, or access the admin menu.

## Dependencies

- MySQL: The program connects to a MySQL database named `moviebooking` hosted on `localhost`. Make sure to update the database connection details if needed.
- Additional C++ libraries: `<iostream>`, `<fstream>`, `<conio.h>`, `<string.h>`, `<math.h>`, `<stdlib.h>`, `<stdio.h>`, `<process.h>`, `<limits>`, `<time.h>`, `<windows.h>`, `<mysql.h>`, `<iomanip>`, `<regex>`, `<cstdlib>`, `<ctime>`, `<iostream>`, `<random>`.

## Database Schema

- `movielist`: Stores information about currently running movies.
  - Columns: `id`, `name`, `description`, `language`.

- `upcoming`: Stores information about upcoming movies.
  - Columns: `date`, `movie_name`, `language`, `description`.

- `bookingdetails`: Stores details of booked tickets.
  - Columns: `username`, `name`, `mobileno`, `emailid`, `seatingclass`, `timing`, `moviename`, `date`.

## Author

- **Karan Sambhaji Babar**
- **Date:** 09/12/2023

## Notes

- The program uses the `mysql` C API to interact with the database.
- Passwords and sensitive information are hard-coded in the program for simplicity. In a real-world scenario, use secure practices to handle credentials.
- The program provides basic input validation, but additional validation and error handling can be added for robustness.
- This system is designed for educational purposes and may require adjustments for production use.
"""
