#include "fopencv.h"



fopencv::fopencv() {

}

fopencv::~fopencv() {

}



cv::Vec3b fopencv::getPixel(cv::Mat img, int x, int y) {
    return img.at<cv::Vec3b>(y, x);
}

cv::Mat fopencv::CreateMat(const std::string& imagePath) {
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);

    if (image.empty()) {
        std::cerr << "Error: Failed to read image from " << imagePath << std::endl;
        return cv::Mat();
    }

    return image;
}
cv::Mat fopencv::CreateGrayMat(const std::string& imagePath) {
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cerr << "Error: Failed to read image from " << imagePath << std::endl;
        return cv::Mat();
    }
    return image;
}



void fopencv::showImg(std::string path) {
    cv::Mat img = CreateMat(path);
    imshow("img", img);
    int x = (1920 - img.cols) / 5.4;
    int y = (1080 - img.rows) / 6;
    cv::moveWindow("img", x, y);
    cv::waitKey(0);
}

cv::Mat fopencv::DetectContours(cv::Mat img) {
    cv::Mat imgBlur, imgCanny, imgDil, imgErode, imgRange;
    cv::Scalar lower(50, 0, 100);
    cv::Scalar upper(100, 255, 150);
    inRange(img, lower, upper, imgRange);
    GaussianBlur(imgRange, imgBlur, cv::Size(0, 0), 1, 0);
    Canny(imgBlur, imgCanny, 65, 75);
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    dilate(imgCanny, imgDil, kernel);
    return imgDil;
}

void fopencv::getContours(std::string pathImg) { //à revoir
    cv::Mat img = CreateMat(pathImg);
    cv::Mat imgDil = DetectContours(img);
    std::vector<std::vector<cv::Point>>contours;
    std::vector<cv::Vec4i>hierarchy;
    findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    drawContours(img, contours, -1, cv::Scalar(255, 0, 255), 2);
    imshow("img", img);
}

void fopencv::showImgtest(std::string path) {
    int hmin = 0, smin = 0, vmin = 0;
    int hmax = 255, smax = 255, vmax = 255;
    cv::Mat img = cv::imread(path, cv::IMREAD_REDUCED_COLOR_2);

    cv::Mat imgHSV, mask;
    cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
    cv::namedWindow("Track", (640, 200));
    cv::createTrackbar("Hue min", "Track", &hmin, 255);
    cv::createTrackbar("Hue max", "Track", &hmax, 255);
    cv::createTrackbar("sat min", "Track", &smin, 255);
    cv::createTrackbar("sat max", "Track", &smax, 255);
    cv::createTrackbar("Val min", "Track", &vmin, 255);
    cv::createTrackbar("Val max", "Track", &vmax, 255);

    while (true) {
        cv::Scalar lower(0, 0, 213);
        cv::Scalar upper(255, 179, 255);
        inRange(imgHSV, lower, upper, mask);
        imshow("Image", img);
        cv::moveWindow("Image", 0, 0);
        imshow("imagemod1", imgHSV);
        cv::moveWindow("imagemod1", 0, 400);
        imshow("imagemod2", mask);
        cv::moveWindow("imagemod2", 700, 0);
        cv::moveWindow("Track", 700, 400);
        cv::waitKey(1);
    }
}

cv::Mat fopencv::extractZone(const cv::Mat& image, Zone Z) {
    int width = Z.C2.x - Z.C1.x;
    int height = Z.C2.y - Z.C1.y;
    cv::Rect roiRect(Z.C1.x, Z.C1.y, width, height);
    cv::Mat roi = image(roiRect).clone();
    return roi;
}

bool fopencv::cvmtfTemplate(const Template& templateImg, const Template& background, Coords& Cresult) {
    Template resultSearch = returnOneMatchTemplate(templateImg, background);
    if (resultSearch.score >= precision) {
        Cresult = resultSearch.C;
        std::cout << "X: " << resultSearch.C.x;
        std::cout << " Y: " << resultSearch.C.y;
        std::cout << "found maxVal: " << resultSearch.score << " " << templateImg.id << std::endl;
        return true;
    }
    else {
        std::cout << "Not found maxVal: " << resultSearch.score << " " << templateImg.id << std::endl;
        return false;
    }
}


