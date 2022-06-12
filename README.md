<div width="100%" style="text-align: center;">
	<img class="logos-image" src="imgs/banner.jpg">
</div>

## Abstract
<p align="justify">The advent of a panoply of resource limited devices opens up new challenges in the design of computer vision algorithms with a clear compromise between accuracy and computational requirements. In this paper we address this and introduce binary image descriptors that establish new operating points in the state-of-the-art's accuracy vs. resources trade-off curve.
We revisit descriptors based on pixel differences and gradients to introduce respectively BAD (Box Average Difference), the fastest binary descriptor in the literature, and HashSIFT.
They are trained using triplet ranking loss, hard negative mining and anchor swap, combined with a new efficient feature selection algorithm.
In our experiments we evaluate the accuracy, execution time and energy consumption of the proposed descriptors. We show that they are the most accurate when confronted with competing techniques with similar computational requirements. Further, in a planar image registration, HashSIFT  performs  on  par  with  the  top deep learning-based descriptors, being several orders of magnitude more efficient.
</p>

## Video
<div style="text-align:center;">
<iframe width="100%" height="530" src="https://www.youtube.com/embed/3WxjxPjDGSQ" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
</div>

## Learning Efficient Local Descriptors

<p>
	The goal of any local feature descriptor is to learn a similarity function \( \mathcal{S}(\cdot, \cdot) \) between local features. 
	We define the training objective of our descriptors with the Triplet Ranking Loss (TRL). It brings different descriptions (\( \mathbf{a}_i \), \( \mathbf{p}_i \)) of the same scene point closer while pushing apart descriptors from other scene points \( \mathbf{n}_i \). Its benefit compared with contrastive pair-wise loss is that it is more related to the nearest neighbors matching task, where a good keypoint match is produced only if the correct corresponding keypoint is the close in descriptor distance.
</p>
<p>
	Hard Negative Mining challenges the TRL with different scene points that have the closest description. At each iteration, we choose our negative \( \mathbf{n}_i \) as the hardest in batch (i.e., the one with the smallest descriptor distance).
</p>

<div width="100%" style="text-align: center;">
	<img width="100%" src="imgs/trl_and_hnm_diagram.jpg">
</div>


## Results
Here we add some extra results showing the performance of the proposed descriptors with other approaches in the State of the Art:

<div class="bootstrap-wrapper" style="text-align: center;">
    <div class="container">
        <div class="row align-self-center"> <!-- Hidden on small screens -->
            <div class="col-md-6">
            	<h4>BAD-256 Reconstruction of Madrid Metropolis</h4>
            	<video width="100%" autoplay muted>
				  <source src="imgs/bad256_mad_metropolis_reconstruction.mp4" type="video/mp4">
				Your browser does not support the video tag.
				</video>
            </div>
            <div class="col-md-6">
            	<h4>BAD-512 Fundamental matrix estimation (EuRoC)</h4>
            	<img class="euroc-img" width="100%" src="imgs/euroc_datase_fundamental_mat.gif">
            </div>
        </div>
    </div>
</div>


### ETH Benchmark
Full results table in ETH Benchmark:


