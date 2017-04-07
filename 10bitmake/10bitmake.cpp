// 10bitmake.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "stdio.h"
#include "iostream"
#include "bitset"

char* tenbit(int* input);
int* arrayadd(int *input);
int *readppm(char *filename, int *width, int *height);
int main()
{
	int height, width;
	using namespace std;
	FILE *fp;
	FILE *fin;
	int err = fopen_s(&fp, "test.bin", "wb");
	if (err != 0)
	{
		cout << "open file fail!" << endl;
		return -1;
	}
	int* ppmdata;
	ppmdata = readppm("1440x2560x30.ppm" , &width , &height);
	//printf("first 3 = %d , %d , %d\n ",*ppmdata , *(ppmdata + 1) , *(ppmdata+2));
	printf("Start build bin file\n");
	int indata[12];
	char *outdata;
	int loopnumber = height * width / 4;
	for (int i = 0; i < loopnumber ; i++)
	{
		indata[0] = *(ppmdata + i * 12);
		indata[1] = *(ppmdata + ((i * 12) + 1));
		indata[2] = *(ppmdata + ((i * 12) + 2));
		indata[3] = *(ppmdata + ((i * 12) + 3));
		indata[4] = *(ppmdata + ((i * 12) + 4));
		indata[5] = *(ppmdata + ((i * 12) + 5));
		indata[6] = *(ppmdata + ((i * 12) + 6));
		indata[7] = *(ppmdata + ((i * 12) + 7));
		indata[8] = *(ppmdata + ((i * 12) + 8));
		indata[9] = *(ppmdata + ((i * 12) + 9));
		indata[10] = *(ppmdata + ((i * 12) + 10));
		indata[11] = *(ppmdata + ((i * 12) + 11));
		outdata = tenbit(indata);
		fwrite(outdata, 15, sizeof(char), fp);
	}
	//cout << "open file succes" << endl;
	//
	//int err2 = fopen_s(&fin, "1440x2560x30.ppm", "r");
	//if (err2 != 0)
	//{
	//	cout << "open file fail!" << endl;
	//	return -1;
	//}
	//cout << "open file succes" << endl;

	//int indata[12] = { 0X3FF,0, 0 ,0X3FF,0, 0 , 0X3FF,0, 0 , 0X3FF,0, 0};
	//char *outdata = tenbit(indata);
	//fwrite(outdata, 15, sizeof(char), fp);

	//int ppmdata[12];
	//int testdata[12] = { 3,4,5 };
	//int *dataptr = testdata;
	//int *ppmptr;
	//ppmptr = (int*)malloc(1440 * 2560 * sizeof(int));
	//fscanf_s(fin, "%d", &testdata, sizeof(int));
	//printf("%d\n", *dataptr);
	//printf("%d\n", *(dataptr+1));
	//fscanf_s(fin, "%d", dataptr[1], sizeof(int));
	//fscanf_s(fin, "%d", testdata[2], sizeof(int));
	//fscanf_s(fin, "%d", testdata[3], sizeof(int));
	//while (!feof(fin)) {
	//	fscanf_s(fin, "%d", ppmptr++, sizeof(int));
	//}
	//printf("%d\n", *ppmptr);
	//for (int i = 0; i < 3; i++)
	//{
	//	cout << *(testdata + i) << endl;
	//}
	//printf("%X\n", testdata);
	//printf("%X\n", dataptr);

	//while (!feof(fin)) {
	//	fscanf_s(fin, "%d", dataptr , sizeof(int));
	//	dataptr++;
	//	
	//}
	//while (!feof(fin)) {
	//	fscanf_s(fin, "%d", dataptr, sizeof(int));
	//	dataptr++;

	//}
	//for (int i = 0; i < 10; i++)
	//{
	//	cout << "%d" << *dataptr << "\n";
	//}
	/*printf("%d\n", testdata);*/
	//cout << testdata << "\n";
	fclose(fp);
	printf("Build over!! \n");
	//fclose(fin);
	system("pause");
	return 0;
}

