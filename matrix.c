#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printMenu();
int **create_matrix(int row, int col);
int free_matrix(int **matrix, int row, int col);
void print_matrix(int **matrix, int row, int col);
int fill_data(int **matrix, int row, int col);
int transpose_matrix(int **matrix, int **matrix_t, int row, int col);
int addition_matrix(int **matrix_a, int **matrix_b, int row, int col);
int subtraction_matrix(int **matrix_a, int **matrix_b, int row, int col);
int multiply_matrix(int **matrix_a, int **matrix_t, int row, int col);

int main()
{
    srand(time(NULL));

    printf("[----- [JinYeongKim] [2019038030] -----]\n");
    printf("Input row and col : ");
    int row, col;
    scanf("%d %d", &row, &col);

    /* if row or col <= 0, matrix can't be created. */
    if (row <= 0 || col <= 0)
    {
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    /* create matrix a, b, c. */
    /* pre/post-condition test is already done by create_matrix() */
    int **a = create_matrix(row, col);
    int **b = create_matrix(row, col);
    int **t = create_matrix(col, row);

    printf("Matrix Created.\n");

    /* infinite loop */
    while (1)
    {
        printMenu();
        printf("Command = ");
        char command;
        scanf(" %c", &command);

        /* switch functions by commands */
        switch (command)
        {

        /* initialize matrices by random values(0 ~ 19) */
        case 'z':
            fill_data(a, row, col);
            fill_data(b, row, col);
            printf("\nMatrix_a and matrix_b are initialized by random values(0 ~ 19).\n");
            break;

        /* print the matrix */
        case 'p':
            /* avoid not initialized matrix */
            if (a[0][0] > 19 || a[0][0] < 0)
            {
                printf("\nInitialize first.\n");
                continue;
            }
            printf("\n[Matrix_a]\n");
            print_matrix(a, row, col);
            printf("\n[Matrix_b]\n");
            print_matrix(b, row, col);
            break;

        /* add matrix_a and matrix_b */
        case 'a':
            printf("\n[Matrix_a + Matrix_b]\n");
            addition_matrix(a, b, row, col);
            break;

        /* subtract matrix_b from matrix_a */
        case 's':
            printf("\n[Matrix_a - Matrix_b]\n");
            subtraction_matrix(a, b, row, col);
            break;

        /* transpose matrix_a */
        case 't':
            printf("\n[Transposed matrix_a]\n");
            transpose_matrix(a, t, row, col);
            print_matrix(t, col, row);
            break;

        /* multiply matrix_a and transposed matrix_a */
        case 'm':
            printf("\nMultiply matrix_a and matrix_t.\n\n");
            transpose_matrix(a, t, row, col);
            multiply_matrix(a, t, row, col);
            break;

        /* free allocated memory and quit */
        case 'q':
            printf("\nFree all matrices..\n");
            free_matrix(a, row, col);
            free_matrix(b, row, col);
            free_matrix(t, col, row);
            printf("Exit program.\n");
            return 0;

        default:
            printf("Improper command\n");
            break;
        }
    }
    return 1;
}

void printMenu()
{
    printf("\n----------------------------------------------------------\n");
    printf("              Matrix Manipulation\n");
    printf("----------------------------------------------------------\n");
    printf("Initialize Matrix   = z     Print Matrix =      p\n");
    printf("Add Matrix          = a     Subtract Matrix =   s\n");
    printf("Transpose matrix_a  = t     Multiply Matrix =   m\n");
    printf("Quit                = q\n");
    printf("----------------------------------------------------------\n");
    return;
}

/* malloc??? ????????? 2?????? matrix ?????? */
int **create_matrix(int row, int col)
{
    /* ????????? ??????(????????? ????????? ????????? ?????? ??????????????? ??????) */
    if (row <= 0 || col <= 0)
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    /* ??? ???????????? ????????? ?????? */
    int **matrix = (int **)malloc(row * sizeof(*matrix));
    /* ????????? ??? ???????????? ????????? ?????? */
    for (int i = 0; i < row; i++)
        matrix[i] = (int *)malloc(col * sizeof(**matrix));

    /* ????????? ??????(matrix??? ????????? ????????? ??? ????????? ??????) */
    if (matrix == NULL)
    {
        printf("Memory Allocation Failed.\n");
        return NULL;
    }
    return matrix;
}

/* ????????? ?????? ?????? */
int free_matrix(int **matrix, int row, int col)
{
    if (row <= 0 || col <= 0)
    {
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    /* matrix??? ????????? ????????? ??? ??????(??? ???????????? ?????? ??? ?????? ??? ???????????? ??????)??? ?????????
    ????????? ??? ????????? ???????????? ?????? ?????? ??? ??? ????????? ??? ????????? ????????? ?????? */
    for (int i = 0; i < row; i++)
        free(matrix[i]);
    free(matrix);

    return 1;
}

/* print matrix */
void print_matrix(int **matrix, int row, int col)
{
    if (row <= 0 || col <= 0)
    {
        printf("Check the sizes of row and col!\n");
    }

    for (int i = 0; i < row; i++)
    {
        for (int k = 0; k < col; k++)
        {
            printf("%d\t", matrix[i][k]);
        }
        printf("\n");
    }
    printf("\n");

    if (matrix == NULL)
        printf("Memory Allocation Failed.\n");
}

/* ???????????? ????????? matrix??? ??????????????? ????????? */
int fill_data(int **matrix, int row, int col)
{
    if (row <= 0 || col <= 0)
    {
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    for (int i = 0; i < row; i++)
    {
        for (int k = 0; k < col; k++)
        {
            matrix[i][k] = rand() % 20;
        }
    }

    if (matrix == NULL)
    {
        printf("Memory Allocation Failed.\n");
        return -1;
    }
    return 1;
}

/* matrix??? ??????????????? ?????????. */
int transpose_matrix(int **matrix, int **matrix_t, int row, int col)
{
    if (row <= 0 || col <= 0)
    {
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    /* ??????????????? ?????? ?????? ?????? ?????? ????????????. */
    /* ??????????????? ?????? ????????? ????????? index??? ?????? ?????????. */
    for (int i = 0; i < col; i++)
    {
        for (int k = 0; k < row; k++)
        {
            matrix_t[i][k] = matrix[k][i];
        }
    }

    if (matrix == NULL || matrix_t == NULL)
    {
        printf("Memory Allocation Failed.\n");
        return -1;
    }
    return 1;
}

/* add two matrices and print */
int addition_matrix(int **matrix_a, int **matrix_b, int row, int col)
{
    if (row <= 0 || col <= 0)
    {
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    /* ??? matrix??? ?????? ????????? matrix_sum ?????? by malloc */
    int **matrix_sum = create_matrix(row, col);

    for (int i = 0; i < row; i++)
    {
        for (int k = 0; k < col; k++)
        {
            matrix_sum[i][k] = matrix_a[i][k] + matrix_b[i][k];
        }
    }

    if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL)
    {
        printf("Memory Allocation Failed.\n");
        return -1;
    }

    print_matrix(matrix_sum, row, col);
    free_matrix(matrix_sum, row, col);
    return 1;
}

/* subtract two matrices and print */
int subtraction_matrix(int **matrix_a, int **matrix_b, int row, int col)
{

    if (row <= 0 || col <= 0)
    {
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    /* [matrix_a - matrix_b] ??? ????????? matrix_sub ?????? by malloc */
    int **matrix_sub = create_matrix(row, col);

    for (int i = 0; i < row; i++)
    {
        for (int k = 0; k < col; k++)
        {
            matrix_sub[i][k] = matrix_a[i][k] - matrix_b[i][k];
        }
    }

    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL)
    {
        printf("Memory Allocation Failed.\n");
        return -1;
    }

    print_matrix(matrix_sub, row, col);
    free_matrix(matrix_sub, row, col);
    return 1;
}

/* matrix?????? ????????? ?????? */
/* ????????? ?????? matrix_t?????? matrix_a??? ??????????????? ?????????. */
int multiply_matrix(int **matrix_a, int **matrix_t, int row, int col)
{
    if (row <= 0 || col <= 0)
    {
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    /* ??? ????????? ?????? ?????? matrix_axt */
    int **matrix_axt = create_matrix(row, row);

    /* a??? 1 ?????? ??? ?????? t??? 1 ?????? ??? ?????? ??? ?????? ??????(a??? ??? ?????? ?????? ???????????? ??? ?????? ?????????.) */
    /* a??? 1 ?????? ??? ?????? t??? 2 ?????? ??? ?????? ??? ?????? ?????? */
    /*                      ...                         */
    /* a??? 2 ?????? ??? ?????? t??? 1 ?????? ??? ?????? ??? ?????? ?????? */
    /* a??? 2 ?????? ??? ?????? t??? 2 ?????? ??? ?????? ??? ?????? ?????? */
    /*                      ...                         */
    for (int i = 0; i < row; i++)
    {
        for (int k = 0; k < row; k++)
        {
            int temp = 0;
            for (int j = 0; j < col; j++)
            {

                temp += matrix_a[i][j] * matrix_t[j][k];
            }
            matrix_axt[i][k] = temp;
        }
    }

    if (matrix_a == NULL || matrix_t == NULL)
    {
        printf("Memory Allocation Failed.\n");
        return -1;
    }

    print_matrix(matrix_axt, row, row);
    free_matrix(matrix_axt, row, row);
    return 1;
}
