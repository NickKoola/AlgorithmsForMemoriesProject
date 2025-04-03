# Finding the closest pair in a set of binary codes for both Hamming distance and Levenshtein

This project goes over tackling the issue of finding closest pair in a non traditional distances Hamming and Levnshtein.
The code and papers for both metrics was initialy combined but as their research and handling split apart, we decided to take challenge them one at a time.

## Getting Started
Both topic's papers are at the root directory. The codes for the seperated topics are under "Hamming code" and "Levenshtein code". 
Each folder is it's own complete project and contain the source code and all necessary files to compile them including makefile.
The implementation between both sub-projects was changed a bit where Hamming code used the standard lib string class to represent the binary codes,
where the Levenshtein part used numbers to represent them as the Levenshtein metric is more complex, and we prefered in the latter to go for faster results in expense for readability as some of our tests took a lot of time otherwise(all deletion substitution and insertion operations were converted to bitwise operations).

Thank you for your time.
