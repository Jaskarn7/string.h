#ifndef _STDIO_H
#include <stdio.h>
#endif
#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#ifdef __MAX_STRING_SIZE__
#undef __MAX_STRING_SIZE__
#endif

#define __MAX_STRING_SIZE__ 0x0100

int str_len(char* _str)
{
	/* Returns length of the string passed */

	char* letter = _str; /* This is where the address of Null terminator will be stored */

	__asm {
		cld
		xor edi, edi
		xor eax, eax
		mov eax, 0x0000 /* Ascii code for NULL terminator ('\0') */
		mov ecx, __MAX_STRING_SIZE__ /* MAX length upto which string will be scanned (Default 256 bytes) */
		mov edi, dword ptr[ebp + 8]
		repne scasb
		dec edi
		mov letter, edi
	}
	return (letter - _str);
}

int str_cmp(char* _str1, char* _str2)
{
	/* Returns 1 if strings are equal otherwise 0 */
	int _str_length = str_len(_str1); /* Length of first passed string */

	if (_str_length != str_len(_str2))
		return 0;

	char c1;

	__asm {
		cld
		mov esi, _str1
		mov edi, _str2
		mov ecx, _str_length
		repe cmpsb
		jecxz EQUAL

		/* If not equal */
		mov c1, 0x0000
		jmp DONE

		/* If equal */
		EQUAL:
		mov c1, 0x0001

		DONE:
	}
	
	/* Checking the last character of string */
	if (c1 == 1)
		return (*(_str1 + _str_length - 1) == *(_str2 + _str_length - 1));
	
	return c1;
}

void str_cpy(char *_str1, char *_str2)
{
	/* Replaces string from `_str2` to `_str1` */
	int _str_length = str_len(_str1);

	if (_str_length < str_len(_str2)) {
		fprintf(stderr, "Error: str_cpy, source string length must be less than or equal to destination string\n");
		return;
	}

	__asm {
		cld
		mov esi, _str2
		mov edi, _str1
		mov ecx, _str_length
		inc ecx
		rep movsb 
	}
}

char *str_cat(char *_str1, char *_str2)
{
	/* Concatenates string from _str2 to _str1 */
	/* Returns address of the resulting string */
	int _str1_length = str_len(_str1);
	int _str2_length = str_len(_str2);

	char *result_str = (char *) malloc((_str1_length + _str2_length + 1) * sizeof(char));
	
	char *__temp__ = _str1;
	char *res_str_ptr = result_str;
	while (*__temp__ != '\0')
		*res_str_ptr++ = *__temp__++;
	
	__temp__ = _str2;
	while (*__temp__ != '\0')
		*res_str_ptr++ = *__temp__++;
	
	*res_str_ptr = '\0';
	
	return result_str;
}

char *str_chr(char *_str, int c)
{
	/* Returns pointer to first occurance to the character `c` in `_str` otherwise NULL */
	char *s = _str;
	int _str_length = str_len(_str);

	__asm {
		cld
		mov eax, c
		mov edi, s
		mov ecx, _str_length
		repne scasb
		dec edi
		mov s, edi
	}

	if (*s == c)
		return s;
	
	return NULL;
	
}
