using System;

namespace Program
{
    class Calculator
    {
        public int A { get; }
        public int B { get; }

        public Calculator(int a, int b)
        {
            A = a;
            B = b;
        }

        public int Add() => A + B;
        public int Subtract() => A - B;
        public int Multiply() => A * B;
        public double Divide()
        {
            if (B == 0) throw new DivideByZeroException("Cannot divide by zero.");
            return (double)A / B;
        }
    }

    class Lab9_Program1
    {
        static int ReadInt(string prompt)
        {
            while (true)
            {
                Console.Write(prompt);
                string? input = Console.ReadLine();
                if (int.TryParse(input, out int value))
                    return value;

                Console.WriteLine("Invalid input. Please enter a valid integer.");
            }
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Simple OOP Calculator");

            int first = ReadInt("Enter the first integer: ");
            int second = ReadInt("Enter the second integer: ");

            var calc = new Calculator(first, second);

            int sum = calc.Add();
            int difference = calc.Subtract();
            int product = calc.Multiply();

            Console.WriteLine();
            Console.WriteLine($"Addition:        {first} + {second} = {sum}");
            Console.WriteLine($"Subtraction:     {first} - {second} = {difference}");
            Console.WriteLine($"Multiplication:  {first} * {second} = {product}");

            if (second == 0)
            {
                Console.WriteLine($"Division:        {first} / {second} = Undefined (division by zero)");
            }
            else
            {
                double quotient = calc.Divide();
                Console.WriteLine($"Division:        {first} / {second} = {quotient}");
            }

            if (sum % 2 == 0)
            {
                Console.WriteLine($"The sum ({sum}) is even.");
            }
            else
            {
                Console.WriteLine($"The sum ({sum}) is odd.");
            }
        }
    }
}