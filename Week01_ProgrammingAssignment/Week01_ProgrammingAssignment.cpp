#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

// This defines a type, not a global variable.
enum PaintBrand
{
    ARMY_PAINTER = 1,
    VALLEJO = 2,
    CITADEL = 3
};

void displayOpeningBanner()
{
    cout << "==================================================\n";
    cout << "  WELCOME TO MPSP - MINIATURE PAINT SCHEME PLANNER\n";
    cout << "==================================================\n";
    cout << "Choose your colors and paints to estimate your cost.\n";
}

// Check that input contains at least one nonblank character.
bool isValidText(string text)
{
    for (int index = 0; index < text.length(); index++)
    {
        if (text[index] != ' ' && text[index] != '\t')
        {
            return true;
        }
    }

    return false;
}

// Read a complete nonempty text answer.
bool readText(string prompt, string& answer)
{
    cout << prompt;
    getline(cin, answer);

    while (cin && !isValidText(answer))
    {
        cout << "Please enter a nonempty answer: ";
        getline(cin, answer);
    }

    return !cin.fail();
}

// Collect and validate a whole number within the allowed range.
bool readInteger(string prompt, int minimum, int maximum, int& answer)
{
    const int INPUT_LIMIT = 10000;

    cout << prompt;
    cin >> answer;

    while (cin.fail() || answer < minimum || answer > maximum ||
        (!cin.eof() && cin.peek() != '\n'))
    {
        if (cin.eof())
        {
            return false;
        }

        cin.clear();
        cin.ignore(INPUT_LIMIT, '\n');

        cout << "Enter a whole number from " << minimum
            << " through " << maximum << ": ";
        cin >> answer;
    }

    // Remove the newline before any later getline call.
    if (!cin.eof())
    {
        cin.ignore(INPUT_LIMIT, '\n');
    }

    return true;
}

// Collect and validate a nonnegative price.
bool readPrice(string prompt, double& price)
{
    const int INPUT_LIMIT = 10000;

    cout << prompt;
    cin >> price;

    while (cin.fail() || price < 0 ||
        (!cin.eof() && cin.peek() != '\n'))
    {
        if (cin.eof())
        {
            return false;
        }

        cin.clear();
        cin.ignore(INPUT_LIMIT, '\n');

        cout << "Enter a price of 0 or more: $";
        cin >> price;
    }

    if (!cin.eof())
    {
        cin.ignore(INPUT_LIMIT, '\n');
    }

    return true;
}

void displayMainMenu(string baseColor, string theoryName, string brandName)
{
    cout << "\n==================================================\n";
    cout << "                     MAIN MENU\n";
    cout << "==================================================\n";
    cout << "1. Select base color: " << baseColor << endl;
    cout << "2. Select color theory: " << theoryName << endl;
    cout << "3. Select paint brand: " << brandName << endl;
    cout << "4. Select additional paints\n";
    cout << "5. View report\n";
    cout << "6. Output report file\n";
    cout << "7. Change text color\n";
    cout << "8. Display opening banner\n";
    cout << "9. Exit\n";
    cout << "10. Enter three extra paint prices\n";
}

bool selectBaseColor(string& baseColor)
{
    return readText("\nEnter your base paint color: ", baseColor);
}

bool selectColorTheory(int& extraColors, string& theoryName)
{
    const int MIN_CHOICE = 1;
    const int MAX_CHOICE = 6;
    int choice = 0;

    cout << "\nChoose your color theory:\n";
    cout << "1. Analogous\n";
    cout << "2. Complementary\n";
    cout << "3. Split Complementary\n";
    cout << "4. Triadic\n";
    cout << "5. Tetradic\n";
    cout << "6. Square\n";

    if (!readInteger("Enter your choice: ", MIN_CHOICE, MAX_CHOICE, choice))
    {
        return false;
    }

    // Keep Dakota's existing color-theory selections and counts.
    switch (choice)
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
    }

    cout << "Selected " << theoryName << ".\n";
    return true;
}

