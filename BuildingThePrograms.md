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
The source code has been compiled on a HPC running __CentOS Linux release 7.9.2009 (Core)__ using the 4 different versions of g++ available as shown below:
|Module|g++ version revealed with the command g++ --version|
|-|-|
|gnu/native|__g++ (GCC) 4.8.5 20150623 (Red Hat 4.8.5-44)__|
|gnu/6.3.0|	__g++ (GCC) 6.3.0__|
|gnu/8.3.0|	__g++ (GCC) 8.3.0__|
|gnu/12.3.0|__g++ (GCC) 12.3.0__|

The source code was also compiled on a second HPC running **Rocky Linux 9.4 (Blue Onyx)** using the 3 different versions of g++ available as shown below:
|Module|g++ version revealed with the command g++ --version|
|-|-|
|Default installation|__g++ (GCC) 11.4.1 20231218 (Red Hat 11.4.1-3)__|
|gcc/13.2.0|__g++ (GCC) 13.2.0__|
|gcc/14.2.0 |__g++ (GCC) 14.2.0__|


Standard computer   
The source code was also compiled on a stand-alone desktop PC running an intel64 version of:  
- __Fedora release 40 (Forty)__.   
    * The command g++ --version displayed this version data as "__g++ (GCC) 14.2.2 20240912 (Red Hat 14.2.1-3)__".  

Virtualized computers  
The host OS was Windows 11 Pro running on a Snapdragon(R) X 12 core X1E80100 @ 3.40 GHz processor and the virtualization was performed using Hyper-V. Since the host used a ARM CPU, the Linux machines where all ARM64.    

The source code was also compiled on 3 Hyper-V virtual machines running ARM64 versions of:  
- __Ubuntu 24.10 - Oracular__:   
    * The command g++ --version displayed this version data as "__g++ (Ubuntu 14.2.0-4ubuntu2)14.2.0__".  
- __Fedora Linux 42 (Workstation Edition)__:  
    * The command g++ --version displayed this version data as "__g++ (GCC) 15.1.1 20250425 (Red Hat 15.1.1-1)__".   
- __Debian GNU/Linux 12 (bookworm)__:  
    * The command g++ --version displayed this version data as "__g++ (Debian 12.2.0-14) 12.2.0.__". 
- __Rocky Linux 9.5 (Blue Onyx)__:
    * The command g++ --version displayed this version data as "__g++ (GCC) 11.5.0 20240719 (Red Hat 11.5.0-5)__". 
- __openSuse Tumbleweed__:
    * The command g++ --version displayed this version data as "__g++ (SUSE Linux) 14.2.1 20250430 [revision 3418d740b344e0ba38022f3bed90540ec3de35dd]__". 

### Windows - Visual Studio 
Create an empty C++ windows console application and select the required source code (*.cpp) and header (*.h) files. 

```AgileROHFinder```: 

___*.cpp files:___ AffyEngine.cpp, AgileROHFinder.cpp, GetRegions.cpp, methods.cpp, parameters.cpp, Region.cpp, SNP.cpp   
___*.h files:___ AffyEngine.h, GetRegions.h, methods.cpp, parameters.h, Region.h, SNP.h.

```AgileROHFilterer```:  
 ___*.cpp files:___ AffyEngine.cpp, CompareRegionList.cpp, AgileROHFilter.cpp, GetRegions.cpp, methods.cpp, parameters.cpp, Region.cpp, SNP.cpp, VCFFilter.cpp  
 ___*.h files:___ AffyEngine.h, CompareRegionList.h, GetRegions.h, methods.h, parameters.h, Region.h, SNP.h, VCFFilter.h.

Then create the applications by selecting the Build > Batch Build menu option and selecting a release version to run on either a 64 or 32 bit computer. 
