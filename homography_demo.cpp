/**
 * @copyright 2021 Xoan Iago Suarez Canosa. All rights reserved.
 * Constact: iago.suarez@thegraffter.com
 * Software developed in the PhD: Low-level vision for resource-limited devices
 */
#include "HashSIFT.h"
#include "BAD.h"

using namespace upm;

inline cv::Mat drawGoodMatches(const cv::Mat &query,
                               const cv::Mat &pattern,
                               const std::vector<cv::KeyPoint> &queryKp,
                               const std::vector<cv::KeyPoint> &trainKp,
                               std::vector<cv::DMatch> matches,
                               int maxMatchesDrawn) {
  cv::Mat outImg;

  if (query.empty() || pattern.empty()) {
    std::cerr << "ERROR in drawGoodMatches: The input image is empty." << std::endl;
    return outImg;
  }

  if (queryKp.empty() || trainKp.empty() || matches.empty()) {
    return outImg;
  }

  if (matches.size() > maxMatchesDrawn) {
    std::vector<cv::KeyPoint> emptyVector;
    std::vector<cv::DMatch> emptyVectorMatches;
    cv::drawMatches(
        query,
        emptyVector,
        pattern,
        emptyVector,
        emptyVectorMatches,
        outImg);
    matches.resize(maxMatchesDrawn);
  }

  cv::drawMatches(
      query,
      queryKp,
      pattern,
      trainKp,
      matches,
      outImg,
      CV_RGB(0, 255, 0),
      CV_RGB(255, 0, 0),
      std::vector<char>(),
      cv::DrawMatchesFlags::DEFAULT);

  cv::putText(outImg,
              std::string("Inliers: ") + std::to_string(matches.size()),
              cv::Point(20, 620),
              cv::FONT_HERSHEY_SIMPLEX,
              1,
              CV_RGB(0, 255, 0),
              2);

  return outImg;
}

int main(int argc, char *argv[]) {
  std::cout << "*************** Homography estimation demo ***************" << std::endl;

  cv::Ptr<cv::Feature2D> detector, descriptor;
  detector = cv::ORB::create(1000);
  // descriptor = cv::ORB::create(1000);
  if (argc > 1 && strcmp(argv[1], "hashsift") == 0) {
    descriptor = HashSIFT::create(1.0f, HashSIFT::SIZE_512_BITS);
  } else {
    descriptor = BAD::create(1.0f, BAD::SIZE_512_BITS);
  }

  cv::Mat patternImg = cv::imread("imgs/pattern.jpg", cv::IMREAD_GRAYSCALE);
  assert(!patternImg.empty());
  cv::resize(patternImg, patternImg, cv::Size(450, 580));

  std::vector<cv::KeyPoint> trainKps;
  cv::Mat trainDescrs;
  detector->detect(patternImg, trainKps);
  descriptor->compute(patternImg, trainKps, trainDescrs);

  auto matcher = cv::makePtr<cv::BFMatcher>(cv::NORM_HAMMING, true);

  cv::Mat queryImg = cv::imread("imgs/query.jpg", cv::IMREAD_GRAYSCALE);
  assert(!queryImg.empty());
  cv::resize(queryImg, queryImg, cv::Size(360, 640));

  // Extract feature points from input gray frame
  std::vector<cv::KeyPoint> queryKps;
  cv::Mat queryDescr;
  detector->detect(queryImg, queryKps);
  descriptor->compute(queryImg, queryKps, queryDescr);

  // Get matches with current pattern
  std::vector<cv::DMatch> noisyMatches;
  matcher->match(queryDescr, trainDescrs, noisyMatches);
  std::sort(noisyMatches.begin(), noisyMatches.end());

  std::vector<cv::DMatch> goodMatches;
  cv::Mat H;
  // If there is enough matches
  if (noisyMatches.size() >= 8) {
    // Prepare data for cv::findHomography
    std::vector<cv::Point2f> srcPts(noisyMatches.size()), dstPts(noisyMatches.size());
    for (size_t i = 0; i < noisyMatches.size(); i++) {
      srcPts[i] = trainKps[noisyMatches[i].trainIdx].pt;
      dstPts[i] = queryKps[noisyMatches[i].queryIdx].pt;
    }

    // Find homography matrix and get goodMatches mask
    std::vector<unsigned char> inliersMask(srcPts.size());
    H = cv::findHomography(srcPts, dstPts, cv::RHO, 3, inliersMask);

    //Create a vector with the better matches, the goodMatches
    for (size_t i = 0; i < inliersMask.size(); i++) {
      if (inliersMask[i]) goodMatches.push_back(noisyMatches[i]);
    }
  }

  // Do some visualization. Show good matches
  cv::Mat visualizeMatches = drawGoodMatches(
      queryImg,
      patternImg,
      queryKps,
      trainKps,
      goodMatches,
      100);
  cv::imshow("Good matches", visualizeMatches);

  // Warp the query image with the estimated transformation
  cv::Mat warped;
  cv::warpPerspective(queryImg, warped, H.inv(), patternImg.size());
  cv::imshow("Warped image", warped);

  std::cout << "Detected features: " << std::setw(4) << queryKps.size() << std::endl;
  std::cout << "Matched features: " << std::setw(4) << goodMatches.size() << std::endl;
  float ratio_inliers = goodMatches.size() / float(queryKps.size());
  std::cout << "Inliers percentage: " << std::setw(4) << ratio_inliers * 100 << "%" << std::endl;
  cv::waitKey();

  return 0;
}