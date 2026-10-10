
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <cstdlib>

using namespace std;

const double PI = 3.14159265358979323846;

struct Calculation {
    string expression;
    double result;
};

vector<Calculation> history;

// -------------------- Input helpers --------------------

void clearLine() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getInt(const string& prompt, int minimum, int maximum) {
    int value;

    while (true) {
        cout << prompt;

        if (cin >> value) {
            clearLine();

            if (value >= minimum && value <= maximum) {
                return value;
            }

            cout << "Enter a number between "
                 << minimum << " and " << maximum << ".\n";
        } else {
            if (cin.eof()) {
                exit(0);
            }

            cout << "Invalid input. Enter a whole number.\n";
            cin.clear();
            clearLine();
        }
    }
}

double getDouble(const string& prompt) {
    double value;

    while (true) {
        cout << prompt;

        if (cin >> value) {
            clearLine();

            if (isfinite(value)) {
                return value;
            }

            cout << "Please enter a finite number.\n";
        } else {
            if (cin.eof()) {
                exit(0);
            }

            cout << "Invalid input. Enter a number.\n";
            cin.clear();
            clearLine();
        }
    }
}

void saveCalculation(const string& expression, double result) {
    history.push_back({expression, result});
}

void showResult(const string& expression, double result) {
    if (!isfinite(result)) {
        cout << "\nError: the result is outside the supported numeric range.\n";
        return;
    }

    cout << "\n" << expression << " = "
         << setprecision(12) << result << "\n";

    saveCalculation(expression, result);
}

// -------------------- Basic calculator --------------------

void basicCalculator() {
    cout << "\n========== BASIC CALCULATOR ==========\n";

    double a = getDouble("Enter first number: ");
    double b = getDouble("Enter second number: ");

    cout << "\nChoose operation:\n";
    cout << "1. Addition (+)\n";
    cout << "2. Subtraction (-)\n";
    cout << "3. Multiplication (*)\n";
    cout << "4. Division (/)\n";
    cout << "5. Modulus (remainder)\n";

    int choice = getInt("Select: ", 1, 5);
    double result = 0;
    string expression;

    switch (choice) {
        case 1:
            result = a + b;
            expression = to_string(a) + " + " + to_string(b);
            break;

        case 2:
            result = a - b;
            expression = to_string(a) + " - " + to_string(b);
            break;

        case 3:
            result = a * b;
            expression = to_string(a) + " * " + to_string(b);
            break;

        case 4:
            if (b == 0) {
                cout << "Error: division by zero is not allowed.\n";
                return;
            }

            result = a / b;
            expression = to_string(a) + " / " + to_string(b);
            break;

        case 5:
            if (b == 0) {
                cout << "Error: modulus by zero is not allowed.\n";
                return;
            }

            result = fmod(a, b);
            expression = to_string(a) + " mod " + to_string(b);
            break;
    }

    showResult(expression, result);
}

// -------------------- Powers and roots --------------------

void powerAndRoot() {
    cout << "\n========== POWERS AND ROOTS ==========\n";
    cout << "1. Power (x^y)\n";
    cout << "2. Square root\n";
    cout << "3. Cube root\n";
    cout << "4. nth root\n";

    int choice = getInt("Select: ", 1, 4);
    double x, y, result;
    string expression;

    switch (choice) {
        case 1:
            x = getDouble("Enter base: ");
            y = getDouble("Enter exponent: ");

            if (x == 0 && y < 0) {
                cout << "Error: zero cannot have a negative exponent.\n";
                return;
            }

            result = pow(x, y);
            expression = to_string(x) + " ^ " + to_string(y);
            break;

        case 2:
            x = getDouble("Enter number: ");

            if (x < 0) {
                cout << "Error: square root requires a non-negative number.\n";
                return;
            }

            result = sqrt(x);
            expression = "sqrt(" + to_string(x) + ")";
            break;

        case 3:
            x = getDouble("Enter number: ");
            result = cbrt(x);
            expression = "cbrt(" + to_string(x) + ")";
            break;

        case 4:
            x = getDouble("Enter number: ");
            y = getDouble("Enter root degree (non-zero): ");

            if (y == 0) {
                cout << "Error: root degree cannot be zero.\n";
                return;
            }

            if (x < 0) {
                if (y != trunc(y) ||
                    fmod(fabs(y), 2.0) != 1.0) {
                    cout << "Error: a negative number requires an "
                         << "odd integer root degree.\n";
                    return;
                }

                result = -pow(-x, 1.0 / y);
            } else {
                result = pow(x, 1.0 / y);
            }

            expression = to_string(y) + "th root of " + to_string(x);
            break;

        default:
            return;
    }

    showResult(expression, result);
}

// -------------------- Factorial --------------------

