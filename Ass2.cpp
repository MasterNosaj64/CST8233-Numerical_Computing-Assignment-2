/****************************************************************************************************************************************
File Name:						Ass2.cpp
Version:						1.0
Auther/Student Name:			Jason Waid
Student Number:					040912687
Couse Name and Number:			Numerical Computing CST8233
Lab Section:					303
Assignment Number:				Assignment #2
Assignment Name:				Moore's law
Due Date:						07/20/2020
Submission Date of Assignment:	07/19/2020
Professor's Name:				Abdullah Kadri
Purpose:						Demonstrate Moore's law
******************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include <math.h>
#include <typeinfo>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
using namespace std;

int main() {

	//Variables for math
	double sumOfXSqr = 0;
	double sumOfY = 0;
	double sumOfYear = 0;
	double sumOfXY = 0;
	int numRecords = 0;

	//variables for results
	double slope = 0;
	double yIntercept = 0;
	double result = 0;

	//variables for menu
	string label = "";
	string name = "";
	char* fileToRead = new char[10];
	double year = 0;
	double numTransistors = 0;
	int menu = 0;

	cout << "LEAST_SQUARES LINEAR REGRESSION\n" << endl;

	//Main MENU
	while (menu != 2) {
		cout << "MENU" << endl;
		cout << " 1. Exponential Fit" << endl;
		cout << " 2. Quit" << endl;
		cout << " ";

		cin >> menu;

		if (menu == 1) {

			cout << "Please enter the name of the file to open: ";
			cin >> fileToRead;

			//Begin of process for opening file
			ifstream myFile(fileToRead, ios::in);

			if (myFile.is_open()) {
				//begin reading file
				getline(myFile, label);
				//prints first line labels
				cout << label << endl;
				numRecords = 0;
				while (myFile >> year >> numTransistors >> name) {
					//prints sequential lines
					cout << left << setw(16) << (int)year << setprecision(3) << scientific << setw(24) << numTransistors << name << endl;

					//apply mathimatical opperations to contents of line
					sumOfXY += (year - 1970) * log(numTransistors);
					sumOfY += log(numTransistors);
					sumOfXSqr += pow(year - 1970, 2);
					sumOfYear += year - 1970; //x
					numRecords++;
				}

				//mathimatical opperations for determining slope and y-intercept
				slope = (numRecords * sumOfXY - sumOfYear * sumOfY) / (numRecords * sumOfXSqr - pow(sumOfYear, 2));
				yIntercept = exp((sumOfY / numRecords) - slope * (sumOfYear / numRecords));

				myFile.close();

				//display counter
				cout << "\nThere are " << numRecords << " records" << endl;
				//display linear regression fit
				cout << "\nLinear Regression Fit: transistor count = " << yIntercept << "*exp(" << slope << "*(year-1970))" << endl;


				//Second MENU
				while (menu != 2) {

					cout << "\nMENU" << endl;
					cout << " 1. Extrapolation" << endl;
					cout << " 2. Main Menu" << endl;
					cout << " ";

					cin >> menu;

					switch (menu) {
					case 1:

						cout << "Please enter the year to extrapolate to: ";
						cin >> year;

						numTransistors = yIntercept * exp(slope * (year - 1970));
						cout << "Year = " << (int)year << endl;
						cout << "transistor count = " << numTransistors << endl;
						cout << "rate of count increase = " << numTransistors * slope << " transistors/year" << endl;

						break;

					case 2:

						cout << "\nLEAST_SQUARES LINEAR REGRESSION\n";
						break;

					default:

						cout << "ERROR - INVALID MENU OPTION" << endl;
						break;
					}
				}
				menu = 0;
			}
			else {
				cout << "ERROR - Unable to open file named: " << fileToRead << endl;
			}
		}

			//case used for quiting program
		else if (menu == 2) {

			return 0;
		}

			//default for handling incorrect inputs
		else {

			cout << "ERROR - INVALID MENU OPTION" << endl;
		}
		}
	}