Template fopencv::returnOneMatchTemplate(const Template& templateImg, const Template& background) {
    double maxVal;
    cv::Point maxLoc;
    cv::Mat resultMat;
    cv::matchTemplate(background.mat, templateImg.mat, resultMat, cv::TM_CCOEFF_NORMED);
    cv::minMaxLoc(resultMat, NULL, &maxVal, NULL, &maxLoc);
    Template resultTemp;
    cv::Point topLeft = maxLoc;
    cv::Point bottomRight(topLeft.x + templateImg.mat.cols, topLeft.y + templateImg.mat.rows);
    resultTemp.C.x = (topLeft.x + bottomRight.x) / 2;
    resultTemp.C.y = (topLeft.y + bottomRight.y) / 2;
    resultTemp.score = maxVal;
    resultTemp.id = templateImg.id;
    resultTemp.mat = templateImg.mat;
    return resultTemp;
}


std::vector<Template> fopencv::returnMultipleMatchTemplate(const Template& templateImg, const Template& background) {
    cv::Mat matresult;
    std::vector<Template> resultMultTemp;
    float matchVal = 0;
    Template resultTemp;
    bool duplicate;
    int x, y;
    cv::matchTemplate(background.mat, templateImg.mat, matresult, cv::TM_CCOEFF_NORMED);
    for (y = 0; y < matresult.rows; ++y) {
        for (x = 0; x < matresult.cols; ++x) {
            duplicate = false;
            matchVal = matresult.at<float>(y, x);
            if (matchVal >= precision) {
                Coords temp(x, y);
                cvmtfHighestScoreZone(templateImg.mat, background.mat, matchVal, temp);
                cv::Point topLeft(temp.x, temp.y);
                cv::Point bottomRight(topLeft.x + templateImg.mat.cols, topLeft.y + templateImg.mat.rows);
                resultTemp.C.x = (topLeft.x + bottomRight.x) / 2;
                resultTemp.C.y = (topLeft.y + bottomRight.y) / 2;
                resultTemp.id = templateImg.id;
                resultTemp.score = matchVal;
                resultTemp.mat = templateImg.mat;
                for (int i = 0; i < resultMultTemp.size(); ++i) {
                    if (abs(resultMultTemp.at(i).C.x - resultTemp.C.x) <= templateImg.mat.cols && abs(resultMultTemp.at(i).C.y - resultTemp.C.y) <= templateImg.mat.rows) {
                        if (resultTemp.score > resultMultTemp.at(i).score) {
                            resultMultTemp.erase(resultMultTemp.begin() + i);
                        }
                        else duplicate = true;
                    }
                }
                if (!duplicate) {
                    resultMultTemp.push_back(resultTemp);
                    x += templateImg.mat.cols;
                }
            }
        }
    }

    return resultMultTemp;
}



bool fopencv::cvmtfMultipleTemplateZone(const Template& templateImg, Template& background, std::vector<Coords>& listcoords, Zone Z) {
    background.mat = extractZone(background.mat, Z);
    if (cvmtfMultipleTemplate(templateImg, background, listcoords)) {
        for (Coords coor : listcoords) {
            coor.x += Z.C1.x;
            coor.y += Z.C1.y;
        }
        return true;
    }
    else return false;
}

bool fopencv::cvmtfZone(const Template& templateImg, Template& background, Coords& Cresult, Zone Z) {

    background.mat = extractZone(background.mat, Z);
    if (cvmtfTemplate(templateImg, background, Cresult)) {
        Cresult.x += Z.C1.x;
        Cresult.y += Z.C1.y;
        return true;
    }
    else return false;

}


bool fopencv::cvmtfMultipleTemplate(const Template& templateImg, const Template& background, std::vector<Coords>& listcoords) {
    listcoords.clear();
    std::vector<Template>resultsearch = returnMultipleMatchTemplate(templateImg, background);
    if (resultsearch.empty())return false;
    else {
        for (Template res : resultsearch) {
            listcoords.push_back(res.C);
        }
        for (Coords& Ce : listcoords) {
            std::cout << "found " << templateImg.id << " X: " << Ce.x << " Y: " << Ce.y << std::endl;
        }
        return true;
    }
}


