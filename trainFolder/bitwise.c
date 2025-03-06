
// C Program to demonstrate use of bitwise operators

#include <stdio.h>
int main()
{
    // a = 5 (00000101 in 8-bit binary), b = 9 (00001001 in
    // 8-bit binary)
    unsigned int a = 5, b = 9;
	// a = 5 > 0000 0101
	// b = 9 > 0000 1001
	
    
	// The result is 00000001
	// BITWISE 
	// & Only if both are a bit to 1 
	// | only if 1 of those are one the bit will be 1
	// ^ if both bit are different the result is 1 
	// bitwise NOT ~ inverse all the bit.
    printf("a = %u, b = %u\n", a, b);
    printf("a&b = %u\n", a & b);

    // The result is 00001101
    printf("a|b = %u\n", a | b);

    // The result is 00001100
    printf("a^b = %u\n", a ^ b);

    // The result is 11111111111111111111111111111010
    // (assuming 32-bit unsigned int)
    printf("~a = %u\n", a = ~a);

    // The result is 00010010
    printf("b<<1 = %u\n", b << 1);

    // The result is 00000100
    printf("b>>1 = %u\n", b >> 1);

    return 0;
}
