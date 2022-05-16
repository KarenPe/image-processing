#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

int main() {
	int size = 150;
	int rows = 2;
	int cols = 3;

	Scalar colors {0, 127, 255};
	Mat image(size * rows, size * cols, CV_8UC1, Scalar(0));

	for (int stage = 0; stage < 6; stage++) {
		rectangle(image, Point(stage % 3 * size, stage / 3 * size), Point(stage * size + size - 1, stage / 3 * size + size - 1), colors[(stage / 3 + stage) % 3], -1);
		circle(image, Point(stage % 3 * size + size / 2, stage / 3 * size + size / 2), 35, colors[((stage / 3)*-1 + stage + 1) % 3], -1);
	}
	imwrite("image.png", image);

	Mat_<int> firstFilter(2, 2);
	firstFilter << 1, 0,
								 0, -1;
	Mat firstFilteredImage;
	filter2D(image, firstFilteredImage, -1, firstFilter);
	imwrite("firstFilteredImage.png", firstFilteredImage);

	Mat_<int> secondFilter(2, 2);
	secondFilter << 0, 1,
								 -1, 0;
	Mat secondFilteredImage;
	filter2D(image, secondFilteredImage, -1, secondFilter);
	imwrite("secondFilteredImage.png", secondFilteredImage);

	Mat meanResult = image.clone();

	for (int row = 0; row < meanResult.rows; row++) {
		for (int col = 0; col < meanResult.cols; col++) {
			meanResult.at<uint8_t>(row, col) = sqrt(firstFilteredImage.at<uint8_t>(row, col) * firstFilteredImage.at<uint8_t>(row, col)
			    + secondFilteredImage.at<uint8_t>(row, col) * secondFilteredImage.at<uint8_t>(row, col));
		}
	}
	imwrite("meanResult.png", meanResult);
	waitKey(0);
}