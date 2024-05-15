#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;


void hideText(Mat& image, const string& text) {
    // Adiciona um delimitador nulo ao final do texto para sinalizar o fim do mesmo, sem o delimitador o texto pode ter erro ao imprimir
    string fullText = text + char(0); 
    int maxCols = image.cols * 3; 
    int maxCharsPerRow = maxCols; 
    int numRows = (fullText.length() + maxCharsPerRow - 1) / maxCharsPerRow;

    if (numRows >= image.rows) {
        cerr << "Erro: Imagem não tem linhas suficientes para armazenar o texto." << endl;
        return;
    }

    for (int i = 0; i < fullText.size(); ++i) {
        int row = i / maxCharsPerRow;
        int col = (i % maxCharsPerRow) / 3;
        int channel = (i % maxCharsPerRow) % 3;

        Vec3b& pixel = image.at<Vec3b>(row, col);
        pixel[channel] = fullText[i]; 
    }
    cout << "Texto adicionado com sucesso! A nova imagem foi gerada e salva na pasta principal do projeto." << endl;
}

string revealText(const Mat& image) {
    string text;
    bool endDetected = false;

    for (int row = 0; row < image.rows && !endDetected; ++row) {
        for (int col = 0; col < image.cols && !endDetected; ++col) {
            Vec3b pixel = image.at<Vec3b>(row, col);
            for (int color = 0; color < 3 && !endDetected; ++color) {
                char c = pixel[color];
                if (c == '\0') {
                    endDetected = true;
                    break;
                }
                text += c;
            }
        }
    }

    return text;
}


int main() {
    Mat image = imread("image-1.png", IMREAD_COLOR); 
    if (image.empty()) {
        cerr << "Erro: Não foi possível carregar a imagem." << endl;
        return -1;
    }

    string secretText = "Olá! Este é o meu primeiro código aprendendo esteganografia.\n"
    "Esteganografia me lembra O Código Da Vinci, por isso escolhi a imagem da Monalisa, do artista Fernando Botero.";
    hideText(image, secretText);

    if (!imwrite("Imagem_com_texto.png", image, vector<int>{IMWRITE_PNG_COMPRESSION, 0})) {
        cerr << "Erro ao salvar a imagem com texto escondido." << endl;
        return -1;
    }

    return 0; 
}
