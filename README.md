# Depth-Estimation for Embedded devices-
Project for depth estimation on embedded devices contianing different code snippets using different variations of different stereo matching algorithms: Block Matching(BM), Semi-Global Block Matching, Graph cuts, Iterated conditional mode , Belief propagation, Tree weighted passing. The comparison of the SM algorithm's code, available in this repository has been modified with some openMP directives for parallel processing. However, the original code is also availble in [here](http://vision.middlebury.edu/MRF/code/). For comparison of stereo matching algorithms, the anchor paper is [this](https://www.cs.cornell.edu/~rdz/Papers/SZSVKATR.pdf).

### Work
This [thesis](https://www.dropbox.com/s/jfxopy60leqtw76/Depth_Estimation_for%20embedded_devices_thesis.pdf?dl=0) for this project can be referred for better understanding.

### Obstacle detection -
For Obstacle detection with toycar, we used [libuvc](https://github.com/ktossell/libuvc) tool for streaming data(images/video) from the [stero camera](https://leopardimaging.com/product/li-usb30-v024stereo/).

### Data -
The data has been picked up from [middlebury site](http://vision.middlebury.edu/stereo/data/)

### Relevant Material-
The relevant material regarding the cameras, algorithms, embedded devices and other tutorials is available [here](https://www.dropbox.com/sh/144i4kgtncedhd7/AACV2EH-SDpGCve5avV2fwy4a?dl=0)
