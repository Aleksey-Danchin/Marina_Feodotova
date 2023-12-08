import math

def binom(n):
   if n == 0:
      return "1"
   
   m = abs(n)
   s = []
   for k in range(m+1):
      c = int(math.factorial(m)/math.factorial(k)/math.factorial(m-k))
      i = "" if c == 1 else str(c)

      if m-k > 0:
         i += 'a'
         if m-k != 1:
            i += '^' + str(m-k)

      if k > 0:
         i += 'b'
         if k != 1:
            i += '^' + str(k)
      
      s.append(i)
   
   s = "+".join(s)
   if n < 0:
      s = f"1/({s})"

   return s

for i in range(-5, 6):
   print(i, binom(i), sep="\n", end="\n\n")