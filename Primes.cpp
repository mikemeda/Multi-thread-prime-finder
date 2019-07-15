#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <thread>
#include "pthread.h"
#include <mutex>
using namespace std;

bool flag2=false;
 int counter=3; // Counter for multiple threads                                                                                                                                            
 int primes = 2; // counter for primes                                                                                                                                                     
 int tCount; // var for user input thread vaue                                                                                                                                             
 int primeLimit; // va\240mutex myMutex;r for user input limit value                                                                                                                       
 mutex myMutex; // global mutex var to lock class objects  

// Function prototypes
void findPrime(); // Void function to find amicable primes
void addPrime(); // void function to add amicable primes
int getNext(); // Void function to increment number for findPrime

// Global Variables for thread access
 
//-----------------------------------




int main(int argc, char *argv[])
{

  // *****************************************************************
  //  Data declarations...
  stringstream mySS;
  string stars;
  stars.append(65, '*');
  // ------------------------------------------------------------------
  //  Get/verify command line arguments.
  //Error out if bad arguments...

  if (argc == 1) {
    cout << "Usage: primes -t <threadCount> -l <limitValue>" << endl;
    exit(1);
  }

  if (argc != 5) {
    cout << "Error, invalid command line options!" << endl;
    exit(1);
  }

  if (string(argv[1]) != "-t") {
    cout << "Error, invalid thread count specifier!" << endl;
    exit(1);
  }

  if (string(argv[3]) != "-l") {
    cout << "Error, invalid limit value specifier!" << endl;
    exit(1);
  }

  // input string arguments from arg vector into int variables
  mySS << argv[2];
  mySS >> tCount;
  mySS.clear();
  mySS << argv[4];
  mySS >> primeLimit;

  // Error checking for out of range values
  if (tCount >= 130) {
    cout << "Error: Thread count is out of range (1 - 128)" << endl;
    exit(1);
  }
  
  if (primeLimit > 1000000000 || primeLimit < 4) {
    cout << "Error: Limit input is out of range (4 - 100,000,000)" << endl;
    exit(1);
  }

  // ------------------------------------------------------------------
  //  Argument Error checking finished.

  // Print out headers for program
  cout << stars << endl << "CS 219 - Assignment #12" << endl;
  cout << "Finding Prime Numbers..." << endl << endl;

  // ------------------------------------------------------------------
  //  Main processing

  // get start timer
  auto t1 = chrono::high_resolution_clock::now();


  // Loop thread count
  thread *t = new thread[tCount];
  for(int i = 0; i < tCount; i++) {
    t[i] = thread(findPrime); // call thread with findPrime function
  }
  for(int j = 0; j < tCount; j++) {
    t[j].join(); // join threads with main
  }

  // get end time
  auto t2 = chrono::high_resolution_clock::now();

  // show results with times
  cout << "Primes Found: " << primes << endl;
  cout << "Program took: "
       << chrono::duration_cast<chrono::milliseconds>
    (t2 - t1).count() << " milliseconds." << endl;
  // *****************************************************************
  //  All done.

  return 0;
}


// main findPrime Algorithm
void findPrime() {
  while(flag2==false) {
    int n=getNext();
    if (n<primeLimit){
     int var1=0;
     bool flag=false;
   int sqre=n;
    while (n%2!=0 && flag==false){
     var1=((n/sqre)+sqre)/2;
    int var2=sqre-var1;
       if(var2>=1){
         sqre=var1;}
       else{
	 
         for(int i=3; i<var1; i=i+2){
	   if(var1%i==0){flag=true; break; }}
	 if (flag==false) { addPrime(); flag=true;}
       }}}
    else{ flag2=true;}

  }                
}



// Will increment counter
int getNext() {
  lock_guard<mutex> guard(myMutex); // Lock count variable to single access
  counter=counter+1;
  return counter;
}

// Will increment prime count
void addPrime() {
  lock_guard<mutex> guard(myMutex); // Lock prime increment to single access at a time
  primes=primes+1;
}