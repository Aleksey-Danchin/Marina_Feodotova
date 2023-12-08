def hofstadter_q(n):
   def temp(n):
      if n < 3:
         yield 1
         return
      
      Q = lambda n: next(temp(n))
      yield Q(n-Q(n-1)) + Q(n-Q(n-2))
   
   for i in range(1, n+1):
      yield next(temp(i))
   

print(*hofstadter_q(7))