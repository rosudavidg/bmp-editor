// Rosu Gabriel-David, 311CD
#include <stdio.h>
#include "bmp_header.h"
#include <string.h>
#include <stdlib.h>

struct pixel
{
	unsigned char b, g, r;
};
typedef struct pixel Pixel;

Pixel*** alocare(Pixel ***a, int nl, int nc)
{
	int i, j;
	a = (Pixel ***)malloc(nl * sizeof(int **));
	for(i = 0; i < nl; i++)
		a[i] = (Pixel **)malloc(nc * sizeof(int *));
	for(i = 0; i < nl; i++)
		for(j = 0; j < nc; j++)
		a[i][j] = (Pixel *)malloc(sizeof(Pixel));
return a;
}

Pixel*** eliberare(Pixel ***a, int nl, int nc)
{
	int i, j;
	for(i = 0; i < nl; i++)
		for(j = 0; j < nc; j++)
			free((Pixel *)a[i][j]);
	for(i = 0; i < nl; i++)
		free((Pixel **)a[i]);
	free((Pixel ***)a);
return a;
}

void read_input_txt(char *arhive_name, char *bmp_name, int *number)
{
	int number2;
	FILE *in_txt;
	in_txt = fopen("input.txt", "rt");

	fgets(bmp_name, 100, in_txt);
	fscanf(in_txt, "%d", &number2);

 //get end of line 
	fgets(arhive_name, 100, in_txt);

	fgets(arhive_name, 100, in_txt);

	bmp_name[strlen(bmp_name) - 1] = '\0';
	arhive_name[strlen(arhive_name) - 1] = '\0';	

	fclose(in_txt);
	*number = number2;
}
void task1(	struct bmp_fileheader file_header, 
			struct bmp_infoheader info_header, 
			Pixel ***image, 
			char *bmp_name)

{
	Pixel ***image_task1;
	image_task1 = NULL;
	image_task1 = alocare(image_task1, info_header.height, info_header.width);

	int i, j;
	for(i = 0; i < info_header.height ; i++)
		for(j = 0; j < info_header.width; j++)
			{
				int x;
				x = image[i][j]->r +
					image[i][j]->g +
					image[i][j]->b;

				x = x / 3;

				image_task1[i][j]->r = x;
				image_task1[i][j]->g = x;
				image_task1[i][j]->b = x;
			}

//	Output
	char bmp_name_task1[100];
	strcpy(bmp_name_task1, bmp_name);
	bmp_name_task1[strlen(bmp_name_task1) -4] = '\0';
	strcat(bmp_name_task1, "_black_white.bmp");

	FILE *out_bmp;
	out_bmp = fopen(bmp_name_task1, "wb");

	fwrite(&file_header, sizeof(struct bmp_fileheader), 1, out_bmp);
	fwrite(&info_header, sizeof(struct bmp_infoheader), 1, out_bmp);

	unsigned char c = 0;
	for(i = 1; i <= 84; i++)
		fwrite(&c, sizeof(unsigned char), 1, out_bmp);

	for(i = 0; i < info_header.height ; i++)
		for(j = 0; j < info_header.width; j++)
		{
			fwrite(&image_task1[i][j]->b, sizeof(unsigned char), 1, out_bmp);
			fwrite(&image_task1[i][j]->g, sizeof(unsigned char), 1, out_bmp);
			fwrite(&image_task1[i][j]->r, sizeof(unsigned char), 1, out_bmp);
		}
	fclose(out_bmp);
	image_task1 = eliberare(image_task1, info_header.height, info_header.width);
}

Pixel*** inversare(Pixel ***image, int nl, int nc)
{
	Pixel ***a;
	a = NULL;
	a = alocare(a, nl, nc);
	int i, j;
	for(i = 0; i < nl; i++)
		for(j = 0; j < nc ;j++)
		{
			a[i][j]->r = image[nl - i - 1][j]->r;
			a[i][j]->g = image[nl - i - 1][j]->g;
			a[i][j]->b = image[nl - i - 1][j]->b;	
		}
return a;
}

