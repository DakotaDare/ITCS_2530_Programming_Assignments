// Week01_ProgrammingAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

int main() {
    cout << "======================================================\n" << endl;
    cout << "    888b     d888 8888888b.   .d8888b.  8888888b." << endl;
    cout << "    8888b   d8888 888   Y88b d88P  Y88b 888   Y88b" << endl;
    cout << "    88888b.d88888 888    888 Y88b.      888    888" << endl;
    cout << "    888Y88888P888 888   d88P  'Y888b.   888   d88P" << endl;  // ASCII ART from https://www.asciiart.eu/text-to-ascii-art
    cout << "    888 Y888P 888 8888888P'      'Y88b. 8888888P" << endl;   // editing for proper syntax and code for program created by me.
    cout << "    888  Y8P  888 888              '888 888" << endl;
    cout << "    888   '   888 888        Y88b  d88P 888" << endl;
    cout << "    888       888 888         'Y8888P'  888\n" << endl;
    cout << "======================================================\n" << endl;
    cout << "   WELCOME TO MPSP (MINIATURE PAINT SCHEME PLANNER)  \n" << endl;
    cout << "======================================================\n" << endl;
    cout << "This program will help you estimate the cost of your miniature paint scheme based on..." << endl;
    cout << "your base color selection," << endl;
    cout << "the method of color theory you'd like to use," << endl;
    cout << "and your preferred paint brand.\n" << endl;
    cout << "After entering all data, the program will save a copy of the report! \n" << endl;

    // variables
    string baseColor;
    int extraColors;
	int theoryChoice;
	string theoryName;
	int brandChoice;
	string brandName;
    double potPrice;

    // string input that can include spaces (example: "Light Blue")
    cout << "Enter the name of your base paint color: " << endl;
    getline(cin, baseColor);
	cout << "\n> You selected " << baseColor << " as your base color.\n" << endl;

    // integer input for the count of additional colors
    // display selections
    cout << "Please select the number for color theory to apply\n";
    cout << "1. Analogous\n";
    cout << "2. Complementary\n";
    cout << "3. Split Complementary\n";
    cout << "4. Triadic\n";
	cout << "5. Tetradic\n";
	cout << "6. Square\n";
    cout << "Enter your choice (1-6): ";

    cin >> theoryChoice;

	// switch case for the color theory selection and the number of additional colors needed for each theory.
    switch (theoryChoice) {
    case 1:
        cout << "\n> You selected Analogous color theory.\n";
        extraColors = 2;
		theoryName = "Analogous";
        break;
    case 2:
        cout << "\n> You selected Complementary color theory.\n";
        extraColors = 2;
		theoryName = "Complementary";
        break;
    case 3:
        cout << "\n> You selected Split Complementary color theory.\n";
        extraColors = 3;
		theoryName = "Split Complementary";
        break;
    case 4:
        cout << "\n> You selected Triadic color theory.\n";
        extraColors = 2;
		theoryName = "Triadic";
        break;
    case 5:
        cout << "\n> You selected Tetradic color theory.\n";
        extraColors = 3;
		theoryName = "Tetradic";
        break;
    case 6:
        cout << "\n> You selected Square color theory.\n";
        extraColors = 4;
		theoryName = "Square";
        break;
    default:
		// using an if statement inside default for wrong selection handling, and defaulting to Complementary color theory if the user enters an invalid choice.
        if (theoryChoice != 1 || 2 || 3 || 4 || 5 || 6) {
            cout << "Invalid choice. Using Complementary color theory.\n";
			extraColors = 2;
			theoryName = "Complementary";
        }
        else {
            break;
        }
        break;
    }

	// integer input for paint brand selection
    cout << "Please select your preferred paint brand:\n";
    cout << "1. The Army Painter\n";
    cout << "2. Vallejo\n";
    cout << "3. Citadel Colour\n";
    cout << "Enter your choice (1-3): ";
    cin >> brandChoice;

	switch (brandChoice) {
    case 1:
        cout << "\n> You selected The Army Painter.\n";
		potPrice = 5.13; // default price for The Army Painter base color
		brandName = "The Army Painter";
        break;
    case 2:
        cout << "\n> You selected Vallejo.\n";
		potPrice = 3.39; // default price for Vallejo base color
		brandName = "Vallejo";
        break;
    case 3:
        cout << "\n> You selected Citadel Colour.\n";
		potPrice = 4.75; // default price for Citadel Colour base color
		brandName = "Citadel Colour";
        break;
    default:
        // using an if statement inside default for wrong selection handling, and defaulting to Citadel Colour if the user enters an invalid choice.
        if (brandChoice != 1 || 2 || 3) {
            cout << "Invalid choice. Using Citadel Colour.\n";
            potPrice  = 4.75;
			brandName = "Citadel Colour";
        }
        else {
            break;
        }
		break;
	}

    // calculate estimated cost of paint for base color and extra colors.
    int potsNeeded = extraColors + 1;
    double totalEstimatedCost = potsNeeded * potPrice;

    // summary table in the console / what will be printed to the report.txt file
    cout << "\n" << left << setw(30) << "REPORT ITEM" << right << setw(20) << "VALUE" << endl;
    cout << string(50, '-') << endl;
    cout << left << setw(30) << setfill('.') << "Base Color Selection:" << right << setw(20) << baseColor << endl;
	cout << left << setw(30) << setfill('.') << "Color Theory Selected:" << right << setw(20) << theoryName << endl;
    cout << left << setw(30) << setfill('.') << "Additional Colors Needed:" << right << setw(20) << extraColors << endl;
    cout << fixed << setprecision(2); // floating-point outputs to 2 decimals (price)
	cout << left << setw(30) << setfill('.') << "Preferred Paint Brand:" << right << setw(20) << brandName << endl;
    cout << left << setw(30) << setfill('.') << "Cost per Paint Pot:" << right << "$" << setw(19) << potPrice << endl;
    cout << left << setw(30) << setfill('.') << "Estimated Pots Needed:" << right << setw(20) << potsNeeded << endl;
    cout << string(50, '-') << endl;
    cout << left << setw(30) << setfill('.') << "Total Estimated Paint Cost:" << right << "$" << setw(19) << totalEstimatedCost << endl;
    cout << string(50, '=') << endl;

    // file stream to print the report out to a text file
    ofstream outFile("report.txt");

    outFile << "==================================================\n";
    outFile << "   MPSP (MINIATURE PAINT SCHEME PLANNER) REPORT   \n";
    outFile << "==================================================\n\n";

    // copied formatting to the output file
    outFile << left << setw(30) << "REPORT ITEM" << right << setw(20) << "VALUE" << endl;
    outFile << string(50, '-') << endl;
    outFile << left << setw(30) << setfill('.') << "Base Color Selection:" << right << setw(20) << baseColor << endl;
    outFile << left << setw(30) << setfill('.') << "Color Theory Selected:" << right << setw(20) << theoryName << endl;
    outFile << left << setw(30) << setfill('.') << "Additional Colors Needed:" << right << setw(20) << extraColors << endl;
    outFile << fixed << setprecision(2);
	outFile << left << setw(30) << setfill('.') << "Preferred Paint Brand:" << right << setw(20) << brandName << endl;
    outFile << left << setw(30) << setfill('.') << "Cost per Paint Pot:" << right << "$" << setw(19) << potPrice << endl;
    outFile << left << setw(30) << setfill('.') << "Estimated Pots Needed:" << right << setw(20) << potsNeeded << endl;
    outFile << string(50, '-') << endl;
    outFile << left << setw(30) << setfill('.') << "Total Estimated Paint Cost:" << right << "$" << setw(19) << totalEstimatedCost << endl;
    outFile << string(50, '=') << endl;

    // close the file stream
    outFile.close();

    cout << "\nReport successfully compiled and saved to 'report.txt'!\n";

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
