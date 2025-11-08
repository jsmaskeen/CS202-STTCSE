using System;

namespace Program
{
    class Vehicle
    {
        protected int speed = 100;
        protected int fuel = 100;
        public virtual void ShowInfo() => Console.WriteLine($"Speed: {speed}, Fuel: {fuel}");
        public virtual void Drive()
        {
            Console.WriteLine($"Vehicle is moving...");
            fuel -= 5;
        }

    }

    class Car : Vehicle
    {
        public int passengers = 10;

        public override void ShowInfo() => Console.WriteLine($"Car Speed: {speed}, Car Fuel: {fuel}, Passenger: {passengers}");
        public override void Drive()
        {
            Console.WriteLine("Car is moving with passenger");
            fuel -= 10;
        }
    }

    class Truck : Vehicle
    {
        public int cargoWeight = 40;
        public override void ShowInfo() => Console.WriteLine($"Truck Speed: {speed}, Truck Fuel: {fuel}, Cargo Weight: {cargoWeight}");
        public override void Drive()
        {
            Console.WriteLine("Truck is moving with cargo");
            fuel -= 15;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Vehicle[] vehicles = { new Vehicle(), new Car(), new Truck() };
            for (int i = 0; i < vehicles.Length; i++)
            {
                vehicles[i].Drive();
                vehicles[i].ShowInfo();
                Console.WriteLine("------------");
            }
        }
    }
}