bool fopencv::cvmtfOneTemplate(const std::vector<Template>& allTempl, const Template& background, Coords& Cresult)
{
    Template resultSearch;
    for (int i = 0; i < allTempl.size(); ++i) {
        if (cvmtfTemplate(allTempl.at(i), background, Cresult))return true;
    }
    return false;
}

bool fopencv::cvmtfOneTemplate(const std::vector<Template>& allTempl, const Template& background, Template& foundTemplate, Coords& Cresult)
{
    Template resultSearch;
    for (int i = 0; i < allTempl.size(); ++i) {
        if (cvmtfTemplate(allTempl.at(i), background, Cresult)) {
            foundTemplate = allTempl.at(i);
            return true;
        }
    }
    foundTemplate = Template();
    return false;
}

bool fopencv::cvmtfOneMultipleTemplate(const std::vector<std::vector<Template>>& allTempl, const Template& background, std::vector<Coords>& Cresult)
{
    Template resultSearch;
    for (int i = 0; i < allTempl.size(); ++i) {
        if (cvmtfAllTemplate(allTempl.at(i), background, Cresult)) {
            std::cout << "Found all needed Templates\n";
            return true;
        }
    }
    return false;
}

bool fopencv::cvmtfAllTemplate(const std::vector<Template>& allTempl, const Template& background, std::vector<Coords>& Cresult)
{
    Template resultSearch;
    Coords temp;
    for (int i = 0; i < allTempl.size(); ++i) {
        if (cvmtfTemplate(allTempl.at(i), background, temp)) {
            std::cout << "Found " << allTempl.at(i).id << std::endl;
            Cresult.push_back(temp);
            continue;
        }
        else return false;
    }
    return true;
}

bool fopencv::cvmtfCompareTemplate(const Template& matgoodTemplate, const Template& background, const Template& matsimilartemplate, Coords& Cresult)
{
    std::vector<Template>tabSimilarTemplates;
    Template goodTemplate = returnOneMatchTemplate(matgoodTemplate, background);
    if (goodTemplate.score < precision)return false;
    else if (matsimilartemplate.id != goodTemplate.id) {
        tabSimilarTemplates = returnMultipleMatchTemplate(matsimilartemplate, background);
        for (int i = 0; i < tabSimilarTemplates.size(); ++i) {
            std::cout << "X: " << tabSimilarTemplates.at(i).C.x << "Y: " << tabSimilarTemplates.at(i).C.y << "  Other template: " << tabSimilarTemplates.at(i).id << "  score: " << tabSimilarTemplates.at(i).score << std::endl;
            if (tabSimilarTemplates.at(i).score > goodTemplate.score && abs(goodTemplate.C.x - tabSimilarTemplates.at(i).C.x) <= goodTemplate.mat.cols && abs(goodTemplate.C.y - tabSimilarTemplates.at(i).C.y) <= goodTemplate.mat.rows) {
                std::cout << "Other template present" << std::endl;
                return false;
            }
        }
        Cresult = goodTemplate.C;
        std::cout << "found maxVal: " << goodTemplate.score << " " << goodTemplate.id << std::endl;
        return true;
    }
    std::cout << "not found maxVal: " << goodTemplate.score << " " << goodTemplate.id << std::endl;
    return false;
}

