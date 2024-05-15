#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

string revealText(const Mat& image) {
    string text;
    bool endDetected = false;

    for (int row = 0; row < image.rows && !endDetected; ++row) {
        for (int col = 0; col < image.cols && !endDetected; ++col) {
            Vec3b pixel = image.at<Vec3b>(row, col);
            for (int color = 0; color < 3 && !endDetected; ++color) {
                char c = pixel[color];
                if (c == '\0') {
                    endDetected = true; // Detecta o fim do texto
                    break;
                }
                text += c;
            }
        }
    }

    return text;
}

int main() {
    const string imagePath = "Imagem_com_texto.png";
    Mat loadedImage = imread(imagePath, IMREAD_COLOR);
    if (loadedImage.empty()) {
        cerr << "Erro: Não foi possível carregar a imagem." << endl;
        return -1;
    }

    string recoveredText = revealText(loadedImage);
    cout << "Texto revelado: " << recoveredText << endl;

    return 0;
}

