#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <conio.h>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{



	/*VideoCapture cap(0); //Tümleþik webcam açýlýþ iþlemi

	if ( !cap.isOpened() )  // Kamera yoksa durumu
	{
	cout << "PC'ye Bagli Kamera Yok" << endl;
	return -1;
	}

	namedWindow("Control", CV_WINDOW_AUTOSIZE); */

	//HSV deðerleri için baþlangýç deðerlerinin atanmasý

	// Otomatik Olarak esil tonlarýný ayýrmak için þu deðerlerle iþlemler yapýlmýþtýr

	/*
	Yeþil ve Tonlarýný Algýlama Ýçin En Düþük
	RGB -> #4DFF4D
	HSV -> 120 100 100

	Yeþil ve Tonlarýný Algýlama Ýçin En Yüksek
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
		cout << "Video akýsýndan frame alinamadi" << endl;
		break;
		}*/

		Mat imgHSV, imgOriginal;

		imgOriginal = imread("C:/Temp_Data/satiliktarlapunjab.jpg");

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); // RGB'den HSV formuna dönüsüm

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Thresholded uygulama iþlemi


		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));


		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		imshow("Thresholded Uygulanan Frame", imgThresholded);
		imshow("Orjinal Frame", imgOriginal);



		//Pixel Oran Ýþlemleri

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
			cout << "Cikis Yapýldý" << endl;
			break;
		}
	}

	getch();
	return 0;

}