void task2_f1(	struct bmp_fileheader file_header, 
				struct bmp_infoheader info_header, 
				Pixel ***image, 
				char *bmp_name)
{
	Pixel ***image_task2_aux, ***image_task2;

	int f1[4][4];
	f1[1][1] = -1;
	f1[1][2] = -1;
	f1[1][3] = -1;
	f1[2][1] = -1;
	f1[2][2] = 8;
	f1[2][3] = -1;
	f1[3][1] = -1;
	f1[3][2] = -1;
	f1[3][3] = -1;
	image_task2 = NULL;
	image_task2_aux = NULL;
	image_task2 = alocare(image_task2, info_header.height, info_header.width);
	image_task2_aux = alocare(image_task2_aux, info_header.height + 2, info_header.width + 2);

	int i, j;

	for(i = 0; i < info_header.height + 2; i++)
		for(j = 0; j < info_header.width + 2; j++)
		{
			image_task2_aux[i][j]->r = 0;
			image_task2_aux[i][j]->g = 0;
			image_task2_aux[i][j]->b = 0;
		}

	for(i = 0; i < info_header.height; i++)
		for(j = 0; j < info_header.width; j++)
		{
			image_task2_aux[i + 1][j + 1]->r = image[i][j]->r;
			image_task2_aux[i + 1][j + 1]->g = image[i][j]->g;
			image_task2_aux[i + 1][j + 1]->b = image[i][j]->b;	
		}

	for(i = 1; i < info_header.height + 1; i++)
		for(j = 1; j < info_header.width + 1; j++)
		{
			int x_r = 0, x_g = 0, x_b = 0;
			int k1, k2;

			for(k1 = 1; k1 <= 3; k1++)
				for(k2 = 1; k2 <= 3; k2++)
				{
					x_r += image_task2_aux[i - 2 + k1][j - 2 + k2]->r * f1[k1][k2];
					x_g += image_task2_aux[i - 2 + k1][j - 2 + k2]->g * f1[k1][k2];
					x_b += image_task2_aux[i - 2 + k1][j - 2 + k2]->b * f1[k1][k2];	
				}
				
			if(x_r < 0) x_r = 0;
			if(x_g < 0) x_g = 0;
			if(x_b < 0) x_b = 0;
			
			if(x_r > 255) x_r = 255;
			if(x_g > 255) x_g = 255;
			if(x_b > 255) x_b = 255;

			image_task2[i - 1][j - 1]->r = (int)x_r;
			image_task2[i - 1][j - 1]->g = (int)x_g;
			image_task2[i - 1][j - 1]->b = (int)x_b;	
		}

//	Output
	char bmp_name_task2[100];
	strcpy(bmp_name_task2, bmp_name);
	bmp_name_task2[strlen(bmp_name_task2) -4] = '\0';
	strcat(bmp_name_task2, "_f1.bmp");

	FILE *out_bmp;
	out_bmp = fopen(bmp_name_task2, "wb");

	fwrite(&file_header, sizeof(struct bmp_fileheader), 1, out_bmp);
	fwrite(&info_header, sizeof(struct bmp_infoheader), 1, out_bmp);

	unsigned char c = 0;
	for(i = 1; i <= 84; i++)
		fwrite(&c, sizeof(unsigned char), 1, out_bmp);

	for(i = 0; i < info_header.height ; i++)
		for(j = 0; j < info_header.width; j++)
		{
			fwrite(&image_task2[i][j]->b, sizeof(unsigned char), 1, out_bmp);
			fwrite(&image_task2[i][j]->g, sizeof(unsigned char), 1, out_bmp);
			fwrite(&image_task2[i][j]->r, sizeof(unsigned char), 1, out_bmp);
		}
	fclose(out_bmp);
	image_task2 = eliberare(image_task2, 
							info_header.height, 
							info_header.width);

	image_task2_aux = eliberare(image_task2_aux, 
								info_header.height + 2, 
								info_header.width  + 2);	
}

