![Graffter Banner](imgs/banner.jpg)
# Revisiting Binary Local Image Description for Resource Limited Devices

This repository contains the source code of **BAD** and **HashSIFT** descriptors presented in "[Revisiting Binary Local Image Description for Resource Limited Devices](https://arxiv.org/pdf/2108.08380.pdf)". When accuracy and efficiency are both important, the descriptors in this repository offer the perfect trade-off for real-time applications and resource limited devices like smartphones, robots or drones. 

![Graffter header image](imgs/header.jpg)

## Dependencies
The code depends on OpenCV 4.
<details> 
<summary>To install OpenCV ... </summary> In Ubuntu 18.04 compile it from sources with the following instructions:

```shell script
# Install dependencies (Ubuntu 18.04)
sudo apt-get install -y build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
# Download source code
git clone https://github.com/opencv/opencv.git --branch 4.5.2 --depth 1
# Create build directory
cd opencv && mkdir build && cd build
# Generate makefiles, compile and install
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j
sudo make install
```

* NOTE: The code also compile with OpenCV 3, but without parallel for's. Thus, the description will be slower.
</details>

## Compile and Run
We provide the pre-trained execution code of BAD and HashSIFT descriptors. 
The code contains two demos. The first one estimates the fundamental matrix between 
two images of the Machine Hall 05 from [EuRoC MAV Dataset](https://projects.asl.ethz.ch/datasets/doku.php?id=kmavvisualinertialdatasets).
The demo detects feature points using ORB detector (FAST + Harris score) and describes using BAD.
We draw the RANSAC inliers with less than 3px of epipolar error.
The code can be compiled with Cmake:

```shell script
mkdir build && cd build
cmake .. && make
./stereo_demo [hashsift]
```

![](imgs/stereo-euroc-compressed.gif)

We also show a second demo that registers a pair of planar images.

```shell script
./homography_demo [hashsift]
```

The result for the provided images should be several imshows and something like this in the standard output:
```
*************** Homography estimation demo ***************
Detected features: 1000
Matched features:   64
Inliers percentage:  6.4%
```
If ORB descriptor is used instead of BAD, only 2.4% of inliers are obtained.

## References
If you use this code, you must cite our Robotics and Automation Letters paper:
```bibtex
@ARTICLE{9521740,
  author={Su\'arez, Iago and Buenaposada, Jos\'e M. and Baumela, Luis},
  journal={IEEE Robotics and Automation Letters}, 
  title={Revisiting Binary Local Image Description for Resource Limited Devices}, 
  year={2021},
  volume={},
  number={},
  pages={1-1},
  doi={10.1109/LRA.2021.3107024}}
```

## Contact and Licence
We provide a free pre-trained version of the execution code. Full execution and training code can be obtained under license, if you are interested please contact us:

* Iago Suárez ( iago.suarez@thegraffter.com ) for technical issues.
* Miguel Ángel Orellana Sainz ( miguel.orellana@thegraffter.com ) for commercial issues.

This software was developed by [The Graffter S.L.](http://www.thegraffter.com) in collaboration with the [PCR lab of the Universidad Politécnica de Madrid](http://www.dia.fi.upm.es/~pcr/research.html).
