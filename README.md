Q-parser
========

Universidad de Colima ISC Project 2013

Q-parser compile variables, numbers and basic arithmetic operations from txt file and return a result.
Tested on Linux Ubuntu
Release 12.04 (precise) 32-bit
Kernel Linux 3.13.0-35-generic

Build Files
=========

gcc version 4.6.3 (Ubuntu/Linaro 4.6.3-1ubuntu5)

````bash
$sudo apt-get install cmake
````

````bash
$make
````

Execute Q-parser sample
=========

````bash
$./qparser data.txt
````

Out
========

File content data.txt

````bash
lado1=5;
lado2=86;
base=105;
color2=200;
calculo=lado1+lado2-base+300-100/color2-4;
````

:: Q-Compiler ::

````bash
lado1=5;
lado2=86;
base=105;
color2=200;
calculo=-3.07;
````
Generated file

````bash
q-data.txt
````

