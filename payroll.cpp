
//*
// Employee Payroll Calculator
// This program calculates monthly payroll after deductions
// for federal tax, state tax, health insurance, and retirement.
//*


#include <fstream>   // For file reading and writing
#include <iomanip>   // For controlling output formatting
#include <string>    // For using strings
using namespace std;

int main()
{
    // Variables to store employee information
    string socialSecurityNumber;
    string firstName;
    string middleInitial;
    string lastName;
    double annualSalary;
    int numberOfIndividualsCovered;
    char retirementParticipationFlag;

    // Variables for calculations
    double federalIncomeTax;
    double stateIncomeTax;
    double healthInsuranceCost;
    double retirementDeductionAmount;
    double annualNetSalaryAfterDeductions;
    double monthlyNetSalaryAfterDeductions;
    string fullNameFormatted;

    // File input and output streams
    ifstream inputFile;
    ofstream outputFile;

    // Open the input file for reading employee data
    inputFile.open("payroll.in");

    // Open the output file where results will be saved
    outputFile.open("payroll.out");

    // Format output numbers to show decimals (e.g., 1000.00)
    outputFile << fixed << showpoint;

    // Loop through each employee's data until there are no more records to read
    while (inputFile >> socialSecurityNumber >> firstName >> middleInitial >> lastName >> annualSalary >> numberOfIndividualsCovered >> retirementParticipationFlag)
    {
        // Format the full name as: "LastName, FirstName M."
        fullNameFormatted = lastName + ", " + firstName + " " + middleInitial + ".";

        // Calculate federal tax based on salary brackets
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

        // Calculate state income tax at 6% of salary
        stateIncomeTax = annualSalary * 0.06;

        // Calculate health insurance cost ($100 per covered individual)
        healthInsuranceCost = numberOfIndividualsCovered * 100;

        // Calculate retirement deduction if employee participates in retirement plan
        if (retirementParticipationFlag == 'Y' || retirementParticipationFlag == 'y')
            retirementDeductionAmount = annualSalary * 0.06;
        else
            retirementDeductionAmount = 0;

        // Calculate the annual net salary after all deductions
        annualNetSalaryAfterDeductions = annualSalary - (federalIncomeTax + stateIncomeTax + healthInsuranceCost + retirementDeductionAmount);

        // Calculate the monthly net salary
        monthlyNetSalaryAfterDeductions = annualNetSalaryAfterDeductions / 12;

        // Output the results to the output file with 2 decimal places
        outputFile << "Social Security Number: " << socialSecurityNumber << endl;
        outputFile << "Name: " << fullNameFormatted << endl;
        outputFile << "Monthly Payroll: $" << setprecision(2) << monthlyNetSalaryAfterDeductions << endl;
        outputFile << endl;  // Blank line between employees
    }

    // Close both input and output files
    inputFile.close();
    outputFile.close();

    return 0;
}