bool selectPaintBrand(double& potPrice, string& brandName)
{
    const double ARMY_PAINTER_PRICE = 5.13;
    const double VALLEJO_PRICE = 3.39;
    const double CITADEL_PRICE = 4.75;

    int choice = 0;

    cout << "\nChoose your paint brand:\n";
    cout << ARMY_PAINTER << ". The Army Painter\n";
    cout << VALLEJO << ". Vallejo\n";
    cout << CITADEL << ". Citadel Colour\n";

    if (!readInteger("Enter your choice: ", ARMY_PAINTER, CITADEL, choice))
    {
        return false;
    }

    PaintBrand selectedBrand = static_cast<PaintBrand>(choice);

    // Use the enum in a decision structure.
    switch (selectedBrand)
    {
    case ARMY_PAINTER:
        brandName = "The Army Painter";
        potPrice = ARMY_PAINTER_PRICE;
        break;

    case VALLEJO:
        brandName = "Vallejo";
        potPrice = VALLEJO_PRICE;
        break;

    case CITADEL:
        brandName = "Citadel Colour";
        potPrice = CITADEL_PRICE;
        break;
    }

    cout << "Selected " << brandName << ".\n";
    return true;
}

// Collect a yes/no answer for one optional paint.
bool readYesNo(string prompt, char& answer)
{
    string text;

    do
    {
        if (!readText(prompt, text))
        {
            return false;
        }

        if (text.length() == 1 &&
            (text[0] == 'y' || text[0] == 'Y' ||
                text[0] == 'n' || text[0] == 'N'))
        {
            answer = text[0];
            return true;
        }

        cout << "Please enter y or n.\n";
    } while (true);
}

// Fill the entire array before allowing it to be used in reports.
bool fillPaintPrices(double prices[], int size)
{
    for (int index = 0; index < size; index++)
    {
        cout << "\nExtra paint " << index + 1 << endl;

        if (!readPrice("Enter the price without a dollar sign: ", prices[index]))
        {
            return false;
        }
    }

    return true;
}

// Calculate a total using the elements stored in the array.
double calculatePaintTotal(const double prices[], int size)
{
    double total = 0.0;

    for (int index = 0; index < size; index++)
    {
        total = total + prices[index];
    }

    return total;
}

double calculateTotalCost(int potsNeeded, double potPrice,
    double optionalPaintCost, double extraPaintCost)
{
    return potsNeeded * potPrice + optionalPaintCost + extraPaintCost;
}

