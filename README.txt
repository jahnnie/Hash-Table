John Yoo
39296132
m3c9
L0E

Clarence Lam
41436130
f8w8
L0E

Instructions/Comments to the marker:

1) The functionality of isFull() is completed by search() and insert().
	- If proof is required, please uncomment out line 422 and lines 446-514 to test. Although a boolean value is not returned,
		"Table full." will be printed to console, with some vacancies in the hash table, proving that quadratic probing does not always lead to completely
		capacitated hash tables.

2) Attempting to hash a very very large amount of data will result in a segmentation fault, reflecting practicality.
		- e.g. rowsToHash = 1000 -> seg fault

3) Many of the methods that we were instructed to implement (bototm of the assignment page) were done, but never executed. Its functionality was mostly
   covered in the second Hasher constructor.

4) A static string array was declared globally with size 7 because we assumed that it would only need to hold the headers and the 6 examples for Part 4.

5) For double hash, h(k) = goodHash(), and h_2(k) = primeHash(). PrimeHash()'s functionality closely reflected that of the example on slide 169 (Lecture 12).

6) TABLE_SIZE will always be prime.

7) tombstones are represented by the string "t".

8) As by one of the TAs confirmation, Donald Knuths' "expected # of probes" equation for our Double Hash function is identical to that of our Quadratic probing.

9) As TABLE_SIZE has been declared globally (in order to ensure that the deconstructor destroys every value),
	it will take the value of the last Hasher that is initalized. Therefore, if you instaniate one Hasher object before another, then call printTable() on the first, it will print
	Hash table subscripts up to the capacity of the second object. Thus, it must be changed every time if printTable() of a specific object is desired.

PART 4 QUESTIONS----------------------------------

1) We chose all hash functions based on what we learned in class.
	The lecture slides for class 12 demonstrate the relative effectiveness/efficiencies of each of our 3 functions.
		- poorHash -> slide 116
		- goodHash -> slide 118
		- primeHash -> slide 169
	
	We believed that goodHash was better than poorHash because the fact that it mulitplied it by 2 (shifting bits leftward) provided better distribution
	and a less chance of collision relative to poorHash.

	In order to maximize effectiveness/efficiency, for double hash, instead of using poorHash as h(k) and goodHash as h_2(k), we used goodHash 
	and primeHash. The hope was that if h(x) = h(y), then h2(x) != h2(y).

	The load factors, although smaller than the requested, were relatively close to the requested, 
	because our TABLE_SIZE was always the very next prime number to the (number of lines)*(the inverse of the requested factor).
	
2) They are independent. The load factor = #inserts/TABLE_SIZE, both components of which are determined independently of the hash function.
3) They were very different. Only in 1/6 cases did we witness our average probes per insert was greater than Knuths' expected.


