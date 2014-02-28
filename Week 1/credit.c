#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long long cc;
    int evenDigit;
    int oddDigit;
    int total = 0;
    bool valid = 0;
    long long creditCheck;

    // get user credit card number
    printf("Number: ");
    do
    {
    cc = GetLongLong();
    }
    while (cc < 0);
    creditCheck = cc;

    // luhn's algorithm
    while (cc > 0)
    {
        evenDigit = (cc % 100) / 10;
        oddDigit = (cc % 10);
        cc /= 100;

        // add digits of multiplication of evenDigit by 2
        evenDigit *= 2;
        if (evenDigit / 10 == 1)
        {
            total += 1;
            total += evenDigit % 10;
        }
        else
        {
            total += evenDigit;
        }

        // add oddDigit
        total += oddDigit;
    }

    // check if the credit card is valid
    if (total % 10 == 0)
    {
        valid = 1;
    }
    else
    {
        printf("INVALID\n");
    }

    // check type of credit card
    if (valid == 1)
    {
        if (creditCheck / 1000000000000000 >= 1)
        {
            switch (creditCheck / 100000000000000)
            {
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    printf("MASTERCARD\n");
                    break;
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                case 48:
                case 49:
                    printf("VISA\n");
                    break;
            }

        }
        else
        {
            if (creditCheck / 100000000000000 > 1)
            {
                switch (creditCheck / 10000000000000)
                {
                    case 34:
                    case 37:
                    printf("AMEX\n");
                    break;
                }
            }
            else
            {
                if (creditCheck / 1000000000000 == 4)
                {
                printf("VISA\n");
                }
            }
        }
    }
}
