clear
echo No joy with Python
python --version
python vision.py
echo
echo So using plain C
echo copy ...
gcc copyImage.c -o copyImage
./copyImage
echo
echo invert ...
gcc invertImage.c -o invertImage
./invertImage
