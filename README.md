**Crypto ver.1.0**
---

The program allows you to study the simple frequency analysis used in cryptography to crack the most simple ciphers.
This is console application

---

Works in compilers:
* gcc-4.8
* MSVS2015 

---

Work algorithm:
1. File coding. If there is already an encoded file, you can skip this step.
Note. Implemented simple coding method with linear cyclic shift by a specified value.
2. Analysis of the text (large) to create a frequency dictionary (getting a "true statistic vector").
3. Analysis of the cipher text to create a frequency dictionary (getting a "false statistic vector").
4. Using the tool to automatically replace characters, based on the previously obtained vectors.

Note. For more information use the key: --help

---

Project structure:
*Example coding and decoding text:		\example
*Source:								\src
*Compiled code:
  * Window 7/8/10:  					\x86_x64
  * Ubuntu 14/16:						\linux	
