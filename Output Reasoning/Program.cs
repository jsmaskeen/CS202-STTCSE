//using System;

// Level 0


//public delegate void AuthCallback(bool validUser);
//public static AuthCallback loginCallback = Login;
//public static void Login()
//{
//    Console.WriteLine("Valid user!");
//}
//public static void Main(string[] args)
//{
//    loginCallback(true);
//}

//namespace MyConsoleApp
//{
//    class Program
//    {
//        public delegate void AuthCallback(bool validUser);
//        public static AuthCallback loginCallback = Login;
//        public static void Login()
//        {
//            Console.WriteLine("Valid user!");
//        }
//        public static void Main(string[] args)
//        {
//            loginCallback(true);
//        }
//    }
//}

//using System;
//delegate void Notify(string msg);
//class Program
//{
//    static void Main()
//    {
//        Notify handler = null;
//        handler += (m) => Console.WriteLine("A: " + m);
//        handler += (m) => Console.WriteLine("B: " + m.ToUpper());
//        handler("hello");
//        handler -= (m) => Console.WriteLine("A: " + m);
//        handler("world");
//    }
//}


// Level 1
//using System;
//class Program
//{
//    static string txtAge;
//    static DateTime selectedDate;
//    static int parsedAge;
//    static void Main(string[] args)
//    {
//        try
//        {
//            Console.WriteLine(txtAge == null ? "txtAge is null" : txtAge);
//            Console.WriteLine(selectedDate == default(DateTime)
//            ? "selectedDate is default"
//            : selectedDate.ToString());
//            if (string.IsNullOrEmpty(txtAge))
//            {
//                Console.WriteLine("txtAge is null or empty, cannot parse");
//            }
//            else
//            {
//                parsedAge = int.Parse(txtAge);
//                Console.WriteLine($"Parsed Age: {parsedAge}");
//            }
//        }
//        catch (FormatException)
//        {
//            Console.WriteLine("Format Exception Caught");
//        }
//        catch (ArgumentNullException)
//        {
//            Console.WriteLine("ArgumentNull Exception Caught");
//        }
//        finally
//        {
//            Console.WriteLine("Finally block executed");
//        }
//    }
//}

//using System;
//delegate void Operation();
//class Program
//{
//    static void Main()
//    {
//        Operation ops = null;
//        ops += Step1;
//        ops += Step2;
//        ops += Step3;
//        try
//        {
//            ops();
//        }
//        catch (Exception ex)
//        {
//            Console.WriteLine("Caught: " + ex.Message);
//        }
//        Console.WriteLine("End of Main");
//    }
//    static void Step1()
//    {
//        Console.WriteLine("Step 1");
//    }
//    static void Step2()
//    {
//        Console.WriteLine("Step 2");
//        throw new InvalidOperationException("Step 2 failed!");
//    }
//    static void Step3()
//    {
//        Console.WriteLine("Step 3");
//    }
//}

// Level 2

//using System;
//namespace MethodOverloadingExample
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            int x = 5;
//            new Base().F(x);
//            new Derived().F(x);
//            Console.ReadKey();
//        }
//    }
//    class Base
//    {
//        public void F(int x)
//        {
//            Console.WriteLine("Base.F(int)");
//        }
//    }
//    class Derived : Base
//    {
//        public void F(double x)
//        {
//            Console.WriteLine("Derived.F(double)");
//        }
//    }
//}

//using System;
//class StepEventArgs : EventArgs
//{
//    public int Step { get; }
//    public StepEventArgs(int s) => Step = s;
//}
//class Workflow
//{
//    public event EventHandler<StepEventArgs> StepStarted;
//    public event EventHandler<StepEventArgs> StepCompleted;
//    public void Run()
//    {
//        for (int i = 1; i <= 3; i++)
//        {
//            StepStarted?.Invoke(this, new StepEventArgs(i));
//            Console.Write($"[{i}]");
//            StepCompleted?.Invoke(this, new StepEventArgs(i));
//        }
//    }
//}
//class Program
//{
//    static void Main()
//    {
//        Workflow wf = new Workflow();
//        wf.StepStarted += (s, e) =>
//        {
//            Console.Write("<S" + e.Step + ">");
//            if (e.Step == 2)
//                ((Workflow)s).StepCompleted += (snd, ev)
//                => Console.Write("(Dyn" + ev.Step + ")");
//        };
//        wf.StepCompleted += (s, e) => Console.Write("<C" + e.Step + ">");
//        wf.Run();
//    }
//}