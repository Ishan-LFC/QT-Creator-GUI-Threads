# QT-Creator-GUI-Threads
GUI application that allows a user to enter start and end numbers as well as the  number of threads to use (maximum 4)

A class named PrimeFinder, capable of running as a thread, to find prime 
numbers between two given numbers.    
Write a GUI application that allows a user to enter start and end numbers as well as the 
number of threads to use (maximum 4).  When Start is clicked, the task should be divided 
into the required number of parts, the required number of PrimeFinder threads started, 
and the primes displayed in an appropriate window (per thread) as they are found.    
This is to be done without using QtConcurrent – you are to manage the threads 
yourself, and clean up after the threads have completed their work.  This means that you 
should be able to change the start, end, and number of thread numbers and click Start 
again without the program crashing or producing strange results.  Also, you should handle 
a user closing the application (closeEvent) before the threads have completed running 
so that the threads can tidy up after themselves before the application is closed. 
