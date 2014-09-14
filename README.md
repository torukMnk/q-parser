Q-parser
========

Universidad de Colima ISC Project 2013

Q-parser compile variables, numbers and basic arithmetic operations from txt file and return an result.
Tested on Linux Ubuntu
Release 12.04 (precise) 32-bit
Kernel Linux 3.13.0-35-generic

gcc version 4.6.3 (Ubuntu/Linaro 4.6.3-1ubuntu5)

Build Files
=========

````bash
sudo apt-get install cmake liblapack-dev
````

````bash
make Makefile


````
Out
========

File content data.txt

*lado1=5;
*lado2=86;
*base=105;
*color2=200;
*calculo=lado1+lado2-base+300-100/color2-4;

:: Q-Compiler ::

*lado1=5;
*lado2=86;
*base=105;
*color2=200;
*calculo=-3.07;

In q-data.txt
