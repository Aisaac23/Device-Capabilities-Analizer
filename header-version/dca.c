#include "dca.h"

//Calls all the functions to create a full report of all the system limits and capabilities on stdout or on a file.
void fullReport(char *fileName)
{
	const int ARRAY_SIZE = 10000;
	FILE *stream;
	if(fileName == NULL)
		stream = stdout;
	else
		stream = fopen(fileName, "a");

	intLimits( stream );
	charLimits( stream );
	
	floatLimits( stream );
	mantisaAndExponentLimits(stream);
	epsilonLimits(stream);
	
	storageSizes(stream);

	fprintf(stream, "Clocks per second:%lu\n\n", CLOCKS_PER_SEC);

	fprintf(stream, "Swaps per second:%llu\n", swapsPerSecond(stream, ARRAY_SIZE) );
	fprintf(stream, "Comparisons per second:%llu\n", comparisonsPerSecond(stream) );
	fprintf(stream, "Memory allocations per second:%llu\n", memoryAllocationsPerSecond(stream) );
	fprintf(stream, "Linear searches in a %u length array:%llu\n", ARRAY_SIZE, linearSearchesPerSecond(stream, ARRAY_SIZE) );
	fprintf(stream, "Binary searches in a %u length array:%llu\n", ARRAY_SIZE, binarySearchesPerSecond( stream, ARRAY_SIZE) );
	
	localeSettings(stream);

	if( fileName != NULL )
		fclose(stream);
	
}

//auxiliar function for the binary search function
int compareints (const void *a, const void *b)
{
  return ( *(int*)a - *(int*)b );
}

//summarizes the limits for all integer/long/short types
void intLimits( FILE *stream )
{	
	fprintf(stream, "int (max):%d\n", INT_MAX);
	fprintf(stream, "int (min):%d\n\n", INT_MIN);

	fprintf(stream, "long (max):%ld\n", (long) LONG_MAX);
	fprintf(stream, "long (min):%ld\n\n", (long) LONG_MIN);

	fprintf(stream, "short (max):%d\n", SHRT_MAX);
	fprintf(stream, "short (min):%d\n\n", SHRT_MIN);

	fprintf(stream, "unsigned int (max):%u\n", (unsigned int) UINT_MAX);
	fprintf(stream, "unsigned long (max):%lu\n", (unsigned long) ULONG_MAX);
	fprintf(stream, "unsigned char (max):%d\n", UCHAR_MAX);
	fprintf(stream, "unsigned short (max):%d\n\n", (unsigned short) USHRT_MAX);

}

//summarizes the limits for all char/wide char types
void charLimits( FILE *stream )
{
	fprintf(stream, "char (max):%d\n", CHAR_MAX);
	fprintf(stream, "char (min):%d\n", CHAR_MIN);
	fprintf(stream, "char (bits):%d\n\n", CHAR_BIT);

	fprintf(stream, "signed char (max):%d\n", SCHAR_MAX);
	fprintf(stream, "signed char (min):%d\n\n", SCHAR_MIN);
}

//summarizes the storagas sizes for all the primitive types
void storageSizes(FILE *stream)
{
	fprintf(stream, "char (storage size):%-lu\n", sizeof(char) );
	fprintf(stream, "Multybyte char for any locale (bytes):%-d\n\n", MB_LEN_MAX);

	fprintf(stream, "float (storage size):%lu\n", sizeof(float) );
	fprintf(stream, "double (storage size):%lu\n", sizeof(double) );
	fprintf(stream, "long double (storage size):%lu\n\n", sizeof(long double));

	fprintf(stream, "int (storage size):%-lu\n", sizeof(int) );
	fprintf(stream, "short (storage size):%-lu\n", sizeof(short) );
	fprintf(stream, "long int (storage size):%-lu\n", sizeof(long int) );
	fprintf(stream, "long long int (storage size):%-lu\n", sizeof(long long int) );

}

//summarizes the limits for all float/double types
void floatLimits( FILE *stream )
{
	fprintf(stream, "float (max):%g\n", (float) FLT_MAX);
	fprintf(stream, "float (min):%g\n\n", (float) FLT_MIN);
	
	fprintf(stream, "double (max):%g\n", (double) DBL_MAX);
	fprintf(stream, "double (min):%g\n\n", (double) DBL_MIN);
	
	fprintf(stream, "long double (max):%Lg\n", (long double) LDBL_MAX);
	fprintf(stream, "long double (min):%Lg\n\n", (long double) LDBL_MIN);

	fprintf(stream, "Base for all floating-point types (float, double, long double):\t%d\n\n", FLT_RADIX);
	fprintf(stream, "Precision value (float):%d\n", FLT_DIG );
	fprintf(stream, "Precision value (double):%d\n", DBL_DIG);
	fprintf(stream, "Precision value (long double):%d\n\n", LDBL_DIG );
}

