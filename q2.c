#include <stdio.h>

// Initial account balance
int balance = 1000;
// Array of transactions (positive values are deposits, negative values are withdrawals)
int transactions[] = {200, -150, -500, -400, -50, -200, 300};

int main()
{
    // Calculate the number of transactions in the array
    size_t size = sizeof(transactions) / sizeof(transactions[0]);
    // Array to store unprocessed transactions
    int tobeprocessed[size];
    // Counter to keep track of unprocessed transactions
    int tobeprocessed_count = 0;

    // Loop through all transactions
    for (int i = 0; i < size; i++)
    {
        // If the transaction is a deposit
        if (transactions[i] > 0)
        {
            // Update balance with deposit amount
            balance += transactions[i];
            // Print success message
            printf("Transaction successful. %d AED has been deposited into your account. New balance is %d AED.\n", transactions[i], balance);
        }
        // If the transaction is a withdrawal
        else
        {
            // Check if withdrawal exceeds the current balance
            if ((balance + transactions[i]) < 0)
            {
                // Print invalid transaction message
                printf("Invalid transaction: Withdrawal of %d AED exceeds current balance of %d AED.\n", transactions[i], balance);
                // Store the unprocessed transaction
                tobeprocessed[tobeprocessed_count++] = transactions[i];
            }
            else
            {
                // Process the withdrawal and update balance
                balance += transactions[i];
                // Print success message
                printf("Transaction successful. %d AED has been withdrawn from your account. New balance is %d AED.\n", transactions[i], balance);
            }
        }

        // If balance reaches zero, stop processing further transactions
        if (balance == 0)
        {
            // Notify that the balance is zero
            printf("Balance is 0. No more transactions will be processed.\n");

            // Add remaining transactions to the unprocessed list
            for (int j = i + 1; j < size; j++)
            {
                tobeprocessed[tobeprocessed_count++] = transactions[j];
            }
            break; // Exit the loop
        }
    }

    // Print the final balance
    printf("\nYour balance: %d AED\n", balance);

    // Print the list of unprocessed transactions
    printf("Unprocessed transactions: ");
    for (int i = 0; i < tobeprocessed_count; i++)
    {
        printf("%d AED, ", tobeprocessed[i]);
    }
    printf("\n");

    return 0;
}
