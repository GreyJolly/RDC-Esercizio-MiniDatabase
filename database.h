
// This represents a record in the only schema of this database
typedef struct Persona {
    char name[20];
    char surname[50];
    char address[100];
    int age;
} Persona;

// This is a node of an index that holds a string
typedef struct IndexNodeString {
    char * value;
    struct IndexNodeString * left;
    struct IndexNodeString * right;
	Persona * persona;
} IndexNodeString;

// This is a node of an index that holds an int
typedef struct IndexNodeInt {
    int value;
    struct IndexNodeInt * left;
    struct IndexNodeInt * right;
	Persona * persona;
} IndexNodeInt;

// A database holds a set of records and a set of indexes
typedef struct {
    IndexNodeString * name;
    IndexNodeString * surname;
    IndexNodeString * address;
    IndexNodeInt * age;
} Database;

// Interface
void insert(Database * database, Persona * persona);
Persona* findByName(Database * database, char * name);
Persona* findBySurname(Database * database, char * surname);
Persona* findByAddress(Database * database, char * address);
Persona* findByAge(Database * database, int age);

// Auxiliary functions
void freeDatabase(Database * database);
void printDatabase(Database * database);
