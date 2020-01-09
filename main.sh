clear
echo No joy with Python
python --version
python vision.py
echo
echo So using plain C
echo copy ...
gcc copyImage.c -o ./Results/copyImage
./Results/copyImage
echo
echo invert ...
gcc invertImage.c -o ./Results/invertImage
./Results/invertImage
echo
echo fold ...
gcc foldImage.c -o ./Results/foldImage
./Results/foldImage
