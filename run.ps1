rm main 
clear 
g++ -std=gnu++20 main.cpp -o main 
Get-Content .\input.txt | .\main > output.txt