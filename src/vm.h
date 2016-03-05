#ifndef vm_h
#define vm_h


#define STACK_SIZE 256
#define NUM_GLOBALS (1<<5)


typedef struct vm {
    int program_counter;
    int stack_pointer;
    int frame_pointer;

    int * code;
    int * globals;

    int * stack;
} VirtualMachine;


void execute( int * code, int start_addr, int length );

#endif
