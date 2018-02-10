#include "opencv2/opencv.hpp"
#include <iostream>
#include <windows.h>
#include <cmath>
 
using namespace std;
using namespace cv;

int H_MIN = 0;
int H_MAX = 256;
int S_MIN = 0;
int S_MAX = 50;
int V_MIN = 0;
int V_MAX = 100;

int peopleCountNew = 0;
int peopleCountOld = 0;

int detectedSum = 0;
 
int main(){

	//Ime trenutnog videa
	string vidName = "video1";

	//VideoCapture objekat koji ce sadrzati video
	VideoCapture cap("Materijali/" + vidName + ".mp4");
    
	//Proveri da li se video uspesno load-ovao
	if(!cap.isOpened()){
		cout << "Error opening video stream or file" << endl;
		return -1;
	}

	//Brojac pomocu kojeg ce se generisati drugacija imena fajlova, a samim tim i drugaciji frejmovi
	int count = -1;

	//Folder u koji ce se cuvati frejmovi
	//string outputDir = "Frejmovi_" + vidName + "\\";
	
	while(1){

		//Mat promenljiva koja ce sadrzati trenutni frejm iz videa
		Mat frame;

		//U svakoj sledecoj iteraciji stavi sledeci frame iz "cap" u "frame"
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

		//Ponovo crop-uj frame
		frame = frame(cropArea2);

		//Definisi prostor koji te zanima
		cv::Rect cropArea3(0, 0, 132, 217);

		//Ponovo crop-uj frame
		frame = frame(cropArea3);

		//Konvertuj boju u HSV radi lakseg pracenja boja i pokreta
		cvtColor(frame,frame,COLOR_BGR2HSV);

		//Filtriraj sliku tako da bude prikazana boja koja te interesuje
		inRange(frame, Scalar(H_MIN,S_MIN,V_MIN), Scalar(H_MAX,S_MAX,V_MAX), frame);

		//Smanji ili potpuno eliminisi sum
		Mat erodeElement = getStructuringElement(MORPH_RECT,Size(3,3));
		erode(frame,frame,erodeElement);

		//Povecaj piksele od interesa
		Mat dilateElement = getStructuringElement(MORPH_RECT,Size(10,10));
		dilate(frame,frame,erodeElement);
		dilate(frame,frame,dilateElement);

		//Maska pomocu koje cemo moci da izbrojimo kolicinu piksela u trenutnom frame-u koji su obojeni belom bojom
		cv::Mat mask;
		cv::inRange(frame, 255, 255, mask);

		//Prebrojavanje svih piksela bele boje unutar trenutnog frame-a.
		double pNum = cv::countNonZero(mask);

		if(pNum != 0)
		{
			if(floor(pNum/144) == 0)
			{
				peopleCountNew = 1;
				cout << peopleCountNew << '\n';
			}
			else
			{
				peopleCountNew = int(pNum/144);
				cout << int(pNum/144) << '\n';
			}
			imshow( "Frame", frame );
		} else
		{
			peopleCountNew = 0;
		}

		if(peopleCountNew > peopleCountOld)
		{
			detectedSum += peopleCountNew;
		}
		else if (peopleCountNew < peopleCountOld)
		{
			if ((peopleCountOld - peopleCountNew) == 1)
			{
				peopleCountNew = peopleCountOld;
			}
		}

		//cout<<"Ukupan broj Ljudi = "<< detectedSum;

		peopleCountOld = peopleCountNew;


		//Generisi ime trenutnog frejma
		string name = "frame " + std::to_string(static_cast<long long>(count)) + ".png";

		/*
		//Ako folder "Frejmovi" ne postoji, sacuvaj u njega trenutni frame
		if (CreateDirectory(outputDir.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
		{
			imwrite(outputDir + name, frame);
		}
		*/

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

	cout<<"Ukupan broj Ljudi = "<< detectedSum;

	cin.get();

	destroyAllWindows();

	return 0;
}