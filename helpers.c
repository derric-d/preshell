#include <shell.h>

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if the contents of both strings are equal, -1 for errors, and
 *      the difference between the first characters that do not match otherwise
 */

int _strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (-1);

	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strcpy - copies the string pointed to by src to a buffer pointed to by dest
 * @dest: pointer to the buffer where the string is to be copied
 * @src: string to be copied
 *
 * Return: pointer to the copied string
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	if (!dest || !src)
		return (NULL);

	for (i = 0; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';

	return (dest);
}

/**
 * _strspn - searches for an initial segment of a string that only includes
 *           characters in a given array
 * @s: string to be scanned
 * @accept: characters to be scanned for
 *
 * Return: number of chars in a string s that consists only of chars in accept,
 *         -1 for any errors
 */

int _strspn(char *s, char *accept)
{
	int seg_count, in_accept, i;

	if (!s || !accept)
		return (-1);

	/* in_accept = 0; */
	for (seg_count = 0; s[seg_count]; seg_count++)
	{
		in_accept = 0;
		for (i = 0; accept[i]; i++)
		{
			if (s[seg_count] == accept[i])
				in_accept = 1;
		}
		if (!in_accept)
			break;
	}
	return (seg_count);
}
