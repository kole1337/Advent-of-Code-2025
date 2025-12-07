using System;
using System.Text.RegularExpressions;

namespace HelloWorld
{
    class Program
    {
        static void Main(string[] args)
        {
                //long sum = 0;
            try
            {
                //using StreamReader reader = new StreamReader("C:\\Users\\np3g22\\Downloads\\aoc25\\day2\\day2\\example.txt");
                //string text = reader.ReadToEnd();
                //string[] words = text.Split(new char[] { ',' });

                ////Write the text to the console
                //for (global::System.Int32 i = 0; i < words.Length; i++)
                //{
                //    //Console.WriteLine(useRegex(words[i]));

                //    string[] nums = words[i].Split(new char[] { '-' });
                //    if (nums[0].Length % 2 == 0 || nums[0].Length % 2 == 0)
                //    {
                //        for (long j = long.Parse(nums[0]); j < long.Parse(nums[1]); j++)
                //        {
                //            //Console.WriteLine(j);
                //            if (j.ToString().Length % 2 == 0)
                //            {
                //                if (isRepeat(j.ToString()))
                //                {
                //                    //Console.WriteLine(j);
                //                    sum += j;
                //                }
                //            }
                //        }
                //    }


                //}
                //Console.WriteLine("Sum: " + sum);
                //int a = 123123123;
                //string w = "asfaff";
                //int b = a.ToString().Length;
                //string c = w.Substring(0, (b / 2)-1), z = w.Substring((b/2)-1);
                //Console.Write(c + ", " + z);

                string input = System.IO.File.ReadAllText("C:\\Users\\np3g22\\Downloads\\aoc25\\day2\\day2\\example.txt");

                long total = 0;

                foreach (var range in input.Split(',', StringSplitOptions.RemoveEmptyEntries))
                {
                    var parts = range.Split('-');
                    long start = long.Parse(parts[0]);
                    long end = long.Parse(parts[1]);

                    for (long n = start; n <= end; n++)
                    {
                        if (IsInvalidId(n))
                            total += n;
                    }
                }

                Console.WriteLine(total);
            }
            catch (Exception e){
                Console.WriteLine("The file could not be read:");
                Console.WriteLine(e.Message);
            }
        }

        public static bool isRepeat(String a)
        {
            Regex regex = new("\\b(\\d+)\\1+\\b", RegexOptions.IgnoreCase);
            return regex.IsMatch(a);
        }

        static bool IsInvalidId(long n)
        {
            string s = n.ToString();

            if (s.Length % 2 != 0)
                return false;   // must be even length

            int half = s.Length / 2;
            string a = s.Substring(0, half);
            string b = s.Substring(half);

            return a == b;
        }
    }


}