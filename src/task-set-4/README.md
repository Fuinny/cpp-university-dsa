# Task Set 4: Hash Tables

### Task 1
Write an application that verifies the username and password matching.
List of data (pairs of values) is provided in an input text file.
Use a console to type the name and a password and to produce an output.

Example:
```
1. Display all elements
2. Insert new element
3. Remove element
4. Login
5. Exit

Enter your choice: 4

Enter username: alice
Enter password: password123

Login successfull!
```

---

### Task 2
Implement additional hash algorithms. Check how each of them performs hashing.

#### a. ETH Algorithm
- Initial value: `h = 1`
- Recursive formula: `hn = ch * ((h mod 257) + 1)`
- Final index: `H = hn mod table_size.`

#### b. GNU-cpp Algorithm
- Initial value: `h = 0`
- Recursive formula: `hn = 4 * h + ch`
- Final index: `H = (last 31 bits of hn) mod table_size`

#### c. GNU-cc1 Algorithm
- Initial value: `h = k`
- Recursive formula: `hn = 613 * h + ch`
- Final index: `H = (last 30 bits of hn) mod table_size`

**Legend:**
- `k` - number of characters
- `h0` - starting value
- `h` - intermediate hash value
- `hn` - result after applying the hash algorithm
- `ch` - current character
- `H` - index in the table

Example:
```
Select hash algorithm:
1. ETH
2. GNU-CPP
3. GNU-CC1

Enter your choice: 3
From 100 buckets in hash table 38 are empty.
```
