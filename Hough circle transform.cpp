
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#ifdef _DEBUG
#pragma comment(lib, "opencv_world4100d")
#else
#pragma comment(lib, "opencv_world4100")
#endif

using namespace cv;
using namespace std;

int main() {
    string imagePath = "C:/Users/sonyrainy/Desktop/coins0.jpg";
    Mat src = imread(imagePath, IMREAD_COLOR);
    if (src.empty()) {
        printf(" Error opening image\n");
        return EXIT_FAILURE;
    }

    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    medianBlur(gray, gray, 5);


    vector<Vec3f> circles;
    HoughCircles(
        gray, circles, HOUGH_GRADIENT,1,
        40,
        100, 40, 
        35, 80
    );

    int coin_count = circles.size();
    printf("%d개 동전 발견\n", coin_count);

    for (size_t i = 0; i < circles.size(); i++) {

        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]); 

        // circle center
        circle(src, center, 1, Scalar(0, 100, 100), 3, LINE_AA);

        // circle outline
        int radius = c[2];
        circle(src, center, radius, Scalar(255, 0, 255), 3, LINE_AA);
    }

    imshow("detected circles", src);
    waitKey();

    return 0;
}
