clear
echo No joy with Python
python --version
python vision.py
echo
echo So using plain C
echo copy ...
gcc ./Source/copyImage.c -o ./Results/copyImage
./Results/copyImage
echo
echo invert ...
gcc ./Source/invertImage.c -o ./Results/invertImage
./Results/invertImage
echo
echo fold ...
gcc ./Source/foldImage.c -o ./Results/foldImage
./Results/foldImage
echo
echo rotate ...
gcc ./Source/rotateImage.c -o ./Results/rotateImage
./Results/rotateImage
echo
echo threshold ...
gcc ./Source/thresholdImage.c -o ./Results/thresholdImage
./Results/thresholdImage
echo
echo blurring ...
gcc ./Source/blurImage.c -o ./Results/blurImage
./Results/blurImage
echo
echo edge detecting ...
gcc ./Source/edgedetectImage.c -o ./Results/edgedetectImage
./Results/edgedetectImage
echo
echo brightening ...
gcc ./Source/brightenImage.c -o ./Results/brightenImage
./Results/brightenImage
echo
echo red inversion ...
gcc ./Source/redImage.c -o ./Results/redImage
./Results/redImage
