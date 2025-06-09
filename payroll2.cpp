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
    char middleInitial;
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
    ifstream inputFile("payroll.in");
    ofstream outputFile("payroll.out");

    // Format output numbers to show decimals (e.g., 1000.00)
    outputFile << fixed << showpoint;

    // Loop through each employee's data
    while (inputFile >> socialSecurityNumber >> firstName >> middleInitial >> lastName
           >> annualSalary >> numberOfIndividualsCovered >> retirementParticipationFlag)
    {
        // Check if middle initial is valid (not just a placeholder like '-')
        if (middleInitial == '-')
            fullNameFormatted = lastName + ", " + firstName;
        else
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

        // State income tax at 6%
        stateIncomeTax = annualSalary * 0.06;

        // Health insurance cost ($100 per covered individual)
        healthInsuranceCost = numberOfIndividualsCovered * 100;

        // Retirement deduction if applicable
        if (retirementParticipationFlag == 'Y' || retirementParticipationFlag == 'y')
            retirementDeductionAmount = annualSalary * 0.06;
        else
            retirementDeductionAmount = 0;

        // Net salary after all deductions
        annualNetSalaryAfterDeductions = annualSalary - (federalIncomeTax + stateIncomeTax + healthInsuranceCost + retirementDeductionAmount);
        monthlyNetSalaryAfterDeductions = annualNetSalaryAfterDeductions / 12;

        // Output employee payroll information
        outputFile << "Social Security Number: " << socialSecurityNumber << endl;
        outputFile << "Name: " << fullNameFormatted << endl;
        outputFile << "Monthly Payroll: $" << setprecision(2) << monthlyNetSalaryAfterDeductions << endl;
        outputFile << endl;  // Blank line between employees
    }

    // Close files
    inputFile.close();
    outputFile.close();

    return 0;
}
