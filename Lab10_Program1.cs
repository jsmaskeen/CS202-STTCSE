using System;
namespace Program
{
    class Program
    {
        private int data;
        static int counter = 0;
        public Program()
        {
            Console.WriteLine("Constructor called!");
            counter++;
            Console.WriteLine($"Counter value: {counter}");
        }
        ~Program()
        {
            Console.WriteLine("Destructor called, object cleaned up!");
            counter--;
            Console.WriteLine($"Counter value: {counter}");
        }
        public void set_data(int value)
        {
            data = value;
        }
        public void show_data()
        {
            Console.WriteLine(data);
        }
    }
    class Test
    {
        static void runner()
        {
            Program obj1 = new Program();
            Program obj2 = new Program();
            Program obj3 = new Program();

            obj1.set_data(10);
            obj2.set_data(20);
            obj3.set_data(30);

            obj1.show_data();
            obj2.show_data();
            obj3.show_data();
        }
        static void Main(string[] args)
        {
            runner();
            GC.Collect();        // Force garbage collection
            GC.WaitForPendingFinalizers(); // Wait for destructors to run
        }
    }
}