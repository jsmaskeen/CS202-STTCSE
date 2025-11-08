using System;

namespace ArrayDemo
{
    class ArrayOperations
    {
        public static void BubbleSort(int[] arr)
        {
            int n = arr.Length;
            for (int i = 0; i < n - 1; i++)
            {
                for (int j = 0; j < n - i - 1; j++)
                {
                    if (arr[j] > arr[j + 1])
                    {
                        int temp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = temp;
                    }
                }
            }
        }

        public static int[] FlattenRowMajor(int[,] matrix)
        {
            int rows = matrix.GetLength(0);
            int cols = matrix.GetLength(1);
            int[] result = new int[rows * cols];

            int index = 0;
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    result[index++] = matrix[i, j];

            return result;
        }

        public static int[] FlattenColumnMajor(int[,] matrix)
        {
            int rows = matrix.GetLength(0);
            int cols = matrix.GetLength(1);
            int[] result = new int[rows * cols];

            int index = 0;
            for (int j = 0; j < cols; j++)
                for (int i = 0; i < rows; i++)
                    result[index++] = matrix[i, j];

            return result;
        }

        public static int[,] MultiplyMatrices(int[,] A, int[,] B)
        {
            int rowsA = A.GetLength(0);
            int colsA = A.GetLength(1);
            int rowsB = B.GetLength(0);
            int colsB = B.GetLength(1);

            if (colsA != rowsB)
                throw new InvalidOperationException("Number of columns in A must equal number of rows in B.");

            int[,] C = new int[rowsA, colsB];

            for (int i = 0; i < rowsA; i++)
            {
                for (int j = 0; j < colsB; j++)
                {
                    C[i, j] = 0;
                    for (int k = 0; k < colsA; k++)
                    {
                        C[i, j] += A[i, k] * B[k, j];
                    }
                }
            }

            return C;
        }

        public static void PrintArray(int[] arr)
        {
            foreach (int num in arr)
            {
                Console.Write(num + " ");
            }
            Console.WriteLine();
        }

        public static void PrintMatrix(int[,] matrix)
        {
            int rows = matrix.GetLength(0);
            int cols = matrix.GetLength(1);
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    Console.Write(matrix[i, j] + "\t");
                }
                Console.WriteLine();
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            int[] arr = { 5, 2, 9, 1, 5, 6 };
            Console.WriteLine("Original Array:");
            ArrayOperations.PrintArray(arr);

            ArrayOperations.BubbleSort(arr);
            Console.WriteLine("Sorted Array (Bubble Sort):");
            ArrayOperations.PrintArray(arr);
            Console.WriteLine();

            int[,] matrix2D = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
            Console.WriteLine("2-D Matrix:");
            ArrayOperations.PrintMatrix(matrix2D);

            int[] rowMajor = ArrayOperations.FlattenRowMajor(matrix2D);
            Console.WriteLine("Flattened (Row-Major):");
            ArrayOperations.PrintArray(rowMajor);

            int[] colMajor = ArrayOperations.FlattenColumnMajor(matrix2D);
            Console.WriteLine("Flattened (Column-Major):");
            ArrayOperations.PrintArray(colMajor);
            Console.WriteLine();

            int[,] A = { { 1, 2 }, { 3, 4 } };
            int[,] B = { { 5, 6 }, { 7, 8 } };
            Console.WriteLine("Matrix A:");
            ArrayOperations.PrintMatrix(A);
            Console.WriteLine("Matrix B:");
            ArrayOperations.PrintMatrix(B);

            int[,] C = ArrayOperations.MultiplyMatrices(A, B);
            Console.WriteLine("Matrix C = A x B:");
            ArrayOperations.PrintMatrix(C);
        }
    }
}
