import random, os

parametr = -1

def gen():
	a = list()
	cnt = random.randint(10, 15)
	x = random.randint(3, 6)
	cnt -= x
	d = {}
	putted = list()
	for i in range(x):
		number = (chr(ord('a') + random.randint(0, 25)))
		tr = chr(ord('a') + random.randint(0, 25))
		flag = False;
		for j in range(len(putted)):
			if (j == number) :
				d[number] = tr
				flag = True
		d[number] = tr
		if (flag == False):
			putted.append(number)
		a.append(str("put ") + str(number) + " " + str(tr))
	parametr = cnt
	l = 0
	for i in range(cnt):
		type = random.randint(1, 5)
		# 1 - put
		# 2 - delete
		# 3 - get
		# 4 - prev
		# 5 - next
		number = -1
		if (type == 1):
			number = (chr(ord('a') + random.randint(0, 25)))
			tr = chr(ord('a') + random.randint(0, 25))
			flag = False;
			for j in range(len(putted)):
				if (j == number) :
					d[number] = tr
					flag = True
			d[number] = tr
			if (flag == False):
				putted.append(number)
			a.append(str("put ") + str(number) + " " + str(tr))
		else :
			number = -1
			if (random.randint(1, 3) != 1):
				if (len(putted) != 0):
					number = putted[random.randint(0, len(putted) - 1)]
				else:
					number = (chr(ord('a') + random.randint(0, 25)))
			else:
				number = (chr(ord('a') + random.randint(0, 25)))
			if (type == 2):
				a.append(str("delete ") + str(number))
			elif (type == 3):
				a.append(str("delete ") + str(number))
			elif (type == 4):
				a.append(str("prev ") + str(number))
			elif (type == 5):
				a.append(str("next ") + str(number))

	return a

def tostr(a):
	res = ''
	for i in range(len(a)):
		res = res + a[i] + "\n"
	return res

print(tostr(gen()))
i = 0
while (True):
	i = i + 1
	f = open("input.txt", "w");
	teststr = tostr(gen());
	f.write(teststr)
	f.close();
	v1 = os.popen("./c < input.txt").read()
	v2 = os.popen("./main1 < input.txt").read()
	if (v1 != v2):
		print("WA :\n" + teststr)
		print("Expected :" + v1 + ", found : " + v2)
		break
	print("Failed " + str(i) + ", test = " + teststr + "\n" + "my_ans = " + v2 + "\n correct = " + v1 + "\n")
