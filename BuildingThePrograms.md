## AgileROHFinder and AgileROHFilter

The source code is in the [source code](source%20code/) and can be used to build two applications that work on either Linux or Windows computers:

```AgileROHFinder```:- which identifies autozygous regions in either next generation sequencing variant data in (uncompressed) vcf files or microarray SNP genotype data.  
or   
```AgileROHFilterer```:- which identifies autozygous regions using exome variant data and then creates a 2nd filtered VCF that only contains variants in the autozygous regions.

## Compiling on a Linux computer

### Linux - g++
Place all the source code files in an empty folder and navigate to it in a Bash shell terminal and issue one or bother of the commands below:

```AgileROHFinder```
 > g++ -g AffyEngine.cpp AgileROHFinder.cpp GetRegions.cpp methods.cpp parameters.cpp Region.cpp SNP.cpp -o AgileROHFinder.exe 2> AgileROHFinder_error.txt

```AgileROHFilterer```
> g++ -g AffyEngine.cpp CompareRegionList.cpp AgileROHFilter.cpp GetRegions.cpp methods.cpp parameters.cpp Region.cpp SNP.cpp VCFFilter.cpp -o AgileROHFilter.exe 2> AgileROHFilter_error.txt

This should build the selected application with any errors stored in the error file. To see all the messages replace the '2>' with '>'.

#### Compilers
The source code has been compiled on a HPC running CentOS Linux release 7.9.2009 (Core) using the 4 different versions of g++ available as shown below:
|Module|g++ version revealed with the command g++ --version|
|-|-|
|gnu/native|	g++ (GCC) 4.8.5 20150623 (Red Hat 4.8.5-44)|
|gnu/6.3.0|	g++ (GCC) 6.3.0|
|gnu/8.3.0|	g++ (GCC) 8.3.0|
|gnu/12.3.0|	g++ (GCC) 12.3.0|

Standard computer   
The source code was also compiled on a stand-alone desktop PC running an intel64 version of:  
- Fedora release 40 (Forty).   
    * The command g++ --version displayed this version data as "___g++ (GCC) 14.2.2 20240912 (Red Hat 14.2.1-3)___".  

Virtualized computers  
The host OS was Windows 11 Pro running on a Snapdragon(R) X 12 core X1E80100 @ 3.40 GHz processor and the virtualization was performed using Hyper-V. Since the host used a ARM CPU, the Linux machines where all ARM64.    

The source code was also compiled on 3 Hyper-V virtual machines running ARM64 versions of:  
- Ubuntu 24.10 - Oracular:   
    * The command g++ --version displayed this version data as "___g++ (Ubuntu 14.2.0-4ubuntu2)14.2.0___".  
- Fedora Linux 42 (Workstation Edition):  
    * The command g++ --version displayed this version data as "___g++ (GCC) 15.1.1 20250425 (Red Hat 15.1.1-1)___".   
- Debian GNU/Linux 12 (bookworm):  
    * The command g++ --version displayed this version data as "___g++ (Debian 12.2.0-14) 12.2.0.___". 


### Windows - Visual Studio 
Create an empty C++ windows console application and select the required source code (*.cpp) and header (*.h) files. 

```AgileROHFinder```: 

___*.cpp files:___ AffyEngine.cpp, AgileROHFinder.cpp, GetRegions.cpp, methods.cpp, parameters.cpp, Region.cpp, SNP.cpp   
___*.h files:___ AffyEngine.h, GetRegions.h, methods.cpp, parameters.h, Region.h, SNP.h.

```AgileROHFilterer```:  
 ___*.cpp files:___ AffyEngine.cpp, CompareRegionList.cpp, AgileROHFilter.cpp, GetRegions.cpp, methods.cpp, parameters.cpp, Region.cpp, SNP.cpp, VCFFilter.cpp  
 ___*.h files:___ AffyEngine.h, CompareRegionList.h, GetRegions.h, methods.h, parameters.h, Region.h, SNP.h, VCFFilter.h.

Then create the applications by selecting the Build > Batch Build menu option and selecting a release version to run on either a 64 or 32 bit computer. 