void task2_f2(	struct bmp_fileheader file_header, 
				struct bmp_infoheader info_header, 
				Pixel ***image, 
				char *bmp_name)
{
	Pixel ***image_task2_aux, ***image_task2;

	int f1[4][4];
	f1[1][1] = 0;
	f1[1][2] = 1;
	f1[1][3] = 0;
	f1[2][1] = 1;
	f1[2][2] = -4;
	f1[2][3] = 1;
	f1[3][1] = 0;
	f1[3][2] = 1;
	f1[3][3] = 0;
	image_task2 = NULL;
	image_task2_aux = NULL;
	image_task2 = alocare(image_task2, info_header.height, info_header.width);
	image_task2_aux = alocare(image_task2_aux, info_header.height + 2, info_header.width + 2);

	int i, j;
	for(i = 0; i < info_header.height + 2; i++)
		for(j = 0; j < info_header.width + 2; j++)
		{
			image_task2_aux[i][j]->r = 0;
			image_task2_aux[i][j]->g = 0;
			image_task2_aux[i][j]->b = 0;
		}

	for(i = 0; i < info_header.height; i++)
		for(j = 0; j < info_header.width; j++)
		{
			image_task2_aux[i + 1][j + 1]->r = image[i][j]->r;
			image_task2_aux[i + 1][j + 1]->g = image[i][j]->g;
			image_task2_aux[i + 1][j + 1]->b = image[i][j]->b;	
		}

	for(i = 1; i < info_header.height + 1; i++)
		for(j = 1; j < info_header.width + 1; j++)
		{
			int x_r = 0, x_g = 0, x_b = 0;
			int k1, k2;

			for(k1 = 1; k1 <= 3; k1++)
				for(k2 = 1; k2 <= 3; k2++)
				{
					x_r += image_task2_aux[i - 2 + k1][j - 2 + k2]->r * f1[k1][k2];
					x_g += image_task2_aux[i - 2 + k1][j - 2 + k2]->g * f1[k1][k2];
					x_b += image_task2_aux[i - 2 + k1][j - 2 + k2]->b * f1[k1][k2];	
				}
				
			if(x_r < 0) x_r = 0;
			if(x_g < 0) x_g = 0;
			if(x_b < 0) x_b = 0;
			
			if(x_r > 255) x_r = 255;
			if(x_g > 255) x_g = 255;
			if(x_b > 255) x_b = 255;

			image_task2[i - 1][j - 1]->r = (int)x_r;
			image_task2[i - 1][j - 1]->g = (int)x_g;
			image_task2[i - 1][j - 1]->b = (int)x_b;	
		}

//	Output
	char bmp_name_task2[100];
	strcpy(bmp_name_task2, bmp_name);
	bmp_name_task2[strlen(bmp_name_task2) -4] = '\0';
	strcat(bmp_name_task2, "_f2.bmp");

	FILE *out_bmp;
	out_bmp = fopen(bmp_name_task2, "wb");

	fwrite(&file_header, sizeof(struct bmp_fileheader), 1, out_bmp);
	fwrite(&info_header, sizeof(struct bmp_infoheader), 1, out_bmp);

	unsigned char c = 0;
	for(i = 1; i <= 84; i++)
		fwrite(&c, sizeof(unsigned char), 1, out_bmp);

	for(i = 0; i < info_header.height ; i++)
		for(j = 0; j < info_header.width; j++)
		{
			fwrite(&image_task2[i][j]->b, sizeof(unsigned char), 1, out_bmp);
			fwrite(&image_task2[i][j]->g, sizeof(unsigned char), 1, out_bmp);
			fwrite(&image_task2[i][j]->r, sizeof(unsigned char), 1, out_bmp);
		}
	fclose(out_bmp);
	image_task2 = eliberare(image_task2, 
							info_header.height, 
							info_header.width);

	image_task2_aux = eliberare(image_task2_aux, 
								info_header.height + 2, 
								info_header.width + 2);	
}

