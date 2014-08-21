#include <stdlib.h>
#include <stdio.h>

#include "opcode.h"
#include "vm.h"



static VirtualMachine * init_vm ( VirtualMachine * vm, int * code )
{
    vm->program_counter = 0;
    vm->stack_pointer = -1;
    vm->frame_pointer = -1;

    vm->code = code;
    vm->globals = malloc( sizeof(int) * NUM_GLOBALS );

    vm->stack = malloc( sizeof(int) * STACK_SIZE );
}


static void cleanup_vm ( VirtualMachine * vm )
{
    free( vm->globals );
    free( vm->stack );
}

#ifdef TRACE

static void print_stack ( VirtualMachine * vm )
{
    int i;
    printf("\t[ ");
    for ( i = 0; i <= vm->stack_pointer; i++)
    {
        printf("%d, ", vm->stack[ i ]);
    }
    printf(" ]\n");
}

static void print_globals( VirtualMachine * vm )
{
    int i;
}

#endif

#define PUSH(value) (vm.stack[++vm.stack_pointer] = (value))
#define POP() (vm.stack[vm.stack_pointer--])


void eval_code( int * code, int start_addr, int length )
{
    VirtualMachine vm; init_vm( &vm, code );
    int opcode;
    int a;
    int b;
    int run = 1;

    vm.program_counter = start_addr;

    #ifdef TRACE
    
    int program_counter = vm.program_counter;
    
    #endif

    while ( vm.program_counter < length && run )
    {
        #ifdef TRACE
        program_counter = vm.program_counter;
        #endif

        opcode = vm.code[vm.program_counter++]; // Fetch and increment program counter

        switch (opcode)
        {
            case OP_IADD:
            {
                b = POP();
                a = POP();
                PUSH(a + b);
                break;
            }
            case OP_ISUB:
            {
                b = POP();
                a = POP();
                PUSH(a - b);
                break;
            }
            case OP_IMUL:
            {
                b = POP();
                a = POP();
                PUSH(a * b);
                break;
            }
            case OP_IDIV:
            {
                b = POP();
                a = POP();
                PUSH(a / b);
                break;
            }
            case OP_ILT:
            {
                b = POP();
                a = POP();
                PUSH(a < b);
                break;
            }
            case OP_IEQ:
            {
                b = POP();
                a = POP();
                PUSH(a == b);
                break;
            }
            case OP_BR:
            {
                vm.program_counter = vm.code[vm.program_counter];
                break;
            }
            case OP_BRT:
            {
                a = POP();
                b = vm.code[vm.program_counter++];
                if (a) vm.program_counter = b;
                break;
            }
            case OP_BRF:
            {
                a = POP();
                b = vm.code[vm.program_counter++];
                if (!a) vm.program_counter = b;
                break;
            }
            case OP_ICONST:
            {
                PUSH(vm.code[vm.program_counter++]);
                break;
            }
            case OP_CALL:
            {
                a = vm.code[vm.program_counter++];      // Get address.
                PUSH(vm.code[vm.program_counter++]);    // Number of arguments.
                PUSH(vm.frame_pointer);                 // Save frame pointer.
                PUSH(vm.program_counter);               // Remember where we were before the call.
                vm.frame_pointer = vm.stack_pointer;    // Set the frame pointer to the current stack pointer.
                vm.program_counter = a;                 // Jump to the function code.
                break;
            }
            case OP_RETURN:
            {
                a = POP();                              // Get the return value;
                vm.stack_pointer = vm.frame_pointer;    // Restore the stack pointer.
                vm.program_counter = POP();             // Restore the program counter.
                vm.frame_pointer = POP();               // Restore the frame pointer.
                b = POP();                              // Get number of arguments.
                vm.stack_pointer -= b;                  // Drop the arguments from the stack.
                PUSH(a);                                // Leave the call result on the stack.
                break;
            }
            case OP_LOAD:
            {
                a = vm.code[vm.program_counter++];      // Offset
                PUSH(vm.stack[vm.frame_pointer + a]);
                break;
            }
            case OP_STORE:
            {
                a = vm.code[vm.program_counter++];      // Offset
                vm.stack[vm.frame_pointer + a] = POP();
                break;
            }
            case OP_GLOAD:
            {
                a = vm.code[vm.program_counter++];      // Offset
                PUSH(vm.globals[a]);
                break;
            }
            case OP_GSTORE:
            {
                a = vm.code[vm.program_counter++];      // Offset
                vm.globals[a] = POP();
                break;
            }
            case OP_PRINT:
            {
                a = POP();
                printf("\n%d\n\n", a);
                break;
            }
            case OP_POP:
            {
                POP();
                break;
            }
            case OP_HALT:
            {
                run = 0;
                break;
            }
        } // switch (opcode)

        #ifdef TRACE
        
        printf("%04d \t %s", program_counter, opcode_names[opcode]);
        print_stack( &vm );

        #endif
    } // while ( vm.program_counter < length )

    cleanup_vm( &vm );
}