void factorialCalculator() {
    cout << "\n========== FACTORIAL ==========\n";

    int n = getInt("Enter a whole number (0-170): ", 0, 170);

    long double result = 1;

    for (int i = 2; i <= n; ++i) {
        result *= i;
    }

    cout << n << "! = "
         << setprecision(15) << result << "\n";

    // Store a double approximation in history.
    saveCalculation(to_string(n) + "!", static_cast<double>(result));
}

// -------------------- Percentage --------------------

void percentageCalculator() {
    cout << "\n========== PERCENTAGE CALCULATOR ==========\n";
    cout << "1. Find X% of a number\n";
    cout << "2. What percentage is X of Y?\n";
    cout << "3. Percentage increase/decrease\n";

    int choice = getInt("Select: ", 1, 3);
    double a, b, result;
    string expression;

    if (choice == 1) {
        a = getDouble("Enter percentage: ");
        b = getDouble("Enter number: ");

        result = (a / 100.0) * b;
        expression = to_string(a) + "% of " + to_string(b);
    } else if (choice == 2) {
        a = getDouble("Enter part: ");
        b = getDouble("Enter total: ");

        if (b == 0) {
            cout << "Error: total cannot be zero.\n";
            return;
        }

        result = (a / b) * 100.0;
        expression = to_string(a) + " is what % of " + to_string(b);
    } else {
        a = getDouble("Enter original value: ");
        b = getDouble("Enter new value: ");

        if (a == 0) {
            cout << "Error: original value cannot be zero.\n";
            return;
        }

        result = ((b - a) / fabs(a)) * 100.0;
        expression = "Percentage change from " +
                     to_string(a) + " to " + to_string(b);
    }

    showResult(expression, result);

    if (choice == 3 && isfinite(result)) {
        if (result > 0) {
            cout << "This is an increase.\n";
        } else if (result < 0) {
            cout << "This is a decrease.\n";
        } else {
            cout << "There is no change.\n";
        }
    }
}

// -------------------- Trigonometry --------------------

void trigonometryCalculator() {
    cout << "\n========== TRIGONOMETRY ==========\n";
    cout << "1. sin\n";
    cout << "2. cos\n";
    cout << "3. tan\n";
    cout << "4. asin\n";
    cout << "5. acos\n";
    cout << "6. atan\n";

    int choice = getInt("Select: ", 1, 6);
    double x, result;
    string expression;

    if (choice <= 3) {
        x = getDouble("Enter angle in degrees: ");
        double radians = x * PI / 180.0;

        if (choice == 1) {
            result = sin(radians);
            expression = "sin(" + to_string(x) + " degrees)";
        } else if (choice == 2) {
            result = cos(radians);
            expression = "cos(" + to_string(x) + " degrees)";
        } else {
            // tan is undefined at odd multiples of 90 degrees.
            double nearest = round((x - 90.0) / 180.0);
            double pole = 90.0 + nearest * 180.0;

            if (fabs(x - pole) < 1e-10) {
                cout << "Error: tangent is undefined at this angle.\n";
                return;
            }

            result = tan(radians);
            expression = "tan(" + to_string(x) + " degrees)";
        }
    } else {
        x = getDouble("Enter value between -1 and 1: ");

        if ((choice == 4 || choice == 5) &&
            (x < -1 || x > 1)) {
            cout << "Error: input must be between -1 and 1.\n";
            return;
        }

        if (choice == 4) {
            result = asin(x) * 180.0 / PI;
            expression = "asin(" + to_string(x) + ")";
        } else if (choice == 5) {
            result = acos(x) * 180.0 / PI;
            expression = "acos(" + to_string(x) + ")";
        } else {
            result = atan(x) * 180.0 / PI;
            expression = "atan(" + to_string(x) + ")";
        }

        expression += " in degrees";
    }

    showResult(expression, result);
}

// -------------------- Logarithms --------------------

void logarithmCalculator() {
    cout << "\n========== LOGARITHMS ==========\n";
    cout << "1. Natural logarithm (ln x)\n";
    cout << "2. Base-10 logarithm (log10 x)\n";
    cout << "3. Logarithm with custom base\n";

    int choice = getInt("Select: ", 1, 3);
    double x, base, result;
    string expression;

    x = getDouble("Enter positive number: ");

    if (x <= 0) {
        cout << "Error: logarithm input must be positive.\n";
        return;
    }

    if (choice == 1) {
        result = log(x);
        expression = "ln(" + to_string(x) + ")";
    } else if (choice == 2) {
        result = log10(x);
        expression = "log10(" + to_string(x) + ")";
    } else {
        base = getDouble("Enter logarithm base: ");

        if (base <= 0 || base == 1) {
            cout << "Error: base must be positive and cannot equal 1.\n";
            return;
        }

        result = log(x) / log(base);
        expression = "log base " + to_string(base) +
                     " of " + to_string(x);
    }

    showResult(expression, result);
}