void task2_f3(	struct bmp_fileheader file_header, 
				struct bmp_infoheader info_header, 
				Pixel ***image, 
				char *bmp_name)
{
	Pixel ***image_task2_aux, ***image_task2;

	int f1[4][4];
	f1[1][1] = 1;
	f1[1][2] = 0;
	f1[1][3] = -1;
	f1[2][1] = 0;
	f1[2][2] = 0;
	f1[2][3] = 0;
	f1[3][1] = -1;
	f1[3][2] = 0;
	f1[3][3] = 1;

	image = inversare(image, info_header.height, info_header.width);
	image_task2= NULL;
	image_task2_aux = NULL;
	image_task2 = alocare(image_task2, info_header.height, info_header.width);
	image_task2_aux = alocare(image_task2_aux, info_header.height + 2, info_header.width + 2);

	int i, j;
	for(i = 0; i < info_header.height + 2; i++)
		for(j = 0; j < info_header.width + 2; j++)
		{
			image_task2_aux[i][j]->r = 0;
			image_task2_aux[i][j]->g = 0;
			image_task2_aux[i][j]->b = 0;
		}

	for(i = 0; i < info_header.height; i++)
		for(j = 0; j < info_header.width; j++)
		{
			image_task2_aux[i + 1][j + 1]->r = image[i][j]->r;
			image_task2_aux[i + 1][j + 1]->g = image[i][j]->g;
			image_task2_aux[i + 1][j + 1]->b = image[i][j]->b;	
		}

	for(i = 1; i < info_header.height + 1; i++)
		for(j = 1; j < info_header.width + 1; j++)
		{
			int x_r = 0, x_g = 0, x_b = 0;
			int k1, k2;

			for(k1 = 1; k1 <= 3; k1++)
				for(k2 = 1; k2 <= 3; k2++)
				{
					x_r += image_task2_aux[i - 2 + k1][j - 2 + k2]->r * f1[k1][k2];
					x_g += image_task2_aux[i - 2 + k1][j - 2 + k2]->g * f1[k1][k2];
					x_b += image_task2_aux[i - 2 + k1][j - 2 + k2]->b * f1[k1][k2];	
				}
				
			if(x_r < 0) x_r = 0;
			if(x_g < 0) x_g = 0;
			if(x_b < 0) x_b = 0;
			
			if(x_r > 255) x_r = 255;
			if(x_g > 255) x_g = 255;
			if(x_b > 255) x_b = 255;

			image_task2[i - 1][j - 1]->r = (int)x_r;
			image_task2[i - 1][j - 1]->g = (int)x_g;
			image_task2[i - 1][j - 1]->b = (int)x_b;	
		}

	image = inversare(image, info_header.height, info_header.width);
	image_task2 = inversare(image_task2, info_header.height, info_header.width);

//	Output
	char bmp_name_task2[100];
	strcpy(bmp_name_task2, bmp_name);
	bmp_name_task2[strlen(bmp_name_task2) -4] = '\0';
	strcat(bmp_name_task2, "_f3.bmp");

	FILE *out_bmp;
	out_bmp = fopen(bmp_name_task2, "wb");

	fwrite(&file_header, sizeof(struct bmp_fileheader), 1, out_bmp);
	fwrite(&info_header, sizeof(struct bmp_infoheader), 1, out_bmp);

	unsigned char c = 0;
	for(i = 1; i <= 84; i++)
		fwrite(&c, sizeof(unsigned char), 1, out_bmp);

	for(i = 0; i < info_header.height ; i++)
		for(j = 0; j < info_header.width; j++)
		{
			fwrite(&image_task2[i][j]->b, sizeof(unsigned char), 1, out_bmp);
			fwrite(&image_task2[i][j]->g, sizeof(unsigned char), 1, out_bmp);
			fwrite(&image_task2[i][j]->r, sizeof(unsigned char), 1, out_bmp);
		}

	fclose(out_bmp);
	image_task2 = eliberare(image_task2, 
							info_header.height, 
							info_header.width);

	image_task2_aux = eliberare(image_task2_aux, 
								info_header.height + 2, 
								info_header.width + 2);	
}

