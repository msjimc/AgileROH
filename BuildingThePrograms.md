## AgileROHFinder and AgileROHFilter

The source code can be used to build two applications that work on either Linux or Windows computers:

```AgileROHFinder```:- which identifies autozygous regions in either next generation sequencing variant data in (uncompressed) vcf files or microarray SNP genotype data.  
or   
```AgileROHFilterer```:- which identifies autozygous regions and then creates a 2nd filtered VCF that contins variants in the autozygous regions.

## Compiling on a Linux computer

### Linux g++
Place all the files in an empty folder and navigate to the in a Bash shell terminal and issue one or bother of the commands below:

```AgileROHFinder```
 > g++ -g AffyEngine.cpp CompareRegionList.cpp AgileROHFinder.cpp GetRegions.cpp methods.cpp parameters.cpp Region.cpp SNP.cpp -o AgileROHFinder.exe 2> AgileROHFinder_error.txt

```AgileROHFilterer```
> g++ -g AffyEngine.cpp CompareRegionList.cpp AgileROHFilter.cpp GetRegions.cpp methods.cpp parameters.cpp Region.cpp SNP.cpp VCFFilter.cpp -o AgileROHFilter.exe 2> AgileROHFilter_error.txt

This should build the selected application with any errors or warnings stored in the error file.

### Windows - Visual Studio 
Create an empty C++ windows console application and select the required source code (*.cpp) and header (*.h) files. 

```AgileROHFinder```: 

AffyEngine.cpp, CompareRegionList.cpp, AgileROHFinder.cpp, GetRegions.cpp, methods.cpp, parameters.cpp, Region.cpp, SNP.cpp, and AffyEngine.h, CompareRegionList.h, GetRegions.h, methods.cpp, parameters.h, Region.h, SNP.h, dirent.h.

```AgileROHFilterer```:  
 AffyEngine.cpp, CompareRegionList.cpp, AgileROHFilter.cpp, GetRegions.cpp, methods.cpp, parameters.cpp, Region.cpp, SNP.cpp, VCFFilter.cpp and AffyEngine.h, CompareRegionList.h, GetRegions.h, methods.h, parameters.h, Region.h, SNP.h, VCFFilter.h, dirent.h.

The create the applications by selecting the Build > Batch Build menu option and selecting a release version to run on either a 64 or 32 bit computer. 