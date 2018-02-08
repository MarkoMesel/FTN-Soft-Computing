#include "opencv2/opencv.hpp"
#include <iostream>
#include <windows.h>
 
using namespace std;
using namespace cv;

int H_MIN = 0;
int H_MAX = 256;
int S_MIN = 0;
int S_MAX = 60;
int V_MIN = 0;
int V_MAX = 60;
 
int main(){

	//Ime trenutnog videa
	string vidName = "video1";

	// Create a VideoCapture object and open the input file
	// If the input is the web camera, pass 0 instead of the video file name
	VideoCapture cap("Materijali/" + vidName + ".mp4");
    
	// Check if camera opened successfully
	if(!cap.isOpened()){
		cout << "Error opening video stream or file" << endl;
		return -1;
	}

	//Brojac pomocu kojeg ce se generisati drugacija imena fajlova, a samim tim i drugaciji frejmovi
	int count = -1;

	//Folder u koji ce se cuvati frejmovi
	string outputDir = "Frejmovi_" + vidName + "\\";
     
	while(1){

		Mat frame;

		// Capture frame-by-frame
		cap >> frame;

		// If the frame is empty, break immediately
		if (frame.empty())
			break;
		
		//Definisi prostor koji te zanima
		cv::Rect cropArea(167, 113, 364, 349);

		//Crop-uj frame
		frame = frame(cropArea);

		//Definisi prostor koji te zanima
		cv::Rect cropArea2(71, 35, 156, 314);

		//Crop-uj frame
		frame = frame(cropArea2);

		//Konvertuj boju u HSV radi lakseg pracenja boja i pokreta
		cvtColor(frame,frame,COLOR_BGR2HSV);

		//Filtriraj sliku tako da bude prikazana boja koja te interesuje
		inRange(frame, Scalar(H_MIN,S_MIN,V_MIN), Scalar(H_MAX,S_MAX,V_MAX), frame);

		//Smanji ili potpuno eliminisi sum
		//Mat erodeElement = getStructuringElement(MORPH_RECT,Size(1,1));
		//erode(frame,frame,erodeElement);


		//Povecaj piksele od interesa
		//Mat dilateElement = getStructuringElement(MORPH_RECT,Size(5,5));
		//dilate(frame,frame,erodeElement);
		//dilate(frame,frame,erodeElement);
		//dilate(frame,frame,erodeElement);
		//dilate(frame,frame,erodeElement);


		// Display the resulting frame
		imshow( "Frame", frame );

		//Generisi ime trenutnog frejma
		string name = "frame " + std::to_string(static_cast<long long>(count)) + ".png";


		//Ako folder "Frejmovi" ne postoji, sacuvaj u njega trenutni frame
		if (CreateDirectory(outputDir.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
		{
			imwrite(outputDir + name, frame);
		}


		//Inkrementiraj brojac
		count++;

		// Press  ESC on keyboard to exit
		char c=(char)waitKey(25);
		if(c==27)
			break;
	}
  
	// When everything done, release the video capture object
	cap.release();
 
	// Closes all the frames
	destroyAllWindows();
     
			/*
		for(int y=0;y<frame.rows;y++)
		{
			for(int x=0;x<frame.cols;x++)
			{
				// get pixel
				Vec3b colorf0 = comparableFrame.at<Vec3b>(Point(x,y));
				Vec3b colorf = frame.at<Vec3b>(Point(x,y));
				// ... do something to the color ....
				
				if(colorf0 != colorf)
				{
					colorf = Vec3b(0,0,0);
				}
				

				// set pixel
				frame.at<Vec3b>(Point(x,y)) = colorf;
			}
		}
		*/


	return 0;
}