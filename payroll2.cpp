// Employee Payroll Calculator
// Calculates monthly payroll after deductions
// Handles employees with or without a middle initial

#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
    // Declare variables
    string socialSecurityNumber;
    string firstName;
    string middleInitial;
    string lastName;
    string possibleMiddle;
    double annualSalary;
    int numberOfIndividualsCovered;
    char retirementParticipationFlag;

    double federalIncomeTax;
    double stateIncomeTax;
    double healthInsuranceCost;
    double retirementDeduction;
    double annualNetSalary;
    double monthlyNetSalary;
    string fullName;

    ifstream inputFile("payroll.in");
    ofstream outputFile("payroll.out");

    outputFile << fixed << showpoint << setprecision(2);

    while (true)
    {
        // Try to read name with optional middle initial
        inputFile >> socialSecurityNumber >> firstName >> possibleMiddle >> lastName;

        if (inputFile.fail()) break;

        if (possibleMiddle.length() == 1 && isalpha(possibleMiddle[0]))
        {
            middleInitial = possibleMiddle;
            inputFile >> annualSalary >> numberOfIndividualsCovered >> retirementParticipationFlag;
        }
        else
        {
            middleInitial = "";
            lastName = possibleMiddle;
            inputFile >> annualSalary >> numberOfIndividualsCovered >> retirementParticipationFlag;
        }

        if (inputFile.fail()) break;

        // Format full name
        if (middleInitial == "")
            fullName = lastName + ", " + firstName;
        else
            fullName = lastName + ", " + firstName + " " + middleInitial + ".";

        // Calculate federal income tax
        if (annualSalary < 5000)
            federalIncomeTax = 0;
        else if (annualSalary < 10000)
            federalIncomeTax = annualSalary * 0.06;
        else if (annualSalary < 20000)
            federalIncomeTax = annualSalary * 0.15;
        else if (annualSalary < 40000)
            federalIncomeTax = annualSalary * 0.20;
        else if (annualSalary < 60000)
            federalIncomeTax = annualSalary * 0.25;
        else
            federalIncomeTax = annualSalary * 0.30;

        // Other deductions
        stateIncomeTax = annualSalary * 0.06;
        healthInsuranceCost = numberOfIndividualsCovered * 100;
        retirementDeduction = (retirementParticipationFlag == 'Y' || retirementParticipationFlag == 'y') ? annualSalary * 0.06 : 0;

        // Net salary
        annualNetSalary = annualSalary - (federalIncomeTax + stateIncomeTax + healthInsuranceCost + retirementDeduction);
        monthlyNetSalary = annualNetSalary / 12;

        // Output result
        outputFile << "Social Security Number: " << socialSecurityNumber << endl;
        outputFile << "Name: " << fullName << endl;
        outputFile << "Monthly Payroll: $" << monthlyNetSalary << endl;
        outputFile << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