bool fopencv::cvmtfCompareMultipleTemplate(const Template& matgoodTemplate, const Template& background, const std::vector<Template>& similartemplates, Coords& Cresult)
{

    Template goodTemplate = returnOneMatchTemplate(matgoodTemplate, background);
    if (goodTemplate.score >= precision) {
        std::vector<Template>similarTemplates;
        std::vector<std::vector<Template>>tabSimilarTemplates;
        for (int i = 0; i < similartemplates.size(); ++i) {
            if (similartemplates.at(i).id != goodTemplate.id) {
                similarTemplates = returnMultipleMatchTemplate(similartemplates.at(i), background);
                std::cout << "found " << similarTemplates.size() << " similar templates" << std::endl;
                for (int i = 0; i < similarTemplates.size(); ++i) {
                    std::cout << "Maxval: " << similarTemplates.at(i).score << std::endl;;
                    if (similarTemplates.at(i).score > goodTemplate.score && abs(goodTemplate.C.x - similarTemplates.at(i).C.x) <= goodTemplate.mat.cols && abs(goodTemplate.C.y - similarTemplates.at(i).C.y) <= goodTemplate.mat.rows) {
                        std::cout << "Other template present" << std::endl;
                        return false;
                    }
                }
            }
        }
        std::cout << "found Maxval: " << goodTemplate.score << " " << goodTemplate.id << std::endl;
        Cresult = goodTemplate.C;
        return true;
    }
    std::cout << "not found " << goodTemplate.score << " " << goodTemplate.id << std::endl;
    return false;
}

bool fopencv::cvmtfCompareMultipleTemplateZone(const Template& matgoodTemplate, Template& background, const std::vector<Template>& similartemplates, Coords& Cresult, Zone Z)
{
    background.mat = extractZone(background.mat, Z);
    if (cvmtfCompareMultipleTemplate(matgoodTemplate, background, similartemplates, Cresult)) {
        Cresult.x += Z.C1.x;
        Cresult.y += Z.C1.y;
        return true;
    }
    else return false;
}

bool fopencv::cvmtfMultipleTemplateCompareMultipleTemplate(const Template& matgoodTemplate, const Template& background, const std::vector<Template>& similartemplates, std::vector<Coords>& listcoord)
{
    listcoord.clear();
    std::vector<Template>tabGoodTemplates = returnMultipleMatchTemplate(matgoodTemplate, background);
    std::vector<Template>tabSimilarTemplates;
    for (int i = 0; i < similartemplates.size(); ++i) {
        if (similartemplates.at(i).id == matgoodTemplate.id)continue;
        tabSimilarTemplates = returnMultipleMatchTemplate(similartemplates.at(i), background);
    }
    bool semblable = false;
    for (int j = 0; j < tabGoodTemplates.size(); ++j) {
        for (int i = 0; i < tabSimilarTemplates.size(); ++i) {
            if (tabSimilarTemplates.at(i).score > tabGoodTemplates.at(j).score && abs(tabGoodTemplates.at(j).C.x - tabSimilarTemplates.at(i).C.x) <= matgoodTemplate.mat.cols && abs(tabGoodTemplates.at(j).C.y - tabSimilarTemplates.at(i).C.y) <= matgoodTemplate.mat.rows) {
                std::cout << "Other template present" << std::endl;
                semblable = true;
                break;
            }
        }
        if (!semblable)listcoord.push_back(tabGoodTemplates.at(j).C);
    }
    if (listcoord.empty()) {
        return false;
    }
    else return true;
}

bool fopencv::cvmtfMultipleTemplateCompareMultipleTemplateZone(const Template& matgoodTemplate, Template& Matbackground, const std::vector<Template>& similartemplates, std::vector<Coords>& listcoord, Zone Z)
{
    Matbackground.mat = extractZone(Matbackground.mat, Z);
    if (cvmtfMultipleTemplateCompareMultipleTemplate(matgoodTemplate, Matbackground, similartemplates, listcoord)) {
        for (int i = 0; i < listcoord.size(); ++i) {
            listcoord.at(i).x += Z.C1.x;
            listcoord.at(i).y += Z.C1.y;
        }
        return true;
    }
    else return false;
}





void fopencv::cvmtfHighestScoreZone(const cv::Mat& templates, const cv::Mat& Background, float& score, Coords& C)
{
    Coords btemp(C.x + templates.cols, C.y + templates.rows);
    Zone ztemp(C, btemp);
    cv::Mat newBackground = extractZone(Background, ztemp);
    cv::Mat result;
    cv::matchTemplate(newBackground, templates, result, cv::TM_CCOEFF_NORMED);
    double maxval;
    cv::Point maxloc;
    cv::minMaxLoc(result, NULL, &maxval, NULL, &maxloc);
    score = maxval;
    C.x = maxloc.x + ztemp.C1.x;
    C.y = maxloc.y + ztemp.C1.y;
}