char* tenbit(int* input) //輸入12個10bit Data,輸出 size = 15的array
{
	char* out = (char*)malloc(sizeof(int) * 15);
	out[0] = *input; //餘2
	out[1] = *input >> 8 | *(input + 1) << 2; //餘4
	out[2] = *(input + 1) >> 6 | *(input + 2) << 4; //餘6
	out[3] = *(input + 2) >> 4 | *(input + 3) << 6; //餘8
	out[4] = *(input + 3) >> 2;

	out[5] = *(input + 4); //餘2
	out[6] = *(input + 4) >> 8 | *(input + 5) << 2; //餘4
	out[7] = *(input + 5) >> 6 | *(input + 6) << 4; //餘6
	out[8] = *(input + 6) >> 4 | *(input + 7) << 6; //餘8
	out[9] = *(input + 7) >> 2;

	out[10] = *(input + 8); //餘2
	out[11] = *(input + 8) >> 8 | *(input + 9) << 2; //餘4
	out[12] = *(input + 9) >> 6 | *(input + 10) << 4; //餘6
	out[13] = *(input + 10) >> 4 | *(input + 11) << 6; //餘8
	out[14] = *(input + 11) >> 2;
	return out;
}

int* arrayadd(int *input)
{
	int a = *input;
	int b = *(input + 1);
	int c = *(input + 2);
	int out[2] = { a + b , b + c };
	return out;
}

int *readppm(char *filename, int *width, int *height)
{
	FILE *fd;
	int  k, nm;
	char c;
	int i, j;
	char b[100];
	float s;
	int red, green, blue;
	long numbytes, howmuch;
	int n;
	int m;
	int *image;



	int err = fopen_s(&fd, filename, "rb");
	if (err != 0)
	{
		printf("Could not open %s\n", filename);
		return NULL;
	}

	c = getc(fd);
	if (c == 'P' || c == 'p')
		c = getc(fd);

	if (c == '3')
	{
		printf("%s is a PPM file (plain text version)\n", filename);

		// NOTE: This is not very good PPM code! Comments are not allowed
		// except immediately after the magic number.
		c = getc(fd);
		if (c == '\n' || c == '\r') // Skip any line break and comments
		{
			c = getc(fd);
			while (c == '#')
			{
				fscanf_s(fd, "%[^\n\r] ", b);
				printf("%s\n", b);
				c = getc(fd);
			}
			ungetc(c, fd);
		}
		fscanf_s(fd, "%d %d %d", &n, &m, &k);

		printf("%d rows  %d columns  max value= %d\n", n, m, k);

		numbytes = n * m * 3;
		image = (int *)malloc(numbytes * sizeof(int));
		if (image == NULL)
		{
			printf("Memory allocation failed!\n");
			return NULL;
		}
		i = 0;
		//for (i = m - 1; i >= 0; i--) for (j = 0; j<n; j++) // Important bug fix here!
		//{ // i = row, j = column
		//	fscanf_s(fd, "%d %d %d", &red, &green, &blue);
		//	image[0] = red;
		//	image[1] = green;
		//	image[2] = blue;
		//}
		while (!feof(fd)) {
			fscanf_s(fd, "%d", &red , sizeof(int));
			image[i] = red;
			i++;
			
		}
	}
	else
		if (c == '6')
		{
			printf("%s is a PPM file (raw version)!\n", filename);

			c = getc(fd);
			if (c == '\n' || c == '\r') // Skip any line break and comments
			{
				c = getc(fd);
				while (c == '#')
				{
					fscanf_s(fd, "%[^\n\r] ", b);
					printf("%s\n", b);
					c = getc(fd);
				}
				ungetc(c, fd);
			}
			fscanf_s(fd, "%d %d %d", &n, &m, &k);
			printf("%d rows  %d columns  max value= %d\n", m, n, k);
			c = getc(fd); // Skip the last whitespace

			numbytes = n * m * 3;
			image = (int *)malloc(numbytes);
			if (image == NULL)
			{
				printf("Memory allocation failed!\n");
				return NULL;
			}
			// Read and re-order as necessary
			for (i = m - 1; i >= 0; i--) for (j = 0; j<n; j++) // Important bug fix here!
			{
				image[(i*n + j) * 3 + 0] = getc(fd);
				image[(i*n + j) * 3 + 1] = getc(fd);
				image[(i*n + j) * 3 + 2] = getc(fd);
			}
		}
		else
		{
			printf("%s is not a PPM file!\n", filename);
			return NULL;
		}
	*height = m;
	*width = n;
	printf("read image\n");
	fclose(fd);
	return image;
}