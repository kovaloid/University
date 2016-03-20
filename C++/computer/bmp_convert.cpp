#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

void main()
{	 
	 BITMAPFILEHEADER bfh;
     BITMAPINFOHEADER bih;
     int Width, Height;
     RGBQUAD Palette[256];
     BYTE *inBuf;
     RGBTRIPLE *outBuf;
     HANDLE hIn, hOut;
     DWORD RW;
     DWORD OffBits;
     int i, j;

     hIn = CreateFile (L"input.bmp", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
     if (hIn == INVALID_HANDLE_VALUE) return;

     hOut = CreateFile (L"output.bmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
     if (hOut == INVALID_HANDLE_VALUE)
     {
         CloseHandle (hIn);
         return;
     }

     // Прочтем данные
     ReadFile (hIn, &bfh, sizeof(bfh), &RW, NULL);
     ReadFile (hIn, &bih, sizeof(bih), &RW, NULL);
     ReadFile (hIn, Palette, 256 * sizeof(RGBQUAD), &RW, NULL);

     // Установим указатель на начало растра
     SetFilePointer (hIn, bfh.bfOffBits, NULL, FILE_BEGIN);
     Width = bih.biWidth;
     Height = bih.biHeight;
     OffBits = bfh.bfOffBits;

     // Выделим память
     inBuf = new BYTE [Width];
     outBuf = new RGBTRIPLE [Width];

     // Заполним заголовки
     bfh.bfOffBits = sizeof (bfh) + sizeof (bih);                              
     bih.biBitCount = 24;
     bfh.bfSize = bfh.bfOffBits + 4 * Width * Height + Height * (Width % 4);  // Размер файла

     // А остальное не меняется
     // Запишем заголовки
     WriteFile (hOut, &bfh, sizeof(bfh), &RW, NULL);
     WriteFile (hOut, &bih, sizeof(bih), &RW, NULL);

     // Начнем преобразовывать
     for (i = 0; i < Height; i++)
     {
         ReadFile (hIn, inBuf, Width, &RW, NULL);
         for (j = 0; j < Width; j++)
         {
             outBuf[j].rgbtRed = Palette[inBuf[j]].rgbRed;
             outBuf[j].rgbtGreen = Palette[inBuf[j]].rgbGreen;
             outBuf[j].rgbtBlue = Palette[inBuf[j]].rgbBlue;
         }
         WriteFile (hOut, outBuf, sizeof(RGBTRIPLE) * Width, &RW, NULL);

         // Пишем мусор для выравнивания
         WriteFile (hOut, Palette, Width % 4, &RW, NULL);
         SetFilePointer (hIn, (3 * Width) % 4, NULL, FILE_CURRENT);
     }

     delete inBuf;
     delete outBuf;
     CloseHandle (hIn);
     CloseHandle (hOut);

	 cout << "Updating has come to the end successfully!"<<endl;
	 system("pause");
}