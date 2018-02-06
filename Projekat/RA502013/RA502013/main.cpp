#include "opencv2/opencv.hpp"
#include <iostream>
#include <windows.h>
 
using namespace std;
using namespace cv;
 
int main(){

	//Ime trenutnog videa
	string vidName = "video2";

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
     
  return 0;
}