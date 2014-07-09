#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <conio.h>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{



	/*VideoCapture cap(0); //T�mle�ik webcam a��l�� i�lemi

	if ( !cap.isOpened() )  // Kamera yoksa durumu
	{
	cout << "PC'ye Bagli Kamera Yok" << endl;
	return -1;
	}

	namedWindow("Control", CV_WINDOW_AUTOSIZE); */

	//HSV de�erleri i�in ba�lang�� de�erlerinin atanmas�

	// Otomatik Olarak esil tonlar�n� ay�rmak i�in �u de�erlerle i�lemler yap�lm��t�r

	/*
	Ye�il ve Tonlar�n� Alg�lama ��in En D���k
	RGB -> #4DFF4D
	HSV -> 120 100 100

	Ye�il ve Tonlar�n� Alg�lama ��in En Y�ksek
	RGB -> 300661A
	HSV -> 135 100 40

	*/
	int iLowH = 40;
	int iHighH = 80;

	int iLowS = 50;
	int iHighS = 255;

	int iLowV = 0;
	int iHighV = 255;



	while (true)
	{
		/* Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
		cout << "Video ak�s�ndan frame alinamadi" << endl;
		break;
		}*/

		Mat imgHSV, imgOriginal;

		imgOriginal = imread("C:/Temp_Data/satiliktarlapunjab.jpg");

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); // RGB'den HSV formuna d�n�s�m

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Thresholded uygulama i�lemi


		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));


		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		imshow("Thresholded Uygulanan Frame", imgThresholded);
		imshow("Orjinal Frame", imgOriginal);



		//Pixel Oran ��lemleri

		double ToplamPixel = imgThresholded.rows * imgThresholded.cols;
		double Beyaz = countNonZero(imgThresholded);
		double Siyah = ToplamPixel - Beyaz;

		float BeyazToplamPixel = Beyaz / ToplamPixel;
		float SiyahToplamPixel = Siyah / ToplamPixel;

		system("CLS");
		cout << "Beyaz / Toplam Pixel Orani :" << BeyazToplamPixel << endl;
		cout << "Siyah / Toplam Pixel Orani :" << SiyahToplamPixel << endl;
		cout << "Toplam Pixel Orani :" << BeyazToplamPixel + SiyahToplamPixel << endl;

		void SERVER();


		if (waitKey(30) == 27)
		{
			cout << "Cikis Yap�ld�" << endl;
			break;
		}
	}

	getch();
	return 0;

}