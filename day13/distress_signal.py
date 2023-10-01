def ReadFile(file_name):
  packages = []
  f = open(file_name, "r")
  temp = f.read().splitlines()
  for line in temp:
    if (line != ""):
      packages.append(eval(line))
  return packages

def CheckPackages(left, right):
  for l, r in zip(left, right):
    if (type(r) == int and type(l) == int):
      if (l < r):
        return 1
      elif (l > r):
        return 0
    else:
      if (type(r) == int):
        r = [r]
      if (type(l) == int):
        l = [l]
      is_ordered = CheckPackages(l, r)
      if (is_ordered != -1):
        return is_ordered
      else:
        continue
  if (len(left) < len(right)):
    return 1
  elif (len(left) > len(right)):
    return 0
  return -1

def main():
  packages = ReadFile("signal.txt")
  correct_order = []
  for i in range(int(len(packages) / 2)):
    print(("-------------- COMPARING PAIR {} --------------").format(i + 1))
    in_order = CheckPackages(packages[2 * i], packages[2 * i + 1])
    is_ordered = "not " if (in_order == 0) else ""
    if (in_order == 1):
      correct_order.append(i + 1)
    print(("Pair {} is {}in order with order value {}").format(i + 1, is_ordered, in_order))
  print("-------------- PART 1 --------------")
  sum = 0
  for pair in correct_order:
    sum += pair
    print(("Pair {} is in order").format(pair))
  print(("Puzzle 1 answer is {}").format(sum))
  print("-------------- PART 2 --------------")
  index1 = 1
  index2 = 2
  for package in packages:
    if (CheckPackages(package, [[2]]) == 1):
      index1 += 1
    if (CheckPackages(package, [[6]]) == 1):
      index2 += 1
  product = index1 * index2
  print(("Puzzle 2 answer is {} * {} = {}").format(index1, index2, product))

if __name__ == "__main__":
  main()