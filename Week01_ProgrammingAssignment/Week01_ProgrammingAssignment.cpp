// Week01_ProgrammingAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

// writes the report table to whichever output stream is provided.
// using the same function keeps the console report and report.txt consistent.
void writeReportTable(ostream& report, const string& baseColor,
    const string& theoryName, const string& brandName, int extraColors,
    double potPrice, int potsNeeded, int primerPots, int metallicPots,
    int washPots, double additionalPaintCost, double totalEstimatedCost);

// displays the color choices and changes the console text color.
void changeTextColor();

// displays the program's opening banner.
void displayOpeningBanner();

// displays the main menu and the current selections.
void displayMainMenu(const string& baseColor, const string& theoryName,
    const string& brandName);

// base color selection
void selectBaseColor(string& baseColor, bool& baseColorSelected);
// color theory selection
void selectColorTheory(int& extraColors, string& theoryName,
    bool& theorySelected);
// paint brand selection
void selectPaintBrand(double& potPrice, string& brandName,
    bool& brandSelected);
// additional paint selection
void selectAdditionalPaints(int& primerPots, double& primerPrice,
    int& metallicPots, double& metallicPrice, int& washPots,
    double& washPrice, double& additionalPaintCost);

int main()
{
    displayOpeningBanner();

    // main variables
    string baseColor;
    string theoryName;
    string brandName;

    int extraColors = 0;
    int menuChoice = 0;
    int potsNeeded = 0;

    double potPrice = 0.0;
    double totalEstimatedCost = 0.0;


    // additional paint variables
    int primerPots = 0;
    int metallicPots = 0;
    int washPots = 0;

    double primerPrice = 0.0;
    double metallicPrice = 0.0;
    double washPrice = 0.0;
    double additionalPaintCost = 0.0;


    // selection flags
    bool baseColorSelected = false;
    bool theorySelected = false;
    bool brandSelected = false;
    bool running = true;


    // main menu loop
	// conditional while loop using the running flag
    while (running)
    {
        displayMainMenu(baseColor, theoryName, brandName);

        cin >> menuChoice;


		// error handling for invalid input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\nInvalid input. Please enter a number "
                << "from 1 through 9.\n";

            continue;
        }


        // main menu switch
        switch (menuChoice)
        {
        case 1: // base color selection
            selectBaseColor(baseColor, baseColorSelected);
            break;

        case 2: // color theory selection
            selectColorTheory(extraColors, theoryName, theorySelected);
            break;

        case 3: // paint brand selection
            selectPaintBrand(potPrice, brandName, brandSelected);
            break;

        case 4: // additional paint selection
            selectAdditionalPaints(primerPots, primerPrice, metallicPots,
                metallicPrice, washPots, washPrice, additionalPaintCost);
            break;


        case 5: // display report in console
        {
            // A report requires the three primary selections.
            if (!baseColorSelected || !theorySelected || !brandSelected)
            {
                cout << "\nPlease complete the base color, "
                    << "color theory, and paint brand selections first.\n";
                break;
            }

            // Calculate the number of base pots and the total cost.
            potsNeeded = extraColors + 1;
            totalEstimatedCost = (potsNeeded * potPrice) + additionalPaintCost;

            // Send the table to the console.
            writeReportTable(cout, baseColor, theoryName, brandName, extraColors,
                potPrice, potsNeeded, primerPots, metallicPots, washPots,
                additionalPaintCost, totalEstimatedCost);
            break;
        }

        case 6: // output report to file
        {
            // A report requires the three primary selections.
            if (!baseColorSelected || !theorySelected || !brandSelected)
            {
                cout << "Please complete the base color, " << endl;
                cout << "color theory, and paint brand selections first.\n";
                break;
            }

            // Calculate the number of base pots and the total cost.
            potsNeeded = extraColors + 1;
            totalEstimatedCost = (potsNeeded * potPrice) + additionalPaintCost;

            // Open the file before writing the report table.
            ofstream outFile("report.txt");
            if (!outFile)
            {
                cout << "Unable to create report.txt.\n";
                break;
            }

            // Write the same table used by the console report.
            outFile << "==================================================\n";
            outFile << "   MPSP (MINIATURE PAINT SCHEME PLANNER) REPORT   \n";
            outFile << "==================================================\n\n";
            writeReportTable(outFile, baseColor, theoryName, brandName, extraColors,
                potPrice, potsNeeded, primerPots, metallicPots, washPots,
                additionalPaintCost, totalEstimatedCost);

            cout << "Report successfully compiled and saved to "
                << "'report.txt'!\n";
            break;
        }

        case 7: // change console text color
        {
            changeTextColor();
            break;
        }

        case 8: // display the opening banner again
        {
            displayOpeningBanner();
            break;
        }

        case 9: // exit program
        {
            cout << "Thank you for using MPSP!\n";
            running = false;

            break;
        }

		default: // invalid menu choice
        {
            cout << "Invalid menu choice. Please enter a number "
                << "from 1 through 9.\n";

            break;
        }
        }
    }


    return 0;
}