// Use this function for both console output and file output.
void writeReportTable(ostream& report, string baseColor,
    string theoryName, string brandName, int potsNeeded,
    double potPrice, int primerPots, int metallicPots, int washPots,
    double optionalPaintCost, const double extraPrices[],
    int size, bool extraPricesEntered, double totalCost)
{
    const int LABEL_WIDTH = 32;
    const int VALUE_WIDTH = 20;
    const int LINE_WIDTH = LABEL_WIDTH + VALUE_WIDTH;
    const int MONEY_DECIMALS = 2;

    report << fixed << setprecision(MONEY_DECIMALS);
    report << "\nMINIATURE PAINT SCHEME PLANNER REPORT\n";
    report << string(LINE_WIDTH, '=') << endl;
    report << left << setw(LABEL_WIDTH) << "REPORT ITEM"
        << right << setw(VALUE_WIDTH) << "VALUE" << endl;
    report << string(LINE_WIDTH, '-') << endl;

    report << left << setw(LABEL_WIDTH) << "Base color:"
        << right << setw(VALUE_WIDTH) << baseColor << endl;
    report << left << setw(LABEL_WIDTH) << "Color theory:"
        << right << setw(VALUE_WIDTH) << theoryName << endl;
    report << left << setw(LABEL_WIDTH) << "Paint brand:"
        << right << setw(VALUE_WIDTH) << brandName << endl;
    report << left << setw(LABEL_WIDTH) << "Base paint pots:"
        << right << setw(VALUE_WIDTH) << potsNeeded << endl;
    report << left << setw(LABEL_WIDTH) << "Price per pot ($):"
        << right << setw(VALUE_WIDTH) << potPrice << endl;
    report << left << setw(LABEL_WIDTH) << "Primer pots:"
        << right << setw(VALUE_WIDTH) << primerPots << endl;
    report << left << setw(LABEL_WIDTH) << "Metallic pots:"
        << right << setw(VALUE_WIDTH) << metallicPots << endl;
    report << left << setw(LABEL_WIDTH) << "Wash pots:"
        << right << setw(VALUE_WIDTH) << washPots << endl;
    report << left << setw(LABEL_WIDTH) << "Optional paint cost ($):"
        << right << setw(VALUE_WIDTH) << optionalPaintCost << endl;

    report << string(LINE_WIDTH, '-') << endl;
    report << "EXTRA PAINT PURCHASES\n";

    if (extraPricesEntered)
    {
        for (int index = 0; index < size; index++)
        {
            report << "Extra paint " << index + 1 << " ($)"
                << right << setw(VALUE_WIDTH)
                << extraPrices[index] << endl;
        }

        report << left << setw(LABEL_WIDTH) << "Extra paint total ($):"
            << right << setw(VALUE_WIDTH)
            << calculatePaintTotal(extraPrices, size) << endl;
    }
    else
    {
        report << "Extra paint prices have not been entered.\n";
    }

    report << string(LINE_WIDTH, '-') << endl;
    report << left << setw(LABEL_WIDTH) << "Total estimated cost ($):"
        << right << setw(VALUE_WIDTH) << totalCost << endl;
    report << string(LINE_WIDTH, '=') << endl;
}

bool saveReport(string baseColor, string theoryName, string brandName,
    int potsNeeded, double potPrice, int primerPots, int metallicPots,
    int washPots, double optionalPaintCost, const double extraPrices[],
    int size, bool extraPricesEntered, double totalCost)
{
    ofstream report("report.txt");

    if (!report)
    {
        return false;
    }

    writeReportTable(report, baseColor, theoryName, brandName,
        potsNeeded, potPrice, primerPots, metallicPots, washPots,
        optionalPaintCost, extraPrices, size, extraPricesEntered, totalCost);

    report.close();
    return !report.fail();
}

void changeTextColor()
{
    const int COLOR_COUNT = 5;
    const int MIN_CHOICE = 1;
    const int colors[COLOR_COUNT] = { 9, 10, 11, 12, 14 };

    int choice = 0;

    cout << "\nChoose a text color:\n";
    cout << "1. Blue\n";
    cout << "2. Green\n";
    cout << "3. Cyan\n";
    cout << "4. Red\n";
    cout << "5. Yellow\n";

    if (readInteger("Enter your choice: ", MIN_CHOICE, COLOR_COUNT, choice))
    {
        SetConsoleTextAttribute(
            GetStdHandle(STD_OUTPUT_HANDLE), colors[choice - 1]);

        cout << "Text color changed.\n";
    }
}