| | # Registered | # Sparse Points | # Obervations | Track Length | Reproj. Error | # Inliner Pairs | # Inliner Matches | # Dense Points |
|---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| <b>Fountain  (11 images) </b>  |  |  |  |  |  |  |  |  |
| ORB | 11 | 15001 | 71171 | 4.744417 | 0.384306 | 55 | 125033 | 306277 |
| BEBLID-256 | 11 | 15539 | 74044 | 4.765043 | 0.394489 | 55 | 133838 | 303771 |
| LATCH | 11 | 15384 | 73907 | 4.804147 | 0.401214 | 55 | 135643 | 307421 |
| BAD-256 | 11 | 15574 | 74404 | 4.77745 | 0.397276 | 55 | 135943 | 307932 |
| BAD-512 | 11 | 15741 | 75613 | 4.80357 | 0.407335 | 55 | 141365 | 305564 |
| RSIFT | 11 | 16167 | 77879 | 4.817158 | 0.433049 | 55 | 154688 | 307027 |
| Binboost | 11 | 15391 | 73011 | 4.743746 | 0.397668 | 55 | 129571 | 302792 |
| LDAHash-DIF | 11 | 15134 | 70865 | 4.682503 | 0.389491 | 55 | 122713 | 304385 |
| HashSIFT-256 | 11 | 16086 | 77507 | 4.818289 | 0.427431 | 55 | 149103 | 306132 |
| HashSIFT-512 | 11 | 16385 | 79082 | 4.826488 | 0.438388 | 55 | 156135 | 305520 |
| TFeat-m* | 11 | 16278 | 78880 | 4.845804 | 0.431607 | 55 | 153725 | 305073 |
| HardNet | 11 | 17071 | 83973 | 4.919044 | 0.477603 | 55 | 183331 | 305701 |
| CDbin-256b | 11 | 16607 | 81360 | 4.899139 | 0.455184 | 55 | 168946 | 305534 |
| <b>Herzjesu (8 images)</b> |  |  |  |  |  |  |  |  |
| ORB | 8 | 7619 | 31475 | 4.13112 | 0.41019 | 28 | 46625 | 237948 |
| BEBLID-256 | 8 | 7922 | 33414 | 4.217874 | 0.429793 | 28 | 51720 | 241862 |
| LATCH | 8 | 7871 | 33058 | 4.199975 | 0.430669 | 28 | 50739 | 240523 |
| BAD-256 | 8 | 8056 | 34038 | 4.225174 | 0.435542 | 28 | 53059 | 242998 |
| BAD-512 | 8 | 8220 | 34893 | 4.244891 | 0.448551 | 28 | 55866 | 236171 |
| RSIFT | 8 | 8533 | 36279 | 4.251611 | 0.476318 | 28 | 60808 | 241740 |
| Binboost | 8 | 7630 | 32009 | 4.195151 | 0.454498 | 28 | 47763 | 233824 |
| LDAHash-DIF | 8 | 7912 | 32683 | 4.130814 | 0.435268 | 28 | 48765 | 244861 |
| HashSIFT-256 | 8 | 8560 | 36392 | 4.251402 | 0.473129 | 28 | 59246 | 240978 |
| HashSIFT-512 | 8 | 8769 | 37376 | 4.262288 | 0.479877 | 28 | 62297 | 240154 |
| TFeat-m* | 8 | 8631 | 36727 | 4.255243 | 0.476186 | 28 | 60675 | 239675 |
| HardNet | 8 | 9444 | 40483 | 4.286637 | 0.517284 | 28 | 74867 | 239362 |
| CDbin-256b | 8 | 8997 | 38650 | 4.295876 | 0.497678 | 28 | 67802 | 242179 |
| <b>South Building (128 images)</b> |  |  |  |  |  |  |  |  |
| ORB | 128 | 137627 | 695789 | 5.055614 | 0.496237 | 8128 | 2285089 | 2137625 |
| BEBLID-256 | 128 | 141604 | 710290 | 5.016031 | 0.500718 | 8128 | 2347648 | 2134091 |
| LATCH | 128 | 139584 | 716808 | 5.135316 | 0.521234 | 8128 | 2345677 | 2144368 |
| BAD-256 | 128 | 145771 | 727953 | 4.993812 | 0.515675 | 8128 | 2435017 | 2145993 |
| BAD-512 | 128 | 148491 | 744604 | 5.014472 | 0.527237 | 8128 | 2533879 | 2127316 |
| RSIFT | 128 | 155195 | 798456 | 5.144856 | 0.58171 | 8128 | 2836156 | 2139778 |
| Binboost | 128 | 135186 | 690751 | 5.109634 | 0.510165 | 8128 | 2220460 | 2156847 |
| LDAHash-DIF | 128 | 141248 | 705928 | 4.997791 | 0.511755 | 8128 | 2469511 | 2132395 |
| HashSIFT-256 | 128 | 149102 | 764699 | 5.128697 | 0.563444 | 8128 | 2718812 | 2116461 |
| HashSIFT-512 | 128 | 156888 | 798948 | 5.092474 | 0.581466 | 8128 | 2904787 | 2142022 |
| Tfeat-m* | 128 | 152834 | 775159 | 5.071902 | 0.574171 | 8128 | 2721956 | 2149925 |
| HardNet | 128 | 168536 | 878847 | 5.214595 | 0.642522 | 8128 | 3344759 | 2122914 |
| CDbin-256b | 128 | 160589 | 832281 | 5.182678 | 0.616106 | 8128 | 3124870 | 2128460 |
| <b>Madrid Metropolis (1344 images) </b> |  |  |  |  |  |  |  |  |
| ORB | 457 | 135826 | 576138 | 4.241736 | 0.641296 | 898475 | 77323855 | 1085693 |
| BEBLID-256 | 549 | 174257 | 705651 | 4.049484 | 0.656167 | 898491 | 78223028 | 1153261 |
| LATCH | 573 | 186886 | 759581 | 4.064408 | 0.655908 | 898825 | 66395879 | 1245053 |
| BAD-256 | 600 | 192638 | 789466 | 4.098184 | 0.675328 | 898344 | 72555880 | 1236144 |
| BAD-512 | 622 | 189523 | 812243 | 4.285723 | 0.677531 | 898327 | 68242893 | 1268840 |
| RSIFT | 729 | 286519 | 1136306 | 3.965901 | 0.678011 | 898184 | 77745627 | 1349061 |
| Binboost | 514 | 143622 | 629993 | 4.386466 | 0.668252 | 897792 | 67946197 | 1129936 |
| LDAHash-DIF | 592 | 233862 | 804944 | 3.441961 | 0.642139 | 898544 | 95827306 | 1046695 |
| HashSIFT-256 | 720 | 298920 | 1075450 | 3.597785 | 0.667772 | 898464 | 88150278 | 1202895 |
| HashSIFT-512 | 720 | 305237 | 1160738 | 3.802743 | 0.686795 | 898459 | 87769325 | 1387138 |
| TFeat-m* | 690 | 262790 | 986470 | 3.753834 | 0.677615 | 897709 | 75823683 | 1233791 |
| HardNet | 849 | 359610 | 1438909 | 4.001304 | 0.701354 | 898257 | 79144113 | 1436234 |
| CDbin-256b | 769 | 260690 | 1108018 | 4.250328 | 0.696556 | 898274 | 79222034 | 1347656 |

# Citation

If you use this project please cite:

```
@article{suarez2021revisiting,
  title={Revisiting Binary Local Image Description for Resource Limited Devices},
  author={Su{\'a}rez, Iago and Buenaposada, Jos{\'e} M and Baumela, Luis},
  journal={IEEE Robotics and Automation Letters},
  volume={6},
  number={4},
  pages={8317--8324},
  year={2021},
  publisher={IEEE}
}

```