void fopencv::CannyEdgeVideo(std::string videoPath) {

    cv::VideoCapture cap(videoPath);
    if (!cap.isOpened()) {
        std::cout << "Error: Unable to open the video file: " << videoPath << std::endl;
        return;
    }

    cv::namedWindow("Edge Image", cv::WINDOW_NORMAL);

    int frameCount = 0; // For debugging purposes, let's count the frames processed

    while (true) {
        cv::Mat frame;
        cap >> frame; // Read a new frame from the video

        if (frame.empty()) {
            std::cout << "End of video!" << std::endl;
            break;
        }

        cv::Mat edges;
        cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
        cv::Canny(edges, edges, 100, 200);

        cv::imshow("Edge Image", edges);

        // Break the loop if the 'q' or 'Esc' key is pressed
        char key = cv::waitKey(25);
        if (key == 'q' || key == 27) {
            std::cout << "Video playback stopped by the user!" << std::endl;
            break;
        }

        // For debugging, print frame count at regular intervals
        if (frameCount % 100 == 0) {
            std::cout << "Processed " << frameCount << " frames." << std::endl;
        }
        frameCount++;
    }

    cap.release();
    cv::destroyAllWindows();
}

void fopencv::SaveCannyEdgeVideo(const std::string& videoPath, const std::string& outputPath) {
    cv::VideoCapture cap(videoPath);
    if (!cap.isOpened()) {
        std::cout << "Error: Unable to open the video file: " << videoPath << std::endl;
        return;
    }

    // Get video properties to create a video writer
    int frameWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int frameHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    double fps = cap.get(cv::CAP_PROP_FPS);
    int codec = cv::VideoWriter::fourcc('X', '2', '6', '4'); // Change this to the desired codec (e.g., 'X', '2', '6', '4' for H.264)

    cv::VideoWriter writer(outputPath, codec, fps, cv::Size(frameWidth, frameHeight), false);

    if (!writer.isOpened()) {
        std::cout << "Error: Unable to create the video writer!" << std::endl;
        return;
    }


    while (true) {
        cv::Mat frame;
        cap >> frame; // Read a new frame from the video

        if (frame.empty()) {
            std::cout << "End of video!" << std::endl;
            break;
        }

        cv::Mat edges;
        cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
        cv::Canny(edges, edges, 100, 200);

        writer.write(edges);
    }

    cap.release();
    writer.release();
    cv::destroyAllWindows();
}

cv::Mat fopencv::performCannyEdgeDetectionFromPicture(const std::string& imagePath) {
    // Load the input image from the file path
    cv::Mat inputImage = cv::imread(imagePath);

    // Check if the input image is valid
    if (inputImage.empty()) {
        std::cerr << "Error: Unable to load the image: " << imagePath << std::endl;
        return cv::Mat();
    }

    // Apply Canny edge detection
    cv::Mat edges;
    cv::Canny(inputImage, edges, 100, 200); // You can adjust the threshold values (100 and 200) as needed

    return edges;
}




void fopencv::performCannyEdgeDetectionFromLiveCamera() {
    cv::VideoCapture cap(0); // Open the default camera (change the index if you have multiple cameras)

    if (!cap.isOpened()) {
        std::cerr << "Error: Unable to access the camera!" << std::endl;
        return;
    }

    cv::Mat frame;
    cv::namedWindow("Live Camera", cv::WINDOW_AUTOSIZE);

    while (true) {
        cap >> frame; // Capture a frame from the camera

        cv::Mat edges;
        cv::Canny(frame, edges, 100, 100); // You can adjust the threshold values (100 and 200) as needed

        cv::imshow("Live Camera", edges);

        char c = cv::waitKey(1);
        if (c == 27) // Press 'Esc' key to exit
            break;
    }

    cap.release();
    cv::destroyAllWindows();
}