void task3(	struct bmp_fileheader file_header, 
				struct bmp_infoheader info_header, 
				Pixel ***image, 
				char *bmp_name,
				int treshold)
{
	int nl, nc;
	nl = info_header.height;
	nc = info_header.width;

	image = inversare(image, info_header.height, info_header.width);

	int i, j;
	
	int **checked;
	checked = (int **)malloc(nl * sizeof(int *));

	for(i = 0; i < nl; i++)
		checked[i] = (int *)malloc(nc * sizeof(int));
	
	for(i = 0; i < info_header.height; i++)
		for(j = 0; j < info_header.width; j++)
			checked[i][j] = 0;

	for(i = 0; i < info_header.height; i++)
		for(j = 0; j < info_header.width; j++)
			if(checked[i][j] == 0)
			{
				checked[i][j] = 1;
					int *vi, *vj;
					long int k;
					k = 1;
					vi = (int *)malloc(nc * nl * sizeof(int));
					vj = (int *)malloc(nc * nl * sizeof(int));
					
					int r, g, b;
					r = image[i][j]->r;
					g = image[i][j]->g;
					b = image[i][j]->b;
	
					vi[1] = i;
					vj[1] = j;
					int count = 1;
					while(count <= k)
					{
						//sus
						if(vi[count] > 0)
							if(checked[vi[count] - 1][vj[count]] == 0)
							{
								
								int r2, g2, b2;
								r2 = image[vi[count] -1][vj[count]]->r - r;
								g2 = image[vi[count] -1][vj[count]]->g - g;
								b2 = image[vi[count] -1][vj[count]]->b - b;

								if(r2 < 0)
									r2 = r2 * (-1);
								if(g2 < 0)
									g2 = g2 * (-1);
								if(b2 < 0)
									b2 = b2 * (-1);
								
								if(r2 + g2 + b2 <= treshold)
								{
									checked[vi[count] - 1][vj[count]] = 1;
									k++;
									vi[k] = vi[count] - 1;
									vj[k] = vj[count];

									image[vi[count] - 1][vj[count]]->r = r;	
									image[vi[count] - 1][vj[count]]->g = g;	
									image[vi[count] - 1][vj[count]]->b = b;	
								}	
			
							}
						//jos
						if(vi[count] < nl - 1)
						if(checked[vi[count] + 1][vj[count]] == 0)
							{
								
								int r2, g2, b2;
								r2 = image[vi[count] +1][vj[count]]->r - r;
								g2 = image[vi[count] +1][vj[count]]->g - g;
								b2 = image[vi[count] +1][vj[count]]->b - b;

								if(r2 < 0)
									r2 = r2 * (-1);
								if(g2 < 0)
									g2 = g2 * (-1);
								if(b2 < 0)
									b2 = b2 * (-1);
								
								if(r2 + g2 + b2 <= treshold)
								{
									checked[vi[count] + 1][vj[count]] = 1;
									k++;
								
									vi[k] = vi[count] + 1;
									vj[k] = vj[count];

									image[vi[count] + 1][vj[count]]->r = r;	
									image[vi[count] + 1][vj[count]]->g = g;	
									image[vi[count] + 1][vj[count]]->b = b;	
								}	
										
							}
						//stanga
						if(vj[count] > 0)
						if(checked[vi[count]][vj[count] - 1] == 0)
							{
								
								int r2, g2, b2;
								r2 = image[vi[count]][vj[count] - 1]->r - r;
								g2 = image[vi[count]][vj[count] - 1]->g - g;
								b2 = image[vi[count]][vj[count] - 1]->b - b;

								if(r2 < 0)
									r2 = r2 * (-1);
								if(g2 < 0)
									g2 = g2 * (-1);
								if(b2 < 0)
									b2 = b2 * (-1);
								
								if(r2 + g2 + b2 <= treshold)
								{
									checked[vi[count]][vj[count] - 1] = 1;
									k++;
								
									vi[k] = vi[count];
									vj[k] = vj[count] - 1;

									image[vi[count]][vj[count] - 1]->r = r;	
									image[vi[count]][vj[count] - 1]->g = g;	
									image[vi[count]][vj[count] - 1]->b = b;	
								}	
										
							}
						//dreapta
						if(vj[count] < nc - 1)
						if(checked[vi[count]][vj[count] + 1] == 0)
							{
								
								int r2, g2, b2;
								r2 = image[vi[count]][vj[count] + 1]->r - r;
								g2 = image[vi[count]][vj[count] + 1]->g - g;
								b2 = image[vi[count]][vj[count] + 1]->b - b;

								if(r2 < 0)
									r2 = r2 * (-1);
								if(g2 < 0)
									g2 = g2 * (-1);
								if(b2 < 0)
									b2 = b2 * (-1);
								
								if(r2 + g2 + b2 <= treshold)
								{
									checked[vi[count]][vj[count] + 1] = 1;
									k++;
							
									vi[k] = vi[count];
									vj[k] = vj[count] + 1;

									image[vi[count]][vj[count] + 1]->r = r;	
									image[vi[count]][vj[count] + 1]->g = g;	
									image[vi[count]][vj[count] + 1]->b = b;	
								}	
										
							}
						count++;
					}

					free(vj);
					free(vi);		
								
			}

	for(i = 0; i < nl; i++)
		free(checked[i]);
	free(checked);

//	Output compressed.BMP
	char bmp_name_task3[100];
	strcpy(bmp_name_task3, bmp_name);
	bmp_name_task3[strlen(bmp_name_task3) -4] = '\0';
	strcat(bmp_name_task3, "_compressed.bmp");

	FILE *out_bmp;
	out_bmp = fopen(bmp_name_task3, "wb");

image = inversare(image, info_header.height, info_header.width);

	fwrite(&file_header, sizeof(struct bmp_fileheader), 1, out_bmp);
	fwrite(&info_header, sizeof(struct bmp_infoheader), 1, out_bmp);

	unsigned char c = 0;
	for(i = 1; i <= 84; i++)
		fwrite(&c, sizeof(unsigned char), 1, out_bmp);

	for(i = 0; i < info_header.height ; i++)
		for(j = 0; j < info_header.width; j++)
		{
			fwrite(&image[i][j]->b, sizeof(unsigned char), 1, out_bmp);
			fwrite(&image[i][j]->g, sizeof(unsigned char), 1, out_bmp);
			fwrite(&image[i][j]->r, sizeof(unsigned char), 1, out_bmp);
		}
	fclose(out_bmp);

//OUTPUT COMPRESSED.BIN	
image = inversare(image, info_header.height, info_header.width);
	strcpy(bmp_name_task3, bmp_name);
	bmp_name_task3[strlen(bmp_name_task3) -4] = '\0';
	strcat(bmp_name_task3, "_compressed.bin");

	strcpy(bmp_name_task3 , "compressed.bin");

	out_bmp = fopen(bmp_name_task3, "wb");

	fwrite(&file_header, sizeof(struct bmp_fileheader), 1, out_bmp);
	fwrite(&info_header, sizeof(struct bmp_infoheader), 1, out_bmp);

	for(i = 1; i <= 84; i++)
		fwrite(&c, sizeof(unsigned char), 1, out_bmp);

	for(i = 0; i < info_header.height ; i++)
		for(j = 0; j < info_header.width; j++)
		{
			if(i == 0)
			{
				int i3, j3;
				i3 = i + 1;
				j3 = j + 1;
				fwrite(&i3, sizeof(unsigned short), 1, out_bmp);
				fwrite(&j3, sizeof(unsigned short), 1, out_bmp);
				
				fwrite(&image[i][j]->r, sizeof(unsigned char), 1, out_bmp);
				fwrite(&image[i][j]->g, sizeof(unsigned char), 1, out_bmp);
				fwrite(&image[i][j]->b, sizeof(unsigned char), 1, out_bmp);
			}
			else
			if(i == nl - 1)
			{
				int i3, j3;
				i3 = i + 1;
				j3 = j + 1;
				fwrite(&i3, sizeof(unsigned short), 1, out_bmp);
				fwrite(&j3, sizeof(unsigned short), 1, out_bmp);
				
				fwrite(&image[i][j]->r, sizeof(unsigned char), 1, out_bmp);
				fwrite(&image[i][j]->g, sizeof(unsigned char), 1, out_bmp);
				fwrite(&image[i][j]->b, sizeof(unsigned char), 1, out_bmp);
			}
			else
			if(j == 0)
			{
				int i3, j3;
				i3 = i + 1;
				j3 = j + 1;
				fwrite(&i3, sizeof(unsigned short), 1, out_bmp);
				fwrite(&j3, sizeof(unsigned short), 1, out_bmp);
				
				fwrite(&image[i][j]->r, sizeof(unsigned char), 1, out_bmp);
				fwrite(&image[i][j]->g, sizeof(unsigned char), 1, out_bmp);
				fwrite(&image[i][j]->b, sizeof(unsigned char), 1, out_bmp);
			}
			else
			if(j == nc - 1)
			{
				int i3, j3;
				i3 = i + 1;
				j3 = j + 1;
				fwrite(&i3, sizeof(unsigned short), 1, out_bmp);
				fwrite(&j3, sizeof(unsigned short), 1, out_bmp);
				
				fwrite(&image[i][j]->r, sizeof(unsigned char), 1, out_bmp);
				fwrite(&image[i][j]->g, sizeof(unsigned char), 1, out_bmp);
				fwrite(&image[i][j]->b, sizeof(unsigned char), 1, out_bmp);
			}
			else
			{
				int ok_afis;
				ok_afis = 0;
				
				if(image[i][j]->r != image[i+1][j]->r)
					ok_afis = 1;
				if(image[i][j]->g != image[i+1][j]->g)
					ok_afis = 1;
				if(image[i][j]->b != image[i+1][j]->b)
					ok_afis = 1;

				if(image[i][j]->r != image[i][j+1]->r)
					ok_afis = 1;
				if(image[i][j]->g != image[i][j+1]->g)
					ok_afis = 1;
				if(image[i][j]->b != image[i][j+1]->b)
					ok_afis = 1;

				if(image[i][j]->r != image[i][j-1]->r)
					ok_afis = 1;
				if(image[i][j]->g != image[i][j-1]->g)
					ok_afis = 1;
				if(image[i][j]->b != image[i][j-1]->b)
					ok_afis = 1;

				if(image[i][j]->r != image[i-1][j]->r)
					ok_afis = 1;
				if(image[i][j]->g != image[i-1][j]->g)
					ok_afis = 1;
				if(image[i][j]->b != image[i-1][j]->b)
					ok_afis = 1;

				if(ok_afis == 1)
				{
					int i3, j3;
					i3 = i + 1;
					j3 = j + 1;
					fwrite(&i3, sizeof(unsigned short), 1, out_bmp);
					fwrite(&j3, sizeof(unsigned short), 1, out_bmp);
				
					fwrite(&image[i][j]->r, sizeof(unsigned char), 1, out_bmp);
					fwrite(&image[i][j]->g, sizeof(unsigned char), 1, out_bmp);
					fwrite(&image[i][j]->b, sizeof(unsigned char), 1, out_bmp);
				}	
			}
		}

	fclose(out_bmp);
}