int main()
{
    const int EXTRA_PAINT_COUNT = 3;
    const int MIN_MENU_CHOICE = 1;
    const int MAX_MENU_CHOICE = 10;
    const int BASE_COLOR_POTS = 1;
    const int ONE_POT = 1;

    const double PRIMER_PRICE = 9.99;
    const double METALLIC_PRICE = 7.75;
    const double WASH_PRICE = 7.75;

    string baseColor;
    string theoryName;
    string brandName;

    int extraColors = 0;
    int menuChoice = 0;
    int primerPots = 0;
    int metallicPots = 0;
    int washPots = 0;

    double potPrice = 0.0;
    double extraPaintPrices[EXTRA_PAINT_COUNT] = {};

    bool baseColorSelected = false;
    bool theorySelected = false;
    bool brandSelected = false;
    bool extraPricesEntered = false;
    bool running = true;

    displayOpeningBanner();

    do
    {
        displayMainMenu(baseColor, theoryName, brandName);

        if (!readInteger("Enter your choice: ",
            MIN_MENU_CHOICE, MAX_MENU_CHOICE, menuChoice))
        {
            break;
        }

        switch (menuChoice)
        {
        case 1:
            if (selectBaseColor(baseColor))
            {
                baseColorSelected = true;
            }
            else
            {
                running = false;
            }
            break;

        case 2:
            if (selectColorTheory(extraColors, theoryName))
            {
                theorySelected = true;
            }
            else
            {
                running = false;
            }
            break;

        case 3:
            if (selectPaintBrand(potPrice, brandName))
            {
                brandSelected = true;
            }
            else
            {
                running = false;
            }
            break;

        case 4:
        {
            char answer = 'n';

            if (!readYesNo("\nAdd primer for $9.99? (y/n): ", answer))
            {
                running = false;
                break;
            }

            // A lowercase or uppercase yes adds one primer pot.
            if ((answer == 'y' || answer == 'Y') && !cin.fail())
            {
                primerPots = ONE_POT;
            }
            else
            {
                primerPots = 0;
            }

            if (!readYesNo("Add metallic paint for $7.75? (y/n): ", answer))
            {
                running = false;
                break;
            }

            // A lowercase or uppercase yes adds one metallic pot.
            if ((answer == 'y' || answer == 'Y') && !cin.fail())
            {
                metallicPots = ONE_POT;
            }
            else
            {
                metallicPots = 0;
            }

            if (!readYesNo("Add wash for $7.75? (y/n): ", answer))
            {
                running = false;
                break;
            }

            if (answer == 'y' || answer == 'Y')
            {
                washPots = ONE_POT;
            }
            else
            {
                washPots = 0;
            }

            cout << "Optional paint selections saved.\n";
            break;
        }

        case 5:
        case 6:
        {
            if (!baseColorSelected || !theorySelected || !brandSelected)
            {
                cout << "Select a base color, color theory, "
                    << "and paint brand first.\n";
                break;
            }

            int potsNeeded = extraColors + BASE_COLOR_POTS;

            double optionalPaintCost =
                primerPots * PRIMER_PRICE +
                metallicPots * METALLIC_PRICE +
                washPots * WASH_PRICE;

            double extraPaintCost = 0.0;

            // Only use the array after all entries have been filled.
            if (extraPricesEntered)
            {
                extraPaintCost =
                    calculatePaintTotal(extraPaintPrices, EXTRA_PAINT_COUNT);
            }

            double totalCost = calculateTotalCost(
                potsNeeded, potPrice, optionalPaintCost, extraPaintCost);

            if (menuChoice == 5)
            {
                writeReportTable(cout, baseColor, theoryName, brandName,
                    potsNeeded, potPrice, primerPots, metallicPots,
                    washPots, optionalPaintCost, extraPaintPrices,
                    EXTRA_PAINT_COUNT, extraPricesEntered, totalCost);
            }
            else
            {
                if (saveReport(baseColor, theoryName, brandName,
                    potsNeeded, potPrice, primerPots, metallicPots,
                    washPots, optionalPaintCost, extraPaintPrices,
                    EXTRA_PAINT_COUNT, extraPricesEntered, totalCost))
                {
                    cout << "Report saved to report.txt.\n";
                }
                else
                {
                    cout << "Unable to save report.txt.\n";
                }
            }

            break;
        }

        case 7:
            changeTextColor();
            break;

        case 8:
            displayOpeningBanner();
            break;

        case 9:
            cout << "Thank you for using MPSP!\n";
            running = false;
            break;

        case 10:
            extraPricesEntered =
                fillPaintPrices(extraPaintPrices, EXTRA_PAINT_COUNT);

            if (extraPricesEntered)
            {
                cout << "All three extra paint prices saved.\n";
            }
            else
            {
                cout << "Input ended before all prices were entered.\n";
                running = false;
            }
            break;
        }

    } while (running);

    return 0;
}