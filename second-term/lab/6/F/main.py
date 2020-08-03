import random, os

def check(b, a):
	f = open("input.txt", "w");
	f.write(b + "\n" + a)
	f.close();
	v1 = os.popen("./jopa < input.txt").read()
	return v1

a = ['udpi', 'chfv']
print(check(a[0], a[1]))