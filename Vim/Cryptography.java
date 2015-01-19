import java.util.*;
import java.math.*;

class Main
{

    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);

        while (in.hasNext())
        {
            int n = in.nextInt();
            BigInteger p = in.nextBigInteger();

            long lo = 1, hi = 1000000000;

            while (lo+1 != hi)
            {
                long mid = (hi+lo)/2;

                BigInteger midBI = new BigInteger(mid+"");
                BigInteger vPow = midBI.pow(n);

                if (vPow.compareTo(p) <= 0)
                    lo = mid;
                else
                    hi = mid;
            }

            System.out.println(lo);
        }
    }
}
