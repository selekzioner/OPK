#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

void bitcpy(unsigned char *dst, size_t dst_ofs, unsigned char *src, size_t src_ofs, size_t bit_count) {

	unsigned char buf[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
	
	for (size_t i = 0, j = src_ofs, k = dst_ofs; i < bit_count; i++, j++, k++) {
		size_t incr;

		if ((j % 8) > (k % 8)) {
			incr = (j % 8) - (k % 8);
			dst[k / 8] = (dst[k / 8] & (~buf[k % 8])) | ((src[j / 8] & buf[j % 8]) >> incr);
		}

		else {
			incr = (k % 8) - (j % 8);
			dst[k / 8] = (dst[k / 8] & (~buf[k % 8])) | ((src[j / 8] & buf[j % 8]) << incr);
		}
	}
}

bool ch_cmp (unsigned char* str, unsigned char* src, size_t size){
	for (size_t i = 0; i < size; i++)
		if (str[i] != src[i])
			return false;

	return true;
}

int main(){

	unsigned char dst1[] = { 0x07, 0x00 };
	unsigned char src1[] = { 0x66, 0xfd };
	unsigned char res1[] = { 0xf7, 0x01 };
	bitcpy(dst1, 2, src1, 8, 7);
	assert(ch_cmp(dst1, res1, 2));

	unsigned char src2[] = { 0xef, 0xe8, 0x6c };
	unsigned char dst2[] = { 0xa8, 0x54, 0xe1 };
	unsigned char res2[] = { 0xa8, 0x3b, 0xe2 };
	bitcpy(dst2, 7, src2, 1, 11);
	assert(ch_cmp(dst1, res1, 3));

	unsigned char src3[] = { 0x01, 0xff, 0x00 }; 
	unsigned char dst3[] = { 0xf2, 0xfd, 0xad }; 
	unsigned char res3[] = { 0x01, 0xff, 0x00 };
	bitcpy(dst3, 0, src3, 0, 24);
	assert(ch_cmp(dst3, res3, 3));

	unsigned char src4[] = { 0x0b, 0x77, 0x1f };
	unsigned char dst4[] = { 0xab };             
	unsigned char res4[] = { 0xaa };		  	 
	bitcpy(dst4, 0, src4, 7, 2);
	assert(ch_cmp(dst4, res4, 1));

	unsigned char dst5[] = { 0x11, 0x02 }; 
	unsigned char src5[] = { 0xe8, 0xf1 };
	unsigned char res5[] = { 0x19, 0x0f };
	bitcpy(dst5, 3, src5, 7, 11);
	assert(ch_cmp(dst5, res5, 2));
	
	unsigned char src6[] = { 0xcd, 0xbf, 0xbe, 0xbd, 0xbc, 0xaf, 0xae, 0xad, 0xac, 0xab };														
	unsigned char dst6[] = { 0x13, 0x12, 0x11, 0x10 };											
	unsigned char res6[] = { 0xbd, 0xbc, 0xaf, 0xae };
	bitcpy(dst6, 0, src6, 24, 32);
	assert(ch_cmp(dst6, res6, 4));

	return 0;
}