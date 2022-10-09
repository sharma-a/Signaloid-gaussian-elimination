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

The input file name is provided as an argument to the program. Upon running it on the Signaloid Cloud Developer Platform, the program calculates the solution to the system in two different ways (see the next section for details, and for a discussion on why we do it in two ways) and outputs them on the standard output. It prints the solution value, its expected value and its variance for each $x$. On hovering at the solution values, the Signaloid system shows a pictorial representation (histogram) of its distribution.

##The solution process
The program finds the solution using Gaussian Elimination in two ways. The first way triangulises the matrix,(converting it to an upper triangular form using row operations) changing the rhs appropriately along the way and does back substitution to find the solution. The second way diagonalises the matrix (this process is often called Gauss-Jordan elimination) and computes the solution by simple division. Pivoting is used in both the methods to increase the numerical stability of the algorithm. This is the process of permuting the unused rows of the matrix (i.e. changing the order of the unused equations) in such a way as to avoid dividing by very small numbers. 







## Getting Started
1. [Fork](https://docs.github.com/en/get-started/quickstart/fork-a-repo) this repository.
2. Edit `README.md` to [adapt the “Add to signaloid.io” button's URL](#option-1--using-the-add-to-signaloidio-button).
3. Edit the code and [configure the build](#configuring-the-build-configmk).

## Repository Structure
The Signaloid Cloud Developer Platform expects any GitHub repository you wish to run to have a `src` folder containing your source code. By default, the Signaloid Cloud Developer Platform will compile all C and C++ source files (extensions `*.c`, `*.cc`, `*.cpp`, `*.c++`, `*.cp`, and `*.cxx`) in the `src` folder and will link them into a single binary and run that on your choice of uncertainty-tracking processor.

### Configuring the Build (`config.mk`)
You can modify the default build behavior described above by providing a file named `config.mk`.

For C repositories, there are two relevant variables in `config.mk`:
- `SOURCES`, a list of C source files to compile;
- `CFLAGS`, the options that are passed to the C compiler.

If the `SOURCES` variable is not set, the Signaloid Cloud Developer Platform compiles all the C and C++ files in the `src` folder.


#### 🎓 Example
The following example shows a `src/` folder for a repository, containing one C source file (`main.c`) and a `config.mk` to modify the build parameters.
```
src/
├── config.mk
└── main.c
```

In this repository, the file [`src/config.mk`](./src/config.mk) contains
```makefile
SOURCES = main.c
CFLAGS  = -DDEBUG
```
This tells the Signaloid Cloud Developer Platform to build the [`main.c`](./src/main.c) file using the compiler flag `-DDEBUG` (i.e., defining the symbol `DEBUG`).

### Headers
Place your header files in the `src` folder. This folder is part of the build include path.

### Libraries
During the build process, the Signaloid Cloud Developer Platform links the compiled object files against the following libraries:
- `libc`: the C standard library;
- `libm`: the C math library (with function prototypes and other definitions in `math.h`);
- `libUncertain`: a library that exposes functionalities of uncertainty-tracking computer architectures (with function prototypes and other definitions in `uncertain.h`).

`libUncertain` allows applications to access and inject uncertainty information into the underlying microarchitectures. You can find out more about `libUncertain` in the [libUncertain documentation](https://libuncertain.signaloid.io/).

## 🍰 Accessing Your GitHub Repository from the Signaloid Cloud Developer Platform
There are two ways to access a GitHub repository from the Signaloid Cloud Developer Platform.

### Option 1:  Using the “Add to signaloid.io” Button
This first option makes it easiest for you (and other GitHub users) to run your repository on the Signaloid Cloud Developer Platform. Edit the snippet at the top of this `README.md` to include the URL of your Git repository.

The text you need to change is (replacing the text `<your repository URL here>`):
```html
[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-dark-v6.svg#gh-dark-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=<your repository URL here>#gh-dark-mode-only)
[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-light-v6.svg#gh-light-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=<your repository URL here>#gh-light-mode-only)
```

Next, go to the repository's Github page and click on the “Add to signaloid.io” button.

### Option 2: Manually Adding Repositories to the Signaloid Cloud Developer Platform
A second option is to manually add a repository to the Signaloid Cloud Developer Platform. To do so, follow these steps:
1. Log in to the Signaloid Cloud Developer Platform at [https://signaloid.io/](https://signaloid.io/). If you do not already have an account, you can create one for free in just three clicks.
2. Click on the `Repositories` tab in the menu on the left side of the screen (you might need to go through the menu icon on mobile screens).
3. Give the Signaloid Cloud Developer Platform permission to access your repositories, using the blue GitHub "Login" button.
4. Click on the green button (Connect to Repositories). All your repositories will appear in a list. Add the relevant repository.
5. Your repository should now appear in the UI.
