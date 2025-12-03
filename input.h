#define INT " %d"
#define STR " %[^\n]s"
#define FLOAT " %f"
#define CHAR " %c"

void input(char tipo[], char label[], void* point){
	printf("%s", label);
	scanf(tipo, point);
}
