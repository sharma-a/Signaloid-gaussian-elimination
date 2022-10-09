[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-dark-v6.png#gh-dark-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/sharma-a/Signaloid-gaussian-elimination#gh-dark-mode-only)
[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-light-v6.png#gh-light-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/sharma-a/Signaloid-gaussian-elimination#gh-light-mode-only)

# Solution of systems of linear equations with random coefficients and random right hand side
This program solves a system of linear equations $Ax=b$ where the matrix $A$ and the vector $b$ have random entries. The program handles the case where $A$ is a non-singular square matrix. The solution to such a system is a random vector whose distribution is difficult to find analytically. This program uses the method of Gaussian Elimination along with the uncertainty tracking feature of the Signaloid system to find these distributions. 


## Using the program
The input to the program is provided as a file that contains the entries of the $A$ matrix and the $b$ vector. 
The first line of the input file is an integer $n$ that tells the dimensionality of the problem (i.e. the number of unknowns, which is the same as the number of equations).
The next $n^2$ lines tell the distribution of the entries of $A$ in a row major sequence, i.e, line 2 is $A_{1,1}$, line 3 is $A_{1,2}$, .... line $n+1$ is $A_{1,n}$, line $n+2$ is $A_{2,1}$  .. and so on.
The next $n$ lines tell the distribution of $b_1,b_2,...b_n$ 

The distribution information for an entry is specified by a string which tells the type of distribution, followed by parameters for that distribution. The distribution types are and their paramaters are:
1. "custom": followed by a sequence of numbers $a_1,a_2,a_3,...a_k$. This denotes a distribution which takes the values $a_1,a_2,a_3,...a_k$ with equal probabilities. If we have a single number after "custom", then that entry is non-random equal to that number.
2. "gauss": followed by two numbers. This is normal distribution where the first number is its mean, and the second is its standard deviation. 
3. "unif": followed by two numbers. This is uniform distribution between the first number (its minimum value), and the second number (maximum value).
4. "exp": followed by a number. This is exponential distribution where the specified number is its mean.

The input file name is provided as an argument to the program. Upon running it on the Signaloid Cloud Developer Platform, the program calculates the solution to the system in two different ways (see the next section for details, and the subsequent one for a discussion on why we do it in two ways) and outputs them on the standard output. It prints the solution value, its expected value and its variance for each $x$. On hovering at the solution values, the Signaloid system shows a pictorial representation (histogram) of its distribution.

## The solution process
The program finds the solution using Gaussian Elimination in two ways. The first way triangulises the matrix,(converting it to an upper triangular form using row operations) changing the rhs appropriately along the way and does back substitution to find the solution. The second way diagonalises the matrix (this process is often called Gauss-Jordan elimination) and computes the solution by simple division. Pivoting is used in both the methods to increase the numerical stability of the algorithm. This is the process of permuting the unused rows of the matrix (i.e. changing the order of the unused equations) in such a way as to avoid dividing by very small numbers. 

### Some issues to be careful about in the implementation
1. Uncertainty tracking is computationally demanding. Unless the signaloid compiler is doing something smart, creating a varaible to store something temporarily will cause the tracking of that temporary varaible, which will eat up precious resources. So I tried to avoid creating temporaries, and tried to make use of the C scoping rules to ensure that they are destroyed when not needed. Also I tended to avoid copying variables to new ones. InsteadI relied on pointers to access values which were already stored elsewhere.
2.Gaussian elimination involves creation of zeroes by subtracting various things. Now, it is good not only from the point of view of efficiency that such zero quantities are not computed but explicitly zeroed out (and terms involving these zeros should be simply omitted while calculating other quantities), but it is essential also from the point of view of not introducing spurious randomness. Signaloid variables are random variables, and even if they are zero they may have a non-trivial distribution whose mean is zero, which can introduce spurious randomness down the calculation chain.    
3.Order of computation(Next Section)




## The finite precision issue: some disconcerting facts and why we solve it in two ways (and why should we explore even more ways)

Now, in an ideal world, both processes (triangulisation and diagonisation) will find exactly the same solutions eventually. But because computers are finite precision machines they may produce different answers. Usual numerical considerations by themselves suggest that sometimes one method should be favoured over the other, even when no randomness is involved. But when we are keeping track of uncertainty as well, the choice of appropriate method becomes even more important. 

In my experiment with the Signaloid system I found out that the order of computation affects the propagation of uncertainty information very heavily, and it is not clear what is the correct order in which the computations should be performed to correctly track the uncertainties.

In particular, I did the following: I created two random variables $a$ and $b$ and calculated $\frac{a^2}{a+b}$ in three different ways: 
`c=(a/(b+a))*a`, `d=(a*a)/(a+b)`  and `e=a/(1.0+b/a)`

The values produced by the three methods were the same (as they should be) but their distributions were very different. The expected values (libUncertainDoubleNthMoment(x,1)) were noticably different and their variances (libUncertainDoubleNthMoment(x,2)) were wildly different. I did a simulation in R to find the correct variances and expected values for this quantity and only one of the methods (the `c` calculated above)  matched the values obtained in the simulation. Further it was not clear to me why the correct method produced the correct uncertainty tracking. If this issue has not been investigated, it must be done so now.

This was the case with a very simple computation. Our problem involves computations much more complex than this, and hence figuring out what factors contribute to correct uncertainty tracking is very important in this case. 

In my program, depending upon the input matrices, the distributions obtained were different in the two methods. In general, the more the number and the variances of the random quantities, the more the variability in the methods. Variances in general varied much more wildly compared to the expected values.


