using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NUnit.Framework;




namespace CLowery_LeetCode
{
    internal class SolutionTests
    {
        Solution solution = new Solution();
        [Test]
        public void TestOne()
        {
            int dividend = 10;
            int divisor = 3;
            int expected = 3;
            int result = solution.Add(dividend, divisor);
            CollectionAssert.AreEqual(expected,result);

        }
         [Test] 
         public void TestTwo()
        {

        }
        [Test]
        public void TestThree()
        {

        }
    }
}
