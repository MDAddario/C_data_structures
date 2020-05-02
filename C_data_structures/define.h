#define TRUE             1
#define FALSE            0
#define BOOL             int
#define INDEX_NOT_FOUND  -1
#define EPSILON          0.000001

// Wrapper classes
typedef struct struct_integer {

	int entry;

} Integer;

typedef struct struct_double {

	double entry;

} Double;

typedef struct struct_string {

	char* entry;

} String;

// Constructors
Integer*  new_integer(int    entry);
Double*   new_double (double entry);
String*   new_string (char*  entry);

// Comparison methods
BOOL  integer_equals(Integer* a, Integer* b);
BOOL  double_equals (Double*  a, Double*  b);
BOOL  string_equals (String*  a, String*  b);

// Recyclers
void integer_free(Integer* wrapper);
void double_free (Double*  wrapper);
void string_free (String*  wrapper);
