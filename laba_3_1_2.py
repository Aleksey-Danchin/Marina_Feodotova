# def f (*lists):
#    lists = [set(l) for l in lists]
#    for i in range(1, len(lists)):
#       lists[0] &= lists[i]
#    return len(lists[0]) == 0

def f (*lists):
   for i in lists[0]:
      flag = True
      for j in range(1, len(lists)):
         if i not in lists[j]:
            flag = False
            break
      
      if flag:
         return False
   return True


print(f(
   [1, 2, 3],
   [1, 4, 5, 6],
   [1, 7, 8, 9],
   [1, 10, 11]
))