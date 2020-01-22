/*This program makes a through analysis to find some of the capabalities of a device's implementation. This includes numerical and char types, some basic processing units and a couple of locale settings.
As long as the device supports the #included C standard libraries, you'll be able to get a report of its capabilities. 

As an input you can provide the name of a file; or an empty string "" so all the information will be sent to stdout. 

./dca myImplementationCapabilities.txt
*/
#include <limits.h>
#include <float.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>

void deviceCapabilitiesAnalizer( char *stream );
long double factorial(long double n);
int compareints (const void * a, const void * b);

int main(int argc, char *argv[])
{
	if( argc < 2 )
		argv[1] = NULL;
	deviceCapabilitiesAnalizer(argv[1]);
	return EXIT_SUCCESS;
}

void deviceCapabilitiesAnalizer(char *fileName)
{
	FILE *stream;
	if(fileName == NULL)
		stream = stdout;
	else
		stream = fopen(fileName, "a");

	fprintf(stream, "*******Integer and character types*******\n\n");
	
	fprintf(stream, "int (storage size):%-lu\n", sizeof(int) );
	fprintf(stream, "char (storage size):%-lu\n", sizeof(char) );
	fprintf(stream, "short (storage size):%-lu\n", sizeof(short) );
	fprintf(stream, "long int (storage size):%-lu\n", sizeof(long int) );
	fprintf(stream, "long long int (storage size):%-lu\n", sizeof(long long int) );
	fprintf(stream, "Multybyte char for any locale (bytes):%-d\n\n", MB_LEN_MAX);
	
	fprintf(stream, "int (max):%d\n", INT_MAX);
	fprintf(stream, "int (min):%d\n\n", INT_MIN);

	fprintf(stream, "long (max):%ld\n", (long) LONG_MAX);
	fprintf(stream, "long (min):%ld\n\n", (long) LONG_MIN);

	fprintf(stream, "char (max):%d\n", CHAR_MAX);
	fprintf(stream, "char (min):%d\n", CHAR_MIN);
	fprintf(stream, "char (bits):%d\n\n", CHAR_BIT);

	fprintf(stream, "short (max):%d\n", SHRT_MAX);
	fprintf(stream, "short (min):%d\n\n", SHRT_MIN);

	fprintf(stream, "signed char (max):%d\n", SCHAR_MAX);
	fprintf(stream, "signed char (min):%d\n\n", SCHAR_MIN);

	fprintf(stream, "unsigned int (max):%u\n", (unsigned int) UINT_MAX);
	fprintf(stream, "unsigned long (max):%lu\n", (unsigned long) ULONG_MAX);
	fprintf(stream, "unsigned char (max):%d\n", UCHAR_MAX);
	fprintf(stream, "unsigned short (max):%d\n\n", (unsigned short) USHRT_MAX);
	
	fprintf(stream, "\n*******Floating point types*******\n\n");
	fprintf(stream, "float (storage size):%lu\n", sizeof(float) );
	fprintf(stream, "double (storage size):%lu\n", sizeof(double) );
	fprintf(stream, "long double (storage size):%lu\n\n", sizeof(long double));

	fprintf(stream, "float (max):\t%g\n", (float) FLT_MAX);
	fprintf(stream, "float (min):\t%g\n\n", (float) FLT_MIN);
	
	fprintf(stream, "double (max):\t%g\n", (double) DBL_MAX);
	fprintf(stream, "double (min):\t%g\n\n", (double) DBL_MIN);
	
	fprintf(stream, "long double (max):\t%Lg\n", (long double) LDBL_MAX);
	fprintf(stream, "long double (min):\t%Lg\n\n", (long double) LDBL_MIN);

	fprintf(stream, "Base for all floating-point types (float, double, long double):\t%d\n\n", FLT_RADIX);
	fprintf(stream, "Precision value (float):%d\n", FLT_DIG );
	fprintf(stream, "Precision value (double):%d\n", DBL_DIG);
	fprintf(stream, "Precision value (long double):%d\n\n", LDBL_DIG );
	
	fprintf(stream, "Mantisa bits / significand (float):%d\n", FLT_MANT_DIG);
	fprintf(stream, "Mantisa bits / significand (double):%d\n", DBL_MANT_DIG);
	fprintf(stream, "Mantisa bits / significand (long double):%d\n\n", LDBL_MANT_DIG);
	
	fprintf(stream, "Minimum int value for the exponent (float):%d\n", FLT_MIN_EXP);
	fprintf(stream, "Minimum int value for the exponent (double):%d\n", DBL_MIN_EXP);
	fprintf(stream, "Minimum int value for the exponent (long double):%d\n\n", LDBL_MIN_EXP );

	fprintf(stream, "Maximum int value for the exponent (float):%d\n", FLT_MAX_EXP);
	fprintf(stream, "Maximum int value for the exponent (double):%d\n", DBL_MAX_EXP);
	fprintf(stream, "Maximum int value for the exponent (long double):%d\n\n", LDBL_MAX_EXP );

	fprintf(stream, "Difference between 1 and the least value greater than 1 that is representable. (float):%g\n", FLT_EPSILON);
	fprintf(stream, "Difference between 1 and the least value greater than 1 that is representable. (double):%g\n", DBL_EPSILON);
	fprintf(stream, "Difference between 1 and the least value greater than 1 that is representable. (long double):%Lg\n\n", LDBL_EPSILON );

	fprintf(stream, "\n*******Processing*******\n\n");
	//Clock ticks are units of time of a constant but system-specific length, as those returned by function clock.
	fprintf(stream, "Clocks per second:%lu\n\n", CLOCKS_PER_SEC);

	const unsigned int ARRAY_SIZE = 10000;
	clock_t tOneScond, tCounter;
  	int array[ARRAY_SIZE];
	unsigned int times = 0;

	for(int a = 0; a<ARRAY_SIZE; a++)
		array[a] = a;

	times = 0;
	tCounter = clock();
	tOneScond = clock()+CLOCKS_PER_SEC;
	while(tCounter < tOneScond)
	{
		int temp = array[0];
		array[0] = array[1];
		array[1] = temp;
		times++;
		tCounter = clock();
	}
	fprintf(stream, "Swaps per second:%u\n", times);
	
	times = 0;
	tCounter = clock();
	tOneScond = clock()+CLOCKS_PER_SEC;
	while(tCounter < tOneScond)
	{
		times++;
		tCounter = clock();	
	}
	fprintf(stream, "Comparisons per second:%u\n", times);

	times = 0;
	tCounter = clock();
	tOneScond = clock()+CLOCKS_PER_SEC;
	char *space = calloc(1, sizeof(char));
	while(tCounter < tOneScond)
	{
		space = realloc(space, times*sizeof(char));
		times++;
		tCounter = clock();
	}
	fprintf(stream, "Memory allocations per second:%u\n", times);

	int key;
	times = 0;
	tCounter = clock();
	tOneScond = clock()+CLOCKS_PER_SEC;
	srand (time(NULL));
	while(tCounter < tOneScond)
	{
		key = rand()%ARRAY_SIZE;
		for(int i = 0; i<ARRAY_SIZE; i++ )
			if(array[i] == key)
			{
				key = array[i];
				i = ARRAY_SIZE;
			}
		times++;
		tCounter = clock();
	}
	fprintf(stream, "Linear searches in a %u length array:%u\n", ARRAY_SIZE, times);

	int * pItem;

	times = 0;
	tCounter = clock();
	tOneScond = clock()+CLOCKS_PER_SEC;
	//srand (time(NULL));
	while(tCounter < tOneScond)
	{
		key = rand()%ARRAY_SIZE;
		pItem = (int*) bsearch (&key, array, ARRAY_SIZE, sizeof (int), compareints);
		times++;
		tCounter = clock();
	}
	fprintf(stream, "Binary searches in a %u length array:%u\n", ARRAY_SIZE, times);
	
	char* locale;
	locale = setlocale(LC_ALL, NULL);
	fprintf(stream, "\nCurrent set locale: %s\n", locale);
	locale = setlocale(LC_ALL,"");
	fprintf(stream, "Current environment's locale: %s\n", locale);
	locale = setlocale(LC_ALL, NULL);

	if( fileName != NULL )
		fclose(stream);
	
}

int compareints (const void *a, const void *b)
{
  return ( *(int*)a - *(int*)b );
}

