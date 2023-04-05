/**
 * @brief mem.c
*  this source implements mem algorithems 
 * that support memory allocation and process manipulation
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 
//********************************************************************************************
//
// including header  files
//
//********************************************************************************************
 #include "mem.h"
//********************************************************************************************
//
// Global variables 
//
//********************************************************************************************

//********************************************************************************************
//
// Method definitions
//
//********************************************************************************************
/**
 * @brief  find the substring s in the long string l and return a pointer for it or NULL
 * 
 * @details memmem() function finds the start of the first occurrence of
            the substring s of length s_len in the memory area l of length l_len.
            it returns a pointer to the beginning of the substring, or NULL if the substring is not found.
 * 
 * @param l         : the main long string
 * @param l_len     : the length of the main string
 * @param s         : the substring looking for
 * @param s_len     : the length of the substring
 * @return void*    a pointer to the beginning of the substring in the main string or NULL
 */


void * memmem(const void *l, size_t l_len, const void *s, size_t s_len)
{
	char *cur, *last;//register
	const char *cl = (const char *)l;
	const char *cs = (const char *)s;

	/* we need something to compare */
	if (l_len == 0 || s_len == 0)
		return NULL;

	/* "s" must be smaller or equal to "l" */
	if (l_len < s_len)
		return NULL;

	/* special case where s_len == 1 */
	if (s_len == 1)
		return memchr(l, (int)*cs, l_len);

	/* the last position where its possible to find "s" in "l" */
	last = (char *)cl + l_len - s_len;

	for (cur = (char *)cl; cur <= last; cur++)
		if (cur[0] == cs[0] && memcmp(cur, cs, s_len) == 0)
			return cur;

	return NULL;
}
//--------------------------------------------------------------------------------------------
