/**
 * @copyright 2021 Xoan Iago Suarez Canosa. All rights reserved.
 * Constact: iago.suarez@thegraffter.com
 * Software developed in the PhD: Low-level vision for resource-limited devices
 */
#include <opencv2/opencv.hpp>
#include "BAD.h"
#include "HashSIFT.h"

using namespace upm;

inline cv::Mat drawGoodMatches(const cv::Mat &query,
                               const cv::Mat &pattern,
                               const std::vector<cv::KeyPoint> &queryKp,
                               const std::vector<cv::KeyPoint> &trainKp,
                               const std::vector<cv::DMatch> &matches) {
  cv::Mat outImg;

  if (query.empty() || pattern.empty()) {
    std::cerr << "ERROR in drawGoodMatches: The input image is empty." << std::endl;
    return outImg;
  }

  if (queryKp.empty() || trainKp.empty() || matches.empty()) {
    return outImg;
  }

  cv::drawMatches(query, queryKp, pattern, trainKp, matches, outImg,
                  CV_RGB(0, 255, 0), CV_RGB(255, 0, 0),
                  std::vector<char>(), cv::DrawMatchesFlags::DEFAULT);

  cv::putText(outImg,
              std::string("Inliers: ") + std::to_string(matches.size()),
              cv::Point(20, query.rows - 20),
              cv::FONT_HERSHEY_SIMPLEX,
              1,
              CV_RGB(0, 255, 0),
              2);

  return outImg;
}

int main(int argc, char *argv[]) {
  std::cout << "*********** Fundamental matrix estimation demo ***********" << std::endl;

  cv::Mat img1 = cv::imread("imgs/1403638539877829376.png", cv::IMREAD_GRAYSCALE);
  cv::Mat img2 = cv::imread("imgs/1403638543027829504.png", cv::IMREAD_GRAYSCALE);
  assert(!img1.empty() && !img2.empty());

  auto detector = cv::ORB::create(1000);
  cv::Ptr<cv::Feature2D> descriptor;
  // descriptor = cv::ORB::create();
  if (argc > 1 && strcmp(argv[1], "hashsift") == 0) {
    descriptor = HashSIFT::create(1.0f, HashSIFT::SIZE_256_BITS);
  } else {
    descriptor = BAD::create(1.0f, BAD::SIZE_256_BITS);
  }

  auto matcher = cv::BFMatcher::create(cv::NORM_HAMMING, true);

  std::vector<cv::KeyPoint> kps1, kps2;
  cv::Mat descrs1, descrs2;
  std::vector<cv::DMatch> matches12;

  // Detect features
  detector->detect(img1, kps1);
  detector->detect(img2, kps2);

  // Describe each detected feature with BAD
  descriptor->compute(img1, kps1, descrs1);
  descriptor->compute(img2, kps2, descrs2);

  matcher->match(descrs1, descrs2, matches12);

  // Select the matches points
  std::vector<cv::Point2f> matched_pts1, matched_pts2;
  for (auto &m: matches12) {
    matched_pts1.push_back(kps1[m.queryIdx].pt);
    matched_pts2.push_back(kps2[m.trainIdx].pt);
  }

  // Compute the fundamental matrix that relates both images
  cv::Mat f_mask;
  cv::Mat F = cv::findFundamentalMat(matched_pts1, matched_pts2, cv::FM_RANSAC, 3., 0.99, f_mask);

  // Select the matches that are RANSAC inliers
  std::vector<cv::DMatch> good_matches;
  for (int i = 0; i < matched_pts1.size(); i++)
    if (f_mask.at<uchar>(i)) good_matches.push_back(matches12[i]);

  // Do some visualization. Show matches with less than 3px epipolar error
  cv::Mat visualize_matches = drawGoodMatches(
      img1,
      img2,
      kps1,
      kps2,
      good_matches);
  cv::imshow("Fundamental matches", visualize_matches);
  cv::waitKey();

  return 0;
}