// Displays the main menu and the current selections.
void displayMainMenu(const string& baseColor, const string& theoryName,
    const string& brandName)
{
    cout << "======================================================\n";
    cout << "                      MAIN MENU\n";
    cout << "======================================================\n";
    cout << "1. Select base color: " << baseColor << "\n";
    cout << "2. Select color theory: " << theoryName << "\n";
    cout << "3. Select paint brand: " << brandName << "\n";
    cout << "4. Select additional paints\n";
    cout << "5. View report\n";
    cout << "6. Output report file\n";
    cout << "7. Change text color\n";
    cout << "8. Display opening banner\n";
    cout << "9. Exit\n";
    cout << "======================================================\n";
    cout << "Enter your choice: ";
}

// Gets and stores the user's base paint color.
void selectBaseColor(string& baseColor, bool& baseColorSelected)
{
    cin.ignore(1000, '\n');
    cout << "\nEnter the name of your base paint color: ";
    getline(cin, baseColor);

    if (baseColor.empty())
    {
        cout << "\nYou must enter a paint color.\n";
        return;
    }

    cout << "\n> You selected " << baseColor
        << " as your base color.\n";
    baseColorSelected = true;
}

// Gets the selected color theory and determines how many extra colors it needs.
void selectColorTheory(int& extraColors, string& theoryName,
    bool& theorySelected)
{
    int theoryChoice;

    cout << "\nPlease select the number for color theory to apply:\n";
    cout << "1. Analogous\n";
    cout << "2. Complementary\n";
    cout << "3. Split Complementary\n";
    cout << "4. Triadic\n";
    cout << "5. Tetradic\n";
    cout << "6. Square\n";
    cout << "Enter your choice (1-6): ";
    cin >> theoryChoice;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input. Please enter a number from 1 through 6.\n";
        return;
    }

    switch (theoryChoice)
    {
    case 1:
        theoryName = "Analogous";
        extraColors = 2;
        break;
    case 2:
        theoryName = "Complementary";
        extraColors = 2;
        break;
    case 3:
        theoryName = "Split Complementary";
        extraColors = 3;
        break;
    case 4:
        theoryName = "Triadic";
        extraColors = 2;
        break;
    case 5:
        theoryName = "Tetradic";
        extraColors = 3;
        break;
    case 6:
        theoryName = "Square";
        extraColors = 4;
        break;
    default:
        cout << "\nInvalid choice. Using Complementary color theory.\n";
        theoryName = "Complementary";
        extraColors = 2;
        break;
    }

    cout << "\n> You selected " << theoryName << " color theory.\n";
    theorySelected = true;
}

// Gets the selected paint brand and stores its price for the report.
void selectPaintBrand(double& potPrice, string& brandName,
    bool& brandSelected)
{
    int brandChoice;

    cout << "\nPlease select your preferred paint brand:\n";
    cout << "1. The Army Painter\n";
    cout << "2. Vallejo\n";
    cout << "3. Citadel Colour\n";
    cout << "Enter your choice (1-3): ";
    cin >> brandChoice;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input. Please enter a number from 1 through 3.\n";
        return;
    }

    switch (brandChoice)
    {
    case 1:
        brandName = "The Army Painter";
        potPrice = 5.13;
        break;
    case 2:
        brandName = "Vallejo";
        potPrice = 3.39;
        break;
    case 3:
        brandName = "Citadel Colour";
        potPrice = 4.75;
        break;
    default:
        cout << "\nInvalid choice. Using Citadel Colour.\n";
        brandName = "Citadel Colour";
        potPrice = 4.75;
        break;
    }

    cout << "\n> You selected " << brandName << ".\n";
    brandSelected = true;
}

// Gets the user's yes/no choices for primer, metallic paint, and wash.
void selectAdditionalPaints(int& primerPots, double& primerPrice,
    int& metallicPots, double& metallicPrice, int& washPots,
    double& washPrice, double& additionalPaintCost)
{
    char answer;

    // Each loop entry represents one optional paint type.
    const string prompts[] = {
        "\nDo you need primer? ($9.99) (y/n): ",
        "\nDo you need a metallic paint? ($7.75) (y/n): ",
        "\nDo you need a wash? ($7.75) (y/n): "
    };
    int* pots[] = { &primerPots, &metallicPots, &washPots };
    double* prices[] = { &primerPrice, &metallicPrice, &washPrice };
    const double costs[] = { 9.99, 7.75, 7.75 };
    const string names[] = { "Primer", "Metallic paint", "Wash" };

    for (int paintChoice = 0; paintChoice < 3; paintChoice++)
    {
        do
        {
            cout << prompts[paintChoice];
            cin >> answer;

            if (answer != 'y' && answer != 'Y' &&
                answer != 'n' && answer != 'N')
            {
                cout << "Invalid answer. Please enter y or n.\n";
                cin.ignore(1000, '\n');
            }
        } while (answer != 'y' && answer != 'Y' &&
            answer != 'n' && answer != 'N');

        if (answer == 'y' || answer == 'Y')
        {
            *pots[paintChoice] = 1;
            *prices[paintChoice] = costs[paintChoice];
            cout << names[paintChoice] << " added.\n";
        }
        else
        {
            *pots[paintChoice] = 0;
            *prices[paintChoice] = 0.0;
            cout << names[paintChoice] << " not added.\n";
        }
    }

    // Calculate the cost of all selected optional paints.
    additionalPaintCost =
        (primerPots * primerPrice) +
        (metallicPots * metallicPrice) +
        (washPots * washPrice);
    cout << "\nAdditional paint selections saved.\n";
}

