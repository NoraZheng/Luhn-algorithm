#include <cs50.h> // CS50 Library for C https://cs50.readthedocs.io/libraries/cs50/c/
#include <math.h>
#include <stdio.h>

string getCardType(long cardNumber);
bool isValid(long cardNumber);
int getFirstDigit(long num);
int getFirstTwoDigits(long cardNumber);
int countDigit(long number);


int main(void)
{
    long cardNumber = get_long("Card number:");
    printf("%s", getCardType(cardNumber));
}

string getCardType(long cardNumber)
{
    int firstDigit = getFirstDigit(cardNumber);
    int firstTwoDigits = getFirstTwoDigits(cardNumber);

    if (isValid(cardNumber))
    {
        switch (countDigit(cardNumber))
        {
            case 13:
                return (firstDigit == 4 ? "VISA\n" : "INVALID\n");
                break;

            case 15:
                return (firstTwoDigits  == 34 || firstTwoDigits  == 37 ? "AMEX\n" : "INVALID\n");
                break;

            case 16:
                if (firstDigit == 4)
                {
                    return "VISA\n";
                }
                else if (firstTwoDigits > 50 && firstTwoDigits < 56)
                {
                    return "MASTERCARD\n";
                }
                else
                {
                    return "INVALID\n";
                }
                break;

            default:
                return "INVALID\n";
        }
    }
    else
    {
        return "INVALID\n";
    }
}

bool isValid(long num)
{
    int evenSum = 0;
    int oddSum = 0;
    int digit = countDigit(num);

    // Process the number until only 1 digit is left
    while (num > 9)
    {
        // Loop through all the digits, starting from the last one
        for (int i = 1; i <= digit; i++)
        {
            // Current digit that's being processed
            int currentDigit = num % 10;
            // Every other digit starting with the number’s second-to-last digit
            if (i % 2 == 0)
                // Multiply by 2. And add to evenSum. If product > 9, add digits of the product instead
            {
                if (currentDigit > 4)
                {
                    // E.g. current digit is 8
                    // 8 * 2 = 16
                    // add 1 + 6 to evenSum
                    evenSum += currentDigit * 2 % 10 + 1;
                }
                else
                {
                    evenSum += currentDigit * 2;
                }
            }
            else
            {
                oddSum += currentDigit;
            }
            // Move on to the next digit. Discarding currentDigit.
            num = num / 10;
        }
    }
    // Return true if the total modulo 10 is congruent to 0
    return ((oddSum + evenSum) % 10 == 0 ? true : false);
}

int getFirstDigit(long num)
{
    while (num > 9)
    {
        num = num / 10;
    }
    return num;
}

int getFirstTwoDigits(long num)
{
    while (num > 99)
    {
        num = num / 10;
    }
    return num;
}

// Helper function to count the number of digits of a card number
int countDigit(long number)
{
    return floor(log10(number) + 1);
}