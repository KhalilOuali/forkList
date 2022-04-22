# forkList
A c program which outputs a list view of all processes created with fork(), for teaching or debugging purposes.
Made and tested on linux.

## How to use
* Download the original c code (forkList.c or forkList1.c)
* Change the instructions under `// INSTRUCTIONS GO HERE:`
* Compile. E.g. `gcc forkList.c -o forkList` in the console
* Run. E.g. `./forkList` in the console. 
(Note: for a better output ordered by creation fork, you can pipe the run command with sort. E.g. `./forkList | sort`)

## Code
* `forkm()`: use this instead of fork(). It calls fork(), traces the created child's lineage, and returns the fork() value.
* `outm()`: you can use this instead of printf() for a cleaner output. Check the [outm()](#outm) section for more info.
* `showm()`: this is the final output instruction, which displays the full list of processes.

## Output
A list of lines with the format:
```
(fork #N) Lineage : ProcessOutput
```
indicating 
* which fork created the current process (0 means it's the original parent)
* its lineage, i.e., its parent, its grandparent, etc.
* its output, i.e., what it would normally print out to the console

## Constants
Right before the main() function, 2 constants are defined:
* `maxLineageLength`: the maximum number of processes in one continuous lineage. If your code has a lot of forks and produces a process which is a distant grandchild, you should raise this constant.
* `maxOutputLength`: the maximum number of characters in a process's output (after the :). If you have a long final output, it will get truncated to this length. You can raise it to extend your output.

## Example
The following code:
```
fork();
if (fork())
	fork();
	
printf("Hello!\n");
```
generates the following process tree:

<p align="center">
  <img src="https://user-images.githubusercontent.com/68998620/164605644-d3ce08c1-3832-48ee-a5ca-d59074d83b62.png">
</p>
Each process will output "Hello!", so the full output will be six times "Hello!":

```
Hello!
Hello!
Hello!
Hello!
Hello!
Hello!
```

Using forkList, the code becomes:
```
forkm();
if (forkm())
	forkm();

outm("Hello!");
  
showm();
```
and the program's output is (e.g.):
```
(fork #0) 0 : Hello!
(fork #2) 0 - 1 : Hello!
(fork #2) 0 - 0 - 0 : Hello!
(fork #1) 0 - 0 : Hello!
(fork #3) 0 - 2 : Hello!
(fork #3) 0 - 0 - 1 : Hello!
```

## outm()
If you were to use printf() for each individual output, it may get jumbled with the outputs of the other processes.

This macro is meant to collect all of the current process's outputs, and show them at the end of its entry in the list.

### forkList vs forkList1
In forkList.c, 
`outm(string)` appends the paramter string to the process's output string, using strcat. This method is not memory-safe, so be careful using it.

In forkList1.c, 
`outm(format, var)` acts exactly like `printf(format, var)`.
#### It produces a lot of notes and warnings during compilation, but this method is actually perfectly memory-safe.
Note that that you must supply the var argument, even if your format doesn't contain any variables.
The output will be automatically truncated to fit the output string's length.