void task4(char *arhive_name)
{
	struct bmp_fileheader file_header;
	struct bmp_infoheader info_header;

	int i, j, nl, nc;

	FILE *task4_read_file;
	task4_read_file = fopen(arhive_name, "rb");

	fread(&file_header, sizeof(struct bmp_fileheader), 1, task4_read_file);
	fread(&info_header, sizeof(struct bmp_infoheader), 1, task4_read_file);
	fseek(task4_read_file, file_header.imageDataOffset, 0);

	nl = info_header.height;
	nc = info_header.width;

	Pixel ***image;
	image = NULL;
	image = alocare(image, info_header.height, info_header.width);
	
	int **checked;
	checked = (int **)malloc(nl * sizeof(int *));
	for(i = 0; i < nl; i++)
		checked[i] = (int *)malloc(nc * sizeof(int));
	
	for(i = 0; i < info_header.height; i++)
		for(j = 0; j < info_header.width; j++)
			checked[i][j] = 0;


	while(!feof(task4_read_file))
	{
		unsigned short i, j;
		unsigned char r, g, b;

		fread(&i, sizeof(unsigned short), 1, task4_read_file);
		fread(&j, sizeof(unsigned short), 1, task4_read_file);
		fread(&r, sizeof(unsigned char), 1, task4_read_file);
		fread(&g, sizeof(unsigned char), 1, task4_read_file);
		fread(&b, sizeof(unsigned char), 1, task4_read_file);
		//printf("%d %d %d %d %d\n", i ,j , r, g, b);
		checked[i - 1][j - 1] = 1;

		image[i - 1][j - 1]->r = r;
		image[i - 1][j - 1]->g = g;
		image[i - 1][j - 1]->b = b;

	}

	for(i = 0; i < info_header.height; i++)
		for(j = 0; j < info_header.width; j++)
			if(checked[i][j] == 1)
				if(checked[i + 1][j] == 0)
				{
					checked[i + 1][j] = 1;
					image[i + 1][j]->r = image[i][j]->r;
					image[i + 1][j]->g = image[i][j]->g;
					image[i + 1][j]->b = image[i][j]->b;	
				}


	image = inversare(image, info_header.height, info_header.width);

	char *out_char = "decompressed.bmp";

	FILE *out_bmp;
	out_bmp = fopen(out_char, "wb");

	fwrite(&file_header, sizeof(struct bmp_fileheader), 1, out_bmp);
	fwrite(&info_header, sizeof(struct bmp_infoheader), 1, out_bmp);

	unsigned char c = 0;
	for(i = 1; i <= 84; i++)
		fwrite(&c, sizeof(unsigned char), 1, out_bmp);

	for(i = 0; i < info_header.height ; i++)
		for(j = 0; j < info_header.width; j++)
		{
			fwrite(&image[i][j]->b, sizeof(unsigned char), 1, out_bmp);
			fwrite(&image[i][j]->g, sizeof(unsigned char), 1, out_bmp);
			fwrite(&image[i][j]->r, sizeof(unsigned char), 1, out_bmp);
		}
	fclose(out_bmp);

	image = eliberare(image, info_header.height, info_header.width);
	for(i = 0; i < nl; i++)
		free(checked[i]);
	free(checked);
	fclose(task4_read_file);

}