//summarizes the limits for the mantisa/significand and the exponent of a float/double type 
void mantisaAndExponentLimits(FILE *stream)
{
	fprintf(stream, "Mantisa bits / significand (float):%d\n", FLT_MANT_DIG);
	fprintf(stream, "Mantisa bits / significand (double):%d\n", DBL_MANT_DIG);
	fprintf(stream, "Mantisa bits / significand (long double):%d\n\n", LDBL_MANT_DIG);
	
	fprintf(stream, "Minimum int value for the exponent (float):%d\n", FLT_MIN_EXP);
	fprintf(stream, "Minimum int value for the exponent (double):%d\n", DBL_MIN_EXP);
	fprintf(stream, "Minimum int value for the exponent (long double):%d\n\n", LDBL_MIN_EXP );

	fprintf(stream, "Maximum int value for the exponent (float):%d\n", FLT_MAX_EXP);
	fprintf(stream, "Maximum int value for the exponent (double):%d\n", DBL_MAX_EXP);
	fprintf(stream, "Maximum int value for the exponent (long double):%d\n\n", LDBL_MAX_EXP );
}

//summarizes the limits for the epsilon value.
void epsilonLimits(FILE *stream)
{

	fprintf(stream, "Difference between 1 and the least value greater than 1 that is representable. (float):%g\n", FLT_EPSILON);
	fprintf(stream, "Difference between 1 and the least value greater than 1 that is representable. (double):%g\n", DBL_EPSILON);
	fprintf(stream, "Difference between 1 and the least value greater than 1 that is representable. (long double):%Lg\n\n", LDBL_EPSILON );

}

//tells how many swaps per second the computer is capable to perform. Note this is just an aporximate measure.
unsigned long long swapsPerSecond(FILE *stream, const int ARRAY_SIZE)
{
	int array[ARRAY_SIZE];
	clock_t tOneScond, tCounter;
	
	for(int a = 0; a<ARRAY_SIZE; a++)
		array[a] = a;

	unsigned long long times = 0;
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

	return times;
}

//tells how many comparisons per second the computer is capable to perform. Note this is just an aporximate measure.
unsigned long long comparisonsPerSecond(FILE *stream)
{
	clock_t tOneScond, tCounter;
	
	unsigned long long times = 0;
	tCounter = clock();
	tOneScond = clock()+CLOCKS_PER_SEC;
	while(tCounter < tOneScond)
	{
		if(tCounter < tOneScond)
			times++;
		tCounter = clock();	
	}
	
	return times;
}

//tells how many memory allocations per second the computer is capable to perform. Note this is just an aporximate measure.
unsigned long long memoryAllocationsPerSecond(FILE *stream)
{
	unsigned long long times = 0;
	clock_t tOneScond, tCounter;

	tCounter = clock();
	tOneScond = clock()+CLOCKS_PER_SEC;
	char *space = calloc(1, sizeof(char));
	while(tCounter < tOneScond)
	{
		space = realloc(space, times*sizeof(char));
		times++;
		tCounter = clock();
	}

	return times;

}

//tells how many linear searches per second the computer is capable to perform. Note this is just an aporximate measure.
unsigned long long linearSearchesPerSecond(FILE *stream, const int ARRAY_SIZE)
{
	int array[ARRAY_SIZE];
	clock_t tOneScond, tCounter;
	
	for(int a = 0; a<ARRAY_SIZE; a++)
		array[a] = a;

	unsigned long long times = 0;
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
	
	return times;
}

//tells how many binary searches per second the computer is capable to perform. Note this is just an aporximate measure.
unsigned long long binarySearchesPerSecond( FILE *stream, const int ARRAY_SIZE)
{
	int * pItem, key;
	int array[ARRAY_SIZE];
	unsigned long long times = 0;
	clock_t tOneScond, tCounter;

	for(int a = 0; a<ARRAY_SIZE; a++)
		array[a] = a;

	times = 0;
	tCounter = clock();
	tOneScond = clock()+CLOCKS_PER_SEC;

	while(tCounter < tOneScond)
	{
		key = rand()%ARRAY_SIZE;
		pItem = (int*) bsearch (&key, array, ARRAY_SIZE, sizeof (int), compareints);
		times++;
		tCounter = clock();
	}
	return times;
}

//informs about the system locale settings and the current set locale settings in the program
void localeSettings(FILE *stream)
{
	char* locale;
	locale = setlocale(LC_ALL, NULL);
	fprintf(stream, "\nCurrent set locale: %s\n", locale);
	locale = setlocale(LC_ALL,"");
	fprintf(stream, "Current environment's locale: %s\n", locale);
	locale = setlocale(LC_ALL, NULL);
}
