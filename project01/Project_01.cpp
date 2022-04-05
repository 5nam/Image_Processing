#include <stdio.h>
#include <math.h>

int main() {
	int i, j;
	unsigned char OrgImg_Coin[256][256]; // # 과제 1
	unsigned char OrgImg_G[256][256]; // 그레이 스케일 과제
	unsigned char OrgImg_Color_R[256][256]; // 컬러 과제
	unsigned char OrgImg_Color_G[256][256]; // 컬러 과제
	unsigned char OrgImg_Color_B[256][256]; // 컬러 과제
	
	// 디스크에서 영상 데이터 읽기
	errno_t err;
	FILE *infile_s = NULL;
	err = fopen_s(&infile_s, "Coin.raw", "rb");
	if (err != 0) {
		printf("File open error!");
		return -1;
	}
	/*
	fopen vs fopen_s
	fopen_s(포인터의 포인터, 파일, ..) 이므로 함수의 첫번째 매개변수가 주소값이 되어야 함.
	*/

	fread(OrgImg_Coin, sizeof(unsigned char), 256 * 256, infile_s);
	fclose(infile_s);

	// 역상 계산을 위한 영상처리
	for (i = 0; i < 256; i++) {
		for (j = 0; j < 256; j++) {
			// y = 255 - x
			OrgImg_Coin[i][j] = 255 - OrgImg_Coin[i][j];
		}
	}

	
	int radius;
	// 원 그리기 : 그레이 스케일
	for (i = 0; i < 256; i++) {
		for (j = 0; j < 256; j++) {
			radius = (int) sqrt(pow((127 - i), 2) + pow((127 - j), 2)); // 반지름 구하는 공식
			
			if (radius < 40) {
				OrgImg_G[i][j] = 0; // 명도값 설정
			}
			else if (40 <= radius && radius < 80) {
				OrgImg_G[i][j] = 64;
			}
			else if (80 <= radius && radius < 120) {
				OrgImg_G[i][j] = 128;
			}
			else if (120 <= radius && radius < 255) {
				if (i < 32 && j < 32) {
					OrgImg_G[i][j] = 0;
				}
				else {
					OrgImg_G[i][j] = 255;
				}
			}
			
		}
	}
	// 원 그리기 : 컬러
	
	for (i = 0; i < 256; i++) {
		for (j = 0; j < 256; j++) {
			radius = (int)sqrt(pow((127 - i), 2) + pow((127 - j), 2)); // 반지름 구하는 공식

			if (radius < 40) {
				OrgImg_Color_R[i][j] = 0;
				OrgImg_Color_G[i][j] = 0;
				OrgImg_Color_B[i][j] = 255;
			}
			else if (40 <= radius && radius < 80) {
				OrgImg_Color_R[i][j] = 0;
				OrgImg_Color_G[i][j] = 255;
				OrgImg_Color_B[i][j] = 0;
			}
			else if (80 <= radius && radius < 120) {
				OrgImg_Color_R[i][j] = 255;
				OrgImg_Color_G[i][j] = 0;
				OrgImg_Color_B[i][j] = 0;
			}
			else if (120 <= radius && radius < 255) {
				if (i < 32 && j < 32) {
					OrgImg_Color_R[i][j] = 0;
					OrgImg_Color_G[i][j] = 0;
					OrgImg_Color_B[i][j] = 0;
				}
				else {
					OrgImg_Color_R[i][j] = 255;
					OrgImg_Color_G[i][j] = 255;
					OrgImg_Color_B[i][j] = 255;
				}
			}

		}
	}

	// 하드디스크에 영상데이터 쓰기
	errno_t err_o;
	errno_t err_g;
	errno_t err_c;
	//errno_t err_c_g;
	//errno_t err_c_b;
	FILE *outfile_s = NULL;
	FILE *outfile_g = NULL;
	FILE *outfile_c = NULL;
	err_o = fopen_s(&outfile_s, "coin_inv.raw", "wb");
	err_g = fopen_s(&outfile_g, "sample gray image.raw", "wb");
	err_c = fopen_s(&outfile_c, "sample color image.raw", "wb");
	fwrite(OrgImg_Coin, sizeof(unsigned char), 256 * 256, outfile_s);
	fwrite(OrgImg_G, sizeof(unsigned char), 256 * 256, outfile_g);

	// 컬러
	fwrite(OrgImg_Color_R, sizeof(unsigned char), 256 * 256, outfile_c);
	fwrite(OrgImg_Color_G, sizeof(unsigned char), 256 * 256, outfile_c);
	fwrite(OrgImg_Color_B, sizeof(unsigned char), 256 * 256, outfile_c);
	

	fclose(outfile_s);
	fclose(outfile_g);
	fclose(outfile_c);
}

// input image - IP - output image
