#define TRUE            1
#define FALSE           0
#define BOOL            int
#define INDEX_NOT_FOUND -1
#define EPSILON         0.000001

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
Integer*  new_integer(int    value);
Double*   new_double (double value);
String*   new_string (char*  value);

// Comparison methods
BOOL  integer_equals(const void * a, const void * b);
BOOL  double_equals (const void * a, const void * b);
BOOL  string_equals (const void * a, const void * b);

// Recyclers
void free_integer(Integer* wrapper);
void free_double (Double*  wrapper);
void free_string (String*  wrapper);
