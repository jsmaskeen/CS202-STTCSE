using System;
using System.Collections.Generic;

namespace LoopFunctionDemo
{
    class Program
    {
        static long Factorial(int n)
        {
            long result = 1;
            for (int i = 2; i <= n; i++)
            {
                result *= i;
            }
            return result;
        }

        static void Main(string[] args)
        {
            Console.WriteLine("For loop:");
            for (int i = 1; i <= 10; i++)
            {
                Console.Write(i + " ");
            }
            Console.WriteLine("\n");

            Console.WriteLine("Foreach loop:");
            List<int> numbers = new List<int>();
            for (int i = 1; i <= 10; i++) numbers.Add(i);

            foreach (int num in numbers)
            {
                Console.Write(num + " ");
            }
            Console.WriteLine("\n");

            string input;
            do
            {
                Console.Write("Enter something (type 'exit' to quit): ");
                input = Console.ReadLine()!;
                if (input.ToLower() != "exit")
                    Console.WriteLine("You entered: " + input);
            } while (input.ToLower() != "exit");

            int number;
            while (true)
            {
                Console.Write("Enter a non-negative integer to calculate factorial: ");
                string? numInput = Console.ReadLine();
                if (int.TryParse(numInput, out number) && number >= 0)
                    break;
                Console.WriteLine("Invalid input. Please enter a non-negative integer.");
            }

            long factorial = Factorial(number);
            Console.WriteLine($"Factorial of {number} is {factorial}");
        }
    }
}