// -------------------- Absolute value and rounding --------------------

void roundingTools() {
    cout << "\n========== ROUNDING TOOLS ==========\n";
    cout << "1. Absolute value\n";
    cout << "2. Floor (round down)\n";
    cout << "3. Ceiling (round up)\n";
    cout << "4. Round to nearest integer\n";

    int choice = getInt("Select: ", 1, 4);
    double x = getDouble("Enter number: ");
    double result;
    string expression;

    switch (choice) {
        case 1:
            result = fabs(x);
            expression = "abs(" + to_string(x) + ")";
            break;
        case 2:
            result = floor(x);
            expression = "floor(" + to_string(x) + ")";
            break;
        case 3:
            result = ceil(x);
            expression = "ceil(" + to_string(x) + ")";
            break;
        case 4:
            result = round(x);
            expression = "round(" + to_string(x) + ")";
            break;
        default:
            return;
    }

    showResult(expression, result);
}

// -------------------- History --------------------

void showHistory() {
    cout << "\n========== CALCULATION HISTORY ==========\n";

    if (history.empty()) {
        cout << "No calculations recorded yet.\n";
        return;
    }

    for (size_t i = 0; i < history.size(); ++i) {
        cout << i + 1 << ". " << history[i].expression
             << " = " << setprecision(12)
             << history[i].result << "\n";
    }
}

void clearHistory() {
    if (history.empty()) {
        cout << "\nHistory is already empty.\n";
        return;
    }

    cout << "\nAre you sure you want to clear history?\n";
    cout << "1. Yes\n";
    cout << "2. No\n";

    int choice = getInt("Select: ", 1, 2);

    if (choice == 1) {
        history.clear();
        cout << "Calculation history cleared.\n";
    } else {
        cout << "History was not changed.\n";
    }
}

// -------------------- Main menu --------------------

void showMenu() {
    cout << "\n";
    cout << "============================================\n";
    cout << "          HEAVY CALCULATOR PRO\n";
    cout << "============================================\n";
    cout << "1.  Basic arithmetic\n";
    cout << "2.  Powers and roots\n";
    cout << "3.  Factorial\n";
    cout << "4.  Percentage calculator\n";
    cout << "5.  Trigonometry\n";
    cout << "6.  Logarithms\n";
    cout << "7.  Rounding and absolute value\n";
    cout << "8.  View calculation history\n";
    cout << "9.  Clear calculation history\n";
    cout << "10. About this calculator\n";
    cout << "11. Exit\n";
    cout << "============================================\n";
}

void showAbout() {
    cout << "\n========== ABOUT ==========\n";
    cout << "Heavy Calculator Pro\n";
    cout << "A C++ scientific calculator project.\n";
    cout << "Built using functions, loops, vectors, structs,\n";
    cout << "input validation, and the cmath library.\n";
    cout << "Calculation history lasts for this session only.\n";
}

int main() {
    cout << fixed;
    cout << "Welcome to Heavy Calculator Pro!\n";

    bool running = true;

    while (running) {
        showMenu();

        int choice = getInt("Choose an option (1-11): ", 1, 11);

        switch (choice) {
            case 1:
                basicCalculator();
                break;
            case 2:
                powerAndRoot();
                break;
            case 3:
                factorialCalculator();
                break;
            case 4:
                percentageCalculator();
                break;
            case 5:
                trigonometryCalculator();
                break;
            case 6:
                logarithmCalculator();
                break;
            case 7:
                roundingTools();
                break;
            case 8:
                showHistory();
                break;
            case 9:
                clearHistory();
                break;
            case 10:
                showAbout();
                break;
            case 11: {
                cout << "\nAre you sure you want to exit?\n";
                cout << "1. Yes\n";
                cout << "2. No\n";

                int confirm = getInt("Choose: ", 1, 2);

                if (confirm == 1) {
                    running = false;
                }
                break;
            }
        }

        if (running && choice >= 1 && choice <= 7) {
            cout << "\n====================================\n";
            cout << "What would you like to do next?\n";
            cout << "1. Try another calculation\n";
            cout << "2. Return to main menu\n";
            cout << "3. Exit calculator\n";

            int next = getInt("Choose (1-3): ", 1, 3);

            if (next == 1) {
                // Repeat the last selected calculation
                switch (choice) {
                    case 1: basicCalculator(); break;
                    case 2: powerAndRoot(); break;
                    case 3: factorialCalculator(); break;
                    case 4: percentageCalculator(); break;
                    case 5: trigonometryCalculator(); break;
                    case 6: logarithmCalculator(); break;
                    case 7: roundingTools(); break;
                }
            } else if (next == 3) {
                running = false;
            }
        }
    }

    cout << "\nThank you for using Heavy Calculator Pro!\n";
    cout << "Keep learning C++!\n";

    return 0;
}