int main()
{

//	Read input.txt
	char arhive_name[100];
	char bmp_name[100];
	int threshold;
	read_input_txt(arhive_name, bmp_name, &threshold);

//	Read headers
	struct bmp_fileheader file_header;
	struct bmp_infoheader info_header;

	FILE *in_bmp;
	in_bmp = fopen(bmp_name, "rb");

	fread(&file_header, sizeof(struct bmp_fileheader), 1, in_bmp);
	fread(&info_header, sizeof(struct bmp_infoheader), 1, in_bmp);
	fseek(in_bmp, file_header.imageDataOffset, 0);

//	Read image
	Pixel ***image;
	image = NULL;
	image = alocare(image, info_header.height, info_header.width);

	int i, j;
	for(i = 0; i < info_header.height ; i++)
		for(j = 0; j < info_header.width; j++)
		{
			fread(&image[i][j]->b, sizeof(unsigned char), 1, in_bmp);
			fread(&image[i][j]->g, sizeof(unsigned char), 1, in_bmp);
			fread(&image[i][j]->r, sizeof(unsigned char), 1, in_bmp);
		}

//	Task 1
	task1(file_header, info_header, image, bmp_name);

//	Task 3
	task3(file_header, info_header, image, bmp_name, threshold);

//	Task 2
	char bmp_name_task1[100];
	strcpy(bmp_name_task1, bmp_name);
	bmp_name_task1[strlen(bmp_name_task1) -4] = '\0';
	strcat(bmp_name_task1, "_black_white.bmp");

	FILE *in_bmp_task2;
	in_bmp_task2 = fopen(bmp_name_task1, "rb");
	fread(&file_header, sizeof(struct bmp_fileheader), 1, in_bmp_task2);
	fread(&info_header, sizeof(struct bmp_infoheader), 1, in_bmp_task2);
	fseek(in_bmp_task2, file_header.imageDataOffset, 0);

	for(i = 0; i < info_header.height ; i++)
		for(j = 0; j < info_header.width; j++)
		{
			fread(&image[i][j]->b, sizeof(unsigned char), 1, in_bmp_task2);
			fread(&image[i][j]->g, sizeof(unsigned char), 1, in_bmp_task2);
			fread(&image[i][j]->r, sizeof(unsigned char), 1, in_bmp_task2);
		}

	task2_f1(file_header, info_header, image, bmp_name);
	task2_f2(file_header, info_header, image, bmp_name);
	task2_f3(file_header, info_header, image, bmp_name);


	

//	Free memory and close files
	image = eliberare(image, info_header.height, info_header.width);
	fclose(in_bmp);
	fclose(in_bmp_task2);

//	Task 4
	task4(arhive_name);

	return 0;
}