// Displays the program title and instructions whenever the user requests it.
void displayOpeningBanner()
{
    cout << "======================================================" << endl;
    cout << "    888b     d888 8888888b.   .d8888b.  8888888b." << endl;
    cout << "    8888b   d8888 888   Y88b d88P  Y88b 888   Y88b" << endl;
    cout << "    88888b.d88888 888    888 Y88b.      888    888" << endl;
    cout << "    888Y88888P888 888   d88P  'Y888b.   888   d88P" << endl;
    cout << "    888 Y888P 888 8888888P'      'Y88b. 8888888P" << endl;
    cout << "    888  Y8P  888 888              '888 888" << endl;
    cout << "    888   '   888 888        Y88b  d88P 888" << endl;
    cout << "    888       888 888         'Y8888P'  888" << endl;
    cout << "======================================================" << endl;
    cout << "   WELCOME TO MPSP (MINIATURE PAINT SCHEME PLANNER)" << endl;
    cout << "======================================================" << endl;
    cout << "This program will help you estimate the cost of your " << endl;
    cout << "miniature paint scheme based on..." << endl;
    cout << "your base color selection," << endl;
    cout << "the method of color theory you'd like to use," << endl;
    cout << "and your preferred paint brand." << endl;
}

// formats one complete report table. The ostream parameter allows the same
// table to be printed to the console or written to report.txt.
void writeReportTable(ostream& report, const string& baseColor,
    const string& theoryName, const string& brandName, int extraColors,
    double potPrice, int potsNeeded, int primerPots, int metallicPots,
    int washPots, double additionalPaintCost, double totalEstimatedCost)
{
    
    report << left << setw(30) << "REPORT ITEM"
        << right << setw(20) << "VALUE" << endl;
    report << string(50, '-') << endl;

    
    report << left << setw(30) << setfill('.') << "Base Color Selection:"
        << right << setw(20) << baseColor << endl;
    report << left << setw(30) << setfill('.') << "Color Theory Selected:"
        << right << setw(20) << theoryName << endl;
    report << left << setw(30) << setfill('.') << "Additional Colors Needed:"
        << right << setw(20) << extraColors << endl;

    
    report << fixed << setprecision(2);
    report << left << setw(30) << setfill('.') << "Preferred Paint Brand:"
        << right << setw(20) << brandName << endl;
    report << left << setw(30) << setfill('.') << "Cost per Paint Pot:"
        << right << "$" << setw(19) << potPrice << endl;
    report << left << setw(30) << setfill('.') << "Estimated Base Pots Needed:"
        << right << setw(20) << potsNeeded << endl;
    report << left << setw(30) << setfill('.') << "Primer Pots:"
        << right << setw(20) << primerPots << endl;
    report << left << setw(30) << setfill('.') << "Metallic Pots:"
        << right << setw(20) << metallicPots << endl;
    report << left << setw(30) << setfill('.') << "Wash Pots:"
        << right << setw(20) << washPots << endl;
    report << left << setw(30) << setfill('.') << "Additional Paint Cost:"
        << right << "$" << setw(19) << additionalPaintCost << endl;

    
    report << string(50, '-') << endl;
    report << left << setw(30) << setfill('.') << "Total Estimated Paint Cost:"
        << right << "$" << setw(19) << totalEstimatedCost << endl;
    report << setfill(' ') << string(50, '=') << endl;
}

// Lets the user choose one of five simple console text colors.
void changeTextColor()
{
    int colorChoice;

    cout << "\nChoose a text color:\n";
    cout << "1. Blue\n";
    cout << "2. Green\n";
    cout << "3. Cyan\n";
    cout << "4. Red\n";
    cout << "5. Yellow\n";
    cout << "Enter your choice (1-5): ";
    cin >> colorChoice;

    // windows console color attributes used by the five menu choices.
    const int colors[] = { 9, 10, 11, 12, 14 };

    if (cin.fail() || colorChoice < 1 || colorChoice > 5)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid color choice. Please enter a number from 1 through 5.\n";
        return;
    }

    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE), colors[colorChoice - 1]);
    cout << "Text color changed.\n";
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
