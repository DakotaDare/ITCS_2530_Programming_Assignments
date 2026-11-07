// Week01_ProgrammingAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    cout << "======================================================" << endl;
    cout << "    888b     d888 8888888b.   .d8888b.  8888888b." << endl;
    cout << "    8888b   d8888 888   Y88b d88P  Y88b 888   Y88b" << endl;
    cout << "    88888b.d88888 888    888 Y88b.      888    888" << endl;
    cout << "    888Y88888P888 888   d88P  'Y888b.   888   d88P" << endl; // ASCII ART from https://www.asciiart.eu/text-to-ascii-art
    cout << "    888 Y888P 888 8888888P'      'Y88b. 8888888P" << endl; // editing for proper syntax and code for program created by me.
    cout << "    888  Y8P  888 888              '888 888" << endl;
    cout << "    888   '   888 888        Y88b  d88P 888" << endl;
    cout << "    888       888 888         'Y8888P'  888" << endl;
    cout << "======================================================" << endl;
    cout << "   WELCOME TO MPSP (MINIATURE PAINT SCHEME PLANNER)"
        << endl;
    cout << "======================================================" << endl;
	cout << "This program will help you estimate the cost of your " << endl;
    cout << "miniature paint scheme based on..." << endl;
    cout << "your base color selection," << endl;
    cout << "the method of color theory you'd like to use," << endl;
    cout << "and your preferred paint brand." << endl;

    // main variables
    string baseColor;
    string theoryName;
    string brandName;

    int extraColors = 0;
    int theoryChoice = 0;
    int brandChoice = 0;
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
        cout << "======================================================\n";
        cout << "                      MAIN MENU\n";
        cout << "======================================================\n";
        cout << "1. Select base color: " << baseColor << "\n";
        cout << "2. Select color theory: " << theoryName << "\n";
        cout << "3. Select paint brand: " << brandName << " \n";
        cout << "4. Select additional paints\n";
        cout << "5. View report\n";
        cout << "6. Output report file\n";
        cout << "7. Exit\n";
        cout << "======================================================\n";
        cout << "Enter your choice: ";

        cin >> menuChoice;


		// error handling for invalid input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\nInvalid input. Please enter a number "
                << "from 1 through 7.\n";

            continue;
        }


        // main menu switch
        switch (menuChoice)
        {
		case 1: // base color selection
        {
            // remove the newline before using getline
            cin.ignore(1000, '\n');

            cout << "\nEnter the name of your base paint color: ";
            getline(cin, baseColor);

            if (baseColor == "")
            {
                cout << "\nYou must enter a paint color.\n";
                break;
            }

            cout << "\n> You selected "
                << baseColor
                << " as your base color.\n";

            baseColorSelected = true;
            break;
        }


		case 2: // color theory selection
        {
            cout << "\nPlease select the number for color theory "
                << "to apply:\n";
            cout << "1. Analogous\n";
            cout << "2. Complementary\n";
            cout << "3. Split Complementary\n";
            cout << "4. Triadic\n";
            cout << "5. Tetradic\n";
            cout << "6. Square\n";
            cout << "Enter your choice (1-6): ";

            cin >> theoryChoice;

			// error handling for invalid input
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "\nInvalid input. Please enter a number "
                    << "from 1 through 6.\n";

                break;
            }


            // color theory switch
            switch (theoryChoice)
            {
            case 1:
                cout << "\n> You selected Analogous color theory.\n";
				extraColors = 2; // set the number of additional colors
				theoryName = "Analogous"; // set the name of the color theory for report
                break;

            case 2:
                cout << "\n> You selected Complementary color theory.\n";
                extraColors = 2;
                theoryName = "Complementary";
                break;

            case 3:
                cout << "\n> You selected Split Complementary "
                    << "color theory.\n";
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
                cout << "\nInvalid choice. Using Complementary "
                    << "color theory.\n";

                extraColors = 2;
                theoryName = "Complementary";
                break;
            }

            theorySelected = true;
            break;
        }


		case 3: // paint brand selection
        {
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

                cout << "\nInvalid input. Please enter a number "
                    << "from 1 through 3.\n";

                break;
            }


            // paint brand switch
            switch (brandChoice)
            {
            case 1:
                cout << "\n> You selected The Army Painter.\n";
                potPrice = 5.13;
                brandName = "The Army Painter";
                break;

            case 2:
                cout << "\n> You selected Vallejo.\n";
                potPrice = 3.39;
                brandName = "Vallejo";
                break;

            case 3:
                cout << "\n> You selected Citadel Colour.\n";
                potPrice = 4.75;
                brandName = "Citadel Colour";
                break;

            default:
                cout << "\nInvalid choice. Using Citadel Colour.\n";

                potPrice = 4.75;
                brandName = "Citadel Colour";
                break;
            }

            brandSelected = true;
            break;
        }


        case 4: // additional paint selection
        {
            char answer;


            // fixed-number loop for primer, metallic paint, and wash
			// do-while loops are used for input validation
            for (int paintChoice = 1;
                paintChoice <= 3;
                paintChoice++)
            {
                switch (paintChoice)
                {
                case 1:
                {
                    // validate the primer answer
                    do
                    {
                        cout << "\nDo you need primer? ($9.99) (y/n): ";
                        cin >> answer;

                        if (answer != 'y' &&
                            answer != 'Y' &&
                            answer != 'n' &&
                            answer != 'N')
                        {
                            cout << "Invalid answer. "
                                << "Please enter y or n.\n";

                            cin.ignore(1000, '\n');
                        }

                    } while (answer != 'y' &&
                        answer != 'Y' &&
                        answer != 'n' &&
                        answer != 'N');


                    // process the primer answer
                    if (answer == 'y' || answer == 'Y')
                    {
                        primerPots = 1;
                        primerPrice = 9.99;
                        cout << "Primer added.\n";
                    }
                    else
                    {
                        primerPots = 0;
                        primerPrice = 0.0;
                        cout << "Primer not added.\n";
                    }

                    break;
                }


                case 2:
                {
                    // validate the metallic paint answer
                    do
                    {
                        cout << "\nDo you need a metallic paint? ($7.75) (y/n): ";
                        cin >> answer;

                        if (answer != 'y' &&
                            answer != 'Y' &&
                            answer != 'n' &&
                            answer != 'N')
                        {
                            cout << "Invalid answer. "
                                << "Please enter y or n.\n";

                            cin.ignore(1000, '\n');
                        }

                    } while (answer != 'y' &&
                        answer != 'Y' &&
                        answer != 'n' &&
                        answer != 'N');


                    // process the metallic paint answer
                    if (answer == 'y' || answer == 'Y')
                    {
                        metallicPots = 1;
                        metallicPrice = 7.75;
                        cout << "Metallic paint added.\n";
                    }
                    else
                    {
                        metallicPots = 0;
                        metallicPrice = 0.0;
                        cout << "Metallic paint not added.\n";
                    }

                    break;
                }


                case 3:
                {
                    // validate the wash answer
                    do
                    {
                        cout << "\nDo you need a wash? ($7.75) (y/n): ";
                        cin >> answer;
                        if (answer != 'y' &&
                            answer != 'Y' &&
                            answer != 'n' &&
                            answer != 'N')
                        {
                            cout << "Invalid answer. "
                                << "Please enter y or n.\n";
                            cin.ignore(1000, '\n');
                        }

                    } while (answer != 'y' &&
                        answer != 'Y' &&
                        answer != 'n' &&
                        answer != 'N');

                    // process the wash answer
                    if (answer == 'y' || answer == 'Y')
                    {
                        washPots = 1;
                        washPrice = 7.75;
                        cout << "Wash added.\n";
                    }
                    else
                    {
                        washPots = 0;
                        washPrice = 0.0;
                        cout << "Wash not added.\n";
                    }

                    break;
                }
                }
            }

            // calculate the cost of the additional paints
            additionalPaintCost =
                (primerPots * primerPrice) +
                (metallicPots * metallicPrice) +
                (washPots * washPrice);
            cout << "\nAdditional paint selections saved.\n";

            break;
        }


        case 5: // display report in console
        {
			// verify report can be generated
            if (!baseColorSelected ||
                !theorySelected ||
                !brandSelected)
            {
                cout << "\nPlease complete the base color, "
                    << "color theory, and paint brand selections first.\n";

                break;
            }


            // calculate the base and additional paint costs
            potsNeeded = extraColors + 1;

            totalEstimatedCost =
                (potsNeeded * potPrice) +
                additionalPaintCost;


            // display the report in the console
            cout << "\n"
                << left << setw(30) << "REPORT ITEM"
                << right << setw(20) << "VALUE" << endl;

            cout << string(50, '-') << endl;

            cout << left << setw(30) << setfill('.')
                << "Base Color Selection:"
                << right << setw(20) << baseColor << endl;

            cout << left << setw(30) << setfill('.')
                << "Color Theory Selected:"
                << right << setw(20) << theoryName << endl;

            cout << left << setw(30) << setfill('.')
                << "Additional Colors Needed:"
                << right << setw(20) << extraColors << endl;

            cout << fixed << setprecision(2);

            cout << left << setw(30) << setfill('.')
                << "Preferred Paint Brand:"
                << right << setw(20) << brandName << endl;

            cout << left << setw(30) << setfill('.')
                << "Cost per Paint Pot:"
                << right << "$" << setw(19) << potPrice << endl;

            cout << left << setw(30) << setfill('.')
                << "Estimated Base Pots Needed:"
                << right << setw(20) << potsNeeded << endl;

            cout << left << setw(30) << setfill('.')
                << "Primer Pots:"
                << right << setw(20) << primerPots << endl;

            cout << left << setw(30) << setfill('.')
                << "Metallic Pots:"
                << right << setw(20) << metallicPots << endl;

            cout << left << setw(30) << setfill('.')
                << "Wash Pots:"
                << right << setw(20) << washPots << endl;

            cout << left << setw(30) << setfill('.')
                << "Additional Paint Cost:"
                << right << "$" << setw(19)
                << additionalPaintCost << endl;

            cout << string(50, '-') << endl;

            cout << left << setw(30) << setfill('.')
                << "Total Estimated Paint Cost:"
                << right << "$" << setw(19)
                << totalEstimatedCost << endl;

            cout << setfill(' ');
            cout << string(50, '=') << endl;

            break;
        }


		case 6: // output report to file
        {
            // verify report can be generated
            if (!baseColorSelected || !theorySelected || !brandSelected)
            {
                cout << "Please complete the base color, " << endl;
                cout << "color theory, and paint brand selections first.\n";

                break;
            }


            // calculate the base and additional paint costs
            potsNeeded = extraColors + 1;

            totalEstimatedCost =
                (potsNeeded * potPrice) +
                additionalPaintCost;


            // open the report file
            ofstream outFile("report.txt");

            if (!outFile)
            {
                cout << "Unable to create report.txt.\n";
                break;
            }


            // report heading
            outFile << "==================================================\n";
            outFile << "   MPSP (MINIATURE PAINT SCHEME PLANNER) REPORT   \n";
            outFile << "==================================================\n\n";


            // report contents
            outFile << left << setw(30) << "REPORT ITEM"
                << right << setw(20) << "VALUE" << endl;

            outFile << string(50, '-') << endl;

            outFile << left << setw(30) << setfill('.')
                << "Base Color Selection:"
                << right << setw(20) << baseColor << endl;

            outFile << left << setw(30) << setfill('.')
                << "Color Theory Selected:"
                << right << setw(20) << theoryName << endl;

            outFile << left << setw(30) << setfill('.')
                << "Additional Colors Needed:"
                << right << setw(20) << extraColors << endl;

            outFile << fixed << setprecision(2);

            outFile << left << setw(30) << setfill('.')
                << "Preferred Paint Brand:"
                << right << setw(20) << brandName << endl;

            outFile << left << setw(30) << setfill('.')
                << "Cost per Paint Pot:"
                << right << "$" << setw(19) << potPrice << endl;

            outFile << left << setw(30) << setfill('.')
                << "Estimated Base Pots Needed:"
                << right << setw(20) << potsNeeded << endl;

            outFile << left << setw(30) << setfill('.')
                << "Primer Pots:"
                << right << setw(20) << primerPots << endl;

            outFile << left << setw(30) << setfill('.')
                << "Metallic Pots:"
                << right << setw(20) << metallicPots << endl;

            outFile << left << setw(30) << setfill('.')
                << "Wash Pots:"
                << right << setw(20) << washPots << endl;

            outFile << left << setw(30) << setfill('.')
                << "Additional Paint Cost:"
                << right << "$" << setw(19)
                << additionalPaintCost << endl;

            outFile << string(50, '-') << endl;

            outFile << left << setw(30) << setfill('.')
                << "Total Estimated Paint Cost:"
                << right << "$" << setw(19)
                << totalEstimatedCost << endl;

            outFile << setfill(' ');
            outFile << string(50, '=') << endl;


            // close the report file
            outFile.close();

            cout << "Report successfully compiled and saved to "
                << "'report.txt'!\n";

            break;
        }


        case 7: // exit program
        {
            cout << "Thank you for using MPSP!\n";
            running = false;

            break;
        }


		default: // invalid menu choice
        {
            cout << "Invalid menu choice. Please enter a number "
                << "from 1 through 7.\n";

            break;
        }
        }
    }


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
