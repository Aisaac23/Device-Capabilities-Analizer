/*This program makes a through analysis to find some of the capabalities of a device's implementation. This includes numerical and char types, some basic processing units and a couple of locale settings.
As long as the device supports the #included C standard libraries, you'll be able to get a report of its capabilities. 

As an input you can provide the name of a file; or an empty string "" so all the information will be sent to stdout. 

./dca myImplementationCapabilities.txt
*/
#ifndef DCA_H_
#define DCA_H_

#include <limits.h>
#include <float.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>



void deviceCapabilitiesAnalizer( char *stream );
long double factorial(long double n);
int compareints (const void * a, const void * b);

void intLimits( FILE *stream );
void charLimits( FILE *stream );
void floatLimits( FILE *stream );
void mantisaAndExponentLimits(FILE *stream);
void epsilonLimits(FILE *stream);
void fullReport(char *fileName);

void localeSettings(FILE *stream);
void storageSizes(FILE *stream);

unsigned long long swapsPerSecond(FILE *stream, const int ARRAY_SIZE);
unsigned long long comparisonsPerSecond(FILE *stream);
unsigned long long memoryAllocationsPerSecond(FILE *stream);
unsigned long long linearSearchesPerSecond(FILE *Stream, const int ARRAY_SIZE);
unsigned long long binarySearchesPerSecond( FILE *Stream, const int ARRAY_SIZE );


#endif
