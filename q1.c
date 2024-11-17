// header files
#include <stdio.h>
#include <stdbool.h>

// constants
#define SIZE 24
#define nRows 8
#define nCols 3

// Given function prototypes
void print_array(int array[], int length);
void print_matrix(int mat[][nCols], int rows);


// Function prototypes
bool isValid(const int arr[], int length, int pos);
void remove_element(int arr[], int length, int pos);
void insert_element(int arr[], int length, int pos, int value);
void reshape(const int arr[], int length, int arr2d[nRows][nCols]);
void trans_matrix(const int mat[nRows][nCols], int mat_transp[nCols][nRows]);
bool found_duplicate(int arr[], int length);


// main function

int main()
{
    int arr[SIZE];
    int arr2d[nRows][nCols];
    int user_choice;
    int element_pos;
    int new_element;
    int mat_transpose[nCols][nRows];
    bool duplicate = found_duplicate(arr,SIZE);
    print_array(arr, SIZE);

    while (true)
    {
        // Menu UI

        printf("\n\nMain Menu\n");
        printf("1. Remove element\n");
        printf("2. Insert element\n");
        printf("3. Reshape matrix\n");
        printf("4. Transpose matrix\n");
        printf("5. Find duplicates\n");
        printf("0. Exit program\n\n");
        printf("Please enter your selection: ");
        scanf("%d",&user_choice);

        // Switch case for user selection

        switch (user_choice)
        {

        // Removes element
        case 1:
            printf("Removing Element \n");
            printf("Enter the position at which the element should be removed: ");
            scanf("%d",&element_pos);

            // Checks if the element position is within range
            if(isValid(arr, SIZE, element_pos))
            {
                printf("Selected position is in range\n");
                remove_element(arr,SIZE,element_pos);
                printf("The updated array is: ");
                for (int j=0; j<SIZE;j++)
                {
                   printf("%d ",arr[j]);
                }
            }

            else
            {
                printf("Position not within the array size!");
            }
            break;

        // Inserts new element
        case 2:
            printf("Inserting new element\n");
            printf("Enter position of the new element: ");
            scanf("%d",&element_pos);
            printf("Enter the new element to be added: ");
            scanf("%d",&new_element);

            if(isValid(arr, SIZE, element_pos))
            {
                printf("Selected position is in range\n");
                insert_element(arr, SIZE, element_pos, new_element);
                for(int j=0; j<SIZE;j++)
                {
                   printf("%d ",arr[j]);
                }
            }
            else
            {
                printf("Wrong Value");
            }
            break;

        // Reshapes 1D array into a 2D array
        case 3:
            reshape(arr, SIZE, arr2d);
            for(int x=0; x<nRows; x++)
            {
                for(int y=0;y<nCols;y++)
                {
                   printf("%d ",arr2d[x][y]);
                }
                printf("\n");
            }
            break;

        // Transpose the matrix
        case 4:
            reshape(arr, SIZE,arr2d);
            trans_matrix(arr2d, mat_transpose);

            for(int f=0;f<nCols;f++)
            {
                for(int b=0;b<nRows;b++)
                {
                   printf("%d ", mat_transpose[f][b]);
                }
                printf("\n");
            }
            break;

        // Checks if there are duplicate elements
        case 5:
            printf("Array has duplicate: %s", duplicate ? "true" : "false");
            break;

        // Exits the function
        case 0:
            return 0;

        // Redirects invalid inputs
        default:
            printf("Invalid input");
            break;
        }
    }
}

// Function that prints array
void print_array(int array[], int length)
{
    printf("Your array is: ");
    for(int i=0;i<length; i++)
    {
        array[i] = i;
        printf("%d ",array[i]);
    }
    printf("\n");
}

// Function that prints the matrix
void print_matrix(int mat[][nCols], int rows)
{
    for(int i=0;i<rows; i++)
    {
        for(int j=0;j<nCols; j++)
        {
            printf("mat[%d][%d]= %d\n", i,j, mat[i][j]);
        }
        puts("");
    }
}

// Function that checks if input is valid
bool isValid(const int arr[], int length, int pos)
{
    return (pos >= 0 && pos < length);
}

// Function that removes elements
void remove_element(int arr[], int length, int pos)
{
    if (isValid(arr, length, pos))
    {
        for (int i = pos; i < length - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
    }

    else
    {
        printf("Invalid position\n");
    }
}

// Function that inserts a new element into the array
void insert_element(int arr[], int length, int pos, int value)
{
    if (!isValid(arr, length, pos))
    {
        printf("Invalid position\n");
    }
    else
    {
        for (int i = length - 1; i > pos; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[pos] = value;
    }
}

// Function that turns the array into a 2D matrix
void reshape(const int arr[], int length, int arr2d[nRows][nCols])
{
    if (length = nRows * nCols)
    {
        int i=0;
        for (int j = 0; j<nRows; j++)
        {
            for (int k = 0; k<nCols; k++)
            {
                arr2d[j][k] = arr[i];
                i++;
            }
        }

    }
    else
    {
        printf("Invalid dimensions\n");
    }
}

// Function that transposes the matrix
void trans_matrix(const int mat[nRows][nCols], int mat_transp[nCols][nRows])
{
    for (int i = 0;i < nRows;i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            mat_transp[j][i] = mat[i][j];
        }
    }
}

// Function that checks if there are duplicate elements
bool found_duplicate(int arr[], int length)
{
    for (int i = 0;i < length;i++)
    {
        for (int j = i + 1;j < length;j++)
        {
            if (arr[i] == arr[j])
            {
                return true;
            }
        }
    }
    return false;
}
